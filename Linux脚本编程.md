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

