# §1 Namespace与Cgroups

Namespace是Linux内核引入的隔离功能。

| Namespace类型 | Flag标识符           | Flag值        | 作用                                 |
| ----------- | ----------------- | ------------ | ---------------------------------- |
| Mount       | `CLONE_NEWNS`     | `0x00020000` | 隔离文件系统                             |
| Cgroup      | `CLONE_NEWCGROUP` | `0x02000000` |                                    |
| UTS         | `CLONE_NEWUTS`    | `0x04000000` | 隔离nodename和domainname              |
| IPC         | `CLONE_NEWIPC`    | `0x08000000` | 隔离System V IPC和POSIX message queue |
| User        | `CLONE_NEWUSER`   | `0x10000000` | 隔离UID和GID                          |
| PID         | `CLONE_NEWPID`    | `0x20000000` | 隔离PID                              |
| Network     | `CLONE_NEWNET`    | `0x40000000` | 隔离网络设备、IP地址、端口号                    |
| Time        | `CLONE_NEWTIME`   | `0x00000080` | 隔离时间                               |

```go
package main
import (
	"log"
	"os"
	"os/exec"
	"syscall"
)
func main() {
	cmd := exec.Command("sh")
	cmd.SysProcAttr = &syscall.SysProcAttr{
		Cloneflags: syscall.CLONE_NEWUTS | syscall.CLONE_NEWIPC | syscall.CLONE_NEWPID | syscall.CLONE_NEWNS | syscall.CLONE_NEWUSER | syscall.CLONE_NEWNET,
	}
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	err := cmd.Run()
	if err != nil { log.Fatal(err) }
	os.Exit(0)
}
```

```shell
$ go run main.go
	sh-5.2$ id
		uid=65534(nobody) gid=65534(nogroup) 组=65534(nogroup)
	sh-5.2$ ifconfig
```

Linux提供了Cgroups，用于限制指定若干进程的资源限额（例如CPU、内存、存储、网络等）。一个Cgroups由若干进程与Subsystem实例构成。

| Subsystem名称 | 作用           |
| ----------- | ------------ |
| `blkio`     | 管理块设备I/O访问控制 |
| `cpu`       | 管理CPU调度策略    |
| `cpuacct`   | 统计CPU占用      |
| `cpuset`    | 管理多核CPU限额    |
| `devices`   | 管理设备访问       |
| `freezer`   | 管理进程的挂起与恢复   |
| `memory`    | 管理内存限额       |
| `net_cls`   | 分类网络包        |
| `net_prio`  | 管理网络包优先级     |
| `ns`        | 管理Namespace  |

使用`lssubsys -a`查看Linux内核支持的所有Subsystem。该命令行工具可安装自`apt install cgroup-bin`或`nix-shell -p libcgroup`。

```shell
$ lssubsys -a
	cpu
	cpuacct
	blkio
	devices
	freezer
	net_cls
	perf_event
	net_prio
	hugetlb
	pids
	rdma
	misc
	debug
```