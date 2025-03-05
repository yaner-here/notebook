# §1 语法

## §1.1 模块与包

在Go中，一个模块可以包含若干个包。我们使用`go mod init <MODULE_NAME>`来新建一个模块：

```shell
$ go mod init demo
	go: creating new go.mod: module demo

$ tree
	.
	└── go.mod
	1 directory, 1 file

$ cat go.mod
	module demo
	go 1.23.6
```

文件夹名称与包名称最好保持一致。包文件夹中的每个`*.go`源文件开头都要加上`package <PACKAGE_NAME>`语句。在下面的例子中，我们使用系统库`fmt`输出`Hello world`。

```shell
$ tree
	.
	├── go.mod
	└── main.go

$ cat main.go
	package main
	import "fmt"
	func main(){
	    s := "Hello world"
	    fmt.Println(s)
	}

$ go run main.go
	Hello world

```

Go自带包管理器。这里我们以一个第三方字符串格式化库`flect`为例，首先使用`go get`命令下载依赖，然后在`main.go`中导入并使用这个包。

```shell
$ go get github.com/gobuffalo/flect
	go: downloading github.com/gobuffalo/flect v1.0.3
	go: added github.com/gobuffalo/flect v1.0.3

$ tree
	.
	├── go.mod
	├── go.sum
	└── main.go
	1 directory, 3 files

$ cat go.mod
	module demo
	go 1.23.6
	require github.com/gobuffalo/flect v1.0.3 // indirect

$ cat go.sum
	github.com/davecgh/go-spew v1.1.0/go.mod h1:<HASH>
	github.com/davecgh/go-spew v1.1.1/go.mod h1:<HASH>
	github.com/gobuffalo/flect v1.0.3 h1:<HASH>
	github.com/gobuffalo/flect v1.0.3/go.mod h1:<HASH>
	github.com/pmezard/go-difflib v1.0.0/go.mod h1:<HASH>
	github.com/stretchr/objx v0.1.0/go.mod h1:<HASH>
	github.com/stretchr/objx v0.4.0/go.mod h1:<HASH>
	github.com/stretchr/objx v0.5.0/go.mod h1:<HASH>
	github.com/stretchr/testify v1.7.1/go.mod h1:<HASH>
	github.com/stretchr/testify v1.8.0/go.mod h1:<HASH>
	github.com/stretchr/testify v1.8.1/go.mod h1:<HASH>
	gopkg.in/check.v1 v0.0.0-20161208181325-20d25e280405/go.mod h1:<HASH>
	gopkg.in/yaml.v3 v3.0.0-20200313102051-9f266ea9e77c/go.mod h1:<HASH>
	gopkg.in/yaml.v3 v3.0.1/go.mod h1:<HASH>

$ cat main.go
	package main
	import "fmt"
	import "github.com/gobuffalo/flect"
	func main(){
	    s := "Hello world"
	    s = flect.Dasherize(s)
	    fmt.Println(s)
	}

$ go run main.go
	hello-world
```

Go语言还支持语义版本，即同时导入一个包的两个不同版本。

```shell
$ tree
	.
	├── go.mod
	└── main.go
	1 directory, 2 files

$ cat go.mod
	module demo
	go 1.23.6
	require (
	    github.com/gofrs/uuid v1.0.0
	    github.com/gofrs/uuid/v3 v3.1.2
	)

$ cat main.go
	package main
	import (
	    "fmt"
	    "log"
	    uuidv1 "github.com/gofrs/uuid"
	    uuidv3 "github.com/gofrs/uuid/v3";
	)
	func main(){
	    id_1 := uuidv1.NewV4()
	    id_2, err := uuidv3.NewV4()
	    if err != nil {
	        log.Fatal(err)
	    }
	    fmt.Println("uuidv1: ", id_1)
	    fmt.Println("uuidv3: ", id_2)
	}

$ go get
	go: downloading github.com/gofrs/uuid/v3 v3.1.2
	go: downloading github.com/gofrs/uuid v1.0.0

$ go run main.go
	uuidv1:  f277b4a0-b03e-4d93-a12a-282071903664
	uuidv3:  6cf39bb1-073c-4dec-91eb-ecc87a9aad88
```

## §1.2 数据类型

### §1.2.1 数字

Go自带以下数学数据类型：

| 数据类型           | 占用字节    | 含义                  |
| -------------- | ------- | ------------------- |
| `uint8`/`byte` | `1`     | 无符号8位整数             |
| `uint16`       | `2`     | 无符号16位整数            |
| `uint32`       | `4`     | 无符号32位整数            |
| `uint64`       | `8`     | 无符号64位整数            |
| `int8`         | `1`     | 有符号8位整数             |
| `int16`        | `2`     | 有符号16位整数            |
| `int32`/`rune` | `4`     | 有符号32位整数            |
| `int64`        | `8`     | 有符号64位整数            |
| `float32`      | `4`     | IEEE-754单精度浮点数      |
| `float64`      | `8`     | IEEE-754双精度浮点数      |
| `complex64`    | `8`     | 复数，实部和虚部均为`float32` |
| `complex128`   | `16`    | 复数，实部和虚部均为`float64` |
| `uint`         | `4`或`8` | 取决于架构的无符号整数         |
| `int`          | `4`或`8` | 取决于架构的有符号整数         |
| `uintptr`      | `4`或`8` | 指针（本质上是`uint`）      |

```shell
$ cat main.go
	package main
	import "fmt"
	func main(){
	    var n uint8 = 255;
	    fmt.Println(n + 1);
	}

$ go run main.go
	0
```

### §1.2.2 字符串

字符串是由若干个字符组成的序列。其中用反引号包裹的是原始型字符串，不会转义特殊字符，可以记录多行文本（类似于Python的三引号字符串）；用双引号包裹的是解释型字符串；用单引号包裹的只能是多字节单字符，其数据结构为`rune`（完全等价于`int32`）。

```shell
$ cat main.go
	package main
	import "fmt"
	func main(){
	    s1 := "String s1 contains a \t character."
	    s2 := `String s2 contains a \t character.`
	    s3 := '爱'
	    fmt.Println(s1);
	    fmt.Println(s2);
	    fmt.Printf("s3's value is %v, type is %T", s3, s3)
	}

$ go run main.go
	String s1 contains a     character.
	String s2 contains a \t character.
	s3's value is 29233, type is int32
```

需要注意的是，Go原生支持UTF-8字符集，但是在字符串中是逐字节保存的（等价于C语言中的`char`）。因此在遍历字符串中的UTF-8字符时，使用`len()`得到的是字节数，于是遍历时，`string()`方法会认为每个字节都是某个UTF-8字符的开始，因此会通过变长编码的方式读取出错误的UTF-8字符。正确的方法是使用`range`关键字：

```shell
$ cat main.go
	package main
	import "fmt"
	func main(){
	    a := "Hello, 世界"
	    for i := 0; i < 15; i++ { fmt.Printf("%d ", i) }
	
	    fmt.Println()
	    for i := 0; i < len(a); i++ { fmt.Printf("%s", string(a[i])) }
	
	    fmt.Println()
	    for _, c := range a { fmt.Printf("%s", string(c)) }
	}

$ go run main.go
	0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
	Hello, ä¸ç
	Hello, 世界
```

## §1.3 变量与常量

Go语言定义变量有两种语法：

- `var <NAME> <TYPE>`：变量定义与赋值可以结合或分离，如没有赋值则定义后缺省为零值。
- `<NAME> := <VALUE>`：变量定义与赋值结合，变量类型取决于值的类型。

定义变量有两种语法：

- `const <NAME> = <VALUE>`：定义并初始化一个常量
- `const { <NAME> = <VALUE> }`：定义并初始化多个常量

Go还支持多变量赋值：

```shell
$ cat main.go
	package main
	import "fmt"
	func get_tuple_values() (int, float64, bool, string) {
	    return 1, 2.2, true, "3.3"
	}
	func main() {
	    _, _, _, s := get_tuple_values()
	    fmt.Println(s)
	}

$ go run main.go
	3.3
```

与C语言不同，在Go语言中，如果两个带类型常量要进行数学运算，则它们的数据类型必须相同，不会进行隐式类型转换。对于无类型常量而言，规则与C语言相同。

```shell
$ cat main.go
	package main
	import "fmt"
	const a = 123 // int,无类型常量,运行时动态调整数据类型
	const b = int(456) // int,有类型常量
	func main() {
	    var c int8 = 0
	    fmt.Printf("a type: %T, b type: %T", a, b) // 均为int
	    fmt.Println(a * c); // 正常
	    fmt.Println(b * c); // 报错, mismatched types int and int8
	}
```

## §1.4 标识符

标识符只能包含数字、字母、下划线，且大小写敏感，不能用数字开头。Go语言规范推荐一律使用驼峰命名法。标识符的第一个字母是否大小写有着特殊含义——在一个包中，只有大驼峰命名的标识符才能被导出，供外界调用。

## §1.5 数组和切片

数组是定长的，切片是变长的，可以使用`<NAME>[<INDEX>]`进行索引。与C语言不同的是，在栈上创建的数组或切片会缺省时被初始化为零值，并且可以通过`=`运算符在变量之间进行深拷贝。

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    a1 := [4]string{"Hello", ",", "world", "!"} // 数组
	    a2 := []string{"Hello", ",", "world", "!"} // 切片
	    fmt.Printf("a1 type: %T, a2 type: %T", a1, a2)
	}

$ go run main.go
	a1 type: [4]string, a2 type: []string
```

在切片末尾追加元素可以使用`append()`方法：

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    var arr1 []int32
	    arr2 := []int32{1, 2, 3}
	    for _, i := range arr2 {
	        arr1 = append(arr1, i)
	    }
	    arr1 = append(arr1, 4)
	    arr1 = append(arr1, arr2...)
	    fmt.Println(arr1)
	    fmt.Println(arr1, "len:", len(arr1))
	}

$ go run main.go
	[1 2 3 4 1 2 3] len: 7
```

与C++中的`std::vector`类似，Go中的切片也有长度和容量的概念，分别使用`len(slice)`和`cap(slice)`获取。除了我们熟知的两种创建变量的方式以外，我们还可以使用`make(type, [init_cap]=0, [mul_cap]=2)`创建切片。

```go
a := []int32{} // 初始长度为0，初始容量为0，容量倍增系数为2
var b []int32 // 初始长度为0，初始容量为0，容量倍增系数为2
c := make(int32, 1, 3) // 初始长度为1，初始容量为3，容量倍增系数为3，赋零值
```

与Python类似，我们可以使用`[<START>:<END>]`语法，对某个数组或切片，创建一个区间左闭右开的子切片，它与原切片共享同一块内存空间。同理，`<START>`和`<END>`均可省略，缺省为第一个/最后一个元素。**我们可以使用`[:]`把数组转换为等价的切片**。

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    a := []int32{1, 2, 3, 4, 5}
	    fmt.Println("a: ", a)
		
	    b := make([]int32, 3)
	    copy(b, a)
	    b[0] = 9;
	    fmt.Println("a: ", a)
		
	    c := a[2:]
	    c[0] = 9
	    fmt.Println("a: ", a)
	}


$ go run main.go
	a:  [1 2 3 4 5]
	a:  [1 2 3 4 5]
	a:  [1 2 9 4 5]
```

## §1.6 流程控制

### §1.6.1 条件语句

与其它语言类似，Go语言支持`if`、`else if`、`else`：

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    a := 2;
	    if a == 1 {
	        fmt.Println("a is 1")
	    } else if a == 2 {
	        fmt.Println("a is 2")
	    } else {
	        fmt.Println("a is unknown")
	    }
	}

$ go run main.go
	a is 2
```

在C++中，我们可以使用逗号表达式，实现在求值前执行其它语句，并且把这些语句压到同一行。Go也有类似的机制，只不过Go使用的不是逗号，而是分号。

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    scores := map[string]int32{
	        "Alice": 90,
	        "Bob": 95,
	    }
	    if _, ok := scores["Carol"]; ok {
	        fmt.Println("Carol exists!")
	    } else {
	        fmt.Println("Carol doesn't exist")
	    }
	}

$ go run main.go
	Carol doesn't exist
```

### §1.6.2 循环语句

Go语言中只有一种循环——`for`。它没有`while`、`do-while`、`while-do`、`foreach`之类的语法糖。

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    str := [2]string{"hello", "world"}
	    for i := 0; i < len(str); i++ {
	        fmt.Printf("%s ", str[i])
	    }
	}

$ go run main.go
	hello world 
```

为了绕过`len()`，Go为遍历集合提供了`range`关键字：

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    str := [2]string{"hello", "world"}
	    for _, c := range str {
	        fmt.Printf("%s ", c)
	    }
	}

$ go run main.go
	hello world 
```

Go提供了`continue`和`break`关键字用于流程控制，像Python一样使用即可。

### §1.6.3 `switch`

Go对于`switch`有两种版本：一种是传统C语言的样式，比如指定某个变量，遍历它的取值范围；另一种是`else if`的简短语法糖，只需指定所需的布尔表达式即可。

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    a := 2
	    switch a {
	        case 1:
	            fmt.Println("a == 1")
	        case 2:
	            fmt.Println("a == 2")
	        default:
	            fmt.Println("a is unknown")
	    }
	    switch {
	        case a >= 1:
	            fmt.Println("a >= 1")
	        case a >= 2:
	            fmt.Println("a >= 2")
	        default:
	            fmt.Println("a is unknown")
	    }
	}

$ go run main.go
	a == 2
	a >= 1
```

需要注意的是在C++中，默认情况下可能命中多个`case`，所以必须使用`break`才能保证命中的唯一性。然而在Go中，每个`case`自带唯一性，只有经过`fallthrough`显示声明后才会继续尝试匹配下一个命中的`case`，此时`default`分支默认会被命中。

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    a := 2
	    switch {
	        case a >= 1:
	            fmt.Println("a >= 1")
	            fallthrough
	        case a >= 2:
	            fmt.Println("a >= 2")
	            fallthrough
	        default:
	            fmt.Println("a is unknown")
	    }
	}

$ go run main.go
	a >= 1
	a >= 2
	a is unknown
```

## §1.7 `map`

Go中的`map[键类型]值类型`是一种内置数据结构，在内存充足的情况下可以存储无穷多个键值对，因此只能使用`len()`方法，不能使用`cap()`方法。类似于C++中的`std::map<键类型,值类型>`，受制于建树原理，存储的键数据类型必须是可以比较大小的。**特殊地，如果一个结构体中的所有字段都是可比较的，则该结构体也是可比较的**。

`map`的遍历顺序是不固定的：

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    scores := map[string]int32{
	        "Alice": 95,
	        "Bob": 60,
	        "Carol": 100,
	    }
	    scores["David"] = 80
		
	    for key := range scores {
	        fmt.Printf("%s %d ", key, scores[key])
	    }
	    fmt.Println()
	    for key, value := range scores {
	        fmt.Printf("%s %d ", key, value)
	    }
		delete(scores, "Alice")
	}

$ go run main.go
	Alice 95 Bob 60 Carol 100 David 80
	Bob 60 Carol 100 David 80 Alice 95
```

`delete(map, key)`用于删除`map`中的键值对。无论`key`是否存在，该函数都不会报错。

Go语言将"查询键值对是否存在"与"查询键值对"两个任务合并在了一起。其实`map[key]`会返回两个值，分别是`value`和布尔型的`ok`，后者表示键值对是否存在。如果不存在，则`value`为对应数据类型缺省的零值。

当`value`为结构体时，`map`不支持直接修改结构体中的字段，必须先取得该结构体，更改其中的字段，再整体更新回去。这一过程的所有赋值都是深拷贝。

## §1.8 函数

Go使用关键字`func`定义函数，语法为`func 函数名(形参列表) 返回类型名`，其中返回类型名缺省时表示不返回值。特殊地，当函数形参列表中存在一个子区间，该区间内的所有变量类型均相同，则可以只为该列表最后一个形参指定变量类型：

```shell
$ cat main.go
	package main
	import "fmt"
	func greet(name, msg string, id int32) {
	    fmt.Printf("Hello, %s![id: %d], %s", name, id, msg)
	}
	func main() {
	    greet("Yaner", "good evening", 1)
	}

$ go run main.go
	Hello, Yaner![id: 1], good evening
```

一个函数可以返回多个值：

```go
func greet(id int32) (int32, string) {
	return 1, "Alice"
}
```

Go提供了具名返回值，指的是进入函数体内，会自动初始化具名返回值对应的变量为零值，然后就能在函数体内进行编辑，遇到不带参数的`return`语句则直接返回具名返回值。

```shell
$ cat main.go
	package main
	import "fmt"
	func IsGood(score int, isDebug bool) (isValid bool) {
	    isValid = true
	    if isDebug {
	        return // return isValid
	    }
	    return score >= 60
	}
	func main() {
	    fmt.Println(IsGood(65, false))
	    fmt.Println(IsGood(40, true))
	}
```

# §2 常用库

### §2.1 `fmt`

`fmt`是Go自带的输入输出格式化库。它提供了以下方法：

```shell
$ go doc --short fmt
	func Fprint(w io.Writer, a ...any) (n int, err error)
	func Fprintf(w io.Writer, format string, a ...any) (n int, err error)
	func Fprintln(w io.Writer, a ...any) (n int, err error)
	func Fscan(r io.Reader, a ...any) (n int, err error)
	func Fscanf(r io.Reader, format string, a ...any) (n int, err error)
	func Fscanln(r io.Reader, a ...any) (n int, err error)
	func Print(a ...any) (n int, err error)
	func Printf(format string, a ...any) (n int, err error)
	func Println(a ...any) (n int, err error)
	func Scan(a ...any) (n int, err error)
	func Scanf(format string, a ...any) (n int, err error)
	func Scanln(a ...any) (n int, err error)
	func Sprint(a ...any) string
	func Sprintf(format string, a ...any) string
	func Sprintln(a ...any) string
	func Sscan(str string, a ...any) (n int, err error)
	func Sscanf(str string, format string, a ...any) (n int, err error)
	func Sscanln(str string, a ...any) (n int, err error)
# ......
```

| 输入变量类型    | 格式化控制符    | 输出类型                                                                                  | 例子                     |
| --------- | --------- | ------------------------------------------------------------------------------------- | ---------------------- |
| 任意值       | `%v`      | 变量值。`bool`为`%t`、`int`系为`%d`、`float`系为`%g`、`string`系为`$s`、`chan`系为`%p`、`pointer`系为`%p` |                        |
| 任意值       | `%+v`     | 变量值，针对结构体额外输出字段名                                                                      | `{Name:Alice}`         |
| 任意值       | `%#v`     | 变量类型和变量值                                                                              | `main.a{Name:"Alice"}` |
| 任意值       | `%T`      | 变量类型                                                                                  |                        |
|           | `%%`      | `%`字符本身                                                                               |                        |
| `bool`    | `%t`      | `true`/`false`                                                                        |                        |
| `int`系    | `%c`      | Unicode解码得到的单个字符，由单引号包括且经过转义                                                          | `13`→`'\r'`            |
| `int`系    | `%q`      | Unicode解码得到的单个字符                                                                      | `13`→`⏎`               |
| `int`系    | `%b`      | 二进制数字                                                                                 |                        |
| `int`系    | `%o`      | 八进制数字                                                                                 |                        |
| `int`系    | `%O`      | 八进制数字，带有`0o`前缀                                                                        |                        |
| `int`系    | `%d`      | 十进制数字                                                                                 |                        |
| `int`系    | `%x`      | 十六进制数字，字母小写                                                                           |                        |
| `int`系    | `%X`      | 十六进制数字，字母大写                                                                           |                        |
| `int`系    | `%U`      | Unicode编码                                                                             | `U+1234`               |
| `float`系  | `%b`      | 以`2`为底的科学记数法，用`p`分隔有效数字和指数                                                            |                        |
| `float`系  | `%e`      | 以`10`为底的科学记数法，用`e`分隔有效数字和指数                                                           |                        |
| `float`系  | `%E`      | 以`10`为底的科学记数法，用`E`分隔有效数字和指数                                                           |                        |
| `float`系  | `%f`/`%F` | 十进制小数                                                                                 |                        |
| `float`系  | `%g`      | 自动根据数值大小，选择`%e`或`%f`                                                                  |                        |
| `float`系  | `%G`      | 自动根据数值大小，选择`%E`或`%F`                                                                  |                        |
| `float`系  | `%x`      | 以`2`为底的科学计数法，有效数字用十六进制表示，所有字母为小写，指数用十进制表示，用`p`分隔有效数字和指数                               |                        |
| `float`系  | `%X`      | 以`2`为底的科学计数法，有效数字用十六进制表示，所有字母为大写，指数用十进制表示，用`p`分隔有效数字和指数                               |                        |
| `string`系 | `%s`      | 特殊字符被转义后的字符串                                                                          |                        |
| `string`系 | `%q`      | 以Unicode编码输出字符串，由双引号包裹                                                                |                        |
| `string`系 | `%x`      | 输出十六进制字节流，字母均为小写                                                                      |                        |
| `string`系 | `%X`      | 输出十六进制字节流，字母均为大写                                                                      |                        |
| 任意值       | `%p`      | 变量的带`0x`前缀的十六进制地址                                                                     |                        |

`fmt`的格式化控制符支持显式实参索引，可以使用类似`%[数字]s`的方式决定引用指定位置的形参，从`1`开始索引：

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    fmt.Printf("%[2]s %[1]s", "World", "Hello")
	}

$ go run main.go
	Hello World
```

## §2.2 `strconv`

`strconv`库用于在字符串和数值之间相互转化。

## §2.3 `sort`

`sort`包用于对切片进行排序。

```shell
$ go doc --short sort
	func Find(n int, cmp func(int) int) (i int, found bool)
	func Float64s(x []float64)
	func Float64sAreSorted(x []float64) bool
	func Ints(x []int)
	func IntsAreSorted(x []int) bool
	func IsSorted(data Interface) bool
	func Search(n int, f func(int) bool) int
	func SearchFloat64s(a []float64, x float64) int
	func SearchInts(a []int, x int) int
	func SearchStrings(a []string, x string) int
	func Slice(x any, less func(i, j int) bool)
	func SliceIsSorted(x any, less func(i, j int) bool) bool
	func SliceStable(x any, less func(i, j int) bool)
	func Sort(data Interface)
	func Stable(data Interface)
	func Strings(x []string)
	func StringsAreSorted(x []string) bool
```

`sort`内置的方法会在原切片的基础上直接更改。

```shell
$ cat main.go
	package main
	import "fmt"
	import "sort"
	func main() {
	    a := []int{1, 4, 2, 3}
	    sort.Ints(a)
	    fmt.Println(a)
	}

$ go run main.go
	[1 2 3 4]
```