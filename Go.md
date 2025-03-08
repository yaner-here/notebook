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

### §1.8.1 具名返回值

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

### §1.8.2 闭包

在闭包问题上，Go使用C++中Lambda的`[&]`机制：

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    a := 1
	    fn := func()(int){
	        a = 2
	        return a
	    }
	    fmt.Println("fn():", fn())
	    fmt.Println("a:", a)
	}

$ go run main.go
	fn(): 2
	a: 2
```

### §1.8.3 可变参数

可变参数指的是零个或多个相同残星的形参，可以在数据类型之前添加`...`前缀来声明，它必须是最后一个参数。

```go
package main
import "fmt"
func main() {
    Greet := func(names ...string){
        for _, name := range names {
            fmt.Println("Hello,", name)
        }
    }
    Greet("Alice", "Bob", "Carol")
    Greet(names...) // 这两种方式效果等价
		// Hello, Alice
		// Hello, Bob
		// Hello, Carol
}
```

### §1.8.4 延迟函数调用

在函数的调用之前使用`defer`关键字，可以将函数的调用延迟到当前所在函数恰好`return`之前。

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    Greet := func(msg string){
	        fmt.Println(msg)
	    }
	    defer Greet("First")
	    Greet("Second")
	    return
	}

$ go run main.go
	Second
	First
```

`defer`常常用于必须执行，不必现在执行函数调用的场景。例如打开一个文件后，我们最终要关闭文件，但是不必现在关闭，因为现在可能需要进行其它的I/O操作。

```go
import (
    "io/ioutil"
    "os"
)
func ReadFile(filePath string)([]byte, error){
    f, err := os.Open(filePath)
    if err != nil {
        return nil, err
    }
    defer f.Close() // 保证在return之前关闭文件
    b, err := ioutil.ReadAll(f)
    if err != nil {
        return nil, err
    }
    return b, nil
}
```

如果一个函数体中存在多个延迟函数调用，则按照栈式时间顺序执行（也就是先进后出）。**如果某个延迟函数调用抛出错误，则会继续执行后面的延迟函数调用，最终一起抛出错误**。`os.Exit()`、`log.Fatal()`除外。

```shell
$ cat main.go
	package main
	import "fmt"
	func main() {
	    defer fmt.Println("1")
	    defer panic(2)
	    defer fmt.Println("3")
	    defer panic(4)
	    defer fmt.Println("5")
	}

$ go run main.go
	5
	3
	1
	panic: 4
	panic: 2
```

需要注意的是：`defer`只能延迟函数调用的执行，而不能延迟函数的实参表达式的执行。这个过程有点类似于SQL语言的预处理，也就是说在`defer`声明完的一瞬间，参数就已经准备好了。为了解决这一问题，我们可以将函数实参的表达式换成一个匿名函数。

```shell
$ cat main.go
	package main
	import "fmt"
	import "time"
	func main() {
	    nowTime := time.Now()
	    defer fmt.Printf("[1] Time delay: %s\n", time.Since(nowTime))
	    defer func(nowTime time.Time) {
	        fmt.Printf("[2] Time delay: %s\n", time.Since(nowTime))
	    }(nowTime)
	    time.Sleep(50 * time.Millisecond)
	}

$ go run main.go
	[2] Time delay: 50.178617ms
	[1] Time delay: 72ns
```

### §1.8.5 `init()`函数

一个Go程序只能有一个`main()`，但是可以有若干个在`main()`之前执行的`init()`函数。Go的策略是：遍历当前模块路径下的所有文件（按字典序升序排列），按先后顺序执行所有出现的`init()`函数。

```go
package main
import "fmt"
func init() {
    fmt.Println("init: [1]") // 第一个执行
}
func init() {
    fmt.Println("init: [2]") // 第二个执行
}
func main() {
    fmt.Println("main: [3]") // 第三个执行
}
```

## §1.9 结构体

Go中的`type`类似于C++中的`typedef`。

初始化结构体时，如果不使用字段名，则必须按顺序提供所有的字段值。

```shell
$ cat main.go
	package main
	import "fmt"
	type User struct {
	    name string
	    age int32
	}
	func main() {
	    user1 := User{
	        name: "Alice",
	        age: 23,
	    }
	    fmt.Println("user1.name =", user1.name)
	
	    user2 := User{"Bob", 18}
	    fmt.Printf("user2: %+v", user2)
	}

$ go run main.go
	user1.name = Alice
	user2: {name:Bob age:18}
```

Go额外支持结构体标签的特性。结构体标签是一个形如`<name>:"<value>"`的字符串。

```go
type User struct {
	name string `json:"name"`
}
```

### §1.9.1 方法

C++中的结构体可以包含一个函数指针，在结构体的命名空间内定义一个方法。Go语言也提供了类似的语法糖，称为**方法**：

```go
package main
import "fmt"
type User struct {
    name string
    age int32
}
func (user User) String() string {
    return fmt.Sprintf("%s is %d years old.", user.name, user.age)
}
func main() {
    user := User{
        name: "Alice",
        age: 23,
    }
    // 以下两种方法等价
    // Alice is 23 years old.
    fmt.Println(user.String())
    fmt.Println(User.String(user))
}
```

方法与函数的定义相似，但是仍有细微的差别：

- 方法的调用必须绑定在自定义类型上，不能独立于结构体实例而调用。
- 方法不能使用泛型，函数可以。

方法只能定义在自定义类型上，不能定义在系统内置类型上。要绕过这一点，我们可以使用`type`给系统内置类型设置一个别名。

```go
// 报错: cannot define new methods on non-local type int
func (i int) Square() int {
    return i * i
}

// 正常
type MyInt int
func (i MyInt) Square() MyInt {
    return i * i
}
```

函数签名本身也是一种类型，可以通过`type`设置别名，并作为一种数据类型用于变量类型的声明。

```go
package main
import "fmt"
type StringGetter func() string // 返回string的函数类型
func Printer(fn StringGetter) {
    fmt.Println(fn())
}
func main() {
    Printer(func() string {
        return "Hello world"
    }) // Hello world
}
```

Go语言规定：**如果B结构体嵌入了A结构体，那么定义在A结构体上的方法C，也能用于B结构体。**

```go
package main
import "fmt"

type Man struct {
    Name string
    Age int
}
func (user Man) getName() (string) {
    return user.Name
}

type Chinese struct {
    Man
    province string
}

func main() {
    person := Chinese{}
    person.Name = "Alice"
    fmt.Println(person.getName()) // Alice
}
```

### §1.9.2 结构体别名

Go语言中不存在继承机制，只有结构体别名。结构体别名只会继承原结构体的所有字段，但是不包含原结构体的方法。

```go
package main
import "fmt"
type User struct {
    id int
    name string
}
type WebUser User
func (user User) GetUserName() string {
    return user.name
}
func main() {
    user_1 := User{1, "Alice"}
    user_2 := WebUser{2, "Bob"}
    fmt.Println(user_1.GetUserName()) // 正常
    fmt.Println(user_2.GetUserName()) // 报错(type WebUser has no field or method GetUserName)
}
```

## §1.10 指针

Go中的指针与C++基本相同，都使用`*`和`&`两个运算符，只不过Go对结构体指针不使用`->`。

```go
package main
import "fmt"
type User struct {
    id int
    name string
}
func changeUserID(user *User, new_id int) {
    user.id = new_id
}
func main() {
    user := User{1, "Alice"}
    fmt.Println("user.id =", user.id) // user.id = 1
    changeUserID(&user, 2)
    fmt.Println("user.id =", user.id) // user.id = 2
}
```

### §1.10.1 `new()`函数

Go中的`new()`函数类似于C语言中的`malloc()`，都返回给定数据类型的一个指针。

```go
package main
type User struct {
    id int
    name string
}
func main() {
	// 以下两种方法等价
    user1_pointer := &User{}
    user2_pointer := new(User)
}
```

### §1.10.2 空指针`nil`

在使用指针前，我们推荐检查是否为空指针。

```go
package main
import "fmt"
type User struct {
    id int
    name string
}
func main() {
    var user_pointer *User; // 缺省为零值，即nil
    fmt.Printf("user_pointer: %p\n", user_pointer) // user_pointer: 0x0
    if user_pointer == nil {
        fmt.Println("nil pointer isn't valid!") // 会被触发
    }
}
```

## §1.11 接口

如果两种结构体都有同名的字段，都有同名的方法，那么我们可以将这种共同点抽象成Go中的接口，它是对结构体的方法的共同点的一种抽象。接口只能包含方法，不能包含字段。

以下面的代码为例：两个结构体都有`Name`字段，但是函数无法接受两个不同类型的实参，即使我们只想调用它们相同的行为：

```go
package main
type Man struct {
	Name string
}
type Woman struct {
	Name string
}
func GetName(user Man) string {
	return user.Name
}
func main() {
	GetName(Woman{Name: "Alice"}) // 报错，类型不匹配
}
```

基于此，我们使用接口。只要一个结构体实现了接口中的所有方法，则自动判定为实现了该接口：

```go
package main
import "fmt"
type Man struct {
    Name string
}
type Woman struct {
    Name string
}
type Nameable interface {
    PrintName()
}
func PrintName(user Nameable) {
    user.PrintName()
}
func (user Man) PrintName() {
    fmt.Println(user.Name)
}
func (user Woman) PrintName() {
    fmt.Println(user.Name)
}
func main() {
    user_1 := Woman{Name: "Alice"}
    user_2 := Man{Name: "Bob"}
    PrintName(user_1) // Alice
    PrintName(user_2) // Bob
}
```

一个结构体可以实现多个接口：

```go
package main
import "fmt"
type User struct {
        Name string
}

type Nameable interface {
    PrintName()
}
func PrintName(user Nameable) {
    user.PrintName()
}
func (user User) PrintName() {
    fmt.Println(user.Name)
}

type Stringable interface {
    Stringify() string
}
func Stringify(user Stringable) string {
    return user.Stringify()
}
func (user User) Stringify() string {
    return fmt.Sprintf("User is %s", user.Name)
}

func main() {
    user := User{Name: "Alice"}
    PrintName(user) // Alice
    fmt.Println(Stringify(user)) // User is Alice
}
```

### §1.11.1 空接口

以下三种方式都能定义一个空接口。

```go
interface {}
type foo interface{}
any
```

由于接口是对结构体的抽象，所以任何数据类型都实现了空接口，反过来说，空接口可以表示所有数据类型。

### §1.11.2 嵌入接口

嵌入接口是若干个接口的并集。

```go
type Readable interface {
	Read() ([]byte, error)
}
type Writeable interface {
	Write(bytes []byte) (error)
}
type File interface {
	Readable
	Writeable
	Close() error
}
```

### §1.11.3 类型断言

在`any`型变量名的后面添加`.(类型名)`，可以让编译器将该变量强行视为指定的类型。如果实际上传入变量值不是所需类型，则后续在其基础上调用接口方法会在运行时会产生`panic`。为了解决这个问题，我们可以使用类型断言的第二个参数，判断断言是否成立。

```go
func Write(w any){
	writer, ok = writer.(io.Writer)
	if !ok {
		fmt.Errorf("Expected io.Writer, but got %T", w)
	}
}
```

### §1.11.4 异常处理

Go语言对异常的处理比较特殊——它认为错误只是一种特殊变量而已，通过`errors`接口表示。以下是两种等价的方式：

```go
package main
import "fmt"
import "errors"
func main() {
    err_1 := errors.New("Error: something wrong")
    err_2 := fmt.Errorf("Error: something wrong")
    fmt.Println(err_1) // Error: something wrong
    fmt.Println(err_2) // Error: something wrong
}
```

Go语言错误的处理更特殊——它由`panic()`引起，并且直接尝试`return`，在`return`之前会执行`defer`函数，这里我们可以使用`recover().(error)`捕获错误，从错误中恢复。

```go
package main
import "fmt"
func main() {
    defer func(){
        p := recover()
        if p == nil {
            return // 正常情况
        }
        if err, ok := p.(error); ok {
            fmt.Println("Catch an exception!", err)
            return // 普通的Exception
        }
        fmt.Println("Catch a panic!", p) // Panic
    }()
    panic("Panic triggered!\n")
}
```

### §1.11.5 自定义异常

自定义异常本质上是一种实现了`Error() string`方法的结构体，该结构体包含着报错相关的所有信息。

```go
package main
import (
        "fmt"
        "time"
)

type TableNotFoundErr struct {
    Key string
    Time time.Time
}
func (err TableNotFoundErr) Error() string {
    return fmt.Sprintf("[%s] Table can't find a key (%s)", err.Time, err.Key)
}

type ScoreMap map[string]int
func (m *ScoreMap) GetScore(name string) (int, error) {
    if m == nil {
        return -1, fmt.Errorf("map pointer is nil")
    }
    val, ok := (*m)[name]
    if !ok {
        return -1, TableNotFoundErr{
            Key: name,
            Time: time.Now(),
        }
    }
    return val, nil
}

func main() {
    scores := ScoreMap {
        "Alice": 100,
    }
    val, err := scores.GetScore("Bob")
    if err != nil {
        fmt.Println(err) // [2025-03-07 12:37:22.916369988 +0800 CST m=+0.000032415] Table can't find a key (Bob)
    } else {
        fmt.Println(val)
    }
}
```

### §1.11.6 错误包装与错误解包装

由于自定义错误本质上是结构体，因此我们可以在结构体字段设置新的错误，这种操作成为错误包装，逆操作称为错误解包装。需要用到`errors.Unwarp(error)`函数，它要求传入的`error`必须实现了`Unwrapper`接口中的`Unwrap() error`方法，否则会返回`nil`。这个接口不在`errors`库中定义，需要我们自己定义。

```go
package main

import (
        "errors"
        "fmt"
)

type Unwrapper interface {
    Unwarp()
}

type AError struct { err error }
func (err AError) Error() string { return fmt.Sprintf("AError: %s", err.err) }
func (err AError) Unwrap() error {
    if _, ok := err.err.(Unwrapper); ok {
        return errors.Unwrap(err.err)
    } else {
        return err.err
    }
}

type BError struct { err error }
func (err BError) Error() string { return fmt.Sprintf("BError: %s", err.err) }
func (err BError) Unwrap() error {
    if _, ok := err.err.(Unwrapper); ok {
        return errors.Unwrap(err.err)
    } else {
        return err.err
    }
}

func ErrorWrapper(err error) (error) {
    err = AError{err: err}
    err = BError{err: err}
    return err
}

func main() {
    err_1 := errors.New("This is an error")
    err_2 := ErrorWrapper(err_1)
    err_3 := errors.Unwrap(err_2)
    err_4 := errors.Unwrap(err_3)
    fmt.Println("err_1:", err_1) // err_1: This is an error
    fmt.Println("err_2:", err_2) // err_2: BError: AError: This is an error
    fmt.Println("err_3:", err_3) // err_3: AError: This is an error
    fmt.Println("err_4:", err_4) // err_4: This is an error
    if err_1 == err_4 {
        fmt.Println("Unwrap success.") // Unwrap success.
    }
}
```

## §1.12 泛型

请看下面这段Go代码——我们想设计一个针对`map[any]any`的通用函数，但是编译器告诉我们`map[int]int`不能直接转化为`map[any]any`。在不使用泛型的情况下，我们只能先把原`map[int]int`复制一份放到`map[any][any]`，传入函数中，将返回的`map[any][any]`再经过类型断言，复制一份放到`map[int]int`。

```go
package main
import "fmt"
func GetAllKeys(m map[any]any) []any {
	keys := make([]any, 0, len(m))
	for key := range m {
		keys = append(keys, key)
	}
	return keys
}
func main() {
	a := map[int]int {
		1: 1,
		2: 4,
		3: 9,
	}
	b := GetAllKeys(a) // cannot use a (variable of type map[int]int) as map[any]any value in argument to GetAllKeys
}
```

Go语言提供了泛型，其语法为`func 函数名[泛型](形参)(返回值){}`。

```go
package main
import "fmt"
func GetAllKeys[K int, V any](m map[K]V) []K {
	keys := make([]K, 0, len(m))
	for key := range m {
		keys = append(keys, key)
	}
	return keys
}
func main() {
	a := map[int]int {
		1: 1,
		2: 4,
		3: 9,
	}
	b := GetAllKeys(a)
	fmt.Println(b) // [1 2 3]
}
```

泛型也是可以实例化的。

```go
package main
import "fmt"
func GetAllKeys[K int, V any](m map[K]V) []K {
	keys := make([]K, 0, len(m))
	for key := range m {
		keys = append(keys, key)
	}
	return keys
}
func main() {
	a := map[int]int {
		1: 1,
		2: 4,
		3: 9,
	}
	fn := GetAllKeys[int, int] // 泛型实例化
	b := fn(a)
	fmt.Println(b)
}
```

### §1.12.1 类型约束

泛型中的数据类型不一定非要是传统数据类型或结构体，也可以是接口，并且通过接口表示约束关系。**类型约束的对应只能是具体变量值**。

```go
package main
import "fmt"
type Comparable interface { // Comparable可以是下面数据类型的任意一个
	int | int8 | int16 | int32 | float32 | float64
}
func GetAllKeys[K Comparable, V any](m map[K]V) []K {
	keys := make([]K, 0, len(m))
	for key := range m {
		keys = append(keys, key)
	}
	return keys
}
func main() {
	a := map[int]int {
		1: 1,
		2: 4,
		3: 9,
	}
	fn := GetAllKeys[int, int]
	b := fn(a)
	fmt.Println(b)
}
```

这样做有一个问题：对于基本数据类型的别名，接口不会将其视为接口中的数据类型，我们真正感兴趣的是它的底层类型，可以使用`~`获取。

```go
package main
import "fmt"
type MyInt int // 定义一个基本数据类型的别名
type Comparable interface {
	~int | ~float32 // ~获取底层类型
}
func GetAllKeys[K Comparable, V any](m map[K]V) []K {
	keys := make([]K, 0, len(m))
	for key := range m {
		keys = append(keys, key)
	}
	return keys
}
func main() {
	a := map[MyInt]MyInt {
		1: 1,
		2: 4,
		3: 9,
	}
	fn := GetAllKeys[MyInt, MyInt]
	b := fn(a)
	fmt.Println(b)
}
```

### §1.12.2 方法约束

**方法约束的对象只能是具体的接口**。如果强行对变量使用，即断言某个变量实现了接口中的方法，则会编译时报错`invalid operation: 变量名(variable of type 变量类型) is not an interface`。我们无需对变量使用方法约束，因为编译器会自己执行方法约束。

类型约束和方法约束都是`interface`，但两者不能出现在同一个接口中。

```go
type MapKey interface {
	constraints.Ordered | fmt.Stringer
} // 报错: cannot use fmt.Stringer in union (fmt.Stringer contains methods)
```

## §1.13 通道

Go语言内部设计了一套并发模型，称为`goroutine`。得益于其设计，我们可以轻松地一次性运行数百万个`goroutine`，而且无需也不可能限制其内存配额与调度策略。

通道时`goroutine`之间用于通信的一种机制。一个通道只能发送和接受相同类型的值，以同步方式传输，可以无缓冲或带缓冲，可以单向或双向。

要声明一个某种数据类型的通道，我们需要在数据类型之前使用`chan`关键字，使用`make()`函数创建。类似于C++中的流使用`>>`和`<<`运算符，Go也对通道使用`->`和`<-`运算符。

```shell
$ cat main.go
	package main
	import "log"
	func Repeater(name string, channel chan string){
		msg := <-channel
		log.Println("[Repeater()] received a message:", msg)
		log.Println("[Repeater()] sending a message:", msg)
		channel <- msg
	}
	
	func main() {
		channel := make(chan string)
		defer close(channel) // 程序退出时关闭通道
		go Repeater("Alice", channel) // 创建一个goroutine
	
		msg := "Hello world"
		log.Println("[main()] sending a message:", msg)
		channel <- msg // 一直阻塞，除非channel读入
		msg = <-channel // 一直阻塞，除非channel输出
		log.Println("[main()] receive a message", msg)
	}

$ go run main.go
	2025/03/08 11:24:01 [main()] sending a message: Hello world
	2025/03/08 11:24:01 [Repeater()] received a message: Hello world
	2025/03/08 11:24:01 [Repeater()] sending a message: Hello world
	2025/03/08 11:24:01 [main()] receive a message Hello world
```

为了在`goroutine`中持续的监听通道，我们通常使用`for range`语句。当通道被关闭时，`range`就能跳出循环。

```shell
$ cat main.go
	package main
	import "log"
	func Repeater(name string, channel chan string){
		for msg := range channel{
			log.Println("[Repeater()] received a message:", msg)
			log.Println("[Repeater()] sending a message:", msg)
			channel <- msg
		}
		log.Println("[Repeater()] quit")
	}
	
	func main() {
		channel := make(chan string)
		defer close(channel) // 程序退出时关闭通道
		go Repeater("Alice", channel) // 创建一个goroutine
	
		msg := "hello"
		log.Println("[main()] sending a message:", msg)
		channel <- msg
		msg = <-channel
		log.Println("[main()] receive a message", msg)
		
		msg = "world"
		log.Println("[main()] sending a message:", msg)
		channel <- msg
		msg = <-channel
		log.Println("[main()] receive a message", msg)
	}
$ go run main.go
	2025/03/08 11:35:55 [main()] sending a message: hello
	2025/03/08 11:35:55 [Repeater()] received a message: hello
	2025/03/08 11:35:55 [Repeater()] sending a message: hello
	2025/03/08 11:35:55 [main()] receive a message hello
	2025/03/08 11:35:55 [main()] sending a message: world
	2025/03/08 11:35:55 [Repeater()] received a message: world
	2025/03/08 11:35:55 [Repeater()] sending a message: world
	2025/03/08 11:35:55 [main()] receive a message world
```

对于多个通道而言，我们经常使用`select`关键字，配合`for`与`switch`语句，来实时处理当前已经准备好的通道。

```go
func Receiver(line_1 chan string, line_2 chan string, quit chan bool) {
	for {
		select {
			case msg := <-line_1:
				log.Println("[Line 1] receive:", msg)
			case msg := <-line_2:
				log.Println("[Line 2] receive:", msg)
			case <-quit:
				log.Println("Exit")
				return
		}
	}
}
```

如果多个`goroutine`同时监听同一个通道，那么对于通道的每一次读写，只有一个`goroutine`能收到。

`<-通道`的返回值有两个，第一个是正常值，第二个是通道是否开启的布尔值。如果通道已关闭，则返回值依次为零值和`false`。

一个通道只能用`close()`关闭一次，否则会引起`panic`。如果向一个已经关闭的通道写入数据，也会引起`panic`。

### §1.13.1 单向通道

默认情况的通道是双向的。声明单向通道时，要在数据类型前面的`chan`的前面再加上`<-`，或者在`chan`的后面再加上`<-`进行修饰。

```go
type OneDirectChannel struct {
	outChannel <-chan string
	inChannel chan<- string
}
```

例如使用单向通道作为`goroutine`的终止信号：

```go
package main

import (
	"log"
	"time"
)
func Listener(id int, quit <-chan struct{}) {
	log.Printf("[Listener %d] start", id)
	<-quit // 持续阻塞，直到收到quit，在这里是quit被关闭的时候
	log.Printf("[Listener %d] quit", id)
}
func main() {
	quitChannel := make(chan struct{})
	for i := 0; i < 3; i++ {
		go Listener(i, quitChannel)
	}
	time.Sleep(50 * time.Millisecond) // 等待goroutine初始化完毕
	log.Println("[main] closing quit")
	close(quitChannel)
	time.Sleep(50 * time.Millisecond) // 等待goroutine退出完毕
}
/*
2025/03/08 22:37:07 [Listener 2] start
2025/03/08 22:37:07 [Listener 0] start
2025/03/08 22:37:07 [Listener 1] start
2025/03/08 22:37:07 [main] closing quit
2025/03/08 22:37:07 [Listener 2] quit
2025/03/08 22:37:07 [Listener 0] quit
2025/03/08 22:37:07 [Listener 1] quit
*/
```

### §1.13.2 带缓冲通道

默认情况下，通道是没有缓冲区的。要创建一个带缓冲的通道，我们需要给`make(chan 数据类型, 缓冲区变量数)`传入第二个参数，它表示缓冲区能存储多少个变量。

```go
package main
import "fmt"
func main() {
	msgChannel := make(chan string, 2)
	msgChannel <- "hello"
	msgChannel <- "world"
	// msgChannel <- "world" // 这一行会导致阻塞与死锁
	fmt.Println("程序并未阻塞")
}
```

带缓冲通道不能保证消息的传递，因此开发者有义务保证程序推出前会排空通道。即使通道被关闭，我们依然可以从中读取值。

## §1.14 `Context`



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

## §2.4 `testing`

Go语言自带一个测试框架，通过`go test`命令行调用，它依赖于`testing`库。

```shell
$ go doc --short testing.T
	func (c *T) Cleanup(f func())
	func (t *T) Deadline() (deadline time.Time, ok bool)
	func (c *T) Error(args ...any)
	func (c *T) Errorf(format string, args ...any)
	func (c *T) Fail()
	func (c *T) FailNow()
	func (c *T) Failed() bool
	func (c *T) Fatal(args ...any)
	func (c *T) Fatalf(format string, args ...any)
	func (c *T) Helper()
	func (c *T) Log(args ...any)
	func (c *T) Logf(format string, args ...any)
	func (c *T) Name() string
	func (t *T) Parallel()
	func (t *T) Run(name string, f func(t *T)) bool
	func (t *T) Setenv(key, value string)
	func (c *T) Skip(args ...any)
	func (c *T) SkipNow()
	func (c *T) Skipf(format string, args ...any)
	func (c *T) Skipped() bool
	func (c *T) TempDir() string
```

测试要求的文件命名规则为：测试文件必须以`_test`结尾。例如`foo.go`对应的测试文件为`foo_test.go`。其中的测试函数必须使用`Test*(*testing.T)`的函数签名。

```shell
$ cat main.go
	package main
	import "fmt"
	func Square(n int) int {
	    return n + n;
	}
	func main() {
	    fmt.Println(Square(2))
	}

$ cat main_test.go
	package main
	import "testing"
	func TestSquare_Errorf(t *testing.T){
	    var key int = 3
	    actual := Square(key)
	    expected := 9
	    if actual != expected {
	        t.Errorf("expected %d but get %d", expected, actual)
	    }
	}

$ go test -v
	=== RUN   TestSquare_Errorf
	    main_test.go:8: expected 9 but get 6
	--- FAIL: TestSquare_Errorf (0.00s)
	FAIL
	exit status 1
	FAIL    demo    0.002s
```

### §2.4.1 `.T.Error()`/`.T.Fatal()`

在`testing.T`的各个方法中，`testing.T.Error()`及其格式化字符串版`testing.T.Errorf()`在触发时，只会输出信息，但是测试流程会正常进行。

`testing.T.Fatal()`及其格式化字符串版`testing.T.Fatalf()`则会直接退出测试流程，可以防止后续的测试流程使得程序抛出`panic`。

### §2.4.2 代码覆盖率

Go语言支持`go test`使用`-cover`或`-coverprofile=<文件路径>`来输出代码覆盖率信息。

```shell
$ go test
	--- FAIL: TestSquare_Errorf (0.00s)
	    main_test.go:8: expected 9 but get 6
	FAIL
	exit status 1
	FAIL    demo    0.001s

$ go test -cover
	--- FAIL: TestSquare_Errorf (0.00s)
	    main_test.go:8: expected 9 but get 6
	FAIL
	exit status 1
	FAIL    demo    0.001s

$ go test -coverprofile=coverage.out
	--- FAIL: TestSquare_Errorf (0.00s)
	    main_test.go:8: expected 9 but get 6
	FAIL
	coverage: 50.0% of statements
	exit status 1
	FAIL    demo    0.002s

$ cat coverage.out
	mode: set
	demo/main.go:3.24,5.2 1 1
	demo/main.go:6.13,8.2 1 0
```

`-coverprofile`生成的文件需要配合`go tool cover`，才能转换成人类可读的报告。

- `--func=<文件路径>`：统计函数的测试成功率，输出到`STDOUT`
- `--html=<文件路径> -o <输出路径>`：统计函数及其测试成功率，输出到`HTML`

### §2.4.3 `.T.Run()`

要在一个测试函数内使用多个测试样例，一种朴素的方法是使用表驱动测试——将所有测试用例放在一个匿名结构体的切片中，随后遍历这个切片即可。

```go
package main
import "testing"
func TestSquare_Errorf(t *testing.T){
    examples := []struct{
        key int
        expected int
    }{
        {key: 1, expected: 2},
        {key: 2, expected: 4},
        {key: 3, expected: 9},
    }
    for _, example := range examples {
        actual := Square(example.key)

        if actual != example.expected {
            t.Errorf("expected %d but get %d", example.expected, actual)
        }
    }
}
```

但是表测试驱动的问题是：我们难以定位到具体是哪一个测试用例出错，除非要额外在报错信息中指出当前测试用例的全部信息。为了解决这一问题，我们可以使用子测试——先使用`testing.T.Parallel()`初始化，然后对每一个测试用例使用`testing.T.Run()`。

```go
package main
import "fmt"
import "testing"
func TestSquare(t *testing.T){
    t.Parallel()
    examples := []struct{
        key int
        expected int
    }{
        {key: 1, expected: 2},
        {key: 2, expected: 4},
        {key: 3, expected: 9},
    }
    for _, example := range examples {
        t.Run(fmt.Sprintf("%d", example.key), func(t *testing.T){
            actual := Square(example.key)
            if actual != example.expected {
                t.Errorf("expected %d but get %d", example.expected, actual)
            }
        })
    }
}
```

```shell
$ go test -v
	=== RUN   TestSquare
	=== PAUSE TestSquare
	=== CONT  TestSquare
	=== RUN   TestSquare/1
	=== RUN   TestSquare/2
	=== RUN   TestSquare/3
	    main_test.go:21: expected 9 but get 6
	--- FAIL: TestSquare (0.00s)
	    --- PASS: TestSquare/1 (0.00s)
	    --- PASS: TestSquare/2 (0.00s)
	    --- FAIL: TestSquare/3 (0.00s)
	FAIL
	exit status 1
	FAIL    demo    0.001s
```

### §2.4.4 `.Short()`/`.T.Skip()`

假设有一些作用较小的测试，我们不希望每次测试都耗时执行，则可以使用Go提供的短测试。当命令行`go test`传入了`-short`参数后，`testing.Short()`就会返回`false`，给了我们判断的依据。我们还可以使用`testing.T.Skip()`输出相应的日志。

```go
func TestSquare(t *testing.T){
	if testing.Short() {
		t.Skip("Skipping in short mode.")
	}
}
```

### §2.4.5 `.T.Parallel()`

如果一个测试函数中调用了`testing.T.parallel()`方法，则该测试可以与其它测试并行执行，并行的进程数由`go test -p <NUM>`指定。也可以通过`--run <REGEX>`限定要执行的测试，使用`-timeout <NUM>`指定测试超时时间的毫秒数，使用`-failfast`在遇到第一处测试失败时就退出后续测试，使用`-count=<NUM>`决定每个测试至少应该执行的次数，用于禁用测试缓存。

### §2.4.6 `.TB.Helper()`/`.TB.Cleanup()`

有时我们编写的测试函数逻辑过于复杂，可能需要将一系列逻辑转移到其它函数中，成为测试辅助函数。直接像普通函数那样，定义一个测试辅助函数是可以的，但问题是：如果测试辅助函数发生`panic`，则报错的行号会执行测试辅助函数，这会让我们不知道究竟是测试函数的那一行调用了这个测试辅助函数。

```shell
$ cat main_test.go
	package main
	import (
	        "fmt"
	        "testing"
	)
	func copyValue(n int) int {
	    panic("Not implemented!")
	    return n
	}
	func TestSquare(t *testing.T){
	    t.Parallel()
	    examples := []struct{
	        key int
	        expected int
	    }{
	        {key: 1, expected: 2},
	        {key: 2, expected: copyValue(4)},
	        {key: 3, expected: 9},
	    }
	    for _, example := range examples {
	        t.Run(fmt.Sprintf("%d", example.key), func(t *testing.T){
	            actual := Square(example.key)
	            if actual != example.expected {
	                t.Errorf("expected %d but get %d", example.expected, actual)
	            }
	        })
	    }
	}

$ go test
	--- FAIL: TestSquare (0.00s)
	panic: Not implemented! [recovered]
		panic: Not implemented!
	
	goroutine 18 [running]:
	    ./main_test.go:18 +0x27
	testing.tRunner(0xc00014e4e0, 0x564168)
	    go/src/testing/testing.go:1690 +0xf4
	created by testing.(*T).Run in goroutine 1
	    go/src/testing/testing.go:1743 +0x390
	exit status 2
	FAIL    demo    0.003s
```

我们将测试函数中的`testing.*T`直接传给测试辅助函数的形参`testing.TB`，并在首行调用`tesing.TB.Helper()`，就能在测试的报错信息中忽略测试辅助函数的存在。

```shell
$ cat main_test.go
	package main
	import (
	        "fmt"
	        "testing"
	)
	func copyValue(tb testing.TB, n int) int {
	    tb.Helper()
	    tb.Fatal("Not implemented!")
	    return n
	}
	func TestSquare(t *testing.T){
	    t.Parallel()
	    examples := []struct{
	        key int
	        expected int
	    }{
	        {key: 1, expected: 2},
	        {key: 2, expected: copyValue(t, 4)},
	        {key: 3, expected: 9},
	    }
	    for _, example := range examples {
	        t.Run(fmt.Sprintf("%d", example.key), func(t *testing.T){
	            actual := Square(example.key)
	            if actual != example.expected {
	                t.Errorf("expected %d but get %d", example.expected, actual)
	            }
	        })
	    }
	}

$ go test
	--- FAIL: TestSquare (0.00s)
	    main_test.go:19: Not implemented!
	FAIL
	exit status 1
	FAIL    demo    0.001s
```

在所有测试均完成后，退出测试流程之前，我们可以使用`testing.TB.Clenaup(func)`注册一个退出事件，常常用于清理资源。**这与`defer`延迟执行的时机并不一样**。

```go
func copyValue(tb testing.TB, n int) int {
	tb.Helper()
	tb.Cleanup(func(){
		tb.Log("Exit event triggered!")
	})
	return n
}
```

## §2.5 `golang.org/x/exp/constraints`

`golang.org/x/exp/constraints`是为泛型设计的一个实验性质包，它定义了大部分泛型所需的约束接口。

```shell
$ go get golang.org/x/exp/constraints
	go: downloading golang.org/x/exp v0.0.0-20250305212735-054e65f0b394
	go: added golang.org/x/exp v0.0.0-20250305212735-054e65f0b394

$ go doc --short golang.org/x/exp/constraints
	type Complex interface{ ... }
	type Float interface{ ... }
	type Integer interface{ ... }
	type Ordered = cmp.Ordered
	type Signed interface{ ... }
	type Unsigned interface{ ... }
```

## §2.6 `os.signal`

`os.signal`包用于捕获Linux的系统信号。

`os.signal.Notify(c chan<- os.Signal, sig ...os.Signal)`用于监听Linux中的某些特定信号，并将其作为`os.Signal`接口传入通道`c`中。

下面的代码用于捕捉Linux的`sigint`信号。注意：**这里必须使用带缓冲通道，否则可能会在Linux发送信号时，Go未准备好接受，从而错过信号**。

```shell
$ cat main.go
	package main
	import (
		"fmt"
		"os"
		"os/signal"
	)
	func main() {
		sigChannel := make(chan os.Signal, 1)
		signal.Notify(sigChannel, os.Interrupt)
	
		fmt.Println("awaiting for signal ...")
		sig := <-sigChannel
		fmt.Println("\nget signal:", sig)
	}

$ go run main.go
	awaiting for signal ...
	^C
	get signal: interrupt
```

下面的代码存在问题：如果发送`sigint`信号的时机刁钻，那么有可能会出现`goroutine`无法及时结束的情况。

```go
package main

import (
	"fmt"
	"os"
	"os/signal"
	"time"
)
type Monitor struct{}
func (m Monitor) Start(quit chan struct{}) {
	tick := time.NewTicker(50 * time.Millisecond)
	defer tick.Stop()
	for {
		select {
			case <-quit:
				fmt.Println("[Monitor] quit")
				return
			case <-tick.C:
				fmt.Println("[Monitor] ticker check")
		}
	}
}
func main() {
	quitChannel := make(chan struct{})
	sigChannel := make(chan os.Signal, 1)
	signal.Notify(sigChannel, os.Interrupt)

	m := Monitor{}
	go m.Start(quitChannel)

	<-sigChannel
	close(quitChannel)
}
// [Monitor] ticker check
// ^C[Monitor] ticker check
```

基于此，我们需要给`goroutine`充足的时间来退出，最好是创建一个依赖关系，使得`goroutine`退出后`main()`才能`return`。这个依赖关系可以用一个只读通道实现：

```go
package main

import (
	"fmt"
	"os"
	"os/signal"
	"time"
)
type Monitor struct { done chan struct{} }
func (m Monitor) Done() <-chan struct{} { return m.done }
func (m Monitor) Start(quit chan struct{}) {
	tick := time.NewTicker(50 * time.Millisecond)
	defer tick.Stop()
	for {
		select {
			case <-quit:
				fmt.Println("[Monitor] quit")
				return
			case <-tick.C:
				fmt.Println("[Monitor] ticker check")
		}
	}
}

func main() {
	quitChannel := make(chan struct{})
	sigChannel := make(chan os.Signal, 1)
	signal.Notify(sigChannel, os.Interrupt)

	m := Monitor{}
	go m.Start(quitChannel)

	<-sigChannel
	close(quitChannel)
	<-m.Done()
}
```

如果`m.Done()`迟迟不返回，我们可以使用`select`语句和`time.After()`通道做一个短接，表示超时非正常退出：

```go
	select {
		case <-m.Done():
			os.Exit(0)
		case <-time.After(500 * time.Millisecond):
			fmt.Println("Exit timeout")
			os.Exit(1)
	}
```