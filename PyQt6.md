# PyQt6

参考资料：

- [PyQt6开发及实例](https://book.douban.com/subject/36452422/)

# §1 初步

```python
import sys
import PyQt6.QtWidgets

app = PyQt6.QtWidgets.QApplication(sys.argv)

window = PyQt6.QtWidgets.QWidget()
window.resize(300, 240)
window.move(320, 240)
window.setWindowTitle("Title Here")

button = PyQt6.QtWidgets.QPushButton(window)
button.setText("Button")
button.move(120, 150)

window.show()
sys.exit(app.exec())
```

# §2 窗口

窗体类指的是控件对象的容器，由`PyQt6.QtWidgets.QWidget`继承而来。

| 窗体类类名                    | 名称     | 包含内容               |
| ----------------------------- | -------- | ---------------------- |
| `PyQt6.QtWidgets.QWidget`     | 基类     |                        |
| `PyQt6.QtWidgets.QDialog`     | 对话框类 | 标题栏、帮助、关闭按钮 |
| `PyQt6.QtWidgets.QMainWindow` | 主窗口类 | 菜单栏、工具栏、状态栏 |

一个完整的Qt程序可能有GUI界面（`PyQt6.QtWidgets.QApplication`），也可能没有GUI界面（`PyQt6.QtWidgets.QCoreApplication`），但是都可以包含若干个窗口。

## §2.1 `PyQt6.QtWidgets.QWidget`

### §2.1.1 坐标系统

以屏幕的左上角为原点，向右为X轴正方向，向下为Y轴正方向，就形成了一套用于定位顶层窗口的坐标系统。

我们知道，一个窗体由标题栏和客户区上下并列组成。标题栏和客户区共同组成了边框（Frame）。而控件使用的坐标系统仅在客户区内，也就是说对应的原点是客户区的左上角，而不是边框的左上角。

### §2.1.2 窗口标题(`windowTitle`)

在QT Designer中，窗口标题由`windowTitle`字段指定，在代码中可以使用`QtWidgets.windowTitle() -> str`获取标题，用`QtWidgets.setWindowTitle(str)`重新设置标题。

### §2.1.3 窗体尺寸与位置(`geometry`)

在Qt Designer中，窗体尺寸与位置由`geometry`指定。在代码中使用`QtWidgets.setGeometry()`指定，其函数签名如下所示：

```python
window = PyQt6.QtWidgets.QWidget()
window.setGeometry(x: int, y: int, width: int, height: int)
window.setGeometry(PyQt6.QtCore.QRect(x: int, y: int, width: int, height: int))
```

初次以外，我们可以使用以下方法分别设置窗体的尺寸与位置：

| 方法名称                                                     | 作用           |
| ------------------------------------------------------------ | -------------- |
| `PyQt6.QtWidgets.move(x: int, y: int)`                       | 设置窗体的位置 |
| `PyQt6.QtWidgets.resize(w: int, h: int)`<br />`PyQt6.QtWidgets.resize(QSize)` | 设置窗体的尺寸 |

Qt提供了以下方法获取窗体的尺寸：

| 方法名称                     | 返回值                | 作用                      |
| ---------------------------- | --------------------- | ------------------------- |
| `PyQt6.QtWidgets.x()`        | `int`                 | 控件相对于父控件的X轴位置 |
| `PyQt6.QtWidgets.y()`        | `int`                 | 控件相对于父控件的Y轴位置 |
| `PyQt6.QtWidgets.pos()`      | `PyQt6.QtCore.QPoint` | 控件相对于父控件的位置    |
| `PyQt6.QtWidgets.width()`    | `int`                 | 控件的宽度（X轴长度）     |
| `PyQt6.QtWidgets.height()`   | `int`                 | 控件的高度（Y轴长度）     |
| `PyQt6.QtWidgets.size()`     | `PyQt6.QtCore.QSize`  | 控件的尺寸                |
| `PyQt6.QtWidgets.geometry()` | `PyQt6.QtCore.QRect`  | 控件的位置和尺寸          |

Qt提供了以下方法限制窗口的尺寸范围：

| 方法名称                                                     | 作用             |
| ------------------------------------------------------------ | ---------------- |
| `PyQt6.QtWidgets.setMinimumWidth(int)`                       | 设置窗体最小宽度 |
| `PyQt6.QtWidgets.setMinimumHeight(int)`                      | 设置窗体最小高度 |
| `PyQt6.QtWidgets.setMinimumSize(width, height)`<br />`PyQt6.QtWidgets.setMinumumSize(QSize)` | 设置窗体最小尺寸 |
| `PyQt6.QtWidgets.setMaximumWidth(int)`                       | 设置窗体最小宽度 |
| `PyQt6.QtWidgets.setMaximumHeight(int)`                      | 设置窗体最小高度 |
| `PyQt6.QtWidgets.setMaximumSize(width, height)`<br />`PyQt6.QtWidgets.setMaximumSize(QSize)` | 设置窗体最小尺寸 |
| `PyQt6.QtWidgets.setFixedWidth(int)`                         | 设置窗体固定宽度 |
| `PyQt6.QtWidgets.setFixedHeight(int)`                        | 设置窗体固定高度 |
| `PyQt6.QtWidgets.setFixedSize(width, height)`<br />`PyQt6.QtWidgets.setFixedSize(QSize)` | 设置窗体固定尺寸 |

Qt使用`PyQt6.QtWidgets.QSizePolicy`来指定窗体尺寸的行为，它由X轴和Y轴的两个`PyQt6.QtWidgets.QSizePolicy.Policy`和两个拉伸系数构成，外加一个用于表示宽度和高度是否相关的标志位：

```python
window = PyQt6.QtWidgets.QWidget()
window.setSizePolicy(PyQt6.QtWidgets.QSizePolicy)
window.setSizePolicy(
    hor: PyQt6.QtWidgets.QSizePolicy.Policy
	vec: PyQt6.QtWidgets.QSizePolicy.Policy
)
```

其中`PyQt6.QtWidgets.QSizePolicy.Policy`是Python中`enum.Enum`类的子类，有以下字段可供使用：

| `PyQt6.QtWidgets.QSizePolicy.Policy`取值              | 作用                           |
| ----------------------------------------------------- | ------------------------------ |
| `PyQt6.QtWidgets.QSizePolicy.Policy.Fixed`            | 固定尺寸                       |
| `PyQt6.QtWidgets.QSizePolicy.Policy.Minimum`          | `sizeHint()`返回的最小尺寸     |
| `PyQt6.QtWidgets.QSizePolicy.Policy.Maximum`          | `sizeHint()`返回的最大尺寸     |
| `PyQt6.QtWidgets.QSizePolicy.Policy.Preferred`        | `sizeHint()`返回的推荐尺寸     |
| `PyQt6.QtWidgets.QSizePolicy.Policy.MinimumExpanding` | `sizeHint()`返回的推荐最小尺寸 |
| `PyQt6.QtWidgets.QSizePolicy.Policy.Expanding`        | `sizeHint()`返回的推荐最大尺寸 |
| `PyQt6.QtWidgets.QSizePolicy.Policy.Ignored`          | 最大尺寸                       |

可以使用下列方法获取或更改`PyQt6.QtWidgets.QSizePolicy.Policy`中的字段：

| 方法名                                | 作用             |
| ------------------------------------- | ---------------- |
| `PyQt6.QtWidgets.horizontalPolicy()`  | 获取水平缩放行为 |
| `PyQt6.QtWidgets.verticalPolicy()`    | 获取垂直缩放行为 |
| `PyQt6.QtWidgets.horizontalStretch()` | 获取水平缩放系数 |
| `PyQt6.QtWidgets.verticalStretch()`   | 获取垂直缩放系数 |
| `PyQt6.QtWidgets.horizontalPolicy()`  | 获取水平缩放行为 |
| `PyQt6.QtWidgets.verticalPolicy()`    | 获取垂直缩放行为 |
| `PyQt6.QtWidgets.horizontalStretch()` | 获取水平缩放系数 |
| `PyQt6.QtWidgets.verticalStretch()`   | 获取垂直缩放系数 |

当窗口的位置或尺寸发生改变时，会触发对应的`moveEvent`和`resizeEvent`事件。

### §2.1.4 调色板(`PyQt6.QtGui.QPalette`)

`PyQt6.QtGUI.QColor`类用于定义RGB/RGBA颜色。

```python
class QColor(PyQt6.sip.simplewrapper):
    def __init__(self, color: PyQt6.QtCore.GlobalColor) -> None: ...
    def __init__(self, rgb: int) -> None: ...
    def __init__(self, rgba64: PyQt6.QtGUI.QRgba64) -> None: ...
    def __init__(self, name: str) -> None: ...
    def __init__(self, r: int, g: int, b: int, alpha: int) -> None: ...
    def __init__(self, a0: PyQt6.QtGui.Qcolor) -> None: ...
```

给定一个`PyQt6.QtGUI.QColor`实例，我们也可以使用`.setNamedColor`来改变其颜色：

```python
color = PyQt6.QtGui.QColor(0, 0, 0)
color.setNamedColor("#66ccff")
```

```python
import PyQt6
import PyQt6.QtWidgets, PyQt6.QtGui, PyQt6.QtCore
import sys

app = PyQt6.QtWidgets.QApplication(sys.argv)

window = PyQt6.QtWidgets.QWidget()
window.setGeometry(320, 240, 300, 240)

palette = PyQt6.QtGui.QPalette()
palette.setColor(
    PyQt6.QtGui.QPalette.ColorRole.Window,
    PyQt6.QtGui.QColor("#66ccff")
)
window.setAutoFillBackground(True)
window.setPalette(palette)

label = PyQt6.QtWidgets.QLabel(window)
label.setText("Hello, World!")
label.setAutoFillBackground(True)

textedit = PyQt6.QtWidgets.QTextEdit(window)
textedit.setGeometry(20, 20, 200, 50)
color = PyQt6.QtGui.QColor(255,50,255)
textedit.setTextColor(color)
textedit.setText("Hello, World!")

window.show()
sys.exit(app.exec())
```

### §2.1.5 字体(`PyQt6.QtGui.QFont`)

`PyQt6.QtGui.QFont`的一个实例表示了某款字形的所有信息。

```python
class QFont(PyQt6.sip.simplewrapper):
    def __init__(self) -> None: ...
    def __init__(self, families: typing.Iterable[str], pointSize: int, weight: int, italic: bool) -> None: ...
    def __init__(self, family: str, pointerSize: int, weight: int, italic: bool)
    def __init__(self, a0: PyQt6.QtGui.QFont)
```

Qt[提供了以下方法](https://doc.qt.io/qtforpython-6/PySide6/QtGui/QFont.html)用于修改`PyQt6.QtGui.QFont`实例中的信息：

| 方法名                                                       | 作用                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `PyQt6.QtGui.QFont.setBold(bool)`                            | 粗体                                                         |
| ``PyQt6.QtGui.QFont.setCaptitalization(a0: PyQt6.QtGui.QFont.Capitalization)`` | 首字母大写                                                   |
| `PyQt6.QtGui.QFont.setFamilies(typing.Iterable[str])`        | 字体名称列表                                                 |
| `PyQt6.QtGui.QFont.setFamily(str)`                           | 字体名称                                                     |
| `PyQt6.QtGui.QFont.setFeature(tag: str, value: int)`         | 字体高级属性                                                 |
| `PyQt6.QtGui.QFont.setFixedPitch(bool)`                      | 字形固定高度                                                 |
| `PyQt6.QtGui.QFont.setHintingPreference(hintingPreference: PyQt6.QtGui.QFont.HintingPreference)` | 跨平台渲染引擎偏好                                           |
| `PyQt6.QtGui.QFont.setItalic(bool)`                          | 斜体                                                         |
| `PyQt6.QtGui.QFont.setKerning(bool = true)`                  | 字距自动调整                                                 |
| `PyQt6.QtGui.QFont.setLetterSpacing(type: PyQt6.QtGui.QFont.SpacingType, spacing: float)` | 字母间距                                                     |
| `PyQt6.QtGui.QFont.setOverline(bool)`                        | 上划线                                                       |
| `PyQt6.QtGui.QFont.setPixelSize(int)`                        | 与设备相关的字体大小                                         |
| `PyQt6.QtGui.QFont.setPointSize(int)`                        | 与设备无关的字体大小                                         |
| `PyQt6.QtGui.QFont.setPointSizeF(float)`                     | 与设备无关的字体大小                                         |
| `PyQt6.QtGui.QFont.setStrikeOut(bool)`                       | 删除线                                                       |
| `PyQt6.QtGui.QFont.setStyle(str|PyQt6.QtGui.QFont.Style)`    | 设置CSS样式表                                                |
| `PyQt6.QtGui.QFont.setStyleHint(PyQt6.QtGui.QFont.StyleHint, strategy: PyQt6.QtGui.QFont.StyleStrategy)` | 设置`styleHint`                                              |
| `PyQt6.QtGui.QFont.setStyleName(str)`                        | 设置字体的`styleName`，例如哥特体、手写体等。详见[namestyle.art](https://www.namestyle.art/) |
| `PyQt6.QtGui.QFont.setStyleStrategy(PyQt6.QtGui.QFont.StyleStrategy)` | 设置字体的`styleStrategy`                                    |
| `PyQt6.QtGui.QFont.setUnderline(bool)`                       | 下划线                                                       |
| `PyQt6.QtGui.QFont.setVariableAxis(tag: str, value: float)`  | 设置字体支持的高级特性                                       |
| `PyQt6.QtGui.QFont.setWeight(PyQt6.QtGui.QFont.Weight)`      | 字重（粗细）                                                 |
| `PyQt6.QtGui.QFont.setWordSpacing(float)`                    | 单词间距                                                     |

