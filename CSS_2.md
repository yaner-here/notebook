# §18 实践开发技巧

经过前17章的学习，我们已经掌握了CSS的基础语法。接下来我们将给出实际开发中常见的需求，并给出相应的CSS最优解。

## §18.1 选择器

### §18.1.1 元素分隔

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

## §18.2 命名规范

### §18.2.1 CSS文件命名

| CSS文件名    | 含义 |
| ------------ | ---- |
| `reset.css`  |      |
| `global.css` |      |
| `theme.css`  |      |
| `module.css` |      |
| `master.css` |      |
| `column.css` |      |
| `form.css`   |      |
| `mend.css`   |      |
| `print.css`  |      |

