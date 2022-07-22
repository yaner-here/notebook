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

# §1 元字符

正则表达式中的各个字符可以分为两类：一类是没有特殊含义的普通字符，称为**文字**（Literal）；另一类是具有特殊含义、代表某种规则的特殊字符，称为**元字符**（Metacharacter）。

## §1.1 `^`/`$` 行的起始与结束

`^`代表一行的开始，`$`代表一行的结束。本来正则表达式的匹配结果可能在行中，而`^`只寻找行首的内容，`$`只寻找行末的内容，这种以位置为依据，而非以文本为依据，限定匹配结果的过程称为**锚定**（Anchor）。

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

# §2 例题

### §2.1 时刻

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

