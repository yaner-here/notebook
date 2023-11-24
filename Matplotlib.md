# Matplotlib

参考书籍：

- 《matplotlib数据可视化实战》 [豆瓣](https://book.douban.com/subject/36418771/) [清华大学出版社](http://www.tup.tsinghua.edu.cn/booksCenter/book_09904501.html)

Matplotlib是一款Python开源绘图模块，用于生成静态或动态、可交互的图表。

# §1 基础语法



# §2 常用图表绘制

## §2.1 折线图

```python
plt.plot(
    [x: Optional, y, **kwargs]+
)
```

| `**kwargs`参数   | 含义                     | 取值范围 |
| ---------------- | ------------------------ | -------- |
| `linewidth`/`lw` | 折线图线条宽度           | `float`  |
| `linestyle`/`ls` | 折线图线条样式           |          |
| `label`          | 图表标题                 |          |
| `color`/`c`      | 颜色                     |          |
| `marker`         | 数据点样式               |          |
| `zorder`         | 绘制顺序，决定了图层位置 |          |

当`x=[0,1,2,...]`时,则可以忽略x参数：

```python
import numpy as np
import matplotlib.pyplot as plt
plt.plot(
	np.arange(10),
    np.sqrt(np.arange(10))
)
plt.plot(
    # np.arange(10), # 若x=[0,1,2,...],则可以忽略x参数
    np.arange(10) ** 2
)
plt.show()19 1plt.plot(2    np.arange(10),3    np.arange(10).sqrt()4)5plt.plot(6    # np.arange(10), // 若x=[0,1,2,...],则可以忽略x参数7    np.arange(10) ** 28)9plt.show()import numpy as np10import matplotlib.pyplot as plt11plt.plot(12    np.arange(10),13    np.sqrt(np.arange(10))14)15plt.plot(16    # np.arange(10), // 若x=[0,1,2,...],则可以忽略x参数17    np.arange(10) ** 218)19plt.show()
```

也可以让`plt.plot()`一次性绘制多个X/Y数组对：

```python
import numpy as np
import matplotlib.pyplot as plt
plt.plot(
	np.arange(10),
    np.sqrt(np.arange(10)),
    np.arange(10),
    np.arange(10) ** 2
)
plt.show()
```

### §2.1.1 设置线条宽度

#### §2.1.1.1 `linewidth`/`lw`

给`plt.plot()`的`**kwargs`传入`linewidth`/`lw`参数，可以改变线条宽度。

```python
import numpy as np
import matplotlib.pyplot as plt
plt.plot(np.arange(10) ** 2, linewidth=2)
plt.plot(np.arange(10) ** 2.5, linewidth=4)
plt.show()
```

#### §2.1.1.2 `plt.rcParams["lines.linewidth"]`

更改全局变量`plt.rcParams["lines.linewidth"]`，可以全局影响后面绘制的所有的线条宽度。

```
import numpy as np
import matplotlib.pyplot as plt

plt.plot(np.arange(10) ** 2)
plt.rcParams["lines.linewidth"] = 5
plt.plot(np.arange(10) ** 2.5)
plt.show()
```

### §2.1.2 设置线条颜色

#### §2.1.2.1 `color`

给`plt.plot()`的`**kwargs`传入`color`/`c`参数，可以改变线条颜色。

`color`支持很多种颜色格式：

| 颜色格式 | 含义                                                     | 示例                    |
| -------- | -------------------------------------------------------- | ----------------------- |
| `[a-z]`  | 色彩字符，详见[§A.1 RGB颜色名称表](##§A.1 RGB颜色名称表) | `plt.plot(color="w")`   |
| `[a-z]+` | 色彩全名，详见[§A.1 RGB颜色名称表](##§A.1 RGB颜色名称表) | `plt.plot(color="red")` |
|          |                                                          |                         |

`plt.plot()`支持设置多个`color`，给多个线条设置不同的颜色：

```python

```

我们甚至可以省略`color`/`c`，直接向`*args`传入颜色：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.plot(np.arange(10), 'r')
plt.plot(np.arange(10), 'blue')
plt.show()
```



# §A 附录

## §A.1 RGB颜色名称表

| 颜色名称            | RGB编码                                    | 颜色名称               | RGB编码                                    | 颜色名称          | RGB编码                                    |
| ------------------- | ------------------------------------------ | ---------------------- | ------------------------------------------ | ----------------- | ------------------------------------------ |
| `AliceBlue`         | <span style='color:#F0F8FF'>#F0F8FF</span> | `AntiqueWhite`         | <span style='color:#FAEBD7'>#FAEBD7</span> | `Aqua`            | <span style='color:#00FFFF'>#00FFFF</span> |
| `Aquamarine`        | <span style='color:#7FFFD4'>#7FFFD4</span> | `Azure`                | <span style='color:#F0FFFF'>#F0FFFF</span> | `Beige`           | <span style='color:#F5F5DC'>#F5F5DC</span> |
| `Bisque`            | <span style='color:#FFE4C4'>#FFE4C4</span> | `Black`                | <span style='color:#000000'>#000000</span> | `BlanchedAlmond`  | <span style='color:#FFEBCD'>#FFEBCD</span> |
| `Blue`              | <span style='color:#0000FF'>#0000FF</span> | `BlueViolet`           | <span style='color:#8A2BE2'>#8A2BE2</span> | `Brown`           | <span style='color:#A52A2A'>#A52A2A</span> |
| `BurlyWood`         | <span style='color:#DEB887'>#DEB887</span> | `CadetBlue`            | <span style='color:#5F9EA0'>#5F9EA0</span> | `Chartreuse`      | <span style='color:#7FFF00'>#7FFF00</span> |
| `Chocolate`         | <span style='color:#D2691E'>#D2691E</span> | `Coral`                | <span style='color:#FF7F50'>#FF7F50</span> | `CornflowerBlue`  | <span style='color:#6495ED'>#6495ED</span> |
| `Cornsilk`          | <span style='color:#FFF8DC'>#FFF8DC</span> | `Crimson`              | <span style='color:#DC143C'>#DC143C</span> | `Cyan`            | <span style='color:#00FFFF'>#00FFFF</span> |
| `DarkBlue`          | <span style='color:#00008B'>#00008B</span> | `DarkCyan`             | <span style='color:#008B8B'>#008B8B</span> | `DarkGoldenRod`   | <span style='color:#B8860B'>#B8860B</span> |
| `DarkGray`          | <span style='color:#A9A9A9'>#A9A9A9</span> | `DarkGrey`             | <span style='color:#A9A9A9'>#A9A9A9</span> | `DarkGreen`       | <span style='color:#006400'>#006400</span> |
| `DarkKhaki`         | <span style='color:#BDB76B'>#BDB76B</span> | `DarkMagenta`          | <span style='color:#8B008B'>#8B008B</span> | `DarkOliveGreen`  | <span style='color:#556B2F'>#556B2F</span> |
| `DarkOrange`        | <span style='color:#FF8C00'>#FF8C00</span> | `DarkOrchid`           | <span style='color:#9932CC'>#9932CC</span> | `DarkRed`         | <span style='color:#8B0000'>#8B0000</span> |
| `DarkSalmon`        | <span style='color:#E9967A'>#E9967A</span> | `DarkSeaGreen`         | <span style='color:#8FBC8F'>#8FBC8F</span> | `DarkSlateBlue`   | <span style='color:#483D8B'>#483D8B</span> |
| `DarkSlateGray`     | <span style='color:#2F4F4F'>#2F4F4F</span> | `DarkSlateGrey`        | <span style='color:#2F4F4F'>#2F4F4F</span> | `DarkTurquoise`   | <span style='color:#00CED1'>#00CED1</span> |
| `DarkViolet`        | <span style='color:#9400D3'>#9400D3</span> | `DeepPink`             | <span style='color:#FF1493'>#FF1493</span> | `DeepSkyBlue`     | <span style='color:#00BFFF'>#00BFFF</span> |
| `DimGray`           | <span style='color:#696969'>#696969</span> | `DimGrey`              | <span style='color:#696969'>#696969</span> | `DodgerBlue`      | <span style='color:#1E90FF'>#1E90FF</span> |
| `FireBrick`         | <span style='color:#B22222'>#B22222</span> | `FloralWhite`          | <span style='color:#FFFAF0'>#FFFAF0</span> | `ForestGreen`     | <span style='color:#228B22'>#228B22</span> |
| `Fuchsia`           | <span style='color:#FF00FF'>#FF00FF</span> | `Gainsboro`            | <span style='color:#DCDCDC'>#DCDCDC</span> | `GhostWhite`      | <span style='color:#F8F8FF'>#F8F8FF</span> |
| `Gold`              | <span style='color:#FFD700'>#FFD700</span> | `GoldenRod`            | <span style='color:#DAA520'>#DAA520</span> | `Gray`            | <span style='color:#808080'>#808080</span> |
| `Grey`              | <span style='color:#808080'>#808080</span> | `Green`                | <span style='color:#008000'>#008000</span> | `GreenYellow`     | <span style='color:#ADFF2F'>#ADFF2F</span> |
| `HoneyDew`          | <span style='color:#F0FFF0'>#F0FFF0</span> | `HotPink`              | <span style='color:#FF69B4'>#FF69B4</span> | `IndianRed`       | <span style='color:#CD5C5C'>#CD5C5C</span> |
| `Indigo`            | <span style='color:#4B0082'>#4B0082</span> | `Ivory`                | <span style='color:#FFFFF0'>#FFFFF0</span> | `Khaki`           | <span style='color:#F0E68C'>#F0E68C</span> |
| `Lavender`          | <span style='color:#E6E6FA'>#E6E6FA</span> | `LavenderBlush`        | <span style='color:#FFF0F5'>#FFF0F5</span> | `LawnGreen`       | <span style='color:#7CFC00'>#7CFC00</span> |
| `LemonChiffon`      | <span style='color:#FFFACD'>#FFFACD</span> | `LightBlue`            | <span style='color:#ADD8E6'>#ADD8E6</span> | `LightCoral`      | <span style='color:#F08080'>#F08080</span> |
| `LightCyan`         | <span style='color:#E0FFFF'>#E0FFFF</span> | `LightGoldenRodYellow` | <span style='color:#FAFAD2'>#FAFAD2</span> | `LightGray`       | <span style='color:#D3D3D3'>#D3D3D3</span> |
| `LightGrey`         | <span style='color:#D3D3D3'>#D3D3D3</span> | `LightGreen`           | <span style='color:#90EE90'>#90EE90</span> | `LightPink`       | <span style='color:#FFB6C1'>#FFB6C1</span> |
| `LightSalmon`       | <span style='color:#FFA07A'>#FFA07A</span> | `LightSeaGreen`        | <span style='color:#20B2AA'>#20B2AA</span> | `LightSkyBlue`    | <span style='color:#87CEFA'>#87CEFA</span> |
| `LightSlateGray`    | <span style='color:#778899'>#778899</span> | `LightSlateGrey`       | <span style='color:#778899'>#778899</span> | `LightSteelBlue`  | <span style='color:#B0C4DE'>#B0C4DE</span> |
| `LightYellow`       | <span style='color:#FFFFE0'>#FFFFE0</span> | `Lime`                 | <span style='color:#00FF00'>#00FF00</span> | `LimeGreen`       | <span style='color:#32CD32'>#32CD32</span> |
| `Linen`             | <span style='color:#FAF0E6'>#FAF0E6</span> | `Magenta`              | <span style='color:#FF00FF'>#FF00FF</span> | `Maroon`          | <span style='color:#800000'>#800000</span> |
| `MediumAquaMarine`  | <span style='color:#66CDAA'>#66CDAA</span> | `MediumBlue`           | <span style='color:#0000CD'>#0000CD</span> | `MediumOrchid`    | <span style='color:#BA55D3'>#BA55D3</span> |
| `MediumPurple`      | <span style='color:#9370DB'>#9370DB</span> | `MediumSeaGreen`       | <span style='color:#3CB371'>#3CB371</span> | `MediumSlateBlue` | <span style='color:#7B68EE'>#7B68EE</span> |
| `MediumSpringGreen` | <span style='color:#00FA9A'>#00FA9A</span> | `MediumTurquoise`      | <span style='color:#48D1CC'>#48D1CC</span> | `MediumVioletRed` | <span style='color:#C71585'>#C71585</span> |
| `MidnightBlue`      | <span style='color:#191970'>#191970</span> | `MintCream`            | <span style='color:#F5FFFA'>#F5FFFA</span> | `MistyRose`       | <span style='color:#FFE4E1'>#FFE4E1</span> |
| `Moccasin`          | <span style='color:#FFE4B5'>#FFE4B5</span> | `NavajoWhite`          | <span style='color:#FFDEAD'>#FFDEAD</span> | `Navy`            | <span style='color:#000080'>#000080</span> |
| `OldLace`           | <span style='color:#FDF5E6'>#FDF5E6</span> | `Olive`                | <span style='color:#808000'>#808000</span> | `OliveDrab`       | <span style='color:#6B8E23'>#6B8E23</span> |
| `Orange`            | <span style='color:#FFA500'>#FFA500</span> | `OrangeRed`            | <span style='color:#FF4500'>#FF4500</span> | `Orchid`          | <span style='color:#DA70D6'>#DA70D6</span> |
| `PaleGoldenRod`     | <span style='color:#EEE8AA'>#EEE8AA</span> | `PaleGreen`            | <span style='color:#98FB98'>#98FB98</span> | `PaleTurquoise`   | <span style='color:#AFEEEE'>#AFEEEE</span> |
| `PaleVioletRed`     | <span style='color:#DB7093'>#DB7093</span> | `PapayaWhip`           | <span style='color:#FFEFD5'>#FFEFD5</span> | `PeachPuff`       | <span style='color:#FFDAB9'>#FFDAB9</span> |
| `Peru`              | <span style='color:#CD853F'>#CD853F</span> | `Pink`                 | <span style='color:#FFC0CB'>#FFC0CB</span> | `Plum`            | <span style='color:#DDA0DD'>#DDA0DD</span> |
| `PowderBlue`        | <span style='color:#B0E0E6'>#B0E0E6</span> | `Purple`               | <span style='color:#800080'>#800080</span> | `RebeccaPurple`   | <span style='color:#663399'>#663399</span> |
| `Red`               | <span style='color:#FF0000'>#FF0000</span> | `RosyBrown`            | <span style='color:#BC8F8F'>#BC8F8F</span> | `RoyalBlue`       | <span style='color:#4169E1'>#4169E1</span> |
| `SaddleBrown`       | <span style='color:#8B4513'>#8B4513</span> | `Salmon`               | <span style='color:#FA8072'>#FA8072</span> | `SandyBrown`      | <span style='color:#F4A460'>#F4A460</span> |
| `SeaGreen`          | <span style='color:#2E8B57'>#2E8B57</span> | `SeaShell`             | <span style='color:#FFF5EE'>#FFF5EE</span> | `Sienna`          | <span style='color:#A0522D'>#A0522D</span> |
| `Silver`            | <span style='color:#C0C0C0'>#C0C0C0</span> | `SkyBlue`              | <span style='color:#87CEEB'>#87CEEB</span> | `SlateBlue`       | <span style='color:#6A5ACD'>#6A5ACD</span> |
| `SlateGray`         | <span style='color:#708090'>#708090</span> | `SlateGrey`            | <span style='color:#708090'>#708090</span> | `Snow`            | <span style='color:#FFFAFA'>#FFFAFA</span> |
| `SpringGreen`       | <span style='color:#00FF7F'>#00FF7F</span> | `SteelBlue`            | <span style='color:#4682B4'>#4682B4</span> | `Tan`             | <span style='color:#D2B48C'>#D2B48C</span> |
| `Teal`              | <span style='color:#008080'>#008080</span> | `Thistle`              | <span style='color:#D8BFD8'>#D8BFD8</span> | `Tomato`          | <span style='color:#FF6347'>#FF6347</span> |
| `Turquoise`         | <span style='color:#40E0D0'>#40E0D0</span> | `Violet`               | <span style='color:#EE82EE'>#EE82EE</span> | `Wheat`           | <span style='color:#F5DEB3'>#F5DEB3</span> |
| `White`             | <span style='color:#FFFFFF'>#FFFFFF</span> | `WhiteSmoke`           | <span style='color:#F5F5F5'>#F5F5F5</span> | `Yellow`          | <span style='color:#FFFF00'>#FFFF00</span> |
| `YellowGreen`       | <span style='color:#9ACD32'>#9ACD32</span> |                        |                                            |                   |                                            |

| 颜色简写名称 | 含义  | 颜色简写名称 | 含义    | 颜色简写名称 | 含义  |
| ------------ | ----- | ------------ | ------- | ------------ | ----- |
| `b`          | blue  | `c`          | cyan    | `g`          | green |
| `k`          | black | `m`          | magenta | `r`          | red   |
| `w`          | white | `y`          | yellow  |              |       |

