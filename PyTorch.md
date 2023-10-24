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

## §1.4 张量数据类型

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
>>>
```
