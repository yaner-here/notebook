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

`plt.plot()`返回一个四元组，表示图像的坐标范围：

```python
import numpy as np
import matplotlib.pyplot as plt

plt.plot(np.arange(10) ** 2)
print(plt.axis()) # (-0.45, 9.45, -4.05, 85.05)
```

### §1.2.2 `plt.xlim()`/`plt.ylim()`

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

### §1.2.3 `plt.xticks()`/``plt.yticks()``

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

### §1.2.4 `plt.tick_params()`

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

## §1.3 图例

### §1.3.1 `plt.legend()`

`plt.legend()`用于设定图例。

```python
plt.legend(
	*args,
    **kwargs
)
```

| `plt.legend()`形参 | 作用                     | 数据类型                                                     | `plt.rcParams`对应属性                  |
| ------------------ | ------------------------ | ------------------------------------------------------------ | --------------------------------------- |
| `loc`              | 图例的位置               | `str | tuple[float, float]`<br />其中`"best" => 0`(缺省)<br />`"upper right" => 1`<br />`"upper left" => 2` <br />`"lower left" => 3`<br />`"lower right" => 4`<br />`"right"/"center right" => 5`<br />`"center left" => 6`<br />`"center right" => 7`<br />`"lower center" => 8`<br />`"upper center" => 9`<br />`"center" => 10`<br /> | `plt.rcParams["legend.loc"]`            |
| `prop`             | 图例字体属性             |                                                              |                                         |
| `title_fontsize`   | 图例字体大小             | `= None`                                                     | `plt.rcParams["legend.title_fontsize"]` |
| `markerscale`      | 图例标记大小缩放比例     | `= 1`                                                        | `plt.rcParams["legend.markerscale"]`    |
| `markerfirst`      | 图例标记是否位于文字左边 | `bool = True`                                                |                                         |
| `numpoints`        | 线条图例标记点数         | `= 1`                                                        | `plt.rcParams["legend.numpoints"]`      |
| `scatterpoints`    | 散点图图例标记点数       | `= 1`                                                        | `plt.rcParams["legend.scatterpoints"]`  |
| `frameon`          | 图例是否含有边框         |                                                              | `plt.rcParams["legend.frameon"]`        |
| `framealpha`       | 图例边框透明度           |                                                              | `plt.rcParams["legend.framealpha"]`     |
| `edgecolor`        | 图例边框颜色             |                                                              | `plt.rcParams["legend.edgecolor"]`      |
| `facecolor`        | 图例边框内的背景颜色     |                                                              | `plt.rcParams["legend.facecolor"]`      |
| `shadow`           | 图例是否有阴影           |                                                              | `plt.rcParams["legend.shadow"]`         |
| `borderpad`        | 图例边框内边距           |                                                              | `plt.rcParams["legend.borderpad"]`      |
| `labelspacing`     | 图例项目之间的间距       |                                                              | `plt.rcParams["legend.labelspacing"]`   |
| `handleheight`     | 图例句柄高度             |                                                              | `plt.rcParams["legend.handleheight"]`   |
| `handlelength`     | 图例句柄长度             |                                                              | `plt.rcParams["legend.handlelength"]`   |
| `handletextpad`    | 图例句柄和文本之间的间距 |                                                              | `plt.rcParams["legend.handletextpad"]`  |
| `handleaxespad`    | 轴和图例边框之间的间距   |                                                              | `plt.rcParams["legend.handleaxespad"]`  |
| `ncol`             | 图例的字段数             |                                                              |                                         |
| `columnspacing`    | 字段之间的间距           |                                                              | `plt.rcParams["legend.columnspacing"]`  |
| `bbox_to_anchor`   | 图例的位置               | `tuple[float, float] | tuple[float, float, float, float]`    |                                         |
| `title`            | 图例标题                 | `font.`                                                      |                                         |



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
> ```
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



11.26 3w+

11.27 4w+

11.28 5w+

