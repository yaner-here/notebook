# §18 开发规范

经过前17章的学习，我们已经掌握了CSS的基础语法。本节将介绍实际开发中的CSS规范。

## §18.1 CSS文件命名

| CSS文件名    | 含义                                         |
| ------------ | -------------------------------------------- |
| `reset.css`  | 重置样式：重置元素默认样式                   |
| `global.css` | 全局样式：全站共用样式，用于定义页面基础样式 |
| `theme.css`  | 主题样式：用于更换站点皮肤                   |
| `module.css` | 模块样式：用于模块/组件的样式                |
| `master.css` | 母版样式：用于设置模版页的样式               |
| `column.css` | 专栏样式：用于设置顶部栏、侧边栏             |
| `form.css`   | 表单样式：用于设置`<form>`标签的样式         |
| `mend.css`   | 补丁样式：用于维护、修改的样式               |
| `print.css`  | 打印样式：用于打印的样式                     |

## §18.2 `class`命名

| 网页内容 | `class`命名           | 网页内容 | `class`命名     |
| -------- | --------------------- | -------- | --------------- |
| 最外层   | `wrapper`             | 顶导航   | `top-nav`       |
| 头部     | `header`              | 菜单     | `menu`          |
| 内容     | `content`/`container` | 子菜单   | `submenu`       |
| 侧边栏   | `sidebar`             | 标题     | `title`         |
| 栏目     | `column`              | 摘要     | `summary`       |
| 热点     | `hot`                 | 登录条   | `loginbar`      |
| 新闻     | `news`                | 搜索     | `search`        |
| 下载     | `download`            | 标签页   | `tab`           |
| 标志     | `logo`                | 广告     | `banner`        |
| 导航     | `nav`                 | 小技巧   | `tips`          |
| 主体     | `main`                | 图标     | `icon`          |
| 左侧     | `main-left`           | 法律声明 | `siteinfolegal` |
| 右侧     | `main-right`          | 网站地图 | `sitemap`       |
| 底部     | `footer`              | 工具条   | `toolbar`       |
| 友情链接 | `friendlink`          | 首页     | `homepage`      |
| 加入我们 | `joinus`              | 子页     | `subpage`       |
| 版权     | `copyright`           | 合作伙伴 | `partner`       |
| 服务     | `service`             | 帮助     | `help`          |
| 登录     | `login`               | 指南     | `guild`         |
| 注册     | `register`            | 滚动     | `scroll`        |
| 主导航   | `main-nav`            | 提示信息 | `msg`           |
| 子导航   | `sub-nav`             | 投票     | `vote`          |
| 边导航   | `side-nav`            | 相关文章 | `related`       |
| 左导航   | `leftside-nav`        | 文章列表 | `list`          |
| 右导航   | `rightside-nav`       |          |                 |

## §18.3 CSS属性顺序

我们在之前的学习中，已经意识到了CSS属性先后顺序的重要性（例如`::hover`、`::activate`等属性）。下标展示出一些常用的推荐CSS属性顺序。

| CSS属性类别     | 优先级 | 涉及的部分CSS属性                                            |
| --------------- | ------ | ------------------------------------------------------------ |
| 文档流/布局属性 | ++     | `display`、`position`、`float`、`clear`                      |
| 盒模型属性      | +      | `width`、`height`、`padding`、`margin`、`border`、`overflow` |
| 文本属性        | =      | `font`、`line-height`、`text-align`、`text-indent`、`vertical-align` |
| 装饰属性        | -      | `color`、`background`、`opacity`、`cursor`                   |
| 其他属性        | --     | `content`、`list-style`、`quotes`                            |

## §18.4 重置默认样式

我们知道，浏览器已经给部分HTML元素设置了默认样式，例如`<input type="button">`、`<ul><li>`等等。每种元素设置的默认样式种类都不一样，因此要重置所有默认样式时，会遇到以下几个问题：

- 某个CSS属性在某个元素上没有默认样式

  你可能会使用`* {margin: 0; padding: 0}`之类的语法重置所有元素。但是有些默认属性没有设置，因此对齐重置CSS属性是没有意义的。这样做会导致性能损耗。

- 难以用一条规则覆盖所有的默认样式

  选择符提供了`*`通配符用于选择所有元素，但是CSS属性名没有提供通配符，所以我们难以覆盖所有的默认样式。

为解决这一问题，开发者Eric Meyer在2011年手动维护并发布了[CSS样式重置表（Reset CSS）](https://meyerweb.com/eric/tools/css/reset/)，覆盖了所有HTML元素的默认样式：

```css
/* http://meyerweb.com/eric/tools/css/reset/ 
   v2.0 | 20110126
   License: none (public domain)
*/
html, body, div, span, applet, object, iframe,
h1, h2, h3, h4, h5, h6, p, blockquote, pre,
a, abbr, acronym, address, big, cite, code,
del, dfn, em, img, ins, kbd, q, s, samp,
small, strike, strong, sub, sup, tt, var,
b, u, i, center,
dl, dt, dd, ol, ul, li,
fieldset, form, label, legend,
table, caption, tbody, tfoot, thead, tr, th, td,
article, aside, canvas, details, embed, 
figure, figcaption, footer, header, hgroup, 
menu, nav, output, ruby, section, summary,
time, mark, audio, video {
	margin: 0;
	padding: 0;
	border: 0;
	font-size: 100%;
	font: inherit;
	vertical-align: baseline;
}
/* HTML5 display-role reset for older browsers */
article, aside, details, figcaption, figure, 
footer, header, hgroup, menu, nav, section {
	display: block;
}
body {
	line-height: 1;
}
ol, ul {
	list-style: none;
}
blockquote, q {
	quotes: none;
}
blockquote:before, blockquote:after,
q:before, q:after {
	content: '';
	content: none;
}
table {
	border-collapse: collapse;
	border-spacing: 0;
}
```

# §19 开发技巧

本章将给出实际开发中常见的需求，并给出相应的CSS最优解。

## §19.1 选择器

### §19.1.1 元素分隔

例题：给定下列菜单，要求相邻两个元素的右边距为`2rem`。

```html
<ul>
    <li>首页</li>
    <li>新闻</li>
    <li>关于</li>
</ul>
```

乍一看，我们可能会想到`li {margin-right: 1rem;}`。但是这样的话，最右侧的元素也会有多余的右边距。如果再用`li:last-of-type {margin-right: inherit}`，虽然也能得到效果，但是太臃肿了。使用相邻选择器只需一行：

```css
li + li { margin-right: 1rem; }
```

## §19.2 盒子模型

### §19.2.1 `border`性能调优

`border: 0`和`border: none`的视觉效果是完全一样的，但在实际开发中我们推荐使用后者，原因有以下两点：

- 性能问题

  如果设置成`border: 0`，那么浏览器依然会对`border`进行渲染，而且确实占用了内存。而`border: none`就能避免这一问题。

- 兼容问题

  `border: 0`的兼容性非常好，在所有浏览器中都表示不显示边框。然而在IE6/IE7中，`border: none`不会产生任何效果，边框依然存在。

### §19.2.2 外边距叠加

外边距叠加指的是两个垂直外边距（`margin`）相遇时，两个外边距会合并在一起，合并后的长度为原先两个外边距的最大值。

外边距叠加可以分为同级元素、父子元素、空元素三种情况：

- 同级元素：上面元素的下外间距与下面元素的上外间距融合

  ```html
  <html>
      <head>
          <style>
              .wrapper {
                  background-color: aquamarine;
                  height: max-content;
                  width: fit-content;
              }
              .wrapper > * {
                  height: 5rem;
                  width: 12rem;
                  background-color: lightblue;
                  text-align: center;
                  line-height: 5rem;
              }
              .wrapper > .box1 { margin-bottom: 30px; }
              .wrapper > .box2 { margin-top: 30px; }
          </style>
      </head>
      <body>
          <div class="wrapper">
              <div class="box1">margin-bottom: 30px</div>
              <div class="box2">margin-top: 30px</div>
          </div>
          最终间距等于max(30px, 30px) = 30px
      </body>
  </html>
  ```

- 父子元素：父元素的上外间距/下外间距与内部子元素的上外间距/下外间距融合

  ```html
  <html>
      <head>
          <style>
              .wrapper {
                  background-color: aquamarine;
                  height: max-content;
                  width: fit-content;
              }
              .wrapper > * {
                  height: 5rem;
                  width: 12rem;
                  background-color: lightblue;
                  text-align: center;
                  line-height: 5rem;
              }
              .wrapper {
                  margin-top: 30px;
              }
              .wrapper > .box { margin-top: 10px; }
          </style>
      </head>
      <body>
          <div class="wrapper">
              <div class="box">margin-top: 30px</div>
              margin-top: 30px<br>
              最终间距等于max(30px, 10px) = 30px
          </div>
      </body>
  </html>
  ```

- 空元素：当元素内容区高度为0时，元素的上外边距和下外边距融合

  ```html
  <html>
      <head>
          <style>
              .wrapper {
                  background-color: aquamarine;
                  height: max-content;
                  width: fit-content;
              }
              .wrapper > * {
                  height: 5rem;
                  width: 12rem;
                  background-color: lightblue;
                  text-align: center;
                  line-height: 5rem;
              }
              .wrapper:nth-of-type(2) {
                  padding-top: 30px;
                  padding-bottom: 30px;
              }
          </style>
      </head>
      <body>
          <div class="wrapper">
              我是上面的wrapper
          </div>
          <div class="wrapper">
              <!-- 内容区高度为0 -->
          </div>
          <div class="wrapper">
              我是下面的wrapper
          </div>
          最终间距等于max(30px, 30px) = 30px
      </body>
  </html>
  ```

  负边距叠加的初衷是希望排版时能保证间距的一致性。例如`article {margin-top:20px; margin-bottom:20px}`保证了第一个`<article>`和顶部、每个`<article>`之间、最后一个`<article>`与底部之间的距离都是`20px`定值。

### §19.2.3 负外边距

我们知道，`margin`的取值也可以是负数。无论`margin`是正是负，该属性都会改变元素的位置，具体规则可以参照下表：

| 为负值的CSS属性                | CSS作用的元素 | 位置发生改变的元素 | 移动方向       |
| ------------------------------ | ------------- | ------------------ | -------------- |
| `margin-top`/`margin-left`     | 文档流元素    | 当前元素           | 反推到相反方向 |
| `margin-right`/`margin-bottom` | 文档流元素    | 后续元素           | 反推到相反方向 |
| `margin-top`/`margin-left`     | 浮动元素      | 当前元素           | 受浮动方向影响 |
| `margin-right`/`margin-bottom` | 浮动元素      | 后续元素           | 受浮动方向影响 |

```html
<html>
    <head>
        <style>
            .container { display: flex; }
            .wrapper {
                width: 200px;
                height: auto;
                text-align: center;
                margin: 10px;
            }
            .wrapper > * { height: 60px; }
            .wrapper > div:nth-of-type(1){ background-color: lightblue; }
            .wrapper > div:nth-of-type(2){ background-color: lightcoral; }
            .wrapper > div:nth-of-type(3){ background-color: lightgreen; }

            .wrapper:nth-of-type(2) > div:nth-of-type(2) {
                margin-top: -10px;
                margin-bottom: -25px;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <div class="wrapper">
                <div>1</div><div>2</div><div>3</div>
            </div>
            <div class="wrapper">
                <div>1</div><div>margin-top: -10px;<br>margin-bottom: -25px</div><div>3</div>
            </div>
        </div>
    </body>
</html>
```

负外边距有以下用途：

- 对齐文本与图片

  在默认情况下，图片和文本的中心线不一定是同一条水平线。例如当图片大于文字时，我们可以给图片设置负底边距：

  ```python
  <html>
      <head>
          <style>
              *:not(body) {
                  border: 1px solid black;
                  margin: 0;
                  padding: 0;
              }
              body > div {
                  background-color: lightblue;
              }
              body > div:nth-of-type(2) > img {
                  margin: 0 0px -10px 0;
              }
          </style>
      </head>
      <body>
          <div>
              <img src="https://www.google.com/favicon.ico">
              <a>Hello, World!</a>
          </div>
          <br>
          <div>
              <img src="https://www.google.com/favicon.ico">
              <a>Hello, World!</a>
          </div>
      </body>
  </html>
  ```

  这种方式的缺点在于减少了“碰撞箱体积”，从而容易与周围元素发生重叠。为解决这一问题，我们可以使用`vertical-align: text-bottom`。

- 双栏自适应布局

  下面的代码定义了一个双栏布局的页面，左侧为主体部分，宽度自适应；右侧为侧边栏部分，宽度固定。

  ```html
  <html>
      <head>
          <style>
              .main, .sidebar {
                  float: left;
                  background: linear-gradient(90deg, rgb(17, 156, 255), rgb(30, 200, 255));
                  border: 1px solid black;
                  box-sizing: border-box; /* 将边框宽度考虑在内,防止float被挤到下一行 */
              }
              .main {
                  width: 100%; 
                  margin-right: -200px;
              }
              .sidebar {
                  width: 200px; 
              }
              .main p {
                  margin-right: calc(200px + 10px); /* 允许主体部分内容区动态调整宽度,防止内容区被遮盖,还可以设置10px间距 */
              }
          </style>
      </head>
      <body>
          <div class="main"><p>这是主体部分，自适应宽度</p></div> 
          <div class="sidebar"><p>这是侧边栏部分，固定宽度</p></div>	
      </body>
  </html>
  
  ```

  让我们来分析这段代码的原理：首先，既然主体和侧边栏都是浮动布局，且主体部分的宽度为100%，说明主题部分的宽度就是整个`<body>`内容区的宽度，会把侧边栏挤到下一行。然后，主体部分通过`margin-right: -200px`缩小了右侧的“碰撞箱体积”，于是这`200px`的空间恰好能被侧边栏填满，于是侧边栏合并到了同一行。最后，主体部分中的`<p>`向右有着`210px`的外边距，因此可以保证主体部分的内容区不会被侧边栏覆盖。

  这种技巧在WordPress中被广泛使用。

- 元素垂直居中

  ```html
  <html>
      <head>
          <style>
              .wrapper {
                  position: relative;
                  width: 200px;
                  height: 160px;
                  border: 1px solid black;
              }
              .wrapper > .item {
                  position: absolute;
                  top: 50%; /* 移动子项左上角 */
                  left: 50%; /* 移动子项左上角 */
                  width: 100px;
                  height: 60px;
                  margin-top: calc(-60px / 2); /* 微调,让中心点位于左上角的位置 */
                  margin-left: calc(-100px / 2); /* 微调,让中心点位于左上角的位置 */
                  background-color: lightblue;
              }
          </style>
      </head>
      <body>
          <div class="wrapper">
              <div class="item"></div>
          </div>
      </body>
  </html>
  ```

### §19.2.4 清除浮动

我们知道，设置了`float`CSS属性的浮动元素是脱离文档流的。这会导致父元素在计算自身尺寸时会忽略浮动元素的尺寸，这一现象称为“高度坍塌”。开发者可以给父元素设置`overflow: hidden`来清除浮动：

```html
<html>
    <head>
        <style>
            .container {
                width: 500px;
                border: 3px solid red;
                padding: 0.2rem;
            }
            .item {
                width: 200px;
                height: 100px;
                border: 1px solid black;
                float: left;
            }
            .item:nth-of-type(1) { float: left; }
            .item:nth-of-type(2) { float: right; }

            .container:nth-of-type(2) { overflow: hidden; }
        </style>
    </head>
    <body>
        <div class="container">
            <div class="item"></div>
            <div class="item"></div>
        </div>
        <div class="container">
            <div class="item"></div>
            <div class="item"></div>
        </div>
    </body>
</html>
```

## §19.3 `display`属性

`display`属性常有以下取值：

| `display`属性值 | 含义           | 尺寸支持 | 外边距支持                                                   | 举例               |
| --------------- | -------------- | -------- | ------------------------------------------------------------ | ------------------ |
| `block`         | 块级元素       | 全支持   | 全支持                                                       | `<div>`            |
| `inline`        | 行内元素       | 不支持   | 只支持`margin-left`/`margin-right`，不支持`margin-top`/`margin-bottom` | `<em>`             |
| `inline-block`  | 行内块级元素   | 全支持   | 全支持                                                       | `<img>`、`<input>` |
| `none`          | 隐藏           |          |                                                              |                    |
| `table-cell`    | 表格单元格元素 |          |                                                              | `<td>`             |

### §19.3.1 表格单元格元素

`display: table-cell`可以让元素以表格单元格的形式显示，具备`<td>`元素的所有特点。其用途有以下三点：

- 图片垂直居中

  ```html
  <html>
      <head>
          <style>
              body { background-color: lightblue; }
              .container {
                  /* display和vertical-align配合使用,实现图片居中 */
                  display: table-cell;
                  vertical-align: middle; 
                  
                  width: 200px;
                  height: 150px;
                  border: 1px solid black;
                  text-align: center; /* 图片水平居中 */
              }
              .container > img {
                  height: 20%;
              }
          </style>
      </head>
      <body>
          <div class="container"><img src="https://www.baidu.com/img/flexible/logo/pc/result.png" alt=""></div>
          <div class="container"><img src="https://www.baidu.com/img/flexible/logo/pc/result@2.png" alt=""></div>
          <div class="container"><img src="https://www.baidu.com/img/flexible/logo/pc/peak-result.png" alt=""></div>
      </body>
  </html>
  ```

- 等高布局

  我们知道，同一行的单元格元素`<td>`的高度相等。同理，`display: table-cell`的元素天生就有等高布局的作用。这种方式的优势在于：我们不用手动指定两列的高度相等。

  ```html
  <html>
      <head>
          <style>
              body { background-color: lightblue; }
              .container {
                  display: table-cell;
                  
                  width: 200px;
                  height: 150px;
                  border: 1px solid black;
                  text-align: center;
              }
              .container > img {
                  height: 20%;
              }
          </style>
      </head>
      <body>
          <div class="container"><img src="https://www.baidu.com/img/flexible/logo/pc/result.png" alt=""></div>
          <div class="container"></div>
          <script>
              document.querySelectorAll('.container:nth-of-type(2)').forEach((element)=>{
                  element.innerHTML = "这是一段多行文本<br>".repeat(15)
              })
          </script>
      </body>
  </html>
  ```

- 自动平均划分元素

  回想一行中的多个单元格挤在同一行的情景，不难发现这些单元格能自动调整宽度，最终占满一行。其行为类似于`display: flex`，会按照原先宽度作为占据宽度时所用的权重。是`display: flex`作用的元素是父元素，而`display: table-cell`作用的元素是子元素。

  ```html
  <html>
      <head>
          <style>
              .container {
                  width: 400px;
                  background-color: lightblue;
              }
              .container > * {
                  display: table-cell;
                  width: 100px;
                  border: 1px solid black;
              }
              .container > *:nth-child(1) { width: 100px; }
              .container > *:nth-child(2) { width: 200px; }
              .container > *:nth-child(3) { width: 300px; }
          </style>
      </head>
      <body>
          <div class="container">
              <div>123</div>
              <div>123</div>
              <div>123</div>
          </div>
      </body>
  </html>
  ```

### §19.3.2 行内块级元素间距

`display: inline-block`是自带“外间距”的。这个“外间距”即使在审查元素上也看不到。要消除这一间距，我们一方面可以给父元素设置`font-size: 0`，然后给子元素单独设置正常的`font-size`；另一方面可以让源代码中的子元素在同一行。

```html
<html>
    <head>
        <style>
            .container {
                width: 400px;
                background-color: lightblue;
            }
            .container > * {
                display: inline-block;
                width: 100px;
                border: 1px solid black;
                font-size: 20px;
            }
            .container:nth-of-type(3) { font-size: 0; }
        </style>
    </head>
    <body>
        <p>display: inline-block</p>
        <div class="container">
            <div>123</div>
            <div>123</div>
            <div>123</div>
        </div>
        <p>display: inline-block, But elements' source codes are in a single line.</p>
        <div class="container">
            <div>123</div><div>123</div><div>123</div>
        </div>
        <p>display: inline-block, But the superelement's font-size is set to 0.</p>
        <div class="container">
            <div>123</div>
            <div>123</div>
            <div>123</div>
        </div>
    </body>
</html>
```

## §19.4 文本效果

### §19.4.1 `text-indent`负值

我们已经知道`text-indent`常用于定义段落的首行多节。例如`text-indent: 2em`能让段落实现首行缩进。其实`text-indent`也能取复制。

考虑下列情景：现要求对网站进行SEO优化。已知SEO特别关注`<h1>`标签，一种常见的思路是将LOGO也放入到`<h1>`标签中。然而搜索引擎只能识别文字，无法识别其中的图片。为解决这一问题，一种思路是让`<h1>`的宽度等于图片的宽度，然后定义`<h1>`的背景图片`background-image`恰为该LOGO图片，最后使用`text-indent: -9999px`来隐藏`<h1>`的文本内容。

```html
<html>
    <head>
        <style>
            h1 {
                background-image: url(https://www.baidu.com/favicon.ico);
                background-repeat: no-repeat;
                text-indent: -9999px;

                border: 1px solid black;
                width: 64px;
                height: 64px;
            }
        </style>
    </head>
    <body>
        <h1>百度一下，你就知道</h1>
    </body>
</html>
```

对于搜索引擎而言，`display: none`的元素会被视为垃圾信息而忽略掉，从而丢失`<h1>`的权重。因此在本例中不推荐使用`display: none`。

### §19.4.2 深入`line-height`

回想英文练习簿的印刷参考线，一行英文的参考线分为四行，从上到下分别是顶线、中线、基线、底线。

<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" width="915px" height="386px" viewBox="-0.5 -0.5 915 386" content="&lt;mxfile host=&quot;app.diagrams.net&quot; modified=&quot;2023-11-12T17:41:47.848Z&quot; agent=&quot;Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36&quot; etag=&quot;hdgW06tmyefBB6nMuF7n&quot; version=&quot;22.1.0&quot; type=&quot;device&quot;&gt;&#10;  &lt;diagram name=&quot;第 1 页&quot; id=&quot;1swZFBiTSMPvMh5uhhbn&quot;&gt;&#10;    &lt;mxGraphModel dx=&quot;1436&quot; dy=&quot;788&quot; grid=&quot;1&quot; gridSize=&quot;10&quot; guides=&quot;1&quot; tooltips=&quot;1&quot; connect=&quot;1&quot; arrows=&quot;1&quot; fold=&quot;1&quot; page=&quot;1&quot; pageScale=&quot;1&quot; pageWidth=&quot;500&quot; pageHeight=&quot;200&quot; math=&quot;0&quot; shadow=&quot;0&quot;&gt;&#10;      &lt;root&gt;&#10;        &lt;mxCell id=&quot;0&quot; /&gt;&#10;        &lt;mxCell id=&quot;1&quot; parent=&quot;0&quot; /&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-2&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;15&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;15&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-3&quot; value=&quot;&amp;lt;font style=&amp;quot;font-size: 60px;&amp;quot; face=&amp;quot;Comic Sans MS&amp;quot;&amp;gt;Hello, my Friend!&amp;lt;/font&amp;gt;&quot; style=&quot;text;html=1;align=center;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;275&quot; y=&quot;5&quot; width=&quot;490&quot; height=&quot;90&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-5&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;45&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;45&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-6&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;75&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;75&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-7&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;105&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;105&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-8&quot; value=&quot;顶线(top)&quot; style=&quot;text;html=1;align=left;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;135&quot; width=&quot;70&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-9&quot; value=&quot;中线(middle)&quot; style=&quot;text;html=1;align=left;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;135&quot; y=&quot;30&quot; width=&quot;90&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-10&quot; value=&quot;基线(baseline)&quot; style=&quot;text;html=1;align=left;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;135&quot; y=&quot;60&quot; width=&quot;100&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-11&quot; value=&quot;底线(bottom)&quot; style=&quot;text;html=1;align=left;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;135&quot; y=&quot;90&quot; width=&quot;90&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-13&quot; value=&quot;字符中心线&quot; style=&quot;text;html=1;align=left;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;825&quot; y=&quot;45&quot; width=&quot;80&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-38&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;225&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;225&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-39&quot; value=&quot;&amp;lt;font style=&amp;quot;font-size: 60px;&amp;quot; face=&amp;quot;Comic Sans MS&amp;quot;&amp;gt;Hello, my Friend!&amp;lt;/font&amp;gt;&quot; style=&quot;text;html=1;align=center;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;275&quot; y=&quot;215&quot; width=&quot;490&quot; height=&quot;90&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-40&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;255&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;255&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-41&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;285&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;285&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-42&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;315&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;315&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-43&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;dashed=1;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;225&quot; y=&quot;270&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;270&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-44&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;dashed=1;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;270&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;225&quot; y=&quot;270&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-45&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;dashed=1;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;215&quot; y=&quot;165&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;805&quot; y=&quot;165&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-47&quot; value=&quot;&amp;lt;font style=&amp;quot;font-size: 12px;&amp;quot;&amp;gt;半行距分割线&amp;lt;/font&amp;gt;&quot; style=&quot;edgeLabel;html=1;align=center;verticalAlign=middle;resizable=0;points=[];&quot; vertex=&quot;1&quot; connectable=&quot;0&quot; parent=&quot;3-VXkYujrOfkpzglf_jQ-45&quot;&gt;&#10;          &lt;mxGeometry x=&quot;-0.034&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;20&quot; as=&quot;offset&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-48&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;dashed=1;&quot; edge=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;212&quot; y=&quot;375&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;802&quot; y=&quot;375&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-49&quot; value=&quot;&amp;lt;font style=&amp;quot;font-size: 12px;&amp;quot;&amp;gt;半行距分割线&amp;lt;/font&amp;gt;&quot; style=&quot;edgeLabel;html=1;align=center;verticalAlign=middle;resizable=0;points=[];&quot; vertex=&quot;1&quot; connectable=&quot;0&quot; parent=&quot;3-VXkYujrOfkpzglf_jQ-48&quot;&gt;&#10;          &lt;mxGeometry x=&quot;-0.034&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;20&quot; as=&quot;offset&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-50&quot; value=&quot;&quot; style=&quot;strokeWidth=1;html=1;shape=mxgraph.flowchart.annotation_2;align=left;labelPosition=right;pointerEvents=1;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;95&quot; y=&quot;165&quot; width=&quot;20&quot; height=&quot;220&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-51&quot; value=&quot;&quot; style=&quot;strokeWidth=1;html=1;shape=mxgraph.flowchart.annotation_2;align=left;labelPosition=right;pointerEvents=1;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;175&quot; y=&quot;165&quot; width=&quot;20&quot; height=&quot;59&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-52&quot; value=&quot;&quot; style=&quot;strokeWidth=1;html=1;shape=mxgraph.flowchart.annotation_2;align=left;labelPosition=right;pointerEvents=1;spacingTop=0;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;175&quot; y=&quot;227&quot; width=&quot;20&quot; height=&quot;89&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-54&quot; value=&quot;内容区&quot; style=&quot;text;html=1;align=center;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;125&quot; y=&quot;256.5&quot; width=&quot;60&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-55&quot; value=&quot;半行距&quot; style=&quot;text;html=1;align=center;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;125&quot; y=&quot;179.5&quot; width=&quot;60&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-56&quot; value=&quot;行框&quot; style=&quot;text;html=1;align=center;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;50&quot; y=&quot;260&quot; width=&quot;50&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-57&quot; value=&quot;&quot; style=&quot;strokeWidth=1;html=1;shape=mxgraph.flowchart.annotation_2;align=left;labelPosition=right;pointerEvents=1;spacingTop=0;rotation=-180;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;835&quot; y=&quot;105&quot; width=&quot;20&quot; height=&quot;120&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-58&quot; value=&quot;&quot; style=&quot;endArrow=none;html=1;rounded=0;fillColor=#f5f5f5;strokeColor=#666666;dashed=1;exitX=0.811;exitY=-0.035;exitDx=0;exitDy=0;exitPerimeter=0;&quot; edge=&quot;1&quot; parent=&quot;1&quot; source=&quot;3-VXkYujrOfkpzglf_jQ-10&quot;&gt;&#10;          &lt;mxGeometry width=&quot;50&quot; height=&quot;50&quot; relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#10;            &lt;mxPoint x=&quot;225&quot; y=&quot;60&quot; as=&quot;sourcePoint&quot; /&gt;&#10;            &lt;mxPoint x=&quot;815&quot; y=&quot;60&quot; as=&quot;targetPoint&quot; /&gt;&#10;          &lt;/mxGeometry&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-59&quot; value=&quot;&quot; style=&quot;strokeWidth=1;html=1;shape=mxgraph.flowchart.annotation_2;align=left;labelPosition=right;pointerEvents=1;spacingTop=0;rotation=-180;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;905&quot; y=&quot;106&quot; width=&quot;20&quot; height=&quot;210&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-60&quot; value=&quot;行距&quot; style=&quot;text;html=1;align=center;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;850&quot; y=&quot;149.5&quot; width=&quot;50&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;        &lt;mxCell id=&quot;3-VXkYujrOfkpzglf_jQ-61&quot; value=&quot;行高&quot; style=&quot;text;html=1;align=center;verticalAlign=middle;resizable=0;points=[];autosize=1;strokeColor=none;fillColor=none;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#10;          &lt;mxGeometry x=&quot;915&quot; y=&quot;196&quot; width=&quot;50&quot; height=&quot;30&quot; as=&quot;geometry&quot; /&gt;&#10;        &lt;/mxCell&gt;&#10;      &lt;/root&gt;&#10;    &lt;/mxGraphModel&gt;&#10;  &lt;/diagram&gt;&#10;&lt;/mxfile&gt;&#10;"><defs/><g><path d="M 165 15 L 765 15" fill="none" stroke="#666666" stroke-miterlimit="10" pointer-events="stroke"/><rect x="225" y="5" width="490" height="90" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 50px; margin-left: 470px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;"><font face="Comic Sans MS" style="font-size: 60px;">Hello, my Friend!</font></div></div></div></foreignObject><text x="470" y="54" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Hello, my Friend!</text></switch></g><path d="M 165 45 L 765 45" fill="none" stroke="#666666" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 165 75 L 765 75" fill="none" stroke="#666666" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 165 105 L 765 105" fill="none" stroke="#666666" stroke-miterlimit="10" pointer-events="stroke"/><rect x="85" y="0" width="70" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe flex-start; width: 1px; height: 1px; padding-top: 15px; margin-left: 87px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: left;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">顶线(top)</div></div></div></foreignObject><text x="87" y="19" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px">顶线(top)</text></switch></g><rect x="85" y="30" width="90" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe flex-start; width: 1px; height: 1px; padding-top: 45px; margin-left: 87px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: left;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">中线(middle)</div></div></div></foreignObject><text x="87" y="49" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px">中线(middle)</text></switch></g><rect x="85" y="60" width="100" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe flex-start; width: 1px; height: 1px; padding-top: 75px; margin-left: 87px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: left;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">基线(baseline)</div></div></div></foreignObject><text x="87" y="79" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px">基线(baseline)</text></switch></g><rect x="85" y="90" width="90" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe flex-start; width: 1px; height: 1px; padding-top: 105px; margin-left: 87px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: left;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">底线(bottom)</div></div></div></foreignObject><text x="87" y="109" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px">底线(bottom)</text></switch></g><rect x="775" y="45" width="80" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe flex-start; width: 1px; height: 1px; padding-top: 60px; margin-left: 777px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: left;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">字符中心线</div></div></div></foreignObject><text x="777" y="64" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px">字符中心线</text></switch></g><path d="M 165 225 L 765 225" fill="none" stroke="#666666" stroke-miterlimit="10" pointer-events="stroke"/><rect x="225" y="215" width="490" height="90" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 260px; margin-left: 470px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;"><font face="Comic Sans MS" style="font-size: 60px;">Hello, my Friend!</font></div></div></div></foreignObject><text x="470" y="264" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Hello, my Friend!</text></switch></g><path d="M 165 255 L 765 255" fill="none" stroke="#666666" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 165 285 L 765 285" fill="none" stroke="#666666" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 165 315 L 765 315" fill="none" stroke="#666666" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 175 270 L 765 270" fill="none" stroke="#666666" stroke-miterlimit="10" stroke-dasharray="3 3" pointer-events="stroke"/><path d="M 165 270 L 175 270" fill="none" stroke="#666666" stroke-miterlimit="10" stroke-dasharray="3 3" pointer-events="stroke"/><path d="M 165 165 L 755 165" fill="none" stroke="#666666" stroke-miterlimit="10" stroke-dasharray="3 3" pointer-events="stroke"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 166px; margin-left: 470px;"><div data-drawio-colors="color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; background-color: rgb(255, 255, 255); white-space: nowrap;"><font style="font-size: 12px;">半行距分割线</font></div></div></div></foreignObject><text x="470" y="169" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="11px" text-anchor="middle">半行距分割线</text></switch></g><path d="M 162 375 L 752 375" fill="none" stroke="#666666" stroke-miterlimit="10" stroke-dasharray="3 3" pointer-events="stroke"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 376px; margin-left: 467px;"><div data-drawio-colors="color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 11px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; background-color: rgb(255, 255, 255); white-space: nowrap;"><font style="font-size: 12px;">半行距分割线</font></div></div></div></foreignObject><text x="467" y="379" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="11px" text-anchor="middle">半行距分割线</text></switch></g><rect x="45" y="165" width="20" height="220" fill="none" stroke="none" pointer-events="all"/><path d="M 65 165 L 55 165 L 55 385 L 65 385" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="all"/><path d="M 45 275 L 55 275" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="all"/><rect x="125" y="165" width="20" height="59" fill="none" stroke="none" pointer-events="all"/><path d="M 145 165 L 135 165 L 135 224 L 145 224" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="all"/><path d="M 125 194.5 L 135 194.5" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="all"/><rect x="125" y="227" width="20" height="89" fill="none" stroke="none" pointer-events="all"/><path d="M 145 227 L 135 227 L 135 316 L 145 316" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="all"/><path d="M 125 271.5 L 135 271.5" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="all"/><rect x="75" y="256.5" width="60" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 272px; margin-left: 105px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">内容区</div></div></div></foreignObject><text x="105" y="275" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">内容区</text></switch></g><rect x="75" y="179.5" width="60" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 195px; margin-left: 105px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">半行距</div></div></div></foreignObject><text x="105" y="198" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">半行距</text></switch></g><rect x="0" y="260" width="50" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 275px; margin-left: 25px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">行框</div></div></div></foreignObject><text x="25" y="279" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">行框</text></switch></g><rect x="785" y="105" width="20" height="120" fill="none" stroke="none" transform="rotate(-180,795,165)" pointer-events="all"/><path d="M 805 105 L 795 105 L 795 225 L 805 225" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" transform="rotate(-180,795,165)" pointer-events="all"/><path d="M 785 165 L 795 165" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" transform="rotate(-180,795,165)" pointer-events="all"/><path d="M 166.1 58.95 L 765 60" fill="none" stroke="#666666" stroke-miterlimit="10" stroke-dasharray="3 3" pointer-events="stroke"/><rect x="855" y="106" width="20" height="210" fill="none" stroke="none" transform="rotate(-180,865,211)" pointer-events="all"/><path d="M 875 106 L 865 106 L 865 316 L 875 316" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" transform="rotate(-180,865,211)" pointer-events="all"/><path d="M 855 211 L 865 211" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" transform="rotate(-180,865,211)" pointer-events="all"/><rect x="800" y="149.5" width="50" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 165px; margin-left: 825px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">行距</div></div></div></foreignObject><text x="825" y="168" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">行距</text></switch></g><rect x="865" y="196" width="50" height="30" fill="none" stroke="none" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility" style="overflow: visible; text-align: left;"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 1px; height: 1px; padding-top: 211px; margin-left: 890px;"><div data-drawio-colors="color: rgb(0, 0, 0); " style="box-sizing: border-box; font-size: 0px; text-align: center;"><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: nowrap;">行高</div></div></div></foreignObject><text x="890" y="215" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">行高</text></switch></g></g><switch><g requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"/><a transform="translate(0,-5)" xlink:href="https://www.drawio.com/doc/faq/svg-export-text-problems" target="_blank"><text text-anchor="middle" font-size="10px" x="50%" y="100%">Text is not SVG - cannot display</text></a></switch></svg>

