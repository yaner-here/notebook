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

# §19 深入CSS概念

本章将深入介绍CSS中的各种概念及其细节。

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

实际开发中，我们常把`height`和`line-height`设为相同的值，同而实现文字的垂直居中。这种做法的原理是：由于`line-height`与`height`相同，所以容器内只能有一行。而我们知道字符中心线就是一行文本内垂直居中的地方。

当`line-height`的单位为`em`或`%`时，`1em`和`100%`表示一倍的`font-size`。当`line-height`为无单位常数时，表示`font-size`的倍数。

### §19.4.3 深入`vertical-align`

`vertical-align`属性作用于容器元素（且为行内元素、行内块级元素、表格单元格元素），用于定义子元素的垂直对齐方式。

在上图中，我们介绍了顶线、中线、基线、底线。恰好`vertical-align`的取值范围中提供了对应的四种关键词，用于实现垂直对齐：

| `vertical-align`属性值 | 作用       |
| ---------------------- | ---------- |
| `top`                  | 沿顶线对齐 |
| `middle`               | 沿中线对齐 |
| `baseline`             | 沿基线对齐 |
| `bottom`               | 沿底线对齐 |

当`vertical-align`取负值时，表示沿原本的基线向上偏移对齐。

## §19.5 表单

### §19.5.1 单选框/复线框文本对齐

受制于`vertical-align: baseline`的影响，单选框/多选框的按钮与文本并不对齐。我们可以为不同`font-size`的文本手动调整`vertical-align`的数值，从而实现文字居中对齐。

```html
<html>
    <head>
        <style>
            label {
                font-size: 40px;
            }
            input:nth-of-type(2) {
                vertical-align: 5px;
            }
        </style>
    </head>
    <body>
        <form action="post">
            <input type="radio" id="male" value="male" name="gender"><label for="male">Male</label>
            <input type="radio" id="female" value="female" name="gender"><label for="female">Female</label>
        </form>
    </body>
</html>
```

### §19.5.2 禁止拖动`<textarea>`

`<textarea>`的右下角有一个小三角，用户可以拖动这个小三角，以改变`<textarea>`的尺寸。我们常用以下两种方法禁止拖动`<textarea>`：

```html
<html>
    <head>
        <style>
            textarea:nth-of-type(1) {
                min-width: 200px;
                max-width: 200px;
                min-height: 100px;
                max-height: 100px;
            }
            textarea:nth-of-type(2) {
                resize: none;
            }
        </style>
    </head>
    <body>
        <textarea cols="30" rows="10"></textarea>
        <textarea cols="30" rows="10"></textarea>
    </body>
</html>
```

### §19.5.3 表单对齐

设想一个登录表单：用户需要输入用户名、密码和验证码。其中验证码的输入框右边需要有一个发送验证码的按钮。你可能会手动给其中的元素指定左右两侧外间距，但是这种方法难以维护。现在常用的方法是：将表单分为左侧一栏和右侧多栏，右侧多栏的长度之和相等。左栏由一堆`<label>`组成且右对齐，右栏由输入框和按钮组成。所有栏都是向左浮动。

```html
<!DOCTYPE html> <!-- 一定要带,确保使用标准模式,而不是怪异模式 -->
<html>
    <head>
        <style>
            form {
                width: 320px;
                font-family: Arial, Helvetica, sans-serif;
                font-size: 14px;
                font-weight: bold;
                border: 1px solid black;
            }
            form > p { overflow: hidden; } /* 清除浮动 */
            form label {
                float: left;
                width: 60px;
                height: 40px;
                line-height: 40px;
                text-align: right;
                margin-right: 10px;
            }
            form input:not(#submit){
                float: left;
                height: 16px;
                padding: 10px;
            }
            form #username, form #password { width: 210px; }
            form #verifyCode { width: 118px; margin-right: 10px; }
            form #submit { width: 82px; height: 40px; }
        </style>
    </head>
    <body>
        <form action="post">
            <p>
                <label for="username">用户名</label>
                <input type="text" id="username">
            </p>
            <p>
                <label for="password">密码</label>
                <input type="text" id="password">
            </p>
            <p>
                <label for="verifyCode">验证码</label>
                <input type="text" id="verifyCode">
                <input type="submit" id="submit">
            </p>
        </form>
    </body>
</html>
```

## §19.6 浮动布局

要让文档脱离文档流有两种方法，一种是设置`display: float`，另一种是设置`display: absolute`：

```python
<html>
    <head>
        <style>
            .container {
                width: 200px;
                border: 1px solid black;
            }
            .container > .item {
                width: 160px;
                margin: 10px;
                height: 40px;
                border: 1px solid black;
                background-color: lightblue;
                margin-left: auto;
                margin-right: auto;
            }
            .container:nth-of-type(2) > .item:nth-of-type(n+2) {
                float: left;
            }
            .container:nth-of-type(3) > .item:nth-child(3) {
                position: absolute;
                top: 150px;
            }
        </style>
    </head>
    <body>
        <div style="display: flex; gap: 1rem;">
            <div class="container">
                <span>全文档流</span>
                <div class="item"></div>
                <div class="item"></div>
                <div class="item"></div>
            </div>
            <div class="container">
                <span>脱离文档流(float: left)</span>
                <div class="item"></div>
                <div class="item"></div>
                <div class="item"></div>
            </div>
            <div class="container">
                <span>脱离文档流(position: absolute)</span>
                <div class="item"></div>
                <div class="item"></div>
                <div class="item"></div>
            </div>
        </div>
    </body>
</html>
```

### §19.6.1 浮动的影响

如果一个元素设置了浮动，那么它会脱离文档流，从而产生以下影响：

- 对自身而言，元素会被转化成块级元素，从而可以设置`width`、`height`、`margin`、`padding`等属性。
- 对父元素而言，父元素不能包裹子元素，因此可能出现“父元素高度坍塌”的现象。
- 对子元素而言，如果子元素也是浮动元素，那么本元素就不会出现“高度坍塌”的现象。

### §19.6.2 清除浮动

“清除浮动”指的是清除浮动元素脱离文档流之后的影响。例如我们不想让浮动后面的非浮动元素环绕在浮动元素的周围，而是希望它们回归到文档流中，就可以通过清除浮动来实现。

常用的清除浮动方法有以下三种：

- `clear: both`

  `clear`是一个专门用于清除浮动的CSS属性，有三种取值：`left`、`right`、`both`，分别表示清除哪一侧的浮动。**该元素应用于浮动元素后面的非浮动元素。**

  这种方法的缺点是会增加多余的标签，同时破坏了HTML文档的语义。

- `overflow: hidden`

  `overflow: hidden`也可用于清除浮动，但是**作用的对象是浮动元素的父元素**。

  这种方法的缺点是额外承担了`overflow: hidden`的初衷——内容不能外溢。这会导致“清除浮动”与“允许溢出/滚动条”不可兼得。

- `::after`

  给**浮动元素的父元素**的`::after`伪元素同时设置三个CSS属性：`clear: both`、`content: ""`和`display: block`。

  这是实际开发中最好的解决方法。

```html
<html>
    <head>
        <style>
            .container {
                width: 400px;
                text-align: center;
                border: 3px solid black;
                margin-bottom: 5rem;
                background-color: lightcoral;
            }
            .container > .item {
                height: 50px;
                width: 80px;
                background-color: lightblue;
            }
            .container > .item:nth-of-type(1) { float: left; }
            .container > .item:nth-of-type(2) { float: right; }

            .container:nth-of-type(4)::after {
                clear: both;
                content: "";
                display: block;
            } 
        </style>
    </head>
    <body>
        <div class="container">
            父元素高度坍塌
            <div class="item"></div>
            <div class="item"></div>
        </div>
        <div class="container">
            clear: both;
            <div class="item"></div>
            <div class="item"></div>
            <div style="clear: both;"></div> <!-- 一个尺寸为0的元素 -->
        </div>
        <div class="container" style="overflow: hidden;">
            overflow: hidden;
            <div class="item"></div>
            <div class="item"></div>
        </div>
        <div class="container">
            ::after{clear&content&display}
            <div class="item"></div>
            <div class="item"></div>
        </div>
    </body>
</html>
```

## §19.7 定位布局

浮动和定位是CSS的两大布局方式。浮动布局比较灵活，但不容易控制，有时我们更愿意选择定位布局，牺牲灵活性换取精确定位。CSS支持的定位布局有四种，分别是固定定位(`fixed`)、相对定位(`relative`)、绝对定位(`absolute`)、静态定位(`static`)。

定位布局有以下通用规则：

- 默认情况下，固定定位和绝对定位都是相对于`<body>`，而相对定位是相对于原始位置。
- 除静态定位以外，只有在定义`position`属性后，`top`/`bottom`/`left`/`right`属性才能生效。
- 绝对定位会将元素强制转换为块级元素，这一行为与浮动布局是一致的。

要实现子元素相对父元素定位，我们首先需要给父元素定义`position: relative`(相对定位)，然后给子元素定义`position: absolute`(绝对定位)。

```html
<html>
    <head>
        <style>
            .container {
                position: relative;
                width: 300px;
                height: 150px;
                background-color: lightblue;
            }
            .container > .item {
                position: absolute;
                width: 150px;
                height: 80px;
                background-color: lightcoral;

                left: calc(300px / 2 - 150px / 2);
                bottom: -80px;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <div class="item"></div>
        </div>
    </body>
</html>
```

## §19.8 CSS图形

在SVG/Canvas还没流行的年代，矢量图形一直是CSS的一大难题。由于位图占用大量空间，所以开发者尝试给元素添加各种CSS属性，把元素捏成目标形状。本章将介绍这一“传统手艺”，虽然在SVG/Canvas流行的今天，这一手艺已经失去了使用价值，但是我们不妨再见证一下前辈开发者的智慧。

### §19.8.1 三角形

当一个盒模型的两条相邻边走某个角落相交时，CSS会在交界处沿某个角度绘制一条接合线：

```html
<html>
    <head>
        <style>
            div {
                width: 200px;
                height: 100px;
                border: 20px solid;
                border-top-color: darkgoldenrod;
                border-right-color: lightpink;
                border-bottom-color: chartreuse;
                border-left-color: darkblue;
            }
        </style>
    </head>
    <body>
        <div></div>
    </body>
</html>
```

接着，我们让这个`<div>`的尺寸缩小到0，于是四条边框挤在一起，形成一个正方形，最后把左、右、下三条边框的颜色设置成透明，一个三角形就做好了。或者把两个小三角形拼成一个大三角形：

```html
<html>
    <head>
        <style>
            div {
                width: 0;
                height: 0;
                border: 20px solid;
            }
            div:nth-of-type(1) { border-color: lightcoral transparent transparent transparent; }
            div:nth-of-type(2) { border-color: lightcoral lightcoral transparent transparent; }
        </style>
    </head>
    <body>
        <div></div>
        <div></div>
    </body>
</html>
```

开发成通常将这些三角形通过相对定位固定到元素的某个位置，通过拼接创造出更复杂的形状：

```html
<html>
    <head>
        <style>
            body { padding: 1rem; }
            div.sign {
                position: relative;
                width: 400px;
                height: 100px;
                background-color: lightblue;
                padding: 1rem;
                box-sizing: border-box;
                border: 1px solid;
            }
            div.sign::before { /* 创建蓝色三角形的外层黑边框 */
                width: 0;
                height: 0;
                display: block;
                content: "";
                border: 20px solid;
                border-color: transparent transparent black transparent;
                position: absolute;
                top: -41px;
                left: calc((400px - 20px * 2) / 2);
                z-index: -1;
            }
            div.sign::after { /* 创建蓝色三角形 */
                width: 0;
                height: 0;
                display: block;
                content: "";
                border: 20px solid;
                border-color: transparent transparent lightblue transparent;
                position: absolute;
                top: -40px;
                left: calc((400px - 20px * 2) / 2);
            }
        </style>
    </head>
    <body>
        <div class="sign">
            这是告示牌。
        </div>
    </body>
</html>
```

### §19.8.2 圆与椭圆

`border-radius`及其四个角的子属性可以控制圆角半径。配合边框使用可以弯曲边框。

```html
<html>
    <head>
        <style>
            body { padding: 1rem; }
            .box {
                height: 100px;
                width: 100px;
                background-color: rgba(173, 216, 230, 0.3);
                text-align: center;
                font-weight: bolder;
                font-size: 80;
                line-height: 100px;
                
                border-radius: 40px;
                border: 10px solid;
                border-color: transparent black transparent black;
            }
        </style>
    </head>
    <body>
        <div class="box">1</div>
    </body>
</html>
```

### §19.8.3 梯形

在[§19.8.1 三角形](###§19.8.1 三角形)的基础上，我们给元素添加高度或宽度，就能调整上底的长度，从而让三角形变成梯形。

```html
<html>
    <head>
        <style>
            body { padding: 1rem; }
            .box {
                box-sizing: border-box;
                border: 50px solid black;
                border-color: transparent transparent black transparent;
                
                width: 150px;
            }
        </style>
    </head>
    <body>
        <div class="box"></div>
    </body>
</html>
```

### §19.8.4 书签图标

书签的形状相等于一个竖条长方形在底部砍去了一个三角形。使用边框能轻松作出该效果。

```html
<html>
    <head>
        <style>
            body { padding: 1rem; }
            .box {
                border: 10px solid black;
                border-color: black black transparent black;
                width: 0;
                height: 15px;
            }
        </style>
    </head>
    <body>
        <div class="box"></div>
    </body>
</html>
```

### §19.8.5 下载图标

下载图标就是一个向下的箭头。我们使用边框制作三角形，再用`border-shadow`缩小阴影尺寸来制作箭头的正方形箭柄：

```html
<html>
    <head>
        <style>
            body { padding: 1rem; }
            .box {
                border: 16px solid black;
                border-color: black transparent transparent transparent;
                width: 0;
                box-shadow: 0 -24px 0 -8px;
            }
        </style>
    </head>
    <body>
        <div class="box"></div>
    </body>
</html>
```

### §19.8.6 单选图标

`box-shadow`属性能根据边框形状创建对应的阴影。

```html
<html>
    <head>
        <style>
            body {
                padding: 1rem;
            }
            .box {
                width: 50px;
                height: 50px;
                background-color: black;
                border: 1px solid black;
                border-radius: 50px;
                
                box-shadow: 0 0 0 5px white, 0 0 0 10px black;
            }
        </style>
    </head>
    <body>
        <div class="box"></div>
    </body>
</html>
```

### §19.8.7 应用列表图标

“田字型”图表由九个排布均匀的点组成。这里我们使用`outline`创建周围8个点，用`border`创建中间的点：

```html
<html>
    <head>
        <style>
            body {
                padding: 1rem;
            }
            .box {
                width: 0px;
                border: 3px solid black;
                outline: 6px dotted;
                outline-offset: 6px;
            }
        </style>
    </head>
    <body>
        <div class="box"></div>
    </body>
</html>
```

## §19.9 层叠上下文

层叠上下文（Stacking Context）与CSS中的Z轴概念相关。根元素或`z-index`不为`auto`的元素都会创建一个自己的层叠上下文。

在一个层叠上下文中，层叠级别（Stacking Level）决定了图层的显示顺序，如下所示：
$$
\begin{align}
	& 边框和背景 < 负\text{z-index} < 块盒子 < 浮动盒子 < \\
	& 行内盒子 < 零\text{z-index} < 正\text{z-index} \\
\end{align}
$$

## §19.10 BFC

块级格式上下文（BFC，Block Formatting Context）是一个独立的渲染区域，规定了内部的块级元素如何布局，且不受外部影响。

如果一个元素具备以下任意一个条件，则CSS会为该元素创建一个新的BFC：

- 根元素
- `float: left`/`float: right`
- `position: absolute`/`position: fixed`
- `overflow: auto`/`overflow: hidden`/`overflow: scroll`
- `display: inline-block`/`display: table-caption`/`display: table-cell`
- `display: flex`/`display: inline-flex`（CSS3特供）

在一个BFC中，盒子从顶端开始一个个的垂直排列，盒子之间的外边距会叠加。

### §19.10.1 避免外边距叠加

既然同在一个BFC内的两个元素才会产生外边距叠加，我们自然想到可以把两个元素放在两个BFC中，就能避免这一问题。

```html
<html>
    <head>
        <style>
            .container {
                width: 20rem;
                height: 10rem;
                background-color: lightblue;
            }
            .bfc {
                overflow: hidden; /* 创建BFC */
            }
            .item {
                width: 5rem;
                height: 3rem;
                background-color: lightcoral;
                border: 1px solid black;
            }
            .bfc:nth-of-type(1) > .item { margin-bottom: 1rem; }
            .bfc:nth-of-type(2) > .item { margin-top: 1rem; }
        </style>
    </head>
    <body>
        <div class="container">
            <div class="bfc">
                <div class="item"></div>
            </div>
            <div class="bfc">
                <div class="item"></div>
            </div>
        </div>
    </body>
</html>
```

### §19.10.2 清除浮动

计算一个BFC的高度时，内部的浮动元素也要考虑计算。因此，为防止父元素高度坍塌的现象，我们可以让父元素成为BFC。

### §19.10.3 避免文字环绕

一个元素浮动之后，其层叠级别比普通文档流的层流级别高。在BFC内部，如果存在新的新的BFC子元素和新的浮动元素，则新BFC与浮动元素不会重叠。

```html
<html>
    <head>
        <style>
            .container {
                width: 20rem;
                height: 5rem;
                background-color: lightblue;
                border: 1px solid black;
            }
            .item {
                width: 5rem;
                height: 1rem;
                background-color: lightcoral;
                border: 1px solid black;

                float: left;
            }
            .bfc {
                overflow: hidden;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <div class="item" style="display: inline-block;"></div>
            
            <div>
                这是一段文本。这是一段文本。这是一段文本。这是一段文本。
            </div>
        </div>
        <div class="container">
            <div class="item" style="display: inline-block;"></div>
            
            <div class="bfc">
                这是一段文本。这是一段文本。这是一段文本。这是一段文本。
            </div>
        </div>
    </body>
</html>
```

### §19.10.4 自适应列布局

之前我们在[§19.2.3 负外边距](###§19.2.3 负外边距)一节中讲过使用负外边距实现自适应列布局。本节将介绍使用BFC实现。核心原理是将固定宽度的一列设置成浮动元素，然后另一列宽度可变的栏设置成BFC。

```html
<html>
    <head>
        <style>
            .sidebar {
                width: 15rem;
                height: 100%;
                background-color: lightblue;

                float: left;
            }
            .main {
                width: auto;
                height: 100%;
                background-color: lightcoral;

                overflow: hidden;
            }
        </style>
    </head>
    <body>
        <div class="sidebar"> 长度不变</div>
        <div class="main">长度可变,自适应</div>
    </body>
</html>
```

# §20 性能调优

## §20.1 属性简写

属性简写指的是，在实现相同效果的前提下，使用字符更少的CSS属性或属性值。

- 子属性合并为总属性

  子属性不仅字符数量多，占用存储空间，而且条目数量也多，拖慢解析效率。所以能使用总属性，就不要使用子属性。

  | 总属性(部分) | 对应子属性                                                   |
  | ------------ | ------------------------------------------------------------ |
  | `border`     | `border-top-color`、`border-top-width`、`border-top-style`、<br/>`border-right-color`、`border-right-width`、`border-right-style`、<br>`border-bottom-color`、`border-bottom-width`、`border-bottom-style`、<br/>`border-left-color`、`border-left-width`、`border-left-style` |
  | `padding`    | `padding-top`、`padding-right`、`padding-bottom`、`padding-left` |
  | `margin`     | `margin-top`、`margin-right`、`margin-bottom`、`margin-left` |
  | `background` | `background-color`、`background-image`、`background-repeat`、`background-attachment`、`background-position` |
  | `font`       | `font-family`、`font-size`、`font-weight`、`line-height`     |

- 属性值缩写

  例如颜色，`#ffffff`可以简写成`#fff`。

## §20.2 语法压缩

### §20.2.1 空白符

在CSS中，只有属性值之间才必须使用分隔符（例如空格、正斜杠），其余地方的空白符完全可以忽略，从而节省CSS文件空间。

```css
/* 原始版本，例如阅读 */
.box {
	padding: 0px;
    border: 0.5px solid black;
    background: url("https://www.baidu.com/favicon.ico")
}

/* 压缩版本，利于储存和传输 */
.box{padding:0px;border:0.5px solid black;background:url("https://www.baidu.com/favicon.ico");}
```

### §20.2.2 结尾分号

CSS的每一个选择器的样式都是用大括号括起来的。实际上，最后一个属性后面可以不用以分号结尾，从而剩下一个分号的空间。

```css
/* 进一步压缩结尾分号 */
.box{padding:0px;border:0.5px solid black;background:url("https://www.baidu.com/favicon.ico")}
```

### §20.2.3 `url()`引号

我们知道，`url()`作为属性值用于索引目标资源文件。然而索引的路径可以不用添加引号。

```css
/* 删除url()内的引号 */
.box{padding:0px;border:0.5px solid black;background:url(https://www.baidu.com/favicon.ico)}
```

### §20.2.4 `0`/`0.x`属性值

一方面，对于`0`而言，我们不必写出它的单位。另一方面，对于`0.x`的小数，我们可以忽略前导`0`，直接以小数点开头。

```css
/* 优化0/0.x的属性值 */
.box{padding:0;border:.5px solid black;background:url(https://www.baidu.com/favicon.ico)}
```

### §20.2.5 提取相同定义

回想各类压缩算法，如果一段子串重复多次出现，我们可以将其提取出来，用一段编号代替它。这其实就是众多CSS第三方库的思路——将常用的一组CSS属性提取出来，从而节省空间。

为了展示原理，这里我们来手动提取相同的义。

```CSS
/* 原始CSS */
h1 { text-indent: 0rem; color: red; border-left: 3px solid black; }
h2 { text-indent: 1rem; color: red; border-left: 3px solid black; }

/* 提取后的CSS */
h1 { text-indent: 0rem; }
h2 { text-indent: 1rem; }
h1, h2 { color: red; border-left: 3px solid black; }
```

实际上，我们还可以利用CSS的继承特点，将可以继承的CSS属性直接定义到父元素上，这样就不用给子元素单独定义了。

## §20.3 高性能选择器

选择器的匹配过程可能与直觉相悖——CSS会从最右侧的选择器开始，依次向左匹配筛选。

CSS有各类选择器，当它们单独使用时，效率从高到低的排序分别为：
$$
\begin{align}
	& \text{id选择器 > class选择器 > 元素选择器 > 相邻选择器 >} \\
	& 子选择器 > 后代选择器 > 通配符选择器 > 属性选择器 > 伪类选择器
\end{align}
$$
基于此，我们可以总结出以下四个选择器性能调优建议：

1. 不要使用通配符：通配符的工作量非常大。
2. id选择器和class选择器不需要元素名：id能保证唯一，所以不需要元素名；class设计的初衷就是通配，限定元素名会破坏这一初衷。
3. 选择器不要超过三层：选择器的耗时会串联叠加，因此选择器不适宜嵌套多层。
4. 右侧选择器的选择条件应尽可能严苛：CSS会从最右侧的选择器开始，因此从一开始就筛去大部分元素，有利于左侧选择器减少运行时间。
5. 禁用后代选择器，少用子代选择器，多用id选择器和class选择器。

# §21 开发技巧

在CSS的开发流程中，开发人员针对频繁出现的设计需求，总结出了若干优秀的工程实践方法。本节将介绍这些开发技巧。

## §21.1 水平居中

### §21.1.1 文字水平居中

使用`text-align: center`，即可控制文字对齐的行为。

```html
<html>
    <head>
        <style>
            .box {
                border: 1px solid black;
                width: 20rem;
                text-align: center;
            }
            .box > div {
                width: min-content;
            }
        </style>
    </head>
    <body>
        <div class="box">
            <span>Hello</span>
        </div>
    </body>
</html>
```

### §21.1.2 块级元素水平居中

如果在一行之内，只有需要居中的元素，没有其它对齐方向元素的干扰，那么我们就可以考虑使用`margin-left: 0; margin-right: 0`。

```html
<html>
    <head>
        <style>
            .box {
                border: 1px solid black;
                width: 20rem;
            }
            .box > .item {
                border: 1px solid black;
                width: 5rem;
                margin-left: auto;
                margin-right: auto;
            }
        </style>
    </head>
    <body>
        <div class="box">
            <div class="item">Hello</div>
        </div>
    </body>
</html>
```

### §21.1.3 行内元素/复合行内元素水平居中

行内元素（`inline`）、复合行内元素（`inline-block`、`inline-table`、`inline-flex`）对齐的方式依然是`text-align: center`。

## §21.2 垂直居中

### §21.2.1 单行文本垂直居中

要让单行文本垂直居中，只需让`line-height`和`height`的属性值相等即可。

### §21.2.2 多行文本垂直居中

要让多行文本垂直居中，这种方法并不好想。然而程序员的智慧是无穷的——实现方法的关键是把多行文本包含在一个`<span>`标签内，然后定义`<span>`为`display: inline-block`，最后定义父元素为`display: table-cell`、`vertical-align: middle`。

```html
<html>
    <head>
        <style>
            .box {
                border: 1px solid black;
                width: 20rem;
                height: 8rem;

                display: table-cell;
                vertical-align: middle;
            }
            .box > .item {
                display: inline-block;
            }
        </style>
    </head>
    <body>
        <div class="box">
            <span class="item">
                这是两行<br>
                多行文本
            </span>
        </div>
    </body>
</html>
```

### §21.2.3 任意元素垂直居中

无论元素是块级元素还是行内元素，如果父元素和子元素的尺寸均已知，我们就可以使用`position: absolute`、`top: 50%`、`left: 50%`来精确调整子元素左上角相对父元素的位置，然后使用`margin-left`和`margin-right`来让子元素中心点移动到原先左上角所在的位置。

```html
<html>
    <head>
        <style>
            .box {
                border: 1px solid black;
                width: 20rem;
                height: 8rem;

                position: relative;
            }
            .box > .item {
                border: 1px solid black;
                width: 7rem;
                height: 3rem;
                
                position: absolute;
                top: 50%;
                left: 50%;
                margin-left: calc(-7rem / 2);
                margin-top: calc(-3rem / 2);
            }
        </style>
    </head>
    <body>
        <div class="box">
            <div class="item"></div>
        </div>
    </body>
</html>
```

### §21.2.4 行内元素垂直居中

如果元素是行内元素，除了[§21.2.3 任意元素垂直居中](###§21.2.3 任意元素垂直居中)介绍的方法，我们还可以使用[§21.2.2 多行文本垂直居中](###§21.2.2 多行文本垂直居中)介绍的方法——给父元素声明为`display: table-cell`和`vertical-align: middle`，给子元素声明为`display: inline-block`。

```html
<html>
    <head>
        <style>
            .box {
                border: 1px solid black;
                width: 20rem;
                height: 8rem;

                display: table-cell;
                vertical-align: middle;
            }
            .box > .item {
                border: 1px solid black;
                /* display: inline-block; */ /* <img>就是inline-block，不必重复声明 */
            }
        </style>
    </head>
    <body>
        <div class="box">
            <img class="item" src="https://www.baidu.com/favicon.ico">
        </div>
    </body>
</html>
```

## §21.3 CSS Sprite

我们直到，每个图片都对应一次HTTP请求。如果页面中有很多图标图像，那么会对服务器产生可观的请求数量。一个好的解决方法是让后端一次性返回一张包含所有贴图的大图片，然后由前端裁剪得到所需的小图标。这种技术称为CSS Sprite（CSS精灵/CSS雪碧图）。

开发着可以使用`background-iamge`加载精灵图，然后用`background-position`截取需要的部分。

```html
<html>
    <head>
        <style>
            .box {
                border: 1px solid black;
                width: fit-content;

            }
            .box > img.item { 
                border: 1px solid black; 
                background-image: url("http://www.spritecow.com/assets/9/tutorial-sprite.png");
                background-repeat: no-repeat;
                width: 33px;
                height: 33px;
            }

            .box > img.item:nth-of-type(1) { background-position: -433px -51px; }
            .box > img.item:nth-of-type(2) { background-position: -476px -51px; }
            .box > img.item:nth-of-type(3) { background-position: -516px -51px; }
            .box > img.item:nth-of-type(4) { background-position: -560px -49px; }
        </style>
    </head>
    <body>
        <div class="box">
            <img class="item">
            <img class="item">
            <img class="item">
            <img class="item">
        </div>
    </body>
</html>
```

关于CSS Sprite，以下有两款工具：

- CSS Sprite Generator
- [Sprite Cow](http://www.spritecow.com/)

## §21.4 字体图标

字体图标是指将图标做成字体的样式。这种方式的优点在于：一是字体本身就是矢量图，可以通过更改字号的方式随意调整大小；二是字体与CSS精灵图一样都是单文件，只需单次HTTP请求即可获取所有图标；三是可有选择性地获取字体图标的子集，从而节省存储空间。

著名的字体图标提供商有[IcoMoon](https://icomoon.io/app/#/select)和[IconFont](https://www.iconfont.cn/)。这里我们以IconFont为例，介绍字体图标的使用方法：

1. 在IconFont官网选择一组需要的图标，添加到购物车，点击“下载代码”按钮，得到一个`download.zip`压缩文件。

2. 将该压缩文件解压，得到以下文件：

   ```shell
   $ tree
   .
   ├── demo.css
   ├── demo_index.html
   ├── iconfont.css
   ├── iconfont.js
   ├── iconfont.json
   └── iconfont.ttf
   ```

3. 按照`demo_index.html`的指示，创建以下HTML文档，即可查看效果：

   ```html
   <html>
       <head>
           <style>
               @font-face {
                   font-family: 'iconfont';
                   src: url('../font_qu9du1jhqwf/iconfont.ttf') format('truetype');
               }
               .iconfont {
                   font-family: "iconfont" !important;
                   font-size: 16px;
                   font-style: normal;
                   -webkit-font-smoothing: antialiased;
                   -moz-osx-font-smoothing: grayscale;
   
                   font-size: 48px;
               }
           </style>
       </head>
       <body>
           <div class="iconfont">&#xe651;</div>
           <div class="iconfont">&#xe882;</div>
           <div class="iconfont">&#xe66c;</div>
       </body>
   </html>
   ```
