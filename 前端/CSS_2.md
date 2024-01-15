# §22 You-need-to-know-css

[You-need-to-know-css](https://lhammer.cn/You-need-to-know-css/#/)是一个开源的CSS技巧项目。

## §22.1 边框与背景

### §22.1.1 半透明边框

默认情况下，背景颜色会作用于边框。我们可以使用`background-clip: padding-box;`来防止背景颜色干扰边框。

```html
<html>
  <head>
    <style>
      body { background-color: blanchedalmond; }
      div {
        width: 20em;
        height: 2em;
        border: 10px solid rgba(255, 255, 255, 0.7);
        background-color: blue;
        margin: 1rem;
        color: white;
      }
      div:nth-child(2) {
        background-clip: padding-box;
      }
    </style>
  </head>
  <body>
    <div>边框颜色=米黄色+半透明白色+蓝色</div>
    <div>边框颜色=米黄色+半透明白色</div>
  </body>
</html>
```

### §22.1.2 多重边框

我们知道`border`属性只能绘制一个边框。但是使用`box-shadow`属性，将模糊半径设为`0`，我们可以绘制很多实心的“边框”。这种方法的局限是：`border`是一个环，而`box-shadow`是一个圆，需要让多个圆重叠起来，才能等价于多个圆环。另一种方法是再绘制一条`outline`，但也只能绘制一次。

```css
<html>

  <head>
    <style>
      div {
        width: 60px;
        height: 60px;
        border-radius: 50%;
        background-color: #fafafa;
      }

      div:nth-of-type(1) {
        box-shadow:
          0 0 0 10px #ff00ff,
          0 0 0 20px #ef00ff,
          0 0 0 30px #df00ff,
          0 0 0 40px #cf00ff,
          0 0 0 50px #af00ff,
          0 0 0 60px #9f00ff,
          0 0 0 70px #8f00ff,
          0 0 0 80px #7f00ff,
          0 0 0 90px #6f00ff;
        outline: 2px dashed gray;
        outline-offset: -10px;
      }
    </style>
  </head>

  <body>
    <div></div>
  </body>

</html>
```

### §22.1.3 边框内圆角

如果`border-radius`小于`border`的宽度，那么只有边框的外侧会产生圆弧，而内部仍然是直角。我们当然可以加长`border-radius`的值，来让内侧边框也有圆角。但是如果限制`border-radius`的最大值，该怎么办呢？



# §A 现代CSS

## §A.1 2023更新日志

Chrome开发者官网公布了题为[CSS Wrapped: 2023!](https://developer.chrome.com/blog/css-wrapped-2023?hl=zh-cn#nesting)的CSS 2023更新日志。

### §A.1.1 基础架构

现在所有主流的浏览器都支持在CSS使用三角函数：`sin()`、`cos()`、`tan()`、`asin()`、`acos()`、`atan()`、`atan2()`、`

```html

```

