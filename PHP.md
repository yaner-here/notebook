# PHP





# §1 语法基础



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

非常奇妙的是，PHP不强制要求事先在类的定义中声明所有属性，而是允许动态地向对象添加属性：

```php
$product->price = 9.9;
print($product->price);
	// 输出"9.9"
```

