# PyTorch

参考书籍：

- PyTorch深度学习实战 [豆瓣](https://book.douban.com/subject/35776474/) [异步社区](https://www.epubit.com/bookDetails?id=UBc833a5819209)

## §1 张量

PyTorch使用的数据结构称为张量（Tensor）。它使用的API与Numpy相似性很高，但是在Numpy的基础上支持GPU加速和分布式计算。

## §1.1 创建张量

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

## §1.2 索引张量

张量索引的语法与列表索引完全一致：

```python
>>> a = torch.arange(12).reshape(3,4)

>>> a 
tensor([[ 0,  1,  2,  3],
        [ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])

>>> a[:]
tensor([[ 0,  1,  2,  3],
        [ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])

>>> a[0:2]
tensor([[0, 1, 2, 3],
        [4, 5, 6, 7]])

>>> a[1:]
tensor([[ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])

>>> a[:2]
tensor([[0, 1, 2, 3],
        [4, 5, 6, 7]])

>>> a[:-1]
tensor([[0, 1, 2, 3],
        [4, 5, 6, 7]])

In [31]: a[0:2:2]
Out[31]: tensor([[0, 1, 2, 3]])
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

