# §1 IPython

## §1.1 帮助

- 在原生Python Shell中，使用`help(<function>)`方法可以输出该`function`的使用文档。
- 在IPython Shell中，使用`<function>?`可以输出该`function`的使用文档。
- 在IPython Shell中，使用`<function>??`可以输出该`function`的函数体。

## §1.2 快捷键

### §1.2.1 导航快捷键

| 快捷键     | 效果             |
| ---------- | ---------------- |
| `Ctrl + A` | 将光标移动至行首 |
| `Ctrl + E` | 将光标移动至行末 |

### §1.2.2 文本输入快捷键

| 快捷键      | 效果                            |
| ----------- | ------------------------------- |
| `Backspace` | 删除光标前一个字符              |
| `Ctrl + D`  | 删除光标后一个字符              |
| `Ctrl + K`  | 在Shell内部剪切光标至行末的字符 |
| `Ctrl + U`  | 在Shell内部剪切行首至光标的字符 |
| `Ctrl + Y`  | 粘贴Shell内部剪切的字符         |
| `Ctrl + T`  | 交换光标前两个字符              |

### §1.2.3 历史命令快捷键

| 快捷键       | 效果               |
| ------------ | ------------------ |
| :arrow_up:   | 获取前一个历史命令 |
| :arrow_down: | 获取后一个历史命令 |
| `Ctrl + R`   | 反向查找历史命令   |

### §1.2.4 终端快捷键

| 快捷键     | 效果             |
| ---------- | ---------------- |
| `Ctrl + L` | 清除终端屏幕内容 |
| `Ctrl + C` | 中断终端         |
| `Ctrl + D` | 退出终端         |

### §1.2.5 魔法命令

| 命令                                | 效果                                                         |
| ----------------------------------- | ------------------------------------------------------------ |
| `%magic`                            | 查看魔法函数的帮助文档(`magic?`,`%magic?`均失效)             |
| `%lsmagic`                          | 列举所有的魔法函数                                           |
| `%paste`                            | 去除粘贴板代码中多余的解释符号(`>>>`,`...:`)和缩进，直接运行 |
| `%cpaste`                           | 创建一个用于粘贴代码的会话，去除多余的解释符号(`>>>`,`...:`)和缩进，然后运行 |
| `%run <filename>`                   | 运行指定的`.py`文件                                          |
| `%timeit`                           | 输出单行代码运行时长                                         |
| `%%timeit`                          | 输出多行代码运行时长                                         |
| `%history [-n <startNum>-<endNum>]` | 输出该会话所有输入的指令，`-n`指定起始位置                   |

## §1.3 输入输出

### §1.3.1 `In`和`Out`

`In`字典存储着该会话的输入的历史命令，`Out`字典存储着该会话的输出历史命令。

```python
In [1]: import math

In [2]: math.sin(math.pi/4)
Out [2]: 0.7071067811865476
    
In [3]: print(In[2]**2)
0.5000000000000001
```

> 注意：`Out`字典存储的是命令的返回值，不一定是在终端上的输出值。例如`print()`能在终端上输出，但是它的返回值是`NoneType`，所以对应的`Out`字典键值对为空。

### §1.3.2 `_`

- 在Python Shell中，下划线`_`变量存储着最近一次的输出，类似于计算器的Ans键。
- 在IPython Shell中，可以增加下划线的个数表示上上一次`__`，上上上一次`___`......的输出。

### §1.3.3 禁止输出

在命令末尾添加分号`;`禁止输出，同时输出结果也不会被储存在`Out`字典中。

## §1.4 与Shell交互

`!<command>`能创建一个临时的命令行用于执行指令，输出的内容可以用于赋值。

```python
In [1]: !whoami
'Active code page: 65001'
desktop-0rkindj\Administrator

In [2]: message=!whoami

In [3]: message
Out [3]: ['Active code page: 65001', 'desktop-0rkindj\\闫刚']
```

> 注意：由于每执行一次`!<command>`就创建一个临时的命令行，所以`!cd ..`的效果并不能持续到下一次交互。Windows的默认路径为`C:\Users\<username>`。为了永久更改工作路径，可以使用魔法命令`%cd`或自动魔法命令`cd`。
>
> ```python
> In [1]: %cd C:\
> C:\
> 
> In [2]: cd Windows\
> C:\Windows
> ```

事实上，类似的魔法命令/自动魔法命令还有很多，例如`cat`、`cp`、`env`、`ls`、`man`、`mkdir`、`more`、`mv`、`pwd`、`rm`、`rmdir`等，这使得IPython Shell可以兼容系统自带的Shell。

## §1.5 异常与调试

### §1.5.1 `%xmode`

`%xmode <ExceptionHandlerMode>`用于改变抛出异常的显示信息格式。可用的`<ExceptionHandlerMode>`有：

- `Plain`

  ```python
  In [1]: func(0)
  raceback (most recent call last):
    File "<ipython-input-47-c70cba0ee6d9>", line 1, in <module>
      func2(0)
    File "<ipython-input-39-f99dec502400>", line 2, in func2
      return func1(x,x)
    File "<ipython-input-38-68225868ec77>", line 2, in func1
      return a/b
  ZeroDivisionError: division by zero
  ```

- `Context`

  ```python
  In [2]: func2(0)
  ---------------------------------------------------------------------------
  ZeroDivisionError                         Traceback (most recent call last)
  <ipython-input-50-c70cba0ee6d9> in <module>
  ----> 1 func2(0)
  
  <ipython-input-39-f99dec502400> in func2(x)
        1 def func2(x):
  ----> 2     return func1(x,x)
        3
  
  <ipython-input-38-68225868ec77> in func1(a, b)
        1 def func1(a,b):
  ----> 2     return a/b
        3
  
  ZeroDivisionError: division by zero
  ```

- `Verbose`

  ```python
  In [3]: func2(0)
  <ipython-input-38-68225868ec77> in func1(a=0, b=0)
        1 def func1(a,b):
  ----> 2     return a/b
          a = 0
          b = 0
        3
  
  ZeroDivisionError: division by zero
  ```

- `Minimal`

  ```python
  In [4]: func2(0)
  ZeroDivisionError: division by zero
  ```

### §1.5.2 `%debug`

在上一次抛出异常的地方开启调试模式。可以使用魔法指令`%pdb on`或`%pdb off`来永久开启/关闭调试模式。

在ipdb中可用的部分指令如下：

| 命令                      | 功能                     |
| ------------------------- | ------------------------ |
| `l(ist)`                  | 显示文件路径             |
| `h(elp)`                  | 显示ipdb中所有可用的指令 |
| `q(uit)`                  | 退出调试器，终止执行程序 |
| `c(ontinue)`              | 退出调试器，继续执行程序 |
| `n(ext)`                  | 跳到程序的下一步         |
| 回车                      | 重复前一个命令           |
| `p(rint)(<VariableName>)` | 打印变量                 |
| `r(eturn)`                | 从子进程跳出             |

```python
In [5]: %debug
> <ipython-input-38-68225868ec77>(2)func1()
		1 def func1(a,b):
---->	2 	return a/b
		3 
    
ipdb> print(a)
1
ipdb> print(b)
0
ipdb> a
a = 1
b = 0
ipdb> quit
```

## §1.6 代码分析与计时

| 命令      | 效果                                                         |
| --------- | ------------------------------------------------------------ |
| `%time`   | 输出单个语句执行所需时间，                                   |
| `%timeit` | 输出多个语句执行所需时间，禁用垃圾回收，降低运行效率，动态调整重复执行取平均值的次数 |
| `%prun`   | 利用分析器运行程序(需要`pip install line_profiler`)          |
| `%lprun`  | 利用逐行分析器运行程序(需要`pip install line_profiler`)      |
| `%memit`  | 测量单个语句的内存占用情况(需要`pip install memory_profiler`) |
| `%mprun`  | 通过逐行的内存分析器运行代码(需要`pip install memory_profiler`) |

### §1.6.1 `%time`与`%timeit`

`%time`输出单行代码的执行结果和执行时间。

```python
In[1]: %time sum(range(1000))
Wall time: 0ns
Out[1]: 499500
```

`%timeit`输出多行代码的平均执行时间，**不会输出代码执行结果**。会根据执行时间动态调整执行次数，耗时较长。

```python
In[1]: %timeit sum(range(100))
12.2 µs ± 127 ns per loop (mean ± std. dev. of 7 runs, 100000 loops each)
```

### §1.6.2 `%prun`和`%lprun`

`%prun`输出该语句调用的**各个子函数**的运行时间。

```python
def addRandom(x):
    a=range(1,x)
    b=sum(a)
    return b
In [27]: %prun add(10000000)
         5 function calls in 0.267 seconds

   Ordered by: internal time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.267    0.267    0.267    0.267 {built-in method builtins.sum}
        1    0.000    0.000    0.267    0.267 <ipython-input-16-544fe6fef8af>:1(add)
        1    0.000    0.000    0.267    0.267 {built-in method builtins.exec}
        1    0.000    0.000    0.267    0.267 <string>:1(<module>)
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
```

`%lprun -f <function> <command>`输出该语句中`<function>`内部**各行**的运行时间，需要提前安装(`pip install line_profiler`)并导入IPython中(`%load_ext line_profiler`)。

```python
In [1]: %lprun -f addRandom addRandom(100000000)
Timer unit: 1e-07 s

Total time: 2.60888 s
File: <ipython-input-4-1ad705d10b5a>
Function: addRandom at line 1

Line #      Hits         Time  Per Hit   % Time  Line Contents
==============================================================
     1                                           def addRandom(x):
     2         1         19.0     19.0      0.0      a=range(1,x)
     3         1   26088761.0 26088761.0    100.0      b=sum(a)
     4         1         14.0     14.0      0.0      return b
```

### §1.6.3 `%memit`和`%mprun`

两者作用类似于`%prun`和`%lprun`。

# §2 NumPy

## §2.1 属性

- `nidm`：数组的维度
- `shape`：数组每个维度的大小
- `size`：数组内元素的总数
- `dtype`：数组内元素的数据类型
- `itemsize`：数组各元素占用字节
- `nbytes`：数组总占用字节

```python
import numpy as np
np.random.seed(0)
a = np.random.randint(10,size=5) # 一维数组
b = np.random.randint(10,size=(5,5)) # 二维数组
c = np.random,randint(10,size=(5,5,5)) # 三维数组
```

## §2.2 索引

`array[<index>,<index>,...]`用于获取数组`array`中第`index`个元素，从0开始数，可以为赋值。

在NumPy的`numpy.ndarray`中可以使用Fancy Indexing，即索引`<index>`可以是`list`或`numpy.ndarray`类型的掩码数组。

```python
x = np.array([100,95,58,78,81,89])
print([x[0],x[2],x[3]]) # [100, 58, 78],传统方法
mask = [0,2,3] #  mask = np.array([0,2,3])也可
print(x[mask]) # [100 58 78],掩码方法
mask = np.array([[0,1],[2,3]]) # 不能使用原生list
print(x[mask]) # array([[100,95],[58,78]])

grade = np.array([
	[100,78,92],
	[60,88,87],
	[56,59,59]
])
row = np.array([0,1,2])
col = np.array([0,1,2])
print(grade[row,col]) #获取主对角线上的成绩
```



## §2.3 切片(视图)

`array[<start>:<stop>]`/`array[<start>:<stop>:<step>]`用于对`array`进行切片，取值范围为$[\mathrm{start},\mathrm{stop})$。`start`缺省为`0`，`stop`缺省为`-1`，`step`缺省为`1`。

对于多维数组，各维度切片用`,`分割，语法可以简化。例如对于二维数组而言，`array[0,:]`和`array[0]`等价。

与Python原生的数组不同，NumPy数组的切片实质上是指针。

## §2.4 副本

`array.copy()`用于复制`array`，常与赋值语句搭配使用。

## §2.5 变形

`array.reshape(<shape>)`将m维数组转化为n维数组。必须预先保证前后元素数量一致，否则会引发`ValueError: cannot reshape array of size <num> into shape <num>`。

```python
a = np.arange(1,10,1) # 创建1×9的一维数组
a.reshape(3,3) # 转化为3×3的二维数组
```

$$
\left[\begin{matrix}
1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & 9
\end{matrix}\right]

\Longrightarrow
\left[\begin{matrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9 \\
\end{matrix}\right]
$$

## §2.6 拼接

### §2.6.1 `np.concatenate`

`np.concatenate([array,array,...],[axis=0])`将一系列`array`去除第`axis`维后拼接而成，其中`axis`从零开始数，缺省值为`0`。

```python
x = np.array([[1,2,3],[4,5,6],[7,8,9]])
y = np.array([[-1,-2,-3],[-4,-5,-6],[-7,-8,-9]])
z = np.array([[1,1,1],[0,0,0],[-1,-1,-1]])
np.concatenate([x,y,z])
```

### §2.6.2 `np.hstack`

`np.hstack([array,array,...])`将一系列`array`沿水平栈方向拼接，即`axis=0`的情境。

### §2.6.3 `np.vstack`

`np.vstack([array,array,...])`将一系列`array`沿垂直栈方向拼接，即`axis=1`的情境。

### §2.6.4 `np.dstack`

`np.dstack([array,array,...])`将一系列`array`沿第三维度方向拼接，即`axis=2`的情境。

## §2.7 分裂

### §2.7.1 `np.split`

`np.split(array,cutInterval,[axis=0])`将`array`按照给定的切割区间`cutInterval`切成`n+1`个子`array`，并组合在一起返回一个原生`list`。其中`cutInterval`的取值范围为$\left[\mathrm{start,end}\right)$

```python
x = [1,2,3,4,5,6,7,8,9]
np.split(x,[1,2,4,5])
```

### §2.7.2 `np.hsplit`

`np.hsplit(array,cutInterval)`按水平栈切割，即`axis=0`。

### §2.7.3 `np.vsplit`

`np.hsplit(array,cutInterval)`按垂直栈切割，即`axis=1`。

### §2.7.4 `np.dsplit`

`np.hsplit(array,cutInterval)`按第三维度切割，即`axis=2`。

## §2.8 运算

对于通用函数(ufunc)或运算符而言，数组的运算等价于每个元素的运算。

| 运算符  | 通用函数                    | 效果                         |
| ------- | --------------------------- | ---------------------------- |
| `+`     | `np.add()`                  | 加法                         |
| `-`     | `np.subtract()`             | 减法                         |
| `-`     | `np.negative()`             | 取负数                       |
| `*`     | `np.multiply()`             | 乘法                         |
| `/`     | `np.divide()`               | 除法                         |
| `//`    | `np.floor_divide()`         | 除法向下取整                 |
| `**`    | `np.power()`                | 指数                         |
|         | `np.exp()`                  | 以$e$为底的指数              |
|         | `np.exp2()`                 | 以2为底的指数                |
|         | `np.log()`                  | 以$e$为底的对数              |
|         | `np.log2()`                 | 以2为底的对数                |
|         | `np.log10()`                | 以10为底的对数               |
|         | `np.expm1()`                | $e^x-1$，比间接调用更精确    |
|         | `np.log1p()`                | $\ln(1+x)$，比间接调用更精确 |
| `%`     | `np.mod()`                  | 模                           |
| `abs()` | `np.absolute()`或`np.abs()` | 绝对值                       |
| `==`    | `np.equal()`                | 是否相等                     |
| `!=`    | `np.not_equal()`            | 是否不相等                   |
| `<`     | `np.less()`                 | 是否小于                     |
| `<=`    | `np.less_equal()`           | 是否小于等于                 |
| `>`     | `np.greater()`              | 是否大于                     |
| `>=`    | `np.greater_equal()`        | 是否大于等于                 |

```python
x = np.array([1,2,3,4,5])
print(x) # [1 2 3 4 5]
print(-x) # [-1 -2 -3 -4 -5]
print(x+1) # [2 3 4 5 6]
print(x*2) # [2 4 6 8 10]
print(x/2) # [0.5 1. 1.5 2. 2.5]
print(x//2) # [0 1 1 2 2]
y = np.empty(5)
np.add(x,5,out=y)`
print(y) # [6,7,8,9,10]
```

## §2.9 指定输出

以上所有通用函数都有可选参数`out`，将储存结果的变量赋给该参数。

```python
x = np.arange(5)
y = np.empty(5)
np.add(x,5,out=y)
print(y) # [5. 6. 7. 8. 9.]
np.add(x,5,out=y[::-1])
print(y) # [9. 8. 7. 6. 5.]
```

## §2.10 聚合

| 函数名      | 针对`NaN`的安全版本 | 功能             |
| ----------- | ------------------- | ---------------- |
| `np.sum`    | `np.nansum`         | 求和             |
| `np.prod`   | `np.nanprod`        | 乘积             |
| `np.mean`   | `np.nanmean`        | 平均值           |
| `np.std`    | `np.nanstd`         | 标准差           |
| `np.var`    | `np.nanvar`         | 方差             |
| `np.min`    | `np.nanmin`         | 最小值           |
| `np.max`    | `np.nanmax`         | 最大值           |
| `np.argmin` | `np.nanargmin`      | 最小值的索引     |
| `np.argmax` | `np.nanargmax`      | 最大值的索引     |
| `np.median` | `np.nanmedian`      | 元素的中位数     |
| `np.any`    |                     | 是否存在元素为真 |
| `np.all`    |                     | 是否所有元素为真 |
| `&`         | `np.bitwise_and`    | 与运算           |
| `|`         | `np.bitwise_or`     | 或运算           |
| `^`         | `np.bitwise_xor`    | 异或运算         |
| `~`         | `np.bitwise_not`    | 否运算           |

所有聚合函数形参都有`axis=None`。缺省时以整个数组为计算范围，指定时按照对应的维度分割计算范围。

### §2.10.1 `np.ufunc.reduce`

调用某一聚合函数的`reduce()`方法，可返回数组中各元素进行都合起来调用该函数的结果。

```python
x = np.arrange(5)
np.add.reduce(x) # 10 (0+1+2+3+4)
np.multiply.reduce(x) # 0 (0×1×2×3×4)
```

### §2.10.2 `np.ufunc.accumulate`

存储`np.reduce`过程中每一步的中间结果。

```python
x = np.arange(5)
np.add.accumulate() # array([ 0,  1,  3,  6, 10], dtype=int32)
```

### §2.10.3 外积`np.ufunc.outer`

`np.<function>.outer(x,y)`返回一个关于该聚合函数的二维数组运算表。

```python
x=np.array([1,2])
y=np.array([0,1])
np.multiply.outer(x,y) # array([[0, 1],[0, 2]])
```

### §2.10.4  求和`np.sum`

`np.sum(array)`和`sum(array)`和`array.sum()`都返回`array`中各元素相加的结果，但是`np.sum`在编译码中操作，所以速度更快。

### §2.10.5 最小值`np.min`/最大值`np.max`

`np.min(array)`和`min(array)`和`array.min()`都返回`array`中元素最小值，最大值同理。

## §2.11 广播

1. 如果连个数组维度数不同，则小维度数组会在最左边补一
2. 如果两个数组维度数相同，但在任何一个维度上形状不匹配，则数组的形状会沿着长度为1的维度扩展
3. 如果两个数组维度数相同，但在任何一个维度上形状不匹配，且没有一个数组的维度等于1，则引发异常

$$
\begin{align}
	\left[\begin{matrix}
		1 & 1 & 1 \\
		1 & 1 & 1 \\
	\end{matrix}\right]_{二维数组(2,3)}
	+
	\left[\begin{matrix}
		0 & 1 & 2 \\
	\end{matrix}\right]_{一维数组(3,)}
	&\overset{规则一}{\Longrightarrow}
	\left[\begin{matrix}
		1 & 1 & 1 \\
		1 & 1 & 1 \\
	\end{matrix}\right]_{二维数组(2,3)}
	+
	\left[\begin{matrix}
		0 & 1 & 2 \\
	\end{matrix}\right]_{二维数组(1,3)}\\
	&\overset{规则二}{\Longrightarrow}
	\left[\begin{matrix}
		1 & 1 & 1 \\
		1 & 1 & 1 \\
	\end{matrix}\right]_{二维数组(2,3)}
	+
	\left[\begin{matrix}
		0 & 1 & 2 \\
		0 & 1 & 2
	\end{matrix}\right]_{二维数组(2,3)}\\
	&\Longrightarrow
	\left[\begin{matrix}
		1 & 2 & 3 \\
		1 & 2 & 3
	\end{matrix}\right]
\end{align}
$$

> 扩充：`np.newaxis`的使用
>
> 1. 增加矩阵维度
>    $$
>    \left[\begin{matrix}
>    1 & 2 & 3 \\
>    \end{matrix}\right]_{一维矩阵(3,)}
>    \overset{\mathrm{array[np.newaxis,:]}\\}{\Longrightarrow}
>    \left[\begin{matrix}
>    1 & 2 & 3 \\
>    \end{matrix}\right]_{二维矩阵(1,3)}
>    $$
>
> 2. 矩阵转置
>    $$
>    \left[
>    	\begin{matrix}
>    		1 & 2 & 3
>    	\end{matrix}
>    \right]_{二维矩阵(1,3)}
>    \overset{\mathrm{array[:,np.newaxis]}}{\Longrightarrow}
>    \left[
>    	\begin{matrix}
>    		1 \\
>    		2 \\
>    		3
>    	\end{matrix}
>    \right]_{二维矩阵(3,1)}
>    $$
>    

## §2.12 布尔数组

### §2.12.1 布尔运算

```python
x = np.array([
	[1,2,3],
    [4,5,6],
    [7,8,9]
])
print(x<6) # [[ True  True  True]
 		   #  [ True  True False]
 		   #  [False False False]]
np.sum(x<6) # 5
np.sum( (x<6) & (x>2) ) # 3
np.sum(x<6,axis=1) # array([3,2,0])
```

### §2.12.2 掩码

```python
grade = np.array([
	[100,78,92],
    [60,88,87],
    [56,59,59]
])
isGood = np.all(grade>=60,axis=1) # array([True,True,False])
goodGrade = grade[isGood] # array([[100,78,92],
       					  #        [60,88,87]])
    
```

## §2.13 排序

### §2.13.1 `np.sort`和`np.argsort`

`np.sort(array)`使用快速排序，返回一个从小到大排列的数组，**不改变原`array`的值**，时间复杂度为$O(n\log n)$。可指定形参`axis`，对该方向以外的维度进行排序。

`array.sort()`同理，**但是会改变原`array`的值。**

`np.argsort(array)`返回从小到大元素的索引数组。

### §2.13.2 `np,partition`

`np.partition(arrau,k)`返回一个部分排序的数组，在该数组中存在着一个位置未知的分隔点，将数组实质上分为两个部分。在该点左侧最靠近的值是第$k$小的值，左侧是小于等于第$k$小的值，右侧是大于第$k$小的值，两侧区间无序。也可指定`axis=None`。

`np.argpartition`同理。

# §3 Pandas

## §3.1 Pandas对象

### §3.1.1 `pd.Series`对象

`Series`对象是一个带有索引的一维数组。其中`Series.index`返回一个表示索引类数组对象`pd.Index`，`Series.values`返回一个储存着值的`np.ndarray`数组。

创建`Series`的方法非常多样，可以传列表和字典。

```python
data = pd.Series({ # 传字典
    'string':'hello',
    114514:1919810,
    'float':0.5
})
data = pd.Series([1,2,3,4,5]) # 传列表
print(data) # 0    1
			# 1    2
            # 2    3
			# 3    4
			# 4    5
			# dtype: int64
print(data.index) # RangeIndex(start=0, stop=5, step=1)
print(data.values) # [1 2 3 4 5]
```

相比于`np.ndarray`来说，`pd.Series`在值方面与之等价，在索引方面采用显式定义。

```python
data = pd.Series(['hello',123,0.5],index=['string','number','float'])
print(data) # string    hello
			# number      123
			# float       0.5
			# dtype: object
print(data['string']) # hello
```

切片规则与`np.ndarray`相同，但是起始索引与终止索引不局限于`list`的整数。

```python
data = pd.Series({'name':'Yaner','age':19,'gender':'male'});
data['age':'gender'] # 切片
					 # age    19
					 # gender male
    				 # dtype: object
data_2 = pd.Series({'name':'Yaner','age':19,'gender':'male'},index=['name',2])
	# 按index筛选
    # name    Yaner
	# 2         NaN (2与gender项无关,故返回NaN)
	# dtype: object
```

### §3.1.2 `pd.DataFrame`

`DataFrame`对象是一个带有索引的二维数组。

```python
dictionary_1 = {'Yan':90,'Liu':89,'Wu':93}
dictionary_2 = {'Yan':75,'Liu':75,'Wu':None}
series_1 = pd.Series(dictionary_1)
series_2 = pd.Series(dictionary_2)
```

- 通过单个`Series`创建`DataFrame`：

  ```python
  dataframe = pd.DataFrame(series_1,columns=['grade'])
  	#      grade
  	# Yan     90
  	# Liu     89
  	# Wu      93
  ```

- 通过包含字典的列表创建`DataFrame`：

  ```python
  data = [{'x':i,'f(x)':i**2} for i in range(1,5)] # [{'x': 1, 'f(x)': 1},
  												 #  {'x': 2, 'f(x)': 4},
   												 #  {'x': 3, 'f(x)': 9},
   												 #  {'x': 4, 'f(x)': 16}]
  pd.DataFrame(data) # x  f(x)
  				# 0  1     1
  				# 1  2     4
  				# 2  3     9
  				# 3  4    16
  ```

- 通过储存着`Series`的字典创建`DataFrame`：

  ```python
  pd.DataFrame({'grade_1':series_1,'grade_2':series_2})
  	#      grade_1  grade_2
  	# Yan       90     75.0
  	# Liu       89     75.0
  	# Wu        93      NaN
  ```

- 通过NumPy的二维数组创建`DataFrame`：

  ```python
  pd.DataFrame(np.random.rand(3,2),columns=['random_1','random_2'],index=[1,2,3])
  	#    random_1  random_2
  	# 1  0.939507  0.435512
  	# 2  0.475176  0.762555
  	# 3  0.780940  0.077148
  ```

- 使用结构化数组创建`DataFrame`：

  ```python
  pd.DataFrame(
  	np.zeros(
          3,
          dtype=[('Integer','i8'),('Float','f8')]
      )
  )
  	#    Integer  Float
  	# 0        0    0.0
  	# 1        0    0.0
  	# 2        0    0.0
  ```

可以使用`DataFrame.drop(columnName,[axis])`删除某一列。

### §3.1.3 `pd.Index`

`Index`是一个只读有序数组，也可看作是数学意义上的可含重复元的集合。

```python
index_1 = pd.Index([2,3,5,7,11]) # Int64Index([2, 3, 5, 7, 11], dtype='int64')
index_1[0] = 15 # TypeError: Index does not support mutable operations
index_2 = pd.Index([3,4,5,6,7])
print(index_1 & index_2) #取交集,Int64Index([3, 5, 7], dtype='int64')
print(index_1 | index_2) #取并集,Int64Index([2, 3, 4, 5, 6, 7, 11], dtype='int64')
print(index_1 ^ index_2) #取异或/运算差,Int64Index([2, 4, 6, 11], dtype='int64')
```

## §3.2 `Series`数据选择方法

| 效果                 | 方法                          | 示例                                          |
| -------------------- | ----------------------------- | --------------------------------------------- |
| 像字典一样调用键值对 | `Series[index]`               | `series['a']`                                 |
| 检索键值对是否存在   | `if(value in Series)`         | `if(2 in series)`                             |
| 显式索引创建切片     | `Series[startKey:endKey]`     | $\mathrm{[startKey,endKey\color{red}{]}}$     |
| 隐式索引创建切片     | `Series[startIndex,endIndex]` | $\mathrm{[startIndex,endIndex\color{red}{)}}$ |

| 索引器 | 效果                                                         | 示例                 |
| ------ | ------------------------------------------------------------ | -------------------- |
| `loc`  | 强制认为索引为显式                                           | `series.loc[index]`  |
| `iloc` | 强制认为索引为隐式                                           | `series.iloc[index]` |
| `ix`   | 等价于正常`[]`<br />取值时为显式,切片时数字恒显式,字符串恒隐式 | `series.ix[index]`   |

## §3.3 `DataFrame`数据选择方法

| 效果                                  | 方法                                                         | 示例                          |
| ------------------------------------- | ------------------------------------------------------------ | ----------------------------- |
| 像字典一样调用键值对获取列表          | `DataFrame[column]`<br />`DataFrame.column`                  | `data['age']`<br />`data.age` |
| 转化为无索引二维数组                  | `DataFrame.values`                                           | `data.values`                 |
| 索引与数据同时转置                    | `DataFrame.T`                                                | `data.T`                      |
| 获取单行无索引`numpy.ndarray`一维数组 | `DataFrame.values[rowIndex]`                                 | `data.values[0]`              |
| 获取有索引`DataFrame`二维数组切片     | `DataFrame.iloc[]`<br />`DataFrame.loc[]`<br />`DataFrame.ix[]` |                               |

## §3.4 索引对齐

Pandas在处理两个对象时，会尝试按索引分别计算，未定义的值由可选形参`fill_value`决定，缺省为`NaN`。

```python
grade_1 = pd.Series({'A':90,'B':89,'C':92})
grade_2 = pd.Series({'A':75,'B':75})
grade = pd.DataFrame({'grade_1':grade_1,'grade_2':grade_2,'sum':sum(grade_1,grade_2)})
	#    grade_1  grade_2    sum
	# A       90     75.0  165.0
	# B       89     75.0  164.0
	# C       92      NaN    NaN
grade = pd.DataFrame({'grade_1':grade_1,'grade_2':grade_2,'sum':grade_1.add(grade_2,fill_value=0)})
	#    grade_1  grade_2    sum
	# A       90     75.0  165.0
	# B       89     75.0  164.0
	# C       92      NaN   92.0
```

## §3.5 处理缺失值

| 方法                                                         | 作用                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `pd.isnull()`                                                | 返回一个`shape`和索引都不变的布尔掩码矩阵,用于表示某一元素是否为`NaN` |
| `pd.notnull()`                                               | `~pd.isnull()`                                               |
| `pd.dropna([axis=0],[how='any'],[thresh],[inplace=False]]])` | 按指定的方向删除缺省值<br />`axis`设置删除的方向,默认为`0`,即按行删除<br />`how`设置删除依据,默认为`'any'`,即存在`NaN`就删除,可换为`'all'`<br />`thresh`设置删除阈值,当`NaN`大于该值时才触发删除操作,与`how`冲突<br />`inplace`决定是否原地做替换,缺省为`false`,即必须通过`data=pd.dropna(data)`才能保存更改。 |
| `pd.fillna([value],[method],[axis])`                         | 按指定的规则填充`NaN`<br />当仅指定`value`时,一律将`NaN`替换为`value`<br />当仅指定`method`时,`method='ffill'`表示用上一个值填充,`method='bfill'`表示用下一个值填充,所以填充值可能还是`NaN`<br />对于`DataFrame`而言,指定`method`时还需指定`axis` |

## §3.6 多级索引

```python
index = [('A','grade_1'),('A','grade_2'),('B','grade_1'),('B','grade_2'),('C','grade_1'),('C','grade_2')]
grade = np.random.random(6)*100
data = pd.Series(grade,index=index)
index_multiIndex = pd.MultiIndex.from_tuples(index)
grade_multiIndex = data.reindex(index_new)
print(grade_multiIndex) # A  grade_1     8.756954
				 #    grade_2    25.060009
				 # B  grade_1    95.425902
				 #    grade_2    59.543517
				 # C  grade_1    64.550445
				 #    grade_2    57.213388
				 # dtype: float64
grade_dataFrame = grade_multiIndex.unstack()
	#      grade_1    grade_2
	# A  77.147189   1.811536
	# B  49.274386  86.215879
	# C  13.074714   3.812315
grade_dataFrame.stack() == grade_multiIndex # 展开操作
```

多级索引可以指定列名与行名。

```python
grade_multiIndex.index.names = ['student','grade']
	# student  grade
	# A        grade_1    77.147189
	#          grade_2     1.811536
	# B        grade_1    49.274386
	#          grade_2    86.215879
	# C        grade_1    13.074714
	#          grade_2     3.812315
	# dtype: float6

```

```python
index = pd.MultiIndex.from_product(
    [[2021,2022],['Spring','Summer','Autumn','Winter']],
    names = ['year','season']
)
columns = pd.MultiIndex.from_product(
	[['A','B','C'],['1st','2nd']],
    names = ['person','times']
)
data = (np.random.random(48).reshape(8,6)*5).round().astype(int)
grade = pd.DataFrame(data,index=index,columns=columns)
	# person        A       B       C
	# times       1st 2nd 1st 2nd 1st 2nd
	# year season
	# 2021 Spring   0   3   1   1   4   3
	#      Summer   4   2   2   2   4   1
	#      Autumn   1   4   4   3   2   5
	#      Winter   4   1   1   2   1   5
	# 2022 Spring   0   3   1   4   0   1
	#      Summer   4   4   5   3   4   4
	#      Autumn   3   0   1   4   4   0
	#      Winter   5   4   4   4   1   0
```

## §3.7 行列转换

### §3.7.1 无序索引和有序索引

如果`MultiIndex`是无序索引，则大多数切片操作都会失效。

```python
index = pd.MultiIndex.from_product([['C','B','A'],[1,2]]) # F字母非升序排列
data = pd.Series(np.random.rand(6),index=index)
data.index.names=['person','times']
print(data) # A  1    0.687538
			#    2    0.125460
			# B  1    0.355622
			#    2    0.668548
			# C  1    0.491877
			#    2    0.865860
			# dtype: float64
print(data['B':'C']) # UnsortedIndexError: 'Key length (1) was greater than MultiIndex lexsort depth (0)'
```

可以使用`sort_index()`对`Series`的索引进行排序，使其有有序索引。

```python
data = data.sort_index()
print(data['B':'C']) # person  times
					 # B       1        0.093197
					 #  	   2        0.054322
					 # C       1        0.439719
					 #  	   2        0.811572
					 # dtype: float64
```

### §3.7.2 `stack()`和`unstack()`

对于一个多级索引数据而言，`unstack(level)`可将第`level`级的数据抽离出来，作为新二维数组`pandas.core.frame.DataFrame`的列。

```python
index = pd.MultiIndex.from_product([['China','America'],[2021,2022],['Technology','Economy']])
data = np.arange(1,9)
rank = pd.Series(data,index=index)
```

$$
\left [\begin{matrix}
 China & 2021 & Technology & 1\\
  &  & Economy & 2\\
  & 2022 & Technology & 3\\
  &  & Economy & 4\\
 America & 2021 & Technology & 5\\
  &  & Economy & 6\\
  & 2022 & Technology & 7\\
  &  & Economy & 8
\end{matrix}\right ]
\Longrightarrow 
\begin{cases}
    level=0,
        \begin{bmatrix}
			&  & America & China\\ 
			2021 & Technology & 6 & 2\\
			& Economy & 5 & 1\\
			2022 & Technology & 8 & 4\\
 			& Economy & 7 & 3
		\end{bmatrix}\\
	level=1,
		\begin{bmatrix}
			&  & 2021 & 2022\\ 
			America & Economy & 6 & 8\\
			& Technology & 5 & 7\\
			China & Economy & 2 & 4\\
 			& Tech & 7 & 3
		\end{bmatrix}\\
	level=2,
		\begin{bmatrix}
			&  & Economy & Technology\\ 
			America & 2021 & 6 & 5\\
			& 2022 & 8 & 7\\
			China & 2021 & 2 & 1\\
 			& 2022 & 4 & 3
		\end{bmatrix}
\end{cases}
$$

`stack()`作用相反，$\forall\ \mathrm{level},s.t.\ \mathrm{data.unstack(level).stack=data}$。（一键回家）

### §3.7.3 `reset_index()`和`set_index()`

`reset_index([name=<dataColumnName>])`将多层索引的一维数组`pandas.core.series.Series`转化为`pandas.core.frame.DataFrame`二维数组，可以赋值形参`name`来改变二维数组中数据新列的列名。若原索引列未由`DataFrames.index.names`指定列名列表，则缺省为`level_<i>`。

```python
rank.reset_index(name='sequence')
	#    level_0  level_1     level_2  sequence
	# 0    China     2021  Technology         1
	# 1    China     2021     Economy         2
	# 2    China     2022  Technology         3
	# 3    China     2022     Economy         4
	# 4  America     2021  Technology         5
	# 5  America     2021     Economy         6
	# 6  America     2022  Technology         7
	# 7  America     2022     Economy         8
```

`set_index(list)`返回一个以列表`list`中的字符串为索引的多级索引`DataFrame`。

```python
rank.index.names=['country','year','filed']
rank.reset_index(name='sequence').set_index(['year','sequence'])
	#                country       filed
	# year sequence
	# 2021 1           China  Technology
	#      2           China     Economy
	# 2022 3           China  Technology
	#      4           China     Economy
	# 2021 5         America  Technology
	#      6         America     Economy
	# 2022 7         America  Technology
	#      8         America     Economy
```

## §3.8 合并数据集

### §3.8.1 `pd.concat()`

为方便起见，定义`makeDataFrame(colStr,rowStr)`如下：

```python
def makeDataFrame(rowStr,colStr):
    data = {
        col:[str(row)+str(col) for row in rowStr] for col in colStr
    }
    return pd.DataFrame(data,list(rowStr))
```

`pd.concat(objs)`可用于合并`Series`或`DataFrame`。

```python
series_1 = pd.Series(['A','B'],index=['1st','2nd'])
series_2 = pd.Series(['C','D'],index=['1st','2nd'])
pd.concat([series_1,series_2],axis=1)
```

$$
\left.
	\begin{matrix}
        \left[\begin{matrix}
            1st&A\\
            2nd&B\
        \end{matrix}\right]\\
        \left[\begin{matrix}
            1st&C\\
            2nd&D\\
        \end{matrix}\right]
    \end{matrix}
\right\}
\overset{\mathrm{pd.concat([series\_1,series\_2],axis=1)}}{\Longrightarrow}
\left[\begin{matrix}
	&0&1\\
	1st&A&C\\
	2nd&B&D\\
\end{matrix}\right]
$$

> 注意：`pd.concat()`与`np.concatenate()`的区别在于前者会保留重复的索引。下面是解决该问题的方法。
>
> 1. 捕捉索引重复的错误
>
>    设置`pd.concat(list,[verify_integrity=False])`的可选形参`verify_integrity=True`，当索引重复会触发`ValueError: Indexes have overlapping values: [0, 1]`。
>
> 2. 忽略索引
>
>    忽略原对象中的索引，一律按照`0,1,2,3,...`的顺序进行排列。需要设置设置`pd.concat(list,[ignore_index=False])`的可选形参`ignore_index=True`。
>
>    ```python
>    dataframe_1 = makeDataFrame('12','ab')
>    dataframe_2 = makeDataFrame('12','bc')
>    pd.concat([dataframe_1,dataframe_2],ignore_index=False,axis=1)
>    pd.concat([dataframe_1,dataframe_2],ignore_index=True,axis=1)
>    ```
>
>    $$
>    \left.
>    	\begin{matrix}
>            \left[\begin{matrix}
>                &a&b\\
>                1&1a&1b\\
>                2&2a&2b
>            \end{matrix}\right]\\
>            \left[\begin{matrix}
>                &b&c\\
>                1&1b&1c\\
>                2&2b&2c
>            \end{matrix}\right]
>        \end{matrix}
>    \right\}
>    \overset{\mathrm{pd.concat}}{\Longrightarrow}
>    \begin{cases}
>    	\mathrm{ignore\_index=False},
>            \left[\begin{matrix}
>                &a&b&b&c\\
>                1&1a&1b&1b&1C\\
>                2&2a&2b&2c&2d\\
>            \end{matrix}\right]\\
>        \mathrm{ignore\_index=True},
>        	\left[\begin{matrix}
>        		&0&1&2&3\\
>                1&1a&1b&1b&1C\\
>                2&2a&2b&2c&2d\\
>        	\end{matrix}\right]
>    \end{cases}
>    $$
>
> 3. 增加多级索引
>
>    设置`pd.concat(list,[keys=KeyList])`的可选形参`keys`为储存着新首级索引字符串的列表。
>
>    ```python
>    pd.concat([series_1,series_2],keys=['x','y'])
>    ```
>
>    $$
>    \left.
>    	\begin{matrix}
>            \left[\begin{matrix}
>                &a&b\\
>                1&1a&1b\\
>                2&2a&2b
>            \end{matrix}\right]\\
>            \left[\begin{matrix}
>                &b&c\\
>                1&1b&1c\\
>                2&2b&2c
>            \end{matrix}\right]
>        \end{matrix}
>    \right\}
>    \overset{\mathrm{pd.concat(),keys=[x,y]}}{\Longrightarrow}
>        \left[\begin{matrix}
>            &&a&b&c\\
>            x&1&1a&1b&\mathrm{NaN}\\
>            &2&2a&2b&\mathrm{NaN}\\
>            y&1&\mathrm{NaN}&1b&1c\\
>            &2&\mathrm{NaN}&2b&2c\\
>        \end{matrix}\right]\\
>    $$

可指定`pd.concat(list,[join='outer'])`中的可选形参`join`来设置合并方式。`join='outer'`时取两表并集，`join='inner'`时取两表补集。

可指定`pd.concat(list,[join_axes])`中的存储所需列名的可选形参`join_axes`列表来筛选列名。即$(\mathrm{list_1}\underline{\or/\and}\mathrm{list}_2)\and\mathrm{join\_axes}$。

### §3.8.2 `pd.merge()`

1. 一对一连接

   ```python
   dataframe_1 = pd.DataFrame({
   	'student':['A','B','C','D'],
   	'score_1':[78,93,43,89]
   })
   dataframe_2 = pd.DataFrame({
   	'student':['A','B','C','D'],
   	'score_2':[76,94,61,85]
   })
   dataframe_3 = pd.merge(dataframe_1,dataframe_2)
   	#   student  score_1  score_2
   	# 0       A       78       76
   	# 1       B       93       94
   	# 2       C       43       61
   	# 3       D       89       85
   ```

2. 多对一连接

   ```python
   dataframe_1 = pd.DataFrame({
   	'student':['A','B','C','D'],
   	'class':[101,102,102,102]
   })
   dataframe_2 = pd.DataFrame({
   	'class':[101,102],
   	'teacher':['Smith','Talor']
   })
   dataframe_3 = pd.merge(dataframe_1,dataframe_2)
   	#   student  class teacher
   	# 0       A    101   Smith
   	# 1       B    102   Talor
   	# 2       C    102   Talor
   	# 3       D    102   Talor
   ```

3. 多对多连接

   ```python
   dataframe_1 = pd.DataFrame({
   	'student':['A','B','C','D'],
   	'class':[101,102,102,102]
   })
   dataframe_2 = pd.DataFrame({
   	'class':[101,101,102,102],
   	'teacher':['Smith','Laplace','Talor','Turing']
   })
   dataframe_3 = pd.merge(dataframe_1,dataframe_2)
   	#   student  class  teacher
   	# 0       A    101    Smith
   	# 1       A    101  Laplace
   	# 2       B    102    Talor
   	# 3       B    102   Turing
   	# 4       C    102    Talor
   	# 5       C    102   Turing
   	# 6       D    102    Talor
   	# 7       D    102   Turing
   ```

- `on`参数用于指定用于合并的参考列，当且仅当两个表存在相同的列，且表示的含义相同时才能用。例`pd.merge(dataframe_1,dataframe_2,on='student')`

- `left.on`和`right.on`参数用于指定左右两表分别用于合并的参考列，当且仅当两表存在含义相同，但列名不同的列时才能用。得到的结果中两个参考列同时存在，引起重复，可以用`DataFrame.drop(columnName,axis=1)`从中任选一列删除。例`pd.merge(dataframe_1,dataframe_2,left.on='student',right.on='pupil')`

- `left_index`和`right_index`参数将左右两表的索引设置为键来实现合并。已经使用`DataFrame.set_index(indexName)`的`DataFrame`已丢失原有的递增整数列，直接使用`pd.merge()`时会产生`MergeError: No common columns to perform merge on.`。此时需要指定这两个参数均为`True`。

- `how`设定不同表的行之间的连接规则，有内连接`how='inner'`取行与行的交集、外连接`how='outer'`取行与行的并集，左连接`how='left'`只取左表的行，右连接`how='right'`只取右边的行。以上方式中未定义的值全部取`NaN`。
- `suffixs`设定两表存在相同的非索引列的列名时，左右两表的列名分别添加怎样的后缀，并将两个后缀以字符串的形式存储在列表中。缺省值为`suffixs=[_x,_y]`。



### §3.8.3 `DataFrame.join()`

`DataFrame.join(DataFrame)`即为`left_index`和`right_index`均为`True`的情境。

```python
dataframe_1 = pd.DataFrame({'student':['A','B','C'],'level':[1,2,3]})
dataframe_2 = pd.DataFrame({'student':['A','B','C'],'age':[5,5,6]})
dataframe2.join(dataframe_1) # ValueError: columns overlap but no suffix specified
dataframe_1 = dataframe_1.set_index('student')
dataframe_2 = dataframe_2.set_index('student')
dataframe_2.join(dataframe_1) #       age  level
						   # student
						   # A          5      1
                           # B          5      2
                           # C          6      3
```

### §3.8.4 `DataFrame.groupby()`

`DataFrame.groupby(columnName)`返回一个`DataFrameGruopBy`对象，可以看作是将`columnName`中各值进行分组后产生的各种`DataFrame`的集合。`DataFrameGruopBy[columnName]`得到`pandas.core.groupby.SeriesGroupBy`对象。

事实上，`columnName`非常灵活：

- `columnName`是表示列名的字符串

  ```python
  dataframe = pd.DataFrame(
      {
          'key':['A','A','B','B','C','C'],
      	'data':[1,5,3,6,7,2],
          'rank':[6,3,4,2,1,5]
      },
      columns=['key','data','rank']
  )
  dataframe.groupby('key').sum() #      data  rank
  							   # key
  							   # A       6     9
  							   # B       9	   6
  							   # C       9     6
  dataframe.groupby('key')['data'] # key
  								 # A    6
  								 # B    9
  								 # C    9
  								 # Name: data, dtype: int64
  ```

- `columnName`是用于存储身份字符串的列表

  ```python
  identity = [1,1,1,2,2,3] # 1~3为一组,4~5为一组,6单独一组
  dataframe.groupby(identity).sum() #    data  rank
  								  # 1     9    13
  								  # 2    13     3
  								  # 3     2     5
  ```

- `columnName`是用于表示身份的字典

  ```python
  # 键为当前索引中的值,值为新组名
  identity = {1:'Male',2:'Female',3:'Female'}
  dataframe.groupby(identity).sum() #         data  rank
  								  # Female     9     6
  								  # Male       5     3
  ```

- `columnName`是用于返回身份信息的函数名

  ```python
  def identity(name):
  	if(str(name)=='1'): return 'Male'
      if(str(name)=='2'): return 'Female'
      if(str(name)=='3'): return 'Female'
  dataframe.groupby(identity).sum() #         data  rank
  								  # Female     9     6
  								  # Male       5     3
  ```

- `columnName`是用于储存任意**函数名、列表、字典混合体**的列表，返回一个带有该列表各元素构成的多级索引数组。TODO?????????????????????

  ```python
  dateframe = dataframe.set_index(['data','rank'])
  identity_1 = [1,1,1,2,2,3] # 1~3为一组,4~5为一组,6单独一组
  def identity_2(number): #倒序排列
      if number == 1: return 'a'
      if number == 2: return 'b'
      if number == 3: return 'c'
  dataframe.groupby([identity1])????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
  ```

可以使用循环对`DataFrameGruopBy`穷举。

```python
for (key,group) in dataframe.groupby('key'):
    print("The shape of "+ key + " is " + str(group.shape))
	# The shape of A is (2, 3)
	# The shape of B is (2, 3)
	# The shape of C is (2, 3)
```

### §3.8.5 `DataFrameGruopBy.aggregate()`

`FrameGruopBy.aggregate()`能方便的实现累加操作。

- 传函数列表`[function_1,function_2,...]`

  ```python
  dataframe = pd.DataFrame(
      {
          'key':['A','B','C','A','B','C'],
          'data1':[0,1,2,3,4,5],
          'data2':[5,0,3,3,7,9]
      },
      columns=['key','data1','data2']
  )
  # 函数列表中,函数指针或函数名字符串均可,以下三种方式等效
  dataframe.groupby('key').aggregate(['min',np.median,max])
  dataframe.groupby('key').aggregate([min,np.median,'max'])
  dataframe.groupby('key').aggregate([min,np.median,max])
  	#     data1            data2
  	#       min median max   min median max
  	# key
  	# A       0    1.5   3     3    4.0   5
  	# B       1    2.5   4     0    3.5   7
  	# C       2    3.5   5     3    6.0   9
  ```

- 传字典`{'column_1:[functionList],column_2:[functionList]'}`

  ```python
  dataframe.groupby('key').aggregate(
      {'data1':['min',max],'data2':np.median}
  )
  	#         data1      data2
  	#       min max median
  	# key
  	# A       0   3    4.0
  	# B       1   4    3.5
  	# C       2   5    6.0
  ```

### §3.8.6 `DataFrame.filter(function)`

`DataFrame.filter(function)`需要一个只包含一个形参`dataframe`的函数用于筛选。

```python
def isLargeStd(dataframe,column,maxStd):
    def isLargeStdExplict(dataframe):
        return dataframe[column].std()>maxStd
    return isLargeStdExplict
?????????????????(TODO://)
```

### §3.8.7 `DataFrame.transform(function)`

`DataFrame.transform(function)`需要一个只包含一个形参`dataframe`的函数用于对每个元素进行替换。

```python
dataframe.groupby('key').transform(lambda x:x.mean())
```

### §3.8.8 `DataFrame.apply(function)`

```python
def func(dataframe):
    dataframe['data1'] += dataframe['data2']
    dataframe.columns=['key','data1+data2','data2']
    return dataframe
dataframe.groupby('key').apply(func)
	#        key  data1+data2  data2
	# data12
	# 0        A            5      5
	# 1        B            1      0
	# 2        C            5      3
	# 3        A            6      3
	# 4        B           11      7
	# 5        C           14      9
```

## §3.9 切割数据集

### §3.9.1 `pd.cut()`

`pd.cut(x,bins)`按照`numeric`型列表`bins`存储的分隔点，将一维数据集`x`中的各元素映射到不同的左开右闭区间。

```python
import numpy as np; import pandas as pd; import seaborn as sns
titanic = sns.load_dataset('titanic')
titanic.head()
#    survived  pclass     sex   age  ...    who adult_male alive
# 0         0       3    male  22.0  ...    man       True    no
# 1         1       1  female  38.0  ...  woman      False   yes
# 2         1       3  female  26.0  ...  woman      False   yes
# 3         1       1  female  35.0  ...  woman      False   yes
# 4         0       3    male  35.0  ...    man       True    no
# [5 rows x 15 columns]
pd.cut(titanic['age'],np.arange(0,100,10))
	# 0      (20.0, 30.0]
	# 1      (30.0, 40.0]
	# 2      (20.0, 30.0]
	#            ...
	# 887    (10.0, 20.0]
	# 888             NaN
	# 889    (20.0, 30.0]
	# 890    (30.0, 40.0]
	# Name: age, Length: 891, dtype: category
	# Categories (9, interval[int64]): [(0, 10] < (10, 20] < (20, 30] < (30, 40] ... (50, 60] < (60, 70] < (70, 80] < (80, 90]]
```

### §3.9.2 `pd.qcut()`

`pd.qcut(x,maxGroup)`将一维数据集`x`分成元素数量尽可能相等的`maxGroup`个组，分隔点由程序自行确定。

```python
pd.qcut(titanic['age'],5)
	# 0       (19.0, 25.0]
	# 1       (31.8, 41.0]
	# 2       (25.0, 31.8]
	#            ...
	# 888              NaN
	# 889     (25.0, 31.8]
	# 890     (31.8, 41.0]
	# Name: age, Length: 891, dtype: category
	# Categories (5, interval[float64]): [(0.419, 19.0] < (19.0, 25.0] < (25.0, 31.8] < (31.8, 41.0] < (41.0, 80.0]]
```

### §3.9.3 `pd.pivot_table()`

`pd.pivot_table(values,index,columns,fill_value=None,dropna=True,aggfunc='mean',margins_name'All')`将数据集`values`按照给定的行列表`index`组建多级索引，按照给定的列列表以先后的形式绘制不同层次的数据表。

```python
age = pd.qcut(titanic['age'],2) # 将年龄分成两类
fare = pd.qcut(titanic['fare'],2) # 按车票分成两类
titanic.pivot_table('survived',['sex',age],[fare,'class']).round(2)
	# fare                 (-0.001, 14.454]    (14.454, 512.329]
	# class                First Second Third  First Second Third
	# sex    age                              
	# female (0.419, 28.0] NaN   0.92   0.61   0.93  0.92   0.37
	#        (28.0, 80.0]  NaN   0.88   0.27   0.98  0.95   0.33
	# male   (0.419, 28.0] NaN   0.04   0.15   0.57  0.45   0.20
	#        (28.0, 80.0]  0.0   0.13   0.13   0.36  0.04   0.14
```

- `fill_value=None`将数据集中的`NaN`替换为预先由该形参设定的值，缺省为`None`。

- `dropna=True`决定是否忽略数据集中全为的`NaN`行，缺省为`True`。

- `aggfunc='mean'`设置累计函数类型，可用函数名字符串或函数指针表示，或者由以上所述作为值、相应的列名作为键构成的字典，针对不同的列应用不同的累计函数

  | 可选值                | 效果   |
  | --------------------- | ------ |
  | `'mean'`(不能带引号)  | 求均值 |
  | `'sum'`或`sum`        | 求和   |
  | `'count'`(不能带引号) | 计数   |
  | `'min'`或`min`        | 最小值 |
  | `'max'`或`max`        | 最大值 |
  | `np.sum`(不能带引号)  | 求和   |
  | `np.min`(不能带引号)  | 最小值 |
  | `np.max`(不能带引号)  | 最大值 |

  ```python
  titanic.pivot_table(
      index='sex',
      columns='class',
      aggfunc={'survived':sum,'fare':'mean'}
  )
  	#               fare                       survived
  	# class        First     Second      Third    First Second Third
  	# sex
  	# female  106.125798  21.970121  16.118810       91     70    72
  	# male     67.226127  19.741782  12.661633       45     17    47
  ```
  
- `margin=False`决定是否增加“总数”一行和“总数”一列。

  ```python
  titanic.pivot_table('survived',index='sex',columns='class').round(2)
  	# class   First  Second  Third
  	# sex
  	# female   0.97    0.92   0.50
  	# male     0.37    0.16   0.14
  titanic.pivot_table('survived',index='sex',columns='class',margins=True).round(2)
  	# class   First  Second  Third   All
  	# sex
  	# female   0.97    0.92   0.50  0.74
  	# male     0.37    0.16   0.14  0.19
  	# All      0.63    0.47   0.24  0.38(总生还率38%)
  ```

## §3.10 字符串向量化

虽然原生Python支持字符串向量化，但是字符串对象内置的方法在异常处理方面有诸多缺陷。

  ```python
  data = ['hello',None,'world']
  data_capittal = [item.capitalize for item in data]
  # AttributeError: 'str' object has no attribute 'capitalize'
  ```

Pandas在异常处理方面做了优化。

```python
data = pd.Series(['hello',None,'world'])
data.str.capitalize() # 0    Hello
					  # 1     None
					  # 2    World
					  # dtype: object

```

## §3.11 时间序列

### §3.11.1 `datetime()`

`datetime(year,month,day[,hour[,minute,[second,[microsecond[,tzinfo]]]]])`是原生Python的`datetime`库中的方法。

```python
from datetime import datetime
datetime.datetime(2022,1,8,15,32) # 2022.1.8 15:32
```

### §3.11.2 `parser.parse()`

`parser.parse(timestr)`是原生Python的`dateutil`库中的方法，将表示时间的字符串`timestr`转换为相应的`datetime.datetime`对象。

```python
from dateutil import parser
date = parser.parse('2021-1-8 15:33')
date = parser.parse('Jan 1st, 2021, 11:15')
```

### §3.11.3 `datetime.datetime.strftime()`

`datetime.datetime`对象内置方法`strftime(formatStr)`，根据给定的字符串将该对象存储的时间按格式输出。`formatStr`的更多信息见[参考链接](https://docs.python.org/3/library/datetime.html#strftime-and-strptime-format-codes)。

### §3.11.4 `np.datetime64`

NumPy定义了64位精度的时间类型`numpy.datetime64`。传参时年份必须是四位数整，月份必须是两位数整，日必须是两位数整，若不足位数要求则左侧补零。

```python
import numpy as np
date = np.datetime64('2022-01-08 12:00')
	# numpy.datetime64('2022-01-08T12:00')
date = np.array('2022-1-8 12:00:00',dtype=np.datetime64)
	# ValueError: Cannot create a NumPy datetime other than NaT with generic units
date = np.array('2022-01-08 12:00:00',dtype=np.datetime64)
	# array('2022-01-08', dtype='datetime64[D]')
```

### §3.11.5 `pd.timestamp`

Pandas利用`timestamp`对象表示时间。

```python
import pandas as pd
date = pd.to_datetime("4th of July, 2022, 11:54:01")
	# Timestamp('2022-07-04 11:54:01')
```

### §3.11.6 `pd.DatetimeIndex()`

Pandas内置方法，用于创建以时间为索引的索引列。

```python
index = pd.DatetimeIndex(['2020.01.01','2021.02.02','2022.03.03'])
data = pd.Series(['1st','2nd','3rd'],index=index)
print(data) # 2020-01-01    1st
			# 2021-02-02    2nd
			# 2022-03-03    3rd
			# dtype: object
```

对于`pandas.core.indexes.datetimes.DatetimeIndex`对象构成的索引列，除了与原字符串一字不差的索引方式之外，还有其他更灵活的方式，例如`data[2015]`将索引一切2015年的条目。

### §3.11.7 `pd.to_datetime()`

接受一个或多个参数，包括日期字符串、`datetime.datetime`对象、及这两种对象构成的列表，并将这些参数统一转化成`datetime.datetime`对象。若参数数量仅为一个，则返回相应的`datetime.datetime`对象；若参数数量为多个，则返回这些对象构成的`pandas.core.indexes.datetimes.DatetimeIndex`对象作为索引列。

### §3.11.8 `PeriodIndex`和`DatetimeIndex.to_period()`

`DatetimeIndex.to_period(freq)`将`pandas.core.indexes.datetimes.DatetimeIndex`对象转化成`pandas._libs.tslibs.period.Period`对象。

`freq`参数如下，更多信息请参考[`offset_aliases`官方文档](https://pandas.pydata.org/pandas-docs/stable/user_guide/timeseries.html#offset-aliases)。

| 频率代码 | 描述              | 频率代码 | 描述                       |
| -------- | ----------------- | -------- | -------------------------- |
| `'D'`    | 天(calendar day)  | `'L'`    | 毫秒(milliseconds)         |
| `'W'`    | 周(weekly)        | `'U'`    | 微秒(microseconds)         |
| `'M'`    | 月末(month end)   | `'N'`    | 纳秒(nanoseconds)          |
| `'Q'`    | 季末(quarter end) | `'B'`    | 工作日(business day)       |
| `'A'`    | 年末(year end)    | `'BN'`   | 月末(business month end)   |
| `'H'`    | 小时(hours)       | `'BQ'`   | 季末(business quarter end) |
| `'T'`    | 分钟(minutes)     | `'BA'`   | 年末(business year end)    |
| `'S'`    | 秒(seconds)       | `'BH'`   | 工作时(business hours)     |

```python
date = pd.to_datetime([
    datetime(2015, 7, 3),
    '4th of July, 2015',
    '2015-Jul-6',
    '07-07-2015',
    '20150708',
])
date.to_period('D')
	# PeriodIndex(
    # 	['2015-07-03', '2015-07-04', '2015-07-06', '2015-07-07', '2015-07-08'],
	# 	dtype='period[D]',
    #	freq='D'
    # )
```

### §3.11.9 `TimedeltaIndex`

当一个日期减另一个日期时，得到的结果为`TimedeltaIndex`类型。

```python
date = pd.to_datetime([
    datetime(2015, 7, 3),
    '4th of July, 2015',
    '2015-Jul-6',
    '07-07-2015',
    '20150708',
])
date - date[0]
	# TimedeltaIndex(
    #	['0 days', '1 days', '3 days', '4 days', '5 days'], 
    #	dtype='timedelta64[ns]',
    #	freq=None
    # )
```

### §3.11.10 `pd.date_range()`

`pd.date_range()`用于创建等间隔的时间序列，足够灵活。

- `pd.date_range(startDate,endDate)`指定起始和终止范围

  ```python
  pd.date_range('20200108','20200112')
  	# DatetimeIndex(
      # ['2020-01-08', '2020-01-09', '2020-01-10', '2020-01-11', '2020-01-12'],
      # dtype='datetime64[ns]',
      # freq='D'
      # )
  ```

- `pd.date_range(startDate,periods,freq='D')`指定起始点、时间间隔和周期次数。

  ```python
  pd.date_range('20220108',periods=5)
  	# DatetimeIndex(
      #	['2022-01-08', '2022-01-09', '2022-01-10', '2022-01-11', '2022-01-12'],
      #	dtype='datetime64[ns]',
      #	freq='D'
      # )
  pd.date_range('20220108',periods=5,freq='H')
  	# DatetimeIndex(
      #	['2022-01-08 00:00:00', '2022-01-08 01:00:00', '2022-01-08 02:00:00', '2022-01-08 03:00:00', '2022-01-08 04:00:00'],
      # dtype='datetime64[ns]',
      # freq='H'
      # )
  ```

  关于`freq`的更多内容，参考[dateoffset-objects官方文档](http:// pandas.pydata.org/pandas-docs/stable/timeseries.html#dateoffset-objects)。

## §3.12 重新取样

为方便起见，以下列股价数据为例：

```python
!pip install pandas_datareader
from pandas_datareader import data
goog = data.DataReader('GOOG',start='2004',end='2016',data_source='yahoo')['Close']
```

### §3.12.1 `Series.resample()`

`Series.resample(rule)`接受一个用于指定取样规则的`offset_aliases`字符串。

```python
good.resample('BA').mean() # 'BA'为年末最后一个工作日
	# 2004-12-31     75.617206
	# 2005-12-30    138.360933
	# 2006-12-29    204.824916
	# 	......
	# 2014-12-31    559.803290
	# 2015-12-31    602.005681
	# 2016-12-30           NaN
	# Freq: BA-DEC, Name: Close, dtype: float64
```

### §3.12.2 `Series.asfreq()`

`Series.asfreq(rule,method=None)`在前者的基础上增加了处理`NaN`的方法，包括`ffill`或`'pad'`向前取值、`bfill`或`backfill`向后取值。

## §3.13 数据迁移

将数据的时间索引列或数据本身向后延迟指定的天数。

### §3.13.1 `Series.shift()`

`Series.shift(day)`将数据向后迁移至`day`天以后。

### §3.13.2 `Series.tshift()`

`Series.tshift(day)`将数据的时间索引列中的时间向后迁移至`day`天以后。

```python
goog = goog.asfreq('D',method='pad')
goog
	# Date
	# 2004-08-19     49.982655
	# 2004-08-20     53.952770
	#                  ...
	# 2015-12-30    771.000000
	# 2015-12-31    758.880005
	# Freq: D, Name: Close, Length: 4152, dtype: float64
goog.shift(365*2)
	# Date
	# 2004-08-19           NaN
	# 2004-08-20           NaN
	#                  ...
	# 2015-12-30    552.658508
	# 2015-12-31    558.262512
	# Freq: D, Name: Close, Length: 4152, dtype: float64
goog.tshift(365*2)
	# Date
	# 2006-08-19     49.982655
	# 2006-08-20     53.952770
	#                  ...
	# 2017-12-29    771.000000
	# 2017-12-30    758.880005
	# Freq: D, Name: Close, Length: 4152, dtype: float64
```

## §3.14 高性能

### §3.14.1 `numexpr.evaluate()`

在计算`NumPy`数组相关的复合代数式时，Numpy会尝试为每一个子运算显示地分配内存。如果数据集特别大，那么消耗的空间和时间就会非常多。**只要能在Python执行的语句，都可以作为字符串成为该函数的形参**。

```python
import numpy as np
rng = np.random.RandomState(42)
x = rng.rand(1000000)
y = rng.rand(1000000)
%timeit mask = (x>0.5)&(y>0.5)
	# 1.37 ms ± 38.9 µs per loop (mean ± std. dev. of 7 runs, 1000 loops each)
```

`numexpr`可以在不为中间过程分配全部内存的前提下，高效地完成复合代数式的运算。

```python
!pip install numexpr
import numexpr
%timeit mask_new = numexpr.evaluate('(x>0.5)&(y>0.5)')
	# 1.24 ms ± 12.3 µs per loop (mean ± std. dev. of 7 runs, 1000 loops each)
np.allclose(mask,mask_new) # True,用于检测两个NumPy数组是否相同
```

### §3.14.2 `pd.eval()`

在计算关于`DataFrame`的复合代数式中，`Pandas`提供的`pd.eval()`也能失效类似的高性能运算。**但是现在只支持各类运算符(减加乘除/大于小于/与或异或)，不支持条件判断、函数引用、循环等更复杂的运算**，只有用`numexpr`才能实现。

```python
import numpy as np
import pandas as pd
rng = np.random.RandomState(42)
(df1,df2,df3,df4) = (
    pd.DataFrame(rng.rand(1000,1000)) for i in range(4) 
)
%timeit df1+df2+df3+df4
	# 6.85 ms ± 156 µs
%timeit pd.eval('df1+df2+df3+df4')
	# 5.07 ms ± 24.4 µs
```

### §3.13.3 `DataFrame.eval()`

相比于Pandas提供的顶层函数`pd.eval()`，`DataFrame`对象自身的方法 `DataFrame.eval()`能借助列名称进行运算。

```python
df = pd.DataFrame(rng.rand(1000000,3),columns=['A','B','C'])
%timeit (df['A']+df['B'])*df['C']
	# 4.88 ms ± 119 µs
%timeit pd.eval("(df.A+df.B)*df.C")
	# 3.38 ms ± 256 µs
%timeit df.eval('(A+B)*C')
	# 3.13 ms ± 76.2 µs
```

`pd.eval()`还可以用来创建新列。

```python
df.eval('D = (A+B)*C')
	#                A         B         C         D
	# 0       0.234499  0.512939  0.586996  0.438743
	# 1       0.088856  0.425749  0.701733  0.361115
	# ...          ...       ...       ...       ...
	# 999998  0.587530  0.636789  0.919383  1.125619
	# 999999  0.888825  0.764271  0.541484  0.895126
```

### §3.14.3 `DataFrame.query()`

为了筛选出符合某些条件的行，我们的思路一般是先求出对应的掩码矩阵，再将其作为依据使用`dataframe[mask]`进行筛选。实际上`DataFrame`中定义了一种更快的方法`DataFrame.query(screenConditionStr)`。

```python
%timeit df[(df.A>0.5)&(df.B>0.5)]
	# 12.5 ms ± 109 µs
%timeit pd.eval('df[(df.A>0.5)&(df.B>0.5)]')
	# 25.5 ms ± 1.05 ms
%timeit df.query('A>0.5 and B>0.5')
	# 17.7 ms ± 71.9 µs
```

`screenConditionStr`中也可以使用`@`表示的局部变量。

```python
Cmean = df['C'].mean()
df[(df.A < Cmean) & (df.B < Cmean)]
df.query('A < @Cmean and B < @Cmean')
```

# §4 Matplotlib

```python
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib as mpl
import matplotlib.pyplot as plt
%matplotlib inline
```

## §4.1 使用技巧

### §4.1.1 设置绘图样式

```python
plt.style.use('classic')
```

`plt.plot(x,y,[color],[linestyle])`提供了`color`参数以改变线条的颜色，`linestyle`参数以改变线条的线型。

| `color`取值举例                               | 效果                                                         |
| --------------------------------------------- | ------------------------------------------------------------ |
| `color='blue'`                                | 标准颜色名称(`red`,`grey`,`purple`,...)                      |
| `color='g'`                                   | 缩写颜色代码(`r`,`g`,`b`,`c`,`m`,`y`,`k`,...)                |
| `color='0.75'`                                | 灰度值(取值范围0~1)                                          |
| `color='#66CCFF'`                             | 十六进制颜色代码(`#66CCFF`,...)                              |
| `color=(1.0,0.3,0.4)                        ` | RGB元组(三个分别代表RGB值的0~1浮点数构成的元组)              |
| `color='chartreuse'`                          | [HTML颜色名称](https://www.runoob.com/html/html-colornames.html) |

| `linestyle`取值举例                     | 效果   |
| --------------------------------------- | ------ |
| `linestyle='solid'`或`linestyle='-'`    | 实线   |
| `linestyle='dashed'`或`linestyle='--'`  | 虚线   |
| `linestyle='dashdot'`或`linestyle='-.'` | 点划线 |
| `linestyle='dotted'`或`linestyle=':'`   | 实点线 |

可以将两者混合起来一起使用。（颜色代码仅支持RGB和CMYK）

```python
plt.plot(x,np.sin(x),'-.k')
```

### §4.1.2 开发环境

- `.py`脚本

  必须使用`plt.show()`才能显示图形。在该方法执行之前可以多次调用`plt.plot()`，从而在同一个窗口显示两个函数图像。一个Python的会话(Session)中**只能使用一次该方法**，否则会导致难以预料的显示异常。

  ```python
  x = np.linspace(0,10,100)
  plt.plot(x,np.sin(x))
  plt.plot(y,np.cos(x))
  plt.show()
  ```

- IPython Shell

  IPython Shell默认操作与`.py`脚本一致，但是可以多次调用`plt.show()`方法。可以使用魔法命令`%matplotlib`将`matplotlib backend`设为`Qt5Agg`，使得每调用一次`plt.plot()`就会弹出一次交互式窗口，但是前后绘制的图像会累积，可以使用`plt.draw()`强制刷新。

  ```python
  In [17]: %matplotlib
  Using matplotlib backend: Qt5Agg
  ```

- IPython Notebook

  IPython Notebook中的图形有两种展现形式：

  - `%matplotlib notebook`启用交互式图形
  - `%matplotlib inline`启用静态行内图形，以`.png`格式存储在`Out`列表中

### §4.1.3 保存图像

```python
functionImage = plt.figure()
plt.plot(x,np.sin(x))
functionImage.savefig('result.png') # 在当前路径下创建文件
from IPython.display import Image
Image('result.png')
```

支持的图像格式有：

```python
functionImage.canvas.get_supported_filetypes()
	# {'eps': 'Encapsulated Postscript',
	#  'jpg': 'Joint Photographic Experts Group',
	#  'jpeg': 'Joint Photographic Experts Group',
	#  'pdf': 'Portable Document Format',
	#  'pgf': 'PGF code for LaTeX',
	#  'png': 'Portable Network Graphics',
	#  'ps': 'Postscript',
	#  'raw': 'Raw RGBA bitmap',
	#  'rgba': 'Raw RGBA bitmap',
	#  'svg': 'Scalable Vector Graphics',
	#  'svgz': 'Scalable Vector Graphics',
	#  'tif': 'Tagged Image File Format',
	#  'tiff': 'Tagged Image File Format'}
```

选择格式时，只需在`savefig(filename)`的`filename`中设置对应的后缀名即可。



### §4.1.4 画图接口

- MATLAB风格接口

  ```python
  plt.figure() # 创建图形
  
  plt.subplot(2,1,1) # 设置子图使用的坐标轴,(行,列,子图编号)
  plt.plot(x,np.sin(x)) # 只在最后一个plt.plot()才弹出窗口
  
  plt.subplot(2,1,2) # 设置子图使用的坐标轴,(行,列,子图编号)
  plt.plot(x,np.cos(x)) # 只在最后一个plt.plot()才弹出窗口
  
  plt.subplot(2,1,1) # 返回到第一个子图,对其进行补充或修改
  plt.plot(x,np.cos(x)) # 执行到次数才弹出窗口
  ```

- 面向对象接口

  `plt.subplots(subplotNum)`返回一个元组`(fig,ax)`，元组内的元素类型分别为`matplotlib.figure.Figure`和`numpy.ndarray`

  ```python
  (flg,ax)=plt.subplots(2)
  x=np.linspace(0,10,100)
  ax[0].plot(x,np.sin(x))
  ax[1].plot(x,np.cos(x))
  ```
  

### §4.1.5 调整坐标轴

- `plt.xlim()`和`plt.ylim()`

  `plt.xlim(left,right)`和`plt.tlim(left,right)`分别用于指定x轴和y轴的取值范围。当`right>left`时正常顺序显示，反之逆序显示.。

  ```python
  plt.plot(x,np.sin(x)+2)
  plt.xlim(-1,11)
  plt.ylim(4,0)
  ```

- `plt.axis()`

  - `plt.axis([xmin,xmax,ymin,ymax])`接受一个列表`[xmin,xmax,ymin,ymax]`，用于指定x轴和y轴的显示范围。

    ```python
    plt.plot(x,np.sin(x)+2)
    plt.axis([-1,11,4,0])
    ```

  - `plt.axis(option)`接受一个字符串`option`，用于指定布局。

    | `option`取值                   | 效果                                         |
    | ------------------------------ | -------------------------------------------- |
    | `option='on'`或`option=True`   | 显示网格线                                   |
    | `option='off'`或`option=False` | 隐藏网格线                                   |
    | `option='equal'`               | x轴与y轴等比例缩放,图像长宽不变              |
    | `option='scaled'`              | x轴与y轴等比例缩放,图像进行裁切              |
    | `option='tight'`               | 使函数图像的四个边界紧贴图像的边             |
    | `option='auto'`                | 自动处理缩放,图像的四个边界与图像的边等间距  |
    | `option='image'`               | 1:1等比例尺绘制,图像进行裁切                 |
    | `option='square'`              | x轴与y轴等比例缩放,但强制$\Delta x=\Delta y$ |

### §4.1.6 图形标签

```python
plt.title('function image') # 设置标题
plt.xlabel('x')				# 设置x轴标签
plt.ylabel('f(x)')			# 设置y轴标签
plt.plot(x,np.sin(x),'-g',label='sin(x)')
plt.plot(x,np.cos(x),':b',label='cos(x)')
plt.legend()				# plt.show()不能创建图例
```

## §4.2 散点图

### §4.2.1 `plt.plot()`

给每个散点指定相同的形状参数，效率高。

| 图形标记            | 形状 | 图形标记            | 形状 |
| ------------------- | ---- | ------------------- | ---- |
| `plt.plot(x,y,'o')` | ●    | `plt.plot(x,y,'^')` | ▲    |
| `plt.plot(x,y,'.')` | •    | `plt.plot(x,y,'<')` | ◀    |
| `plt.plot(x,y,',')` | ·    | `plt.plot(x,y,'>')` | ▶    |
| `plt.plot(x,y,'x')` | ×    | `plt.plot(x,y,'s')` | ■    |
| `plt.plot(x,y,'+')` | +    | `plt.plot(x,y,'d')` | ♦    |
| `plt.plot(x,y,'v')` | ▼    |                     |      |

### §4.2.2 `plt.scatter()`

`plt.scatter(x,y,[s,c,marker,alpha])`能进一步控制每个散点的形状参数，但效率较低。

```python
rng = np.random.RandomState(0)
x = rng.randn(100)
y = rng.randn(100)
colorList = rng.rand(100)
sizeList = 1000 * rng.rand(100)
plt.scatter(x,y,c=colorList,s=sizeList,alpha=0.3,cmap='viridis')
plt.colorbar()
```

## §4.3 误差可视化

### §4.3.1 `plt.errorbar()`基本误差线

`plt.errorbar(x,y,yerr=0,[fmt,ecolor,elinewidth,capsize])`绘制基本误差线，`yerr`指定误差线的长度范围，`ecolor`指定误差线的颜色，`elinewidth`指定误差线的宽度，`capsize`为数型变量，指定误差线两侧横杠的宽度。

```python
# 模拟误差数据
x = np.linspace(0,10,50)
y = np.sin(x) + 0.1 * (np.random.randn(50)-1)

# 绘制基本误差线
plt.errorbar(x,y,yerr=0.1,fmt='.k',ecolor='lightgray',capsize=3)
```

### §4.3.2 连续误差

`plt.`
