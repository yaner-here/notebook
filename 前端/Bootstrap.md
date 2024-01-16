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

### §











`.g-0`

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
```

