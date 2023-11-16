# jQuery

参考书籍：

jQuery基础教程（第四版） [豆瓣](https://book.douban.com/subject/25733582/)

jQuery是一个著名的面向浏览器运行时的JavaScript框架，涵盖了选择元素、处理时间、样式动画、操作DOM、异步请求、插件扩展等内容。

例如：给`div.box`添加`hightlight`Class类名。使用原生JavaScript较为繁琐：

```javascript
window.onload = () => {
	document.querySelectorAll('div.box').foreach((element) => {
    	if(!(new RegExp('highlight')).test(element.className)){
        	element.className += 'highlight';
        }
    });
};
```

但是使用jQuery，代码量能大幅减少：

```javascript
$(document).ready(() => {
    $('div.box').addClass('highlight');
});
```

# §1 jQuery基础语法

## §1.1 选择元素

jQuery的语法与CSS选择符一致，用于从DOM中获取元素或元素集合。将CSS选择符传入构造函数`$()`或`jQuery()`中，就能获得一个jQuery对象，里面包含了一个或多个DOM元素。我们可以对这些元素批量操作。

```javascript
$('div.item:not(.horizontal)');
jQuery('div.item:not(.horizontal)').addClass('red');
```

### §1.1.1 `filter()`

CSS提供的各类选择器丰富多样，可以满足大多数情况的需求。但是如果面对更复杂的需求，就必须由JavaScript介入才能实现。例如，要求筛选同时符合`div.item`和`ul > div.red`两个CSS选择符的元素，纯CSS就无法做到。

基于此，jQuery在CSS选择符的基础上，增加了`filter()`函数以供进行逻辑与运算。

```javascript
$('div.item').filter('ul > div.red')
```

`filter()`还能接受函数作为实参，在函数内构造更复杂的筛选条件。例如下面的代码通过判断超链接是否指向站外，来给外链添加样式。

```javascript
$(document).ready(() => {
	$('a').filter(function(){
	    return this.hostname && this.hostname !== location.hostname;
	}).addClass('external_link');
});
```

### §1.1.2 自定义选择符

除了CSS1~3规定的CSS选择符以外，jQuery还支持自定义选择符。自定义选择符的语法与伪类选择符相同，都以`:`开头。详见[官方文档](https://api.jquery.com/category/selectors/jquery-selector-extensions/)。

#### §1.1.2.1 `:animated`

`:animate`选择符用于选择正在进行动画的元素。

```html
<html>
    <head>
        <script src="./node_modules/jquery/dist/jquery.js"></script>
        <style>
            div {
                width: 100px;
                height: 100px;
                border: 1px solid black;
                background-color: lightblue;
            }
            .red {
                background-color: lightcoral;
            }
        </style>
    </head>
    <body>
        <div class="animate"></div>
        <script>
            function toggle(){
                $("div.animate").slideToggle(1000, toggle);
            }
            toggle();
            $(":animated").addClass("red");
        </script>
    </body>
</html>
```

#### §1.1.2.2 `[name!="value"]`

`[name!="value"]`选择符，是对`[name="value"]`的扩展，等价于`:not([name='value'])`。

```html
<html>
    <head>
        <script src="./node_modules/jquery/dist/jquery.js"></script>
        <style>
            div {
                width: 100px;
                height: 100px;
                border: 1px solid black;
                background-color: lightblue;
            }
            .red { background-color: lightcoral; }
        </style>
    </head>
    <body>
        <div class="a"></div>
        <div class="b"></div>
        <script>
            $("div[class!='a']").addClass("red");
        </script>
    </body>
</html>
```

#### §1.1.2.3 `:button`

`:button`选择符用于选择`<button>`和`<input type="button"/>`元素，等价于`button, input[type='button']`。

#### §1.1.2.4 `:checkbox`

`:checkbox`选择符用于选择`type`属性为`checkbox`的元素，等价于`[type='checkbox']`。

#### §1.1.2.5 `:contains()`

`:contains()`选择符用于检测元素本身及其子元素的`innerText`是否包含指定的子字符串。

```javascript
<html>
    <head>
        <script src="./node_modules/jquery/dist/jquery.js"></script>
        <style>
            .bold {
                font-weight: bold;
            }
        </style>
    </head>
    <body>
        <div class="article">
            <span>2023-11-15</span>
            <a href="./">News: Leaders of China and America stressed cooperation's significance</a>
        </div>
        <div class="article">
            <span>2023-11-16</span>
            <a href="./">Comment: Fickle society leaves people at a loss </a>
        </div>
        <script>
            $("div:contains('Comment')").addClass("bold");
        </script>
    </body>
</html>
```

#### §1.1.2.6 `:eq()`

`:eq()`选择符用于在筛选结果中选择第`index`个元素（从`0`开始）。该自定义选择符从`3.4`版本起被抛弃，推荐使用`.eq()`方法。

```html
<html>
    <head>
        <script src="./node_modules/jquery/dist/jquery.js"></script>
        <style>
            /* div {
                width: 100px;
                height: 100px;
                border: 1px solid black;
                background-color: lightblue;
            } */
            .bold {
                font-weight: bold;
            }
        </style>
    </head>
    <body>
        <div class="article">
            <span>2023-11-15</span>
            <a href="./">News: Leaders of China and America stressed cooperation's significance</a>
        </div>
        <div class="article">
            <span>2023-11-16</span>
            <a href="./">Comment: Fickle society leaves people at a loss </a>
        </div>
        <script>
            $("div:eq(1)").addClass("bold");
        </script>
    </body>
</html>
```

#### §1.1.2.7 `:even`

`:even`选择符在筛选结果中选择所有序号为偶数的元素（从`0`开始）。该自定义选择符从`3.4`版本起被抛弃，推荐使用`.even()`方法。

#### §1.1.2.8 `:file`

`:file`选择符用于筛选`type`属性为`file`的元素，等价于`[type='file']`。

#### §1.1.2.9 `:first`

在筛选结果中选择第`0`个元素（从`0`开始）。该自定义选择符从`3.4`版本起被抛弃。

#### §1.1.2.10 `:gt()`

该自定义选择符从`3.4`版本起被抛弃。

#### §1.1.2.11 `:has()`



#### §1.1.2.12 `:header`



#### §1.1.2.13 `:hidden`



#### §1.1.2.14 `:image`



#### §1.1.2.15 `:input`



#### §1.1.2.16 `:last`

该自定义选择符从`3.4`版本起被抛弃。

#### §1.1.2.17 `:lt`

该自定义选择符从`3.4`版本起被抛弃。

#### §1.1.2.18 `:odd`

该自定义选择符从`3.4`版本起被抛弃。

#### §1.1.2.19 `:parent`



#### §1.1.2.20 `:password`



#### §1.1.2.21 `:radio`



#### §1.1.2.22 `:reset`



#### §1.1.2.23 `:selected`



#### §1.1.2.24 `:submit`



#### §1.1.2.25 `:text`



#### §1.1.2.26 `:visible`





### §1.1.3 DOM遍历

jQuery提供了众多DOM的选择方法，而且每个选择方法返回的都是jQuery对象，这意味着我们可以连缀调用：

```javascript
$('a:contains(Notice)')
	.parent() // 获取父元素
	.find('span') // 获取父元素的<span>标签
	.addClass('red') // 给<span>标签添加red类
	.end() // 返回到上级父元素
	.find('p') // 获取父元素的<p>标签
	.addClass('border') // 给<p>表气啊添加border类
```

TODO:

### §1.1.4 `next()`/`nextAll()`

```javascript

```

### §1.1.5 访问底层DOM

在大部分jQuery的开发流程中，我们只需要与jQuery对象打交道。但是如果要访问其中的底层DOM元素，jQuery也有对应的方法。

jQuery对象提供了`[]`和`.get()`两种方法：

```javascript
let spanDOM_1 = $("span")[0];
let spanDOM_2 = $("span").get(1);

let spanDOMs = $("span")
```

## §1.2 事件

jQuery扩展了JavaScript的事件处理机制，提供了更优雅的语法。

### §1.2.1 `ready()`

我们经常需要在某组件加载完成后，执行某些初始化操作。原生实现该功能的方法有以下两种：

- 原生JavaScript：`window.onload: function`

  ```javascript
  window.onload = function(){
      // ......
  }
  ```

- 原生HTML：`<element onload="...">`

  ```html
  <body onload="alert('加载完成');">
  	Hello, World!
  </body>
  ```

jQuery在此基础上提供了封装，通过`.ready()`方法添加到启动队列中，从而自动实现多个`window.onload`参数。

特殊地，当元素是`document`时，`document.ready(function)`可以简写成`$(function)`，也就是把函数传入到jQuery的构造函数中。

当多个JavaScript共同争夺同一个`$`的使用权时，我们可以先引入jQuery，然后调用`$.noConflict)`释放`$`的使用权，再引入其它需要`$`的包。`.ready(...)`或`jQuery((...)=>{})`接受一个形参，表示该jQuery库的命名。此时我们再传入`$`，就能在该作用域内继续让jQuery使用`$`：

```html
<script src="jQuery.js"></script>
<script>$.noConflict();</script>

<script src="xxx.js"></script>
......
<script src="xxx.js"></script>

<script>
    $.ready(function($){
    	$. //......
    });
	$(function($){
		$. //......
    });
</script>
```

### §1.2.2 绑定事件

回想原生JavaScript的时代，开发者需要用`document.addEventListener(event: string, function: callback)`来为元素绑定事件。jQuery提供了`.on()`用于缩短函数名：

```html
<html>
    <head>
        <script src="./node_modules/jquery/dist/jquery.js"></script>
        <style>
            div {
                width: 85%;
                height: auto;
                margin-left: auto;
                margin-right: auto;
                padding: 1rem;
                border: 1px solid black;
            }
            .active { font-weight: bold; }
            .width-wide { width: 85%; }
            .width-normal { width: 60%; }
            .width-narrow { width: 40%; }
        </style>
    </head>
    <body>
        <button id="button-width-wide">宽布局</button>
        <button id="button-width-normal">适中布局</button>
        <button id="button-width-narrow">窄布局</button>
        <div></div>
        <script>
            $("#button-width-wide").on('click', function(){
                $("div").removeClass("width-normal");
                $("div").removeClass("width-narrow");
                $("div").addClass("width-wide");
            });
            $("#button-width-normal").on('click', function(){
                $("div").removeClass("width-wide");
                $("div").removeClass("width-narrow");
                $("div").addClass("width-normal");
            });
            $("#button-width-narrow").on('click', function(){
                $("div").removeClass("width-wide");
                $("div").removeClass("width-normal");
                $("div").addClass("width-narrow");
            });
        </script>
    </body>
</html>
```

当事件被触发时，回调函数中的`this`一定指向携带相应行为的DOM元素。而我们之前也讲过，构造函数`$()`可以接收一个DOM对象，因此我们可以使用`$(this)`直接获取当前元素被包装好的jQuery对象，然后调用jQuery提供的各类API。

又已知`.removeClass()`不传入参数时，表示清除所有类。因此上面可以进一步改写：

```javascript
<html>
    <head>
        <script src="./node_modules/jquery/dist/jquery.js"></script>
        <style>
            div {
                height: auto;
                margin-left: auto;
                margin-right: auto;
                padding: 1rem;
                border: 1px solid black;
            }
            .active { font-weight: bold; }
            .width-wide { width: 85%; }
            .width-normal { width: 60%; }
            .width-narrow { width: 40%; }
        </style>
    </head>
    <body>
        <button id="button-width-wide">宽布局</button>
        <button id="button-width-normal">适中布局</button>
        <button id="button-width-narrow">窄布局</button>
        <div class="width-normal"></div>
        <script>
            $("button").on('click', function(){
                $("div").removeClass();
            })
            $("#button-width-wide").on('click', function(){
                $("div").addClass("width-wide");
            });
            $("#button-width-normal").on('click', function(){
                $("div").addClass("width-normal");
            });
            $("#button-width-narrow").on('click', function(){
                $("div").addClass("width-narrow");
            });
        </script>
    </body>
</html>
```

