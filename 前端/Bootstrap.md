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

Bootstrap通过更改原生CSS中的`text-align`属性值，封装成了自己的浮动布局。

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

#### §1.4.2.2 文本换行



#### §1.4.2.3 文本大小写



#### §1.4.2.4 文本加粗与斜体



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

### §1.4.4 `.rounded-*`

Bootstrap`.rounded-*`用于改变元素的`border-radius`属性值，使其等于预置的CSS变量。

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

## §2.10 按钮(`.btn-*`)



## §2.11 

# §3 常用组件设计



2024.01.17 3w+

2024.01.18 4w+

2024.01.19 5w+

2024.01.20 6w+

2024.01.21 7w+

2024.01.22 8w+

2024.01.23 9w+

2024.01.24 10w+

2024.01.25 11w+
