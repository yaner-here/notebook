# Regex（正则表达式）

正则表达式（Regex,Regular Expression）是一种文本模式，用于匹配某个句法规则的字符串，实现检索、替换等功能。

# §0 基础知识

## §0.1 背景

在命令行中，我们有时会遇到一些“通配符”，例如`*Test.php`表示所有以`Test.php`结尾的文件：

```shell
$ ls
    File.php  FileTest.php  User.php  UserTest.php
$ rm ./*Test.php
$ ls
    File.php  User.php
```

许多Shell都提供了这种通配符，包含这些通配符的文件名构成了**文件名模式**（Filename Patterns）。但是处理其它文本的话，Shell的这些通配符就很难胜任了。我们需要一种**通用模式语言**（Generalized Pattern Language）处理各类文本，这种模式语言及其模式本身被称为**正则表达式**（Regular Expression，Regex）。

## §0.2 `grep`家族

我们之前使用Linux时已经知道，`grep`命令搭配管道符`|`可以实现按行筛选的操作。事实上Linux包含的远不止`grep`这一种，而是一整个家族：

```shell
$ ls -l /bin/* | grep "grep"
    lrwxrwxrwx 1 root /bin/bzegrep -> bzgrep
    lrwxrwxrwx 1 root /bin/bzfgrep -> bzgrep
    -rwxr-xr-x 1 root /bin/bzgrep
    -rwxr-xr-x 1 root /bin/egrep
    -rwxr-xr-x 1 root /bin/fgrep
    -rwxr-xr-x 1 root /bin/grep
    lrwxrwxrwx 1 root /bin/lzegrep -> /etc/alternatives/lzegrep
    lrwxrwxrwx 1 root /bin/lzfgrep -> /etc/alternatives/lzfgrep
    lrwxrwxrwx 1 root /bin/lzgrep -> /etc/alternatives/lzgrep
    -rwxr-xr-x 1 root /bin/pgrep
    lrwxrwxrwx 1 root /bin/pkill -> pgrep
    -rwxr-xr-x 1 root /bin/ptargrep
    -rwxr-xr-x 1 root /bin/rgrep
    lrwxrwxrwx 1 root /bin/xzegrep -> xzgrep
    lrwxrwxrwx 1 root /bin/xzfgrep -> xzgrep
    -rwxr-xr-x 1 root /bin/xzgrep
    -rwxr-xr-x 1 root /bin/zegrep
    -rwxr-xr-x 1 root /bin/zfgrep
    -rwxr-xr-x 1 root /bin/zgrep
    -rwxr-xr-x 1 root /bin/zipgrep
    -rwxr-xr-x 1 root /bin/zstdgrep
```

每个`grep`家族成员的使用方法大同小异，都类似于`grep [option...] pattern [filepath...]`：

```shell
yaner@DESKTOP-UVBN0SD:~/test$ grep --help
    用法: grep [选项]... 模式 [文件]...
    # ......
yaner@DESKTOP-UVBN0SD:~/test$ egrep --help
    用法: grep [选项]... 模式 [文件]...
    # ......
yaner@DESKTOP-UVBN0SD:~/test$ fgrep --help
    用法: grep [选项]... 模式 [文件]...
    # ......
```

其中`egrep`常用于检索文本文件：

```shell
$ cat info.csv 
    Name,Age,Country
    Alice,18,US
    Bob,19,CN
    Carol,20,EN
    David,19,DE
    Eve,20,CN
$ egrep "^(Alice|Bob)" info.csv 
    Alice,18,US
    Bob,19,CN
```

## §0.3 正则表达式的流派

各流派正则表达式支持情况：

| 元字符           |     `grep`     |   `egrep`   |      `Emacs`       |      `Tcl`       |   `Perl`    |   `.NET`    |   `Java`    |
| ---------------- | :------------: | :---------: | :----------------: | :--------------: | :---------: | :---------: | :---------: |
| `*`/`^`/`$`/`[]` |       √        |      √      |         √          |        √         |      √      |      √      |      √      |
| `?`/`+`/`|`      | `\?`/`\+`/`\|` | `?`/`+`/`|` |    `?`/`+`/`\|`    |   `?`/`+`/`|`    | `?`/`+`/`|` | `?`/`+`/`|` | `?`/`+`/`|` |
| `()`             |     `\(\)`     |    `()`     |       `\(\)`       |       `()`       |    `()`     |    `()`     |    `()`     |
| `(?:)`           |                |             |                    |                  |      √      |      √      |      √      |
| 单词分界符       |                |   `\<\>`    | `\<\>`或`\b`或`\B` | `\n`或`\M`或`\y` | `\b`或`\B`  | `\b`或`\B`  | `\b`或`\B`  |
| `\w`/`\W`        |                |      √      |         √          |        √         |      √      |      √      |      √      |
| 反向引用         |       √        |      √      |         √          |        √         |      √      |      √      |      √      |

## §0.4 正则表达式的处理方式

一般来说，编程语言对正则表达式的处理方式分为集成式处理、程序式处理、面向对象式处理。

### §0.4.1 集成式处理

集成式处理（Integrated Handling）指的是正则表达式直接内建于编程语言中，例如Perl。这种处理方式隐藏了正则表达式的预处理、返回值等细节，降低了程序的繁琐程度。

### §0.4.2 程序式处理

程序式处理（Procedural Handling）指的是正则表达式并不属于编程语言基本元素，只能先接受字符串，然后才能将其作为正则表达式对待，真正负责处理表达式的是编程语言内置的函数或运算符。

以Java为例，Java支持程序式处理：

```java
String input = "......";
if(Pattern.matches("Hello"),input){ // Pattern类提供的matches()方法
    // ......
}
if(input.matches("Hello")){ // String类提供的matches()方法
	// ......
}
```

微软的.NET平台也提供了相关API：

```.net
If Regex.IsMatch(Input,"Hello") Then
	// ......
End if
```

PHP原生内置`preg_match()`等函数：

```php
if(preg_match('/Hello/i',$input,$matches)){
	echo $matches[1];
}
```



### §0.4.3 面向对象式处理

面向对象式处理（Object-Oriented Handling）指的是正则表达式并不属于编程语言基本元素，只能先接受字符串，然后才能将其作为正则表达式对待，真正负责处理表达式的是编程语言内置的对象中的方法，并没有专门用于负责处理正则表达式的运算符。

以Java为例，Java也支持面向对象式处理：

```java
String input = "......";
Pattern regex = Pattern.compile("Hello",Pattern.CASE_INSENSITIVE);
Matcher matcher = regex.matcher(input);
if(matcher.find()){
	// ......
}
```

VB.NET也提供了正则表达式的API：

```vb
Imports System.Text.RegularExpressions
Dim input as string = "......"
Dim regex as Regex = New Regex("^Subject: (.+)",RegexOptions.IgnoreCase)
Dim match as Match = regex.Match(input);
If match.Success
    msgbox(match.Groups(1).Value)
End if
```

Python使用的是`re`库：

```python
import re
input = "......"
regex = re.compile("Hello")
match = regex.search(input)
if match:
    print(match.group(1))

```



# §1 元字符

正则表达式中的各个字符可以分为两类：一类是没有特殊含义的普通字符，称为**文字**（Literal）；另一类是具有特殊含义、代表某种规则的特殊字符，称为**元字符**（Metacharacter）。

## §1.1 `^`/`$` 行的起始与结束

在`egrep`中，`^`代表一行的开始，`$`代表一行的结束。本来正则表达式的匹配结果可能在行中，而`^`只寻找行首的内容，`$`只寻找行末的内容，这种以位置为依据，而非以文本为依据，限定匹配结果的过程称为**锚定**（Anchor）。

在Perl等编程语言中，`^`和`$`通常只表示整个文本的起点和终点，而不是每一行的行首与行尾。如果要匹配，可以使用[`m`修饰符](#§2.4 修饰符)。

## §1.2 `[]` 字符组

### §1.2.1 匹配若干字符之一

`[]`用于表示匹配字符组内的任何一个字符。例如`[Aa]pple`同时匹配`Apple`和`apple`，`<h[123456]>`匹配HTML的标题标签`<h1>`/`<h2>`/....../`<h6>`。

除此之外，`[]`内可以用连字符`-`表示一个范围，例如`[1-6]`与`[123456]`是完全一样的，`[abcdefg]`可以简化成`[a-g]`。甚至我们可以使用多个`-`构成多重范围，例如`[123456abcdefABC?_.!]`可以简写成`[1-6a-fA-C?_.!]`或`[?a-f_A-C.1-6!]`，这些范围的排列顺序没有影响。

> 注意：只有在字符组`[]`内部，**并且不被夹在左右另外两个字符的中间**，连字符`-`才被视为元字符，否则它只是一个文字而已，只能匹配一个普通的连字符`-`。例如要匹配`1-2`、`1.2`、`1/2`，我们不能写`1[.-/]2`，因为会被识别成“从`.`到`/`”的范围，可以写`1[-./]2`和`1[./-]2`。

### §1.2.2 排除所有字符

`[^]`用于匹配所有未在字符组中列出的字符（行首与行尾换行符不算字符），这一过程称为**排除**（Negate），例如`[^1-3]`匹配除了`1`/`2`/`3`之外的任何字符。

## §1.3 `.` 匹配任意字符

小数点`.`用于匹配任意字符和字符组，例如`a.c`可以匹配`abc`/`a c`/`a/c`/`a-c`等等。

> 注意：在字符组`[]`内部，小数点`.`被视为文字而非元字符。

## §1.4 `|` 匹配任意子表达式

`|`的含义是“或”，我们可以把这些子表达式拼成一个正则表达式，这些子表达式称为**多选分支**（Alternative）。例如`123|abc`既可以匹配`123`，也可以匹配`abc`；又例如`[Aa]pple`完全可以改写成`(A|a)pple`。

得益于`|`的引入，从这一节开始，我们要正式接触正则表达式化简这个概念。例如我们要匹配`first`和`1st`，注意到两者都以`st`结尾，我们就能压缩正则表达式的长度，从`first|1st`简化成`(fir|1)st`。

虽然`|`与`[]`都能起到“或”的效果，但是`|`的子表达式可以是一个完整的正则表达式，而`[]`只能匹配或排除一个指定的字符组。

## §1.5 忽略大小写

我们知道，正则表达式是严格区分大小写的，并不原生提供表示忽略大小写的元字符。然而许多支持正则表达式的程序却提供了忽略大小写的选项，例如`egrep`的命令行参数`-i`：

```shell
$ egrep --help
    模式选择与解释：
        # ......
          -i, --ignore-case         在模式和数据中忽略大小写
              --no-ignore-case      不要忽略大小写（默认）
        # ......
t$ cat info.csv
    Flag
    fl0g
    fLaG
    FLaG
    f1og
$ egrep -i "^flag" info.csv
    Flag
    fLaG
    FLaG
```

## §1.6 `\<`/`\>` 单词分界符

如果现在要匹配一个单词，我们最先想到的正则表达式可能是该单词本身。例如尝试匹配下列文本中的版本号`16.04`：

```shell
$ cat info.csv 
    In 2016.04.10, Ubuntu version 16.04 was released.
$ egrep -i "16.04" info.csv
    In 20__16.04__.10, Ubuntu version __16.04__ was released.
```

结果非常尴尬，我们把`2016.04.10`中的`16.04`也匹配上了。更关键的是，如果我们要匹配只有一个字母的单词`a`，可想而知我们误匹配的结果将会更多。这种问题的本质，是一个单词本身包含在另一个单词中。为解决这一问题，正则表达式引入了单词分界符这一概念，分别用`<\`和`\>`表示单词的开头与结尾，类似于用`^`和`$`表示行首与行末，都是代表一个概念，而不是代表一个存在的字符：

```shell
$ egrep -i "\<16.04\>" info.csv
	In 2016.04.10, Ubuntu version __16.04__ was released.
```

## §1.7 `?` 可选项元素

以`color`和`colour`为例，要同时匹配英式和美式英语，同时又不能匹配拼写错误的单词，我们可以使用`?`代表前面的字符可有可无，得到符合要求的正则表达式：`colou?r`;

```shell
$ cat info.csv 
    color
    colour
    coliur
$ egrep -i "colou?r" info.csv
    color
    colour
```

`u?`作为一个整体，对于任意字符串都是能够匹配成功的。因为无论字符`u`是否存在，`?`前面的字符都是可有可无的，符合这个可选项元素的要求。因此，决定整个正则表达式是否能匹配成功，关键在于`u?`之后的元素是否能匹配成功。这就会导致一个问题：开发者有时会忘记在`u?`的后面再加元素，从而跟`u?`完全没加一样。例如我们只想匹配`apple`的单数和复数，稍有不慎就会写出这种`apples?`的正则表达式：

```shell
$ cat info.csv 
    apple
    apples
    applet # n.小程序
$ egrep -i "apples?" info.csv # 错误用法
    apple
    apples
    applet # 竟然也匹配上了
$ egrep -i "apples?$" info.csv # 正确用法
    apple
    apples
```

## §1.8 `*`/`+` 重复出现

`+`表示该元字符前面紧邻的元素至少出现一次，`*`表示该元字符前面紧邻的元素出现任意多次（包括0次）。`+`、`*`、`?`这三种元字符都限制了前面紧邻元素的出现次数，因此统称为**量词**（Quantifier）。

## §1.9 `{}` 区间量词

大多数版本的`egrep`还支持区间量词这一特性。`{min,max}`用于表示该元字符前面紧邻的元素至少出现`min`次，最多出现`max`次；`{times}`表示恰好重复`times`次。

例如匹配一个任意位数的十进制小数，要求匹配`12.34`或`12`，过滤`01.12000`和`12.`：先分析整数部分，要么为单独的0，要么是不以0开头的数字，那么整数部分的正则表达式可以为`(0|[1-9]+[0-9]*)`；然后分析小数点部分，小数点可以不带，于是记为`\.?`小数部分；如果有小数点的话，那么末尾不能为0，其它位就可以为0，于是记为`[0-9]+[1-9]`；如果没有小数点的话，应该直接到行末。综合以上讨论结果，得到完整的正则表达式`^(0|[1-9]+[0-9]*)(\.[0-9]+[1-9])?$`：

```shell
$ cat info.csv 
    0
    0.0
    1
    1.0
    1.234
    1.2340
    1.23400
    1.234005
$ egrep -i "^(0|[1-9]+[0-9]*)(\.[0-9]+[1-9])?$" info.csv
    0
    1
    1.234
    1.234005
```

## §1.10 `\1` 反向引用

假如我们有以下文本，要求匹配所有的前后两个单词拼写相同的行：

```shell
$ cat info.csv
    apple  Apple # 两个空格
    banana    banana # 四个空格
    carrot carrot # 一个空格
```

许多正则表达式软件都支持“记忆”前面括号匹配的文本内容，第一个括号匹配的文本内容可以在后续正则表达式中记为`\1`，第二个括号匹配的文本内容可以在后续正则表达式中记为`\2`，以此类推。这种特性称为**反向引用**（Backreference）。因此我们就可以针对上述任务写出正则表达式`^\<.+\> +\1$`：

```shell
$ egrep "^(\<[a-zA-Z]+\>) +\1" info.csv
    banana    banana
    carrot carrot
```

## §1.11 特殊字符转义

如果我们想使用的文字恰好是当前语境下的元字符，可以在该字符前加上反斜杠`\`进行转义。如果原本的文字明明不需要转义，那么反斜杠将会被忽略。

> 注意；大多数编程语言都支持字符组内部的转义，但是大多说的`egrep`却不支持，它们会把`\`视为一个单独的文字。

# §2 Perl

Perl一种用于Linux系统的脚本语言，可以看作升级版的`shell`。下面是一个简单的示例：

```perl
$i = 1;
while($i <= 9){
    $iSquare = $i * $i;
    print "$i × $i = $iSquare\n";
    $i++;
}
```

```shell
$ perl test.pl
    1 × 1 = 1
    2 × 2 = 4
    3 × 3 = 9
    4 × 4 = 16
    5 × 5 = 25
    6 × 6 = 36
    7 × 7 = 49
    8 × 8 = 64
    9 × 9 = 81
```

Perl原生支持正则表达式，但是其语法与`egrep`有所区别。`=~`表示匹配正则表达式，正则表达式用`/.../`包起来，`m`告知Perl编译器这是一个正则表达式，由`=~`完成进行正则表达式匹配（Regular Expression Match）：

```perl
print "请输入数字：";
$number = <STDIN>;
if($number =~ m/^[0-9]+$/){
    print "输入合法";
}else{
    print "输入非法，只能输入纯数字";
}
```

```shell
$ perl test.pl
    请输入数字：123abc
    输入非法，只能输入纯数字
```

Perl等编程语言及支持正则表达式的其它工具，都在正则表达式的基础上额外引入了自己的语法和元字符。本章重点介绍这些额外的语法。

## §2.1 `(?:)` 非捕获型括号

我们知道，Perl会自动将正则表达式中由括号匹配到的文本赋给`$1`、`$2`等变量。但是有时我们撰写正则表达式时，经常手动加括号以提升可读性。更关键的是，这种Perl程序也不容易维护，因为正则表达式的一个括号变了，脚本中的所有`$1`等变量都要更改序号。有没有什么元字符，既能像`()`一样可以创建子表达式，又不会让匹配的文字被Perl捕获呢？这就是非捕获型括号`(?:...)`：

```perl
print("Input a string: ");
$string = <STDIN>;
chomp($string);
if($string =~ m/^([A-Za-z0-9]+) ([A-Za-z0-9]+)$/){
    print "()() First Parameter: $1\n";
}
if($string =~ m/^(?:[A-Za-z0-9]+) ([A-Za-z0-9]+)$/){
    print "(?:)() First Parameter: $1\n";
}
```

```shell
$ perl -w test.pl
    Input a string: first second
    ()() First Parameter:    first
    (?:)() First Parameter:  second
```

## §2.2 其它转义字符

Perl等编程语言额外提供了一些转义字符：

| 转义字符 | 作用                                               |
| -------- | -------------------------------------------------- |
| `\t`     | 制表符                                             |
| `\n`     | 换行符                                             |
| `\r`     | 回车符                                             |
| `\s`     | 任何空白字符（空格符、制表符、进纸符）             |
| `\S`     | 除空白字符（空格符、制表符、进纸符）之外的任何字符 |
| `\w`     | 等价于`[A-Za-z0-9]`                                |
| `\W`     | 除`[A-Za-z0-9]`之外的任何字符                      |
| `\d`     | 纯数字（`[0-9]`）                                  |
| `\D`     | 除数字之外的任何字符                               |

> 注意：在Perl中，`\b`表示单词分界符，在字符组`[]`中表示退格符。

## §2.4 修饰符

我们知道，原生的正则表达式本身没有忽略大小写的功能。为了忽略大小写，`egrep`提供了`-i`选项。类似的，Perl也提供了这一功能，但是不是基于命令行选项，而是在正则表达式的后面添加一些字符，这类字符称为**修饰符**（Modifier）。

```perl
if(string =~ m/[a-z]+/i){...}
```

上面使用的是`i`修饰符。虽然`/`并不属于修饰符的一部分，但是为了方便，实际中经常记为`/i`。

修饰符有很多种：

| 修饰符 | 英文全称                       | 作用                                    |
| ------ | ------------------------------ | --------------------------------------- |
| `i`    | Case-insenitive                | 忽略大小写                              |
| `g`    | Global Match                   | 全局匹配                                |
| `x`    | Free-form Expression           | 宽松排列（忽略大多数空白字符和`#`注释） |
| `m`    | Multiline/Enhanced Line Anchor | 多行/增强的行锚点                       |

```perl
# 宽松排列
$email = "demo\@example.com";
$email =~ s{
    \b
    # 这是一个注释
    (
        \w+
        \@
        [\w.]+
    )
    \b
}{
    <a href="mailto:$1">$1</a>
}gix;
print "$email";
	# $ perl test.pl
    	<a href="mailto:demo@example.com">demo@example.com</a>
```



## §2.5 `/` 替换

到目前为止，我们学习的正则表达式只有一个功能——查找。而且这个正则表达式在Perl中还得用`/.../`包起来，前面加上`m`表示匹配。Perl提供了替换功能，通过多个`/`组成`/a/b/`结构，并且在前面加上`s`表示查找和替换（Serach and Replace），将第一个匹配`a`表达式的文字替换为`b`。如果要全部替换，应该在末尾加上修饰符`g`：

```perl
print("Input a string: ");
$string = <STDIN>;
chomp($string);
$string =~ s/\bAlice\b/Bob/;
print "$string";
```

```shell
$ perl -w test.pl
    Input a string: Hello, Mike!
    Hello, Mike!
$ perl -w test.pl
    Input a string: Hello, Alice!
    Hello, Bob!
```

> 注意：Perl程序不仅可以写在文件中，也可以作为命令行参数传入：
>
> ```shell
> $ cat info.csv 
>     Hello, Alice!
>     This is Alice.
>     Where is Alice?
> $ perl -p -i -e 's/Alice/Bob/g' info.csv 
> $ cat info.csv 
>     Hello, Bob!
>     This is Bob.
>     Where is Bob?
> ```
>
> 其中`-p`表示逐行检查，`-i`表示将替换后的结果写入原文件，`-e`表示后面传入的是正则表达式。

## §2.6 `(?=)`/`(?<=)`/`(?!)`/`(?<!)` 环视

如果要给一个大数加上数字分隔符，例如把`12345678`变成`12,345,678`，怎么用正则表达式实现呢？我们已经知道了数字分隔符的用法：从最后的个位数开始向前数，每经过三个数字就在左面添加一个逗号。要实现这个功能，我们需要用到**环视**（Lookahead）这一特性。

环视是正则表达式中的一种只匹配位置，不匹配内容的元素。之前介绍的`\b`匹配单词的起始处、`^`和`$`匹配行首与行尾，也是只匹配位置，但是环视的通用性更强，分为四种种情形：

- 肯定顺序环视（Positive Lookahead）：`(?=...)`按照当前位置右边的字符作为是否匹配的依据
- 肯定逆序环视（Positive Lookbehind）：`(?<=...)`按照当前位置左边的字符作为是否匹配的依据
- 否定顺序环视：（Negative Lookahead）`(?!...)`按照当前位置右边的字符作为是否不匹配的依据
- 否定逆序环视：（Negative Lookbehind）`(?<!...)`按照当前位置左边的字符作为是否不匹配的依据

结合环视，我们就能用另一种方式解决从`Alices`到`Alice's`：

```perl
$string = "Alices";
$string =~ s/\bAlices\b/Alice's/; # 简单的替换
print "$string";

$string = "Alices";
$string =~ s/Alice(?=s\b)/Alice'/; # 使用环视进行替换
print "$string";
```

回到数字分隔符的问题，插入的位置必须符合两个要求：左边必须至少有一个数字，右边的数字个数必须是3的倍数（不是右侧存在`(\d\d\d)+`，而是右侧到数字结束位置能匹配`(\d\d\d)+\b`），分别对应着`(?<=\d)`和`(?=(\d\d\d)+\b)`：

```perl
$number = <STDIN>;
$number =~ s/(?<=\d)(?=(\d\d\d)+\b)/,/g;
print "$number";
```

```shell
$ perl -w test.pl
    Input a number: 1234567
    1,234,567
$ perl -w test.pl
    Input a number: 123456789
    123,456,789
```

如果禁用所用的环视元字符，那么思考这个正则表达式：`s/(\d)((\d\d\d)+\b)/$1,$2/g`，能不能实现相同的效果呢？答案是不能。我们知道，修饰符`g`表示全局，是用迭代的方式实现的。以`123456789`为例，首先匹配到了`3`和`456789`，两者之间加上了一个逗号。问题来了，我们知道`456789`已经曾经被匹配过了，于是根据迭代的原理，下一次迭代开始的位置一定是上一次迭代结束的位置，那么`6`和`789`就永远不可能被匹配了，因此得到的结果只能有一个逗号：`123,456789`。而使用环视的意义就在于此：只匹配位置，永远不匹配文字，这样就能不“使用”文字，让这些文字能够参与到下一次迭代中。

难道真的没有办法了吗？既然一次替换解决不了，那我们就多次地替换，直到不能替换为止：

```perl
while($text =~ s/(\d)((\d\d\d)+\b)/$1,$2/g){
	;
}
```

## §2.7 其它分隔符

到目前为止，我们在Perl中见过的所有用于替换的正则表达式，都是形如`s/regex/replacement/modifier`的结构。如果`regex`或`replacement`中出现大量的`/`，那么我们就需要对其进行转义，使用大量的`\/`。这无疑是非常麻烦的——凭什么就因为区区两个分隔符`/`，就需要其它所有文字`/`让路呢？如果能把分隔符换成其它字符，那么我们理论上就没有再对文字`/`转义的必要了。

Perl支持的分隔符有`/`、`{}`和`!`：

```perl
$string = "Hello, Alice";
$string =~ s/Alice/Bob    Look at this {}!/g; # 分隔符为/
print "$string\n";

$string = "Hello, Alice";
$string =~ s{Alice}{Bob    Look at this //!}g; # 分隔符为{}
print "$string\n";

$string = "Hello, Alice";
$string =~ s!Alice!Bob    Look at this {}\!!g; # 分隔符为!
print "$string\n";
```

```shell
$ perl -w test.pl
    Hello, Bob    Look at this {}!
    Hello, Bob    Look at this //!
    Hello, Bob    Look at this {}!
```

## §2.8 正则表达式库

对于一些重复使用的正则表达式，我们可以将其保存起来，并插入到其它正则表达式中：

```perl
$phoneRegex = qr/\b1\d{10}\b/;
$message = "This is my phone number: 12345678901";

$message =~ s/.*$phoneRegex/98765432109/ig;
print "$message";
```

```shell
$ perl -w test.pl
	98765432109
```

要保存正则表达式，我们需要使用`qr`操作符，让Perl生成一个Regex类型的对象并作为变量保存。

> 注意：在Perl中，正常情况下`$`也可以表示行尾，又可以表示变量符，不需要转义。然而在字符组中，它只能用于表示变量符，而且使用时必须转义。

# §3 Java

Java使用`java.util.regex`包处理正则表达式：

```java
import java.util.regex.*;

class Demo {
    public static void main(String[] args) {
        String input = "eMail: test@example.com";
        Pattern regex = Pattern.compile("^Email: (.+)$",Pattern.CASE_INSENSITIVE);
        Matcher matcher = regex.matcher(input);
        if(matcher.find()){
            System.out.println(matcher.group(1)); // 提取邮箱地址
        }
    }
}
```

## §3.1 查找与替换





```java
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Pattern;

class Demo {
    public static void main(String[] args) {
        Pattern regex1 = Pattern.compile("\\b([a-z]+)((?:\\s|\\<[^>]+\\>)+)(\\1\\b)", Pattern.CASE_INSENSITIVE);
        Pattern regex2 = Pattern.compile("^(?:[^\\e]*\\n)+", Pattern.MULTILINE);
        Pattern regex3 = Pattern.compile("^([^\\n]+)", Pattern.MULTILINE);
        String replace1 = "\033[7m$1\033[m$2\033[7m$3\033[m";
        for (int i = 0; i < args.length; i++) {
            try{
                BufferedReader in = new BufferedReader(new FileReader(args[i]));
                String text;
                while((text = getPara(in)) != null){
                    text = regex1.matcher(text).replaceAll(replace1);
                    text = regex2.matcher(text).replaceAll("");
                    text = regex3.matcher(text).replaceAll(args[i] + ": $1");
                    System.out.print(text);
                }
            }catch(IOException e){
                System.err.println("Can't read [" + args[i] + "]" + e.getMessage());
            }
        }
    }

    public static String getPara(BufferedReader in) throws IOException {
        StringBuffer buffer = new StringBuffer();
        String line;
        while ((line = in.readLine()) != null && (buffer.length() == 0 || line.length() != 0)) {
            buffer.append(line + '\n');
        }
        return buffer.length() == 0 ? null : buffer.toString();
    }
}
```

```shell
$ cat text.txt 
    This is a weird weird document.
    Because it contains contains too much much repetive words.
$ java Demo.java text.txt
    text.txt: This is a [weird weird] document.
    text.txt: Because it [contains contains] too [much much] repetive words.
```

# §4 `.NET`

# §5 `PHP`

PHP是一门容易入门的Web编程语言。PHP不仅能支持正则表达式，而且提供了三套独立的正则引擎：`preg`、`ereg`、`mb_ereg`。这里我们重点研究`preg`。本节将默认读者已经掌握PHP的基本语法。

## §5.1 支持的流派

`preg`引擎支持的正则表达式流派如下表所示：

| 字符缩略表示法 | 正则表达式元素                                               |
| -------------- | ------------------------------------------------------------ |
|                | `\a`、`[\b]`、`\e`、`\f`、`\n`、`\r`、`\t`、`\0oct`、`\hhex`、`\x{hex}`、`\cchar`<br />（只有在字符组内部，`\b`才表示退格符，其余均为单词分界符） |

| 字符组及相关结构  | 正则表达式元素                                |
| ----------------- | --------------------------------------------- |
| 字符组            | `[...]`、`[^...]`                             |
| 通配符            | `.`                                           |
| Unicode混合序列   | `\X`（只在修饰符`u`中有效）                   |
| 字符组缩略表示法  | `\w`、`\d`、`\s`、`\W`、`\D`、`\S`            |
| Unicode属性与区块 | `\p{Prop}`、`\P{Prop}`（只在修饰符`u`中有效） |
| 单个字节          | `\C`                                          |

| 描点与其他零长度断言 | 正则表达式元素                               |
| -------------------- | -------------------------------------------- |
| 行首/字符串起始位置  | `^`、`\A`                                    |
| 行末/字符串结束位置  | `$`、`\z`、`\Z`                              |
| 当前匹配的起始位置   | `\G`                                         |
| 单词分界符           | `\b`、`\B`                                   |
| 环视                 | `(?=...)`、`(?!...)`、`(?<=...)`、`(?<!...)` |

| 注释与模式修饰符 | 正则表达式元素                                 |
| ---------------- | ---------------------------------------------- |
| 模式修饰符       | `(?mods-mods)`（`x`、`s`、`m`、`i`、`X`、`U`） |
| 模式修饰范围     | `(?mods-mods:...)`                             |
| 注释             | `(?#...)`（只在修饰符`x`中有效）               |

| 分组及捕获           | 正则表达式元素                              |
| -------------------- | ------------------------------------------- |
| 捕获型括号与反向引用 | `(...)`、`\1`、`\2`                         |
| 命名捕获括号         | `(?P<name>)`、`(?P=name)`                   |
| 非捕获型括号         | `(?:...)`                                   |
| 固化分组             | `(?>...)`                                   |
| 多选结构             | `|`                                         |
| 递归                 | `(?R)`、`(?num)`、`(?P>name)`               |
| 条件判断             | `(?if then|else)`                           |
| 匹配优先量词         | `*`、`+`、`?`、`{n}`、`{m,n}`、`{n,}`       |
| 忽略匹配优先量词     | `*?`、`+?`、`??`、`{n}?`、`{m,n}?`、`{n,}?` |
| 占有优先量词         | `*+`、`++`、`?+`、`{n}+`、`{m,n}+`、`{n,}+` |
| 文字范围             | `\Q...\E`（只能用在字符组内部）             |



## §5.2 `preg`引擎与函数接口

`preg`的全称为Perl正则表达式（Perl Regular Expressions），是一种程序式正则引擎。其作者Andrei Zmievski仿照Perl中的正则表达式引擎，在PHP中完整复刻了一套名为PCRE（Perl Compatible Regular Expressions）的函数接口。该引擎提供了以下11个基层函数，统称为PCRE函数：

| PCRE函数                                                     | 作用                                                         | `$flag`形参取值及作用                                        |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `preg_match(string $pattern,string $subject,array &$matches=null,int $flags=0,int $offset=0):0|1|false` | 根据给定的正则表达式`$pattern`，从字符串`$subject`的第`$offset`位开始，统计一次匹配次数并返回`int`（0或1）并将匹配结果全部写入`&$matches`数组中。如果发生错误则返回`false`。 | `PREG_OFFSET_CAPTURE`：返回值数组中的元素不再是字符串，而是一个个新数组，每个新数组都包含字符串和**该字符串的第一个字符在原字符串中的位置**（从0开始数）<br />`PREG_UNMATCHED_AS_NULL`：如果其中一个结果为空字符串，那么在返回时将其替换为`null` |
| `preg_match_all(string $pattern,string $subject,array &$matches=null,int $flags=0,int $offset=0):int|false` | 根据给定的正则表达式`$pattern`，从字符串`$subject`的第`$offset`位开始，统计所有匹配次数并返回`int`并将匹配结果全部写入`&$matches`数组中。如果发生错误则返回`false`。 | `PREG_PATTERN_ORDER`：对匹配结果进行排序，靠前的元素尽可能满足更多的多选结构（`?+*(|)`等）<br />`PREG_SET_ORDER`：对匹配结果进行排序，正则表达式从字符串第一个字符开始向后匹配，最先匹配到的子字符串靠前<br />其余同`preg_match()`。 |
| `preg_filter(mixed $pattern,mixed $replacement,mixed $subject,int $limit=-1,int &$count=null):string|array|null` | 该函数与`preg_replace()`作用一样，但是返回的数组中只包含匹配成功的字符串 |                                                              |
| `preg_grep(string $pattern,array<string> $array,int $flags=0):array|false` | 根据给定的正则表达式`$pattern`，从`$array`中依次选取字符串进行匹配，将所有匹配结果以数组的形式返回。如果发生错误则返回`false`。 | `PREG_GREP_INVERT`：返回正则表达式**不**匹配的所有结果。     |
| `preg_last_error_msg():string`                               | 返回上一次调用PREG函数发生错误时的报错信息                   |                                                              |
| `preg_last_error():int`                                      | 返回上一次调用PREG函数发生错误时的错误代码                   | 返回值与以下[预定义常量](https://www.php.net/manual/zh/pcre.constants.php)对应：<br />`PREG_NO_ERROR`<br />`PREG_INTERNAL_ERROR`<br />`PREG_BACKTRACK_LIMIT_ERROR`<br />`PREG_RECURSION_LIMIT_ERROR`<br />`PREG_BAD_UTF8_ERROR`<br />`PREG_BAD_UTF8_OFFSET_ERROR`<br />`PREG_JIT_STACKLIMIT_ERROR` |
| `preg_quote($string $str,string $delimiter=null):string`     | 对包含特殊字符（`.\+*?[]^$(){}=!<>|:-#`以及`$delimiter`）的原生正则表达式`$str`进行转义并返回 |                                                              |
| `preg_replace_callback(string|array $pattern,callable $callback,string|array $subject,int $limit=-1,int &$count=null,int $flags=0):string|array|null` | 该函数等价于：调用`preg_replace()`函数后，将其返回值传入`$callback`中，将其返回值作为最终的结果输出 | `PREG_OFFSET_CAPTURE`：<br />`PREG_UNMATCHED_AS_NULL`：      |
| `preg_replace_callback_array(array $pattern,string|array $subject,int $limit=-1,int &$count=null,int $flags=0):string|array|null` | 该函数等价于`preg_replace_callback()`但是`$pattern`不再是正则表达式数组，而是以正则表达式为键，以`callback`为值的键值对构成的数组 | `PREG_OFFSET_CAPTURE`：<br />`PREG_UNMATCHED_AS_NULL`：      |
| `preg_replace(string|array $pattern,string|array $replacement,string|array $subject,int $limit=-1,int &$count=null):string|array|null` | 根据传入的正则表达式`$pattern`，在字符串`$subject`中进行匹配，将匹配项用`$replacement`进行替换，至多替换`$limit`次，并将真正的替换次数写入到`&$count`。无论是否发生过替换，都返回所有的`string`或`array<string>`。 |                                                              |
| `preg_split(string $pattern,string $subject,int $limit=-1,int $flags=0):array` | 通过一个正则表达式分隔字符串，并以数组的形式返回             | `PREG_SPLIT_NO_EMPTY`：返回值`array`内删除仅含空白字符的项<br />`PREG_SPLIT_DELIM_CAPTURE`：`array`内也包含反向引用的值<br />`PREG_SPLIT_OFFSET_CAPTURE`：返回值数组中的元素不再是字符串，而是一个个新数组，每个新数组都包含字符串和**该字符串的第一个字符在原字符串中的位置**（从0开始数） |

下面是一个简单的的Demo：

```php
$input = "123 456-7890";
if(preg_match_all('/\d+/',$input,$matches)){
    echo "Splited Numbers:\n";
    foreach($matches[0] as $key => $match){
        echo "$key. $match\n";
    }
}
```

### §5.2.1 `$pattern`形参

所有PREG函数的第一个参数都是`$pattern`。

> 注意：PHP的字符串有单引号和双引号两种形式。一般情况下，正则表达式可能会包含大量的反斜杠`\`。各中引号类型的行为如下所示所以为了避免转义，我们通常使用单引号字符串。
>
> | 字符串两侧引号类型 |                       `\`                       | `\\` | `\'` | `\"` | `\1011` | `\n` | `\w` |
> | :----------------: | :---------------------------------------------: | :--: | :--: | :--: | :-----: | :--: | ---- |
> |    单引号字符串    | 将右单引号转义<br />`Unexpected string content` | `\`  | `'`  | `\'` | `\1011` | `⏎`  | `\w` |
> |    双引号字符串    |  将右双引号转义<br />`Unexpected end of line`   | `\`  | `\'` | `"`  |  `A1`   | `\n` | `\w` |
>
> 单引号字符串仅要求对极少的特殊字符进行转义。例如`'\n'`就不会被转义成换行符。
>
> 假设我们要在PHP中表示`\n`这两个字符。由于这是换行符的转义形式，所以我们并不能直接使用`"\n"`，但是可以直接使用`'\n'`。如果用双引号表示的话，我们必须对其进行转义：`"\\n"`。当然，我们也可以对`'\n'`的反斜杠进行转义：`'\\n'`。`'\n'`与`'\\n'`的效果完全一致。
>
> 但是如果我们要表示`\w`这两个字符呢？首先`\w`并不是什么字符的转义形式，所以双引号会将`"\w"`真的看作两个独立的字符，这与`"\\w"`的效果完全一致。此时单双引号用法完全相同。
>
> 分析以上两个例子，我们发现，双引号的用法虽然更灵活，但是我们不希望正则表达式`^\w\w$`在PHP中的表示方式出现`"\\w\w"`这两种用法，否则我们还要额外确认这是不是转义字符。为了减少字符串长度，我们肯定是希望用字符最少的`"\w"`表示法。既然我们确定了只使用`"\w"`，还不如一开始就选用单引号表示法，起码它只对极小部分的特殊字符进行转义，在正常的使用中我们完全不用担心`\n`能否转义，而是直接无脑用单个反斜杠`'\n'`就可以了。
>
> 综上所述，在PHP中编写正则表达式的字符串，**最好用单引号表示法**。

编写正则表达式和正则表达式字符串之间，唯一的区别就是隔了一层转义。为避免出错，我们应该先按照需求编写正则表达式，在考虑其转义前的字符串。例如要求匹配`C:\`、`E:\`等盘符的根目录，考虑到正则表达式中的`\`需要转义，我们设计的正则表达式为`/^[A-Z]:\\$/`。接着考虑其转义前的字符串，还是因为每个`\`都需要转义，所以我们最终的正则表达式字符串为`$regex = '/^[A-Z]:\\\\/'`。

## §5.3 分隔符

`preg`正则引擎要求正则表达式字符串的两端必须有分隔符。两者分隔符可以选择`{}`、`()`、`<>`、`[]`、`//`。

从中任选一组分隔符，如果正则表达式中存在与分隔符冲突的特殊字符，那么正则表达式中的特殊字符必须经过转义。

> 注意：分割符本质上并不参与实际的正则表达式，这一点我们在Perl中体会过。例如`{}`，当这对字符在首尾作为分隔符时，没有人会认为这是限制重复次数的量词；例如`()`，没有人会认为这是捕获型括号。

## §5.4 模式修饰符

PHP不仅支持正则表达式的部分模式修饰符，而且自己还引入了独占的模式修饰符：

| 修饰符 | 作用                              |
| ------ | --------------------------------- |
| `i`    | 忽略大小写                        |
| `m`    | 增强的行锚点模式                  |
| `s`    | 点号通配模式                      |
| `x`    | 宽松排列和注释模式                |
| `u`    | 用UTF-8编码读取正则表达式字符串   |
| `X`    | 启用PCRE的额外功能（Extra Stuff） |
| `e`    |                                   |
| `S`    |                                   |
| `U`    |                                   |
| `A`    |                                   |
| `D`    |                                   |



# §6 高性能调优

虽然条条大路通罗马，但是我们还是希望在一众可以实现相同功能的正则表达式中，选择性能最强的那一个。本章介绍如何写出高性能的正则表达式。

一个好的正则表达式应在以下几种方面之间取得平衡：

- 只匹配期望的文本，排除其它文本
- 易于理解和维护
- 如果使用NFA引擎，必须保证不匹配时快速报错

## §6.1 匹配IPv4地址

IPv4地址由四个000-255的数字构成，合起来成为一个点分十进制数字。这里最难缠的就是怎么0-255的数字，直接我们用的都是分类讨论的思路，所以我们可能会写出这种庞大的正则表达式：`(\d|[1-9]\d|1\d\d|2([0-4]\d|5[0-5]))`。这还只是一个0-255的正则表达式，如果要匹配完整的IPv4地址就要把这玩意儿复制四遍。一方面，这么庞大的式子包含了重复的单元，并且难以维护；另一方面，受制于NFA引擎的原理，如此多的多选分支结构会严重影响执行效率。

|   选择结构的分支    | 分支匹配的数字范围 |
| :-----------------: | :----------------: |
|        `\d`         |        0-9         |
|      `[1-9]\d`      |       10-99        |
|       `1\d\d`       |      100-199       |
| `2([0-4]\d|5[0-5])` |      200-255       |

我们肯定要对这个正则表达式进行优化，核心思路是“关注字符串中什么位置可以出现哪种字符”。这时我们就要把字符串看成一个真正的数字，而不仅仅是字符序列，现在没有`0`这一说，只有`000`这种说法。先看百位数，如果是`0`或`1`，那么后面的十位数和个位数不受影响；如果是`2`，那么再看十位数，以此类推，我们得到的表达式为`([01]\d\d|2([0-4]\d|5[0-5]))`。

|   选择结构的分支    | 分支匹配的数字范围 |
| :-----------------: | :----------------: |
|     `[01]\d\d`      |      000-199       |
| `2([0-4]\d5|[0-5])` |      200-255       |

然而这样我们同时排除了`0`和`00`，于是我们还要进行修正。如果给定的数字最多只有十位数，那么它肯定在`[0,255]`这个范围内。为了不引入`\d`和`\d\d`这两个分支，我们可以考虑在现有分支上做点改动，将部分元素用`?`修饰，例如`[01]\d\d`改成`[01]?\d?\d`，以达到百位数或十位数可加可不加的效果。虽然这样我们引入了`000`这种字符串，但是对于正常的字符串没有影响。为了这飞跃性的性能提升，牺牲一点数据的格式要求是非常值得的：

- 当只有`0`或`1`时，`[01]?`匹配的个位数会交还给最后的`\d`，匹配成功
- 当只有`2-9`时，`\d?`匹配的个位数会交还给最后的`\d`，匹配成功
- 当只有`10-29`时，`[01]`匹配十位数，`\d?`匹配的个位数会交还给最后的`\d`，匹配成功
- 当只有`30-99`时，`\d?`匹配十位数，`\d`匹配个位数，匹配成功

|   选择结构的分支    | 分支匹配的数字范围 |
| :-----------------: | :----------------: |
|    `[01]?\d?\d`     |   0-199、000-199   |
| `2([0-4]\d|5[0-5])` |      200-255       |

现在我们的优化版本是`([01]?\d?\d|2([0-4]\d|5[0-5]))`，性能已经很强了。那么问题来了：它还能更强吗？可以！下面的这个奇技淫巧非常的巧妙，就是让`?`出现的位置靠后，让NFA引擎能及时地判断异常字符串并报错。这里我们把`[01]?\d?\d`改成`[01]?\d\d?`，就能更加提前地判断出`0a5`不符合要求：

|   选择结构的分支    | 分支匹配的数字范围 |
| :-----------------: | :----------------: |
|    `[01]?\d\d?`     |   0-199、000-199   |
| `2([0-4]\d|5[0-5])` |      200-255       |

至此，我们终于得到了性能最强的`0-255`正则表达式`([01]?\d\d?|2([0-4]\d|5[0-5]))`。将其复制四次，就能得到IPv4的正则表达式：

```
\<([01]?\d\d?|2([0-4]\d|5[0-5]))\.([01]?\d\d?|2([0-4]\d|5[0-5]))\.([01]?\d\d?|2([0-4]\d|5[0-5]))\.([01]?\d\d?|2([0-4]\d|5[0-5]))\>
```

## §6.2 提取路径中的文件名

例如给定一个路径`/usr/bin/gcc`，要求输出`gcc`。

一种思路是忽略掉前面的路经名，只关注最后的文件名，对应的正则表达式为`([^\/]*)$`：

```perl
$string = "/usr/bin/gcc";
if($string =~ m/([^\/]*)$/){
    print "$1";
}
```

```shell
$ perl -w test.pl
	gcc
```

这种方法涉及到大量的回溯操作，因此效率非常低，时间复杂度为$O(n^2)$。另一种思路是使用回溯/交还的特性，先用`.*`匹配一整行的所有字符，然后再用`/`强迫`.*`交还至最后一个`/`，然后再用`.*`匹配剩下的文件名。对应的正则表达式为`.*\/(.*)`，时间复杂度为$O(n)$：

```perl
$string = "/usr/bin/gcc";
if($string =~ m/.*\/(.*)/){
    print "$1";
}
```

```shell
$ perl -w test.pl
	gcc
```

另一种思路是直接替换：

| 编程语言（Linux环境） | 代码                                       |
| --------------------- | ------------------------------------------ |
| Perl                  | `$path =~ s{^.*/}{};`                      |
| PHP                   | `$path = preg_replace('{/^.*/}','',$path)` |
| `java.util.regex`     | `path = path.replaceFirst("^.*/","")`      |
| VB.NET                | `path = Regex.Replace(path,"^.*/","")`     |

| 编程语言（Windows环境） | 代码                                         |
| ----------------------- | -------------------------------------------- |
| Perl                    | `$path =~ s{^.*\\\}{};`                      |
| PHP                     | `$path = preg_replace('{/^.*\\\}','',$path)` |
| `java.util.regex`       | `path = path.replaceFirst("^.*\\\\","")`     |
| VB.NET                  | `path = Regex.Replace(path,"^.*\\","")`      |

## §6.3 匹配无嵌套对称的括号

在数据结构与算法中，我们学过利用栈来实现括号配对检测。这里我们简化一下问题只考虑`()`小括号这一种括号，并且匹配第一个括号中的内容，例如`(a+(b)+c)+(d)`只匹配`a+(b)+c`。

我们已经知道`\(.*\)`是行不通的，这是因为它匹配的`(`和`)`不一定属于同一个逻辑上的括号对，最终的匹配结果为`a+(b)+c)+(d`，所以我们不能用`.*`。那么用`[^)]*`行不行呢？也不行，因为它见到`)`就急着结束匹配，得到的结果是`a+(b`。

不幸的是，正则表达式本身并不图灵完备，因此无法灵活地处理任意深度的嵌套括号。然而，现代的编程语言在正则表达式的基础上引入了一些新功能，Perl、.NET、PHP都提供了对应的解决方案。这里我们以Perl为例——Perl提供了`string x count`运算符，可以把`string`重复`count`次：

```perl
$regex = '\('.'(?:[^()]|\('x$depth.'[^()]*'.'\))*'x$depth.'\)';
```

## §6.4 匹配有嵌套不对称的括号

例如给出以下字符串`<input placeholder="> Input here">Username</input>`，要求提取出`Username`。

## §6.5 去除文本首尾的空白字符

我们已经学过了使用替换来去除文本首尾的空白字符——首先匹配前面的空白字符，其次匹配后面的空白字符，对应的正则表达式为`s{(^\s*|\s*$)}{}g`：

```perl
$string = " Hello World  ";
$string =~ s{(^\s*|\s*$)}{}g;
print "$string";
```

```shell
$ perl -w test.pl
    Hello World
```

我们来对它进行一下性能分析。首先NFA引擎用的是顺序多选结构，我们使用的是优先匹配量词，所以开头的一个空格匹配速度很快。但是之后就有问题了，对于字符串中的`H`，首先`\s*`未能匹配，于是默认匹配数量为0，然后发现下一个`$`也无法匹配，于是强迫`\s*`交出一个`$`，发现也不行，所以`H`匹配失败。这之后的每个字符都要经历一遍类似的流程。因此最好情况下时间复杂度是$O(2n)$。而最坏情况是中间隔着一堆空白字符，例如`a        b`，这种最坏情况下时间复杂度飙升至$O(n^2)$。

那么如果我们不使用多选结构，而是直接使用忽略优先匹配量词，同时匹配两侧的空白字符，能不能提升性能呢？可以。使用`s{\s*(.*?)\s*$}{$1}g`，就可以保证在$O(2n)$的时间内完成匹配：

```perl
$string = " Hello World  ";
$string =~ s{\s*(.*?)\s*$}{$1}g;
print "$string";
```

```shell
$ perl -w test.pl
    Hello World
```

当然我们也可用环视代替忽略优先匹配量词，时间复杂度同样是$O(2n)$：

```perl
$string = " Hello World  ";
$string =~ s{^\s((?:.*\S)?)\s*$}{$1}g;
print "$string";
```

```shell
$ perl -w test.pl
    Hello World
```

优化到这里，我们发现制约效率的瓶颈在于一次次的回溯。虽然我们已经把单次`*`回溯的时间复杂度从$O(n)$降到了$O(1)$，但是仍然抑制不了`*`被其它量词要求交还字符。要造出效率最高的正则表达式，我们就不能只用一个表达式了，可以将任务进行拆解，分别设计两个正则表达式。这种方法的优势在于删除开头空白字符时，时间复杂度可以压到$O(1)$，从而让整个流程时间复杂度压到原来的一半，也就是$O(n)$：

```perl
$string = " Hello World  ";
$string =~ s{^\s*}{}g;
$string =~ s{\s*$}{}g;
print "$string";
```

```shell
$ perl -w test.pl
    Hello World
```

## §6.6 按文件头提取文本

假设邮政编码长度为6，其中某地区的邮政编码前两位为`00`。现在有一批各地区的邮政编码，但是每两个相邻的邮政编码之间没有任何分隔符。例如`123456006666654321`可以拆成`123456`、`006666`、`654321`，我们要做的就是匹配该地区的邮政编码`006666`。

乍一看，我们非常容易想到`00\d\d\d\d`。但是这个正则表达式有一个问题，就是如果邮政编码的后四位出现`00`组合，那么正则表达式就会认为这个`00`组合是新的邮政编码的开头：

```perl
$string = "120034123456007800";
if($string =~ m/(00\d\d\d\d)/g){
    print "First Code: $1\n";
}
```

```shell
$ perl -w test.pl
    First Code: 003412
```

一种思路是使用非捕获型括号，对应的正则表达式为`(?:[^4]\d{5}|\d[^4]\d{4})*`：

```

```

？？？？？？TODO：？？？？？？？

# §A 例题

## §A.1 是否为时刻

要求匹配形如`20:12:59`、`00:00:00`的时长字符串。

- 小时数：必须是一个0到24的整数
  - 当十位数为0时，个位数可以是任意数
  - 当十位数为1时，个位数可以是任意数
  - 当十位数为2时，个位数只能从0到3
- 分钟数：必须是一个0到59的整数，容易发现十位数从0到5，个位数不受限制
- 秒种数：同分钟数

得到的正则表达式为`^([01][0-9]|[2][0-3]):[0-5][0-9]:[0-5][0-9]$`。

```shell
$ cat info.csv 
    12:30:59
    0:0:0
    25:00:00
    00:61:00
    00:00:61
$ egrep "^([01][0-9]|[2][0-3]):[0-5][0-9]:[0-5][0-9]$" info.csv 
    12:30:59
```

## §A.2 自动中美汇率转换

已知中美汇率为$\frac{1}{6.75}$.要求根据输入的货币类型与数字，自动转换成另一种货币并输出数字（保留两位小数），例如输入`USD 10.5`，输出`CNY 70.89`。

```perl
print("中美汇率计算器\n请输入要转换的货币与面值:");
$string = <STDIN>;
chomp($string); # 删除末尾换行符
if($string =~ m/^(USD|CNY) ([0-9]+(\.[0-9]+)?)$/){
    $usd2cnyRatio = 6.75;
    $type = $1;
    $number = $2;
    if($type eq "USD"){
        $newType = "CNY";
        $newNumber = $number / $usd2cnyRatio;
    }elsif($type eq "CNY"){
        $newType = "USD";
        $newNumber = $number * $usd2cnyRatio;
    }
    printf "$string -> $newType %.2f",$newNumber;
}else{
    print "输入不合法！";
    exit;
}
```

```shell
$ perl -w test.pl
    中美汇率计算器
    请输入要转换的货币与面值:CNY 2000
    CNY 2000 -> USD 296.30
$ perl -w test.pl
    中美汇率计算器
    请输入要转换的货币与面值:USD 1.2.3
    输入不合法！
$ perl -w test.pl
    中美汇率计算器
    请输入要转换的货币与面值:JPY 10000.00
    输入不合法！
```

## §A.3 修正浮点数

受制于浮点数的计算原理，部分小数从十进制转换到二进制时会产生误差，例如经典的`0.1+0.2!=0.3`：

```python
Python 3.10.4 [GCC 11.2.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> 0.1 + 0.2
    0.30000000000000004
```

现在为修正这一问题，我们可以制定一种标准，假如小数点后连续出现8个`0`时，就忽略这之后的所有小数数字。假设所有输入都是需要修正的合法小数（例如不出现`000.123`/`123`/`1.00000000`的情况），试编写这一程序。

```perl
print("Input a string: ");
$string = <STDIN>;
chomp($string);
$string =~ s/^(\d*\.\d*)0{8}\d*$/$1/;
print "$string";
```

```shell
$ perl -w test.pl
    Input a string: 123.456
    123.456
$ perl -w test.pl
    Input a string: 123.45600000000
    123.456
$ perl -w test.pl
    Input a string: 123.45600000000789
    123.456
$ perl -w test.pl
    Input a string: 123.4560000789
    123.4560000789
```

上述正则表达式虽然能实现预期功能，但是有一个问题：处理正常数据（例如`123.456`）时，它还是会进行一次替换操作，这无疑增大了系统资源开销。有没有一种方法，让正则表达式最后的`\d*`真的匹配到数字以后，才执行替换操作呢？有一种错误的想法是把`\d*`改成`\d+`，但是这样会导致一些问题——如果小数末尾只包含连续的8个0，`\d+`就会匹配失败，从而让程序认为无需对其进行修正，直接将原数据原封不动地输出：

```perl
print("Input a string: ");
$string = <STDIN>;
chomp($string);
$string =~ s/^(\d*\.\d*)0{8}\d+$/$1/; # 把末尾的\d*改成了\d+
print "$string";
```

```shell
yaner@DESKTOP-UVBN0SD ~/test> perl -w test.pl
    Input a string: 123.45600000000
    123.45600000000
```

既然我们的正则表达式是在Perl中解析的，我们就可以利用Perl语言的特性：

```perl
print("Input a string: ");
$string = <STDIN>;
chomp($string);
if($string =~ /^(\d*\.\d*)0{8}\d*$/){
    print "$1";
}else{
    print "$string";
}
```

```shell
$ perl -w test.pl
    Input a string: 123.456
    Legal Number: 123.456
$ perl -w test.pl
    Input a string: 123.45600000000789
    Fixed Number: 123.456
$ perl -w test.pl
    Input a string: 123.456000789
    Legal Number: 123.456000789
$ perl -w test.pl
    Input a string: 123.45600000000
    Fixed Number: 123.456
```



## §A.4 文件逐行读取与写入

现在`mail.txt`中包含以下内容：

```
From: hotel@example.com (Seasonal Hotel)
To: alice@example.com (Alice)
Subject: Hotel is booked successfully

Mrs.Alice,
	We have received your requestion of reservation on July 23th in Seasonal Hotel. Your room id is 1206.
	Wish you a pleasant time in our hotel, and all of our staff are looking forward to your arrival.
```

我们的任务是根据上述内容，生成一份邮件回复的模版，并将内容写入到`reply.txt`：

```
From: alice@example.com (Alice)
To: hotel@example.com (Seasonal Hotel)
Subject: re: Hotel is booked successfully

|> Mrs.Alice,
|>     We have received your requestion of reservation on July 23th in Seasonal Hotel. Your room id is 1206.
|>     Wish you a pleasant time in our hotel, and all of our staff are looking forward to your arrival.
```

Perl提供了`<>`运算符用于逐行读取数据，相当于`getline()`函数：

```perl
$from = ""; # 声明全局变量
$to = ""; # 声明全局变量
$subject = ""; # 声明全局变量
while($line = <>){
    if($line =~ m/^From:\s*(\w.*)$/i){
        $from = $1;
    }elsif($line =~ m/^To:\s*(\w.*)$/i){
        $to = $1;
    }elsif($line =~ m/^Subject:\s*(\w.*)$/i){
        $subject = $1;
    }elsif($line =~ m/^\s*$/){
        last;
    }
}
if(not defined($from) or not defined($to) or not defined($subject)){
    die "Missing required information!";
}
print("From: $to\n");
print("To: $from\n");
print("Subject: re: $subject\n\n");
while($line = <>){
    print "|> $line";
}
```

```shell
$ cat info.csv
    From: hotel@example.com (Seasonal Hotel)
    To: alice@example.com (Alice)
    Subject: Hotel is booked successfully

    Mrs.Alice,
            We have received your requestion of reservation on July 23th in Seasonal Hotel. Your room id is 1206.
            Wish you a pleasant time in our hotel, and all of our staff are looking forward to your arrival.
$ perl -w test.pl info.csv > reply.txt
$ cat reply.txt 
    From: alice@example.com (Alice)
    To: hotel@example.com (Seasonal Hotel)
    Subject: re: Hotel is booked successfully

    |> Mrs.Alice,
    |>      We have received your requestion of reservation on July 23th in Seasonal Hotel. Your room id is 1206.
    |>      Wish you a pleasant time in our hotel, and all of our staff are looking forward to your arrival.
```

## §A.5 HTML空行转换器

HTML渲染时使用`<br>`来表示换行符。我们的目标是将HTML源文件中的一个或多个连续的空行全部换成单个`<br>`标签。

首先让Perl使用文件读取模式（File-slurp），允许一次性读入多行文本，而不是每次只读入一行文本：

```perl
undef $/;
$text = <>; # 一次性读取整个文件
```

为了让`^`和`$`代表行首与行尾，而不是整个文本的起始与末尾，我们使用`m`修饰符。

```perl
undef $/;
$text = <>;
$text =~ s/^\s*$/<br>/mg; # 正则表达式总是尝试匹配最长串
print "$text";
```

```shell
$ cat info.html
    <html>
        <body>
            <h1>Hello!</h1>

            <span>This is a simple webpage.</span>


            <a>But the source file contains too much blank line.</a>
        </body>
    </html>
$ perl -w test.pl info.html
    <html>
        <body>
            <h1>Hello!</h1>
    		<br>
            <span>This is a simple webpage.</span>
    		<br>
            <a>But the source file contains too much blank line.</a>
        </body>
    </html>
```

## §A.6 匹配双引号中的文本

要求设计一个正则表达式，能匹配`"UAC" is the short of "User Account Control"`中的`UAC`。

一开始我们可能想到`"(.*)"`，但是这一表达式中的`.*`会尽可能匹配更长的字符串，导致匹配的结果只有`UAC" is the short of "Use Account Control`这一个：

```perl
$input = "\"UAC\" is the short of \"User Account Control\"";
$input =~ m/"(.*)"/;
print "$1";
```

```shell
$ perl -w test.pl
UAC" is the short of "User Account Control
```

我们现在要解决的问题是，如何让正则表达式的`(.*)`碰到第一个右双引号就立刻退出匹配，换言之，如何让`(.*)`匹配除了双引号之外的字符——我们想到了`[^...]`可以表示否定：`[^"]`：

```perl
$input = "\"UAC\" is the short of \"User Account Control\"";
$input =~ m/"([^"]*)"/;
print "$1";
```

```shell
$ perl -w test.pl
	UAC
```

## §A.7 匹配HTML加粗标签中的文本

要求设计一个正则表达式，能匹配`<b>This</b> sentence contains <b>bold</b> characters`中的`This`。

参考[§A.6 匹配双引号中的文本](#§A.6 匹配双引号中的文本)一节的经验，我们肯定不能写`<b>.*</b>`。那么能不能用`[^</b>]`呢？不能，因为字符组会认为不能出现`<`、`/`、`b`、`>`中的任何一个字符，而我们预期的是不能连续出现`</b>`这一个整体。

解决思路有如下几种：

- 将这个整体用括号括起来：

  ```perl
  $input = "<b>This</b> sentence contains <b>bold</b> characters";
  $input =~ m{<b>([^(<\/b>)]*)<\/b>}g;
  print "$1";
  ```

  ```shell
  $ perl -w test.pl
      This
  ```

- 使用忽略匹配优先量词：

  ```perl
  $input = "<b>This</b> sentence contains <b>bold</b> characters";
  $input =~ m{<b>(.*?)<\/b>}g;
  print "$1";
  ```

  ```shell
  $ perl -w test.pl
      This
  ```

- 使用排除环视与忽略匹配优先量词：

  ```perl
  $input = "<b>This</b> sentence contains <b>bold</b> characters";
  $input =~ m{<b>((?!<\/b>).*?)<\/b>}g;
  	# 先匹配<b>，然后如果右边没有</b>，就匹配任意字符.。重复这个过程*，直到右边有</b>
  print "$1";
  ```

  ```shell
  $ perl -w test.pl
      This
  ```

# §B 正则引擎与原理

## §B.1 正则引擎分类

正则表达式的引擎简称正则引擎，虽然可以细分很多种，但是可以大致分为两大类：文本主导引擎（DFA）和表达式主导引擎（NFA）。为了规范各类引擎，特别是NFA引擎的行为，IEEE发布了POSIX标准（Portable Operating System Interface）。

```mermaid
flowchart LR

	TraditionalNFA[("传统型NFA")]
	POSIXNFA[("POSIX NFA")]
	DFA[("DFA")]
	
	Start(("开始"))
	IsIgnoreClassifierSupported[/"是否支持忽略优先量词"/]
	IsCapturingParenthesesAndBackreference[/"是否支持捕获型括号和回溯"/]
	
	Start-->IsIgnoreClassifierSupported
	IsIgnoreClassifierSupported--"是"-->TraditionalNFA
	IsIgnoreClassifierSupported--"否"-->IsCapturingParenthesesAndBackreference
	IsCapturingParenthesesAndBackreference--"是"-->POSIXNFA
	IsCapturingParenthesesAndBackreference--"否"-->DFA
```

| 正则引擎类型 |                  使用该引擎的编程语言和程序                  |
| :----------: | :----------------------------------------------------------: |
|     DFA      |      `awk`、`egrep`、`flex`、`lex`、`MySQL`、`Procmail`      |
|  传统型DFA   | `GNU Emacs`、`Java`、`grep`、`less`、`more`、`.NET`、`PCRE library`、`Perl`、`PHP`、`Python`、`Ruby`、`sed`、`vi` |
|  POSIX NFA   | `mawk`、`Mortice Kern Systems' utilities`、`GNU Emacs`（明确指定时） |
| DFA/NFA混合  |          `GNU awk`、`GNU grep`、`GNU egrep`、`Tcl`           |

## §B.2 正则引擎原理

到目前为止，我们学过的所有正则表达式都满足以下两条普适的规则：

1. 优先选择最左端的匹配结果

   举个例子，现在我们使用正则表达式`s/aa/b/`，对字符串`aaa`进行替换。那么正则引擎是先会匹配左侧的`aa`替换成`b`得到`ba`，还是先匹配右侧的`aa`替换成`b`得到`ab`呢？依据这条原则，结果应该是前者：

   ```perl
   $input = "aaa";
   $input =~ s/aa/b/;
   print "$input"
   ```

   ```shell
   $ perl -w test.pl 
   	ba
   ```

   这是因为正则引擎的匹配过程总是从左开始。正则表达式开始匹配时，首先从第一个`a`开始，按照正则表达式尝试匹配，发现能够匹配成功，于是选中第一、二个`a`，将这一整体替换为`b`。

2. 优先匹配量词（`*`、`+`、`?`、`{m,n}`），且尽可能在成功的前提下匹配更长的文字序列

   举个例子，现在我们使用正则表达式`s/a{3}/b/`，对字符串`aaaaaaa`进行替换，那么第一次匹配成功时，对应的文字是`aaa`还是`aa`呢？依据这条原则，结果应该是前者：

   ```perl
   $input = "aaaaaaa";
   $input =~ s/aa/b/;
   print "$input"
   ```

   ```shell
   $ perl -w test.pl
   	bba
   ```

   但是“尽可能匹配更长的文字序列”必须在成功的前提下。而且后面元字符匹配的“最长序列”受制于前一个元字符匹配的最长序列。

   - “尽可能匹配更长的文字序列”必须在成功的前提下

     以`^.*\d\d$`为例，这个正则表达式的作用是提取一串数字的最后两位数字。最前面是`.*`，可以匹配任意长的所有字符，貌似会把最后两位数字也匹配进去，导致我们的`\d\d`无法匹配。这种说法是错误的，因为`\d\d`无法匹配就代表着整个正则表达式匹配失败，这个时候为了匹配成功，`\d\d`会强迫之前的元字符逐个**交还**（Unmatch）某些字符。以字符串`123`为例，首先`.*`匹配`123`，然后`\d\d`匹配失败，于是`.*`会把`3`交还回来，`\d`发现可以匹配成功。接着前进到下一个`\d`，发现匹配又失败了，于是强迫`\d`把`3`交还回来，但是此时前一个`\d`匹配失败，因此前一个`\d`会强迫`.*`交还一个字符`2`，现在前一个`\d`匹配成功，`.*`也匹配成功，于是整个匹配过程顺利结束。

   - 后面元字符匹配的“最长序列”受制于前一个元字符匹配的最长序列

     以`^.*\d+$`为例，尝试用字符串`Copyright 2003`进行匹配，得到的结果是什么呢？首先前一个元字符`.*`会尽可能的匹配最长序列，显然它可以从头一直匹配到尾，但是之后的`\d+`不能匹配了。于是`\d+`强迫`.*`交还一个文字`3`，此时`.*`和`\d`都符合要求，于是`\d+`匹配到的结果只有`3`。这里`\d+`并不能够匹配到它的极限——`2003`，这是因为后一个元字符`\d+`匹配到的最长序列受制于前一个元字符`.*`匹配到的`Copyright 200`影响。

## §B.3 NFA与DFA

思考这个问题：如果用`to(nite|knight|night)`尝试匹配字符串`Shall we go tonight?`，匹配流程是什么样的？NFA和DFA会给出不同的答案。

### §B.3.1 NFA简介

表达式主导引擎/非确定型有穷自动机（NFA）会从正则表达式的第一个字符开始，在字符串中查找匹配的部分，如果符合，那么就尝试用正则表达式的第二个字符，对字符串进行匹配，以此类推，直到正则表达式的所有元字符都匹配成功。

分析上述例子，`to(nite|knight|night)`会先从`t`开始，在字符串中匹配到`t`，然后接着用正则表达式的第二个字符`o`，发现字符串的`t`后面也有`o`，匹配成功，然后进入到正则表达式的`()`元字符。`()`内有三种选项，NFA会一个个的尝试。首先尝试`nite`，发现正则表达式的`t`无法匹配，转而尝试`knight`，发现正则表达式的`k`无法匹配，转而尝试`night`，匹配成功。

在这种匹配方式中，表达式的控制权在不同元素间来回切换，因此被称为表达式优先引擎。

NFA在处理正则表达式的过程中，每一个子表达式都是各自独立的，子表达式之间不存在联系。除此之外，NFA还支持一系列DFA不支持的功能：

- 反向引用（Perl中的`$1`，正则表达式中的`\1`）
- 环视
- 非匹配优先量词
- 有序多选结构
- 固化分组与占有优先量词

### §B.3.2 DFA简介

文本主导引擎/确定性有穷自动机（DFA）会从字符串的第一个字符开始，尝试匹配整个正则表达式，如果出现问题，那么就将当前正则表达式挂起，引入字符串的第二个字符，再让正则表达式进行匹配。以此类推，直到整个正则表达式匹配成功。这种方式在扫描字符串时，会记录当前有效的所有匹配分支。

分析上述例子，DFA首先读取字符串的第一个字符`S`，代入到正则表达式`to(nite|knight|night)`中，发现正则表达式第一个文字`t`都匹配不了，因此DFA抛弃了字符串的第一个字符`S`，然后读取字符串的第二个字符`h`。以此类推，直到DFA读取字符串的`t`，发现可以和正则表达式的第一个字符`t`匹配，再读取后一个字符`o`，也匹配成功，但是后续的元字符是一个选择分支元素`()`。这个时候DFA就会创建分支，将这个正则表达式拆成`to(nite)`、`to(knight)`、`to(night)`，分别进行匹配，发现只有`to(night)`可以匹配成功，于是整体判定为成功。

```mermaid
flowchart LR
	a1-->a2-->a3-->a4-->a5-->a6
	a6-->a7-->a7_lose["失败"]-->success
	a6-->a8-->a7_win["成功"]-->success
	a6-->a9-->a9_lose["失败"]-->success
	success["有一个匹配成功就算成功"]
	subgraph a1 [" "]
		direction LR
		a1_1([">S< hall we go tonight?"])
		a1_2["/ >t< o(nite|knight|night) /"]
	end
	subgraph a2 [" "]
		direction LR
		a2_1(["S >h< all we go tonight?"])
		a2_2["/ >t< o(nite|knight|night) /"]
	end
	subgraph a3 ["......"]
		direction LR
	end
	subgraph a4 [" "]
		direction LR
		a4_1(["Shall we go >t< onight?"])
		a4_2["/ >t< o(nite|knight|night) /"]
	end
	subgraph a5 [" "]
		direction LR
		a5_1(["Shall we go t >o< night?"])
		a5_2["/ t >o< (nite|knight|night) /"]
	end
	subgraph a6 [" "]
		direction LR
		a6_1(["Shall we go to >n< ight?"])
		a6_2["/ to >(nite|knight|night)< /"]
	end
	subgraph a7 [" "]
		direction LR
		a7_1(["Shall we go to >n< ight?"])
		a7_2["/ to >(nite)< /"]
	end
	subgraph a8 [" "]
		direction LR
		a8_1(["Shall we go to >n< ight?"])
		a8_2["/ to >(knight)< /"]
	end
	subgraph a9 [" "]
		direction LR
		a9_1(["Shall we go to >n< ight?"])
		a9_2["/ to >(night)< /"]
	end
```

### §B.3.3 有穷自动机的确定性

根据NFA和DFA的原理，我们可以推理出一般情况下DFA的效率要更高，因为NFA会使用不同的子表达式对相同的文字进行匹配，导致浪费了大量时间。

DFA（确定型有穷自动机）的最大特点就是，在抵达正则表达式的末尾之前，就能直到其是否能够全局匹配给定的字符串。只要字符串中的一个文字被匹配过，那么它所属的子表达式就永远不会改变。

NFA（非确定型有穷自动机）恰恰相反，由于它会将正则表达式衍生出众多分支，所以只要所有分支都没遍历完，我们就不知道某个字符属于哪个子表达式，甚至是第一个字符属于哪个表达式也不知道。

### §B.3.4 回溯

NFA引擎最重要的特性就是**回溯**（Backtracking）：依次处理各个子表达式，当遇到多个可能成功的分支时，暂且选择其中一个，同时记住另外几个并压入栈中（LIFO，后进先出，Last In First Out），以备这一个匹配不成功。

问题来了：NFA引擎会最优先选择哪个子表达式？答案是下面这条很拗口的原则：

> 如果需要在“进行尝试”和“跳过尝试”之间进行选择，那么对于匹配优先量词，NFA引擎会优先“进行尝试”；如果对于忽略优先量词，那么会优先“跳过尝试”。

例如用正则表达式`ab?c`匹配字符串`abc`，NFA引擎的过程如下：

1. 先读正则表达式的第一个元素`a`，发现字符串的第一个字符`a`可以匹配。
2. 再读正则表达式的第二个元素`b?`，根据上述拗口的原则，这-是一个匹配优先量词，因此NFA引擎会优先“进行尝试”，同时将“跳过尝试”的分支压入栈内，发现字符串的第二个字符`b`符合要求。
3. 最后读正则表达式的第三个元素`c`，发现发现字符串的第三个字符`c`可以匹配。

例如用正则表达式`ab?c`匹配字符串`ac`，NFA引擎的过程如下：

1. 先读正则表达式的第一个元素`a`，发现字符串的第一个字符`a`可以匹配。
2. 再读正则表达式的第二个元素`b?`，根据上述拗口的原则，这是一个匹配优先量词，因此NFA引擎会优先“进行尝试”，同时将“跳过尝试”的分支压入栈内，发现字符串的第二个字符`c`不符合符求。于是回溯到“跳过尝试”的状态。
3. 最后读正则表达式的第三个元素，发现字符串的第二个字符`c`可以匹配。

例如用正则表达式`ab??c`匹配字符串`ac`，NFA引擎的过程如下：

1. 先读正则表达式的第一个元素`a`，发现字符串的第一个字符`a`可以匹配。
2. 再读正则表达式的第二个元素`b??`，根据上述拗口的原则，这是一个忽略优先匹配量词，因此NFA引擎会优先“跳过尝试”，同时将“进行尝试”的分支压入栈内。
3. 最后读正则表达式的第三个元素，发现字符串的第二个字符`c`可以匹配。

`+`和`*`可以大致看作`(...(...(...)?)?)?`，因此也是匹配优先量词。

### §B.3.5 POSIX

分析这道题：用正则表达式`a(b)?(bc)?`匹配字符串`abc`，得到的结果是什么？答案是：因引擎而异。

- NFA是正经的顺序匹配，所以匹配到`(b)?`之后，因为在字符串中找不到第二个`b`，所以无法匹配`(bc)?`最终得到的结果就是`ab`。
- DFA类似于广搜，既会尝试匹配`(b)?`，又会尝试匹配`(bc)?`，同时记录多个匹配，并最终选择更长的匹配结果`abc`。

为了让NFA的输出效果与DFA看齐，我们不得不又使用一堆特性。为了解决这种乱象，IEEE颁布了POSIX标准，规定如果字符串的某个位置存在多个可能的匹配，则应该返回最长的匹配，其实现原理类似于深搜，但是遍历完整颗树才结束。符合POSIX标准的NFA引擎特称为POSIX NFA。



## §B.4 固化分组

思考这个例子：设计一种正则表达式，能够保留十位数小数到小数点后三位（向下取整，不考虑四舍五入），并且具有鲁棒性，遇到非法输入（非小数、小数点后只有一两位数字）时可以提示报错：

- 例如`12.3`报错，因为我们不知道百分位和千分位，为了保证数据的准确性，我们不能凭空在后面自己加数据
- 例如`12.345`输出`12.345`
- 例如`12.34560`输出`12.345`
- 例如`12.340`输出`12.34`

乍一看这道题，我们可能不假思索地写入这种正则表达式：`(\d\d[1-9]?)\d+`。前两个`\d`用于匹配十分位和百分位，后面的`[1-9]?`用于排除千分位的`0`，最后的`\d+`一是可以无限匹配之后的所有数字，检测后面是否出现非数字字符，从而验证数据的合法性，二是至少匹配一个数字，可以匹配千分位，防止没有千分位，只有十分位和百分位时不报错：

```perl
print("Input a string: ");
$string = <STDIN>;
chomp($string);
if($string =~ /(\d+\.\d\d[1-9]?)\d+/){
    print "Fixed Number: $1";
}else{
    print "Illegal Number!";
}
```

```shell
$ perl -w test.pl
    Input a string: 123.456789
    Fixed Number: 123.456
$ perl -w test.pl
    Input a string: 123.4
    Illegal Number!
```

然而这个正则表达式有个BUG——就是在处理正常的只有千分位数字时会吞最后一位：

```shell
$ perl -w test.pl
    Input a string: 123.456
    Fixed Number: 123.45
```

之所以会出现这种情况，是因为正则表达式的**交还**性质。最后的`\d+`因为没有数字可以匹配，所以会强迫之前的`[0-9]?`交出一个数字。

所以怎么修这个BUG呢？我们肯定不能把正则表达式的`\d+`改成`\d*`因为根据上述分析，`+`的作用是防止没有千分位的情况。有没有一种方法，禁止后面的量词进行回溯呢？非常不幸，没有。但是我们可以让前面的量词不交还字符，就算后面的量词进行回溯，因为前面的量词没有将其他情况压入栈内，所以后面的量词也拿不到数字。这就是**固化分组**（Atomic Grouping）`(?>)`：

我们给`[0-9]?`添加固化分组`(?>...)`，变成`(?>[0-9]?)`，这样`[0-9]?`就不会交还任何字符了：

```perl
print("Input a string: ");
$string = <STDIN>;
chomp($string);
if($string =~ /(?>\d+\.\d\d[1-9]?)\d*/){
    print "Fixed Number: $1";
}else{
    print "Illegal Number!";
}
```

```shell
$ perl -w test.pl
    Input a string: 123.456
    Fixed Number: 123.456
```

一般情况下，固化分组不能与忽略优先匹配量词搭配使用，例如`(?>.*?)`将不会匹配任何字符。

固化分组本质上并不是一个新功能，因为我们完全可以用肯定环视模拟固化分组。例如固化分组`((?>...))`可以改写成`((?=...))\1`。

## §B.5 占有优先量词

我们在上一节[§B.4 固化分组](#§B.4 固化分组)中已经知道，给`.*`套上`(?>...)`变成`(?>.*)`，可以让`.*`不交还任何字符。但是给每一个量词都套上`(?>...)`实在是太麻烦了，事实上正则表达式提供了占有优先量词，可以起到固化分组的效果：

|   原写法   |  固化分组写法  | 占有优先量词写法 |
| :--------: | :------------: | :--------------: |
|   `...?`   |   `(?>...?)`   |     `...?+`      |
|   `...*`   |   `(?>...*)`   |     `...*+`      |
|   `...+`   |   `(?>...+)`   |     `...++`      |
| `...{m,n}` | `(?>...{m,n})` |   `...{m,n}+`    |

## §B.6 有序多选结构

我们已经直到NFA引擎在处理`(...|...|...)`之类的多选结构时，经历的流程类似于深搜，只要找到一个子表达式符合要求，那么就会忽略其他表达式。而DFA引擎类似于广搜，同时处理众多子表达式，谁经历的步骤最少就能率先匹配成功。在NFA引擎的处理过程中，我们容易发现多选结构的选择是有时间上的先后顺序的，而时间上的先后顺序又取决于正则表达式多选结构的列举顺序，因此我们称NFA引擎的多选结构是有序的。

思考这个问题：现在要提取一句话中的一月份日期，例如要从`Today is Jan 5 and we are going to travel.`提取出`Jan 5`。通过对一月份日期的穷举，我们可以轻松地写出用于匹配数字部分的有序结构：`(Jan (0?|\d|[12]\d|3[01]))`。但是这个正则表达式是有问题的：

```perl
$string = "Tomorrow is Jan 31 and we will go back.";
if($string =~ m/(Jan (0?\d|[12]\d|3[01]))/){
    print "$1";
}
```

```shell
$ perl -w test.pl
	Jan 3
```

怎么会事呢？我们的正则表达式只匹配了第一个数字，这是由于多选结构的有序性，Perl先尝试匹配第一个分支`0?\d`，发现`31`的`3`可以匹配成功，于是直接结束匹配过程。要修这个BUG也很简单，我们只需调整多选结构中各分支的顺序即可：

```perl
$string = "Tomorrow is Jan 31 and we will go back.";
if($string =~ m/(Jan (3[01]|[12]\d|0?\d))/){
    print "$1";
}
```

```shell
$ perl -w test.pl
    Jan 31
```

