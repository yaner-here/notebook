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
>
> 

# §A PyTorch API

> 注意：无特殊说明，本章涉及到的函数均为“浅拷贝”。可以实现“深拷贝”的方法如下所示：
>
> - `torch.Tensor(...).clone()`/`torch.clone()`
> - `torch.Tensor(...).contiguous()`
> - `torch.Tensor(...).cuda()`
> - `torch.Tensor(...).reshape()`/`torch.reshape()`（当且仅当输入的张量不连续时）

## §A.1 创建操作

创建操作指的是用于构造张量的函数。例如`ones()`和`from_numpy()`。

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

## §A.3 逐点操作

逐点操作指的是对每个元素分别应用一个函数来得到一个新的张量。例如`abs()`和`cos()`。

### §A.3.1 小于等于(`le()`)

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

## §A.5 比较操作

比较操作指的是在张量上计算数字谓词的函数。例如`equal()`和`max()`。

## §A.6 频谱操作

频谱操作指的是在频域中进行变换和操作的函数。

## §A.7 BLAS/LAPACK操作

BLAS/LAPACK操作值的是符合基本线性代数子程序（BLAS）规范的函数，用于标量、向量与向量、向量与矩阵、矩阵与矩阵之间的操作。

## §A.8 随机采样操作

随机采样操作指的是从概率分布中随机生成数值的函数。例如`randn()`、`normal()`。

## §A.9 序列化操作

序列化操作指的是保存和加载张量的函数。例如`load()`和`save()`。

## §A.10 并行化操作

并行化操作指的是用于控制并行CPU执行线程总数的函数。例如`set_num_threads()`。

## §A.11 其它操作

