# Matplotlib

参考书籍：

- 《matplotlib数据可视化实战》 [豆瓣](https://book.douban.com/subject/36418771/) [清华大学出版社](http://www.tup.tsinghua.edu.cn/booksCenter/book_09904501.html)

Matplotlib是一款Python开源绘图模块，用于生成静态或动态、可交互的图表。

# §1 基础语法

## §1.1 `plt.rcParams`

`plt.rcParams`是Matplotlib提供的全局性字典`collections.abc.KeysView`，加载了绘图的所有全局属性。

```python
import matplotlib.pyplot as plt
print(plt.rcParams.keys())
"""
KeysView(RcParams({'_internal.classic_mode': False,
          'agg.path.chunksize': 0,
          'animation.bitrate': -1,
          'animation.codec': 'h264',
          'animation.convert_args': ['-layers', 'OptimizePlus'],
          'animation.convert_path': 'convert',
          'animation.embed_limit': 20.0,
          'animation.ffmpeg_args': [],
          'animation.ffmpeg_path': 'ffmpeg',
          'animation.frame_format': 'png',
          'animation.html': 'none',
          'animation.writer': 'ffmpeg',
          'axes.autolimit_mode': 'data',
          'axes.axisbelow': 'line',
          'axes.edgecolor': 'black',
          'axes.facecolor': 'white',
          'axes.formatter.limits': [-5, 6],
          'axes.formatter.min_exponent': 0,
          'axes.formatter.offset_threshold': 4,
          'axes.formatter.use_locale': False,
          'axes.formatter.use_mathtext': False,
          'axes.formatter.useoffset': True,
          'axes.grid': False,
          'axes.grid.axis': 'both',
          'axes.grid.which': 'major',
          'axes.labelcolor': 'black',
          'axes.labelpad': 4.0,
          'axes.labelsize': 'medium',
          'axes.labelweight': 'normal',
          'axes.linewidth': 0.8,
          'axes.prop_cycle': cycler('color', ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd', '#8c564b', '#e377c2', '#7f7f7f', '#bcbd22', '#17becf']),
          'axes.spines.bottom': True,
          'axes.spines.left': True,
          'axes.spines.right': True,
          'axes.spines.top': True,
          'axes.titlecolor': 'auto',
          'axes.titlelocation': 'center',
          'axes.titlepad': 6.0,
          'axes.titlesize': 'large',
          'axes.titleweight': 'normal',
          'axes.titley': None,
          'axes.unicode_minus': True,
          'axes.xmargin': 0.05,
          'axes.ymargin': 0.05,
          'axes.zmargin': 0.05,
          'axes3d.grid': True,
          'axes3d.xaxis.panecolor': (0.95, 0.95, 0.95, 0.5),          'axes3d.yaxis.panecolor': (0.9, 0.9, 0.9, 0.5),   
          'axes3d.zaxis.panecolor': (0.925, 0.925, 0.925, 0.5),
          'backend': 'TkAgg',
          'backend_fallback': True,
          'boxplot.bootstrap': None,
          'boxplot.boxprops.color': 'black',
          'boxplot.boxprops.linestyle': '-',
          'boxplot.boxprops.linewidth': 1.0,
          'boxplot.capprops.color': 'black',
          'boxplot.capprops.linestyle': '-',
          'boxplot.capprops.linewidth': 1.0,
          'boxplot.flierprops.color': 'black',
          'boxplot.flierprops.linestyle': 'none',
          'boxplot.flierprops.linewidth': 1.0,
          'boxplot.flierprops.marker': 'o',
          'boxplot.flierprops.markeredgecolor': 'black',    
          'boxplot.flierprops.markeredgewidth': 1.0,        
          'boxplot.flierprops.markerfacecolor': 'none',     
          'boxplot.flierprops.markersize': 6.0,
          'boxplot.meanline': False,
          'boxplot.meanprops.color': 'C2',
          'boxplot.meanprops.linestyle': '--',
          'boxplot.meanprops.linewidth': 1.0,
          'boxplot.meanprops.marker': '^',
          'boxplot.meanprops.markeredgecolor': 'C2',        
          'boxplot.meanprops.markerfacecolor': 'C2',        
          'boxplot.meanprops.markersize': 6.0,
          'boxplot.medianprops.color': 'C1',
          'boxplot.medianprops.linestyle': '-',
          'boxplot.medianprops.linewidth': 1.0,
          'boxplot.notch': False,
          'boxplot.patchartist': False,
          'boxplot.showbox': True,
          'boxplot.showcaps': True,
          'boxplot.showfliers': True,
          'boxplot.showmeans': False,
          'boxplot.vertical': True,
          'boxplot.whiskerprops.color': 'black',
          'boxplot.whiskerprops.linestyle': '-',
          'boxplot.whiskerprops.linewidth': 1.0,
          'boxplot.whiskers': 1.5,
          'contour.algorithm': 'mpl2014',
          'contour.corner_mask': True,
          'contour.linewidth': None,
          'contour.negative_linestyle': 'dashed',
          'date.autoformatter.day': '%Y-%m-%d',
          'date.autoformatter.hour': '%m-%d %H',
          'date.autoformatter.microsecond': '%M:%S.%f',     
          'date.autoformatter.minute': '%d %H:%M',
          'date.autoformatter.month': '%Y-%m',
          'date.autoformatter.second': '%H:%M:%S',
          'date.autoformatter.year': '%Y',
          'date.converter': 'auto',
          'date.epoch': '1970-01-01T00:00:00',
          'date.interval_multiples': True,
          'docstring.hardcopy': False,
          'errorbar.capsize': 0.0,
          'figure.autolayout': False,
          'figure.constrained_layout.h_pad': 0.04167,       
          'figure.constrained_layout.hspace': 0.02,
          'figure.constrained_layout.use': False,
          'figure.constrained_layout.w_pad': 0.04167,       
          'figure.constrained_layout.wspace': 0.02,
          'figure.dpi': 100.0,
          'figure.edgecolor': 'white',
          'figure.facecolor': 'white',
          'figure.figsize': [6.4, 4.8],
          'figure.frameon': True,
          'figure.hooks': [],
          'figure.labelsize': 'large',
          'figure.labelweight': 'normal',
          'figure.max_open_warning': 20,
          'figure.raise_window': True,
          'figure.subplot.bottom': 0.11,
          'figure.subplot.hspace': 0.2,
          'figure.subplot.left': 0.125,
          'figure.subplot.right': 0.9,
          'figure.subplot.top': 0.88,
          'figure.subplot.wspace': 0.2,
          'figure.titlesize': 'large',
          'figure.titleweight': 'normal',
          'font.cursive': ['Apple Chancery',
                           'Textile',
                           'Zapf Chancery',
                           'Sand',
                           'Script MT',
                           'Felipa',
                           'Comic Neue',
                           'Comic Sans MS',
                           'cursive'],
          'font.family': ['sans-serif'],
          'font.fantasy': ['Chicago',
                           'Charcoal',
                           'Impact',
                           'Western',
                           'Humor Sans',
                           'xkcd',
                           'fantasy'],
          'font.monospace': ['DejaVu Sans Mono',
                             'Bitstream Vera Sans Mono',    
                             'Computer Modern Typewriter',  
                             'Andale Mono',
                             'Nimbus Mono L',
                             'Courier New',
                             'Courier',
                             'Fixed',
                             'Terminal',
                             'monospace'],
          'font.sans-serif': ['DejaVu Sans',
                              'Bitstream Vera Sans',        
                              'Computer Modern Sans Serif', 
                              'Lucida Grande',
                              'Verdana',
                              'Geneva',
                              'Lucid',
                              'Arial',
                              'Helvetica',
                              'Avant Garde',
                              'sans-serif'],
          'font.serif': ['DejaVu Serif',
                         'Bitstream Vera Serif',
                         'Computer Modern Roman',
                         'New Century Schoolbook',
                         'Century Schoolbook L',
                         'Utopia',
                         'ITC Bookman',
                         'Bookman',
                         'Nimbus Roman No9 L',
                         'Times New Roman',
                         'Times',
                         'Palatino',
                         'Charter',
                         'serif'],
          'font.size': 10.0,
          'font.stretch': 'normal',
          'font.style': 'normal',
          'font.variant': 'normal',
          'font.weight': 'normal',
          'grid.alpha': 1.0,
          'grid.color': '#b0b0b0',
          'grid.linestyle': '-',
          'grid.linewidth': 0.8,
          'hatch.color': 'black',
          'hatch.linewidth': 1.0,
          'hist.bins': 10,
          'image.aspect': 'equal',
          'image.cmap': 'viridis',
          'image.composite_image': True,
          'image.interpolation': 'antialiased',
          'image.lut': 256,
          'image.origin': 'upper',
          'image.resample': True,
          'interactive': False,
          'keymap.back': ['left', 'c', 'backspace', 'MouseButton.BACK'],
          'keymap.copy': ['ctrl+c', 'cmd+c'],
          'keymap.forward': ['right', 'v', 'MouseButton.FORWARD'],
          'keymap.fullscreen': ['f', 'ctrl+f'],
          'keymap.grid': ['g'],
          'keymap.grid_minor': ['G'],
          'keymap.help': ['f1'],
          'keymap.home': ['h', 'r', 'home'],
          'keymap.pan': ['p'],
          'keymap.quit': ['ctrl+w', 'cmd+w', 'q'],
          'keymap.quit_all': [],
          'keymap.save': ['s', 'ctrl+s'],
          'keymap.xscale': ['k', 'L'],
          'keymap.yscale': ['l'],
          'keymap.zoom': ['o'],
          'legend.borderaxespad': 0.5,
          'legend.borderpad': 0.4,
          'legend.columnspacing': 2.0,
          'legend.edgecolor': '0.8',
          'legend.facecolor': 'inherit',
          'legend.fancybox': True,
          'legend.fontsize': 'medium',
          'legend.framealpha': 0.8,
          'legend.frameon': True,
          'legend.handleheight': 0.7,
          'legend.handlelength': 2.0,
          'legend.handletextpad': 0.8,
          'legend.labelcolor': 'None',
          'legend.labelspacing': 0.5,
          'legend.loc': 'best',
          'legend.markerscale': 1.0,
          'legend.numpoints': 1,
          'legend.scatterpoints': 1,
          'legend.shadow': False,
          'legend.title_fontsize': None,
          'lines.antialiased': True,
          'lines.color': 'C0',
          'lines.dash_capstyle': <CapStyle.butt: 'butt'>,   
          'lines.dash_joinstyle': <JoinStyle.round: 'round'>,
          'lines.dashdot_pattern': [6.4, 1.6, 1.0, 1.6],    
          'lines.dashed_pattern': [3.7, 1.6],
          'lines.dotted_pattern': [1.0, 1.65],
          'lines.linestyle': '-',
          'lines.linewidth': 1.5,
          'lines.marker': 'None',
          'lines.markeredgecolor': 'auto',
          'lines.markeredgewidth': 1.0,
          'lines.markerfacecolor': 'auto',
          'lines.markersize': 6.0,
          'lines.scale_dashes': True,
          'lines.solid_capstyle': <CapStyle.projecting: 'projecting'>,
          'lines.solid_joinstyle': <JoinStyle.round: 'round'>,
          'macosx.window_mode': 'system',
          'markers.fillstyle': 'full',
          'mathtext.bf': 'sans:bold',
          'mathtext.bfit': 'sans:italic:bold',
          'mathtext.cal': 'cursive',
          'mathtext.default': 'it',
          'mathtext.fallback': 'cm',
          'mathtext.fontset': 'dejavusans',
          'mathtext.it': 'sans:italic',
          'mathtext.rm': 'sans',
          'mathtext.sf': 'sans',
          'mathtext.tt': 'monospace',
          'patch.antialiased': True,
          'patch.edgecolor': 'black',
          'patch.facecolor': 'C0',
          'patch.force_edgecolor': False,
          'patch.linewidth': 1.0,
          'path.effects': [],
          'path.simplify': True,
          'path.simplify_threshold': 0.111111111111,        
          'path.sketch': None,
          'path.snap': True,
          'pcolor.shading': 'auto',
          'pcolormesh.snap': True,
          'pdf.compression': 6,
          'pdf.fonttype': 3,
          'pdf.inheritcolor': False,
          'pdf.use14corefonts': False,
          'pgf.preamble': '',
          'pgf.rcfonts': True,
          'pgf.texsystem': 'xelatex',
          'polaraxes.grid': True,
          'ps.distiller.res': 6000,
          'ps.fonttype': 3,
          'ps.papersize': 'letter',
          'ps.useafm': False,
          'ps.usedistiller': None,
          'savefig.bbox': None,
          'savefig.directory': '~',
          'savefig.dpi': 'figure',
          'savefig.edgecolor': 'auto',
          'savefig.facecolor': 'auto',
          'savefig.format': 'png',
          'savefig.orientation': 'portrait',
          'savefig.pad_inches': 0.1,
          'savefig.transparent': False,
          'scatter.edgecolors': 'face',
          'scatter.marker': 'o',
          'svg.fonttype': 'path',
          'svg.hashsalt': None,
          'svg.image_inline': True,
          'text.antialiased': True,
          'text.color': 'black',
          'text.hinting': 'force_autohint',
          'text.hinting_factor': 8,
          'text.kerning_factor': 0,
          'text.latex.preamble': '',
          'text.parse_math': True,
          'text.usetex': False,
          'timezone': 'UTC',
          'tk.window_focus': False,
          'toolbar': 'toolbar2',
          'webagg.address': '127.0.0.1',
          'webagg.open_in_browser': True,
          'webagg.port': 8988,
          'webagg.port_retries': 50,
          'xaxis.labellocation': 'center',
          'xtick.alignment': 'center',
          'xtick.bottom': True,
          'xtick.color': 'black',
          'xtick.direction': 'out',
          'xtick.labelbottom': True,
          'xtick.labelcolor': 'inherit',
          'xtick.labelsize': 'medium',
          'xtick.labeltop': False,
          'xtick.major.bottom': True,
          'xtick.major.pad': 3.5,
          'xtick.major.size': 3.5,
          'xtick.major.top': True,
          'xtick.major.width': 0.8,
          'xtick.minor.bottom': True,
          'xtick.minor.ndivs': 'auto',
          'xtick.minor.pad': 3.4,
          'xtick.minor.size': 2.0,
          'xtick.minor.top': True,
          'xtick.minor.visible': False,
          'xtick.minor.width': 0.6,
          'xtick.top': False,
          'yaxis.labellocation': 'center',
          'ytick.alignment': 'center_baseline',
          'ytick.color': 'black',
          'ytick.direction': 'out',
          'ytick.labelcolor': 'inherit',
          'ytick.labelleft': True,
          'ytick.labelright': False,
          'ytick.labelsize': 'medium',
          'ytick.left': True,
          'ytick.major.left': True,
          'ytick.major.pad': 3.5,
          'ytick.major.right': True,
          'ytick.major.size': 3.5,
          'ytick.major.width': 0.8,
          'ytick.minor.left': True,
          'ytick.minor.ndivs': 'auto',
          'ytick.minor.pad': 3.4,
          'ytick.minor.right': True,
          'ytick.minor.size': 2.0,
          'ytick.minor.visible': False,
          'ytick.minor.width': 0.6,
          'ytick.right': False}))
"""
```

## §1.2 坐标轴

### §1.2.1 `plt.plot()`

Matplotlib使用`plt.plot()`来配置坐标轴。

```python
plt.plot(
    arg: 
    	list[xmin: float, xmax: float, ymin: float, ymax: float] |
    	Literal["off", "on", "equal", "scaled", "tight", "auto", "image", "square"] | 
    	bool
) -> tuple[float, float, float, float]
```

向`plt.plot()`传入一个`list[float, float, float, float]`，用于限制坐标范围：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.axis([1, 9, -5, 100])
plt.plot(np.arange(10) ** 2)
plt.show()
```

`plt.axis()`返回一个四元组，表示图像的坐标范围：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.plot(np.arange(10) ** 2)
print(plt.axis()) # (-0.45, 9.45, -4.05, 85.05)
```

### §1.2.2 `plt.axis()`

`plt.axis()`用于设置坐标轴的范围。

```python
plt.axis(
	[xmin, xmax, ymin, ymax]
) -> tuple[float, float, float, float]
```

### §1.2.3 `plt.xlim()`/`plt.ylim()`

 `plt.xlim()`/`plt.ylim()`用于单独设置X轴和Y轴的范围，用法与`plt.axis()`类似。

```python
plt.xlim/ylim(tuple[min: float, max: float]) -> tuple[float, float]
plt.xlim(left: float, right: float) -> tuple[float, float]
plt.ylim(bottom: float, top: float) -> tuple[float, float]
```

```python
import numpy as np
import matplotlib.pyplot as plt

plt.xlim([1, 9])
plt.ylim(-5, 100)
plt.plot(np.arange(10) ** 2)
plt.show()
print(plt.axis()) # (-0.45, 9.45, -4.05, 85.05)
```

### §1.2.4 `plt.xticks()`/``plt.yticks()``

`plt.xticks()`/`plt.yticks()`用于改变X轴/Y轴的刻度标签的**内容和一部分样式**。

```python
plt.xticks(
	ticks: Optional[ARRAY_LIKE] = None,
    labels: Optional[ARRAY_LIKE] = None,
    minor: bool = False
    **kwargs: {
    	rotation: float | "vertical" | "horizontal",
        color: COLOR_LIKE,
        fontsize: float | Literal["xx-small", "x-small", "small", "medium", "large", "x-large", "xx-large"],
        # ......
    }
) -> (locs: numpy.ndarray, labels: list[matplotlib.text.Text])
```

`plt.xticks()`/`plt.yticks()`同时传入`ticks`和`labels`时，要求`len(ticks)==len(labels)`，从而将`ticks`中的刻度全替换为`labels`。

```python
import numpy as np
import matplotlib.pyplot as plt

x_data = [2021, 2022, 2023]
x_label = ["二零二一年", "二零二二年", "二零二三年"]
y_data = np.random.rand(3, 3)

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.xticks(x_data, x_label, rotation=15.5, color="red")
plt.plot(x_data, y_data[0], x_data, y_data[1], x_data, y_data[2])
plt.show()
```

从上面的描述中，我们也可以意识到，`len(labels)`用于控制刻度的数量，`labels[i+1]-labels[i]`用于控制刻度之间代表的实际间隔。

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 2 * np.pi, 1000)
y = np.sin(x)
x_label = np.arange(0, 10, 1)
y_label = np.linspace(-2, 2, 21)

plt.plot(x, y)
plt.xticks(x_label) # 10个刻度,间隔为1
plt.yticks(y_label) # 20个刻度,间隔为0.2
plt.show()
```

> 注意：`plt.xticks()`/`plt.yticks()`中的`fontsize`参数，对应着`plt.rcParams["xtick.labelsize"]`/`plt.rcParams["ytick.labelsize"]`。

### §1.2.5 `plt.tick_params()`

`plt.tick_params()`用于设定坐标轴的**所有样式**，包括刻度字体大小、颜色、方向等。

```python
plt.tick_params(
	axis: Literal["both", "x", "y"] = "both",
    **kwargs: {
    	which: Literal["major", "minor", "both"] = "major", # 设置的刻度线类别
        direction: Literal["in", "out", "inout"] = "out", # 刻度线位置
		reset: bool = False, # 应用样式之后是否要重置刻度
        length: float, # 刻度线长度(单位为点数)
        width: float, # 刻度线宽度(单位为点数)
        color: COLOR_LIKE, # 刻度线颜色
        pad: float, # 刻度线与标签之间的距离(单位为点数)
        labelsize: float | str, # 标签字体大小
        labelcolor: COLOR_LIKE, # 标签文字颜色
        labelfontfamily: str, # 标签文字字体
        colors: COLOR_LIKE, # 刻度线颜色和标签文字颜色
        zorder: float, # 刻度线颜色和标签文字的图层位置
        bottom/top/left/right: bool, # 是否绘制指定位置的刻度线
        labelbottom/labeltop/labelleft/labelright: bool, # 是否绘制指定位置的标签
        labelrotation: float, # 标签旋转角度
        grid_color: COLOR_LIKE, # 网格线颜色
        grid_alpha: float, # 网格线透明度
        grid_linewidth: float, # 网格线宽度(单位为点数)
        grid_linestyle: str # 网格线样式
    }
)
```

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 2 * np.pi, 100)
y = np.sin(x)

plt.plot(x, y)
plt.tick_params(axis='x', direction="in", length=8, width=3, color="red")
plt.tick_params(axis='y', direction="out", pad=3, labelsize="20", labelcolor="red")
plt.show()
```

## §1.3 图例(`plt.legend()`)

`plt.legend()`用于设定图例。

```python
plt.legend(
	*args: {
    	handles: Optional[typing.Iterable[matplotlib.lines.Line2D]],
        labels: Optional[typing.Iterable[typing.Iterable[str]]]
    },
    **kwargs
)
```

| `plt.legend()`形参 | 作用                                                         | 数据类型                                                     | `plt.rcParams`对应属性                  |
| ------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | --------------------------------------- |
| `loc`              | 图例的位置                                                   | `str | int`<br />其中`"best" => 0`(缺省)<br />`"upper right" => 1`<br />`"upper left" => 2` <br />`"lower left" => 3`<br />`"lower right" => 4`<br />`"right"/"center right" => 5`<br />`"center left" => 6`<br />`"center right" => 7`<br />`"lower center" => 8`<br />`"upper center" => 9`<br />`"center" => 10`<br /> | `plt.rcParams["legend.loc"]`            |
| `prop`             | 图例字体属性                                                 | `None | dict | matplotlib.font_manager.FontProperties = None` |                                         |
| `title_fontsize`   | 图例字体大小                                                 | `= None`                                                     | `plt.rcParams["legend.title_fontsize"]` |
| `markerscale`      | 图例标记大小缩放比例                                         | `float = 1.0`                                                | `plt.rcParams["legend.markerscale"]`    |
| `markerfirst`      | 图例标记是否位于文字左边                                     | `bool = True`                                                |                                         |
| `numpoints`        | 线条图例标记点数                                             | `int = 1`                                                    | `plt.rcParams["legend.numpoints"]`      |
| `scatterpoints`    | 散点图图例标记点数                                           | `int = 1`                                                    | `plt.rcParams["legend.scatterpoints"]`  |
| `frameon`          | 图例是否含有边框                                             | `bool: True`                                                 | `plt.rcParams["legend.frameon"]`        |
| `framealpha`       | 图例边框透明度                                               | `float: 0.8`                                                 | `plt.rcParams["legend.framealpha"]`     |
| `edgecolor`        | 图例边框颜色                                                 | `Literal["inherit"] | COLOR_LIKE = 0.8`                      |                                         |
| `facecolor`        | 图例边框内的背景颜色                                         | `Literal["inherit"] | COLOR_LIKE = "interit"`                | `plt.rcParams["legend.facecolor"]`      |
| `shadow`           | 图例是否有阴影                                               | `None | bool | dict = False`                                 | `plt.rcParams["legend.shadow"]`         |
| `borderpad`        | 图例边框内边距                                               | `float = 0.4`                                                | `plt.rcParams["legend.borderpad"]`      |
| `labelspacing`     | 图例项目之间的间距                                           | `float = 0.5`                                                | `plt.rcParams["legend.labelspacing"]`   |
| `handleheight`     | 图例句柄高度                                                 | `float = 0.7`                                                | `plt.rcParams["legend.handleheight"]`   |
| `handlelength`     | 图例句柄长度                                                 | `float = 2.0`                                                | `plt.rcParams["legend.handlelength"]`   |
| `handletextpad`    | 图例句柄和文本之间的间距                                     | `float = 0.8`                                                | `plt.rcParams["legend.handletextpad"]`  |
| `handleaxespad`    | 轴和图例边框之间的间距                                       | `float = 0.5`                                                | `plt.rcParams["legend.handleaxespad"]`  |
| `ncol`             | 图例的字段数                                                 | `int = 1`                                                    |                                         |
| `columnspacing`    | 字段之间的间距                                               | `float = 2.0`                                                | `plt.rcParams["legend.columnspacing"]`  |
| `bbox_to_anchor`   | 以图例左下角为`(0,0)`，右上角为`(1,1)`,建立相对坐标系。`bbox_to_anchor`使用该相对坐标，决定图例矩形框左上角的位置。(与`loc`不能同时用) | `tuple[float, float] | tuple[float, float, float, float]`    |                                         |
| `title`            | 图例标题                                                     | `str | None`                                                 |                                         |

调用`plt.legend()`用于创建所有曲线的图例，`plt.plot(label="...")`用于指定图例的标签文字，里面传入的参数用于控制图例样式：

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 2 * np.pi, 20)
y = [np.sin(x), np.cos(x), np.square(x)]

plt.plot(x, y[0], marker="o", label="sin(x)")
plt.plot(x, y[1], marker="v", label="cos(x)")
plt.plot(x, y[2], marker="x", label="x^2")

plt.legend(
    loc = 6, edgecolor = "black", facecolor = "#66ccff", numpoints = 2, frameon = True,
    shadow = True, title = "Legend Title"
)
plt.show()
```

使用`plt.legend(*args)`中的`handles`和`labels`，可以指定需要图例的曲线，并为其指定标签文字：

```python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.lines

x = np.linspace(0, 2 * np.pi, 20)
y = [np.sin(x), np.cos(x), np.square(x)]

line: list[matplotlib.lines.Line2D] = [
    plt.plot(x, y[0], marker="o", label="sin(x)")[0],
    plt.plot(x, y[1], marker="v", label="cos(x)")[0],
    plt.plot(x, y[2], marker="x", label="x^2")[0]
]

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.legend([line[0], line[1]], ["正弦", "余弦"])
plt.show()
```

一个图表默认只有一个图例。如果要显示两个图例，我们需要使用`plt.gca()`获取子图，然后对子图使用`.add_artist()`添加子图的图例，最后在主图中添加图例：

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 2 * np.pi, 20)
y = [np.sin(x), np.cos(x)]
line = [
    plt.plot(x, y[0], marker="o", label="sin(x)")[0],
    plt.plot(x, y[1], marker="v", label="cos(x)")[0],
]

plt.gca().add_artist(plt.legend(handles=[line[0]], loc=1))
plt.legend(handles=[line[1]], loc=4)

plt.show()
```

## §1.4 网格（`plt.grid()`）

`plt,plot()`用于绘制网格。网格可以是十字正交、十字斜交、维度曲线网格等。

```python
plt.plot(
	visible: Optional[bool | None] = None,
    which: Optional["major", "minor", "both"] = "both",
    axis: Optional[Literal["both", "x", "y"]] = "both",
    **kwargs: {
        matplotlib.lines.Line2D
    }
)
```

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 2 * np.pi, 20)
plt.plot(x, np.sin(x), marker="o", label="sin(x)")[0],
plt.plot(x, np.cos(x), marker="v", label="cos(x)")[0],

plt.grid(True, "major", "both", color="#dddddd", linestyle="--", linewidth="1")

plt.show()
```

## §1.5 参考线

### §1.5.1 水平/垂直参考线(`plt.axhline()`/`plt.axvline()`)

`plt.axhline()`/`plt.axvline()`用于绘制水平/垂直参考线。其实从本质来说，网格就是按照一定规则自动生成的参考线。这里我们用`plt.axhline()`/`plt.axvline()`创建的参考线需要手动指定。

```python
plt.axhline(
	y: float = 0,
    xmin: float = 0, # 绝对坐标
    xmax: float = 1, # 绝对坐标
    **kwargs: {
    	matplotlib.lines.Line2D
    }
) -> matplotlib.lines.Line2D

plt.avhline(
	x: float = 0,
    ymin: float = 0, # 绝对坐标
    ymax: float = 1, # 绝对坐标
    **kwargs: {
    	matplotlib.lines.Line2D
    }
) -> matplotlib.lines.Line2D
```

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 2 * np.pi, 20)
plt.plot(x, np.sin(x), marker="o", label="sin(x)")
plt.plot(x, np.cos(x), marker="v", label="cos(x)")

plt.axhline(0, 0, 1, color="#aaaaaa", linewidth=0.5, linestyle="--")
plt.axhline(-1, 0.5, 1, color="#999999", linewidth=0.5, linestyle="--")
plt.axhline(1, 0, 0.5, color="#888888", linewidth=0.5, linestyle="--")
plt.axvline(np.pi * 0, 0, 1, color="#aaaaaa", linewidth=0.5, linestyle="--")
plt.axvline(np.pi * 1, 0.5, 1, color="#999999", linewidth=0.5, linestyle="--")
plt.axvline(np.pi * 2, 0, 0.5, color="#888888", linewidth=0.5, linestyle="--")

plt.show()
```

### §1.5.2 无限长参考线(`plt.axline()`)

`plt.axline()`用于绘制斜的参考线，在确定直线的方式中，支持两点式和点斜式。

```python
plt.axline(
	xy1: tuple[float, float],
    xy2: tuple[float, float] | None, *,
    slope: float | None,
    **kwargs
)
```

```python
import typing, typing_extensions
import matplotlib.lines

import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-5, 5, 100)
y = 1 / (1 + np.exp(-x))

plt.plot(x, y)
plt.axhline(0.5, ls="-.", lw=0.5, c="gray")
plt.axvline(0, ls="-.", lw=0.5, c="gray")
plt.axline((0, 0.5), slope=0.25, lw=1, ls="--", c="black")
plt.show()
```

## §1.6 参考区域

### §1.6.1 水平/垂直参考区域(`plt.axhspan()`/`plt.axvspan()`)

`plt.axhspan()`/`plt.axvspan()`用于绘制水平/垂直参考区域。

```python
plt.axhspan(
	ymin: float, # 绝对坐标
    ymax: float, # 绝对坐标
    xmin: float = 0, 
    xmax: float = 1,
    **kwargs: { <matplotlib.patches.Polygon>
		alpha: float(0, 1) | None = None,
		color: COLOR_LIKE, # 没有简写"c"!
		edgecolor/ec: COLOR_LIKE,
		facecolor/fc: COLOR_LIKE,
		linestyle/ls: str = "-",
		linewidth/lw: float | None = None,
		zorder: float = 0
    }
) -> matplotlib.patches.Polygon

plt.axvspan(
	xmin: float,
    xmax: float,
    ymin: float = 0,
    ymax: float = 1,
    **kwargs: { <matplotlib.patches.Polygon>:
		alpha: float(0, 1) | None = None,
		color: COLOR_LIKE,
		edgecolor/ec: COLOR_LIKE,
		facecolor/fc: COLOR_LIKE,
		linestyle: str = "-",
		linewidth/lw: float | None = None,
		zorder: float = 0
    }
) -> matplotlib.patches.Polygon
```

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-5, 5, 100)
y = np.sin(x)

plt.plot(x, y)
plt.axhspan(-0.5, 0.5, color="#66ccff", ls="--", alpha=0.8)
plt.axvspan(-0.5, 0.5, color="#ff8899", ls="--", alpha=0.5)
plt.show()
```

### §1.6.2 不规则填充区域(`plt.fill()`)

在[§1.6.1 水平/垂直参考区域(`plt.axhspan()`/`plt.axvspan()`)](###§1.6.1 水平/垂直参考区域(`plt.axhspan()`/`plt.axvspan()`))一节中，我们接触到了`matplotlib.patches.Polygon`。本节我们将学习使用`plt.fill()`填充不规则多边形。

```python
plt.fill(
    *args: [
        x: typing.Sequence[float],
	    y: typing.Sequence[float],
    	color: Optional[str]
    ]+ | [
    	x: str,
        y: str,
        data: dict{[str: typing.Sequence[float]]+}
    ],
    **kwargs: { <matplotlib.patches.Polygon>:
        color / c: COLOR_LIKE,
        edgecolor/ ec: COLOR_LIKE,
        fill: bool = True,
        linestyle: str,
        linewidth / lw: float | None = None,
        zorder: float
    }
) -> list[matplotlib.patches.Polygon]
```

```python
import numpy as np
import matplotlib.pyplot as plt

x = [[0, 1, 3, 3], [3, 4, 4]]
y = [[0, 7, 6, 2], [0, 7, 1]]

plt.fill(x[0], y[0], "g", x[1], y[1], "r")
plt.show()
```

`plt.fill()`也可以从`data: dict`中取值：

```python
import numpy as np
import matplotlib.pyplot as plt

data = {
    "x": [0, 1, 3, 3],
    "y": [0, 7, 6, 2]
}

plt.fill("x", "y", data=data)
plt.show()
```

### §1.6.3 填充积分区域(`plt.fill_between()`)

`plt.fill_between()`用于绘制沿$x$轴的定积分$\displaystyle{\int_{x_{min}}^{x_{max}}y_2(i)-y_1(i)\ di}$围成的区域。

```python
plt.fill_between(
	x: array[number], # 长度一律为N
	y1: array[number] | float[0, 1], # 长度一律为N
    y2: array[number] | float[0, 1] = 0, # 长度一律为N
    where: Optional[array[bool]] = None,
    **kwargs: { <matplotlib.collections.PolyCollection>:
        color / c: COLOR_LIKE,
        cmap: matplotlib.colors.ColorMap | str | None,
        edgecolor / ec: COLOR_LIKE,
        facecolor / fc: COLOR_LIKE,
        fill: bool = True,
        linestyle: str,
        linewidth/lw: float,
        zorder: float,
    }
) -> matplotlib.collections.PolyCollection
```

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, np.pi * 2, 100)
y = np.sin(x)

plt.plot(x, y)
plt.fill_between(x, 0, y, color="#66ccff")
plt.show()
```

`plt.fill_between()`中的`where`用于接受`bool`值，该值可以通过预设的布尔表达式计算而来，作为定积分区域的附加条件：
$$
\begin{align}
	S & =\{(x,y)\ |\ \min\left({y_1(x),y_2(x)}\right)\le y\le \max\left({y_1(x),y_2(x)}\right)\and\text{where}(x,y)=\text{True}\} \\
	  & \subset\R^2
\end{align}
$$
基于此，我们可以用其求解线性规划区域：

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-5, 10, 500)
y = [-5*x+17, -x+8]
y_min = np.minimum(y[0], y[1])

plt.plot(x, y[0], x, y[1])
plt.fill_between(
    x, -6*x-5, y_min,
    where=((x>=0)&(x<=6)), 
    color="#66ccff"
)
plt.show()
```

## §1.7 图表文字(`plt.text()`)

```py
plt.text(
	x: float, # 文字左下角的横坐标
	y: float, # 文字左下角的横坐标
	s: str,
	fontdict: Dict | None = None,
	**kwargs: { <matplotlib.text.Text>:
        alpha: float[0, 1] | None ,
        backgroundcolor: COLOR_LIKE ,
        bbox: dict{ <matplotlib.patches.FancyBboxPatch>:
			boxstyle: str | matplotlib.patches.BoxStyle,
			edgecolor / ec: COLOR_LIKE | None,
			facecolor / fc: COLOR_LIKE | None,
			# ......
		},
        color / c: COLOR_LIKE,
        fontfamily: str,
        fontsize / size: float | Literal["xx-small", "x-small", "small", "medium", "large", "x-large", "xx-large"],
        fontstretch / stretch: number[0, 1000] | Literal["ultra-condensed", "extra-condensed", "condensed", "semi-condensed", "normal", "semi-expanded", "expanded", "extra-expanded", "ultra-expanded"],
		fontweight / weight: number[0, 1000] | Literal["ultralight", "light", "normal", "regular", "book", "medium", "roman", "semibold", "demibold", "demi", "bold", "heavy", "extra bold", "black"],
        horizontalalignment / ha: Literal["left", "center", "right"],
        rotation: float | Literal["vertical", "horizontal"], # 绕矩形左下角旋转
        transform: matplotlib.transforms.Transform,
        verticalalignment / va: Literal["bottom", "baseline", "center", "center_baseline", "top"],
        wrap: bool, # 是否自动换行
        zorder: float,
    }
) -> matplotlib.text.Text
```

`horizontalalignment`/`ha`决定了矩形中用于和`(x,y)`对齐的点位于边框的哪个角落的水平方向：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.axis([0, 10, 0, 10])
plt.text(5, 2, "horizontalalignment=left", c="r", backgroundcolor="#66ccff", horizontalalignment="left")
plt.text(5, 5, "horizontalalignment=right", c="g", backgroundcolor="#66ccff", horizontalalignment="right")
plt.text(5, 8, "horizontalalignment=center", c="b", backgroundcolor="#66ccff", horizontalalignment="center")
plt.plot([5, 5, 5], [2, 5, 8], '.', markersize=15, zorder=4)
plt.show()
```

`rotation`会将文本框沿左下角旋转：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.axis([0, 10, 0, 10])
plt.text(5, 2, "horizontalalignment=left", c="r", backgroundcolor="#66ccff", horizontalalignment="left", rotation=15)
plt.text(5, 5, "horizontalalignment=right", c="g", backgroundcolor="#66ccff", horizontalalignment="right", rotation=15)
plt.text(5, 8, "horizontalalignment=center", c="b", backgroundcolor="#66ccff", horizontalalignment="center", rotation=15)
plt.plot([5, 5, 5], [2, 5, 8], '.', markersize=15, zorder=4)
plt.show()

```

`verticalalignment`/`va`决定了矩形中用于和`(x,y)`对齐的点位于边框的哪个角落的垂直方向：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.axis([0, 10, 0, 10])
plt.text(5, 2, "verticalalignment=top", c="r", backgroundcolor="#66ccff", verticalalignment="top")
plt.text(5, 5, "verticalalignment=center", c="g", backgroundcolor="#66ccff", verticalalignment="center")
plt.text(5, 8, "verticalalignment=bottom", c="b", backgroundcolor="#66ccff", verticalalignment="bottom")
plt.plot([5, 5, 5], [2, 5, 8], '.', markersize=15, zorder=4)
plt.show()

```

`bbox: dict{<matplotlib.patches.FancyBboxPatch>}`用于规定本文框的样式。其中的`boxstyle`键用于指定文本框的外形：

| `boxstyle`属性值(`str`) | `boxstyle`属性值(`matplotlib.patches.BoxStyle`) | 形状     | 默认值                        |
| ----------------------- | ----------------------------------------------- | -------- | ----------------------------- |
| `square`                | `matplotlib.patches.BoxStyle.Square`            | 矩形     | `pad=0.3`                     |
| `circle`                | `matplotlib.patches.BoxStyle.Circle`            | 圆形     | `pad=0.3`                     |
| `ellipse`               | `matplotlib.patches.BoxStyle.Ellipse`           | 椭圆     | `pad=0.3`                     |
| `larrow`                | `matplotlib.patches.BoxStyle.LArrow`            | 左箭头   | `pad=0.3`                     |
| `rarrow`                | `matplotlib.patches.BoxStyle.RArrow`            | 右箭头   | `pad=0.3`                     |
| `darrow`                | `matplotlib.patches.BoxStyle.DArrow`            | 双向箭头 | `pad=0.3`                     |
| `round`                 | `matplotlib.patches.BoxStyle.Round`             | 圆角矩形 | `pad=0.3, rounding_size=None` |
| `round4`                | `matplotlib.patches.BoxStyle.Round4`            | 圆角矩形 | `pad=0.3, rounding_size=None` |
| `sawtooth`              | `matplotlib.patches.BoxStyle.Sawtooth`          | 锯齿形   | `pad=0.3, toothsize=None`     |
| `roundtooth`            | `matplotlib.patches.BoxStyle.Roundtooth`        | 波浪线形 | `pad=0.3, toothsize=None`     |

```python
import numpy as np
import matplotlib.pyplot as plt

boxstyles = ["square", "circle", "ellipse", "larrow", "rarrow", "darrow", "round", "round4", "sawtooth", "roundtooth"]

plt.axis([0, 10, 0, 10])
for index, boxstyle in enumerate(boxstyles):
    plt.text(2, index, f"boxstyle:{boxstyle}", bbox={
        "boxstyle": boxstyle,
        "facecolor": "#66ccff"
    })
plt.show()
```

## §1.8 子图

### §1.8.1 多窗口(`plt.figure()`)

`plt.figure()`用于管理窗口及其样式。

```python
plt.figure(
	num: Optional[int | str | matplotlib.figure.Figure | matplotlib.figure.SubFigure] = None, # int表示图表编号，str表示图表名称
	figsize: tuple[float, float] = (6.4, 4.8), # 图表的宽高(英寸)
	dpi: float = 100,
	facecolor: COLOR_LIKE = "white", # 窗口背景颜色
	edgecolor: COLOR_LIKE = "white", # 窗口边框颜色
	frameon: bool = True, # 是否显示边框
	FigureClass: matplotlib.figure.Figure,
	clear: bool = False,
    layout: Literal["constrained", "compressed", "tight", "none"] | matplotlib.layout_engine.LayoutEngine | None = None,
	**kwargs: {
        <matplotlib.figure.Figure>
    }
)
```

回想CSS中的盒子模型，我们可以调整父标签的尺寸和内边距，但是不会影响内容区的实质内容。这里`plt.figure()`控制的窗口就相当于父元素，里面包含的图表就相当于内容区。因此`plt.figure()`控制的是窗口，而不是图表。

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, np.pi * 2, 100)
y = np.sin(x)

plt.figure(figsize=(7, 3), facecolor="#66ccff", edgecolor="r")
plt.plot(x, y)

plt.show()
```

`plt.figure()`中的`num`表示从这行代码开始处理哪个窗口，表示设置对象的切换。

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, np.pi * 2, 100)
y = np.sin(x)

plt.figure(1, figsize=(7, 3), facecolor="#66ccff")
plt.plot(x, y)
plt.figure(2, figsize=(5, 5), facecolor="#bbbbbb")
plt.plot(x, y)
plt.figure(1) # 切换回来
plt.plot(x, y + 1)

plt.show()
```

### §1.8.2 多子图`plt.subplot()`

`plt.subplot()`用于在窗口（Figure）中创建子图表/轴对象（Axes）。

```python
plt.subplot(
	*args: int | tuple[int, int, int] | matplotlib.gridspec.SubplotSpec = (1, 1, 1),
    projection: Optional[Literal["aitoff", "hammer", "lambert", "mollweide", "polar", "rectilinear"]] = None,
    polor: bool = False, # 等价于projection = "polor" if polor else None
    sharex: Optional[matplotlib.axes.Axes], # 共享X轴的大小和标记
    sharey: Optional[matplotlib.axes.Axes], # 共享Y轴的大小和标记
    **kwargs
) -> matplotlib.axes.Axes
```

`*args`有以下几种写法：

- `tuple[int, int, int]`：`(nrows, ncols, index)`分别表示子图行数、子图列数、子图序号（从左往右，从上到下递增，从`1`开始）。
- `*args: float, float, float`：等价于`tuple[int, int, int]`，也就是对其使用`*`解构赋值。
- `int[111, 999]`：给定一个三位数，会自动拆成三个一位数，对应着`nrows`、`ncols`、`index`。

与`plt.figure()`相似，`plt.subplot()`中的`nrows`、`ncols`、`index`表示从这行代码开始处理哪个子图，表示设置对象的切换。

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, np.pi * 10, 100)
y = np.sin(x)

plt.subplot(2, 1, 1)
plt.title("oscillation")
plt.plot(x, y)
plt.ylabel("position")

plt.subplot(2, 1, 2)
plt.plot(x, y * np.exp(-0.1 * x))
plt.xlabel("time")
plt.ylabel("position")

plt.show()
```

`plt.subplot()`还能实现网格布局中的`colspan`/`rowspan`合并单元格效果，但是实现逻辑有点绕。考虑下列情形：在$2\times2$的网格中，包含左上角$(1,1)$、右上角$(1,2)$和最底一行$(2,1)+(2,2)$三幅子图。要实现最低一行子图横跨所有列，我们需要给`plt.subplot()`传递`(2,1,2)`三组参数，让Matplotlib绘制第三幅子图时，认为整个网格只有一列，所以就会占据整个横向空间：

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, np.pi * 10, 100)
y = np.sin(x)

plt.subplot(2, 2, 1)
plt.plot(x, y)

plt.subplot(2, 2, 2)
plt.plot(x, y * np.exp(-0.1 * x))

plt.subplot(2, 1, 2) # 虚晃一枪，骗过Matplotlib
plt.plot(x, y * np.exp(0.1 * x))

plt.show()
```

`projection`形参支持绘制多种投影：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(15, 8),layout="tight")
plt.suptitle("Projection")

for i, projection in enumerate(["aitoff", "hammer", "lambert", "mollweide", "polar", "rectilinear"]):
    plt.subplot(2, 3, i+1, projection=projection)
    plt.plot(np.linspace(-1, 1, 100), np.linspace(-2, 2, 100))
    plt.title(f"projection={projection}")
    plt.grid(True)
    
plt.show()
```

`sharex/sharey`形参接受一个`matplotlib.axes.Axes`实例，表示当前子图使用的X轴/Y轴与传入的子图的X轴/Y轴共享。

```python
import numpy as np
import matplotlib.pyplot as plt

x = (np.linspace(-5, 5, 200), np.linspace(-2, 2, 100))
y = np.sin(5*x[0]) * np.exp(-np.abs(x[0])), np.sin(5*x[1]) * np.exp(-np.abs(x[1]))

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False

plt.figure(1)
plt.suptitle("未同步X轴")
ax1 = plt.subplot(211)
ax1.plot(x[0], y[0])
ax2 = plt.subplot(212)
ax2.plot(x[1], y[1])

plt.figure(2)
plt.suptitle("已同步X轴")
ax1 = plt.subplot(211)
ax1.plot(x[0], y[0])
ax2 = plt.subplot(212, sharex=ax1)
ax2.plot(x[1], y[1])

plt.show()
```

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-5, 5, 200)
y = np.sin(x), np.sin(x) + 5

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False

plt.figure(1)
plt.suptitle("未同步Y轴")
ax1 = plt.subplot(121)
ax1.plot(x, y[0])
ax2 = plt.subplot(122)
ax2.plot(x, y[1])

plt.figure(2)
plt.suptitle("已同步Y轴")
ax1 = plt.subplot(121)
ax1.plot(x, y[0])
ax2 = plt.subplot(122, sharey=ax1)
ax2.plot(x, y[1])

plt.show()
```

### §1.8.3 子图总标题(`plt.suptitle()`)

在介绍子图之前，我们一直使用`plt.title()`设置整个图表的总标题。然而引入子图之后，`plt.title()`表示的是子图的标题。如果要设置整个图表的总标题，我们需要用到`plt.suptitle()`。

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, np.pi * 10, 100)
y = np.sin(x)

plt.figure(layout="tight")
plt.suptitle("Total subplots")

plt.subplot(2, 2, 1)
plt.title("subplot 1")
plt.plot(x, y)

plt.subplot(2, 2, 2)
plt.title("subplot 2")
plt.plot(x, y * np.exp(-0.1 * x))

plt.subplot(2, 1, 2)
plt.title("subplot 3")
plt.plot(x, y * np.exp(0.1 * x))

plt.show()
```

### §1.8.4 多子图布局(`plt.tight_layout()`)

`plt.tight_layout()`用于指定多子图的布局。

```python
plt.tight_layout(
    pad: float = 1.08 # fontsize的倍数
    h_pad: float = <pad>,
    w_pad: float = <pad>,
    rect: tuple[left, bottom, right, top] = (0, 0, 1, 1)
)
```

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False

def subplot(nrows: int, ncols: int, index: int):
    ax = plt.subplot(nrows, ncols, index)
    ax.plot([0, 1], [0, 3])
    ax.set_xlabel("X坐标", fontsize=20)
    ax.set_ylabel("Y坐标", fontsize=20)
    ax.set_ylabel("子图标题", fontsize=20)

for i in range(4):
    subplot(2, 2, i+1)

plt.tight_layout() # 开启紧凑布局，防止重叠
plt.show()
```

> 注意：开启紧凑布局，除了使用`plt.tight_layout()`手动开启外，也可以让全局变量`plt.rcParams["figure.autolayout"]`为`True`。
>
> ```python
> import numpy as np
> import matplotlib.pyplot as plt
> 
> plt.rcParams["font.family"] = ["Microsoft JhengHei"]
> plt.rcParams["axes.unicode_minus"] = False
> plt.rcParams["figure.autolayout"] = True # 开启紧凑布局，防止重叠
> 
> def subplot(nrows: int, ncols: int, index: int):
>     ax = plt.subplot(nrows, ncols, index)
>     ax.plot([0, 1], [0, 3])
>     ax.set_xlabel("X坐标", fontsize=20)
>     ax.set_ylabel("Y坐标", fontsize=20)
>     ax.set_ylabel("子图标题", fontsize=20)
> 
> for i in range(4):
>     subplot(2, 2, i+1)
> 
> plt.show()
> ```

### §1.8.5 多子图(`plt.subplots()`)

`plt.subplots()`同样用于设置子图，但是功能比`plt.subplot()`更多。

```python
plt.subplots(
	nrows: int = 1,
    ncols: int = 1, *,
    sharex: bool | Literal["none", "all", "row", "col"] = False,
    sharey: bool | Literal["none", "all", "row", "col"] = False,
    squeeze: bool = True,
    width_ratios: Optional[typing.Iterable[float]] = None,
    height_ratios: Optional[typing.Iterable[float]] = None,
    subplot_kw: Optional[<matplotlib.figure.Figure.add_subplot(...)>:] = None,
    grid_spec_kw: Optional[<matplotlib.gridspec.GridSpec(...)>:]= None,
    **fig_kw: **plt.figure(...)
) -> tuple[
    matplotlib.figure.Figure, 
    typing.Union[
        matplotlib.axes.Axes,
        numpy.ndarray[matplotlib.axes.Axes]
    ]
]
```

`nrows`和`ncols`用于指定子图的行列数量：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(6, 3))
ax[0].plot([0, 3])
ax[1].plot([0, 2])

plt.show()
```

由于`axes`也可能是`numpy.ndarray`，所以我们可以使用Numpy数组提供的高级索引功能：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

fig, ax = plt.subplots(nrows=2, ncols=2, figsize=(6, 3))
ax[0, 0].plot([0, 1]) # 高级索引
ax[0, 1].plot([0, 2])
ax[1, 0].plot([0, 3])
ax[1, 1].plot([0, 4])

plt.show()
```

> 注意：由于`axes`也可能是`numpy.ndarray`，这使得我们可以使用Numpy中的方法遍历每个`matplotlib.axes.Axes`：
>
> - `numpy.ndarray.flat: typing.Iterable`
>
>   ```python
>   import numpy as np
>   import matplotlib.pyplot as plt
>   
>   plt.rcParams["font.family"] = ["Microsoft JhengHei"]
>   plt.rcParams["axes.unicode_minus"] = False
>   plt.rcParams["figure.autolayout"] = True
>   
>   fig, axes = plt.subplots(nrows=2, ncols=2, figsize=(6, 3))
>   for ax in axes.flat:
>       ax.set_title("子图")
>       ax.set_xlabel("时间")
>       ax.set_ylabel("位置")
>       ax.label_outer()
>   plt.show()
>   ```
>
> - `numpy.nditer(numpy.ndarray, flags=["refs_ok"]) -> typing.Iterable`
>
>   因为该Numpy数组存储的数据类型是`Object`，所以会触发`TypeError: Iterator operand or requested dtype holds references, but the NPY_ITER_REFS_OK flag was not enabled`。这使得我们必须添加`"refs_ok"`的`FLAG`。
>
>   ```python
>   import numpy as np
>   import matplotlib.pyplot as plt
>                           
>   plt.rcParams["font.family"] = ["Microsoft JhengHei"]
>   plt.rcParams["axes.unicode_minus"] = False
>   plt.rcParams["figure.autolayout"] = True
>                           
>   fig, axes = plt.subplots(nrows=2, ncols=2, figsize=(6, 3))
>   for ax in np.nditer(axes, flags=["refs_ok"]):
>       ax = ax.item()
>       ax.set_title("子图")
>       ax.set_xlabel("时间")
>       ax.set_ylabel("位置")
>       ax.label_outer()
>   plt.show()
>   ```

`shareX`和`shareY`用于设置是否共享X轴和Y轴。如果共享，则会自动给每个`plt`执行`plt.label_out()`，从而删除里面的X轴和Y轴标签：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

fig, axes = plt.subplots(nrows=2, ncols=2, figsize=(6, 3))
fig.suptitle("关闭shareX和shareY")
for ax in axes.flat:
    x = np.arange(np.random.randint(2, 30))
    y = np.random.randint(0, 30, len(x))
    ax.plot(x, y)

fig, axes = plt.subplots(nrows=2, ncols=2, figsize=(6, 3), sharex=True, sharey=True)
fig.suptitle("启用shareX和shareY")
for ax in axes.flat:
    x = np.arange(np.random.randint(2, 30))
    y = np.random.randint(0, 30, len(x))
    ax.plot(x, y)

plt.show()
```

### §1.8.6 多子图(`fig.add_subplot()`)

之前我们介绍了一系列`plt.xxx()`开头的函数，它们都是Matplotlib提供的函数式API。本节我们将使用Matplotlib的OOAPI。关于OO API的更多细节，参考[§1.9 OO API](##§1.9 OO API)。

这里我们调用`plt.figure()`返回的`fig`实例的`.adds_subplot()`方法：

```python
fig.add_subplot(
	*args: int[111, 999] | tuple[int, int, int] | matplotlib.SubplotSpec = (1, 1, 1),
    projection: Optional[None | Literal["aitoff", "hammer", "lambert", "mollweide", "polar", "rectilinear"]],
    polar: bool = False,
    axes_class: Optional[matplotlib.axes.Axes],
    sharex: Optional[matplotlib.axes.Axes],
    sharey: Optional[matplotlib.axes.Axes],
    label: str,
    **kwargs: {<matplotlib.axes.Axes>:}
)
```

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

fig = plt.figure(1)
fig.add_subplot(1, 2, 1).plot(np.random.rand(20))
fig.add_subplot(2, 2, 2).plot(np.random.rand(20))
fig.add_subplot(2, 2, 4).plot(np.random.rand(20))

plt.show()
```

### §1.8.7 多子图布局(`fig.add_gridspec()`)

`fig.add_gridspec()`用于创建网格布局，可以通过网格布局创建子图。

```python
fig.add_gridspec(
	nrows: int = 1,
    ncols: int = 1,
    **kwargs: { <matplotlib.gridspec.GridSpec>:
    	left / right / top / bottom: Optional[float[0, 1]], # 决定了图表四个方向的边界
    	hspace / wspace: Optional[float], # 各图表间的间隔长度
		width_ratios / height_ratios: Optional[typing.Sequence[number]], # 各行/各列的高度/宽度之比
        # ......
    }
) -> matplotlib.gridspec.GridSpec
```

`matplotlib.gridspec.GridSpec(GridSpecBase).__getitem__`沿用了NumPy数组的高级索引，既可以将多级索引合并到一个元组中，也可以使用`:`选中完整的一行或一列：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

fig = plt.figure(1)
gs = fig.add_gridspec(2, 2)
axes = [ # 如果无colspan/rowspan需求，可以直接axes = gs.subplots().flat
    fig.add_subplot(gs[0, 0]),
    fig.add_subplot(gs[0, 1]),
    fig.add_subplot(gs[1, :])
]
for index, ax in enumerate(axes):
    ax.set_title(f"subplot: {index}")
    ax.plot(np.random.random(10))

plt.show()
```

`hspace`/`wspace`用于设置图表之间的间距：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

fig = plt.figure(1)
gs = fig.add_gridspec(2, 2, hspace=0.1, wspace=0.1)
axes = gs.subplots(sharex=True, sharey=True).flat

for index, ax in enumerate(axes):
    ax.plot(np.random.random(10))

plt.show()
```

`width_ratios`/`height_ratios`用于指定网格布局的各行/各列的高度/宽度之比：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

fig = plt.figure(1)
gs = fig.add_gridspec(2, 2, width_ratios=[1.5, 1], height_ratios=[1, 2])
axes = gs.subplots().flat

for index, ax in enumerate(axes):
    ax.plot(np.random.random(10))

plt.show()
```

### §1.8.8 多子图(`plt.axes()`/`fig.add_axes()`)

`plt.axes()`/`fig.add_axes`用于创建更灵活的子图，可以摆脱网格布局的限制，自由地安排子图的位置。

```python
plt.axes / fig.add_axes(
	arg: None | tuple[float, float, float, float], # 相对坐标，分别表示left, bottom, width, height
    projection: Optional[None | Literal["aitoff", "hammer", "lambert", "mollweide", "polar", "rectilinear"]],
    polar: bool = False,
    sharex: optional[matplotlib.axes.Axes],
    sharey: optional[matplotlib.axes.Axes],
    xlim: tuple[float, float], # 指定left和right
    ylim: tuple[float, float], # 指定bottom和top
    xlabel / ylabel: str,
    # ......
) -> matplotlib.axes.Axes
```

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

fig = plt.figure(1)
ax = plt.axes([0.2, 0.4, 0.4, 0.4]) 
# left, bottom, width, height = 0.2, 0.4, 0.4, 0.4

ax.plot(np.random.random(10))

plt.show()
```

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

x = np.linspace(-np.pi, np.pi, 100)
y_sin = np.sin(x)
y_line = x

fig = plt.figure(1)
ax1 = plt.axes()
ax1.plot(x, y_sin)
ax1.plot(x, y_line)
ax1.set_title("y=sin(x)")

ax2 = fig.add_axes([0.2, 0.6, 0.2, 0.2])
ax2.set_xlim(-1, 1)
ax2.set_ylim(-1, 1)
ax2.set_title("切线")
ax2.plot(x, y_sin)
ax2.plot(x, y_line)

plt.show()
```

## §1.9 OO API

我们使用的形如`plt.xxx()`的API，都是Matplotlib提供的函数式API。在通过`ax=plt.subplot()`拿到`matplotlib.axes.Axes`实例后，我们可以使用Matlotlib提供的面向对象的API（Object Oriented API, OOAPI）。

OO API的方法名与函数式API略有不同：

| `pyplot` API        | OO API                   | 作用                       |
| ------------------- | ------------------------ | -------------------------- |
| `plt.text()`        | `ax.text()`              | 添加文字(以绝对坐标为单位) |
| `plt.annotate()`    | `ax.annotate()`          | 添加文字和箭头             |
| `plt.xlabel()`      | `ax.set_xlabel()`        | 设置X轴标签                |
| `plt.ylabel()`      | `ax.set_ylabel()`        | 设置Y轴标签                |
| `plt.xlim()`        | `ax.set_xlim()`          | 设置X轴范围                |
| `plt.ylim()`        | `ax.set_ylim()`          | 设置Y轴范围                |
| `plt.title()`       | `ax.set_title()`         | 设置图表/子图标题          |
| `plt.figtext()`     | `ax.text()`              | 添加文字(以相对坐标为单位) |
| `plt.suptitle()`    | `ax.suptitle()`          | 设置子图总标题             |
| `plt.axis()`        | `ax.set_axis_off()`      | 关闭图表标记               |
| `plt.axis("equal")` | `ax.set_aspect("equal")` | 让X轴和Y轴单位长度相同     |
| `plt.xticks()`      | `xaxis.set_ticks()`      | 设置X轴刻度                |
| `plt.yticks()`      | `xaxis.set_ticks()`      | 设置Y轴刻度                |

```python
import numpy as np
import matplotlib.pyplot as plt

ax = plt.subplot()
ax.set_xlabel("time")
ax.set_ylabel("position")
ax.grid(True)
ax.plot(np.arange(5, -10, -1))
ax.plot(np.arange(-5, 5))

plt.show()
```

## §1.10 多Y轴(`ax.twinx()`)

`ax.twinx()`用于返回一个共享X轴、不共享Y轴的子图对象。

```python
ax.twin() -> matplotlib.axes.Axes
```

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

fig, ax_1 = plt.subplots(1, 1)
ax_2 = ax_1.twinx()

ax_1.plot(np.random.randint(0, 100, 10), "ro-")
ax_2.plot(np.random.randint(0, 10, 10), "bo-")
fig.legend(labels=["randint(0, 100)", "randint(0, 10)"])

plt.show()
```

## §1.11 注释(`plt.annotate()`)

注释由注释文字和带箭头的线条构成，用于指向某个点/某条线并配上文字说明。

```python
plt.annotate(
	text: sr,
    xy: tuple[float, float],
    xytext: tuple[float, float] = <xy>,
    xycoords: str |
    		  tuple[str, str] | 
    		  matplotlib.artist.Artist | 
    		  matplotlib.transforms.Transform | 
    		  callable[matplotlib.backend_bases.RendererBase 
                       -> matplotlib.artist.Artist | matplotlib.transforms.Transform
              ] = "data",
    textcoords: str |
    		  	tuple[str, str] | 
    		  	matplotlib.artist.Artist | 
    		  	matplotlib.transforms.Transform | 
    		  	callable[matplotlib.backend_bases.RendererBase 
                         -> matplotlib.artist.Artist | matplotlib.transforms.Transform
              	] = <xycoords>,
    arrowprops: Optional[dict{
        "edgecolor" / "ec": COLOR_LIKE,
        "facecolor" / "fc": COLOR_LIKE,
    	"width": float, # 箭头宽度(以点为单位)
        "headwidth": float, # 箭头宽度(以点为单位)
        "headlength": float, # 箭头宽度(以点为单位)
        "shrink": float, # 箭头宽度(以点为单位)
        "?": dict[<matplotlib.patches.FancyArrowPatch>:]
    }],
    annotation_clip: bool | None = None, # 注释超出Axes范围时，是否不显示溢出范围
    **kwargs: {<matplotlib.text.Text>:}
) -> matplotlib.text.Annotation
```

`text`参数表示注释文本，`xy`和`xytext`分别表示箭头指向的坐标和注释文本的坐标：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

x = np.linspace(-np.pi, np.pi, 100)
y = np.sin(x)

plt.plot(x, y)
plt.annotate("极大值", (np.pi/2, 1), (2, 1.5), arrowprops={
    "facecolor": "#66ccff",
    "shrink": 0
})
plt.ylim(-2, 2)
plt.show()
```

`xycoords`用于指定`xy`所使用的坐标系统。`textcoords`用于指定`xytext`所使用的坐标系统，并且在`xycoords`的基础上，增加了三个新的坐标系统以供选择，缺省值与`xycoords`相同。

| `xycoords: str`属性值 | 作用                                      |
| --------------------- | ----------------------------------------- |
| `figure points`       | 以`Figure`左下角为原点，以点为单位        |
| `figure pixels`       | 以`Figure`左下角为原点，以像素为单位      |
| `figure fraction`     | 以`Figure`左下角为原点，以百分比为单位    |
| `subfigure points`    | 以`SubFigure`左下角为原点，以点为单位     |
| `subfigure pixels`    | 以`SubFigure`左下角为原点，以像素为单位   |
| `subfigure fraction`  | 以`SubFigure`左下角为原点，以百分比为单位 |
| `axes points`         | 以`Axes`左下角为原点，以点为单位          |
| `axes pixels`         | 以`Axes`左下角为原点，以像素为单位        |
| `axes fraction`       | 以`Axes`左下角为原点，以百分比为单位      |
| `data`(缺省)          | 以正交坐标$(0,0)$为原点                   |
| `polar`               | 以极坐标$(0,0)$为原点                     |

| `textcoords: str`多的属性值 | 作用                                       |
| --------------------------- | ------------------------------------------ |
| `offset points`             | 相对于`xycoords`的偏移量，以点为单位       |
| `offset pixels`             | 相对于`xycoords`的偏移量，以像素为单位     |
| `offset fontsize`           | 相对于`xycoords`的偏移量，以字体大小为单位 |

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

x = np.linspace(-np.pi, np.pi, 100)
y = np.sin(x)

plt.plot(x, y)
plt.annotate("极大值", (np.pi/2, 1), (0.5, 0.5), "data", "axes fraction",
    arrowprops={
        "facecolor": "#66ccff",
        "shrink": 0
    }
)
plt.ylim(-2, 2)
plt.show() # 在GUI中拖动视图，查看axes fraction效果
```

`arrowprops`指定了箭头的样式。

```python
arrowprops: Optional[
    dict{ # 不包含"arrowstyle"键
    	"width": float, # 箭头宽度(以点为单位)
        "headwidth": float, # 箭头宽度(以点为单位)
        "headlength": float, # 箭头宽度(以点为单位)
        "shrink": float, # 箭头宽度(以点为单位)
        "?": dict[<matplotlib.patches.FancyArrowPatch>:]
	} | 
    dict{ # 包含"arrowstyle"键
    	"arrowstyle": Literal["-", "<-", "->", "<->", "<|-", "-|>", "<|-|>", "]-", "-[", "]-[", "|-|", "]->", "<-[", "simple", "fancy", "wedge"] | matplotlib.patches.ArrowStyle = "simple", # 箭头样式
    	"connectionstyle": Optional[Literal["arc3", "angle3", "angle", "arc", "bar"] | matplotlib.patches.ConnectionStyle] = "arc3", # 连接样式
    	"relpos": , # 箭头起点相对于注释文字的位置
        "patchA": matplotlib.patches.Patch = None, # 箭头头部形状
        "patchB": matplotlib.patches.Patch = None, # 箭头尾部形状
        "shrinkA": float = 2, # 箭头头部尺寸缩放系数
        "shrinkB": float = 2, # 箭头尾部尺寸缩放系数
        "mutation_scale": float = 1, # 缩放arrowstyle相关属性(文字大小,headlength等等)
        "mutation_aspect": None | float = None,
        "?": dict[<matplotlib.patches.FancyArrowPatch>:]
    }
]
```

| `arrowstyle: str`参数值 | 对应的`matplotlib.patches.ArrowStyle`子类 | 默认属性                                                     |
| ----------------------- | ----------------------------------------- | ------------------------------------------------------------ |
| `"-"`                   | `Curve`                                   | `None`                                                       |
| `"<-"`                  | `CurveA`                                  | `head_length=0.4, head_width=0/2`                            |
| `"->"`                  | `CurveB`                                  | `head_length=0.4, head_width=0/2`                            |
| `"<->"`                 | `CurveAB`                                 | `head_length=0.4, head_width=0/2`                            |
| `"<|-"`                 | `CurveFilledA`                            | `head_length=0.4, head_width=0/2`                            |
| `"-|>"`                 | `CurveFilledB`                            | `head_length=0.4, head_width=0/2`                            |
| `"<|-|>"`               | `CurveFilledAB`                           | `head_length=0.4, head_width=0/2`                            |
| `"]-"`                  | `BrackedA`                                | `widthA=1.0, lengthA=0.2, angleA=0`                          |
| `"-["`                  | `BrackedB`                                | `widthB=1.0, lengthB=0.2, angleB=0`                          |
| `]-[`                   | `BrackedAB`                               | `widthA=1.0, lengthA=0.2, angleA=0, widthB=1.0, lengthB=0.2, angleB=0` |
| `"|-|"`                 | `BarAB`                                   | `widthA=1.0, lengthA=0.2, widthB=0, angleB=0`                |
| `"]->"`                 | `BrackedCurve`                            | `widthA=1.0, lengthA=0.2 angleA=None`                        |
| `"<-["`                 | `CurveBracked`                            | `widthB=1.0, lengthB=0.2, angleB=None`                       |
| `"simple"`              | `Simple`                                  | `head_length=0.5, head_width=0.5, tail_width=0.2`            |
| `"fancy"`               | `Fancy`                                   | `head_length=0.4, head_width=0.4, tail_width=0.4`            |
| `"wedge"`               | `Wedge`                                   | `tail_width=0.3, shrink_factor=0.5`                          |

| `connectionstyle: str`参数值 | 对应`matplotlib.patches.ConnectionStyle`子类 | 默认属性                                             |
| ---------------------------- | -------------------------------------------- | ---------------------------------------------------- |
| `"arc3"`                     | `Arc3`                                       | `rad=0.0`                                            |
| `"angle3"`                   | `Angle3`                                     | `angleA=90, angleB=0`                                |
| `"angle"`                    | `Angle`                                      | `angleA=90, angleB=0, rad=0.0`                       |
| `"arc"`                      | `Arc`                                        | `angleA=90, angleB=0, armA=None, armB=None, rad=0.0` |
| `"bar"`                      | `Bar`                                        | `armA=0.0, armB=0.0, fraction=0.3, angle=None`       |

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

plt.figure(figsize=(20,5))
arrowstyles = ["-", "<-", "->", "<->", "<|-", "-|>", "<|-|>", "]-", "-[", "]-[", "|-|", "]->", "<-["]
connectionstyles = ["arc3", "angle3", "angle", "arc", "bar"]
for i, arrowstyle in enumerate(arrowstyles):
    for j, connectionstyle in enumerate(connectionstyles):
        plt.annotate(
            text = f"{arrowstyle, connectionstyle}", xy = (i * 5 + 4, j * 2), xytext = (i * 5, j * 2),
            arrowprops={
                "arrowstyle": arrowstyle,
                "connectionstyle": connectionstyle
            }
        )
plt.ylim(-1, 9)
plt.xlim(-1, 65)
plt.show()
```

`connectionstyle: str`除了预设值以外，还支持在五个预设参数的基础上自设一些样式。其中各形参出现的组合，必须在五个预设参数的默认值组合的子集中。

- `matplotlib.patches.ConnectionStyle.Angle3`/`"angle3,angleA={},angleB={}"`

  `Angle3`在两点之间创建一条简单的二次贝塞尔曲线，中间控制点位于首尾两个角度构成射线的交点。

  ```python
  import numpy as np
  import matplotlib.pyplot as plt
  import itertools
  
  plt.rcParams["font.family"] = ["Microsoft JhengHei"]
  plt.rcParams["axes.unicode_minus"] = False
  plt.rcParams["figure.autolayout"] = True
  
  angle3_examples = [
      f"angle3,angleA={i},angleB={j}" for i, j in 
          itertools.product(
              np.linspace(0, 135, 4).astype(np.int32), 
              np.linspace(0, 135, 4).astype(np.int32)
          )
  ]
  
  fig, axes = plt.subplots(4, 4, figsize=(6, 6))
  connectionstyles = angle3_examples
  
  for index, ax in enumerate(axes.flat):
      ax.set_xlim(0, 1)
      ax.set_ylim(0, 1.25)
      ax.set_xticks([])
      ax.set_yticks([])
      arrow_head = (0.3, 0.2)
      arrow_tail = (0.8, 0.6)
      if index in [0, 5, 10, 15]:
          ax.text(x = 0.05, y = 0.7, s = "angleA-angleB\n≠can't be kπ/2", wrap=True)
          continue
  
      ax.plot(
          [arrow_head[0], arrow_tail[0]], 
          [arrow_head[1], arrow_tail[1]],
          "g."
      )
      ax.annotate(
          text="", xy=arrow_head, xytext=arrow_tail,
          arrowprops={
              "arrowstyle": "->",
              "connectionstyle": connectionstyles[index]
          }
      )
      ax.text(
          x = 0.05, y = 1.2, s=connectionstyles[index].replace(",", ",\n"),
          horizontalalignment="left",
          verticalalignment="top"
      )
  
  plt.show()
  ```

- `matplotlib.patches.ConnectionStyle.Angle`/`"angle,angleA={},angleB={},rad={}"`

  `Angle`类在两点之间创建一条分段连续的贝塞尔曲线，通过点位于首尾角度构成射线的交点，连接边缘使用`rad`倒圆角。

  ```python
  import numpy as np
  import matplotlib.pyplot as plt
  import itertools
  
  plt.rcParams["font.family"] = ["Microsoft JhengHei"]
  plt.rcParams["axes.unicode_minus"] = False
  plt.rcParams["figure.autolayout"] = True
  
  angle3_examples = [
      f"angle,angleA=-190,angleB={i},rad={j}" for i, j in 
          itertools.product(
              np.linspace(0, 90, 5).astype(np.int32), 
              np.linspace(0, 90, 10).astype(np.int32)
          )
  ]
  
  fig, axes = plt.subplots(5, 10, figsize=(15, 8))
  connectionstyles = angle3_examples
  
  for index, ax in enumerate(axes.flat):
      ax.set_xlim(0, 1)
      ax.set_ylim(0, 1.25)
      ax.set_xticks([])
      ax.set_yticks([])
      arrow_head = (0.3, 0.2)
      arrow_tail = (0.8, 0.6)
  
      ax.plot(
          [arrow_head[0], arrow_tail[0]], 
          [arrow_head[1], arrow_tail[1]],
          "g."
      )
      ax.annotate(
          text="", xy=arrow_head, xytext=arrow_tail,
          arrowprops={
              "arrowstyle": "->",
              "connectionstyle": connectionstyles[index]
          }
      )
      ax.text(
          x = 0.05, y = 1.2, s=connectionstyles[index].replace(",", ",\n"),
          horizontalalignment="left",
          verticalalignment="top"
      )
      
  fig.subplots_adjust(left=0.01, bottom=0.01, top=0.99, right=0.99)
  plt.tight_layout()
  plt.show()
  ```

- `matplotlib.patches.ConnectionStyle.Arc`/`"arc,angleA={},angleB={},armA={},armB={},rad={}"`

  `Arc`类用于在两点之间创建一条分段连续的二次贝塞尔曲线，该曲线有两个经过点，一个点在与A点相距`armA`且角度为`angleA`的位置，另一个点在与B点相距`armB`且角度为`angleB`的位置，且边缘处均以`rad`为倒角。

- `matplotlib.patches.ConnectionStyle.Arc3`/`"arc3,rad={}"`

  `Arc3`类用于在两点之间创建一条简单的二次贝塞尔曲线。创建曲线时，中间控制点 (C) 与起点`A`和终点`B`的距离相同，并且`C`到连接`A`和`B`的直线距离是`rad`乘以`A`与`B`之间的距离。

  ```python
  import numpy as np
  import matplotlib.pyplot as plt
  
  plt.rcParams["font.family"] = ["Microsoft JhengHei"]
  plt.rcParams["axes.unicode_minus"] = False
  plt.rcParams["figure.autolayout"] = True
  
  angle3_examples = [
      f"arc3,rad={i}" for i in np.linspace(-2, 2, 26).round(3)
  ]
  
  fig, axes = plt.subplots(5, 5, figsize=(9, 8))
  connectionstyles = angle3_examples
  
  for index, ax in enumerate(axes.flat):
      ax.set_xlim(0, 1)
      ax.set_ylim(0, 1.25)
      ax.set_xticks([])
      ax.set_yticks([])
      arrow_head = (0.3, 0.2)
      arrow_tail = (0.8, 0.6)
  
      ax.plot(
          [arrow_head[0], arrow_tail[0]], 
          [arrow_head[1], arrow_tail[1]],
          "g."
      )
      ax.annotate(
          text="", xy=arrow_head, xytext=arrow_tail,
          arrowprops={
              "arrowstyle": "->",
              "connectionstyle": connectionstyles[index]
          }
      )
      ax.text(
          x = 0.05, y = 1.2, s=connectionstyles[index].replace(",", ",\n"),
          horizontalalignment="left",
          verticalalignment="top"
      )
  
  fig.subplots_adjust(left=0.01, bottom=0.01, top=0.99, right=0.99)
  plt.tight_layout()
  plt.show()
  
  ```

- `matplotlib.patches.ConnectionStyle.Bar`/`"bar,armA={},armB={},fraction={},angle={}"`

  `Bar`类用于绘制一条由三条线段构成的折线，交点均为$90\degree$，其中头部臂的长度为$\text{armA}+\text{fraction}\times|A-B|$，尾部臂的长度为$\text{armB}+\text{fraction}\times|A-B|$，`angle`决定了连接线的角度，默认为`None`时连接线平行于`A`和`B`。

  ```python
  import numpy as np
  import matplotlib.pyplot as plt
  import itertools
  
  plt.rcParams["font.family"] = ["Microsoft JhengHei"]
  plt.rcParams["axes.unicode_minus"] = False
  plt.rcParams["figure.autolayout"] = True
  
  angle3_examples = [
      f"bar,armA={i},armB={j}" for i, j in 
          itertools.product(
              np.linspace(-50, 50, 6).round(3),
              np.linspace(-50, 50, 6).round(3)
          )
  ]
  
  fig, axes = plt.subplots(6, 6, figsize=(9, 8))
  connectionstyles = angle3_examples
  
  for index, ax in enumerate(axes.flat):
      ax.set_xlim(0, 1)
      ax.set_ylim(0, 1.25)
      ax.set_xticks([])
      ax.set_yticks([])
      arrow_head = (0.3, 0.2)
      arrow_tail = (0.8, 0.6)
  
      ax.plot(
          [arrow_head[0], arrow_tail[0]], 
          [arrow_head[1], arrow_tail[1]],
          "g."
      )
      ax.annotate(
          text="", xy=arrow_head, xytext=arrow_tail,
          arrowprops={
              "arrowstyle": "->",
              "connectionstyle": connectionstyles[index]
          }
      )
      ax.text(
          x = 0.05, y = 1.2, s=connectionstyles[index].replace(",", ",\n"),
          horizontalalignment="left",
          verticalalignment="top"
      )
  
  fig.subplots_adjust(left=0.01, bottom=0.01, top=0.99, right=0.99)
  plt.tight_layout()
  plt.show()
  ```

- 五种预设类的自定义参数演示：

  ```python
  import numpy as np
  import matplotlib.pyplot as plt
  import itertools
  
  angle3_examples = [
      f"angle3,angleA={i},angleB={j}"
      for i, j
      in itertools.product(np.linspace(0, 180, 8), np.linspace(0, 180, 8))
  ]
  
  fig, axes = plt.subplots(3, 5, figsize=(7, 6.2))
  connectionstyles = [
      "angle3,angleA=90,angleB=0",
      "angle3,angleA=0,angleB=90",
      "angle,angleA=-90,angleB=180,rad=0",
      "angle,angleA=-90,angleB=180,rad=5",
      "angle,angleA=-90,angleB=10,rad=5",
      "arc3,rad=0.",
      "arc3,rad=0.3",
      "arc3,rad=-0.3",
      "arc,angleA=-90,angleB=0,armA=30,armB=30,rad=0",
      "arc,angleA=-90,angleB=0,armA=30,armB=30,rad=5",
      "arc,angleA=-90,angleB=0,armA=0,armB=40,rad=0",
      "bar,fraction=0.3",
      "bar,fraction=-0.3",
      "bar,angle=180,fraction=-0.3",
      "bar,angle=180,fraction=-0.3"
  ]
  
  for index, ax in enumerate(axes.flat):
      ax: matplotlib.axes.Axes = ax
      ax.set_xlim(0, 1)
      ax.set_ylim(0, 1.25)
      ax.set_xticks([])
      ax.set_yticks([])
      arrow_head = (0.3, 0.2)
      arrow_tail = (0.8, 0.6)
      ax.plot([arrow_head[0], arrow_tail[0]], [
              arrow_head[1], arrow_tail[1]], "g.")
      ax.annotate(
          text="", xy=arrow_head, xytext=arrow_tail,
          arrowprops = {
              "arrowstyle": "->",
              "connectionstyle": connectionstyles[index]
          }
      )
      ax.text(
          x=0.05, y=1.2, s=connectionstyles[index].replace(",", ",\n"),
          horizontalalignment="left",
          verticalalignment="top"
      )
  
  plt.tight_layout()
  plt.show()
  ```

`arrowstyle`除了上面给出的数种通用种类，还有`simple`、`fancy`、`wedge`三种：

- `simple`：实心三角箭头

  ```python
  import numpy as np
  import matplotlib.pyplot as plt
  
  plt.rcParams["font.family"] = ["Microsoft JhengHei"]
  plt.rcParams["axes.unicode_minus"] = False
  plt.rcParams["figure.autolayout"] = True
  
  plt.annotate(
      text = "arrowstyle: simple", xy = (0.2, 0.2), xytext = (0.7, 0.8),
      arrowprops = {
          "arrowstyle": "simple",
          "connectionstyle": "arc3,rad=0.2"
      }
  )
  plt.show()
  ```

- `fancy`：头窄尾宽的三角箭头

  ```python
  import numpy as np
  import matplotlib.pyplot as plt
  
  plt.rcParams["font.family"] = ["Microsoft JhengHei"]
  plt.rcParams["axes.unicode_minus"] = False
  plt.rcParams["figure.autolayout"] = True
  
  plt.annotate(
      text = "arrowstyle: fancy", xy = (0.2, 0.2), xytext = (0.7, 0.8),
      arrowprops = {
          "arrowstyle": "fancy",
          "connectionstyle": "arc3,rad=0.2"
      }
  )
  plt.show()
  ```

- `wedge`：头窄尾宽的曲线，没有三角

  ```python
  import numpy as np
  import matplotlib.pyplot as plt
  
  plt.rcParams["font.family"] = ["Microsoft JhengHei"]
  plt.rcParams["axes.unicode_minus"] = False
  plt.rcParams["figure.autolayout"] = True
  
  plt.annotate(
      text = "arrowstyle: wedge", xy = (0.2, 0.2), xytext = (0.7, 0.8),
      arrowprops = {
          "arrowstyle": "wedge",
          "connectionstyle": "arc3,rad=0.2"
      }
  )
  plt.show()
  ```

`plt.annotate(**kwargs: matplotlib.text.Text)`中的`bbox: dict[<matplotlib.patches.FancyBboxPatch>]`参数用于设置注释文字所在的文本框样式：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

plt.annotate(
    text = "arrowstyle: fancy", xy = (0.2, 0.2), xytext = (0.7, 0.8),
    bbox = {
    	"boxstyle": "round4",
        "facecolor": "#66ccff"
    },
    arrowprops = {
        "arrowstyle": "fancy",
        "connectionstyle": "arc3,rad=0.2"
    }
)
plt.show()
```

## §1.12 刻度

TODO：？？？？？？？？？？？？？？？

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

x = np.linspace(0, np.pi * 2, 100)
y = np.sin(x)

fig = plt.figure(1)
ax = fig.add_subplot()
ax.plot(x, y)
ax.xaxis.set_major_locator(matplotlib.ticker.MultipleLocator(np.pi / 4))
ax.xaxis.set_major_formatter(matplotlib.ticker.FuncFormatter(
    lambda x, pos: f"$\\frac{{{int(np.round(x/(np.pi/4)))}\pi}}{{{4}}}$"
))

plt.show()
```





# §2 常用图表绘制

## §2.1 折线图

```python
plt.plot(
    [x: Optional, y, **kwargs]+
) -> list[matplotlib.lines.Line2D]
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

给`plt.plot()`的`**kwargs`传入`color`/`c`参数，可以改变线条颜色。

`color`支持很多种颜色格式：

| 颜色格式                         | 含义                                                     | 示例                                |
| -------------------------------- | -------------------------------------------------------- | ----------------------------------- |
| `[a-z]`                          | 色彩字符，详见[§A.1 RGB颜色名称表](##§A.1 RGB颜色名称表) | `plt.plot(color="w")`               |
| `[a-z]+`                         | 色彩全名，详见[§A.1 RGB颜色名称表](##§A.1 RGB颜色名称表) | `plt.plot(color="red")`             |
| `#[a-f0-9]`                      | RGB十六进制                                              | `plt.plot(color="#ff0000")`         |
| `tuple[float,float,float]`       | RGB向量                                                  | `plt.plot(color=(0.2,0.3,0.4))`     |
| `tuple[float,float,float,float]` | RGBA向量                                                 | `plt.plot(color=(0.2,0.3,0.4,0.5))` |
| `tab:[a-z]+`                     | 色彩调色板(Tableau Palette)                              | `plt.plot(color="tab:blue")`        |
| `[a-z]+`                         | CSS预置颜色                                              | `plt.plot(color="lightblue")`       |
| `String(float)`                  | 黑白阶的灰度                                             | `plt.plot(color="0.5")`             |

在不引起歧义的情况下，我们可以省略`color`/`c`，直接向`*args`传入颜色：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.plot(np.arange(10), 'r')
plt.plot(np.arange(10), 'blue')
plt.show()
```

`plt.plot()`支持设置多个`color`，给多个线条设置不同的颜色（此时必须向`*args`传值）：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.plot(
    np.arange(10), np.arange(10) ** 1.5, "0.9", 
    np.arange(10) ,np.arange(10) ** 2, "0.9",
)
plt.show()
```

### §2.1.3 设置线条样式

给`plt.plot()`的`**kwargs`传入`linestyle`/`ls`参数，可以改变线条样式。

| 样式名称      | 样式名称字符 | 含义   |
| ------------- | ------------ | ------ |
| `solid`(缺省) | `-`          | 实线   |
| `dashed`      | `--`         | 短划线 |
| `dashdot`     | `-.`         | 点划线 |
| `dotted`      | `:`          | 点线   |

```python
import numpy as np
import matplotlib.pyplot as plt
plt.plot(np.arange(10), np.arange(10) ** 0.5, linestyle="-")
plt.plot(np.arange(10), np.arange(10) ** 1.0, linestyle="--")
plt.plot(np.arange(10), np.arange(10) ** 1.5, linestyle="-.")
plt.plot(np.arange(10), np.arange(10) ** 2.0, linestyle=":")
plt.show()
```

同样地，`linestyle`也可以省略，从而把所有线条的绘制压缩至一个`plt.plot()`函数内：

```python
import numpy as np
import matplotlib.pyplot as plt
plt.plot(
    np.arange(10), np.arange(10) ** 0.5, "-",
    np.arange(10), np.arange(10) ** 1.0, "--",
    np.arange(10), np.arange(10) ** 1.5, "-.",
    np.arange(10), np.arange(10) ** 2.0, ":"
)
plt.show()
```

### §2.1.4 设置节点样式

给`plt.plot()`的`**kwargs`传入`marker`参数，可以改变线条样式。

| 节点样式名称 | 含义   | 节点样式名称  | 含义      | 节点样式名称   | 含义      |
| ------------ | ------ | ------------- | --------- | -------------- | --------- |
| `-`/`solid`  | 实线   | `--`/`dashed` | 虚线      | `-.`/`dashdot` | 虚点线    |
| `:`/`dotted` | 虚点   | `.`           | 点        | `,`            | 像素      |
| `o`          | 圆     | `v`           | 下三角    | `^`            | 上三角    |
| `<`          | 左三角 | `>`           | 右三角    | `1`            | 正Y型     |
| `2`          | 倒Y型  | `3`           | 右斜Y型   | `4`            | 左斜Y型   |
| `s`          | 正方形 | `p`           | 正五边形  | `*`            | 五角星    |
| `+`          | 加号   | `D`           | 斜正方形  | `d`            | 窄菱形    |
| `x`          | 叉号   | `H`           | 正六边形⬣ | `h`            | 正六边形⬢ |

```python
import numpy as np
import matplotlib.pyplot as plt

plt.plot(np.arange(10), np.arange(10) ** 0.5, marker="D")
plt.plot(np.arange(10), np.arange(10) ** 1.0, marker="d")
plt.plot(np.arange(10), np.arange(10) ** 1.5, marker="H")
plt.plot(np.arange(10), np.arange(10) ** 2.0, marker="h")
plt.show()
```

同样地，`marker`也可以省略，从而把所有线条的绘制压缩至一个`plt.plot()`函数内：

```python
import numpy as np
import matplotlib.pyplot as plt
plt.plot(
    np.arange(10), np.arange(10) ** 0.5, "D",
    np.arange(10), np.arange(10) ** 1.0, "d",
    np.arange(10), np.arange(10) ** 1.5, "H",
    np.arange(10), np.arange(10) ** 2.0, "h"
)
plt.show()
```

### §2.1.5 设置标题

#### §2.1.5.1 设置图表标题

`plt.title()`用于设置图表标题。

```python
plt.title(
	label: str,
    fontdict: dict{
    	"fontsize": plt.rcParams["axes.titlesize"],
        "fontweight": plt.rcParams["axes.titleweight"],
        "color": COLOR_LIKE,
        "werticalalignment" = "baseline",
        "horizontalalignment": Literal["center", "left", "right"] = "center",
    }
    **kwargs: {
    	fontsize: int | Literal["xx-small" | "x-small" | "small" | "medium" | "large" | "x-large" | "xx-large"],
        fontweight: int | Literal["extra bold" | "heavy" | "bold" | "normal" | "light" | "ultralight"],
        fontstyle: Literal["normal" | "italic" | "oblique"],
        loc: Literal["center" | "left" | "right"],
        color: str | tuple[float]
    }
)
```

```python
import numpy as np
import matplotlib.pyplot as plt
plt.title(
    "Graph 1", 
    fontsize="x-large", 
    fontweight="bold", 
    fontstyle="italic", 
    loc="left", 
    color="#66ccff"
)
plt.plot(np.arange(10), np.arange(10) ** 0.5, "Dr-.")
plt.show()
```

#### §2.1.5.2 设置轴标题

```python
plt.xlabel/ylabel(
	label: str
    **kwargs: {
    	fontsize: int | Literal["xx-small" | "x-small" | "small" | "medium" | "large" | "x-large" | "xx-large"],
        labelpad: float = 4.0 # 标题与图表的间距(包括箭头和刻度标签)
        loc: # 对齐方式
        	Literal["center" | "left" | "right"] | # 对于xlabel()
            Literal["center" | "top" | "bottom"] # 对于ylabel()
        color: str | tuple[float]
    }
)
```

其中的部分`**kwargs`参数可以在`plt.rcParams`中全局更改：

- `labelpad`：对应`plt.rcParams["axes.labelpad"]`
- `loc`(对于`plt.xlabel()`)：对应`plt.rcParams["xaxis.labellocation"]`
- `loc`(对于`plt.ylabel()`)：对应`plt.rcParams["yaxis.labellocation"]`

```python
import numpy as np
import matplotlib.pyplot as plt
plt.xlabel("X", fontsize="20", labelpad=2, loc="right", color="red")
plt.ylabel("Y", fontsize="10", labelpad=6, loc="top", color="blue")
plt.plot(np.arange(10), np.arange(10) ** 0.5, "Dr-.")
plt.show()
```

> 注意：Matplotlib的默认字体不支持中文。如果要显示中文，需要手动更改`plt.rcParams["font.family"]: list[str]`。例如使用微软雅黑：
>
> ```python
> import numpy as np
> import matplotlib.pyplot as plt
> plt.rcParams["font.family"] = ["Microsoft JhengHei"]
> plt.xlabel("X轴", fontsize="20", labelpad=2, loc="right", color="red")
> plt.ylabel("Y轴", fontsize="10", labelpad=6, loc="top", color="blue")
> plt.plot(np.arange(10), np.arange(10) ** 0.5, "Dr-.")
> plt.show()
> ```

> 注意：Matplotlib输出负号时，默认使用`U+2212`(`−`)字符。然而，更常用的负号字符是`U+002D`(`-`)。有些字体没有实现`U+2212`，我们可以设置`plt.rcParams["axes.unicode_minus"]`为`False`，从而使用ASCII提供的负号。
>
> ```python
> import numpy as np
> import matplotlib.pyplot as plt
> plt.rcParams["font.family"] = ["Microsoft JhengHei"]
> plt.rcParams["axes.unicode_minus"] = False
> plt.xlabel("X轴", fontsize="20", labelpad=2, loc="right", color="red")
> plt.ylabel("Y轴", fontsize="10", labelpad=6, loc="top", color="blue")
> plt.plot(np.arange(-5, 5), np.arange(-5, 5), "Dr-.")
> plt.show()
> ```

### §2.1.6 保存图表

#### §2.1.6.1 图形界面

在图形窗口中，选择最下方的最右侧按钮（`Save the figure`）即可。

#### §2.1.6.2 `plt.savefig()`

`plt.savefig()`用于保存图表为图片。

```python
matplotlib.savefig(
	fname: str | PATH_LIKE | FILE_LIKE, *,
    transparent: bool = None, # 背景是否透明
    dpi: float | "figure" = "figure",
    format: Literal["jpg", "png", "pdf", ...] = None, 
    metadata: Optional[dict] = None,
    bbox_inches: str | matplotlib.transforms.Bbox = None, # 边界框
    pad_inches: float | Literal["layout"] = 0.1, # 周围填充量
    facecolor: COLOR_LIKE | Literal["auto"] = "auto", # 图表表面颜色
    edgecolor: COLOR_LIKE | Literal["auto"] = "auto", # 图表边缘颜色
    backend: Optional[str[Literal["AGG" | "PDF" | "PS" | "SVG" | "PGF" | "Cairo" | "module://"+re.compile(".*")]]] = None, # 渲染器
    **kwargs
)
```

### §2.1.7 加载图表

Matplotlib使用`matplotlib.image`子模块加载已保存的图表：

```python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as img

plt.plot(np.arange(-5, 5), np.arange(-5, 5), "Dr-.")
plt.savefig("./demo.png")

plt.imshow(img.imread('./demo.png'))
plt.axis("off")
plt.show()
```

`img.imshow()`支持多种加载多种文件：

```python
img.imshow(
	X: List[int, int] | List[int, int, int, int, int] | List[int, int, int, int, int, int] |
       List[int, int] | List[int, int, float, float, float] | List[int, int, float, float, float, float]
    cmap: str | matplotlib.colors.Colormap, # 色彩映射图
    aspect: Literal["auto" | "equal"]
)
```

## §2.2 极坐标图

在[§1.8.2 多子图`plt.subplot()`](###§1.8.2 多子图`plt.subplot()`)一节中，我们提到过`projection`形参为`"polar"`时，可以绘制极坐标图$(\theta,r)$。当然，`plt.sublots(**subplot_kw)`已经包含了`plt.subplot()`中的形参列表，所以用这个函数也能创建极坐标图。

```python
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = ["Microsoft JhengHei"]
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.autolayout"] = True

# 绘制极坐标方程 r = θ/3 + sin(2θ)
theta = np.linspace(0, 10 * np.pi, 500)
r = theta / 3 + np.sin(2 * theta)

ax = plt.subplot(projection="polar")
ax.plot(theta, r, color="purple", linewidth=2)
ax.set_title("极坐标方程 r = θ/3 + sin(2θ)")
plt.show()
```

## §2.3 散点图(`plt.scatter()`)



```python
plt.scatter(
	x / y: float | typing.Sequence[float],
    s: Optional[float | typing.Sequence[float]] = None,
    marker = None,
    
)
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

## §A.2 TeX符号子集

Matplotlib提供了一套TeX符号的子集，用于在图表中绘制公式。公式需要用`$$`包裹起来。

```python
import matplotlib.pyplot as plt
plt.title(r"$2\pi$")
plt.show()
```

### §A.2.1 字体

| 字体名称             | 对应`rcParams["mathtext.fontset"]`字符串 |
| -------------------- | ---------------------------------------- |
| DejaVu Sans          | `dejavusans`                             |
| DejaVu Serif         | `dejavuserif`                            |
| Computer Modern(TeX) | `cm`                                     |
| STIX                 | `stix`                                   |
| STIX sans-serif      | `stixsans`                               |

| 字体样式                              | TeX代码                 | 效果演示                 | 对应`rcParams[ "mathtext.fontset" ]`字符串 |
| ------------------------------------- | ----------------------- | ------------------------ | ------------------------------------------ |
| 罗马字体                              | `\mathrm{...}`          | $\mathrm{test}$          | `"mathtext.rm"`                            |
| 意大利斜体                            | `\mathit{...}`          | $\mathit{test}$          | `"mathtext.it"`                            |
| 打字机字体                            | `\mathtt{...}`          | $\mathtt{test}$          | `"mathtext.tt"`                            |
| 花体                                  | `'\mathcal{...}`        | $\mathcal{test}$         | `"mathtext.cal"`                           |
| 空心字体                              | `\mathbb{...}`          | $\mathbb{test}$          |                                            |
| 罗马字体+空心字体(仅STIX字体格式)     | `\mathrm{\mathbb{...}}` | $\mathrm{\mathbb{test}}$ |                                            |
| 哥特字体(仅STIX字体格式)              | `\mathfrak{...}`        | $\mathfrak{test}$        |                                            |
| `sans-serif`字体(仅STIX字体格式)      | `\mathsf{...}`          | $\mathsf{test}$          | `"mathtext.sf"`                            |
| 罗马字体+无衬线印刷体(仅STIX字体格式) | `\mathrm{\mathsf{...}}` | $\mathrm{\mathsf{test}}$ |                                            |
| 罗马字体+粗体                         | `\mathbf{}`             | $\mathbf{test}$          | `"mathtext.bf"`                            |
| 加粗意大利斜体(仅STIX字体格式)        | `\mathbfit{...}`        | $\mathbfit{test}$        | `"mathtext.bfit"`                          |

### §A.2.2 希腊字母

| 小写希腊字母 | 大写希腊字母 | TeX代码    |
| ------------ | ------------ | ---------- |
| α            | Α            | `\alpha`   |
| β            | Β            | `\beta`    |
| γ            | Γ            | `\gamma`   |
| δ            | Δ            | `\delta`   |
| ε            | Ε            | `\epsilon` |
| ζ            | Ζ            | `\zeta`    |
| η            | Η            | `\eta`     |
| θ            | Θ            | `\theta`   |
| ι            | Ι            | `\lota`    |
| κ            | Κ            | `\kappa`   |
| λ            | Λ            | `\lambda`  |
| μ            | Μ            | `\mu`      |
| ν            | Ν            | `\nu`      |
| ξ            | Ξ            | `\xi`      |
| ο            | Ο            | `\omicron` |
| π            | Π            | `\pi`      |
| ρ            | Ρ            | `\rho`     |
| σ            | Σ            | `\sigma`   |
| τ            | Τ            | `\tau`     |
| υ            | Υ            | `\upsilon` |
| φ            | Φ            | `\phi`     |
| χ            | Χ            | `\chi`     |
| ψ            | Ψ            | `\psi`     |
| ω            | Ω            | `\omega`   |

### §A.2.3 分隔符

| 分隔符 | TeX代码 | 分隔符 | TeX代码   | 分隔符 | TeX代码   |
| -------- | ------- | --------- | --------- | --------- | --------- |
| $($    | `(`    | $\leftparen$ | `\leftparen` | $\rightparen$ | `\rightparen` |
| $)$    | `)`    | $.$ | `.` | $/$ | `/` |
| $<$    | `<`    | $>$ | `>` | $[$ | `[` |
| $\lbrack$    | `\lbrack`    | $\backslash$ | `\backslash` | $\vert$ | `\vert` |
| $|$    | `|`    | $\rbrack$ | `\rbrack` | $]$ | `]` |
| $\{$    | `\{`    | $\lbrace$ | `\lbrace` | $\leftbrace$ | `\leftbrace` |
| $\rightbrace$    | `\rightbrace`    | $\}$ | `\}` | $\rbrace$ | `\rbrace` |
| $\|$    | `\|`    | $\Vert$ | `\Vert` | $\uparrow$ | `\uparrow` |
| $\downarrow$    | `\downarrow`    | $\updownarrow$ | `\updownarrow` | $\Uparrow$ | `\Uparrow` |
| $\Downarrow$    | `\Downarrow`    | $\Updownarrow$ | `\Updownarrow` | $\lceil$ | `\lceil` |
| $\rceil$    | `\rceil`    | $\lfloor$ | `\lfloor` | $\rfloor$ | `\rfloor` |
| $\langle$    | `\langle`    | $\rangle$ | `\rangle` | $\lgroup$ | `\lgroup` |
| $\rgroup$    | `\rgroup`    |  |  |||

### §A.2.4 大型运算符

| 大型运算符 | TeX代码 | 大型运算符  | TeX代码   | 大型运算符  | TeX代码   |
| -------- | ------- | --------- | --------- | --------- | --------- |
| $\prod$    | `\prod`    | $\coprod$ | `\coprod` | $\sum$ | `\sum` |
| $\int$    | `\int`    | $\iint$ | `\iint` | $\iiint$ | `\iiint` |
| $\oint$    | `\oint`    | $\oiint$ | `\oiint` | $\oiiint$ | `\oiiint` |
| $\bigwedge$    | `\bigwedge`    | $\bigvee$ | `\bigvee` | $\bigcap$ | `\bigcap` |
| $\bigcup$    | `\bigcup`    | $\bigodot$ | `\bigodot` | $\bigoplus$ | `\bigoplus` |
| $\bigotimes$    | `\bigotimes`    | $\biguplus$ | `\biguplus` | $\bigsqcup$ | `\bigsqcup` |     
| $\iiiint$    | `\iiiint`    |  |  |  |  |

### §A.2.5 二元运算符

| 二元运算符 | TeX代码 | 二元运算符 | TeX代码   | 二元运算符 | TeX代码   |
| -------- | ------- | --------- | --------- | --------- | --------- |
| $*$    | `*`    | $+$ | `+` | $-$ | `-` |
| $\pm$    | `\pm`    | $\times$ | `\times` | $\div$ | `\div` |
| $\dagger$    | `\dagger`    | $\ddagger$ | `\ddagger` | $−$ | `−` |
| $\mp$    | `\mp`    | $\dotplus$ | `\dotplus` | $\slash$ | `\slash` |
| $\setminus$    | `\setminus`    | $\ast$ | `\ast` | $\circ$ | `\circ` |
| $\bullet$    | `\bullet`    | $\wedge$ | `\wedge` | $\vee$ | `\vee` |
| $\cap$    | `\cap`    | $\cup$ | `\cup` | $\dotminus$ | `\dotminus` |
| $\minuscolon$    | `\minuscolon`    | $\dotsminusdots$ | `\dotsminusdots` | $\wr$ | `\wr` |
| $\cupdot$    | `\cupdot`    | $\uplus$ | `\uplus` | $\sqcap$ | `\sqcap` |
| $\sqcup$    | `\sqcup`    | $\oplus$ | `\oplus` | $\ominus$ | `\ominus` |
| $\otimes$    | `\otimes`    | $\oslash$ | `\oslash` | $\odot$ | `\odot` |
| $\circledcirc$    | `\circledcirc`    | $\circledast$ | `\circledast` | $\circleddash$ | `\circleddash` |
| $\boxplus$    | `\boxplus`    | $\boxminus$ | `\boxminus` | $\boxtimes$ | `\boxtimes` |
| $\boxdot$    | `\boxdot`    | $\unlhd$ | `\unlhd` | $\unrhd$ | `\unrhd` |
| $\intercal$    | `\intercal`    | $\veebar$ | `\veebar` | $\barwedge$ | `\barwedge` |
| $\barvee$    | `\barvee`    | $\diamond$ | `\diamond` | $\cdot$ | `\cdot` |
| $\star$    | `\star`    | $\divideontimes$ | `\divideontimes` | $\leftthreetimes$ | `\leftthreetimes` |
| $\rightthreetimes$    | `\rightthreetimes`    | $\curlyvee$ | `\curlyvee` | $\curlywedge$ | `\curlywedge` |
| $\Cap$    | `\Cap`    | $\Cup$ | `\Cup` | $\doublebarwedge$ | `\doublebarwedge` |
| $\obar$    | `\obar`    | $\bigtriangleup$ | `\bigtriangleup` | $\rhd$ | `\rhd` |
| $\triangleright$    | `\triangleright`    | $\bigtriangledown$ | `\bigtriangledown` | $\triangleleft$ | `\triangleleft` |
| $\lhd$    | `\lhd`    | $\bigcirc$ | `\bigcirc` | $\boxbar$ | `\boxbar` |
| $\amalg$    | `\amalg`    | $\merge$ | `\merge` |  |  |

### §A.2.6 关系符号

| 关系符号 | TeX代码 | 关系符号  | TeX代码   | 关系符号  | TeX代码   |
| -------- | ------- | --------- | --------- | --------- | --------- |
| $:$    | `:`    | $<$ | `<` | $=$ | `=` |
| $\equal$    | `\equal`    | $>$ | `>` | $\backepsilon$ | `\backepsilon` |
| $\dots$    | `\dots`    | $\in$ | `\in` | $\notin$ | `\notin` |
| $\smallin$    | `\smallin`    | $\ni$ | `\ni` | $\notsmallowns$ | `\notsmallowns` |
| $\smallowns$    | `\smallowns`    | $\propto$ | `\propto` | $\varpropto$ | `\varpropto` |
| $\rightangle$    | `\rightangle`    | $\mid$ | `\mid` | $\nmid$ | `\nmid` |
| $\parallel$    | `\parallel`    | $\nparallel$ | `\nparallel` | $\therefore$ | `\therefore` |
| $\because$    | `\because`    | $\ratio$ | `\ratio` | $\sim$ | `\sim` |
| $\backsim$    | `\backsim`    | $\nsim$ | `\nsim` | $\eqsim$ | `\eqsim` |
| $\simeq$    | `\simeq`    | $\nsimeq$ | `\nsimeq` | $\cong$ | `\cong` |
| $\simneqq$    | `\simneqq`    | $\ncong$ | `\ncong` | $\approx$ | `\approx` |
| $\napprox$    | `\napprox`    | $\approxeq$ | `\approxeq` | $\approxident$ | `\approxident` |
| $\backcong$    | `\backcong`    | $\asymp$ | `\asymp` | $\Bumpeq$ | `\Bumpeq` |
| $\bumpeq$    | `\bumpeq`    | $\doteq$ | `\doteq` | $\doteqdot$ | `\doteqdot` |
| $\Doteq$    | `\Doteq`    | $\fallingdotseq$ | `\fallingdotseq` | $\risingdotseq$ | `\risingdotseq` |
| $\coloneq$    | `\coloneq`    | $\eqcolon$ | `\eqcolon` | $\eqcirc$ | `\eqcirc` |
| $\circeq$    | `\circeq`    | $\arceq$ | `\arceq` | $\wedgeq$ | `\wedgeq` |
| $\veeeq$    | `\veeeq`    | $\stareq$ | `\stareq` | $\triangleq$ | `\triangleq` |
| $\triangleeq$    | `\triangleeq`    | $\eqdef$ | `\eqdef` | $\measeq$ | `\measeq` |
| $\questeq$    | `\questeq`    | $\neq$ | `\neq` | $\ne$ | `\ne` |
| $\equiv$    | `\equiv`    | $\nequiv$ | `\nequiv` | $\Equiv$ | `\Equiv` |
| $\leq$    | `\leq`    | $\geq$ | `\geq` | $\leqq$ | `\leqq` |
| $\geqq$    | `\geqq`    | $\lneqq$ | `\lneqq` | $\gneqq$ | `\gneqq` |
| $\ll$    | `\ll`    | $\gg$ | `\gg` | $\between$ | `\between` |
| $\nless$    | `\nless`    | $\ngtr$ | `\ngtr` | $\nleq$ | `\nleq` |
| $\ngeq$    | `\ngeq`    | $\lesssim$ | `\lesssim` | $\gtrsim$ | `\gtrsim` |
| $\nlesssim$    | `\nlesssim`    | $\ngtrsim$ | `\ngtrsim` | $\lessgtr$ | `\lessgtr` |
| $\gtrless$    | `\gtrless`    | $\nlessgtr$ | `\nlessgtr` | $\ngtrless$ | `\ngtrless` |
| $\prec$    | `\prec`    | $\succ$ | `\succ` | $\preceq$ | `\preceq` |
| $\preccurlyeq$    | `\preccurlyeq`    | $\succcurlyeq$ | `\succcurlyeq` | $\succeq$ | `\succeq` |
| $\precsim$    | `\precsim`    | $\succsim$ | `\succsim` | $\nprec$ | `\nprec` |
| $\nsucc$    | `\nsucc`    | $\subset$ | `\subset` | $\supset$ | `\supset` |
| $\nsubset$    | `\nsubset`    | $\nsupset$ | `\nsupset` | $\subseteq$ | `\subseteq` |
| $\supseteq$    | `\supseteq`    | $\nsubseteq$ | `\nsubseteq` | $\nsupseteq$ | `\nsupseteq` |
| $\subsetneq$    | `\subsetneq`    | $\supsetneq$ | `\supsetneq` | $\sqsubset$ | `\sqsubset` |
| $\sqsupset$    | `\sqsupset`    | $\sqsubseteq$ | `\sqsubseteq` | $\sqsupseteq$ | `\sqsupseteq` |
| $\oequal$    | `\oequal`    | $\vdash$ | `\vdash` | $\dashv$ | `\dashv` |
| $\top$    | `\top`    | $\bot$ | `\bot` | $\rightassert$ | `\rightassert` |
| $\models$    | `\models`    | $\vDash$ | `\vDash` | $\Vdash$ | `\Vdash` |
| $\Vvdash$    | `\Vvdash`    | $\rightModels$ | `\rightModels` | $\nvdash$ | `\nvdash` |
| $\nvDash$    | `\nvDash`    | $\nVdash$ | `\nVdash` | $\nVDash$ | `\nVDash` |
| $\scurel$    | `\scurel`    | $\trianglelefteq$ | `\trianglelefteq` | $\trianglerighteq$ | `\trianglerighteq` |
| $\measuredrightangle$    | `\measuredrightangle`    | $\varlrtriangle$ | `\varlrtriangle` | $\bowtie$ | `\bowtie` |
| $\ltimes$    | `\ltimes`    | $\rtimes$ | `\rtimes` | $\backsimeq$ | `\backsimeq` |
| $\Subset$    | `\Subset`    | $\Supset$ | `\Supset` | $\pitchfork$ | `\pitchfork` |
| $\equalparallel$    | `\equalparallel`    | $\lessdot$ | `\lessdot` | $\gtrdot$ | `\gtrdot` |
| $\lll$    | `\lll`    | $\ggg$ | `\ggg` | $\lesseqgtr$ | `\lesseqgtr` |
| $\gtreqless$    | `\gtreqless`    | $\eqless$ | `\eqless` | $\eqgtr$ | `\eqgtr` |
| $\curlyeqprec$    | `\curlyeqprec`    | $\curlyeqsucc$ | `\curlyeqsucc` | $\npreccurlyeq$ | `\npreccurlyeq` |
| $\nsucccurlyeq$    | `\nsucccurlyeq`    | $\nsqsubseteq$ | `\nsqsubseteq` | $\nsqsupseteq$ | `\nsqsupseteq` |
| $\sqsubsetneq$    | `\sqsubsetneq`    | $\sqsupsetneq$ | `\sqsupsetneq` | $\lnsim$ | `\lnsim` |
| $\gnsim$    | `\gnsim`    | $\precnsim$ | `\precnsim` | $\succnsim$ | `\succnsim` |
| $\ntriangleleft$    | `\ntriangleleft`    | $\ntriangleright$ | `\ntriangleright` | $\ntrianglelefteq$ | `\ntrianglelefteq` |
| $\ntrianglerighteq$    | `\ntrianglerighteq`    | $\disin$ | `\disin` | $\isins$ | `\isins` |
| $\varisins$    | `\varisins`    | $\isindot$ | `\isindot` | $\isinobar$ | `\isinobar` |
| $\varisinobar$    | `\varisinobar`    | $\isinvb$ | `\isinvb` | $\isinE$ | `\isinE` |
| $\nisd$    | `\nisd`    | $\nis$ | `\nis` | $\varnis$ | `\varnis` |
| $\niobar$    | `\niobar`    | $\varniobar$ | `\varniobar` | $\bagmember$ | `\bagmember` |
| $\frown$    | `\frown`    | $\smile$ | `\smile` | $\triangle$ | `\triangle` |
| $\blacktriangleright$    | `\blacktriangleright`    | $\triangleright$ | `\triangleright` | $\vartriangleright$ | `\vartriangleright` |
| $\blacktriangleleft$    | `\blacktriangleleft`    | $\triangleleft$ | `\triangleleft` | $\vartriangleleft$ | `\vartriangleleft` |
| $\perp$    | `\perp`    | $\Join$ | `\Join` | $\leqslant$ | `\leqslant` |
| $\geqslant$    | `\geqslant`    | $\lessapprox$ | `\lessapprox` | $\gtrapprox$ | `\gtrapprox` |
| $\lnapprox$    | `\lnapprox`    | $\gnapprox$ | `\gnapprox` | $\lesseqqgtr$ | `\lesseqqgtr` |
| $\gtreqqless$    | `\gtreqqless`    | $\eqslantless$ | `\eqslantless` | $\eqslantgtr$ | `\eqslantgtr` |
| $\precapprox$    | `\precapprox`    | $\succapprox$ | `\succapprox` | $\precnapprox$ | `\precnapprox` |
| $\succnapprox$    | `\succnapprox`    | $\subseteqq$ | `\subseteqq` | $\supseteqq$ | `\supseteqq` |
| $\subsetneqq$    | `\subsetneqq`    | $\supsetneqq$ | `\supsetneqq` |  |  |

### §A.2.7 箭头符号

| 箭头符号 | TeX代码 | 箭头符号 | TeX代码   | 箭头符号 | TeX代码   |
| -------- | ------- | --------- | --------- | --------- | --------- |
| $\overleftarrow{}$ | `\overleftarrow`    | $\overleftrightarrow{}$ | `\overleftrightarrow` | $\leftarrow$ | `\leftarrow` |
| $\uparrow$    | `\uparrow`    | $\to$ | `\to` | $\rightarrow$ | `\rightarrow` |
| $\downarrow$    | `\downarrow`    | $\leftrightarrow$ | `\leftrightarrow` | $\updownarrow$ | `\updownarrow` |
| $\nwarrow$    | `\nwarrow`    | $\nearrow$ | `\nearrow` | $\searrow$ | `\searrow` |
| $\swarrow$    | `\swarrow`    | $\nleftarrow$ | `\nleftarrow` | $\nrightarrow$ | `\nrightarrow` |
| $\leftsquigarrow$    | `\leftsquigarrow`    | $\rightsquigarrow$ | `\rightsquigarrow` | $\twoheadleftarrow$ | `\twoheadleftarrow` |
| $\twoheaduparrow$    | `\twoheaduparrow`    | $\twoheadrightarrow$ | `\twoheadrightarrow` | $\twoheaddownarrow$ | `\twoheaddownarrow` |
| $\leftarrowtail$    | `\leftarrowtail`    | $\rightarrowtail$ | `\rightarrowtail` | $\mapsfrom$ | `\mapsfrom` |
| $\mapsup$    | `\mapsup`    | $\mapsto$ | `\mapsto` | $\mapsdown$ | `\mapsdown` |
| $\updownarrowbar$    | `\updownarrowbar`    | $\hookleftarrow$ | `\hookleftarrow` | $\hookrightarrow$ | `\hookrightarrow` |
| $\looparrowleft$    | `\looparrowleft`    | $\looparrowright$ | `\looparrowright` | $\leftrightsquigarrow$ | `\leftrightsquigarrow` |
| $\nleftrightarrow$    | `\nleftrightarrow`    | $\downzigzagarrow$ | `\downzigzagarrow` | $\Lsh$ | `\Lsh` |
| $\Rsh$    | `\Rsh`    | $\Ldsh$ | `\Ldsh` | $\Rdsh$ | `\Rdsh` |
| $\curvearrowleft$    | `\curvearrowleft`    | $\curvearrowright$ | `\curvearrowright` | $\circlearrowleft$ | `\circlearrowleft` |
| $\cwopencirclearrow$    | `\cwopencirclearrow`    | $\circlearrowright$ | `\circlearrowright` | $\leftharpoonup$ | `\leftharpoonup` |
| $\leftharpoondown$    | `\leftharpoondown`    | $\upharpoonright$ | `\upharpoonright` | $\upharpoonleft$ | `\upharpoonleft` |
| $\rightharpoonup$    | `\rightharpoonup`    | $\rightharpoondown$ | `\rightharpoondown` | $\downharpoonright$ | `\downharpoonright` |
| $\downharpoonleft$    | `\downharpoonleft`    | $\rightleftarrows$ | `\rightleftarrows` | $\updownarrows$ | `\updownarrows` |
| $\leftrightarrows$    | `\leftrightarrows`    | $\leftleftarrows$ | `\leftleftarrows` | $\upuparrows$ | `\upuparrows` |
| $\rightrightarrows$    | `\rightrightarrows`    | $\downdownarrows$ | `\downdownarrows` | $\leftrightharpoons$ | `\leftrightharpoons` |
| $\rightleftharpoons$    | `\rightleftharpoons`    | $\nLeftarrow$ | `\nLeftarrow` | $\nLeftrightarrow$ | `\nLeftrightarrow` |
| $\nRightarrow$    | `\nRightarrow`    | $\Leftarrow$ | `\Leftarrow` | $\Uparrow$ | `\Uparrow` |
| $\Rightarrow$    | `\Rightarrow`    | $\Downarrow$ | `\Downarrow` | $\Leftrightarrow$ | `\Leftrightarrow` |
| $\Updownarrow$    | `\Updownarrow`    | $\Nwarrow$ | `\Nwarrow` | $\Nearrow$ | `\Nearrow` |
| $\Searrow$    | `\Searrow`    | $\Swarrow$ | `\Swarrow` | $\Lleftarrow$ | `\Lleftarrow` |
| $\Rrightarrow$    | `\Rrightarrow`    | $\rightzigzagarrow$ | `\rightzigzagarrow` | $\leadsto$ | `\leadsto` |
| $\barleftarrow$    | `\barleftarrow`    | $\rightarrowbar$ | `\rightarrowbar` | $\cupleftarrow$ | `\cupleftarrow` |
| $\multimap$    | `\multimap`    | $\longleftarrow$ | `\longleftarrow` | $\longrightarrow$ | `\longrightarrow` |
| $\longleftrightarrow$    | `\longleftrightarrow`    | $\Longleftarrow$ | `\Longleftarrow` | $\Longrightarrow$ | `\Longrightarrow` |
| $\Longleftrightarrow$    | `\Longleftrightarrow`    | $\longmapsto$ | `\longmapsto` | $\dashleftarrow$ | `\dashleftarrow` |
| $\dashrightarrow$    | `\dashrightarrow`    |  |  |||

### §A.2.8 杂项符号

| 杂项符号 | TeX代码 | 杂项符号 | TeX代码   | 杂项符号 | TeX代码   |
| -------- | ------- | --------- | --------- | --------- | --------- |
| $\$$    | `\$`    | $\cent$¢ | `\cent` | $\sterling$ | `\sterling` |
| $\yen$    | `\yen`    | $\S$ | `\S` | $\copyright$ | `\copyright` |
| $\neg$    | `\neg`    | $\circledR$ | `\circledR` | $\degree$ | `\degree` |
| $\P$    | `\P`    | $\hbar$ | `\hbar` | $\imath$ | `\imath` |
| $\i$ı   | `\i`    | $\L$Ł | `\L` | $\l$ | `\l` |
| $\lambdabar$ƛ   | `\lambdabar`    | $\jmath$ | `\jmath` | $\dag$ | `\dag` |
| $\ddag$‡  | `\ddag`    | $\perthousand$ | `\perthousand` | $\prime$ | `\prime` |
| $\backprime$    | `\backprime`    | $\hslash$ | `\hslash` | $\Im$ | `\Im` |
| $\ell$    | `\ell`    | $\wp$ | `\wp` | $\Re$ | `\Re` |
| $\mho$    | `\mho`    | $\Finv$ | `\Finv` | $\Game$ | `\Game` |
| $\forall$    | `\forall`    | $\complement$ | `\complement` | $\partial$ | `\partial` |
| $\exists$    | `\exists`    | $\nexists$ | `\nexists` | $\emptyset$ | `\emptyset` |
| $\varnothing$    | `\varnothing`    | $\increment$∆ | `\increment` | $\nabla$ | `\nabla` |
| $\QED$∎   | `\QED`    | $\infty$ | `\infty` | $\angle$ | `\angle` |
| $\measuredangle$    | `\measuredangle`    | $\sphericalangle$ | `\sphericalangle` | $\ac$ | `\ac` |
| $\sinewave$∿   | `\sinewave`    | $\hermitmatrix$⊹ | `\hermitmatrix` | $\circledS$ | `\circledS` |
| $\blacksquare$    | `\blacksquare`    | $\triangle$ | `\triangle` | $\vartriangle$ | `\vartriangle` |
| $\blacktriangle$    | `\blacktriangle`    | $\blacktriangledown$ | `\blacktriangledown` | $\triangledown$ | `\triangledown` |
| $\bigstar$    | `\bigstar`    | $\danger$☡ | `\danger` | $\spadesuit$ | `\spadesuit` |
| $\heartsuit$    | `\heartsuit`    | $\diamondsuit$ | `\diamondsuit` | $\clubsuit$ | `\clubsuit` |
| $\clubsuitopen$♧   | `\clubsuitopen`    | $\flat$ | `\flat` | $\natural$ | `\natural` |
| $\sharp$    | `\sharp`    | $\checkmark$ | `\checkmark` | $\maltese$ | `\maltese` |

### §A.2.9 口音字符

| 口音符号 | TeX代码 | 口音符号  | TeX代码   | 口音符号  | TeX代码   |
| -------- | ------- | --------- | --------- | --------- | --------- |
| $\acute a$    | `\acute a`    | $\'a$ | `\'a` | $\bar a$ | `\bar a` |
| $\breve a$    | `\breve a`    | $\dot a$ | `\dot a` | $\.a$ | `\.a` |
| $\ddot a$    | `\ddot a`    | $\''a$ | `\''a` | $\dddot a$ | `\dddot a` |
| $\ddddot a$    | `\ddddot a`    | $\grave a$ | `\grave a` | $\`a$ | `\`a` |
| $\hat a$    | `\hat a`    | $\^a$ | `\^a` | $\tilde a$ | `\tilde a` |
| $\~a$    | `\~a`    | $\vec a$ | `\vec a` | $\overline{abc}$ | `\overline{abc}` |





11.30 7w+

12.1 8w+

12.2 9w+

12.3 10w+

12.4 11w+

12.5 12w+











































































































































































