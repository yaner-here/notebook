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



























