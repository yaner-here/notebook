# PyTorch

参考书籍：

- PyTorch深度学习实战 [豆瓣](https://book.douban.com/subject/35776474/) [异步社区](https://www.epubit.com/bookDetails?id=UBc833a5819209)

# §0 背景知识

## §0.1 代码模版与编码习惯

```python
%matplotlib inline
from matplotlib import pyplot as plt
import numpy as np

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

torch.set_printoptions(edgeitems=2)
torch.manual_seed(123)
```

习惯上，我们用以下规则对变量命名：

- `_t`：存储在CPU中的张量
- `_g`：存储在GPU中的张量
- `_a`：Numpy数组

# §1 张量

PyTorch使用的数据结构称为张量（Tensor）。它使用的API与Numpy相似性很高，但是在Numpy的基础上支持GPU加速和分布式计算。

## §1.1 张量创建

张量与多维数组的概念类似，都能将向量和矩阵推广到任意维度。

我们可以用`torch.ones()`创建一个值全为`1`的张量：

```python
>>> import torch

>>> torch.ones(3)
tensor([1., 1., 1.])
```

我们可以用`torch.zeros()`创建一个值全为`0`的张量：

```python
>>> import torch

>>> torch.zeros((2,3))
tensor([[0., 0., 0.],
        [0., 0., 0.]])
```

我们还可以给`torch.tensor()`传入一个列表，创建指定值的张量：

```python
>>> torch.tensor([[2, 1, 4, 3], [1, 2, 3, 4], [4, 3, 2, 1]])
tensor([[2, 1, 4, 3], 
        [1, 2, 3, 4], 
        [4, 3, 2, 1]])
```

对张量的索引还是张量，我们可以用`.item()`方法或`float()`强制转换得到原始的浮点数：

```python
>>> torch.ones(3)[0]
tensor(1.)

>>> torch.ones(3)[0].item()
1.0

>>> float(torch.ones(3)[0])
1.0
```

`torch.Tensor.shape`属性负责返回该张量在每个维度上的长度。

```python
>>> torch.ones((2,3)).shape
torch.Size([2, 3])
```

## §1.2 张量索引

张量索引的语法与列表索引完全一致：

```python
>>> a = torch.arange(12).reshape(3,4)

>>> a 
tensor([[ 0,  1,  2,  3],
        [ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])

>>> a[:] # 所有元素
tensor([[ 0,  1,  2,  3],
        [ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])

>>> a[0:2] # 索引位于区间[0,2)之内的元素
tensor([[0, 1, 2, 3],
        [4, 5, 6, 7]])

>>> a[1:] # 索引位于区间[1,∞)之内的元素
tensor([[ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])

>>> a[:2] # 索引位于区间[-∞,2)之内的元素
tensor([[0, 1, 2, 3],
        [4, 5, 6, 7]])

>>> a[:-1] # 索引位于区间[-∞,LENGTH-1)之内的元素
tensor([[0, 1, 2, 3],
        [4, 5, 6, 7]])

>>> a[0:2:2] # for(int i=0; i<2 ; i+=2)
tensor([[0, 1, 2, 3]])
```

如果张量是多维的，我们在使用索引访问张量的元素时，可以只使用一次`[]`，并直接为其传入一个`tuple`：

```python
>>> a = torch.ones((2,3))

>>> a[1][2]
tensor(1.)

>>> a[1,2]
tensor(1.)

>>> a[(1,2)]
tensor(1.)
```

在此基础上，我们可以给`tuple`传入类似的`:`索引语法：

```python
>>> a[0:3:2, :] 
tensor([[ 0,  1,  2,  3],
        [ 8,  9, 10, 11]])

>>> a[0:3:2, 1]
tensor([1, 9])
```

`torch.Tensor[None]`用于包裹当前的张量，形成大小为`1`的新张量：

```python
>>> a 
tensor([[ 0,  1,  2,  3],
        [ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])

>>> a[None] 
tensor([[[ 0,  1,  2,  3],
         [ 4,  5,  6,  7],
         [ 8,  9, 10, 11]]])

>>> a[None][None] 
tensor([[[[ 0,  1,  2,  3],
          [ 4,  5,  6,  7],
          [ 8,  9, 10, 11]]]])

>>> a[None,None] 
tensor([[[[ 0,  1,  2,  3],
          [ 4,  5,  6,  7],
          [ 8,  9, 10, 11]]]])

>>> a[None,2]
tensor([[ 8,  9, 10, 11]])

>>> a[2,None]
tensor([[ 8,  9, 10, 11]])
```

除了NumPy式的索引以外，我们还可以使用PyTorch提供的高级索引。**高级索引的本质是掩码**。例如现在有一个二维张量，我们要提取其中一些不连续的行，要提取的行序号有一个布尔型一维张量掩码给出，我们就可以这样做：

```python
>>> data = torch.arange(50).reshape((10,5))
>>> mask = (torch.randn(10) > 0.5)

>>> data[mask]
tensor([[ 5,  6,  7,  8,  9],
        [10, 11, 12, 13, 14],
        [25, 26, 27, 28, 29],
        [45, 46, 47, 48, 49]])
```

## §1.3 张量命名

在实际工程中，我们往往要处理高维张量。有时我们很容易混淆不同维度的含义。

```python
# 20张1024×768的RGB图像
>>> img_batch = torch.randn(20, 3, 1024, 768)
```

乍一看似乎也没那么复杂。但是一旦涉及到运算，程序就会混乱起来。以下面的任务为例：给定一个`shape=(20,3,1024,768)`的`img_batch`数据集，和一个`shape=(3,)`的RGB权重，求该数据集的灰度图像：

```python
img_batch = torch.randn(20, 3, 1024, 768)
weight = torch.tensor([0.3, 0.5, 0.2])

# 转置成列向量 torch.Shape[(3)] -> torch.Shape([3,1,1])
unsqueezed_weight = weight.unsqueeze(-1).unsqueeze_(-1)

# torch.Shape([20,3,1024,768]) × torch.Shape([3,1,1]) 自动扩张
# 1. 低维向高维补齐，在前面加上维度1，得到[20,3,1024,768]×[1,3,1,1]
# 2. 比较第一维：1能补齐到20，可以扩张
# 3. 比较第二维：3=3，无需扩张
# 4. 比较第三维、第四维，同理
# 乘法得到的结果为[20,3,1024,768]，取倒数第三列相加即可
img_gray_batch = (img_batch * unsqueezed_weight).sum(-3)
```

PyTorch对此的解决方案是：提供`torch.einsum()`。它接受一种索引迷你语言。[TIM ROCKTÄSCHEL](https://rockt.github.io/2018/04/30/einsum)的博客对此有详细的介绍，这里我们就先略过不谈。但是从下面的例子来看，想要掌握它并不容易：

```python
img_gray_batch = torch.einsum('...chw,c->...hw', img_batch, weight)
```

后来，PyTorch 1.3引入了张量命名，旨在解决这一问题。我们可以给函数传递一个`names: dict[str]`来给各个维度命名：

```python
>>> img_batch = torch.randn(20, 3, 1024, 768, names=['batch', 'channel', 'width', 'height'])
<ipython-input-4-8a01d359a276>:1: UserWarning: Named tensors and all their associated APIs are an experimental feature and subject to change. Please do not use them for anything important until they are released as stable. (Triggered internally at ..\c10/core/TensorImpl.h:1903.)
  img_batch = torch.randn(20, 3, 1024, 768, names=['batch', 'channel', 'width', 'height'])
```

我们也可以使用`torch.Tensor.refine_names(*names)`对一个现有的无名张量新建命名，也可以使用`torch.Tensor.rename(*names, **rename_map)`进行重命名：

```python
>>> torch.randn(20, 3, 1024, 768).refine_names('batch', 'channel', 'width', 'height')
tensor([[[[-0.5621, -1.6498, -1.0574,  ...,  0.9333, -0.5680, -2.3511],
          ...,
          [-0.2888, -0.7668,  0.2727,  ...,  0.7270, -0.1783, -1.2426]]]],
       names=('batch', 'channel', 'width', 'height'))

>>> img_batch.refine_names(..., 'x', 'y') # ×，refine_names()只能用于新建命名，而不是重命名
RuntimeError: refine_names: cannot coerce Tensor['batch', 'channel', 'width', 'height'] to Tensor['batch', 'channel', 'x', 'y'] because 'width' is different from 'x' at index 2

>>> torch.randn(100, 3, 1024, 768, names=['batch', 'channel', 'width', 'height']).rename(width="x", height="y")
tensor([[[[ 1.0991e+00, -2.3605e-01,  2.5031e+00,  ...,  7.0446e-01,
		  ...,
            5.5866e-01,  9.6926e-01]]]], names=('batch', 'channel', 'x', 'y'))

# torch.Tensor.rename()传入一个None，清空所有命名
>>> torch.randn(100, 3, 1024, 768, names=['batch', 'channel', 'width', 'height']).rename(None)
tensor([[[[ 1.0991e+00, -2.3605e-01,  2.5031e+00,  ...,  7.0446e-01,
		  ...,
            5.5866e-01,  9.6926e-01]]]], names=(None, None, None, None))
```

> 注意：`refine_names()`的返回值是改名后的`torch.Tensor`实例，该实例与原实例共享同一块内存。所以推荐使用`a = refine_names(a)`的语法，以彻底完成改名。

或者直接更改`torch.Tensor.names: list`变量，实现命名与重命名：

```python
>>> import torch

>>> img_batch = torch.randn(20, 3, 1024, 768, names=['batch','channel','width','height'])
<ipython-input-2-675797e5aa01>:1: UserWarning: Named tensors and all their associated APIs are an experimental feature and subject to change. Please do not use them for anything important until they are released as stable. (Triggered internally at ..\c10/core/TensorImpl.h:1903.)
  img_batch = torch.randn(20, 3, 1024, 768, names=['batch','channel','width','height'])

>>> img_batch.names = [None, None, 'x', 'y']

>>> img_batch
<ipython-input-2-675797e5aa01>:1: UserWarning: Named tensors and all their associated APIs are an experimental feature and subject to change. Please do not use them for anything important until they are released as stable. (Triggered internally at ..\c10/core/TensorImpl.h:1903.)
  img_batch = torch.randn(20, 3, 1024, 768, names=['batch','channel','width','height'])
tensor([[[[ 2.9544,  0.7406,  1.0776,  ...,  1.5093, -1.3728,  1.8298],
          ...,
          [-0.0891,  0.6877,  0.3349,  ...,  1.4525,  2.5378, -1.0757]]]],
       names=(None, None, 'x', 'y'))
```

至此，我们可以用命名张量求出RGB加权的灰度图像，它的形式非常简洁：

```python
import torch

img_batch = torch.randn(20, 3, 1024, 768, names=['batch', 'channel', 'width' ,'height'])
weight = torch.tensor([0.3, 0.5, 0.2], names=['channel'])

# ([3]) -> ([1,3,3,1])
weight_aligned = weight.align_as(img_batch)

img_gray_batch = (img_batch * weight_aligned).sum('channel')
```

## §1.4 张量的数据类型

一个张量只能存储一批数据类型相同的数据。PyTorch支持的部分数据类型如下所示：

| `torch.dtype`数据类型(部分)    | 作用           | 说明    |
| ------------------------------ | -------------- | ------- |
| `torch.float32`/`torch.float`  | 单精度浮点数   | 缺省    |
| `torch.float64`/`torch.double` | 双精度浮点数   |         |
| `torch.float16`/`torch.half`   | 半精度浮点数   | GPU独占 |
| `torch.int8`                   | 8位有符号帧数  |         |
| `torch.uint8`                  | 8位无符号整数  |         |
| `torch.int16`/`torch.short`    | 16位有符号整数 |         |
| `torch.int32`/`torch.int`      | 32位有符号整数 |         |
| `torch.int64`/`torch.long`     | 64位有符号整数 | 缺省    |
| `torch.bool`                   | 布尔数         |         |

我们可以通过给`torch.Tensor`的构造函数传递`dtype`参数，来指定张量的数据类型：

```python
>>> a = torch.ones(10, dtype=torch.double)
tensor([1., 1., 1., 1., 1., 1., 1., 1., 1., 1.], dtype=torch.float64)
```

也可以对张量实例使用对应类型的转换方法：

```python
>>> a.short()
tensor([1, 1, 1, 1, 1, 1, 1, 1, 1, 1], dtype=torch.int16)
```

或者在张量实例的`.to()`方法中指定数据类型：

```python
>>> a.to(torch.int8)
tensor([1, 1, 1, 1, 1, 1, 1, 1, 1, 1], dtype=torch.int8)

>>> a.to(dtype=torch.float16)
tensor([1., 1., 1., 1., 1., 1., 1., 1., 1., 1.], dtype=torch.float16)
```

## §1.5 张量的存储视图

张量中的数据储存在连续的内存块中，由`torch.Storage`实例统一管理。张量只是这片内存块的一个视图，因此多个张量可以索引同一存储区。

```python
>>> a = torch.tensor([[[1,2],[3,4],[5,6]]])

>>> type(a.storage())
torch.storage.TypedStorage

>>> a.storage()
 1
 2
 3
 4
 5
 6
[torch.storage.TypedStorage(dtype=torch.int64, device=cpu) of size 6]
```

我们也可以直接修改存储区的值：

```python
>>> a.storage()[0] = 999

>>> a
tensor([[[999,   2],
         [  3,   4],
         [  5,   6]]])
```

## §1.6 张量元数据

为了在存储区中建立索引，张量需要一些定义自己的信息，统称为元数据，包括形状、偏移量、步长。

- 形状：张量在每个纬度上有多少个元素
- 偏移量：某个元素相对张量中第一个元素的索引
- 步长：为了获得下一个元素需要跳过的元素数量

```python
>>> a = torch.tensor([[1,2],[3,4],[5,6]])

>>> a[2].size()
torch.Size([2])

>>> a[2].storage_offset() # 偏移量
4

>>> a.stride() # 步长
(2, 1)
```

访问一个二维张量中的第$(i,j)$个元素，其实是在访问位于$\text{首地址}+\text{stride[0]}\times i+\text{stride}[1]\times j$的元素。

例如，给定下列二维张量，其步长为$(2,1)$，则转置后的步长为$(1,2)$：

```python
>>> a = torch.tensor([[1,2],[3,4],[5,6]])
# 存储区为: 1 2 3 4 5 6
>>> a.stride()
(2, 1)

>>> a.to().stride()
(1, 2)
```

## §1.7 连续张量

在[§1.6 张量元数据](##§1.6 张量元数据)一节中，我们已经知道了张量步长的最后一维`torch.Tensor(...).stride()[-1]`并不总是$1$。这使得该张量对应的视图在存储区上不连续。我们可以用`torch.Tensor(...).is_contiguous()`方法来验证这一点：

```python
>>> a = torch.randn((20,5,2))

>>> a.is_contiguous()
True

>>> a.transpose(0,2).is_contiguous()
False
```

`torch.Tensor(...).contiguous()`可以**另外开辟一块存储区**，对非连续张量使用的数据进行重排，使其变成连续张量：

```python
>>> a = torch.randn((20,5,2))
	a_T = a.transpose(0,2)

>>> print(a.shape, a.stride(), a.is_contiguous(), sep=' '*4)
	print(a_T.shape, a_T.stride(), a_T.is_contiguous(), sep=' '*4)
torch.Size([20, 5, 2])    (10, 2, 1)    True
torch.Size([2, 5, 20])    (1, 2, 10)    False

>>> a_T_contious = a_T.contiguous()

>>> print(a.shape, a.stride(), a.is_contiguous(), sep=' '*4)
	print(a_T.shape, a_T.stride(), a_T.is_contiguous(), sep=' '*4)
	print(a_T_contious.shape, a_T_contious.stride(), a_T_contious.is_contiguous(), sep=' '*4)
torch.Size([20, 5, 2])    (10, 2, 1)    True
torch.Size([2, 5, 20])    (1, 2, 10)    False
torch.Size([2, 5, 20])    (100, 20, 1)    True
```

## §1.8 张量的存储位置

PyTorch支持将张量在以下位置存储和计算：

- 在CPU上计算，存储在内存中
- 在Nvidia GPU（CUDA）上计算，存储在显存中
- 在AMD GPU（ROCm）上计算，存储在显存中
- 在Google TPU上计算，存储在显存中

张量数据在计算机上的位置由其`device`属性指定，默认情况是CPU：

```python
>>> a = torch.randn((20,5,2))
>>> a_T = a.transpose(0,2)

>>> type(a.device), a.device
(torch.device, device(type='cpu'))
```

我们可以在创建张量时或使用`to()`方法，指定`device`形参，来更改张量的存储位置：

```python
>>> b = torch.ones(2,2).to(device='cuda')
>>> b
tensor([[1., 1.],
        [1., 1.]], device='cuda:0')
```

如果有多个CUDA设备，可以指定`device='cuda:<序号>'`：

```python
>>> b = torch.ones(2,2).to(device='cuda:0')
```

我们也可以用简写的`cuda()`和`cpu()`方法实现互转：

```python
>>> b = torch.ones(2,2)

>>> b = b.cuda()
>>> b
tensor([[1., 1.],
        [1., 1.]], device='cuda:0')

>>> b = b.cpu()
>>> b
tensor([[1., 1.],
        [1., 1.]])
```

## §1.9 与NumPy交互

PyTorch框架使用了Python缓冲区协议，可以实现零拷贝开销的互操作性。

将`torch.Tensor(...)`转化为`numpy.ndarray(...)`，可以使用张量提供的`numpy()`方法：

```python
>>> import torch, numpy

>>> a = torch.Tensor([1,2,3]).numpy()
>>> type(a)
numpy.ndarray
```

将`numpy.ndarray(...)`转化为`torch.Tensor(...)`，可以使用`torch.from_numpy()`方法：

```python
>>> import torch, numpy

>>> a = numpy.array([1,2,3])
>>> type(torch.from_numpy(a))
torch.Tensor
```

> 注意：NumPy默认的数据类型是`float64`，而PyTorch默认的数据类型是`float32`。为提高训练效率，加载NumPy的持久化文件`*.npy`后最好降低精度。

## §1.10 张量序列化/持久化

PyTorch内部使用Python的`pickle`来对张量对象进行序列化。`torch.load()`和`torch.save()`的定义如下图所示

```python
torch.save(
	obj: torch.Tensor,
    f: Union[str, PathLike, BinaryIO, IO[bytes]] # 例如文件描述符open()
)

torch.load(
    f: Union[str, PathLike, BinaryIO, IO[bytes]]
) -> torch.Tensor
```

# §2 数据处理

## §2.1 图像数据

图像本质上是颜色编码的矩阵，其中最流行的颜色编码方式是RGB。这里我们使用Python的第三方库`imageio`来操纵图片。

```python
>>> import torch, numpy
>>> import imageio.v3 as imageio

>>> image_array = imageio.imread('./dlwpt-code-master/data/p1ch4/image-dog/bobby.jpg')
>>> type(image_array), image_array.shape
(numpy.ndarray, (720, 1280, 3))
```

目前我们得到的矩阵是$W\times H\times C$，然而PyTorch要求的是$T\times C \times H \times W$，因此我们还要对其变形：

```python
>>> images_tensor = torch.from_numpy(image_array).permute(2, 0, 1).unsqueeze(dim=0)
>>> images_tensor.shape, images_tensor.dtype
(torch.Size([1, 3, 720, 1280]), torch.uint8)
```

最后对像素值归一化：

```python
>>> images_tensor = images_tensor.float() / 255
```

## §2.2 表格数据

表格数据包括CSV、Excel等格式。这里我们使用Github上的开源数据集[awesome-public-datasets](https://github.com/awesomedata/awesome-public-datasets.git)中的葡萄酒数据集`tabular_wine`。

```bash
$ git clone https://github.com/awesomedata/awesome-public-datasets.git
$ cd ./awesome-public-datasets/Datasets
```

Python生态提供了众多解析CSV的库，常见的有以下几种：

- Python自带的`csv`模块
- NumPy
- pandas（内存和时间最少）

这里我们以NumPy为例：

```python
>>> import numpy, torch

>>> wine_dataset = torch.from_numpy(numpy.loadtxt(
    	'./dlwpt-code-master/data/p1ch4/tabular-wine/winequality-white.csv',
    	dtype=numpy.float32,
    	delimiter=";",
    	skiprows=1
	))
>>> wine_dataset.shape
torch.Size([4898, 12])

>>> wine_data = wine_dataset[:,:-1]
>>> wine_label = wine_dataset[:,-1]
>>> wine_data.shape, wine_label.shape
(torch.Size([4898, 11]), torch.Size([4898]))
```

然后创建独热编码：

```python
>>> wine_label_onehot = torch.zeros(wine_label.shape[0], 11).scatter_(1, wine_label.unsqueeze(1), 1)

>>> wine_label_onehot[0]
tensor([0., 0., 0., 0., 0., 0., 1., 0., 0., 0., 0.])
```

> 扩展知识：数据集中的数据可以分为三大类型：
>
> - 连续值：严格有序，不同值之间的差异非常严格，可以进行数学运算。例如时间、重量等。
> - 序数值：严格有序，不同值之间不再有固定关系，数学运算没有意义。例如大杯/中杯/小杯。
> - 分类值：无序，没有固定关系，数学运算没有意义。例如牛/羊/鸡。
>
> 基于此，当我们拿到一组数据时，可以按照以下流程图决定直接使用数据，还是使用独热编码：
>
> ```mermaid
> flowchart LR
> 	a[/"原始数据集"/]-->b{"连续/离散?"}
> 	b--"连续"-->c[["直接使用数据"]]
> 	b--"离散"-->d{"有序/无序?"}
> 	d--"有序"-->e{"顺序优先?"}
> 	e--"顺序优先"-->c
> 	e--"顺序不优先"-->g[["独热编码"]]
> 	d--"无序"-->f{"是否分类?"}--"是"-->g
> ```

接下来我们对每条数据的各项变量进行归一化，使用的公式是$\displaystyle\frac{x_i-\overline{x}}{\sigma_x}$：

```python
>>> wine_data_normalized = (wine_data - wine_data.mean(dim=0)) / wine_data.var(dim=0).sqrt()
>>> wine_data_normalized
tensor([[ 1.7208e-01, -8.1761e-02,  2.1326e-01,  ..., -1.2468e+00,
         -3.4915e-01, -1.3930e+00],
        ...,
        [-1.0129e+00, -6.7703e-01,  3.7852e-01,  ...,  4.7505e-01,
         -1.4882e+00,  1.0448e+00]])
```

让我们看一下一共有多少条数据的葡萄酒得分小于`3`：

```python
>>> wine_data_bad = wine_label_bad = (wine_label <= 3)
>>> wine_label_bad.shape, wine_label_bad
(torch.Size([4898]), tensor([False, False, False,  ..., False, False, False]))

>>> wine_data_bad = wine_data[wine_label_bad]
>>> wine_data_bad.shape
torch.Size([20, 11]) # 一共有20条数据的葡萄酒得分小于3
```

以此类推，我们把葡萄酒按照分数分为三类：3分及以下、4分到6分、7分及以上。

```python
>>> wine_data_bad = wine_data[wine_label <= 3]
>>> wine_data_medium = wine_data[(wine_label >= 3) & (wine_label <= 6)]
>>> wine_data_good = wine_data[wine_label >= 7]

>>> wine_data_good.shape[0], wine_data_medium.shape[0], wine_data_bad.shape[0]
(1060, 3838, 20)
```

接下来，我们看一下各档次葡萄酒的11个属性值之间的差异：

```python
>>> wine_data_mean_bad = wine_data_bad.mean(dim=0)
>>> wine_data_mean_medium = wine_data_medium.mean(dim=0)
>>> wine_data_mean_good = wine_data_good.mean(dim=0)

>>> import csv
>>> with open('./dlwpt-code-master/data/p1ch4/tabular-wine/winequality-white.csv', 'r') as file:
... 	column_names = next(csv.reader(file, delimiter=";"))
>>> print(column_names)
['fixed acidity', 'volatile acidity', 'citric acid', 'residual sugar', 'chlorides', 'free sulfur dioxide', 'total sulfur dioxide', 'density', 'pH', 'sulphates', 'alcohol', 'quality']

>>> for index, args in enumerate(zip(column_names, wine_data_mean_good, wine_data_mean_medium, wine_data_mean_bad)):
...		print("{:2} {:20} {:7.2f} {:7.2f} {:7.2f}".format(index, *args))
 0 fixed acidity           6.73    6.89    7.60
 1 volatile acidity        0.27    0.28    0.33
 2 citric acid             0.33    0.34    0.34
 3 residual sugar          5.26    6.70    6.39
 4 chlorides               0.04    0.05    0.05
 5 free sulfur dioxide    34.55   35.52   53.33
 6 total sulfur dioxide  125.25  141.98  170.60
 7 density                 0.99    0.99    0.99
 8 pH                      3.22    3.18    3.19
 9 sulphates               0.50    0.49    0.47
10 alcohol                11.42   10.27   10.34
```

## §2.3 时间序列数据

[Bike Sharing Dataset](https://www.kaggle.com/datasets/lakshmi25npathi/bike-sharing-dataset)是由波尔图大学整理并发布的开源时序数据集，包含了2011~2012年华盛顿地区自行车共享系统的每小时租车数量，以及对应的天气和季节信息。原始CSV文件包含的属性如下表所示：

| 列序号 | 属性名称     | 含义                                                     | 数据类型             |
| ------ | ------------ | -------------------------------------------------------- | -------------------- |
| 0      | `instant`    | 索引                                                     | `int`                |
| 1      | `day`        | 日期，格式为`YYYY-mm-dd`                                 | `str`                |
| 2      | `season`     | 季节，`1`/`2`/`3`/`4`分别表示春/夏/秋/冬                 | `enum[1,2,3,4]`      |
| 3      | `yr`         | 年份                                                     | `int`                |
| 4      | `mnth`       | 月份                                                     | `int`                |
| 5      | `hr`         | 小时                                                     | `enum[0,1,2,...,23]` |
| 6      | `holiday`    | 是否为节假日                                             | `enum[0,1]`          |
| 7      | `weekday`    | 星期                                                     | `enum[0,1,2,...,6]`  |
| 8      | `workingday` | 是否为工作日                                             | `enum[0,1]`          |
| 9      | `weathersit` | 天气状况，`1`/`2`/`3`/`4`分别表示晴/雾/小雨小雪/大雨大雪 | `enum[1,2,3,4]`      |
| 10     | `temp`       | 温度（摄氏）                                             | `float`              |
| 11     | `atemp`      | 感知温度（摄氏）                                         | `float`              |
| 12     | `hum`        | 湿度                                                     | `float`              |
| 13     | `windspeed`  | 风速                                                     | `int`                |
| 14     | `casual`     | 临时用户租赁自行车的总数                                 | `int`                |
| 15     | `registered` | 注册用户租赁自行车的总数                                 | `int`                |
| 16     | `cnt`        | 租赁自行车的总数                                         | `int`                |

首先，我们读取数据，并且清除日期一列中的`YYYY`和`mm`的部分：

```python
>>> import numpy, torch

>>> bike_dataset = torch.from_numpy(numpy.loadtxt(
... 	fname="./dlwpt-code-master/data/p1ch4/tabular-wine/hour_fixed.csv",
...     dtype=numpy.float32,
...     comments="#",
...     delimiter=",",
...     converters={
...     	1: lambda x: float(x[8:10])
...     },
... 	skiprows=1
... ))
>>> bike_dataset.shape, bike_dataset
(torch.Size([17520, 17]),
 tensor([[1.0000e+00, 1.0000e+00, 1.0000e+00,  ..., 3.0000e+00, 1.3000e+01,
          1.6000e+01],
         ...,
         [1.7379e+04, 3.1000e+01, 1.0000e+00,  ..., 1.2000e+01, 3.7000e+01,
          4.9000e+01]]))
```

现在我们有了一个简陋的二维矩阵，它的形状为$N\times C$。在实际数据处理中，我们更希望使用按时间顺序排列的、形状为$N'\times C\times L$的三维张量，其中$N$代表样本数量，$N'$代表日期总数，L代表$24$个小时，$C$代表属性总数。注意到原数据集从头开始的每一组24个连续数据，都是同一日期内不同小时的各项变量的集合，可以连续反映一天的数据，因此我们可以直接使用`view()`函数，得到$N'\times L\times C$，然后再用`transpose()`函数，得到$N'\times C\times L$：

```python
>>> bike_daily_dataset = bike_dataset.view(-1, 24, bike_dataset.shape[1])
>>> bike_daily_dataset
(torch.Size([730, 24, 17]),
 tensor([[[1.0000e+00, 1.0000e+00, 1.0000e+00,  ..., 3.0000e+00, 1.3000e+01, 1.6000e+01],
          ...,
          [1.7379e+04, 3.1000e+01, 1.0000e+00,  ..., 1.2000e+01, 3.7000e+01, 4.9000e+01]]]))

>>> bike_daily_dataset = bike_daily_dataset.transpose(1, 2)
>>> bike_daily_dataset.shape, bike_daily_dataset
(torch.Size([730, 17, 24]),
 tensor([[[1.0000e+00, 2.0000e+00, 3.0000e+00,  ..., 2.2000e+01, 2.3000e+01, 2.4000e+01],
          ...,
          [3.4000e+01, 1.9000e+01, 1.1000e+01,  ..., 9.0000e+01, 6.1000e+01, 4.9000e+01]]]))
```

## §2.4 文本数据

文本数据常被用于NLP领域中。NLP对文本的操作分为字符级别和单词级别，都使用独热编码。

古登堡计划是一项致力于将文学作品数字化和归档的志愿者活动，这里我们以《傲慢与偏见》为例，下载其`txt`文件并加载到内存中，取其中的一行进行分析：

```python
>>> import torch

>>> with open(./dlwpt-code-master/data/p1ch4/jane-austen/1342-0.txt) as file:
... 	text = file.read()

>>> line = text.split('\n')[123]
>>> len(line), line
(72,
 'all silly and ignorant like other girls; but Lizzy has something more of')
```

接下来我们依据ASCII编码方式，对这句话中的72个字符进行128位的独热编码：

```python
>>> line_onehot = torch.zeros(len(line), 128)

>>> for index, character in enumerate(line):
... 	line_onehot[index][ord(character)] = 1
```

容易发现，如果待处理文本的字符数过多，那么独热编码非常吃内存。为了解决这一问题，NLP领域常用一种名为**嵌入(Embedding)**的方法。它的核心思想是将多种类的分类值，映射成指定长度的一维浮点数张量。比较流行的模型有`word2Vec`等等。接下来我们将实现一个最简单、最符合直觉的嵌入算法：将数千种单词映射成一个整数型标量，也就是将单词整理成单词本，把独热编码换成单词本中的索引。我们首先要从字符串中提取干净的词语，然后将它们编纂成单词本：

```python
>>> def get_word_list(input: str):
... 	return [word.strip('.,;:"!?“”_-\'()[]{}') for word in input.replace('\n', ' ').split()]

>>> words_list = get_word_list(text)
>>> words_dict = sorted(set(words_list))
>>> word_index_map = {word: index for word, index in enumerate(words_list)}

>>> word_index_map
{0: 'The',
 1: 'Project',
 ...
 998: 'she',
 999: 'had',
 ...}
```

然后再对句子中的单词进行嵌入编码：

```python
>>> line_words_list = get_word_list(line)

>>> line_embedding = torch.Tensor([word_index_map[word] for word in line_words_list])
>>> line_embedding
tensor([1120., 6396., 1190., 3905., 4458., 5079., 3521., 1690.,  531., 3709.,
        6497., 4774., 5004.])
```

# §3 PyTorch训练框架

本章我们将介绍神经网络的Python原生实现方法和PyTorch框架实现方法。

## §3.1 实战线性回归

### §3.1.1 自动求导

考虑以下线性回归问题给出的初始值，我们可以手动用链式法则求出梯度：

```python
>>> x = torch.arange(10)
>>> y_truth = torch.arange(10) * 3 - 1

>>> k = torch.tensor([1])
>>> b = torch.tensor([0])
>>> y_predict = x * k + b 
>>> loss = ((y_predict - y_truth) ** 2).sum() / x.shape[0] / 2
```

$$
\begin{cases}
	\displaystyle\frac{\partial L}{\partial w}=\frac{\partial(\frac{1}{2n}\sum((wx_i+b)-y_i)^2}{\partial w}=\frac{2}{n}\sum(wx_i+b-y_i)\cdot x_i=\frac{1}{n}\sum{(\hat{y_i}-y_i)}x_i \\
	\displaystyle\frac{\partial L}{\partial b}=\frac{\partial(\frac{1}{2n}\sum((wx_i+b)-y_i)^2}{\partial b}=\frac{2}{n}\sum(wx_i+b-y_i)\cdot 1  =\frac{1}{n}\sum{(\hat{y_i}-y_i)} \\
\end{cases}
$$

```python
>>> dL_dw = ((y_predict - y_truth) * x).sum() / x.shape[0]
tensor(-52.5000, grad_fn=<DivBackward0>)

>>> dL_db = ((y_predict - y_truth)).sum() / x.shape[0]
tensor(-8., grad_fn=<DivBackward0>)
```

以上手动的方法需要耗费较多的时间用于数学推导。如果网络复杂起来，那么这种方法就不再具有可行性。为此，PyTorch提供了自动求导机制，只要自变量有`requires_grad=True`，并且函数最终值调用了`.backward()`，PyTorch就能自动计算出函数值对自动量的梯度：

```python
>>> x = torch.arange(10)
>>> k = torch.tensor([1], dtype=torch.float, requires_grad=True)
>>> b = torch.tensor([0], dtype=torch.float, requires_grad=True)
>>> y_predict = x * k + b
>>> y_truth = torch.arange(10, dtype=torch.float, requires_grad=True) * 3 - 1
>>> loss = ((y_predict - y_truth) ** 2).sum() / x.shape[0] / 2

>>> loss.backward()
>>> k.grad, b.grad
(tensor([-52.5000]), tensor([-8.]))
```

每个张量都有一个`.grad: torch.Tensor|None`属性，用于保存最终损失函数对本张量在此处属性值处的偏导数。默认情况下，该属性值为`None`。

> 注意：`torch.Tensor(...).grad`属性保存的张量不是最新值，而是**累加值**。PyTorch之所以这样做，是为了保证更高的灵活性。我们现在的线性回归模型用不到，因此每次`.backward()`并提取`.grad`后，都要及时使用`.grad.zero_()`清空梯度。

于是，我们不再手写梯度计算，而是使用PyTorch的自动求导机制，就能写出这样的代码：

```python
def training_loop(epochs, learning_rate, k, b, y_truth, x):
    for epoch in range(epochs):

        if k.grad is not None:
            k.grad.zero_()
        if b.grad is not None:
            b.grad.zero_()
        
        y_predict = k * x + b

        loss = ((y_predict - y_truth) ** 2).sum() / x.shape[0] / 2
        loss.backward()
        with torch.no_grad():
            k -= learning_rate * k.grad
            b -= learning_rate * b.grad
            
    return k, b

k = torch.tensor([1.0], requires_grad=True)
b = torch.tensor([0.0], requires_grad=True)
x = torch.arange(10, dtype=torch.float)
y_truth = torch.arange(10, dtype=torch.float) * 3 - 1

training_loop(10000, 0.001, k, b, y_truth, x)
```

### §3.1.2 优化器

在上一节中，我们使用了批量梯度下降，通过手动计算`leanring_rate * grad`的方式计算参数的变化量。实际上，PyTorch的`torch.optim`模块提供了大量的优化器，用于自动更新每个参数：

```python
>>> import torch
>>> print(dir(torch.optim))
['ASGD', 'Adadelta', 'Adagrad', 'Adam', 'AdamW', 'Adamax', 'LBFGS', 'NAdam', 'Optimizer', 'RAdam', 'RMSprop', 'Rprop', 'SGD', 'SparseAdam', '__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__path__', '__spec__', '_functional', '_multi_tensor', 'lr_scheduler', 'swa_utils']
```

我们常用其中的`SGD`优化器。SGD（Stochastic Gradient Desecent，随机梯度下降）是一种常用的优化方法，该算法的伪代码如下所示：

```python
def SGD(learning_rate: float,
        params: torch.Tensor,
        weight_decay: float = 0, # 在[0, 1]之内
        momentum: float = 0, # 在[0, 1]之内
        dampening: float = 0, # 在[0, 1]之内
        nesterow: typing.Optional[bool] = None,
        maximize: typing.Optional[bool] = False
) -> torch.Tensor :
    for epoch in range(epochs):
        grad[t] = grad(f(params[t-1]), params[t-1])
        grad[t] += weight_dacay * params[t-1]
        b[t] = momentum * b[t-1] + (1 - dampening) * b[t] # 规定 b[0] = 0
        if nesterow:
            grad[t] = grad[t] + momentum * b[t]
        else:
            grad[t] = b[t]
        if maximize:
            params[t] = params[t-1] + weight_decay * grad[t]
        else:
            params[t] = params[t-1] - weight_decay * grad[t]
    return params[epochs]
```

在优化器的构造函数中，以列表形式传入要调整的参数张量。在反向传播前，可以直接调用优化器的`.zero_grad()`方法清零参数张量的梯度；在反向传播后，也能直接调用优化器`.step()`方法进行更新：

```python
>>> def model(x, w, b):
... 	return w * x + b

>>> x = torch.arange(10, dtype=torch.float)
>>> y_truth = 3 * x - 1

>>> params = torch.tensor([1.0, 0.0], requires_grad=True)
tensor([1., 0.], requires_grad=True)

>>> optimizer = torch.optim.SGD([params], 0.001)
>>> y_predict = model(x, *params)
>>> loss = ((y_predict - y_truth) ** 2).mean()
>>> loss.backward()

# 不再手动 params -= learning_rate * params.grad
>>> optimizer.step()
>>> params
tensor([1.1050, 0.0160], requires_grad=True)
```

基于此，我们可以修改[§3.1.1 自动求导](###§3.1.1 自动求导)的线性回归代码：

```python
def training_loop(epochs, optimizer: torch.optim.Optimizer, y_truth, x):
	for epoch in range(epochs):

		optimizer.zero_grad()
		
		y_predict = k * x + b

		loss = ((y_predict - y_truth) ** 2).sum() / x.shape[0] / 2
		loss.backward()
		optimizer.step()
            
	return k, b

k = torch.tensor([1.0], requires_grad=True)
b = torch.tensor([0.0], requires_grad=True)
x = torch.arange(10, dtype=torch.float)
y_truth = torch.arange(10, dtype=torch.float) * 3 - 1
optimizer: torch.optim.Optimizer = torch.optim.SGD([k, b], 0.001)

training_loop(10000, optimizer, y_truth, x)
# (tensor([2.9878], requires_grad=True), tensor([-0.9236], requires_grad=True))
```

除了SGD，我们也可以试试Adam：

```python
......
optimizer: torch.optim.Optimizer = torch.optim.Adam([k, b], 0.001)

training_loop(10000, optimizer, y_truth, x)
# (tensor([2.9993], requires_grad=True), tensor([-0.9960], requires_grad=True))
```

### §3.1.3 数据集划分

本节我们将学习如何把数据集划分为两部分——训练集和测试集。要手动实现这个功能，我们需要先了解PyTorch的两个特性：

- 高级索引：

  ```python
  >>> data = torch.arange(9, -1, -1)
  >>> index = torch.tensor([2, 8])
  >>> data[index]
  tensor([7, 1])
  ```

- `torch.randperm()`：

  详见[§A.8.1 随机排列(`randperm()`)](###§A.8.1 随机排列(`randperm()`))一节。

基于此，我们就能手动划分数据集：

```python
>>> count = 10
>>> x = torch.arange(count, dtype=torch.float)
>>> y_truth = 3 * x - 1

>>> shuffled_index = torch.randperm(count)
>>> validate_count = int(0.2 * count)

>>> x_train = x[shuffled_index[:-validate_count]]
>>> x_validate = x[shuffled_index[-validate_count:]]
>>> y_truth_train = y_truth[shuffled_index[:-validate_count]]
>>> y_truth_validate = y_truth[shuffled_index[-validate_count:]]
```

接着我们再改写训练主函数，使其同时显示模型在训练集和测试集上的损失：

```python
>>> def model(t_u, w, b):
... 	return w * t_u + b

>>> def get_loss(t_p, t_c):
    	squared_diffs = (t_p - t_c)**2
    	return squared_diffs.mean()

>>> def training_loop(epochs, optimizer, params, x_train, x_validate, y_truth_train, y_truth_validate):
...     for epoch in range(epochs):
...         
...         y_predict_train = model(x_train, *params)
...         train_loss = get_loss(y_predict_train, y_truth_train)
...                              
...         optimizer.zero_grad()
...         train_loss.backward()
...         optimizer.step()
... 
...         if epoch % 500 == 0:
...             y_predict_validate = model(x_validate, *params)
...             validate_loss = get_loss(y_predict_validate, y_truth_validate)
...             print(f"Epoch {epoch}, Training loss {train_loss.item():.4f},", f" Validation loss {validate_loss.item():.4f}")
...             
...     return params

>>> params = torch.tensor([1.0, 0.0], requires_grad=True)
>>> optimizer = optim.SGD([params], lr=0.003)

>>> training_loop(
...     epochs = 3000, 
...     optimizer = optimizer,
...     params = params,
...     x_train = x_train,
...     x_validate = x_validate,
...     y_truth_train = y_truth_train,
...     y_truth_validate = y_truth_validate
... )
# tensor([3.3313, 0.3368], requires_grad=True)
```

### §3.1.4 关闭自动求导

[§3.1.3 训练集与测试集](###§3.1.3 训练集与测试集)最后的代码只剩下了一个问题：训练集产生的`train_loss`计算时会创建一个计算图，用于后续的梯度下降。然而测试集产生的`validate_loss`也会创建一个计算图，但是我们用不到这个计算图，因为我们并没有在测试集上训练模型。有没有什么办法，能让PyTorch避免这一算力开销呢？这就引出了`torch.no_grad()`和`torch.set_grad_enabled()`。

```python
torch.no_grad(
    orig_func: None
) -> torch.autograd.grad_mode.no_grad

torch.set_grad_enabled(
	mode: bool
) -> torch.autograd.grad_mode.set_grad_enabled
```

这两个函数通过控制当前上下文中表达式计算涉及到的张量，是否需要`require_grad=True/False`，从而控制是否启用反向传播。以下是改进后的代码：

```python
>>> def training_loop(epochs, optimizer, params, x_train, x_validate, y_truth_train, y_truth_validate):
...     for epoch in range(epochs):
...         
...         y_predict_train = model(x_train, *params)
...         train_loss = get_loss(y_predict_train, y_truth_train)
...                              
...         optimizer.zero_grad()
...         train_loss.backward()
...         optimizer.step()
... 
...         if epoch % 500 == 0:
... 			with torch.no_grad():
...             	y_predict_validate = model(x_validate, *params)
...             	validate_loss = get_loss(y_predict_validate, y_truth_validate)
...             	print(f"Epoch {epoch}, Training loss {train_loss.item():.4f},", f" Validation loss {validate_loss.item():.4f}")
...             
...     return params
```

## §3.2 实战神经网络

上世纪50至60年代，通用近似定理的证明，意味着神经网络可以用来近似任意的复杂函数，并且可以达到任意近似精度。

PyTorch为神经网络提供了`torch.nn`子模块，包含了各类神经网络所需的层（模块）。PyTorch的所有模块都是`torch.nn.Module`的子类，都实现了`__call__()`魔术方法。`torch.nn.Module.Linear`就是其中的一种。在[§3.1.4 关闭自动求导](###§3.1.4 关闭自动求导)中，我们使用`y_predict = model(x, *params)`的`model`是一个手动定义的函数。从现在起，我们使用的`model`将被换为`torch.nn.Module`。

```python
# 伪代码
model = torch.nn.Linear(1, 1)
y_predict = model(x)
```

`torch.nn.Module`的`__call__()`方法定义如下所示。可以看到，把模块当作函数调用会涉及到很多上下文，因此直接调用模块的`.forward()`方法不合适：

```python
class torch.nn.Module:
    # ......
    def __call__(self, *input, **kwargs):
        for hook in self._forward_pre_hooks.values():
            hook(self, input)
        result = self.forward(*input, **kwargs)

        for hook in self._forward_hooks.valus():
            hook_result = hook(self, input, result)

        for hook in self._backward_hooks.values():
            #......
            
        return result
    # ......
```

### §3.2.1 层(模块)

`torch.nn.Linear`的构造函数如下所示：

```python
torch.nn.Linear.__init__(
	in_features: int, # 输入特征的数量
    out_features: int, # 输出特征的数量
    bias: bool = True, # 是否设置偏置项
    device: torch.device = None,
    dtype: torch.dtype = None
) -> None
```

一个线性层实例有`.weight`和`.bias`两个属性，分别表示权重和偏置，初始化时随机设置。当然也可以通过`.parameters()`方法获得以上两个张量构成的`typing.Generator`，传递给优化器：

```python
>>> model = torch.nn.Linear(1, 1)

>>> model.weight
tensor([[-0.9276]], requires_grad=True)

>>> model.bias
tensor([-0.4858], requires_grad=True)

>>> print([tensor for tensor in model.parameters()])
[Parameter containing: tensor([[-0.9276]], requires_grad=True), 
 Parameter containing: tensor([-0.4858], requires_grad=True)]
```

线性层实例期望收到一个二维张量，就能计算该特征经线性变换后的输出。其中第零维是样本的批次大小，第一未才是样本特征本身，它本身是被设计成一次性处理多条输入的：

```python
>>> x = torch.arange(10, dtype=torch.float).reshape(-1, 1)
>>> model(x)
tensor([[-0.4858],
        [-1.4134],
        [-2.3410],
        [-3.2686],
        [-4.1963],
        [-5.1239],
        [-6.0515],
        [-6.9791],
        [-7.9068],
        [-8.8344]], grad_fn=<AddmmBackward0>)
```

如果一开始就传入一个一维张量，那么线性层实例就会将其自动转换为二维张量，然后进行计算：

```python
>>> x = torch.Tensor([1.0])
>>> model(x)
tensor([-1.4134], grad_fn=<ViewBackward0>)
```

于是在此基础上，我们就可以进一步优化[§3.1.4 关闭自动求导](###§3.1.4 关闭自动求导)中的代码：

```python
import torch

count = 10
x = torch.arange(count, dtype=torch.float)
y_truth = 3 * x - 1

shuffled_index = torch.randperm(count)
validate_count = int(0.2 * count)

x_train = x[shuffled_index[:-validate_count]]
x_validate = x[shuffled_index[-validate_count:]]
y_truth_train = y_truth[shuffled_index[:-validate_count]]
y_truth_validate = y_truth[shuffled_index[-validate_count:]]

def get_loss(t_p, t_c):
	squared_diffs = (t_p - t_c)**2
	return squared_diffs.mean()

def training_loop(epochs, optimizer, model, x_train, x_validate, y_truth_train, y_truth_validate):
	for epoch in range(epochs):
		
		y_predict_train = model(x_train)
		train_loss = get_loss(y_predict_train, y_truth_train)

		optimizer.zero_grad()
		train_loss.backward()
		optimizer.step()

		if epoch % 500 == 0:
			with torch.no_grad():
				y_predict_validate = model(x_validate)
				validate_loss = get_loss(y_predict_validate, y_truth_validate)
				print(f"Epoch {epoch}, Training loss {train_loss.item():.4f},", f" Validation loss {validate_loss.item():.4f}")
			
	return model.weight, model.bias

model = torch.nn.Linear(1, 1)
optimizer = torch.optim.SGD(model.parameters(), lr=0.003)

training_loop(
    epochs = 3000, 
    optimizer = optimizer,
    model = model,
    x_train = x_train.unsqueeze(1),
    x_validate = x_validate.unsqueeze(1),
    y_truth_train = y_truth_train.unsqueeze(1),
    y_truth_validate = y_truth_validate.unsqueeze(1)
)
# Epoch 0, Training loss 237.3346,  Validation loss 169.9207
# Epoch 500, Training loss 0.1782,  Validation loss 0.0149
# Epoch 1000, Training loss 0.0222,  Validation loss 0.0019
# Epoch 1500, Training loss 0.0028,  Validation loss 0.0002
# Epoch 2000, Training loss 0.0003,  Validation loss 0.0000
# Epoch 2500, Training loss 0.0000,  Validation loss 0.0000
# (Parameter containing:
#  tensor([[2.9994]], requires_grad=True),
#  Parameter containing:
#  tensor([-0.9961], requires_grad=True))
```

### §3.2.2 损失函数

除了层以外，`torch.nn`也包含了一些常用的损失函数。其中`torch.nn.MSELoss()`表示均方误差。它接受两个一维张量，返回两者之差的平方和。

```python
import torch, collections

count = 10
x = torch.arange(count, dtype=torch.float)
y_truth = 3 * x - 1

shuffled_index = torch.randperm(count)
validate_count = int(0.2 * count)

x_train = x[shuffled_index[:-validate_count]]
x_validate = x[shuffled_index[-validate_count:]]
y_truth_train = y_truth[shuffled_index[:-validate_count]]
y_truth_validate = y_truth[shuffled_index[-validate_count:]]

def training_loop(epochs, optimizer, model, loss_fn, x_train, x_validate, y_truth_train, y_truth_validate):
	for epoch in range(epochs):
		
		y_predict_train = model(x_train)
		train_loss = loss_fn(y_predict_train, y_truth_train)

		optimizer.zero_grad()
		train_loss.backward()
		optimizer.step()

		if epoch % 500 == 0:
			with torch.no_grad():
				y_predict_validate = model(x_validate)
				validate_loss = loss_fn(y_predict_validate, y_truth_validate)
				print(f"Epoch {epoch}, Training loss {train_loss.item():.4f},", f" Validation loss {validate_loss.item():.4f}")
			
	return model.weight, model.bias

loss_fn = torch.nn.MSELoss()
model = torch.nn.Linear(1, 1)
optimizer = torch.optim.SGD(model.parameters(), lr=0.003)

training_loop(
    epochs = 3000, 
    optimizer = optimizer,
    model = model,
	loss_fn= loss_fn,
    x_train = x_train.unsqueeze(1),
    x_validate = x_validate.unsqueeze(1),
    y_truth_train = y_truth_train.unsqueeze(1),
    y_truth_validate = y_truth_validate.unsqueeze(1)
)
# Epoch 0, Training loss 185.6520,  Validation loss 230.1455
# Epoch 500, Training loss 0.0483,  Validation loss 0.0633
# Epoch 1000, Training loss 0.0096,  Validation loss 0.0125
# Epoch 1500, Training loss 0.0019,  Validation loss 0.0025
# Epoch 2000, Training loss 0.0004,  Validation loss 0.0005
# Epoch 2500, Training loss 0.0001,  Validation loss 0.0001
# (Parameter containing:
#  tensor([[2.9987]], requires_grad=True),
#  Parameter containing:
#  tensor([-0.9927], requires_grad=True))
```

### §3.2.3 连接模块

从习惯来讲，线性模型加激活层称为隐藏层。随着隐藏层越来越多，维护这样一个`training_loop()`函数将越来越难。为此，PyTorch提供了`torch.nn.Sequential`容器来定义一个完整的神经网络：

```python
>>> seq_model = torch.nn.Sequential(
... 	torch.nn.Linear(1, 13),
...     torch.nn.Tanh(),
...     torch.nn.Linear(13, 1)
... )

>>> seq_model
Sequential(
  (0): Linear(in_features=1, out_features=13, bias=True)
  (1): Tanh()
  (2): Linear(in_features=13, out_features=1, bias=True)
)
```

我们看到，`torch.nn.Sequential`实例按照顺序给每个层都进行了标号。实际上，我们也可以将这些标号换成字符串，只需调用其构造方法时不直接传递`*args`，而是传递`OrderedDict(*args)`：

```python
>>> import collections

>>> seq_named_model = torch.nn.Sequential(
...     collections.OrderedDict([
... 	    ('hidden_linear',torch.nn.Linear(1, 13)),
...     	('hidden_activation',torch.nn.Tanh()),
...     	('output_linear',torch.nn.Linear(13, 1))
... 	]
... ))
>>> seq_named_model
Sequential(
  (hidden_linear): Linear(in_features=1, out_features=13, bias=True)
  (hidden_activation): Tanh()
  (output_linear): Linear(in_features=13, out_features=1, bias=True)
)
```

我们之前提到过，任意一层的实例都有一个`.parameters()`方法，返回一个层实例中各项参数的迭代器实例。例如一个线性层有着两个参数张量，分别代表着权重和偏置。其实`torch.nn.Sequential`也有`.parameters()`方法，返回各个层使用的参数：

```python
>>> [item.shape for item in seq_model.parameters()]
[torch.Size([13, 1]), torch.Size([13]), torch.Size([1, 13]), torch.Size([1])]
```

其实，PyTorch提供了`.named_parameters()`方法，返回一个迭代器，迭代器每次返回一组可调参数及其所在的位置：

```python
>>> [name for name, param in seq_model.named_parameters()]
['0.weight', '0.bias', '2.weight', '2.bias']
```

`OrderedDict`传递的名称也会影响到`.named_parameters()`的返回值：

```python
>>> [name for name, param in seq_named_model.named_parameters()]
['hidden_linear.weight',
 'hidden_linear.bias',
 'output_linear.weight',
 'output_linear.bias']
```

`torch.nn.Sequential`本质上是一个容器，那么我们也能从中通过整型下标提取出对应位置的层实例。值得注意的是，如果这个容器在创建时接受的是`OrderedDict`，那么我们不仅可以通过整型下标获得层实例，也可以通过`.__attr__()`魔术方法直接访问：

```python
>>> seq_model.0 # 无法直接通过名称访问
Cell In[DETACTED], line DETACTED
->  seq_model.0
SyntaxError: invalid syntax

>>> seq_model[0] # 可以通过整型下标访问
Linear(in_features=1, out_features=13, bias=True)

>>> getattr(seq_model, "0") # 可以通过__attr__()访问
Linear(in_features=1, out_features=13, bias=True)
```

```python
>>> seq_named_model.hidden_linear # 可以直接通过名称访问
Linear(in_features=1, out_features=13, bias=True)

>>> getattr(seq_named_model, "0") # 不能通过原来的名称访问
---------------------------------------------------------------------------
AttributeError                            Traceback (most recent call last)
File c:\Users\DETACTED\.conda\lib\site-packages\torch\nn\modules\module.py:1695, in Module.__getattr__(self, name)
-> 1695 raise AttributeError(f"'{type(self).__name__}' object has no attribute '{name}'")
AttributeError: 'Sequential' object has no attribute '0'

>>> getattr(seq_named_model, "hidden_linear") # 只能通过现在的名称访问
Linear(in_features=1, out_features=13, bias=True)
```

于是，我们就能改写[§3.2.2 损失函数](###§3.2.2 损失函数)中的单层线性层，变成具有10个神经元的隐藏层、一层`tanh()`激活层、一层10个神经元的线性层组合的神经网络：

```python
import torch, collections

count = 10
x = torch.arange(count, dtype=torch.float)
y_truth = 3 * x - 1

shuffled_index = torch.randperm(count)
validate_count = int(0.2 * count)

x_train = x[shuffled_index[:-validate_count]]
x_validate = x[shuffled_index[-validate_count:]]
y_truth_train = y_truth[shuffled_index[:-validate_count]]
y_truth_validate = y_truth[shuffled_index[-validate_count:]]

def training_loop(epochs, optimizer, model, loss_fn, x_train, x_validate, y_truth_train, y_truth_validate):
	for epoch in range(epochs):
		
		y_predict_train = model(x_train)
		train_loss = loss_fn(y_predict_train, y_truth_train)

		optimizer.zero_grad()
		train_loss.backward()
		optimizer.step()

		if epoch % 500 == 0:
			with torch.no_grad():
				y_predict_validate = model(x_validate)
				validate_loss = loss_fn(y_predict_validate, y_truth_validate)
				print(f"Epoch {epoch}, Training loss {train_loss.item():.4f},", f" Validation loss {validate_loss.item():.4f}")

loss_fn = torch.nn.MSELoss()
model = nn.Sequential(OrderedDict([
    ('hidden_linear', nn.Linear(1, 10)),
    ('hidden_activation', nn.Tanh()),
    ('output_linear', nn.Linear(10, 1))
]))
optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

training_loop(
    epochs = 3000, 
    optimizer = optimizer,
    model = model,
	loss_fn= loss_fn,
    x_train = x_train.unsqueeze(1),
    x_validate = x_validate.unsqueeze(1),
    y_truth_train = y_truth_train.unsqueeze(1),
    y_truth_validate = y_truth_validate.unsqueeze(1)
)

for name, parameter in model.named_parameters():
	print(f"{name}: {parameter}")
# Epoch 0, Training loss 241.9196,  Validation loss 73.0770
# Epoch 500, Training loss 1.2290,  Validation loss 0.3979
# Epoch 1000, Training loss 2.6887,  Validation loss 0.9148
# Epoch 1500, Training loss 1.6562,  Validation loss 0.6057
# Epoch 2000, Training loss 1.0335,  Validation loss 0.3461
# Epoch 2500, Training loss 0.6566,  Validation loss 0.2053
# hidden_linear.weight: Parameter containing:
# tensor([[-0.4703],
#         [-0.7558],
#         [-0.1886],
#         [-0.1900],
#         [-0.3648],
#         [ 0.7319],
#         [-0.3118],
#         [ 0.9323],
#         [ 0.2202],
#         [ 0.3002]], requires_grad=True)
# hidden_linear.bias: Parameter containing:
# tensor([ 1.6251,  5.1934, -0.9684, -0.9625,  0.8155, -3.9516,  0.1589,
#         -7.1332,  0.6795, -0.0591], requires_grad=True)
# output_linear.weight: Parameter containing:
# tensor([[-2.3631, -1.6100, -2.7419, -2.7787, -2.0121,  2.1128, -2.5346,
#           2.0478,  2.7706,  2.5343]], requires_grad=True)
# output_linear.bias: Parameter containing:
# tensor([3.1331], requires_grad=True)
```

## §3.3 实战全连接神经网络

### §3.3.1 下载数据集

TorchVision的`datasets`子模块提供了大量的数据集可供下载：

```python
>>> import torchvision

>>> dir(torchvision.datasets)
['CIFAR10',
 'CIFAR100',
...
 'MNIST',
 'Middlebury2014Stereo',
 'MovingMNIST',
...
]
```

CIFAR-10是由加拿大高级研究所（Canadian Institude For Advanced Research，CIFAR）收集和标记的微小图像数据集。该数据集由60000张$32\times32$分辨率的图像构成，包含飞机(`0`)、汽车(`1`)、鸟(`2`)、猫(`3`)、鹿(`4`)、狗(`5`)、青蛙(`6`)、马(`7`)、船(`8`)、卡车(`9`)共十大类图像。

```python
>>> cifar10_train = torchvision.datasets.CIFAR10(
... 	'../data-unversioned/p1ch7/',
... 	train=True,
... 	download=True
... )
>>> cifar10_train
Dataset CIFAR10
    Number of datapoints: 50000
    Root location: ../data-unversioned/p1ch7/
    Split: Train

>>> cifar10_validate = torchvision.datasets.CIFAR10(
... 	'../data-unversioned/p1ch7/',
... 	train=False,
... 	download=True
... )
>>> cifar10_validate
Dataset CIFAR10
    Number of datapoints: 10000
    Root location: ../data-unversioned/p1ch7/
    Split: Test

>>> type(cifar10_train), type(cifar10_validate)
(torchvision.datasets.cifar.CIFAR10, torchvision.datasets.cifar.CIFAR10)

>>> type(cifar10_train).__mro__
(torchvision.datasets.cifar.CIFAR10,
 torchvision.datasets.vision.VisionDataset,
 torch.utils.data.dataset.Dataset,
 typing.Generic,
 object)
```

### §3.3.2 数据集

PyTorch提供了`torch.utils.data.dataset.Dataset`类，表示对数据集的抽象。数据集实例必须要实现两个方法：

- `__len__()`：数据集中样本的数量
- `__item__()`：通过整形下标可以访问特定位置的样本

```python
>>> len(cifar10_train), len(cifar10_validate)
(50000, 10000)

>>> cifar10_train[0]
(<PIL.Image.Image image mode=RGB size=32x32>, 6)

>>> plt.imshow(cifar10_train[0])
```

### §3.3.3 数据集变换

我们需要把PIL图像转换成PyTorch能处理的张量。`torchvision.transforms`子模块定义了一套可组合的变换器：

```python
>>> dir(torchvision.transforms)
['AugMix',
 'AutoAugment',
 'AutoAugmentPolicy',
...
 'autoaugment',
 'functional',
 'transforms']
```

其中`torchvision.transforms.ToTensor`示例用于将PIL图像转换成张量：

```python
>>> transform_to_tensor = torchvision.transforms.ToTensor()

>>> transfozrm_to_tensor(cifar10_train[0][0]).shape
torch.Size([3, 32, 32])
```

其实，我们不用非得拿到数据集后再将其转换成张量，而是通过数据集构造方法中的`transform`形参，在新建数据集时就一次性拿到张量：

```python
>>> cifar10_train_tensor = torchvision.datasets.CIFAR10(
... 	'../data-unversioned/p1ch7/', 
... 	train=True, 
... 	download=False,
... 	transform=torchvision.transforms.ToTensor()
... )

>>> cifar10_train_tensor[0][0]
(tensor([[[0.2314, 0.1686,  ..., 0.5961, 0.5804],
          [0.0627, 0.0000,  ..., 0.4667, 0.4784],
          ...,
          [0.3765, 0.1647,  ..., 0.1333, 0.1333],
          [0.4549, 0.3686,  ..., 0.3294, 0.2824]]]),
 6)
```

> 注意：PIL实例中的像素数据是以`uint8`的形式储存的。经`torchvision.transforms.ToTensor()`处理后，像素数据在$C\times H\times W$张量总以`torch.float32`的形式储存，每个值都位于区间$[0,1]$之内。
>
> 但是，`matplotlib.pyplot.imshow()`接受的张量必须是$H\times W\times C$。这需要我们给原先的张量调用`.permute(1, 2, 0)`翻转一下维度。
>
> ```python
> >>> matplotlib.pyplot.imshow(cifar10_train_tensor[0][0].permute(1, 2, 0))
> ```

拿到张量以后，我们还要对其归一化，使得每个通道的均值为0，标准差为1。这里我们使用`torchvision.transforms.Normalize()`。归一化$\displaystyle\frac{x_i-\overline{x}}{\sigma_x}$需要得到各个颜色通道由于CIFAR10数据集规模很小，我们完全可以将其全部加载到内存中：

```python
>>> cifar10_train_tensor[0][0].shape
torch.Size([3, 32, 32])

>>> images = torch.stack([image for image, label in cifar10_train_tensor], dim=3)
>>> images.shape
torch.Size([3, 32, 32, 50000])

>>> images.view(3, -1).shape # 提取所有图片像素的三个颜色通道
torch.Size([3, 51200000])

>>> images.view(3, -1).mean(dim=1) # 求平均值
tensor([0.4914, 0.4822, 0.4465])

>>> images.view(3, -1).std(dim=1) # 求标准差
tensor([0.2470, 0.2435, 0.2616])

>>> cifar10_transformed_train = torchvision.datasets.CIFAR10(
... 	'../data-unversioned/p1ch7/', 
... 	train=True, 
... 	download=True,
... 	transform=torchvision.transforms.Compose([
...     	torchvision.transforms.ToTensor(),
...     	torchvision.transforms.Normalize(mean=(0.4915, 0.4823, 0.4468), std=(0.2470, 0.2435, 0.2616))
... 	])
... )
>>> cifar10_transformed_validate = torchvision.datasets.CIFAR10(
... 	'../data-unversioned/p1ch7',
... 	train=False,
... 	download=True,
... 	transform=torchvision.transforms.Compose([
...     	torchvision.transforms.ToTensor(),
...         torchvision.transforms.Normalize(mean=(0.4915, 0.4823, 0.4468), std=(0.2470, 0.2435, 0.2616))
...     ])
... )
```

本节我们只考虑二分类的问题，这里我们就随机选取其中的两类图片——飞机(`0`)和鸟(`2`)，并将其序号转换为`0`与`1`：

```python
>>> label_map = {0: 0, 2: 1}
>>> cifar2_transformed_train = [(image_tensor, label_map[label]) for image_tensor, label in cifar10_transformed_train if label in [0, 2]]
>>> cifar2_transformed_validate = [(image_tensor, label_map[label]) for image_tensor, label in cifar10_transformed_validate if label in [0, 2]]
```

### §3.3.4 数据集加载器

既然我们已经有了`torch.utils.data.dataset.Dataset`类了，为什么还要使用数据集加载器`torch.utils.data.DataLoader`呢？这是因为`Dataset`中的样本数据是固定的。将`list[(data, label)]`传给`DataLoader`，可以改变样本的顺序。

```python
import random, pprint, torch

data = [random.random() for i in range(100)]
label = list(range(100))
data_list = list(zip(data, label))

loader = torch.utils.data.DataLoader(data_list, 10, True)
pprint.pprint([label for data, label in loader])
# [tensor([25, 62, 46, 15,  9, 48, 66, 26, 23, 27]),
#  tensor([52, 14, 68, 58, 44, 87, 20, 65, 86, 31]),
#  tensor([84, 73, 57, 88, 85,  2, 69, 13,  1, 79]),
#  tensor([19, 42, 78, 91, 32, 21, 49, 34, 11, 53]),
#  tensor([90, 38, 83,  5, 37, 97, 47, 55, 29, 70]),
#  tensor([17, 39, 10, 80, 16, 33, 22, 74,  4, 60]),
#  tensor([63, 51,  0, 61, 71, 81,  8, 35, 43, 12]),
#  tensor([96, 59, 56, 82, 76, 89, 54, 75, 45, 24]),
#  tensor([28, 92, 64, 93, 18, 72, 40,  6,  7, 36]),
#  tensor([77, 50, 30,  3, 95, 99, 94, 41, 67, 98])]
```

### §3.3.5 完整的神经网络

我们之前将MSE作为损失函数。但是在这个例子中，我们最终的目的不是让输出向量趋近于独热编码，而是让`_, index = output.max(dim=1)`能返回正确的`index`。至于是否趋于独热编码，其实没那么重要了。对此，我们使用更合适的NLL（负对数似然）损失函数：
$$
\text{NLLloss}=-\sum_{i=1}^{n}{\log(x_i)}, \text{where}\ x_i\in\left[0,1\right]
$$


每个样本有$32\times32\times3=3072$个特征。我们定义如下的神经网络。你可能会想问，为什么网络最后一层使用的是`torch.nn.LogSoftmax()`而不是`torch.nn.Softmax()`，这里我们先按下不表，本节最后会解释：

```python
>>> model = torch.nn.Sequential(
... 	torch.nn.Linear(3072, 512),
... 	torch.nn.Tanh(),
... 	torch.nn.Linear(512, 2),
... 	torch.nn.LogSoftmax(dim=1)
... )
```

最终代码如下：

```python
import torch, torchvision

cifar10_transformed_train = torchvision.datasets.CIFAR10(
	'../data-unversioned/p1ch7/', 
	train=True, 
	download=True,
	transform=torchvision.transforms.Compose([
    	torchvision.transforms.ToTensor(),
    	torchvision.transforms.Normalize(mean=(0.4915, 0.4823, 0.4468), std=(0.2470, 0.2435, 0.2616))
	])
)
cifar10_transformed_validate = torchvision.datasets.CIFAR10(
	'../data-unversioned/p1ch7',
	train=False,
	download=True,
	transform=torchvision.transforms.Compose([
    	torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize(mean=(0.4915, 0.4823, 0.4468), std=(0.2470, 0.2435, 0.2616))
    ])
)

label_map = {0: 0, 2: 1}
cifar2_transformed_train = [(image, label_map[label]) for image, label in cifar10_transformed_train if label in [0, 2]]
cifar2_transformed_validate = [(image, label_map[label]) for image, label in cifar10_transformed_validate if label in [0, 2]]

def training_loop(
        epochs: int, 
        optimizer: torch.optim.Optimizer, 
        model: torch.nn.Module,
        loss_function: torch.nn.modules.loss,
        train_dataloader: torch.utils.data.DataLoader,
        validate_dataloader: torch.utils.data.DataLoader,
    ):
    for epoch in range(epochs):
        for images, labels in train_dataloader:
            y_predict_train = model(images.view(images.shape[0], -1))
            loss = loss_function(y_predict_train, labels)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
        print(f"epoch: {epoch}, train_loss:{float(loss)}, ", end='')

        with torch.no_grad():
            for images, labels in validate_dataloader:
                y_predict_validate = model(images.view(images.shape[0], -1))
                loss = loss_function(y_predict_validate, labels)
                print(f"validate_loss: {loss}")

model = torch.nn.Sequential(
    torch.nn.Linear(3072, 512),
    torch.nn.Tanh(),
    torch.nn.Linear(512, 2),
    torch.nn.LogSoftmax(dim=1)
)

training_loop(
    epochs = 100,
    optimizer = torch.optim.SGD(model.parameters(), 0.005),
    model = model,
    loss_function = torch.nn.NLLLoss(),
    train_dataloader = torch.utils.data.DataLoader(cifar2_transformed_train, batch_size=64, shuffle=True),
    validate_dataloader = torch.utils.data.DataLoader(cifar2_transformed_validate, batch_size=2000, shuffle=True)
)
# epoch: 0, train_loss: 0.323549, validate_loss: 0.469412
# epoch: 1, train_loss: 0.493782, validate_loss: 0.465300
# epoch: 2, train_loss: 0.712485, validate_loss: 0.462837
# epoch: 3, train_loss: 0.510695, validate_loss: 0.482677
# epoch: 4, train_loss: 0.271365, validate_loss: 0.438540
# epoch: 5, train_loss: 0.332817, validate_loss: 0.428254
# ...
# epoch: 96, train_loss: 0.009780, validate_loss: 0.576314
# epoch: 97, train_loss: 0.024985, validate_loss: 0.586031
# epoch: 98, train_loss: 0.016191, validate_loss: 0.587952
# epoch: 99, train_loss: 0.020891, validate_loss: 0.581102
```

观察训练集和测试集的损失函数值，我们很容易发现这个神经网络产生了过拟合。在下一节我们将学习使用卷积来增强神经网络的泛化能力。

从数学上来说，`torch.nn.LogSoftmax()`加`torch.nn.NLLLoss()`结合起来，实质上等价于只用`torch.nn.CrossEnropyLoss()`。

## §3.4 实战卷积神经网络

`torch.nn`模块提供了各类卷积层：

- `torch.nn.Conv1d`：一维卷积，用于时间序列
- `torch.nn.Conv2d`：二维卷积，用于图像
- `torch.nn.Conv3d`：三维卷积，用于视频和体数据

我们可以通过这些卷积类的构造函数中的`kernel_size`形参，来指定卷积核的大小。

```python
torch.nn.Conv1d.__init__(
    in_channels: int, 
    out_channels: int, 
    kernel_size: int | tuple[int], 
    stride: Optional[int, tuple[int]] = 1, 
    padding: Optional[int, tuple, str] = 0, 
    dilation: Optional[int, tuple[int]] = 1, 
    groups: Optional[int]= 1, 
    bias: Optional[bool] = True, 
    padding_mode: Optional[str] = 'zeros', 
    device: torch.device = None, 
    dtype: torch.dtype = None
)

torch.nn.Conv2d.__init__(
    in_channels: int, 
    out_channels: int, 
    kernel_size: int | tuple[int], 
    stride: Optional[int, tuple[int]] = 1, 
    padding: Optional[int, tuple, str] = 0, 
    dilation: Optional[int, tuple[int]] = 1, 
    groups: Optional[int]= 1, 
    bias: Optional[bool] = True, 
    padding_mode: Optional[str] = 'zeros', 
    device: torch.device = None, 
    dtype: torch.dtype = None
)

torch.nn.Conv3d(
    in_channels: int, 
    out_channels: int, 
    kernel_size: int | tuple[int], 
    stride: Optional[int, tuple[int]] = 1, 
    padding: Optional[int, tuple, str] = 0, 
    dilation: Optional[int, tuple[int]] = 1, 
    groups: Optional[int]= 1, 
    bias: Optional[bool] = True, 
    padding_mode: Optional[str] = 'zeros', 
    device: torch.device = None, 
    dtype: torch.dtype = None
)
```

我们知道，卷积的本质就是线性变换，所以一个卷积层也有自己的权重和偏置。它们在创建之初就被随机初始化过，这里我们以二维卷积为例：

```python
>>> import torch

>>> conv = torch.nn.Conv2d(3, 16, kernel_size=3)
>>> conv.weight.shape, conv.bias.shape
(torch.Size([16, 3, 3, 3]), torch.Size([16]))
```

一个二维卷积层实例期望收到一个形状为$\text{\textcolor{red}Batch}\times\text{\textcolor{red}Channel}\times\text{\textcolor{red}Height}\times\text{\textcolor{red}Width}$的四维张量。接下来我们手动调整卷积层的权重和偏置，尝试将一幅图片经过该卷积层的处理，最终显示处理前和处理后的效果：

> 注意：卷积层的权重和偏置都默认开启了`requires_grad=True`，所以在修改的权重和偏置的时候需要在`torch.no_grad()`的上下文中进行。

```python
conv = torch.nn.Conv2d(3, 16, kernel_size=3)
with torch.no_grad():
    conv.bias.zero_()
    conv.weight.fill_(1.0 / 9.0)
    
image, _ = cifar2_train[0] # image: 3×32×32
image_conved = conv(image.unsqueeze(0)) # image_conved: 1×16×30×30


plt.figure(figsize=(10, 4.8))

ax1 = plt.subplot(1, 3, 1)
plt.title('input_ChannelMean')
plt.imshow(image.mean(0), cmap='gray')

plt.subplot(1, 3, 2, sharex=ax1, sharey=ax1)
plt.title('output_Channel1') 
plt.imshow(image_conved[0, 0].detach(), cmap='gray')

plt.subplot(1, 3, 3, sharex=ax1, sharey=ax1)
plt.title('output_Channel9') 
plt.imshow(image_conved[0, 8].detach(), cmap='gray')

plt.show() # 图片经过处理后更模糊
print(
    image.mean(0).shape,
    image_conved[0, 0].detach().shape,
    image_conved[0, 9].detach().shape
) # torch.Size([32, 32]) torch.Size([30, 30]) torch.Size([30, 30])
```

可以看到，全一卷积核的作用是模糊图片。在卷积的过程中，我们得到的图片尺寸也缩小了。卷积层的构造函数提供了`padding`形参，给图片外部镶一圈半径为`padding`的纯`0`（黑）边。

```python
conv = torch.nn.Conv2d(3, 16, kernel_size=3, padding=1)
```

池化与卷积的区别是：卷积可以被看作是一个连续的滑动窗口，窗口之间是可以重叠的；而池化是一个离散的窗口，窗口之间不能重叠。PyTorch提供的池化层之一是最大池化`torch.nn.MaxPool2d`，即取窗口内的最大值。

```python
pool = torch.nn.MaxPool2d(2)
image, _ = cifar2_train[0]
image_pooled = pool(image.unsqueeze(0))

plt.figure(figsize=(10, 4.8))

plt.subplot(1, 2, 1) 
plt.title('output') 
plt.imshow(image_pooled[0, 0].detach(), cmap='gray')

plt.subplot(1, 2, 2)
plt.imshow(image.mean(0), cmap='gray')
plt.title('input')

plt.show()

print(image.unsqueeze(0).shape, image_pooled.shape)
# (torch.Size([1, 3, 32, 32]), torch.Size([1, 3, 16, 16]))
```

### §3.4.1 自定义层(模块)

了解卷积和池化的作用后，你可能反手写出一个下面的卷积神经网络，但是执行的时候会报错：

```python
model = torch.nn.Sequential(
    torch.nn.Conv2d(3, 16, kernel_size=3, padding=1), # 1×3×32×32 -> 1×16×32×32
    torch.nn.Tanh(),
    torch.nn.MaxPool2d(2), # 1×16×32×32 -> 1×16×16×16
    torch.nn.Conv2d(16, 8, kernel_size=3, padding=1), # 1×16×16×16 -> 1×8×16×16
    torch.nn.Tanh(),
    torch.nn.MaxPool2d(2), # 1×8×16×16 -> 1×8×8×8
    torch.nn.Linear(8 * 8 * 8, 32), # 报错的位置
    torch.nn.Tanh(),
    torch.nn.Linear(32, 2)
)

model(image.unsqueeze(0))
# RuntimeError: mat1 and mat2 shapes cannot be multiplied (64x8 and 512x32)
```

看到报错信息，我们立刻反应过来是$64\times8$没有转化为$1\times512$，导致矩阵不能相乘。问题是，在PyTorch 1.3之前，我们还没有`torch.nn.Flatten()`。既然已有的工具无法满足我们的需求，那我们就自己写一个`torch.nn.Module`的子类。

一个`torch.nn.Module`的子类，至少要实现两个方法：`__init__()`负责初始化`torch.nn`中的基本层，`forward()`将各个基本层组合在一起，手动实现前向传播的路径，由各个基本层自动实现反向传播。

```python
class CustomizedNet(torch.nn.Module):
    def __init__(self) -> None:
        super().__init__()

        self.conv1 = torch.nn.Conv2d(in_channels=3, out_channels=16, kernel_size=3, padding=1)
        self.act1 = torch.nn.Tanh()
        self.pool1 = torch.nn.MaxPool2d(2)
        
        self.conv2 = torch.nn.Conv2d(in_channels=16, out_channels=8, kernel_size=3, padding=1)
        self.act2 = torch.nn.Tanh()
        self.pool2 = torch.nn.MaxPool2d(2)

        self.fc1 = torch.nn.Linear(512, 32)
        self.act3 = torch.nn.Tanh()
        self.fc2 = torch.nn.Linear(32,2)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        out = self.pool1(self.act1(self.conv1(x)))
        out = self.pool2(self.act2(self.conv2(out)))
        out = out.view(-1, 8, 8) # 这是我们自定义的
        out = self.fc2(self.act3(self.fc1(x)))
        return out

model = CustomizedNet()
model(image.unsqueeze(0)) # 升维，添加N维度(样本数量)
```

如果一个`torch.nn.Module`实例中，以组合方式包含其它的`torch.nn.Module`，那么这些实例属性也会被自动注册为子模块。例如我们可以用`.parameters()`方法获取到各个子模块的参数张量。即使我们并没有显式地声明这些`torch.nn.Module`是子模块，PyTorch依然能自动识别：

```python
>>> model = CustomizedNet()
>>> [i.shape for i in model.parameters()]
[torch.Size([16, 3, 3, 3]),
 torch.Size([16]),
 torch.Size([8, 16, 3, 3]),
 torch.Size([8]),
 torch.Size([32, 512]),
 torch.Size([32]),
 torch.Size([2, 32]),
 torch.Size([2])]
```

### §3.4.2 模块与函数式API

PyTorch的每个`torch.nn`模块都有一个对应的函数式API`torch.nn.functional`。这里的函数式API指的是没有中间状态的API，其本次输出完全取决于本次输入。例如`torch.nn.Conv2d`是一个模块，它在初始化时就被指定了输入维度和输出维度，因此存在中间状态。而`torch.nn.functional.Conv2d`是一个函数，所有参数都是直到调用的时候才传入，不保存中间状态。

将模块换成函数式API，这一方式的优势在于：减少中间状态，从而减少内存占用。例如一个`torch.nn.MaxPool2d(2)`，它的`.parameters()`所占用的空间随上下文而改变。在本例中，这一尺寸可能是`torch.Size([8, 16, 3, 3])`，也可能是`torch.Size([32, 512])`。如果面临更大的数据集，那么它占用的内存会进一步增加。为了避免这些参数常驻内存，我们可以使用对应的函数式API`torch.nn.functional.max_pool2d()`。

```python
class CustomizedNet(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.conv1 = torch.nn.Conv2d(3, 16, kernel_size=3, padding=1)
        self.conv2 = torch.nn.Conv2d(16, 8, kernel_size=3, padding=1)
        self.fc1 = torch.nn.Linear(8 * 8 * 8, 32)
        self.fc2 = torch.nn.Linear(32, 2)
        
    def forward(self, x):
        out = torch.nn.functional.max_pool2d(torch.tanh(self.conv1(x)), 2)
        out = torch.nn.functional.max_pool2d(torch.tanh(self.conv2(out)), 2)
        out = out.view(-1, 8 * 8 * 8)
        out = self.fc2(torch.tanh(self.fc1(out)))
        return out
    
model = CustomizedNet()
model(image.unsqueeze(0))
# tensor([[-0.0273,  0.1006]], grad_fn=<AddmmBackward0>)
```

### §3.4.3 保存与加载模型

接下来，我们使用[§3.4.2 模块与函数式API](###§3.4.2 模块与函数式API)设计的卷积神经网络，看一下它在训练集与测试集上的准确率，是否优于[§3.3.5 完整的神经网络](###§3.3.5 完整的神经网络)的全连接神经网络：

```python
import torch, torchvision

# 1.加载数据集
data_path = '../data-unversioned/p1ch6/'
cifar10_train = torchvision.datasets.CIFAR10(
    data_path, 
    train = True, 
    download = True,
    transform = torchvision.transforms.Compose([
        torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize((0.4915, 0.4823, 0.4468), (0.2470, 0.2435, 0.2616))
    ])
)
cifar10_validate = torchvision.datasets.CIFAR10(
    data_path, 
    train = False, 
    download = True,
    transform = torchvision.transforms.Compose([
        torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize((0.4915, 0.4823, 0.4468), (0.2470, 0.2435, 0.2616))
    ])
)
label_map = {0: 0, 2: 1}
category_names = ['airplane', 'bird']
cifar2_train = [(image, label_map[label]) for image, label in cifar10_train if label in [0, 2]]
cifar2_validate = [(image, label_map[label]) for image, label in cifar10_validate if label in [0, 2]]

# 2.创建卷积神经网络
class CustomizedNet(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.conv1 = torch.nn.Conv2d(3, 16, kernel_size=3, padding=1)
        self.conv2 = torch.nn.Conv2d(16, 8, kernel_size=3, padding=1)
        self.fc1 = torch.nn.Linear(8 * 8 * 8, 32)
        self.fc2 = torch.nn.Linear(32, 2)
        
    def forward(self, x):
        out = torch.nn.functional.max_pool2d(torch.tanh(self.conv1(x)), 2)
        out = torch.nn.functional.max_pool2d(torch.tanh(self.conv2(out)), 2)
        out = out.view(-1, 8 * 8 * 8)
        out = self.fc2(torch.tanh(self.fc1(out)))
        return out
    
# 3. 编写训练函数
def training_loop(
        epochs: int, 
        optimizer: torch.optim.Optimizer, 
        model: torch.nn.Module,
        loss_function: torch.nn.modules.loss,
        train_dataloader: torch.utils.data.DataLoader,
        validate_dataloader: torch.utils.data.DataLoader
    ):
    for epoch in range(epochs):
        # 训练集
        train_loss = 0
        for images, labels_truth in train_dataloader:
            labels_predict = model(images)
            loss = loss_function(labels_predict, labels_truth)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            train_loss += float(loss)
        train_loss /= len(train_dataloader)

        # 测试集
        validate_loss = 0
        with torch.no_grad():
            for images, labels_truth in validate_dataloader:
                labels_predict = model(images)
                validate_loss = loss_function(labels_predict, labels_truth)
        validate_loss /= len(validate_dataloader)
        
        # 输出
        print(f'epoch: {epoch}, train_loss: {train_loss}, validate_loss: {validate_loss}')

# 4.开始训练
model = CustomizedNet()
optimizer = torch.optim.SGD(model.parameters(), lr=0.005)
cifar2_train_dataloader = torch.utils.data.DataLoader(
    cifar2_train, 
    batch_size = 64,
    shuffle = True
)
cifar2_validate_dataloader = torch.utils.data.DataLoader(
    cifar2_validate,
    batch_size = 2000,
    shuffle = False
)
training_loop(
    epochs = 100,
    optimizer = optimizer,
    model = model,
    loss_function = torch.nn.CrossEntropyLoss(),
    train_dataloader = cifar2_train_dataloader,
    validate_dataloader = cifar2_validate_dataloader
)
# epoch: 0, train_loss: 0.5933953159174342, validate_loss: 0.5173754096031189
# epoch: 1, train_loss: 0.5089306787700411, validate_loss: 0.48000314831733704
# epoch: 2, train_loss: 0.48738924997627353, validate_loss: 0.46513861417770386
# epoch: 3, train_loss: 0.4730880321211116, validate_loss: 0.4527730941772461
# epoch: 4, train_loss: 0.46109508443030583, validate_loss: 0.4394274950027466
# ...
# epoch: 96, train_loss: 0.22837189167358313, validate_loss: 0.28784435987472534
# epoch: 97, train_loss: 0.22985974851117771, validate_loss: 0.32625812292099
# epoch: 98, train_loss: 0.22635355520590095, validate_loss: 0.276863694190979
# epoch: 99, train_loss: 0.22662421595898402, validate_loss: 0.2704527974128723

# 5. 测试分类准确率
def print_accuracy(name: str, model: torch.nn.Module, dataloader: torch.utils.data.DataLoader):
    correct_counter = 0
    total_counter = 0
    with torch.no_grad():
        for images, labels_truth in dataloader:
            _, labels_predicted = model(images).max(dim=1)
            total_counter += images.shape[0]
            correct_counter += (labels_predicted == labels_truth).sum()
    print(f"{name} Accuracy: {correct_counter}/{total_counter} = {correct_counter / total_counter}")

print_accuracy("Train", model, cifar2_train_dataloader)
print_accuracy("Validate", model, cifar2_validate_dataloader)
# Train Accuracy: 9372/10000 = 0.9372000098228455
# Validate Accuracy: 1796/2000 = 0.8980000019073486
```

我们的模型在测试集上得到了89.8%的准确率。接下来我们使用`torch.save()`保存这个模型：

```python
torch.save(model.state.dict(), '../data-unversioned/p1ch6/bird_airplane_classification.pt')

```

或者从硬盘中加载模型：

```python
model = CustomizedNet()
model.load_state_dict(
    torch.load('../data-unversioned/p1ch6/bird_airplane_classification.pt')
)
```

### §3.4.4 GPU训练

`torch.device()`函数接受一个字符串形参，返回该字符串对应的设备实例`torch.device`。这个返回的值可以用于`.to()`的实参。

为了让我们的运算在GPU上进行，我们需要让张量和网络同时迁移到GPU上：

```python
>>> import torch
>>> device = torch.device('cuda') if torch.cuda.is_available() else torch.device('cpu')

>>> a = torch.Tensor([1, 2, 3])
>>> a = a.to(device=device)
>>> a.device
device(type='cuda', index=0)

>>> model = torch.nn.Linear(10, 2)
>>> model.to(device=device)
>>> model.weight.device
device(type='cuda', index=0)
```

下面是修改后的代码：

```python
import torch, torchvision

# 0.做好CUDA准备
device = torch.device('cuda') if torch.cuda.is_available() else torch.device('cpu')

# 1.加载数据集
data_path = '../data-unversioned/p1ch6/'
cifar10_train = torchvision.datasets.CIFAR10(
    data_path, 
    train = True, 
    download = True,
    transform = torchvision.transforms.Compose([
        torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize((0.4915, 0.4823, 0.4468), (0.2470, 0.2435, 0.2616))
    ])
)
cifar10_validate = torchvision.datasets.CIFAR10(
    data_path, 
    train = False, 
    download = True,
    transform = torchvision.transforms.Compose([
        torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize((0.4915, 0.4823, 0.4468), (0.2470, 0.2435, 0.2616))
    ])
)
label_map = {0: 0, 2: 1}
category_names = ['airplane', 'bird']
cifar2_train = [(image, label_map[label]) for image, label in cifar10_train if label in [0, 2]]
cifar2_validate = [(image, label_map[label]) for image, label in cifar10_validate if label in [0, 2]]

# 2.创建卷积神经网络
class CustomizedNet(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.conv1 = torch.nn.Conv2d(3, 16, kernel_size=3, padding=1)
        self.conv2 = torch.nn.Conv2d(16, 8, kernel_size=3, padding=1)
        self.fc1 = torch.nn.Linear(8 * 8 * 8, 32)
        self.fc2 = torch.nn.Linear(32, 2)
        
    def forward(self, x):
        out = torch.nn.functional.max_pool2d(torch.tanh(self.conv1(x)), 2)
        out = torch.nn.functional.max_pool2d(torch.tanh(self.conv2(out)), 2)
        out = out.view(-1, 8 * 8 * 8)
        out = self.fc2(torch.tanh(self.fc1(out)))
        return out
    
# 3. 编写训练函数
def training_loop(
        epochs: int, 
        optimizer: torch.optim.Optimizer, 
        model: torch.nn.Module,
        loss_function: torch.nn.modules.loss,
        train_dataloader: torch.utils.data.DataLoader,
        validate_dataloader: torch.utils.data.DataLoader
    ):
    for epoch in range(epochs):
        # 训练集
        train_loss = 0
        for images, labels_truth in train_dataloader:
            images = images.cuda()
            labels_truth = labels_truth.cuda()
            labels_predict = model(images)
            loss = loss_function(labels_predict, labels_truth)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            train_loss += float(loss)
        train_loss /= len(train_dataloader)

        # 测试集
        validate_loss = 0
        with torch.no_grad():
            for images, labels_truth in validate_dataloader:
                images = images.cuda()
                labels_truth = labels_truth.cuda()
                labels_predict = model(images)
                validate_loss = loss_function(labels_predict, labels_truth)
        validate_loss /= len(validate_dataloader)
        
        # 输出
        print(f'epoch: {epoch}, train_loss: {train_loss}, validate_loss: {validate_loss}')

# 4.开始训练
model = CustomizedNet().to(device=device) # 加载到GPU
optimizer = torch.optim.SGD(model.parameters(), lr=0.005)
cifar2_train_dataloader = torch.utils.data.DataLoader(
    cifar2_train, 
    batch_size = 64,
    shuffle = True
)
cifar2_validate_dataloader = torch.utils.data.DataLoader(
    cifar2_validate,
    batch_size = 2000,
    shuffle = False
)
training_loop(
    epochs = 100,
    optimizer = optimizer,
    model = model,
    loss_function = torch.nn.CrossEntropyLoss(),
    train_dataloader = cifar2_train_dataloader,
    validate_dataloader = cifar2_validate_dataloader
)

# 5. 测试分类准确率
def print_accuracy(name: str, model: torch.nn.Module, dataloader: torch.utils.data.DataLoader):
    correct_counter = 0
    total_counter = 0
    with torch.no_grad():
        for images, labels_truth in dataloader:
            images = images.cuda()
            labels_truth = labels_truth.cuda()
            _, labels_predicted = model(images).max(dim=1)
            total_counter += images.shape[0]
            correct_counter += (labels_predicted == labels_truth).sum()
    print(f"{name} Accuracy: {correct_counter}/{total_counter} = {correct_counter / total_counter}")

print_accuracy("Train", model, cifar2_train_dataloader)
print_accuracy("Validate", model, cifar2_validate_dataloader)
```

### §3.4.5 防止过拟合

本节将介绍一些学术上用于抑制过拟合的措施，以及PyTorch的实现方法。

#### §3.4.5.1 L2正则化/权重衰减

为防止权重矩阵的部分元素过大，我们可以给损失函数增加一个由比例项控制的惩罚项：权重矩阵各参数平方之和。

```python
loss = loss_function(labels_predicted, labels_truth)
loss += l2_lambda * sum(
	[p.pow(2).sum() for p in model.parameters()]
)
```

然而数学上已经证明了：这种方式完全等价于设置`weight_decay`参数，详见[`torch.optim.SGD`PyTorch官方文档](https://pytorch.org/docs/stable/generated/torch.optim.SGD.html#torch.optim.SGD)。

```python
# ......
optimizer = torch.optim.SGD(model.parameters(), lr=0.002, weight_decay=0.1)
# ......


```

在反向传播时，让每个权重值按照预先指定比例缩小。

#### §3.4.5.2 Dropout

Dropout于2014年由加拿大学着Geoff Hinton小组提出，其核心思想是将每轮第二代训练中的部分神经元随机清零。我们可以用`torch.nn.conv1_dropout`/`torch.nn.conv2_dropout`方便地实现：

```python
class NetDropout(torch.nn.Module):
    def __init__(self, n_chans1=32):
        super().__init__()
        self.n_chans1 = n_chans1
        self.conv1 = torch.nn.Conv2d(3, n_chans1, kernel_size=3, padding=1)
        self.conv1_dropout = torch.nn.Dropout2d(p=0.4)
        self.conv2 = torch.nn.Conv2d(n_chans1, n_chans1 // 2, kernel_size=3, padding=1)
        self.conv2_dropout = torch.nn.Dropout2d(p=0.4)
        self.fc1 = torch.nn.Linear(8 * 8 * n_chans1 // 2, 32)
        self.fc2 = torch.nn.Linear(32, 2)
        
    def forward(self, x):
        out = torch.nn.functional.max_pool2d(torch.tanh(self.conv1(x)), 2)
        out = self.conv1_dropout(out)
        out = torch.nn.functional.max_pool2d(torch.tanh(self.conv2(out)), 2)
        out = self.conv2_dropout(out)
        out = out.view(-1, 8 * 8 * self.n_chans1 // 2)
        out = torch.tanh(self.fc1(out))
        out = self.fc2(out)
        return out
```

#### §3.4.5.3 批量归一化

2015年，谷歌的研究人员公布了一篇关于Batch Normalization的论文。它的核心思想是：让权重矩阵经过反向传播后，重新批量进行归一化，使得该层产生的输出进一步压缩，以免落入后续激活函数的饱和区。

PyTorch为此提供了`torch.nn.BatchNorm1d`、`torch.nn.BatchNorm2d`、`torch.nn.BatchNorm3d`：

```python
class NetBatchNorm(torch.nn.Module):
    def __init__(self, n_chans1=32):
        super().__init__()
        self.n_chans1 = n_chans1
        self.conv1 = torch.nn.Conv2d(3, n_chans1, kernel_size=3, padding=1)
        self.conv1_batchnorm = torch.nn.BatchNorm2d(num_features=n_chans1)
        self.conv2 = torch.nn.Conv2d(n_chans1, n_chans1 // 2, kernel_size=3, 
                               padding=1)
        self.conv2_batchnorm = torch.nn.BatchNorm2d(num_features=n_chans1 // 2)
        self.fc1 = torch.nn.Linear(8 * 8 * n_chans1 // 2, 32)
        self.fc2 = torch.nn.Linear(32, 2)
        
    def forward(self, x):
        out = self.conv1_batchnorm(self.conv1(x))
        out = torch.nn.functional.max_pool2d(torch.tanh(out), 2)
        out = self.conv2_batchnorm(self.conv2(out))
        out = torch.nn.functional.max_pool2d(torch.tanh(out), 2)
        out = out.view(-1, 8 * 8 * self.n_chans1 // 2)
        out = torch.tanh(self.fc1(out))
        out = self.fc2(out)
        return out
```

### §3.4.6 创建深层网络

对于层数非常深的神经网络而言，开始几层的参数传播到后面的影响会越来越小，导致反向传播时的梯度消失现象，使得开始几层的参数无法收敛。为了解决这一问题，Kaiming He等人于2015年提出了ResNet。其核心思想是不再让各层串联，而是偶尔设置几个跳跃连接，使得起始层的输出能直接叠加到到后面层，而不用经过中间几层。

```python
class CustomizedNet(torch.nn.Module):
    # ......
    def forward(self, x):
        # ......
        out = self.xxx(out)
        out1 = out
        out = self.xxx(out)
        out = self.xxx(out)
        out = self.xxx(out + out1) # 低层输出直接叠加到高层输入
        # ......
```

现在我们已经学会手动搭建十几层的神经网络了。但是现在的网络动辄三十多层，如果手动在`__init__()`中创建三十几个`torch.nn.Module`变量，那么就会既麻烦又不容易维护。

PyTorch对此的解决方案是：允许用户拼接自定义的层，构成一个新层。这个拼接过程可以使用程序批量实现。

```python
class 自定义网络的基本块(torch.nn.module):
    # ......

class 自定义网络(torch.nn.Module):
    def __init__(self):
        self.blocks = torch.nn.Sequential(
        	*(重复次数 * [自定义网络的基本块])
        )
```

## §3.5 实战肿瘤识别

CT扫描的到的数据，本质上是X射线单通道的三维数组，就像是一组沿Z轴堆叠的灰度图像。我们知道，二维图像上的基本数据单元称为像素。同理，三维数组的基本数据单元称为体素。在CT扫描中，数值的大小反映了放射性密度的大小，它表示被测物体的质量密度与原子序数。

本次我们使用的数据集源于LUNA 2016挑战赛，数据集可在官网或[Kaggle](https://www.kaggle.com/datasets/avc0706/luna16)下载。

### §3.5.1 处理CT原始数据集

LUNA 2016数据集包含两类文件：`.mhd`保存元数据，`.raw`保存三维数组原始数据。根据医学领域的DICOM命名法，CT扫描得到的每一个UID都形如正则表达式`uid(\d+.)*(\d+)`。例如UID`uid1.2.3`对应着数据集的`1.2.3.mhd`和`1.2.3.raw`文件。

`candidate.csv`记录了所有疑似是结节的肿块信息。其中共有551000行数据，有1351个样本是真的结节：

| 列名        | 数据类型            | 作用           |
| ----------- | ------------------- | -------------- |
| `seriesuid` | `/uid(\d+.)*(\d+)/` | UID            |
| `coordX`    | `float`             | X轴坐标        |
| `coordY`    | `float`             | Y轴坐标        |
| `coordZ`    | `float`             | Z轴坐标        |
| `class`     | `bool`              | 是否真的为结节 |

`annotations.csv`记录了一些已经标记为实际结节的候选者信息。其中共有1187个样本：

| 列名          | 数据类型            | 作用             |
| ------------- | ------------------- | ---------------- |
| `seriesuid`   | `/uid(\d+.)*(\d+)/` | UID              |
| `coordX`      | `float`             | X轴坐标          |
| `coordY`      | `float`             | Y轴坐标          |
| `coordZ`      | `float`             | Z轴坐标          |
| `diameter_mm` | `float`             | 结节的直径(毫米) |

以上这两个数据集并不都是完美的：

- `candidate.csv`中标记为真的结节（共有1351个），并没有全部在`annotations.csv`体现（共有1187个）。

- `candidate.csv`和`annotations.csv`的X/Y/Z坐标并不完全重合。下面是一个具体的例子：

  ```sh
  $ cat candidates.csv | grep "1.3.6.1.4.1.14519.5.2.1.6279.6001.100225287222365663678666836860"
  ......,-128.94,-175.04,-297.87,1
  
  $ cat annoations.csv | grep "1.3.6.1.4.1.14519.5.2.1.6279.6001.100225287222365663678666836860"
  ......,-128.6994211,-175.3192718,-298.3875064,5.651470635
  ```





























# §4 部署

## §4.1 部署到网络

本节我们将尝试将PyTorch训练的模型部署到Flask上，由Flask提供对外统一访问的网络接口。我们默认读者有一定的Flask基础。

## §4.2 导出到ONNX

ONNX是一种描述操作及其参数的标准格式，为神经网络和机器学习模型提供了一种通用的、互操作性的接口。ONNX文件可以在ONNX运行时中执行。现在很多专门为人工智能设计的加速器硬件都支持ONNX，一些云计算平台也支持用户上传ONNX文件。

Python的第三方库`onnxruntime`/`onnxruntime-gpu`就是ONNX的运行时之一。`torch.onnx`子模块提供了模型的导出功能：

```python
model = #...
torch.onnx.export(
	model, # 模型实例
    torch.ones(恰当的形状), # 虚拟输入。输入的值不重要，重要的是形状
    './model.onnx' # 保存路径
)
```

然后用`onnxruntime`/`onnxruntime-gpu`加载并运行模型：

```python
import onnxruntime

sess = onnxruntime.InferenceSession('./model.onnx')
predict_onnx = sess.run(
	None,
    {sess.get_inputs()[0].name: batch}
)
```







# §5 高性能训练

## §5.1 `functools`缓存

[Python官方库`functools`](https://docs.python.org/zh-cn/3/library/functools.html)提供了一些用于缓存的装饰器。

### §5.1.1 无限制缓存(`@functools.cache()`)

`@functools.cache()`用于给函数提供缓存，使其面对相同的传入实参时，不必再计算一次，而是直接从缓存拿出结果：

```python
@functools.cache
```

在学习算法的斐波那契数列时，我们了解过动态规划的概念。其涉及到的核心思想是给递归加上缓存，保存斐波纳挈数列各项的值，便于后面的计算由重复使用。

```python
import datetime, functools


def fibonacci_original(n: int) -> int:
    if n == 1 or n == 2:
        return 1
    return fibonacci_original(n - 1) + fibonacci_original(n - 2)
start_time = datetime.datetime.now()
fibonacci_original(30)
end_time = datetime.datetime.now()
print(f"fibonacci_original(30): {(end_time - start_time).microseconds}μs")


def fibonacci_dp(n: int, cached_dict: dict[int, int] = {}) -> int:
    if n == 1 or n == 2:
        return 1
    if n in cached_dict.keys():
        return cached_dict[n]
    result = fibonacci_dp(n - 1, cached_dict) + fibonacci_dp(n - 2, cached_dict)
    cached_dict[n] = result
    return result
start_time = datetime.datetime.now()
fibonacci_dp(30)
end_time = datetime.datetime.now()
print(f"fibonacci_dp(30): {(end_time - start_time).microseconds}μs")
```

现在，我们可以使用Python官方库`functools`中的`@functional.cache()`装饰器，来保存以往计算过的所有函数值。当传入实参重复的时候，就直接返回缓存值：

```python
import datetime, functools


@functools.cache
def fibonacci_cached(n: int) -> int:
    if n == 1 or n == 2:
        return 1
    return fibonacci_cached(n - 1) + fibonacci_cached(n - 2)

start_time = datetime.datetime.now()
fibonacci_cached(30)
end_time = datetime.datetime.now()
print(f"fibonacci_cached(30): {(end_time - start_time).microseconds}μs")
```

### §5.1.2 实例方法缓存(`@functools.cached_property`)

在[§5.1.1 无限制缓存(`@functools.cache()`)](###§5.1.1 无限制缓存(`@functools.cache()`))一节中，我们学会了如何给普通函数添加缓存。其实`funtools`的`@functools.cached_property`也支持修饰类的实例方法，将其从实质上变为一个固定值的属性。

```python
class Dataset:
    def __init__(self):
        # ......
        
    @functools.cached_property    
    def mean(self):
        return torch.mean(...)
```

### §5.1.3 LRU缓存(`@functools.lru_cache()`)

在《计算机组成原理》中，我们学过Cache的置换策略，其中一种就是LRU（Least Recently Used，最近最少使用）算法。如果缓存空间是有限的，我们就需要考虑缓存的换出规则了。Python提供了LRU的换出规则。

```python
@functools.lru_cache(
    maxsize = 128: int | None,
    typed = False: bool
)
```

其中各参数含义如下：

- `maxsize`：LRU缓存空间。设置为`None`时表示无限空间，等价于`@functools.cache`
- `typed`：是否为不同数据类型的返回值使用单独的LRU缓存空间。

## §5.2 `diskcache`缓存

[`diskcache-python`](https://github.com/grantjenks/python-diskcache)是Python的一款第三方硬盘缓存库，其实现依赖于SQLite数据库。

### §5.2.1 `diskcache.Cache`

`diskcache.Cache`类提供了最基础的磁盘缓存。

```python
import diskcache
import random

# 指定Cache(SQLite数据库)的存放文件夹路径
cache = diskcache.Cache('./cache')

# 写入缓存
for i in range(100):
    cache[i] = random.random()
    
# 读取缓存
print(cache[50])

# 关闭缓存
cache.close()

# 开启缓存(速度慢)并读取缓存
print(cache[50])

# 删除缓存
del cache[50]
```

其实现的`memoize()`方法被广泛用于修饰器：

```python
import diskcache
import datetime

cache = diskcache.Cache('./cache')

@cache.memoize()
def fibonacci(n: int):
    if n == 1 or n == 2:
        return 1
    return fibonacci(n - 1) + fibonacci(n - 2)

start_time = datetime.datetime.now()
print(fibonacci(100))
end_time = datetime.datetime.now()
print((start_time - end_time).microseconds) # 969049

start_time = datetime.datetime.now()
print(fibonacci(100))
end_time = datetime.datetime.now()
print((start_time - end_time).microseconds) # 0
```

### §5.2.2 `diskcache.FanoutCache`

在[§5.2.1 `diskcache.Cache`](###§5.2.1 `diskcache.Cache`)的基础上，我们提出了缓存分页`diskcache.FanoutCache`的概念，从而防止单文件过大，影响多线程并发读写。

```python
diskcache.FanoutCache.__init__(
	directory = None,
    shards: int = 8
    timeout: float = 0.010
    disk: class = diskcache.core.Disk.__class__
    **settings
)
```















# §A PyTorch API

> 注意：无特殊说明，本章涉及到的函数均为“浅拷贝”。可以实现“深拷贝”的方法如下所示：
>
> - `torch.Tensor(...).clone()`/`torch.clone()`
> - `torch.Tensor(...).contiguous()`
> - `torch.Tensor(...).cuda()`
> - `torch.Tensor(...).reshape()`/`torch.reshape()`（当且仅当输入的张量不连续时）

## §A.1 创建操作

创建操作指的是用于构造张量的函数。例如`ones()`和`from_numpy()`。

### §A.1.x 分离(`detach()`)

`torch.Tensor(...).detach()`用于创建一个与原张量相同的张量，两者共用存储空间，但是分离后的张量`require_grad`为`False`，其`.grad`也被置为`None`：

```python
>>> import torch
>>> a = torch.ones(2,2, requires_grad=True)
>>> loss = a.mean()
>>> loss.backward()
>>> b = a.detach()

>>> a, b
(tensor([[1., 1.],
         [1., 1.]], requires_grad=True),
 tensor([[1., 1.],
         [1., 1.]]))

>>> a.grad, b.grad
(tensor([[0.2500, 0.2500],
         [0.2500, 0.2500]]),
 None)
```

## §A.2 索引/切片/连接/转换操作

本节函数用于改变张量的形状、步长或内容。例如`transpose()`。

### §A.2.1 转置(`transpose()`/`t()`)

张量的转置有以下几种方法：

```python
torch.Tensor(...).transpose(
    dim0: int,
    dim1: int
)

torch.transpose(
	input: torch.Tensor,
    dim0: int,
    dim1: int
)
```

| 参数                  | 作用                               |
| --------------------- | ---------------------------------- |
| `input: torch.Tensor` | 待转置的张量                       |
| `dim0: int`           | 需要转置的两个维度之一，对应的序号 |
| `dim1: int`           | 需要转置的两个维度之一，对应的序号 |

当`input: torch.Tensor`恰好为二维张量时，`transpose()`可以退化为`t()`：

```python
torch.Tensor((...,...)).t()

torch.t(input: torch.Tensor)
```

对于高维张量的转置，其本质上是交换对应维度序号的[步长和形状](##§1.6 张量元数据)数值。例如一个形状为$(20,5,2)$的张量，其步长为$(10,2,1)$。当我们对其第一维和第三维进行转置时，得到的张量形状为$(2,5,20)$，步长为$(1,2,10)$。

### §A.2.2 全零填充(`zero_()`)

使用`zero_()`函数来给张量中的每个元素置零。

```python
torch.Tensor(...).zero_()
```

### §A.2.3 重排(`permute()`)

`torch.permute()`用于返回一个原张量的、各维度形状按照指定顺序重排后的视图。要求`len(dims) == len(tensor.shape)`且`dims`中的数字必须在`[0, len(dims)]`内，且每个数字只能出现一次：

```python
torch.permute(
	input: torch.Tensor,
    dims: tuple[int]
) -> torch.Tensor

torch.Tensor(...).permute(
	dims: tuple[int]
) -> torch.Tensor
```

`torch.permute()`是`torch.transpose()`的升级版，它可以一次性交换多个维度，而不是局限于两个维度。

```python
>>> import torch

>>> a = torch.randn((720, 1080, 3));
>>> b = a.permute(2, 0, 1) # 从0, 1, 2交换到2, 0, 1

>>> b.shape
torch.Size([3, 720, 1080])

>>> b.is_contiguous()
False
```

### §A.2.4 变形(`reshape()`)

`torch.reshape()`用于将张量变形为指定形状的张量，可能返回视图或拷贝。

```python
torch.Tensor().reshape(
	shape: tuple[int]
) -> Torch.Tensor

torch.reshape(
	input: torch.Tensor,
    shape: tuple[int]
) -> torch.Tensor
```

当`input.is_contiguous() == True`时，返回的是视图，反之则返回拷贝：

```python
>>> a = torch.ones(2, 3, 5)
>>> b = a.transpose(0, 2)
>>> c = b.reshape((2, 3, 5))

>>> print([i.is_contiguous() for i in [a, b, c]] )
[True, False, True]

>>> a.zero_()

>>> print([i[0][0][0] for i in [a, b, c]])
[tensor(0.), tensor(0.), tensor(1.)]
```

### §A.2.5 视图(`view()`)

`torch.Tensor().view()`返回原张量经过重新排列后的视图。要求`shape`各数值相乘必须等于原张量的元素总数：

```python
torch.Tensor().view(
	shape: tuple[int]
)
```

`torch.Tensor().view()`和`torch.Tensor().transpose()`有各大的差别，但这种差别用数学语言描述显得很抽象：

- `view()`生成的视图保证：
  $$
  \begin{align}
  	&\text{stride}'[i]=\text{stride}[i+1]\times\text{size}[i+1] & ,\forall i \in[0,D) \\
  	&\text{stride}'[D]=\text{stride}[D]
  \end{align}
  $$

- `transpose()`生成的视图保证：$\text{stride}'[i]$的值互换。

```python
>>> a = torch.arange(24).reshape((2, 3, 4))
>>> b = a.transpose(0, 2)
>>> c = a.view(4, 3, 2)
>>> b, c
(tensor([[[ 0, 12],  	|	tensor([[[ 0,  1],
          [ 4, 16],  	|	         [ 2,  3],
          [ 8, 20]], 	|  	         [ 4,  5]],
 					 	|
         [[ 1, 13],	 	|        	[[ 6,  7],
          [ 5, 17],  	|            [ 8,  9],
          [ 9, 21]], 	|            [10, 11]],
 						|
         [[ 2, 14],  	|           [[12, 13],
          [ 6, 18],  	|		     [14, 15],
          [10, 22]], 	|            [16, 17]],
 					  	|
         [[ 3, 15],   	|           [[18, 19],
          [ 7, 19],   	|            [20, 21],
          [11, 23]]]),	|            [22, 23]]]))
```

如果`shape`中出现`-1`，则表示对应维度的长度未知，需要PyTorch根据其它已知长度的维度推测出来：

```python
>>> a = torch.arange(24)
>>> a.view(-1, 3, 4).shape
torch.Size([2, 3, 4])
```

### §A.2.6 添加维度(`unsqueeze()`)

`torch.Tensor(...).squeeze()`和`torch.unsqueeze()`用于在指定的维度位置上，增加张量的维度。

```python
torch.unsqueeze(
	input: torch.Tensor,
    dim: int
)

torch.Tensor(...).unsqueeze(
	dim: int
)
```

例如给第$0$维（最外围）增加维度时，原先的第$0$维会向后退成第$1$维，原先的第$1$维会向后退成第$2$维......后面维度同理，这相当于打包原先的张量成`1`份；给第$1$维增加维度时，第$1$维会向后退成第$2$维......后面维度同理，相当于打包了第$1$维起的张量，一共打包了`.shape[0]`份。

```python
>>> import torch
>>> label = torch.arange(5)

>>> label.unsqueeze(0)
tensor([[0, 1, 2, 3, 4]])

>>> label.unsqueeze(1)
tensor([[0],
        [1],
        [2],
        [3],
        [4]])
```

### §A.2.7 散射(`scatter()`/`scatter_()`)

`torch.scatter()`/`torch.Tesnor(...).scatter_()`均涉及到三个维度相同的张量——`self`、`src`和`index`，可以将`src`中的值按照`index`与`dim`确定的索引顺序全部其一填入到`self`中。

```python
torch.scatter(
	input: torch.Tensor,
    dim: int,
    index: torch.Tensor,
    src: Union[torch.Tensor, float],
    reduce: Literal["add", "multiply"] | None = "multiply"
) -> torch.Tensor

torch.Tensor(...).scatter_(
    dim: int,
    index: torch.Tensor,
    src: Union[torch.Tensor, float],
    reduce: Literal["add", "multiply"] | None = "multiply"
) -> torch.Tensor
```

以三维张量为例，下面展示了`dim`参数对函数效果的影响：
$$
\forall \text{i,j,k} \in D, \begin{cases}
	\text{self}[\textcolor{red}{\text{index}[i][j][k]}][j][k]:=\text{src}[i][j][k] & ,\text{dim}=1 \\
	\text{self}[i][\textcolor{red}{\text{index}[i][j][k]}][k]:=\text{src}[i][j][k] & ,\text{dim}=2 \\
	\text{self}[i][j][\textcolor{red}{\text{index}[i][j][k]}]:=\text{src}[i][j][k] & ,\text{dim}=3 \\
\end{cases}
$$
例如，我们有一个取值为$[0,4]$之间的一维标签张量，我们可以用`scatter_()`方法创建对应的独热编码：

```python
>>> label = torch.arange(5)

>>> label_onehot = torch.zeros(label.shape[0], 5,).scatter_(
... 	1,
... 	label.unsqueeze(1),
... 	1
...	)
>>> label_onehot
tensor([[1., 0., 0., 0., 0.],
        [0., 1., 0., 0., 0.],
        [0., 0., 1., 0., 0.],
        [0., 0., 0., 1., 0.],
        [0., 0., 0., 0., 1.]])
```

### §A.2.8 聚集(`gather`)

[TODO:](https://pytorch.org/docs/stable/generated/torch.gather.html#torch-gather)











### §A.2.9 堆叠(`stack()`)

`torch.stack()`用于沿新维度连接一系列张量：

```python
torch.stack(
	tensors: collections.abc.Sequence[torch.Tensor],
    dim: int = 0, *,
    out: Optional[torch.Tensor] = None
)
```

这个函数的作用比较抽象，下面是该函数实现的伪代码：

```typescript
// 伪代码
function get_tuple_atomic(tensor_pointer_1, tensor_pointer_2){
	// tensor_pointer_1和tensor_pointer_2的形状相同，但不一定是一维，可能是高维，取决于len(tensor.shape) - dim
    return[tensor_pointer_1, tensor_pointer_2];
}

function stack_iterate(tensor_pointer_1, tensor_pointer_2, dim){
    if(dim == 0){
    	return get_tuple_atomic(tensor_pointer_1, tensor_pointer_2);
    } else if (dim > 0){
    	let tensor_sub = []
        for(let i = 0 ; i < tensor_pointer_1.shape[0] ; ++i){
    		tensor_sub.append(get_tuple_iterate(
                tensor_pointer_1[i],
                tensor_pointer_2[i],
                dim - 1
            ));
    	}
        return tensor_sub;
    }
}
```

下面是一个具体的例子：

```python
>>> a = torch.tensor([[1, 2, 3],[4, 5, 6]]) # 形状为2×3
>>> b = torch.tensor([[7, 8, 9],[10, 11, 12]]) # 形状为2×3

>>> torch.stack([a, b], dim=0) # [a, b]
tensor([[[ 1,  2,  3],	# 形状为(2)×2×3
         [ 4,  5,  6]],
        [[ 7,  8,  9],
         [10, 11, 12]]])

>>> torch.stack([a, b], dim=1) # [[a[0], b[0]], [a[1], b[1]]]
tensor([[[ 1,  2,  3], # 形状为2×(2)×3
         [ 7,  8,  9]],
        [[ 4,  5,  6],
         [10, 11, 12]]])

>>> torch.stack([a, b], dim=2) # [[a[0][0], b[0][0]], [a[0][1], b[0][1]], [a[0][2], b[0][2]]], ......
tensor([[[ 1,  7],	# 形状为2×3×(2)
         [ 2,  8],
         [ 3,  9]],
        [[ 4, 10],
         [ 5, 11],
         [ 6, 12]]])
```



## §A.3 逐点操作

逐点操作指的是对每个元素分别应用一个函数来得到一个新的张量。例如`abs()`和`cos()`。

### §A.3.1 小于等于(`le()`)

> 注意：该函数等价于`<=`运算符。

`torch.le()`和`torch.Tensor(...).ge()`用于逐元素比较两个张量对应的元素是否是小于等于的关系。

```python
torch.ge(
	input: torch.Tensor,
    other: Union[torch.Tensor, float], *
    out=None: Optional[Union[torch.Tensor, None]]
)

torch.Tensor(...).ge(
	other: Union[torch.Tensor, float], *
    out=None: Optional[Union[torch.Tesnor, None]]
)
```

其中`out`为输出的张量。

当`other`为张量时，采取自动广播机制进行比较：

```python
>>> a = torch.arange(30).reshape(2,3,5)

>>> a.le(15)
tensor([[[ True,  True,  True,  True,  True],
         [ True,  True,  True,  True,  True],
         [ True,  True,  True,  True,  True]],

        [[ True, False, False, False, False],
         [False, False, False, False, False],
         [False, False, False, False, False]]])

>>> a.le(torch.Tensor([8, 9, 10, 11, 12]))
tensor([[[ True,  True,  True,  True,  True],
         [ True,  True,  True,  True,  True],
         [False, False, False, False, False]],

        [[False, False, False, False, False],
         [False, False, False, False, False],
         [False, False, False, False, False]]])
```

### §A.3.2 大于等于(`ge()`)

> 注意：该函数等价于`>=`运算符。

`torch.ge()`和`torch.Tensor(...).ge()`用于逐元素比较两个张量对应的元素是否是大于等于的关系。

```python
torch.ge(
	input: torch.Tensor,
    other: Union[torch.Tensor, float], *
    out=None: Optional[Union[torch.Tensor, None]]
)

torch.Tensor(...).ge(
	other: Union[torch.Tensor, float], *
    out=None: Optional[Union[torch.Tesnor, None]]
)
```

其中`out`为输出的张量。

> 注意：经实测，`out`参数处于不可用的状态😅。网上关于`out`变量的资料几乎没有。
>
> ```python
> >>> torch.__version__
> '2.1.0+cu118'
> 
> >>> a = torch.arange(30).reshape(2,3,5)
> >>> a.ge()
> ---------------------------------------------------------------------------
> NameError                                 Traceback (most recent call last)
> c:\Users\Yaner\Desktop\Thoughts\demo.ipynb 单元格 5 line 4
> ----> 4 a.ge(15, out=b)
> NameError: name 'b' is not defined
> 
> >>> b = torch.ones((2,3,5))
> >>> a.ge(15, out=b)
> ---------------------------------------------------------------------------
> TypeError                                 Traceback (most recent call last)
> c:\Users\DETACTED\Desktop\Thoughts\demo.ipynb 单元格 5 line 3
> ----> 3 a.ge(15, out=b)
> TypeError: ge() received an invalid combination of arguments - got (int, out=Tensor), but expected one of:
>  * (Tensor other)
>  * (Number other)
> ```

当`other`为张量时，采取自动广播机制进行比较：

```python
>>> a = torch.arange(30).reshape(2,3,5)

>>> a.ge(15)
tensor([[[False, False, False, False, False],
         [False, False, False, False, False],
         [False, False, False, False, False]],

        [[ True,  True,  True,  True,  True],
         [ True,  True,  True,  True,  True],
         [ True,  True,  True,  True,  True]]])

>>> a.ge(torch.Tensor([8, 9, 10, 11, 12]))
tensor([[[False, False, False, False, False],
         [False, False, False, False, False],
         [ True,  True,  True,  True,  True]],

        [[ True,  True,  True,  True,  True],
         [ True,  True,  True,  True,  True],
         [ True,  True,  True,  True,  True]]])
```

## §A.4 规约操作

规约操作指的是通过迭代张量来计算聚合值的函数。例如`mean()`、`std()`、`norm()`。

### §A.4.1 平均值(`mean()`)

`torch.mean()`和`torch.Tensor(...).mean()`用于返回整个张量的各个元素或沿某一轴元素的平均值。

```python
torch.mean(
	input: torch.Tensor,
    dim: int | tuple[int],
    keepdim=False: bool, *,
    dtype=None: Optional[torch.dtype],
    out=None: Optional[torch,Tensor]
)

torch.Tensor(...).mean(
    dim=None: Optional[int, tuple[int]],
    keepdim=False: bool, *,
    dtype=None: Optional[torch.dtype],
    out=None: Optional[torch,Tensor]
)
```

这里我们详细介绍一下`dim`和`keepdim`参数。

当`dim=None`时，`mean()`对全体元素取平均值。当`dim=a`时，第$a$维的长度会被缩短为$1$，这个维度唯一的值就是平均值，随后再删除这个维度，即脱去平均值外面的`[]`，使其降维。

```python
>>> a = torch.arange(24).float().reshape(2, 3, 4)
>>> a
tensor([[[ 0.,  1.,  2.,  3.],
         [ 4.,  5.,  6.,  7.],
         [ 8.,  9., 10., 11.]],
        [[12., 13., 14., 15.],
         [16., 17., 18., 19.],
         [20., 21., 22., 23.]]])

>>> a.mean()
tensor(11.5000)

>>> a.mean(0) # a[0]和a[1]重叠在一起，求平均值
tensor([[ 6.,  7.,  8.,  9.],
        [10., 11., 12., 13.],
        [14., 15., 16., 17.]])

>>> a.mean(1) # a[*][0], a[*][1], a[*][2]重叠在一起，求平均值
tensor([[ 4.,  5.,  6.,  7.],
        [16., 17., 18., 19.]])

>>> a.mean(2) # a[*][*][0], a[*][*][1], a[*][*][2], a[*][*][3]重叠在一起，求平均值
tensor([[ 1.5000,  5.5000,  9.5000],
        [13.5000, 17.5000, 21.5000]])
```

当`keepdim=True`时，上面的规则有所变动——第$a$维的不会被删除。

```python
>>> a = torch.arange(24).float().reshape(2,3,4)
>>> a
tensor([[[ 0.,  1.,  2.,  3.],
         [ 4.,  5.,  6.,  7.],
         [ 8.,  9., 10., 11.]],
        [[12., 13., 14., 15.],
         [16., 17., 18., 19.],
         [20., 21., 22., 23.]]])

>>> a.mean(0, True)
tensor([[[ 6.,  7.,  8.,  9.],
         [10., 11., 12., 13.],
         [14., 15., 16., 17.]]])

>>> a.mean(1, True)
tensor([[[ 4.,  5.,  6.,  7.]],
        [[16., 17., 18., 19.]]])

>>> a.mean(2, True)
tensor([[[ 1.5000],
         [ 5.5000],
         [ 9.5000]],
        [[13.5000],
         [17.5000],
         [21.5000]]])
```

### §A.4.2 方差(`var()`)

`torch.var()`和`torch.Tensor(...).var()`用于计算张量的方差，计算公式为：
$$
\sigma^2=\frac{1}{\max(0, N-\text{correction})}\sum_{i=0}^{N-1}(x_i-\overline{x})^2
$$

```python
torch.var(
	input: torch.Tensor,
	dim=None: Optional[int | tuple[int]], *,
    correction=1: int,
    keepdim=False: bool,
    out=None: Optional[torch.Tensor]
)

torch.Tensor(...).var(
	dim=None: Optional[int | tuple[int]], *,
    correction=1: int,
    keepdim=False: bool,
    out=None: Optional[torch.Tensor]
)
```

`dim`和`keepdim`参数的作用与[§A.4.1 平均值(`mean()`)](###§A.4.1 平均值(`mean()`))类似，这里不再赘述。

```python
>>> a = torch.arange(24).float().reshape(2,3,4)

>>> a.var()
tensor(50.)

>>> a.var(0) # a[0]和a[1]重叠在一起，求两个数之间的方差
tensor([[72., 72., 72., 72.],
        [72., 72., 72., 72.],
        [72., 72., 72., 72.]])

>>> a.var(1) # a[*][0], a[*][1], a[*][2]重叠在一起，求三个数之间的方差
tensor([[16., 16., 16., 16.],
        [16., 16., 16., 16.]])

>>> a.var(2) # a[*][*][0], a[*][*][1], a[*][*][2], a[*][*][3]重叠在一起，求四个数之间的方差
tensor([[1.6667, 1.6667, 1.6667],
        [1.6667, 1.6667, 1.6667]])
```

### §A.4.3 标准差(`std()`)

`torch.var()`和`torch.Tensor(...).var()`用于计算张量的标准差，计算公式为：
$$
\sigma=\sqrt{\frac{1}{\max(0, N-\text{correction})}\sum_{i=0}^{N-1}(x_i-\overline{x})^2}
$$
该函数从效果上等价于`torch.var().sqrt()`。

`dim`和`keepdim`参数的作用与[§A.4.2 方差(`var()`)](###§A.4.2 方差(`var()`))类似，这里不再赘述。

### §A.4.4 元素数量(`numel()`)

`torch.numel()`和`torch.Tensor(...).numel()`用于统计某个张量包含的元素个数：

```python
torch.numel(
	input: torch.Tensor
) -> int

torch.Tensor(...).numel() -> int
```

张量的元素个数等价于其形状`torch.Size`中的各个元素相乘：

```python
>>> a = torch.ones(1,2,3,4,5)

>>> a.numel()
120 # 1×2×3×4×5

>>> import operator, functools
>>> functools.reduce(operator.mul, a.shape, 1)
120 # a.shape中的每个元素相乘
```

## §A.5 比较操作

比较操作指的是在张量上计算数字谓词的函数。例如`equal()`和`max()`。

### §A.5.1 最大值(`max()`)

`torch.max()`和`torch.Tensor(...).max()`用于返回张量沿某个维度的最大值，以及最大值对应的索引

```python
torch.max(
	input: torch.Tensor,
    dim: Optional[int],
    keepdim: Optional[bool] = False
) -> torch.return_types.max[torch.Tensor, torch.Tensor]

torch.Tensor(...).max(
    dim: Optional[int],
    keepdim: Optional[bool] = False
) -> torch.return_types.max[torch.Tensor, torch.Tensor]
```

以下是一个使用示例：

```python
>>> a = torch.arange(24)[torch.randperm(24)].reshape(2, 3, 4)
# tensor([[[13, 11,  9, 15],
#          [23,  0, 12, 19],
#          [22, 21, 17,  7]],
#         [[ 3,  4,  5, 14],
#          [ 2, 18, 16,  6],
#          [10, 20,  1,  8]]])

>>> a.max(dim=0) # 遍历任意j,k，在i∈{0,1}的两个数内比较最大值
# torch.return_types.max(
#     values=tensor(
#         [[13, 11,  9, 15],
#          [23, 18, 16, 19],
#          [22, 21, 17,  8]]
#     ),
#     indices=tensor(
#         [[0, 0, 0, 0],
#          [0, 1, 1, 0],
#          [0, 0, 0, 1]]
#     )
# )

>>> a.max(dim=1) # 遍历任意i,k，在j∈{0,1,2}的三个数内比较最大值
# torch.return_types.max(
#     values=tensor(
#         [[23, 21, 17, 19],
#          [10, 20, 16, 14]]
#     ),
#     indices=tensor(
#         [[1, 2, 2, 1],
#          [2, 2, 1, 0]]
#     )
# )

>>> a.max(dim=2) # 遍历任意i,j，在k∈{0,1,2,3}的四个数内比较最大值
# torch.return_types.max(
#     values=tensor(
#         [[15, 23, 22],
#          [14, 18, 20]]
#     ),
#     indices=tensor(
#         [[3, 0, 0],
#          [3, 1, 1]]
#     )
# )
```

## §A.6 频谱操作

频谱操作指的是在频域中进行变换和操作的函数。

## §A.7 BLAS/LAPACK操作

BLAS/LAPACK操作值的是符合基本线性代数子程序（BLAS）规范的函数，用于标量、向量与向量、向量与矩阵、矩阵与矩阵之间的操作。

## §A.8 随机采样操作

随机采样操作指的是从概率分布中随机生成数值的函数。例如`randn()`、`normal()`。

### §A.8.1 随机排列(`randperm()`)

`torch.randperm()`接受一个整数`n`，返回一个`0, 1, 2, ..., n-1`随机打乱后的一维张量。

```python
torch.randperm(
	n: int, *,
    generator: Optional[torch.Generator] = None,
    out: Optional[torch.Tensor] = None,
    dtype: Optional[torch.dtype] = torch.int64,
    layout: Optional[torch.layout] = torch.strided,
    device: Optional[torch.device] = None,
    requires_grad: Optional[bool] = False,
    pin_memory: Optional[bool] = False
)
```

如果给形参`n`传递一个一维张量的实参，则PyTorch会报错：

```python
>>> import torch

>>> torch.randperm(5)
tensor([3, 0, 2, 1, 4])

>>> torch.randperm(torch.Tensor(5))
---------------------------------------------------------------------------
TypeError                                 Traceback (most recent call last)
	----> 1 torch.randperm(torch.Tensor(5))
TypeError: randperm(): argument 'n' (position 1) must be int, not Tensor
```

### §A.8.2 Softmax(`softmax()`)

`torch.nn.functional.softmax()`、`torch.softmax()`、`torch.Tensor(...).softmax()`用于沿某个维度计算张量的各分量Softmax值：

```python
torch.softmax(
	input: torch.Tensor,
    dim: int = None, *,
    dtype=None
) -> torch.Tensor

torch.nn.functional.softmax(
	input: torch.Tensor,
    dim: int = None,
    _stacklevel = 3,
    dtype: Optional[torch.dtype] = None
) -> torch.Tensor

torch.Tensor(...).softmax(
	dim: int = None
) -> torch.Tensor
```


$$
\text{Softmax}(x_i)=\frac{e^{x_i}}{\displaystyle\sum_{j=1}^{n}e^{x_j}}
$$
该函数中的维度`dim`作用可以理解为：在形状向量中，按住除`dim`之外的所有`len(tensor.shape) - 1`个维度，随便赋一组值，然后让第`dim`维改变，将改变过程中涉及到的数值集合在一起，参与Softmax运算。

```python
>>> x = torch.arange(2*3*4, dtype=torch.float).reshape(2,3,4)
>>> x
tensor([[[ 0.,  1.,  2.,  3.],
         [ 4.,  5.,  6.,  7.],
         [ 8.,  9., 10., 11.]],
        [[12., 13., 14., 15.],
         [16., 17., 18., 19.],
         [20., 21., 22., 23.]]])

>>> x.softmax(dim=0)
# x[i][j][k]，对于任意j,k，给每个i∈{0,1}放在一起做softmax
tensor([[[6.1442e-06, 6.1442e-06, 6.1442e-06, 6.1442e-06],
         [6.1442e-06, 6.1442e-06, 6.1442e-06, 6.1442e-06],
         [6.1442e-06, 6.1442e-06, 6.1442e-06, 6.1442e-06]],
        [[9.9999e-01, 9.9999e-01, 9.9999e-01, 9.9999e-01],
         [9.9999e-01, 9.9999e-01, 9.9999e-01, 9.9999e-01],
         [9.9999e-01, 9.9999e-01, 9.9999e-01, 9.9999e-01]]])

>>> x.softmax(dim=1)
# x[i][j][k], 对于任意i,k，给每个j∈{0,1,2}放在一起做softmax
tensor([[[3.2932e-04, 3.2932e-04, 3.2932e-04, 3.2932e-04],
         [1.7980e-02, 1.7980e-02, 1.7980e-02, 1.7980e-02],
         [9.8169e-01, 9.8169e-01, 9.8169e-01, 9.8169e-01]],
        [[3.2932e-04, 3.2932e-04, 3.2932e-04, 3.2932e-04],
         [1.7980e-02, 1.7980e-02, 1.7980e-02, 1.7980e-02],
         [9.8169e-01, 9.8169e-01, 9.8169e-01, 9.8169e-01]]])

>>> x.softmax(dim=2)
# x[i][j][k], 对于任意i,j，给每个k∈{0,1,2,3}放在一起做softmax
tensor([[[0.0321, 0.0871, 0.2369, 0.6439],
         [0.0321, 0.0871, 0.2369, 0.6439],
         [0.0321, 0.0871, 0.2369, 0.6439]],
        [[0.0321, 0.0871, 0.2369, 0.6439],
         [0.0321, 0.0871, 0.2369, 0.6439],
         [0.0321, 0.0871, 0.2369, 0.6439]]])
```

## §A.9 序列化操作

序列化操作指的是保存和加载张量的函数。例如`load()`和`save()`。

### §A.9.1 保存(`save()`)

`torch.save()`用于保存模型。`obj: object`代表它能保存很多种对象，例如`model.state_dict() -> OrderedList`和`torch.Tensor`。

```python
torch.save(
    obj: object,
    f: FILE_LIKE,
    pickle_module: Any = pickle,
    pickle_protocol: int = DEFAULT_PROTOCOL,
    _use_new_zipfile_serialization: bool = True,
    _disable_byteorder_record: bool = False
) -> None:
```

### §A.9.2 加载(`load()`)

`torch.load()`用于保存模型。

```python
model = CustomizedNet()
model.load_state_dict(
    torch.load('../data-unversioned/p1ch6/bird_airplane_classification.pt')
)
```

## §A.10 并行化操作

并行化操作指的是用于控制并行CPU执行线程总数的函数。例如`set_num_threads()`。

## §A.11 其它操作

