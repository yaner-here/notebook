# §1 Shell

## §1.1 Shell会话

### §1.1.1 虚拟控制台

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

### §1.1.2 终端仿真器

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

| `Konsole`快捷键               | 作用                             |
| -------------------------- | ------------------------------ |
| `Ctrl + Shift + N`（New）    | 创建新窗口和Shell会话                  |
| `Ctrl + Shift + T`（Tab）    | 在当前窗口创建Shell会话                 |
| `Ctrl + Shift + W`（Window） | 关闭当前Shell会话                    |
| `Ctrl + Shift + Q`（Quit）   | 关闭当前窗口                         |
| `Ctrl + Shift + S`（Save）   | **保存当前Shell会话为`.txt`或`.html`** |
| `Ctrl + Shift + P`         | **打印当前Shell会话**                |
| `Ctrl + Shift + C`（Copy）   | 复制                             |
| `Ctrl + Shift + V`（Paste）  | 粘贴                             |
| `Ctrl + Alt + S`           | **修改当前Shell会话标题**              |
| `Ctrl + Alt + U`           | **上传文件（需支持`ZMODEM`文件传输协议）**    |
| `Ctrl + Shift + F`         | 查找文本                           |
| `F3`                       | **向前查找文本**                     |
| `Shift + F3`               | **向后查找文本**                     |
| `Shift + Up/Down`          | **向上滚动文本**                     |
| `Shift + PageUp/PageDown`  | **向下滚动文本**                     |
| `Ctrl + Shift + L`         | **关闭当前Shell会话并新建一个Shell会话**    |
| `Ctrl + Shift + H`         | **关闭当前窗口并新建一个窗口**              |
| `Ctrl + Shift + K`         | **清空当前Shell会话的输出**             |
| `Ctrl + Shift + B`         | 为当前所在目录创建书签                    |
| `Ctrl + Shift + M`         | 打开/关闭菜单栏                       |
| `Ctrl + Shift + ,`         | 打开`Konsole`设置                  |

## §1.2 Shell类型

当Linux用户登录时，默认启动的Shell取决于`/etc/passwd`记录的用户配置：

```passwd
$ sudo cat /etc/passwd
	root:x:0:0:root:/root:/bin/bash
```

大多数Linux发行版会在`/etc/shells`显示该环境已安装的Shell：

```shells
$ cat /etc/shells
	# /etc/shells: valid login shells
	/bin/sh
	/bin/bash
	/usr/bin/bash
	/bin/rbash
	/usr/bin/rbash
	/usr/bin/sh
	/bin/dash
	/usr/bin/dash
```

`bash`本身提供了以下常见的参数：

- `-c <STRING>`：执行`<STRING>`命令后退出，将`STDOUT`和`STDERR`重定向到父Shell
- `-i`：重定向`STDIN`到子Shell的交互式子Shell
- `-l`：作为登录Shell启动
- `-r`：将子Shell限制在父Shell所在路径中

## §1.3 启动文件

启动Shell时，`bash`会尝试预加载一些Shell脚本，我们将其称为启动文件。至于预加载哪些启动文件，这取决于启动Shell的方式——登录Shell、交互式Shell、非交互式Shell。

如果要持久化启动文件，针对系统而言推荐把脚本放在`/etc/profile.d`目录下，针对用户而言推荐把脚本放在`~/.bashrc`。
### §1.3.1 登录Shell

登录Linux系统时，`bash`会作为登录Shell启动。登录Shell预加载以下启动文件：

- `/etc/profile`：全局启动文件，第一个优先执行
- `~/.bash_profile`：用户启动文件，第二个优先执行
- `~/.bash_login`：用户启动文件，第三个优先执行
- `~/.profile`：用户启动文件，第四个优先执行
- `~/.bashrc`：用户启动文件，不由`bash`默认执行，而是由前四者执行
- `/etc/environment`、`~/.pam_environment`：需要Linux启用可拆卸式认证模块（PAM）

### §1.3.2 交互式Shell

在Shell中使用`bash`命令启动的子Shell称为交互式Shell，它仍然可以接受用户输入。交互式Shell只加载：

- `~/.bashrc`：用户启动文件

### §1.3.3 非交互式Shell

使用`bash <FILE>`执行脚本时，启动的Shell称为非交互式Shell。它不预加载任何启动文件，只会执行`$BASH_ENV`值对应的脚本路径。



# §2 常用命令 

## §2.1 进程

### §2.1.1 `ps`

`ps`命令用于输出**当前时刻**的进程信息。

```shell
$ ps
      PID    PPID    PGID     WINPID   TTY         UID    STIME COMMAND
     1112    1111    1112       7060  pty0      197609 00:50:15 /usr/bin/bash
     1823    1112    1823      11068  pty0      197609 00:59:44 /usr/bin/ps
```

`ps`命令支持显示的进程信息有：

- `UID`：启动该进程用户的`UID`
- `PID`：该进程的`PID`
- `PPID`：父进程的`PID`
- `C`：进程生命周期中的CPU利用率
- `STIME`：进程启动时的系统时间
- `TTY`：进程所属的Shell会话
- `TIME`：进程累计运行的CPU时间
- `COMMAND`：启动该进程的程序路径
- `F`：进程的系统标志
- `S`：进程的状态（`O`为正在运行，`S`为休眠、`R`为等待运行、`Z`为僵尸进程，即该进程已停止但父进程未响应、T为停止）
- `PRI`：进程的优先级（数字越小，优先级越高）
- `NI`：进程的谦让度（用于决定`PRI`）
- `ADDR`：进程的内存地址
- `SZ`：进程的`swap`体积
- `WCHAN`：进程休眠的内核函数地址

| `ps`选项                         | 作用（`MSYS2`环境）                                                 |
| ------------------------------ | ------------------------------------------------------------- |
| `-a`/`--all`/`-e`/`--everyone` | 显示所有用户的进程                                                     |
| `-s`（Summary）                  | 只显示`PID`、`TTY`、`STIME`、`COMMAND`                              |
| `-f`（Full）                     | 只显示`UID`、`PID`、`PPID`、`TTY`、`STIME`、`COMMAND`                 |
| `-l`（Long）                     | 只显示`PID`、`PPID`、`PGID`、`WINPID`、`TTY`、`UID`、`STIME`、`COMMAND` |
| `-p <PID>`（Process）            | 只显示特定`PID`的进程                                                 |
| `-u <UID>`（User）               | 只显示特定`UID`的进程                                                 |
| `--forest`                     | 展示父子进程关系树状图                                                   |

```shell
$ ps --forest
    PID TTY          TIME CMD
   5895 tty2     00:00:00 login
  64364 tty2     00:00:00  \_ bash
  64391 tty2     00:00:00      \_ bash
  64398 tty2     00:00:00          \_ bash
  64405 tty2     00:00:00              \_ bash
  64412 tty2     00:00:00                  \_ bash
```

### §2.1.2 `top`

`top`命令用于**实时输出**进程信息。

```shell
top - 02:04:07 up  5:55,  0 user,  load average: 0.07, 0.03, 0.00
Tasks:   6 total,   1 running,   5 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
MiB Mem :  15911.5 total,  13352.6 free,   1299.5 used,   1536.7 buff/cache
MiB Swap:   4096.0 total,   4096.0 free,      0.0 used.  14612.1 avail Mem

  PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
    1 root      20   0    2452   1604   1496 S   0.0   0.0   0:00.00 init(kali-linux
    5 root      20   0    2460      4      0 S   0.0   0.0   0:00.00 init
   12 root      20   0    2460    108      0 S   0.0   0.0   0:00.00 SessionLeader
   13 root      20   0    2476    116      0 S   0.0   0.0   0:00.00 Relay(14)
   14 root      20   0    7192   4020   3356 S   0.0   0.0   0:00.00 bash
   28 root      20   0    9104   4600   2524 R   0.0   0.0   0:00.00 top
```

- 第一行显示了系统概况。分别是系统当前时间、运行时长、登录用户数量、最近1/5/15分钟的平均CPU负载。
- 第二行显示了进程概况。分别是系统进程总数、运行中/休眠中/已停止/已僵化的进程总数。
- 第三行显示了CPU概况。分别是用户空间（`us`）占用CPU百分比、内核空间（`sy`）占用CPU百分比、用户空间中改变过优先级的进程（`ni`）占用CPU百分比、空闲（`id`）CPU百分比、硬中断（`hi`）占用CPU百分比、软中断（`si`）占用CPU百分比、虚拟化（`st`）占用CPU百分比。
- 第四行和第五行显示了物理内存/虚拟内存概况。分别是内存总量（`total`）、空闲内存（`free`）、已用内存（`used`）、缓存与缓冲区占用内存（`buff/cahce`）
- 最后的表格显示了进程概况。
	- `PID`：当前进程的PID
	- `USER`：当前进程所属用户的用户名
	- `PR`：当前进程的优先级
	- `NI`：当前进程的谦让度
	- `VIRT`：当前进程的虚拟内存占用量
	- `RES`：当前进程的物理内存占用量
	- `SHR`：当前进程的共享内存占用量
	- `S`：进程的状态（`R`为运行中、`S`为休眠中、`D`代表可中断休眠中、`T`为停止、`Z`为僵化）
	- `%CPU`：当前进程的CPU占用时间比例
	- `%MEM`：当前进程的物理内存占用比例
	- `TIME+`：当前进程CPU占用时间之和
	- `COMMAND`：启动当前进程的程序路径

`top`界面支持命令`f`。事实上，`top`能显示的进程信息还有很多。在`top`界面内按下`f`键，可设置显示的进程信息与排序依据，排序依据缺省为`%CPU`。

`top`界面支持命令`d`，用于更改刷新时间间隔。

### §2.1.3 `kill`

在Linux中，信号的本质是一种软件中断，进程之间使用信号来通信。常用的部分标准Unix进程信号的定义如下表所示：

| 信号编号 | 信号名称                 | 信号作用                              | 标准         | `tty`的等价快捷键 |
| ---- | -------------------- | --------------------------------- | ---------- | ----------- |
| `1`  | `SIGHUP`             | 虚拟控制台已关闭                          | `POSIX`    |             |
| `2`  | `SIGINT`             | 硬中断                               | `ANSI`     | `Ctrl + C`  |
| `3`  | `SIGQUIT`            | 硬退出                               | `POSIX`    | `Ctrl + \`  |
| `4`  | `SIGILL`             | 调用非法指令                            | `ANSI`     |             |
| `5`  | `SIGTRAP`            | 调试器断点跟踪                           | `POSIX`    |             |
| `6`  | `SIGABRT`            | 调用`abort()`                       | `BSD`      |             |
| `7`  | `SIGBUS`             | 访问总线的非法物理地址                       | `BSD`      |             |
| `8`  | `SIGFPE`             | 浮点数异常                             | `ANSI`     |             |
| `9`  | `SIGKILL`            | 强制终止进程（**无法拦截和处理**）               | `POSIX`    |             |
| `10` | `SIGUSR1`            | 自定义信号                             | `POSIX`    |             |
| `11` | `SIGSEGV`            | 分段错误（`Segment Fault`）             |            |             |
| `12` | `SIGUSR2`            | 自定义信号                             | `POSIX`    |             |
| `13` | `SIGPIPE`            | 管道另一端的接受进程不存在                     | `POSIX`    |             |
| `14` | `SIGALRM`            | 进程调用`alarm()`                     | `POSIX`    |             |
| `15` | `SIGTERM`            | 请求终止进程（**可以拦截和处理**）               | `ANSI`     |             |
| `16` | `SIGSTKFLT`          | 堆栈损坏或溢出                           |            |             |
| `17` | `SIGCHLD`            | 子进程终止、中断、恢复                       | `POSIX`    |             |
| `18` | `SIGCONT`            | 从`SIGSTOP`停止状态恢复运行                | `POSIX`    |             |
| `19` | `SIGSTOP`            | 强制暂停进程（**无法拦截和处理**），直到收到`SIGCONT` | `POSIX`    |             |
| `20` | `SIGTSTP`            | 请求暂停进程（**可以拦截和处理**），直到收到`SIGCONT` | `POSIX`    | `Ctrl + Z`  |
| `21` | `SIGTTIN`            | 请求从`tty`中读取内容，暂停进程直到收到`SIGCONT`   | `POSIX`    |             |
| `22` | `SIGTTOU`            | 请求向`tty`中写入内容，暂停进程直到收到`SIGCONT`   | `POSIX`    |             |
| `23` | `SIGURG`             | `Socket`收到带有`URGENT`标志的包          | `BSD`      |             |
| `24` | `SIGXCPU`            | CPU调度决定暂停进程                       | `BSD`      |             |
| `25` | `SIGXFSZ`            | 进程的文件体积超过阈值                       | `BSD`      |             |
| `26` | `SIGVTALRM`          | 进程耗尽时间片                           | `BSD`      |             |
| `27` | `SIGPROF`            | 性能测试计时器结束                         | `BSD`      |             |
| `28` | `SIGWINCH`           | 改变窗口尺寸                            | `BSD`      |             |
| `29` | `SIGIO`              | `I/O`从阻塞状态恢复                      | `System V` |             |
| `30` | `SIGPWR`             | 电源故障                              | `System V` |             |
| `31` | `SIGUNUSED`/`SIGSYS` | 未定义信号                             | `System V` |             |

`kill -l`会展示当前环境的Linux内核定义的所有信号，`kill -l <SIGNAL>`用于在`<SIGNAL>`信号名与对应宏定义编号之间来回转换：

```shell
# kill -l
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGEMT       8) SIGFPE       9) SIGKILL     10) SIGBUS
11) SIGSEGV     12) SIGSYS      13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGURG      17) SIGSTOP     18) SIGTSTP     19) SIGCONT     20) SIGCHLD
21) SIGTTIN     22) SIGTTOU     23) SIGIO       24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGPWR      30) SIGUSR1
31) SIGUSR2     32) SIGRTMIN    33) SIGRTMIN+1  34) SIGRTMIN+2  35) SIGRTMIN+3
36) SIGRTMIN+4  37) SIGRTMIN+5  38) SIGRTMIN+6  39) SIGRTMIN+7  40) SIGRTMIN+8
41) SIGRTMIN+9  42) SIGRTMIN+10 43) SIGRTMIN+11 44) SIGRTMIN+12 45) SIGRTMIN+13
46) SIGRTMIN+14 47) SIGRTMIN+15 48) SIGRTMIN+16 49) SIGRTMAX-15 50) SIGRTMAX-14
51) SIGRTMAX-13 52) SIGRTMAX-12 53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9
56) SIGRTMAX-8  57) SIGRTMAX-7  58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4
61) SIGRTMAX-3  62) SIGRTMAX-2  63) SIGRTMAX-1  64) SIGRTMAX

# kill -l SIGINT
2

# kill -l INT
2

# kill -l 2
INT
```

键盘本身并不发送信号，而是虚拟控制台通常规定了一些从快捷键到`ASCII`控制字符的映射规则，有些`ASCII`控制字符对应着特定的信号。这些规则可以通过`stty -a`查看。如上表所示，只有`Ctrl + C`、`Ctrl + \`、`Ctrl + Z`对应的`ASCII`控制字符能够发送信号。

```shell
$ stty -a | grep -Ewoe "\w+ = \^[a-zA-Z0-9];"
intr = ^C;
kill = ^U;
eof = ^D;
swtch = ^Z;
start = ^Q;
stop = ^S;
susp = ^Z;
rprnt = ^R;
werase = ^W;
lnext = ^V;
discard = ^O;
```

只有拥有`root`权限的用户才可以向其它进程发送信号。我们使用`kill -s <SIGNAL> <PID>`向进程发送信号。

```shell
# kill -s INT 382
```

### §2.1.4 `pkill`

`kill <PID>`只能使用进程的`PID`来终止进程。在此基础上，`pkill <COMMAND>`支持指定进程名称（允许通配符）来终止进程。

```shell
# pkill http*
```

## §2.2 存储

### §2.2.1 `mount`

`mount`命令用于查询当前的挂载情况，并挂载或取消挂载存储设备。

`mount`展示的挂载情况由四部分构成：设备文件名、挂载点路径、文件系统类型、已挂载设备的访问状态。

```shell
$ mount # 展示当前挂载情况
C:/msys64 on / type ntfs (binary,noacl,auto)
C:/msys64/usr/bin on /bin type ntfs (binary,noacl,auto)
C: on /c type ntfs (binary,noacl,posix=0,user,noumount,auto)
D: on /d type exfat (binary,noacl,posix=0,user,noumount,auto)
E: on /e type vfat (binary,noacl,posix=0,user,noumount,auto)

$ mount -t exfat # 只展示当前exfat文件系统的挂载情况
D: on /d type exfat (binary,noacl,posix=0,user,noumount,auto)
```

`mount -t <TYPE> <DEVICE> <DIRECTORY>`用于挂载设备`<DEVICE>`到指定的目录`<DIRECTORY>`下。下表展示了部分常见的文件系统类型：

| 文件系统`<TYPE>`    | 含义                   | Windows支持 | Linux支持 |
| --------------- | -------------------- | --------- | ------- |
| `vfat`（`FAT32`） | 微软的`FAT32`文件系统       | ✅         | ✅       |
| `ntfs`          | 微软的`NTFS`文件系统        | ✅         | ✅       |
| `exfat`         | 扩展`FAT`文件系统          | ✅         | ✅       |
| `iso9660`       | 标准`CD-ROM`与`DVD`文件系统 | ✅         | ✅       |
| `ext4`          | Linux的`ext4`文件系统     | ❎         | ✅       |

`-o <OPTION>`用于设置挂载的选项：

- `ro`：以只读形式挂载
- `rw`：以读写形式挂载
- `user`：允许普通用户挂载
- `check-none`：挂载时不执行完整性校验
- `loop`：挂载文件

### §2.2.2 `umount`

`umount [<DIRECTORY>|<DEVICE>]`用于卸载设备，可以通过设备名`<DEVICE>`或挂载点`<DIRECTORY>`指定设备。

### §2.2.3 `df`

`df`命令用于显示设备剩余存储空间。每一行输出的信息分别为设备文件位置、`1KB`块总数、`1KB`块占用数、`1KB`块可用数、已用空间百分比、挂载点。

```shell
$ df
Filesystem      1K-blocks      Used  Available Use% Mounted on
/dev/sdf       1055762868   1038500 1001020896   1% /
rootfs            8143404      2060    8141344   1% /init
none              8143404         0    8143404   0% /dev
C:\            1999461372 468076824 1531384548  24% /mnt/c

$ df -t exfat -t ntfs # 同理可用-t筛选多种文件系统
```

### §2.2.4 `du`

`du`命令用于展示特定目录下各个文件夹的磁盘占用情况。实践中，我们常用`-c`展示已列出文件的总占用空间、`-h`按人类易读格式输出（而非原始的`1KB`单位）、`-s`只输出一行关于当前目录`./`的总占用空间。

## §2.3 处理数据

### §2.3.1 `sort`

`sort <OPTION>* <FILE>+`命令用于将给定文件中的数据，按特定规则逐行排序。

`sort`支持以下排序规则：

- `<NONE>`：缺省时按字典序升序排序
- `-n`/`--numeric-sort`/`--sort=numeric`：按十进制数字序升序排序
- `-R`/`--random-sort`/`--sort=random`：洗乱
	- `--random-source=<FILE>`：设置随机数种子
- `-V`/`--version-sort`/`--sort=version`：依据版本号格式，以`.`为分隔符，按字典序升序排序
- `-M`/`--month-sort`/`--sort=month`：按三字母月份英文缩写升序排序（`MON`、`FEB`、...）
- `-h`/`--human-numeric-sort`/`--sort=human-numeric`：按人类可读数字格式（`K`、`M`、`G`、`T`、...）升序排序
- `-g`/`--general-numeric-sort`/`--sort=general-numeric`：按二/八/十/十六进制数字格式（`0b1`、`02`、`3`、`0x4`）升序排序
- `-d`/`--dictionary-order`：依据路径格式，以`/`为分隔符，按字典序升序排序
- `-r`/`--reverse`：逆序（即降序）排序
- `[-k/--key [F[.C1][OPTS1][,F[.C2][OPTS2]]]]+`：指定更复杂的排序规则。`F`表示以空格分隔的第`F`个字段；`C1`/`C2`表示当前字段从第几个字符开始或结尾（含）作为排序依据，从`1`开始数，缺省表示首尾字符；`OPTS_1`表示当前字段的第`C1`个字符的排序规则；`OPTS_2`表示当前字段的第`[C1, C2]`位字符的排序规则。多个`-k/--key`表示排序规则优先级的先后。

针对每一行的文本处理，有以下选项可用：

- `-b`/`--ignore-leading-blanks`：忽略每一行的前导空格
- `-f`/`--ignore-case`：忽略大小写
- `-i`/`--ignore-non-printing`：忽略`ASCII`控制字符
- `-t`/`--field-separator=<SEP>`：指定分隔符`<SEP>`

针对排序的相关操作，有以下选项可用：

- `-c`/`--check`/`--check=diagnose-first`：输出从首行起，第一行不满足排序规则的信息
- `--check=quiet`/`--check=slient`：如果不满足排序规则，则返回`1`，反之返回`0`
- `-m`/`--merge`：需要确保`<FILE>+`均已排序，输出其归并排序的结果
- `-s`/`--stable`：启用稳定排序
- `-u`/`--unique`：与`-c`合用时表示检查严格排序，不与`-c`合用时重复行只输出一次

针对性能方面，有以下选项可用：

- `-S`/`--buffer-size=<SIZE>`：指定内存占用上限
- `-T`/`--temporary-directory=<DIR>`：指定临时文件夹目录

针对输出方面，有以下选项可用：

- `-o`/`--output=<FILE>`：将`STDOUT`重定向到文件`<FILE>`
- `-z`/`--zero-terminated`：将输出的`\n`替换为`\0`

```shell
$ cat test.txt
1 2
2 1
5 3
4 2
4 1
4 3

$ sort --check test.txt
sort: test.txt:4: disorder: 4 2

$ sort --check=quiet test.txt
	# exit code with 1
```

### §2.3.2 `grep`

`grep <OPTION>* <PATTERN> <FILE>`命令用于逐行搜索匹配指定模式的文本，输出包含该模式的行内容。

特殊地，`grep`提供了以下常用选项：

- `-v`/`--invert-match`：输出不匹配指定模式的文本
- `-n`/`--line-number`：在每一行的输出结果前添加行号`<LINE>:`
- `-c`/`--count`：只输出一行，表示匹配模式的行总数
- `[-e/--regexp=<REGEX>]*`：指定多个正则表达式

Linux社区还提供支持POSIX扩展正则表达式的`egrep`，还有`fgrep`等扩展版本。

### §2.3.3 `gzip`/`gunzip`

`gzip [<FILE>|<DIRECTORY>]`用于递归地逐个压缩文件成`.gz`格式，`gunzip`用于解压。

```shell
$ ls
1.txt  2.txt

$ gzip *.txt
$ ls
1.txt.gz  2.txt.gz

$ gunzip *.txt.gz
$ ls
1.txt  2.txt
```

### §2.3.4 `tar`

`tar <FUNCTION> [<OPTION>]* <OBJECT>+`是一种将多个文件合并成一个文件的归档工具。

`tar`中的`<FUNCTION>`定义了以下操作：

- `-A`/`--concatenate`：在一个`.tar`文件的末尾追加另一个`.tar`文件
- `-c`/`--create`：创建一个新`.tar`文件
- `-d`/`--diff`：检查`.tar`文件与文件系统的不同之处
- `--delete`：删除`.tar`文件中的文件
- `-r`/`--append`：在`.tar`文件的末尾追加一个新文件
- `-t`/`--list`：列出`.tar`文件的内容
- `-u/--update=<FILE>*`：用更新的同名文件替换`.tar`中的同名旧文件
- `-x`/`--extract`：从`.tar`中提取文件

```shell
$ tar -c -f txt1.tar 1.txt 2.txt # 创建归档文件
$ tar -t -f txt1.tar # 查看归档文件中的内容
	1.txt
	2.txt

$ tar -r -f txt1.tar 3.txt 4.txt # 向tar文件添加文件
$ tar -t -f txt1.tar
	1.txt
	2.txt
	3.txt
	4.txt

$ tar --delete 3.txt 4.txt -f txt1.tar # 从tar文件删除文件
$ tar -t -f txt1.tar
1.txt
2.txt

$ tar -c 1.txt 2.txt -f txt1.tar
$ tar -c 3.txt 4.txt -f txt2.tar
$ tar -A txt1.tar -f txt2.tar # 将txt1.tar中的文件追加到txt2.tar的末尾
$ tar -t -f txt2.tar
	3.txt
	4.txt
	1.txt
	2.txt

$ echo "abc" > 1.txt
$ tar -d -f txt1.tar # 检测文件是否被修改
	1.txt: Mod time differs
	1.txt: Size differs
$ tar -x -f txt1.tar -C ./extract # 更新tar中的文件
$ mkdir extract; tar -x -f txt1.tar -C ./extract; # 从tar提取文件
$ ls ./extract/
	1.txt  2.txt
$ cat ./extract/1.txt
	abc
```

`<OPTION>`定义了以下操作行为：

- `-C/--directory=<DIR>`：切换目录
- `-f/--file=<FILE>`：指定要读取或写入的归档文件
- `-p`/`--preserve-permissions`/`--same-permissions`：保留文件权限
- `-v`/`--verbose`：展示详细信息（处理的文件名）

`<OPTION>`支持对归档结果使用如下压缩方式：

- `--no-auto-compress`：不根据`-f`选项的文件名自动选择压缩方式
- `-j`/`--bzip2`：使用`bzip2`压缩归档结果
- `-J`/`--xz`：使用`xz`压缩归档结果
- `--lzip`：使用`lzip`压缩归档结果
- `--lzma`：使用`lzma`压缩归档结果
- `--lzop`：使用`lzop`压缩归档结果
- `--zstd`：使用`zstd`压缩归档结果
- `-z`/`--gzip`/`--gunzip`/`--ungzip`：使用`gz`压缩归档结果
- `-Z`/`--compress`/`--uncompress`：使用`compress`压缩归档结果

## §2.4 日志

### §2.4.1 `history`

`history`用于命令历史记录。它的执行过程是：先加载`~/.bash_history`的内容到内存中，作为当前Shell会话的命令历史记录，然后将当前Shell的执行命令追加到内存区的末尾，每次调用`history`时都会输出内存区的内容，最后当使用`history -a`或Shell会话退出时，才会将内存区的内容**覆写到`~/.bash_history`**。**这意味着，多个Shell会话退出时，会互相覆盖`~/.bash_history`，使得下一个新建的Shell会话无法访问全部的命令历史记录**。

根据以上原理，如果要删除所有历史记录，我们既可以直接删除`~/.bash_history`，也可以用`history -c; history -a;`先清空内存区的内容，然后用空内容覆写到`~/.bash_history`。

当前Shell会话的命令历史记录上限由`$HISTSIZE`指定，缺省为`1000`。

```shell
$ echo $HISTSIZE
1000
```

`!<LINE>`是表示"`history`输出的第`<LINE>`行内容"的宏。

```shell
$ history
	......
	44 ls
	......
$ !44
ls # 先输出宏替换的结果，再执行命令
	code
```

`!!`是表示"最近一次执行的命令"的宏。优先选择当前Shell会话执行过的命令，如果没有，就选`.bash_history`中的最近一条命令。

```shell
$ ls
	code

$ # 直接按回车，因此判定为未执行任何命令，!!依然能定位到ls

$ !!
ls # 先输出宏替换的结果，再执行命令
	code

$ type !!
type ls # 先输出宏替换的结果，再执行命令
	ls is aliased to `ls --color=auto'
```

## §2.5 用户管理

每个用户会被分配：唯一的正整数用户ID（UID）、小于等于8个字符的用户名、以及对应的密码。UID和登录名的匹配关系记录在`/etc/passwd`中：

```passwd
$ cat /etc/passwd
	# 用户名:密码:UID:GID:备注字段:用户根目录路径:默认Shell路径
	root:x:0:0:root:/root:/bin/bash
	www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
	yaner:x:1000:1000:,,,:/home/yaner:/bin/bash
```

`root`用户的UID恒为`0`。Linux为系统账户保留了`[0, x)`的UID，创建用户账户时会从`[x, +∞)`递增分配UID。这里的`x`取决于发行版具体的规定，例如Ubuntu的`x`设置为`1000`。

`/etc/shadow`记录了用户密码的哈希值或DES密文。

```shadow
# 用户名:密码密文:上次修改密码的时间戳转天数:还剩多少天才能修改密码:还剩多少天就要必须修改密码:密码过期前提前多少天提醒用户:密码过期时多少天后禁用账户:账户被禁用时间戳转天数:预留字段
root:*:19219:0:99999:7:::
yaner:$y$j9T$cS2h4LMHIIDT.bJqjctf40$MV0s0no.EdoP7A8TohNedyygBtMwyiAHsF9A1Y1erJC:20035:0:99999:7:::
```

### §2.5.1 用户

#### §2.5.1.1 `useradd`

`useradd`命令用于添加用户并设置用户根目录。创建用户使用的配置默认从`/etc/default/useradd`加载，可以通过`useradd -D`选项查看：

```shell
$ cat /etc/default/useradd
	SHELL=/bin/sh
	# GROUP=100
	# HOME=/home
	# INACTIVE=-1
	# EXPIRE=
	# SKEL=/etc/skel
	# creating the account
	# CREATE_MAIL_SPOOL=no

$ useradd -D
	GROUP=100 # 新用户添加到GID为100的公共组
	HOME=/home # 新用户的用户根目录为/home/<USERNAME>
	INACTIVE=-1 # 新用户的密码过期后不会被禁用
	EXPIRE= # 新用户的密码不会过期
	SHELL=/bin/sh # 新用户使用sh作为默认Shell
	SKEL=/etc/skel # 新用户的用户根目录内容是/etc/skel的拷贝
	CREATE_MAIL_SPOOL=no # 不创建/home/<USERNAME>/mail接受邮件
```

`/etc/default/useradd`只规定了`useradd`的一部分默认行为，更多的安全设置默认值定义于`/etc/login.defs`中。例如`useradd`默认不会创建用户根目录，要更改这一默认行为，我们可以在`/etc/default/useradd`或`/etc/login.defs`添加一行`CREATE_HOME yes`即可。

`useradd`提供了以下常用选项：

| `useradd`选项          | 作用                               |
| -------------------- | -------------------------------- |
| `-c <COMMENT>`       | 在`/etc/passwd`中添加用户备注            |
| `-d <HOME_DIR>`      | 指定用户根目录，例如`/home/与用户名不同的名称`      |
| `-e <EXPIRE_DATE>`   | 用`YYYY-MM-DD`格式指定账户过期日期          |
| `-f <INACTIVE_DAYS>` | 密码过期多少天后禁用账户，`-1`表示不禁用           |
| `-g <INTIAL_GROUP>`  | 指定用户登录组的GID或组名                   |
| `-G <GROUP>`         | 指定用户附加组                          |
| `-k`                 | 与`-m`一起使用，将`/etc/skel/*`复制到用户根目录 |
| `-m`                 | 创建用户根目录                          |
| `-M`                 | 不创建用户根目录                         |
| `-n`                 | 创建一个与当前用户的用户名相同的用户组              |
| `-r`                 | 创建一个系统账户                         |
| `-p <PASSWORD>`      | 指定新账户密码                          |
| `-s <SHELL>`         | 指定默认Shell                        |
| `-u <UID>`           | 指定UID                            |

`useradd -D -<OPTION> <VALUE>`用于更改某个选项`-<OPTION>`的默认值。例如`useradd -D -s /bin/bash`用于更改`useradd`的默认配置。

#### §2.5.1.2 `userdel`

`userdel <USERNAME>`会删除`/etc/passed`和`/etc/shadow`中的用户信息。额外使用`-r`会删除用户根目录。

#### §2.5.1.3 `usermod`

`usermod`用于修改账户字段，并更改主要组（Primary Group）和辅助组（Secondary Group）的关系。`usermod`的大部分选项与`useradd`一样，除此以外还提供了`-l`用于修改用户名、`-L`用于禁用账户、`-p <PASSWORD>`用于修改密码、`-U`用于恢复账户。

#### §2.5.1.4 `passwd`

`passwd`用于修改**当前帐户**的密码。使用`-e`可以保证该账户下次登录时必须重新设置密码。

#### §2.5.1.5 `chpasswd`

`chpasswd`用于**批量**修改**任意账户**的密码。它会从`STDIN`读入一系列外部以`\n`分隔的、内部用`:`分隔的用户名和新密码的二元组，然后批量修改密码。

```shell
$ chpasswd < new_password.txt
```

#### §2.5.1.6 `chsh`

`chsh -s <SHELL_PATH> <USERNAME>`用于修改账户的默认Shell。这里的`<SHELL_PATH>`必须是绝对路径，不能是文件名。

#### §2.5.1.7 `chfn`

`chfn <USERNAME>`用于修改账户的备注字段。它会执行一个交互式向导，提示用户输入自己的Name、Office、Office Phone、Home Phone字段。这些信息可以通过`finger <USERNAME>`读取账户备注信息后格式化输出。

#### §2.5.1.8 `chage`

`chage <OPTION> <USERNAME>`用于修改账户的有效期。这里的有效期既可以用`YYYY-MM-DD`表示，也可以用一个从1970年1月1日起经过的天数表示。

| `chage`选项 | 作用             |
| --------- | -------------- |
| `-d`      | 设置上次修改密码的时间    |
| `-E`      | 设置密码过期日期       |
| `-I`      | 设置密码过期多少天后锁定账户 |
| `-m`      | 设置密码更改的最小间隔天数  |
| `-M`      | 设置密码的最大有效天数    |
| `-W`      | 设置密码过期前多少天就提醒  |

### §2.5.2 用户组

Linux的用户组信息存储在`/etc/group`中：

```bash
$ cat /etc/group
	# 组名:组密码:GID:属于该组的用户列表
	root:x:0:
	adm:x:4:yaner
	www-data:x:33:
```

#### §2.5.2.1 `groupadd`

`groupadd <GROUPNAME>`用于创建新的用户组：

```shell
# groupadd share
# tail -n 1 /etc/group
	share:x:1001:
```

创建的用户组，默认情况下不包含任何账户。我们可以用`usermod -G <GROUPNAME> <USERNAME>`将用户添加到用户组中，或者用`usermod -g <GROUPNAME> <USERNAME>`更新用户的主要组（Primary Group）。**添加完毕后，账户`<USERNAME>`必须注销后重新登录，用户组所属关系才能更新生效**。

```shell
# usermod -G share yaner
# tail -n 1 /etc/group
	share:x:1001:yaner
# usermod
```

#### §2.5.2.2 `groupmod`

`groupmod`用于修改组信息。

```shell
$ groupmod -n <NEW_GROUPNAME> <GROUPNAME> # 修改组名
$ groupmod -g <NEW_GID> <GID> # 修改GID
```

## §2.6 文件

### §2.6.1 `ls`

`ls <DIR=./>`用于显示某个特定目录下的文件与目录信息。

```shell
$ ls -l
	total 92
	drwxr-xr-x 11 yaner yaner  4096 Nov 19 16:18 .
	drwxr-xr-x  3 root  root   4096 Nov  9 02:08 ..
	-rw-------  1 yaner yaner  3625 Nov 20 00:54 .bash_history
	-rw-r--r--  1 yaner yaner  5551 Nov  9 02:08 .bashrc
```

1. 第一个字段的第一个字符表示对象类型：`-`为文件、`d`为目录、`l`为链接、`c`为字符设备、`b`为块设备、`p`为具名管道、`s`为Socket。
2. 第一个字段的后九个字符分别表示属主、属组、其它用户的读、写、执行权限。
3. 第二个字段表示该对象包含了多少个硬链接。在不考虑人为制造硬链接的情况下，文件的值为`1`，目录的值为当前目录下的所有对象总数加`2`（`.`和`..`）。
4. 第三个字段表示该对象的属主（Owner）名
5. 第四个字段表示该对象的属组名
6. 第五个字段表示该对象的大小，单位为`Byte`
7. 第六个字段表示最后修改时间
8. 第七各字段表示对象名

### §2.6.2 `umask`

当用户新建一个文件或目录时，我们会发现它“出厂自带”权限属性：

```shell
$ mkdir new_folder
$ touch new_file
$ ls -la
	total 96
	-rw-r--r--  1 yaner yaner     0 Nov 20 01:45 new_file
	drwxr-xr-x  2 yaner yaner  4096 Nov 20 01:45 new_folder
```

这种权限默认值由`umask`命令指定，`umask`控制着`rwxrwxrwx`这九项权限的全局禁用开关。具体来说，`umask`的**后三位八进制数码**表示权限属性掩码，真正的默认权限属性由八进制数（文件为`666`，目录为`777`）**减去这三位八进制数码**（默认为`022`）得到。执行`umask`会输出当前的默认权限属性的掩码，这个值由`/etc/profile`指定或由`/etc/skel/.bashrc`初始化：

```shell
$ grep -rn "umask" /etc
	/etc/post-install/05-home-dir.post:9:  umask 022
	/etc/skel/.bashrc:112:# Set a more restrictive umask: i.e. no exec perms for others:
	/etc/skel/.bashrc:113:# umask 027
	/etc/skel/.bashrc:115:# umask 077
```

我们可以使用`umask <OCT_NUMBER>`更改`umask`的掩码，它会影响所有文件的权限：

```shell
$ touch new_file
$ ls -l
	total 0
	-rw-r--r-- 1 Yaner None 0 Nov 20 21:26 new_file
$ umask 066
$ ls -l
	total 0
	-rw------- 1 Yaner None 0 Nov 20 21:26 new_file
```

### §2.6.3 `chmod`

`chmod <OPTION>* <MODE> <FILE>`命令用户更改`<FILE>`的权限。

这里的`<MODE>`支持两种形式：八进制形式和符号形式。

- 八进制形式（`[0-7]{3,4}`）：SUID/SGID/粘滞位是否启用的前一位八进制数字（可选）、`rwxrwxrwx`的后三位八进制数字（必选）。
- 符号模式（`[ugoa]+[+-=][rwxXstugo]+`）：
	1. 第一组字符表示`chmod`修改权限的作用对象，其中`u`表示用户、`g`表示用户组、`o`表示其他用户、`a`表示上述三者皆有。
	2. 第二组字符表示权限的具体更改行为，其中`+`表示增加权限、`-`表示移除权限，`=`表示设置权限。
	3. 第三组字符表示具体的权限种类，其中`rwx`分别表示读取写入执行、`X`表示当对象是目录或已有执行权限的文件时才允许更改执行权限、`s`表示同时设置SUID和SGID、`t`表示设置粘滞位（Sticky Bit）、`ugo`分表表示设置属主/用户组/其他用户的权限。

`chmod`提供了`-R`选项用于递归地更改权限。

上文中提到了SUID、SGID和粘滞位。这三个额外的属性是为了解决文件共享的问题而发明的。一种显然的想法是：我们可以为需要共享的文件、需要分享给的对象，创立一个额外的用户组。然而这种方案不易维护，设想文件数量多、用户规模大、文件和用户都在频繁地新建和删除时，这种方案产生了大量的人工维护成本。为了解决这一问题，Linux使用了SUID、SGID和粘滞位这三个**布尔属性**：

- SUID（Set UID）：任意用户执行文件时，该文件以文件属主的权限启动。例如任何用户都能使用`passwd`
  ```shell
  $ ls -l /bin/passwd # 注意下面的s，表示SUID已启用
	  -rwsr-xr-x 1 root root 68208 May 28  2020 /bin/passwd
```
- SGID（Set GID）：任意用户执行文件时，该文件以文件属组的权限启动；对于目录来说，其子树下的所有文件都会继承目录的SGID。
  ```shell
  $ touch /share/1.txt
  $ ls -l /share/ # 未启用SGID
	  -rw-r--r-- 1 root root   0 Nov 20 15:22 1.txt
  
  $ chmod 2774 /share # 启用SGID
  $ ls -ld /share # 注意下面的S，表示启用了SGID
	  drwxr-Sr-- 2 root root 4096 Nov 20 16:13 /share
  $ touch /share/2.txt
  $ ls -l /share
	  -rw-r--r-- 1 root root   0 Nov 20 15:22 1.txt
	  -rw-r--r-- 1 root shared 0 Nov 20 15:23 2.txt
```
- 粘滞位（Sticky Bit）：作用于目录时，只有目录属主和Root用户有权重命名或删除该目录中的文件。这正是Linux推荐的文件共享方案：创建共享目录`/share`，将其属组改为`root`，启用粘滞位`chmod 1777 /share`即可，以此来实现不同用户的分离。`/tmp`采用的就是这种方案。
  ```shell
  root$ mkdir /share
  root$ chmod 1777 /share
  root$ ls -ld /share # 注意下面的t，表示启用了粘滞位
	  drwxrwxrwt 2 root root 4096 Nov 20 16:13 /share
  root$ touch /share/root_file
  root$ su yaner
  yaner$ rm /share/root_file
	  rm: cannot remove '/share/root_file': Operation not permitted
```

### §2.6.5 `chown`

`chown <OPTION>* [<NEW_OWNER>][.<NEW_GROUP>] <FILE>`用于更改文件的属主和属组。该命令可以单独修改属主`<NEW_OWNER>`、单独修改属组`.<NEW_GROUP>`、同时修改属主和属组`<NEW_OWNER>.<NEW_GROUP>`。

```shell
$ ls -l
	total 0
	-rw-r--r-- 1 root root 0 Nov 20 14:53 new_file
$ chown yaner.yaner new_file
$ ls -l
	total 0
	-rw-r--r-- 1 yaner yaner 0 Nov 20 14:53 new_file
```

如果`<NEW_OWNER>`就是当前Shell登录的用户，则`.<NEW_GROUP>`缺省为用户所在的用户组，只需要使用`<NEW_OWNER>.`即可。

### §2.6.5 `chgrp`

`chgrp <NEW_GROUP> <FILE>`用于更改文件的属组。

### §2.6.6 `setfacl`/`getfacl`

Linux支持一种更细粒度的文件权限管理——访问控制列表（Access Control List, ACL）。`getfacl`用于查看ACL属性，`setfacl`用于设置ACL属性。

`getfacl <FILE>`用于获取文件`<FILE>`的所有ACL属性，分别是文件名、属主、属组、属主权限、属组权限、其他用户权限、ACL权限。

`setfacl -m <RULE> <FILE>`用于给**文件**`<FILE>`添加一条ACL属性`<RULE>`。其中`<RULE>`的定义为：`u(ser)?:<UID_OR_USERNAME>:<PERMS>`或`g(roup)?:<GID_OR_GROUPNAME>:<PERMS>`或`o(ther)?::<PERMS>`。这里的`<PERMS>`定义为`r?w?x?`。

`setfacl -x <RULE> <FILE>`用于删除**文件**`<FILE>`的，某条ACL属性`<RULE>`。这里的`<RULE>`格式略有不同，它不能包含第三个字段，但是可选第二个与第三个字段之间的`:`。

`setfacl -d <OPTION> d:<RULE> <DIR>`用于为**目录**`<DIR>`添加或删除ACL权限。需要注意的是`<RULE>`前面必须带有`d:`。目录的ACL权限会继承到其目录树下的所有文件。

```shell
$ touch new_file
$ getfacl new_file
	# file: new_file
	# owner: root
	# group: root
	user::rw-
	group::r--
	other::r--
$ setfacl -m group:shared:rw new_file
$ getfacl new_file
	# file: new_file
	# owner: root
	# group: root
	user::rw-
	group::r--
	group:shared:rw-
	mask::rw-
	other::r--
$ setfacl -x group:shared new_file
$ getfacl new_file
	# file: new_file
	# owner: root
	# group: root
	user::rw-
	group::r--
	mask::r--
	other::r--
```

## §2.7 文件系统

Linux支持的常见文件系统有：

| 文件系统    | 类型      | 原理                                                                                                                                     | 缺点                                       |
| ------- | ------- | -------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------- |
| `EXT`   |         | Linux最初引入的文件系统。它使用固定大小的磁盘块保存数据，使用`inode`跟踪文件信息，在每个物理存储设备中均维护一张`inode`表。每个`inode`节点对应一个文件，包含唯一的`inode`号、文件名、文件大小、属主、属组、访问权限、指向每个数据块的指针。 | 单文件大小小于等于`2GB`                           |
| `EXT2`  |         | 在`EXT`的基础上，在`inode`表中记录文件的创建/修改/最后访问时间、单文件大小扩充至`32TB`、保存文件时按组分配磁盘块。                                                                    | 存储文件和更新`inode`表时，禁止断电，否则导致两者失去同步，容易损坏文件  |
| `EXT3`  | 日志文件系统  | 默认使用有序模式的日志文件系统。单文件大小最大为`2TB`，单分区大小最大为`32TB`。                                                                                          | 不支持恢复误删的文件，不支持压缩                         |
| `EXT4`  | 日志文件系统  | 默认使用有序模式的日志文件系统。单文件大小最大为`16TB`，单分区大小最大为`1EB`。支持加密和压缩，允许目录下任意多数量的文件。**兼容`EXT2`和`EXT3`，可以作为`EXT4`进行挂载，从而提高性能**。                          |                                          |
| `JFS`   | 日志文件系统  | 使用有序模式的日志文件系统。                                                                                                                         |                                          |
| `XFS`   | 日志文件系统  | 使用回写模式的日志文件系统。                                                                                                                         |                                          |
| `ZFS`   | 卷管理文件系统 | 支持完整性校验与自动修复。单文件最大为`16EB`，单分区最大为`256e15ZB`                                                                                             | 内存占用高，最低为`768MB`。闭源，无法进入Linux内核主分支，需额外安装 |
| `Btrfs` | 卷管理文件系统 | 稳定性强、易用性高、支持动态调整卷大小。                                                                                                                   |                                          |

日志文件系统是一种保护措施——它不会直接将数据写入存储设备后更新`inode`表，而是先将文件写入临时文件（日志），在保证存储文件和`inode`表同步更新完毕后，才会删除日志。Linux提供了以下三种日志文件系统的实现方法：

| 日志文件系统实现方法  | 含义                          | 特点         |
| ----------- | --------------------------- | ---------- |
| 数据模式        | 日志同时记录`inode`和文件数据          | 安全性高，性能差   |
| 有序模式        | 日志只记录`inode`，直到文件写入成功后才删除日志 | 安全性和性能取得折中 |
| 回血模式        | 日志只记录`inode`，不控制文件合适写入      | 安全性差       |
| （不采用日志文件系统） |                             | 安全性最差      |

卷管理文件系统是一种针对大量存储设备的管理方案——一个或多个磁盘可以共同创建一个存储池，然后从存储池划分出若干个虚拟磁盘（即为卷），这样可以更灵活地按需增加或删除卷，提供更强的灵活性。受益于该功能，众多卷管理文件系统也支持COW（写时复制）和快照等高级特性。

### §2.7.1 管理分区

Linux使用以下规则，来为硬盘分配设备名称：

- SATA驱动器或SCSI驱动器：命名为`/dev/sd[a-z]`，从`/dev/sda`开始按字典序自增。
- NVME驱动器：命名为`/dev/nvme[0-9]n[1-9]`。其中第一个`[0-9]`取决于Linux检测驱动器的检测顺序，第二个`[1-9]`表示分配给该驱动器的编号。
- IDE驱动器：命名为`/dev/hd[a-z]`，从`/dev/hda`开始按字典序自增。

#### §2.7.1.1 `fdisk`

`fdisk`用于管理使用MBR（Master Boot Record）分区表的磁盘。MBR最多只能利用单盘`2TB`空间，且最多支持四个主分区，或者三个主分区加一个扩展分区。

`fdisk -l`查看所有存储设备的信息：

```shell
$ sudo fdisk -l
	Disk /dev/sdb: 40 GiB, 42949672960 bytes, 83886080 sectors
	Disk model: QEMU HARDDISK
	Units: sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
```

`fdisk <DEVICE>`会进入设备的编辑命令行。该命令行提供了以下命令：

| `fdisk`命令   | 作用                |
| ----------- | ----------------- |
| `a`（Active） | 设置活动分区标志          |
| `b`         | 编辑BSD Unix使用的标签   |
| `c`         | 设置DOS兼容标志         |
| `d`（Delete） | 删除分区              |
| `g`         | 初始化空的GPT分区表       |
| `G`         | 初始化空的IRIX（SGI）分区表 |
| `l`（List）   | 显示可用的分区类型         |
| `m`（Menu）   | 显示命令菜单            |
| `n`（New）    | 添加新分区             |
| `o`         | 初始化空的DOS分区表       |
| `p`（Print）  | 显示当前分区表           |
| `q`（Quit）   | 仅退出，不保存更改         |
| `s`         | 为Sun Unix创建新标签    |
| `t`（Tag）    | 修改分区的系统ID         |
| `u`（Unit）   | 修改显示单元            |
| `v`（Verify） | 验证分区表             |
| `w`（Write）  | 退出，保存更改           |
| `x`         | 高级功能              |

下面的流程演示了如何创建两个主分区。

```shell
root@ECS1033:~# fdisk /dev/sdb
	Welcome to fdisk (util-linux 2.34).
	Changes will remain in memory only, until you decide to write them.
	Be careful before using the write command.

	The old ext4 signature will be removed by a write command.

	Device does not contain a recognized partition table.
	Created a new DOS disklabel with disk identifier 0x823f5311.

	Command (m for help): p
		Disk /dev/sdb: 40 GiB, 42949672960 bytes, 83886080 sectors
		Disk model: QEMU HARDDISK
		Units: sectors of 1 * 512 = 512 bytes
		Sector size (logical/physical): 512 bytes / 512 bytes
		I/O size (minimum/optimal): 512 bytes / 512 bytes
		Disklabel type: dos
		Disk identifier: 0x823f5311

	Command (m for help): a
		No partition is defined yet!

	Command (m for help): n
		Partition type
		   p   primary (0 primary, 0 extended, 4 free)
		   e   extended (container for logical partitions)
		Select (default p): p
		Partition number (1-4, default 1): 2
		First sector (2048-83886079, default 2048): 2048
		Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-83886079, default 83886079): 83886079
		Created a new partition 2 of type 'Linux' and of size 40 GiB.

	Command (m for help): p
		Disk /dev/sdb: 40 GiB, 42949672960 bytes, 83886080 sectors
		Disk model: QEMU HARDDISK
		Units: sectors of 1 * 512 = 512 bytes
		Sector size (logical/physical): 512 bytes / 512 bytes
		I/O size (minimum/optimal): 512 bytes / 512 bytes
		Disklabel type: dos
		Disk identifier: 0x823f5311
		
		Device     Boot Start      End  Sectors Size Id Type
		/dev/sdb2        2048 83886079 83884032  40G 83 Linux

	Command (m for help): w
		The partition table has been altered.
		Syncing disks.
```

#### §2.7.1.2 `gdisk`

`gdisk`用于管理使用GPT（GUID Partition Table）分区表的磁盘分区。

| `gdisk`命令     | 作用           |
| ------------- | ------------ |
| `b`（Backup）   | 将GPT分区表备份到文件 |
| `c`（Change）   | 修改分区名称       |
| `d`（Delete）   | 删除分区         |
| `i`（Info）     | 显示分区信息       |
| `l`（List）     | 显示可用的分区类型    |
| `n`（New）      | 添加分区         |
| `o`           | 初始化GPT分区表    |
| `p`（Print）    | 显示当前GPT分区表   |
| `q`（Quit）     | 仅退出，不保存更改    |
| `r`（Recovery） | 恢复和转换        |
| `s`（Sort）     | 排序分区         |
| `t`（Tag）      | 修改分区的类型      |
| `v`（Verify）   | 验证磁盘         |
| `w`（Write）    | 退出，保存更改      |
| `x`           | 附加选项         |
| `?`           | 显示帮助         |

#### §2.7.1.3 `parted`

`parted`是GNU发布的一款全能管理分区工具，且其命令行中的命令不再是单字母，而是更容易阅读的单词。它的优势在于：可以调整现有分区的大小。

```shell
$ parted /dev/sdb
GNU Parted 3.3
	Using /dev/sdb
	Welcome to GNU Parted! Type 'help' to view a list of commands.
	(parted) mklabel gpt
		Warning: Partition(s) on /dev/sdb are being used.
		Ignore/Cancel? I
		Warning: The existing disk label on /dev/sdb will be destroyed and all data on this disk will be lost. Do you want to
continue?
		Yes/No? Y
	(parted) mkpart volume1
		File system type?  [ext2]? ext4
		Start? 1
		End? 33%
	(parted) mkpart volume2
		File system type?  [ext2]? btrfs
		Start? 33%
		End? 66%
	(parted) mkpart volume3
		File system type?  [ext2]? zfs
		Start? 66%
		End? 99%
	(parted) print
		Model: QEMU QEMU HARDDISK (scsi)
		Disk /dev/sdb: 42.9GB
		Sector size (logical/physical): 512B/512B
		Partition Table: gpt
		Disk Flags:
		Number  Start   End     Size    File system  Name     Flags
		 1      1049kB  14.2GB  14.2GB  ext4         volume1
		 2      14.2GB  28.3GB  14.2GB  btrfs        volume2
		 3      28.3GB  42.5GB  14.2GB  zfs          volume3
	(parted) rm
		Partition number? 3
	(parted) print
		Model: QEMU QEMU HARDDISK (scsi)
		Disk /dev/sdb: 42.9GB
		Sector size (logical/physical): 512B/512B
		Partition Table: gpt
		Disk Flags:
		Number  Start   End     Size    File system  Name     Flags
		 1      1049kB  14.2GB  14.2GB  ext4         volume1
		 2      14.2GB  28.3GB  14.2GB  btrfs        volume2
	(parted) quit
		Information: You may need to update /etc/fstab.
$ lsblk
	NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
	sdb      8:16   0   40G  0 disk /opt/1
	├─sdb1   8:17   0 13.2G  0 part
	└─sdb2   8:18   0 13.2G  0 part
```

### §2.7.2 管理文件系统

每种文件系统都有各自的格式化工具。

| 程序名          | 作用            |
| ------------ | ------------- |
| `mkefs`      | 创建`ext`文件系统   |
| `mke2fs`     | 创建`ext2`文件系统  |
| `mkfs.ext3`  | 创建`ext3`文件系统  |
| `mkfs.ext4`  | 创建`ext4`文件系统  |
| `jfs_mkfs`   | 创建`jfs`文件系统   |
| `mkfs.xfs`   | 创建`xfs`文件系统   |
| `mkfs.zfs`   | 创建`zfs`文件系统   |
| `mkfs.btrfs` | 创建`btrfs`文件系统 |

只需以`root`权限，执行`<程序名> <PARITION_PATH>`即可在指定分区上创建文件系统。

我们可以通过编辑`/etc/fstab`，实现开机自动挂载。

### §2.7.3 维护文件系统

#### §2.7.3.1 `fsck`

`fsck <OPTION> <FILESYSTEM>`用于检查和修复文件系统，文件系统类型优先由`/etc/fstab`指定，否则由命令行参数`-t <FILESYSTEM>`手动指定，这里的`<FILESYSTEM>`既可以是文件系统类型的字符串，也可以是挂载点。

| `fsck`命令          | 作用                        |
| ----------------- | ------------------------- |
| `-a`（Auto）        | 检测到错误时自动修复                |
| `-A`（All）         | 只检测`/etc/fstab`中列出的所有文件系统 |
| `-N`              | 只显示要检查的内容，不进行实际检查         |
| `-r`              | 出现错误时及时提示                 |
| `-R`              | 使用`-A`时跳过根文件系统            |
| `-t <FILESYSTEM>` | 指定文件系统类型                  |
| `-V`（Verbose）     | 输出详细信息                    |
| `-y`（Yes）         | 检测到错误时自动修复                |

`fsck`要求检查的分区必须未被挂载。对于根目录来说，我们只能进入Linux Live CD环境才能将其卸载，使用`fsck`进行操作。

### §2.7.4 管理逻辑卷

Linux提供了逻辑卷管理器（LVM，Logical Volume Manager），可以将另一块硬盘上的分区加入已有的文件系统，从而动态地增加存储空间，无需重建整个文件系统。

LVM将一个或多个分区组合成一个逻辑卷，作为单个分区进行格式化。LVM由三个部分构成：

- 物理卷（PV，Physical Volume）：本质上是一个分区，通过`pvcreate`命令创建，记录了LVM结构、卷标、元数据。
- 卷组（VG，Volume Group）：本质上是一个PV集合，也就是一个存储池，通过`vgcreate`命令创建。一个PV最多只能属于一个VG。
- 逻辑卷（LV，Logical Volume）：本质上是一个VG中的若干存储空间快（PE，Physical Extents）集合，通过`lvcreate`命令创建。一个LV不能跨VG创建。

使用`pvcreate <VOLUME>+`创建PV：

```shell
$ umount /dev/sdb ; umount /dev/sdb1 ; umount /dev/sdb2 ; umount /dev/sdb3 ; # 保证物理卷全部未挂载
$ lsblk
	NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
	sdb      8:16   0   40G  0 disk
	├─sdb1   8:17   0 13.2G  0 part
	├─sdb2   8:18   0 13.2G  0 part
	└─sdb3   8:19   0 13.2G  0 part
$ pvcreate /dev/sdb1 /dev/sdb2 /dev/sdb3
	  Physical volume "/dev/sdb1" successfully created.
	  Physical volume "/dev/sdb2" successfully created.
	  Physical volume "/dev/sdb3" successfully created.
```

使用`vgcreate <VG_NAME> <VOLUME>+`创建VG，使用`vgdisplay`查看已创建的VG：

```shell
$ vgdisplay # 显示当前的VG，防止创建VG时重名
$ vgcreate vg0 /dev/sdb1 /dev/sdb2
	  Volume group "vg0" successfully created
$ vgdisplay
	  --- Volume group ---
	  VG Name               vg0
	  System ID
	  Format                lvm2
	  Metadata Areas        2
	  Metadata Sequence No  1
	  VG Access             read/write
	  VG Status             resizable
	  MAX LV                0
	  Cur LV                0
	  Open LV               0
	  Max PV                0
	  Cur PV                2
	  Act PV                2
	  VG Size               26.39 GiB
	  PE Size               4.00 MiB
	  Total PE              6757
	  Alloc PE / Size       0 / 0
	  Free  PE / Size       6757 / 26.39 GiB
	  VG UUID               oQN7jf-ccyP-wXgU-TjFC-zA35-tw3Z-zNifXo
```

使用`vgcreate <VG_NAME> <VOLUME>+`向VG添加PV，使用`vgreduce <VG_NAME> <VOLUME>`从VG删除PV：

```shell
$ vgextend vg0 /dev/sdb3
	  Volume group "vg0" successfully extended
$ vgdisplay
	  --- Volume group ---
	  VG Name               vg0
	  System ID
	  Format                lvm2
	  Metadata Areas        3
	  Metadata Sequence No  2
	  VG Access             read/write
	  VG Status             resizable
	  MAX LV                0
	  Cur LV                0
	  Open LV               0
	  Max PV                0
	  Cur PV                3
	  Act PV                3
	  VG Size               <39.59 GiB
	  PE Size               4.00 MiB
	  Total PE              10135
	  Alloc PE / Size       0 / 0
	  Free  PE / Size       10135 / <39.59 GiB
	  VG UUID               oQN7jf-ccyP-wXgU-TjFC-zA35-tw3Z-zNifXo

$ vgreduce vg0 /dev/sdb3
  Removed "/dev/sdb3" from volume group "vg0"
root@ECS1033:~# vgdisplay
	  --- Volume group ---
	  VG Name               vg0
	  System ID
	  Format                lvm2
	  Metadata Areas        2
	  Metadata Sequence No  3
	  VG Access             read/write
	  VG Status             resizable
	  MAX LV                0
	  Cur LV                0
	  Open LV               0
	  Max PV                0
	  Cur PV                2
	  Act PV                2
	  VG Size               26.39 GiB
	  PE Size               4.00 MiB
	  Total PE              6757
	  Alloc PE / Size       0 / 0
	  Free  PE / Size       6757 / 26.39 GiB
	  VG UUID               oQN7jf-ccyP-wXgU-TjFC-zA35-tw3Z-zNifXo
```

使用`lvcreate -L <SIZE> -v <VG_NAME>`，从存储池VG`<VG_NAME>`中创建一个大小为`<SIZE>`的LV。这个LV会显示在`/dev/<VG_NAME>/lvol[0-9]`，按数字序升序自增。

```shell
$ lvcreate -L 25G -v vg0
	  Archiving volume group "vg0" metadata (seqno 3).
	  Creating logical volume lvol0
	  Creating volume group backup "/etc/lvm/backup/vg0" (seqno 4).
	  Activating logical volume vg0/lvol0.
	  activation/volume_list configuration setting not defined: Checking only host tags for vg0/lvol0.
	  Creating vg0-lvol0
	  Loading table for vg0-lvol0 (253:0).
	  Resuming vg0-lvol0 (253:0).
	  Wiping known signatures on logical volume "vg0/lvol0"
	  Initializing 4.00 KiB of logical volume "vg0/lvol0" with value 0.
	  Logical volume "lvol0" created.
```

使用`lvdisplay`、`lvs`或`lvscan`查看创建的LV：

```shell
$ lvdisplay
	  --- Logical volume ---
	  LV Path                /dev/vg0/lvol0
	  LV Name                lvol0
	  VG Name                vg0
	  LV UUID                tSDnsI-t1kR-prlS-odnw-Yc4P-w5rB-gIR7gX
	  LV Write Access        read/write
	  LV Creation host, time ECS1033, 2024-11-21 15:51:54 +0000
	  LV Status              available
	  # open                 0
	  LV Size                25.00 GiB
	  Current LE             6400
	  Segments               2
	  Allocation             inherit
	  Read ahead sectors     auto
	  - currently set to     256
	  Block device           253:0
$ lvs
	  LV    VG  Attr       LSize  Pool Origin Data%  Meta%  Move Log Cpy%Sync Convert
	  lvol0 vg0 -wi-a----- 25.00g
$ lvs
	lvs     lvscan
$ lvscan
	  ACTIVE            '/dev/vg0/lvol0' [25.00 GiB] inherit
```

现在的LV是一个虚拟卷，可以正常地被格式化为某种文件系统：

```shell
$ mkfs.ext4 /dev/vg0/lvol0
	mke2fs 1.45.5 (07-Jan-2020)
	Discarding device blocks: done
	Creating filesystem with 6553600 4k blocks and 1638400 inodes
	Filesystem UUID: eb0d54b5-88e2-47bd-9ecc-65b981b90336
	Superblock backups stored on blocks:
	        32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632, 2654208,
	        4096000
	Allocating group tables: done
	Writing inode tables: done
	Creating journal (32768 blocks): done
	Writing superblocks and filesystem accounting information: done
$ mkdir /lvm_test
$ mount -t ext4 /dev/vg0/lvol0 /lvm_test
```

可以使用`lvextend`和`lvreduce`命令，动态调整LV的大小。

```shell
$ lvextend -L +1G /dev/vg0/lvol0
	  Size of logical volume vg0/lvol0 changed from 2.00 GiB (512 extents) to 3.00 GiB (768 extents).
	  Logical volume vg0/lvol0 successfully resized.
$ lvreduce -L -1G /dev/vg0/lvol0
	  WARNING: Reducing active and open logical volume to 2.00 GiB.
	  THIS MAY DESTROY YOUR DATA (filesystem etc.)
	  Do you really want to reduce vg0/lvol0? [y/n]: y
	  Size of logical volume vg0/lvol0 changed from 3.00 GiB (768 extents) to 2.00 GiB (512 extents).
	  Logical volume vg0/lvol0 successfully resized.
```

除此之外，还有`pvremove`、`vgremove`、`lvremove`等命令，本节略。

## §2.8 包管理器

### §2.8.1 `apt`

Debian系的LInux发行版（Debian、Ubuntu等）使用APT工具集作为包管理工具。APT工具集包括`apt-cache`、`apt-get`和`apt`。其中`apt`本质上是`apt-cache`和`apt-get`的CLI前端。

`dpkg -L <PACKAGE>`用于获取`apt`源安装`<PACKAGE>`时，涉及变更的所有目录与文件。`dpkg --search <FILE>`用于获取由路径指定的`<FILE>`属于哪个软件包。

```shell
$ dpkg -L acl
	/.
	/bin
	/bin/chacl
	/bin/getfacl
	/bin/setfacl
	/usr
	/usr/share
	/usr/share/doc
	/usr/share/doc/acl
	/usr/share/doc/acl/copyright
	/usr/share/man
	/usr/share/man/man1
	/usr/share/man/man1/chacl.1.gz
	/usr/share/man/man1/getfacl.1.gz
	/usr/share/man/man1/setfacl.1.gz
	/usr/share/man/man5
	/usr/share/man/man5/acl.5.gz
	/usr/share/doc/acl/changelog.Debian.gz
$ dpkg --search getfacl
	acl: /usr/share/man/man1/getfacl.1.gz
	acl: /bin/getfacl
```

使用`apt list`查看仓库中所有可安装的包；使用`apt list --installed`查看所有已安装的包：

```shell
$ apt list --installed
	Listing... Done
	accountsservice/now 0.6.55-0ubuntu12~20.04.1 amd64 [installed,upgradable to: 0.6.55-0ubuntu12~20.04.7]
	acl/focal,now 2.2.53-6 amd64 [installed]
	adduser/focal,now 3.118ubuntu2 all [installed,automatic]
	......
```

使用`apt upgrade`**在不删除任何旧版本包的情况下**，更新所有已安装包的版本；使用`apt full-upgrade`使用激进策略，不惜一切代价更新所有已安装包的版本。

使用`apt remove <PACKAGE>`删除软件包，但是**保留数据和配置文件**；使用`apt purge <PACKAGE>`彻底删除软件包本体，及其数据和配置文件，**但是不会删除其依赖的软件包**；使用`apt autoremove`删除所有未被引用的软件包。

`apt`使用的软件仓库定义在`/etc/apt/sources.list`，其语法结构为`[deb|deb-src] <ADDRESS> <DISTRIBUTION_NAME> <PACKAGE_TYPE_LIST>`。其中各参数的含义为：

- `deb`表示二进制源，`deb-src`表示源代码源。
- `<ADDRESS>`表示软件仓库的网址。
- `<DISTRIBUTION_NAME>`表示发行版的版本名称
- `<PACKAGE_TYPE_LIST>`是一组单词的集合，例如`main`、`restricted`、`universe`、`partner`等。

# §3 Shell脚本语法

## §3.1 子Shell

### §3.1.1 命令列表与进程列表

命令列表使用`;`将一个或多个命令合并成一行（可以使用`{}`包起来，**且`{}`内部必须用空格分隔**），**在本Shell中运行**。进程列表使用`()`将命令列表包起来，**在子Shell中运行**。为了验证这一点，我们可以使用`bash`提供的环境变量`$BASH_SUBSHELL`来验证，它反映了Shell的嵌套深度，根Shell的`$BASH_SUBSHELL`为`0`。｛

```shell
$ { echo $BASH_SUBSHELL; { echo $BASH_SUBSHELL; { echo $BASH_SUBSHELL; } } } # 命令列表
0
0
0

# 
$ echo $BASH_SUBSHELL; (echo $BASH_SUBSHELL; (echo $BASH_SUBSHELL;)) # 进程列表
	0
	1
	2
```

### §3.1.2 后台模式

在命令列表或进程列表的后面加一个`&`，就可以创建一个作业。此时`bash`会先输出当前创建的后台作业号与`PID`，然后显示所有已执行完毕、**且未曾在此显示过**的后台作业，最后恢复可交互的状态。**后台作业号从`1`开始自增**。

```c++
$ sleep 5& # 第0秒执行
[1] 1241

$ sleep 5& # 第1秒执行
[2] 1242

$ sleep 5& # 第10秒执行
[3] 1243
[1]   Done                    sleep 5
[2]   Done                    sleep 5
```

后台作业和接下来的交互式执行命令均在当前Shell中运行，而不会在子Shell中。这一点可以用`ps`证明——它们的`PPID`均为当前Shell的`PID`：

```shell
$ sleep 100&
$ ps -f
     UID     PID    PPID  TTY        STIME COMMAND
   Yaner    1267    1248 pty1     01:29:54 /usr/bin/ps
   Yaner    1266    1248 pty1     01:29:51 /usr/bin/sleep
   Yaner    1248    1247 pty1     01:29:44 /usr/bin/bash
```

`bash`提供了`jobs`关键字，用于查看当前Shell的后台作业情况。具体来说，它会显示当前正在运行（`Running`）的后台作业，以及所有已执行完毕（`Done`）、**且未曾在此显示过**的后台作业。我们还可以使用`-l`显示后台作业的`PID`。其中`+`表示最近启动的后台作业，`-`表示第二最近启动的后台作业。

```shell
$ sleep 100&
	[1] 1243
$ jobs
	[1]+  Running                 sleep 100 &
$ sleep 1&
	[2] 1244
$ jobs
	[1]-  Running                 sleep 100 &
	[2]+  Done                    sleep 1
$ jobs # [2]完成后只会显示一次
	[1]+  Done                    sleep 100
$ jobs # [1]完成后只会显示一次
```

下面我们介绍进程列表与后台模式混用的情况。以下面的命令为例——首先父Shell创建了后台作业，于是将作业信息输出到父Shell的`STDOUT`。然后子Shell执行后台作业，遇到`echo "abc"`时直接将子Shell的`STDOUT`重定向到父Shell的`STDOUT`后清空缓存区，导致父Shell直接错位显示`abc\n`。后台作业执行完毕时，父Shell负责输出执行完毕的信息到父Shell的`STDOUT`，但没有及时清空缓存区，于是必须向父Shell的`STDIN`输入回车键，才能先后触发`bash`执行命令与输出作业调度完成信息。

```shell
$ (sleep 1; echo "abc"; sleep 1;)&
[1] 1257

$ abc
↵
[1]+  Done                    ( sleep 1; echo $BASH_SUBSHELL; sleep 1 )
```

### §3.1.3 协程

协程（`coproc [<JOB_NAME>=COPROC] <COMMAND>`）本质上就是进程列表和后台模式混用的一种简便表示方式。协程先创建一个子Shell，然后在子Shell中执行`<COMMAND>`。**两者的区别是：`coproc`不会将子Shell的`STDOUT`重定向到父Shell的`STDOUT`**、`coproc`可以自定义后台作业的名称（缺省为`COPROC`）。

```shell
$ coproc { sleep 1; echo "abc"; sleep 60; }
[1] 1319

$ coproc job1 { sleep 1; echo "abc"; sleep 60; }
[2] 1325

$ jobs
[1]-  Running                 coproc COPROC { sleep 1; echo "abc"; sleep 60; } &
[2]+  Running                 coproc job1 { sleep 1; echo "abc"; sleep 60; } &
```

## §3.2 命令

### §3.2.1 外部命令和内建命令

外部命令（即文件系统命令）是独立于`bash`之外存在的程序文件，执行时会产生子进程。内建命令在编译时就被定义在Shell中的，并不对应着任何真实存在的文件，无需使用子进程执行。**因此，内建命令的效率通常比外部命令要高**。

`which <COMMAND>`命令用于搜索当前环境变量中外部命令`<COMMAND>`对应的文件位置。

```shell
$ which ls # ls是外部命令，which能输出ls文件所在的路径
	/usr/bin/ls
$ which cd # cd是内建命令，所以which找不到对应的程序文件，输出空串
	
```

`type <COMMAND>`命令用于输出命令`<COMMAND>`的类型，即外部命令、内建命令或别名。有些命令有多种实现方式，可以使用`-a`选项展示全部实现：

```shell
$ type pwd
	pwd is a shell builtin
$ type pwd
	pwd is a shell builtin
	pwd is /usr/bin/pwd
	pwd is /bin/pwd
$ type ls
	ls is aliased to `ls --color=auto'
$ type gcc
	gcc is /usr/bin/gcc
```

### §3.2.2 命令别名

`alias <ALIAS>='<COMMAND>'`用于在当前Shell会话（**不包括子Shell**）中创建别名，`unalias <ALIAS>`用于删除别名：

```shell
$ alias abc='whoami'
$ abc
	yaner
$ unalias abc
$ abc
	-bash: abc: command not found
```

`alias -p`用于查看当前Shell会话（**不包括子Shell**）中的所有别名：

```shell
$ alias -p
	alias l='ls -CF'
	alias la='ls -A'
	alias ll='ls -l'
	alias ls='ls --color=auto'
```

### §3.2.3 命令替换

Shell脚本可以将某条命令的`STDOUT`输出信息作为某个变量的变量值，称为命令替换。**这里的命令会在子Shell中执行，因此无法调用脚本中定义的局部变量**。有两种命令替换的方式：用反引号包裹`<COMMAND>`、用`$()`包裹。

```shell
$ list=`ls`
$ echo ${list[*]}
	new_file new_folder

$ list=$(ls)
$ echo ${list[*]}
	new_file new_folder
```

## §3.3 变量

环境变量本质上是加载到内存中的键值对。环境变量有两种——全局变量和局部变量。全局变量会加载到任何Shell会话中，而局部变量只作用于当前Shell会话（不包括子Shell）中。在Shell中，我们使用`$<KEY>`引用环境变量`<KEY>`的值。

Linux提供了`env`、`printenv`、`set`命令来查看环境变量。它们的语法略有区别——不带参数执行时，它们都能输出全部环境变量，其中只有`set`保证变量名升序输出，还会额外显示局部Shell函数；`env [<KEY>=<VALUE>]* <COMMAND>`用于临时设置环境变量后执行`<COMMAND>`；`printenv <KEY>+`用于逐行输出指定的一个或多个环境变量的值。

```shell
$ type env
	env is /usr/bin/env
$ type printenv
	printenv is /usr/bin/printenv

$ printenv HOSTTYPE SHELL
	x86_64
	/bin/bash
$ env HOSTTYPE="Unknown" printenv HOSTTYPE
	Unknown
```

`<KEY>=<VALUE>`用于设置局部变量，要注意`<KEY>`、`=`、`<VALUE>`三者之间不能有任何空格：

```shell
$ ABC="abc"
$ echo $ABC
	abc
$ bash -c 'echo $abc'
	# 无内容输出
```

`export <KEY>[=<VALUE>]`用于设置全局变量，同理也不能有空格间隔。当`<VALUE>`未指定时，会直接使用`$<KEY>`的值：

```shell
$ export ABC="abc"
$ echo $ABC
	abc
$ bash -c 'echo $ABC'
	abc
```

事实上，`$<KEY>`和`${<KEY>}`都能获取到`KEY`的变量值：

```shell
$ echo $SHELL
	/bin/bash
$ echo ${SHELL}
	/bin/bash
```

常用的环境变量如下表所示：

| 环境变量                    | 含义                                                                 | 用法或示例值                                                                      | `Unix Bourne`<br>兼容性 | `bash`<br>兼容性 |
| ----------------------- | ------------------------------------------------------------------ | --------------------------------------------------------------------------- | -------------------- | ------------- |
| `HOME`                  | 用户的根目录                                                             | `/home/yaner`                                                               | ✔                    | ✔             |
| `IFS`                   | Shell用于将字符串分隔为若干标识符的分隔符                                            | ` `（空格）                                                                     | ✔                    | ✔             |
| `PATH`                  | Shell查找命令时的搜索目录，用`:`分隔                                             | `/bin;/sbin`                                                                | ✔                    | ✔             |
| `PS1`                   | 命令提示符的主提示符                                                         |                                                                             | ✔                    | ✔             |
| `PS2`                   | 命令提示符的次提示符                                                         |                                                                             | ✔                    | ✔             |
| `BASH`                  | 该`bash`会话的`bash`路径                                                 | `/bin/bash`                                                                 | ❌                    | ✔             |
| `BASH_ALIASES`          | 已启用的、非Shell内置的别名关联数组                                               | 定义`alias ABC="abc"`，则`${BASH_ALIASES[@]}`输出`abc`                            | ❌                    | ✔             |
| `BASH_ARGC`             | `bash`或脚本启动时的参数个数                                                  | `0`                                                                         | ❌                    | ✔             |
| `BASH_ARGV`             | `bash`或脚本启动是的参数数组                                                  | `echo ${BASH_ARGV[@]}`                                                      | ❌                    | ✔             |
| `BASH_ARCV0`            | `bash`或脚本的文件名                                                      |                                                                             | ❌                    | ✔             |
| `BASH_CMDS`             | Shell已执行过命令的位置                                                     |                                                                             | ❌                    | ✔             |
| `BASH_COMMAND`          | 正在或将要执行的命令                                                         |                                                                             | ❌                    | ✔             |
| `BASH_COMPAT`           | Shell兼容级别                                                          |                                                                             | ❌                    | ✔             |
| `BASH_ENV`              | 预执行的初始化脚本路径                                                        |                                                                             | ❌                    | ✔             |
| `BASH_EXECUTION_STRING` | 使用`bash -c "<COMMAND>"`传递的指令                                       |                                                                             | ❌                    | ✔             |
| `BASH_LINENO`           | 当前正在执行的函数在脚本中的行号数组                                                 |                                                                             | ❌                    | ✔             |
| `BASH_LOADABLE_PATH`    | Shell用于查找内建命令的目录，用`:`分隔                                            |                                                                             | ❌                    | ✔             |
| `BASH_REMATCH`          | 保存正则表达式比较运算符`=~`进行肯定匹配时，匹配到的内容数组                                   |                                                                             | ❌                    | ✔             |
| `BASH_SOURCE`           | 以数组形式记录当前执行函数的脚本文件名调用栈                                             |                                                                             | ❌                    | ✔             |
| `BASH_SUBSHELL`         | 当前Shell会话的嵌套级别，初始为`0`                                              |                                                                             | ❌                    | ✔             |
| `BASH_VERSINFO`         | 以数组形式记录`bash`的主版本号、次版本号、补丁级别、发行状态编号、发行状态、系统架构与平台                   | `5 2 37 1 release x86_64-pc-msys`                                           | ❌                    | ✔             |
| `BASH_XTRACEFD`         | 重定向`set -x`开启调试选项后，其跟踪输出会被重定向到文件描述符`$BASH_XTRACEFD`对应的流            | `0`/`1`/`2`                                                                 | ❌                    | ✔             |
| `BASHOPTS`              | 当前Shell会话启用的选项                                                     |                                                                             | ❌                    | ✔             |
| `BASHPID`               | 当前Shell会话的`PID`                                                    |                                                                             | ❌                    | ✔             |
| `CHILD_MAX`             | `bash`会记录最近`$CHILD_MAX`条命令执行后的返回值                                  |                                                                             | ❌                    | ✔             |
| `COLUMNS`               | 当前Shell会话的终端显示宽度（单行字符数）                                            |                                                                             | ❌                    | ✔             |
| `COMP_CWORD`            | `$COMP_WORDS`的索引，其中包含当前光标的位置                                       |                                                                             | ❌                    | ✔             |
| `COMP_LINE`             | 当前命令行                                                              |                                                                             | ❌                    | ✔             |
| `COMP_POINT`            | 光标相对于当前命令起始处的索引                                                    |                                                                             | ❌                    | ✔             |
| `COMP_KEY`              | 用于调用Shell函数补全功能的最后一个按键                                             |                                                                             | ❌                    | ✔             |
| `COMP_TYPE`             | 调用Shell函数补全功能的类型                                                   |                                                                             | ❌                    | ✔             |
| `COMP_WORDBREAKS`       | `Readline`库中用于单词不全的分隔符                                             |                                                                             | ❌                    | ✔             |
| `COMP_WORDS`            | 表示当前命令行所有单词的数组变量                                                   |                                                                             | ❌                    | ✔             |
| `COMPERPLY`             | 表示Shell函数生成的所有补全代码数组                                               |                                                                             | ❌                    | ✔             |
| `COPORC`                | 表示匿名协程IO的文件描述符数组                                                   |                                                                             | ❌                    | ✔             |
| `DIRSTACK`              | 表示目录栈的当前内容                                                         |                                                                             | ❌                    | ✔             |
| `EMACS`                 | `Emacs`是否启用缓冲区，并禁止行编辑功能                                            | `\n`或`t`                                                                    | ❌                    | ✔             |
| `EPOCHREALTIME`         | 当前时间戳对应的微秒数                                                        |                                                                             | ❌                    | ✔             |
| `EPOCHSECONDS`          | 当前时间戳对应的秒数                                                         |                                                                             | ❌                    | ✔             |
| `ENV`                   | 当`bash`以`POSIX`模式启动时，预执行路径为`$ENV`的初始化脚本                            |                                                                             | ❌                    | ✔             |
| `EUID`                  | 当前用户的有效用户ID                                                        |                                                                             | ❌                    | ✔             |
| `EXECIGNORE`            | 使用`path`命令搜索时的排除程序列表                                               |                                                                             | ❌                    | ✔             |
| `FCEDIT`                | `fc`命令使用的默认文本编辑器                                                   |                                                                             | ❌                    | ✔             |
| `FIGNORE`               | 使用`Tab`补全文件名时，忽略的后缀名清单，使用`:`分隔                                     |                                                                             | ❌                    | ✔             |
| `FUNCNAME`              | 当前执行的Shell函数名称                                                     |                                                                             | ❌                    | ✔             |
| `FUNCNEST`              | 脚本中函数的最大嵌套深度，大于该值时立即退出                                             |                                                                             | ❌                    | ✔             |
| `GLOBIGNORE`            | 表示文件名扩展可以忽略的一组文件名模式，使用`:`分隔                                        |                                                                             | ❌                    | ✔             |
| `GROUPS`                | 当前用户所属用户组，是数组便变量                                                   |                                                                             | ❌                    | ✔             |
| `histchars`             | 控制历史记录扩展，最多为`3`                                                    |                                                                             | ❌                    | ✔             |
| `HISTCMD`               | 当前命令在历史记录中的编号                                                      |                                                                             | ❌                    | ✔             |
| `HISTCONTROL`           | 控制哪些命令可以保存在历史记录列表中                                                 |                                                                             | ❌                    | ✔             |
| `HISTFILE`              | 保存命令历史记录的文件目录                                                      | 缺省为`.bash_history`                                                          | ❌                    | ✔             |
| `HISTFILESIZE`          | 保存命令历史记录的文件最大行数                                                    |                                                                             | ❌                    | ✔             |
| `HISTIGNORE`            | 用`:`分隔的命令模式数组，若历史命令与之相匹配，则不计入历史命令中                                 |                                                                             | ❌                    | ✔             |
| `HISTSIZE`              | 保存命令历史记录的内存区最大行数                                                   |                                                                             | ❌                    | ✔             |
| `HISTTIMEFORMAT`        | 用于格式化命令历史记录的时间戳显示方式                                                |                                                                             | ❌                    | ✔             |
| `HOSTFILE`              | Shell补全主机名时读取的文件路径                                                 |                                                                             | ❌                    | ✔             |
| `HOSTNAME`              | 主机名                                                                |                                                                             | ❌                    | ✔             |
| `HOSTTYPE`              | 系统架构                                                               |                                                                             | ❌                    | ✔             |
| `IGNOREEOF`             | Shell退出时的触发条件为连续接收到`$IGNOREEOF`个`EOF`字符                            | 缺省为`1`                                                                      | ❌                    | ✔             |
| `INPUTRC`               | `Readline`初始化文件名                                                   | 缺省为`.inputrc`                                                               | ❌                    | ✔             |
| `INSIDE_EMACS`          | Shell会话是否在`Emacs`的缓冲区中运行                                           |                                                                             | ❌                    | ✔             |
| `LANG`                  | Shell的语言环境种类                                                       |                                                                             | ❌                    | ✔             |
| `LC_ALL`                | Shell支持的所有语言环境中类                                                   |                                                                             | ❌                    | ✔             |
| `LC_COLLATE`            | 字符串排序使用的语言规则                                                       |                                                                             | ❌                    | ✔             |
| `LC_CTYPE`              | 文件名扩展和模式匹配中的字符解释方式                                                 |                                                                             | ❌                    | ✔             |
| `LC_MESSAGES`           |                                                                    |                                                                             | ❌                    | ✔             |
| `LC_NUMERIC`            | 格式化数字的语言规则                                                         |                                                                             | ❌                    | ✔             |
| `LC_TIME`               | 格式化时间的语言规则                                                         |                                                                             | ❌                    | ✔             |
| `LINENO`                | 当知执行的脚本语句行号                                                        |                                                                             | ❌                    | ✔             |
| `LINES`                 | 当前Shell会话的终端显示高度（单列字符数）                                            |                                                                             | ❌                    | ✔             |
| `MACHTYPE`              | 系统类型（CPU-公司-操作系统）                                                  | `x86_64-pc-msys`                                                            | ❌                    | ✔             |
| `OLDPWD`                | 上一个所在的目录                                                           |                                                                             | ❌                    | ✔             |
| `OPTERR`                | 是否显示`getopts`命令产生的错误                                               | `0`/`1`                                                                     | ❌                    | ✔             |
| `OSTYPE`                | 系统类型（操作系统）                                                         | `msys`                                                                      | ❌                    | ✔             |
| `PIPESTATUS`            | 前台进程的退出状态                                                          |                                                                             | ❌                    | ✔             |
| `POSIXLY_CORRECT`       | 是否以`POSIX`模式启动`bash`                                               | 空串或非空串                                                                      | ❌                    | ✔             |
| `PPID`                  | 父进程的`PID`                                                          |                                                                             | ❌                    | ✔             |
| `PROMPT_COMMAND`        | 初始化执行的命令                                                           |                                                                             | ❌                    | ✔             |
| `PROPMT_DIRTRIM`        | 命令提示符显示当前路径时，只显示从当前文件夹起，向父级回溯的`$PROMPT_DIRTRIM`个文件夹名称，值为`0`是表示全部显示 | `PROMPT_DIRTRIM=0`时，显示`/mnt/c/Users`；`PROMPT_DIRTRIM=1`时，显示`.../Users`；以此类推 | ❌                    | ✔             |
| `PS0`                   | 是否在执行命令之前，先执行之前由交互式Shell教师的内容                                      |                                                                             | ❌                    | ✔             |
| `PS3`                   | `select`命令的提示符                                                     |                                                                             | ❌                    | ✔             |
| `PS4`                   | 如果使用`bash -x`选项，则在命令行之前显示`$PS4`提示符                                 |                                                                             | ❌                    | ✔             |
| `PWD`                   | 当前Shell会话所在的目录                                                     |                                                                             | ❌                    | ✔             |
| `RANDOM`                | 读取`$RANDOM`时返回一个`[0, 32768)`之间的随机整数；写入`$RANDOM`时设置随机数种子            |                                                                             | ❌                    | ✔             |
| `READLINE_LINE`         | 使用`bind -x`选项时，保存`Readline`缓冲区的内容                                  |                                                                             | ❌                    | ✔             |
| `READLINE_POINT`        | 使用`bind -x`选项时，表示`Readline`缓冲区当前内容插入点的位置                           |                                                                             | ❌                    | ✔             |
| `REPLY`                 | `read`命令的默认变量                                                      |                                                                             | ❌                    | ✔             |
| `SECONDS`               | 从Shell会话运行开始，到现在经过的秒数。写入时会充值计数器                                    |                                                                             | ❌                    | ✔             |
| `SHELL`                 | 当前Shell会话的文件路径                                                     |                                                                             | ❌                    | ✔             |
| `SHELLOPTS`             | `bash`已启用的选项，用`:`分隔                                                |                                                                             | ❌                    | ✔             |
| `SHLVL`                 | Shell会话的嵌套层级，与`$BASH_SUBSHELL`一致                                   |                                                                             | ❌                    | ✔             |
| `TIMEFORMAT`            | Shell显示时间的格式                                                       |                                                                             | ❌                    | ✔             |
| `TMOUT`                 | `select`和`read`命令在无输入的情况下等待的时长，单位为秒                                |                                                                             | ❌                    | ✔             |
| `TMPDIR`                | Shell创建临时文件的保存目录                                                   |                                                                             | ❌                    | ✔             |
| `UID`                   | 用户的`UID`                                                           |                                                                             | ❌                    | ✔             |

### §3.3.1 数组变量

数组变量用于存储多个值，既可以作为整体引用，也可以用从递增下标单独引用。其声明格式为：两侧由`()`包裹的、各个值用空格分割。

```shell
$ array=(123 abc def)
$ echo $array # 默认显示第0个值
	123
$ echo ${array[0]} # 显示第0个值
	123
$ echo ${array[1]} # 显示第1个值
	abc
$ echo ${array[*]} # 显示所有值
	123 abc def
```

我们可以更改和删除数组变量中的某个值。需要注意：这里的删除更像是清空，因为一旦`unset`了某个值，则它虽然不会在`${array[*]}`显示，但是引用下标时会返回空值，而不是让后面的值向前顶替。

```shell
$ array[2]=ghi # 修改第2个值
$ unset array[1] # 删除第1个值
$ echo ${array[1]}
	# 输出空值
$ echo ${array[2]} # 后面的值没有向前顶替
	ghi
$ echo ${array[*]} # [*]不显示空值
	123 ghi
$ unset array # 删除环境变量
```

## §3.4 重定向流

- 重定向覆盖`STDOUT`流：`>`或`1>`
- 重定向追加`STDOUT`流：`>>`或`1>>`
- 重定向覆盖`STDERR`流：`2>`
- 重定向追加`STDERR`流：`2>>`
- 重定向`STDIN`流：`<`
- 内联重定向`STDIN`：`<< <EOF_STR>`，检测到`<EOF_STR>`时终止输入

## §3.5 管道

`<COMMAND> | <COMMAND>`将前面命令的输出作为后面命令的输入，无需使用文件作为暂存介质。Linux会同时执行这两个命令，数据流不会存储到任何文件或缓冲区。

## §3.6 表达式运算

### §3.6.1 `expr`

`expr`是Bourne Shell提供的一种功能较弱的计算器。它支持的运算有：短路逻辑与`&`、短路逻辑或`|`、小于`<`、小于等于`<=`、等于`=`、不等于`!=`、大于等于`>=`、大于`>`、加法`+`、减法`-`、乘法`*`、除法`/`、取余`%`、提取正则表达式的匹配内容`(match)? <STRING>:<REGEX>`、提取子串`substr <STRING> <POS> <LENGTH>`、查找子串出现的位置`index <STRING> <CHARS>`、输出字符串长度`length <STRING>`、将`<TOKEN>`解释为关键字（即使是关键字）`+ <TOKEN>`、括号`()`。

有些Shell会重载运算符的含义，移作他用。为了完成运算，我们需要在运算符之前使用反斜杠`\`进行转义。

```shell
$ expr 1 + 2
	3
$ expr 2 * 3
	expr: syntax error
$ expr 2 \* 3
	6
```

### §3.6.2 `$[]`

鉴于`expr`有局限性，Bash提供了另一种表达式运算语法：`$[<EXPRESSION>]`。**这种方式只支持整数运算**。

```shell
$ echo $[2*3]
	6
```

Zsh在此基础上提供了浮点数级别的运算。

### §3.6.3 `bc`

`bc`是一个支持编程的计算器，它能处理整数、浮点数、变量、数组、注释、表达式、流程控制语句和函数。执行`bc`命令后，会进入`bc`的交互式命令行。

## §3.7 退出状态码

Linux提供了特殊变量`$?`用于保存最后一个已执行命令的退出状态码。退出状态码是一个`0~255`的`uint8`整数。

Linux内核在[`errno-base.h`](https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/errno-base.h)、[`errno.h`](https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/errno.h)中定义了以下退出状态码：

| 退出状态码     | 宏名                                                  | 含义                                   |
| --------- | --------------------------------------------------- | ------------------------------------ |
| `1`       | `EPERM`（Error Peremeter）                            | 错误的参数，操作不允许                          |
| `2`       | `ENOENT`（Error No Entry）                            | 目录或文件不存在                             |
| `3`       | `ESRCH`（Error Search）                               | 进程不存在                                |
| `4`       | `EINTR`（Error Interrupt）                            | 系统中断                                 |
| `5`       | `EIO`（Error IO）                                     | IO错误                                 |
| `6`       | `ENXIO`（Error No Such IO）                           | 设备或地址不存在                             |
| `7`       | `E2BIG`（Error Too Big）                              | 命令行参数列表过长                            |
| `8`       | `ENOEXEC`（Error No Execute）                         | `exec()`格式错误                         |
| `9`       | `EBADF`（Error Bad File）                             | 文件数错误                                |
| `10`      | `ECHILD`（Error Child）                               | 没有子进程                                |
| `11`      | `EAGAIN`（Error Again）                               | 重试                                   |
| `12`      | `ENOMEM`（Error No Memory）                           | 内存耗尽                                 |
| `13`      | `EACCES`（Error Access）                              | 权限不足                                 |
| `14`      | `EFAULT`（Error Fault）                               | 地址错误                                 |
| `15`      | `ENOTBLK`（Error Not Block）                          | 需要块设备                                |
| `16`      | `EBUSY`（Error Busy）                                 | 设备或资源忙碌中                             |
| `17`      | `EEXIST`（Error Exists）                              | 文件已存在                                |
| `18`      | `EXDEV`（Error Cross Device）                         | 跨设备链接                                |
| `19`      | `ENODEV`（Error No Device）                           | 设备不存在                                |
| `20`      | `ENOTDIR`（Error Not Directory）                      | 对象不是目录                               |
| `21`      | `EISDIR`（Error Is Directory）                        | 对象是目录                                |
| `22`      | `EINVAL`（Error Invalid）                             | 非法命令行参数                              |
| `23`      | `ENFILE`（Error Not File）                            | 文件表（File Table）溢出                    |
| `24`      | `EMFILE`（Error Many Files）                          | 打开的文件过多                              |
| `25`      | `ENOTTY`（Error Not TTY）                             | 对象不是TTY                              |
| `26`      | `ETXTBSY`（Error Text Busy）                          | 文件忙碌中                                |
| `27`      | `EFBIG`（Error File Big）                             | 文件过大                                 |
| `28`      | `ENOSPC`（Error No Space）                            | 设备空间不足                               |
| `29`      | `ESPIPE`（Error Seek Pipe）                           | 非法搜索                                 |
| `30`      | `EROFS`（Error Readonly Filesystem）                  | 文件系统只读                               |
| `31`      | `EMLINK`（Error Many Links）                          | 链接过多                                 |
| `32`      | `EPIPE`（Error Pipe）                                 | 管道损坏                                 |
| `33`      | `EDOM`（Error Domain）                                | 函数接受的实参超出定义域                         |
| `34`      | `ERANGE`（Error Range）                               | 函数返回值无法表示                            |
| `35`      | `EDADLK`（Error Deadlock）                            | 资源发生死锁现象                             |
| `36`      | `ENAMETOOLONG`（Error Name Too Long）                 | 文件名太长                                |
| `37`      | `ENOLCK`（Error No Lock）                             | 没有可用的Record块                         |
| `38`      | `ENOSYS`（Error No System）                           | 系统调用数量非法                             |
| `39`      | `ENOTEMPTY`（Error Not Empty）                        | 目录非空                                 |
| `40`      | `ELOOP`（Error Loop）                                 | 软链接数量过多                              |
| `EAGAIN`  | `EWOULDBLOCK`（Error Would Block）                    | 操作将会阻塞                               |
| `42`      | `ENOMSG`（Error No Message）                          | 指定类型没有消息                             |
| `43`      | `EIDRM`（Error Identifier Removed）                   | 标识符已移除                               |
| `44`      | `ECHRNG`（Error Channel Range）                       | Channel编号超出范围                        |
| `45`      | `EL2NSYNC`（Error Level 2 Not Synchronized）          | Level-2未同步                           |
| `46`      | `EL3HLT`（Error Level 3 Halted）                      | Level-3停机                            |
| `47`      | `EL3RST`（Error Level 3 Reset）                       | Level-3复位                            |
| `48`      | `ELNRNG`（Error Link Range）                          | 链接数超出范围                              |
| `49`      | `EUNATCH`（Error Unattach）                           | 协议驱动级未挂载                             |
| `50`      | `ENOCSI`（Error No CSI）                              | 没有可用的CSI结构                           |
| `51`      | `EL2HLT`（Error Level 2 Halted）                      | Level-2停机                            |
| `52`      | `EBADE`（Error Bad Exchange）                         | 非法交换                                 |
| `53`      | `EBADR`（Error Bad Request）                          | 非法请求描述符                              |
| `54`      | `EXFULL`（Error Exchange Full）                       | 交换已满                                 |
| `55`      | `ENOANO`（Error No Anode）                            | 没有Anode                              |
| `56`      | `EBADRQC`（Errot Bad Request Code）                   | 非法请求吗                                |
| `57`      | `EBADSLT`（Error Bad Slot）                           | 非法插槽                                 |
| `EDEADLK` | `EDEADLOCK`（Error Deadlock）                         |                                      |
| `59`      | `EBFONT`（Error Bad Font）                            | 字体文件损坏                               |
| `60`      | `ENOSTR`（Error No Stream）                           | 设备不能作为流                              |
| `61`      | `ENODATA`（Error No Data）                            | 没有可用数据                               |
| `62`      | `ETIME`（Error Time）                                 | 计时器过期                                |
| `63`      | `ENOSR`（Error No Stream Resources）                  | 流资源耗尽                                |
| `64`      | `ENONET`（Error No Network）                          | 网络不通                                 |
| `65`      | `ENOPKG`（Error No Package）                          | 软件包未安装                               |
| `66`      | `EREMOTE`（Error Remote）                             | 对象在远程                                |
| `67`      | `ENOLINK`（Error No Link）                            | 链接已被保留                               |
| `68`      | `EADV`（Error Advertise）                             | 广告机制错误                               |
| `69`      | `ESRMNT`（Error Srmount）                             | Srmount错误                            |
| `70`      | `ECOMM`（Error Communication）                        | 发送时通信错误                              |
| `71`      | `EPROTO`（Error Protocol）                            | 协议错误                                 |
| `72`      | `EMULTIHOP`（Error Multihop）                         | 尝试多跳                                 |
| `73`      | `EDOTDOT`（Error Dot Dot）                            | RFS特定错误                              |
| `74`      | `EBADMSG`（Error Bad Message）                        | 不是数据信息                               |
| `75`      | `EOVERFLOW`（Error Overflow）                         | 值超出了数据类型的范围                          |
| `76`      | `ENOTUNIQ`（Error Not Unique）                        | 主机名在网络上不唯一                           |
| `77`      | `EBADFD`（Error Bad File Descriptor）                 | 文件描述符已损坏                             |
| `78`      | `EREMCHG`（Error Remote Change）                      | 远程地址已改变                              |
| `79`      | `ELIBACC`（Error Library Access）                     | 找不到共享链接库                             |
| `80`      | `SLIBBAD`（Error Library Bad）                        | 共享链接库已损坏                             |
| `81`      | `ELIBSCN`（Error Library Section）                    | 可执行程序的`.lib`部分损坏                     |
| `82`      | `ELIBMAX`（Error Library Max）                        | 加载共享链接库数量过多                          |
| `83`      | `ELIBEXEC`（Error Library Execute）                   | 不能直接执行共享链接库                          |
| `84`      | `EILSEQ`（Error Illegal Sequence）                    | 非法字节系列                               |
| `85`      | `ERESTART`（Error Restart）                           | 从系统中断中恢复                             |
| `86`      | `ESTRPIPE`（Error Stream Pipe）                       | 流管道错误                                |
| `87`      | `EUSERS`（Error Users）                               | 用户数量过多                               |
| `88`      | `ENOTSOCK`(Error Not Socket)                        | 在非Socket对象上执行Socket操作                |
| `89`      | `EDESTADDRREQ`（Error Destination Address Required）  | 未指定目标地址                              |
| `90`      | `EMSGSIZE`（Error Message Size）                      | 消息过长                                 |
| `91`      | `EPROTOTYPE`（Error Protocol Type）                   | Socke协议类型错误                          |
| `92`      | `ENOPROTOOPT`（Error Protocol Option）                | 协议不可用                                |
| `93`      | `EPROTONOSUPPORT`（Error Protocol Not Supported）     | 协议不支持                                |
| `94`      | `ESOCKTNOSUPPORT`（Eror Socket Type Not Supported）   | Socket类型不支持                          |
| `95`      | `EOPNOTSUPP`（Error Operation Not Supported）         | 路由节点不支持操作                            |
| `96`      | `EPFNOSUPPORT`（Error Protocol Family Not Supported） | 协议族不支持                               |
| `97`      | `EAFNOSUPPORT`（Error Address Family Not Supported）  | 协议族不支持地址族                            |
| `98`      | `EADDRIUNSE`（Error Address In Use）                  | 地址已被占用                               |
| `99`      | `EADDRNOTAVAIL`（Error Address Not Available）        | 地址不可用                                |
| `100`     | `ENETDOWN`（Erroe Network Unreachable）               | 网络不可用                                |
| `101`     | `ENETUNREACH`（Error Network Reset）                  | 网络不可达                                |
| `102`     | `ENETRESET`（Error Network Reset）                    | 网络连接被路由节点Reset                       |
| `103`     | `ECONNABORTED`（Error Connection Aborted）            | 软件导致的连接中断                            |
| `104`     | `ECONNRESET`（Error Connection Reset）                | 网络连接被目标地址Reset                       |
| `105`     | `ENOBUFS`（Error No Buffers）                         | Buffer空间已满                           |
| `106`     | `EISCONN`（Error Is Connected）                       | 网络已经建立连接                             |
| `107`     | `ENOTCONN`（Error Not Connected）                     | 网络未建立连接                              |
| `108`     | `ESHUTDOWN`（Error Shutdown）                         | 本地通过`shutdown()`关闭Socket后，本地仍然尝试发送数据 |
| `109`     | `ETOOMANYREFS`（Error Too Many Reference）            | 引用计数过高，导致文件描述符或内存块拼接失败               |
| `110`     | `ETIMEDOUT`（Error Timed Out）                        | 连接超时                                 |
| `111`     | `ECONNREFUSED`（Error Connection Refused）            | 连接被拒                                 |
| `112`     | `EHOSTDOWN`（Error Host Down）                        | 远程通过`shutdown()`关闭Socket后，本地仍然尝试发送数据 |
| `113`     | `EHOSTUNREACH`（Error Host Unreachable）              | 路由不可达                                |
| `114`     | `EALREADY`（Error Already）                           | 操作早已进行中                              |
| `115`     | `EINPROGRESS`（Error In Progress）                    | 操作现在进行中                              |
| `116`     | `ESTALE`（Error Stale）                               | 文件句柄过时                               |
| `117`     | `EUCLEAN`（Error Unclean）                            | 数据结构需要初始化                            |
| `118`     | `ENOTNAM`（Error Not Name）                           | 文件不属于XENIX命名类型                       |
| `119`     | `ENAVAIL`（Error Available）                          | 没有可用的XENIX信号量                        |
| `120`     | `EISNAM`（Error Is Name）                             | 文件属于XENIX命名类型                        |
| `121`     | `EREMOTEIO`（Error Remote IO）                        | 远程IO错误                               |
| `122`     | `EDQUOT`（Error Quota）                               | 超出预设配额                               |
| `123`     | `ENOMEDIUM`（Error No Medium）                        | 未找到介质                                |
| `124`     | `EMEDIUMTYPE`（Error Medium Type）                    | 截至类型错误                               |
| `125`     | `ECANCELED`（Error Canceled）                         | 操作取消                                 |
| `126`     | `ENOKEY`（Error No Key）                              | 密钥不可用                                |
| `127`     | `EKEYEXPIRED`（Error Key Expired）                    | 密钥已过期                                |
| `128`     | `EKEYREVOKED`（Error Key Revoked）                    | 密钥已撤销                                |
| `129`     | `EKEYREJECTED`（Error Key Rejected）                  | 密钥被服务拒绝                              |
| `130`     | `EOWNERDEAD`（Error Owner Dead）                      | 属主已被删除                               |
| `131`     | `ENOTRECOVERABLE`（Error Not Recoverable）            | 不可恢复                                 |
| `132`     | `EPFKILL`（Error RF Kill）                            | RF-kill关闭了无线网络，导致操作不能执行              |
| `133`     | `EHWPOISON`（Error Hardware Poison）                  | 内存页硬件错误                              |



| 退出状态码   | 含义      |
| ------- | ------- |
| `0`     | 命令执行成功  |
| `1`     | 一般性位置错误 |
| `2`     |         |
| `126`   |         |
| `127`   |         |
| `128`   |         |
| `128+x` |         |
| `130`   |         |
| `255`   |         |
