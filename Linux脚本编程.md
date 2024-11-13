# §1 Shell

## §1.1 虚拟控制台

Linux启动时，会自动创建多个虚拟控制台，以供CLI使用。进入GUI时代，我们通常使用模拟控制台终端。

```shell
Ubuntu 20.04 LTS Host tty2 # 虚拟控制台2，可以通过Ctrl + Alt + F2进入
Host login: root
Password:

root@Host:~$ tty # 通过tty命令手动查询虚拟控制台编号
/dev/tty/2
```

Linux提供了`setterm`命令用于设置CLI的样式。

| `setterm`选项                | 含义             | 取值范围                                                           |
| -------------------------- | -------------- | -------------------------------------------------------------- |
| `--background <COLOR>`     | 设置CLI的背景色      | `black`/`red`/`green`/`yellow`/`blue`/`magenta`/`cyan`/`white` |
| `--foreground <COLOR>`     | 设置CLI的前景(文本)色  | `black`/`red`/`green`/`yellow`/`blue`/`magenta`/`cyan`/`white` |
| `--inversescreen <ENABLE>` | 设置反色           | `on`/`off`                                                     |
| `--reset`                  | 重置为默认样式并清屏     |                                                                |
| `--store`                  | 将当前CLI样式设为默认样式 |                                                                |

大多数Linux发行版中，允许使用快捷键`Ctrl + Alt + F1/F7/F8`退出GUI，进入CLI的虚拟控制台中，并且使用`Ctrl + Alt + F1~F8`进行切换。

## §1.2 终端仿真器

GUI使用终端仿真器（Terminal Emulator）来模拟虚拟控制台。市面上常见的终端仿真器有：`GNOME Terminal`、`Konsole`、`Xterm`等等。

`GNOME Terminal`的快捷键如下表所示：

| `GNOME Terminal`快捷键        | 作用             |
| -------------------------- | -------------- |
| `Ctrl + Shift + N`（New）    | 创建新窗口和Shell会话  |
| `Ctrl + Shift + T`（Tab）    | 在当前窗口创建Shell会话 |
| `Ctrl + Shift + W`（Window） | 关闭当前Shell会话    |
| `Ctrl + Shift + Q`（Quit）   | 关闭当前窗口         |
| `Ctrl + Shift + C`（Copy）   | 复制             |
| `Ctrl + Shift + V`（Paste）  | 粘贴             |
| `Ctrl + Shift + F`         | 查找文本           |
| `Ctrl + Shift + G`         | 向前查找文本         |
| `Ctrl + Shift + H`         | 向后查找文本         |
| `Ctrl + Shift + J`         | 取消查找文本高亮显示     |
| `Ctrl + PageUp`            | 切换到上一个Shell会话  |
| `Ctrl + PageDown`          | 切换到下一个Shell会话  |
| `Ctrl + Shift + PageUp`    | 将当前Shell会话向前移动 |
| `Ctrl + Shift + PageDown`  | 将当前Shell会话向后移动 |

`Konsole`的快捷键如下表所示：

