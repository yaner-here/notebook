# PHP





# §1 语法基础



数据类型

|  基本类型  |        类型检查函数        |                      含义                      |
| :--------: | :------------------------: | :--------------------------------------------: |
| `Boolean`  |        `is_bool()`         |                     布尔值                     |
| `Integer`  | `is_integer()`/`is_Long()` |                      整数                      |
|  `Double`  |       `is_double()`        |                     浮点数                     |
|  `String`  |       `is_string()`        |                     字符串                     |
|  `Object`  |       `is_object()`        |                      对象                      |
|  `Array`   |        `is_array()`        |                      数组                      |
| `Resource` |      `is_resource()`       | 识别和使用外部资源的句柄（例如数据库、文件等） |
|   `Null`   |        `is_null()`         |                 未被赋值时的值                 |





# §3 面向对象

2004年，PHP 5.0正式发布，支持面向对象编程的所有特性。

## §3.1 类与对象

在PHP中，类的声明和实例化语句与其它语言非常相似：

```php
class Commodity {

}
$obj1 = new Commodity();
$obj2 = new Commodity();
var_dump($obj1);
	// 输出"object(CustomizeClass)[1]"
var_dump($obj2);
	// 输出"object(CustomizeClass)[2]"
```

> 注意：在PHP 5.1之前，`print(Object)`等价于`var_dump(Object)`，两者都会输出一个包含对象实例的字符串。然而从PHP 5.2开始，`print()`只能接受字符串类型的参数，不再支持对象，强行调用`print(Object)`会触发`Catchable fatal error: Object of class ... could not be converted to string`的错误，除非这个类本身定义了`__toString()`方法。

可以给属性添加`public`、`protected`、`private`修饰符（缺省为`public`）：

```php
class Commodity {
	public $name = "default commodity name";
    protected $inventory = 100;
    private $origin = "America";
    public function getOrigin(){
    	return $this->origin;
    }
}
$product = new Commodity();
$product->name = "Apple";
print($product->name);
	// 输出"Apple"
print($product->inventory);
	// 输出"Fatal error: Cannot access protected property Commodity::$inventory"
print($product->origin);
	// 输出"Fatal error: Cannot access private property Commodity::origin"
```

| 修饰词           | 类内部 | 子类内部 | 全局 |
| :--------------- | :----: | :------: | :--: |
| `public`（默认） |   √    |    √     |  √   |
| `protected`      |   √    |    √     |      |
| `private`        |   √    |          |      |

非常奇妙的是，PHP不强制要求事先在类的定义中声明所有属性，而是允许动态地向对象添加属性：

```php
$product->price = 9.9;
print("商品单价：{$product->price}");
	// 输出"商品单价：9.9"
```

## §3.2 构造方法

> 注意：在PHP 5之前的版本中，构造方法的名称必须与类名相同，这一点类似于C++和Java。在PHP 7之后的版本中，构造方法的名称只有`__construct()`这一种，这一点类似于Python的`__new__()`。

```php
class Commodity {
	public $name;
    protected $inventory;
    private $origin;
    public function __construct($name,$inventory,$origin){
    	$this->name = $name;
        $this->inventory = $inventory;
        $this->origin = $origin;
    }
}
$product = new Commodity("Apple","100","9.9")
```

## §3.3 弱类型检查/强类型检查

我们知道，C++与Java中对参数的类型有明确的限制，而PHP 5也引入了类类型声明，本质上是强类型声明。

```php
function printCommodity(Commodity $product){
    print($product->name);
}
printCommodity("This is a string");
	// 输出"TypeError: Argument 1 passed to printCommodity()" must be an instance of Commodity, String given, called in ......
```

自PHP 7开始，类型检查默认为为弱类型检查。这使得上述代码的确限制了参数类型，但是没有完全限制。因为PHP的默认类型转换功能比其他语言强了太多了：因为字符串可以隐式转换为整数、浮点数和布尔值：

```php
function printScore(int $score){
    print("你的分数为{$score}分");
}
printScore("100");
	// PHP 5输出"Argument 1 passed to printScore() must be an instance of int, string given"
	// PHP 7输出”你的分数为100分“

function printIsCorrect(bool $isCorrect){
	$isCorrect ? print("回答正确！") : print("回答错误！");
}
printIsCorrect("false");
	// PHP 5输出" Argument 1 passed to printIsCorrect() must be an instance of bool, string given"
	// PHP 7输出"回答正确！"
```

PHP 7提供了`declare(strict_types=1)`以启用强类型检查。这个语句必须在PHP程序的第一行，并且在调用它的PHP程序内声明，而不是定义它的地方声明。

PHP支持的类型声明如下所示：

|  类型声明  |       弱类型检查       | 起始支持版本 |
| :--------: | :--------------------: | :----------: |
|  `array`   |          数组          |     5.1      |
|   `int`    |         整数和         |     7.0      |
|  `float`   |      浮点数、整数      |     7.0      |
| `callable` | 可调用代码（匿名函数） |     5.4      |
|   `bool`   |         布尔值         |     7.0      |
|  `string`  |         字符串         |     5.0      |
|   `self`   |     指向自己的引用     |     5.0      |
|  [类类型]  |     类或接口的类型     |     5.0      |
|   `void`   |         `null`         |     7.1      |

## §3.4 继承

PHP中的继承使用关键字`extends`。

```php
class Commodity {
	public $name;
    protected $inventory;
    private $origin;
    protected function __construct(string $name,int $inventory,string $origin){
        $this->name = $name;
        $this->inventory = $inventory;
        $this->origin = $origin;
    }
}
class BookCommodity extends Commodity{
    public $totalPage;
    public function __construct(string $name,int $inventory,string $origin,int $totalPage){
        parent::__construct($name,$inventory,$origin);
        $this->totalPage = $totalPage;
    }
    public function printName(){
        print($this->name);
    }
}
$book = new BookCommodity("PHP",100,"",123);
$book->printName();
```

> 注意：在父类中可以直接使用`$param`调用定义在父类中的变量，不必使用`$this->param`的形式，这一点类似于Java。但是不能在子类中直接使用父类的变量`$param`，必须通过`$this->param`或`parent::$param`调用。

## §3.5 常量

PHP支持将类内的字段设为常量，而且不需要以`$`开头，习惯全为大写字母：

```php
class ErrorCode {
	static const UNKNOWN = 0;
    static const NETWORK_404 = 1;
    static const NETWORK_403 = 2;
    static const TIME_EXCEEDED = 3;
}
function sendErrorCode(){
	print(ErrorCode::TIME_EXCEEDED);
}
```

## §3.6 抽象类

抽象类由关键字`abstract`定义，本身无法被实例化，除非其子类实现了抽象类声明的所有方法，不然其子类也不能被实例化。

当一个类显式地被`abstract`修饰，那么这个类即使不含任何抽象方法，也不能被实例化。

```php
abstract class Person {
    protected $name;
    public function setName(string $name){
        $this->name = $name;
    }
    abstract public function print();
}
class PrintablePerson extends Person{
    public function print(){
        print("姓名:".$this->name);
    }
}
```

## §3.7 接口

接口的关键字是`interface`和`implements`与抽象类相比，接口只能声明方法，而不能实现方法。

```php
interface Printable {
    public function print():void;
    public function getPrintString():string;
}
class Person implements Printable{
    protected $name;
    public function setName(string $name){
        $this->name = $name;
    }
    public function print():void{
        print($this->getPrintString());
    }
    public function getPrintString():string{
        return "姓名:".$this->name;
    }
}
$person = new Person();
$person->setName("Alice");
$person->print();
```

## §3.8 trait

继承和接口都能复用代码。然而继承限制类与类之间必须存在继承关系，接口只能复用方法的声明，而不能复用方法的定义。

假设遇到下面的情况：在一个电商平台中，买家、卖家和电商部门都需要计算某件商品打折之后的价格。但是这三方使用的折扣不同，卖家折扣减去买家折扣等于电商部门的获利。显然双方调用的这个方法，声明一样，都是`getPrice(折扣，原价)`，定义也一样，都是当前价格乘以折扣百分比。怎么实现呢？

- 如果用继承的思想，那么首先要将买家、卖家和电商部门看成三个子类，然后尝试提取他们的共性，找出父类。把什么当成父类才合适呢？如果是`Person`的话，电商部门是人的集合，并不能当成独立的个人看待。借用法律的概念，这三者应该归纳到“主体”这一概念，其学术翻译为`Entity`。这只是一个普通的电商系统，却引入了一个毫不相关的"主体"父类，于是我们就得到了这么一个别扭的继承关系：

  ```mermaid
  graph TB
  	subgraph Entity
  		EntityGetDiscount["static getPrice(int discountPercentage,float originalPrice)<br>return discountPercentage × originalPrice ÷ 100;"]
  	end
  	EntityGetDiscount-->Buyer
  	EntityGetDiscount-->Seller
  	EntityGetDiscount-->Platform
  ```

- 如果用接口的思想，那么新建一个`PriceCalculatable`接口，声明该方法，然后在三个类中分别定义一遍，造成了代码的重复。

在Java中，我们通用的解决方法是定义一个独立的类，将"接口"中的方法全部搬到这个独立的类中实现，然后所有的类就能全局调用这个类中的方法：

```java
public class PriceCalculator {
	public static float getPrice(int discountPercentage,float originalPrice){
        return discountPercentage * originalPrice / 100;
    }
}
public class Buyer/Seller/Platform{
	public static void main(String[] args){
    	System.out.println(PriceCalculator.getPrice(80,100));
    }
}
```

这种类的特殊之处在于：我们不需要对其实例化。怎么表示这一特性呢？用`abstract`修饰肯定不行，这是对抽象类的滥用。Java对这一问题束手无策，但是PHP在`class`、`interface`的基础上加入了`trait`这一概念，专门用来表示这种“不用实例化”的、能同时声明和定义方法的、可以多重继承的纯功能“接口”。

```php
trait PriceUtilities {
    public function getPrice(int $discountPercentage,float $originalPrice):float{
        return $discountPercentage * $originalPrice / 100;
    }
}
class Buyer/Seller/Platform {
    use PriceUtilities;
}
$product = new Buyer();
print($product->getPrice(80,19.9)); // 输出"15.92"
```

多个trait包含的同名方法会引起命名冲突，在编译时报错：

```php
trait CatAction {
    public function greet(){print("Meow~");}
}
trait DogAction {
    public function greet(){print("Woof!");}
}
class Pet {
    use CatAction,DogAction;
		// 报错输出"Trait method greet has not been applied, because there are collisions with other trait methods on Pet"
}
```

我们可以用`insteadof`关键字强行多选一，然后用`as`关键字给其它方法起别名以供调用：

```php
trait CatAction{...}
trait DogAction{...}
class Pet {
    use CatAction,DogAction{
        CatAction::greet insteadof DogAction;
        DogAction::greet as dog_greet;
    }
}
$pet = new Pet();
$pet->greet();
	// 输出"Meow~"
$pet->dog_greet();
	// 输出"Woof!"
```

`as`关键字还可以强行改变`trait`中的访问权限：

```php
trait SecretTrait { private function secretFunction(){print "secret function";} }
class MyClass {
    use SecretTrait;
}
$obj = new MyClass();
$obj->secretFunction();
	// 输出错误"Call to private method"
```

```php
trait SecretTrait { private function secretFunction(){print "secret function";} }
class MyClass {
    use SecretTrait{
        SecretTrait::secretFunction as public;
    }
}
$obj = new MyClass();
$obj->secretFunction();
	// 输出"secret function"
```

## §3.9 延迟静态绑定

下面的这段工厂模式的代码存在着代码重复的问题：

```php
class Animal {
    public $name;
}
class Cat extends Animal {
    private function __construct(string $name){
        $this->name = $name;
    }
    public static function createInstance(string $name):Cat{
        return new Cat($name);
    }
}
class Dog extends Animal {
    private function __construct(string $name){
        $this->name = $name;
    }
    public static function createInstance(string $name):Dog{
        return new Dog($name);
    }
}
```

我们思路是将这些子类中的函数迁移到父类中。但是下面的代码会报错：

```php
class Animal {
    public $name;
    private function __construct(string $name){
        $this->name = $name;
    }
    public static function createInstance(string $name):Animal{
        return new self($name);
    }
}
class Cat extends Animal{}
class Dog extends Animal{
    public function greet(){print("Woof!");}
}
$dog = Dog::createInstance("Hello");
$dog->greet();
    // 输出错误"Uncaught Error: Call to undefined method Animal::greet()"
```

这是因为`self`指向的是引用该关键字的`DomainObject`，而不是对其进行调用的`Document`。PHP 5.3引入了延迟静态绑定，用`static`代替`self`：

```php
class Animal {
    public $name;
    private function __construct(string $name){
        $this->name = $name;
    }
    public static function createInstance(string $name):Animal{
        return new static($name); // 更改了此处
    }
}
class Cat extends Animal{}
class Dog extends Animal{
    public function greet(){print("Woof!");}
}
$dog = Dog::createInstance("Hello");
$dog->greet();
	// 输出"Woof!"
```

再例如下面的代码：

```php
abstract class Book {
    private $group;
    public function __construct(){
        // $this->group = self::getDefaultGroup();
        // $this->group = static::getDefaultGroup();
    }
    public static function getDefaultGroup():string{
        return "Default";
    }
    public function getGroup():string{
        return $this->group;
    }
}
class Fiction extends Book {
    public static function getDefaultGroup():string{
        return "Fiction";
    }
}
$fiction = new Fiction();
print($fiction->getGroup());
    // self->gerDefaultGroup()输出"Default"
	// static::getDefaultGourp()输出"Fiction"
```

## §3.10 异常处理

PHP 5引入了异常这一概念，类似于Java中的``Exception`和`Error`。

| `Exception`方法名  | 作用                                   |
| ------------------ | -------------------------------------- |
| `getMessage()`     | 获取Exception消息字符串                |
| `getCode()`        | 获取Exception错误代码                  |
| `getFile()`        | 获取发生异常的文件                     |
| `getLine()`        | 获取发生异常额行号                     |
| `getPrevious()`    | 获取一个嵌套异常对象                   |
| `getTrace()`       | 获取一个包含方法调用跟踪信息的多维数组 |
| `getTraceAsString` | 获取`getTrace()`的字符串版本           |
| `__toString()`     | 将Exception实例转为字符串              |

| `Error`子类           | 作用                   |
| --------------------- | ---------------------- |
| `ArithmeticError`     | 数学运算错误           |
| `AssertionError`      | `assert()`断言失败错误 |
| `DivisionByZeroError` | 除以0错误              |
| `ParseError`          | `eval()`语句解析错误   |
| `TypeError`           | 传参类型不匹配错误     |



```php
function isFileExist(string $filePath){
    try{
        if(!file_exists($file)){
        	throw new Exception("File '{$file}' doesn't exist.");
    	}
    } catch(Exception e) {
        print("文件未找到");
    } finally {
        
    }
}
```

PHP也同样支持创建Exception的子类：

```
class FileNotFoundException extends Exception{
    
}
```

## §3.11 final

被`final`修饰的类无法被继承，被`final`修饰的方法无法被重写：

```php
final class A {}
class B extends A {}
	// 输出错误"Class IllegalCheckout may not inherit from final class A"
```

```php
class A{
    public final function func(){}
}
class B extends A {
    public function func(){}
    	// 输出错误"Cannot override final method A::func()"
}
```

## §3.12 拦截器

设想一个这样的函数`getParameter(string $parameter)`，当类中存在该变量时就返回变量，不存在时就返回`null`。要在Java做到这一点，必须手写一遍反射和异常处理的轮子。而PHP将其封装成了拦截器：

| 拦截器方法                         | 作用                                  |
| ---------------------------------- | ------------------------------------- |
| `__get($property)`                 | 尝试访问未定义属性时被调用            |
| `__set($property,$value)`          | 尝试对未定义属性赋值时被调用          |
| `__isset($property)`               | 尝试对未定义属性调用`isset()`时被调用 |
| `__unset($property)`               | 尝试对未定义属性调用`unset()`时被调用 |
| `__call($method,$arg_array)`       | 尝试调用未定义实例方法时被调用        |
| `__callStatic($method,$arg_array)` | 尝试调用未定义静态方法时被调用        |

```php
class Person {
    private $name;
    public function __get(string $property){
        $method = "get{$property}";
        if(method_exists($this,$method)){
            return $this->$method();
        }else{
            print("{$property}属性不存在！");
        }
    }
    public function setName(string $name):void{
        $this->name = $name;
    }
    public function getName():string{
        return $this->name;
    }
}
$person = new Person();
$person->setName("Alice");
print($person->__get("name"));
	// 输出"Alice"
print($person->getName());
	// 输出"Alice"
print($person->__get("age"));
	// 输出"age属性不存在！"
print($person->getAge());
	// 输出报错"Uncaught Error: Call to undefined method Person::getAge()"
```

## §3.13 析构方法

PHP 5引入了`__destruct()`，当对一个实例被`unset()`调用时就会执行。

```php
class A{
    public function __destruct(){
        print("Destructing instance...");
    }
}
$a = new A();
unset($a);
	// 输出"Destructing instance..."
```

## §3.14 `__clone()`

将一个实例赋给另一个变量是很常见的操作。PHP 4时，这一过程会导致对象被复制了一份，两个变量指向两个不同的实例。PHP 5以后，这一过程会导致两个变量指向同一个实例，如果要复制对象的话，必须使用`clone`关键字：

```php
class A{
    public $data = 1;
}
$a = new A();
print($a->data); // 输出"1"
$b = clone $a;
print($b->data); // 输出"1"
```

这一过程调用了类内的`__clone()`方法，我们可以重写该方法：

```php
class A{
    public $data = 1;
    public function __clone(){
        $this->data = 0;
    }
}
$a = new A();
print($a->data); // 输出"1"
$b = clone $a;
print($b->data); // 输出"0"
```

## §3.15 `__toString()`

在PHP 5.1之前，`print()`可以直接输出实例的ID：

```php
class A{}
$a = new A();
print($a);
	// Object id #1
```

在PHP 5.2以后，实例不能直接被输出，必须通过显示声明并定义`__toString()`才能转为字符串:

```php
class A{
    public $data = 1;
}
$a = new A();
print($a);
	// Object of class A could not be converted to string 
```

```php
class A{
    public $data = 1;
    public function __toString(){
        return "The data is ".$this->data;
    }
}
$a = new A();
print($a);
	// 输出"The data is 1"
```

## §3.16 回调函数

PHP 4引入了Lambda表达式，调用`create_function(string args,string commands)`会返回一个Lambda表达式。该函数功能堪比`eval()`，所以经常被用来攻击。自PHP 7.2开始，该函数被deprecated了，取而代之的是匿名函数：

```php
// create_function()
$function1 = create_function(
	'string $name',
    'print("Hello,{$name}!")'
);

// 匿名函数
$function = function($name){
	print("Hello,{$name}");
}
```

匿名函数是一个`callback`类型的变量，既然这是一个变量，那么它就可以当作函数的实参，也可以当作函数的返回值：

```php
class Student {}
class School{
    private $callbacks;
    public function registerCallback(callable $callback):void{
        if(!is_callable($callback)){
            throw new Exception("callback not callable");
        }
        $this->callbacks[] = $callback;
    }
    public function startNewDay(Student $student){
        foreach ($this->callbacks as $callback){
            call_user_func($callback,$student);
        }
    }
}

// 匿名函数
$gotoSchool = function(){print("已到达学校\n");};
$doExam = function(){print("分数为".random_int(0,100));};
$leaveSchool = function(){print("已离开学校");};

$school = new School();
$school->registerCallback($gotoSchool);
$school->registerCallback($doExam);
$school->registerCallback($leaveSchool);

$student = new Student();
$school->startNewDay($student);
```

```php
function getGreetFunction(string $name):callable{
    return function() use ($name){
        print("Hello,".$name);
    };
}
$AliceGreetFunction = getGreetFunction("Alice");
$AliceGreetFunction();
	// 输出"Hello,Alice"
```

## §3.17 匿名类

匿名类常用于简单且特定于局部的上下文，可以看作是某个接口的“实例”。

```php
interface Describable {
    public function getDescription(Person $person):string;
}

class Person {
    public $name;
    public function Person(string $name){
        $this->name = $name;
    }
    public function printDescription(Describable $describable){
        $describable->getDescription($this);
    }
}
$person = new Person("Alice");
$person->printDescription(
        new class implements Describable{
            public function getDescription(Person $person):string{
                return "姓名".$person->name;
            }
        }
);
```

## §3.18 命名空间

在Java中，为了区分同名类，我们使用形如`package com.example`的软件包来管理这些类。在C++中，面对同样的问题，我们使用`namespace std`的命名空间，并且允许在一个命名空间中`use`另一个命名空间进行嵌套。

PHP没有原生的“包”的概念，但是PHP 5.3引入了命名空间这一概念，从这一点上来说它像C++。然而要理清C++的命名空间嵌套关系，就只能层层向上地手动跳转到各个命名空间，并且在创建命名空间的时候还要时刻提防循环嵌套。而PHP的命名空间比较奇妙，它可以使用`namespace com\example;`的方式来管理命名空间的嵌套，从这一点上来说它又像Java。更加奇妙的是，PHP的命名空间路径支持绝对路径`\com\example`和相对路径`com\example`，从这一点上来说它比Java还高级。

`use`关键字是从根命名空间开始查找的，因此不需要在路径开头加`\`：

```php
// a.php
namespace view_1;
class MainFrame {
    static function sayHello(){print("Hello World! From view_1.");}
}
```

```php
// b.php
namespace view_@;
class MainFrame {
    static function sayHello(){print("Hello World! From view_2.");}
}
```

```php
// index.php
function sayHello(){ // 分别调用，开头必须加反斜杠
    \view_1\MainFrame::sayHello(); // 输出"Hello World! From view_1."
    \view_2\MainFrame::sayHello(); // 输出"Hello World! From view_2."
}

use view_1\MainFrame; // 使用use关键字，开头不加反斜杠
function sayHello(){
    MainFrame::sayHello();
}

use view_2\MainFrame as View2MainFrame; // 使用use和as关键字起别名
function test(){
    View2MainFrame::sayHello();
}
```

## §3.19 文件包含

与C语言的`#include<>`类似，PHP支持以下方法来包含文件：

| 函数                                 | 作用                                              |
| ------------------------------------ | ------------------------------------------------- |
| `include()`或`include ...`           | 包含文件，若文件不存在则抛出`E_WARNING`，继续执行 |
| `include_once()`或`include_once ...` | 对于重复包含的文件，仅包含一次，文件不存在则同上  |
| `require(...)`或`require ...`        | 包含文件，若文件不存在则抛出`E_ERROR`，停止执行   |
| `require_once()`或`require_once ...` | 对于重复包含的文件，仅包含一次，文件不存在则同上  |

PHP 5引入了自动加载功能，只需调用`spl_autoload_register()`即可：

```php
spl_autoload_register();
$object = new CustomizeClass();
```

自动加载将尝试
