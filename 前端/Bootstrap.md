# Bootstrap

参考资料：

- 《Bootstrap 5.x 从入门到项目实战》 [豆瓣](https://book.douban.com/subject/36489295/)

本笔记内容基于Bootstrap 5.3.2。

# §1 布局

## §1.1 布局容器

Bootstrap提供了两种容器元素，分别是`.container`和`.container-fluid`。

| 布局容器           | 作用                       | 宽度变化 |
| ------------------ | -------------------------- | -------- |
| `.container`       | 固定宽度，支持响应式布局   | 离散     |
| `.container-fluid` | 占据视口(viewport)全部宽度 | 连续     |

观察源代码，我们可以发现Bootstrap使用了媒体查询来动态改变布局容器的宽度：

```css
.container {
  padding-right: 15px;
  padding-left: 15px;
  margin-right: auto;
  margin-left: auto;
}
@media (min-width: 768px) {
  .container {
    width: 750px;
  }
}
@media (min-width: 992px) {
  .container {
    width: 970px;
  }
}
@media (min-width: 1200px) {
  .container {
    width: 1170px;
  }
}
.container-fluid {
  padding-right: 15px;
  padding-left: 15px;
  margin-right: auto;
  margin-left: auto;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
        <style>
            div {
                background-color: lightblue;
            }
        </style>
    </head>
    <body>
        <div class="container">Hello</div>
        <div class="container-fluid">World</div>
    </body>
</html>
```

`.container`也针对不同尺寸的设备屏幕，设计了多动变体，用于指定不同的宽度：

| `class`名称      |  超小屏幕设备(`<576px`)   | 小型屏幕设备(`[576px,768px)`)    | 中型屏幕设备(`[768px,992px)`) | 大型屏幕设备(`[992px,1200px)`) | 特大屏幕设备(`[1200px,1400px)`) | 超大屏幕设备(`>=1400px`) |
| ---------------- | --- | --- | --- | --- | --- | --- |
| `.container-sm`  | `100%` | `540px` | `720px` | `960px` | `1140px` | `1320px` |
| `.container-md`  | `100%` | `100%` | `720px` | `960px` | `1140px` | `1320px` |
| `.container-lg`  | `100%` | `100%` | `100%` | `960px` | `1140px` | `1320px` |
| `.container-xl`  | `100%` | `100%` | `100%` | `100%` | `1140px` | `1320px` |
| `.container-xll` | `100%` | `100%` | `100%` | `100%` | `100%` | `1320px` |

## §1.2 栅格布局

Bootstrap使用自定义的`.row-*`和`-.col-*`来封装原生CSS的Flex布局，形成Bootstrap自己的栅格布局。

### §1.2.1 `.row`/`.col`

默认的`.row`和`.col`负责启用Bootstrap的栅格布局与指定默认宽度，此时还没有Flex的12个格子这一说法：

```css
.row {
  --bs-gutter-x: 1.5rem;
  --bs-gutter-y: 0;
  display: flex;
  flex-wrap: wrap;
  margin-top: calc(-1 * var(--bs-gutter-y));
  margin-right: calc(-0.5 * var(--bs-gutter-x));
  margin-left: calc(-0.5 * var(--bs-gutter-x));
}
.row > * {
  flex-shrink: 0;
  width: 100%;
  max-width: 100%;
  padding-right: calc(var(--bs-gutter-x) * 0.5);
  padding-left: calc(var(--bs-gutter-x) * 0.5);
  margin-top: var(--bs-gutter-y);
}

.col {
  flex: 1 0 0%;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            [2,3,4,5,6,7,8,9,10,11,12,13,14].forEach(i => {
                htmlString = "<div class='row'>";
                htmlString += `<div class="col border bg-light">1/${i}</div>`.repeat(i)
                htmlString += "</div>";
                document.write(htmlString);
            })
        </script>
    </body>
</html>
```

`.col-1`、`.col-2`、...、`.col-12`将Bootstrap的栅格布局假想分割为12等份，然后占据其中的几等份。从这里开始出现“12份”的说法，当一行的元素份数之和超过12份时会被换行：

```css
.col-1 {
  flex: 0 0 auto;
  width: 8.33333333%;
}
.col-2 {
  flex: 0 0 auto;
  width: 16.66666667%;
}
/* ... */
.col-12 {
  flex: 0 0 auto;
  width: 100%;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="row bg-light border">
            <div class="col-3 border">123</div>
            <div class="col-6 border">123</div>
            <div class="col-3 border">123</div>
            <div class="col-5 border">123</div>
            <div class="col-5 border">123</div>
        </div>
    </body>
</html>
```

`.col-{BREAK_POINT}-*`使用媒体查询，针对不同宽度的页面单独指定样式：

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div id="width"></div>
        <script>
            const widthElement = document.getElementById('width');
            window.onresize = function(event){
                let sizeType = "当前尺寸类型: ";
                switch (true) {
                    case innerWidth < 576:
                        sizeType = "xs";
                        break;
                    case innerWidth >= 576 && innerWidth < 768:
                        sizeType = "sm";
                        break;
                    case innerWidth >= 768 && innerWidth < 992:
                        sizeType = "md";
                        break;
                    case innerWidth >= 992 && innerWidth < 1200:
                        sizeType = "lg";
                        break;
                    case innerWidth >= 1200 && innerWidth < 1400:
                        sizeType = "xl";
                        break;
                    case innerWidth >= 1400:
                        sizeType = "xxl";
                    default:
                        break;
                }
                widthElement.innerHTML = `页面宽度: ${window.innerWidth}px, 尺寸类型: ${sizeType}`;
            };
        </script>
        <div class="row bg-light border">
            <div class="col-12 col-sm-6 col-md-3 col-lg-2 bg-light border">首页</div>
            <div class="col-12 col-sm-6 col-md-3 col-lg-2 bg-light border">业务领域</div>
            <div class="col-12 col-sm-6 col-md-3 col-lg-2 bg-light border">产品介绍</div>
            <div class="col-12 col-sm-6 col-md-3 col-lg-2 bg-light border">党建工作</div>
            <div class="col-12 col-sm-6 col-md-3 col-lg-2 bg-light border">荣誉奖项</div>
            <div class="col-12 col-sm-6 col-md-3 col-lg-2 bg-light border">社会公益</div>
            <div class="col-12 col-sm-6 col-md-3 col-lg-2 bg-light border">信息公开</div>
            <div class="col-12 col-sm-6 col-md-3 col-lg-2 bg-light border">关于我们</div>
        </div>
    </body>
</html>
```

如果我们要换行，其实不用非要让上一层的各元素宽度之和达到12份。Bootstrap提供了`.w-100`让一行没有高度的元素单独占一列，于是后面的元素自然换到了下一行：

```css
.w-100 {
  width: 100% !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="row">
            <div class="col border bg-light">栏目</div>
            <div class="col border bg-light">栏目</div>
            <div class="w-100"></div>
            <div class="col border bg-light">栏目</div>
            <div class="col border bg-light">栏目</div>
        </div>
    </body>
</html>
```

由于原生CSS的Flex布局原生支持嵌套，因此Bootstrap中的这两个属性也可以嵌套：

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="row bg-light border">
                <div class="border">嵌套列演示</div>
                <div class="col-8 border">
                    <div>左侧列</div>
                    <div class="row border">
                        <div class="col-6 border">嵌套列</div>
                        <div class="col-6 border">嵌套列</div>
                    </div>
                </div>
                <div class="col-4 border">右侧列</div>
        </div>
    </body>
</html>
```

### §1.2.2 `.order`

`.order-first`、`.order-last`、`.order-<数字>`通过改变原生CSS中的`order`属性值，来调整Bootstrap栅格布局中的元素顺序：

```css
.order-first {
  order: -1 !important;
}
.order-0 {
  order: 0 !important;
}
.order-1 {
  order: 1 !important;
}
.order-2 {
  order: 2 !important;
}
.order-3 {
  order: 3 !important;
}
.order-4 {
  order: 4 !important;
}
.order-5 {
  order: 5 !important;
}
.order-last {
  order: 6 !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="row bg-light border">
            <div class="col border order-last">1+.order-last</div>
            <div class="col border">2</div>
            <div class="col border order-first">3+.order-first</div>
        </div>
    </body>
</html>
```

### §1.2.3 `.offset`

`.offset-<数字>`通过调整原生CSS的`margin-left`属性值，使得目标元素向右移动的“份”数。

```css
.offset-1 {
  margin-left: 8.33333333%;
}
.offset-2 {
  margin-left: 16.66666667%;
}
.offset-3 {
  margin-left: 25%;
}
.offset-4 {
  margin-left: 33.33333333%;
}
.offset-5 {
  margin-left: 41.66666667%;
}
.offset-6 {
  margin-left: 50%;
}
.offset-7 {
  margin-left: 58.33333333%;
}
.offset-8 {
  margin-left: 66.66666667%;
}
.offset-9 {
  margin-left: 75%;
}
.offset-10 {
  margin-left: 83.33333333%;
}
.offset-11 {
  margin-left: 91.66666667%;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="row bg-light border">
            <div class="col-6 offset-3 bg-warning">col-6 + offset-3</div>
        </div>
</html>
```

同样的，`.offset`也提供了对应的响应式属性`.offset-<BREAK_POINT>-<数字>`：

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="row bg-light border">
            <div class="col-md-6 offset-md-3 bg-warning">col-md-6 + offset-md-3</div>
        </div>
        <div class="row bg-light border">
            <div class="col-md-4 offset-md-1 bg-warning">col-md-6 + offset-md-3</div>
            <div class="col-md-4 offset-md-2 bg-warning">col-md-6 + offset-md-3</div>
        </div>
        <div class="row bg-light border">
            <div class="col-md-4 bg-warning">col-md-6 + offset-md-3</div>
            <div class="col-md-4 offset-md-4 bg-warning">col-md-6 + offset-md-3</div>
        </div>
    </body>
</html>
```

## §1.3 弹性布局

Bootstrap使用自定义的`.d-flex`和`.d-inline-flex`来封装原生CSS的Flex布局，形成Bootstrap自己的弹性布局。

### §1.3.1 `.d-flex`/`.d-inline-flex`

`.d-flex`用于创建弹性布局，`.d-inline-flex`用于创建行内弹性布局。

```css
.d-flex {
  display: flex !important;
}
.d-inline-flex {
  display: inline-flex !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="d-flex p-2 border bg-success">
            <span>.d-flex</span>
            <div class="bg-light border p-2 m-1">测试按钮</div>
            <div class="bg-light border p-2 m-1">测试按钮</div>
            <div class="bg-light border p-2 m-1">测试按钮</div>
        </div>
        <div class="d-inline-flex p-2 border bg-success">
            <span>.d-inline-flex</span>
            <div class="bg-light border p-2 m-1">测试按钮</div>
            <div class="bg-light border p-2 m-1">测试按钮</div>
            <div class="bg-light border p-2 m-1">测试按钮</div>
        </div>
    </body>
</html>
```

同样地，Bootstrap也提供了相应的响应式属性`.d-<BREAK_POINT>-flex`和`.d-<BREAK_POINT>-inline-flex`。

### §1.3.2 `.flex-row`/`.flex-column`

Bootstrap通过设置原生CSS中的`flex-direction`属性值，为弹性布局提供了一系列决定排列方向的属性。

```css
.flex-row {
  flex-direction: row !important;
}
.flex-column {
  flex-direction: column !important;
}
.flex-row-reverse {
  flex-direction: row-reverse !important;
}
.flex-column-reverse {
  flex-direction: column-reverse !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["flex-row", "flex-row-reverse", "flex-column-reverse", "flex-column"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <div class="d-flex ${className} p-2 m-3 border bg-success">
                        <span>.${className}</span>
                        <div class="bg-light border p-2 m-1">测试按钮1</div>
                        <div class="bg-light border p-2 m-1">测试按钮2</div>
                        <div class="bg-light border p-2 m-1">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

同样地，Bootstrap也提供了相应的响应式属性`.flex-<BREAK_POINT>-row`和`.flex-<BREAK_POINT>-column`。

### §1.3.3 `.justify-content-*`

Bootstrap通过更改原生CSS中的`justify-contnet`属性值，封装了一系列控制弹性布局元素排列的属性。

```css
.justify-content-start {
  justify-content: flex-start !important;
}
.justify-content-end {
  justify-content: flex-end !important;
}
.justify-content-center {
  justify-content: center !important;
}
.justify-content-between {
  justify-content: space-between !important;
}
.justify-content-around {
  justify-content: space-around !important;
}
.justify-content-evenly {
  justify-content: space-evenly !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["justify-content-start", "justify-content-end", "justify-content-center", "justify-content-between", "justify-content-around", "justify-content-evenly"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <span class="w-100">.${className}</span>
                    <div class="d-flex flex-row ${className} p-2 m-3 border bg-success">
                        <div class="bg-light border p-2 m-1">测试按钮1</div>
                        <div class="bg-light border p-2 m-1">测试按钮2</div>
                        <div class="bg-light border p-2 m-1">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

同样地，Bootstrap也提供了相应的响应式属性`.justify-content-<BREAK_POINT>-*`。

### §1.3.4 `.align-items-*`

Bootstrap通过更改原生CSS中的`align-items`属性值，封装了一系列控制弹性布局元素垂直对齐的属性。

```css
.align-items-start {
  align-items: flex-start !important;
}
.align-items-end {
  align-items: flex-end !important;
}
.align-items-center {
  align-items: center !important;
}
.align-items-baseline {
  align-items: baseline !important;
}
.align-items-stretch {
  align-items: stretch !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["align-items-start", "align-items-end", "align-items-center", "align-items-baseline", "align-items-stretch"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <span class="w-100">.${className}</span>
                    <div class="d-flex flex-row ${className} p-1 m-3 border bg-success" style="height:100px;">
                        <div class="bg-light border p-2 m-1">测试按钮1</div>
                        <div class="bg-light border p-2 m-1">测试按钮2</div>
                        <div class="bg-light border p-2 m-1">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

同样地，Bootstrap也提供了相应的响应式属性`.align-items-<BREAK_POINT>-*`。

### §1.3.5 `.align-self-*`

Bootstrap通过更改原生CSS中的`align-self`属性值，封装了一系列控制弹性布局元素垂直对齐参考线的属性。

```css
.align-self-auto {
  align-self: auto !important;
}
.align-self-start {
  align-self: flex-start !important;
}
.align-self-end {
  align-self: flex-end !important;
}
.align-self-center {
  align-self: center !important;
}
.align-self-baseline {
  align-self: baseline !important;
}
.align-self-stretch {
  align-self: stretch !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["align-self-auto", "align-self-start", "align-self-end", "align-self-center", "align-self-baseline", "align-self-stretch"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <span class="w-100">.${className}</span>
                    <div class="d-flex flex-row p-1 m-3 border bg-success" style="height:100px;">
                        <div class="bg-light border p-2 m-1">测试按钮1</div>
                        <div class="bg-light border p-2 m-1 ${className}">测试按钮2</div>
                        <div class="bg-light border p-2 m-1">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

同样地，Bootstrap也提供了相应的响应式属性`.align-self-<BREAK_POINT>-*`。

### §1.3.6 `.flex-fill`

Bootstrap通过更改原生CSS中的`flex`属性值，使得`.flex-fill`可以强制平分一行内剩下的空间。

```css
.flex-fill {
  flex: 1 1 auto !important;
}
```

同样地，Bootstrap也提供了相应的响应式属性`.flex-<BREAK_POINT>-fill`。

### §1.3.7 `.flex-grow-*`/`.flex-shrink-*`

Bootstrap通过更改原生CSS中的`flex-grow`/`flex-shrink`属性值，封装了一系列控制弹性布局宽度缩放系数的属性。

```css
.flex-grow-0 {
  flex-grow: 0 !important;
}
.flex-grow-1 {
  flex-grow: 1 !important;
}
.flex-shrink-0 {
  flex-shrink: 0 !important;
}
.flex-shrink-1 {
  flex-shrink: 1 !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["flex-grow-0", "flex-grow-1", "flex-shrink-0", "flex-shrink-1"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <span class="w-100">.${className}</span>
                    <div class="d-flex flex-row p-1 m-3 border bg-success" style="height:100px;">
                        <div class="bg-light border p-2 m-1">测试按钮1</div>
                        <div class="bg-light border p-2 m-1 ${className}">测试按钮2</div>
                        <div class="bg-light border p-2 m-1">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

同样地，Bootstrap也提供了相应的响应式属性`.flex-<BREAK_POINT>-grow-*`/`.flex-<BREAK_POINT>-shrink-*`。

### §1.3.8 `.ms-*`/`.me-*`

Bootstrap通过更改原生CSS中的`margin-left`/`margin-right`属性值，封装了一系列控制左右外间距的属性。

```css
.ms-0 {
  margin-left: 0 !important;
}
.ms-1 {
  margin-left: 0.25rem !important;
}
.ms-2 {
  margin-left: 0.5rem !important;
}
.ms-3 {
  margin-left: 1rem !important;
}
.ms-4 {
  margin-left: 1.5rem !important;
}
.ms-5 {
  margin-left: 3rem !important;
}
.ms-auto {
  margin-left: auto !important;
}

.me-0 {
  margin-right: 0 !important;
}
.me-1 {
  margin-right: 0.25rem !important;
}
.me-2 {
  margin-right: 0.5rem !important;
}
.me-3 {
  margin-right: 1rem !important;
}
.me-4 {
  margin-right: 1.5rem !important;
}
.me-5 {
  margin-right: 3rem !important;
}
.me-auto {
  margin-right: auto !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            [
                "ms-auto", "ms-0", "ms-1", "ms-2", "ms-3", "ms-4", "ms-5",
                "me-auto", "me-0", "me-1", "me-2", "me-3", "me-4", "me-5"
            ].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <span class="w-100">.${className}</span>
                    <div class="d-flex flex-row p-1 m-3 border bg-success" style="height:100px;">
                        <div class="bg-light border p-2 m-1">测试按钮1</div>
                        <div class="bg-light border p-2 m-1 ${className}">测试按钮2</div>
                        <div class="bg-light border p-2 m-1">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

### §1.3.9 `.mt-*`/`.mb-*`

Bootstrap通过更改原生CSS中的`margin-top`/`margin-bottom`属性值，封装了一系列控制上下外间距的属性。

```css
.mt-0 {
  margin-top: 0 !important;
}
.mt-1 {
  margin-top: 0.25rem !important;
}
.mt-2 {
  margin-top: 0.5rem !important;
}
.mt-3 {
  margin-top: 1rem !important;
}
.mt-4 {
  margin-top: 1.5rem !important;
}
.mt-5 {
  margin-top: 3rem !important;
}
.mt-auto {
  margin-top: auto !important;
}

.mb-0 {
  margin-bottom: 0 !important;
}
.mb-1 {
  margin-bottom: 0.25rem !important;
}
.mb-2 {
  margin-bottom: 0.5rem !important;
}
.mb-3 {
  margin-bottom: 1rem !important;
}
.mb-4 {
  margin-bottom: 1.5rem !important;
}
.mb-5 {
  margin-bottom: 3rem !important;
}
.mb-auto {
  margin-bottom: auto !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            [
                "mt-auto", "mt-0", "mt-1", "mt-2", "mt-3", "mt-4", "mt-5",
                "mb-auto", "mb-0", "mb-1", "mb-2", "mb-3", "mb-4", "mb-5"
            ].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <span class="w-100">.${className}</span>
                    <div class="d-flex flex-row p-1 m-3 border bg-success" style="height:100px;">
                        <div class="bg-light border p-2 m-1">测试按钮1</div>
                        <div class="bg-light border p-2 m-1 ${className}">测试按钮2</div>
                        <div class="bg-light border p-2 m-1">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

### §1.3.10 `.flex-wrap`

`.flex-wrap`/`.flex-nowrap`/`.flex-wrap-reverse`通过更改原生CSS的`flex-wrap`属性值，来调整弹性布局的换行行为。

```css
.flex-wrap {
  flex-wrap: wrap !important;
}
.flex-nowrap {
  flex-wrap: nowrap !important;
}
.flex-wrap-reverse {
  flex-wrap: wrap-reverse !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["flex-wrap", "flex-nowrap", "flex-wrap-reverse"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <span class="w-100">.${className}</span>
                    <div class="d-flex flex-row p-1 m-3 border bg-success ${className}" style="width:300px;">
                        <div class="bg-light border p-2 m-1">测试按钮1</div>
                        <div class="bg-light border p-2 m-1">测试按钮2</div>
                        <div class="bg-light border p-2 m-1">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

同样地，Bootstrap也提供了相应的响应式属性`.flex-<BREAK_POINT>-wrap`/`.flex-<BREAK_POINT>-nowrap`/`.flex-<BREAK_POINT>-wrap-reverse`。

### §1.3.11 `.order-*`

`.order-*`通过更改原生CSS的`order`属性值，来调整弹性布局的元素排列顺序。

```css
.order-first {
  order: -1 !important;
}
.order-0 {
  order: 0 !important;
}
.order-1 {
  order: 1 !important;
}
.order-2 {
  order: 2 !important;
}
.order-3 {
  order: 3 !important;
}
.order-4 {
  order: 4 !important;
}
.order-5 {
  order: 5 !important;
}
.order-last {
  order: 6 !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="d-flex flex-row p-1 m-3 border bg-success">
            <div class="bg-light border p-2 m-1 order-last">order-last</div>
            <div class="bg-light border p-2 m-1 order-5">order-5</div>
            <div class="bg-light border p-2 m-1 order-4">order-4</div>
            <div class="bg-light border p-2 m-1 order-3">order-3</div>
            <div class="bg-light border p-2 m-1 order-2">order-2</div>
            <div class="bg-light border p-2 m-1 order-1">order-1</div>
            <div class="bg-light border p-2 m-1 order-first">order-first</div>
        </div>
    </body>
</html>
```

同样地，Bootstrap提供了相应的响应式属性`.order-<BREAK_POINT>-*`。

### §1.3.12 `.align-content-*`

Bootstrap通过更改原生CSS中的`align-content`属性值，封装了一系列控制弹性布局元素垂直对齐边界的属性。该属性生效需要`flex-wrap: wrap;`的支持。

```css
.align-content-start {
  align-content: flex-start !important;
}
.align-content-end {
  align-content: flex-end !important;
}
.align-content-center {
  align-content: center !important;
}
.align-content-between {
  align-content: space-between !important;
}
.align-content-around {
  align-content: space-around !important;
}
.align-content-stretch {
  align-content: stretch !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["align-content-start", "align-content-end", "align-content-center", "align-content-between", "align-content-around", "align-content-stretch"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <span class="w-100">.${className}</span>
                    <div class="d-flex flex-row p-1 m-3 border bg-success flex-wrap ${className}" style="height:100px;">
                        <div class="bg-light border p-2 m-1 h-50">测试按钮1</div>
                        <div class="bg-light border p-2 m-1 h-50">测试按钮2</div>
                        <div class="bg-light border p-2 m-1 h-50">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

## §1.4 浮动布局

### §1.4.1 `.float-*`

Bootstrap通过更改原生CSS中的`float`属性值，封装成了自己的浮动布局。

```css
.float-start {
  float: left !important;
}
.float-end {
  float: right !important;
}
.float-none {
  float: none !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>        
        <script>
            ["float-start", "float-end", "float-none"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <span class="w-100">.${className}</span>
                    <div class="d-flex flex-row p-1 m-3 border bg-success flex-wrap ${className}" style="height:100px;">
                        <div class="bg-light border p-2 m-1 h-50">测试按钮1</div>
                        <div class="bg-light border p-2 m-1 h-50">测试按钮2</div>
                        <div class="bg-light border p-2 m-1 h-50">测试按钮3</div>
                    </div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            })
        </script>
    </body>
</html>
```

同样地，Bootstrap也提供了相应的响应式属性`.float-<BREAK_POINT>-*`。

### §1.4.2 `.text-*`

#### §1.4.2.1 文本对齐

Bootstrap提供了下面三个属性，用于更改原生CSS中的`text-align`属性值。

```css
.text-start {
  text-align: left !important;
}
.text-end {
  text-align: right !important;
}
.text-center {
  text-align: center !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>        
        <script>
            ["text-start", "text-end", "text-center"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <p class="w-100 ${className}">.${className}</p>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

同样地，Bootstrap也提供了相应的响应式属性`.text-<BREAK_POINT>-*`。

#### §1.4.2.2 文本换行(`.text-wrap`)

Bootstrap提供了下面两个属性，用于更改原生CSS中的`white-space`属性值。

```css
.text-wrap {
  white-space: normal !important;
}
.text-nowrap {
  white-space: nowrap !important;
}
```

#### §1.4.2.3 文本大小写(`.text-*case`)

Bootstrap提供了下面三个属性，用于更改原生CSS中的`text-transform`属性值。

```css
.text-lowercase {
  text-transform: lowercase !important;
}
.text-uppercase {
  text-transform: uppercase !important;
}
.text-capitalize {
  text-transform: capitalize !important;
}
```

#### §1.4.2.4 文本加粗与斜体(`.fw-*`/`.fst-*`)

Bootstrap提供了以下属性，用于更改原生CSS中的`font-weight`属性值。

```css
.fw-lighter {
  font-weight: lighter !important;
}
.fw-light {
  font-weight: 300 !important;
}
.fw-normal {
  font-weight: 400 !important;
}
.fw-medium {
  font-weight: 500 !important;
}
.fw-semibold {
  font-weight: 600 !important;
}
.fw-bold {
  font-weight: 700 !important;
}
.fw-bolder {
  font-weight: bolder !important;
}
```

Bootstrap提供了以下属性，用于更改原生CSS中的`font-style`属性值。

```css
.fst-italic {
  font-style: italic !important;
}
.fst-normal {
  font-style: normal !important;
}
```

#### §1.4.2.5 文本大小(`.fs-*`)

Bootstrap提供了以下属性，用于更改原生CSS中的`font-size`属性值。

```css
.fs-1 {
  font-size: calc(1.375rem + 1.5vw) !important;
}
.fs-2 {
  font-size: calc(1.325rem + 0.9vw) !important;
}
.fs-3 {
  font-size: calc(1.3rem + 0.6vw) !important;
}
.fs-4 {
  font-size: calc(1.275rem + 0.3vw) !important;
}
.fs-5 {
  font-size: 1.25rem !important;
}
.fs-6 {
  font-size: 1rem !important;
}
```

#### §1.4.2.6 文本颜色(`.text-*`)

Bootstrap提供了许多改变文本颜色的属性。

| 属性名 | 作用 |
| ------ | ---- |
|`text-primary`|蓝色|
|`text-secondary`|灰色|
|`text-success`|浅绿色|
|`text-danger`|浅红色|
|`text-warning`|浅黄色|
|`text-info`|浅蓝色|
|`text-light`|浅灰色|
|`text-dark`|深灰色|
|`text-muted`|灰色|
|`text-white`|白色|
|`text-black-50`|半透明黑色|
|`text-white-50`|半透明白色|
|`text-inherit`|`inherit`|

```css
.text-primary {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-primary-rgb), var(--bs-text-opacity)) !important;
}
.text-secondary {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-secondary-rgb), var(--bs-text-opacity)) !important;
}
.text-success {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-success-rgb), var(--bs-text-opacity)) !important;
}
.text-info {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-info-rgb), var(--bs-text-opacity)) !important;
}
.text-warning {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-warning-rgb), var(--bs-text-opacity)) !important;
}
.text-danger {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-danger-rgb), var(--bs-text-opacity)) !important;
}
.text-light {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-light-rgb), var(--bs-text-opacity)) !important;
}
.text-dark {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-dark-rgb), var(--bs-text-opacity)) !important;
}
.text-black {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-black-rgb), var(--bs-text-opacity)) !important;
}
.text-white {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-white-rgb), var(--bs-text-opacity)) !important;
}
.text-body {
  --bs-text-opacity: 1;
  color: rgba(var(--bs-body-color-rgb), var(--bs-text-opacity)) !important;
}
.text-muted {
  --bs-text-opacity: 1;
  color: var(--bs-secondary-color) !important;
}
.text-black-50 {
  --bs-text-opacity: 1;
  color: rgba(0, 0, 0, 0.5) !important;
}
.text-white-50 {
  --bs-text-opacity: 1;
  color: rgba(255, 255, 255, 0.5) !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <style>
            body { background-color: antiquewhite; }
        </style>
        <script>
            ["text-primary", "text-secondary", "text-success", "text-danger", "text-warning", "text-info", "text-light", "text-dark", "text-muted", "text-white"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <p class="${className}">${className}</p>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

#### §1.4.2.7 文本修饰(`.text-decoration-*`)

Bootstrap提供了`text-decoration-*`属性，用于改变元素的`text-decoration`的属性值。

```css
.text-decoration-none {
  text-decoration: none !important;
}
.text-decoration-underline {
  text-decoration: underline !important;
}
.text-decoration-line-through {
  text-decoration: line-through !important;
}
```

### §1.4.3 `.g-*`/`.gx-*`/`.gy-*`

Bootstrap内置了`.g-*`/`.gx-*`/`.gy-*`等属性，通过更改CSS变量的值实现间距的调整。同样地，Bootstrap也提供了相应的响应式属性`.g-<BREAK_POINT>-*`/`.gx-<BREAK_POINT>-*`/`.gy-<BREAK_POINT>-*`。

```css
.g-0, .gx-0 {
  --bs-gutter-x: 0;
}
.g-0, .gy-0 {
  --bs-gutter-y: 0;
}
.g-1, .gx-1 {
  --bs-gutter-x: 0.25rem;
}
.g-1, .gy-1 {
  --bs-gutter-y: 0.25rem;
}
.g-2, .gx-2 {
  --bs-gutter-x: 0.5rem;
}
.g-2, .gy-2 {
  --bs-gutter-y: 0.5rem;
}
.g-3, .gx-3 {
  --bs-gutter-x: 1rem;
}
.g-3, .gy-3 {
  --bs-gutter-y: 1rem;
}
.g-4, .gx-4 {
  --bs-gutter-x: 1.5rem;
}
.g-4, .gy-4 {
  --bs-gutter-y: 1.5rem;
}
.g-5, .gx-5 {
  --bs-gutter-x: 3rem;
}
.g-5, .gy-5 {
  --bs-gutter-y: 3rem;
}
.row {
  --bs-gutter-x: 1.5rem;
  --bs-gutter-y: 0;
  /* ...... */
  margin-top: calc(-1 * var(--bs-gutter-y));
  margin-right: calc(-0.5 * var(--bs-gutter-x));
  margin-left: calc(-0.5 * var(--bs-gutter-x));
}
.row > * {
  /* ...... */
  padding-right: calc(var(--bs-gutter-x) * 0.5);
  padding-left: calc(var(--bs-gutter-x) * 0.5);
  margin-top: var(--bs-gutter-y);
}
```

# §2 默认样式

## §2.1 标题(`<h*>`/`.h*`)

Bootstrap重置了浏览器自带的`<h1>`、`<h2>`、`<h3>`、`<h4>`、`<h5>`、`<h6>`样式。

```css
h6, .h6, h5, .h5, h4, .h4, h3, .h3, h2, .h2, h1, .h1 {
  margin-top: 0;
  margin-bottom: 0.5rem;
  font-weight: 500;
  line-height: 1.2;
  color: var(--bs-heading-color);
}
h1, .h1 {
  font-size: calc(1.375rem + 1.5vw);
}
@media (min-width: 1200px) {
  h1, .h1 {
    font-size: 2.5rem;
  }
}
h2, .h2 {
  font-size: calc(1.325rem + 0.9vw);
}
@media (min-width: 1200px) {
  h2, .h2 {
    font-size: 2rem;
  }
}
h3, .h3 {
  font-size: calc(1.3rem + 0.6vw);
}
@media (min-width: 1200px) {
  h3, .h3 {
    font-size: 1.75rem;
  }
}
h4, .h4 {
  font-size: calc(1.275rem + 0.3vw);
}
@media (min-width: 1200px) {
  h4, .h4 {
    font-size: 1.5rem;
  }
}
h5, .h5 {
  font-size: 1.25rem;
}
h6, .h6 {
  font-size: 1rem;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <h1>&lt;h1&gt;</h1><p class="h1">.h1</p>
        <h2>&lt;h2&gt;</h2><p class="h2">.h2</p>
        <h3>&lt;h3&gt;</h3><p class="h3">.h3</p>
        <h4>&lt;h4&gt;</h4><p class="h4">.h4</p>
        <h5>&lt;h5&gt;</h5><p class="h5">.h5</p>
        <h6>&lt;h6&gt;</h6><p class="h6">.h6</p>
    </body>
</html>
```

## §2.2 突出显示(`.display-*`)

Bootstrap提供了`.display-*`属性，用于突出显示文字。

```css
.display-1 {
  font-size: calc(1.625rem + 4.5vw);
  font-weight: 300;
  line-height: 1.2;
}
@media (min-width: 1200px) {
  .display-1 {
    font-size: 5rem;
  }
}
.display-2 {
  font-size: calc(1.575rem + 3.9vw);
  font-weight: 300;
  line-height: 1.2;
}
@media (min-width: 1200px) {
  .display-2 {
    font-size: 4.5rem;
  }
}
.display-3 {
  font-size: calc(1.525rem + 3.3vw);
  font-weight: 300;
  line-height: 1.2;
}
@media (min-width: 1200px) {
  .display-3 {
    font-size: 4rem;
  }
}
.display-4 {
  font-size: calc(1.475rem + 2.7vw);
  font-weight: 300;
  line-height: 1.2;
}
@media (min-width: 1200px) {
  .display-4 {
    font-size: 3.5rem;
  }
}
.display-5 {
  font-size: calc(1.425rem + 2.1vw);
  font-weight: 300;
  line-height: 1.2;
}
@media (min-width: 1200px) {
  .display-5 {
    font-size: 3rem;
  }
}
.display-6 {
  font-size: calc(1.375rem + 1.5vw);
  font-weight: 300;
  line-height: 1.2;
}
@media (min-width: 1200px) {
  .display-6 {
    font-size: 2.5rem;
  }
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <p class="display-1">.display-1</p>
        <p class="display-2">.display-2</p>
        <p class="display-3">.display-3</p>
        <p class="display-4">.display-4</p>
        <p class="display-5">.display-5</p>
        <p class="display-6">.display-6</p>
    </body>
</html>
```

## §2.3 段落(`<p>`/`.lead`)

Bootstrap调整了`<p>`的样式，使得上外间距全部移动到下外边距。`.lead`用于突出强调段落。

```css
p {
  margin-top: 0;
  margin-bottom: 1rem;
}
.lead {
  font-size: 1.25rem;
  font-weight: 300;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <p class="lead">标题</p>
        <p>文字。</p>
        <p>文字。</p>
        <p>文字。</p>
        <p>文字。</p>
    </body>
</html>
```

## §2.4 强调(`<mark>`/`<strong>`/`<e>`)

Bootstrap调整了`<mark>`/`<strong>`/`<e>`的样式。

```css
mark, .mark {
  padding: 0.1875em;
  color: var(--bs-highlight-color);
  background-color: var(--bs-highlight-bg);
}
b, strong {
  font-weight: bolder;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <mark>&lt;mark&gt;</mark>
        <b>&lt;b&gt;</b>
        <strong>&lt;strong&gt;</strong>
    </body>
</html>
```

## §2.5 提示语(`abbr[title]`)

`<abbr title="">`是HTML5引入的新标签，当鼠标移动到该标签之上时，会弹出预先指定的提示语。Bootstrap改写了这一标签的CSS属性。

```css
abbr[title] {
  -webkit-text-decoration: underline dotted;
  text-decoration: underline dotted;
  cursor: help;
  -webkit-text-decoration-skip-ink: none;
  text-decoration-skip-ink: none;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <p>这是一段<abbr title="提示语">提示语</abbr></p>
    </body>
</html>
```

## §2.6 引用(`<blockquote>`/`.blockquote-footer`)

`<blockquote>`是HTML5引入的语义化标签，用于表示引用的文本。Bootstrap改写了这一标签的CSS属性。

```css
blockquote {
  margin: 0 0 1rem;
}
.blockquote {
  margin-bottom: 1rem;
  font-size: 1.25rem;
}
.blockquote > :last-child {
  margin-bottom: 0;
}
.blockquote-footer {
  margin-top: -1rem;
  margin-bottom: 1rem;
  font-size: 0.875em;
  color: #6c757d;
}
.blockquote-footer::before {
  content: "— ";
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <blockquote class="blockquote">
            <p>这是引用文本。</p>
            <footer class="blockquote-footer">
                这是引用<cite>脚注</cite>。
            </footer>
        </blockquote>
    </body>
</html>
```

## §2.7 代码块(`<code>`/`<pre>`)

Bootstrap改写了行内代码`<code>`和代码块`<pre>`元素的CSS属性。

```css
pre, code, kbd, samp {
  font-family: var(--bs-font-monospace);
  font-size: 1em;
}
pre {
  display: block;
  margin-top: 0;
  margin-bottom: 1rem;
  overflow: auto;
  font-size: 0.875em;
}
pre code {
  font-size: inherit;
  color: inherit;
  word-break: normal;
}
code {
  font-size: 0.875em;
  color: var(--bs-code-color);
  word-wrap: break-word;
}
a > code {
  color: inherit;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <p>行内代码&lt;code&gt;: <code>int a = 1;</code></p>
        <p>代码块&lt;pre&gt;:
            <pre>
                int add(int a, int b){
                    return a + b;
                }
            </pre>
        </p>
    </body>
</html>
```

## §2.8 图片(`.img-*`)

Bootstrap为图片提供了两种响应式属性，分别是同步缩放`.img-fluid`和缩略图`.img-thumbnail`。`.img-fluid`限制了图片的最大宽度，并为较小宽度提供了响应式设计。

```css
.img-fluid {
  max-width: 100%;
  height: auto;
}
.img-thumbnail {
  padding: 0.25rem;
  background-color: var(--bs-body-bg);
  border: var(--bs-border-width) solid var(--bs-border-color);
  border-radius: var(--bs-border-radius);
  max-width: 100%;
  height: auto;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <p>.img-fluid</p>
        <img class="img-fluid" src="https://www.baidu.com/img/flexible/logo/pc/result@2.png" alt="">
        <p>.img-thumbnail</p>
        <div class="d-flex flex-nowrap w-100">
            <img class="img-thumbnail w-25" src="https://i2.hdslb.com/bfs/archive/349d11af2161fd4d734540df5206c66242b5e975.jpg@824w_464h_1c_!web-popular.avif" alt="">
            <img class="img-thumbnail w-25" src="https://i1.hdslb.com/bfs/archive/14945c3f6893e7489e15d731aa3032716e00ebea.jpg@824w_464h_1c_!web-popular.avif" alt="">
        </div>
    </body>
</html>
```

## §2.9 表格

### §2.9.1 `<table>`/`.table`

HTML中与表格相关的标签有`<table>`、`<thead>`、`<tbody>`、`<tr>`、`<td>`、`<th>`、`<caption>`。Bootstrap重新设计了这些标签的样式，并提供了`.table`属性。

```css
table {
  caption-side: bottom;
  border-collapse: collapse;
}
caption {
  padding-top: 0.5rem;
  padding-bottom: 0.5rem;
  color: var(--bs-secondary-color);
  text-align: left;
}
th {
  text-align: inherit;
  text-align: -webkit-match-parent;
}
thead, tbody, tfoot, tr, td, th {
  border-color: inherit;
  border-style: solid;
  border-width: 0;
}
.table > :not(caption) > * > * {
  padding: 0.5rem 0.5rem;
  color: var(--bs-table-color-state, var(--bs-table-color-type, var(--bs-table-color)));
  background-color: var(--bs-table-bg);
  border-bottom-width: var(--bs-border-width);
  box-shadow: inset 0 0 0 9999px var(--bs-table-bg-state, var(--bs-table-bg-type, var(--bs-table-accent-bg)));
}
.table > tbody {
  vertical-align: inherit;
}
.table > thead {
  vertical-align: bottom;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>        
        <caption>表格标题</caption>
        <table class="table">
            <thead>
                <tr><th>姓名</th><th>性别</th><th>年龄</th></tr>
            </thead>
            <tbody>
                <tr><td>张三</td><td>男</td><td>18</td></tr>
                <tr><td>李四</td><td>女</td><td>19</td></tr>
                <tr><td>王五</td><td>男</td><td>20</td></tr>
            </tbody>
        </table>
    </body>
</html>
```

### §2.9.2 个性化主题(`.table-*`)

Bootstrap为`<table>`提供了多种个性化主题的属性。

| 属性名 | 作用 |
| ---- | ---- |
| `.table-borderless`     |  无边框主题    |
| `.table-striped`     |  条纹间隔主题    |
| `.table-bordered`     |  全边框主题    |
| `.table-hover`     |  鼠标悬浮效果主题    |

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>        
        <script>
            ["table-borderless", "table-striped", "table-bordered", "table-hover"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <caption>${className}</caption>
                    <table class="table ${className}">
                        <thead>
                            <tr><th>姓名</th><th>性别</th><th>年龄</th></tr>
                        </thead>
                        <tbody>
                            <tr><td>张三</td><td>男</td><td>18</td></tr>
                            <tr><td>李四</td><td>女</td><td>19</td></tr>
                            <tr><td>王五</td><td>男</td><td>20</td></tr>
                        </tbody>
                    </table>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

除此以外，Bootstrap还有针对`<thead>`、`<tbody>`、`<tr>`、`<td>`的属性。

| 属性名             | 作用   |
| ------------------ | ------ |
| `.table-primary`   | 蓝色   |
| `.table-success`   | 绿色   |
| `.table-danger`    | 红色   |
| `.table-info`      | 浅蓝色 |
| `.table-warning`   | 橘色   |
| `.table-active`    | 灰色   |
| `.table-secondary` | 灰色   |
| `.table-light`     | 浅灰色 |
| `.table-dark`      | 深灰色 |

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>        
        <script>
            ["table-primary", "table-success", "table-danger", "table-info", "table-warning", "table-active", "table-secondary", "table-light", "table-dark"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <caption>${className}</caption>
                    <table class="table">
                        <thead>
                            <tr><th>姓名</th><th>性别</th><th>年龄</th></tr>
                        </thead>
                        <tbody>
                            <tr><td>张三</td><td>男</td><td>18</td></tr>
                            <tr class="${className}"><td>李四</td><td>女</td><td>19</td></tr>
                            <tr><td>王五</td><td>男</td><td>20</td></tr>
                        </tbody>
                    </table>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.9.3 响应式表格(`.table-responsive`)

Bootstrap提供了`.table-responsive`属性，当表格内容过长时，会自动创建水平滚动条。同样地，Bootstrap也提供了相应的响应式属性`.table-repsonsive-<BREAK_POINT>`。

```css
.table-responsive {
  overflow-x: auto;
  -webkit-overflow-scrolling: touch;
}
@media (max-width: 575.98px) {
  .table-responsive-sm {
    overflow-x: auto;
    -webkit-overflow-scrolling: touch;
  }
}
@media (max-width: 767.98px) {
  .table-responsive-md {
    overflow-x: auto;
    -webkit-overflow-scrolling: touch;
  }
}
@media (max-width: 991.98px) {
  .table-responsive-lg {
    overflow-x: auto;
    -webkit-overflow-scrolling: touch;
  }
}
@media (max-width: 1199.98px) {
  .table-responsive-xl {
    overflow-x: auto;
    -webkit-overflow-scrolling: touch;
  }
}
@media (max-width: 1399.98px) {
  .table-responsive-xxl {
    overflow-x: auto;
    -webkit-overflow-scrolling: touch;
  }
}
```

## §2.10 边框(`.border-*`)

### §2.10.1 边框位置(`.border-*`)

Bootstrap将原生CSS的`border-top`、`border-right`、`border-bottom`、`border-left`封装起来，形成了自己的属性——`border-top`、`border-end`、`border-bottom`、`border-start`。

`.border-*`用于创建边框，而`.border-*-0`用于隐藏边框。

```css
.border {
  border: var(--bs-border-width) var(--bs-border-style) var(--bs-border-color) !important;
}
.border-0 {
  border: 0 !important;
}
.border-top {
  border-top: var(--bs-border-width) var(--bs-border-style) var(--bs-border-color) !important;
}
.border-top-0 {
  border-top: 0 !important;
}
.border-end {
  border-right: var(--bs-border-width) var(--bs-border-style) var(--bs-border-color) !important;
}
.border-end-0 {
  border-right: 0 !important;
}
.border-bottom {
  border-bottom: var(--bs-border-width) var(--bs-border-style) var(--bs-border-color) !important;
}
.border-bottom-0 {
  border-bottom: 0 !important;
}
.border-start {
  border-left: var(--bs-border-width) var(--bs-border-style) var(--bs-border-color) !important;
}
.border-start-0 {
  border-left: 0 !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["border", "border-top", "border-end", "border-bottom", "border-start"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <div style="width:10rem" class="m-2 ${className}">${className}</div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.10.2 边框颜色(`.border-*`)

Bootstrap为边框设置了多种可选的颜色。

```css
.border-primary {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-primary-rgb), var(--bs-border-opacity)) !important;
}
.border-secondary {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-secondary-rgb), var(--bs-border-opacity)) !important;
}
.border-success {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-success-rgb), var(--bs-border-opacity)) !important;
}
.border-info {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-info-rgb), var(--bs-border-opacity)) !important;
}
.border-warning {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-warning-rgb), var(--bs-border-opacity)) !important;
}
.border-danger {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-danger-rgb), var(--bs-border-opacity)) !important;
}
.border-light {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-light-rgb), var(--bs-border-opacity)) !important;
}
.border-dark {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-dark-rgb), var(--bs-border-opacity)) !important;
}
.border-black {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-black-rgb), var(--bs-border-opacity)) !important;
}
.border-white {
  --bs-border-opacity: 1;
  border-color: rgba(var(--bs-white-rgb), var(--bs-border-opacity)) !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["border-primary", "border-secondary", "border-success", "border-danger", "border-warning", "border-info", "border-light", "border-dark", "border-white"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <div class="border m-2 ${className}">${className}</div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.10.3 圆角边框(`.rounded-*`)

Bootstrap中的`.rounded-*`用于改变元素的`border-radius`属性值，使其等于预置的CSS变量。

```css
.rounded {
  border-radius: var(--bs-border-radius) !important;
}
.rounded-0 {
  border-radius: 0 !important;
}
.rounded-1 {
  border-radius: var(--bs-border-radius-sm) !important;
}
.rounded-2 {
  border-radius: var(--bs-border-radius) !important;
}
.rounded-3 {
  border-radius: var(--bs-border-radius-lg) !important;
}
.rounded-4 {
  border-radius: var(--bs-border-radius-xl) !important;
}
.rounded-5 {
  border-radius: var(--bs-border-radius-xxl) !important;
}
.rounded-circle {
  border-radius: 50% !important;
}
.rounded-pill {
  border-radius: var(--bs-border-radius-pill) !important;
}
.rounded-top {
  border-top-left-radius: var(--bs-border-radius) !important;
  border-top-right-radius: var(--bs-border-radius) !important;
}
.rounded-top-0 {
  border-top-left-radius: 0 !important;
  border-top-right-radius: 0 !important;
}
.rounded-top-1 {
  border-top-left-radius: var(--bs-border-radius-sm) !important;
  border-top-right-radius: var(--bs-border-radius-sm) !important;
}
.rounded-top-2 {
  border-top-left-radius: var(--bs-border-radius) !important;
  border-top-right-radius: var(--bs-border-radius) !important;
}
.rounded-top-3 {
  border-top-left-radius: var(--bs-border-radius-lg) !important;
  border-top-right-radius: var(--bs-border-radius-lg) !important;
}
.rounded-top-4 {
  border-top-left-radius: var(--bs-border-radius-xl) !important;
  border-top-right-radius: var(--bs-border-radius-xl) !important;
}
.rounded-top-5 {
  border-top-left-radius: var(--bs-border-radius-xxl) !important;
  border-top-right-radius: var(--bs-border-radius-xxl) !important;
}
.rounded-top-circle {
  border-top-left-radius: 50% !important;
  border-top-right-radius: 50% !important;
}
.rounded-top-pill {
  border-top-left-radius: var(--bs-border-radius-pill) !important;
  border-top-right-radius: var(--bs-border-radius-pill) !important;
}
.rounded-end {
  border-top-right-radius: var(--bs-border-radius) !important;
  border-bottom-right-radius: var(--bs-border-radius) !important;
}
.rounded-end-0 {
  border-top-right-radius: 0 !important;
  border-bottom-right-radius: 0 !important;
}
.rounded-end-1 {
  border-top-right-radius: var(--bs-border-radius-sm) !important;
  border-bottom-right-radius: var(--bs-border-radius-sm) !important;
}
.rounded-end-2 {
  border-top-right-radius: var(--bs-border-radius) !important;
  border-bottom-right-radius: var(--bs-border-radius) !important;
}
.rounded-end-3 {
  border-top-right-radius: var(--bs-border-radius-lg) !important;
  border-bottom-right-radius: var(--bs-border-radius-lg) !important;
}
.rounded-end-4 {
  border-top-right-radius: var(--bs-border-radius-xl) !important;
  border-bottom-right-radius: var(--bs-border-radius-xl) !important;
}
.rounded-end-5 {
  border-top-right-radius: var(--bs-border-radius-xxl) !important;
  border-bottom-right-radius: var(--bs-border-radius-xxl) !important;
}
.rounded-end-circle {
  border-top-right-radius: 50% !important;
  border-bottom-right-radius: 50% !important;
}
.rounded-end-pill {
  border-top-right-radius: var(--bs-border-radius-pill) !important;
  border-bottom-right-radius: var(--bs-border-radius-pill) !important;
}
.rounded-bottom {
  border-bottom-right-radius: var(--bs-border-radius) !important;
  border-bottom-left-radius: var(--bs-border-radius) !important;
}
.rounded-bottom-0 {
  border-bottom-right-radius: 0 !important;
  border-bottom-left-radius: 0 !important;
}
.rounded-bottom-1 {
  border-bottom-right-radius: var(--bs-border-radius-sm) !important;
  border-bottom-left-radius: var(--bs-border-radius-sm) !important;
}
.rounded-bottom-2 {
  border-bottom-right-radius: var(--bs-border-radius) !important;
  border-bottom-left-radius: var(--bs-border-radius) !important;
}
.rounded-bottom-3 {
  border-bottom-right-radius: var(--bs-border-radius-lg) !important;
  border-bottom-left-radius: var(--bs-border-radius-lg) !important;
}
.rounded-bottom-4 {
  border-bottom-right-radius: var(--bs-border-radius-xl) !important;
  border-bottom-left-radius: var(--bs-border-radius-xl) !important;
}
.rounded-bottom-5 {
  border-bottom-right-radius: var(--bs-border-radius-xxl) !important;
  border-bottom-left-radius: var(--bs-border-radius-xxl) !important;
}
.rounded-bottom-circle {
  border-bottom-right-radius: 50% !important;
  border-bottom-left-radius: 50% !important;
}
.rounded-bottom-pill {
  border-bottom-right-radius: var(--bs-border-radius-pill) !important;
  border-bottom-left-radius: var(--bs-border-radius-pill) !important;
}
.rounded-start {
  border-bottom-left-radius: var(--bs-border-radius) !important;
  border-top-left-radius: var(--bs-border-radius) !important;
}
.rounded-start-0 {
  border-bottom-left-radius: 0 !important;
  border-top-left-radius: 0 !important;
}
.rounded-start-1 {
  border-bottom-left-radius: var(--bs-border-radius-sm) !important;
  border-top-left-radius: var(--bs-border-radius-sm) !important;
}
.rounded-start-2 {
  border-bottom-left-radius: var(--bs-border-radius) !important;
  border-top-left-radius: var(--bs-border-radius) !important;
}
.rounded-start-3 {
  border-bottom-left-radius: var(--bs-border-radius-lg) !important;
  border-top-left-radius: var(--bs-border-radius-lg) !important;
}
.rounded-start-4 {
  border-bottom-left-radius: var(--bs-border-radius-xl) !important;
  border-top-left-radius: var(--bs-border-radius-xl) !important;
}
.rounded-start-5 {
  border-bottom-left-radius: var(--bs-border-radius-xxl) !important;
  border-top-left-radius: var(--bs-border-radius-xxl) !important;
}
.rounded-start-circle {
  border-bottom-left-radius: 50% !important;
  border-top-left-radius: 50% !important;
}
.rounded-start-pill {
  border-bottom-left-radius: var(--bs-border-radius-pill) !important;
  border-top-left-radius: var(--bs-border-radius-pill) !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            [
                "rounded", "rounded-start", "rounded-end", "rounded-top", "rounded-bottom", "rounded-circle", "rounded-pill",
                "rounded-0", "rounded-1", "rounded-2", "rounded-3", "rounded-4", "rounded-5"
            ].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <div class="border m-2 border-black ${className}">${className}</div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.10.4 边框宽度(`.border-*`)

Bootstrap提供了从一到五的边框宽度等级。

```css
.border-1 {
  border-width: 1px !important;
}

.border-2 {
  border-width: 2px !important;
}

.border-3 {
  border-width: 3px !important;
}

.border-4 {
  border-width: 4px !important;
}

.border-5 {
  border-width: 5px !important;
}
```

## §2.11 背景(`.bg-*`)

Bootstrap提供了许多调整背景颜色的属性。

```css
.bg-primary {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-primary-rgb), var(--bs-bg-opacity)) !important;
}
.bg-secondary {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-secondary-rgb), var(--bs-bg-opacity)) !important;
}
.bg-success {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-success-rgb), var(--bs-bg-opacity)) !important;
}
.bg-info {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-info-rgb), var(--bs-bg-opacity)) !important;
}
.bg-warning {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-warning-rgb), var(--bs-bg-opacity)) !important;
}
.bg-danger {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-danger-rgb), var(--bs-bg-opacity)) !important;
}
.bg-light {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-light-rgb), var(--bs-bg-opacity)) !important;
}
.bg-dark {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-dark-rgb), var(--bs-bg-opacity)) !important;
}
.bg-black {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-black-rgb), var(--bs-bg-opacity)) !important;
}
.bg-white {
  --bs-bg-opacity: 1;
  background-color: rgba(var(--bs-white-rgb), var(--bs-bg-opacity)) !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["bg-primary", "bg-secondary", "bg-success", "bg-info", "bg-warning", "bg-danger", "bg-light", "bg-dark", "bg-black"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <div class="border m-2 ${className}">${className}</div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

## §2.12 宽度和高度(`.w-*`/`.h-*`)

Bootstrap提供了调整宽度和高度的属性。

```css
.w-25 {
  width: 25% !important;
}
.w-50 {
  width: 50% !important;
}
.w-75 {
  width: 75% !important;
}
.w-100 {
  width: 100% !important;
}
.w-auto {
  width: auto !important;
}
.mw-100 {
  max-width: 100% !important;
}
.vw-100 {
  width: 100vw !important;
}
.min-vw-100 {
  min-width: 100vw !important;
}

.h-25 {
  height: 25% !important;
}
.h-50 {
  height: 50% !important;
}
.h-75 {
  height: 75% !important;
}
.h-100 {
  height: 100% !important;
}
.h-auto {
  height: auto !important;
}
.mh-100 {
  max-height: 100% !important;
}
.vh-100 {
  height: 100vh !important;
}
.min-vh-100 {
  min-height: 100vh !important;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["w-25", "w-50", "w-75", "w-100", "w-auto"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <div class="border m-2 border-black ${className}">${className}</div>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

## §2.13 外边距和内边距(`.m-*`/`.p-*`)

Bootstrap提供了调整`margin`和`padding`的属性。

| 简写 | 全拼      | 含义           |
| ---- | --------- | -------------- |
| `m`  | `margin`  | 外边距         |
| `p`  | `padding` | 内边距         |
| `t`  | `top`     | 上             |
| `b`  | `bottom`  | 下             |
| `s`  | `start`   | 左             |
| `e`  | `end`     | 右             |
| `x`  | `x`       | 横向（上和下） |
| `y`  | `y`       | 竖向（左和右） |

```css
.m-0 { margin: 0 !important;}
.m-1 { margin: 0.25rem !important;}
.m-2 { margin: 0.5rem !important;}
.m-3 { margin: 1rem !important;}
.m-4 { margin: 1.5rem !important;}
.m-5 { margin: 3rem !important;}
.m-auto { margin: auto !important;}

.mx-0 { margin-right: 0 !important; margin-left: 0 !important;}
.mx-1 { margin-right: 0.25rem !important; margin-left: 0.25rem !important;}
.mx-2 { margin-right: 0.5rem !important; margin-left: 0.5rem !important;}
.mx-3 { margin-right: 1rem !important; margin-left: 1rem !important;}
.mx-4 { margin-right: 1.5rem !important; margin-left: 1.5rem !important;}
.mx-5 { margin-right: 3rem !important; margin-left: 3rem !important;}
.mx-auto { margin-right: auto !important; margin-left: auto !important;}

.my-0 { margin-top: 0 !important; margin-bottom: 0 !important;}
.my-1 { margin-top: 0.25rem !important; margin-bottom: 0.25rem !important;}
.my-2 { margin-top: 0.5rem !important; margin-bottom: 0.5rem !important;}
.my-3 { margin-top: 1rem !important; margin-bottom: 1rem !important;}
.my-4 { margin-top: 1.5rem !important; margin-bottom: 1.5rem !important;}
.my-5 { margin-top: 3rem !important; margin-bottom: 3rem !important;}
.my-auto { margin-top: auto !important; margin-bottom: auto !important;}

.mt-0 { margin-top: 0 !important;}
.mt-1 { margin-top: 0.25rem !important;}
.mt-2 { margin-top: 0.5rem !important;}
.mt-3 { margin-top: 1rem !important;}
.mt-4 { margin-top: 1.5rem !important;}
.mt-5 { margin-top: 3rem !important;}
.mt-auto { margin-top: auto !important;}

.me-0 { margin-right: 0 !important;}
.me-1 { margin-right: 0.25rem !important;}
.me-2 { margin-right: 0.5rem !important;}
.me-3 { margin-right: 1rem !important;}
.me-4 { margin-right: 1.5rem !important;}
.me-5 { margin-right: 3rem !important;}
.me-auto { margin-right: auto !important;}

.mb-0 { margin-bottom: 0 !important;}
.mb-1 { margin-bottom: 0.25rem !important;}
.mb-2 { margin-bottom: 0.5rem !important;}
.mb-3 { margin-bottom: 1rem !important;}
.mb-4 { margin-bottom: 1.5rem !important;}
.mb-5 { margin-bottom: 3rem !important;}
.mb-auto { margin-bottom: auto !important;}

.ms-0 { margin-left: 0 !important;}
.ms-1 { margin-left: 0.25rem !important;}
.ms-2 { margin-left: 0.5rem !important;}
.ms-3 { margin-left: 1rem !important;}
.ms-4 { margin-left: 1.5rem !important;}
.ms-5 { margin-left: 3rem !important;}
.ms-auto { margin-left: auto !important;}

.p-0 { padding: 0 !important;}
.p-1 { padding: 0.25rem !important;}
.p-2 { padding: 0.5rem !important;}
.p-3 { padding: 1rem !important;}
.p-4 { padding: 1.5rem !important;}
.p-5 { padding: 3rem !important;}

.px-0 { padding-right: 0 !important; padding-left: 0 !important;}
.px-1 { padding-right: 0.25rem !important; padding-left: 0.25rem !important;}
.px-2 { padding-right: 0.5rem !important; padding-left: 0.5rem !important;}
.px-3 { padding-right: 1rem !important; padding-left: 1rem !important;}
.px-4 { padding-right: 1.5rem !important; padding-left: 1.5rem !important;}
.px-5 { padding-right: 3rem !important; padding-left: 3rem !important;}

.py-0 { padding-top: 0 !important; padding-bottom: 0 !important;}
.py-1 { padding-top: 0.25rem !important; padding-bottom: 0.25rem !important;}
.py-2 { padding-top: 0.5rem !important; padding-bottom: 0.5rem !important;}
.py-3 { padding-top: 1rem !important; padding-bottom: 1rem !important;}
.py-4 { padding-top: 1.5rem !important; padding-bottom: 1.5rem !important;}
.py-5 { padding-top: 3rem !important; padding-bottom: 3rem !important;}

.pt-0 { padding-top: 0 !important;}
.pt-1 { padding-top: 0.25rem !important;}
.pt-2 { padding-top: 0.5rem !important;}
.pt-3 { padding-top: 1rem !important;}
.pt-4 { padding-top: 1.5rem !important;}
.pt-5 { padding-top: 3rem !important;}

.pe-0 { padding-right: 0 !important;}
.pe-1 { padding-right: 0.25rem !important;}
.pe-2 { padding-right: 0.5rem !important;}
.pe-3 { padding-right: 1rem !important;}
.pe-4 { padding-right: 1.5rem !important;}
.pe-5 { padding-right: 3rem !important;}

.pb-0 { padding-bottom: 0 !important;}
.pb-1 { padding-bottom: 0.25rem !important;}
.pb-2 { padding-bottom: 0.5rem !important;}
.pb-3 { padding-bottom: 1rem !important;}
.pb-4 { padding-bottom: 1.5rem !important;}
.pb-5 { padding-bottom: 3rem !important;}

.ps-0 { padding-left: 0 !important;}
.ps-1 { padding-left: 0.25rem !important;}
.ps-2 { padding-left: 0.5rem !important;}
.ps-3 { padding-left: 1rem !important;}
.ps-4 { padding-left: 1.5rem !important;}
.ps-5 { padding-left: 3rem !important;} 
```

## §2.14 显示(`.d-*`)

Bootstrap将原生CSS中的`display`属性进行了封装。

```css
.d-inline {
  display: inline !important;
}
.d-inline-block {
  display: inline-block !important;
}
.d-block {
  display: block !important;
}
.d-grid {
  display: grid !important;
}
.d-inline-grid {
  display: inline-grid !important;
}
.d-table {
  display: table !important;
}
.d-table-row {
  display: table-row !important;
}
.d-table-cell {
  display: table-cell !important;
}
.d-flex {
  display: flex !important;
}
.d-inline-flex {
  display: inline-flex !important;
}
.d-none {
  display: none !important;
}
```

同样地，Bootstrap提供了相应的响应式属性`.d-<BREAK_POINT>-*`。以下是几种常见的组合使用方式：

| 属性                          | 作用                       |
| ----------------------------- | -------------------------- |
| `d-block d-sm-none`           | 只在超小型设备(`xs`)上显示 |
| `d-none d-sm-block d-md-none` | 只在小型设备(`sm`)上显示   |
| `d-none d-md-block d-lg-none` | 只在中型设备(`md`)上显示   |
| `d-none d-lg-block d-xl-none` | 只在大型设备(`lg`)上显示   |
| `d-none d-xl-block`           | 只在超大型设备(`xl`)上显示 |
| `d-none`                      | 在所有设备上隐藏           |
| `[d-block]`或空字符串         | 在所有设备上显示           |
| `d-none d-sm-block`           | 只在超小型设备(`xs`)上隐藏 |
| `d-sm-none d-md-block`        | 只在小型设备(`sm`)上隐藏   |
| `d-md-none d-lg-block`        | 只在中型设备(`md`)上隐藏   |
| `d-lg-none d-xl-block`        | 只在大型设备(`lg`)上隐藏   |
| `d-xl-none`                   | 只在超大型设备(`xl`)上隐藏 |

## §2.15 溢出(`.overflow-*`)

Bootstrap对原生CSS中的`overflow`进行了封装。

```css
.overflow-auto {
  overflow: auto !important;
}
.overflow-hidden {
  overflow: hidden !important;
}
.overflow-visible {
  overflow: visible !important;
}
.overflow-scroll {
  overflow: scroll !important;
}
.overflow-x-auto {
  overflow-x: auto !important;
}
.overflow-x-hidden {
  overflow-x: hidden !important;
}
.overflow-x-visible {
  overflow-x: visible !important;
}
.overflow-x-scroll {
  overflow-x: scroll !important;
}
.overflow-y-auto {
  overflow-y: auto !important;
}
.overflow-y-hidden {
  overflow-y: hidden !important;
}
.overflow-y-visible {
  overflow-y: visible !important;
}
.overflow-y-scroll {
  overflow-y: scroll !important;
}
```

## §2.16 定位方式(`.position-*`)

Bootstrap封装了原生CSS中的`position`属性值。

```css
.position-static {
  position: static !important;
}
.position-relative {
  position: relative !important;
}
.position-absolute {
  position: absolute !important;
}
.position-fixed {
  position: fixed !important;
}
.position-sticky {
  position: -webkit-sticky !important;
  position: sticky !important;
}
```

## §2.17 阴影(`.shadow-*`)

Bootstrap封装了原生CSS中的`box-shadow`属性值。

```css
.shadow {
  box-shadow: var(--bs-box-shadow) !important;
}
.shadow-sm {
  box-shadow: var(--bs-box-shadow-sm) !important;
}
.shadow-lg {
  box-shadow: var(--bs-box-shadow-lg) !important;
}
.shadow-none {
  box-shadow: none !important;
}
```

> 注意：这里的`sm`、`lg`不是响应式的意思，而是表示阴影的大小。

## §2.18 表单(`.form-*`)

我们直到，HTML提供了`<input>`、`<select>`、`<option>`、`<textarea>`等表单元素，

```css
input, button, select, optgroup, textarea {
  margin: 0;
  font-family: inherit;
  font-size: inherit;
  line-height: inherit;
}
button, select {
  text-transform: none;
}
[role=button] {
  cursor: pointer;
}
select {
  word-wrap: normal;
}
select:disabled {
  opacity: 1;
}
[list]:not([type=date]):not([type=datetime-local]):not([type=month]):not([type=week]):not([type=time])::-webkit-calendar-picker-indicator {
  display: none !important;
}
button, [type=button], [type=reset], [type=submit] {
  -webkit-appearance: button;
}
button:not(:disabled), [type=button]:not(:disabled), [type=reset]:not(:disabled), [type=submit]:not(:disabled) {
  cursor: pointer;
}
::-moz-focus-inner {
  padding: 0;
  border-style: none;
}
textarea {
  resize: vertical;
}
fieldset {
  min-width: 0;
  padding: 0;
  margin: 0;
  border: 0;
}
legend {
  float: left;
  width: 100%;
  padding: 0;
  margin-bottom: 0.5rem;
  font-size: calc(1.275rem + 0.3vw);
  line-height: inherit;
}
@media (min-width: 1200px) {
  legend {
    font-size: 1.5rem;
  }
}
legend + * {
  clear: left;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <form class="p-5">
            <div class="my-3">
                <label class="form-label">用户名</label>
                <input class="form-control" type="text" name="username" id="username">
            </div>
            <div class="my-3">
                <label class="form-label">密码</label>
                <input class="form-control" type="text" name="username" id="username">
            </div>
            <button class="btn btn-primary">登录</button>
        </form>
    </body>
</html>
```

### §2.18.1 表单控件(`.form-control-*`)

在HTML中，可供用户输入的元素称为表单控件。Bootstrap对众多表单控件的样式进行了重写。

```css
.form-control {
  display: block;
  width: 100%;
  padding: 0.375rem 0.75rem;
  font-size: 1rem;
  font-weight: 400;
  line-height: 1.5;
  color: var(--bs-body-color);
  -webkit-appearance: none;
  -moz-appearance: none;
  appearance: none;
  background-color: var(--bs-body-bg);
  background-clip: padding-box;
  border: var(--bs-border-width) solid var(--bs-border-color);
  border-radius: var(--bs-border-radius);
  transition: border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
}
@media (prefers-reduced-motion: reduce) {
  .form-control {
    transition: none;
  }
}
.form-control[type=file] {
  overflow: hidden;
}
.form-control[type=file]:not(:disabled):not([readonly]) {
  cursor: pointer;
}
.form-control:focus {
  color: var(--bs-body-color);
  background-color: var(--bs-body-bg);
  border-color: #86b7fe;
  outline: 0;
  box-shadow: 0 0 0 0.25rem rgba(13, 110, 253, 0.25);
}
.form-control::-webkit-date-and-time-value {
  min-width: 85px;
  height: 1.5em;
  margin: 0;
}
.form-control::-webkit-datetime-edit {
  display: block;
  padding: 0;
}
.form-control::-moz-placeholder {
  color: var(--bs-secondary-color);
  opacity: 1;
}
.form-control::placeholder {
  color: var(--bs-secondary-color);
  opacity: 1;
}
.form-control:disabled {
  background-color: var(--bs-secondary-bg);
  opacity: 1;
}
.form-control::-webkit-file-upload-button {
  padding: 0.375rem 0.75rem;
  margin: -0.375rem -0.75rem;
  -webkit-margin-end: 0.75rem;
  margin-inline-end: 0.75rem;
  color: var(--bs-body-color);
  background-color: var(--bs-tertiary-bg);
  pointer-events: none;
  border-color: inherit;
  border-style: solid;
  border-width: 0;
  border-inline-end-width: var(--bs-border-width);
  border-radius: 0;
  -webkit-transition: color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
  transition: color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
}
.form-control::file-selector-button {
  padding: 0.375rem 0.75rem;
  margin: -0.375rem -0.75rem;
  -webkit-margin-end: 0.75rem;
  margin-inline-end: 0.75rem;
  color: var(--bs-body-color);
  background-color: var(--bs-tertiary-bg);
  pointer-events: none;
  border-color: inherit;
  border-style: solid;
  border-width: 0;
  border-inline-end-width: var(--bs-border-width);
  border-radius: 0;
  transition: color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
}
@media (prefers-reduced-motion: reduce) {
  .form-control::-webkit-file-upload-button {
    -webkit-transition: none;
    transition: none;
  }
  .form-control::file-selector-button {
    transition: none;
  }
}
.form-control:hover:not(:disabled):not([readonly])::-webkit-file-upload-button {
  background-color: var(--bs-secondary-bg);
}
.form-control:hover:not(:disabled):not([readonly])::file-selector-button {
  background-color: var(--bs-secondary-bg);
}

.form-control-plaintext {
  display: block;
  width: 100%;
  padding: 0.375rem 0;
  margin-bottom: 0;
  line-height: 1.5;
  color: var(--bs-body-color);
  background-color: transparent;
  border: solid transparent;
  border-width: var(--bs-border-width) 0;
}
.form-control-plaintext:focus {
  outline: 0;
}
.form-control-plaintext.form-control-sm, .form-control-plaintext.form-control-lg {
  padding-right: 0;
  padding-left: 0;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <form class="p-5">
            <input class="form-control my-2" type="button" value="按钮">
            <input class="form-control my-2" type="date" name="" id="">
            <input class="form-control my-2" type="datetime-local" name="" id="">
            <input class="form-control my-2" type="file" name="" id="">
            <input class="form-control my-2" type="range" name="" id="">
            <input class="form-control my-2" type="submit" value="提交">
            <textarea class="form-control" name="" id="" cols="30" rows="3">多行文本</textarea>
        </form>
    </body>
</html>
```

### §2.18.2 表单控件大小(`.form-control-*`)

Bootstrap为表单控件提供了三种尺寸，从小到大依次为：`.form-control-sm`、`.form-control`、`.form-control-lg`。首尾两个属性都需要配合中间的`,form-control`一起使用。

```css
.form-control-sm {
  min-height: calc(1.5em + 0.5rem + calc(var(--bs-border-width) * 2));
  padding: 0.25rem 0.5rem;
  font-size: 0.875rem;
  border-radius: var(--bs-border-radius-sm);
}
.form-control-sm::-webkit-file-upload-button {
  padding: 0.25rem 0.5rem;
  margin: -0.25rem -0.5rem;
  -webkit-margin-end: 0.5rem;
  margin-inline-end: 0.5rem;
}
.form-control-sm::file-selector-button {
  padding: 0.25rem 0.5rem;
  margin: -0.25rem -0.5rem;
  -webkit-margin-end: 0.5rem;
  margin-inline-end: 0.5rem;
}

.form-control-lg {
  min-height: calc(1.5em + 1rem + calc(var(--bs-border-width) * 2));
  padding: 0.5rem 1rem;
  font-size: 1.25rem;
  border-radius: var(--bs-border-radius-lg);
}
.form-control-lg::-webkit-file-upload-button {
  padding: 0.5rem 1rem;
  margin: -0.5rem -1rem;
  -webkit-margin-end: 1rem;
  margin-inline-end: 1rem;
}
.form-control-lg::file-selector-button {
  padding: 0.5rem 1rem;
  margin: -0.5rem -1rem;
  -webkit-margin-end: 1rem;
  margin-inline-end: 1rem;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["form-control-sm", "form-control-lg"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <form id="form" class="p-5">
                        <input class="form-control ${className} my-2" type="button" value="按钮">
                        <input class="form-control ${className} my-2" type="date" name="" id="">
                        <input class="form-control ${className} my-2" type="datetime-local" name="" id="">
                        <input class="form-control ${className} my-2" type="file" name="" id="">
                        <input class="form-control ${className} my-2" type="range" name="" id="">
                        <input class="form-control ${className} my-2" type="submit" value="提交">
                        <textarea class="form-control ${className} my-2" name="" id="" cols="30" rows="3">多行文本</textarea>
                    </form>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.18.3 表单控件只读(`readonly`)

Bootstrap会探测DOM上是否有`readonly`属性，从而调整只读的样式。

```css
.form-control[type=file]:not(:disabled):not([readonly]) {
  cursor: pointer;
}
.form-control:hover:not(:disabled):not([readonly])::-webkit-file-upload-button {
  background-color: var(--bs-secondary-bg);
}
.form-control:hover:not(:disabled):not([readonly])::file-selector-button {
  background-color: var(--bs-secondary-bg);
}
.form-control-color:not(:disabled):not([readonly]) {
  cursor: pointer;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["readonly"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <form id="form" class="p-5">
                        <input ${className} class="form-control my-2" type="button" value="按钮">
                        <input ${className} class="form-control my-2" type="date" name="" id="">
                        <input ${className} class="form-control my-2" type="datetime-local" name="" id="">
                        <input ${className} class="form-control my-2" type="file" name="" id="">
                        <input ${className} class="form-control my-2" type="range" name="" id="">
                        <input ${className} class="form-control my-2" type="submit" value="提交">
                        <textarea ${className} class="form-control my-2" name="" id="" cols="30" rows="3">多行文本</textarea>
                    </form>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.18.4 表单纯文本(`.form-control-plaintext`)

`.form-control-plaintext`使得表单控件丢失边框样式，但是保留`:active`和输入功能。

```css
.form-control-plaintext {
  display: block;
  width: 100%;
  padding: 0.375rem 0;
  margin-bottom: 0;
  line-height: 1.5;
  color: var(--bs-body-color);
  background-color: transparent;
  border: solid transparent;
  border-width: var(--bs-border-width) 0;
}
.form-control-plaintext:focus {
  outline: 0;
}
.form-control-plaintext.form-control-sm, .form-control-plaintext.form-control-lg {
  padding-right: 0;
  padding-left: 0;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["form-control-plaintext"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <form id="form" class="p-5">
                        <input class="form-control ${className} my-2" type="button" value="按钮">
                        <input class="form-control ${className} my-2" type="date" name="" id="">
                        <input class="form-control ${className} my-2" type="datetime-local" name="" id="">
                        <input class="form-control ${className} my-2" type="file" name="" id="">
                        <input class="form-control ${className} my-2" type="range" name="" id="">
                        <input class="form-control ${className} my-2" type="submit" value="提交">
                        <textarea class="form-control ${className} my-2" name="" id="" cols="30" rows="3">多行文本</textarea>
                    </form>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.18.5 范围输入控件(`.form-range`)

Bootstrap使用`.form-range`修饰`<input type="range">`。

```css
.form-range {
  width: 100%;
  height: 1.5rem;
  padding: 0;
  -webkit-appearance: none;
  -moz-appearance: none;
  appearance: none;
  background-color: transparent;
}
.form-range:focus {
  outline: 0;
}
.form-range:focus::-webkit-slider-thumb {
  box-shadow: 0 0 0 1px #fff, 0 0 0 0.25rem rgba(13, 110, 253, 0.25);
}
.form-range:focus::-moz-range-thumb {
  box-shadow: 0 0 0 1px #fff, 0 0 0 0.25rem rgba(13, 110, 253, 0.25);
}
.form-range::-moz-focus-outer {
  border: 0;
}
.form-range::-webkit-slider-thumb {
  width: 1rem;
  height: 1rem;
  margin-top: -0.25rem;
  -webkit-appearance: none;
  appearance: none;
  background-color: #0d6efd;
  border: 0;
  border-radius: 1rem;
  -webkit-transition: background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
  transition: background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
}
@media (prefers-reduced-motion: reduce) {
  .form-range::-webkit-slider-thumb {
    -webkit-transition: none;
    transition: none;
  }
}
.form-range::-webkit-slider-thumb:active {
  background-color: #b6d4fe;
}
.form-range::-webkit-slider-runnable-track {
  width: 100%;
  height: 0.5rem;
  color: transparent;
  cursor: pointer;
  background-color: var(--bs-secondary-bg);
  border-color: transparent;
  border-radius: 1rem;
}
.form-range::-moz-range-thumb {
  width: 1rem;
  height: 1rem;
  -moz-appearance: none;
  appearance: none;
  background-color: #0d6efd;
  border: 0;
  border-radius: 1rem;
  -moz-transition: background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
  transition: background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
}
@media (prefers-reduced-motion: reduce) {
  .form-range::-moz-range-thumb {
    -moz-transition: none;
    transition: none;
  }
}
.form-range::-moz-range-thumb:active {
  background-color: #b6d4fe;
}
.form-range::-moz-range-track {
  width: 100%;
  height: 0.5rem;
  color: transparent;
  cursor: pointer;
  background-color: var(--bs-secondary-bg);
  border-color: transparent;
  border-radius: 1rem;
}
.form-range:disabled {
  pointer-events: none;
}
.form-range:disabled::-webkit-slider-thumb {
  background-color: var(--bs-secondary-color);
}
.form-range:disabled::-moz-range-thumb {
  background-color: var(--bs-secondary-color);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        音量：<label id="volume"></label>
        <script>
            function onRangeChange(event) {
                document.getElementById("volume").innerHTML = event.target.value
            }
        </script>
        <form id="form" class="p-5">
            <input class="form-control form-range my-2" type="range" step="1" min="0" max="100" oninput="onRangeChange(event)">
        </form>
    </body>
</html>
```



### §2.18.6 单选框/复选框控件(`.form-check-*`)

我们知道，一个完整的单选框包含左边的输入控件和右边的文字标签。Bootstrap使用`.form-check`修饰这个完整的整体，然后使用`.form-check-input`和`.form-check-label`分别修饰控件和文本。

```css
.form-check {
  display: block;
  min-height: 1.5rem;
  padding-left: 1.5em;
  margin-bottom: 0.125rem;
}
.form-check .form-check-input {
  float: left;
  margin-left: -1.5em;
}
.form-check-input {
  --bs-form-check-bg: var(--bs-body-bg);
  flex-shrink: 0;
  width: 1em;
  height: 1em;
  margin-top: 0.25em;
  vertical-align: top;
  -webkit-appearance: none;
  -moz-appearance: none;
  appearance: none;
  background-color: var(--bs-form-check-bg);
  background-image: var(--bs-form-check-bg-image);
  background-repeat: no-repeat;
  background-position: center;
  background-size: contain;
  border: var(--bs-border-width) solid var(--bs-border-color);
  -webkit-print-color-adjust: exact;
  color-adjust: exact;
  print-color-adjust: exact;
}
.form-check-input[type=checkbox] {
  border-radius: 0.25em;
}
.form-check-input[type=radio] {
  border-radius: 50%;
}
.form-check-input:active {
  filter: brightness(90%);
}
.form-check-input:focus {
  border-color: #86b7fe;
  outline: 0;
  box-shadow: 0 0 0 0.25rem rgba(13, 110, 253, 0.25);
}
.form-check-input:checked {
  background-color: #0d6efd;
  border-color: #0d6efd;
}
.form-check-input:checked[type=checkbox] {
  --bs-form-check-bg-image: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 20 20'%3e%3cpath fill='none' stroke='%23fff' stroke-linecap='round' stroke-linejoin='round' stroke-width='3' d='m6 10 3 3 6-6'/%3e%3c/svg%3e");
}
.form-check-input:checked[type=radio] {
  --bs-form-check-bg-image: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='-4 -4 8 8'%3e%3ccircle r='2' fill='%23fff'/%3e%3c/svg%3e");
}
.form-check-input[type=checkbox]:indeterminate {
  background-color: #0d6efd;
  border-color: #0d6efd;
  --bs-form-check-bg-image: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 20 20'%3e%3cpath fill='none' stroke='%23fff' stroke-linecap='round' stroke-linejoin='round' stroke-width='3' d='M6 10h8'/%3e%3c/svg%3e");
}
.form-check-input:disabled {
  pointer-events: none;
  filter: none;
  opacity: 0.5;
}
.form-check-input[disabled] ~ .form-check-label, .form-check-input:disabled ~ .form-check-label {
  cursor: default;
  opacity: 0.5;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <form id="form" class="p-5">
            <div class="form-check">
                <input class="form-check-input" type="radio" name="radio" id="radio">
                <label class="form-check-label" for="radio">单选框</label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="checkbox" name="checkbox" id="checkbox">
                <label class="form-check-label" for="checkbox">复选框</label>
            </div>
        </form>
    </body>
</html>
```

前面我们说过，Bootstrap使用`.form-check`修饰这个完整的整体。其实我们也可以用`.form-check-inline`，使多个单选框/复选框控件水平排列。

```css
.form-check-inline {
  display: inline-block;
  margin-right: 1rem;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <form id="form" class="p-5">
            <div class="form-check-inline">
                <input class="form-check-input" type="radio" name="radio" id="radio">
                <label class="form-check-label" for="radio">单选框</label>
            </div>
            <div class="form-check-inline">
                <input class="form-check-input" type="checkbox" name="checkbox" id="checkbox">
                <label class="form-check-label" for="checkbox">复选框</label>
            </div>
        </form>
    </body>
</html>
```

### §2.18.7 表单文本

Bootstrap提供了`.form-text`属性，常用于作为提示文字。

```css
.form-text {
  margin-top: 0.25rem;
  font-size: 0.875em;
  color: var(--bs-secondary-color);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <form id="form" class="p-5">
            <label class="form-label">新密码</label>
            <input class="form-control" type="text">
            <span class="form-text">密码必须包含大小写和数字。</span>
        </form>
    </body>
</html>
```

### §2.18.8 表单控件禁用(`disabled`)

与[§2.18.3 表单控件只读(`readonly`)](###§2.18.3 表单控件只读(`readonly`))类似，Bootstrap也提供了`disabled`DOM属性。这里不再赘述。

### §2.18.9 单选/多选菜单(`select.form-select`)

Bootstrap针对`<select>`和`<select multiple>`提供了`.form-select`属性，为单选/多选菜单提供样式。

```css
.form-select {
  --bs-form-select-bg-img: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 16 16'%3e%3cpath fill='none' stroke='%23343a40' stroke-linecap='round' stroke-linejoin='round' stroke-width='2' d='m2 5 6 6 6-6'/%3e%3c/svg%3e");
  display: block;
  width: 100%;
  padding: 0.375rem 2.25rem 0.375rem 0.75rem;
  font-size: 1rem;
  font-weight: 400;
  line-height: 1.5;
  color: var(--bs-body-color);
  -webkit-appearance: none;
  -moz-appearance: none;
  appearance: none;
  background-color: var(--bs-body-bg);
  background-image: var(--bs-form-select-bg-img), var(--bs-form-select-bg-icon, none);
  background-repeat: no-repeat;
  background-position: right 0.75rem center;
  background-size: 16px 12px;
  border: var(--bs-border-width) solid var(--bs-border-color);
  border-radius: var(--bs-border-radius);
  transition: border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
}
@media (prefers-reduced-motion: reduce) {
  .form-select {
    transition: none;
  }
}
.form-select:focus {
  border-color: #86b7fe;
  outline: 0;
  box-shadow: 0 0 0 0.25rem rgba(13, 110, 253, 0.25);
}
.form-select[multiple], .form-select[size]:not([size="1"]) {
  padding-right: 0.75rem;
  background-image: none;
}
.form-select:disabled {
  background-color: var(--bs-secondary-bg);
}
.form-select:-moz-focusring {
  color: transparent;
  text-shadow: 0 0 0 var(--bs-body-color);
}
.form-select-sm {
  padding-top: 0.25rem;
  padding-bottom: 0.25rem;
  padding-left: 0.5rem;
  font-size: 0.875rem;
  border-radius: var(--bs-border-radius-sm);
}
.form-select-lg {
  padding-top: 0.5rem;
  padding-bottom: 0.5rem;
  padding-left: 1rem;
  font-size: 1.25rem;
  border-radius: var(--bs-border-radius-lg);
}
[data-bs-theme=dark] .form-select {
  --bs-form-select-bg-img: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 16 16'%3e%3cpath fill='none' stroke='%23dee2e6' stroke-linecap='round' stroke-linejoin='round' stroke-width='2' d='m2 5 6 6 6-6'/%3e%3c/svg%3e");
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <select class="form-select m-2">
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
        </select>
        <select multiple class="form-select m-2">
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
        </select>
    </body>
</html>
```

### §2.18.10 浮动标签(`.form-floating`)

在Bootstrap中，`.form-floating`的样式效果类似于Material UI中的文本框标签动画。当元素被选中时，`placeholder`的文本会自动缩小并向上移动。`.form-floating`要求第一个元素必须为`<input>`且DOM上带有`placeholder`属性值，第二个子元素必须为`<label>`。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <form action="">
            <div class="form-floating m-3">
                <input type="text" class="form-control" id="email" placeholder="输入邮箱">
                <label>输入邮箱</label>
            </div>
            <div class="form-floating m-3">
                <input type="text" class="form-control" placeholder="输入密码">
                <label>输入密码</label>
            </div>
        </form>
    </body>
</html>
```

### §2.18.11 表单验证(`.*-feedback`/`.*-valid*`)

用Bootstrap提供的`.was-validated`和`.needs-validation`修饰`<form>`元素，可以让其中的`<input>`根据数据是否符合要求来改变边框颜色。而`.valid-feedback`和`.invalid-feedback`用于提供反馈。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <form class="was-validated needs-validation">
            <div class="form-floating m-3">
                <input type="email" required class="form-control" placeholder="输入邮箱">
                <label>输入邮箱</label>
                <div class="invalid-feedback">邮箱格式错误</div>
            </div>
            <div class="form-floating m-3">
                <input type="password" required class="form-control" placeholder="输入密码">
                <label>输入密码</label>
                <div class="invalid-feedback">请输入密码</div>
            </div>
        </form>
    </body>
</html>
```

## §2.19 按钮(`.btn-*`)

Bootstrap通过`.btn`来表示按钮，每个按钮都应该带有该属性。

### §2.19.1 按钮背景颜色(`.btn-*`)

| 属性名           | 颜色   |
| ---------------- | ------ |
| `.btn-primary`   | 蓝色   |
| `.btn-secondary` | 灰色   |
| `.btn-success`   | 绿色   |
| `.btn-danger`    | 红色   |
| `.btn-warning`   | 黄色   |
| `.btn-info`      | 浅蓝色 |
| `.btn-light`     | 浅灰色 |
| `.btn-dark`      | 黑色   |

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["btn-primary", "btn-secondary", "btn-success", "btn-danger", "btn-warning", "btn-info", "btn-light", "btn-dark"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <button class="m-2 btn ${className}">${className}</button>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.19.2 按钮边框颜色(`.btn-outline-*`)

`.btn-outline-*`用于同时改变按钮的边框与文字的颜色。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["btn-outline-primary", "btn-outline-secondary", "btn-outline-success", "btn-outline-danger", "btn-outline-warning", "btn-outline-info", "btn-outline-light", "btn-outline-dark"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <button class="m-2 btn ${className}">${className}</button>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.19.3 按钮大小(`.btn-*`)

Bootstrap提供了三种不同大小的尺寸属性——`.btn-sm`、`.btn`、`.btn-lg`。首尾两个属性需要搭配中间的属性一起使用。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["btn btn-sm", "btn", "btn btn-lg"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <button class="m-2 btn-primary ${className}">${className}</button>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.19.4 按钮激活与禁用(`[active]`/`[disabled]`)

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["active", "正常按钮" ,"disabled"].forEach((className)=>{
                const flexBoxDomSerialization = `
                    <button class="m-2 btn btn-primary ${className}">${className}</button>
                `;
                document.querySelector("body").innerHTML += flexBoxDomSerialization;
            });
        </script>
    </body>
</html>
```

### §2.19.5 按钮加载样式(`.spinner-border`/`.spinner-grow`)

Bootstrap提供了两种加载动画样式——`.spinner-border`和`.spinner-grow`，并且配备了对应的小尺寸属性。我们可以使用`text-*`改变其颜色，或者`.spinner-border-sm`/`.spinner-grow-sm`来缩小尺寸。

```css
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <button class="btn btn-primary m-2">
            <span class="spinner-border spinner-border-sm"></span>
            按钮 spinner-border
        </button>
        <button class="btn btn-primary m-2">
            <span class="spinner-grow spinner-grow-sm"></span>
            按钮 grow-border
        </button>
    </body>
</html>
```

### §2.19.6 按钮组(`.btn-group`)

Bootstrap提供了按钮组属性，用于将许多按钮排成一行。该样式常用于翻页按钮组。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="btn-group m-2">
            <button type="button" class="btn border btn-primary">&lt;</button>
            <button type="button" class="btn border btn-light">1</button>
            <button type="button" class="btn border btn-light">2</button>
            <button type="button" class="btn border btn-warning">3</button>
            <button type="button" class="btn border btn-light">4</button>
            <button type="button" class="btn border btn-primary">&gt;</button>
        </div>
    </body>
</html>
```

同样地，Bootstrap也提供了三档尺寸：`.btn-group-sm`、`.btn-group`、`.btn-group-lg`。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <script>
            ["btn-group-sm", "", "btn-group-lg"].forEach((className) => {
                const htmlString = `
                    <div class="btn-group ${className}">
                        <button type="button" class="btn border btn-primary">&lt;</button>
                        <button type="button" class="btn border btn-light">1</button>
                        <button type="button" class="btn border btn-light">2</button>
                        <button type="button" class="btn border btn-warning">3</button>
                        <button type="button" class="btn border btn-light">4</button>
                        <button type="button" class="btn border btn-primary">&gt;</button>
                    </div>
                `;
                document.body.innerHTML += htmlString;
            });
        </script>
    </body>
</html>
```

### §2.19.7 按钮组工具栏(`.btn-toolbar`)

在上一节中，我们接触了Bootstrap中的`.btn-group`。实际上Bootstrap提供的组还有`.input-group`。将多个组包裹起来，对父元素使用`.btn-toolbar`，我们就得到了更复杂的按钮组工具栏。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.js"></script>
    </head>
    <body>
        <div class="btn-toolbar m-2">
            <div class="btn-group">
                <button type="button" class="btn border btn-primary">&lt;</button>
                <button type="button" class="btn border btn-light">1</button>
                <button type="button" class="btn border btn-light">2</button>
                <button type="button" class="btn border btn-warning">3</button>
                <button type="button" class="btn border btn-light">4</button>
                <button type="button" class="btn border btn-primary">&gt;</button>
            </div>
            <div class="input-group">
                <div class="input-group-prepend">
                    <div class="input-group-text">跳转至</div>
                </div>
                <input class="form-control" type="text">
            </div>
        </div>
    </body>
</html>
```

## §2.20 下拉菜单(`.dropdown-*`)

下拉菜单整体作为一个`.btn-group`，包含了三个部分：一是菜单入口`.dropdown`，二是子菜单`.dropdown-menu`，三是一系列子菜单项`.dropdown-item`。

> 注意：下拉菜单需要`popper.js`的支持。在Bootstrap发行的JavaScript脚本中，`bootstrap.js`不包含`popper.js`框架，这里我们需要使用`bootstrap.bundle.js`。

一个基本的下拉菜单结构如下所示，其中`.dropdown-toggle`用于修饰按钮的三角形展开图标，`data-bs-toggle`用于让JavaScript绑定菜单展开的行为。

```html
<div class="dropdown">
    <button class="dropdown-toggle" data-bs-toggle="dropdown">触发按钮</button>
    <div class="dropdown-menu">
        <div class="dropdown-item"></div>
    </div>
```

下面是一个完整的例子：

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body>
        <div class="btn-group">
            <button class="btn btn-primary">首页</button>
            <div class="btn-group">
                <button class="btn btn-info dropdown-toggle" data-bs-toggle="dropdown">课程</button>
                <div class="dropdown-menu">
                    <button class="dropdown-item">C</button>
                    <button class="dropdown-item">C++</button>
                    <button class="dropdown-item">Java</button>
                    <button class="dropdown-item">Python</button>
                </div>
            </div>
        </div>
    </body>
</html>
```

### §2.20.1 分裂式菜单(`.dropdown-toggle-split`)

假设有一个按钮组包含了两个按钮，左边的按钮表示主页设置，占了四个中文字符，而右边的按钮只有一个三角形，表示点击展开更多项目。我们希望右边的按钮尽可能短，给其他同级菜单项腾出更多空间。Bootstrap提供了`.dropdown-toggle-split`属性来实现这一点。

```css
.dropdown-toggle-split {
  padding-right: 0.5625rem;
  padding-left: 0.5625rem;
}
.dropdown-toggle-split::after, .dropup .dropdown-toggle-split::after, .dropend .dropdown-toggle-split::after {
  margin-left: 0;
}
.dropstart .dropdown-toggle-split::before {
  margin-right: 0;
}

.btn-sm + .dropdown-toggle-split, .btn-group-sm > .btn + .dropdown-toggle-split {
  padding-right: 0.375rem;
  padding-left: 0.375rem;
}

.btn-lg + .dropdown-toggle-split, .btn-group-lg > .btn + .dropdown-toggle-split {
  padding-right: 0.75rem;
  padding-left: 0.75rem;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body>
        <div class="btn-group">
            <button class="btn btn-primary">个人信息</button>
            <div class="btn-group">
                <button class="btn btn-info dropdown-toggle dropdown-toggle-split" data-bs-toggle="dropdown"></button>
                <div class="dropdown-menu">
                    <button class="dropdown-item">C</button>
                    <button class="dropdown-item">C++</button>
                    <button class="dropdown-item">Java</button>
                    <button class="dropdown-item">Python</button>
                </div>
            </div>
        </div>
    </body>
</html>
```

### §2.20.2 菜单展开方向(`.drop*`)

在前文中，我们一直给下拉菜单的整体元素赋予`.btn-group`。在此基础上，Bootstrap提供了`.dropup`、`.dropdown`、`.dropstart`、`.dropend`，用于规定菜单的展开方向。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body>
        <script>
            ["dropdown", "dropstart", "dropend", "dropup"].forEach((className) => {
                const htmlString = `
                    <div class="btn-group">
                        <button class="btn btn-primary">${className}</button>
                        <div class="btn-group ${className}">
                            <button class="btn btn-info dropdown-toggle dropdown-toggle-split" data-bs-toggle="dropdown"></button>
                            <div class="dropdown-menu">
                                <button class="dropdown-item">C</button>
                                <button class="dropdown-item">C++</button>
                                <button class="dropdown-item">Java</button>
                                <button class="dropdown-item">Python</button>
                            </div>
                        </div>
                    </div>
                `;
                document.body.innerHTML += htmlString;
            });
        </script>
    </body>
</html>
```

### §2.20.3 菜单分割线(`.dropdown-divider`)

Bootstrap提供了菜单分隔线，只需在众多`.dropdown-item`中插入一个`.dropdown-divider`即可。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body>
        <div class="btn-group">
            <button class="btn btn-primary">课程信息</button>
            <div class="btn-group">
                <button class="btn btn-info dropdown-toggle dropdown-toggle-split" data-bs-toggle="dropdown"></button>
                <div class="dropdown-menu">
                    <button class="dropdown-item">C</button>
                    <button class="dropdown-item">C++</button>
                    <div class="dropdown-divider"></div>
                    <button class="dropdown-item">Java</button>
                    <button class="dropdown-item">Python</button>
                </div>
            </div>
        </div>
    </body>
</html>
```

### §2.20.4 菜单激活和禁用(`.active`/`.disabled`)

> 注意：这里的激活与禁用不是附加在DOM上的属性，而是`class`属性名。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body>
        <div class="btn-group">
            <button class="btn btn-primary">课程信息</button>
            <div class="btn-group">
                <button class="btn btn-info dropdown-toggle dropdown-toggle-split" data-bs-toggle="dropdown"></button>
                <div class="dropdown-menu">
                    <button class="dropdown-item disabled">C(disabled)</button>
                    <button class="dropdown-item">C++</button>
                    <div class="dropdown-divider"></div>
                    <button class="dropdown-item active">Java(active)</button>
                    <button class="dropdown-item">Python</button>
                </div>
            </div>
        </div>
    </body>
</html>
```

### §2.20.5 菜单项对齐方式(`.dropdown-menu-*`)

Bootstrap为`.dropdown-menu`提供了两种菜单项对齐方式：`.dropdown-menu-start`、`.dropdown-menu-end`。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body>
        <script>
            ["dropdown-menu-start", "dropdown-menu-end"].forEach((className) => {
                const htmlString = `
                    <div class="btn-group">
                        <button class="btn btn-primary">${className}</button>
                        <div class="btn-group">
                            <button class="btn btn-info dropdown-toggle dropdown-toggle-split" data-bs-toggle="dropdown"></button>
                            <div class="dropdown-menu ${className}">
                                <button class="dropdown-item">C</button>
                                <button class="dropdown-item">C++</button>
                                <button class="dropdown-item">Java</button>
                                <button class="dropdown-item">Python</button>
                            </div>
                        </div>
                    </div>
                `;
                document.body.innerHTML += htmlString;
            });
        </script>
    </body>
</html>
```

### §2.20.6 菜单位置偏移(`[data-bs-offset]`)

针对`button.dropdown-toggle[data-bs-toggle="dropdown"]`，Bootstrap为其DOM引入了`[data-bs-offset]=“%d,%d”`属性，其属性值的两个数字分别表示水平和垂直方向的偏移量，中间用逗号分隔。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body>
        <script>
            ["0,0", "100,0", "0,100", "100,100"].forEach((className) => {
                const htmlString = `
                    <div class="btn-group">
                        <button class="btn btn-primary">${className}</button>
                        <div class="btn-group">
                            <button class="btn btn-info dropdown-toggle dropdown-toggle-split" data-bs-toggle="dropdown" data-bs-offset="${className}""></button>
                            <div class="dropdown-menu">
                                <button class="dropdown-item">C</button>
                                <button class="dropdown-item">C++</button>
                                <button class="dropdown-item">Java</button>
                                <button class="dropdown-item">Python</button>
                            </div>
                        </div>
                    </div>
                `;
                document.body.innerHTML += htmlString;
            });
        </script>
    </body>
</html>
```

### §2.20.7 垂直菜单(`.btn-group-vertical`)

给菜单入口加上`.btn-group-vertical`，可以让按钮组垂直排列。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body>
        <div class="btn-group-vertical">
            <button class="btn btn-primary">首页</button>
            <div class="btn-group dropend">
                <button class="btn btn-info dropdown-toggle" data-bs-toggle="dropdown">课程</button>
                <div class="dropdown-menu">
                    <button class="dropdown-item">C</button>
                    <button class="dropdown-item">C++</button>
                    <button class="dropdown-item">Java</button>
                    <button class="dropdown-item">Python</button>
                </div>
            </div>
        </div>
    </body>
</html>
```

## §2.21 导航组件(`.nav`)

在Bootstrap中，一个基本的导航组件`ul.nav`由众多`li.nav-item`构成，每个`li.nav-item`包含对应的超链接`.nav-link`：

```html
<ul class="nav">
    <li class="nav-item"><a href="#" class="nav-link">首页</a></li>
    <li class="nav-item"><a href="#" class="nav-link">新闻</a></li>
    <li class="nav-item"><a href="#" class="nav-link">联系我们</a></li>
</ul>
```

```css
.nav {
  --bs-nav-link-padding-x: 1rem;
  --bs-nav-link-padding-y: 0.5rem;
  --bs-nav-link-font-weight: ;
  --bs-nav-link-color: var(--bs-link-color);
  --bs-nav-link-hover-color: var(--bs-link-hover-color);
  --bs-nav-link-disabled-color: var(--bs-secondary-color);
  display: flex;
  flex-wrap: wrap;
  padding-left: 0;
  margin-bottom: 0;
  list-style: none;
}

.nav-link {
  display: block;
  padding: var(--bs-nav-link-padding-y) var(--bs-nav-link-padding-x);
  font-size: var(--bs-nav-link-font-size);
  font-weight: var(--bs-nav-link-font-weight);
  color: var(--bs-nav-link-color);
  text-decoration: none;
  background: none;
  border: 0;
  transition: color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out;
}
```

注意到`.nav`会设置原生CSS为`display: flex;`，因此我们可以使用`justify-content-*`、`flex-column`等弹性布局相关属性，调整导航组件的对齐方式、排列方向等属性。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["justify-content-start", "justify-content-end", "justify-content-center", "flex-column"].forEach((className) => {
                const htmlString = `
                    <ul class="nav ${className} border">
                        <li class="nav-item"><a href="#" class="nav-link">${className}</a></li>
                        <li class="nav-item"><a href="#" class="nav-link">${className}</a></li>
                        <li class="nav-item"><a href="#" class="nav-link">${className}</a></li>
                    </ul>
                `;
                document.body.innerHTML += htmlString;
            });
        </script>
    </body>
</html>
```

### §2.21.1 标签页(`.nav-tabs`)

Bootstrap在`ul.nav`的基础上增加`.nav-tabs`修饰，可以将导航组件转换为标签页的样式。

```css
.nav-tabs {
  --bs-nav-tabs-border-width: var(--bs-border-width);
  --bs-nav-tabs-border-color: var(--bs-border-color);
  --bs-nav-tabs-border-radius: var(--bs-border-radius);
  --bs-nav-tabs-link-hover-border-color: var(--bs-secondary-bg) var(--bs-secondary-bg) var(--bs-border-color);
  --bs-nav-tabs-link-active-color: var(--bs-emphasis-color);
  --bs-nav-tabs-link-active-bg: var(--bs-body-bg);
  --bs-nav-tabs-link-active-border-color: var(--bs-border-color) var(--bs-border-color) var(--bs-body-bg);
  border-bottom: var(--bs-nav-tabs-border-width) solid var(--bs-nav-tabs-border-color);
}
.nav-tabs .nav-link {
  margin-bottom: calc(-1 * var(--bs-nav-tabs-border-width));
  border: var(--bs-nav-tabs-border-width) solid transparent;
  border-top-left-radius: var(--bs-nav-tabs-border-radius);
  border-top-right-radius: var(--bs-nav-tabs-border-radius);
}
.nav-tabs .nav-link:hover, .nav-tabs .nav-link:focus {
  isolation: isolate;
  border-color: var(--bs-nav-tabs-link-hover-border-color);
}
.nav-tabs .nav-link.active,
.nav-tabs .nav-item.show .nav-link {
  color: var(--bs-nav-tabs-link-active-color);
  background-color: var(--bs-nav-tabs-link-active-bg);
  border-color: var(--bs-nav-tabs-link-active-border-color);
}
.nav-tabs .dropdown-menu {
  margin-top: calc(-1 * var(--bs-nav-tabs-border-width));
  border-top-left-radius: 0;
  border-top-right-radius: 0;
}
```

标签页也可以与下拉菜单相结合：

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="nav nav-tabs">
            <li class="nav-item"><a href="#" class="nav-link">首页</a></li>
            <li class="nav-item dropdown">
                <a href="#" class="nav-link dropdown-toggle" data-bs-toggle="dropdown">课程列表</a>
                <div class="dropdown-menu">
                    <div class="dropdown-item">C</div>
                    <div class="dropdown-item">C++</div>
                    <div class="dropdown-item">Java</div>
                    <div class="dropdown-item">Python</div>
                </div>
            </li>
            <li class="nav-item"><a href="#" class="nav-link">关于我们</a></li>
        </ul>
    </body>
</html>
```

### §2.21.2 胶囊式导航(`.nav-pills`)

Bootstrap在`ul.nav`的基础上增加`.nav-pills`修饰，可以将导航组件转换为胶囊式导航的样式。再给`a.nav-link`增加`.active`修饰，可以改变其背景色表示选中状态。

```css
.nav-pills {
  --bs-nav-pills-border-radius: var(--bs-border-radius);
  --bs-nav-pills-link-active-color: #fff;
  --bs-nav-pills-link-active-bg: #0d6efd;
}
.nav-pills .nav-link {
  border-radius: var(--bs-nav-pills-border-radius);
}
.nav-pills .nav-link.active, .nav-pills .show > .nav-link {
  color: var(--bs-nav-pills-link-active-color);
  background-color: var(--bs-nav-pills-link-active-bg);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="nav nav-pills">
            <li class="nav-item"><a href="#" class="nav-link active">首页</a></li>
            <li class="nav-item dropdown">
                <a href="#" class="nav-link dropdown-toggle" data-bs-toggle="dropdown">课程列表</a>
                <div class="dropdown-menu">
                    <div class="dropdown-item">C</div>
                    <div class="dropdown-item">C++</div>
                    <div class="dropdown-item">Java</div>
                    <div class="dropdown-item">Python</div>
                </div>
            </li>
            <li class="nav-item"><a href="#" class="nav-link">关于我们</a></li>
        </ul>
    </body>
</html>
```

### §2.21.3 导航填充(`.nav-fill`)

Bootstrap在`ul.nav`的基础上增加`.nav-fill`修饰，可以让导航组件在水平方向上填满整个空间。

```css
.nav-fill > .nav-link, .nav-fill .nav-item {
  flex: 1 1 auto;
  text-align: center;
}
.nav-justified > .nav-link, .nav-justified .nav-item {
  flex-basis: 0;
  flex-grow: 1;
  text-align: center;
}
.nav-fill .nav-item .nav-link, .nav-justified .nav-item .nav-link {
  width: 100%;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="nav nav-pills nav-fill">
            <li class="nav-item"><a href="#" class="nav-link active">首页</a></li>
            <li class="nav-item dropdown">
                <a href="#" class="nav-link dropdown-toggle" data-bs-toggle="dropdown">课程列表</a>
                <div class="dropdown-menu">
                    <div class="dropdown-item">C</div>
                    <div class="dropdown-item">C++</div>
                    <div class="dropdown-item">Java</div>
                    <div class="dropdown-item">Python</div>
                </div>
            </li>
            <li class="nav-item"><a href="#" class="nav-link">关于我们</a></li>
        </ul>
    </body>
</html>
```

### §2.21.4 选项卡切换(`.tab-*`)

对于`a.dropdown-link`元素，Bootstrap允许其作为触发选项卡切换的元素。众多选项卡`.tan-pane[id]`包裹在一个整体容器`.tab-content`中，然后给`a.dropdown-link`元素添加`[data-bs-toggle="pill", href="#id"]`，使得JavaScript建立触发关系，同时会改变`.dropdown-item`的`.active`状态。

```css
.tab-content > .tab-pane {
  display: none;
}
.tab-content > .active {
  display: block;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="nav nav-pills">
            <li class="nav-item">
                <a class="nav-link" data-bs-toggle="pill" href="#home">首页</a>
            </li>
            <li class="nav-item dropdown">
                <a href="#" class="nav-link dropdown-toggle" data-bs-toggle="dropdown" href="#home">课程列表</a>
                <div class="dropdown-menu">
                    <a class="dropdown-item" data-bs-toggle="pill" href="#c">C</a>
                    <a class="dropdown-item" data-bs-toggle="pill" href="#c++">C++</a>
                    <a class="dropdown-item" data-bs-toggle="pill" href="#java">Java</a>
                    <a class="dropdown-item" data-bs-toggle="pill" href="#python">Python</a>
                </div>
            </li>
            <li class="nav-item">
                <a href="#about" class="nav-link" data-bs-toggle="pill">关于我们</a>
            </li>
        </ul>
        <div class="tab-content">
            <div class="tab-pane" id="home">这是首页内容</div>
            <div class="tab-pane" id="c">这是C内容</div>
            <div class="tab-pane" id="c++">这是C++内容</div>
            <div class="tab-pane" id="java">这是Java内容</div>
            <div class="tab-pane" id="python">这是Python内容</div>
            <div class="tab-pane" id="about">这是关于我们内容</div>
        </div>
    </body>
</html>
```

### §2.21.5 导航项展开排列(`.nav-justified`)

`.nav-justified`可以使`.nav`中的`.nav-item`均匀展开排列。

```css
.nav-justified > .nav-link,
.nav-justified .nav-item {
  flex-basis: 0;
  flex-grow: 1;
  text-align: center;
}

.nav-fill .nav-item .nav-link,
.nav-justified .nav-item .nav-link {
  width: 100%;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="nav nav-tabs nav-justified">
            <li class="nav-item"><a href="#" class="nav-link">首页</a></li>
            <li class="nav-item dropdown">
                <a href="#" class="nav-link dropdown-toggle" data-bs-toggle="dropdown">课程列表</a>
                <div class="dropdown-menu">
                    <div class="dropdown-item">C</div>
                    <div class="dropdown-item">C++</div>
                    <div class="dropdown-item">Java</div>
                    <div class="dropdown-item">Python</div>
                </div>
            </li>
            <li class="nav-item"><a href="#" class="nav-link">关于我们</a></li>
        </ul>
    </body>
</html>
```

## §2.22 警告框(`.alert-*`)

类似于Github对Markdown的扩展语法`![warning]`，Bootstrap也提供了类似的不同颜色的警告框。

```css
.alert {
  --bs-alert-bg: transparent;
  --bs-alert-padding-x: 1rem;
  --bs-alert-padding-y: 1rem;
  --bs-alert-margin-bottom: 1rem;
  --bs-alert-color: inherit;
  --bs-alert-border-color: transparent;
  --bs-alert-border: var(--bs-border-width) solid var(--bs-alert-border-color);
  --bs-alert-border-radius: var(--bs-border-radius);
  --bs-alert-link-color: inherit;
  position: relative;
  padding: var(--bs-alert-padding-y) var(--bs-alert-padding-x);
  margin-bottom: var(--bs-alert-margin-bottom);
  color: var(--bs-alert-color);
  background-color: var(--bs-alert-bg);
  border: var(--bs-alert-border);
  border-radius: var(--bs-alert-border-radius);
}
.alert-heading {
  color: inherit;
}
.alert-link {
  font-weight: 700;
  color: var(--bs-alert-link-color);
}
.alert-dismissible {
  padding-right: 3rem;
}
.alert-dismissible .btn-close {
  position: absolute;
  top: 0;
  right: 0;
  z-index: 2;
  padding: 1.25rem 1rem;
}
.alert-primary {
  --bs-alert-color: var(--bs-primary-text-emphasis);
  --bs-alert-bg: var(--bs-primary-bg-subtle);
  --bs-alert-border-color: var(--bs-primary-border-subtle);
  --bs-alert-link-color: var(--bs-primary-text-emphasis);
}
.alert-secondary {
  --bs-alert-color: var(--bs-secondary-text-emphasis);
  --bs-alert-bg: var(--bs-secondary-bg-subtle);
  --bs-alert-border-color: var(--bs-secondary-border-subtle);
  --bs-alert-link-color: var(--bs-secondary-text-emphasis);
}
.alert-success {
  --bs-alert-color: var(--bs-success-text-emphasis);
  --bs-alert-bg: var(--bs-success-bg-subtle);
  --bs-alert-border-color: var(--bs-success-border-subtle);
  --bs-alert-link-color: var(--bs-success-text-emphasis);
}
.alert-info {
  --bs-alert-color: var(--bs-info-text-emphasis);
  --bs-alert-bg: var(--bs-info-bg-subtle);
  --bs-alert-border-color: var(--bs-info-border-subtle);
  --bs-alert-link-color: var(--bs-info-text-emphasis);
}
.alert-warning {
  --bs-alert-color: var(--bs-warning-text-emphasis);
  --bs-alert-bg: var(--bs-warning-bg-subtle);
  --bs-alert-border-color: var(--bs-warning-border-subtle);
  --bs-alert-link-color: var(--bs-warning-text-emphasis);
}
.alert-danger {
  --bs-alert-color: var(--bs-danger-text-emphasis);
  --bs-alert-bg: var(--bs-danger-bg-subtle);
  --bs-alert-border-color: var(--bs-danger-border-subtle);
  --bs-alert-link-color: var(--bs-danger-text-emphasis);
}
.alert-light {
  --bs-alert-color: var(--bs-light-text-emphasis);
  --bs-alert-bg: var(--bs-light-bg-subtle);
  --bs-alert-border-color: var(--bs-light-border-subtle);
  --bs-alert-link-color: var(--bs-light-text-emphasis);
}
.alert-dark {
  --bs-alert-color: var(--bs-dark-text-emphasis);
  --bs-alert-bg: var(--bs-dark-bg-subtle);
  --bs-alert-border-color: var(--bs-dark-border-subtle);
  --bs-alert-link-color: var(--bs-dark-text-emphasis);
}
```

```css
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["纯alert", "alert-success", "alert-info", "alert-warning", "alert-danger", "alert-primary", "alert-secondary", "alert-dark", "alert-light"].forEach((className) => {
                const htmlString = `
                    <div class="alert ${className}">${className}</div>
                `;
                document.body.innerHTML += htmlString;
            });
        </script>
    </body>
</html>
```

### §2.22.1 警告链接(`.alert-link`)

Bootstrap对警告框中的超链接`<a>`做了额外的样式优化。

```css
.alert-link {
  font-weight: 700;
  color: var(--bs-alert-link-color);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["纯alert", "alert-success", "alert-info", "alert-warning", "alert-danger", "alert-primary", "alert-secondary", "alert-dark", "alert-light"].forEach((className) => {
                const htmlString = `
                    <div class="alert ${className}">这是一个引用:<a class="alert-link" href="#">${className}</a></div>
                `;
                document.body.innerHTML += htmlString;
            });
        </script>
    </body>
</html>
```

### §2.22.2 关闭警告框(`.alert-dismissible`)

Bootstrap允许用户关闭警告框。需要给警告框`div.alert`增加`.alert-dismissible`属性，并且在内部增加`<button class="btn-close" data-bs-dismiss="alert">`关闭按钮。

```css
.alert-dismissible {
  padding-right: 3rem;
}
.alert-dismissible .btn-close {
  position: absolute;
  top: 0;
  right: 0;
  z-index: 2;
  padding: 1.25rem 1rem;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["纯alert", "alert-success", "alert-info", "alert-warning", "alert-danger", "alert-primary", "alert-secondary", "alert-dark", "alert-light"].forEach((className) => {
                const htmlString = `
                    <div class="alert ${className} alert-dismissible">
                        ${className}
                        <button class="btn-close" data-bs-dismiss="alert"></button>
                    </div>
                `;
                document.body.innerHTML += htmlString;
            });
        </script>
    </body>
</html>
```

## §2.23 徽章(`.badge`)

徽章的作用类似于标签，Bootstrap规定徽章通常使用`<span>`标签，其背景颜色由`.bg-*`指定。

```css
.badge {
  --bs-badge-padding-x: 0.65em;
  --bs-badge-padding-y: 0.35em;
  --bs-badge-font-size: 0.75em;
  --bs-badge-font-weight: 700;
  --bs-badge-color: #fff;
  --bs-badge-border-radius: var(--bs-border-radius);
  display: inline-block;
  padding: var(--bs-badge-padding-y) var(--bs-badge-padding-x);
  font-size: var(--bs-badge-font-size);
  font-weight: var(--bs-badge-font-weight);
  line-height: 1;
  color: var(--bs-badge-color);
  text-align: center;
  white-space: nowrap;
  vertical-align: baseline;
  border-radius: var(--bs-badge-border-radius);
}
.badge:empty {
  display: none;
}
.btn .badge {
  position: relative;
  top: -1px;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["bg-primary", "bg-secondary", "bg-success", "bg-danger", "bg-warning", "bg-info", "bg-light", "bg-dark"].forEach((className) => {
                const htmlString = `
                    <span class="badge ${className}">${className}</span>
                `;
                document.body.innerHTML += htmlString;
            });
        </script>
    </body>
</html>
```

## §2.24 进度条(`.progress`/`.progress-bar`)

一个完整的进度条可以拆分成两部分：外面的槽`.progress`和里面的条`.progress-bar`。多个条可以将进度加起来。

```css
.progress, .progress-stacked {
  --bs-progress-height: 1rem;
  --bs-progress-font-size: 0.75rem;
  --bs-progress-bg: var(--bs-secondary-bg);
  --bs-progress-border-radius: var(--bs-border-radius);
  --bs-progress-box-shadow: var(--bs-box-shadow-inset);
  --bs-progress-bar-color: #fff;
  --bs-progress-bar-bg: #0d6efd;
  --bs-progress-bar-transition: width 0.6s ease;
  display: flex;
  height: var(--bs-progress-height);
  overflow: hidden;
  font-size: var(--bs-progress-font-size);
  background-color: var(--bs-progress-bg);
  border-radius: var(--bs-progress-border-radius);
}
.progress-bar {
  display: flex;
  flex-direction: column;
  justify-content: center;
  overflow: hidden;
  color: var(--bs-progress-bar-color);
  text-align: center;
  white-space: nowrap;
  background-color: var(--bs-progress-bar-bg);
  transition: var(--bs-progress-bar-transition);
}
@media (prefers-reduced-motion: reduce) {
  .progress-bar {
    transition: none;
  }
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="progress">
            <div class="progress-bar w-25">25%</div>
            <div class="progress-bar w-50 bg-secondary">50%</div>
        </div>
    </body>
</html>
```

### §2.24.1 条纹进度条(`.progress-bar-striped`)

Bootstrap给`.progress-bar`提供了`.progress-bar-striped`属性，使其带有条纹样式。

```css
.progress-bar-striped {
  background-image: linear-gradient(45deg, rgba(255, 255, 255, 0.15) 25%, transparent 25%, transparent 50%, rgba(255, 255, 255, 0.15) 50%, rgba(255, 255, 255, 0.15) 75%, transparent 75%, transparent);
  background-size: var(--bs-progress-height) var(--bs-progress-height);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="progress">
            <div class="progress-bar w-25 progress-bar-striped">25%</div>
            <div class="progress-bar w-50 progress-bar-striped bg-secondary">50%</div>
        </div>
        <!-- <script>
            ["bg-primary", "bg-secondary", "bg-success", "bg-danger", "bg-warning", "bg-info", "bg-light", "bg-dark"].forEach((className) => {
                const htmlString = `
                    <span class="badge ${className}">${className}</span>
                `;
                document.body.innerHTML += htmlString;
            });
        </script> -->
    </body>
</html>
```

### §2.24.2 动画进度条(`.progress-bar-animated`)

Bootstrap给`.progress-bar.progress-bar-striped`提供了`.progress-bar-animated`属性，使条纹样式带有动画效果。

```css
.progress-bar-animated {
  animation: 1s linear infinite progress-bar-stripes;
}
@media (prefers-reduced-motion: reduce) {
  .progress-bar-animated {
    animation: none;
  }
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="progress">
            <div class="progress-bar w-25 progress-bar-striped progress-bar-animated">25%</div>
            <div class="progress-bar w-50 progress-bar-striped progress-bar-animated bg-secondary">50%</div>
        </div>
    </body>
</html>
```

## §2.25 导航栏(`.navbar`)

Bootstrap使用`.navbar`定义导航栏，并通过`.navbar-expand-<BREAK_POINT>`定义响应式布局。导航栏内还可以包含以下组件：

| 属性名                         | 作用                         |
| ------------------------------ | ---------------------------- |
| `.navbar-brand`                | LOGO                         |
| `.navbar-nav`                  | 下拉菜单                     |
| `.navbar-toggler`              | 折叠插件与切换导航           |
| `.navbar-text`                 | 优化垂直对齐、水平间距的文本 |
| `.navbar-collapse`/`.collapse` | 折叠的导航栏内容             |

```css
.navbar {
  --bs-navbar-padding-x: 0;
  --bs-navbar-padding-y: 0.5rem;
  --bs-navbar-color: rgba(var(--bs-emphasis-color-rgb), 0.65);
  --bs-navbar-hover-color: rgba(var(--bs-emphasis-color-rgb), 0.8);
  --bs-navbar-disabled-color: rgba(var(--bs-emphasis-color-rgb), 0.3);
  --bs-navbar-active-color: rgba(var(--bs-emphasis-color-rgb), 1);
  --bs-navbar-brand-padding-y: 0.3125rem;
  --bs-navbar-brand-margin-end: 1rem;
  --bs-navbar-brand-font-size: 1.25rem;
  --bs-navbar-brand-color: rgba(var(--bs-emphasis-color-rgb), 1);
  --bs-navbar-brand-hover-color: rgba(var(--bs-emphasis-color-rgb), 1);
  --bs-navbar-nav-link-padding-x: 0.5rem;
  --bs-navbar-toggler-padding-y: 0.25rem;
  --bs-navbar-toggler-padding-x: 0.75rem;
  --bs-navbar-toggler-font-size: 1.25rem;
  --bs-navbar-toggler-icon-bg: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 30 30'%3e%3cpath stroke='rgba%2833, 37, 41, 0.75%29' stroke-linecap='round' stroke-miterlimit='10' stroke-width='2' d='M4 7h22M4 15h22M4 23h22'/%3e%3c/svg%3e");
  --bs-navbar-toggler-border-color: rgba(var(--bs-emphasis-color-rgb), 0.15);
  --bs-navbar-toggler-border-radius: var(--bs-border-radius);
  --bs-navbar-toggler-focus-width: 0.25rem;
  --bs-navbar-toggler-transition: box-shadow 0.15s ease-in-out;
  position: relative;
  display: flex;
  flex-wrap: wrap;
  align-items: center;
  justify-content: space-between;
  padding: var(--bs-navbar-padding-y) var(--bs-navbar-padding-x);
}
.navbar > .container,
.navbar > .container-fluid,
.navbar > .container-sm,
.navbar > .container-md,
.navbar > .container-lg,
.navbar > .container-xl,
.navbar > .container-xxl {
  display: flex;
  flex-wrap: inherit;
  align-items: center;
  justify-content: space-between;
}
.navbar-brand {
  padding-top: var(--bs-navbar-brand-padding-y);
  padding-bottom: var(--bs-navbar-brand-padding-y);
  margin-right: var(--bs-navbar-brand-margin-end);
  font-size: var(--bs-navbar-brand-font-size);
  color: var(--bs-navbar-brand-color);
  text-decoration: none;
  white-space: nowrap;
}
.navbar-brand:hover, .navbar-brand:focus {
  color: var(--bs-navbar-brand-hover-color);
}
.navbar-nav {
  --bs-nav-link-padding-x: 0;
  --bs-nav-link-padding-y: 0.5rem;
  --bs-nav-link-font-weight: ;
  --bs-nav-link-color: var(--bs-navbar-color);
  --bs-nav-link-hover-color: var(--bs-navbar-hover-color);
  --bs-nav-link-disabled-color: var(--bs-navbar-disabled-color);
  display: flex;
  flex-direction: column;
  padding-left: 0;
  margin-bottom: 0;
  list-style: none;
}
.navbar-nav .nav-link.active, .navbar-nav .nav-link.show {
  color: var(--bs-navbar-active-color);
}
.navbar-nav .dropdown-menu {
  position: static;
}
.navbar-text {
  padding-top: 0.5rem;
  padding-bottom: 0.5rem;
  color: var(--bs-navbar-color);
}
.navbar-text a,
.navbar-text a:hover,
.navbar-text a:focus {
  color: var(--bs-navbar-active-color);
}
.navbar-collapse {
  flex-basis: 100%;
  flex-grow: 1;
  align-items: center;
}
.navbar-toggler {
  padding: var(--bs-navbar-toggler-padding-y) var(--bs-navbar-toggler-padding-x);
  font-size: var(--bs-navbar-toggler-font-size);
  line-height: 1;
  color: var(--bs-navbar-color);
  background-color: transparent;
  border: var(--bs-border-width) solid var(--bs-navbar-toggler-border-color);
  border-radius: var(--bs-navbar-toggler-border-radius);
  transition: var(--bs-navbar-toggler-transition);
}
@media (prefers-reduced-motion: reduce) {
  .navbar-toggler {
    transition: none;
  }
}
.navbar-toggler:hover {
  text-decoration: none;
}
.navbar-toggler:focus {
  text-decoration: none;
  outline: 0;
  box-shadow: 0 0 0 var(--bs-navbar-toggler-focus-width);
}
.navbar-toggler-icon {
  display: inline-block;
  width: 1.5em;
  height: 1.5em;
  vertical-align: middle;
  background-image: var(--bs-navbar-toggler-icon-bg);
  background-repeat: no-repeat;
  background-position: center;
  background-size: 100%;
}
.navbar-nav-scroll {
  max-height: var(--bs-scroll-height, 75vh);
  overflow-y: auto;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <nav class="navbar navbar-expand-md bg-light">
            <a href="#" class="navbar-brand">
                <img src="https://www.baidu.com/favicon.ico" alt="">
                <span>百度</span>
            </a>
            <button class="navbar-toggler" data-bs-toggle="collapse" data-bs-target="#collapse">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="collapse">
                <ul class="navbar-nav">
                    <li class="nav-item active">
                        <a class="nav-link " href="#">首页</a>
                    </li>
                    <li class="nav-item dropdown">
                        <a class="nav-link dropdown-toggle" href="#" data-bs-toggle="dropdown">课程列表</a>
                        <div class="dropdown-menu">
                            <a class="dropdown-item" href="#">C</a>
                            <a class="dropdown-item" href="#">C++</a>
                            <a class="dropdown-item" href="#">Java</a>
                            <a class="dropdown-item" href="#">Python</a>
                        </div>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link disabled" href="#">关于我们</a>
                    </li>
                </ul>
            </div>
            <span class="navbar-text">当前时间: 2024/01/21</span>
        </nav>
    </body>
</html>
```

### §2.25.1 导航栏定位(`.fixed-*`)

Bootstrap提供了两种用于导航栏定位的属性：`.fixed-top`和`.fixed-bottom`。

```css
.fixed-top {
  position: fixed;
  top: 0;
  right: 0;
  left: 0;
  z-index: 1030;
}
.fixed-bottom {
  position: fixed;
  right: 0;
  bottom: 0;
  left: 0;
  z-index: 1030;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["fixed-top", "fixed-bottom"].forEach((className) => {
                document.body.innerHTML += `
                    <nav class="navbar navbar-expand-md bg-light ${className}">
                        <a href="#" class="navbar-brand">
                            <img src="https://www.baidu.com/favicon.ico" alt="">
                            <span>百度</span>
                        </a>
                        <button class="navbar-toggler" data-bs-toggle="collapse" data-bs-target="#collapse">
                            <span class="navbar-toggler-icon"></span>
                        </button>
                        <div class="collapse navbar-collapse" id="collapse">
                            <ul class="navbar-nav">
                                <li class="nav-item active">
                                    <a class="nav-link " href="#">首页</a>
                                </li>
                                <li class="nav-item dropdown">
                                    <a class="nav-link dropdown-toggle" href="#" data-bs-toggle="dropdown">课程列表</a>
                                    <div class="dropdown-menu">
                                        <a class="dropdown-item" href="#">C</a>
                                        <a class="dropdown-item" href="#">C++</a>
                                        <a class="dropdown-item" href="#">Java</a>
                                        <a class="dropdown-item" href="#">Python</a>
                                    </div>
                                </li>
                                <li class="nav-item">
                                    <a class="nav-link disabled" href="#">关于我们</a>
                                </li>
                            </ul>
                        </div>
                        <span class="navbar-text">当前时间: 2024/01/21</span>
                    </nav>
                `;
            });
        </script>
    </body>
</html>
```

### §2.25.2 导航栏颜色(`.navbar-dark`)

Bootstrap在`.navbar`的基础上，引入了`.navbar-dark`属性用于重新更改导航栏颜色为暗色模式，需要配合`.bg-*`一起使用。

```css
.navbar-dark,
.navbar[data-bs-theme=dark] {
  --bs-navbar-color: rgba(255, 255, 255, 0.55);
  --bs-navbar-hover-color: rgba(255, 255, 255, 0.75);
  --bs-navbar-disabled-color: rgba(255, 255, 255, 0.25);
  --bs-navbar-active-color: #fff;
  --bs-navbar-brand-color: #fff;
  --bs-navbar-brand-hover-color: #fff;
  --bs-navbar-toggler-border-color: rgba(255, 255, 255, 0.1);
  --bs-navbar-toggler-icon-bg: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 30 30'%3e%3cpath stroke='rgba%28255, 255, 255, 0.55%29' stroke-linecap='round' stroke-miterlimit='10' stroke-width='2' d='M4 7h22M4 15h22M4 23h22'/%3e%3c/svg%3e");
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["navbar bg-light", "navbar-dark bg-dark"].forEach((className) => {
                document.body.innerHTML += `
                    <nav class="navbar navbar-expand-md ${className}">
                        <a href="#" class="navbar-brand">
                            <img src="https://www.baidu.com/favicon.ico" alt="">
                            <span>百度</span>
                        </a>
                        <button class="navbar-toggler" data-bs-toggle="collapse" data-bs-target="#collapse">
                            <span class="navbar-toggler-icon"></span>
                        </button>
                        <div class="collapse navbar-collapse" id="collapse">
                            <ul class="navbar-nav">
                                <li class="nav-item active">
                                    <a class="nav-link " href="#">首页</a>
                                </li>
                                <li class="nav-item dropdown">
                                    <a class="nav-link dropdown-toggle" href="#" data-bs-toggle="dropdown">课程列表</a>
                                    <div class="dropdown-menu">
                                        <a class="dropdown-item" href="#">C</a>
                                        <a class="dropdown-item" href="#">C++</a>
                                        <a class="dropdown-item" href="#">Java</a>
                                        <a class="dropdown-item" href="#">Python</a>
                                    </div>
                                </li>
                                <li class="nav-item">
                                    <a class="nav-link disabled" href="#">关于我们</a>
                                </li>
                            </ul>
                        </div>
                        <span class="navbar-text">当前时间: 2024/01/21</span>
                    </nav>
                `;
            })
        </script>
    </body>
</html>
```

## §2.26 列表组(`.list-group`)

Bootstrap在`<ul>`元素的基础上，设计了列表组样式。一个列表组`ul.list-group`包含了若干列表元素`li.list-group-item`/`li.list-group-action`，分别指定了`li`和`li:active`的样式。同理，`.list-group-item`也支持`.active`和`.disabled`的修饰。

```css
.list-group {
  --bs-list-group-color: var(--bs-body-color);
  --bs-list-group-bg: var(--bs-body-bg);
  --bs-list-group-border-color: var(--bs-border-color);
  --bs-list-group-border-width: var(--bs-border-width);
  --bs-list-group-border-radius: var(--bs-border-radius);
  --bs-list-group-item-padding-x: 1rem;
  --bs-list-group-item-padding-y: 0.5rem;
  --bs-list-group-action-color: var(--bs-secondary-color);
  --bs-list-group-action-hover-color: var(--bs-emphasis-color);
  --bs-list-group-action-hover-bg: var(--bs-tertiary-bg);
  --bs-list-group-action-active-color: var(--bs-body-color);
  --bs-list-group-action-active-bg: var(--bs-secondary-bg);
  --bs-list-group-disabled-color: var(--bs-secondary-color);
  --bs-list-group-disabled-bg: var(--bs-body-bg);
  --bs-list-group-active-color: #fff;
  --bs-list-group-active-bg: #0d6efd;
  --bs-list-group-active-border-color: #0d6efd;
  display: flex;
  flex-direction: column;
  padding-left: 0;
  margin-bottom: 0;
  border-radius: var(--bs-list-group-border-radius);
}
.list-group-item {
  position: relative;
  display: block;
  padding: var(--bs-list-group-item-padding-y) var(--bs-list-group-item-padding-x);
  color: var(--bs-list-group-color);
  text-decoration: none;
  background-color: var(--bs-list-group-bg);
  border: var(--bs-list-group-border-width) solid var(--bs-list-group-border-color);
}
.list-group-item + .list-group-item {
  border-top-width: 0;
}
.list-group-item + .list-group-item.active {
  margin-top: calc(-1 * var(--bs-list-group-border-width));
  border-top-width: var(--bs-list-group-border-width);
}
.list-group-item-action {
  width: 100%;
  color: var(--bs-list-group-action-color);
  text-align: inherit;
}
.list-group-item-action:hover, .list-group-item-action:focus {
  z-index: 1;
  color: var(--bs-list-group-action-hover-color);
  text-decoration: none;
  background-color: var(--bs-list-group-action-hover-bg);
}
.list-group-item-action:active {
  color: var(--bs-list-group-action-active-color);
  background-color: var(--bs-list-group-action-active-bg);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="list-group">
            <li class="list-group-item">列表项</li>
            <li class="list-group-item list-group-item-action">列表项(有:hover效果)</li>
            <li class="list-group-item active">列表项(active)</li>
            <li class="list-group-item disabled">列表项(disabled)</li>
        </ul>
    </body>
</html>
```

### §2.26.1 无边框列表组(`.list-group-flush`)

在`ul.list-group`的基础上，Bootstrap提供了`ul.list-group.list-group-flush`，用于消除列表组的边框和圆角。

```css
.list-group-flush {
  border-radius: 0;
}
.list-group-flush > .list-group-item {
  border-width: 0 0 var(--bs-list-group-border-width);
}
.list-group-flush > .list-group-item:last-child {
  border-bottom-width: 0;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="list-group list-group-flush">
            <li class="list-group-item">列表项</li>
            <li class="list-group-item list-group-item-action">列表项(有:hover效果)</li>
            <li class="list-group-item active">列表项(active)</li>
            <li class="list-group-item disabled">列表项(disabled)</li>
        </ul>
    </body>
</html>
```

### §2.26.2 列表项颜色(`.list-group-item-*`)

```css
.list-group-item-primary {
  --bs-list-group-color: var(--bs-primary-text-emphasis);
  --bs-list-group-bg: var(--bs-primary-bg-subtle);
  --bs-list-group-border-color: var(--bs-primary-border-subtle);
  --bs-list-group-action-hover-color: var(--bs-emphasis-color);
  --bs-list-group-action-hover-bg: var(--bs-primary-border-subtle);
  --bs-list-group-action-active-color: var(--bs-emphasis-color);
  --bs-list-group-action-active-bg: var(--bs-primary-border-subtle);
  --bs-list-group-active-color: var(--bs-primary-bg-subtle);
  --bs-list-group-active-bg: var(--bs-primary-text-emphasis);
  --bs-list-group-active-border-color: var(--bs-primary-text-emphasis);
}
.list-group-item-secondary {
  --bs-list-group-color: var(--bs-secondary-text-emphasis);
  --bs-list-group-bg: var(--bs-secondary-bg-subtle);
  --bs-list-group-border-color: var(--bs-secondary-border-subtle);
  --bs-list-group-action-hover-color: var(--bs-emphasis-color);
  --bs-list-group-action-hover-bg: var(--bs-secondary-border-subtle);
  --bs-list-group-action-active-color: var(--bs-emphasis-color);
  --bs-list-group-action-active-bg: var(--bs-secondary-border-subtle);
  --bs-list-group-active-color: var(--bs-secondary-bg-subtle);
  --bs-list-group-active-bg: var(--bs-secondary-text-emphasis);
  --bs-list-group-active-border-color: var(--bs-secondary-text-emphasis);
}
.list-group-item-success {
  --bs-list-group-color: var(--bs-success-text-emphasis);
  --bs-list-group-bg: var(--bs-success-bg-subtle);
  --bs-list-group-border-color: var(--bs-success-border-subtle);
  --bs-list-group-action-hover-color: var(--bs-emphasis-color);
  --bs-list-group-action-hover-bg: var(--bs-success-border-subtle);
  --bs-list-group-action-active-color: var(--bs-emphasis-color);
  --bs-list-group-action-active-bg: var(--bs-success-border-subtle);
  --bs-list-group-active-color: var(--bs-success-bg-subtle);
  --bs-list-group-active-bg: var(--bs-success-text-emphasis);
  --bs-list-group-active-border-color: var(--bs-success-text-emphasis);
}
.list-group-item-info {
  --bs-list-group-color: var(--bs-info-text-emphasis);
  --bs-list-group-bg: var(--bs-info-bg-subtle);
  --bs-list-group-border-color: var(--bs-info-border-subtle);
  --bs-list-group-action-hover-color: var(--bs-emphasis-color);
  --bs-list-group-action-hover-bg: var(--bs-info-border-subtle);
  --bs-list-group-action-active-color: var(--bs-emphasis-color);
  --bs-list-group-action-active-bg: var(--bs-info-border-subtle);
  --bs-list-group-active-color: var(--bs-info-bg-subtle);
  --bs-list-group-active-bg: var(--bs-info-text-emphasis);
  --bs-list-group-active-border-color: var(--bs-info-text-emphasis);
}
.list-group-item-warning {
  --bs-list-group-color: var(--bs-warning-text-emphasis);
  --bs-list-group-bg: var(--bs-warning-bg-subtle);
  --bs-list-group-border-color: var(--bs-warning-border-subtle);
  --bs-list-group-action-hover-color: var(--bs-emphasis-color);
  --bs-list-group-action-hover-bg: var(--bs-warning-border-subtle);
  --bs-list-group-action-active-color: var(--bs-emphasis-color);
  --bs-list-group-action-active-bg: var(--bs-warning-border-subtle);
  --bs-list-group-active-color: var(--bs-warning-bg-subtle);
  --bs-list-group-active-bg: var(--bs-warning-text-emphasis);
  --bs-list-group-active-border-color: var(--bs-warning-text-emphasis);
}
.list-group-item-danger {
  --bs-list-group-color: var(--bs-danger-text-emphasis);
  --bs-list-group-bg: var(--bs-danger-bg-subtle);
  --bs-list-group-border-color: var(--bs-danger-border-subtle);
  --bs-list-group-action-hover-color: var(--bs-emphasis-color);
  --bs-list-group-action-hover-bg: var(--bs-danger-border-subtle);
  --bs-list-group-action-active-color: var(--bs-emphasis-color);
  --bs-list-group-action-active-bg: var(--bs-danger-border-subtle);
  --bs-list-group-active-color: var(--bs-danger-bg-subtle);
  --bs-list-group-active-bg: var(--bs-danger-text-emphasis);
  --bs-list-group-active-border-color: var(--bs-danger-text-emphasis);
}
.list-group-item-light {
  --bs-list-group-color: var(--bs-light-text-emphasis);
  --bs-list-group-bg: var(--bs-light-bg-subtle);
  --bs-list-group-border-color: var(--bs-light-border-subtle);
  --bs-list-group-action-hover-color: var(--bs-emphasis-color);
  --bs-list-group-action-hover-bg: var(--bs-light-border-subtle);
  --bs-list-group-action-active-color: var(--bs-emphasis-color);
  --bs-list-group-action-active-bg: var(--bs-light-border-subtle);
  --bs-list-group-active-color: var(--bs-light-bg-subtle);
  --bs-list-group-active-bg: var(--bs-light-text-emphasis);
  --bs-list-group-active-border-color: var(--bs-light-text-emphasis);
}
.list-group-item-dark {
  --bs-list-group-color: var(--bs-dark-text-emphasis);
  --bs-list-group-bg: var(--bs-dark-bg-subtle);
  --bs-list-group-border-color: var(--bs-dark-border-subtle);
  --bs-list-group-action-hover-color: var(--bs-emphasis-color);
  --bs-list-group-action-hover-bg: var(--bs-dark-border-subtle);
  --bs-list-group-action-active-color: var(--bs-emphasis-color);
  --bs-list-group-action-active-bg: var(--bs-dark-border-subtle);
  --bs-list-group-active-color: var(--bs-dark-bg-subtle);
  --bs-list-group-active-bg: var(--bs-dark-text-emphasis);
  --bs-list-group-active-border-color: var(--bs-dark-text-emphasis);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["list-group-item-success", "list-group-item-secondary", "list-group-item-info", "list-group-item-warning", "list-group-item-danger", "list-group-item-light", "list-group-item-dark"].forEach((className) => {
                document.body.innerHTML += `
                    <ul class="list-group m-2">
                        <li class="list-group-item">列表项</li>
                        <li class="list-group-item ${className}">${className}</li>
                        <li class="list-group-item">列表项</li>
                    </ul>
                `;
            })
        </script>
    </body>
</html>
```

### §2.26.3 水平排列列表组(`.list-group-horizontal`)

Bootstrap在`ul.list-group`的基础上，提供了`.list-group-horizontal`属性，用于设置水平排列的列表组。

```css
.list-group-horizontal {
  flex-direction: row;
}
.list-group-horizontal > .list-group-item:first-child:not(:last-child) {
  border-bottom-left-radius: var(--bs-list-group-border-radius);
  border-top-right-radius: 0;
}
.list-group-horizontal > .list-group-item:last-child:not(:first-child) {
  border-top-right-radius: var(--bs-list-group-border-radius);
  border-bottom-left-radius: 0;
}
.list-group-horizontal > .list-group-item.active {
  margin-top: 0;
}
.list-group-horizontal > .list-group-item + .list-group-item {
  border-top-width: var(--bs-list-group-border-width);
  border-left-width: 0;
}
.list-group-horizontal > .list-group-item + .list-group-item.active {
  margin-left: calc(-1 * var(--bs-list-group-border-width));
  border-left-width: var(--bs-list-group-border-width);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="list-group list-group-horizontal">
            <li class="list-group-item list-group-item-action">列表项</li>
            <li class="list-group-item list-group-item-action">列表项(有:hover效果)</li>
            <li class="list-group-item list-group-item-action active">列表项(active)</li>
            <li class="list-group-item list-group-item-action disabled">列表项(disabled)</li>
        </ul>
    </body>
</html>
```

## §2.27 面包屑(`.breadcrumb`)

面包屑本质上是一种分隔符，例如文件路径中的路径分隔符`/`就可以看作是面包屑。Bootstrap规定，一个文件路径整体为`.breadcrumb`，其中的文件夹都是`.breadcrumb-item`。

```css
.breadcrumb {
  --bs-breadcrumb-padding-x: 0;
  --bs-breadcrumb-padding-y: 0;
  --bs-breadcrumb-margin-bottom: 1rem;
  --bs-breadcrumb-bg: ;
  --bs-breadcrumb-border-radius: ;
  --bs-breadcrumb-divider-color: var(--bs-secondary-color);
  --bs-breadcrumb-item-padding-x: 0.5rem;
  --bs-breadcrumb-item-active-color: var(--bs-secondary-color);
  display: flex;
  flex-wrap: wrap;
  padding: var(--bs-breadcrumb-padding-y) var(--bs-breadcrumb-padding-x);
  margin-bottom: var(--bs-breadcrumb-margin-bottom);
  font-size: var(--bs-breadcrumb-font-size);
  list-style: none;
  background-color: var(--bs-breadcrumb-bg);
  border-radius: var(--bs-breadcrumb-border-radius);
}
.breadcrumb-item + .breadcrumb-item {
  padding-left: var(--bs-breadcrumb-item-padding-x);
}
.breadcrumb-item + .breadcrumb-item::before {
  float: left;
  padding-right: var(--bs-breadcrumb-item-padding-x);
  color: var(--bs-breadcrumb-divider-color);
  content: var(--bs-breadcrumb-divider, "/") /* rtl: var(--bs-breadcrumb-divider, "/") */;
}
.breadcrumb-item.active {
  color: var(--bs-breadcrumb-item-active-color);
}
```

Bootstrap默认使用的分隔符为`/`。我们也可以手动更改`.breadcrumb-item + .breadcrumb-item::before { content: "/" }`中的`content`属性值，来手动设置分隔符。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ol class="breadcrumb">
            <li class="breadcrumb-item">新闻</li>
            <li class="breadcrumb-item">国际新闻</li>
            <li class="breadcrumb-item">俄乌局势</li>
        </ol>
    </body>
</html>
```

## §2.28 分页按钮组(`.pagination`)

如果一个网页内容过多，我们通常会选择分页处理，并给用户提供一个用于切换分页的按钮组。在之前的学习中，我们曾经手动使用按钮组实现了分页效果。其实Bootstrap已经做了分页按钮的样式。只需给`<ul>`增加`.pagination`属性，并在其中包含一系列`<li class="page-item">`，每个`li.page-item`包含一个`a.page-link`即可。

```css
.pagination {
  --bs-pagination-padding-x: 0.75rem;
  --bs-pagination-padding-y: 0.375rem;
  --bs-pagination-font-size: 1rem;
  --bs-pagination-color: var(--bs-link-color);
  --bs-pagination-bg: var(--bs-body-bg);
  --bs-pagination-border-width: var(--bs-border-width);
  --bs-pagination-border-color: var(--bs-border-color);
  --bs-pagination-border-radius: var(--bs-border-radius);
  --bs-pagination-hover-color: var(--bs-link-hover-color);
  --bs-pagination-hover-bg: var(--bs-tertiary-bg);
  --bs-pagination-hover-border-color: var(--bs-border-color);
  --bs-pagination-focus-color: var(--bs-link-hover-color);
  --bs-pagination-focus-bg: var(--bs-secondary-bg);
  --bs-pagination-focus-box-shadow: 0 0 0 0.25rem rgba(13, 110, 253, 0.25);
  --bs-pagination-active-color: #fff;
  --bs-pagination-active-bg: #0d6efd;
  --bs-pagination-active-border-color: #0d6efd;
  --bs-pagination-disabled-color: var(--bs-secondary-color);
  --bs-pagination-disabled-bg: var(--bs-secondary-bg);
  --bs-pagination-disabled-border-color: var(--bs-border-color);
  display: flex;
  padding-left: 0;
  list-style: none;
}
.page-item:not(:first-child) .page-link {
  margin-left: calc(var(--bs-border-width) * -1);
}
.page-item:first-child .page-link {
  border-top-left-radius: var(--bs-pagination-border-radius);
  border-bottom-left-radius: var(--bs-pagination-border-radius);
}
.page-item:last-child .page-link {
  border-top-right-radius: var(--bs-pagination-border-radius);
  border-bottom-right-radius: var(--bs-pagination-border-radius);
}
.page-link {
  position: relative;
  display: block;
  padding: var(--bs-pagination-padding-y) var(--bs-pagination-padding-x);
  font-size: var(--bs-pagination-font-size);
  color: var(--bs-pagination-color);
  text-decoration: none;
  background-color: var(--bs-pagination-bg);
  border: var(--bs-pagination-border-width) solid var(--bs-pagination-border-color);
  transition: color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
}
@media (prefers-reduced-motion: reduce) {
  .page-link {
    transition: none;
  }
}
.page-link:hover {
  z-index: 2;
  color: var(--bs-pagination-hover-color);
  background-color: var(--bs-pagination-hover-bg);
  border-color: var(--bs-pagination-hover-border-color);
}
.page-link:focus {
  z-index: 3;
  color: var(--bs-pagination-focus-color);
  background-color: var(--bs-pagination-focus-bg);
  outline: 0;
  box-shadow: var(--bs-pagination-focus-box-shadow);
}
.page-link.active, .active > .page-link {
  z-index: 3;
  color: var(--bs-pagination-active-color);
  background-color: var(--bs-pagination-active-bg);
  border-color: var(--bs-pagination-active-border-color);
}
.page-link.disabled, .disabled > .page-link {
  color: var(--bs-pagination-disabled-color);
  pointer-events: none;
  background-color: var(--bs-pagination-disabled-bg);
  border-color: var(--bs-pagination-disabled-border-color);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="pagination">
            <li class="page-item"><a href="#" class="page-link">&lt;</a></li>
            <li class="page-item"><a href="#" class="page-link">1</a></li>
            <li class="page-item"><a href="#" class="page-link active">2</a></li>
            <li class="page-item"><a href="#" class="page-link disabled">3</a></li>
            <li class="page-item"><a href="#" class="page-link">&gt;</a></li>
        </ul>
    </body>
</html>
```

注意到`.pagination`设置了`display: flex`，因此我们可以使用`justify-content-*`设置分页按钮组居左、居中、居右对齐。

### §2.28.1 分页按钮组尺寸(`.pagination-*`)

Bootstrap提供了三种分页按钮组的尺寸：`.pagination-sm`、`.pagination`、`.pagination-lg`。

```css
.pagination-lg {
  --bs-pagination-padding-x: 1.5rem;
  --bs-pagination-padding-y: 0.75rem;
  --bs-pagination-font-size: 1.25rem;
  --bs-pagination-border-radius: var(--bs-border-radius-lg);
}
.pagination-sm {
  --bs-pagination-padding-x: 0.5rem;
  --bs-pagination-padding-y: 0.25rem;
  --bs-pagination-font-size: 0.875rem;
  --bs-pagination-border-radius: var(--bs-border-radius-sm);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["pagination pagination-sm", "pagination", "pagination pagination-lg"].forEach((className) => {
                document.body.innerHTML += `
                    <ul class="${className}">
                        <li class="page-item"><a href="#" class="page-link">&lt;</a></li>
                        <li class="page-item"><a href="#" class="page-link">1</a></li>
                        <li class="page-item"><a href="#" class="page-link active">2</a></li>
                        <li class="page-item"><a href="#" class="page-link disabled">3</a></li>
                        <li class="page-item"><a href="#" class="page-link">&gt;</a></li>
                    </ul>
                `;
            })
        </script>
    </body>
</html>
```

## §2.29 卡片(`.card`)

Bootstrap提供了卡片`.card`的样式，包含以下附属属性：

| 属性名          | 作用       |
| --------------- | ---------- |
| `card-title`    | 卡片标题   |
| `card-subtitle` | 卡片副标题 |
| `card-body`     | 卡片主题   |
| `card-text`     | 卡片文本   |
| `card-link`     | 卡片超链接 |
| `card-img`      | 卡片图片   |
| `card-header`   | 卡片页眉   |
| `card-footer`   | 卡片页尾   |

```css
.card {
  --bs-card-spacer-y: 1rem;
  --bs-card-spacer-x: 1rem;
  --bs-card-title-spacer-y: 0.5rem;
  --bs-card-title-color: ;
  --bs-card-subtitle-color: ;
  --bs-card-border-width: var(--bs-border-width);
  --bs-card-border-color: var(--bs-border-color-translucent);
  --bs-card-border-radius: var(--bs-border-radius);
  --bs-card-box-shadow: ;
  --bs-card-inner-border-radius: calc(var(--bs-border-radius) - (var(--bs-border-width)));
  --bs-card-cap-padding-y: 0.5rem;
  --bs-card-cap-padding-x: 1rem;
  --bs-card-cap-bg: rgba(var(--bs-body-color-rgb), 0.03);
  --bs-card-cap-color: ;
  --bs-card-height: ;
  --bs-card-color: ;
  --bs-card-bg: var(--bs-body-bg);
  --bs-card-img-overlay-padding: 1rem;
  --bs-card-group-margin: 0.75rem;
  position: relative;
  display: flex;
  flex-direction: column;
  min-width: 0;
  height: var(--bs-card-height);
  color: var(--bs-body-color);
  word-wrap: break-word;
  background-color: var(--bs-card-bg);
  background-clip: border-box;
  border: var(--bs-card-border-width) solid var(--bs-card-border-color);
  border-radius: var(--bs-card-border-radius);
}
.card > hr {
  margin-right: 0;
  margin-left: 0;
}
.card > .list-group {
  border-top: inherit;
  border-bottom: inherit;
}
.card > .list-group:first-child {
  border-top-width: 0;
  border-top-left-radius: var(--bs-card-inner-border-radius);
  border-top-right-radius: var(--bs-card-inner-border-radius);
}
.card > .list-group:last-child {
  border-bottom-width: 0;
  border-bottom-right-radius: var(--bs-card-inner-border-radius);
  border-bottom-left-radius: var(--bs-card-inner-border-radius);
}
.card > .card-header + .list-group, .card > .list-group + .card-footer {
  border-top: 0;
}
.card-body {
  flex: 1 1 auto;
  padding: var(--bs-card-spacer-y) var(--bs-card-spacer-x);
  color: var(--bs-card-color);
}
.card-title {
  margin-bottom: var(--bs-card-title-spacer-y);
  color: var(--bs-card-title-color);
}
.card-subtitle {
  margin-top: calc(-0.5 * var(--bs-card-title-spacer-y));
  margin-bottom: 0;
  color: var(--bs-card-subtitle-color);
}
.card-text:last-child {
  margin-bottom: 0;
}
.card-link + .card-link {
  margin-left: var(--bs-card-spacer-x);
}
.card-header {
  padding: var(--bs-card-cap-padding-y) var(--bs-card-cap-padding-x);
  margin-bottom: 0;
  color: var(--bs-card-cap-color);
  background-color: var(--bs-card-cap-bg);
  border-bottom: var(--bs-card-border-width) solid var(--bs-card-border-color);
}
.card-header:first-child {
  border-radius: var(--bs-card-inner-border-radius) var(--bs-card-inner-border-radius) 0 0;
}
.card-footer {
  padding: var(--bs-card-cap-padding-y) var(--bs-card-cap-padding-x);
  color: var(--bs-card-cap-color);
  background-color: var(--bs-card-cap-bg);
  border-top: var(--bs-card-border-width) solid var(--bs-card-border-color);
}
.card-footer:last-child {
  border-radius: 0 0 var(--bs-card-inner-border-radius) var(--bs-card-inner-border-radius);
}
.card-header-tabs {
  margin-right: calc(-0.5 * var(--bs-card-cap-padding-x));
  margin-bottom: calc(-1 * var(--bs-card-cap-padding-y));
  margin-left: calc(-0.5 * var(--bs-card-cap-padding-x));
  border-bottom: 0;
}
.card-header-tabs .nav-link.active {
  background-color: var(--bs-card-bg);
  border-bottom-color: var(--bs-card-bg);
}
.card-header-pills {
  margin-right: calc(-0.5 * var(--bs-card-cap-padding-x));
  margin-left: calc(-0.5 * var(--bs-card-cap-padding-x));
}
.card-img-overlay {
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  padding: var(--bs-card-img-overlay-padding);
  border-radius: var(--bs-card-inner-border-radius);
}
.card-img,
.card-img-top,
.card-img-bottom {
  width: 100%;
}
.card-img,
.card-img-top {
  border-top-left-radius: var(--bs-card-inner-border-radius);
  border-top-right-radius: var(--bs-card-inner-border-radius);
}
.card-img,
.card-img-bottom {
  border-bottom-right-radius: var(--bs-card-inner-border-radius);
  border-bottom-left-radius: var(--bs-card-inner-border-radius);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="card">
            <div class="card-header">卡片页眉</div>
            <img src="https://www.baidu.com/favicon.ico" alt="" class="card-img" style="width: 3rem;">
            <div class="card-title">卡片标题</div>
            <div class="card-subtitle">卡片副标题</div>
            <div class="card-body">
                <p class="card-text">卡片文本</p>
                <a class="card-link" href="#">加入购物车</a>
                <a class="card-link" href="#">立即购买</a>
            </div>
            <div class="card-footer">卡片页脚</div>
        </div>
    </body>
</html>
```

### §2.29.1 卡片背景图片(`.card-img-overlay`)

`.card-img-overlay`用于将文字放在图片之上。

```css
.card-img-overlay {
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  padding: var(--bs-card-img-overlay-padding);
  border-radius: var(--bs-card-inner-border-radius);
}
```

```css
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="card bg-primary">
            <img src="https://www.baidu.com/favicon.ico" alt="" style="width: 10rem;">
            <div class="card-img-overlay">这段文字浮在图片之上</div>
        </div>
    </body>
</html>
```

### §2.29.2 卡片组(`.card-group`)

`.card-group`用于对多个卡片进行排版。

```css
.card-group > .card {
  margin-bottom: var(--bs-card-group-margin);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="card-group center">
            <div class="card">
                <img class="card-img-top mx-auto" src="https://www.baidu.com/favicon.ico" alt="" style="width: 10rem;">
                <div class="card-body">
                    <h5 class="card-title">baidu</h5>
                    <p class="card-text">搜索引擎</p>
                </div>
            </div>
            <div class="card">
                <img class="card-img-top mx-auto" src="https://www.bing.com/favicon.ico" alt="" style="width: 10rem;">
                <div class="card-body">
                    <h5 class="card-title">bing</h5>
                    <p class="card-text">搜索引擎</p>
                </div>
            </div>
            <div class="card">
                <img class="card-img-top mx-auto" src="https://www.google.com/favicon.ico" alt="" style="width: 10rem;">
                <div class="card-body">
                    <h5 class="card-title">google</h5>
                    <p class="card-text">搜索引擎</p>
                </div>
            </div>
        </div>
    </body>
</html>
```

## §2.30 手风琴(`.accordion`)

我们知道，选项卡是横向排列的。手风琴的作用类似于选项卡，但是沿纵向排列。一个手风琴(`.accordion`)包含了若干个手风琴项(`.accordion-item`)。每个手风琴项可以由下列部件组成：

| 属性名               | 作用         |
| -------------------- | ------------ |
| `accordion-header`   | 标题         |
| `accordion-button`   | 折叠按钮     |
| `accordion-collapse` | 手风琴折叠体 |
| `accordion-body`     | 手风琴内容区 |

```css
.accordion {
  --bs-accordion-color: var(--bs-body-color);
  --bs-accordion-bg: var(--bs-body-bg);
  --bs-accordion-transition: color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out, border-radius 0.15s ease;
  --bs-accordion-border-color: var(--bs-border-color);
  --bs-accordion-border-width: var(--bs-border-width);
  --bs-accordion-border-radius: var(--bs-border-radius);
  --bs-accordion-inner-border-radius: calc(var(--bs-border-radius) - (var(--bs-border-width)));
  --bs-accordion-btn-padding-x: 1.25rem;
  --bs-accordion-btn-padding-y: 1rem;
  --bs-accordion-btn-color: var(--bs-body-color);
  --bs-accordion-btn-bg: var(--bs-accordion-bg);
  --bs-accordion-btn-icon: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 16 16' fill='%23212529'%3e%3cpath fill-rule='evenodd' d='M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708z'/%3e%3c/svg%3e");
  --bs-accordion-btn-icon-width: 1.25rem;
  --bs-accordion-btn-icon-transform: rotate(-180deg);
  --bs-accordion-btn-icon-transition: transform 0.2s ease-in-out;
  --bs-accordion-btn-active-icon: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 16 16' fill='%23052c65'%3e%3cpath fill-rule='evenodd' d='M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708z'/%3e%3c/svg%3e");
  --bs-accordion-btn-focus-border-color: #86b7fe;
  --bs-accordion-btn-focus-box-shadow: 0 0 0 0.25rem rgba(13, 110, 253, 0.25);
  --bs-accordion-body-padding-x: 1.25rem;
  --bs-accordion-body-padding-y: 1rem;
  --bs-accordion-active-color: var(--bs-primary-text-emphasis);
  --bs-accordion-active-bg: var(--bs-primary-bg-subtle);
}
.accordion-button {
  position: relative;
  display: flex;
  align-items: center;
  width: 100%;
  padding: var(--bs-accordion-btn-padding-y) var(--bs-accordion-btn-padding-x);
  font-size: 1rem;
  color: var(--bs-accordion-btn-color);
  text-align: left;
  background-color: var(--bs-accordion-btn-bg);
  border: 0;
  border-radius: 0;
  overflow-anchor: none;
  transition: var(--bs-accordion-transition);
}
@media (prefers-reduced-motion: reduce) {
  .accordion-button {
    transition: none;
  }
}
.accordion-button:not(.collapsed) {
  color: var(--bs-accordion-active-color);
  background-color: var(--bs-accordion-active-bg);
  box-shadow: inset 0 calc(-1 * var(--bs-accordion-border-width)) 0 var(--bs-accordion-border-color);
}
.accordion-button:not(.collapsed)::after {
  background-image: var(--bs-accordion-btn-active-icon);
  transform: var(--bs-accordion-btn-icon-transform);
}
.accordion-button::after {
  flex-shrink: 0;
  width: var(--bs-accordion-btn-icon-width);
  height: var(--bs-accordion-btn-icon-width);
  margin-left: auto;
  content: "";
  background-image: var(--bs-accordion-btn-icon);
  background-repeat: no-repeat;
  background-size: var(--bs-accordion-btn-icon-width);
  transition: var(--bs-accordion-btn-icon-transition);
}
@media (prefers-reduced-motion: reduce) {
  .accordion-button::after {
    transition: none;
  }
}
.accordion-button:hover {
  z-index: 2;
}
.accordion-button:focus {
  z-index: 3;
  border-color: var(--bs-accordion-btn-focus-border-color);
  outline: 0;
  box-shadow: var(--bs-accordion-btn-focus-box-shadow);
}
.accordion-header {
  margin-bottom: 0;
}
.accordion-item {
  color: var(--bs-accordion-color);
  background-color: var(--bs-accordion-bg);
  border: var(--bs-accordion-border-width) solid var(--bs-accordion-border-color);
}
.accordion-item:first-of-type {
  border-top-left-radius: var(--bs-accordion-border-radius);
  border-top-right-radius: var(--bs-accordion-border-radius);
}
.accordion-item:first-of-type .accordion-button {
  border-top-left-radius: var(--bs-accordion-inner-border-radius);
  border-top-right-radius: var(--bs-accordion-inner-border-radius);
}
.accordion-item:not(:first-of-type) {
  border-top: 0;
}
.accordion-item:last-of-type {
  border-bottom-right-radius: var(--bs-accordion-border-radius);
  border-bottom-left-radius: var(--bs-accordion-border-radius);
}
.accordion-item:last-of-type .accordion-button.collapsed {
  border-bottom-right-radius: var(--bs-accordion-inner-border-radius);
  border-bottom-left-radius: var(--bs-accordion-inner-border-radius);
}
.accordion-item:last-of-type .accordion-collapse {
  border-bottom-right-radius: var(--bs-accordion-border-radius);
  border-bottom-left-radius: var(--bs-accordion-border-radius);
}

.accordion-body {
  padding: var(--bs-accordion-body-padding-y) var(--bs-accordion-body-padding-x);
}
```

给`.accordion-collapse.accordion`指定`.show`属性，可以使其处于展开状态。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="accordion">
            <div class="accordion-item">
                <h2 class="accordion-header">
                    <button class="accordion-button" data-bs-toggle="collapse" data-bs-target="#collapse-1">这里是标题</button>
                </h2>
                <div class="accordion accrodion-aollapse collapse show" id="collapse-1">
                    <div class="accordion-body">
                        <p>这里是内容</p>
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>
```

### §2.30.1 无边框手风琴(`.accordion-flush`)

Bootstrap在`.accordion`的基础上，引入了`.accordion-flush`，用于将手风琴样式改为无边框。

```css
.accordion-flush .accordion-collapse {
  border-width: 0;
}
.accordion-flush .accordion-item {
  border-right: 0;
  border-left: 0;
  border-radius: 0;
}
.accordion-flush .accordion-item:first-child {
  border-top: 0;
}
.accordion-flush .accordion-item:last-child {
  border-bottom: 0;
}
.accordion-flush .accordion-item .accordion-button, .accordion-flush .accordion-item .accordion-button.collapsed {
  border-radius: 0;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="accordion accordion-flush">
            <div class="accordion-item">
                <h2 class="accordion-header">
                    <button class="accordion-button" data-bs-toggle="collapse" data-bs-target="#collapse-1">这里是标题</button>
                </h2>
                <div class="accordion accrodion-aollapse collapse show" id="collapse-1">
                    <div class="accordion-body">
                        <p>这里是内容</p>
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>
```

# §3 JavaScript插件

作为一个UI组件库，Bootstrap除了提供必要的CSS以外，还要有JavaScript的支撑。Bootstrap的所有JavaScript插件存放在`node_modules/bootstrap/js/dist`目录下，合在一起形成了`node_modules/bootstrap/dist/js/bootstrap.bundle.js`。

| 文件名              | 作用       |
| ------------------- | ---------- |
| `alert.js`          | 警告框     |
| `base-component.js` | 基本组件   |
| `button.js`         | 按钮       |
| `carousel.js`       | 轮播组件   |
| `collapse.js`       | 折叠组件   |
| `dropdown.js`       | 下拉菜单   |
| `modal.js`          | 模态框     |
| `offcanvas.js`      | 侧边栏导航 |
| `popover.js`        | 弹窗       |
| `scrollspy.js`      | 滚动监听   |
| `tab.js`            | 便签页     |
| `toast.js`          | Toast组件  |
| `tooltip.js`        | 工具提示   |

## §3.1 警告框插件(`alert.js`)

警告框插件文件在`node_modules/bootstrap/js/dist/alert.js`。该插件与[§2.22 警告框(`.alert-*`)](##§2.22 警告框(`.alert-*`))配合使用。对于关闭按钮`button.btn.btn-close`，我们需要为其指定`[data-bs-dismiss="alert"]`属性。

在Bootstrap中，警告框元素实例可以通过`bootstrap.Alert(element)`构造函数获得，也提供了`.close()`方法，用于关闭警告框。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="alert alert-primary show fade" id="alert">
            警告框文本
            <button class="btn btn-close float-end" data-bs-dismiss="alert"></button>
        </div>
        <button id="trigger" class="btn btn-primary">手动调用JavaScript关闭警告框</button>
        <script>
            const alertDom = document.getElementById("alert")
            const alertBootstrap = new bootstrap.Alert(alertDom);
            document.getElementById("trigger").addEventListener("click", () => {
                alertBootstrap.close();
            });
        </script>
    </body>
</html>
```

## §3.2 按钮插件(`alert.js`)

按钮插件文件在`node_modules/bootstrap/js/dist/button.js`。对于按钮组`btn-group`，我们需要为其指定`[data-bs-toggle="button"]`属性。

### §3.2.1 按钮式复选框组(`label.btn`)

我们用`.btn`修饰`<label>`，并在内部包含一个`<input type="checkbox">`，即可得到一堆形如按钮的复选框。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="btn-group">
            <label class="btn btn-primary" for="checkbox-apple">
                <input type="checkbox" name="apple" id="checkbox-apple">
                <span>苹果</span>
            </label>
            <label class="btn btn-primary" for="checkbox-banana">
                <input type="checkbox" name="apple" id="checkbox-banana">
                <span>香蕉</span>
            </label>
            <label class="btn btn-primary" for="checkbox-cheery">
                <input type="checkbox" name="apple" id="checkbox-cheery">
                <span>樱桃</span>
            </label>
        </div>
    </body>
</html>
```

## §3.3 轮播插件(`carousel.js`)

轮播插件文件在`node_modules/bootstrap/js/dist/carousel.js`。

一个轮播元素需要`.slide`规定动画效果，也需要`.carousel`进行JavaScript绑定，同时添加DOM属性`[data-bs-ride="carousel"]`，并规定自己的`[id]`。轮播元素内部由三个元素构成：

- `.carousel-indicators`：最下方的播放进度指示条。里面的`<button>`元素既要有`[data-bs-target]`指向轮播元素`.carousel`的`[id]`，也要有`data-bs-slide-to`指向图片的索引数字（从零计数）。
- `.carousel-inner`：用于存放众多`.carousel-item`，每个`.carousel`由图片`img`和文字`carousel.caption`。其中`img`需要设置`.w-100`。我们还可以给`.carousel-item`指定DOM属性`[data-bs-interval]`，设置自动循环的间隔时间。
- 前进和后退按钮：`button.carousel-control-prev`和`button.carousel-control-next`。均需要设置DOM属性`data-bs-target`为轮播元素的`[id]`，也要设置`data-bs-slide`为`"prev"`或`"next"`来绑定行为。

```css
.carousel {
  position: relative;
}
.carousel.pointer-event {
  touch-action: pan-y;
}
.carousel-inner {
  position: relative;
  width: 100%;
  overflow: hidden;
}
.carousel-inner::after {
  display: block;
  clear: both;
  content: "";
}
.carousel-item {
  position: relative;
  display: none;
  float: left;
  width: 100%;
  margin-right: -100%;
  -webkit-backface-visibility: hidden;
  backface-visibility: hidden;
  transition: transform 0.6s ease-in-out;
}
@media (prefers-reduced-motion: reduce) {
  .carousel-item {
    transition: none;
  }
}
.carousel-item.active,
.carousel-item-next,
.carousel-item-prev {
  display: block;
}
.carousel-item-next:not(.carousel-item-start),
.active.carousel-item-end {
  transform: translateX(100%);
}
.carousel-item-prev:not(.carousel-item-end),
.active.carousel-item-start {
  transform: translateX(-100%);
}
.carousel-control-prev,
.carousel-control-next {
  position: absolute;
  top: 0;
  bottom: 0;
  z-index: 1;
  display: flex;
  align-items: center;
  justify-content: center;
  width: 15%;
  padding: 0;
  color: #fff;
  text-align: center;
  background: none;
  border: 0;
  opacity: 0.5;
  transition: opacity 0.15s ease;
}
@media (prefers-reduced-motion: reduce) {
  .carousel-control-prev,
  .carousel-control-next {
    transition: none;
  }
}
.carousel-control-prev:hover, .carousel-control-prev:focus,
.carousel-control-next:hover,
.carousel-control-next:focus {
  color: #fff;
  text-decoration: none;
  outline: 0;
  opacity: 0.9;
}
.carousel-control-prev {
  left: 0;
}
.carousel-control-next {
  right: 0;
}
.carousel-control-prev-icon,
.carousel-control-next-icon {
  display: inline-block;
  width: 2rem;
  height: 2rem;
  background-repeat: no-repeat;
  background-position: 50%;
  background-size: 100% 100%;
}
.carousel-control-prev-icon {
  background-image: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 16 16' fill='%23fff'%3e%3cpath d='M11.354 1.646a.5.5 0 0 1 0 .708L5.707 8l5.647 5.646a.5.5 0 0 1-.708.708l-6-6a.5.5 0 0 1 0-.708l6-6a.5.5 0 0 1 .708 0z'/%3e%3c/svg%3e");
}
.carousel-control-next-icon {
  background-image: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 16 16' fill='%23fff'%3e%3cpath d='M4.646 1.646a.5.5 0 0 1 .708 0l6 6a.5.5 0 0 1 0 .708l-6 6a.5.5 0 0 1-.708-.708L10.293 8 4.646 2.354a.5.5 0 0 1 0-.708z'/%3e%3c/svg%3e");
}
.carousel-indicators {
  position: absolute;
  right: 0;
  bottom: 0;
  left: 0;
  z-index: 2;
  display: flex;
  justify-content: center;
  padding: 0;
  margin-right: 15%;
  margin-bottom: 1rem;
  margin-left: 15%;
}
.carousel-indicators [data-bs-target] {
  box-sizing: content-box;
  flex: 0 1 auto;
  width: 30px;
  height: 3px;
  padding: 0;
  margin-right: 3px;
  margin-left: 3px;
  text-indent: -999px;
  cursor: pointer;
  background-color: #fff;
  background-clip: padding-box;
  border: 0;
  border-top: 10px solid transparent;
  border-bottom: 10px solid transparent;
  opacity: 0.5;
  transition: opacity 0.6s ease;
}
@media (prefers-reduced-motion: reduce) {
  .carousel-indicators [data-bs-target] {
    transition: none;
  }
}
.carousel-indicators .active {
  opacity: 1;
}
.carousel-caption {
  position: absolute;
  right: 15%;
  bottom: 1.25rem;
  left: 15%;
  padding-top: 1.25rem;
  padding-bottom: 1.25rem;
  color: #fff;
  text-align: center;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="carousel slide bg-dark" data-bs-ride="carousel" id="carousel-1">
            <div class="carousel-indicators">
                <button class="active" data-bs-target="#carousel-1" data-bs-slide-to="0"></button>
                <button data-bs-target="#carousel-1" data-bs-slide-to="1"></button>
                <button data-bs-target="#carousel-1" data-bs-slide-to="2"></button>
            </div>
            <div class="carousel-inner">
                <div class="carousel-item active">
                    <img src="https://www.baidu.com/favicon.ico" style="width:100%">
                    <div class="carousel-caption">
                        <h3>百度</h3>
                        <p>搜索引擎</p>
                    </div>
                </div>
                <div class="carousel-item">
                    <img src="https://www.bing.com/favicon.ico" style="width:100%">
                    <div class="carousel-caption">
                        <h3>必应</h3>
                        <p>搜索引擎</p>
                    </div>
                </div>
                <div class="carousel-item">
                    <img src="https://www.google.com/favicon.ico" style="width:100%">
                    <div class="carousel-caption">
                        <h3>谷歌</h3>
                        <p>搜索引擎</p>
                    </div>
                </div>   
            </div>
            <button class="carousel-control-prev" data-bs-target="#carousel-1" data-bs-slide="prev">
                <span class="carousel-control-prev-icon"></span>
            </button>
            <button class="carousel-control-next" data-bs-target="#carousel-1" data-bs-slide="next">
                <span class="carousel-control-next-icon"></span>
            </button>
        </div>
    </body>
</html>
```

### §3.3.1 渐变轮播(`.carousel.fade`)

轮播使用的动画由`.slide`指定。在默认的左右滑动`.slide`基础上，轮播组件提供了`.carousel-fade`效果。

```css
.carousel-fade .carousel-item {
  opacity: 0;
  transition-property: opacity;
  transform: none;
}
.carousel-fade .carousel-item.active,
.carousel-fade .carousel-item-next.carousel-item-start,
.carousel-fade .carousel-item-prev.carousel-item-end {
  z-index: 1;
  opacity: 1;
}
.carousel-fade .active.carousel-item-start,
.carousel-fade .active.carousel-item-end {
  z-index: 0;
  opacity: 0;
  transition: opacity 0s 0.6s;
}
@media (prefers-reduced-motion: reduce) {
  .carousel-fade .active.carousel-item-start,
  .carousel-fade .active.carousel-item-end {
    transition: none;
  }
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="carousel slide bg-dark carousel-fade" data-bs-ride="carousel" id="carousel-1">
            <div class="carousel-indicators">
                <button class="active" data-bs-target="#carousel-1" data-bs-slide-to="0"></button>
                <button data-bs-target="#carousel-1" data-bs-slide-to="1"></button>
                <button data-bs-target="#carousel-1" data-bs-slide-to="2"></button>
            </div>
            <div class="carousel-inner">
                <div class="carousel-item active">
                    <img src="https://www.baidu.com/favicon.ico" style="width:100%">
                    <div class="carousel-caption">
                        <h3>百度</h3>
                        <p>搜索引擎</p>
                    </div>
                </div>
                <div class="carousel-item">
                    <img src="https://www.bing.com/favicon.ico" style="width:100%">
                    <div class="carousel-caption">
                        <h3>必应</h3>
                        <p>搜索引擎</p>
                    </div>
                </div>
                <div class="carousel-item">
                    <img src="https://www.google.com/favicon.ico" style="width:100%">
                    <div class="carousel-caption">
                        <h3>谷歌</h3>
                        <p>搜索引擎</p>
                    </div>
                </div>   
            </div>
            <button class="carousel-control-prev" data-bs-target="#carousel-1" data-bs-slide="prev">
                <span class="carousel-control-prev-icon"></span>
            </button>
            <button class="carousel-control-next" data-bs-target="#carousel-1" data-bs-slide="next">
                <span class="carousel-control-next-icon"></span>
            </button>
        </div>
    </body>
</html>
```

### §3.3.2 轮播暗色主题(`.carousel-dark`)

Bootstrap在默认的白色主题`.carousel`基础上，提供了暗色主题`.carousel-dark`效果。

```css
.carousel-dark .carousel-control-prev-icon,
.carousel-dark .carousel-control-next-icon {
  filter: invert(1) grayscale(100);
}
.carousel-dark .carousel-indicators [data-bs-target] {
  background-color: #000;
}
.carousel-dark .carousel-caption {
  color: #000;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="carousel slide bg-dark carousel-dark" data-bs-ride="carousel" id="carousel-1">
            <div class="carousel-indicators">
                <button class="active" data-bs-target="#carousel-1" data-bs-slide-to="0"></button>
                <button data-bs-target="#carousel-1" data-bs-slide-to="1"></button>
                <button data-bs-target="#carousel-1" data-bs-slide-to="2"></button>
            </div>
            <div class="carousel-inner">
                <div class="carousel-item active">
                    <img src="https://www.baidu.com/favicon.ico" style="width:100%">
                    <div class="carousel-caption">
                        <h3>百度</h3>
                        <p>搜索引擎</p>
                    </div>
                </div>
                <div class="carousel-item">
                    <img src="https://www.bing.com/favicon.ico" style="width:100%">
                    <div class="carousel-caption">
                        <h3>必应</h3>
                        <p>搜索引擎</p>
                    </div>
                </div>
                <div class="carousel-item">
                    <img src="https://www.google.com/favicon.ico" style="width:100%">
                    <div class="carousel-caption">
                        <h3>谷歌</h3>
                        <p>搜索引擎</p>
                    </div>
                </div>   
            </div>
            <button class="carousel-control-prev" data-bs-target="#carousel-1" data-bs-slide="prev">
                <span class="carousel-control-prev-icon"></span>
            </button>
            <button class="carousel-control-next" data-bs-target="#carousel-1" data-bs-slide="next">
                <span class="carousel-control-next-icon"></span>
            </button>
        </div>
    </body>
</html>
```

## §3.4 折叠插件(`collapse.js`)

折叠插件文件在`node_modules/bootstrap/js/dist/collapse.js`。

一个折叠插件需要由两部分组成：触发器和折叠元素。

- 折叠元素可以由以下两种属性之一声明：`.collapse`表示无动画的折叠元素，`.collapsing`表示有动画的折叠元素。两种方式都需要附有`[id]`属性。
- 触发器需要用`[data-bs-toggle="collapse"]`声明。当触发器为`<a>`时，只需在其`[href]`中声明`[id]`即可；如果触发器是`<button>`，还需要指定DOM属性`data-bs-target`，其属性值为`selector`，可以批量选择多个元素。

```css
.collapse:not(.show) {
  display: none;
}
.collapsing {
  height: 0;
  overflow: hidden;
  transition: height 0.35s ease;
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <a class="btn btn-primary" href="#collapse-1" data-bs-toggle="collapse">&lt;a&gt;触发折叠</a>
        <button class="btn btn-primary" data-bs-target="#collapse-2" data-bs-toggle="collapse">&lt;button&gt;触发折叠</button></button>
        <div class="collapsing" id="collapse-1">
            <div class="card card-body">由&lt;a&gt;触发的折叠内容</div>
        </div>
        <div class="collapse" id="collapse-2">
            <div class="card card-body">由&lt;button&gt;触发的折叠内容</div>
        </div>
        <div class="collapse show" id="collapse-3">
            <div class="card card-body">由.show修饰的折叠控件自动展开</div>
        </div>
    </body>
</html>
```

## §3.5 下拉菜单插件(`dropdown.js`)

下拉菜单插件文件在`node_modules/bootstrap/js/dist/dropdown.js`。

Bootstrap对下拉菜单`.dropdown`提供了四种触发事件：

| 事件名称             | 作用                     |
| -------------------- | ------------------------ |
| `show.bs.dropdown`   | 展开下拉菜单开始时的事件 |
| `shown.bs.dropdown`  | 展开下拉菜单结束时的事件 |
| `hide.bs.dropdown`   | 折叠下拉菜单开始时的事件 |
| `hidden.bs.dropdown` | 折叠下拉菜单结束时的事件 |

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <div class="dropdown">
            <button class="btn btn-primary dropdown-toggle" data-bs-toggle="dropdown">展开菜单</button>
            <div class="dropdown-menu">
                <a class="dropdown-item" href="#">首页</a>
                <a class="dropdown-item" href="#">课程列表</a>
                <a class="dropdown-item" href="#">关于我们</a>
            </div>
        </div>
        <div id="info"></div>
        <script>
            const infoDom = document.querySelector("#info");
            const dropdownDom = document.querySelector(".dropdown");
            ["show.bs.dropdown", "shown.bs.dropdown", "hide.bs.dropdown", "hidden.bs.dropdown"].forEach((eventName) => {
                dropdownDom.addEventListener(eventName, (event) => {
                    infoDom.innerHTML += `检测到${eventName}事件触发<br>`;
                });
            });
        </script>
    </body>
</html>
```

## §3.6 模态框插件(`modal.js`)

模态框插件文件在`node_modules/bootstrap/js/dist/modal.js`。模态框是覆盖在父窗体上的子窗体，通常用于显示通知。

一个模态框元素由`.modal`声明，用于定义窗体，里面包含`.modal-dialog`用于定义对话框层，里面再嵌套一层`.modal-content`用于定义显示内容。`.modal-content`可以包含以下元素：

- `.modal-header`：模态框页眉
- `.modal-body`：模态框正文
- `.modal-footer`：模态框页脚
- `.modal-title`：模态框标题

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <button class="btn btn-primary" data-bs-target="#modal" data-bs-toggle="modal">打开模态框</button>
        <div class="modal" id="modal">
            <div class="modal-dialog">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title">模态框标题</h5>
                        <button class="btn-close" data-bs-dismiss="modal"></button>
                    </div>
                    <div class="modal-body">
                        <p>这是模态框正文</p>
                    </div>
                    <div class="modal-footer">
                        <button class="btn btn-primary">确认</button>
                        <button class="btn btn-danger">取消</button>
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>
```

### §3.6.1 模态框居中(`.modal-dialog-centered`)

Bootstrap为`.modal-dialog`提供了`.modal-dialog-centered`属性，用于规定模态框在垂直方向上居中显示。

```css
.modal-dialog-centered {
  display: flex;
  align-items: center;
  min-height: calc(100% - var(--bs-modal-margin) * 2);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <button class="btn btn-primary" data-bs-target="#modal" data-bs-toggle="modal">打开模态框</button>
        <div class="modal" id="modal">
            <div class="modal-dialog modal-dialog-centered">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title">模态框标题</h5>
                        <button class="btn-close" data-bs-dismiss="modal"></button>
                    </div>
                    <div class="modal-body">
                        <p>这是模态框正文</p>
                    </div>
                    <div class="modal-footer">
                        <button class="btn btn-primary" data-bs-dismiss="modal">确认</button>
                        <button class="btn btn-danger" data-bs-dismiss="modal">取消</button>
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>
```

### §3.6.2 模态框尺寸(`.modal-*`)

Bootstrap为`.modal-dialog`提供了四种尺寸：

```css
@media (min-width: 576px) {
  .modal {
    --bs-modal-margin: 1.75rem;
    --bs-modal-box-shadow: var(--bs-box-shadow);
  }
  .modal-dialog {
    max-width: var(--bs-modal-width);
    margin-right: auto;
    margin-left: auto;
  }
  .modal-sm {
    --bs-modal-width: 300px;
  }
}
@media (min-width: 992px) {
  .modal-lg,
  .modal-xl {
    --bs-modal-width: 800px;
  }
}
@media (min-width: 1200px) {
  .modal-xl {
    --bs-modal-width: 1140px;
  }
}
```

| 属性名                    | 模态框宽度 |
| ------------------------- | ---------- |
| `.modal-dialog .modal-sm` | 300px      |
| `.modal-dialog`           | 500px      |
| `.modal-dialog .modal-lg` | 800px      |
| `.modal-dialog .modal-xl` | 1140px     |

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["modal-sm", "modal-", "modal-lg", "modal-xl"].forEach((className, index) => {
                document.body.innerHTML += `
                    <button class="btn btn-primary" data-bs-target="#modal-${index}" data-bs-toggle="modal">打开模态框${className}</button>
                    <div class="modal" id="modal-${index}">
                        <div class="modal-dialog modal-dialog-centered ${className}">
                            <div class="modal-content">
                                <div class="modal-header">
                                    <h5 class="modal-title">模态框标题(${className})</h5>
                                    <button class="btn-close" data-bs-dismiss="modal"></button>
                                </div>
                                <div class="modal-body">
                                    <p>这是模态框正文</p>
                                </div>
                                <div class="modal-footer">
                                    <button class="btn btn-primary" data-bs-dismiss="modal">确认</button>
                                    <button class="btn btn-danger" data-bs-dismiss="modal">取消</button>
                                </div>
                            </div>
                        </div>
                    </div>
                `;
            })
        </script>
    </body>
</html>
```

## §3.7 侧边栏插件(`offcanvas.js`)

侧边栏插件文件在`node_modules/bootstrap/js/dist/offcanvas.js`。

一个侧边栏元素由`.offcanvas`声明，内部包含两部分：`.offcanvas-header`和`.offcanvas-body`。同样地，侧边栏默认为隐藏状态，需要由`<button data-bs-toggle="offcanvas" data-bs-target="...">`触发展开。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <button class="btn btn-primary" data-bs-toggle="offcanvas" data-bs-target="#offcanvas-1">展开侧边栏</button>
        <div class="offcanvas offcanvas-start" id="offcanvas-1">
            <div class="offcanvas-header">
                <h5 class="offcanvas-title">侧边栏标题</h5>
                <button type="button" class="btn-close" data-bs-dismiss="offcanvas"></button>
            </div>
            <div class="offcanvas-body">
                <div>你好</div>
                <div class="dropdown">
                    <button class="btn btn-secondary dropdown-toggle" data-bs-toggle="dropdown">更多</button>
                    <ul class="dropdown-menu">
                        <li class="dropdown-item"><a class="dropdown-link" href="#">1</a></li>
                        <li class="dropdown-item"><a class="dropdown-link" href="#">2</a></li>
                        <li class="dropdown-item"><a class="dropdown-link" href="#">3</a></li>
                    </ul>
                </div>
            </div>
        </div>
    </body>
</html>
```

### §3.7.1 侧边栏位置(`.offcanvas-*`)

在`.offcanvas`的基础上，Bootstrap允许侧边栏元素在屏幕的左、右、上、下边缘弹出和隐藏，分别对应`.offcanvas-start`、`.offcanvas-end`、`.offcanvas-top`、`.offcanvas-bottom`。

```css
.offcanvas.offcanvas-start {
  top: 0;
  left: 0;
  width: var(--bs-offcanvas-width);
  border-right: var(--bs-offcanvas-border-width) solid var(--bs-offcanvas-border-color);
  transform: translateX(-100%);
}
.offcanvas.offcanvas-end {
  top: 0;
  right: 0;
  width: var(--bs-offcanvas-width);
  border-left: var(--bs-offcanvas-border-width) solid var(--bs-offcanvas-border-color);
  transform: translateX(100%);
}
.offcanvas.offcanvas-top {
  top: 0;
  right: 0;
  left: 0;
  height: var(--bs-offcanvas-height);
  max-height: 100%;
  border-bottom: var(--bs-offcanvas-border-width) solid var(--bs-offcanvas-border-color);
  transform: translateY(-100%);
}
.offcanvas.offcanvas-bottom {
  right: 0;
  left: 0;
  height: var(--bs-offcanvas-height);
  max-height: 100%;
  border-top: var(--bs-offcanvas-border-width) solid var(--bs-offcanvas-border-color);
  transform: translateY(100%);
}
```

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            ["offcanvas-start", "offcanvas-end", "offcanvas-top", "offcanvas-bottom"].forEach((className, index) => {
                document.body.innerHTML += `
                    <button class="btn btn-primary" data-bs-toggle="offcanvas" data-bs-target="#offcanvas-${index}">展开${className}侧边栏</button>
                    <div class="offcanvas ${className}" id="offcanvas-${index}">
                        <div class="offcanvas-header">
                            <h5 class="offcanvas-title">侧边栏标题</h5>
                            <button type="button" class="btn-close" data-bs-dismiss="offcanvas"></button>
                        </div>
                        <div class="offcanvas-body">
                            <div>你好</div>
                            <div class="dropdown">
                                <button class="btn btn-secondary dropdown-toggle" data-bs-toggle="dropdown">更多</button>
                                <ul class="dropdown-menu">
                                    <li class="dropdown-item"><a class="dropdown-link" href="#">1</a></li>
                                    <li class="dropdown-item"><a class="dropdown-link" href="#">2</a></li>
                                    <li class="dropdown-item"><a class="dropdown-link" href="#">3</a></li>
                                </ul>
                            </div>
                        </div>
                    </div>
                `;
            })
        </script>
    </body>
</html>
```

### §3.7.2 侧边栏背景行为(`[data-bs-scroll]`/`[data-bs-backdrop]`)

针对`.offcanvas`，Bootstrap提供了`[data-bs-scroll]`用于设置`<body>`是否可以滚动，`[data-bs-backdrop]`用预示着是否显示给`<body>`蒙上一层灰色背景。两个属性值的取值范围均为`"true"`或`"false"`。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <script>
            [["true", "true"], ["true", "false"], ["false", "true"], ["false", "false"]].forEach((classNames, index) => {
                document.body.innerHTML += `
                    <button class="btn btn-primary" data-bs-toggle="offcanvas" data-bs-target="#offcanvas-${index}">展开侧边栏${index}</button>
                    <div class="offcanvas offcanvas-start" id="offcanvas-${index}" data-bs-scroll="${classNames[0]}" data-bs-backdrop="${classNames[1]}">
                        <div class="offcanvas-header">
                            <h5 class="offcanvas-title">侧边栏标题</h5>
                            <button type="button" class="btn-close" data-bs-dismiss="offcanvas"></button>
                        </div>
                        <div class="offcanvas-body">
                            <div>
                                data-bs-scroll="${classNames[0]}" &lt;body&gt;${classNames[0] === "true" ? "可以" : "不可以"}用鼠标滚轮滚动
                                <br>
                                data-bs-backdrop="${classNames[1]}" &lt;body&gt;${classNames[1] === "true" ? "" : "没有"}被灰色背景覆盖
                            </div>
                        </div>
                    </div>
                `;
            });
            document.body.innerHTML += "<p>很长的文本，仅供占位翻页使用</p>".repeat(50)
        </script>
    </body>
</html>
```

## §3.8 弹窗插件(`tooltip.js`)

弹窗插件文件在`node_modules/bootstrap/js/dist/tooltip.js`，同时也需要`popover.js`的支持。

一个弹窗本身不需要任何元素作为支撑，我们只需考虑弹窗的触发器即可。触发器`[data-bs-toggle="popover", title="标题", data-bs-content="内容"]`应该同时带有弹窗本身的信息。受制于性能问题，Bootstrap不会根据`data-bs-toggle="popover"`自动初始化弹窗，而是需要开发者手动调用JavaScript注册弹窗控件。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <span data-bs-toggle="popover" title="弹出标题" data-bs-content="弹出内容">
            <button class="btn btn-primary">打开弹窗</button>
        </span>
        <script>
            let popoverInstances = [].slice.call(document.querySelectorAll('[data-bs-toggle="popover"]')).map(
                function (popoverElement){
                    return new bootstrap.Popover(popoverElement);
                }
            );
        </script>
    </body>
</html>
```

### §3.8.1 弹窗方向(`[data-bs-placement]`)

在`[data-bs-toggle="popover"]`的基础上，Bootstrap为DOM提供了`[data-bs-placement]`属性，用于规定弹窗弹出后所在的位置，取值范围有`"left"`、`"right"`、`"top"`、`"bottom"`。当空间不足时，弹出方向会有所差异，因此必须保证距离视口边缘有充足的空间。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body style="padding: 10rem;">
        <script>
            ["left", "right", "top", "bottom"].forEach((className) => {
                document.body.innerHTML += `
                    <button class="btn btn-primary" data-bs-toggle="popover" title="弹出标题" data-bs-content="弹出内容" data-bs-placement="${className}">
                        打开弹窗${className}
                    </button>
                `;
            })
        </script>
        <script>
            let popoverInstances = [].slice.call(document.querySelectorAll('[data-bs-toggle="popover"]')).map(
                function (popoverElement){
                    return new bootstrap.Popover(popoverElement);
                }
            );
        </script>
    </body>
</html>
```

### §3.8.2 弹窗关闭方式(`[data-bs-trigger]`)

Bootstrap给`[data-bs-toggle="popover"]`提供了`[data-bs-trigger]`属性，用户规定弹窗的关闭方式：

- `""`(缺省)：再次单击触发器来关闭
- `"focus"`：单击弹窗以外的区域自动关闭
- `"hover"`：鼠标移出后自动关闭

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body style="padding: 10rem;">
        <script>
            ["", "focus", "hover"].forEach((className) => {
                document.body.innerHTML += `
                    <button class="btn btn-primary" data-bs-toggle="popover" title="弹出标题" data-bs-content="弹出内容" ${className ? `data-bs-trigger="${className}"` : ""}>
                        打开弹窗(${className})
                    </button>
                `;
            })
        </script>
        <script>
            let popoverInstances = [].slice.call(document.querySelectorAll('[data-bs-toggle="popover"]')).map(
                function (popoverElement){
                    return new bootstrap.Popover(popoverElement);
                }
            );
        </script>
    </body>
</html>
```

## §3.9 滚动监听插件(`scrollspy.js`)

滚动监听插件文件在`node_modules/bootstrap/js/dist/spyscroll.js`。

我们知道，HTML中提供了锚点效果，只需在URL的末尾添加`#...`，就能跳转至对应`[id]`元素所在的位置。Bootstrap提供的滚动监听插件，用于根据滚动条的位置给元素添加属性。

一个导航栏监听一段区域的进度条。被监听的的元素用`[data-bs-spy="scroll"]`声明，并用`[data-bs-target]`指明导航栏，可选`[data-bs-offset]`给定进度条偏移距离。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <nav class="navbar navbar-light bg-light" id="navbar">
            <ul class="nav nav-pills">
                <li class="nav-item">
                    <a class="nav-link" href="#list1">项目1</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="#list2">项目2</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link dropdown-toggle" data-bs-toggle="dropdown" href="#list3">项目3</a>
                    <div class="dropdown-menu">
                        <a href="#list4" class="dropdown-item">项目4</a>
                        <a href="#list5" class="dropdown-item">项目5</a>
                        <a href="#list6" class="dropdown-item">项目6</a>
                    </div>
                </li>
            </ul>
        </nav>
        <div data-bs-spy="scroll" data-bs-target="#navbar" data-bs-offset="80" style="width: 500px; height: 300px; overflow: scroll;">
            <div class="h-50 border m-3 py-5 bg-light text-center" id="list1">项目1</div>
            <div class="h-50 border m-3 py-5 bg-light text-center" id="list2">项目2</div>
            <div class="h-50 border m-3 py-5 bg-light text-center" id="list3">项目3</div>
            <div class="h-50 border m-3 py-5 bg-light text-center" id="list4">项目4</div>
            <div class="h-50 border m-3 py-5 bg-light text-center" id="list5">项目5</div>
            <div class="h-50 border m-3 py-5 bg-light text-center" id="list6">项目6</div>
        </div>
    </body>
</html>
```

## §3.10 标签页插件(`tab.js`)

标签页插件文件在`node_modules/bootstrap/js/dist/tab.js`。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <ul class="nav nav-tabs">
            <li class="nav-item"><a class="nav-link" href="#item1" data-bs-toggle="tab">项目1</a></li>
            <li class="nav-item"><a class="nav-link" href="#item2" data-bs-toggle="tab">项目2</a></li>
            <li class="nav-item"><a class="nav-link" href="#item3" data-bs-toggle="tab">项目3</a></li>
        </ul>
        <div class="tab-content">
            <div id="item1" class="tab-pane fade show active">
                <img src="https://www.baidu.com/favicon.ico" alt="">
            </div>
            <div id="item2" class="tab-pane fade">
                <img src="https://www.bing.com/favicon.ico" alt="">
            </div>
            <div id="item3" class="tab-pane fade">
                <img src="https://www.google.com/favicon.ico" alt="">
            </div>
        </div>
    </body>
</html>
```

## §3.11 提示框插件(`tooltip.js`)

提示框插件文件在`node_modules/bootstrap/js/dist/tooltip.js`。提示框类似于漫画中人物间常用的对话框。其用法与[§3.8 弹窗插件(`tooltip.js`)](##§3.8 弹窗插件(`tooltip.js`))完全一致。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <button class="btn btn-primary" data-bs-toggle="tooltip" data-bs-trigger="click" data-bs-placement="top" title="提示信息">点击查看提示信息(top)</button>
        <button class="btn btn-primary" data-bs-toggle="tooltip" data-bs-trigger="click" data-bs-placement="bottom" title="提示信息">点击查看提示信息(bottom)</button>
        <button class="btn btn-primary" data-bs-toggle="tooltip" data-bs-trigger="click" data-bs-placement="left" title="提示信息">点击查看提示信息(left)</button>
        <button class="btn btn-primary" data-bs-toggle="tooltip" data-bs-trigger="click" data-bs-placement="right" title="提示信息">点击查看提示信息(right)</button>
        <script>
            let tooltipTriggerList = [].slice.call(document.querySelectorAll('[data-bs-toggle="tooltip"]')).map(
                (element) => { return new bootstrap.Tooltip(element); }
            );
        </script>
    </body>
</html>
```

## §3.12 Toast插件(`toast.js`)

Toast插件文件在`node_modules/bootstrap/js/dist/toast.js`。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <button class="btn btn-primary">生成Toast消息</button>
        <div class="toast position-fixed bottom-0 end-0" data-bs-animation="false">
            <div class="toast-header">
                <strong class="me-auto">Toast标题</strong>
                <small class="ms-auto">Toast副标题</small>
                <button class="btn-close" data-bs-dismiss="toast"></button>
            </div>
            <div class="toast-body">
                <p>这是一条Toast消息</p>
            </div>
        </div>
        <script>
            document.querySelector("button").addEventListener("click", function() {
                new bootstrap.Toast(document.querySelector(".toast")).show();
            });
        </script>
    </body>
</html>
```

### §3.12.1 堆叠Toast消息(`.toast-container`)

Boostrap使用`.toast-container`管理多个堆叠的Toast消息。

```html
<!DOCTYPE html>
<html lang="zh_CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="referrer" content="never">
        <title>BootStrap</title>
        <link rel="stylesheet" href="./node_modules/bootstrap/dist/css/bootstrap.css">
        <script src="./node_modules/bootstrap/dist/js/bootstrap.bundle.js"></script>
    </head>
    <body class="p-5">
        <button class="btn btn-primary" id="toast-button-1">生成Toast消息1</button>
        <button class="btn btn-primary" id="toast-button-2">生成Toast消息2</button>
        <div class="toast-container position-fixed bottom-0 end-0">
            <div id="toast-1" class="toast" data-bs-animation="false">
                <div class="toast-header">
                    <strong class="me-auto">Toast标题</strong>
                    <small class="ms-auto">Toast副标题</small>
                    <button class="btn-close" data-bs-dismiss="toast"></button>
                </div>
                <div class="toast-body">
                    <p>这是一条Toast消息</p>
                </div>
            </div>
            <div id="toast-2" class="toast" data-bs-animation="false">
                <div class="toast-header">
                    <strong class="me-auto">Toast标题</strong>
                    <small class="ms-auto">Toast副标题</small>
                    <button class="btn-close" data-bs-dismiss="toast"></button>
                </div>
                <div class="toast-body">
                    <p>这是一条Toast消息</p>
                </div>
            </div>
        </div>
        <script>
            document.querySelector("#toast-button-1").addEventListener("click", function() {
                new bootstrap.Toast(document.querySelector("#toast-1")).show();
            });
            document.querySelector("#toast-button-2").addEventListener("click", function() {
                new bootstrap.Toast(document.querySelector("#toast-2")).show();
            });
        </script>
    </body>
</html>
```
