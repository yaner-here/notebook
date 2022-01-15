# §1 在HTML中插入JavaScript

## §1.1 延迟脚本和异步脚本

- 延迟脚本

  立即下载，待DOM树加载完毕后按先后顺序执行。

- 异步脚本

  立即下载，立刻执行，不能保证执行顺序。

  > 注意：因为不能保证执行时DOM树加载完毕，故尽量不要在异步脚本中对DOM树进行操作。

```html
<html>
    <head>
        <script type="text/javascript" src="1.js"></script>
        <script type="text/javascript" src="2.js" defer="defer"></script> <!--延迟脚本-->
        <script type="text/javascript" src="3.js" async></script> <!--异步脚本-->
    </head>
    <body>
        <!--内容-->
        <script type="text/javascript" src="4.js"></script>
    </body>
</html>
```

## §1.2 绕过XHTML编码限制

XHTML的语法较为严格，这使得我们在编写代码时需要考虑更多特殊字符的限制。

以下这段代码能被正确解析：

```xhtml
<script type="text/javascript">
	function Min(a,b){
        return a>b?b:a;
    }
</script>
```

如果`>`或`<`的前面带有空格，则XHTML会认为这是某个标签的开端，从而引起解析错误：

```xhtml
<script type="text/javascript">
	function Min ( a , b ) {
        return a > b ? b : a ;
    }
</script>
```

### §1.2.1 实体编码

将特殊字符用实体的方式编码：

```xhtml
<script type="text/javascript">
	function Min ( a , b ) {
        return a &lt; b ? b : a ;
    }
</script>
```

### §1.2.2 CData片段

CData片段是XHTML中的特殊区域，这里的字符不会被当作DOM树被解析，而是直接作为文本处理。

```xhtml
<script type="text/javascript">
	<![CDATA[
        function Min ( a , b ) {
            return a > b ? b : a ;
        }
    ]]>
</script>
```

## §1.3 `<noscript>`元素

只有当浏览器不支持或禁用JavaScript时，`<noscript></noscript>`中的内容将才会被解析到DOM树。

```html
<body>
    <noscript>
        <p>您的浏览器不支持JavaScript,请尽快升级</p>
    </noscript>
</body>
```

# §2 基本语法

## §2.1 标识符

> 注意：
>
> - 相比于其他语言，JavaScript的标识符还可以以美元符号`$`开头，之后也可以有美元符号`$`。
> - 标识符支持扩展ASCII和Unicode
> - 命名时按照ECMAScript规范，使用小驼峰命名法。

## §2.2 严格模式

ECMAScript 5引入了严格模式，在该模式下JavaScript的一些不确定行为将得到处理，甚至对不安全的操作直接报错。

```javascript
function Add(a,b){
    "use strict"; // 启用严格模式
    // 函数体
}
```

## §2.3 作用域

`var`定义的是局部变量，直接对变量赋值定义的是全局变量。强行调用不存在的变量将会触发`Uncaught ReferenceError`。

```javascript
function test(){
	var variable1 = 1,variable2 = 2; //局部变量 
    variable3 = 3; //全局变量
}
alert(variable1); //报错ReferenceError
alert(variable3); //正常执行
```

## §2.4 数据类型

JavaScript共有六种数据类型，不允许自定义类型。数据类型可由`typeof`操作符（针对六种基本数据类型）或`instanceof`操作符（针对引用类型，例如`Array`、`Object`、`RegExp`）识别。本质上`typeof`是操作符而不是函数，这意味着参数可以加括号也可以不加括号。

```javascript
console.log(typeof("abc"));
console.log(typeof "abc");
function addArrayNumber(numArray){
    //添加数据类型检测,加强鲁棒性
    if(numArray instanceof Array){
        //......核心逻辑
    }else{
        alert("传参类型不是数组!")
    }
}
```

|     值类型     |    未定义     |   布尔型    |  字符(串)  |    数值    | 对象/数组/null |     函数     |
| :------------: | :-----------: | :---------: | :--------: | :--------: | :------------: | :----------: |
| `typeof`返回值 | `"undefined"` | `"boolean"` | `"string"` | `"number"` |   `"object"`   | `"function"` |

> 注意：在IE、Firefox和Chrome7^-^中，`typeof(正则表达式)`会返回`object`，而Chrome 7^+^会返回`function`。

### §2.4.1 `undefined`

`undefined`的出现有两种情况：

- 定义了变量但没有赋值
- 强行将`undefined`赋给变量

判断方法有：

- `typeof()=='undefined'`
- `()==undefined`

```javascript
var variable1;
var variable2 = undefined;
typeof(variable1) == 'undefined'; //成立
variable2 == undefined; //成立
```

### §2.4.2 `object`

表示指向对象的指针，包括数组`array`、元组`tuple`、空对象指针`null`等。

### §2.4.3 `boolean`

`boolean`型变量只有两个值：`true`和`false`。可以用`Boolean()`函数将任意值转化为`Boolean`型变量。

> 注意：
>
> - `true`和`false`是区分大小写的。
> - 经过实测，即使开启严格模式，直接使用`any->boolean`的隐式转换并不会有警告或报错。

```javascript
var right = true;
var wrong = false;
```

| 数据类型               | `boolean` | `string`       | `number`                 | `object`               | `undefined` | ``   |
| ---------------------- | --------- | -------------- | ------------------------ | ---------------------- | ----------- | ---- |
| `Boolean()`为`true`时  | `true`    | 任意非空字符串 | 任何非零值(包括$\infin$) | 任何对象(包括空数组等) | N/A(不适用) |      |
| `Boolean()`为`false`时 | `false`   | `""`(空字符串) | `0`和`NaN`               | `null`                 | `undefined` |      |

### §2.4.4 `number`

```javascript
var octNumber1 = 077; //带有前导0,按照八进制进行运算
var octNumber2 = 078; //无效的八进制,按照十进制进行解析

var hexNumber1 = 0xAbCd; //带有前导0x,按照十六进制进行运算,大小写可混用

var floatNumber1 = 0.1;
var floatNumber2 = .1; //当整数部分为0时可省略整数部分

var infinityNumber1 = Number.MAX_VALUE; //仍然是整数
var infinityNumber2 = 1.90e308; //超出范围直接转化为infinity
alert(isFinite(infinityNumber1)); //判断是否为有限数字

var NaNnumber1 = 0/0; //只有0除以0才会得到NaN,因为1/0=+infinity,-1/0=-infinity
var test = NaNnumber1 + 1; //任何包含NaN的操作都会输出NaN,任何包含NaN的条件都会输出false
alert(NaN == NaN); //NaN与任何值都不相等,包括它自己
isNaN(NaN); //判断是否为NaN
isNaN("10"); //isNaN尝试将参数转换为数字,,然后再判断是否为NaN
isNaN("string"); //如果无法转为数字则会判断为NaN
```

将非数值转化为数值的函数：

- `Number(字符串)`：可用于任意数据类型。

  > 注意：`Number()`的转换规则较为复杂
  >
  > - 如果是`boolean`，则按`true`和`false`分别转换为`1`和`0`。
  >
  > - 如果是`number`，则直接转。
  >
  > - 如果是`null`，则返回`0`。
  >
  > - 如果是`undefined`，则返回`NaN`。
  >
  > - 如果是`object`，
  >
  >   - 若为`null`，则返回`0`。
  >
  >   - 若不为`null`，
  >
  >     ```mermaid
  >     flowchart LR
  >         a1(variable)-->a2("valueOf()")
  >         a2--"能被转化为number"-->a3("isNaN()")
  >         a2--"不能被转化为number"-->a4("toString()")--"转化为string"-->a3
  >     ```
  >
  >     
  >
  > - 如果是`string`，
  >
  >   - 若只包含整数或浮点数，则忽略前导符，直接当作十进制数字转换。
  >   - 若为空字符串，则返回`0`。
  >   - 若包含其他字符，则返回`NaN`。

- `parseInt(字符串,[进制数])`：将字符串转化为整型。

  ```伪代码
  未指定进制数时:
  for(读取位数从0开始递增){
  	若遇到非数字字(包括小数点)符,则continue;
  	若遇到数字字符,则顺次读取之后所有无前导0十进制、0前导八进制，0x前导十六进制的数字、,构成一个整数
  	直到遇见下一个非数字字符(包括小数点)
  	return 整数
  }
  ```

  ```javascript
  var hexNumber1 = parseInt("0xaF");
  var hexNumber2 = parseInt("0xaF",16);
  var hexNumber3 = parseInt("aF",16);	//三种方法等价
  ```

- `parseFloat(字符串)`：将字符串转化为浮点型。

  ```伪代码
  for(读取位数从0开始递增){
  	若遇到非数字字符(不包括小数点)符,则continue;
  	若遇到数字字符(包括小数点),则顺次读取之后所有数字,构成一个浮点数
  	直到遇见下一个非数字字符或第二个小数点
  	return 浮点数
  }
  ```

  > 注意：
  >
  > - `parseFloat()`忽略所有前导符，统一按十进制读取

### §2.4.5 `string`

`toString()`将任何数据类型转换成字符串。

## §2.5 相等和全等

`==`/`!=`和`===`/`!==`分别表示相等/不相等和全等/不全等。区别在于前者会尝试进行转换数据类型，后者不会。

> 注意：`==`遵循以下规则
>
> - 如果有一个参数为`boolean`，则先将`true`转为`1`，`false`转为`0`。
> - 如果有一个参数为`object`，则先取`valueOf()`进行转换。
> - 如果有一个参数为`string`，则先取`Number()`进行转换。
> - **`null==undefined`是成立的。**
> - 如果有一个参数为`NaN`，则`==`一律返回`false`。
> - 如果两个参数均为`object`，则判断两者指针是否指向的是同一个对象，若是，则返回`true`。

> 注意：`===`遵循以下规则
>
> - **`null==undefined`不成立。**

## §2.6 label语句

```javascript
var a,b,num=0;
outcome:
for(a=1;a<=3;a++){
    for(b=1;b<=3;b++){
        if(a==2&&b==2)
        	{/* break或continue或break outcome过continue outcome */}
        else
        	{num++;}
    }
}
console.log('a='+a+',b='+b,'num='+num);
```

| /\* 填充内容 \*/  |   `break;`   |   `continue;`    |   `break outcome;`    |                  `continue outcome;`                  |
| :---------------: | :----------: | :--------------: | :-------------------: | :---------------------------------------------------: |
| 当a=2,b=2时的处理 | 跳出内层循环 | 停止当次内层循环 | 跳转至outcome后的语句 | 跳转至outcome指定的语句<br />但不执行外层循环的初始话 |
|   输出(a,b,num)   |   (4,4,7)    |     (4,4,8)      |        (2,2,4)        |                        (4,4,7)                        |

## §2.7 with语句

指定某个对象的作用域，用于简化代码。

> 注意：with语句运行效率极低，也不便于调试代码，在开发大型程序时应尽量避免使用。

```javascript
var number1 = Math.round(2*(Math.sin(Math.PI/6))); //较繁琐
with(Math){
    var number2 = round(2*sin(PI/6));
}
```

## §2.8 传参

### §2.8.1 显式传参

```javascript
function addTwoNumber(a,b){
    return a+b;
}
console.log(addTwoNumber(1,1));
```

### §2.8.2 隐式传参

`arguments`是作用域为函数体内部的数组，记录了函数传来的各种参数。

```javascript
function addAllNumber(){
	var sum=0;
    for(var i in arguments){
        sum+=arguments[i];
    }
    return sum;
}
```

### §2.8.3 同步参数

```javascript
function add10(a,b){
    arguments[1]=10;
    alert(arguments[0]+b);
    alert(arguments[0]+arguments[1]);
}
```

以上述代码为例，修改`argument[1]`时，对应位置上的`b`也发生了改变。

> 注意：当启用严格模式时，经过实测不会报错，但`argument[1]`和`b`的值不再保持同步。

## §2.9 作用域

C/C++中不能在函数中定义函数，而JavaScript可以。

```javascript
var globalVariable=“a”;
function demo(){
	var localVariable="b";
    function subDemo(){
        var sub_localVariable="c";
    }
}
```

### §2.9.1 延长作用域链

```javascript
function generateUrl(){
    var suffix="?username=xxx&password=xxx";
    with(location){
        var url=href+suffix;
	}
    return url; //return在localtion.href和suffix的作用域内,而with的出现又延长了url的作用域链
}
```

### §2.9.2 没有块级作用域

在ECMAScript 6颁布之前，JavaScript的作用域只有全局作用域和函数作用域两种，没有块作用域的概念。

- 在该例中，看似`var result`在`{}`内，`return`语句无法获得，但是要注意JavaScript没有块作用域，所以`var`和`return`在同一个函数作用域内，代码可以正常运行。

  ```javascript
  function floor(floatNumber){
      if(floatNumber-parseInt(floatNumber)>=0.5)
      	{var result=parseInt(floatNumber)+1;}
      else
          {var result=parseInt(floatNumber);}
      return result;
  }
  ```

- 在该例中，`var result`在`if`的函数作用域内，`console.log()`在全局作用域内，故代码无法运行。

  ```javascript
  floatNumber=0.1;
  if(floatNumber-parseInt(floatNumber)>=0.5)
      {var result=parseInt(floatNumber)+1;}
  else
      {var result=parseInt(floatNumber);}
  console.log(result);
  ```

- 变量创建的位置决定了变量的作用域。

  ```javascript
  for(var globalVariable=1;globalVariable<10;globalVariable++){
      var localVariable=2;
  }
  console.log(globalVariable); //正常运行
  console.log(localVariable); //报错
  ```

## §2.10 引用类型

### §2.10.1 object

创建方法：

- `new`操作符后跟`Object()`构造函数

  ```javascript
  var person=new Object();
  person.name="xxx";
  person.age=18;
  ```

- 对象字面量表示法

  ```javascript
  var person=new Object(){
  	"name"=xxx,
      "age"=xxx,
      "graduate year":2020
      5:true //创建对象时会将number型转化为string型
  };
  ```

调用方法：

```javascript
alert(person['name']);
alert(person.name); //两种方法效果相同

alert(person["graduate year"]); //由于属性名中带有空格,所以不能使用点表示法来访问
```

### §2.10.2 array

创建方法：

- 使用`Array()`构造函数

  ```javascript
  var numArray=new Array(10); //创建一个长度为10的数组
  var strArray=new Array("red"); //创建一个长度为1的字符串数组
  var demoArray=Array(10) //医科生觉new操作符
  ```
  
- 数组字面量表示法

  ```javascript
  var strArray=["red","blue","grey"]; //创建一个长度为3的字符串数组
  var emptyArray=[]; //创建空数组
  var errArray=[1,2,]; //不会报错
  ```

  > 注意：在IE8^-^中，`errArray`将会是一个长度为2，元素分别为`1,2,undefined`的数组。在其它浏览器中，`errArray`将会是一个长度为2，元素分别为`1,2`的数组。 

#### §2.10.2.1 `array.length`

`array.length`返回该数组的元素数量。该方法允许通过强行被赋值的方式，来改变数量的元素数量，从而实现元素的修改。

```javascript
var numArray=[1,2,3];
numArray.length=4;	//此时numArray被延长,为[1,2,3,undefined]
numArray.length=2; //次数numArray被截断,为[1,2]

numArray[numArray.length]=3;
numArray[numArray.length]=4;
numArray[numArray.length]=5; //直接入栈
//...
```

#### §2.10.2.2 `array.isArray()`

对于一个网页或者同一个全局作用域而言，我们如果要判断一个`object`是否为`array`，只需调用`instanceof`操作符即可。

```javascript
if(something instanceof Array){
    ...
}
```

然而，对于包含多框架的网页来说，实际上存在多个不同的全局执行环境。当数组从第一个框架被传入第二个框架时，在第二个框架中使用`instanceof`将无法识别在第一个框架中生成的数组。

```html
<!DOCTYPE html> <!-- 首页 -->
<html><frameset> <!-- frameset标签不能与body标签共存 -->
	<frame src="1.html"></frame>
	<frame src="2.html"></frame>
</frameset></html>
```

```html
<!DOCTYPE html> <!-- 1.html -->
<html><script type="text/javascript">
    window.arrOrigin=[1,2,3];
    console.log(arrOrigin instanceof Array); //ture
</script></html>
```

```html
<html><script type="text/javascript">
	var arrInherit=parent.frames[0].window.arrOrigin;
    console.log(arr instanceof Array); //false,需实现允许浏览器执行跨站脚本
</script></html>
```

#### §2.10.2.3 `array.valueOf()`和`array.toString()`和`array.toLocaleString()`和`array.join()`

事实上，任意`object`中都有方法`array.valueOf()`，用于返回该`object`本身。`array`作为`object`的一种类型，自然继承了这一方法。

> `valueOf()`什么伞兵方法，原地TP了属于是:sweat_smile:

`array.toString()`和`array.toLocaleString()`将数组中的元素以字符串的方式有序输出，元素之间用逗号`,`隔开，不包含两侧方括号`[]`。

> 注意：`alert()`会尝试将参数转化为`string`型，然而用到的方法略有区别，详见下例。
>
> ```javascript
> var name1={
>     toLocaleString:function(){return "toLocaleString";}, //重写(override)两个函数
>     toString:function(){return "toString";}
> },name2={
>     toLocaleString:function(){return "toLocaleString";},
>     toString:function(){return "toString";}
> };
> var name=[name1,name2];
> alert(name);
> alert(name.toString());
> alert(name.toLocaleString();
> ```
>
> |   语句   |  `alert(name);`   | `alert(name.toString());` | `alert(name.toLocaleString());` |
> | :------: | :---------------: | :-----------------------: | :-----------------------------: |
> | 执行结果 | toString,toString |     toString,toString     |  toLocaleString,toLocaleString  |

`array.join(string)`同样将数组中的元素以字符串的方式有序输出，但是可以自定义分隔符`string`。

#### §2.10.2.4 栈方法

`array.pop(argument1,argument2,...)`将参数按照从左到右的顺序依次入栈，在数组结尾添加元素。

`array.shift()`取出数组开始处的第一个元素。

`array.unshift(argument1,argument2,...)`将数组按照元素从左到右的顺序依次入栈，在开始处添加元素。

`array.pop()`取出数组末尾第一个元素。

#### §2.10.2.5 重排序方法

`array.reverse()`反转数组中的元素顺序。

`array.sort([function])`先将数组中的元素转成字符串，再按照字符串比较规则从小到大排序，最后转成原来的数据类型。当指定`function`参数时，将按照其指向的函数给出的返回值判断大小并排序。

```javascript
function compare(a,b){
    if(a>b){return 1;}
    if(a==b){return 0;}
    if(a<b){return -1;}
}
var numArrar=[1,3,2,4,6,5];
console.log(numArrar.sort(compare));
```

#### §2.10.2.6 切片

`array.concat()`创建数组`array`的副本，并将参数从左到右追加至副本末尾。若参数中包含数组，则会先被拆成元素，不会出现“存储的是数组指针”的情况。

```javascript
var numArray1=[1,2];
var numArray2=numArray1.concat(3,4,[5,6]);
console.log(numArray2); //numArray2=[1,2,3,4,5,6]
```

`array.slice(num_a,num_b)`截取`array`中下标`i`满足`num_a<=i<num_b`的部分。若`num_a`或`num_b`为负数，则给末尾元素从右往左数依次标号为`-1`、`-2`、`-3`...。如果结束位置小于起始位置，则返回空数组。

`array.splice(initial_index,delete_num,[argument1,argument2,...])`

- 省略`argument`参数时，删除包括下标为`initial_index`在内的向后数共计`delete_num`项元素，并将删除的元素以数组的方式返回。
- 填写`argument`并且`delete_num==0`时，在第`initial_index-1`至`initial_index`之间依次添加`argument`参数。
- 填写`argument`并且`delete_num!=0`时，删除包括下标为`initial_index`在内的向后数共计`delete_num`项元素，然后依次添加`argument`参数，并将删除的元素以数组的方式返回。。

#### §2.10.2.7 位置方法

`array.indexOf(item,[initial_index=0])`从`initial_index`处**向后**查找**第一个**与`item`相等（这里用的是`==`而非`===`）的元素的下标，若不存在则返回`-1`。

`arraylastIndexOf(item,[initial_index=0])`从`initial_index`处**向前**查找**第一个**与`item`相等（这里用的是`==`而非`===`）的元素的下标，若不存在则返回`-1`。

#### §2.10.2.8 迭代方法

`array.every(function)`对`array`中的每一项元素都由函数指针`function`进行穷举，当且仅当所有返回值均为`true`才会返回布尔值`bool`，否则返回`false`。

`array.every(function)`对`array`中的每一项元素都对函数指针`function`进行穷举，若有一个返回值为`true`，则返回布尔值`bool`，否则返回`false`。

`array.filter(function)`对`array`中的每一项元素都由函数指针`function`进行穷举，当且仅当所有返回值均为`true`才会返回布尔值`bool`。

`array.forEach(function)`对`array`中的每一项元素都由函数指针`function`进行处理，无返回值。

`array.map(function)`对`array`中的每一项元素都由函数指针`function`进行穷举，将所有返回值组合成新数组并作为返回值。

```javascript
var numArray=[1,2,3,4,5];
function isBiggerThan3(item){
    return item>3?1:0;
};
//以下两种方法等效
alert(numArray.every(isBiggerThan3));
alert(numArray.every(function isLessThan3(item,index,array){
    console.log(index); //可以通过内部匿名函数传递下标index
    console.log(array); //可以通过内部匿名函数传递数组本体array
    return item<3;
}));
//array.each()
numArray.forEach(function multiple2(item,index,array){
   console.log(item*2);
});
```

### §2.10.3 date

定义`Date`对象：

```javascript
var now=new Date();
```

#### §2.10.3.1 指定时间

`Date.parse(string)`根据字符串`string`解析时间。

```javascript
var time=new Date(Date.parse('2020.1.1 20:00:00'));
var time=new Date('2020.1.1 20:00:00');
var time=new Date(Date.UTC(2020,0,1,20,0,0));
var timeNow=Date.now(); //获取当前时间
var timeNow=new Date(); //获取当前时间
```

#### §2.10.3.2 日期格式化

| 代码 | `date.toTimeString()`              | `date.toDateString()` | `date.toLocaleTimeString()` | `date.toLocaleDateString` | `date.toUTCString()`            |
| ---- | ---------------------------------- | --------------------- | --------------------------- | ------------------------- | ------------------------------- |
| 输出 | '23:46:29 GMT+0800 (中国标准时间)' | 'Mon Oct 04 2021'     | '下午11:46:29'              | '2021/10/4'               | 'Mon, 04 Oct 2021 15:46:29 GMT' |

### §2.10.4 RegExp

```javascript
var regex = /at/p;
var regex = new RegExp("cat","g");
```

#### §2.10.4.1 标志(flags)

- `g`：全局模式（Global），该模式将被应用于所有字符串，而非在发现第一个匹配项时立即停止。
- `i`：不区分大小写（Case-insensitive）
- `m`：多行模式（Multiline），当达到一行文本末尾时，还会继续查找下一行中是否存在匹配项

#### §2.10.4.2 实例属性

- `RegExp.global`：布尔值，是否设置了全局模式。
- `RegExp.ignoreCase`：布尔值，是否忽略大小写。
- `RegExp.multiline`：布尔值，设否设置了多行模式。
- `RegExp.lastIndex`：整型值，表示开始搜索下一个匹配项的字符位置。
- `RegExp.source`：正则表达式经过转义得到的字符串形式。

#### §2.10.4.3 `RegExp.exec()`

```javascript
var text="momm and dad and baby";
var pattern=/mom(and dad(and baby)?)?/gi;
var matches=pattern.exec(text);
matches.index; //0
matches.input; //"mom and dad and baby"
matches[0]; //"mom and dad and baby"
matches[1]; //" and dad and baby"
matches[2]; //" and baby"
```

### §2.10.5 function

```javascript
function sum1(a,b){return a+b;}
var sum2=function(a,b){return a+b;};
var sum3=new Function("a","b","return a+b");
var sum4=sum1;
console.log(sum1(1,1)+sum2(1,1)+sum3(1.1)+sum4(1,1));
```

#### §2.10.5.1 函数声明与函数表达式

```javascript
console.log(sum1(1,1)); //不会报错,因为JavaScript在运行之前会优先解析函数声明
function sum1(a,b){return a+b;}
console.log(sum2(1,1)); //报错,因为由变量定义的函数表达式的优先级低于函数声明
var sum2=funtion(a,b){return a+b;};
```

#### §2.10.5.2 函数指针

```javascript
function sum1(a,b){return a+b;}
function callFunction(functionName,argument){
    return functionName(argument[0],argument[1]);
}
alert(callFunction(sum1,[1,1]));
```

#### §2.10.5.3 函数返回函数

```javascript
function createCompareObjectPropertyFunction(propertyName){
	return function(obj1,obj2){
		if(obj1[propertyName]>obj2[propertyName])
            {return 1;}
        else if(obj1[propertyName]>obj2[propertyName])
            {return -1;}
        else
            {return 0;}
	};
}
var users=[
    {username='mike',age=19},
    {username='xiaoming',age=18},
    {username='lihua',age=16}
];
users.sort(createCompareObjectPropertyFunction(username))

```

#### §2.10.5.4 this

```javascript
function getCustomizeProperty(){alert(this.customizeProperty);}
window.customizeProperty='window_public_environment';
var a={customizeProperty:'object_public_environment'};
a.getCustomizeProperty=getCustomizeProperty;
alert(getCustomizeProperty());
alert(a.getCustomizeProperty());
```

#### §2.10.5.5 function.caller

`function.caller`返回调用该`function`的函数指针。

```javascript
function outFunc(){inFun();}
function inFun(){alert(this.caller);}
outFunc(); //funtion ourFunc(){inFun();}
```

#### §2.10.5.6 function.length

`function.length`表示该函数所需的参数数量。

```javascript
function zeroParameterFunc(){
	return 0;
}
function oneParameterFunc(parameter_1){
	return 0;
}
function twoParameterFunc(parameter_1,parameter_2){
	return 0;
}
console.log(zeroParameterFunc().length);
console.log(oneParameterFunc().length);
console.log(twoParameterFunc().length);
```

#### §2.10.5.7 function.apply()和function.call()和function.bind()

`function.apply(this,array/object)`和`function.call(this,parameter_1,...,parameter_n)`和`function.bind(object)`都用于指定所引用的外部函数的作用域，同时批量传递父函数接受的参数给子函数。这两个函数的引入，使得针对`object`内部属性的函数不必定义在该对象内部，从而脱离对象的束缚。

- 批量传递父函数接受的参数给子函数

  ```javascript
  function printMessage(message){alert(message);}
  function callPrintMessage_1(message){
      return printMessage.apply(this,arguments); //传递arguments对象
  }
  function callPrintMessage_2(message){
      return printMessage.apply(this,[message]); //传递数组
  }
  callPrintMessage_1('Hello World!');
  callPrintMessage_2('Hello World!');
  function callPrintMessage_3(message){
      return printMessage.call(this,message); //传递值,手动列举变量名
  }
  callPrintMessage_3('Hello World!');
  ```
  
- 指定所引用的外部函数的作用域

  ```javascript
  function getCustomizeVariable(){alert(this.customizeVariable);}
  var window.customizeVariable='window_global_environment';
  var someObject={customizeVariable='object_global_environment'};
  getCustomizeVariable(); //全局作用域,this默认指window对象,输出window_global_environment
  getCustomizeVariable.call(this); //全局作用域,this指window对象,输出window_global_environment
  getCustomizeVariable.call(window); //指定了作用域为window对象,输出window_global_environment
  getCustomizeVariable.call(someObject); //指定了作用域为someObject对象,输出object_global_environment
  ```

- 针对`object`内部属性的函数不必定义在该对象内部

  ```javascript
  var object_1={
      name:'object_1',
      getNameInObj:function(){
          alert(this.name);
      }
  };
  function getNameOutObj(){
      alert(this.name);
  }
  object_1.getNameInObj(); //定义在object内部的函数
  getNameOutObj.call(object_1); //定义在object外部的函数
  var getName = getNameOutObj.bind(object_1);
  getName(); //创建新函数
  ```

### §2.10.6 基本包装类型

对于`number`、`boolean`和`string`来说，当调用这三种数据类型的变量时，JavaScript会尝试创建对应的`object`，并在句柄结束后被立即销毁。

```javascript
var str='150'
var num=Number(str);
var obj=new Number(str);
alert(typeof(num)); //转型函数Number(),输出number
alert(typeof(obj)); //构造函数Number(),输出object

num.customizeProperty='num'; //调用时名义上是number,实质上是object
alert(num.customizeProperty); //但上句结束后对象被立即销毁,故输出undefined
obj.customizeProperty='obj';
alert(obj.customizeProperty); //输出obj
```

#### §2.10.6.1 number

- `number.toString(scale)`将number转换成`scale`进制，以字符串形式输出。
- `number.toFixed(digit)`输出精确到小数点后`digit`位的`number`。
- `number.toExponential(digit)`指定科学记数法中数字部分精确到小数点后`digit`位,以字符串形式输出，例如`"1.0e3"`。
- `number.toPrecision(length)`限定输出形式中数字部分的数字字符的个数为`length`(不包括小数点)，用最合适的方法输出对应的字符串。

> 注意：`new Number(value);`创建的是`object`，如果要调用该对象储存的数值，则应该使用`Number.valueOf()`方法。
>

#### §2.10.6.2 string

- `string.length()`返回该字符串对象中的字符数(双字节字符仍然算作一个字符)。
- `string.charAt(index)`从零开始，返回该字符串对象的第`index`个字符。
- `string.charCodeAt(index)`返回该字符串对象的第`index`个字符对应的ASCII~DEC~码。
- `string[index]`从零开始，返回该字符串对象的第`index`个字符。
- `string.concat(extraStr)`返回将`string`和`extraStr`拼接在一起得到的新字符串，但不会改变`string`自身的值。
- `string.slice()`
  - `string.slice(startIndex)`从零开始，截取第`startIndex`个字符及其之后的所有字符。当`startIndex<0`时，截取第`startIndex`位及之后所有的字符串。
  - `string.slice(startIndex,endIndex)`从零开始，截取[`startIndex`,`endIndex`]的字符串。
- `string.substring()`
  - `string.substring(startIndex)`从零开始，截取第`startIndex`个字符及其之后的所有字符。当`startIndex<0`时，返回全部字符串。
  - `string.substring(startIndex,endIndex)`从零开始，截取[`startIndex`,`endIndex`]或[`endIndex`,`startIndex`]的字符串。若`endIndex<0`，等价于`endIndex=0`，然后再套入两个区间中的一个。
- `string.substr()`
  - `string.substr(startIndex)`从零开始，截取第`startIndex`个字符及其之后的所有字符。当`startIndex<0`时，截取第`startIndex`位及之后所有的字符串。
  - `string.substr(startIndex,length)`从零开始，截取第`startIndex`个字符及其之后，总长度为`length`的字符串。当`length<0`时，等价于`length=0`，故返回空字符串。
- `string.indexOf(char,[startIndex=0])`从第`startIndex`位开始，向后寻找并返回`char`第一次出现的位置，未找到时返回`-1`。
- `string.lastIndexOf(char,[startIndex=0])`从第`startIndex`位开始，向前寻找并返回`char`第一次出现的位置，未找到时返回`-1`。
- `string.trim()`返回一份删除前后空格的字符串副本。
- `string.toUpperCase()`返回一份全大写字母的字符串副本。
- `string.toLocaleUpperCase()`根据当地语言规则，返回一份全大写字母的字符串副本。
- `string.toLowerCase()`返回一份全小写字母的字符串副本。
- `string.toLocaleLowerCase()`根据当地语言规则，返回一份全小写字母的字符串副本。
- `string.split(char,[length])`将字符串按`char`分开，返回分隔开每一项构成的数组(不包括`char`本身)。指定`length`时，截取数组前`length`项。
- `string.localeCompare(otherStr)`若`string>otherStr`则返回`1`，小于则返回`-1`，等于则返回`0`。
- `String.fromCharCode(ASCII_1,...,ASCII_n)`将一系列ASCII码转化为对应的字符串。

#### §2.10.6.3 boolean

> 注意：`boolean`和`new Boolean(value)`创建的`obj`类型不同，而`boolean`和`Boolean.valueOf()`的类型相同，两者不能混用。
>
> ```javascript
> var bool=false;
> var obj=new Boolean(false);
> bool==true //false
> obj==true //false,因为该Number(object)返回NaN
> bool?1:0 //0
> obj?1:0 //1,因为object不为null
> ```
>

### §2.10.7 单体内置对象

上文介绍的`object`、`array`、`string`均为内置对象，而单体内置对象还包括`global`和`math`。

#### §2.10.7.1 global

在全局作用域中定义的一切函数和变量都属于`Global`对象。只要能在全局作用域中直接调用的方法和变量，都是`Global`对象中的一部分。

##### §2.10.7.1.1 URI编码

- `encodeURI()/decodeURI()`将字符串中的空格进行URL编码/解码。
- `encodeURIComponent()/decodeURIComponent()`将字符串中的特殊字符进行URL编码/解码。

```javascript
var illegalLink='http://www.baidu.com/a b'
alert(encodeURI(illegalLink)); //'http://www.baidu.com/a%20b'
alert(encodeURIComponent(illegalLink)); //'http%3A%2F%2Fwww.baidu.com%2Fa%20b'
```

##### §2.10.7.1.2 eval()

`eval()`接受一串表示JavaScript的字符串，并将其解析为JavaScript语句。

```javascript
var command='alert("Hello World!");';
eval(command); //等价于alert("Hello World!");
```

> 注意：在严格模式下，由`eval()`解析的JavaScript语句与全局作用域隔离，语句可以访问全局作用域，但全局作用域不能访问语句。
>
> ```javascript
> var command='function alertWelcome(){alert("Hello World!");}';
> eval(command);
> alertWelcome(); //输出Hello World!
> 
> var msg='Hello World!';
> command='alert(msg);';
> eval(command); //输出Hello World!
> ```
>
> ```javascript
> "use strict";
> 
> var command='function alertWelcome(){alert("Hello World!");}';
> eval(command);
> alertWelcome(); //Uncaught ReferenceError:alertWelcome is not defined
> 
> var msg='Hello World!';
> command='alert(msg);';
> eval(command); //输出Hello World!
> ```

##### §2.10.7.1.3 window

```javascript
function alertMessage(){
    alert('Hello World!');
}
alertMessage();
window.alertMessage(); //两种方法等效
```

可以用`this`返回当前区域的global对象。

```javascript
var global=function getGlobalObject(){
    return this;
}
```

##### §2.10.7.1.4 Math

| 属性           | 值                 | 说明                              |
| -------------- | ------------------ | --------------------------------- |
| `Math.E`       | 2.718281828459045  | $e$                               |
| `Math.LN10`    | 2.302585092994046  | $\ln(10)$                         |
| `Math.LN2`     | 0.6931471805599453 | $\ln(2)$                          |
| `Math.LOG2E`   | 1.4426950408889634 | $\log_2(e)$                       |
| `Math.LOG10E`  | 0.4342944819032518 | $\log_{10}(e)$                    |
| `Math.PI`      | 3.141592653589793  | $\pi$                             |
| `Math.SQRT1_2` | 0.7071067811865476 | $\displaystyle\sqrt{\frac{1}{2}}$ |
| `Math.SQRT2`   | 1.4142135623730951 | $\sqrt{2}$                        |

- `Math.max(parameter_1,...,parameter_n)`返回`parameter_i`中的最大值。

- `Math.min(parameter_1,...,parameter_n)`返回`parameter_i`中的最小值。

- `Math.ceil(num)`返回`num`向上取整的结果。

- `Math.floor(num)`返回`num`向下取整的结果。

- `Math.round(num)`返回`num`四舍五入取整的结果。

- `Math.random()`返回一个位于$[0,1)$之内的随机数。

  ```javascript
  function randomInt(startInt,endInt){
  	var cases=startInt-endInt+1; //在[startInt,endInt]之内总共有(endInt-startInt+1)个整数
      return Math.floor(Math.random()*cases+startInt);
  }
  ```

- `Math.abs(x)`返回$|x|$。

- `Math.exp(x)`返回$e^{x}$。

- `Math.log(x)`返回$\ln(x)$。

- `Math.pow(x,a)`返回$x^a$。

- `Math.sqrt(x)`返回$\sqrt{x}$。

- `Math.acos(x)`返回$\cos^{-1}(x)$。

- `Math.asin(x)`返回$\sin^{-1}(x)$。

- `Math.atan(x)`返回$\tan^{-1}(x)$。

- `Math.atan2(y,x)`返回$\tan^{-1}(\displaystyle\frac{y}{x})$。

- `Math.cos(x)`返回$\cos(x)$。

- `Math.sin(x)`返回$\sin(x)$。

- `Math.tan(x)`返回$\tan(x)$。

# §3 面向对象

## §3.1 属性类型

### §3.1.1 数据属性

给`object`设置属性时，每个属性都有对应的四个描述其行为的特性(Attribute)。

|        特性        |                   含义                   |  默认值   |
| :----------------: | :--------------------------------------: | :-------: |
| `[[Configurable]]` | 能否通过`delete`删除属性从而重新定义属性 |   true    |
|  `[[Enumerable]]`  |       能否通过`for-in`循环返回属性       |   true    |
|   `[[Writable]]`   |             能否修改属性的值             |   true    |
|    `[[Value]]`     |                 属性的值                 | undefined |

> 注意：修改特性时，必须使用`Object.defineProperty(obj,property,{newAttributeObject})`。
>
> - `obj`所需修改对象的名称。
>
> - `property`字符串，表示被修改属性的名称，必要时添加引号。
>
> - `{newAttributeObject}`存储新特性的对象，只能包含`configurable`、`enumerable`、`writable`和`value`中的至少一项。
>
>   ```javascript
>   var person={name:'LiHua'};
>   var newAttributeObject={
>       writable:false
>   };
>   Object.defineProperty(person,'name',newAttributeObject);
>   ```

- `configurable`

  ```javascript
  var person={name:'LiHua'};
  var newAttributeObject={
      configurable:false
  };
  Object.defineProperty(person,'name',newAttributeObject);
  delete person.name //由于configurable为false,故delete语句无效
  alert(person.name); //仍然输出LiHua
  ```

- `enumerable`

- `writable`

  ```javascript
  var person={name:'LiHua'};
  var newAttributeObject={
      writable:false
  };
  Object.defineProperty(person,'name',newAttributeObject);
  person.name='Mike'; //由于writable为false,所以该语句无效,但没有Error和Warning
  alert(person.name); //仍然输出LiHua
  ```

- `value`

  ```javascript
  var person={name:'LiHua'};
  var newAttributeObject={
      value:'Mike'
  };
  Object.defineProperty(person,'name',newAttributeObject); //重新设置person.name
  alert(person.name); //输出Mike
  ```

### §3.1.2 访问器属性

|        特性        |                   含义                   |  默认值   |
| :----------------: | :--------------------------------------: | :-------: |
| `[[Configurable]]` | 能否通过`delete`删除属性从而重新定义属性 |   true    |
|  `[[Enumerable]]`  |       能否通过`for-in`循环返回属性       |   true    |
|     `[[Get]]`      |          获得该属性时执行的函数          | undefined |
|     `[[Set]]`      |          改变该属性时执行的函数          | undefined |

> 注意：修改特性时，必须使用`Object.defineProperty(obj,property,{newAttributeObject})`。
>
> - `obj`所需修改对象的名称。
>
> - `property`字符串，表示被修改属性的名称，必要时添加引号。
>
> - `{newAttributeObject}`存储新特性的对象，只能包含`configurable`、`enumerable`、`set`和`get`中的至少一项。
>
>   ```javascript
>   var person={name:'LiHua'};
>   var newAttributeObject={
>       configurable:false
>   };
>   Object.defineProperty(person,'name',newAttributeObject);
>   ```
>
>   > 注意：在定义`set`和`get`特性时，也可使用`object.__defineGetter(property,function)`和`object.__defineSetter__(property,function)`。
>   >
>   > ```javascript
>   > var person={name:'LiHua',age:19};
>   > person.__defineGetter__('personalProfile',
>   > 	function(){return this.name+' is '+String(this.age)+' years old.';}
>   > );
>   > alert(person.personalProfile);
>   > ```

- `configurable`

- `enumerable`

- `get`

  ```javascript
  var person={name:'LiHua'};
  var newAttributeObject={
      get:function(){
          return this.name.toLowerCase();
      }
  };
  Object.defineProperty(person,'upperCaseName',newAttributeObject);
  alert(person.upperCaseName); //定义了"新"属性,输出lihua
  ```

- `set`

  ```javascript
  var person={name:'LiHua',_birth:2002,_age:19};
  var newAttributeObject={
      set:function(newAge){
          this._birth=this._birth-(newAge-this._age); //按照年龄,自动更新出生年份
          this._age=newAge;
      }
  };
  Object.defineProperty(person,'age',newAttributeObject);
  person.age=20;
  alert(person._birth);
  ```

> 注意：`Object.defineProperty()`只能定义一个属性。如果要同时定义多个属性，必须使用`Object.defineProperties(obj,propertiesObj)`。
>
> ```javascript
> var book={};
> var propertiesObj={
>     _year:
>     	{
>         	value:2004
>     	},
>     edition:
>     	{
>         	value:1
>     	},
>     year:
>     	{
>         	get:function(){
>             	return this._year;
>         	},
>         	set:function(newValue){
>             	if(newValue>2004)
>                 	{
>                 		this._year=newValue;
>                 		this.edition+=newValue-2004;
>             		}
>                 else
>                 	{
>                      	alert("年份只能递增!");   
>                     }
>             }
>         }
> };
> Object.defineProperties(book,propertiesObj);
> ```

> 注意：`object.customizeProperty`只能获取到`customizeProperty.value`或`get()`的`return`值。如果要获取该对象，则应使用`Object.getOwnPropertyDescriptor(obj,customizeProperty)`
>
> ```javascript
> var person={name:'LiHua'};
> var descriptor=Object.getOwnPropertyDescriptor(person,"name");
> alert(typeof(descriptor));
> ```

## §3.2 创建对象的模式

### §3.2.1 工厂模式

定义批量返回`Object`的函数。

```javascript
function createPerson(name,age){
    var person={};
    person.name=name;
    person.age=age;
    person.selfDesc=function(){
        alert(this.name+' is '+String(this.age)+' years old.');
    };
    return person;
}
var LiHua=createPerson('LiHua','19');
```

> 注意：
>
> - 由工厂模式定义的`Object`在`instanceof`中仍被判定为`Object`，也就是说工厂模式无法自定义对象类型。
>
>   ```javascript
>   LiHua instanceof Object; //true
>   LiHua instanceof Person; //false
>   ```
>
> - 由工厂模式定义的`Object`的`object.constructor`属性为空函数指针。

### §3.2.2 构造函数模式

```javascript
function Person(name,age){
    this.name=name;
    this.age=age;
    this.selfDesc=function(){
        alert(this.name+' is '+String(this.age)+' years old.');
    };
}
//当作构造函数使用
var LiHua=new Person('LiHua',19);
LiHua.selfDesc();
//当作普通函数使用
Person('Mike',18);
window.selfDesc();
//在另一个对象的作用域中使用
var Diana=new Object();
Person.call(Diana,'Diana',23);
Diana.selfDesc();
```

> 注意：
>
> - 由构造函数模式定义的`Object`在`instanceof`中可以被判定为别名，也就是说工厂模式可以自定义对象类型。
>
>   ```javascript
>   LiHua instanceof Object; //true
>   LiHua instanceof Person; //true
>   ```
>
> - 由构造函数模式定义的`Object`的`object.constructor`属性为创建该对象的函数。
>
>   ```javascript
>   var Mike=LiHua.constructor('Mike',18);
>   ```

### §3.2.3 原型模式

每个`Function`都有一个原型属性(`prototype`)，该属性是一个对象指针，指向的对象保存着所有由构造函数创建的`object`的属性和方法。

```javascript
function Person(){};
Person.prototype.name='Mike';
Person.prototype.age=18;
Person.prototype.selfDesc=function(){alert(this.name);};
var Mike=new Person();
```

虽然对象指针`object.prototype`对JavaScript不可见，但可以用`function.prototype.isPrototypeOf(object)`来判断对象指针`object.prototype`是否指向对象`function.prototype`，以及`Object.getPeototypeOf(object)`获取`object`的原型对象`object.propotype`。

在调用`object`中的变量或方法时，JavaScript会先检查该对象`object`中是否有该变量或方法的定义。如果有，则直接调用；如果没有，则再从对象指针`object.propotype`指向的原型对象`function.prototype`中检查是否有该变量或方法的定义，如果有，则直接调用；如果没有，则返回`Uncaught ReferenceError`。

```javascript
Mike.name='new Mike';
alert(Mike.name); //new Mike
delete Mike.name;
alert(Mike.name); //Mike
```

`object.hasOwnProperty(propertyName)`检测一个属性`propertyName`是否存在于实例中。如果存在于实例中，则返回`true`；如果存在于原型中，则返回`false`。

`propertyName in object`检测一个属性`propertyName`是否存在于对象`object`中的实例或原型中(即是否有定义)。如果存在，则返回`true`；如果不存在，则返回`false`。

综上所述，可以自定义一系列函数，能够自动判断属性`propertyName`在`object`中没有定义/在实例中有定义/在实例中无定义但在原型中无定义。

```javascript
function whereExistProperty(object,propertyName){
    if(propertyName in object)
        {
            if(object.hasOwnProperty(propertyName))
                {return 2;}
            else
                {return 1;}
        }
    else
        {return 0;}
}
function hasPrototypeProperty(object,propertyName){
    return (!object.hasOwnProperty(propertyName))&&(name in object);
}
```

为列举对象中定义过的所有属性，可使用`Object.keys(function.prototype)`或`Object.getOwnPropertyNames(function.prototype)`来获取仅在函数中或事例中可枚举的/仅在原型中的所有属性构成的数组。

```javascript
function Person(){}
Person.prototype.name='Mike';
Person.prototype.age=18;
Person.prototype.selfDesc=function(){alert(this.name+String(age));};
var Mike=new Person();

Object.keys(Person.prototype); //['name','age','selfDesc']
Object.keys(Mike); //[]

Object.getOwnPropertyNames(Person.protptype); //['constructoe','name','age','selfDesc']
```

为简化`function.prototype`的写法，可将该对象替换成预先准备号的对象。此过程相当于重写对象`function.prototype`。这种方法会让原型中所有元素的`enumerable`更新为`true`。

```javascript
Mike instanceof Person; //true
Mike.constructor==Person; //true
newPrototype={
    name:'Diana',
    age:23
};
Person.prototype=newPrototype;
var Mike=new Person();
Mike instanceof Person; //true
Mike.constructor==Person; //false,因为刚创建函数时Person.prototype.constructor指向Person(),更新Person.prototype时,constructor会指向Object()而非Person(),除非在newPrototype中主动设置constructor=person
```

如果不想让原型中所有元素的`enumerable`更新为`true`，还可以用`Object.defineProperty(function.prototype,propertyName,newPropertyObj)`来更新。

原型具有动态性，这是由"二次搜索"实现的。

```javascript
/* function Person(){......} */
var Mike=new Person();
Person.prototype.selfDesc=function(){alert(this.name+String(this.age));};
Mike.selfDesc(); //可正常输入

Person.prototype={
    constructor:Person
    name:'Mike'
    age:18;
    newSelfDesc:function(){/*......*/};
}
Mike.newSelfDesc(); //报错,因为Mike.constructor指向的是原先Person.prototype的地址,而现在的地址是一个匿名对象.故匿名对象中的改变无法同步到旧对象.
```

### §3.2.4 构造函数模式与原型模式混用

构造函数模式的优点在于各对象之间的变量相互独立，原型模式的优点在于可以创建各对象共用的变量方法。将这二者结合起来，就可以灵活控制变量和方法的`public`和`private`。

```javascript
function Student(name,age){
    this.name=name;
    this.age=age;
    this.educationExperience=['大连理工大学'] //确立共性后,分别创建属于自己的数组
};
Student.prototype={
    constructor:Student,
    getEducationExperience:function(){
        alert(this.educationExperience); //每个object都必须有的函数
    };
};
var Diana=Student('Diana',23);
var LiHua=Student('LiHua',18);
Diana.educationExperience.push('清华大学');
LiHua.educationExperience.push('北京大学');
```

### §3.2.5 动态原型模式

```javascript
function Student(name,age){
    this.name=name;
    this.age=age;
    this.educationExperience=['大连理工大学']
    if(typeof(this.selfDesc)=='undefined') //如果实例没有定义,则
        {
            Student.prototype.selfDesc=function(){
            	alert(this.name+String(this.age));   
            };
        }
};
```

然而这种方式有一个缺点，每次调用函数`Student()`创建实例时，`Student.prototype`就会被更新一次，造成不必要的资源浪费。于是我们增加一个判断条件，这就是动态原型模式。在第一次创建实例时，实例和对应的原型肯定都没有`selfDesc()`这个方法，所以`typeof`返回的结果一定是`undefined`，符合我们预先设置的判断条件，于是在原型中定义该方法。在以后创建实例时，显然原型中存在该方法，`typeof`会返回`function`，故判断条件不成立，`Student.prototype`不会被刷新，从而杜绝了不必要的资源浪费。

```javascript
function Student(name,age){
    this.name=name;
    this.age=age;
    this.educationExperience=['大连理工大学'];
    if(typeof(this.selfDesc)=='undefined')
        {
            Student.prototype.selfDesc=function(){
            	alert(this.name+String(this.age));   
            };
        }
};
```

### §3.2.6 寄生构造函数模式

在工厂模式的基础上，将临时对象`tmp`的创建方法从`tmp={}`改为`tmp=new Object()`，即为寄生构造函数模式。

```javascript
function Person(name,age){
    var tmp=new Object();
    tmp.name=name;
    tmp.age=age;
    tmp.selfDesc=function(){
        alert(this.name+String(this.age));
    };
    return tmp;
}
```

该模式可以在特殊情况下为对象创建构造函数。

```javascript
function specialArray(){
    var values=new Array();
    values.push.apply(values,arguments); //将输入的数据放置在原数组后面
    values.toPipedString=function(){ //定义新方法
        return this.join("|");
    };
    return values;
}
var color=new specialArray("red","blue","green");
alert(color.toPipedString()); //"red|blue|green"
```

> 注意：函数的`return`值是`Array`对象，本质上只是`Object`中的`Array`类型，所以无法用`instanceof`判断对象的自定义类型。
>
> ```javascript
> color instanceof Object; //true
> color instanceof Array; //true
> color instanceof specialArray; //false
> ```
>
> 

### §3.2.7 稳妥构造函数模式

稳妥对象指的是既没有公共属性，也没有包含`this`的方法，通常方法中也没有`new`的`object`。

根据稳妥对象的定义，我们可以将§3.2.5中的例子进行改写，尽可能减少`this.name`被访问的次数。

```javascript
function Person(name,age){
    var tmp=new Object();
    tmp.name=name;
    tmp.age=age;
    tmp.selfDesc=function(){
        alert(name); //而非this.name
    }
    return tmp;
}
var Mike=new Person('Mike',18);
```

## §3.3 继承

### §3.3.1 原型链

```javascript
function masterType(){ //定义父对象的父属性为true
    this.masterProperty=true;
}
masterType.prototype.getMasterProperty=function(){ //定义父对象返回父属性的函数
    return this.masterProperty;
}
function slaveType(){ //定义子对象的子属性为false
    this.slaveProperty=false;
}
slaveType.prototype=new masterType(); //子对象原型继承父对象原型
slaveType.prototype.getSlaveProperty=function(){ //定义子对象返回子属性的函数,先创建再定义,防止被上行刷掉
    return this.slaveProperty;
}

var tmp=new slaveType();//定义子属性
tmp.getMasterProperty; //true,子对象继承了父对象的属性和方法
```

在上例中，`slaveType`继承了`masterType`的属性，`masterType`继承了`Object`的属性，从而形成一条原型链。

```javascript
tmp instanceof Object; //true
tmp instanceof masterType; //true
tmp instanceof slaveType; //true

Object.prototype.isPrototypeOf(tmp); //true
masterType.prototype.isPrototypeOf(tmp); //true
slaveType.prototype.isPrototypeOf(tmp); //true
```

> 注意：用这种方法定义的变量地址和方法地址是共用的。
>
> ```javascript
> function masterType(){
> this.masterProperty=null;
> this.masterArray=[1,2];
> }
> function slaveType(){
> }
> slaveType.prototype=new masterType(); //子对象原型继承父对象原型
> var tmp1=new slaveType();
> tmp1.masterProperty=1;
> tmp1.masterArray.push(3);
> var tmp2=new slaveType();
> tmp2.masterProperty=2;
> tmp2.masterArray.push(4);
> alert(tmp1.masterProperty); //1,因为masterProperty是值传递
> alert(tmp2.masterArray); //[1,2,3,4],因为masterArray是地址传递
> ```

### §3.3.2 借用构造函数/伪造对象/经典继承

为了使得不同对象间的变量和方法相互独立，故使用借用构造函数的方式。

```javascript
function masterType(){
    this.number=[1,2,3];
}
function slaveType(){
    masterType.call(this); //在slaveType中执行masterType的所有初始化语句
}
var tmp1=new slaveType();
var tmp2=new slaveType();
tmp1.number.push(4);
tmp2.number.push(5);
alert(tmp1.number); //[1,2,3,4]
alert(tmp2.number); //[1,2,3,5]
```

相比原型链而言，借用构造函数可以在子类型构造函数中给父类型构造函数传参。

```javascript
function masterType(name){
    this.name=name;
    this.array=[1,2,3];
}
function slaveType(){
    masterType.call(this,'LiHua'); //直接传参
}
var tmp=new slaveType();
tmp.name; //'LiHua'
```

### §3.3.3 组合继承/伪经典继承

```javascript
function masterType(name){
    this.name=name;
    this.array=[1,2,3];
}
function slaveType(name,age){
    masterType.call(this,name); //在slaveType作用域中创建this.name和this.array
    this.age=age;
}
slaveType.prototype=new masterType(); //创建原型链
slaveType.prototype.selfDesc=function(){alert(this.name+String(this.age));}
slaveType.prototype.constructor=slaveType;
var obj_1=new slaveType("LiHua",18);
var obj_2=new slaveType("Mike",19);
obj_1.array.push(4);
alert(obj_1.array); //[1,2,3,4]
alert(obj_2.array); //[1,2,3]
```

### §3.3.4 原型式继承

借助已有对象的原型来创建新对象。

```javascript
function copyObject(obj){
    function temp(){};
    temp.prototype=obj; //将新函数的原型绑定到旧原型
    return new temp(); //返回新原型创建的对象
}
```

然而这种方法复制的对象有问题：旧原型本身作为对象地址，被赋到了新原型，也就是两者共用一个地址，于是新对象会共用旧对象的变量地址，而不是每个新对象占有各自的独立变量空间。

```javascript
var master={name:null,list:[1,2,3]};
var slave_1=copyObject(master);
var slave_2=copyObject(master);
slave_1.name='LiHua';
slave_2.name='Mike';
alert(slave_1.name); //'LiHua',值参数分离
slave_1.list.push(4);
slave_2.list.push(5);
alert(slave_1.name); //[1,2,3,4,5],地址参数共用
```

为了解决该问题，JavaScript新增了`Object.create(obj,[newPropertyObj])`方法。

- 未指定`newPropertyObj`时，该方法与我们自定义的`copyObject()`方法一致。
- 指定`newPropertyObj`时，`newPropertyObj`中定义的新属性会覆盖原有`obj`中的属性。

### §3.3.5 寄生式继承

```javascript
function copyObject(obj){
    var temp=Object.create(obj);
    temp.test=function(){alert('test');};
    return temp;
}
var master={name:'LiHua'};
var slave=copyObject(master);
slave.test();
```

### §3.3.6 寄生组合式继承

```javascript
function masterType(name,age){
    this.name=name;
    this.age=age;
    this.array=[1,2,3];
}
masterType.prototype.selfDesc=function(){alert(this.name+String(this.age));};
function slaveType(name,age){
    masterType.call(this,name);
    this.age=age;
}
slaveType.prototype=new masterType();
slaveType.prototype.constructor=slaveType;
slaveType.prototype.selfDesc(){alert(this.name+String(this.age));};
```

# §4 函数表达式

定义函数有两种方法：函数声明和函数表达式。

- 函数声明

  ```javascript
  function customizeFunc_1(){};
  ```

- 函数表达式

  ```javascript
  customizeFunc_2=function(){};
  ```

> 注意：
>
> - 函数声明的一个重要特性是函数声明提升，即执行代码前会先读取函数声明，这意味着可以把调用该函数的语句放在其定义的前面。反观函数表达式，作为一个正常的赋值语句，并没有优先执行的特性。
>
>   ```javascript
>   customizeFunc_1(); //可正常执行
>   function customizeFunc_1(){};
>   
>   customizeFunc_2(); //报错
>   customizeFunc_2=function(){};
>   ```
>
> - 要尤其警惕函数声明提升。因为无论函数声明在何处，JavaScript都会优先解析，即使函数声明在一个根本不可能被执行的地方。
>
>   ```javascript
>   if(false){function defineFunc_1(){};}
>   var a=1;
>   if(a)
>       {function defineFunc_2(){alert('1');}}
>   else
>       {function defineFunc_2(){alert('2');}}
>   ```
>
>   按照常理，`defineFunc_1()`不会被解析，`defineFunc_2()`会输出`1`。但是由于函数声明提升这一特性，效果可能不符合预期。不同浏览器对这种函数声明的处理不同。Chrome系完全符合预期；Firefox系会无条件按照最后一次出现的函数声明进行解析，即`defineFunc_1()`会被解析，`defineFunc_2()`会输出`2`。
>
>   为避免这种情况，我们可以换用函数表达式来实现这种效果。
>
>   ```javascript
>   var a=1;
>   if(a)
>       {defineFunc_2=function(){alert('1');}}
>   else
>       {defineFunc_2=function(){alert('2');}}
>   ```

## §4.1 递归调用的陷阱

```javascript
function factorial(num){
    if(num==0||num==1)
        {return 1;}
    else
        {return factorial(num-1);} //Uncaught ReferenceError: factorial is not defined.
}
var newFactorial=factorial(num);
factorial=null;
alert(newFactorial(5)); //报错
```

上述代码有一个问题：由于函数指针`factorial`在后续代码中被设为`null`，因此函数指针`newFactorial`指向的函数体内部在调用函数指针`factorial`时就会报错。

`arguments.callee`是一个指向此处正在执行的函数的指针，于是可以进行如下改写：

```javascript
function factorial(num){
    if(num==0||num==1)
        {return 1;}
    else
        {return arguments.callee(num-1);} //对此处进行更改
}
var newFactorial=factorial(num);
factorial=null;
alert(newFactorial(5));
```

改进过的代码仍然有一个问题：严格模式下不能访问`arguments.callee`。回想一下`Uncaught ReferenceError`的原因，是函数指针`factorial`不再指向函数体。所以我们要找一个替代品，使得这个替代品永远指向函数体，而函数表达式可以实现该效果：

```javascript
var factorial=function f(num){ //给原先的匿名函数指定固定的名称
    if(num==0||num==1)
        {return 1;}
    else
        {return f(num-1);} //对此处进行更改
}
var newFactorial=factorial(num);
factorial=null;
alert(newFactorial(5));
```

## §4.2 闭包

闭包是指有权访问另一个函数作用域中变量和方法的函数。

```javascript
function createIsBothLessThanNum(num){
	return function(value_1,value_2){
		if(value_1<num&&value_2<num)
            {return 1};
        else
            {return 0};
    };
}
var IsBothLessThan5=createIsBothLessThanNum(2);
alert(IsBothLessThan5(2,3));
```

在上例中，`IsBothLessThan5()`可以调用`num=5`，是因为其作用域链可以追溯到`createIsBothLessThanNum()`。

### §4.2.1 this对象作用域

匿名函数的执行具有全局性，因此其`this`对象指向`window`。

```javascript
var name='Window'
var obj={
    name:'Object',
    getName:function(){
        return function(){return this.name};
    }
}
alert(obj.getName()()); //'Window'
```

为了实现预期效果，我们可以把外部作用域中的`this`对象保存在闭包中，这样闭包内的成员就能访问了。

```javascript
var name='Window'
var obj={
    name:'Object',
    getName:function(){
        var temp=this; //这不是匿名函数,此处的this指向obj
        return function(){return temp.name};
    }
}
alert(obj.getName()()); //'Object'
```

### §4.2.2 内存泄漏

在IE9^-^浏览器中，由于对JS对象和COM对象使用不同的垃圾收集历程，闭包会有一些特殊问题：如果闭包的作用域链中保存着一个HTML元素，则该元素无法被销毁。

```javascript
function alertElementId(elementName){
    var element=document.getElementById(elementName);
    element.onclick=function(){alert(element.id);};
}
```

根据其内存回收机制，只要引用数大于0，则内存不会被回收。匿名函数保存了对`alertElementId()`中`element`的引用，因此`element`的引用数至少为1，这使得`element`占用的内存永远不会被回收。如果多次调用该函数，那么内存各处为`element`分配的空间就会越来越多，导致内存泄露。

以下是一种改进方案：

```javascript
function alertElementId(elementName){
    var element=document.getElementById(elementName);
    var id=element.id;
    element.onclick=function(){alert(id);};
    element=null;
}
```

## §4.3 模仿块级作用域

JavaScript中没有块级作用域这一概念，这意味着在代码块中定义的变量和方法实际上是在函数中创建的。

```javascript
function temp(){
    {var a=1;}
    var a; //尝试重新定义a
    alert(a); //仍然是1
}
```

经常利用匿名函数的性质通过函数表达式来模仿块级作用域：

```javascript
//报错,因为function是关键字,JavaScript规定了各类关键字的语法,在函数体定义完毕后再添加圆括号不符合关键字语法
function (){alert('Hello World!');}();
//正确,因为函数表达式不受上述限制
(
    function (){alert('Hello World!');}
)();
//根据此原理可模仿块级作用域
function temp(){
    (
    	function(){
            var i=0;
        }
    )();
    alert(i); //Uncaught ReferenceError
}
```

# §5 BOM

## §5.1 `window`对象

### §5.1.1 全局作用域

```javascript
var message='Hello World';
function printMessage(){
    console.log(this.message);
}
// 
console.log(window.message);
printMessage();
window.printMessage();
```

