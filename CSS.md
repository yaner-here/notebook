# tCSS

# §0 前置知识

## §0.1 在HTML引入CSS

### §0.1.1 `<link>`标签

`<link>`标签必须放在`<head>`元素中。

```htaccess
<link rel="stylesheet" type="text/css" href="./index.css" media="all">
```

其中`<link>`标签涉及的属性有：

- `rel`：资源与文档的关系(Relation)
- `type`：资源的MIME类型
- `href`：资源的路径，可以是绝对URL或相对URL
- `media`：资源的应用场景。

### §0.1.2 `@import`语句

`@import`声明必须放在`<style>`的开头。

```html
<style>
    @import url(index.css)
</style>
```

### §0.1.3 `HTTP Header`

HTTP协议允许在响应头指定加载的CSS文件。

- `Apache`的分布式配置文件`.htaccess`：

  ```htaccess
  Header add Link "</index.css>;rel=stylesheet;type=text/css"
  ```

- `Apache`的全局配置文件`httpd.conf`：

  ```htaccess
  <Directory /var/www/html/site>
  	Header add Link "</index.css>;rel=stylesheet;type=text/css"
  </Directory>
  ```

### §0.1.4 行内样式

```html
<span style="color: red">Hello</span>
```



# §1 CSS语法

样式表由一个或多个规则组成。一个规则由前面选择符(`selector`)和后面的声明块(`declaration block`)组成。声明块之中的声明用分号`;`隔开。

```css
h1 {color: red; background: yellow}
```

## §1.1 注释

CSS支持`/* */`类型的注释，不允许注释嵌套：

```css
/*
	这是多行注释
*/
```

注释不能算作空白字符，因此下面的写法是合法的：

```css
h1 {color: red}
h1 {co/*我是突然闯入的注释*/lor: red}
```

由于历史原因，CSS注释可以使用HTML中的注释标记：

```css
h1 {color: red <!-- 让标题为红色 --> }
```

## §1.2 选择符

### §1.2.1 元素选择符

元素选择符用于选择HTML或XML文档中的元素。

```css
h1 {color: red}
```

### §1.2.2 群组选择符

群组选择符允许将一个样式应用到一组元素上，各个元素之间用`,`分隔：

```css
h1, h2, h3, h4, h5, h6 {color: red}
```

特殊地，使用`*`表示匹配所有元素，称为通用选择符。

```css
* {color: red; font: 18px}
```

> 注意：虽然一组声明的最后一处声明后不必加引号，但是工程中还是推荐加上。否则在其后面添加样式时容易忘记补上，导致新增的一行声明被解析成上一层声明的关键词。

### §1.2.3 类选择符

类选择符`.`用于匹配文档元素中的`class`属性。其之前的字符串指定匹配的元素(通配则置为`*`或空)，之后的字符串指定匹配的`class`属性。在其之后继续加类选择符进行串联，表示同时匹配到多个`class`属性，区分大小写。

```html
<h1 class="warning urgent">Notice</h1>
<h2 class="info">Idea</h2>
<style>
    .warning {font-weight: bold;}
    h2.info {font-style: italic;}
    .warning.urgent{color: red}
</style>
```

### §1.2.4 ID选择符

ID选择符`*`用于匹配文档中唯一出现的`id`属性。其语法与类选择符类似，但是不能串联，区分大小写。

```html
<div id="navbar">
    <a id="title">Welcome</a>
    <span id="currentTime">2023-08-08</span>
</div>
<style>
    #navbar {width: 100%;}
    a#title {font-weight: bold;}
    *#currentTime {color: green;}
</style>
```

### §1.2.5 属性选择符

属性选择符`[]`用于匹配函数某种属性的元素。支持串联。

```html
<div id="loginFrame">
    <input type="checkbox" checked/>
</div>
<style>
    input[checked] {color: red;} /* 筛选所有预先勾选的多选框 */
    *[id] {border: 2px solid red;} /* 筛选所有具有ID属性的元素 */
    input[type][checked] { font-weight: bold; }
</style>
```

属性选择符不仅可以匹配属性名，还可以匹配属性值。如果属性值可能会引起歧义，可以用双引号`"`或单引号`'`包裹：

```html
<a href="https://www.baidu.com">Baidu</a>
<a class="warning-1 urgent">Pending...</a>
<style>
    a[href="https://www.baidu.com"] {...} /* 精准匹配 */
	a[class|="warning"] /* 模糊匹配，匹配以warning或以warning-开头的 */
	a[class~="warning-1"] /* 精准匹配，匹配属性值被空格分割后的单词 */
    a[class*="ing urg"] /* 模糊匹配，匹配子串 */
    a[href^="https://"] /* 模糊匹配，匹配开头 */
    a[href$=".com"] /* 模糊匹配，匹配结尾 */
</style>
```

上面的语法和正则表达式比较相似。实际上，属性选择符也支持正则表达式里的“大小写敏感”模式`i`：

```html
<div id="NavBar"></div>
<style>
    div[id="navbar" i] {color: red;}
</style>
```

属性选择符本身是大小写敏感的，除非属性值本身是HTML/XML规定的关键字：

```html
<input type="checkbox"/>
<style>
    input[type="ChEcKbOx"] {color: red;} /* 匹配成功 */
</style>
```

### §1.2.6 后代选择符

后代选择符` `用于筛选目标元素的所有子元素和子元素的子元素。

```html
<div class="list"><ul>
    <li>Item 1</li>
</ul></div>
<style>
    .list ul li {color: red;}
</style>
```

### §1.2.7 子代联结符

子代联结符`>`与后代选择符` `配合使用，用于筛选目标元素的所有子元素。

```html
<div class="list"><ul>
    <li>Item 1</li>
</ul></div>
<style>
    .list > ul > li {color: red;}
</style>
```

### §1.2.8 紧邻同胞联结符

紧邻同胞联结符`+`与后代选择符` `配合使用，用于筛选目标元素的所有兄弟元素。

```html
<div class="list"><ul>
    <li type="title">Item:</li>
    <li>Item 1</li>
    <li>Item 2</li>
</ul></div>
<style>
    li[type="title"] + li {color: gray;} /* 只为非title设置样式 */
</style>
```

### §1.2.9 一般同胞联结符

一般同胞联结符`~`与后代选择符` `配合使用，用于匹配与目标元素后面的所有兄弟元素，也就是选择后续元素。

```html
<div>
    <h1>Title</h1>
    <a>Item 1</a> <!-- 变成红色 -->
    <a>Item 2</a> <!-- 变成红色 -->
</div>
<style>
    div h1 ~a {color: red;}
</style>
```

### §1.2.10 伪类选择符

伪类选择符`:`用于选择伪类。可以串联使用。关于伪类的具体内容详见[§1.3 伪类](#§1.3 伪类)。

> 注意：伪类的"串联"不同于传统意义上的链式调用。在链式调用中，每个选择符接受到的实参都是上一个选择符的输出结果，而伪类选择符的"串联"表示每一个伪类选择符的实参都是初始传入的。
>
> 例如，`div:first-child:last-child:`表示在所选中的`div`元素中，只有既是`fisrt-child`也是`last-child`的元素才能匹配成功，因此其效果等价于`:only-child`。

### §1.2.11 伪元素选择符

为实现特定的效果，伪元素和伪类都能向文档中插入虚构的元素。伪元素选择符为`::`。

## §1.3 伪类

伪类指的是文档中不一定真实存在的结构，或者某些元素的特定状态，它必须依赖于已有的元素。

### §1.3.1 结构伪类

#### §1.3.1.1 `:root`

`:root`表示文档的根元素。在HTML文档中，它指的就是`<html>`元素。

```html
<html>
	<style>
        :root {border: 1px solid red;}
        html {border: 1px solid red;}
    </style>
</html>

```

#### §1.3.1.2 `:empty`

`:empty`表示没有任何子元素（包括文本元素）的元素。

```html
<div>Hello world</div>
<div> </div>
<div>
</div>
<div><!----></div> <!-- 这个元素会被屏蔽 -->
<div></div> <!-- 这个元素会被屏蔽 -->
<style>
    div:empty {display: none;}
</style>
```

> 注意：`:empty`很容易被滥用成`*:empty`，从而会匹配`<input>`、`<img>`、`<br>`、`<textarea>`这类本身没有子元素的标签。

#### §1.3.1.3 `:only-child`

`:only-child`的作用是：当选定的元素只有一个子元素时，且子元素类型恰好为`:only-child`指定的类型时，选中该子元素。

```html
<html>
    <head>
        <style>
            a[href] img:only-child {border: 2px solid black;}
        </style>
    </head>
    <body>
        <a href="baidu.com"><img src="./avatar.png"><br/></a> <!-- 未选中 -->
        <a href="baidu.com"><img src="./avatar.png">Baidu</a> <!-- 已选中 -->
    </body>
</html>
```

#### §1.3.1.4 `:only-of-type`

`:only-child`的作用是：当选定的元素只有一个`:only-child`指定类型的子元素时，选中该子元素。它与`:only-child`的区别是：`:only-of-type`可以允许选定的元素有多个子元素，只要其中符合指定类型的子元素只有一个就可以；而`:only-child`只允许选定的元素只有一个子元素，且其类型恰好为`:only-child`指定的类型。

```html
<html>
    <head>
        <style>
            a[href] img:only-of-type {border: 2px solid black;}
        </style>
    </head>
    <body>
        <a href="baidu.com"><img src="./avatar.png"><br/></a><!-- 已选中 -->
        <a href="baidu.com"><img src="./avatar.png">Baidu</a><!-- 已选中 -->
    </body>
</html>
```

> 注意：`:only-of-type`牵扯到了父元素和子元素的概念。例如在`div a:only-of-type`中，到底谁是父元素呢？答案是`div`。因此在下面的例子中，两个子元素都不会被选中：
>
> ```html
> <style>
>     p.unique:only-of-type {color: red;}
> </style>
> <div>
>     <p class="unique">Hello</p>
>     <p class="common">World</p>
> </div>
> ```

#### §1.3.1.5 `:first-child`和`:last-child`

`:first-child`用于表示在众多同级的兄弟节点中，排在第一个的，且恰为指定类型的子元素。

`:last-child`用于表示在众多同级的兄弟节点中，排在最后一个的，且恰为指定类型的子元素。

```html
<style>
    p:first-child {color:red;}
    p:last-child {color:green;}
</style>
<p>First</p> <!-- 红色 -->
<p>Second</p>
<p>Third</p> <!-- 绿色 -->
```

#### §1.3.1.6 `:first-of-type`和`:last-of-type`

`:first-of-type`用于表示与指定类型相同的众多兄弟元素中，其中的第一个子元素。

`:last-of-type`用于表示与指定类型相同的众多兄弟元素中，其中的最后一个子元素。

```html
<style>
    p:first-of-type {color:red;}
    p:last-of-type {color:green;}
</style>
<p>First</p> <!-- 红色 -->
<p>Second</p>
<p>Third</p> <!-- 绿色 -->
```

#### §1.3.1.7 `:nth-child()`和`:nth-last-child`

`:nth-child()`用于表示在众多同级的兄弟节点中，排在第$n$个的，且恰为指定类型的子元素。此处$n$从$1$开始计数。

```html
<html>
    <head>
        <style>
            body > div:nth-child(2) {color: red;}
        </style>
    </head>
    <body>
        <div>Hello</div>
        <div>Hello</div> <!-- 红色 -->
        <div>Hello</div>
    </body>
</html>
```

`:nth-child()`还可以接收由自然数$n$构成形如`an+b`的表达式：

```html
<html>
    <head>
        <style>
            body > div:nth-child(2n+1) {color: red;}
        </style>
        <title>让奇数项全都为红色</title>
    </head>
    <body>
        <div>我是奇数</div><div>我是偶数</div>
        <div>我是奇数</div><div>我是偶数</div>
        <div>我是奇数</div><div>我是偶数</div>
    </body>
</html>
```

`:nth-child()`还可以接收`even`、`odd`这两个关键字，分别表示筛选红偶数项和奇数项：

```html
<html>
    <head>
        <style>
            body > div:nth-child(odd) {color: green;}
            body > div:nth-child(even) {color: red;}
        </style>
        <title>让奇数项全都为绿色,偶数项为红色</title>
    </head>
    <body>
        <div>我是奇数</div><div>我是偶数</div>
        <div>我是奇数</div><div>我是偶数</div>
        <div>我是奇数</div><div>我是偶数</div>
    </body>
</html>
```

`:nth-last-child()`作用是类似的，只不过是从尾到头计数。用于表示在众多同级的兄弟节点中，排在第$n$个的，且恰为指定类型的子元素。此处$n$从$1$开始计数。

> 注意：`:nth-child()`和`:nth-last-child()`本质上的区别是计数起点。灵活地选择计数起点，可以实现更灵活的功能。
>
> 例题：现在有如下由众多`<div>`组成的HTML文档，现在需要让最后一个元素的颜色为灰色，而且相邻元素要灰白交替显示。请编写CSS。
>
> ```html
> <html>
>     <body>
>         <div>好多元素</div>
>         <div>好多元素</div>
>         <div>......</div>
>         <div>好多元素</div>
>         <div>这一行必须是灰色</div>
>     </body>
> </html>
> ```
>
> 答：使用`:nth-last-child()`即可。
>
> ```css
> /* 两种方法均可 */
> div:nth-last-child(2n+1) {color: gray}
> div:nth-last-child(odd) {color: gray}
> ```

#### §1.3.1.8 `:nth-of-type`和`:nth-last-of-type()`

用法与[§1.3.1.7 `:nth-child()`和`:nth-last-child`](§1.3.1.7 `:nth-child()`和`:nth-last-child`)类似。

### §1.3.2 动态伪类

我们之前讲过，所有伪类都必须依赖于已有的元素。当HTML文档给定的一瞬间，结构伪类就一定能从HTML文档中找到已有的元素。然而对于动态伪类来说，依赖的元素可能并不存在与原生HTML文档中，必须经过浏览器渲染后才有可能产生。

#### §1.3.2.1 超链接伪类

在HTML中，我们常用`<a href="google.com">`等方法做一个超链接，而不会认为一个普通的`<a></a>`是超链接。

"未被访问过"和"未访问状态"是两个完全不同的概念。我们以这两个`<a>`标签为例，这两个概念的关系如下图所示：

```html
<a>普通标签</a>
<a href="baidu.com">百度</a>
```

```mermaid
flowchart LR
subgraph "未访问状态 :link"
	link["&lt;a href=&quot;baidu.com&quot;&gt;<br/>未被访问过"]
end
subgraph "已访问状态 :visited"
	visited["&lt;a href=&quot;baidu.com&quot;&gt;<br/>已被访问过"]
end
link--"访问"-->visited
visited--"访问"-->visited
normal["&lt;a&gt;普通标签&lt;a&gt;<br/>未被访问过"] --"访问(失败)"--> normal
```

`:link`用于指示被标记为超链接（即具有`href`属性）的，且未被访问过的元素，也就是处于未访问状态的元素。

`:visited`用于指示已被访问过的超链接。

> 注意：超链接伪类可以被用于泄露用户隐私。理论上，JS脚本可以探测与`:visited`相同样式的所有DOM节点，从而推断出用户访问过哪些网站。鉴于此，从2017年开始，几乎所有主流浏览器厂商都支持下列补救措施：
>
> 1. `:visited`伪类能操纵的CSS属性仅限于颜色，例如`color`、`background-color`、`column-rule-color`、`outline-color`、`border-color`、`border-top/bottom/left/right-color`。
> 2. `:link`伪类不再只选择未访问状态的超链接，而是选择所有超链接。除非`:visited`覆盖了已访问状态的超链接。
> 3. 浏览器的JavaScript Runtime规定，无论超链接状态如何，返回的值始终都是未访问状态的值。

#### §1.3.2.2 用户操作伪类

`:focus`用于指示当前获得输入焦点的元素，可以通过`TAB`键和鼠标获得。

`:hover`用于指示当前被鼠标指针悬停的元素。

`:active`用于指示由用户输入激活的元素，例如对超链接按下鼠标到松开鼠标的一段时间。

```html
<html>
    <head>
        <style>
            input:focus{background-color:lightgray;}
            input:hover{background-color:lightblue;}
            input:active{background-color:lightgreen;}
        </style>
    </head>
    <body>
        <input type="text" tabindex="1"/>
        <input type="text" tabindex="2"/>
        <input type="text" tabindex="3"/>
    </body>
</html>
```

> 注意：受制于特定性，伪类的顺序不可随意设置。在实际工程中，通常推荐的顺序从`:link/:visited/:hover/:active`变成了`:link/:visited/:focus/:hover/:active`。

#### §1.3.2.3 UI状态伪类

`:enabled`用于指示接受输入的元素。

`:disabled`用于指示不接受输入的元素。

`:checked`用于指示由用户或文档默认选中的单选按钮或复选框。

`:indeterminate`用于指示"既没有选中，也没有未选中"的单选按钮和复选框。（该状态只能由DOM脚本设定，不能由用户设定）

`:default`用于指示默认选中的元素，且仅特指单选按钮、复选框、选项。

`:valid`用于指示满足数据有效性语义的元素，且仅特指输入框。

`:invalid`用于指示不满足数据有效性语义的元素，且仅特指输入框。

`:in-range`用于指示当前输入的值在控件允许的最小值和最大值之间的元素，且仅特指输入框。

`:out-range`用于指示当前输入的值小于控件允许最小值或大于控件允许最大值的元素，且仅特指输入框。

`:required`用于指示用户必须输入的元素，且仅特指输入框。

`:optional`用于指示用户非必要输入的元素，且仅特指输入框。

`:read-write`用于指示用户可以编辑的元素，且仅特指输入框。

`:read-only`用于指示用户不能编辑的元素，且仅特指输入框。

```html
<html>
<head>
    <style>
        input:disabled {opacity: 0.5;}
        input:enabled {border-color: black;}
        input:checked + label {font-weight: bold;}
        input:not(:checked) + label {color: #555;}
        input:indeterminate + label {font-style: italic;}
        input:default + label {color: darkred;}
        input:required {border-style: double;}
        input:optional {border-style: dotted;}
        input:invalid {border: 2px solid red;}
        input:valid {border: 2px solid green;}
        input:in-range {border: 5px solid green;}
        input:out-of-range {border: 5px solid red;}
        textarea:read-only {border-color: aqua;}
        textarea:read-write {border-color: greenyellow;}
    </style>
</head>
<body>
    <form>
        <div>
            <span>Username:</span><input type="text" tabindex="1" required/>
        </div>
        <div>
            <span>Password:</span>
            <input disabled type="text" tabindex="2">
        </div>
        <div>
            <span>Email:</span>
            <input type="email"/>
        </div>
        <div>
            <span>Gender:</span>
            <input type="radio" name="gender" id="male" value="male"><label for="male">Male</label>
            <input type="radio" name="gender" id="female" value="female"><label for="female">Female</label>
        </div>
        <div>
            <span>Preference:</span>
            <input type="checkbox" name="preference" id="sports" checked value="sports"/><label for="sports">Sports</label>
            <input type="checkbox" name="preference" id="music" value="music"/><label for="music">Music</label>
            <input type="checkbox" name="preference" id="cooking" value="cooking"/><label for="cooking">Cooking</label>
        </div>
        <div>
            <span>Budget:</span>
            <input type="number" min="100" max="100000" step="10000"/>
        </div>
        <div>
            <span>Matio:</span><textarea></textarea>
        </div>
        <div>
            <span>Info:</span><textarea disabled></textarea>
        </div>
    </form>
</body>
</html>
```

> 注意：`:in-range`并不意味着`:valid`。HTML5为`<input type="number" min="..." max="...">`引入了`step`属性，作为右侧加减按钮的步进长度。其`value`即使位于`[min, max]`内，只要不能被`step`整除，它就是`:invalid`。

#### §1.3.2.4 `:target`

在形如`http://...#...`的URL中，井号`#`后面的字符串被称为片段标识符，用于定位HTML文档中具有相同`id`的标签。`:target`伪类用于标记`id`与片段标识符相等的目标元素。

```html
<html>
<head>
    <style>
        #catalog > a {display: block;}
        :target {border-left: 5px solid gray; background-color: lightblue; font-weight: bold;}
    </style>
</head>
<body>
    <div id="catalog">
        <h1>目录</h1>
        <a href="./#chapter1">1.摘要</a>
        <a href="./#chapter2">2.过程</a>
        <a href="./#chapter3">3.结语</a>
    </div>
    <div id="text">
        <h1>正文</h1>
        <div id="chapter1">1.摘要 这是摘要</div>
        <div id="chapter2">2.过程 这是过程</div>
        <div id="chapter3">3.结语 这是结语</div>
    </div>
</body>
</html>
```

#### §1.3.2.5 `:lang()`

浏览器可以通过[`lang`属性](https://developer.mozilla.org/zh-CN/docs/Web/HTML/Global_attributes/lang)、[`<meta>`标签](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Language)和HTML响应头这三个途径推断语言来源：

```html
<p lang="fr">这是法语</p>
<meta http-equiv="Content-Language" content="de, en">
```

```http
Content-Language: de-DE
```

`:lang()`选中具有指定语言属性的元素。

```html
<html lang="zh">
<head>
    <style>
        :lang(zh) {color: red;}
        :lang(en) {color: blue;}
        :lang(fr) {color: green;}
    </style>
</head>
<body>
    <p lang="en">这是英语</p>
    <p lang="fr">这是法语</p>
    <p>这是全局的中文</p>
</body>
</html>
```

#### §1.3.2.6 `:not()`

一个很经典的例子是：在重大公祭日时，网站的所有元素都必须转为灰白，除非存在某些元素必须设为彩色。在`:not()`出现之前，普遍的做法是：先把所有元素设为灰白，然后单独给特殊元素加`!important`覆盖掉：

```html
<html lang="zh">
<head>
    <style>
        p {filter: grayscale(1);}
        .red{color: red;}
        .blue{color: blue;}
        .green{color: green;}
        .keep-colorful {filter: grayscale(0) !important;}
    </style>
</head>
<body>
    <p class="red">网站标题</p>
    <p class="blue">网站信息</p>
    <p class="green keep-colorful">特殊元素</p>
</body>
</html>
```

有了`:not()`以后就方便多了：

```html
<html lang="zh">
<head>
    <style>
        .red{color: red;}
        .blue{color: blue;}
        .green{color: green;}
        body > *:not(.keep-colorful) {filter: grayscale(1);}
    </style>
</head>
<body>
    <p class="red">网站标题</p>
    <p class="blue">网站信息</p>
    <p class="green keep-colorful">特殊元素</p>
</body>
</html>
```

## §1.4 伪元素

### §1.4.1 装饰首字母

`::first-letter`用于装饰非行内元素的首字母。

例如给定以下需求：给英文报纸排版，每篇文章`<div>`由数个`<h1>`、`<h2>`和若干个`<p>`构成，要求给第一个出现的`<p>`的首字母调成粗体大字号：

```html
<html lang="zh">
<head>
    <style>
        p, h1 {
            font-family: 'Times New Roman', Times, serif;
        }
        .article > p:first-of-type::first-letter {
            font-weight: bold;
            font-size: 200%;
        }
    </style>
</head>
<body>
    <div class="article">
        <h1>Population Arising Comes To An End In China</h1>
        <p>This is first paragragh.</p>
        <p>This is second paragragh.</p>
        <p>This is third paragragh.</p>
    </div>
</body>
</html>
```

### §1.4.2 装饰首行

`::first-line`用于装饰元素的首行文本。

> 注意：目前`::first-letter`和`::first-line`都只能应用到块级元素上，而不能应用到行内元素上。并且这两者允许使用的CSS属性也有限制：
>
> - `::first-line`允许使用的CSS属性：所有字体属性、所有背景属性、所有文本装饰属性、所有行内排版属性、所有行内布局属性、所有边框属性，`box-shadow`、`color`、`opacity`。
> - `::first-line`允许使用的CSS属性：所有字体属性、所有背景属性、所有外边距属性、所有内边距属性、所有边框属性、所有文本装饰属性、所有行内排版属性、`color`、`opacity`。

### §1.4.3 装饰前置与后置元素

CSS可以自己生成并插入内容，从而影响HTML文档建立的DOM。

例如继续完善[§1.4.1 装饰首字母](§1.4.1 装饰首字母)一节的任务：每篇文章由一个`<h1>`、多个`<h2>`和`<p>`交叉构成，要求给每个`<h2>`的标题前插入两个灰色的左方括号：

```css
<html lang="en">
<head>
    <style>
        p, h1, h2 {
            font-family: 'Times New Roman', Times, serif;
        }
        .article > h2 + p::first-letter {
            font-weight: bold;
            font-size: 150%;
        }
        .article > h2::before {
            content: "[[";
        }
    </style>
</head>
<body>
    <div class="article">
        <h1>Population Arising Ended In China</h1>
        <h2>Data analyse</h2>
        <p>Here is the population statistic released from China Constitution of Statistics, ...</p>
        <p>From the graph, we can see that ...</p>
        <h2>The reason</h2>
        <p>The first reason is that ...</p>
        <p>The second reason is that ...</p>
        <h2>Dangerous consequence</h2>
        <p>Military circuiting is more difficult ...</p>
        <p>Finacial marketing's pulse will be slower ...</p>
    </div>
</body>
</html>
```

## §1.5 属性值

CSS中的一切都是文本，我们之前已经见识过了部分CSS属性及其可能的属性值，例如`margin: 2px`、`display: none`、`color: red`等等。属性值可以大致分为关键字、字符串和其他文本值这三类。

### §1.5.1 关键字

CSS定义的关键字有很多，几乎每个CSS属性都有自己支持的一套关键字。比较常见的有`red`、`none`之类的。

CSS3定义了以下全局关键字，每个CSS属性都能用：

- `inherit`：强制继承父元素的该属性
- `initial`：把属性值设置为预定义的初始值
- `unset`：对于可继承的属性，其效果等价于`inherit`；对于不可继承的属性，其效果等价于`initial`

> 注意：`all`属性非常特殊，它表示除`direction`和`unicode-bidi`之外的所有属性，它的属性值只能取这三个全局关键字。例如可以通过该属性，让子元素继承父元素的几乎所有属性：
>
> ```css
> ... {all: inherit;}
> ```

### §1.5.2 字符串

CSS中的字符串与其他编程语言的字符串有很多相似之处：

```css
content: "这是一个字符串";
content: "这是一个带引号'的字符串";
content: "可以给引号\"转义";
```

当字符串过长，需要换行时，可以使用下列方法：

```css
content: "这是换行 \
的字符串";
```

如果真的要在字符串中插入换行符，可以使用Unicode字符`\A`：

```css
content: "这是换行\A的字符串"
```

### §1.5.3 URL

URL的格式为`url(...)`。其中的URL链接既可以是绝对路径`url(protocol://server/pathname)`，也可以是相对路径`url(./...)`。

> 注意：包含URL的CSS文航会作用到HTML文档上。相对路径所参照的根目录取决于该URL所在的文档路径，而不是作用到的HTML文档的路径。

### §1.5.4 绝对长度单位

| 绝对长度单位      | 作用                          |
| ----------------- | ----------------------------- |
| 英寸(`in`)        | 美制单位，$1$英寸=$2.54$厘米  |
| 厘米(`cm`)        | 公制单位                      |
| 毫米(`mm`)        | 公制单位                      |
| 四分之一毫米(`q`) | 公制单位                      |
| 点(`pt`)          | 印刷度量单位，$1$英寸=$72$点  |
| 派卡(`pc`)        | 印刷度量单位，$1$英寸=$6$派卡 |
| 像素(`px`)        | CSS规定$1$英寸=$96$像素       |

### §1.5.5 分辨率单位

为适应媒体查询和响应式设计，CSS增加了三个描述显示器分辨率的单位：

| 分辨率单位       | 作用                        |
| ---------------- | --------------------------- |
| 点每英寸(`dpi`)  | 在$1$英寸范围内能显示的点数 |
| 点每厘米(`dpcm`) | 在$1$厘米范围内能显示的点数 |
| 点每像素(`dppx`) | 在$1$像素范围内能显示的点数 |

分辨率单位只能应用于媒体查询：

```css
@media (min-resolution: 500dpi){
	/* 分辨率大于等于500dpi时生效 */   
}
```

### §1.5.6 相对长度单位

相对长度单位是参考其它长度而言的，例如屏幕分辨率、视区宽度、用于偏好设置等。

| 相对长度单位 | 作用                                                         |
| ------------ | ------------------------------------------------------------ |
| `em`         | 参考该元素小写字母`m`的宽度，即该元素的`font-size`值，$1$`em`=$1$`font-size` |
| `ex`         | 参考该元素小写字母`x`的高度，$1$`ex`=$1$小写字母`x`的高度    |
| `rem`        | 参考根元素小写字母`m`的宽度，即该元素的`font-size`值，$1$`em`=$1$根元素的`font-size` |

```html
<html lang="en">
<head>
    <style>
        h1 {font-size: 24px;}
        h2 {font-size: 18px;}
        p {font-size: 12px;}
        h1, h2, p {margin-left: 1em;}
        small {margin-left: 0.8em;}

    </style>
</head>
<body>
    <h1>Left margin = <small>24</small></h1>
    <h1>Left margin = <small>18</small></h1>
    <p>Left margin = <small>24</small></p>
</body>
</html>
```

| 相对长度单位 | 作用                        |
| ------------ | --------------------------- |
| `ch`         | 参考该元素字符`0`字形的进距 |

进距指的是一个字形的起点到下一个紧邻字形的起点之间的距离，等价于字形本身的宽度加上侧边的间距。除非是等宽字体，否则对于大多数西文字体而言，字体与字体间距并不一致，而且任意一个字符的进距也不一定等于字体字形的进距。

```html
<html lang="en">
<head>
    <style>
        .section > div {
            height: 1ch;
            width: 3ch;
            background-color: red;
        }
    </style>
</head>
<body>
    <div class="section" style="font-family: Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;">
        <span>123</span>
        <div></div>
    </div>
    <div class="section" style="font-family: 'Courier New', Courier, monospace;">
        <span>123</span>
        <div></div>
    </div>
    <div class="section" style="font-family: Verdana, Geneva, Tahoma, sans-serif;">
        <span>123</span>
        <div></div>
    </div>
</body>
</html>
```

| 相对长度单位       | 作用                                                |
| ------------------ | --------------------------------------------------- |
| 视区宽度(`vw`)     | $\displaystyle\frac{当前视区的宽度除以}{100}$       |
| 视区高度(`vh`)     | $\displaystyle\frac{当前视区的高度}{100}$           |
| 视区尺寸最小值(``) | $\displaystyle\min\left(\text{vw},\text{vh}\right)$ |
| 视区尺寸最大值(``) | $\displaystyle\max\left(\text{vw},\text{vh}\right)$ |

```html
<html lang="en">
<head>
    <style>
        body {
            padding: 0;
            margin: 0;
        }
        .container {
            height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
        }
        .item {
            border: 2px solid rgb(128, 128, 128);
            border-radius: 0.5em;
            padding: 20px;
            width: 60vw;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="item">我的宽度可以随浏览器窗口的宽度自动改变!</div>
    </div>
</body>
</html>
```

### §1.5.7 `calc()`

CSS允许用户使用一些简单的表达式作为属性值，让浏览器动态计算属性值。这些表达式需要用`calc()`包裹，且仅支持加减乘除与括号`+-*/()`。

```css
p {width: calc(90% - 2em)}
```

> 注意：`calc()`计算的表达式，既是数学意义上的表达式，又是编程意义上的表达式。
>
> 1. 从数学层面来说，必须保证运算符两侧的单位一致。例如`2 + 1.1`是合法的，`7em - 20%`是合法的，但是`7em - 0.2`是非法的。
> 2. 从数学层面来说，必须保证运算符两侧的值至少有一个为无量纲数。例如`2 * 2em`是合法的，`2 * 2`是合法的，但是`2em * 2em`是非法的。
> 3. 从数学层面来说，必须保证出发运算符`/`的除数为无量纲数。例如`2em /3`是合法的，但是`2 / 3em`是非法的。
> 4. 从编程层面来说，加减运算符`+-`的两侧必要有空格，乘除运算符`*/`没有这一限制。
> 5. 从编程层面来说，`calc()`支持的表达式中最多只能包含20个算子（数字、百分数等）。超过20个算子的表达式无效。

### §1.5.8 `attr()`

我们知道，HTML文档的内容是固定的，后来有了SHTML作为HTML模版，允许服务器端渲染。同理，CSS文档的内容是固定的，但是有了`attr()`，我们就能根据HTML动态决定CSS的属性值。

例如可以配合伪元素，根据AJAX返回的内容添加序号：

```html
<html lang="en">
<head>
    <style>
        .item::before {content: "[" attr(id) "]";}
    </style>
</head>
<body>
    <div class="item" id="1">参考文献</div>
    <div class="item" id="2">参考文献</div>
    <div class="item" id="3">参考文献</div>
</body>
</html>
```

### §1.5.9 颜色

#### §1.5.9.1 具名颜色

HTML规定了16个[基本颜色关键字](https://zh.wikipedia.org/wiki/%E7%BD%91%E9%A1%B5%E9%A2%9C%E8%89%B2)：

| 基本颜色关键字 | 颜色代码  | 基本颜色关键字 | 颜色代码  |
| -------------- | --------- | -------------- | --------- |
| `aqua`         | `#00ffff` | `blue`         | `#0000ff` |
| `gray`         | `#808080` | `lime`         | `#00ff00` |
| `navy`         | `#000080` | `purple`       | `#800080` |
| `silver`       | `#c0c0c0` | `white`        | `#ffffff` |
| `black`        | `#000000` | `fuchsia`      | `#ff00ff` |
| `green`        | `#008000` | `maroon`       | `#800000` |
| `olive`        | `#808000` | `red`          | `#ff0000` |
| `teal`         | `#008080` | `yellow`       | `#ffff00` |

CSS4还规定了148个额外的具名颜色。

#### §1.5.9.2 RGB颜色和RGBa颜色

RGB认为所有颜色都可以分解成三个0-255之间的红色、绿色、蓝色的分量。RGBa增加一个维度`alpha`，表示颜色的不透明度，取值范围是`[0,1]`之间的任意浮点数。CSS支持以下四种方法指定RGB颜色和RGBa颜色：

1. 函数式RGB颜色

   ```css
   p {
   	color: rgb(128,128,128); /* 要么只能用整数 */
       color: rgb(50%,50%,50%); /* 要么只能用百分数 */
       color: rgb(50%,50%,128); /* 不能混用整数和百分数 */
   }
   ```

   虽然CSS名义上支持浮点数的分量，但是实际上用户代理会自动对其四舍五入，让其变为整数。如果分量为小于0，则约为0；如果大于255，则约为255。综上，函数式RGB颜色最终的输出可以表示为：
   $$
   \text{RGB}(r,g,b)=\left[\begin{matrix}
   	R\\G\\B
   \end{matrix}\right]
   =
   \left[\begin{matrix}
   	\text{round}(\min(\max(0,r),255))\\
   	\text{round}(\min(\max(0,g),255))\\
   	\text{round}(\min(\max(0,b),255))\\
   \end{matrix}\right]
   $$

2. 函数式RGBa颜色

   ```css
   p {
   	color: rgba(128,128,128,0.8);
   }
   ```

   舍入规则与函数式RGB颜色相同。

3. 十六进制RGB颜色

   可以使用两位十六进制数字表示分量，共计六位。如果只有三位，浏览器会自动将每个数字向后紧邻复制一次，扩充到六位。

   ```css
   p {
   	color: #ff0000; /* 小写字母都行 */
       color: #FF0000; /* 大写字母都行 */
       color: #123 /* 等价于#112233 */
   }
   ```

4. 十六进制RGBa颜色

   2017年，一种新的RGBa表示方法被提出了。它沿用了十六进制RGB颜色表示方法，将`alpha`分量离散化成0-255之间的离散值。

   ```css
   p {
   	color: #66ccff88;
       color: #6cf8; /* 简写 *?
   }
   ```

#### §1.5.9.3 HSL颜色和HSLa颜色

HSL颜色是由色相（Hue）、饱和度（Saturation）、明度（Lightness）构成的简称。其中$H\in[0\degree,360\degree)$，$S,L\in[0,1]$。

$RGB\rightarrow HLS$：

- $$
  H=\begin{align}\begin{cases}
  		0&,\max(R,G,B)=\min(R,G,B)\\
  		\displaystyle\frac{60\degree\times(G-B)}{\max(R,G,B)-\min(R,G,B)}\mod{360\degree}&,\max(R,G,B)=R\\
  		\displaystyle\frac{60\degree\times(B-R)}{\max(R,G,B)-\min(R,G,B)}+120\degree&,\max(R,G,B)=G\\
  		\displaystyle\frac{60\degree\times(R-G)}{\max(R,G,B)-\min(R,G,B)}+240\degree&,\max(R,G,B)=B\\
  	\end{cases}\end{align}
  $$

- $$
  L=\displaystyle\frac{\max(R,G,B)+\min(R,G,B)}{2}
  $$

- $$
  S=\begin{align}\begin{cases}
  	0&,\left|\max(R,G,B)\right|=\left|\min(R,G,B)\right|\\
  	\displaystyle\frac{\max(R,G,B)-\min(R,G,B)}{\max(R,G,B)+\min(R,G,B)}&,L\in(0,\displaystyle\frac{1}{2}]\\
  	\displaystyle\frac{\max(R,G,B)-\min(R,G,B)}{2-(\max(R,G,B)+\min(R,G,B))}&,L>\displaystyle\frac{1}{2}
  \end{cases}\end{align}
  $$

$HLS\rightarrow RGB$：

- 定义中间变量$q,p$为：
  $$
  \begin{cases}
  	q=\begin{align}\begin{cases}
  		L+LS&,L\in[0,\displaystyle\frac{1}{2})\\
  		L+S-LS&,L\in[\displaystyle\frac{1}{2},1]
  	\end{cases}\end{align}\\
  	p=2L-q\\
  \end{cases}
  $$

- 定义$t_R,t_G,t_B$分别为：
  $$
  \begin{cases}
  	t_R=\displaystyle\frac{h}{360}+\displaystyle\frac{1}{3}\mod1\\
  	t_G=\displaystyle\frac{h}{360}\mod1\\
  	t_B=\displaystyle\frac{h}{360}-\displaystyle\frac{1}{3}\mod1
  \end{cases}
  $$

- 最终结果为：
  $$
  RGB_{i(i\in\{R,G,B\})}=
  \begin{align}\begin{cases}
  	p+6(q-p)t_i&,t_i<\in[0,\displaystyle{\frac{1}{6}})\\
  	q&,t_i\in\displaystyle[\frac{1}{6},\frac{1}{2})\\
  	p+6(q-p)(\displaystyle\frac{2}{3}-t_i)&,t_i\in[\displaystyle\frac{1}{2},\displaystyle\frac{2}{3})\\
  	p&,t_i\in[\displaystyle\frac{2}{3},1]
  	
  \end{cases}\end{align}
  $$

#### §1.5.9.4 `currentColor`

该关键字表示当前元素的`color`属性值。

```html
<html>
<head>
    <style>
        .red {color: red;}
        .showBorder {
            border: 2px solid currentColor;
        }
    </style>
</head>
<body>
    <div class="showBorder red">
        这是一段文本
    </div>
</body>
</html>
```

### §1.5.10 角度

| 角度单位       | 作用              |
| -------------- | ----------------- |
| 角度(`deg`)    | 一圈为$360$度     |
| 百分度(`grad`) | 一圈为$100$百分度 |
| 弧度(`rad`)    | 一圈为$2\pi$弧度  |
| 圈数(`turn`)   |                   |

### §1.5.11 时间

| 时间单位   | 作用             |
| ---------- | ---------------- |
| 秒(`s`)    |                  |
| 毫秒(`ms`) | $1$秒=$1000$毫秒 |

### §1.5.12 频率

| 频率单位             | 作用                 |
| -------------------- | -------------------- |
| 赫兹(`hz`或`Hz`)     |                      |
| 千赫兹(`khz`或`hHz`) | $1$千赫兹=$1000$赫兹 |

### §1.5.13 自定义值

2017年，CSS引入了自定义属性。自定义属性以两个连字符开头`--`，可以在CSS中创建默认继承的属性，作为变量配合`var()`调用。从本质上来说，自定义属性就是宏。

```html
<html lang="en">
<head>
    <style>
        html {
            --base-color: #66ccff
        }
        h1 {
            color: var(--base-color);
        }
    </style>
</head>
<body>
    <h1>标题</h1>
</body>
</html>
```

众所周知，宏的使用方式是没有上限的。这里举一个例子：为不同缩进程度的无序列表设置不同的左边距长度。一般情况下，我们会考虑这样实现：

```css
ul li {margin-left: 2ch;}
ul ul li {margin-left: 4ch;}
ul ul ul li {margin-left: 6ch;}
ul ul ul ul li {margin-left: 8ch;}
```

现在使用自定义属性和`calc()`，就可以实现等价效果：

```css
html {
    --custom: 2;
}
@supports (color: var(--custom)){
    @supports (--custom: value){
        ul li {margin-left: calc(1 * var(--custom));}
        ul ul li {margin-left: calc(2 * var(--custom));}
        ul ul ul li {margin-left: calc(3 * var(--custom));}
        ul ul ul ul li {margin-left: calc(4 * var(--custom));}
    }
}

```

# §2 优先级、继承、层叠

优先级是规则的属性，可以表示为初值为`(0,0,0,0)`的四维向量`(x,y,z,t)`。如果多个规则针对同一个元素设置了冲突的样式，那么最终应该听谁的呢？答案是计算这些规则的优先级，比较时从前往后比较分量大小，率先能判断出分量高者胜出。

优先级计算规则如下所示：

1. 选择符中的每个`id`属性会让优先级增加`(0,1,0,0)`。
2. 选择符中的每个`class`属性、属性选择符`[]`、伪类会让优先级增加`(0,0,1,0)`。
3. 选择符中的每个元素和伪元素会让优先级增加`(0,0,0,1)`。
4. 连结符和通用选择符不增加优先级。

例如`html > body #answer table tr[id="total"] *.link`中出现了$1$个`id`属性，总共出现了$2$个`class`属性和属性选择符，出现了$4$个元素，因此该CSS规则的优先级为`(0,1,2,4)`。

现在我们已经知道了第二、三、四位分量的计算规则。其实第一位分量是为声明行内样式`<... style="...">`而设计的。它的第一位分量恒为`1`，有着最高的优先级。

## §2.1 重要声明

```mermaid
flowchart LR
subgraph unimportant["无重要声明"]
	declare1["声明"]
	declare2["声明"]
	declare3["声明"]
end
unimportant--"取优先级最高者"-->declare4["声明"]
subgraph important["!important"]
	declare5["声明"]
	declare6["声明"]
	declare7["声明"]
end
important--"取优先级最高者"-->declare8["声明"]
declare4 & declare8 --"取!important"--> declare9["最终生效的声明"]
```

可以使用`!important`表示该声明重要程度超过其它所有声明。`!important`本身并不会影响规则的优先级。所有规则会根据是否被`!important`声明分成两组，各自内部取优先级最高者，最后优先取`!important`声明的规则。

> 注意：从以上事实来看，我们知道，优先级并不是唯一一个决定最终效果的因素。优先级最高的规则，也可能不生效。

```css
p {
	color: red !important;
    background: white;
    font-weight: bold;
}
```

## §2.2 继承

某些样式不仅会应用到CSS所指的元素上，而且还会应用到其子元素上。这种现象被称为继承。将DOM树想象成一个从上向下生长的树，那么继承的方向为向下传播，也就是父元素传给子元素，直到子元素没有子元素为止。

> 注意：我们说继承是向下传播的，然而CSS规范中只有一处例外：当`<html>`标有规定背景，而`<body>`规定背景时，`background`属性会从`<body>`传播到`<html>`上。

真正能被允许继承的CSS属性只占一小部分。例如盒模型相关的、边框相关的属性肯定不能继承，但是`color`之类的属性可以继承。

继承的CSS属性没有优先级这一说。注意，不是零优先级，而是无优先级，可以理解为比零优先级还要低。

## §2.3 层叠

如果由两个发生冲突的规则，而且它们的优先级完全一样，那么到底选谁生效呢？这种情况下的抉择过程称为层叠。

CSS规定的层叠规则如下：

1. 按照显式权重（行内样式`important`>`!important`>无重要标记）进行排序，尝试选取最高者。
2. 按照来源（读者`!important`>创作人员>读者>用户代理）进行排序，尝试选取最高者。
   - 创作人员：引入的CSS文件或`<style>`标签内容
   - 读者：用户自行设计的CSS文件（浏览器脚本、审查元素）
   - 用户代理：浏览器预置样式（超链接样式、`<input>`样式、自带的阅读模式）
3. 按照优先级进行排序，尝试选取最高者。
4. 按照声明的先后顺序（越靠后权重越高）进行排序，选择最高者。

> 注意：在[§1.3.2.2 用户操作伪类](§1.3.2.2 用户操作伪类)一节中，我们知道实际工程中常常按照`LVFHA`顺序（`link-visited-focus-hover-active`）编写连接的样式。
>
> 经过本章的学习，我们已经知道了下列规则的优先级都是`(0,0,1,0)`：
>
> ```css
> a:link {color: red;}
> a:visited {color: red;}
> a:focus {color: red;}
> a:hover {color: red;}
> a:active {color: red;}
> ```
>
> 为了让这五个伪类实现预期的效果，`:link`和`:visited`必须放在`:hover`、`:focus`、`:active`的前面，否则后三者会被前两者覆盖，永远无法匹配。
>
> 除此之外，把伪类穿在一起，也能解决这一问题：
>
> ```css
> a:link {color: red;}
> a:visited {color: red;}
> a:link:hover {color: red;}
> a:visited:hover{color: red;}
> a:link:active {color: red;}
> a:visited:active {color: red;}
> ```

# §3 字体

## §3.1 字体族

我们知道，字体通常包含多个变体，例如粗体、斜体等等。例如`Times`字体，它的变体包括`TimesRegular`、`TimesBold`、`TimesItalic`、`TimesBoldItalic`等等。严格来说，`Times`不是一个字体，而是一个包含多个字形的字体族。

字体族使用`font-family`属性声明：

```css
body {
    font-family: sans-serif, Times;
}
```

浏览器从前向后查找计算机中是否包含声明的字体。如果不存在，则依次向后查找匹配。

CSS定义了五种通用字体族：

1. 衬线字体：有衬线，宽度不同。
2. 无衬线字体：无衬线，宽度不同。
3. 等宽字体：有衬线或无衬线，宽度相同。
4. 草书字体/手写体：有书法风格，比衬线字体更华丽。
5. 奇幻字体/装饰字体/展示字体：用于展示符号的字体。

## §3.2 `@font-face`

`@font-face`允许开发使用使用自定义的字体。通常情况下，浏览器只会从浏览器本地查找已安装的字体。现在有了`@font-face`，即使本地没有安装，浏览器也能使用服务器端的字体，而无需将其安装在本地。

```html
<html>
<head>
    <style>
        @font-face {
            font-family: CascadiaCodeRegular;
            src: url(./static/font/CascadiaCode/CascadiaCode-Regular.otf);
        }
        h1 {
            font-family: CascadiaCodeRegular;
        }
    </style>
</head>
<body>
    <h1>font-size()</h1>
</body>
</html>
```

在CSS规范中，浏览器应该采用懒加载机制——只有需要渲染指定字体的文本时才向服务器请求下载字体文件。2017年时，各大浏览器都未能实现这一机制。实测2023年Chrome已经能实现这一机制。

`@font-face`的`src`支持提供多个下载源，下载链接之间用逗号隔开。一些版本较旧的浏览器可能不支持新式字体标准，只有下载完字体文件后才能发现。为了解决这一问题，开发人员可以在CSS中用`format()`预先声明该字体使用的标准：

```css
@font-face {
	font-family: "SwitzeraADF",
    src: url("SwitzeraADF-Regular.otf") format("opentype"),
         url("SwitzeraADF-Regular.true") format("truetype");
}
```



目前CSS支持的字体格式如下所示：

| 格式                          | `format()`值        |
| ----------------------------- | ------------------- |
| EOT(Embedded OpenType)        | `embedded-opentype` |
| OTF(OpenType)                 | `opentype`          |
| SVG(Scalable Vector Graphics) | `svg`               |
| TTF(TrueType)                 | `truetype`          |
| WOFF(Web Open Font Format)    | `woff`              |

> 注意：一些旧的浏览器对`@font-face`的支持存在BUG。例如对于IE6，在`src`属性中填入多个备选`url()`，会导致只有第一个`url()`生效，其余`url()`一概返回404。
>
> 为了解决这一问题，研究人员使用IE6的另一个解析器BUG来绕过这个`url()`BUG——IE6遇到`?#iefix`会出发一个解析器BUG，从而认为该`url()`无效，转而向后寻找`url()`。
>
> ```css
> @font-face {
> 	font-family: "SwitzeraADF";
>     src: url("SwitzeraADF-Regular.eot");
>     src: url("SwitzeraADF-Regular.eot#iefix") format("embedded-opentype"),
>          url("SwitzeraADF-Regular.woff") format("woff"),
>          url("SwitzeraADF-Regular.ttf") format("truetype"),
>          url("SwitzeraADF-Regular.svg#switzera_adf_regular") format("svg");
> }
> ```

除了`font-family`和`src`这两个必需的属性外，CSS也为`@font-face`提供了额外的可选属性：

| 属性                    | 默认值       | 作用                                                         |
| ----------------------- | ------------ | ------------------------------------------------------------ |
| `font-style`            | `normal`     | 声明字形（常规、斜体、斜体                                   |
| `font-weight`           | `normal`     | 声明字重（粗体）                                             |
| `font-stretch`          | `normal`     | 声明字符宽度（紧缩、加宽）                                   |
| `font-variant`          | `normal`     | 声明字形变体（大小写字母）                                   |
| `font-feature-settings` | `normal`     | 声明OpenType底层特性（连字）                                 |
| `unicode-range`         | `U+0-10FFFF` | 声明可用字符范围。只有当前页面包含范围之内的Unicode字符时才加载。语法较灵活，支持属性值与通配符：`U+4E00-9FFFF, U+30??,U+A5` |

使用以上可选属性，我们终于可以用`@font-face`引入整个字体族，而不是单个字体了：

```html
<html>
<head>
    <style>
        @font-face {
            font-family: CascadiaCode;
            font-weight: normal;
            font-style: normal;
            font-stretch: normal;
            src: url(./static/font/CascadiaCode/CascadiaCode-Regular.otf) format("opentype");
        }
        @font-face {
            font-family: CascadiaCode;
            font-weight: bold;
            font-style: normal;
            font-stretch: normal;
            src: url(./static/font/CascadiaCode/CascadiaCode-Bold.otf) format("opentype");
        }
        @font-face {
            font-family: CascadiaCode;
            font-weight: normal;
            font-style: italic;
            font-stretch: normal;
            src: url(./static/font/CascadiaCode/CascadiaCode-Italic.otf) format("opentype");
        }
        @font-face {
            font-family: CascadiaCode;
            font-weight: bold;
            font-style: italic;
            font-stretch: normal;
            src: url(./static/font/CascadiaCode/CascadiaCode-BoldItalic.otf) format("opentype");
        }
        h1 {
            font-family: CascadiaCode;
        }
    </style>
</head>
<body>
    <h1 style="font-weight: normal; font-style: normal;">font-size()</h1>
    <h1 style="font-weight: bold; font-style: normal;">font-size()</h1>
    <h1 style="font-weight: normal; font-style: italic;">font-size()</h1>
    <h1 style="font-weight: bold; font-style: italic;">font-size()</h1>
</body>
</html>
```

## §3.3 字体属性

### §3.3.1 字重(`font-weight`)

CSS的`font-weight`属性用于控制自重，其可能的取值有：`normal`（等价于`400`）、`bold`（等价于`700`）、`bolder`、`lighter`、`100`、`200`、`300`、`400`、`500`、`600`、`700`、`800`、`900`。默认值为`normal`。

如果字体族中的字重等价少于规定的九个，则浏览器按照以下规则处理：

1. 如果`500`未定义，则将`500`定义为`400`。
2. 如果`300`未定义，则将`300`定义小于等于`200`的第一个变体
3. 如果`600`未定义，则将那个`600`定义为大于等于`700`的第一个变体。如果不存在，则将`600`定义为`500`
4. 如果`700`、`800`、`900`未定义，规则同第三条。
5. 如果`bolder`为定义，则将`bolder`定义为从`bold`向上查找遇到的第一个已定义的字形。

使用特性字重的字形有以下几种方法：

```html
<!-- 使用<strong>和标签 -->
<strong>123</strong>
<strong>粗<strong>更粗</strong></strong>

<!-- 使用CSS的font-weight属性 -->
<div style="font-weight: bold;">
    <div>粗</div>
    <div style="font-weight: bolder">
		更粗
    </div>
</div>
```

### §3.3.2 字号(`font-size`)

字号用于控制字体显示的大小。英文练习本中，一行有四条参考线，其中从上往下数的第一条线和第三条线称为基线，这个大小指的是两条基线之间的距离，所以一个字符的高度完全有可能超过字。它的默认值为`normal`，取值范围有：

1. `xx-small`、`x-small`、`small`、`medium`、`large`、`x-large`、`xx-large`、`smaller`、`larger`
2. `<length>`
3. `<percentage>`

#### §3.3.2.1 绝对大小

`font-size`支持的绝对大小关键字有：`xx-small`、`x-small`、`small`、`medium`、`large`、`x-large`、`xx-large`。

| 关键字     | CSS1       | CSS2       | CSS3       |
| ---------- | ---------- | ---------- | ---------- |
| `xx-small` | `5px`      | `9px`      | `10px`     |
| `x-small`  | `7px`      | `11px`     | `12px`     |
| `small`    | `11px`     | `13px`     | `14px`     |
| `medium`   | **`16px`** | **`16px`** | **`16px`** |
| `large`    | `24px`     | `19px`     | `19px`     |
| `x-large`  | `36px`     | `23px`     | `24px`     |
| `xx-large` | `54px`     | `28px`     | `32px`     |

需要注意的是，`medium`的值并不恒为`16px`。不同的浏览器，不同的HTML标签，甚至不同类型的字体都可能会认为`medium`不为`16px`：

```html
<html>
<head>
    <style>
        p {font-size: medium;}
        span {font-family: monospace;font-size: 1em;}
    </style>
</head>
<body>
    <p>123<span>123</span></p>
</body>
</html>
```

这是因为字号向下传递时，传递的永远是关键字。在普通字体中，`medium`默认是`16px`，而对于等宽字体来说，默认字号`medium`是`13px`。为解决这一问题，一种通用的方法是在`monospace`之后补充`,serif`。

#### §3.3.2.2 相对大小

`font-size`支持的相对大小关键字有：`larger`和`smaller`，相邻两级的字号相差`1.2`倍。

```html
<html>
<head>
    <style>
        bigger {
            font-size: larger;
        }
    </style>
</head>
<body>
    <div>
        <span>123</span>
        <bigger>
            <span>123</span>
            <bigger>
                <span>123</span>
            </bigger>
        </bigger>
    </div>
</body>
</html>
```

#### §3.3.2.3 百分数与`em`

百分数和`em`参考的对象是父元素的字号。

```html
<html>
<head>
    <style>
        bigger {
            font-size: 200%;
            font-size: 2em; /* 两种方式等价 */
        }
    </style>
</head>
<body>
    <div>
        <span>123</span>
        <bigger>
            <span>123</span>
            <bigger>
                <span>123</span>
            </bigger>
        </bigger>
    </div>
</body>
</html>
```

#### §3.3.2.4 自动调整字号(`font-size-adjust`)

给定一款字形，我们定义这个字形的高宽比值为小写字母`x`的高度除以字号。在旧版本浏览器中，当其已加载完HTML，但未加载完CSS时，就会使用默认样式来渲染。因此存在一瞬间，用户看到的是未经CSS修饰的文本。`font-size-adjust`可以用于更改字形的高宽比值，使文字更容易阅读；也可以减轻默认样式渲染差异带来的影响。

例如给定`Verdana`和`Times`两种同字号`10px`字体，我们很明显就能看出这两种字形的实际显示大小不一致。这是因为它们的高宽比值分别为`0.58`和`0.46`，值越大就说明在字号相等的前提下，字体实际显示大小越大。

`font-size-adjust`对`font-size`的影响如下所示：
$$
\text{font-size}_{\color{red}{\text{new}}}=\text{font-size}_{\color{red}{\text{raw}}}\times\frac{\text{font-size-adjust}}{高宽比值}
$$
只要我们把`Times`字体的`font-size-adjust`设置成`Verdana`的高宽比值，就能弥补高宽比值差异造成的影响：

```html
<html>
<head>
    <style>
        p {font-size: 10px;}
        p.font1 {
            font-family: Verdana, sans-serif; 
        }
        p.font2 {
            font-family: Times, serif;
            font-size-adjust: 0.58;
        }
    </style>
</head>
<body>
    <p class="font1">abc123</p>
    <p class="font2">abc123</p>
</body>
</html>
```

实际上，我们不需要知道字体的高宽比值，仅仅使用`auto`关键字，浏览器就会自动计算。

> 注意：在2017年，唯一支持`font-size-adjust`属性的浏览器只有Firefox。经2023年Chrome实测，`font-size-adjust`产生的效果近乎可以忽略不计。

### §3.3.3 字形(`font-style`)

`font-style`负责控制字形，只有常规(`normal`)、斜体(`italic`)、倾斜体(`oblique`)这三种取值。

斜体和倾斜体虽然都能让字体倾斜，但是斜体注重手写的程序，而倾斜体只是单纯的印刷体。现在字体设计界对字形的支持较差，一般将斜体和倾斜体混为一谈。

```html
<html>
<head>
    <style>
        p {font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;}
        .type1 {font-style: italic;}
        .type2 {font-style: oblique;}
    </style>
</head>
<body>
    <p class="type1">abc123</p>
    <p class="type2">abc123</p>
</body>
</html>
```

### §3.3.4 字体拉伸(`font-stretch`)

有些字体族提供了较宽或较窄的字符形式，这些变体通常被命名为`Condensed`、`Wide`、`Ultra Expanded`等标识。它的取值范围有：`normal`、`ultra-condensed`、`extra-condensed`、`condensed`、`semi-condensed`、`expanded`、`extra-expanded`、`ultra-expanded`。

```html
<html>
<head>
    <style>
        @font-face {
            font-family: "Inconsolata";
            src: url("https://fonts.gstatic.com/s/inconsolata/v31/QlddNThLqRwH-OJ1UHjlKENVzlm-WkL3GZQmAwPyya15.woff2") format("woff2");
            font-stretch: 50% 200%;
        }

        p {
            font-family: Inconsolata;
        }

        p.type1 {
            font-stretch: extra-condensed;
        }

        p.type2 {
            font-stretch: extra-expanded;
        }
    </style>
</head>
<body>
    <p class="type1">abc123</p>
    <p class="type2">abc123</p>
</body>
</html>
```

### §3.3.5 字距(`font-kerning`)

字符之间相对位置的长度称为字距。它和`letter-spacing`最大的差别在于：`font-kerning`允许字符之间真正地按照规律紧凑起来。例如我们手写`To`这个单词时，会将`o`写到`T`的右下角，而`letter-spacing`就有可能让`o`碰到`T`的横杠。

截止2023年，只有Firefox支持该特性。

### §3.3.6 字体特性(`font-feature-settings`)

`font-feature-settings`属性可以从底层控制OpenType字体(`.otf`)支持的特性，因此不能应用于其它字体格式中。

OpenType字体支持特性参见[微软帮助文档](https://learn.microsoft.com/en-us/typography/opentype/spec/featurelist)。在这些特性中，默认开启的有以下特性：

| OpenType特性 | 作用           |
| ------------ | -------------- |
| `calt`       | 根据上下文替换 |
| `ccmp`       | 组合字符       |
| `clig`       | 根据上下文连字 |
| `liga`       | 标准连字       |
| `locl`       | 本地化形式     |
| `mark`       | 基本定位标记   |
| `mkmk`       | 标记定位标记   |
| `rlig`       | 必要的连字     |

```html
<html>
<head>
    <style>
        @font-face {
            font-family: CascadiaCode;
            src: url(./static/font/CascadiaCode/CascadiaCode-Regular.otf);
        }
        p {font-family: CascadiaCode;}
        .style1 { font-feature-settings: "liga" off, "calt" off, "clig" off, "rlig" off; }
        .style2 { font-feature-settings: "liga" on , "calt" on , "clig" on , "rlig" on; }

    </style>
</head>
<body>
    <p class="style1">(()=>{1===0})();</p>
    <p class="style2">(()=>{1===0})();</p>
</body>
</html>
```

### §3.3.7 字体变形(`font-variant`)

CSS3提供了字体变形`font-variant`属性及其附属的多个子属性。字体变形包括连写、大小写、小数、`z`和`0`的贯穿线等特征。该属性需要字体本身支持。

例如使用小号大写字母，每个单词都以大写字母展示，且首字母字号稍大。

```html
<html>
<head>
    <style>
        h1 {
            font-variant: small-caps;
        }
    </style>
</head>
<body>
    <h1>Every Letter Is In Captial!</h1>
</body>
</html>
```

#### §3.3.7.1 `font-variant-ligatures`

决定英文字母（例如`fi`）是否连字。

#### §3.3.7.2 `font-variant-caps`

决定英文字母是否以小号大写方式呈现。

```html
<html>
<head>
    <style>
        .style1 {font-variant: normal;}
        .style2 {font-variant: small-caps;}
        .style3 {font-variant: all-small-caps;}
    </style>
</head>
<body>
    <h1 class="style1">Hello</h1>
    <h1 class="style2">Hello</h1>
    <h1 class="style3">Hello</h1>
</body>
</html>
```

#### §3.3.7.3 `font-variant-numeric`

决定数字显示方式。例如`0`是否有贯穿线，数字是否上下交错排布。

## §3.4 总属性`font`

总属性`font`决定着五个子属性，分为两组，第一组是`font-style`、`font-weight`、`font-variant`，第二组是`font-size[/line-height]`、`font-family`。

第一组的三个属性非常宽松，声明顺序没有限制，而且都可以缺省为`normal`。第二组的两个属性较为严格，声明顺序不能打乱，而且都不能缺省。虽然`line-height`本身不属于字体的属性，但是也可以在`font`属性中跟随`font-size`共同指定，写成类似于`24px/1.5`的格式。

```css
font: bold italic 24px Verdana, Helvetica, Arial, sans-serif;
```

除此之外，开发人员也可以不使用以上五个子属性，而是使用操作系统设置的默认值。操作系统提供的配置往往更能与系统本身达成一致性设计的效果，这些配置称为系统字体。可用的系统字体有：

| 系统字体        | 作用                       |
| --------------- | -------------------------- |
| `caption`       | 用于说明文字的控件（按钮） |
| `icon`          | 图表                       |
| `menu`          | 菜单（下拉菜单、菜单列表） |
| `message-box`   | 对话框                     |
| `small-caption` | 标注小型控件               |
| `status-bar`    | 窗口状态栏                 |

```html
<h1 style="font: caption;">text</h1>
<h1 style="font: icon;">text</h1>
<h1 style="font: menu;">text</h1>
<h1 style="font: message-box;">text</h1>
<h1 style="font: small-caption;">text</h1>
<h1 style="font: status-bar;">text</h1>
```

# §4 文本

## §4.1 行内与块级

块级方向指的是当前书写模式放置块级元素的方向。在英语中，块级方向是从上到下，也就是说一个自然段放在另一个自然段的下面。

行内元素指的是块级元素中行内元素的书写方向。在英语中，行内方向从左向右。

## §4.2 行内属性

### §4.2.1 缩进(`text-indent`)

`text-indent`用于设置第一行文本的缩进长度，可以是负值，默认向子元素继承。

```html
<div style="width: 100px; background-color: coral;">
    <p style="text-indent: 1ch;">这是第一段:</p>
    <p style="text-indent: 2ch;">这是第二段：</p>
    <p style="text-indent: 4ch;">这是第三段：</p>
</div>
```

```html
<div style="width: 100px; background-color: coral; padding-left: 4em;">
    <p style="text-indent: -1ch;">悬挂缩进Demo:</p>
    <p style="text-indent: -2ch;">悬挂缩进Demo:</p>
    <p style="text-indent: -4ch;">悬挂缩进Demo:</p>
</div>
```

### §4.2.2 横向对齐(`text-align`/`text-align-last`)

`text-align`用于设置文本各行的对齐方式。

| `text-align`属性值 | 作用                         |
| ------------------ | ---------------------------- |
| `start`            | 靠当前语言的书写起点向其对齐 |
| `end`              | 靠当前语言的书写起点向其对齐 |
| `left`             | 无论语言，一概向左对齐       |
| `right`            | 无论语言，一概向右对齐       |
| `center`           | 除最后一行以外，居中对齐     |
| `justify`          | 首行两端对齐                 |

```html
<div style="width: 80px; background-color: coral;;">
    <p style="text-align: start;">Hello world, this is a text-align demo.</p>
    <p style="text-align: end;">Hello world, this is a text-align demo.</p>
    <p style="text-align: left;">Hello world, this is a text-align demo.</p>
    <p style="text-align: right;">Hello world, this is a text-align demo.</p>
    <p style="text-align: center;">Hello world, this is a text-align demo.</p>
    <p style="text-align: justify;">Hello world, this is a text-align demo.</p>
</div>
```

`text-align-last`用于设置最后一行的对齐方式，其取值与`text-align`常用属性值相同。当文本只有一行时，`text-align-last`的优先级高于`text-align`的优先级。

## §4.3 块级属性

### §4.3.1 行高(`line-height`)

`line-height`属性指定行与行之间的基线距离。从这一点来说，行距等于行高减去字体高度。当`line-height`的属性值为距离单位时，属性值代表的是绝对距离；当属性值为无量纲数时，代表的时从父元素继承`line-height`属性值时使用的换算比例。

```html
<html>
<head>
    <style>
        p {background-color: wheat;}
    </style>
</head>
<body>
    <div style="width: 80px;">
        <p style="line-height: 5px;">123123</p>
        <p style="line-height: 10px;">123123</p>
        <p style="line-height: 15px;">123123</p>
        <p style="line-height: 20px;">123123</p>
        <p style="line-height: 25px;">123123</p>
    </div>
</body>
</html>
```

### §4.3.2 纵向对齐(`vertical-align`)

| `vertical-align`属性值 | 作用                                                         |
| ---------------------- | ------------------------------------------------------------ |
| `baseline`(默认值)     | 让元素的基线与父元素该行的基线对齐                           |
| `sub`                  | 让元素的基线低于父元素该行的基线，即放在下标处。CSS没有规定下降的距离，显示效果受限于浏览器， |
| `super`                | 让元素的基线高于父元素该行的基线，即放在上标处。CSS没有规定上升的距离，显示效果受限于浏览器， |
| `top`                  | 让元素的顶边与父元素该行的顶边对齐                           |
| `text-top`             | 让元素的基线与父元素该行的顶边对齐                           |
| `middle`               | 让元素的中线与父元素该行的中线对齐                           |
| `bottom`               | 让元素的底边与父元素该行的底边对齐                           |
| `text-bottom`          | 让元素的基线与父元素该行的底边对齐                           |

```html
<html>
<head>
    <style>
        p {
            background-color: lightgreen;
            line-height: 40px;
        }
        p > img {height: 10px; width: 10px; background-color: gold;}
    </style>
</head>
<body>
    <div style="width: 300px;">
        <p>
            <span style="vertical-align: super;">忐</span>
            <span style="vertical-align: sub;">忑</span>
            <span>不安 :)</span>
        </p>
        <p>vertical-align: baseline<img style="vertical-align: baseline;"/></p>
        <p>vertical-align: sub<img style="vertical-align: sub;"/></p>
        <p>vertical-align: super<img style="vertical-align: super;"/></p>
        <p>vertical-align: top<img style="vertical-align: top;"/></p>
        <p>vertical-align: text-top<img style="vertical-align: text-top;"/></p>
        <p>vertical-align: middle<img style="vertical-align: middle;"/></p>
        <p>vertical-align: bottom<img style="vertical-align: bottom;"/></p>
        <p>vertical-align: text-bottom<img style="vertical-align: text-bottom;"/></p>
    </div>
</body>
</html>
```

| `vertical-align`属性值 | 作用                                                         |
| ---------------------- | ------------------------------------------------------------ |
| 百分数                 | 相对于父元素的`line-height`，将元素的基线从父元素的基线抬升或下沉的百分比。负数为下降，正数为上升 |
| 绝对长度               | 从CSS2引入，指定上升或下沉的距离                             |

```html
<html>
<head>
    <style>
        p {
            background-color: lightgreen;
            line-height: 40px;
        }
        p > img {height: 10px; width: 10px; background-color: gold;}
    </style>
</head>
<body>
    <div style="width: 300px;">
        <p>vertical-align: -100%<img style="vertical-align: -100%;"/></p>
        <p>vertical-align: -50%<img style="vertical-align: -50%;"/></p>
        <p>vertical-align: 0%<img style="vertical-align: 0%;"/></p>
        <p>vertical-align: 50%<img style="vertical-align: 50%;"/></p>
        <p>vertical-align: 100%<img style="vertical-align: 100%;"/></p>
    </div>
</body>
</html>
```

## §4.4 间距

### §4.4.1 单词间距(`word-spacing`)

`word-spacing`决定了单词之间的距离。这里的“单词”指的是两侧有空白字符的仅包含非空白字符的字符串。该属性默认为`normal`，等价于绝对长度`0`。正值时加大间距，负值时缩短间距。受制于CSS对于单词的定义，该属性不适用于象形文字等非罗马文字。

```html
<p style="word-spacing: -1.0em;">Hello World!</p>
<p style="word-spacing: -0.5em;">Hello World!</p>
<p style="word-spacing: 0.0em;">Hello World!</p>
<p style="word-spacing: normal;">Hello World!</p>
<p style="word-spacing: 0.5em;">Hello World!</p>
<p style="word-spacing: 1.0em;">Hello World!</p>
```

该属性会受到`text-align: justify`的影响。

### §4.4.2 字符间距(`letter-spacing`)

`letter-spacing`决定了字符之间的距离。该属性默认为`normal`，等价于绝对长度`0`。正值时加大间距，负值时缩短间距。

```html
<p style="letter-spacing: 0.1em;">Hello, 世界!</p>
<p style="letter-spacing: 0em;">Hello, 世界!</p>
<p style="letter-spacing: normal;">Hello, 世界!</p>
<p style="letter-spacing: -0.1em;">Hello, 世界!</p>
```

## §4.5 文本转换(`text-transform`)

`text-transform`专门用于转变文本的大小写。

| `text-transform`属性值 | 作用                 |
| ---------------------- | -------------------- |
| `uppercase`            | 全大写               |
| `lowercase`            | 全小写               |
| `captialize`           | 每个单词的首字母大写 |
| `none`(缺省)           | 无转换               |

```html
<p>hello, ABC</p>
<p style="text-transform: none;">hello, ABC</p>
<p style="text-transform: uppercase;">hello, ABC</p>
<p style="text-transform: lowercase;">hello, ABC</p>
<p style="text-transform: capitalize;">hello, ABC</p>
```

## §4.6 文本装饰(`text-decoration`)

`text-decoration`属性决定文本的装饰形式。

| `text-decoration`属性值 | 作用                                         |
| ----------------------- | -------------------------------------------- |
| `none`(缺省)            | 无效果                                       |
| `underline`             | 下划线，等价于`<u></u>`                      |
| `overline`              | 上划线                                       |
| `line-through`          | 删除线，等价于`<strike></strike>`或`<S></S>` |

```html
<a href="google.com">Google</a>
<a href="google.com" style="text-decoration: none;">Google</a>
<p style="text-decoration: none;">hello, ABC.</p>
<p style="text-decoration: underline;">hello, ABC.</p>
<p style="text-decoration: overline;">hello, ABC.</p>
<p style="text-decoration: underline overline;">hello, ABC.</p>
<p style="text-decoration: line-through;">hello, ABC.</p>
```

`text-decoration`属性不参与继承，但是父元素产生的装饰线属性会覆盖在子元素上面，导致子元素无法通过声明`text-decoration: none`来去除自己身上的装饰线。但是子元素可以声明自己的装饰线，且其图层在父元素装饰线之上，起到覆盖的作用。

## §4.7 文本渲染效果(`text-rendering`)

`text-rendering`本质上不是CSS属性，而是一个SVG属性，决定了浏览器在显示文本时应该优先考虑什么方面。

| `text-rendering`属性值 | 作用                                         |
| ---------------------- | -------------------------------------------- |
| `auto`(缺省)           | 无标准，由浏览器自行决定                     |
| `optimizeSpeed`        | 优先考虑绘制速度，而不是清晰性（紧排和连字） |
| `optimizeLegibility`   | 优先考虑清晰性（紧排和连字），而不是绘制速度 |
| `geometricPrecision`   | 优先考虑SVG矢量精确性，以SVG绘制字形         |

## §4.8 文本阴影(`text-shadow`)

`text-shadow`属性可以给文本设置多个阴影，每组阴影值用逗号分隔。每个阴影由四个值定义：

1. 第一个属性值：颜色。可以为颜色关键字或函数式RGB颜色。实际上该属性可以放在首部或尾部。

   ```html
   <h1 style="text-shadow: black 0 0 4px;">123</h1> <!-- 生效 -->
   <h1 style="text-shadow: 0 black 0 4px;">123</h1> <!-- 无效 -->
   <h1 style="text-shadow: 0 0 black 4px;">123</h1> <!-- 无效 -->
   <h1 style="text-shadow: 0 0 4px black;">123</h1> <!-- 生效 -->
   ```

2. 第二个属性值：横向位置偏移距离。正数为右，负数为左。

3. 第三个属性值：纵向位置偏移距离。正数为下，负数为上。

4. 第四个属性值：模糊半径。可选。具体的模糊算法由浏览器决定。

```html
<html>
<head>
    <style>
        h1 { color: red; }
        .type1 { 
            text-shadow: 1em 0 5px black, -1em 0 5px blue; 
        }
    </style>
</head>
<body>
    <h1 class="type1">Hello</h1>
</body>
</html>
```

> 注意：大量阴影或模糊半径较大的阴影会消耗大量CPU性能。

## §4.9 空白(`white-space`)

`white-space`属性用于指定浏览器对空格、换行符、制表符的处理方式。

根据[MDN文档](https://developer.mozilla.org/zh-CN/docs/Web/CSS/white-space)，`white-space`有以下取值：

| `white-space`属性值 | 换行符 | 空格和制表符 | 文本换行 | 行末空格 | 行末的其他空白分隔符 |
| :------------------ | :----- | :----------- | :------- | :------- | -------------------- |
| `normal`            | 合并   | 合并         | 换行     | 移除     | 挂起                 |
| `nowrap`            | 合并   | 合并         | 不换行   | 移除     | 挂起                 |
| `pre`               | 保留   | 保留         | 不换行   | 保留     | 不换行               |
| `pre-wrap`          | 保留   | 保留         | 换行     | 挂起     | 挂起                 |
| `pre-line`          | 保留   | 合并         | 换行     | 移除     | 挂起                 |
| `break-spaces`      | 保留   | 保留         | 换行     | 换行     | 换行                 |

```html
<html>
<body>
    <div style="width: 200px; background-color: gray;">
        <select>
            <option>normal</option>
            <option>nowrap</option>
            <option>pre</option>
            <option>pre-wrap</option>
            <option>pre-line</option>
            <option>break-spaces</option>
            <option>preserve nowrap</option>
        </select>
        <p>
            This is a very very very long sentence whose length is far longer than container's width.
            This is another very very very long sentence.
        </p>
    </div>
    <script>
        const selectDOM = document.querySelector("select");
        const paragraphDOM = document.querySelector("p");
        selectDOM.addEventListener("change", (e)=>{
            paragraphDOM.setAttribute("style", `white-space: ${e.target.value}`);
        });
    </script>
</body>
</html>
```

## §4.10 制表符宽度(`tab-size`)

`tab-size`用于指定制表符字符的宽度。该属性仅当`white-space`保留空格和制表符时才生效。

| `tab-size`属性值           | 作用                   |
| -------------------------- | ---------------------- |
| 整数值                     | 表示几个连续空格的长度 |
| 单位长度(例如`2px`,`1rem`) | 表示绝对长度           |

```html
<html>
<head>
    <style>
        p {white-space: pre;}
    </style>
</head>
<body>
    <div>
        <p style="white-space: normal;">&#09;This sentence start with a tab character.</p>
        <p style="tab-size: 1;">&#09;This sentence start with a tab character.</p>
        <p style="tab-size: 2;">&#09;This sentence start with a tab character.</p>
        <p style="tab-size: 4;">&#09;This sentence start with a tab character.</p>
        <p style="tab-size: 8;">&#09;This sentence start with a tab character.</p>
        <p>&#09;This sentence start with a tab character.</p>
    </div>
</body>
</html>
```

## §4.11 换行和断字

如果行宽较短，但是单词很长时，通常使用连字符。HTML提供了`&shy;`实体，Unicode也提供了`\u00ad`，两者都能供浏览器显示连字符时进行参考。`hyphens`属性决定连字符在何种情况下显示：

| `hyphens`属性值 | 作用                                     |
| --------------- | ---------------------------------------- |
| `manual`(缺省)  | 只根据手动生命的连字符显示连字符         |
| `auto`          | 自动根据语法和手动声明的连字符显示连字符 |
| `none`          | 不显示任何连字符                         |

```html
<!DOCTYPE html>
<html>

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <style type="text/css">
        * {
            padding: 0;
            margin: 0;
        }

        #app-wrapper {
            position: absolute;
            cursor: move;
        }
        code {
            font-family:'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;
            font-weight: bold;
        }
    </style>
</head>

<body>
    <div>
        <div>
            是否携带<code>&amp;shy;</code>实体:
            <select id="shy-entity">
                <option>是</option>
                <option>否</option>
            </select>
        </div>
        <div>
            <code>hyphens</code>属性值:
            <select id="hyphens">
                <option>manual</option>
                <option>auto</option>
                <option>none</option>
            </select>
        </div>
    </div>
    <div id="app-wrapper">
        <p id="paragraph" style="width: 100%;">Super&shy;cali&shy;fragi&shy;listic&shy;expi&shy;ali&shy;docious anti&shy;dis&shy;establish&shy;ment&shy;arian&shy;ism.</p>
    </div>
    <script>
        const shyDOM = document.querySelector("#shy-entity");
        const hyphensDOM = document.querySelector("#hyphens");
        const paragraphDOM = document.querySelector("#paragraph");
        shyDOM.addEventListener("change", (e)=>{
            if(e.target.value === "是"){
                paragraphDOM.innerHTML = "Super&shy;cali&shy;fragi&shy;listic&shy;expi&shy;ali&shy;docious anti&shy;dis&shy;establish&shy;ment&shy;arian&shy;ism."
            }else if(e.target.value === "否"){
                paragraphDOM.innerHTML = "Supercalifragilisticexpialidocious antidisestablishmentarianism."
            }
        });
        hyphensDOM.addEventListener("change", (e)=>{
            paragraphDOM.setAttribute("style", `width: 100%; hyphens:${e.target.value};`);
        })
    </script>
</body>
<script>
    /**
     * 创建一个可拖拽的矩形
     */
    function CreateDragRect(elm, options = {}) {
        if (!elm) throw new Error('el 必须是一个document对象');
        this.rect = elm;
        this.isLeftMove = true;
        this.isTopMove = true;
        this.rectDefaultPosition = options.position || 'fixed';
        this.rectDefaultLeft = options.x || 0;
        this.rectDefaultTop = options.y || 0;
        this.rectWidth = options.width || 100;
        this.rectHeight = options.height || 100;
        this.rectMinWidth = options.rectMinWidth || 5;  //最小宽度(超过之后不允许再缩放)
        this.rectMinHeight = options.rectMinHeight || 5;  //最小高度(超过之后不允许再缩放)
        this.rectBackgroundColor = options.background || '#ccc';
        this.dragIconSize = options.dragIconSize || '4px';
        this.dragIconColor = options.dragIconColor || '#f00';
        //主矩形是否可以移动
        this.isMove = false;
        this.initStyle();
        this.bindDragEvent(this.rect);
    }

    /**
     * 主矩形绑定move事件
     */
    CreateDragRect.prototype.bindDragEvent = function (dom, position) {
        const _this = this;
        dom.onmousedown = function (event) {
            event.stopPropagation();
            //按下矩形的时候可以移动，否则不可移动
            _this.isMove = !position;
            // 获取鼠标在wrapper中的位置
            let boxX = event.clientX - dom.offsetLeft;
            let boxY = event.clientY - dom.offsetTop;
            //鼠标移动事件(如果计算太高,有拖影)
            document.onmousemove = _this.throttle(function (moveEv) {
                let ev = moveEv || window.event;
                ev.stopPropagation();
                let moveX = ev.clientX - boxX;
                let moveY = ev.clientY - boxY;
                switch (position) {
                    case 'top-left':    //左上: 需计算top left width
                        _this.nwRectSize(moveX, moveY);
                        break;
                    case 'top-right':   //右上 计算top 和 height
                        _this.neRectSize(moveX, moveY);
                        break;
                    case 'right-bottom':  //只需计算当前鼠标位置
                        _this.seRectSize(moveX, moveY);
                        break;
                    case 'left-bottom': //计算left偏移量，计算w
                        _this.swRectSize(moveX, moveY);
                        break;
                    default:    //拖拽矩形
                        if (!_this.isMove) return null;
                        _this.moveRect(ev.clientX - boxX, ev.clientY - boxY);
                }
            }, 15);

            //鼠标松开，移除事件
            document.onmouseup = function (event) {
                document.onmousemove = null;
                document.onmouseup = null;
                // 存储当前的rect的宽高
                _this.rectWidth = _this.rect.offsetWidth;
                _this.rectHeight = _this.rect.offsetHeight;
                // 获得当前矩形的offsetLeft 和 offsetTop
                _this.rectOffsetLeft = _this.rect.offsetLeft;
                _this.rectOffsetTop = _this.rect.offsetTop;
            }
        }
    }

    /**
     * 初始化样式
     */
    CreateDragRect.prototype.initStyle = function () {
        this.rect.style.position = this.rectDefaultPosition;
        this.rect.style.width = this.rectWidth + 'px';
        this.rect.style.height = this.rectHeight + 'px';
        this.rect.style.left = this.rectDefaultLeft + 'px';
        this.rect.style.top = this.rectDefaultTop + 'px';
        this.rect.style.background = this.rectBackgroundColor;
        //依次为上 右 下 左
        let dragIcons = [
            {
                cursor: 'nw-resize',
                x: 'top',
                y: 'left'
            },
            {
                cursor: 'ne-resize',
                x: 'top',
                y: 'right'
            },
            {
                cursor: 'se-resize',
                x: 'right',
                y: 'bottom'
            },
            {
                cursor: 'sw-resize',
                x: 'left',
                y: 'bottom'
            }
        ];
        for (let i = 0, l = dragIcons.length; i < l; i++) {
            let icon = document.createElement('i');
            icon.id = Math.random().toString(36).substring(7);
            icon.style.display = 'inline-block';
            icon.style.width = this.dragIconSize;
            icon.style.height = this.dragIconSize;
            icon.style.position = 'absolute';
            icon.style.zIndex = 10;
            icon.style.cursor = dragIcons[i].cursor;
            icon.style.backgroundColor = this.dragIconColor;
            icon.style[dragIcons[i].x] = -parseInt(icon.style.width) / 2 + 'px';
            icon.style[dragIcons[i].y] = -parseInt(icon.style.height) / 2 + 'px';
            //绑定四个角的拖拽事件
            this.bindDragEvent(icon, `${dragIcons[i].x}-${dragIcons[i].y}`);
            //插入到矩形
            this.rect.appendChild(icon);
        }
    };

    /**
     * 移动主矩形
     */
    CreateDragRect.prototype.moveRect = function (x, y) {
        if (this.isTopMove && this.isLeftMove) {
            this.rect.style.left = x + 'px';
            this.rect.style.top = y + 'px';
        }
    };

    /**
     * 移动主矩形缩放 - 左上
     */
    CreateDragRect.prototype.nwRectSize = function (x, y) {
        //计算是否是最小宽度
        const { width, height, isLeftMove, isTopMove } = this.getMinSize(this.rectWidth - x, this.rectHeight - y);
        if (isTopMove) {
            this.rect.style.top = this.rectOffsetTop + y + 'px';
            this.rect.style.height = height + 'px';
        }
        if (isLeftMove) {
            this.rect.style.left = this.rectOffsetLeft + x + 'px';
            this.rect.style.width = width + 'px';
        }
    };

    /**
     * 移动主矩形缩放 - 左下
     */
    CreateDragRect.prototype.swRectSize = function (x, y) {
        //计算是否是最小宽度
        const { width, height, isLeftMove, isTopMove } = this.getMinSize(this.rectWidth - x, y);
        if (isLeftMove) {
            this.rect.style.left = this.rectOffsetLeft + x + 'px';
            this.rect.style.width = width + 'px';
        }
        if (isTopMove) {
            this.rect.style.height = height + 'px';
        }
    };

    /**
     * 移动主矩形缩放 - 右上
     */
    CreateDragRect.prototype.neRectSize = function (x, y) {
        //计算是否是最小宽度
        const { width, height, isTopMove, isLeftMove } = this.getMinSize(x, this.rectHeight - y);
        if (isTopMove) {
            this.rect.style.height = height + 'px';
            this.rect.style.top = this.rectOffsetTop + y + 'px';
        }
        if (isLeftMove) {
            this.rect.style.width = width + 'px';
        }
    };

    /**
     * 移动主矩形缩放 - 右下
     */
    CreateDragRect.prototype.seRectSize = function (x, y) {
        //计算是否是最小宽度
        const { width, height } = this.getMinSize(x, y);
        this.rect.style.width = width + 'px';
        this.rect.style.height = height + 'px';
    };

    /**
    * 节流函数
    * @param {*} fn 
    * @param {*} delay 
    */
    CreateDragRect.prototype.throttle = function (fn, delay) {
        let last = 0;
        return function () {
            let curr = Date.now();
            if (curr - last > delay) {
                fn.apply(this, arguments);
                last = curr;
            }
        }
    }

    /**
     * 获取宽高
     * @param {*} w 
     * @param {*} h 
     * @return { Object }
     */
    CreateDragRect.prototype.getMinSize = function (w, h) {
        let rectMinWidth = this.rectMinWidth;
        let rectMinHeight = this.rectMinHeight;
        //x拖拽
        this.isLeftMove = w >= this.rectMinWidth;
        //y拖拽
        this.isTopMove = h >= this.rectMinHeight;
        if (this.isLeftMove) rectMinWidth = w;
        if (this.isTopMove) rectMinHeight = h;
        return { width: rectMinWidth, height: rectMinHeight, isLeftMove: this.isLeftMove, isTopMove: this.isTopMove };
    }
    const dr = new CreateDragRect(document.getElementById('app-wrapper'), {
        x: 50,
        y: 100,
        width: 300,
        height: 100,
    });
</script>

</html>
```

我们知道，`<br>`与`\n`都是硬换行。当一个文本太长时，浏览器会自动为其换行，这种换行称为软换行。`work-brak`属性决定了软换行的行为。

| `word-break`属性值 | 作用                                   | 非CJK行为    | CJK行为      | 断字 |
| ------------------ | -------------------------------------- | ------------ | ------------ | ---- |
| `normal`(默认)     | 只在单词之间换行                       | 照常         | 照常         | 有   |
| `break-all`        | 可以在任何字符之间软换行               | 任何字符之间 | 任何字符之间 | 无   |
| `keep-all`         | 只在单词之间换行，除非单词只有一个字符 | 照常         | 序列两侧     | 有   |

`line-break`属性用于更精细地控制CJK的断字行为。

| `line-break` 属性值 | 作用                               |
| ------------------- | ---------------------------------- |
| `auto`(缺省)        | 让浏览器自主决定                   |
| `loose`             | 宽松的换行规则，用于文本较短的情况 |
| `normal`            | 常规的换行规则                     |
| `strict`            | 严格的换行规则                     |

## §4.12 书写模式(``writing-mode`)

不同的语言有着不同的书写方向。例如英语从左到右从上到下，阿拉伯语从右到左从上到下，汉语和日语从上到下，也可以从左到右，蒙古语从右到左。`writing-mode`用于控制书写模式：

| `writing-mode`属性值  | 作用               |
| --------------------- | ------------------ |
| `horizontal-tb`(缺省) | 从左到右，从上到下 |
| `vertical-rl`         | 从上到下，从右到左 |
| `vertical-lr`         | 从上到下，从左到右 |

```html
<html>
<head>
    <title>Figure</title>
    <style type="text/css">
    </style>
    <style type="text/css">
        p {
            border: 1px dotted;
            width: 15em;
            height: 6em;
        }
    </style>
</head>
<body>
    writing-mode:
    <select id="writing-mode">
        <option>horizontal-tb</option>
        <option>vertical-rl</option>
        <option>vertical-lr</option>
    </select>
    <div>
        <p>This is a paragraph of English text, largely unstyled.</p>
    </div>
    <script>
        const selectDOM = document.querySelector("#writing-mode");
        const paragraphDOM = document.querySelector("p");
        selectDOM.addEventListener("change", (e)=>{
            paragraphDOM.setAttribute("style", `writing-mode: ${e.target.value};`);
        });
    </script>
</body>
</html>
```

### §4.12.1 字符朝向(`text-orientation`)

当多语言字符混杂时，可以使用`text-orientation`属性控制字符的方向。

| `text-orientation`属性值 | 作用                           |
| ------------------------ | ------------------------------ |
| `mixed`                  | CJK字符头朝上，非CJK字符头朝右 |
| `upright`                | 字符全部头朝上                 |
| `sideways`               | 字符全部头朝右                 |

```html
<html>
<head>
    <title>Figure</title>
    <style type="text/css">
    </style>
    <style type="text/css">
        p {
            border: 1px dotted;
            width: 15em;
            height: 6em;
        }
    </style>
</head>
<body>
    writing-mode:
    <select id="text-orientation">
        <option>mixed</option>
        <option>upright</option>
        <option>sideways</option>
    </select>
    <div style="writing-mode: vertical-lr;">
        <p>この部分の日本語には英語と数字が混じっています。This section of Japanese is mixed with English and numbers.</p>
    </div>
    <script>
        const selectDOM = document.querySelector("#text-orientation");
        const paragraphDOM = document.querySelector("p");
        selectDOM.addEventListener("change", (e)=>{
            paragraphDOM.setAttribute("style", `text-orientation: ${e.target.value};`);
        });
    </script>
</body>
</html>
```

# §5 盒模型

## §5.1 元素的显示方式(`display`)

例如给定下列`<a>`超链接，使其从行内元素转变为块级元素，这样用户即使不点击文字，只需点击块级元素范围内，就能跳转。

```html
<html>
<head>
    <style>
        .navbar {
            width: 10rem;
        }
        .navbar a {
            display: block;
        }
        .navbar a:hover {
            background-color: lightgray;
        }
    </style>
</head>
<body>
    <div class="navbar">
        <a href="/home">Home</a>
        <a href="/news">News</a>
        <a href="/about">About</a>
    </div>
</body>
</html>
```

或者给定下列无序列表，使得列表中的每一项元素`<li>`都以行内方式显示：

```html
<html>
<head>
    <style>
        ul li {
            display: inline;
            border-right: 1px black solid;
            padding: 0 0.33em;
        }
        ul li:first-child {
            border-left: 1px black solid;
        }
    </style>
</head>
<body>
    <ul>
        <li>Alice.</li>
        <li>Bob.</li>
        <li>Carol.</li>
    </ul>
</body>
</html>
```

块级元素的后代可以是行内元素，但是行内元素的后代不能是块级元素。

```mermaid
graph LR
	subgraph "外边距Margin(内侧紧邻边框)"
		subgraph "内边距Padding(外侧紧邻边框)"
			subgraph "内容(默认为真正的高与宽)"
			end
		end
	end
```

## §5.2 盒模型尺寸模式(`box-sizing`)

任何盒模型都有自己的尺寸。然而盒模型包含了外边距、边框、内边距、内容这些组成部分，而`box-sizing`属性决定了盒模型的宽度和高度从哪个组成部分开始算起。

| `box-sizing`属性      | 作用                                      |
| --------------------- | ----------------------------------------- |
| `content-box`(缺省)   | `width`和`height`用于约束内容区域的尺寸   |
| `padding-box`(已弃用) | `width`和`height`用于约束内边距区域的尺寸 |
| `border-box`          | `width`和`height`用于约束边框区域的尺寸   |

```html
<html>
<head>
    <style>
        p {
            height: 150px; 
            width: 200px;
            background-color: lightgray; 
            border: 20px lightblue solid;
            padding: 10px 30px;
        }
        .box-sizing-content-box { box-sizing: content-box; }
        .box-sizing-padding-box { box-sizing: padding-box; }
        .box-sizing-border-box { box-sizing: border-box; }
    </style>
</head>
<body>
    box-sizing:
    <select>
        <option>content-box</option>
        <option>padding-box</option>
        <option>border-box</option>
    </select>
    <p>
        This is a simple sentence for showing box-sizing property.
    </p>
    <script>
        const paragraphDOM = document.querySelector("p");
        const boxsizingDOM = document.querySelector("select");
        boxsizingDOM.addEventListener("change", (e)=>{
            paragraphDOM.setAttribute("class", "box-sizing-" + e.target.value);
            console.log(paragraphDOM.attributes["class"]);
        });
    </script>
</body>
</html>
```

## §5.3 横向格式化属性

横向格式化属性指的是能影响元素在水平方向布局的属性，一共有以下七个：`margin-left`、`margin-right`、`border-left`、`border-right`、`padding-left`、`padding-right`、`width`。

这七个属性的值加在一起，必须等于父元素(容纳块)的宽度。其中`margin-left`、`margin-right`、`width`有且仅有一个的属性值设为`auto`，则浏览器会自动调整设为`auto`的属性，使得元素在水平方向上填满容纳块。

在机械制图中，我们学习过"过约束"的概念。同理，如果`margin-left`、`margin-right`、`width`都是具体的值，没有一个是`auto`时，这就是过约束状态，七个属性值相加不一定等于容纳块宽度。因此浏览器会自动将`margin-right`设为`auto`。

```html
<html>
<head>
    <style>
        body {
            padding: 0 0 0 0;
            background-color: aliceblue;
        }
        div {
            background-color: lightgray;
            margin-left: 10px;
            border-left: 10px solid lightblue;
            width: 50px;
            border-right: 10px solid lightblue;
            padding-left: 10px;
            margin-right: 10px;

            margin-bottom: 5px;
        }
        div:hover { background-color: gray; }
    </style>
</head>
<body>
    <div>Hello</div>
    <div style="width: auto;">Hello</div>
    <div style="margin-left: auto;">Hello</div>
    <div style="margin-right: auto;">Hello</div>
    <div style="width: auto; margin-left: auto;margin-right: auto;">Hello</div>
</body>
</html>
```

对于不同的`auto`属性值组合，CSS规定的处理策略如下：

| `margin-left` | `width` | `margin-right` | 作用                                    |
| ------------- | ------- | -------------- | --------------------------------------- |
| 具体值        | 具体值  | 具体值         | 过约束，右外边距设为`0`                 |
| `auto`        | 具体值  | `auto`         | 左右外边距长度相等，扩充至填满容纳块    |
| 具体值        | `auto`  | `auto`         | 右外边距设为`0`                         |
| `auto`        | `auto`  | 具体值         | 左外边距设为`0`                         |
| `auto`        | `auto`  | `auto`         | 左右外边距设为`0`，宽度扩充至填满容纳块 |

> 注意：CSS规定可以设置负外边距。此时`auto`的计算规则仍然遵从上表，只是形式上要求七个属性值相加为容纳块的宽度，实际上子元素完全有可能超出容纳块的显示范围。

## §5.4 纵向格式化属性

纵向格式化属性决定了元素在垂直方向的排版样式，包括`margin-top`、`border-top`、`padding-top`、`height`、`padding-bottom`、`border-bottom`、`margin-bottom`。

与横向格式化属性相似，这七个属性值相加的结构必须等于容纳块的高度。且其中只有三个属性可以设置为`auto`：`margin-top`、`height`、`margin-bottom`。

| `margin-top` | `height` | `margin-bottom` | 作用                                                         |
| ------------ | -------- | --------------- | ------------------------------------------------------------ |
| 具体值       | 具体值   | 具体值          | 若七个属性值相加小于等于容纳块高度，则自动扩充内容区域高度；如大于容纳块高度，则自动缩减内容区高度；若内容区高度缩减至`0`，则突破相加为定值的限制。 |
| `auto`       | 任意     | 任意            | 上外边距设为`0`                                              |
| 任意         | 任意     | `auto`          | 下外边距设为`0`                                              |
| 任意         | `auto`   | 任意            | 自动扩充内容区高度至填满容纳块                               |

```html
<html>
<head>
    <style>
        body {
            padding: 0 0 0 0;
            background-color: aliceblue;
        }
        .content {
            width: 20em;
            background-color: lightgray;
            box-sizing: border-box;
            margin-top: 10px;
            border-top: 10px solid lightblue;
            padding-top: 0.5em;
            height: 6em;
            padding-bottom:10em;
            border-bottom: 10px solid lightblue;
        }
        .content:hover { background-color: gray; }
    </style>
</head>
<body>
    <div style="height: 10rem;">
        <div class="content">This is a long sentence for testing vertical alignment properties.</div>
    </div>
</body>
</html>
```

只有相邻的纵向外边距会自动折叠，而内边距和边框不会。可以这么理解：准备两个白色卡片，每个卡片周围有一圈矩形的透明塑料。现在将这两个卡片重叠，只要白色部分之间不重叠、白色部分与透明塑料不重叠即可，透明塑料之间的重叠是允许的。

```html
<html>
<head>
    <style>
        ul li {
            margin-bottom: 15px;
            margin-top: 10px; /* 该属性似乎无效 */
        }
    </style>
</head>
<body>
    <div style="display: inline;">
        <ul> <!-- 貌似间隔25px，实际间隔max(15px,10px)=15px -->
            <li>Alice</li>
            <li>Bob</li>
            <li>Carol</li>
        </ul>
    </div>
</body>
</html>
```

同理，`margin-top`与`margin-bottom`也能设置负边距：

```html
<html>
<head>
</head>
<body>
    <div style="margin-bottom: 1em;">This is the first sentence.</div>
    <div style="margin-top: -1em;">This is the second sentence.</div>
    <br/>
    <div style="margin-bottom: 1em;">This is the first sentence.</div>
    <div style="margin-top: -1.5em;">This is the second sentence.</div>
	<div style="width: 420px; margin-right: 10px; margin-left: 10px; margin-bottom: 0; border: 3px solid black;">
    	<p style="margin-top: -10px; margin-right: 10px; margin-left: 10px; margin-bottom: 0; border: 3px solid gray;">
        	A paragraph
    	</p>
    	A  div
	</div>
</body>
</html>
```

## §5.5 宽度和高度(`width`/`height`)

在`box-sizing`属性缺省的情况下，元素的宽度`width`指的是从左内边界到右内边界的距离，元素的高度`height`指的是从上内边界到下内边界的距离。

这两个属性不能应用到行内非置换元素上，比如`<a>`。如果非要使用这两种属性，可以考虑将这种元素变为非行内元素，例如`display: block`或`display: inline-clock`。

```html
<html>
<head>
    <style>
        a:link {
            background-color: lightgray;
            height: 10px;
            width: 10px;
        }
    </style>
</head>
<body>
    <a href="/" style="display: initial;">Baidu</a>
    <br/>
    <a href="/" style="display: block;">Baidu</a>
    <br/>
    <a href="/" style="display: inline-block;" >Baidu</a>
</body>
</html>
```

## §5.6 内边距(`padding`)

`padding`的属性值可以为以下类型：

| 第一个参数 | 第二个参数 | 第三个参数 | 第四个参数 | 作用                                             |
| ---------- | ---------- | ---------- | ---------- | ------------------------------------------------ |
| 顶内边距   | 右内边距   | 下内边距   | 左内边距   |                                                  |
| 顶内边距   | 右内边距   | 下内边距   |            | 令左内边距等于右内边距                           |
| 顶内边距   | 右内边距   |            |            | 令左内边距等于右内边距，下内边距等于顶内边距     |
| 顶内边距   |            |            |            | 令左内边距等、下内边距。右内边距全部等于顶内边距 |

这幅图总结了以上表格的内容：当箭头指向的某一侧属性未指定时，CSS就会默认尝试继承源头的已存在的属性值。

```mermaid
flowchart LR
	top --> right & bottom
	right --> left
```

当属性值为百分数时，该属性参考的是父元素内容区的宽度：

```html
<html>
<head>
    <style>
        div {
            margin-top: 20%;
            margin-left: 30%;
            margin-right: 30%;
            background-color: lightgray;
            border: 1px solid black;
        }
    </style>
</head>
<body>
    <div>Hello World!</div>
</body>
</html>
```

对于行内非置换元素而言，`padding`属性在垂直方向上(`padding-top`和`padding-bottom`)不影响实际显示的效果，没有视觉效果。除非该元素有背景色，会导致背景色沿元素上下延伸。在水平方向时，则会有实际的视觉效果：

```html
<html>
<head>
    <style>
        strong { background-color: lightgray; }
        .style1 { padding-top: 0; }
        .style2 { padding-top: 0.5em; }
        .style3 {padding-left: 1em;}
    </style>
</head>
<body>
    <p>Hello <strong class="style1">World!</strong></p>
    <p>Hello <strong class="style2">World!</strong></p>
    <p>Hello <strong class="style3">World!</strong></p>
</body>
</html>
```

对于行内置换元素而言，`padding`属性在垂直和水平方向上都会产生视觉效果，甚至会影响行高：

```html
<html>
<head>
    <style>
        img {
            width: 30px;
            padding-top: 1.5rem;
            padding-bottom: 0.5rem;
            background-color: lightblue;
        }
    </style>
</head>
<body>
    <div style="width: 200px; background-color: lightgray;">
        This is a picture which has a huge padding-top: <img src="https://www.google.com/images/branding/googlelogo/2x/googlelogo_light_color_92x30dp.png"/>
    </div>
</body>
</html>
```

使用`box-decoration-box`属性，可以改变行内元素每一行的内边距行为：

```html
<html>
<head>
    <style>
        body {
            background-color: darkgray;
        }
        div.root {
            border: 1px solid black;
            width: 8rem;
            margin-bottom: 1rem;
            background-color: black;
        }
        span {
            margin: 1rem;
            line-height: 3rem;
            box-shadow: 8px 8px 10px 0 #ff1492, -5px -5px 5px 0 #00f, 5px 5px 15px 0 #ff0;
            border-style: solid;
            border-radius: 8px;
            color: white;
        }
    </style>
</head>
<body>
    <div class="root">
        <span>这段话横跨了两行。</span>
    </div>
    <div class="root">
        <span style="box-decoration-break: clone; -webkit-box-decoration-break: clone;">这段话横跨了两行。</span>
    </div>
</body>
</html>
```



## §5.7 边框(`border`)

边框时元素的内容区或内边距外部周围的一条或多条线段，由三要素组成：宽度、式样和颜色。

- 宽度(`border-width`)：缺省为`2px`
- 式样(`border-style`)：缺省为`none`
- 颜色(`border-color`)：缺省为元素自身的前景色(`color`)，如果没有则从父元素继承

### §5.7.1 边框式样(`border-style`)

`border-style`属性用于指定边框的式样。当其属性值有四个、三个、两个、一个值时，参考[§5.2.5 内边距(`padding`)](###§5.2.5 内边距(`padding`))一节的规则。当然，也可以分别使用`border-top-style`、`border-right-style`、`border-bottom-style`、`border-left-style`。

| `border-style`属性值 | 作用                             |
| -------------------- | -------------------------------- |
| `none`               | 不显示边框                       |
| `hidden`             | 除表格样式冲突之外，等价于`none` |
| `solid`              | 实线边框                         |
| `dotted`             | 点线边框                         |
| `dashed`             | 短划线边框                       |
| `double`             | 双实线边框                       |
| `groove`             | 雕刻效果，与`ridge`相对          |
| `ridge`              | 浮雕效果，与`groove`相对         |
| `inset`              | 陷入效果，与`outset`相对         |
| `outset`             | 突出效果，与`inset`相对          |

```html
<html>
<head>
    <style>
        div {
            width: 20rem;
            margin-bottom: 0.5rem;
            border-width: 3px;
        }
    </style>
</head>
<body>
    <div style="border-style: none;">border-style: none</div>
    <div style="border-style: hidden;">border-style: hidden</div>
    <div style="border-style: solid;">border-style: solid</div>
    <div style="border-style: dotted;">border-style: dotted</div>
    <div style="border-style: dashed;">border-style: dashed</div>
    <div style="border-style: double;">border-style: double</div>
    <div style="border-style: groove;">border-style: groove</div>
    <div style="border-style: ridge;">border-style: ridge</div>
    <div style="border-style: inset;">border-style: inset</div>
    <div style="border-style: outset;">border-style: outset</div>
    <div style="border-style: none;">border-style: none</div>
    <div style="border-style: solid dotted double inset;">border-style: solid dotted double inset</div>
</body>
</html>
```

### §5.7.2 边框宽度(`border-width`)

`border-width`用于指定边框的宽度。该属性只能设置一个属性值，而且应用于各个方向。如果向分别设置各个方向的边框宽度，只能使用`border-top-width`、`border-right-width`、`border-bottom-width`、`border-left-width`分别指定。

| `border-width`属性值 | 作用                                              |
| -------------------- | ------------------------------------------------- |
| 长度                 | 当`border-style`为`none`或`hidden`时，强制设为`0` |
| `thin`               |                                                   |
| `medium`(缺省)       |                                                   |
| `thick`              |                                                   |

```html
<html>
<head>
    <style>
        div {
            width: 20rem;
            margin-bottom: 0.5rem;
            border-style: outset;
        }
        .style1 {
            border-top-width: 2px;
            border-right-width: 5px;
            border-bottom-width: 10px;
            border-left-width: 20px;
            border-style: solid dashed double inset;
        }
    </style>
</head>
<body>
    <div style="border-width: 1px;">border-width: 1px</div>
    <div style="border-width: thin;">border-width: thin</div>
    <div style="border-width: 2px;">border-width: 2px</div>
    <div style="border-width: medium;">border-width: medium</div>
    <div style="border-width: 5px;">border-width: 5px</div>
    <div style="border-width: thick;">border-width: thick</div>
    <div style="border-width: 10px;">border-width: 10px</div>
    <div style="border-width: 20px;">border-width: 20px</div>
    <div style="border-width: 40px;">border-width: 40px</div>
    <div class="style1">Mixed border-width</div>
</body>
</html>
```

### §5.7.3 边框颜色(`border-color`)

`border-color`属性用于指定边框的颜色。当其属性值有四个、三个、两个、一个值时，参考[§5.2.5 内边距(`padding`)](###§5.2.5 内边距(`padding`))一节的规则。当然，也可以分别使用`border-top-color`、`border-right-color`、`border-bottom-color`、`border-color`。

```html
<html>
<head>
    <style>
        div {
            width: 10rem;
            border-style: solid;
            border-width: 10px;
            border-color: black blue red green;
        }
    </style>
</head>
<body>
    <div>Hello World!</div>
</body>
</html>
```

> 注意：之前我们说过，当`border-style`为`none`或`hidden`时，那么就算强制声明`border-width`，CSS也会将其视为`0`。如果我们就是想让边框的宽度占着位，同时不想让边框本体显示，也就是设置透明边框，可以考虑将`border-color`设为`transparent`。

对于行内非置换元素而言，垂直方向的边框并不会影响`line-height`，而水平方向的边框会推开文本。而对于行内置换元素而言，任何方向的边框都会推开文本：

```html
<html>
<head>
    <style>
        strong {
            border-top: 5px solid lightgray;
            border-bottom: 20px solid lightcoral;
            border-left: 1rem solid lightblue;
            border-right: 1rem solid lightgreen;
        }
    </style>
</head>
<body>
    <div style="width: 150px;">
        This is a long sentence which takes up <strong>many</strong> lines.
    </div>
</body>
</html>
```

### §5.7.4 圆角边框(`border-radius`)

`border-radius`属性用于设置边框的圆角半径。当其属性值有四个、三个、两个、一个值时，参考[§5.2.5 内边距(`padding`)](###§5.2.5 内边距(`padding`))一节的规则。当然，也可以分别使用`border-top-left-radius`、`border-top-right-radius`、`border-bottom-left-radius`、`border-bottom-right-radius`。

圆角的绘制过程如下所述：

1. 找到该圆角半径所描述的角落顶点
2. 以该顶点为圆心，圆角半径为半径绘制圆
3. 每个顶点重复以上步骤，得到四个圆，取其圆弧与公切线线段。

> 注意：如果某个圆的半径过大，使得公切线线段难以判断，则强制令其半径缩小到刚好不发生冲突的长度。
>
> 例如`border-radius: 9999em`的作用是：让元素边框中长度最短的两侧变成半圆形：
>
> ```html
> <html>
> <head>
>     <style>
>         div {
>             background-color: lightgray;
>             border-radius: 9999em;
>             margin-bottom: 1rem;
>         }
>     </style>
> </head>
> <body>
>     <div style="width: 100px; height: 50px;"></div>
>     <div style="width: 75px; height: 50px;"></div>
>     <div style="width: 50px; height: 50px;"></div>
>     <div style="width: 25px; height: 50px;"></div>
> </body>
> </html>
> ```

如果圆角半径为百分数，则百分数的计算参照物为相邻一边的变长。例如某矩形的尺寸为`10px*5px`，圆角半径为`20%`，则圆角的长半径为`2px`，短半径为`1px`，即为椭圆的一部分。

我们还可以分别指定圆角的横向半径和纵向半径，只需用斜线隔开即可。斜线两侧仍然可以填1~4个属性值：

```html
<html>
<head>
    <style>
        div {
            width: 200px; 
            height: 100px;
            background-color: lightgray;
            margin-bottom: 1rem;
        }
    </style>
</head>
<body>
    <div style="border-radius: 2em / 1em;"></div>
    <div style="border-radius: 1em 1.5em 2em 2.5em / 2.5em 2em 1.5em 1em;"></div>
</body>
</html>
```

### §5.7.5 图像边框(`border-image`)

到此为止，我们介绍的边框都是由浏览器根据规则绘制的矢量图，样式不够丰富。`border-image`系列属性允许我们加载外部图像作为边框。

`border-image-source`用于指示图像边框的资源地址。在以下例子中，边框的四个角都有一个圆点图片：

```
<html>
<head>
    <style>
        div {
            width: 200px; 
            height: 100px;
            background-color: lightgray;
            border-width: 25px;
            border-style: solid;
            border-image-source: url("https://meyerweb.github.io/csstdg4figs/08-padding-borders-outlines-and-margins/i/circle.png");
        }
    </style>
</head>
<body>
    <div></div>
</body>
</html>
```

> 注意：`border-image`系列属性生效的前提是`border-style`不为`none`和`hidden`。

`border-image-slice`属性在图像上放置4条裁剪线，这4条裁剪线将整个图像边框分为了九宫格，其中包括四个角、四条边和一个中心。该属性的默认值为`100%`CSS将四个角作为边框四个角使用的图像，四条边作为边框四边使用的图像，至于一个中心则默认废弃不用，除非为其属性值添加`fill`。`border-image-slice`的属性值依然可以接受1~4个值，分别指示上、右、下、左四边的偏移量，可以使用百分数表示比例或纯数字表示像素数：

> 注意：`border-image-slice`除了接受正常的百分数以外，还有以下特例：
>
> - 当`border-image-slice`检测到留给四条边的区域面积不为正，而是小于等于`0`时，就不显示四条边的图像。
> - 准确地来说，四个角使用的图像分别是由对应的两条裁剪线法向量决定的二维子平面。因此当裁剪线重叠甚至越过时，四个角使用的图像会有公共部分。

```html
<html>
<head>
    <style>
        div {
            width: 200px; 
            height: 100px;
            background-color: lightgray;
            margin-bottom: 0.5rem;
            border-width: 25px;
            border-style: solid;
            border-image-source: url("https://meyerweb.github.io/csstdg4figs/08-padding-borders-outlines-and-margins/i/circle.png");
        }
    </style>
</head>
<body>
    <div style="border-image-slice: 30%;"></div>
    <div style="border-image-slice: 30% fill;"></div>
    <div style="border-image-slice: 49.9%;"></div>
    <div style="border-image-slice: 50%;"></div>
    <div style="border-image-slice: 80%;"></div>
</body>
</html>
```

默认情况下，图像边框的长度取决于`border-width`属性。如果开发者想让图像边框的长度不同于`border-width`，可以使用`border-image-width`属性。该属性没有下属的子属性，可以接收1~4个参数。其属性值可以接受以下单位：

- 绝对长度单位：效果等价于`border-width`
- 纯数字：这一边`border-width`的倍数
- 百分数：以边框图片的这一边长度为基准
- `auto`：使用`border-image-slice`的计算结果，如果不存在则使用`border-width`

```html
<html>
<head>
    <style>
        div {
            width: 200px; 
            height: 100px;
            background-color: lightgray;
            margin-bottom: 0.5rem;
            border-width: 25px;
            border-style: solid;
            border-image-source: url("https://meyerweb.github.io/csstdg4figs/08-padding-borders-outlines-and-margins/i/circle.png");
            border-image-slice: 49.9%;
        }
    </style>
</head>
<body>
    <!-- border-image-source使用的图片为50px×50px -->
    <div style="border-image-width: 1;"></div>
    <div style="border-image-width: 25px;"></div>
    <div style="border-image-width: 10%;"></div>
    <div style="border-image-width: auto;"></div>
</body>
</html>
```

我们已经知道了`padding`属性可以防止边框与内容区挨的太近。其实除了内边距以外，还可以从边框入手，在边框区域内扩大边框的粗细程度，让原先的图像边框向外扩充。这就是`border-image-outset`属性。使用审查工具，就能看到`padding`和`border-image-outset`的作用区域并不一样。

```html
<html>
<head>
    <style>
        div {
            width: 200px; 
            height: 100px;
            background-color: lightgray;
            padding: 0.5rem;
            margin: 3rem;

            border-width: 25px;
            border-style: solid;
            
            border-image-slice: 49.9%;
            border-image-source: url("https://meyerweb.github.io/csstdg4figs/08-padding-borders-outlines-and-margins/i/circle.png");
            border-image-outset: 1rem;
        }
    </style>
</head>
<body>
    <div class="style1"></div>
    <script>
        window.onload = () => {
            const divDOM = document.getElementsByTagName("div");
            console.log(divDOM);
            for(let i = 0 ; i < divDOM.length ; ++i){
                divDOM[i].innerText = "这是一段文本。".repeat(6);
            }            
        };
    </script>
</body>
</html>
```

到目前位置，四条边的图像边框都是拉伸而成的。`border-image-repeat`属性控制着各边的边框图像处理方式。其属性值可以有1~2个关键词，分别控制纵轴和横轴：

| `border-image-repeat`属性值 | 作用                                                         |
| --------------------------- | ------------------------------------------------------------ |
| `stretch`(缺省)             | 拉伸图像                                                     |
| `repeat`                    | 沿中轴平铺图像，到边缘处直接截断                             |
| `round`                     | 沿该边重复$\displaystyle\text{round}(\frac{边框该边的长度}{图像该边的长度})$次，并辅以拉伸图像 |
| `space`                     | 沿该边重复$\displaystyle\text{floor}(\frac{边框该边的长度}{图像该边的长度})$次，并调节各段间距 |

```html
<html>
<head>
    <style>
        div {
            width: 200px; 
            height: 100px;
            background-color: lightgray;
            padding: 0.5rem;
            margin: 3rem;

            border-width: 25px;
            border-style: solid;
            
            border-image-slice: 25%;
            border-image-source: url("https://meyerweb.github.io/csstdg4figs/08-padding-borders-outlines-and-margins/i/circle.png");
        }
    </style>
</head>
<body>
    <div style="border-image-repeat: stretch;"></div>
    <div style="border-image-repeat: repeat;"></div>
    <div style="border-image-repeat: round;"></div>
    <div style="border-image-repeat: space;"></div>
    <script>
        window.onload = () => {
            const divDOM = document.getElementsByTagName("div");
            console.log(divDOM);
            for(let i = 0 ; i < divDOM.length ; ++i){
                divDOM[i].innerText = "这是一段文本。".repeat(6);
            }            
        };
    </script>
</body>
</html>
```

现在我们已经介绍了五个相关的图像边框属性：`border-image-source`、`border-image-slice`、`border-image-width`、`border-image-outset`、`border-image-repeat`。这五个子属性合在一起，可以简写为`border-image`属性：

```
border-image: <source>
border-image: <source> <slice> / <width>? / <outset>? <repeat>?
```

## §5.8 轮廓(`outline`)

`outline`属性决定元素的轮廓，可以的取值为：

```css
outline: <ouline-color>? <outline-style>? <outline-width>? 
```

轮廓与边框的区别体现在三个方面：

1. 轮廓不占空间

2. 轮廓可以不是矩形

   ```html
   <html>
   <head>
       <style>
           div {
               width: 200px;
               background-color: lightgray;
               margin-bottom: 1rem;
           }
           span.style1 {
               outline: dotted 2px black;
           }
           span.style2 {
               border: dotted 2px black;
           }
       </style>
   </head>
   <body>
       <div style="width: 200px;">
           这是一段话。
           <span class="style1">这是一段话。这是一段话。这是一段话。这是一段话。</span>
           这是一段话。
       </div>
       <div style="width: 200px;">
           这是一段话。
           <span class="style2">这是一段话。这是一段话。这是一段话。这是一段话。</span>
           这是一段话。
       </div>
   </body>
   </html>
   ```

3. 浏览器只在元素处于`:focus`状态时渲染轮廓

4. 不能给单边设置轮廓

### §5.8.1 轮廓式样(`outline-style`)

除了`hidden`换为`auto`以外，轮廓式样的取值与边框式样的取值完全一致。详见[§5.7.1 边框式样(`border-style`)](###§5.7.1 边框式样(`border-style`))一节。

```html
<html>
<head>
    <style>
        div {
            width: 20rem;
            margin-bottom: 0.5rem;
            outline-width: 3px;
        }
    </style>
</head>
<body>
    <div style="outline-style: none;">outline-style: none</div>
    <div style="outline-style: auto;">outline-style: auto</div>
    <div style="outline-style: solid;">outline-style: solid</div>
    <div style="outline-style: dotted;">outline-style: dotted</div>
    <div style="outline-style: dashed;">outline-style: dashed</div>
    <div style="outline-style: double;">outline-style: double</div>
    <div style="outline-style: groove;">outline-style: groove</div>
    <div style="outline-style: ridge;">outline-style: ridge</div>
    <div style="outline-style: inset;">outline-style: inset</div>
    <div style="outline-style: outset;">outline-style: outset</div>
</body>
</html>
```

### §5.8.2 轮廓宽度(`outline-width`)

轮廓宽度的取值与边框宽度的取值完全一致。唯一的区别是`outline-width`没有下属的子属性，不能为某一边设置特定的宽度。

### §5.8.3 轮廓颜色(`outline-color`)

轮廓颜色的取值与边框颜色的取值完全一致。

## §5.9 外边距(`margin`)

开发者也可以针对每一遍设置外边距属性，可以接收1~4个关键字使用子属性`margin-top`、`margin-right`、`margin-bottom`、`margin-left`即可。

### §5.9.1 外边距折叠

在[§5.4 纵向格式化属性](##§5.4 纵向格式化属性)一节我们已经讨论了外边距的折叠行为。

```html
<html>
<head>
    <style>
        div {
            width: 200px;
            background-color: lightgray;
            margin-bottom: 1rem; /* 发生重叠 */
        }
        div:not(:first-child) {
            margin-top: 1rem; /* 发生重叠 */
        }
    </style>
</head>
<body>
    <div style="width: 200px;">123</div>
    <div style="width: 200px;">123</div>
    <div style="width: 200px;">123</div>
</body>
</html>
```

如果子元素的外边距超出了父元素的范围，那么子元素的外边距虽然不会计入父元素的外边距，但实际上也会被当成父元素外边距的一部分。

```html
<html>
<head>
    <style>
        header { background-color: lightblue;}
        h1 { margin: 1em; }
    </style>
</head>
<body>
    <header>
        <h1>Hello World!</h1>
    </header>
</body>
</html>
```

### §5.9.2 负外边距

给子元素设置负外边距，可以让子元素从父元素中冒出来。这一特性在平面设计中非常好用：

```html
<html>
<head>
    <style>
        div {
            width: 500px; 
            background-color: lightgray;
            margin: 1rem;
            border: 1px solid; /* 很重要！ */
        }
        h1 { 
            padding: 2rem 2rem 0rem 2rem;
        }
        p { 
            margin: 0rem;
            padding: 1rem;
        }
        p.punch {
            background-color: white;
            margin-left: 5rem;
            margin-right: 0px;
            border-width: 2px;
            border-style: solid;
            border-right-style: hidden;
        }
        p.mond {
            background-color: rgba(255, 0, 0, 0.2);
            margin: 1em 3em -3em -3em;
        }
    </style>
</head>
<body>
    <div>
        <a href="https://baijiahao.baidu.com/s?id=1699590831615037098&wfr=spider&for=pc"><h1>2021年5月12日外交部发言人华春莹主持例行记者会</h1></a>
        <p>香港中评社记者：昨天中国公布第七次人口普查结果。之前《金融时报》发表所谓独家消息，......，称“中国面临人口危机”，认为中国人口出生率下降、老龄化问题加剧、劳动力人口萎缩会对中国经济造成严重影响，并预言“在可预见的未来，中国可能无法取代美国成为最大的经济体”，甚至会影响中国领导人承诺实现的“中国梦”。对此你怎么看？</p>
        <p class="punch">华春莹：......，根据国家统计局权威发布，......。这个数据表明，中国人口十年来继续保持低速增长态势，中国人口总量持续增长，仍然是世界第一人口大国。人口质量稳步提升，人口受教育程度明显提高。人口结构调整变化，性别结构改善。人口流动集聚的趋势更加明显，城镇化水平持续提高。......</p>
        <p>......，中国人口14.1178亿，不是仍然比美欧国家人口总数加起来还多吗？不知有关媒体记者如何摇身变成人口统计学专家和社会学家，从何得出“中国人口危机说”的结论？......</p>
        <p class="mond">回顾一下过去几十年来，在中国发展的几乎每一个关键阶段，西方都会对中国做出种种评判和预测，出现了各种各样的论调，如各种版本的“中国威胁论”“中国崩溃论”。但随着中国持续发展，这些论调后来都一一被事实打脸。中国已经开启全面建设社会主义现代化国家新征程，我们将继续沿着已经被证明是正确的道路坚定前行。希望热衷于炮制各种涉华论调的人也能和我们中国人民一样健康快乐地生活，共同迎接并且见证“中国梦”的实现。</p>
    </div>
</body>
</html>
```

> 注意：边框会影响内容区的范围。我们已经知道盒模型由内容区、内边距、边框、外边距四部分组成，而且`background`只包括内边距和内容区。然而，如果我们不设置边框，而且子元素的外边距为负值，想冒出父元素的`auto`高度范围，那么内容区会在垂直方向上自动扩充，将本应冒出父元素的子元素重新包含到父元素的内容区中。
>
> 要让子元素真正的从父元素中冒出，可以考虑给边框设置透明颜色：
>
> ```css
> border: 1px solid rgba(0, 0, 0, 0);
> ```

### §5.9.3 行内元素的外边距

对于行内非置换元素而言，外边距不会在垂直方向上产生影响，只会在水平方向上有影响。同理，将其设置为父外边距，则元素两端可能会与周围的内容重叠。

```html
<html>
<head>
    <style>
        span { background-color: lightblue; }
        strong {background-color: lightpink;}
        strong.style1 {
            margin-top: 25px;
            margin-bottom: 50px;
        }
        strong.style2 {
            margin-left: 25px;
            margin-right: 25px;
        }
    </style>
</head>
<body>
    <span><strong class="style2">Hello</strong>, <strong class="style1">World</strong>!</span>
</body>
</html>
```

对于行内置换元素而言，外边距在垂直和水平方向上都能产生影响。

# §6 背景与前景

CSS可以为任何元素设置前景色和背景色。

## §6.1 前景色(`color`)

`color`属性用于设置元素的前景色。其中前景指的是元素的文本和四周的边框。如果指定了`border-color`，那么边框的颜色将优先使用`border-color`。

```html
<html>
<head>
    <style>
        div {
            width: 20rem;
            margin-bottom: 1em;
            border-style: solid;
        }
    </style>
</head>
<body>
    <div style="color: red;">Hello World!</div>
    <div style="color: blue;">Hello World!</div>
    <div style="color: green;">Hello World!</div>
    <div style="color: green; border-color: blue;">Hello World!</div>
</body>
</html>
```

`color`属性也可应用于表单元素的文字上：

```html
<html>
<head>
    <style>
        select { color: red; }
        label { color: red; }
        button { color: red ;}
    </style>
</head>
<body>
    <select>
        <option>Alice</option>
        <option>Bob</option>
        <option>Carol</option>
    </select>
    <input type="checkbox" id="demo1"><label for="demo1">Hello</label></input>
    <input type="checkbox" id="demo2"><label for="demo2">World</label></input>
    <button>Click me</button>
</body>
</html>
```

## §6.2 背景 

### §6.2.1 背景色(`background-color`)

`background-color`属性用于设置元素的背景色。其中背景指的是元素的内容区、内边距区和边框区。

在实际项目中，`color`与`background-color`通常配套使用。因为浏览器的默认`color`与`background-color`千奇百怪，如果只设置其中的一个，那么浏览器的另一个可能就会发生冲突，使得文字与背景颜色难以辨认，不利于用户阅读。

```html
<html>
<head>
    <style>
        h1 {
            background-color: rgb(20%,20%,20%);
            color: white;
            padding: 0.5rem;
        }
        a:link {
            color: blue;
            background-color: lightgray;
        }
        a:visited {
            color: red;
            background-color: gray;
        }
        a:hover {
            color: greenyellow;
            background-color: gray;
        }
    </style>
</head>
<body>
    <h1>这是一段标题</h1>
    <p>
        这是一段文本。<a href="./">这是一个超链接。</a>
    </p>
</body>
</html>
```

这里有个小技巧——边框和背景颜色可以配合使用，实现"双色边框"的效果：

```html
<html>
<head>
    <style>
        h1 {
            background-color: skyblue;
            padding: 0.5rem;
            border: 0.5rem solid lightblue;
        }
        div {
            padding: 0.5rem;
            background-color: rgb(30%, 30%, 30%);
            color: white;
        }
    </style>
</head>
<body>
    <h1>
        <div>这个黑色&lt;div&gt;被"双色边框"覆盖了</div>
    </h1>
</body>
</html>
```

### §6.2.2 裁剪背景(`background-clip`)

我们知道，`background`的范围默认为内容区、内边距区和边框区。`background-clip`属性可以更精细的控制背景的范围。如果设置了`border-radius`，就等边框渲染完毕后，根据圆角边框的范围再做一次裁剪。

| `background-clip`属性 | 作用                                                         |
| --------------------- | ------------------------------------------------------------ |
| `border-box`          | 背景的范围为内容区、内边距区、边框区                         |
| `padding-box`         | 背景的范围为内容区、内边距区                                 |
| `content-box`         | 背景的范围为内容区                                           |
| `text`                | 背景的范围仅为文字，相当于背景与文字取交集(前提是`color: transparent`) |

> 注意：根据[MDN](https://developer.mozilla.org/zh-CN/docs/Web/CSS/background-clip#%E6%B5%8F%E8%A7%88%E5%99%A8%E5%85%BC%E5%AE%B9%E6%80%A7)，截止到2023年，Chromium系浏览器仍不支持`background:  text`属性值。该属性值仅被`-webkit-background-clip: text`支持。

```html
<html>
<head>
    <style>
        div {
            width: 40rem;
            padding: 0.5rem;
            margin-bottom: 1rem;
            border: 1rem dashed black;
            background-color: royalblue;
        }
    </style>
</head>
<body>
    <div style="background-clip: border-box;">background-clip: border-box</div>
    <div style="background-clip: padding-box;">background-clip: padding-box</div>
    <div style="background-clip: content-box;">background-clip: content-box</div>
    <div style="color: transparent; -webkit-background-clip: text; background-clip: text;">background-clip: content-box</div>
</body>
</html>
```

### §6.2.3 背景图(`background-image`)

`background-image`属性允许加载外部图像作为背景，是一个非继承属性。

```html
<html>
<head>
    <style>
        div {
            width: 30rem;
            height: 8rem;
            padding: 0.5rem;
            padding-left: 9rem;
            margin-bottom: 1rem;
            border: 1px solid black;

            background-color: lightgray;
            background-repeat: no-repeat;
        }
    </style>
</head>
<body>
    <div style="background-image: url('https://cdn-icons-png.flaticon.com/128/1164/1164651.png');">Hello World!</div>
</body>
</html>
```

在实际工程中，`background-image`与`background-color`通常配套使用，防止`background-image`资源失效而导致排版混乱。

### §6.2.4 背景定位(`background-position`)

`background-position`属性决定了背景的具体位置。该属性接受1~2个参数，分别表示横向坐标与纵向坐标。当然也可以使用`top`、`right`、`bottom`、`left`关键字强行指定：

```html
<html>
<head>
    <style>
        div {
            width: 20rem;
            height: 15rem;
            padding: 0.5rem;
            margin-bottom: 1rem;
            border: 1px solid black;

            background-image: url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/radio-warn-fade.png");
            background-color: lightgray;
            background-repeat: no-repeat;
        }
    </style>
</head>
<body>
    <div style="background-position: center;">Hello World!</div>
    <div style="background-position: 10% 25%;">Hello World!</div>
    <div style="background-position: right bottom;">Hello World!</div>
    <div style="background-position: right 10% bottom 10%;">Hello World!</div>
</body>
</html>
```

当`background-position`的属性值为百分数时，其规则较为复杂。以横轴为例，横轴的百分比参照的基准是$\text{width}-2\times背景图像的宽度$，操控的是背景图像中点的位置，其变化范围为$[背景图像的宽度, \text{width}-背景图像的宽度]$。纵轴同理。

| 等效的单参数关键字 | 等效的双参数关键字               | 等效的百分数关键字 |
| ------------------ | -------------------------------- | ------------------ |
| `center`           | `center center`                  | `50%`与`50% 50%`   |
| `right`            | `center right`与`right center`   | `100%`与`100% 50%` |
| `left`             | `center left`与`left center`     | `0%`或`0% 50%`     |
| `top`              | `top center`与`center top`       | `50% 0%`           |
| `bottom`           | `bottom center`与`center bottom` | `50% 100%`         |
|                    | `top left`与`left top`（缺省）   | `0% 0%`            |
|                    | `top right`与`right top`         | `100% 0%`          |
|                    | `bottom left`与`left bottom`     | `100% 100%`        |
|                    | `bottom right`与`right bottom`   | `0% 100%`          |

### §6.2.5 改变定位框(`background-origin`)

`background-origin`属性决定背景图像中点活动范围的计算方式。乍一看，该属性与`background-clip`属性的取值非常相近，但是两者承担的职能还是不同的。`background-clip`决定的是背景的绘制区域，而`background-origin`决定的是背景相对位置的参考基准位置。

| `background-origin`属性值 | 作用                                 |
| ------------------------- | ------------------------------------ |
| `border-box`              | 背景图像左上角默认在边框区的左上角   |
| `padding-box`             | 背景图像左上角默认在内边距区的左上角 |
| `content-box`             | 背景图像左上角默认在内容区的左上角   |

```html
<html>
<head>
    <style>
        div {
            width: 20rem;
            height: 20rem;
            padding: 1rem;
            margin-bottom: 1rem;
            border: 20px dotted black;

            background-image: url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/yinyang.png");
            background-color: lightgray;
            background-repeat: no-repeat;
        }
    </style>
</head>
<body>
    <div style="background-origin: border-box;">Hello World</div>
    <div style="background-origin: padding-box;">Hello World</div>
    <div style="background-origin: content-box;">Hello World</div>
</body>
</html>
```

现在考虑`background-clip`与`background-origin`组合作用的情景：

```html
.style1 {
    background-clip: content-box;
    background-origin: padding-box;
}
.style2 {
    background-clip: padding-box;
    background-origin: content-box;
}
<div class="style1">Hello World</div>
<div class="style2">Hello World</div>
```

在上面的例子中，`.style1`将背景图片的左上角移动到内边距区的左上角，然后只允许内容区内显示背景图片，从而造成背景图像被裁剪；`.style2`将背景图片的左上角移动到内容区的左上角，然后只允许内边距区内显示背景图像，这一步不会产生任何影响。

### §6.2.6 背景重复方式(`background-repeat`)

`background-repeat`属性决定了背景图片的重复方式。其属性值的正则表达式可以表示为`[repeat-x | repeat-y] | [repeat | space | round | no-repeat]{1,2}`。

| `background-repeat`属性值 | 作用                                                         |
| ------------------------- | ------------------------------------------------------------ |
| `repeat-x`                | 沿横轴无限平铺图像                                           |
| `repeat-y`                | 沿纵轴无限平铺图像                                           |
| `repeat`                  | 沿横轴和纵轴无限平铺图像                                     |
| `space`                   | 在横轴和纵轴重复$\lfloor\displaystyle\frac{元素该边长度}{背景图像该边长度}\rfloor$次，并自动调整间距。如果该值小于$1$，则向上取整到$1$，使其在该轴方向上至少出现一次 |
| `round`                   | 在横轴和纵轴重复$\text{round}(\displaystyle\frac{元素该边长度}{背景图像该边长度})$次，并自动调整背景图像的尺寸 |
| `no-repeat`               | 不重复背景图                                                 |

| 等效单个关键词 | 等效两个关键词        |
| -------------- | --------------------- |
| `repeat-x`     | `repeat no-repeat`    |
| `repeat-y`     | `no-repeat repeat`    |
| `repeat`       | `repeat repeat`       |
| `no-repeat`    | `no-repeat no-repeat` |
| `space`        | `space space`         |
| `round`        | `round round`         |

```html
<html>
<head>
    <style>
        h1 {
            border: 2px solid black;
            padding: 0.5rem;
            margin-bottom: 0.5rem;
            background-image: url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/yinyang-sm.png");
            background-color: lightgray;
        }
    </style>
</head>
<body>
    <h1 style="background-repeat: repeat-x;">background-repeat: repeat-x</h1>
    <h1 style="background-repeat: repeat-y;">background-repeat: repeat-y</h1>
    <h1 style="background-repeat: repeat;">background-repeat: repeat</h1>
    <h1 style="background-repeat: no-repeat;">background-repeat: no-repeat</h1>
    <h1 style="background-repeat: space;">background-repeat: space</h1>
    <h1 style="background-repeat: round;">background-repeat: round</h1>
</body>
</html>
```

> 习题：给一个矩形元素设置波浪线边框。
>
> 在[§5.7.5 图像边框(`border-image`)](###§5.7.5 图像边框(`border-image`))一节中，我们学过可以使用预先设计好的波浪环素材绘制波浪线边框。经过本节学习，我们可以使用`background-repeat: repeat-x`在上下两边界绘制波浪线。
>
> ```html
> <html>
> <head>
>     <style>
>         h1 {
>             background-image: url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/wavybord.gif");
>             background-repeat: repeat-x;
>             background-color: lightgray;
>         }
>     </style>
> </head>
> <body>
>     <h1>这是一个标题</h1>
> </body>
> </html>
> ```

### §6.2.7 背景粘附(`background-attachment`)

之前我们学习的背景都是粘附与含有`background`相关属性的元素上的。这意味这背景图像的位置会跟随者元素位置而变化，也就是说文档视图滚动时，背景图像会随之一起滚动。

`background-attachment`属性用于调整背景粘附的行为。

| `background-attachment` | 作用                                                         |
| ----------------------- | ------------------------------------------------------------ |
| `scroll`(缺省)          | 当该元素本身有滚动条时，背景图像只受本身滚动条的影响，不受外界滚动条的影响 |
| `fixed`                 | 把背景图像固定在视区中，不受滚动的影响。此时背景图像对齐所参考的原点是**视区的左上角** |
| `local`                 | 把背景图像固定在元素中，受滚动的影响                         |

`background-attachment: fixed`很特殊的一点在于背景图像对齐所参考的原点是**视区的左上角**。这就允许我们实现某些背景图像素材的完美对齐。例如在下面的示例中，白底黑框的`<h1>`长框灰色网格与背景白色网格都是从视图的左上角开始排列的，因此对齐得十分整齐。而且从视觉效果上，就好像是背景是白色网格，保持不动，而`<h1>`是透明的灰色框体。以下两种方式实现的视觉效果完全相同，均如上所述：

1. 使用`background-attachment: fixed;`修饰`<h1>`

   ```html
   <html>
   <head>
       <style>
           body {
               /* 灰色背景格子图像 */
               background-image: url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/grid1.gif");
               background-repeat: repeat;
               background-attachment: fixed;
           }
           h1 {
               /* 白色背景格子图像 */
               background-image: url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/grid2.gif");
               background-repeat: repeat;
               background-attachment: fixed;
               margin: 3rem;
               border: 5px solid ;
           }
       </style>
   </head>
   <body>
       <span style="font-size: xx-large; font-weight: bold;">&lt;body&gt; background-attachment: fixed;</span>
       <h1 style="background-attachment: fixed;">&lt;h1&gt; background-attachment: fixed</h1>
       <h1 style="background-attachment: fixed;">&lt;h1&gt; background-attachment: fixed</h1>
       <h1 style="background-attachment: fixed;">&lt;h1&gt; background-attachment: fixed</h1>
       <h1 style="background-attachment: fixed;">&lt;h1&gt; background-attachment: fixed</h1>
   </body>
   </html>
   ```

2. 使用`background-color: rgba(0,0,0,0.2);`修饰`<h1>`

   ```html
   <html>
   <head>
       <style>
           body {
               /* 白色背景格子图像 */
               background-image: url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/grid2.gif");
               background-repeat: repeat;
               background-attachment: fixed;
           }
           h1 {
               /* 灰色透明背景 */
               background-color: rgba(0, 0, 0, 0.2);
               margin: 3rem;
               border: 5px solid ;
           }
       </style>
   </head>
   <body>
       <span style="font-size: xx-large; font-weight: bold;">&lt;body&gt; background-attachment: fixed;</span>
       <h1 >&lt;h1&gt; background-color: rgba(0,0,0,0.2)</h1>
       <h1 >&lt;h1&gt; background-color: rgba(0,0,0,0.2)</h1>
       <h1 >&lt;h1&gt; background-color: rgba(0,0,0,0.2)</h1>
       <h1 >&lt;h1&gt; background-color: rgba(0,0,0,0.2)</h1>
   </body>
   </html>
   ```

### §6.2.8 背景尺寸(`background-size`)

`background-size`属性用于控制背景的尺寸。其属性值的正则表达式为`[[<length>|<percentage>|auto]{1,2}|cover|contain]`。如果有两个关键字，则前一个是横向尺寸，后一个是纵向尺寸。

| `background-size`属性值 | 作用                                                         |
| ----------------------- | ------------------------------------------------------------ |
| `<length>`              |                                                              |
| `<percentage>`          | 参照基准为背景定位区的尺寸，由`background-origin`决定，而非`background-clip` |
| `auto`(缺省)            |                                                              |
| `cover`                 | 将图像等比例缩放，使得背景图片能包含整个元素（当然背景图片的可视区域只有元素，会进行裁剪） |
| `contain`               | 讲图像等比例缩放，使得整个元素恰好能包含背景图片             |

`auto`关键词的规则较为复杂：

1. 给定一个具体的背景图像，如果一个轴的尺寸为`auto`，另一个轴的尺寸为具体值，则`auto`为保留背景图像宽高比计算得到的数值。
2. 如果第一步计算失败，则`auto`被解析为背景图片的固有绝对尺寸。
3. 如果第二步失败了(例如矢量图没有宽高比信息)，则`auto`被解析为`100%`。

```html
<html>
<head>
    <style>
        div {
            width: 400px;
            height: 150px;
            border: 2px solid black;
            margin-bottom: 0.5rem;
            background-image: url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/yinyang-200.png");
            background-repeat: no-repeat;
            background-position: center;
        }
    </style>
</head>
<body>
    <div style="background-size: 100px 100px;">Hello, World!</div>
    <div style="background-size: 100px 200px;">Hello, World!</div>
    <div style="background-size: 200px 100px;">Hello, World!</div>
</body>
</html>
```

### §6.2.9 背景(综合属性)(`background`)

`background`属性本质上是对所有与背景相关属性的整合。例如下面的两种写法产生的效果完全一致：

```css
body {
    background-color: white;
    background-image: url();
    background-position: top left;
    background-repeat: repeat-y;
    background-attachment: fixed;
    background-origin: padding-box;
    background-clip: border-box;
    background-size: 50% 50%;
}
body {
    background-color: white url() repeat-y top left / 50% 50% fixed padding-box border-box;
}
```

`background`对属性值的顺序有以下限制：

1. `background-size`必须跟在`background-position`后面，而且二者之间必须用正斜杠`/`隔开。
2. 横向值在前，纵向值在后。
3. 我们知道`background-origin`和`background-clip`使用的关键词很相近。如果`background`属性值出现了两次类似的关键词，则最先出现的记为`background-origin`，后出现的记为`background-clip`。

### §6.2.10 多个背景

到目前为止，除了`background-color`之外，我们学过的所有背景属性，都支持设置多个值，每个值之间用个逗号隔开：

```html
<html>
<head>
    <style>
        div {
            width: 40rem;
            height: 15rem;
            background-image: url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/bg01.png"),
                url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/bg02.gif"),
                url("https://meyerweb.github.io/csstdg4figs/09-colors-backgrounds-and-gradients/i/bg03.jpg");
            background-position: top right, left center, 50% 100%;
            background-repeat: no-repeat, no-repeat, repeat-x;
            text-align: center;
        }
    </style>
</head>
<body>
    <div>多个背景</div>
</body>
</html>
```

> 注意：绘制的多个背景中，先声明的处于较上的图层。

假如`background-image`设置了7个值，而`background-repeat`只设置了3个值，两者不能一一对应，那么CSS将会自动按顺序重复这3个值，直到重复出7个值为止。

## §6.3 渐变

渐变指的是一种颜色到另一种颜色的平滑过渡。

CSS支持两种类型的渐变：线性渐变和径向渐变。每种渐变又可细分为循环渐变和不循环渐变。

### §6.3.1 线性渐变(`linear-gradient`)

线性渐变的基本语法为：`[[角度|to 哪一侧|to 哪个四分之一角],]? [色标 [,中色点]?]#, 中色点`。其中`#`表示前面的值可以重复一次及以上，但是每次重复之间都要加逗号`,`分隔。

```html
<html>
<head>
    <style>
        div {
            border: 2px solid black;
            width: 20rem;
            height: 5rem;
            margin-bottom: 0.5rem;
        }
    </style>
</head>
<body>
    <div style="background-image: linear-gradient(purple, gold);"></div>
    <div style="background-image: linear-gradient(90deg, purple, gold);"></div>
    <div style="background-image: linear-gradient(to left, purple, gold);"></div>
    <div style="background-image: linear-gradient(to bottom left, purple, gold);"></div>
    <div style="background-image: linear-gradient(to bottom left, purple, gold, navy);"></div>
</body>
</html>
```

中色点的定义为：`颜色 [绝对长度|百分比]?`。前面的`颜色`表示了该点的颜色，后面的表示了该点相对起始位置的距离（注意，不是相对上一个中色点的距离）。

```html
<div style="background-image: linear-gradient(purple 10%, gold 50%);"></div>
<div style="background-image: linear-gradient(purple 1rem, gold 6rem);"></div>
```

如果带有距离信息的和没有距离信息的中色点混用，那么如何确定没有距离信息的中色点的位置呢？答案是：选取两侧邻近的有距离信息的中色点，让没有距离信息的中色点在其中均匀分布。

```html
<div style="background-image: linear-gradient(purple 10%, green, blue, gold 90%);"></div>
```

如果两个中色点的位置发生重合，那么颜色在这一点会发生突变。与高等数学中的左极限和右极限相类比，虽然位置重合，但声明顺序一定有先后之分。首先声明的颜色就是左极限，后声明的就是右极限，而左极限不一定等于右极限。

这种方法经常用于实现颜色相间的"条纹"：

```html
<html>
<head>
    <style>
        div {
            border: 2px solid black;
            width: 20rem;
            height: 5rem;
            margin-bottom: 0.5rem;

            background-image: linear-gradient(90deg,
                gray 0%, gray 25%,
                transparent 25%, transparent 50%, 
                gray 50%, gray 75%,
                transparent 75%, transparent
            );
        }
    </style>
</head>
<body>
    <div></div>
</body>
</html>
```

到此，我们都默认中色点的位置随着声明的顺序而增大。如果一个中色点的位置很靠前，但是声明顺序很落后，那么这个中色点的声明顺序是不正常的。CSS对此的处理方法是：令该中色点的位置与前一个声明的中色点位置重合，使该中色点的作用位置靠后。

```html
<html>
<head>
    <style>
        div {
            border: 2px solid black;
            width: 20rem;
            height: 5rem;
            margin-bottom: 0.5rem;

            background-image: linear-gradient(90deg,
                red 10%, blue 90%, green 50%
            ); /* 实际上green的位置在90% */
        }
    </style>
</head>
<body>
    <div></div>
</body>
</html>
```

在讲解`角度`之前，首先要明确梯度线的概念。在二维平面内确定一条直线需要两个变量，下面给定确定该梯度线的两个条件：

1. 当角度为$x$`deg`时，渐变的方向向量的极坐标角度$\theta=90\degree-x$

2. 沿渐变方向向量最贴近的一条对角线，这条对角线对应矩形上的两个端点。这两点到梯度线的距离应该相等。过这两点向梯度线做垂线，得到的两个垂足分别记为起点和终点。

   该约束条件等价于“梯度线必须通过矩形中心”。

![梯度线示例](https://developer.mozilla.org/en-US/docs/Web/CSS/gradient/linear-gradient/linear-gradient.png)

以下是带有`角度`的`linear-gradient`颜色计算方式：

1. 如果点$(x,y)$恰好在梯度线上，则令起点和中点分别对应`linear-gradient`中色点的起点和终点，对颜色进行线性插值。
2. 如果点$(x,y)$不在梯度线上，则过改点向梯度线做垂足，令该点的颜色为垂足的颜色。

带有`to 哪个四分之一角`的行为比较特殊。例如`to top right`，你可能猜测该梯度线指向的方向恰为$45\degree$。然而实际是，CSS会过矩形中心，做一条主对角线的垂线，令其为梯度线。

```html
<html>
<head>
    <style>
        div {
            border: 2px solid black;
            margin-bottom: 0.5rem;
            background-image: linear-gradient(to top right, red, blue);
        }
    </style>
</head>
<body>
    <div style="width: 10rem; height: 2rem;"></div>
    <div style="width: 10rem; height: 5rem;"></div>
    <div style="width: 10rem; height: 10rem;"></div>
    <div style="width: 5rem; height: 10rem;"></div>
    <div style="width: 2rem; height: 10rem;"></div>
</body>
</html>
```

### §6.3.2 径向渐变(`radial-gradient`)

径向渐变的语法为：

```
radial-gradient(
	[[<shape>||<size>] [at <position>]?, | at <position>,]?
	[<color-stop> [, <color-hint>]?] [,<color-stop>]+
)
```

其中：

- `[x||y]`表示可以取其中的一个值或多个值，而且顺序任意。
- `+`表示重复一次或多次

对于径向渐变而言，梯度线的方向不再是一个定值，而是一个包含约束的极坐标点$(r,\theta)$的区域集合。这里我们令左上角、右上角、右下角、左下角对应的角度组成一个集合，即$\Theta=\{\theta_1,\theta_2,\theta_3,\theta_4\}$。

`<shape>`指明径向渐变的形状，只有两种取值：`circle`圆和`ellipse`椭圆

`<size>`指明径向渐变的尺寸，可以接受1~2个尺寸值，描述为`50px`或`50px 100px`；也可以接受以下四种关键词：

| `<shape>`关键词         | 圆形时的作用                                                 | 椭圆时的作用                                                 |
| ----------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `closest-side`          | 梯度线的末端为$(\underset{r,\theta\in[0,2\pi)}{\text{argmin}(\theta)},r_{min})$ | 梯度线横轴的末端为$(\underset{r,\theta\in\{90\degree,270\degree\}}{\text{argmin}(\theta)},r_{min})$，纵轴的末端为梯度线的末端为$(\underset{r,\theta\in\{0\degree,180\degree\}}{\text{argmin}(\theta)},r_{min})$ |
| `farthest-side`         | 梯度线的末端为$(\underset{r,\theta\in[0,2\pi)}{\text{argmax}(\theta)},r_{max})$ | 梯度线横轴的末端为$(\underset{r,\theta\in\{90\degree,270\degree\}}{\text{argmax}(\theta)},r_{max})$，纵轴的末端为梯度线的末端为$(\underset{r,\theta\in\{0\degree,180\degree\}}{\text{argmax}(\theta)},r_{max})$ |
| `closest-corner`        | 梯度线的末端为$(\underset{r,\theta\in\Theta}{\text{argmin}(\theta)},r_{min})$ | 与圆形时相同，渐变宽高比与`closest-side`一样                 |
| `farthest-corner`(缺省) | 梯度线的末端为$(\underset{r,\theta\in\Theta}{\text{argmax}(\theta)},r_{max})$ | 与圆形时相同，渐变宽高比与`farthest-side`一样                |

```html
<html>
<head>
    <style>
        div {
            border: 2px solid black;
            margin-bottom: 0.5rem;
            width: 10rem; 
            height: 5rem;
            color: white;
        }
    </style>
</head>
<body>
    <div style="background-image: radial-gradient(closest-side at 33% 66%, yellow, purple);">closest-side</div>
    <div style="background-image: radial-gradient(farthest-side at 33% 66%, yellow, purple);">farthest-side</div>
    <div style="background-image: radial-gradient(closest-corner at 33% 66%, yellow, purple);">closest-corner</div>
    <div style="background-image: radial-gradient(farthest-corner at 33% 66%, yellow, purple);">farthest-corner</div>
</body>
</html>
```

| `<shape>`取值\\`<size>`数值 | 无   | 单属性值     | 多属性值   |
| --------------------------- | ---- | ------------ | ---------- |
| 无                          |      | 圆形         | 圆形或椭圆 |
| `circle`                    | 圆形 | 不能填百分比 |            |
| `ellipse`                   | 椭圆 |              |            |

`at <position>`用于定位径向渐变，可以把径向渐变的中心放在默认中央以外的位置，属性值与`background-position`完全一致，其中第一个参数如果是长度的话，表示渐变中心距离左边界的距离；第二个参数同理，表示距离上边界的距离：

```html
<html>
<head>
    <style>
        div {
            border: 2px solid black;
            margin-bottom: 0.5rem;
            width: 10rem; 
            height: 5rem;
            color: white;
        }
    </style>
</head>
<body>
    <div style="background-image: radial-gradient(at bottom left, yellow, purple);">at bottom left</div>
    <div style="background-image: radial-gradient(at center right, yellow, purple);">at center right</div>
    <div style="background-image: radial-gradient(at top center, yellow, purple);">at top center</div>
    <div style="background-image: radial-gradient(at center left, yellow, purple);">at center left</div>
</body>
</html>
```

`<color-stop>`中色点的取值与线性渐变的规则完全一致：

1. 首个色标的位置默认为`0%`，最后一个色标的位置默认为`100%`。例如`green, red`等价于`green 0%, red 100%`。
2. 如果某个中色点为显示声明位置，则其位置为最临近的首尾两个位置确定的中色点的线性插值。例如`red, green, blue`等价于`red, green 50%, blue`。

考虑`<size>`为`0px`时的极端情况。此时CSS会将`0px`视为一个非常小的值，类似于数学上的$\displaystyle\lim_{\epsilon\rightarrow0}{\epsilon}$。在Chrome上，这一点$\epsilon$是不可见的。

### §6.3.3 循环线性渐变(`repeating-linear-gradient`)

在之前的渐变中，首尾两个色标决定了颜色渐变的范围，超出这个范围都是纯色。而循环渐变允许色标和中色点也不断重复排列。

> 注意：循环渐变要求所有色标和中色点的位置均为**绝对长度**，而不能是**相对长度（例如百分数）**，否则循环渐变的行为将退化为非循环渐变，在整个背景显示区域内只重复一次。
>
> ```html
> <html>
> <head>
>     <style>  
>         div {
>             width: 20rem;
>             height: 40px;
>             border: 2px solid black;
>             color: white;
>             font-size: large;
>             font-weight: bold;
>             margin-bottom: 1rem;
>         }
>     </style>
> </head>
> <body>
>     <div style="background: repeating-linear-gradient(-45deg, black 0, black 25px,  25px, darkgoldenrod 50px) top left repeat;">这才应该是警戒线的样式</div>
>     <div style="background: repeating-linear-gradient(-45deg, black 0, black 50%,  50%, darkgoldenrod 100%) top left repeat;">这条警戒线只循环了一次，不正常</div>
> </body>
> </html>
> ```

> 注意：之前的非循环渐变默认首尾色标的位置分别为`0%`和`100%`，但是循环渐变要求末尾色标的位置必须显式声明，用以确定一个循环的长度。

当首尾色标的颜色不一样时，会出现“急停”现象，颜色在两个循环的交界处发生突变。这对于平滑渐变是不利的，但是有时我们可以故意利用这种现象绘制图案，例如下面的警戒线示例：

```html
<html>
<head>
    <style>  
        div {
            width: 20rem;
            height: 40px;
            border: 2px solid black;
            color: white;
            font-size: large;
            font-weight: bold;
            margin-bottom: 1rem;
        }
    </style>
</head>
<body>
    <div style="background: linear-gradient(-45deg, black 0, black 25px,  25px, darkgoldenrod 50px) top left/40px 40px repeat;">这条警戒线不正常</div>
    <div style="background: repeating-linear-gradient(-45deg, black 0, black 25px,  25px, darkgoldenrod 50px) top left repeat;">这才应该是警戒线的样式</div>
</body>
</html>
```

### §6.3.4 循环径向渐变(`repeating-radial-gradient`)

循环径向渐变`repeating-radial-gradient`的语法与径向渐变基本一致。

```html
<html>
<head>
    <style>  
        div {
            width: 20rem;
            height: 10rem;
            border: 2px solid black;
            color: black;
            font-size: large;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div style="background: repeating-radial-gradient(100px 50px, lightblue 20px, skyblue 50px, lightblue 80px);">这是循环镜像渐变</div>
</body>
</html>
```

> 注意：虽然循环线性渐变要求所有色标和中色点的位置不能为百分数，但是在循环径向渐变中却可以。

> 注意：如果要让循环径向渐变真正地循环起来，就必须显式声明循环径向渐变的尺寸。这是因为循环渐变尺寸的缺省值为`farthest-corner`。如果渐变中心恰好在容纳块中心，那么它等价于`50% 50%`。这会导致一次循环就会充满整个容纳块，导致渐变只会循环一次。

### §6.3.5 渐变设计技巧

渐变的本质就是图像，这意味着我们可以像图像那样，控制渐变、尺寸和控制方式。以下示例使用渐变创建了图像，作为`background`属性的`<image>`，作为背景图像进行平铺：

```html
<html>
<head>
    <style>
        div {
            border: 2px solid black;
            width: 10rem; 
            color: white;
            background: darkcyan center / 25px 25px repeat radial-gradient(
                circle at center, rgba(0,0,0,0.2), rgba(0,0,0,0.2) 10px, transparent 10px 
            );
        }
    </style>
</head>
<body>
    <div>使用渐变创建图像，作为background属性的&lt;image&gt;，地位等价于url(...)</div>
</body>
</html>
```

利用多个渐变绘制多个图像，应用到多个背景中，可以实现很惊艳的效果。以下示例使用了多个深红-浅红-深红的渐变，绘制了舞台的幕布：

```html
<html>
<head>
    <style>  
        div {
            border: 2px solid black;
            width: 80%;
            height: 10rem;
            margin: 0.5rem auto 0.5rem auto;
            color: #eeeeee;
            text-shadow: 1px 1px 2px black;
            font-size: larger;
            text-align: center;
            padding-top: 1rem;
        }
        div.layer1 {
            background: linear-gradient(0deg, rgba(255, 128, 128, 0.25), transparent 75%);
        }
        div.layer2 {
            background: linear-gradient(89deg, transparent, transparent 30%, #510A0E 35%, #510A0E 40%, #61100F 43%, #B93F3A 50%,
                    #4B0408 55%, #6A0F18 60%, #651015 65%, #510A0E 70%,
                    #510A0E 75%, rgba(255, 128, 128, 0) 80%, transparent);
        }
        div.layer3 {
            background: linear-gradient(92deg,
                    #510A0E, #510A0E 20%, #61100F 25%, #B93F3A 40%, #4B0408 50%,
                    #6A0F18 70%, #651015 80%, #510A0E 90%, #510A0E);
        }
        div.final {
            background:
                linear-gradient(0deg, rgba(255, 128, 128, 0.25), transparent 75%),
                linear-gradient(89deg, transparent, transparent 30%, #510A0E 35%, #510A0E 40%, #61100F 43%, #B93F3A 50%,
                    #4B0408 55%, #6A0F18 60%, #651015 65%, #510A0E 70%,
                    #510A0E 75%, rgba(255, 128, 128, 0) 80%, transparent),
                linear-gradient(92deg,
                    #510A0E, #510A0E 20%, #61100F 25%, #B93F3A 40%, #4B0408 50%,
                    #6A0F18 70%, #651015 80%, #510A0E 90%, #510A0E);
        }
    </style>
</head>
<body>
    <div class="layer1">第一层<br/>background: linear-gradient(0deg, rgba(255, 128, 128, 0.25), transparent 75%);</div>
    <div class="layer2">第二层<br/>background: linear-gradient(89deg, transparent, transparent 30%, #510A0E 35%, #510A0E 40%, #61100F 43%, #B93F3A 50%,
        #4B0408 55%, #6A0F18 60%, #651015 65%, #510A0E 70%,
        #510A0E 75%, rgba(255, 128, 128, 0) 80%, transparent);</div>
    <div class="layer3">第三层<br/>、background: linear-gradient(92deg,
        #510A0E, #510A0E 20%, #61100F 25%, #B93F3A 40%, #4B0408 50%,
        #6A0F18 70%, #651015 80%, #510A0E 90%, #510A0E);</div>
    <div class="final">三层叠加的结果</div>
</body>
</html>
```

## §6.4 盒子投影(`box-shadow`)

`box-shadow`属性用于给元素所在的框体创建投影。其语法与`text-shadow`大致一致。`box-shadow`接受1~4个距离参数与1个颜色参数，其中前两个距离参数代表横轴与纵轴的偏移量，第三个参数表示阴影半径，第四个参数表示阴影扩散距离。但是`box-shadow`支持在属性值开头声明`inset`属性，表示这是个内阴影。

```html
<html>
<head>
    <style>  
        body {
            background-image: repeating-linear-gradient(45deg, #eee, #eee 4px, #ccc 4px, #ccc 8px);
        }
        div {
            width: 12rem;
            height: 6rem;
            border: 2px solid black;
            border-radius: 1rem;
            font-weight: bold;
            margin: 0.5rem;
            padding: 0.5rem;
            background-color: lightblue;
            float: left;
        }
        div:nth-child(1){
            box-shadow: 10px 10px gray;
        }
        div:nth-child(2){
            box-shadow: inset 10px 10px gray;
        }
        div:nth-child(3){
            box-shadow: 0 0 5px 5px rgba(0, 0, 0, 0.5);
        }
        div:nth-child(4){
            box-shadow: inset 0 0 5px 5px rgba(0, 0, 0, 0.5);
        }
    </style>
</head>
<body>
    <div>这是一个box-shadow: 10px 10px gray;的盒子，是外阴影</div>
    <div>这是一个inset 10px 10px gray;的盒子，是内阴影</div>
    <div>这是一个box-shadow: 0 0 5px 5px rgba(0, 0, 0, 0.5);的盒子，是向外扩展的渐变阴影</div>
    <div>这是一个box-shadow: inset 0 0 5px 5px rgba(0, 0, 0, 0.5);的盒子，是向内扩展的渐变阴影</div>
</body>
</html>
```

乍一看，这个投影仿佛就是原框体的复制品，形状上一模一样，只不过被挡住了而已。但实际上并不是这样。做个实验，我们给框体设置透明背景，会发现框体的正下方根本没有盒子投影。这说明盒子投影的形状是不完整的。

```html
<html>
<head>
    <style>  
        body {
            background-image: repeating-linear-gradient(45deg, #eee, #eee 4px, #ccc 4px, #ccc 8px);
        }
        div {
            width: 20rem;
            height: 5rem;
            border: 2px solid black;
            font-size: large;
            font-weight: bold;
            
            background-color: rgba(255, 0, 0, 0.3);
            box-shadow: 10px 10px gray;
        }
    </style>
</head>
<body>
    <div>这是一个有投影的盒子</div>
</body>
</html>
```

与`text-shadow`一样，`box-shadow`也可以应用多个投影，用逗号`,`隔开即可。

# §7 浮动

“浮动”指的是元素的对齐方向。CSS标准规定：浮动通过`float`属性实现。有趣的是，在浮动的标准确定以前，就已经有了浮动的实现了。例如`<img align="right"/>`：

```html
<html>
<head>
    <style>
        img {
            background-color: gray;
            border: 1px solid;
        }
    </style>
</head>
<body>
    <img src="https://www.google.com/images/branding/googlelogo/1x/googlelogo_light_color_272x92dp.png" align="right"/>
</body>
</html>
```

在浏览器的审查元素中打开，会看到`<img>`中的`align="right"`被转换成了现代的`float: right`CSS属性。

| `float`属性值 | 作用           |
| ------------- | -------------- |
| `left`        | 元素浮动到左侧 |
| `right`       | 元素浮动到右侧 |
| `none`(缺省)  |                |

## §7.1 浮动的影响

1. 浮动的元素脱离了常规的文档流。元素浮动后，原来所占的位置空了出来，新位置参与实际的占位。

   ```html
   <html>
   <head>
       <style>
           div {
               border: 1px solid black;
               width: 20rem;
           }
           p {
               margin: 0.5rem;
           }
           p.aside {
               width: 6rem;
               float: right;
               border: 1px solid black;
               background-color: lightgrey;
           }
       </style>
   </head>
   <body>
       <div>
           <p>这是标题</p>
           <p class="aside">我是侧栏说明。我脱离了正常的文本布局，所以外层的&lt;div&gt;不会管我。</p>
           <p>这是正文。右面是一个&lt;p class="aside"&gt;，设置了float:right的CSS属性。</p>
       </div>
   </body>
   </html>
   ```

2. 元素浮动后，无论元素原先是行内框还是块级框，都会变成块级框。也就是说，CSS给浮动的元素自动加上`display: block`属性。

3. 浮动元素的左、右、上边界不能超过容纳块的左、右、上边界，却可以超过下边界。

   > 注意：如果浮动元素太宽，超出了左边界或右边界（却绝育浮动方向），则CSS不得不渲染，

   > 注意：如果给浮动元素设置负外边距，从视觉效果上来说，确实会发生越界。但是从规范上来说，这依然不矛盾。因为越界的判定标准是“子元素的外边界超出了父元素的容纳框”，而负外边距相当于覆盖了自己的外边界，使得外边界向容纳框中移动，因此外边界仍然在容纳框中。

4. 如果前面声明浮动的元素靠左，且后一个浮动元素的顶边**不在**前一个浮动元素底边的下边，那么后面元素的左边界必须在前面元素的右边界的右侧。同理，如果前面声明浮动的元素靠右，且同样后一个浮动元素**不在**下边，则后面元素的右边界必须在前面元素左边界的左侧。这条规则能避免浮动元素相互覆盖。

   > 注意：前一个浮动元素下边界在后一个浮动元素的上边界，有可能是因为两个浮动元素间相隔了若干个非浮动元素，也有可能是两个浮动元素的宽度之和超过了容纳块的宽度，使得CSS不得不换行。

   ```html
   <html>
   <head>
       <style>
           div {
               border: 1px solid black;
               width: 20rem;
           }
           p {
               margin: 0.5rem;
           }
           p.aside {
               float: left;
               border: 1px solid black;
               background-color: lightgrey;
           }
           p.rightFloat {
               width: 3rem;
               float: left;
               border: 1px solid black;
               background-color: lightgrey;  
           }
       </style>
   </head>
   <body>
       <div>
           <p>这是标题</p>
           <p class="aside" style="width: 6rem;">我是靠左的侧栏说明。</p>
           <p class="aside" style="width: 6rem;">我是另一个靠左的侧栏说明。 </p>
           <p>这是正文。本页面设置了两个带有float属性的元素，都是靠左浮动。</p>
       </div>
   </body>
   </html>
   ```

5. 浮动元素的顶边不能比前方任何浮动元素或块级元素的顶边高。

6. 在不违反以上规则的前提下，浮动元素必须尽可能的放在高的位置上。

   ```html
   <html>
   <head>
       <style>
           div {
               border: 1px solid black;
               width: 20rem;
           }
           p {
               margin: 0.5rem;
           }
           p.leftFloat {
               float: left;
               border: 1px solid black;
               background-color: lightgrey;
           }
           p.rightFloat {
               float: right;
               border: 1px solid black;
               background-color: lightgrey;  
           }
       </style>
   </head>
   <body>
       <div>
           <p>这是标题</p>
           <p class="leftFloat" style="width: 3rem;">我是靠左的侧栏说明。</p>
           <p class="leftFloat" style="width: 4rem;">我是另一个靠左的侧栏说明。 </p>
           <p class="rightFloat" style="width: 4rem;">我是靠右的侧栏说明，因为横向空间足够，所以没有另起一行。 </p>
           <p>这是正文。本页面设置了三个带有float属性的元素，前两个都是靠左浮动，后一个是靠右浮动。</p>
       </div>
   </body>
   </html>
   ```

7. 在满足以上规则的前提下，左浮动元素应该尽量靠左，右浮动元素应该尽量靠右。

8. 若浮动元素的后代中存在浮动元素，且子元素尺寸较大时，才扩大父元素的尺寸。反之如果是非浮动元素的后代，则不会扩大父元素的尺寸。

   为了防止浮动元素被遮盖，浮动元素的背景永远在非浮动元素之上。

   ```html
   <html>
   <head>
       <style>
           .box {
               border: 1px solid black;
               width: 16rem;
               background-color: lightcoral;
           }
           .float_picture {
               width: 2rem;
               height: 7rem;
               float: right;
               background: url('https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/down-arrow.png') repeat-y, lightgreen;
           }
       </style>
   </head>
   <body>
       <div class="box">
           <p>
               <span class="float_picture"></span>
               这是一个非浮动元素，右面的背景图片是靠右浮动的。
           </p>
       </div>
       <p style="background-color: lightcyan;">这是一段文本，但是被上面浮动元素隔开了，导致上半段间距较小，下半段间距较大。而且浮动元素的背景永远在非浮动元素之上。</p>
       <div class="box" style="float: left">
           <p>
               <span class="float_picture"></span>
               这是一个浮动元素，图片是靠右浮动的。<strong>注意到背景图像撑大了父元素的尺寸。</strong>
           </p>
       </div>
   </body>
   </html>
   ```

9. 当浮动元素与行内元素重叠时，两者位于同一图层渲染。当浮动元素与块级元素重叠时，块级元素的内容覆盖在浮动元素之上，块级元素的背景和边框在浮动元素之下。

## §7.2 清除浮动(`clear`)

有时我们想把文档划分为多个区域，每个区域相互独立。但是`float`的出现使得该规则被打破。在[§7.1 浮动的影响](##§7.1 浮动的影响)第八条规则中，我们能观察到这一异常行为。当时我们是将父元素也设为浮动元素，才解决了问题。实际上，CSS提供了另一种方法，能够确保父元素跟随子浮动元素自动增长，防止影响到其它区域。这就是`clear`属性。

| `clear`属性值 | 作用                           |
| ------------- | ------------------------------ |
| `left`        | 让左浮动元素的右侧不出现该元素 |
| `right`       | 让右浮动元素的左侧不出现该元素 |
| `both`        | 同时启用`left`和`right`        |
| `none`(缺省)  |                                |

下面的例子中，父元素的下面是一个同级`<p>`元素，父元素包含一个子浮动元素`<img>`：

```html
<html>
<head>
    <style>
        .box {
            border: 1px solid black;
            width: 16rem;
            background-color: lightcoral;
        }
        .float_picture {
            width: 2rem;
            height: 7rem;
            float: right;
            background: url('https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/down-arrow.png') repeat-y, lightgreen;
        }
    </style>
</head>
<body>
    <div class="box">
        <p>
            <span class="float_picture"></span>
            这是一个非浮动元素，右面的背景图片是靠右浮动的。
        </p>
    </div>
    <p style="background-color: lightcyan; clear: right;">这是一段文本，启用了clear: right，不会受到上面浮动元素的影响了</p>
</body>
</html>
```

> 注意：`clear`的实现方式发生过改变。CSS2及之前，`clear`的实现方式是增加元素的`margin-top`属性值，这会导致原先摄者的上外边距被覆盖掉。CSS2.1及之后引入了间距(`clearance`)，负责将元素向下移动，从而不再影响上外边距。

还有一个问题：我们看到子浮动元素与外级`<p>`元素是贴在一起的。如果我们要让这两者保持一点间隔，应该给这三者之中的谁添加`margin`属性呢？**答案是子浮动元素**。经过实践可知，另两者都不行。使用审查元素可知，CSS认为两个同级的元素根本没有挨在一起，所以给父元素是无效的；如果给另一个同级元素添加`margin`属性，就会发现它的外边距对浮动元素没有任何作用。

## §7.3 浮动形状

CSS3增加了新模块CSS Shapes，使得浮动框的形状可以不再局限于矩形。

### §7.3.1 定义形状(`shape-outside`)

`shape-outside`属性用于定义内容流动的形状。该属性计算图像中的透明部分，使得内容流入与其直接接触的那一侧的透明部分。也就是说，内容要么流向浮动元素的左侧，要么是右侧，不可能同时是左右侧。

| `shape-outside`属性值          | 作用 |
| ------------------------------ | ---- |
| `none`(缺省)                   |      |
| `<basic-shape> || <shape-box>` |      |
| `<image>`                      |      |

对于`<image>`，CSS将提取图片资源（带有Alpha通道的PNG、GIF）中的透明部分。

```html
<html>
<head>
    <style>
        .root {
            border: 1px solid black;
            width: 11rem;
            margin-bottom: 0.5rem;
        }
        img {
            float: left;
            width: 5rem;
        }
        img.float {
            shape-outside: url("https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/moon.png");
        }
    </style>
</head>
<body>
    <div class="root">
        <img class="float" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/moon.png"/>
        这是一个包含向左浮动图片的div。这段文字被图片的形状隔开了。
    </div>
    <div class="root">
        <img src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/moon.png"/>
        这是一个包含向左浮动图片的div。图像被当成一个矩形，而不是弯的。
    </div>
</body>
</html>
```

`<basic-shape>`可以是下面类型中的某一个：

- `inset()`([MDN文档](https://developer.mozilla.org/en-US/docs/Web/CSS/basic-shape/inset))：接受1~4个参数与质心位置，作为与容纳框的上右下左的边距绘制矩形
- `circle()`([MDN文档](https://developer.mozilla.org/en-US/docs/Web/CSS/basic-shape/circle))：接受半径参数与圆心位置，绘制圆形
- `ellipse()`([MDN文档](https://developer.mozilla.org/en-US/docs/Web/CSS/basic-shape/ellipse))：接受2个参数或四个关键词与圆心位置，绘制椭圆
- `polygen()`([MDN文档](https://developer.mozilla.org/en-US/docs/Web/CSS/basic-shape/polygon))：接受若干个端点位置，绘制多边形

```html
<html>
<head>
    <style>
        .root {
            border: 1px solid black;
            width: 18rem;
            margin-bottom: 1rem;
        }
        img {
            float: left;
            width: 2rem;
            background-color: lightblue;
            border: 1rem solid lightskyblue;
            padding: 1rem;
            margin: 1rem;
        }
        p {
            margin-top: 2rem;
            margin-bottom: 3rem;
        }
    </style>
</head>
<body>
    <div class="root">
        <img style="shape-outside: inset(30px);" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/chrome.jpg"/>
        <p>矩形：shape-outside: inset(30px);</p>
    </div>
    <div class="root">
        <img style="shape-outside: circle(15px);" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/chrome.jpg"/>
        <p>圆形：shape-outsise: border-box</p>
    </div>
    <div class="root">
        <img style="shape-outside: ellipse(50px 20px);" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/chrome.jpg"/>
        <p>竖椭圆：shape-outside: ellipse(50px 20px);</p>
    </div>
    <div class="root">
        <img style="shape-outside: polygon(50% 0%, 100% 50%, 50% 100%, 0% 50%);" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/chrome.jpg"/>
        <p>扁棱形：shape-outside: polygon(50% 0%, 100% 50%, 50% 100%, 0% 50%);</p>
    </div>
</body>
</html>
```

`<shape-box>`可以是下面类型中的某一个：

- `margin-box`：以外边距区的边界作为流动流入的区域
- `border-box`：以边框区的边界作为流动流入的区域
- `padding-box`：以内边距区边界作为流动流入的区域
- `content-box`：以内容区的边界作为流动流入的区域

```html
<html>
<head>
    <style>
        .root {
            border: 1px solid black;
            width: 15rem;
            margin-bottom: 0.5rem;
        }
        img {
            float: left;
            width: 2rem;
            background-color: lightblue;
            border: 1rem solid lightskyblue;
            padding: 1rem;
            margin: 1rem;
        }
        p {
            margin-top: 3rem;
            margin-bottom: 3rem;
        }
    </style>
</head>
<body>
    <div class="root">
        <img style="shape-outside: margin-box;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/chrome.jpg"/>
        <p>shape-outsise: margin-box</p>
    </div>
    <div class="root">
        <img style="shape-outside: border-box;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/chrome.jpg"/>
        <p>shape-outsise: border-box</p>
    </div>
    <div class="root">
        <img style="shape-outside: padding-box;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/chrome.jpg"/>
        <p>shape-outsise: padding-box</p>
    </div>
    <div class="root">
        <img style="shape-outside: content-box;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/chrome.jpg"/>
        <p>shape-outsise: content-box</p>
    </div>
</body>
</html>
```

### §7.3.2 形状透明阈值(`shape-image-threshold`)

前面我们提到过，图像的透明部分允许内容流入。至于像素点要怎么才算透明，Alpha值要怎么高才算符合要求，可以使用`shape-image-threshold`属性设置阈值。

```html
<html>
<head>
    <style>
        .root {
            border: 1px solid black;
            width: 18rem;
            margin-bottom: 1rem;
        }
        img {
            float: left;
            width: 5rem;
            background-color: lightblue;
            shape-outside: url("https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/sit-gradient.png");
        }
        p {
            margin-top: 0.5rem;
            margin-bottom: 0.5rem;
        }
    </style>
</head>
<body>
    <div class="root">
        <img style="shape-image-threshold: 0.1;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/sit-gradient.png"/>
        <p>这是一段文本，shape-image-threshold: 0.1;这是一段文本，shape-image-threshold: 0.1;</p>
    </div>
    <div class="root">
        <img style="shape-image-threshold: 0.5.;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/sit-gradient.png"/>
        <p>这是一段文本，shape-image-threshold: 0.5;这是一段文本，shape-image-threshold: 0.5;</p>
    </div>
    <div class="root">
        <img style="shape-image-threshold: 0.9;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/sit-gradient.png"/>
        <p>这是一段文本，shape-image-threshold: 0.9;这是一段文本，shape-image-threshold: 0.9;</p>
    </div>
</body>
</html>
```

### §7.3.3 形状外边距(`shape-margin`)

`shape-margin`属性将形状沿各个边的法向方向向外或向内移动，也就是为形状添加"外边距"。

```html
<html>
<head>
    <style>
        .root {
            border: 1px solid black;
            width: 15rem;
            margin-bottom: 1rem;
        }
        img {
            float: left;
            width: 10rem;
            shape-outside: url("https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/star.svg");
        }
        p {
            margin-top: 0.5rem;
            margin-bottom: 0.5rem;
        }
    </style>
</head>
<body>
    <div class="root">
        <img src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/star.svg"/>
        <p>这个元素中包含了一个向左浮动的图片和一个p标签，其中图片没有设置了shape-margin</p>
    </div>
    <div class="root">
        <img style="shape-margin: 1.4rem;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/star.svg"/>
        <p>这个元素中包含了一个向左浮动的图片和一个p标签，其中图片设置了shape-margin: 1.4rem;</p>
    </div>
    <div class="root">
        <img style="shape-margin: 2rem;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/star.svg"/>
        <p>这个元素中包含了一个向左浮动的图片和一个p标签，其中图片设置了shape-margin: 2rem;。超出容纳块的形状会被裁剪。</p>
    </div>
</body>
</html>
```

我们注意到最后一个`<div>`设置的`shape-margin`过大，导致文字没有按照预期的那样让形状周围排列。这是因为形状外边距生效的范围只在父元素容纳块中，否则过大的外边距会被容纳块边缘裁剪。为了解决这一问题，我们可以同步扩大`margin`的范围：

```html
<html>
<head>
    <style>
        .root {
            border: 1px solid black;
            width: 15rem;
            margin-bottom: 1rem;
        }
        img {
            float: left;
            width: 10rem;
            shape-outside: url("https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/star.svg");
        }
        p {
            margin-top: 0.5rem;
            margin-bottom: 0.5rem;
        }
    </style>
</head>
<body>
    <div class="root">
        <img style="shape-margin: 2rem; margin: 0 2rem 2rem 0;" src="https://meyerweb.github.io/csstdg4figs/10-floating-and-shapes/i/star.svg"/>
        <p>这个元素中包含了一个向左浮动的图片和一个p标签，其中图片设置了shape-margin: 2rem;。超出容纳块的形状会被裁剪。</p>
    </div>
</body>
</html>
```

# §8 定位

CSS一共提供了五种定位类型，由`position`属性指定：

| `position`属性值 | 中文名称 | 作用                                               | 非根元素的容纳块                                             |
| ---------------- | -------- | -------------------------------------------------- | ------------------------------------------------------------ |
| `static`(缺省)   | 静态定位 | 块级元素生成矩形框，行内元素生成若干行框           | 父块级元素容纳块                                             |
| `relative`       | 相对定位 | 元素框的位置偏移一定的距离，形状与`static`一样不变 | 父块级元素容纳块                                             |
| `sticky`         | 粘性定位 | 当且仅当达到触发粘滞的条件是，元素框才脱离文档流   | 如果父元素是块级元素，则为父元素的内边距块（即边框区以内）；如果父元素是行内元素，则为父元素内容区的外切矩形。 |
| `absolute`       | 绝对定位 | 元素框完全脱离文档流，位置参照物依然是父元素容纳块 |                                                              |
| `fixed`          | 固定定位 | 元素框完全脱离文档流，位置参照物是视图容纳块       |                                                              |

## §8.1 偏移属性

在相对定位、绝对定位、粘滞定位和固定定位中，需要声明指定定位元素的各边相对容纳块的偏移距离，使用的属性成为偏移属性：`top`、`right`、`bottom`、`left`。

```html
<html>
<head>
    <style>  
        div.container {
            background-color: lightgray;
            width: 20rem;
            height: 10rem;
            position: relative;
        }
        div.item {
            background-color: lightblue;
            position: absolute;
            top: 50%;
            left: 50%;
            bottom: 0;
            right: 0;
        }
    </style>
</head>
<body>
    <div class="container">
        这是一个容纳框
        <div class="item">这是一个定位元素</div>
    </div>
</body>
</html>
```

在定位元素中，宽度和高度不一定非要用`width`和`height`属性所定义，我们还可以用`top`、`right`、`bottom`、`left`四个便宜属性完全确定。

## §6.2 限制高度和宽度

CSS可以限制一个元素的高度范围与宽度范围，可以通过`min-width`和`max-width`指定宽度的范围，通过`min-height`和`max-height`指定高度的范围。这也是许多响应式设计、移动端视图的基础。

```html
<html>
<head>
    <style>  
        div.container {
            background-color: lightgray;
            width: 80%;
            height: 10rem;
            position: relative;
        }
        div.item {
            background-color: lightblue;
            position: absolute;
            min-width: 20rem;
            top: 50%;
            left: 50%;
            bottom: 0;
            right: 0;
        }
    </style>
</head>
<body>
    <div class="container">
        这是一个容纳框
        <div class="item">为了保证这个元素能容纳其中的内容，只有当页面足够宽时，这个定位元素的宽度才是父元素的50%。</div>
    </div>
</body>
</html>
```

## §6.3 内容溢出(`overflow`)

`overflow`属性决定了内容溢出容纳框时的行为：

| `overflow`属性值 | 作用                             |
| ---------------- | -------------------------------- |
| `visiable`(缺省) | 超出元素的内容是可见的           |
| `hidden`         | 超出元素的内容是隐形的           |
| `scroll`         | 超出元素的内容以滚动条的形式展示 |
| `auto`           | 由浏览器自行决定                 |

```html
<html>
<head>
    <style>  
        div.container {
            background-color: lightgray;
            width: 20rem;
            height: 5rem;
            position: relative;
            margin-bottom: 1rem;
        }
    </style>
</head>
<body>
    <div class="container" style="overflow: visible;">
        <p>这个容纳框包含着多行文本</p>
        <p>这个容纳框的样式为overflow: visible;</p>
        <p>这意味着溢出的内容是可见的</p>
    </div>
    <div class="container" style="overflow: hidden;">
        <p>这个容纳框包含着多行文本</p>
        <p>这个容纳框的样式为overflow: hidden;</p>
        <p>这意味着溢出的内容是隐形的</p>
    </div>
    <div class="container" style="overflow: scroll;">
        <p>这个容纳框包含着多行文本</p>
        <p>这个容纳框的样式为overflow: scroll;</p>
        <p>这意味着溢出的内容以滚动条的形式展示</p>
    </div>
    <div class="container" style="overflow: auto;">
        <p>这个容纳框包含着多行文本</p>
        <p>这个容纳框的样式为overflow: auto;</p>
        <p>这意味着溢出的内容由浏览器自行决定</p>
    </div>
</body>
</html>
```

## §6.4 可见性(`visibility`)

`visibility`属性决定着元素的可见性

| `visibility`属性值 | 作用                                                   |
| ------------------ | ------------------------------------------------------ |
| `visible`(缺省)    | 元素可见                                               |
| `hidden`           | 语速不可见，但仍然影响布局                             |
| `collapse`         | 对于渲染表格来说负责折叠，对于非表格元素等价于`hidden` |

> 注意：虽然`display: none`也能让元素隐形，但是实际上该属性将元素完全从文档流中移除，不再占据位置。而`visibility: hidden`不会影响页面布局，甚至边框也依然保留，从视觉效果来说等价于`opacity: 0`。

`visibility`属性是继承的，但是给子元素设置`visibility: visible`，可以突破父元素`visibility: none`的限制。

## §6.5 绝对定位

绝对定位的元素完全从文档流中移除，其位置由相对容纳块的距离确定。绝对定位元素的容纳块是**`position`属性不是`static`的最近的祖辈元素**。我们直到`position`属性的默认值就是`static`。所以我们选中容纳块后，一般将其属性改为`position: relative`，而且不设置偏移。



9.8 15w字

9.9 16w字



# §A 附录

## §A.1 厂商前缀

有些CSS属性名会带有一个前缀（例如`-o-border-image`），用于让浏览器厂商标记实验用途或专属的CSS功能。

| 前缀       | 厂商                                          |
| ---------- | --------------------------------------------- |
| `-epub-`   | 国际数字出版论坛指定的`ePub`格式              |
| `-moz-`    | 基于`Mozilla`的浏览器（例如`Firefox`）        |
| `-ms-`     | `Internet Explorer`                           |
| `-o-`      | 基于`Opera`的浏览器                           |
| `-webkit-` | 基于`Webkit`的浏览器（例如`Safari`,`Chrome`） |

## §A.2 媒体类型

CSS2引入了媒体类型，表示当前文档展示时所处的环境。

可以用以下方法声明媒体类型：

```html
1.
<link ... media="{{media}}">
<link ... media="{{media}}, {{media}}, ...">

2.
<style media="{{media}}"></style>
<style media="{{media}}, {{media}}, ..."></style>

3.
<style> @import url(index.css) {{media}}</style>
<style> @import url(index.css) {{media}}, {{media}}, ...</style> /*引入多种媒体类型的样式*/
<style> @import url(index.css) {{media}} and {{media}} and ...</style> /**/

<style> @media {{media}} {color: red;}</style>
<style> @media {{media}}, {{media}} {color: red;}</style>
```

常见的媒体类型有：

| 媒体类型     | 作用         |
| ------------ | ------------ |
| `all`        | 全部         |
| `print`      | 打印文档     |
| `screen`     | 桌面显示器   |
| `projection` | 幻灯片或投影 |
| `handheld`   | 移动端浏览器 |

