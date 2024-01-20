# Bootstrap

参考资料：

- 《Bootstrap 5.x 从入门到项目实战》 [豆瓣](https://book.douban.com/subject/36489295/)

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

Bootstrap提供了两种加载动画样式——`.spinner-border`和`.spinner-grow`，并且配备了对应的小尺寸属性。

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

```

```





























# §3 常用组件设计



2024.01.20 6w+

2024.01.21 7w+

2024.01.22 8w+

2024.01.23 9w+

2024.01.24 10w+

2024.01.25 11w+

2024.01.26 12w+
