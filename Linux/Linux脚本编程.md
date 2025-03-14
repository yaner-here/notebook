参考文献：

- 《Linux命令行与shell脚本编程大全（第4版）》 [豆瓣](https://book.douban.com/subject/35933905/)

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

### §2.1.5 `trap`

`trap <COMMANDS> <SIGNALS>`用于设置捕获Linux信号后执行的命令；`trap -- <SIGNALS>`用于删除自定义规则。特殊地，`trap -`或`trap --`表示删除所有自定义规则，恢复到默认状态。

下面的脚本捕获了`SIGINT`（`Ctrl + C`）信号，从而避免关键代码执行时被打断。

```shell
$ cat script.sh
	trap "echo 'Ctrl + C detected, but this virus can'\'t' be stopped'" SIGINT;
	for (( i = 1 ; i <= 5 ; ++i )) ; do
	    echo "Process($i/5)..."
	    sleep 1;
	done
$ bash ./script.sh
	Process(1/5)...
	Process(2/5)...
	^CCtrl + C detected, but this virus can't be stopped
	Process(3/5)...
	Process(4/5)...
	^CCtrl + C detected, but this virus can't be stopped
	Process(5/5)...
```

除了Linux信号以外，`trap`还能捕获一种名为`EXIT`的特殊事件，它代表着脚本执行完毕后要退出的事件。

```shell
~ cat script.sh
	trap "echo 'trap EXIT'" EXIT;
	echo "Processing...";
~ bash ./script.sh
	Processing...
	trap EXIT
```

`trap -p`选项用于获取当前Shell或脚本环境下自定义的`trap`规则：

```shell
~ cat script.sh
	trap "echo 'trap EXIT'" EXIT;
	trap -p
~ bash ./script.sh
	trap -- 'echo '\''trap EXIT'\''' EXIT
	trap EXIT
```

使用

### §3.1.6 `$$`

`$$`表示当前进程的PID。

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

## §2.9 编辑器

### §2.9.1 `sed`

`sed <OPTIONS>? <SCRIPT> <FILE>?`（Stream Editor）是一个针对文件流的编辑器。它能从`STDIN`或`<FILE>`中逐行读入，根据`<SCRIPT>`匹配行内的文本并修改，将修改后的单行数据输出到`STDOUT`。

可以使用`sed [-e]? '<SCRIPT>'`进行匹配与修改：

```
$ cat data.txt
	Alice loves the apple.
	Alice loves the banana.
	Alice loves the cherry.
$ cat data.txt | sed 's/Alice/Bob/'
	Bob loves the apple.
	Bob loves the banana.
	Bob loves the cherry.
$ cat data.txt | sed -e 's/Alice/Bob/; s/loves/likes/'
	Bob likes the apple.
	Bob likes the banana.
	Bob likes the cherry.
```

多个规则可以放进一个文件中，用`sed -f`选项读取。

```shell
$ cat data.txt
	Alice loves the apple.
	Alice loves the banana.
	Alice loves the cherry.
$ cat rule.txt
	s/Alice/Bob/
	s/loves/likes/
$ cat data.txt | sed -f rule.txt
	Bob likes the apple.
	Bob likes the banana.
	Bob likes the cherry.
```

#### §2.9.1.1 替换功能

格式为`s/<PATTERN>/<SUBSTITUDE>/<FLAG>`的`sed`规则用于替换文本。这里的`<FLAG>`有以下选项可用：

- `g`（Global）：替换每一个匹配处
- `p`（Print）：只输出匹配成功且替换后的行文本
- `w <FILE>`（Write）：只将匹配成功的替换结果写入文件
- `<NUMBER>`：只替换第`<NUMBER>`个匹配处
- `r <FILE>`（Read）：从`<FILE>`中读取文本，追加到`STDIN`的末尾

#### §2.9.1.2 行寻址

```shell
$ sed '{s/abc/def/g}';   # 检测和更改所有行
$ sed '2{s/abc/def/g}';  # 只检测和更改第二行
$ sed '2,3{s/abc/def/g}'; # 只检测和更改第二、三行
$ sed '2,${s/abc/def/g}'; # 只检测和更改第二行及其之后行
```

#### §2.9.1.3 正则表达式寻址

```shell
$ sed '/<REGEX>/s/abc/def/g' # 只有符合<REGEX>的行才能检测和更改
```

#### §2.9.1.4 命令组

```shell
$ seg '3,${s/abc/def/g; s/123/456/g}'
```

#### §2.9.1.5 删除功能

删除功能只需要`d`即可，同时支持行寻址和正则表达式寻址。

```shell
$ cat data.txt
	Alice loves the apple.
	Alice loves the banana.
	Alice loves the cherry.
$ sed '2d' data.txt # 行寻址
	Alice loves the apple.
	Alice loves the cherry.
$ sed '/a/d' data.txt # 正则表达式寻址
	Alice loves the cherry.
```

除此以外，删除模式还支持正则表达式行寻址，其语法为`/<START_DELETE_PATTERN>/,/<END_DELETE_PATTERN>/d`，通过两个正则表达式寻找起始行和终止行，删除这之间的所有行文本（包括起点和终点这两行）。**具体来说，这种删除模式类似于双指针，先由起点指针搜索匹配的一行，然后结束指针在此基础上搜索匹配的一行，缺省首尾指针后进行删除，开启下一轮循环，以此类推**。如果一直找不到终点行，则从起点行开始一直删到尾。

```shell
$ cat data.txt
	Alice loves the apple.
	Alice loves the banana.
	Alice loves the cherry.
$ sed '/apple/,/banana/d' data.txt
	Alice loves the cherry.
```

#### §2.9.1.6 插入模式和追加模式

插入模式`i`和追加模式`a`分别表示在匹配行之前/之后添加一行。它的语法略有不同，主要体现在斜杠用的是反斜杠。

```shell
$ echo "Hello World" | sed 'i\Header';
	Header
	Hello World
$ echo "Hello World" | sed 'a\Footer';
	Hello World
	Footer
```

插入模式和追加模式都支持行寻址。

```shell
$ sed '3a\Footer'; # 追加到第三行之后
$ sed '$a\Footer'; # 追加到最后一行之后
```

#### §2.9.1.7 修改模式

修改模式`c`的语法与插入模式和追加模式类似，它的作用是将匹配的行全部替换为目标文本。

修改模式支持行寻址和正则表达式寻址。

```shell
$ cat data.txt
	Alice loves the apple.
	Alice loves the banana.
	Alice loves the cherry.
$ cat data.txt | sed '2c\Line 2 is changed!'
	Alice loves the apple.
	Line 2 is changed!
	Alice loves the cherry.
$ cat data.txt | sed '/a/c\This line contains \'a\'!'
	This line contains 'a'!
	This line contains 'a'!
	Alice loves the cherry.
```

#### §2.9.1.8 转换模式

转换模式`y`用于处理单个字符，其语法为`[ADDRESS]y/<INCHARS>/<OUTCHARS>/`。转换模式会按照`<INCHARS>`和`<OUTCHARS>`形成的转换表，对字符进行一对一的映射。如果`<INCHARS>`和`<OUTCHARS>`的长度不同，则`sed`会报错。

```shell
$ cat data.txt
	aabbcc
$ cat data.txt | sed 'y/abc/cza/'
	cczzaa
```

#### §2.9.1.9 打印选项

`sed '='`用于在每一行之前追加一行行号（从`0`开始）。`sed 'l'`用于将文本中的不可打印字符以`ASCII`转义符的形式输出。

#### §2.9.1.10 `n`与`N`

`n`（Next）用于让`sed`不处理当前行，而是处理当前行的下一行。它的意义相当于给正则表达式赋予了环视的功能。
```shell
$ cat data.txt # 任务：只删除Header后的空行
	Header
	
	Content
	
	Footer
$ sed '/^$/d' data.txt # 直接匹配会出错
	Header
	Content
	Footer
$ sed '/Header/{n; d;}' data.txt
	Header
	Content
	
	Footer
```

`N`（Next）用于让`sed`不仅处理当前行，还同时处理下一行。

```shell
$ cat data.txt
	Header
	
	Content
	
	Footer
$ sed '/Header/{N; s/\n/(换行符)/;}' data.txt
	Header(换行符)
	Content
	
	Footer
```

`N`命令经常用于跨行排版纯文本的词组替换：

```shell
$ cat data.txt
	This is a RFC documentation of Ethernet
	Protocol. Usually, documentattions will
	be formatted to fit the limited column
	size.
$ sed 'N; s/Ethernet\nProtocol/IPv4\nProtocol/' data.txt
	This is a RFC documentation of IPv4
	Protocol. Usually, documentattions will
	be formatted to fit the limited column
	size.
```

**这里要额外警惕：`n`与`N`的识别行为类似于双指针，它只会检测`1/2`行、`3/4`行、...是否匹配，而不会检查`1/2`行、`2/3`行、`3/4`行、...是否匹配**。

```shell
$ cat data.txt
	one
	two
	three
	four
$ sed 'N ; /one\ntwo/d' data.txt
	three
	four
$ sed 'N ; /two\nthree/d' data.txt
	one
	two
	three
	four
```

**除此以外，`n`和`N`都要求当前行的下一行是存在的。如果当前行就是最后一行，则`sed`编辑器会判定为编辑结束，直接退出**。

除了替换模式，`n`和`N`也能用户删除模式、打印模式等等。例如多行删除模式（`D`），只会删除匹配的第一行，而不会像`d`那样删除所有行。

```shell
$ cat data.txt
	one
	two
	three
	four
$ sed 'N ; /one\ntwo/D' data.txt
	two
	three
	four
```

#### §2.9.1.11 保留空间

模式空间和保留空间都是`sed`提供的内存缓冲区。其中保留空间用于让开发者临时储存文本文件。相关的命令如下：

- `h`：将模式空间复制到保留空间
- `H`：将模式空间附加到保留空间
- `g`：将保留空间复制到模式空间
- `G`：将保留空间附加到模式空间
- `x`：交换保留空间和模式空间的内容

下面的例子演示了如何使用保留空间。其中`sed -n`选项阻止自动输出模式空间的内容，只有`p`命令才能打印输出：

1. `sed`读取第一行`one`，存入模式空间
2. `h`命令将模式空间复制到保留空间，两者的值均为`one`
3. `p`命令打印模式空间，即`STDOUT`的第一行`one`
4. `n`命令读入第二行`two`，将其覆盖到模式空间中
5. `p`命令打印模式空间，即`STDOUT`的第二行`two`
6. `g`命令将保留空间复制到模式空间，两者的值均为`one`
7. `p`命令打印模式空间，即`STDOUT`的第三行`one`

```shell
$ echo -e "one\ntwo" | sed -n '/one/{h; p; n; p; g; p;}'
	one
	two
	one
```

#### §2.9.1.12 排除模式

排除模式`!`本质上是放在其他模式前面的修饰符，会让原本的命令失效。例如`!p`表示匹配到的不打印：

```shell
# 敏感词过滤
$ echo -e "好\n坏\n善\n恶" | sed -n '/[坏恶]/!p'
	好
	善
```

前文说过，`n`和`N`不会处理当前行是最后一行的情况。事实上，我们完全可以使用`$!n`或`$!N`，表示如果当前行是最后一行，则禁用`n`或`N`。这里的`$`就是`[address]`的一个特例，其余情况正常使用。

#### §2.9.1.13 分支

分支的语法为`[address]b [label]?`，其中`[label]`表示要跳转到的`sed`命令的标签，缺省表示跳过`sed`的所有命令。

可以看到， 在下面的例子中，`sed`跳过了第二行和第三行的替换操作：

```shell
$ cat data.txt
	one
	one
	one
$ cat data.txt | sed '2,3b; s/one/two/'
	two
	one
	one
```

`[label]`需要自定义，不能超过七个字符：

```shell
$ cat data.txt
	one two
	one two
	one two
$ cat data.txt | sed '2b label2; :label1 s/one/three/; :label2 s/two/four/;'
	three four
	one four # 第二行的one没有被替换
	three four
```

分支命令可以放在`sed`脚本中的任何位置：

```shell
$ cat data.txt
	移,除,所,有,逗,号,
$ cat data.txt | sed ':start p; s/,//; /,/b start;'
	移,除,所,有,逗,号,
	移除,所,有,逗,号,
	移除所,有,逗,号,
	移除所有,逗,号,
	移除所有逗,号,
	移除所有逗号,
	移除所有逗号
```

#### §2.9.1.14 测试

测试命令`t`的语法是`[address]t [label]?`，它提供了一种`sed`版的`if-then`语句。它会检测前一个命令是否匹配且执行成功。如果成功，则不跳转到标签；如果不成过，则跳转到标签。

```shell
$ cat data.txt
	移,除,所,有,逗,号,
$ cat data.txt | sed ':start p; s/,//; t start;'
	移,除,所,有,逗,号,
	移除,所,有,逗,号,
	移除所,有,逗,号,
	移除所有,逗,号,
	移除所有逗,号,
	移除所有逗号,
	移除所有逗号
	移除所有逗号
```

#### §2.9.1.15 正则表达式替换

在形如`/<REGEX>/<SUBSTITUDE>/`的结构中，我们可以在`<SUBSTITUDE>`中使用`&`引用`<REGEX>`匹配的完整部分。

```shell
$ echo "Hello World" | sed 's/Hello/"&"/'
	"Hello" World
```

也可以在`<REGEX>`中使用`(<SUB_REGEX>)`创建子模式，使用`\1`、`\2`、...分别引用第一个子模式、第二个子模式、...匹配的内容。

### §2.9.2 `gawk`

`gawk`是`awk`的GNU版本，它提供了一个完整的编程环境，因此比`sed`更灵活。其语法为`gawk <OPTIONS>? <PROGRAM> <FILE>`，并且提供了以下常用选项：

- `-F <FILE_SEPERATOR>`：指定用于划分字段的分隔符
- `-f <PROGRAM_FILE>`：从`<PROGRAM_FILE>`中读取`gawk`脚本代码
- `-v <KEY>=<VALUE>`：定义`gawk`脚本中的变量与默认值
- `-L <LEVEL>`：定义`gawk`的兼容模式与警告级别

`gawk`脚本的语法是：由`{}`包裹起来的字符串。它的位置变量含义与Bash脚本的含义类似，除了`$0`表示整个本文行。例如下面的命令输出当前Linux环境中的所有用户：

```shell
$ cat /etc/passwd | gawk -F: '{print $1;}'
	root
	systemd-coredump
	systemd-network
```

`gawk`脚本中的`BEGIN`关键字允许脚本代码在开头执行一次，`END`关键字允许在结尾执行一次：

```shell
$ cat /etc/passwd | gawk -F: 'BEGIN {print ">> Users List Begin<<";} {print $1;} END {print ">> Users List End <<"}'
    >> Users List Begin <<
	root
	systemd-coredump
	systemd-network
	>> Users List End <<
```

#### §2.9.2.1 变量

`gawk`支持两种变量：内建变量、自定义变量。

前文介绍过数据字段变量（`$1`、`$2`、...），它们就属于内建变量。以下介绍了其他常用的内建变量：

| 内建变量          | 含义                                    |
| ------------- | ------------------------------------- |
| `ARGC`        | 命令行参数的数量                              |
| `ARGIND`      | 当前处理的文件在`$ARGV`中的索引                   |
| `ARGV`        | 命令行参数的数组变量                            |
| `CONVFMT`     | `printf`命令对数字的转换格式，缺省为`%.6g`          |
| `ENVIRON`     | 当前Shell环境变量构成的关联数组                    |
| `ERRNO`       | 读取或关闭文件时的退出状态码                        |
| `FILENAME`    | `gawk`读取的文件名                          |
| `FNR`         | 当前数据文件中的记录数                           |
| `IGNORECASE`  | 设为非零值时，忽略字母大小写                        |
| `NF`          | 数据文件中的字段总数，特殊地`$NF`表示最后一个字段的值         |
| `NR`          | 已处理的记录数                               |
| `OFMT`        | 数字的输出显示格式，缺省为`%.6g`                   |
| `RLENGTH`     | `match`函数匹配的子串长度                      |
| `RSTART`      | `match`函数匹配的子串起始位置                    |
| `FIELDWIDTHS` | 用空格分隔的一系列数字，用于规定每个字段的宽度，一旦设置则`$FS`不生效 |
| `FS`          | 输入字段分隔符，缺省为一个空格字符                     |
| `RS`          | 输入记录分隔符，缺省为一个换行符                      |
| `OFS`         | 输出字段分隔符，缺省为一个空格字符                     |
| `ORS`         | 输出记录分隔符，缺省为一个换行符                      |

```shell
$ cat data.txt
	alice,15,male
	bob,18,female
	carol,22,male
$ gawk 'BEGIN {FS=","; OFS=" - ";} {print $1,$2,$3}' data.txt
	alice - 15 - male
	bob - 18 - female
	carol - 22 - male
$ gawk 'BEGIN {FIELDWIDTHS="3 2 3";} {print $1,$2,$3}' data.txt
	ali ce ,15
	bob ,1 8,f
	car ol ,22
```

**`gawk`脚本引用变量值时，无需在变量名之前添加`$`**。`gawk`脚本中的`ARGV`与Bash脚本中的`$ARGV`略有不同——`gawk`不会将`gawk`脚本字符串本身视为一个参数。

```shell
$ gawk '{print ARGC,ARGV[0],ARGV[1]}' ./data.txt
	2 gawk ./data.txt
```

自定义变量的语法与Bash脚本完全一致。除了在`gawk`脚本中定义变量，也可以在`gawk KEY=VALUE`命令行中直接定义。使用`gawk -v KEY=VALUE`可以让自定义变量在`BEGIN{}`块之前就生效。

#### §2.9.2.2 数组

使用`<VAR>[<KEY>]=<VALUE>`定义数组变量。使用如下循环遍历数组变量：

```shell
for (key in array) {
	echo '$key = $var[key]'
}
```

使用`delete <VAR>[<KEY>]`删除元素

#### §2.9.2.3 模式匹配

`gawk`允许使用正则表达式、匹配操作符（`~`）和数学表达式（支持`>`/`<`/`==`/`>=`/`<=`）进行匹配。

```shell
# 使用正则表达式匹配
$ gawk '/<REGEX>/{<SCRIPT>}'

# 只使用正则表达式匹配每条记录的第二个字段，匹配成功则执行
$ gawk '$2 ~ /<REGEX>/{<SCRIPT>}'
# 只使用正则表达式匹配每条记录的第二个字段，匹配失败则执行
$ gawk '$2 !~ /<REGEX>/{<SCRIPT>}'

# 只有当$3==0时才执行
$ gawk '$3 == 0 {<SCRIPT>}'
```

#### §2.9.2.4 流程控制

`gawk`支持`if(){}else{}`、`while(){}`、`do{}while()`、`for(;;){}`等常见的流程控制关键字。

```shell
$ cat data.txt
	1
	5
	9
	3
	4
$ gawk '{ if($1>=5){print $1;}}' data.txt
	5
	9
$ gawk '{ while($1>0){printf "%d ", $1; $1 = $1 - 1;} printf "\n";}' data.txt
	1
	5 4 3 2 1
	9 8 7 6 5 4 3 2 1
	3 2 1
	4 3 2 1
```

#### §2.9.2.5 函数

`gawk`脚本提供了以下内建函数：

| 内建函数                       | 作用                                                                                                       |
| -------------------------- | -------------------------------------------------------------------------------------------------------- |
| `atan2(x, y)`              | $\text{arctan}(x)$                                                                                       |
| `cos(x)`                   | $\cos(x)$                                                                                                |
| `exp(x)`                   | $e^x$                                                                                                    |
| `int(x)`                   | 向下取整                                                                                                     |
| `log(x)`                   | $\ln(x)$                                                                                                 |
| `rand()`                   | `[0, 1)`随机数                                                                                              |
| `sin(x)`                   | $\sin(x)$                                                                                                |
| `sqrt(x)`                  | `\sqrt{x}`                                                                                               |
| `srand(x)`                 | 重置随机数种子为`x`                                                                                              |
| `asort(s,d?)`              | 将数组`s`按**值**排序，重新分配从序号递增的键。如果传入`d`，则将排序后的结果存入`d`中                                                        |
| `asorti(s,d?)`             | 将数组`s`按**索引**排序，重新分配从序号递增的键。如果传入`d`，则将排序后的结果存入`d`中                                                       |
| `gensub(r,s,h,t?)`         | 将字符串`t`中匹配正则表达式`r`的部分替换成字符串`s`，如果未传入`t`则缺省为`$0`。至于替换哪些部分，如果`h`是以`g`/`G`开头的字符串，则替换全部；如果是数字，则只替换第`h`处匹配的部分 |
| `gsub(r,s,t?)`             | 将字符串`t`中**所有**匹配正则表达式`r`的部分替换成字符串`s`，如果未传入`t`则缺省为`$0`                                                    |
| `index(s,t)`               | 返回子串`t`在字符串`s`中首次出现的位置，如果未找到则返回`0`                                                                       |
| `length(s?)`               | 返回字符串`s`的长度，如果未传入`s`，则缺省为`$0`                                                                            |
| `match(s,r,a?)`            | 返回字符串`s`匹配正则表达式`r`的位置，如果传入数组`a`，则将所有位置存储`a`中                                                             |
| `split(s,a,r?)`            | 将字符串`s`按正则表达式`r`（缺省为`$IFS`）分割，将分隔结果存入数组`a`中，并返回一共分成了多少段                                                  |
| `sprintf(fmt,vars?)`       | 等价于`printf`，只不过带了括号                                                                                      |
| `sub(r,s,t?)`              | 将字符串`t`中**第一处**匹配正则表达式`r`的部分替换成字符串`s`，如果未传入`t`则缺省为`$0`                                                   |
| `substr(s,i,n?)`           | 返回字符串`s`从索引`i`开始、长度为`n`的子串。未传入`n`时缺省为直到字符串末尾                                                             |
| `tolower(s)`               | 将字符串`s`中的所有字母转成小写                                                                                        |
| `toupper(s)`               | 将字符串`s`中的所有字母转成大写                                                                                        |
| `mktime(datespec)`         | 将一个格式为`YYYY MM DD HH MM SS [DST]`的日期转换为时间戳                                                               |
| `strftime(fmt,timestamp?)` | 将时间戳转换为`fmt`格式的日期，`fmt`会传给Linux中的`date`命令。`timestamp`缺省时为当前时间的时间戳                                        |
| `systime()`                | 返回当前时间的时间戳                                                                                               |

`gawk`也允许开发者自定义函数。

```shell
$ cat script.txt
	function get_rand(upper_bound){
	    return int(upper_bound*rand());
	}
	{
	    print "生成5个0~100的随机数:";
	    for(i=1;i<=5;++i){
	        print get_rand(100);
	    }
	}
$ echo '' | gawk -f script.txt
	生成5个0~100的随机数:
	92
	59
	30
	57
	74
```

## §2.10 终端

### §2.10.1 `tmux`

`tmux`有三个从大到小的概念：工作空间（Workspace/Session）、大窗口（Window）、小窗口（Pane）。它使用的所有快捷键都要加一个前缀键（Prefix Key），缺省为`Ctrl+B`，然后输入单字符命令。

| 快捷键/命令                   | 作用                   |
| ------------------------ | -------------------- |
| 前缀键`,c`                  | 在当前工作空间内，在末尾创建一个大窗口  |
| 前缀键`,p`                  | 在当前工作空间内，切换到上一个大窗口   |
| 前缀键`,n`                  | 在当前工作空间内，切换到下一个大窗口   |
| 前缀键`,[0-9]`              | 在当前工作空间内，切换到指定序号的大窗口 |
| 前缀键`,shift+[0-9]`        | 在当前工作空间内，删除指定序号的大窗口  |
| 前缀键`,%`                  | 在当前大窗口内，竖向分屏地创建小窗口   |
| 前缀键`,"`                  | 在当前大窗口内，横向分屏地创建小窗口   |
| 前缀键`,[方向键]`              | 在当前大窗口内，切换到相对方向的小窗口  |
| 前缀键`,q,[0-9]`            | 在当前大窗口内，切换到指定序号的小窗口  |
| 前缀键`,z`                  | 在当前大窗口内，最大化/恢复当前的小窗口 |
| 前缀键`,x`                  | 在当前大窗口内，删除当前的小窗口     |
| 前缀键`,w`                  | 查看全局窗口概览信息           |
| 前缀键`,d`                  | 暂时离开工作空间             |
| `tmux attach [-t <NUM>]` | 重新进入工作空间             |
| `tmux ls`                | 查看所有工作空间             |

`tmux`的配置文件保存在`~/.tmux.conf`或`~/.config/.tmux.conf`，具体配置可参见[Tmux Cheat Sheet]((https://tmuxcheatsheet.com/)。

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

在命令列表或进程列表的后面加一个`&`，就可以创建一个作业。此时`bash`会先输出当前创建的后台作业号与`PID`，然后显示所有已执行完毕、**且未曾在此显示过**的后台作业，最后恢复可交互的状态。**后台作业号从`1`开始自增**。**后台进程运行时，它的`STDOUT`、`STDERR`依然重定向到终端**。

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

`bash`提供了`jobs`关键字，用于查看当前Shell的后台作业情况。具体来说，它会显示当前正在运行（`Running`）的后台作业，以及所有已执行完毕（`Done`）、**且未曾在此显示过**的后台作业。我们还可以使用`-l`显示后台作业的`PID`。其中`+`表示最近启动的后台作业，**作业控制命令缺省时也会引用该作业**，`-`表示第二最近启动的后台作业。

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

用户可以通过`Ctrl + Z`暂停作业，再用`bg <作业号>?`恢复作业，或者用`fg <作业号>?`重启作业。

```shell
$ cat script.sh
	for (( i = 1 ; i <= 5 ; ++i )); do
	    echo "Processing($i/5)";
	    sleep 1;
	done
$ bash ./script.sh
	Processing(1/5)
	Processing(2/5)
	^Zfish: Job 1, 'bash ./script.sh' has stopped
$ jobs
	Job     Group   CPU     State   Command
	1       1752    0%      stopped bash ./script.sh
$ bg
	Send job 1 'bash ./script.sh' to background
	Processing(3/5)
$ Processing(4/5)
	Processing(5/5)
fish: Job 1, 'bash ./script.sh' has ended
```

Shell会话运行的后台作业，会始终与当前Shell会话绑定在一起。如果退出当前会话，则后台作业也会全部随之退出。

### §3.1.3 `nohup`

在钱文忠，我们提到如果退出当前会话，则后台作业也会全部随之退出。`nohup`通过拦截`SIGHUP`信号，实现防止后台作业退出的效果。

与此同时，`nohup`会解除`STDOUT`和`STDERR`与终端会话的联系，将这两个输出流**以追加模式**重定向到`$HOME/nohup.out`或`./nohup.out`。如果有多个`nohup`运行的后台作业，则这些输出信息会混在一起。

### §3.1.4 协程

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

### §3.1.5 谦让度

在多任务操作系统中，调度优先级（也称谦让度，Nice Value）表示相对于其他进程，内核为该进程分配的CPU时间。其取值范围为`[-29, 19]`，左右两端分别表示最高优先级和最低优先级。默认情况下，Shell以谦让度`0`运行所有进程。

我们可以使用`nice -n <NICE_VALUE> <COMMAND>`命令以谦让度为`<NICE_VALUE>`运行程序`<COMMAND>`。当`<NICE_VALUE>`为正数时，`-n <NICE_VALUE>`可以简写为`-<NICE_VALUE>`；当`<NICE_VALUE>`为负数时，`-n <NICE_VALUE>`可以简写为`--<NICE_VALUE_ABS>`。

```shell
$ nice -10 ./script.sh &
```

`renice -n <NICE_VALUE> -p <PID>`可以更改进程的谦让度。对于普通用户而言，`renice`用能用于属主为自己的进程，且**只能调低优先级**。而`root`权限就没有这些限制。

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

### §3.3.2 `source`/点号操作符

`source <FILE>`和`. <FILUE>`的作用完全一致，类似于C语言中的`#include<>`宏，都能将`<FILE>`中的内容添加到当前位置，供Shell执行。这样做可以继承`<FILE>`中定义的变量和函数。**用`source`引入的变量和函数全部会被视为全局的变量和函数，可以自动继承给子进程**。

## §3.4 重定向流

- 重定向覆盖`STDOUT`流：`>`或`1>`
- 重定向追加`STDOUT`流：`>>`或`1>>`
- 重定向覆盖`STDERR`流：`2>`
- 重定向追加`STDERR`流：`2>>`
- 重定向`STDIN`流：`<`
- 内联重定向`STDIN`：`<< <EOF_STR>`，检测到`<EOF_STR>`时终止输入
- 重定向到`STDOUT`流：`>&1`
- 重定向到`STDERR`流：`>&2`

Linux将每个对象当作文件来处理，每个文件由一个非负整数唯一指定，称为**文件描述符**。一个进程最多可以同时打开的文件描述符是有限的，通常为`9`个。Bash保留了前三个文件描述符：

| 文件描述符 | 宏定义名     | 含义   |
| ----- | -------- | ---- |
| `0`   | `STDIN`  | 标准输入 |
| `1`   | `STDOUT` | 标准输出 |
| `2`   | `STDERR` | 标准错误 |

文件描述符可以用在重定向流操作符的前面，例如`2>`表示重定向`STDERR`，`&>`表示同时重定向`STDOUT`和`STDERR`。

Shell脚本允许使用`exec`进行全局的重定向。例如`exec 0< file.txt`、`exec 1> stdout.txt`、`exec 2> stderr.txt`。一旦使用这种方法完成重定向，则不太容易恢复到原先的状态。为了实现撤销操作，我们需要借用其它的文件描述符，使其重定向到标准流。

```shell
exec 3>&1;         # 将3重定向到STDOUT
exec 1>stdout.txt; # 将1重定向到stdout.txt
exec 1>&3;         # 将1重定向到STDOUT 

exec 4<&0;         # 将4重定向到STDIN
exec 0<stdin.txt;  # 将0重定向到文件
exec 0<&6;         # 将0重定向到STDIN
```

一个文件描述符可以同时被当作输入流和输出流。我们使用形如`exec 3<> file.txt`的语法创建。这时要特别警惕：读取和写入共享同一个文件指针。因此写入操作会从之前读指针的位置起，向后覆盖原文件的内容。

Shell使用类似于`exec 3>&~`的语法来手动关闭文件描述符。

```shell
exec 3> log.txt # 重定向文件描述符3到log.txt
exec 3>&~       # 关闭文件描述符3
echo "test" >&3 # 报错: 3: Bad file descriptor
```

### §3.4.1 `lsof`

`lsof`命令展示了Linux打开的所有文件描述符。各列的含义分别为：

- `COMMAND`：进程对应文件名的前`9`个字符
- `PID`：进程`PID`
- `USER`：进程属主的用户名
- `FD`：文件描述符及其访问类型（`r`为读、`w`为写、`u`为读写）
- `TYPE`：文件类型（`CHR`为字符型、`BLK`为块型、`DIR`为目录、`REG`为常规文件）
- `DEVICE`：设备号（主设备号与从设备号）
- `SIZE`：文件大小
- `NODE`：本地文件的节点号
- `NAME`：文件路径

```shell
$ lsof
COMMAND      PID    TID TASKCMD               USER   FD      TYPE             DEVICE SIZE/OFF       NODE NAME
systemd        1                              root  cwd       DIR                8,2     4096          2 /
systemd        1                              root  rtd       DIR                8,2     4096          2 /
systemd        1                              root  txt       REG                8,2  1620224      14901 /usr/lib/systemd/systemd
```

### §3.4.2 `tee`

为了让程序的`STDOUT`输出流，同时重定向到屏幕`STDOUT`和文件，我们可以使用`tee <FILE>`命令实现流的复制。该命令会读取`STDIN`中的所有内容，将其同时写入`STDOUT`和`<FILE>`。

```shell
$ echo "[info]: login failed" | tee ./log.txt
	[info]: login failed
$ cat ./log.txt
	[info]: login failed
```

`tee`的默认写入方式是覆盖。我们可以使用`tee -a`选项将写入方式更改为追加。

### §3.4.3 Here Document

Here Document是Bash为内敛输入重定向符`<<`提供的一种语法糖。**只有Fish不支持该语法糖，Sh、Bash、Zsh均支持**。

```shell
cat << EOF
	随便一些文本
	不会被Shell当成命令执行
EOF # 不准在这一行的末尾加引号，即使有空格也不行！
```

实践中，Here Document经常与重定向输出流一起使用。

```shell
$ cat >> stdout.txt << EOF
    > Hello
    > World
    > EOF
$ cat stdout.txt
	Hello
	World
```

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

### §3.6.4 `test`

`test`只有在表达式为真时才返回退出状态码`0`。**这里的表达式可以包含数值、字符串和文件**。

```shell
$ test <EXP1> # 判定<EXP1>是否为空

# 比较数值
$ test <EXP1> -eq <EXP2> # ==
$ test <EXP1> -ge <EXP2> # >=
$ test <EXP1> -gt <EXP2> # >
$ test <EXP1> -le <EXP2> # <=
$ test <EXP1> -lt <EXP2> # <
$ test <EXP1> -ne <EXP2> # !=

# 比较字符串
$ test <STR1> =  <STR2> # ==
$ test <STR1> != <STR2> # !=
$ test <STR1> \<  <STR2> # <
$ test <STR1> \>  <STR2> # >
$ test -n <STR>         # 是否不为空串
$ test -z <STR>         # 是否为空串

# 比较文件
$ test -d <FILE> # 是否存在且是否为目录
$ test -e <FILE> # 是否存在
$ test -f <FILE> # 是否存在且是否为文件
$ test -r <FILE> # 是否存在且是否可读
$ test -s <FILE> # 是否存在且是否非空
$ test -w <FILE> # 是否存在且是否为可写
$ test -x <FILE> # 是否存在且是否为可执行
$ test -O <FILE> # 是否存在且属主是否为当前用户
$ test -G <FILE> # 是否存在且属组是否为当前用户组
$ test <FILE1> -nt <FILE1> # <FILE1>是否比<FILE2>新，需要保证文件存在
$ test <FILE1> -ot <FILE2> # <FILE1>是否比<FILE2>旧，需要保证文件存在
```

### §3.6.5 `(())`

双括号命令允许使用高级数学表达式（包括`test`涉及的所有关于数字的表达式），其语法为`(( <EXPRESSION> ))`。它支持以下命令：

```shell
$ (( $KEY++ )) # 后置++
$ (( $KEY-- )) # 后置--
$ (( ++$KEY )) # 前置++
$ (( --$KEY )) # 前置--
$ (( ! )) # 布尔反
$ (( ~ )) # 按位反
$ (( ** )) # 幂次
$ (( << )) # 左移
$ (( >> )) # 右移
$ (( & )) # 按位与
$ (( | )) # 按位或
$ (( && )) # 布尔与
$ (( || )) # 布尔或
$ (( == )) # 数字==
$ (( >= )) # 数字>=
$ (( > )) # 数字>
$ (( <= )) # 数字<=
$ (( <  )) # 数字<
$ (( != )) # 数字!=
```

**使用`(())`的数学表达式中的运算符，不必经过反斜杠进行转义**。

### §3.6.6 `[[]]`

双方括号支持了`test`涉及的所有关于字符串的表达式，其语法为`[[ <CONDITION> ]]`。除此之外，它的`==`运算符还支持通配符匹配。

```shell
$ if [[ abc == a* ]] ; then echo "matched" ; fi
	matched
```

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

开发者可以自定义退出状态码，不一定遵循上述规范。以下是一张约定俗成的退出状态码含义表：

| 退出状态码   | 含义                                          |
| ------- | ------------------------------------------- |
| `0`     | 命令执行成功                                      |
| `1`     | 一般性位置错误                                     |
| `2`     | 非法Shell命令                                   |
| `126`   | 命令无法执行                                      |
| `127`   | 未找到命令                                       |
| `128`   | 无效的退出参数                                     |
| `128+x` | 与Linux信号`x`相关的错误，例如`130`表示通过`Ctrl + C`终止的命令 |

### §3.7.1 `exit`

默认情况下，Shell脚本的退出状态码，就是脚本中最后一个命令的退出状态码。我们可以使用`exit <CODE>`自定义退出状态码。

```shell
$ cat ./script.sh
	exit 123;
$ bash ./script.sh
$ echo $?
	123
```

## §3.8 流程控制语句

### §3.8.1 `if-then`

`if-then`语句的基本结构为：

```shell
# 第一种写法，给then换行，命令不必以分号结尾
if <COMMAND>
then
	<COMMAND>+
fi

# 第二种写法，
if <COMMAND> ; then
	<COMMAND>+
fi
```

如果`<COMMAND>`的退出状态码为`0`，则判定为真。

### §3.8.2 `if-then-else`

```shell
if <COMMAND> ; then
	<COMMAND>+
else
	<COMMAND>+
fi
```

### §3.8.3 `if-then-elif`

```shell
if <COMMAND> ; then
	<COMMAND>+
elif <COMMAND> ; them
	<COMMAND>+
fi
```

### §3.8.4 `[]`

我们知道`if`只能判定退出状态码是否为`0`，而`test`用于将表达式转化为退出状态码，从而实现更丰富的`if`判定条件。

Bash为`test`提供了一种语法糖：`[<CONDITION>]`。其中的运算符如果被占用（例如`>`同时表示大于和重定向），则需要使用反斜杠进行转义。

```shell
$ cat ./condition.sh
	#!bash
	if [ 2 -ge 1 ] ; then
	    echo "2 > 1"
	fi
	
	if [ "abc" \< "def" ] ; then
	    echo "abc < def"
	fi

$ bash ./condition.sh
	2 > 1
	abc < def
```

### §3.8.5 `&&`/`||`

`&&`和`||`用于连接两个条件，使其组成复合条件。

```shell
$ if [ 1 -eq 1 ] && [ 2 -eq 2 ] ; then echo "1 == 1 && 2 == 2" ; fi
	1 == 1 && 2 == 2
```

### §3.8.6 `case`

`case-esac`的语法比较特殊：

```shell
case <VARIABLE> in (<PATTERN> | )+ \)
	<COMMANDS>;; # 必须在最后一行命令使用两个分号
(<PATTERN> | )+ \)
	<COMMANDS>;; # 必须在最后一行命令使用两个分号
(<PATTERN> | )+ \)
	<COMMANDS>;; # 必须在最后一行命令使用两个分号
esac
```

下面的脚本展示了如何检测当前运行的Shell：

```shell
nixos@nixos ~> cat script.sh
shell_name=$(ps -p $$ -o comm=)
case $shell_name in
    sh )
        echo "You are using outdated shell! :(" ;;
    bash )
        echo "You are using normal shell! :P" ;;
    zsh | fish )
        echo "You are using fashion shell! :)" ;;
    * )
        echo "You are using unknown shell! :o" ;;
esac

nixos@nixos ~> bash ./script.sh
You are using normal shell! :P
nixos@nixos ~> zsh ./script.sh
You are using fashion shell! :)
nixos@nixos ~> sh ./script.sh
You are using outdated shell! :(
```

### §3.8.7 `for`

#### §3.8.7.1 `for-in`

```shell
for <VARIABLE> in <LIST>
do
	<COMMANDS>;
done

for <VARIABLE> in <LIST> ; do
	<COMMANDS>;
done
```

```shell
$ cat script.sh
	for str in alice bob carol david ; do
	    echo "$str" ;
	done
$ bash script.sh
	alice
	bob
	carol
	david
```

如果列表中的元素出现单引号，则Shell将会令"出现单引号"的配对元素之间的所有元素视为一个整体，并去除单引号。

```shell
$ cat script.sh
	for str in alice bo'b carol dav'id elien ; do
	    echo "$str" ;
	done
$ bash script.sh
	alice
	bob carol david
	elien
```

我们可以使用转义字符来强制表示单引号字符：

```shell
nixos@nixos ~> cat script.sh
	for str in alice bo\'b carol dav\'id elien ; do
	    echo "$str" ;
	done
nixos@nixos ~> bash script.sh
	alice
	bo'b
	carol
	dav'id
	elien
```

或者使用双引号包裹：

```shell
nixos@nixos ~> cat script.sh
	for str in alice "bo'b" carol "dav'id" elien ; do
	    echo "$str" ;
	done
nixos@nixos ~> bash script.sh
	alice
	bo'b
	carol
	dav'id
	elien
```

这里的`<LIST>`还可以来自于命令的输出：

```shell
$ cat script.sh
	files=$(ls);
	files=$files" End";
	for str in $files; do
	    echo "$str" ;
	done
$ bash script.sh
	script.sh
	End
```

Shell使用`$IFS`（内部字段分隔符，`Internal Field Separator`）来解析字段的分隔符。默认情况下，`$IFS`的值为`" \t\n"`，也就是说Shell会**同时**将空格、制表符、换行符作为分隔符。在脚本中，我们经常会更改`IFS="\n"`，避免列表中的空格字符干扰。

```shell
$ printf "$IFS" | hexdump -v -C
	00000000  0a 20 09                                          |. .|
	00000003
$ cat data.txt
	Alice like apple
	Bob like banana
$ cat script.sh
	IFS=$'\n';
	for str in $(cat ./data.txt); do
	    echo "$str" ;
	done
$ bash script.sh
	Alice like apple
	Bob like banana
```

#### §3.8.7.2 C语言风格`for`

```shell
for (( <VARIABLE_ASSIGNMENT> ; <CONTIDITION> ; <ITERRATION_PROCESS> )) do
	<COMMANDS>;
done
```

Bash提供了以下语法糖，使其更贴近C语言的`for`语句：

1. 变量赋值`<VARIABLE_ASSIGNMENT>`允许在`=`的两边添加空格。
2. 迭代条件`<CONDITION>`引用变量值时，不必在变量名之前添加`$`。
3. 迭代条件`<CONDITION>`可以直接调用运算符，不必使用`expr`。

```shell
$ cat script.sh
	# 可以换成i = 1，可以换成i <= 3
	for (( i=1, j = 1 ; $i <= 3; ++i, --j )) do
	    printf "Iteration: #%d\n" $i;
	done
$ bash script.sh
	Iteration: #1
	Iteration: #2
	Iteration: #3
```

### §3.8.8 `while`

`while`语句依赖于循环条件的状态退出状态码：只有当`<TEST_COMMANDS>`的退出状态码不为`0`时，才会退出循环。

```shell
while <TEST_COMMANDS>; do
	<COMMANDS>;
done
```

```shell
$ cat script.sh
	number=3;
	while [ $number -ge 0 ]; do
	    echo "number: $number";
	    number=$[ $number - 1 ];
	done
$ bash script.sh
	number: 3
	number: 2
	number: 1
	number: 0
```

事实上，如果`<TEST_COMMANDS>`由多行命令构成（由`\n`或`;`分隔），则这个整体的退出状态码就是最后一个命令的退出状态码。

```shell
$ cat script.sh
	number=3;
	while echo "number: $number"; [ $number -ge 1 ]; do
	    number=$[ $number - 1 ];
	done
$ bash script.sh
	number: 3
	number: 2
	number: 1
	number: 0
```

### §3.8.9 `until`

`until`与`while`完全相反——只有当`<TEST_COMMANDS>`的退出状态码为`0`时，才会退出循环。

```shell
until <TEST_COMMANDS>; do
	<COMMANDS>;
done
```

```shell
$ cat script.sh
	number=3;
	until [ $number -le 0 ]; do
	    number=$[ $number - 1 ];
	    echo "number: $number";
	done
$ bash script.sh
	number: 2
	number: 1
	number: 0
```

### §3.8.10 `break`与`continue`

`break <N>?`和`continue <N>?`分别用于跳出单层循环（`<N>`层循环）和单次循环（`<N>`层单次循环）。

```shell
$ cat script.sh
for (( i = 1 ; i < 3 ; ++i )) do
    echo -e "enter i = $i";
    for (( j = 1 ; j < 3 ; ++j )) do
        echo -e "\tenter j = $j";
        for (( k = 1 ; k < 3 ; ++k )) do
            echo -e "\t\tenter k = $k";
            if [ $i -eq 2 ] && [ $j -eq 1 ] && [ $k -eq 1 ]; then
                echo -e "\t\tcontinue 2, 不执行i=2,j=1,k=2";
                continue 2;
            fi
            echo -e "\t\tquit k = $k";
        done
        echo -e "\tquit j = $j";
    done
    echo -e "quit i = $i";
done

$ bash script.sh
enter i = 1
        enter j = 1
                enter k = 1
                quit k = 1
                enter k = 2
                quit k = 2
        quit j = 1
        enter j = 2
                enter k = 1
                quit k = 1
                enter k = 2
                quit k = 2
        quit j = 2
quit i = 1
enter i = 2
        enter j = 1
                enter k = 1
                continue 2, 不执行i=2,j=1,k=2
        enter j = 2
                enter k = 1
                quit k = 1
                enter k = 2
                quit k = 2
        quit j = 2
quit i = 2
```

### §3.8.11 循环流重定向

在上述各种循环的`done`后面，可以接入**流重定向**或**管道**，将循环体内各个语句产生的流汇总起来。**既可以接入输入流，也可以接入输出流**。

```shell
$ cat script.sh
	for (( i = 1 ; i <= 4 ; ++i )) do
	    for (( j = 1 ; j <= 4 ; ++j )) do
	        echo "$[ $i * $j] = $i * $j";
	    done
	done | sort --numeric-sort
$ bash script.sh
	1 = 1 * 1
	2 = 1 * 2
	2 = 2 * 1
	3 = 1 * 3
	3 = 3 * 1
	4 = 1 * 4
	4 = 2 * 2
	4 = 4 * 1
	6 = 2 * 3
	6 = 3 * 2
	8 = 2 * 4
	8 = 4 * 2
	9 = 3 * 3
	12 = 3 * 4
	12 = 4 * 3
	16 = 4 * 4
```

## §3.9 参数输入

### §3.9.1 `$<NUMBER>`

位置参数的变量名都是数字，其中`$0`表示脚本名、`$1`及之后的变量均为位置参数值，以此类推，直到`$9`，再往后的位置变量需要用`${数字}`的形式来引用。

```shell
$ cat script.sh
	echo $0;
	echo $1;
	echo $2;
	echo $3;
$ bash script.sh 123 abc "+-*/"
	script.sh
	123
	abc
	+-*/
```

需要警惕的是：`$0`本质上代表了脚本文件的路径，并不一定总是脚本文件名。我们可以使用`basename`命令对路径做处理，得到想要的脚本文件名：

```shell
$ cat script.sh
	echo "\$0 is $0, basename \$0 is `basename $0`";
$ bash script.sh
	$0 is script.sh, basename $0 is script.sh
$ bash ~/script.sh
	$0 is /home/nixos/script.sh, basename $0 is script.sh
$ ~> bash ./script.sh
	$0 is ./script.sh, basename $0 is script.sh
```

### §3.9.2 `$#`

`$#`表示传入的参数数量。这个数字从`0`开始数，不包括脚本文件名`$0`。要获取第`i`个参数，我们需要用`${<VALUE>}`语法，并且`<VALUE>`中引用变量值时，需要使用`#<KEY>`，而不是`$<KEY>`。

```shell
$ cat script.sh
	echo "传入了$#个参数";
	for (( i = 1 ; i <= $# ; ++i )) do
	    echo "第$i个参数的值为: ${!i}";
	done
$ bash ./script.sh 123 456
	传入了2个参数
	第1个参数的值为: 123
	第2个参数的值为: 456
```

### §3.9.3 `$*`与`$@`

`$*`和`$@`两个变量均储存了所有的命令行参数信息。其中`$*`将所有参数视为一个字符串，而`$@`将所有参数按`$IFS`分隔成若干字段。

```shell
$ cat script.sh
	for str in "$*"; do
	    echo $str;
	done
$ bash ./script.sh 123 456
	123 456

$ cat script.sh
	for str in $@; do
	    echo $str;
	done
$ bash ./script.sh 123 456
	123
	456
```

### §3.9.4 `shift`

`shift`用于将命令行参数的值向左移动一格：`$0`保持不变，`$1`的值被替换为`$2`的值，`$2`的值被替换为`$3`的值，以此类推。因此我们可以将其视为队列的`queue.pop_front()`，我们可以通过`$1`不断地获取`queue.top()`。

```shell
$ cat script.sh
	i=0;
	while [ -n "$1" ] ; do
	    i=$[ $i + 1 ];
	    echo "第$i个参数的值为$1";
	    shift;
	done
$ bash ./script.sh 123 456
	第1个参数的值为123
	第2个参数的值为456
```

`shift <STEP_NUMBER>`允许一次性执行`<STEP_NUMBER>`次`queue.pop_front()`，从而方便地跳过不需要的值。

### §3.9.5 `getopt`

有些脚本支持选项和参数一起使用。一种简便的实现方式是将它们都视为参数，然后利用`shift`一直读队头。

```shell
$ cat script.sh
	i=0;
	while [ -n "$1" ] ; do
	    case "$1" in
	        -a )
	            echo "Option -a detected";
	            shift;;
	        -d | --dir )
	            echo "Option -d get value of $2"
	            shift 2;;
	        * )
	            i=$[ $i + 1 ];
	            echo "Param of #$i is $1";
	            shift 1;;
	    esac
	done
$ bash ./script.sh -a --dir ./folder file_1 file_2
	Option -a detected
	Option -d get value of ./folder
	Param of #1 is file_1
	Param of #2 is file_2
```

这种方式缺乏灵活性，且不易维护，尤其是当出现`ls -la`需要解析成`ls -l -a`的情景。Shell为此提供了`getopt <OPTION_DEFINE> <PARAMETERS>`命令。我们以下面的命令为例：

```shell
$ getopt abcd:e: -a -d d_value -bc -e e_value
	 -a -d d_value -b -c -e e_value --
```

`<OPTION_DEFINE>`使用定义了一系列单字母选项，**前面没有`：`紧跟的**字母代表一个无参数选项，**紧跟在`:`前面的**单字母代表一个有参数选项。我们将`"$@"`字符串传给脚本中的`opt`悬心爱过，它会将选项和参数用`--`分离，便于后续脚本手动解析。为了防止传入未知选项，但是`getopt`输出报错信息，工程上经常使用`getopt -q`选项屏蔽报错。

`set -- <变量>`允许使用给定变量的值替代位置变量。这里我们将`getopt`得到的结果送给`set --`即可。

```shell
$ cat script.sh
	set -- $(getopt -q abcd:e: "$@");
	echo $@;
	while [ -n "$1" ] ; do
	    case "$1" in
	        -a | -b | -c )
	            echo "Option $1 detected";
	            shift;;
	        -d | -e )
	            echo "Option $1 is $2";
	            shift 2;;
	        -- )
	            shift;;
	        * )
	            echo "Param: $1";
	            exit 1;;
	    esac
	done
~ bash ./script.sh -l -d ./folder -a -e ./newfile -bc
	-d './folder' -a -e './newfile' -b -c --
	Option -d is './folder'
	Option -a detected
	Option -e is './newfile'
	Option -b detected
	Option -c detected
```

**需要注意的是：`getopt`命令不擅长处理带有`$IFS`的变量值，即使这部分值用双引号包裹也不行**。例如`-m "abc efg"`不会被单独当作一个带参数的选项，而是会被当成一个带参数的选项`-m 'abc`和另一个参数`efg‘`。所以`getopt`仍然具有相当大的局限性。

### §3.9.6 `getopts`

**只有Bash提供了`getopts`**，它是`getopt`的升级版。它的输出不再是单一的字符串，而是可以与Shell脚本位置变量联系密切的值。其语法与`getopt`完全一致，但是在使用上有所差别。

`getopts`封装了三个局部变量供Shell使用：

- `$opt`表示当前读取到的选项，不包含前导横杠`-`、
- `$OPTARG`表示当前选项对应的值。如果定义选项带有参数，则缺省为字符`?`。
- `$OPTIND`表示解析完当前选项后，下一个未解析的字段在第几个位置上（初始值为`1`，解析单个选项或单个参数都会自增`1`）。工程上经常使用`shift $[ $OPTIND - 1 ]`，将`$1`切换到第一个参数的位置上。

```shell
$ cat script.sh
	while getopts ab:c opt ; do
	    case "$opt" in
	        a )
	            echo "Option -a detected";;
	        b )
	            echo "Option -b detected, its value is $OPTARG";;
	        c )
	            echo "Option -c detected";;
	        * )
	            echo "Unknown option: $opt";;
	    esac
	done
	shift $[ $OPTIND - 1 ];
	i=0;
	for param in "$@"; do
	    i=$[ $i + 1 ];
	    echo "Param #$i is $param";
	done
$ bash ./script.sh -b abc -ac
	Option -b detected, its value is abc
	Option -a detected
	Option -c detected
	Param #1 is param1
	Param #2 is param2
```

`getopts`能解决`getopt`的`$IFS`分隔符问题。例如对于`-m "abc efg"`的解析完全正确。事实上，`getopts`允许在选项和值之间不添加空格，例如`g++ -Ddebug`就等价于`g++ -D debug`。

### §3.9.7 `read`

`read <VARIABLE>`用于让`STDIN`陷入阻塞，等待用户输入，最后将输入值存储到`$<VARIABLE>`变量中。

```shell
$ cat script.sh
	echo -n "Enter your name: ";
	read name;
	echo "Hello, $name!";
$ bash ./script.sh
	Enter your name: Yaner
	Hello, Yaner!
```

事实上，`read`也提供了`-p <PROMPT>`选项，能够等效地实现上述效果：

```shell
$ cat script.sh
	read -p "Enter your name: " name;
	echo "Hello, $name!";
$ bash ./script.sh
	Enter your name: Yaner
	Hello, Yaner!
```

`read`支持读入一次性读入多个变量。用户在`STDIN`中输入的值会按照`$IFS`进行分隔，以此赋给变量列表。最后一个变量会获得`STDIN`剩余的所有值。

```shell
$ cat script.sh
	read -p "Enter your name, gender and address: " name gender address;
	echo "Hello, $name!";
	echo "Your gender is $gender";
	echo "Your address is $address";
~ bash ./script.sh
	Enter your name, gender and address: Yaner Male Asia, China
	Hello, Yaner!
	Your gender is Male
	Your address is Asia, China
```

当`read`的变量列表缺省时，它会向`$REPLY`中写入。

```shell
~ cat script.sh
	echo "我是复读机.";
	read -p "请输入第一句你想说的话: ";
	echo "$REPLY";
	read -p "请输入第二句你想说的话: " text2;
	echo "$text2";
~ bash ./script.sh
	我是复读机.
	请输入第一句你想说的话: Hello
	Hello
	请输入第二句你想说的话: World
	World
```

`read -t <SECONDS>`选项规定了用户输入的限时（单位为秒）。

```shell
$ cat script.sh
	read -t 3 -p "请输入答案(限时3秒): 1 + 1 = " answer;
	if [ -z "$answer" ] ; then
	    echo -e "\n你没有输入答案 :(";
	elif [ "$answer" -eq 2 ]; then
	    echo "回答正确 :)";
	else
	    echo "回答错误 :(";
	fi
$ bash ./script.sh
	请输入答案(限时3秒): 1 + 1 =
	你没有输入答案 :(
$ bash ./script.sh
	请输入答案(限时3秒): 1 + 1 = 2
	回答正确 :)
$ bash ./script.sh
	请输入答案(限时3秒): 1 + 1 = 3
	回答错误 :(
```

`read -s`用于将`STDIN`输入的字符设置成与终端背景色一样的颜色，从而变相实现隐藏输入的效果。

`read`每次读取一行。如果是空行则返回非零退出状态码。利用这一点，我们可以使用管道将文件重定向到`read`的`STDIN`，并且用`while read`循环实现逐行读取：

```shell
$ cat data.txt
	Alice
	Bob
	Carol
	David
$ cat script.sh
	i=0
	cat $1 | while read line; do
	    i=$[ $i + 1 ];
	    echo "Line #$i: $line";
	done
$ bash ./script.sh ./data.txt
	Line #1: Alice
	Line #2: Bob
	Line #3: Carol
	Line #4: David
```

### §3.9.8 `select`

`select`命令为CLI提供了方便的菜单控件模版。`select`本身就是一种循环结构，开发者将菜单选项字符串列表传入`select <VARIABLE> in`的参数列表中，就能循环地无限输入，知道遇到`break`语句为止。

```shell
$ cat script.sh
	PS3="Input your option (1~4): "
	select option in "du" "df" "lsblk" "quit";
	do
	    case $option in
	        "du" )
	            echo `du -h`;;
	        "df" )
	            echo `df -h`;;
	        "lsblk" )
	            echo `lsblk`;;
	        "quit" )
	            break;;
	        * )
	            echo "Unknown option, try again!";;
	    esac
	done
$ bash script.sh
	1) du
	2) df
	3) lsblk
	4) quit
	Input your option (1~4): 3
	NAME MAJ:MIN RM SIZE RO TYPE MOUNTPOINTS sda 8:0 0 388.4M 1 disk sdb 8:16 0 1G 0 disk [SWAP] sdc 8:32 0 1T 0 disk /nix/store /mnt/wslg/distro /
Input your option (1~4): 4
```

### §3.9.9 `dialog`

`dialog`命令为CLI提供了输入框组件。大部分Linux发行版并不自带该命令，需要手动安装`dialog`软件包。

与HTML中的`<input type="<TYPE>">`标签类似，`dialog`提供了各种丰富的输入框。详见帮助文档，本节略。

## §3.10 临时文件

### §3.10.1 `mktemp`

`mktemp`本质上是一个能按照文件名掩码`X`，创建随机文件名的`touch`，并输出文件路径到`STDOUT`和`$tempfile`中。

```shell
~ mktemp -t log_XXXXXX.txt
	/tmp/log_sGnaIW.txt
~ ls -l /tmp/log_*.txt
	-rw------- 1 nixos users 0 Nov 25 07:23 /tmp/log_sGnaIW.txt
```

使用`-t`将临时文件创建在`/tmp`目录下。

使用`-d`创建目录，并输出文件夹路径到`STDOUT`和`$tempdir`。

## §3.11 计划任务

### §3.11.1 `at`/`atq`/`atrm`

`at`命令用于指定作业任务何时运行。后台运行的守护进程`atd`会每隔`60`秒，扫描一遍目录`/var/spool/at`或`/var/spool/cron/atjobs`，如果其中存在与当前之间一致的作业，则立刻执行该作业。**`at`并不是GNU标准的一部分，因此需要额外安装这个名为`at`的软件包**。

`at [-f <FILE>]? <TIME>`可以从`STDIN`或`<FILE>`中读取要执行的命令，并打包成一个计划任务。这里的`<TIME>`支持多种格式，格式文档在`/usr/share/doc/at/timespec`：

- `HH:MM`：指定小时和分钟（24小时制），例如`10:15`。
- `HH:MM AM/PM`：指定小时和分钟（12小时制），例如`10:15 AM`。
- `<英文时间名词>`：例如`now`、`noon`、`midnight`、`teatime`（`16:00`）。
- `MMDDYY`/`MM/DD/YY`/`DD.MM.YY`：指定年份、月份和日期。
- `<三字母月份缩写> DD`：指定月份和日期，例如`July 7`。
- `<时间增量>`：例如`Now + 25 minutes`、`10:15 tomorrow`、`10:15 + 7 days`（不支持`seconds`）。

`at`规定了52种作业队列，每个队列的名称由`[a-zA-z]`的单字母命名。队列名称的字典序越大，则谦让度越高，执行优先级越低。具体的队列使用`at -q <QUEUE_NAME>`指定，缺省值为`a`。

默认情况下，Linux会将作业的`STDOUT`和`STDERR`通过`sendmail`命令，使用邮件系统发送给作业属主的邮箱地址。如果没有安装并配置`sendmail`，则作业的输出信息会丢失。所以实践中，我们经常对作业的`STDOUT`和`STDERR`重定向到某个文件。特殊地，使用`at -M`选项可以禁止作业输出信息。

`atq`用于查看所有计划任务。`atrm <TASK_NO>`用于删除作业编号为`<TASK_NO>`的计划任务。

```shell
$ at -f ./script.sh now + 5 minutes
	warning: commands will be executed using /bin/sh
	job 4 at Mon Nov 25 14:20:00 2024
$ atq
	1       Mon Nov 25 14:19:00 2024 a nixos
	2       Mon Nov 25 14:20:00 2024 a nixos
$ atrm 1
	2       Mon Nov 25 14:20:00 2024 a nixos
```

### §3.11.2 `cron`/`crontab`

`cron`读取一个叫做时间表的文件，从而创建任务。每一行都代表这一个任务，它的格式是：

```crontab
<MINUTE_PAST_HOUR> <HOUR_OF_DAY> <DAY_OF_MONTH> <MONTH> <DAY_OF_WEEK> <COMMAND>
```

- `<MINUTE_PAST_HOUR>`指示每个小时中的哪个分钟时刻，取值范围为`[0, 59]`，其中`*`表示全部。
- `<HOUR_OF_DAY>`指示每天中的哪个小时时刻，取值范围为`[0, 23]`，其中`*`表示全部。
- `<DAY_OF_MONTH>`指示每个月中的哪一天，取值范围为`[1, 28/29/30/31]`，其中`*`表示全部。
- `<MONTH>`指示每年中的那一个月，取值范围为`[1, 12]`，其中`*`表示全部。
- `<DAY_OF_WEEK>`表示每周中的哪一个星期，取值范围为`[0, 7]`或`[mon, sun]`，其中`*`表示全部，`0`或`7`都表示星期日。

`crontab`提供了修改时间表的CLI接口。它本质上只是对时间表的位置做了一个封装，本身并没有提供任何修改时间表的功能。

## §3.12 函数

Bash提供了两种定义函数的方式：

```shell
function <FUNCTION_NAME> {
	<COMMANDS>;
}
<FUNCTION_NAME>() {
	<COMMANDS>;
}
```

调用函数就像调用命令一样：

```shell
$ cat script.sh
	function print_hello() {
	    echo "Hello!";
	}
	print_hello;
$ bash script.sh
	Hello!
```

**函数必须先声明后调用**。**同名函数可以先后覆盖，而且不会有任何报错和提示**。

### §3.12.1 `return`

既然我们可以把函数视为命令，那么函数本身也可以有自己的退出状态码，缺省时为函数体内最后一个命令的退出状态码。我们需要在调用函数后马上读取`$?`，才能获取函数的退出状态码。

默认情况下，函数体内允许使用`return <EXIT_CODE>`命令，手动指定退出状态码，可以视为函数的返回值。**这会带来一个限制：函数返回值的取值范围和退出状态码一样，都是`uint8`**。

```shell
$ cat script.sh
	function multiply_times_2 {
	    echo "Input a nnumber: ";
	    read value;
	    return $[ $value * 2 ];
	}
	multiply_times_2;
	echo $?;
$ bash script.sh # 结果正确
	Input a nnumber:
	123
	246
$ bash script.sh # 结果错误
	Input a nnumber:
	1000
	208
```

### §3.12.2 函数输出

前文提到，`return`语句只能返回`uint8`的值。如果要获取函数体内某个运算结果的值，我们只能采取一种曲线救国的方式：使用`$(<FUNCTION_NAME>)`获取函数的`STDOUT`，将其储存到某个变量中。**在这种情况下，我们必须保证`STDOUT`不得混入其它命令的输出**。例如`echo`会扰乱`STDOUT`的输出，但是`read -p <PROMPT>`就不会输出到`STDOUT`，而是直接显示到屏幕上。

```shell
$ cat script.sh
	function multiply_times_2 {
	    read -p "Input a number: " value;
	    echo $[ $value * 2 ];
	}
	result=$(multiply_times_2);
	echo "$result";
$ bash script.sh
	Input a number: 1000
	2000
```

### §3.12.3 函数传参

既然我们可以把函数视为命令，那么函数本身也可以像CLI命令那样传递选项和参数。

```shell
$ cat script.sh
	function multiply {
	    if [ -z $1 ] || [ -z $2 ] ; then
	        echo "Error Params!" >&2;
	        return 1;
	    fi
	    echo $[ $1 * $2 ];
	}
	
	echo "call multiply";
	echo $(multiply);
	
	echo "call multiply 2 3";
	echo $(multiply 2 3);
$ bash script.sh
	call multiply
	Error Params!

	call multiply 2 3
	6
```

函数体内所有使用`<KEY>=<VALUE>`定义的变量，都是**全局变量**，这意味着它们在函数体外也能被引用。然而这样容易导致函数内外出现重名的变量，导致变量值被更改。实践中更推荐使用**局部变量**，语法为`local <KEY>=<VALUE>`。

对于数组变量而言，我们传参的方式永远都是在调用处现场解包，再在函数体内使用`echo "$@"`现场打包。

```shell
$ [127]> cat script.sh
	function array_function {
	    local array_temp=($(echo "$@"));
	    echo "array_function() get the array: ${array_temp[*]}";
	}
	array=(1 2 3 4 5);
	echo "origin array is ${array[*]}";
	array_function ${array[*]};
$ bash script.sh
	origin array is 1 2 3 4 5
	array_function() get the array: 1 2 3 4 5
```

使用同样的思路，我们也可以将函数返回的`STDOUT`重新打包成数组变量。

```shell
$ cat script.sh
	function array_function {
	    local array_temp=(1 2 3 4 5);
	    echo ${array_temp[*]};
	}
	result=($(array_function));
	echo "array_function return: ${result[*]}";
$ bash script.sh
	array_function return: 1 2 3 4 5
```