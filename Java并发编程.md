参考文献：

- [《图解Java并发编程》](https://book.douban.com/subject/35634953/)

# §1 线程

Java使用`java.lang.Runnable`接口表示线程的行为，同时提供了该接口的一个实现类`java.lang.Thread`表示线程。因此，我们有两种定义线程的方式：

1. 继承`java.lang.Thread`类，并覆盖`void run()`方法。
2. 实现`java.lang.Runnable`接口，实现`void run()`方法，作为实参传入到`Thread()`的构造函数中。

```java
class MyThread1 extends Thread {  
    @Override  
    public void run() {  
        System.out.printf("[MyThread1] %s is running.\n", Thread.currentThread().getName());  
    }  
}  
  
class MyThread2 implements Runnable {  
    @Override  
    public void run() {  
        System.out.printf("[MyThread2] %s is running.\n", Thread.currentThread().getName());  
    }  
}  
  
public class JucMain {  
    public static void main(String[] args) {  
        System.out.printf("[JucMain] %s is running.\n", Thread.currentThread().getName());  
        new MyThread1().start();  
        new Thread(new MyThread2()).start();  
    }  
}
/*
	[JucMain] main is running.
	[MyThread1] Thread-0 is running.
	[MyThread2] Thread-1 is running.
*/
```

JVM对线程的抽象如下图所示：

```mermaid
graph LR
	A["java.lang.Thread<br/>Java class"]
		--> B["JavaThread<br/>JVM C++ class"] 
		--> C["OSThread<br/>JVM C++ class"]
		--> D["pthread<br/>C library"]
		--> E["内核线程<br/>Linux"]
```

## §1.1 线程状态

Java将线程的状态分为以下六种：

```java
public enum java.lang.Thread::State {
	NEW, /* NEW类别 */
	RUNNABLE, /* RUNNABLE类别和RUNNING类别 */
	BLOCKED, WAITING, TIMED_WAITING, /* NOT RUNNABLE类别 */
	TERMINATED; /* TERMINATED类别 */
}
```

1. `NEW`：新建状态。线程被创建但未启动。
2. `RUNNABLE`：可运行状态或运行状态。可运行状态表示线程被放入线程池中，等待CPU执行；运行状态表示线程正在运行。Java将`RUNNABLE`和`RUNNING`统称为`RUNNABLE`，**这是因为Java层无法感知线程处于两种状态的哪一种**。
3. `BLOCKED`：阻塞状态。线程被`synchronized`锁阻塞，放弃分配CPU并进入等待队列。例如I/O、主动睡眠、锁竞争等情况。
4. `WAITING`：等待状态。线程释放对象锁并进入等待队列。
5. `TIMED_WAITING`：计时等待状态。线程释放对象锁并进入等待队列。
6. `TERMINATED`：死亡状态。线程正常结束或异常退出。

```mermaid
flowchart TB
	new["NEW"]
	runnable["RUNNABLE"]
	blocked["BLOCKED"]
	waiting["WAITING"]
	timed_waiting["TIMED_WAITING"]
	terminated["TERMINATED"]
	new --"Thread.start()"--> runnable
	runnable --"分到CPU"--> running --"Thread.yield()"--> runnable
	running --"正常/异常退出"--> terminated
	running --"Object.wait()<br/>Thread.join()<br/>LockSupport.park()" --> waiting
	waiting --"LockSupport.unpark()" --> runnable
	running --"synchronized"--> blocked
	waiting --"Object.notify()<br/>Object.notifyAll()"--> blocked
	blocked --"锁被释放"--> runnable
	running --"Thread.sleep()<br/>Object.wait()<br/>Thread.join()<br/>LockSupport.parkNanos()<br/>LockSupport.parkUntil()"--> timed_waiting
	timed_waiting --"Object.notify()<br/>Object.notifyAll()"--> blocked
	timed_waiting --"睡眠结束<br/>LockSupport.unpark()"--> runnable
```

## §1.2 线程优先级

Java规定了线程的优先级范围`[1, 10]`，提供了优先级的相关常量。

```java
public class Thread implements Runnable {
	// ...
	public static final int MIN_PRIORITY = 1;  
	public static final int NORM_PRIORITY = 5;  
	public static final int MAX_PRIORITY = 10;
	// ...
}
```

JVM会根据平台规范映射到操作系统对应的优先级区间（例如[Windows的优先级范围](https://learn.microsoft.com/zh-cn/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreadpriority)是`{-15,-2,-1,0,1,2,15,65536,131072}`，[Linux的优先级范围](https://github.com/torvalds/linux/blob/155a3c003e555a7300d156a5252c004c392ec6b0/include/linux/sched.h#L1897-L1906)是`[-20,19]`）。具体来说，JVM会根据`java_to_os_priority`数组进行映射。以[OpenJDK](https://github.com/openjdk/jdk/blob/bf225c201f00f3a478b51c3cf045759b66899684/src/hotspot/os/linux/os_linux.cpp#L3949)为例：

```cpp
/* /jdk/src/hotspot/os/linux/os_linux.cpp */
int os::java_to_os_priority[CriticalPriority + 1] = {
	19,  // 0 Entry should never be used
	4,   // 1 MinPriority
	3,   // 2
	2,   // 3
	1,   // 4
	0,   // 5 NormPriority
	-1,  // 6
	-2,  // 7
	-3,  // 8
	-4,  // 9 NearMaxPriority
	-5,  // 10 MaxPriority
	-5   // 11 CriticalPriority
};

/* /jdk/src/hotspot/os/windows/os_windows.cpp */
int os::java_to_os_priority[CriticalPriority + 1] = {
    THREAD_PRIORITY_IDLE,          // 0  Entry should never be used
    THREAD_PRIORITY_LOWEST,        // 1  MinPriority
    THREAD_PRIORITY_LOWEST,        // 2
    THREAD_PRIORITY_BELOW_NORMAL,  // 3
    THREAD_PRIORITY_BELOW_NORMAL,  // 4
    THREAD_PRIORITY_NORMAL,        // 5  NormPriority
    THREAD_PRIORITY_NORMAL,        // 6
    THREAD_PRIORITY_ABOVE_NORMAL,  // 7
    THREAD_PRIORITY_ABOVE_NORMAL,  // 8
    THREAD_PRIORITY_HIGHEST,       // 9  NearMaxPriority
    THREAD_PRIORITY_HIGHEST,       // 10 MaxPriority
    THREAD_PRIORITY_HIGHEST        // 11 CriticalPriority
};
```

开发者可以读取和更改`Thread`的优先级：

```java
class MyThread extends Thread {
    @Override
    public void run() {
        int count = 0;
        for (int i = 0 ; i < 100000000; ++i) {
            ++count;
        }
        System.out.printf("[%s] Finished. Priority: %d\n", this.getName(), this.getPriority());
    }
}

public class JucMain {
    public static void main(String[] args) {
        Thread thread1 = new MyThread(); thread1.setPriority(Thread.MIN_PRIORITY);
        Thread thread2 = new MyThread(); // thread2.setPriority(Thread.NORM_PRIORITY);
        Thread thread3 = new MyThread(); thread3.setPriority(Thread.MAX_PRIORITY);
        thread1.start(); thread2.start(); thread3.start();
    }
}
/*
	[Thread-2] Finished. Priority: 10
	[Thread-0] Finished. Priority: 1
	[Thread-1] Finished. Priority: 5
*/
```

## §1.3 线程操作

### §1.3.1 谦让

`Thread.yield()`表示当前线程放弃CPU的使用权，并加入到队列末尾。

```java
public class JucMain {
    public static void main(String[] args) {
        Thread thread = new Thread(() -> {
            while (true) {
                System.out.println("yield cpu time");
                Thread.yield();
            }
        });
        thread.setDaemon(true);
        thread.start();
        
        for (int i = 0; i < 5; i++) {
            System.out.println("main thread");
        }
    }
} /* 可以观察到，当主线程输出时，子线程几乎不输出 */
```

### §1.3.2 睡眠

`Thread.sleep(long)`表示使得当前线程睡眠`long`毫秒时间。特殊地，传入`0`时等价于`Thread.yield()`。`Thread.sleep()`不会释放锁（但是`Object.wait()`会释放）：

```java
public class JucMain {
    public static void main(String[] args) {
        Object lock = new Object();

        Thread thread1 = new Thread(() -> {
            synchronized (lock) {
                System.out.printf("[%s] Get the lock.\n", Thread.currentThread().getName());
                try { Thread.sleep(1000); } catch (InterruptedException e) { e.printStackTrace(); }
                System.out.printf("[%s] Release the lock.\n", Thread.currentThread().getName());
            }
        });
        Thread thread2 = new  Thread(() -> {
            System.out.printf("[%s] Waiting for the lock...\n", Thread.currentThread().getName());
            synchronized (lock) {
                System.out.printf("[%s] Get the lock.\n", Thread.currentThread().getName());
            }
        });

        thread1.start();
        thread2.start();
    }
}
/*
	[Thread-0] Get the lock.
	[Thread-1] Waiting for the lock...
	[Thread-0] Release the lock.
	[Thread-1] Get the lock.
*/
```

### §1.3.3 中断

Java使用中断变量来实现中断机制，若该`bool`型中断变量为`true`，则线程抛出异常后进入异常处理逻辑作为中断入口。

以下是使用自定义中断变量模拟Java中断机制的一个伪代码例子：

```java
class MyThread extends Thread {  
    private volatile  boolean isInterrupted = false;  
    public void interrupt() {  
        isInterrupted = true;  
    }  
    public void run () {  
        while (!isInterrupted) {  
            Thread.yield();  
        }  
        System.out.printf("[%s] is interrupted.\n", Thread.currentThread().getName());  
    }  
}  
  
public class JucMain {  
    public static void main(String[] args) throws InterruptedException {  
        MyThread thread = new MyThread();  
        thread.start();  
  
        Thread.sleep(100);  
        thread.interrupt(); /* 执行后输出 [Thread-0] is interrupted. */
    }  
}
```

事实上，Java已经为我们提供了这个中断变量`interrupted`，以及相关中断触发函数：

```java
public class Thread implements Runnable {
	// ...
	volatile boolean interrupted;
	// ...
	public void interrupt() { /* Setter(设置为true)，并根据子线程进行后续操作 */
        interrupted = true;
        interrupt0();
        if (this != Thread.currentThread()) {
            Interruptible blocker;
            synchronized (interruptLock) {
                blocker = nioBlocker;
                if (blocker != null) {
                    blocker.interrupt(this);
                }
            }
            if (blocker != null) {
                blocker.postInterrupt();
            }
        }
    }
	public static boolean interrupted() { /* 先Getter再Setter(设置为false) */
	    return currentThread().getAndClearInterrupt();
	}
	public boolean isInterrupted() { /* Getter */
	    return interrupted;
	}
	final void setInterrupt() { /* Setter(设置为true) */
	    if (!interrupted) {
	        interrupted = true;
	        interrupt0();
	    }
	}
	final void clearInterrupt() { /* Setter(设置为false) */
	    if (interrupted) {
	        interrupted = false;
	        clearInterruptEvent();
	    }
	}
	boolean getAndClearInterrupt() { /* 先Getter再Setter(设置为false) */
	    boolean oldValue = interrupted;
	    if (oldValue) {
	        interrupted = false;
	        clearInterruptEvent();
	    }
	    return oldValue;
	}
}
```

#### §1.3.3.1 手工实现

对于`RUNNABLE`状态的线程，我们可以使用`while(!Thread.currentThread().isInterrupted())`循环监测是否触发中断：

```java
public class JucMain {
    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(() -> {
            while(!Thread.currentThread().isInterrupted()) {
                Thread.yield();
            }
            System.out.printf("[%s] is interrupted.\n", Thread.currentThread().getName());
        });
        thread.start();

        Thread.sleep(100);
        thread.interrupt(); /* 执行后输出 [Thread-0] is interrupted. */
    }
}
```

对于`BLOCKED`/`WAITING`/`TIMED_WAITING`状态的线程，我们可以捕获中断异常`java.lang.InterruptedException`来监测是否触发中断：

```java
public class JucMain {
    public static void main(String[] args) throws InterruptedException {
        Thread thread_join = new Thread(() -> {
            try {
                Thread.currentThread().join();
            } catch (InterruptedException e) {
                System.out.printf("[%s] is interrupted.\n", Thread.currentThread().getName());
            }
        });
        Thread thread_synchronized = new Thread(() -> {
            try {
                Object lock = new Object();
                synchronized (lock) {
                    lock.wait();
                }
            } catch (InterruptedException e) {
                System.out.printf("[%s] is interrupted.\n", Thread.currentThread().getName());
            }
        });

        thread_join.start(); thread_join.interrupt(); /* [Thread-0] is interrupted. */
        thread_synchronized.start(); thread_synchronized.interrupt(); /* [Thread-1] is interrupted. */
    }
}
```

综合以上两种情况，就是Java中的经典的手工中断实现方式：

```java
public class JucMain {
    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(() -> {
            while(!Thread.currentThread().isInterrupted()) {
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    System.out.printf("[%s] is interrupted during TIMED_WAITING state.\n", Thread.currentThread().getName());
                }
            }
            System.out.printf("[%s] is interrupted during RUNNING state.\n", Thread.currentThread().getName());
        });
        thread.start();
        // Thread.sleep(10); // 增加/不增加这一行，提高输出TIMED_WAITING/RUNNING的概率
        thread.interrupt();
    }
}
/*
	输出以下两种情况的某一种：
	[Thread-0] is interrupted during RUNNING state.
	[Thread-0] is interrupted during TIMED_WAITING state.
*/
```

#### §1.3.3.2 `LockSuppor.park()`实现

`java.util.concurrent.locks.LockSupport.park()`会让当前线程进入一种特殊的阻塞状态。在这种状态下，当前线程已经设置了中断变量，但是之后外界调用其`Thread.interrupt()`时不会触发`InterruptedException`异常，并使得当前线程切换回`RUNNABLE`状态，之后执行后续命令作为中断入口：

```java
public class JucMain {
    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(() -> {
            System.out.printf("[%s] is running\n", Thread.currentThread().getName());
            System.out.printf("[%s] is waiting by LockSupport.pork()\n", Thread.currentThread().getName());
            LockSupport.park();
            System.out.printf("[%s] is interrupted\n", Thread.currentThread().getName());
        });
        thread.start();
        Thread.sleep(10);
        thread.interrupt();
    }
}
/*
	[Thread-0] is running
	[Thread-0] is waiting by LockSupport.pork()
	[Thread-0] is interrupted
*/
```

### §1.3.4 阻塞与唤醒

阻塞与唤醒用于控制并发编程中的时序逻辑。考虑一种情景：我们使用`String message = null`变量在线程A和线程B之间共享数据，线程A负责写入，线程B负责读取。然而两个线程同时启动时，有可能出现线程B未写入的情况，这导致线程A读取到`null`值，引发预期外行为：

```java
public class JucMain {
    private static String message;
    public static void main(String[] args) throws InterruptedException {
        Thread thread_write = new Thread(() -> {
            message = "Hello World";
        });
        Thread thread_read = new Thread(() -> {
            System.out.printf("[%s] Read the message: %s\n", Thread.currentThread().getName(), message);
        });

        thread_read.start(); thread_write.start();
    }
}
```

这使得我们需要审慎地考虑时序逻辑。Java为此提供了多种阻塞与唤醒的机制。

#### §1.3.4.1 `Thread.suspend()/resume()`

`thread.suspend()`用于使线程陷入阻塞状态，`thread.resume()`用于使线程恢复运行状态。**这意味着一个线程调用自己的`resume()`陷入阻塞后，永远不能唤醒自己，必须由其他线程唤醒**。

针对上例，对于`Thread.suspend()`与`Thread.resume()`，我们可以对读线程加入非`null`判断，如果读到`null`，就用`Thread.suspend()`阻塞读线程自己；让写线程写入后调用读线程的`Thread.resume()`使其恢复运行：

```java
public class JucMain {
    private static volatile String message;
    private static Thread thread_write = new WriteThread();
    private static Thread thread_read = new ReadThread();
    static class WriteThread extends Thread {
        @Override
        public void run () {
            message = "Hello World";
            thread_read.resume();
        }
    }
    static class ReadThread extends Thread {
        @Override
        public void run () {
            if (message == null) {
                suspend();
            }
            System.out.printf("[%s] Read the message: %s\n", Thread.currentThread().getName(), message);
        }
    }
    public static void main(String[] args) throws InterruptedException {
        thread_read.start(); thread_write.start();
    }
}
```

该方法于Java 1.0被引入，于Java 1.2被移除。经实际工程证明，这种方案极易引发死锁问题。例如下面的伪代码——

```java
Thread thread = new Thread(() -> {
	while(true) {
		System.out.println("..."); /* 获取System.out同步锁 */
	}
});
thread.start();
thread.suspend(); /* 阻塞子线程，但是不释放子线程的锁 */
System.out.println("..."); /* 尝试获取System.out同步锁，从而永远在这里阻塞 */
thread.resume(); /* 无法执行这一步，主线程和子线程均陷入死锁 */
```

#### §1.3.4.1 `Object.wait()/notify()`

容易发现，`Thread.suspend()/resume()`之所以会产生死锁问题，是因为`Thread.suspend()`不释放任何锁。基于此，Java提出了一种新的阻塞与唤醒范式，旨在使得线程阻塞时释放锁。为此，该**方案要求与`synchronized`配合使用，且`synchronized`获取的对象锁与`Object.wait()/notify()`调用的是同一个对象**。

```java
synchronized (对象A) { // 获取对象A的对象锁
	// ...
	对象A.wait(); // 及时释放对象A的对象锁，从而缓解死锁问题
}
```

Java给每个`Object`对象锁维护一个等待队列。`Object.wait()`会尝试释放当前线程早已在`synchronized`获取的对象锁，并加入到该对象锁`Object`的等待队列中，将当前线程设置为`WAITING`状态。`Object.notify()`会从其等待队列中随机选择一个线程，使其从`WAITING`状态转变为`BLOCKED`状态，从而使其一直尝试抢占锁，抢占成功后继续往下执行。`Object.notifyAll()`有略微的区别，它会选择等列队列中的所有线程。

```java
public class JucMain {
    private static String message;
    public static void main(String[] args) {
        Object lock = new Object();
        Thread thread_read = new Thread(() -> {
            synchronized (lock) {
                if (message == null) {
                    try { lock.wait(); } catch (InterruptedException e) { throw new RuntimeException(e); }
                }
            }
            System.out.printf("[%s] Read the message: %s\n", Thread.currentThread().getName(), message);
        });
        Thread thread_write = new Thread(() -> {
            synchronized (lock) {
                message = "Hello World";
                lock.notify();
            }
        });
        thread_read.start(); thread_write.start(); /* [Thread-0] Read the message: Hello World */
    }
}
```

这种方案有一个缺点：就是必须保证`Object.wait()`比`Object.notify()`先执行，否则会导致调用`Object.wait()`的线程用于阻塞。

#### §1.3.4.1 `LockSupport.park()/unpark()`

`LockSupport.park()/unpark()`使用了许可机制，完全不需要考虑对象锁和等待队列，从而彻底解决了`Object.wait()/notify()`的死锁和竞态条件问题。具体来说，即使`LockSupport.unpark()`先执行，那么`LockSupport.park()`也不会阻塞。授予许可的过程具有幂等性，而收回许可会导师许可撤销。

```java
public class JucMain {
    private static String message;
    public static void main(String[] args) {
        Thread thread_read = new Thread(() -> {
            if (message == null) {
                LockSupport.park();
            }
            System.out.printf("[%s] Read the message: %s\n", Thread.currentThread().getName(), message);
        });
        Thread thread_write = new Thread(() -> {
            message = "Hello World";
            LockSupport.unpark(thread_read);
        });
        thread_read.start(); thread_write.start(); /* [Thread-0] Read the message: Hello World */
    }
}
```

#### §1.3.4.1 `Thread.join()`

`Thread.join()`本质上是对`Object.wait()/notify()`的封装。A线程调用B线程的`Thread.join()`方法后，会陷入`WAITING`状态，直到B线程执行完毕为止。具体来说，`Thread.join()`创建了一个B线程的对象锁，并调用其`Object.wait()`，从而让A线程陷入阻塞。B线程结束后（`!thread.isAlive()`），调用B线程自己的`this.notifyAll()`，让A线程恢复`BLOCKED`状态，从而尝试抢占锁并向下执行。

```java
public class JucMain {
    private static String message;
    public static void main(String[] args) {
        Thread thread_write = new Thread(() -> {
            message = "Hello World";
        });
        Thread thread_read = new Thread(() -> {
            if (message == null) {
                try { thread_write.join(); } catch (InterruptedException e) { throw new RuntimeException(e); }
            }
            System.out.printf("[%s] Read the message: %s\n", Thread.currentThread().getName(), message);
        });
        thread_read.start(); thread_write.start(); /* [Thread-0] Read the message: Hello World */
    }
}
```

`Thread.join(long)`也允许设置超时时间，这是因为`Object.wait()`也支持设置超时时间。

## 1.4 一致性问题

Java内存模型（JMM）规定，每个线程都有自己的内存空间。`volatile`关键字保证变量在公共内存空间被修改后，立即对所有私有内存空间可见。

例如下面的程序：在不使用`volatile`修饰公共变量`String message`时，读线程不会向公共内存空间读取最新的`message`值，从而一直陷入死循环。使用`volatile`修饰后，写线程对`message`的修改对读线程立即可见，因此可以使得读线程正常退出。

```java
public class JucMain {
	// private static String message; /* 会导致读线程死循环 */
    private static volatile String message;
    public static void main(String[] args) {
        Thread thread_write = new Thread(() -> {
            message = "Hello World";
        });
        Thread thread_read = new Thread(() -> {
            while (true) {
                if (message != null) {
                    System.out.printf("[%s] Read the message: %s\n", Thread.currentThread().getName(), message);
                    break;
                }
            }
        });
        thread_read.start();
        try { Thread.sleep(100); } catch (InterruptedException e) { throw new RuntimeException(e); }
        thread_write.start();
    }
}
```

然而，`volatile`只解决了可见性问题。对于非原子操作而言，依然存在着脏读问题。例如下面的程序使用了`++count`这一非原子操作，使得计数值不准确：

```java
public class JucMain {
    private static volatile int count;
    public static void main(String[] args) {
        for (int i = 1; i <= 5; ++i) {
            Thread thread = new Thread(() -> {
                for (int j = 1; j <= 10000; ++j) {
                    ++count;
                }
                System.out.printf("[%s] add 10000 to count\n", Thread.currentThread().getName());
            });
            thread.start();
        }
        try { Thread.sleep(1000); } catch (InterruptedException e) { throw new RuntimeException(e); }
        System.out.printf("[%s] Expect count=50000, but got count=%d\n", Thread.currentThread().getName(), count);
    }
}
/*
	[Thread-0] add 10000 to count
	[Thread-3] add 10000 to count
	[Thread-2] add 10000 to count
	[Thread-4] add 10000 to count
	[Thread-1] add 10000 to count
	[main] Expect count=50000, but got count=23052
*/
```

为了解决这个问题，我们还需要使用锁来实现同步。

## 1.5 死锁问题

死锁的形成需要同时具备以下条件：

- 互斥条件。锁具有排他性，最多只能被一个线程占用。
- 阻塞不释放条件。线程陷入阻塞状态时，不会主动释放之前占用的锁。
- 占有并等待条件。线程并不同时占用所有锁，而是先占用前者，再尝试占用后者。
- 非抢占条件。线程不会主动抢占其它线程占用的锁，只能等待其它线程资源释放。
- 环形条件。所有等待的线程和等待的资源形成环形。

为了解决死锁问题，我们有以下措施：

### §1.5.1 锁的顺序化

锁的顺序化属于**事前的预防措施**，破坏**环形条件**。所有的线程都按照同样的顺序尝试获取锁。

```mermaid
graph LR
	P1["线程1"] --> P1LockA["锁A"] --> P1LockB["锁B"] --> P1LockC["锁C"]
	P2["线程2"] --> P2LockA["锁A"] --> P2LockB["锁B"] --> P2LockC["锁C"]
	P3["线程3"] --> P3LockA["锁A"] --> P3LockB["锁B"] --> P3LockC["锁C"]
```

### §1.5.2 资源合并

资源合并属于**事前的预防措施**，破坏**占有并等待条件**。讲若干个锁的顺序获取操作打包成一个原子操作。

### §1.5.3 避免锁嵌套

避免锁嵌套属于**事前的预防措施**，破坏**阻塞不释放条件**。每个线程一次只获取一个锁，不经过阻塞操作就及时释放，从而避免阻塞。

### §1.5.4 锁超时机制

锁超时机制属于**事后的预防措施**，破坏**阻塞不释放条件**。当线程超时获取锁的等待操作超时后，就结束自己，从而释放锁。

### §1.5.5 抢占资源机制

抢占资源机制属于**事后的预防措施**，破坏**非抢占条件**。由于目前已经形成死锁，则当前线程抢夺其它线程的锁，不会导致其它线程恢复运行，于是当前线程就能执行。

### §1.5.6 撤销线程机制

撤销线程机制属于**事后的预防措施**，破坏**阻塞不释放条件**。当发生死锁时，系统随机杀死一个线程。

# §2 锁

## §2.1 互斥锁

Java提供了`synchronized`关键字用于实现互斥锁，即同一时刻只能有一个线程获取这种锁。加锁机制既可以确保可见性又可以确保原子性，而`volatile`变量只能确保可见性。

在下面的例子中，我们使用`synchronized`同步块，把一组非原子操作打包成了原子操作。

```java
public class JucMain {
    private static volatile int count;
    private static synchronized void addCount() {
        ++count;
    }
    public static void main(String[] args) {
        for (int i = 1; i <= 5; ++i) {
            Thread thread = new Thread(() -> {
                for (int j = 1; j <= 10000; ++j) {
                    addCount();
                }
                System.out.printf("[%s] add 10000 to count\n", Thread.currentThread().getName());
            });
            thread.start();
        }
        try { Thread.sleep(1000); } catch (InterruptedException e) { throw new RuntimeException(e); }
        System.out.printf("[%s] Expect count=50000, got count=%d\n", Thread.currentThread().getName(), count);
    }
}
/*
	[Thread-0] add 10000 to count
	[Thread-4] add 10000 to count
	[Thread-1] add 10000 to count
	[Thread-2] add 10000 to count
	[Thread-3] add 10000 to count
	[main] Expect count=50000, got count=50000
*/
```

`synchronized`关键字作用于不同的位置，会创建不同粒度的互斥锁：

- 作用于实例方法上，会创建一个对象级别的互斥锁
- 作用于类静态方法上，会创建一个类级别的互斥锁
- 作用于实例方法内，可以使用任意对象作为互斥锁
- 作用于类静态方法内，可以使用任意对象作为互斥锁

## §2.2 自旋锁

自旋锁是一种非阻塞锁。当线程遇到自旋锁，且暂时获取不到锁时，会一直作为`RUNNING`状态陷入死循环，不断检查锁是否被释放。这会导致自旋锁一直占用CPU，因此适用于占用锁时长较短的情景。

### §2.2.1 原始自旋锁

下面的代码展示了一种自旋锁的原始实现方案。我们使用变量`value`为`0`/`1`表示锁未被/已被占用。为了保证原子性和一致性，我们使用了CAS原语和`volatile`关键字。

```java
class SpinLock {
    private static Unsafe unsafe;
    private static final long valueOffset;
    private volatile int value = 0;
    static {
        try {
            Field unsafeInstanceField = Unsafe.class.getDeclaredField("theUnsafe");
            unsafeInstanceField.setAccessible(true);

            unsafe = (Unsafe) unsafeInstanceField.get(Unsafe.class);
            valueOffset = unsafe.objectFieldOffset(SpinLock.class.getDeclaredField("value"));
        } catch (NoSuchFieldException e) {
            throw new RuntimeException(e);
        }
    }

    public void lock() {
        while(true) {
            int newV = value + 1;
            if (newV == 1 && unsafe.compareAndSwapInt(this, valueOffset, 0, newV)) {
                return;
            }
        }
    }
    public void unlock() {
        unsafe.compareAndSwapInt(this, valueOffset, 1, 0);
    }
}
```

原始自旋锁有以下缺点：

1. 不具有公平性，所有线程同时抢占锁。
2. 为保证`volatile`的一致性，引入大量通信开销，CPU核心越多开销越大。

### §2.2.2 排队自旋锁

排队自旋锁引入了排队机制，给每个尝试抢占锁的线程分配一个排队号码，让它们不断轮训是否轮到了自己。**这种方案保证了公平性**。

```java
class TicketLock {
    private static Unsafe unsafe;
    private static final long ticketNumOffset;
    private static final long processingNumOffset;
    private volatile int ticketNum; /* 当前未被分配的排队序号 */
    private volatile int processingNum; /* 当前叫号 */
    static {
        try {
            Field unsafeInstanceField = Unsafe.class.getDeclaredField("theUnsafe");
            unsafeInstanceField.setAccessible(true);

            unsafe = (Unsafe) unsafeInstanceField.get(Unsafe.class);
            ticketNumOffset = unsafe.objectFieldOffset(TicketLock.class.getDeclaredField("ticketNum"));
            processingNumOffset = unsafe.objectFieldOffset(TicketLock.class.getDeclaredField("processingNum"));
        } catch (NoSuchFieldException e) {
            throw new RuntimeException(e);
        }
    }

    public int lock() {
        int nowNum;
        while (true) { /* 尝试取号，如果其它线程已经取号则尝试下一次取号 */
            nowNum = ticketNum;
            if (unsafe.compareAndSwapInt(this, ticketNumOffset, ticketNum, ticketNum + 1)) {
                break;
            }
        }
        while (processingNum != nowNum) { /* 等待叫号，在此处自旋 */
            ;
        }
        return nowNum;
    }
    public void unlock(int ticket) {
        unsafe.compareAndSwapInt(this, processingNumOffset, ticket, ticket + 1); /* 更新叫号 */
    }
}
```

然而，排队自旋锁依然没有减少通信开销。这是因为线程不停地访问`volatile`变量，来判定自己是否有资格获得锁。

### §2.2.3 CLH锁

CLH锁的核心思想是：为了判定当前线程是否有资格获得锁，我们不访问`volatile`变量，而是访问预先保存的`volatile`变量的本地副本。我们不再依赖`volatile`保证线程节点插入和删除的原子性，而是通过更高效的自旋+CAS操作。

```java
class CLHLock {
    private class CLHNode {
        private volatile boolean isLocked = true;
    }

    private static Unsafe unsafe;
    private static final long valueOffset;
    private volatile CLHNode tail; /* 等待队列队尾节点 */

    static {
        try {
            Field unsafeInstanceField = Unsafe.class.getDeclaredField("theUnsafe");
            unsafeInstanceField.setAccessible(true);

            unsafe = (Unsafe) unsafeInstanceField.get(Unsafe.class);
            valueOffset = unsafe.objectFieldOffset(CLHLock.class.getDeclaredField("tail"));
        } catch (NoSuchFieldException e) {
            throw new RuntimeException(e);
        }
    }

    public int lock(CLHNode currentThreadNode) {
        CLHNode preNode = null;
        while (true) {
            preNode = tail; /* 保存队列队尾节点的本地副本 */
            /* 更新当前线程为队列队尾的节点 */
            /* 形成preNode -> this.tail=currentThreadNode的链表队列 */
            if (unsafe.compareAndSwapObject(this, valueOffset, preNode, currentThreadNode)) {
                break;
            }
        }
        while (preNode != null && preNode.isLocked) {
            ; /* 自旋等待，直到preNode执行完毕 */
        }
    }
    public void unlock(CLHNode currentThreadNode) {
	    /* 当前 */
        if (!unsafe.compareAndSwapObject(this, valueOffset, currentThreadNode, null)) {
            currentThreadNode.isLocked = false;
        }
    }
}
```

我们通过一个例子解释这个过程。给定`Thread`线程A、线程B、线程C及其对应的`CLHNode`节点A、节点B、节点C：

1. 线程A尝试获取锁。线程A调用`CLHLock.lock(node_A)`，使得本地局部变量`preNode_A`为`null`，全局同步变量`tail`为`node_A`。于是线程A成功地获取了锁。**产生先后关系`null -> node_A`**。
2. 线程B尝试获取锁。线程B调用`CLHLock.lock(node_B)`，使得本地局部变量`preNode_B`为`node_A`，全局同步变量`tail`为`node_B`。**产生先后关系`node_A -> node_B`**。
3. 线程C尝试获取锁。线程C调用`CLHLock.locl(node_C)`，使得本地局部变量`preNode_C`为`node_B`，此时CPU切换线程。
4. 线程D尝试获取锁。线程D调用`CLHLock.locl(node_D)`，使得本地局部变量`preNode_D`为`node_B`，全局同步变量`tail`为`node_D`。**产生先后关系`node_B -> node_D`**。
5. 线程C恢复运行，发现CAS原子操作失败，于是重新执行CAS操作，使得本地局部变量`preNode_C`为`node_D`，全局同步变量`tail`为`node_C`。**产生先后关系`node_D -> node_C`**。
6. 至此，根据每个线程的`preNode_?`和自己持有的节点，显然存在先后关系：`preNode_A(null) -> preNode_B(node_A) -> preNode_D(node_B) -> preNode_C(node_D) -> (node_C)`。要推进这个先后关系，**显然要么`preNode == null`，要么`preNode`对应的线程已经执行完毕**。
7. 线程C恢复运行，发现自己的`preNode_C`非空（等于`node_D`），且`node_D`未完成，因此继续自旋等待。
8. 线程D恢复运行，发现自己的`preNode_D`非空（等于`node_B`），且`node_B`未完成，因此继续自旋等待。
9. 线程B恢复运行，发现自己的`preNode_B`非空（等于`node_A`），且`node_A`未完成，因此继续自旋等待。
10. 线程A恢复运行，发现自己的`preNode_A`为空，因此获得锁，执行下一步运行逻辑。
11. 剩余步骤同理。

CLH锁节省了大量的`volatile`同步变量读取操作，只留下了CAS的重试开销，因此效率较高。但是CLH锁的公平性严重依赖于UMA（统一内存访问，Uniform Memory Access），需要保证每个线程对同一个公共变量的CAS的耗时几乎相等。然而这对于NUMA架构而言是不可能的，如果公共变量不在某个线程的本地主存储中，则CAS耗时较长，从而降低性能。

### §2.2.4 MCS锁

在CLH锁中，显然每个等待锁的变量都在自旋。MCS锁在此基础上，为每个节点维护一个`spin`变量，表示是否需要自旋。当前一个线程释放锁时，会修改后一个线程的`spin`变量，告知后一个线程现在就可以获取锁，不必继续自旋。

```java
class MCSLock {
    private class MCSNode {
        public MCSNode next;
        private volatile boolean spin = true;
    }

    private static Unsafe unsafe;
    private static final long valueOffset;
    private volatile MCSNode tail;

    static {
        try {
            Field unsafeInstanceField = Unsafe.class.getDeclaredField("theUnsafe");
            unsafeInstanceField.setAccessible(true);

            unsafe = (Unsafe) unsafeInstanceField.get(Unsafe.class);
            valueOffset = unsafe.objectFieldOffset(MCSLock.class.getDeclaredField("tail"));
        } catch (NoSuchFieldException e) {
            throw new RuntimeException(e);
        }
    }

    public int lock(MCSNode currentThreadNode) {
        MCSNode preNode = null;
        while (true) {
            preNode = tail;
            if (unsafe.compareAndSwapObject(this, valueOffset, tail, currentThreadNode)) {
                break;
            }
        }
        /* 如果preNode为null，则说明该线程在队列的队首，因此可以直接获取锁 */
        if (preNode != null) { /* 如果preNode不为null，则需要维护preNode的后继next */
            preNode.next = currentThreadNode; /* 反之设立preNode的后继节点为自己，也就是在链表队列末尾追加自己 */
            while (currentThreadNode.spin) { /* 等待preNode结束后更改自己的spin变量为false，即通知自己退出自旋 */
                ;
            }
        }
    }
    public void unlock(MCSNode currentThreadNode) {
        if (tail != currentThreadNode) { /* 如果当前线程节点后面还有其它线程节点 */
            /* 如果当前节点还没有被后续节点设置next，则需要等待 */
            if (currentThreadNode.next == null) {
                if (unsafe.compareAndSwapObject(this, valueOffset, currentThreadNode, null)) {
                    return; /* 证明当前线程是最后一个入队的线程，且一直在队列的队尾，且一直没有新的线程入队，因此没有要通知的后继节点，直接返回即可 */
                } else {
                    while (currentThreadNode.next == null) { /* 等待新入队的节点维护当前节点的next */
                        ;
                    }
                }
            }
            /* 如果当前节点已经被后续节点设置了next，则通知后续节点停止自旋，开始执行 */
            currentThreadNode.next.spin = false;
        }
    }
}
```

## §2.4 `LockSupport`

`java.util.concurrent.locks.LockSupport`提供了线程阻塞与唤醒原语。

| 作用     | `LockSupport`方法名          | 备注                            |
| ------ | ------------------------- | ----------------------------- |
| 阻塞线程   | `park()`                  |                               |
| 阻塞线程   | `parkNanos(long)`         | 指定了超时时间`long`                 |
| 阻塞线程   | `parkUntil(long)`         | 制定了过期时间`long`                 |
| 阻塞线程   | `park(Object)`            | 指定了阻塞对象`Object`               |
| 阻塞线程   | `parkNanos(Object, long)` | 指定了阻塞对象`Object`，指定了超时时间`long` |
| 阻塞线程   | `parkUntil(Object, long)` | 指定了阻塞对象`Object`，制定了过期时间`long` |
| 恢复线程   | `unpark(Thread)`          |                               |
| 获取阻塞对象 | `getBlocker(Thread)`      |                               |

`LockSupport`使用了许可机制。许可是一种有状态的布尔型信号变量，`0`表示无许可，`1`表示有许可。正因为其有状态，所以先执行`unpark()`就不会导致`park()`阻塞。

外界调用`Thread.interrupt()`方法时，如果线程此时被`LockSupport.park()`阻塞，则会立即解除阻塞并继续向下执行：

```java
public class JucMain {
    public static void main(String[] args) {
        Thread thread = new Thread(() -> {
            LockSupport.park();
            System.out.printf("[%s] recover from LockSupport.lock()", Thread.currentThread().getName());
        });
        thread.start();
        thread.interrupt();
    }
}
/*
	[Thread-0] recover from LockSupport.lock()
*/
```

对于指定阻塞对象的阻塞线程，我们可以使用`LockSupport.getBlocker(Thread)`的方法获取。在下面的例子中，我们让线程1阻塞，用线程2获取线程1的`Blocker`。

```java
public class JucMain {
    public static void main(String[] args) throws InterruptedException {
        Object lock = new Object();
        Thread thread1 = new Thread(() -> {
            System.out.printf("[%s] use blocker %s\n", Thread.currentThread().getName(), lock);
            LockSupport.park(lock);
        });
        Thread thread2 = new Thread(() -> {
            Object blocker = LockSupport.getBlocker(thread1);
            System.out.printf("[%s] thread1 blocker is %s\n", Thread.currentThread().getName(), blocker);
        });
        thread1.setDaemon(true);

        thread1.start();
        Thread.sleep(100);
        thread2.start();
    }
}
/*
	[Thread-0] use blocker java.lang.Object@31cf8b4e
	[Thread-1] thread1 blocker is java.lang.Object@31cf8b4e
*/
```

接下来我们分析`LockSupport`的源码实现。

- `LockSupport`类的构造方法故意设置为`private`，因此无法实例化，开发者只能使用它提供的静态方法。
- `LockSupport`包含一个静态`Unsafe`实例`U`。
	- 在旧版JDK中，由于无法`new`一个`Unsafe`实例，所以只能在`static`静态代码块中，使用`Unsafe.class.getDeclaredField("theUnsafe")`获取`Unsafe.theUnsafe`字段实例`field`，然后使其可以被访问`field.setAccessible(true)`，再通过反射`(Unsafe) field.get(Unsafe.class)`获取`Unsafe`实例。**这种方法虽然麻烦，但是适用于全版本JDK的所有情况**。
	- 在新版JDK中，`Unsafe`直接提供了静态方法`getUnsafe()`，可以直接返回`Unsafe`内的私有静态变量`theUnsafe`。**但是这种方案只能用于被信任的类，否则会抛出`SecurityException`异常**。
- `LockSupport`包含一个静态`long`变量`PARKBLOCKER`，表示`Thread.parkLocker`变量相对于`Thread`基址的偏移量。
- `LockSupport.park*()`系列方法用于阻塞线程。首先设置线程的`parkBlocker`，然后调用`Unsafe.park()`进行阻塞，恢复运行后清空线程的`parkBlocker`。

```java
public class LockSupport {
	/* 私有构造方法，因此无法实例化 */
    private LockSupport() {}

	/* Unsafe实例 */
    private static final Unsafe U = Unsafe.getUnsafe();

	/* 用于虚拟线程 */
    private static final JavaLangAccess JLA = SharedSecrets.getJavaLangAccess();

	/* Thread.parkBlocker的偏移量/Getter/Setter */
    private static final long PARKBLOCKER = U.objectFieldOffset(Thread.class, "parkBlocker");
    private static void setBlocker(Thread t, Object arg) {
        U.putReferenceOpaque(t, PARKBLOCKER, arg);
    }
    public static void setCurrentBlocker(Object blocker) {
        U.putReferenceOpaque(Thread.currentThread(), PARKBLOCKER, blocker);
    }
    public static Object getBlocker(Thread t) {
        if (t == null)
            throw new NullPointerException();
        return U.getReferenceOpaque(t, PARKBLOCKER);
    }

	/* 阻塞线程的方法 */
	/* 设置Thread.parkBlocker，调用Unsafe.park()，阻塞结束后清空Thread.parkBlocker */
    public static void park(Object blocker) {
        Thread t = Thread.currentThread();
        setBlocker(t, blocker);
        try {
            if (t.isVirtual()) {
                JLA.parkVirtualThread();
            } else {
                U.park(false, 0L);
            }
        } finally {
            setBlocker(t, null);
        }
    }
    public static void parkNanos(Object blocker, long nanos) {
        if (nanos > 0) {
            Thread t = Thread.currentThread();
            setBlocker(t, blocker);
            try {
                if (t.isVirtual()) {
                    JLA.parkVirtualThread(nanos);
                } else {
                    U.park(false, nanos);
                }
            } finally {
                setBlocker(t, null);
            }
        }
    }
    public static void parkUntil(Object blocker, long deadline) {
        Thread t = Thread.currentThread();
        setBlocker(t, blocker);
        try {
            parkUntil(deadline);
        } finally {
            setBlocker(t, null);
        }
    }
    public static void park() {
        if (Thread.currentThread().isVirtual()) {
            JLA.parkVirtualThread();
        } else {
            U.park(false, 0L);
        }
    }
    public static void parkNanos(long nanos) {
        if (nanos > 0) {
            if (Thread.currentThread().isVirtual()) {
                JLA.parkVirtualThread(nanos);
            } else {
                U.park(false, nanos);
            }
        }
    }
    public static void parkUntil(long deadline) {
        if (Thread.currentThread().isVirtual()) {
            long millis = deadline - System.currentTimeMillis();
            JLA.parkVirtualThread(TimeUnit.MILLISECONDS.toNanos(millis));
        } else {
            U.park(true, deadline);
        }
    }

	/* 恢复线程的方法 */
    public static void unpark(Thread thread) {
        if (thread != null) {
            if (thread.isVirtual()) {
                JLA.unparkVirtualThread(thread);
            } else {
                U.unpark(thread);
            }
        }
    }
	// ...
}

```

## §2.5 重入锁

Java提供了`java.util.concurrent.locks.ReentrantLock`重入锁。其构造函数接受一个`boolean`值，表示是否创建一个公平锁。在下面的例子中，我们使用GUI来可视化非公平锁和公平锁的线程调度策略。

```java
public class JucMain {

	// private static ReentrantLock lock = new ReentrantLock(false); /* 非公平锁 */
	private static ReentrantLock lock = new ReentrantLock(true); /* 公平锁 */

    public static void main(String[] args) {
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new FlowLayout(FlowLayout.LEFT));
        frame.setSize(new Dimension(350, 200));

        for (int i = 1; i <= 10; ++i) {
            JProgressBar progressBar = new JProgressBar();
            progressBar.setStringPainted(true);
            progressBar.setMinimum(0);
            progressBar.setMaximum(1000);
            frame.add(progressBar);

            Thread thread = new Thread(() -> {
                progressBar.setString(Thread.currentThread().getName());
                int count = 0;
                while (count <= 1000) {
                    lock.lock();
                    progressBar.setValue(++count);
                    try { Thread.sleep(1); } catch (InterruptedException e) { throw new RuntimeException(e); }
                    lock.unlock();
                }
            });
            thread.start();
        }

        frame.setVisible(true);
    }
}
```

## §2.A CAS

CAS（比较并交换，Compare And Swap）是CPU级别的一种原子操作，当且仅当内存值等于预期值时，说明此时其他线程没有更改内存值，不存在数据冲突问题，才用新值写入到内存值；如果内存值不等于预期值，则一直重试该操作，直到成功为止。

```java
public final clas Unsafe {
    public final native boolean compareAndSetInt(
	    Object o,     /* 对象基址 */
	    long offset,  /* 对象int成员的基址偏移量 */
		int expected, /* 预期值 */
		int x         /* 新值 */
	);
}
```

以`java.util.concurrent.atomic.AtomicInteger::incrementAndGet()`源码为例：

```mermaid
flowchart LR
	A[["java.util.concurrent.atomic<br/>AtomicInteger<br/>::incrementAndGet()"]] -->
		B["jdk.internal.misc<br/>Unsafe<br/>::getAndAddInt()"] -->
		C["jdk.internal.misc<br/>Unsafe<br/>::weakCompareAddSetInt()"] -->
		D[["jdk.internal.misc<br/>Unsafe<br/>::compareAndSetInt()"]]
```

在JDK 8及之前，Java使用`sun.misc.Unsafe`类调用CAS操作。具体来说，我们需要通过反射机制，使用类对象的`class.getDeclaredField(变量名)`获取字段实例`Field`，再调用`Unsafe`的实例`unsafe`提供的`unsafe.objectFieldOffset(Field)`方法获取`long`型的基址偏移量，最后调用`unsafe.compareAndSwapObject(obj, valueOffset, ...)`直接操作内存。

在JDK 9及之后，Java使用`java.lang.invoke.VarHandle`类作为替代，将`obj`基址及其偏移量`valueOffset`封装成一个可操作的`VarHandle`实例。具体来说，我们直接调用`java.lang.invoke.MethodHandles`提供的`MethodHandles.lookup().findVarHandle(类对象, 字段名, 字段数据类型类对象)`获取`VarHandle`实例，再调用其自带泛型的实例方法`varHandle.compareAndSet(obj, ...)`即可。

这里我们以[OpenJDK 24的HotSpot源码](https://github.com/openjdk/jdk/blob/ceb51d44449977ecc142f6af03f93162b98adaf6/src/hotspot/share/prims/unsafe.cpp#L737)为例，它会调用X86指令集的`cmpxchg`或ARM的`cmpxchgl`汇编指令。

```cpp
/* src/hotspot/share/prims/unsafe.cpp */
UNSAFE_ENTRY_SCOPED(jlong, Unsafe_CompareAndExchangeLong(JNIEnv *env, jobject unsafe, jobject obj, jlong offset, jlong e, jlong x)) {
	oop p = JNIHandles::resolve(obj); /* JVM层的Java对象 */
	volatile jlong* addr = (volatile jlong*)index_oop_from_field_offset_long(p, offset); /* 根据偏移量获得long基址 */
	return Atomic::cmpxchg(addr, e, x); /* 调用CAS原子操作 */
} UNSAFE_END
```

CAS存在以下问题：

- CAS的原子操作只能针对一个变量，不能保证多个变量的原子操作。
- CAS的重试机制造成较大开销。如果一直不成功，就会一直重试。
- ABA问题。甲线程的预期值为A，乙丙线程依次将内存值修改为B和A，这会导致甲线程认为其他线程没有更改过内存值。解决方法是增加一个自增的版本号。

# §3 AQS

AQS（Abstract Queued Synchronized）是Java并发的核心机制，它作为一个同步器，可以在多个线程之间同步共享变量的值。

## §3.1 AQS组成部分

AQS是一个抽象类，为后续的实现类定义了五个成分：

- 同步状态：实现锁机制。
- 等待队列：存放等待锁的线程节点
- 条件队列：实现条件队列模式。

### §3.1.1 等待队列

对于等待队列，AQS采用CLH锁的实现，也就是用物理上的双向链表维护一个逻辑上的队列。我们令队尾进，队头出。

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
    private transient volatile Node head; /* CLH锁等待队列头结点 */
    private transient volatile Node tail; /* CLH锁等待队列尾结点 */
	// ...
	/* 获取volatile变量的偏移量 */
    private static final Unsafe U = Unsafe.getUnsafe();
    private static final long STATE = U.objectFieldOffset(AbstractQueuedSynchronizer.class, "state");
    private static final long HEAD = U.objectFieldOffset(AbstractQueuedSynchronizer.class, "head");
    private static final long TAIL = U.objectFieldOffset(AbstractQueuedSynchronizer.class, "tail");
    // ...
}
```

类似的，AQS使用`AbstractQueuedSynchronized::Node`节点，以链表方式实现队列，提供了配套的CASSetter方法：

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
    abstract static class Node {
        volatile Node prev;
        volatile Node next;
        Thread waiter; /* 表示独占锁/共享锁 */
        volatile int status;

        private static final long STATUS = U.objectFieldOffset(Node.class, "status");
        private static final long NEXT = U.objectFieldOffset(Node.class, "next");
        private static final long PREV = U.objectFieldOffset(Node.class, "prev");

		final boolean casPrev(Node c, Node v) {
		    return U.weakCompareAndSetReference(this, PREV, c, v);
		}
		final boolean casNext(Node c, Node v) {
		    return U.weakCompareAndSetReference(this, NEXT, c, v);
		}
		final int getAndUnsetStatus(int v) {
		    return U.getAndBitwiseAndInt(this, STATUS, ~v);
		}
		final void setPrevRelaxed(Node p) {
		    U.putReference(this, PREV, p);
		}
    }
}
```

```mermaid
flowchart TB
	subgraph Node_A
		direction TB
		Node_A_prev["Node prev"]
		Node_A_next["Node next"]
		Node_A_waiter["Thread waiter"]
	end
	subgraph Node_B
		direction TB
		Node_B_prev["Node prev"]
		Node_B_next["Node next"]
		Node_B_waiter["Thread waiter"]
	end
	subgraph Node_C
		direction TB
		Node_C_prev["Node prev"]
		Node_C_next["Node next"]
		Node_C_waiter["Thread waiter"]
	end
	Node_A_next --> Node_B_next --> Node_C_next
	Node_A_waiter --> Node_B_waiter --> Node_C_waiter
	Node_C_prev --> Node_B_prev --> Node_A_prev
```

### §3.1.2 同步状态

对于同步状态，AQS提供了以下状态（不同JDK的源码实现可能不同）：

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
    static final int WAITING   = 1;
    static final int CANCELLED = 0x80000000; // INT32_MIN (-2147483648)
    static final int COND      = 2;
    private volatile int state; /* 同步状态 */
    // ...
    abstract static class Node {
	    // ...
        volatile int status;
    }
    // ...
}
```

| 状态     | 旧版JDK          | 新版JDK                 | 含义                                    |
| ------ | -------------- | --------------------- | ------------------------------------- |
| 无状态    | `0`            | `0`                   | 初始状态                                  |
| 等待唤醒状态 | `SIGNAL=-1`    | `WAITING=1`           | 当前节点的后继节点通过`LockSupport.park()`进入等待状态 |
| 已取消状态  | `CANCELLED=1`  | `CANCELLED=INT32_MIN` | 当前节点因为超时或中断而被取消                       |
| 条件等待状态 | `CONDITION=-2` | `COND=2`              | 当前节点在条件队列中                            |
| 共享传播状态 | `PROPAGATE=-3` | 无                     | 当前节点无条件向下传播，用于共享模式                    |

```mermaid
stateDiagram-v2
	direction LR

	state "0" as INIT
	state "SIGNAL<br/>-1" as SIGNAL
	state "CANCELLED<br/>1" as CANCELLED
	state "CONDITION<br/>-2" as CONDITION
	state "PROPAGATE<br/>-3" as PROPAGATE

	[*] --> INIT CONDITION
	INIT --> SIGNAL CANCELLED PROPAGATE
	SIGNAL --> CANCELLED INIT
	PROPAGATE --> INIT SIGNAL
	CONDITION --> CANCELLED
	CANCELLED --> [*]
```

```mermaid
stateDiagram-v2
    direction LR

    state "0" as INIT
    state "WAITING<br/>1" as WAITING
    state "COND<br/>2" as COND
    state "CANCELLED<br/>-2147483648" as CANCELLED

	[*] --> INIT
    INIT --> WAITING
    INIT --> CANCELLED
    WAITING --> INIT
    WAITING --> CANCELLED
    [*] --> COND
    COND --> INIT
    COND --> CANCELLED
    CANCELLED --> [*]
```

AQS针对同步状态变量提供了一系列辅助方法，例如Getter和基于CAS的Setter：

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
	private volatile int state; /* 同步状态 */
	protected final int getState() {
        return state;
    }
    protected final void setState(int newState) {
        state = newState;
    }
    protected final boolean compareAndSetState(int expect, int update) {
        return U.compareAndSetInt(this, STATE, expect, update);
    }
    // ...
    abstract static class Node {
	    volatile int state;
	    // ...
		final void setStatusRelaxed(int s) {
		    U.putInt(this, STATUS, s);
		}
		final void clearStatus() {
            U.putIntOpaque(this, STATUS, 0);
        }
    }
    // ...
}
```

### §3.1.3 条件队列

AQS的条件队列提供了阻塞与唤醒的机制，其中`ConditionObject`是条件队列的实现类。条件队列由若干条件节点`ConditionNode`组成。每个条件节点具有一个`nextWaiter`指针用于构成链表，而条件队列具有`firstWaiter`和`lastWaiter`用于指向条件队列的头结点和尾节点。

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
    static final class ConditionNode extends Node implements ForkJoinPool.ManagedBlocker {
        ConditionNode nextWaiter;
	    // ...
    }
	public class ConditionObject implements Condition, java.io.Serializable {
        // ...
        private transient ConditionNode firstWaiter;
        private transient ConditionNode lastWaiter;
		
        public ConditionObject() { }
    }
}
```

`ConditionObject`实现了`Condition`接口，它包含两个核心方法：`await()`和`signal()`。`await()`用于让当前线程释放锁，并进入等待状态，加入到条件队列，直到被`signal()`唤醒/被中断/超时。`signal()`用于从条件队列中取出等待时间最长的节点，将其移动到同步队列中，与同步队列中的其它节点一起抢占锁。

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	public class ConditionObject implements Condition, java.io.Serializable {
        public final boolean await(long time, TimeUnit unit) throws InterruptedException {
            long nanosTimeout = unit.toNanos(time);
            if (Thread.interrupted())
                throw new InterruptedException();
                
            ConditionNode node = newConditionNode(); /* 创建条件节点(同时防止OOM) */
            if (node == null) /* 处理OOM */
                return false;
            
            /* 加入到条件队列并释放锁 */
            int savedState = enableWait(node);
            
            long nanos = (nanosTimeout < 0L) ? 0L : nanosTimeout;
            long deadline = System.nanoTime() + nanos;
            boolean cancelled = false, interrupted = false;
            
            while (!canReacquire(node)) { /* 当前节点是否被signal()移动到同步队列中 */
	            /* 如果未被signal()调用 */
                if (
	                (interrupted |= Thread.interrupted()) ||
                    (nanos = deadline - System.nanoTime()) <= 0L
                ) { /* 如果中断或超时早于signal，则跳出循环抛出异常 */
                    if (cancelled = (node.getAndUnsetStatus(COND) & COND) != 0)
	                    
                        break;
                } else
	                /* 如果signal早于中断或超时，就挂起自己等待唤醒 */
                    LockSupport.parkNanos(this, nanos);
            }
            node.clearStatus();
            reacquire(node, savedState);
            if (cancelled) { /* 如果仍在条件队列中 */
                unlinkCancelledWaiters(node); /* 就挂起线程 */
                if (interrupted)
                    throw new InterruptedException();
            } else if (interrupted)
                Thread.currentThread().interrupt();
            return !cancelled;
        }
        public final void signal() {
            ConditionNode first = firstWaiter;
            if (!isHeldExclusively())
                throw new IllegalMonitorStateException();
            else if (first != null)
                doSignal(first, false);
        }
	}
}
```

### §3.1.A `signalNext()`

`AbstractQueuedSynchronized.signalNext()`用于AQS独占锁，从当前节点`h`出发，向队尾查找一个深度。将后继节点设置为`WAITING`状态并唤醒线。`AbstractQueuedSynchronized.signalNextIfShared()`逻辑类似，用于AQS共享锁，但是使用了`instanceof`判定是否是AQS共享锁节点。

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
    private static void signalNext(Node h) {
        Node s;
        if (h != null && (s = h.next) != null && s.status != 0) { // 获取后继节点s
            s.getAndUnsetStatus(WAITING); // 设置后继节点s为WAITING
            LockSupport.unpark(s.waiter); // 唤醒后继节点s的线程
        }
    }
    private static void signalNextIfShared(Node h) {
        Node s;
        if (h != null && (s = h.next) != null && (s instanceof SharedNode) && s.status != 0) {
            s.getAndUnsetStatus(WAITING);
            LockSupport.unpark(s.waiter);
        }
    }
}
```

### §3.1.B `cleanQueue()`

`AbstractQueuedSynchronized.cleanQueue()`用于清除队列中的所有`CANCELLED`状态的节点：

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
    private void cleanQueue() {
        while (true) {
	        // p -> q(当前) -> s
	        Node q = tail; /* 当前正在检查的节点，从队尾向队头遍历 */
	        Node s = null; /* q的后继节点(successor) */
	        Node p = null; /* q的前驱节点(prev) */
	        Node n = null;
            while (true) {
	            /* 如果队列中只有<=1个节点，则判定删除完毕 */
                if (q == null || (p = q.prev) == null) { return; }
	            
	            /* 初始时q在队尾，所以s一定为null，因此s==null用于判定q是不是队尾 */
	            /* 保证一致性，这段时间没有新节点竞争加入队列(tail==q) */
	            /* 保证双向链表关系q->s依然成立(s.prev==q)，并且后继节点未CANCELLED */
	            /* 若不能保证，则放弃本次针对当前节点q的尝试，开启下一次尝试 */
                if (s == null ? tail != q : (s.prev != q || s.status < 0))
                    break;
		        
                if (q.status < 0) { /* 如果当前节点为CANCELLED，则需要清除当前节点 */
                    if (
	                    /* 如果当前节点q在队尾tail，则需要把tail从q换成前驱节点p */
	                    /* 如果当前节点q在队中，则需要把后继节点s的s.prev从q换成前驱节点p */
	                    (s == null ? casTail(q, p) : s.casPrev(q, p)) &&
                        q.prev == p /* 防止另一个线程在前驱节点p上也同时执行cleanQueue()，破坏了p->q关系 */
                    ) {
                        p.casNext(q, s); /* 让前驱节点p的p.next指向后继节点s。这一步不要求必须成功，。 */
                        if (p.prev == null) /* 如果p是队头，则q的移除可能让p是队列中的唯一节点，需要尝试唤醒 */
                            signalNext(p); /* 取消后继节点s(即p.next)的WAITING状态，并用LockSupport.unpark(s)唤醒 */
                    }
                    break; /* 删除了当前CANCELLED节点q，然后再次从队尾重新扫描 */
                }
	            
	            /* 如果p->q断开，说明有其它线程竞争执行cleanQueue()，刚才删除了p和q之间的节点。我们需要修复p->q的关系 */
                if ((n = p.next) != q) {
                    if (n != null && q.prev == p) {
                        p.casNext(n, q); /* 让p.next修改为q，做了其它线程的任务，助人为乐 */
                        if (p.prev == null) /* 如果p是队头，则q的移除可能让p是队列中的唯一节点，需要尝试唤醒 */
                            signalNext(p); /* 取消后继节点s(即p.next)的WAITING状态，并用LockSupport.unpark(s)唤醒 */
                    }
                    break;
                }
                
                /* 当前节点向队头移动 */
                s = q;
                q = q.prev;
            }
        }
    }
}
```

## §3.2 独占锁与共享锁

AQS本身只是一个抽象类，它的实现类才能称之为锁。无论是独占锁还是共享锁，AQS都保留了对应的接口。

独占锁只有一个资源，由若干线程竞争抢占，在此情况下状态变量`state`表示资源是否被占用（`0`或`1`）；共享锁可以指定资源的数量，由若干线程抢占，在此情况下状态变量`state`表示剩余可占用的资源数量。

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
	static final class ExclusiveNode extends Node { } /* 独占锁节点 */
    static final class SharedNode extends Node { } /* 共享锁节点 */
    // ...
}
```

### §3.2.1 `acquire()`

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {

	/* 尝试获取独占锁，返回值表示获取是否成功。若获取失败则不阻塞，而是及时退出 */
    protected boolean tryAcquire(int arg) {
        throw new UnsupportedOperationException();
    }

	/* 尝试获取共享锁，返回值表示获取是否成功。若获取失败则不阻塞，而是及时退出 */
    protected int tryAcquireShared(int arg) {
        throw new UnsupportedOperationException();
    }

	/* 首先尝试插队获取独占锁，若插队失败则排队 */
    public final void acquire(int arg) {
        if (!tryAcquire(arg))
            acquire(null, arg, false, false, false, 0L);
    }

	/* 首先尝试插队获取共享锁，若插队失败则排队 */
    public final void acquireShared(int arg) {
        if (tryAcquireShared(arg) < 0)
            acquire(null, arg, true, false, false, 0L);
    }

	/*
		AQS独占锁与AQS共享锁的共用的获取锁的方法
		@param bool timed 是否启用等待超时机制
		@param long time 设置等待超时的判定时刻
	*/
    final int acquire(Node node, int arg, boolean shared, boolean interruptible, boolean timed, long time) {
    
        Thread current = Thread.currentThread();
        byte spins = 0, postSpins = 0;
        boolean interrupted = false;
        boolean first = false; /* 当前节点node是否为队首，设置标志位避免重复检查 */
        Node pred = null; /* 当前节点的前驱节点 */

        while (true) { /* 一直尝试获取锁，直到获取成功/中断/超时 */
	        /* 开始尝试直接抢占锁，不排队 */
            if (
	            /* 当前节点不在等待队列队首位置(记忆化，如果不在就一直刷新first，直到在为止就剪枝跳过) */
	            !first &&
	            /* 当前节点及其前驱节点必须非null，记前驱节点为prev */
	            (pred = (node == null) ? null : node.prev) != null &&
	            /* 当前节点不在等待队列队首位置(head为隐节点，head.next才是队首位置) */
                !(first = (head == pred))
            ) {
                if (pred.status < 0) { /* 如果前驱节点为CANCELLED，则清理队列 */
                    cleanQueue();
                    continue;
                } else if (pred.prev == null) { /* pred是隐节点 */
                    Thread.onSpinWait(); /* 在JVM层优化自旋等待的CPU占用，不会阻塞线程 */
                    continue;
                }
            }
            if (first || pred == null) { /* 如果当前节点在队首或尚未入队，则有资格抢占锁 */
                boolean acquired; /* 是否成功获取锁 */
                try { /* 尝试获取锁 */
                    if (shared)
                        acquired = (tryAcquireShared(arg) >= 0);
                    else
                        acquired = tryAcquire(arg);
                } catch (Throwable ex) {
                    cancelAcquire(node, interrupted, false);
                    throw ex;
                }
                if (acquired) { /* 如果抢占锁成功 */
                    if (first) { /* 如果当前节点在队首，那么还需要出队 */
                        node.prev = null; /* 切断前驱节点与当前节点的关系 */
                        head = node; /* 自己成为新的隐节点 */
                        pred.next = null; /* 切断前驱节点与当前节点的关系 */
                        node.waiter = null; /* 撤销线程引用，防止内存泄露 */
                        if (shared)
                            signalNextIfShared(node);
                        if (interrupted)
                            current.interrupt();
                    }
                    return 1;
                }
            }
            
            /* 尝试入队 */
            Node t;
            if ((t = tail) == null) { /* 如果队列为空，则创建虚节点来初始化队列 */
                if (tryInitializeHead() == null)
                    return acquireOnOOME(shared, arg);
            } else if (node == null) { /* 如果外界调用了acquire()，则其传入node=null，需要自动新建 */
                try {
                    node = (shared) ? new SharedNode() : new ExclusiveNode();
                } catch (OutOfMemoryError oome) {
                    return acquireOnOOME(shared, arg);
                }
            } else if (pred == null) { /* 如果当前节点node尚未入队，则在此处入队 */
                node.waiter = current; /* 设置当前节点对应的线程实例 */
                node.setPrevRelaxed(t); /* 乐观地设置node.prev = 原队尾节点tail */
                if (!casTail(t, node)) /* 尝试把队尾节点tail替换为node */
	                /* 如果替换失败，说明有线程竞争进入队尾，则乐观失败，需要撤回之前的乐观操作 */
                    node.setPrevRelaxed(null); /* 使得下一次循环仍然进入这个pred == null的if分支 */
                else
	                /* 如果替换成功，维护原队尾节点的next指向真正队尾节点node */
                    t.next = node;
            } else if (first && spins != 0) { /* 当前节点在队头 */
                --spins;
                Thread.onSpinWait(); /* 这说明队头之前的节点已经结束，已经释放锁，可以尝试抢占 */
            } else if (node.status == 0) { /* 当前节点不在队头，又是初始状态 */
                node.status = WAITING; /* 只能切换到WAITING状态 */
            } else { /* 万事俱备，可以阻塞Thread了 */
                spins = postSpins = (byte)((postSpins << 1) | 1); /* 更新自旋次数 */
                try { /* 阻塞线程 */
                    long nanos;
                    if (!timed)
                        LockSupport.park(this);
                    else if ((nanos = time - System.nanoTime()) > 0L)
                        LockSupport.parkNanos(this, nanos);
                    else
                        break;
                } catch (Error | RuntimeException ex) {
                    cancelAcquire(node, interrupted, interruptible);
                    throw ex;
                }
                node.clearStatus(); /* 线程被唤醒后，恢复当前节点的状态为初始状态 */
                if ((interrupted |= Thread.interrupted()) && interruptible)
                    break;
            }
        }
        return cancelAcquire(node, interrupted, interruptible);
    }
}
```

我们发现，AQS均没有实现`tryAcquire()`和`tryAcquireShared()`的具体逻辑，而是直接抛出一个表示未支持操作的异常。这是因为AQS采用了职责分离的思想——AQS负责控制流，其实现类负责业务逻辑。以下是一种可行的独占锁和共享锁的实现：

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	@Override
	public boolean tryAcquire(int acquire) {
		if (compareAndSetState(0, 1)) {
			return true;
		}
		return false;
	}

	@Override
	public int tryAcquireShared(int interval) {
		while (true) {
			int current = getState();
			int newCount = current - 1;
			if (newCount < 0 || compareAndSetState(current, newCount)) {
				return newCount;
			}
		}
	}
}
```

### §3.2.2 `cancelAcquire()`

`AbstractQueuedSynchronizer.cancelAcquire()`用于取消获取锁，调用时需要传入待取消节点。

考虑队列`线程A(虚节点,head) -> 线程B -> 线程C -> 线程D(tail)`，我们取消节点时需要考虑四种情况：

1. 取消队尾节点（即D节点）。更新C节点的`next`为`null`，更新全局`tail`为C节点，最后直接删除D节点。
2. 取消队中节点（例C节点）。更新B节点的`next`为D节点，更新D节点的`prev`为B节点，最后直接删除C节点。
3. 取消虚节点的后继节点（即B节点）。更新A节点的`next`为C节点，更新C节点的`prev`为A节点，最后直接删除C节点，并唤醒C节点。
4. 取消被取消节点的后继节点（例B节点已取消，再取消C节点）。同第3条情况，都需要唤醒后继节点。

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
	private int cancelAcquire(Node node, boolean interrupted, boolean interruptible) {
        if (node != null) {
            node.waiter = null; /* 解除线程实例引用关系，防止内存泄露 */
            node.status = CANCELLED; /* 设置当前节点状态为CANCELLED */
            if (node.prev != null)
                cleanQueue(); /* 清空队列中的CANCELLED节点 */
        }
        if (interrupted) {
            if (interruptible)
                return CANCELLED;
            else
                Thread.currentThread().interrupt();
        }
        return 0;
    }
}
```

### §3.2.3 `release()`/`releaseShared()`

`AbstractQueuedSynchronizer`提供的`release()`用于释放独占锁，`releaseShared()`用于释放共享锁。释放后允许下一个节点执行。

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
    protected boolean tryRelease(int arg) {
        throw new UnsupportedOperationException();
    }
    public final boolean release(int arg) {
        if (tryRelease(arg)) {
            signalNext(head);
            return true;
        }
        return false;
    }
    
    protected boolean tryReleaseShared(int arg) {
        throw new UnsupportedOperationException();
    }
    public final boolean releaseShared(int arg) {
        if (tryReleaseShared(arg)) {
            signalNext(head);
            return true;
        }
        return false;
    }
}
```

### §3.2.4 `acquireInterruptibly()`/`acquireSharedInterruptibly()`

我们知道，`synchronized`的机制是一直尝试获取锁，只要开始等待锁就会一直等待，即使我们对当前线程`thread`调用`.interrupt()`尝试中断也无济于事。为了解决这个问题，AQS提供了`acquireInterruptibly()`/`acquireSharedInterruptibly()`用于支持AQS独占锁/共享锁的中断——如果线程在等待锁的过程中被中断，则该线程会被立即唤醒，停止等待锁，并抛出`InterruptedException`异常，并清除中断状态。

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
	public final void acquireInterruptibly(int arg) throws InterruptedException {
        if (
	        Thread.interrupted() || (
	            !tryAcquire(arg) && 
	            /* 这里传入的interruptable = true */
	            acquire(null, arg, false, true, false, 0L) < 0 
	        )
        ) {
	        throw new InterruptedException();
        }
    }
    public final void acquireSharedInterruptibly(int arg)
        throws InterruptedException {
        if (
	        Thread.interrupted() || (
		        tryAcquireShared(arg) < 0 &&  
		        /* 这里传入的interruptable = true, share = true */
		        acquire(null, arg, true, true, false, 0L) < 0
		    )
        ) {
	        throw new InterruptedException();
        }
    }
    // ...
}
```

### §3.2.5 `tryAcquireNanos()`/`tryAcquireSharedNanos()`

`tryAcquireNanos()`/`tryAcquireSharedNanos()`用于实现AQS独占锁的超时机制。

```java
public abstract class AbstractQueuedSynchronizer extends AbstractOwnableSynchronizer implements Serializable {
	// ...
    public final boolean tryAcquireNanos(int arg, long nanosTimeout) throws InterruptedException {
        if (!Thread.interrupted()) { /* 若线程早已被中断，则应该尽快退出 */
            if (tryAcquire(arg)) /* 非公平锁优化，插队避免入队操作 */
                return true;
            if (nanosTimeout <= 0L) /* 已经超时，取消抢占锁 */
                return false;
            int stat = acquire(null, arg, false, true, true, System.nanoTime() + nanosTimeout);
            if (stat > 0) /* 抢占锁成功 */
                return true;
            if (stat == 0) /* 已经超时，取消抢占锁 */
                return false;
            /* stat < 0的情况会被if(!Thread.interrupted())捕获 */
        }
        throw new InterruptedException();
    }
    public final boolean tryAcquireSharedNanos(int arg, long nanosTimeout) throws InterruptedException {
        if (!Thread.interrupted()) {
            if (tryAcquireShared(arg) >= 0)
                return true;
            if (nanosTimeout <= 0L)
                return false;
            int stat = acquire(null, arg, true, true, true, System.nanoTime() + nanosTimeout);
            if (stat > 0)
                return true;
            if (stat == 0)
                return false;
        }
        throw new InterruptedException();
    }
    // ...
}
```

# §4 同步器

同步器的核心是管理一个共享状态，通过控制状态来实现不同类型的锁。AQS抽象类已经提供了`getState()`、`setState()`、`compareAndSetState()`三个方法用于管理共享状态，开发者通常继承AQS实现自己的逻辑。

## §4.1 闭锁

闭锁（`java.util.concurrent.CountDownLatch`）用于让若干线程同时满足所有条件后，才同时开始继续执行。它维护一个共享状态`state`，每次调用`countDown()`都会**非阻塞地**`--state`。当`state>0`时阻塞所有调用`await()`的线程，当`state==0`时恢复所有线程。

以下是闭锁的JDK实现代码。我们定义了一个AQS的继承内部类`Sync`，用于把AQS的状态变量`state`封装为闭锁业务相关的共享变量`count`：

```java
public class CountDownLatch {
    /* 定义AQS的实现类Sync，负责管理状态变量state */
    private static final class Sync extends AbstractQueuedSynchronizer {
        Sync(int count) { setState(count); }
        int getCount() { return getState(); }
        protected int tryAcquireShared(int acquires) { return (getState() == 0) ? 1 : -1; }
        protected boolean tryReleaseShared(int releases) {
            while (true) {
                int cur_count = getState(), next_c = cur_count - releases;
                if (cur_count == 0) { return false; }
                if (compareAndSetState(cur_count, next_c)) { return next_c == 0; }
            }
        }
    }
    private final Sync sync;

    public CountDownLatch(int count) {
        if (count < 0) { throw new IllegalArgumentException("count < 0"); }
        this.sync = new Sync(count);
    }

    /* API: await()，阻塞线程 */
    public void await() throws InterruptedException { sync.acquireSharedInterruptibly(1); }
    public boolean await(long timeout, TimeUnit unit) throws InterruptedException { return sync.tryAcquireSharedNanos(1, unit.toNanos(timeout)); }

    /* API: countDown()，自减计数器，减到0时恢复所有阻塞的线程 */
    public void countDown() { sync.releaseShared(1); }

    /* API: getCount()，获取计数器的值 */
    public long getCount() { return sync.getCount(); }

    public String toString() { return super.toString() + "[Count = " + sync.getCount() + "]"; }
}
```

下面是使用闭锁的一个示例：

```java
import java.util.Random;
import java.util.concurrent.CountDownLatch;

public class JucMain {
    static CountDownLatch latch = new CountDownLatch(3);
    public static void main(String[] args) throws InterruptedException {
        for (int i = 1; i <= 3; ++i) {
            Thread thread = new Thread(() -> {
                try { Thread.sleep(new Random().nextLong(200)); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.printf("[%s] latch countdown from %d to %d\n", Thread.currentThread().getName(), latch.getCount(), latch.getCount() - 1);
                latch.countDown();
                System.out.printf("[%s] waiting for latch...\n", Thread.currentThread().getName());
                try { latch.await(); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.printf("[%s] finished.\n", Thread.currentThread().getName());
            });
            thread.start();
        }
        System.out.printf("[%s] waiting for latch...\n", Thread.currentThread().getName());
        latch.await();
        System.out.printf("[%s] finished.\n", Thread.currentThread().getName());
    }
}
/*
	[main] waiting for latch...
	[Thread-0] latch countdown from 3 to 2
	[Thread-0] waiting for latch...
	[Thread-1] latch countdown from 2 to 1
	[Thread-1] waiting for latch...
	[Thread-2] latch countdown from 1 to 0
	[Thread-2] waiting for latch...
	[Thread-0] finished.
	[Thread-2] finished.
	[Thread-1] finished.
	[main] finished.
*/
```

## §4.2 信号量

信号量（`java.util.concurrent.Semaphore`）用于维护当前可用的资源数量`permits`。当且仅当`permis>0`时才允许新线程获取资源。

`Semaphore`本身就是一个共享锁，可以通过配置指定为公平锁或非公平锁。具体来说，`Semaphore`定义了一个内部抽象类`Sync`，及其两个内部实现类`NonfairSync`（非公平锁）和`FairSync`（公平锁），在`Semaphore`的构造函数传入一个`boolean fair`决定实例化哪个实现类，并赋值给静态变量`Sync sync`以实现多态。`NonfairSync`和`FairSync`的唯一区别体现在`tryAcquireShared()`的实现上，`FairSync.tryAcquireShared()`先使用`hasQueuedPredecessors()`询问队列中是否存在早于自己的线程，如果是的话就取消本次获取所得尝试，进入下一次自旋。

```java
class Semaphore implements java.io.Serializable {
    abstract static class Sync extends AbstractQueuedSynchronizer {
        /* 构造方法、Getter、Setter */
        Sync(int permits) { setState(permits); }
        final int getPermits() { return getState(); }
        /* 获取锁并维护信号量(非公平锁) */
        final int nonfairTryAcquireShared(int acquires) {
            while (true) {
                int available_permits = getState();
                int remaining_permits = available_permits - acquires;
                if (remaining_permits < 0 || compareAndSetState(available_permits, remaining_permits)) { return remaining_permits; }
            }
        }
        /* 增加信号量的值 */
        protected final boolean tryReleaseShared(int releases) {
            while (true) {
                int current_permits = getPermits();
                int next_permits = current_permits + releases;
                if (next_permits < current_permits) { throw new Error("permit count exceeds INT32_MAX, resulting in overflow"); }
                if (compareAndSetState(current_permits, next_permits)) { return true; }
            }
        }
        /* 减少信号量的值 */
        final void reducePermits(int reductions) {
            while (true) {
                int current_permits = getState();
                int next_permits = current_permits - reductions;
                if (next_permits > current_permits) { throw new Error("permit count is less than INT32_MIN, resulting underflow"); }
                if (compareAndSetState(current_permits, next_permits)) { return; }
            }
        }
        /* 重置信号量的值为0 */
        final int drainPermits() {
            while (true) {
                int current_permits = getState();
                if (current_permits == 0 || compareAndSetState(current_permits, 0)) { return current_permits; }
            }
        }

    }
    static final class NonfairSync extends Sync {
        /* 构造函数 */
        NonfairSync(int permits) { super(permits); }
        /* 获取锁并维护信号量(非公平锁) */
        /* 将NonfairSync.tryAcquireShared()重定向到Sync.nonfairTryAcquireShared() */
        protected int tryAcquireShared(int acquires) { return nonfairTryAcquireShared(acquires); }
    }
    static final class FairSync extends Sync {
        /* 构造函数 */
        FairSync(int permits) { super(permits); }
        /* 获取锁并维护信号量(公平锁) */
        /* NonfairSync.tryAcquireShared()覆盖了Sync.tryAcquireShared()的逻辑 */
        protected int tryAcquireShared(int acquires) {
            while (true) {
                if (hasQueuedPredecessors()) { return -1; } /* 比Sync.tryAcquireShared()多出来这一行，询问队列中是否存在早于自己的线程 */
                int available_permits = getState();
                int remaining_permits = available_permits - acquires;
                if (remaining_permits < 0 || compareAndSetState(available_permits, remaining_permits)) { return remaining_permits; }
            }
        }
    }
    private final Sync sync;
    /* Sync构造方法 */
    public Semaphore(int permits) { sync = new NonfairSync(permits); }
    public Semaphore(int permits, boolean fair) { sync = fair ? new FairSync(permits) : new NonfairSync(permits); }
    
    /* API: 判断Semaphore的类型(公平锁/非公平锁) */
    public boolean isFair() { return sync instanceof FairSync; }
}
```

`Semaphore`提供了`acquire()`和`release()`方法用于占用和释放锁：

```java
class Semaphore implements java.io.Serializable {
	/* >>> 获取锁 <<< */
    /* API: 获取一个锁，可以因中断而被打断 */
    public void acquire() throws InterruptedException { sync.acquireSharedInterruptibly(1); }
    /* API: 获取permits个锁，可以因中断而被打断 */
    public void acquire(int permits) throws InterruptedException {
        if (permits < 0) { throw new IllegalArgumentException(); }
        sync.acquireSharedInterruptibly(permits);
    }
    /* API: 获取一个锁，不可被打断 */
    public void acquireUninterruptibly { sync.acquireShared(1); }
    /* API: 获取permits个锁，不可被打断 */
    public void acquireUninterruptibly(int permits) {
        if (permits < 0) { throw new IllegalArgumentException(); }
        sync.acquireShared(permits);
    }

	/* >>> 释放锁 <<< */
	/* API: 释放一个锁 */
    public void release() { sync.releaseShared(1); }
	/* API: 释放permits个锁 */
    public void release(int permits) {
        if (permits < 0) throw new IllegalArgumentException();
        sync.releaseShared(permits);
    }

	/* >>> 以下tryAcquire()方法由AbstractQueuedSynchronizer.acquire()调用 <<< */
    public boolean tryAcquire() { return sync.nonfairTryAcquireShared(1) >= 0; }
    public boolean tryAcquire(long timeout, TimeUnit unit) throws InterruptedException { return sync.tryAcquireSharedNanos(1, unit.toNanos(timeout)); }
    public boolean tryAcquire(int permits) {
        if (permits < 0) throw new IllegalArgumentException();
        return sync.nonfairTryAcquireShared(permits) >= 0;
    }
    public boolean tryAcquire(int permits, long timeout, TimeUnit unit) throws InterruptedException {
        if (permits < 0) throw new IllegalArgumentException();
        return sync.tryAcquireSharedNanos(permits, unit.toNanos(timeout));
    }
}
```

最后，`Semaphore`对`Sync`的方法做了封装，也对其父类`AbstractQueuedSynchronizer`的方法进行了封装，均暴露成API：

```java
public class JucMain {
	/* API: 等待队列是否非空，重定向到AbstractQueuedSynchronizer.hasQueuedThreads() */
    public final boolean hasQueuedThreads() { return sync.hasQueuedThreads(); }
    
    /* API: 等待队列长度，重定向到AbstractQueuedSynchronizer.getQueueLength() */
    public final int getQueueLength() {
        return sync.getQueueLength();
    }
    
    /* API: 等待队列中的所有节点，重定向到AbstractQueuedSynchronizer.getQueueThreads() */
    protected Collection<Thread> getQueuedThreads() { return sync.getQueuedThreads(); }
    public String toString() {
        return super.toString() + "[Permits = " + sync.getPermits() + "]";
    }

	/* API: 获取当前剩余资源数，重定向到Sync.gerPermits() */
    public int availablePermits() { return sync.getPermits(); }

	/* API: 重置所有可用资源为0，重定向到Sync.drainPermits() */
    public int drainPermits() { return sync.drainPermits(); }

	/* API: 扣减reduciton个可用资源，重定向到Sync.reducePermits() */
    protected void reducePermits(int reduction) {
        if (reduction < 0) throw new IllegalArgumentException();
        sync.reducePermits(reduction);
    }
}
```

以下是使用`Semaphore`的一个示例：三个线程抢占两个资源，每个线程先通过`semaphore.acquire()`抢占锁，再通过`semaphore.release()`释放锁。

```java
public class JucMain {
    static Semaphore semaphore = new Semaphore(2);
    public static void main(String[] args) throws InterruptedException {
        for (int i = 1; i <= 3; ++i) {
            Thread thread = new Thread(() -> {
                System.out.printf("[%s] waiting for semaphore...\n", Thread.currentThread().getName());
                try { semaphore.acquire(); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.printf("[%s] get semaphore.\n", Thread.currentThread().getName());
                try { Thread.sleep(100); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.printf("[%s] release semaphore.\n", Thread.currentThread().getName());
                semaphore.release();
            });
            thread.start();
        }
    }
}
/*
	[Thread-0] waiting for semaphore...
	[Thread-2] waiting for semaphore...
	[Thread-2] get semaphore.
	[Thread-1] waiting for semaphore...
	[Thread-0] get semaphore.
	[Thread-2] release semaphore.
	[Thread-0] release semaphore.
	[Thread-1] get semaphore.
	[Thread-1] release semaphore.
*/
```

## §4.3 循环屏障

循环屏障（`java.util.concurrent.CyclicBarrier`）用于让若干线程同时满足所有条件后，才同时开始继续执行。与闭锁（`CountDownLatch`）不同的是，循环屏障达到条件放行所有线程后，又恢复到原始状态，因此可以重复使用；循环屏障的`await()`等价于闭锁地`countDown()`与`await()`，也就是说循环屏障的`await()`是一个**阻塞方法**。同样都是让共享状态变量自减，然而一个线程可以多次调用`CountDownLatch.countDown()`，但是只能调用一次`CyclicBarrier.await()`。

`ReetrantLock`用于保护`Generation`节点和`count`共享变量防止被多个线程同时访问。

```java
class CyclicBarrier {
    private static class Generation { boolean broken = false; }
    private final ReentrantLock lock = new ReentrantLock();
    private final Condition trip = lock.newCondition();
    private final int parties; /* 倒计数器最大值 */
    private final Runnable barrierCommand; /* 触发点任务 */
    private Generation generation = new Generation();
    private int count; /* count由ReentrantLock保证一致性，无需volatile */

    public CyclicBarrier(int parties, Runnable barrierAction) {
        if (parties <= 0) throw new IllegalArgumentException();
        this.parties = parties;
        this.count = parties;
        this.barrierCommand = barrierAction;
    }
    public CyclicBarrier(int parties) {
        this(parties, null);
    }

    /* API: 返回循环屏障最大值parties */
    public int getParties() { return parties; }

    /* API: 循环屏障是否被异常情况破坏 */
    public boolean isBroken() {
        final ReentrantLock lock = this.lock; lock.lock();
        try { return generation.broken; } finally { lock.unlock(); }
    }

    /* 本次循环屏障成功，count==0，触发循环屏障的重置操作，准备开始下一次循环 */
    private void nextGeneration() {
        trip.signalAll(); /* 释放屏障的所有线程 */
        count = parties; /* 重置循环屏障共享状态变量 */
        generation = new Generation(); /* 重置Generation节点 */
    }

    /* 本次循环屏障失败(中断/超时/屏障动作异常)，触发循环屏障的清理操作 */
    private void breakBarrier() {
        generation.broken = true;
        count = parties;
        trip.signalAll();
    }

    /* API: 彻底重置循环屏障到初始状态 */
    public void reset() {
        final ReentrantLock lock = this.lock; lock.lock();
        try { breakBarrier(); nextGeneration(); } finally { lock.unlock(); }
    }

    /* API: 还需要多少次await()就能放行本次循环屏障 */
    public int getNumberWaiting() {
        final ReentrantLock lock = this.lock; lock.lock();
        try { return parties - count; } finally { lock.unlock(); }
    }

    /* await()共用的底层实现方法(有/无超时机制) */
    private int dowait(boolean timed, long nanos) throws InterruptedException, BrokenBarrierException, TimeoutException {
        final ReentrantLock lock = this.lock; lock.lock();
        try {
            final Generation cur_generation = generation;
            if (cur_generation.broken) { throw new BrokenBarrierException(); }
            if (Thread.interrupted()) { throw new InterruptedException(); }
            int index = --count;
            if (index == 0) { /* 如果倒计数器降为0，则执行触发任务 */
                Runnable command = barrierCommand;
                if (command != null) {
                    try {
                        command.run();
                    } catch (Throwable ex) {
                        breakBarrier();
                        throw ex;
                    }
                }
                nextGeneration(); /* 重置循环屏障到初始状态 */
                return 0;
            }
            while (true) { /* 陷入则色 */
                try {
                    if (!timed) {
                        trip.await();
                    } else if (nanos > 0L) {
                        nanos = trip.awaitNanos(nanos);
                    }
                } catch (InterruptedException ie) {
                    if (cur_generation == generation && !cur_generation.broken) {
                        breakBarrier();
                        throw ie;
                    } else {
                        Thread.currentThread().interrupt();
                    }
                }
            }
        } finally {
            lock.unlock();
        }
    }

    /* API: 无超时机制，重定向到dowait() */
    public int await() throws InterruptedException, BrokenBarrierException {
        try { return dowait(false, 0L); } catch (TimeoutException toe) { throw new Error(toe); }
    }
    /* API: 有超时机制，重定向到dowait() */
    public int await(long timeout, TimeUnit unit) throws InterruptedException, BrokenBarrierException, TimeoutException {
        return dowait(true, unit.toNanos(timeout));
    }
}
```

以下是使用循环屏障的一个示例。这里的`CyclicBarrier`设置为两个线程打包成一组。

```java
import java.util.concurrent.CyclicBarrier;

public class JucMain {
    static CyclicBarrier barrier = new CyclicBarrier(2, () -> {
        System.out.printf("[%s] barrier released.\n", Thread.currentThread().getName());
    });
    public static void main(String[] args) throws InterruptedException {
        for (int i = 1; i <= 4; i++) {
            Thread thread = new Thread(() -> {
                System.out.printf("[%s] waiting for barrier...\n", Thread.currentThread().getName());
                try { barrier.await(); Thread.sleep(500); } catch (Exception e) { throw new RuntimeException(e); }
                System.out.printf("[%s] finished.\n", Thread.currentThread().getName());
            });
            thread.start();
        }
    }
}
/*
	[Thread-0] waiting for barrier...
	[Thread-3] waiting for barrier...
	[Thread-2] waiting for barrier...
	[Thread-1] waiting for barrier...
	[Thread-2] barrier released.
	[Thread-1] barrier released.
	[Thread-1] finished.
	[Thread-2] finished.
	[Thread-3] finished.
	[Thread-0] finished.
*/
```

## §4.4 相位器

相位器（`java.util.concurrent.Phaser`）可以视为多个串行的闭锁。只有当所有已注册的线程都到达了某个阶段，相位器才会同时放行所有线程，直到都触及到下一个阶段。

相位器使用共享状态变量`volatile long state`，手动划分各个bit表示不同变量。

- `state`的0~15位（`state & 0x000000000000ffff`）：未到达参与者的数量
- `state`的16~31位（`state & 0x00000000ffff0000`）：总参与者的数量
- `state`的32~62位（`state & 0x7fffffff00000000`）：当前阶段数
- `state`的63位（`state & 0x8000000000000000`）：相位器终止位

```java
public class Phaser {
    private volatile long state;

    /* 参与者数量最大值 */
    private static final int  MAX_PARTIES     = 0xffff;
    /* 阶段数最大值 */
    private static final int  MAX_PHASE       = Integer.MAX_VALUE;

	/* 总参与者数量的bit偏移量 */
    private static final int  PARTIES_SHIFT   = 16;
    /* 当前阶段数的bit偏移量 */
    private static final int  PHASE_SHIFT     = 32;

	/* 未到达参与者数量的mask */
    private static final int  UNARRIVED_MASK  = 0xffff;
	/* 总参与者数量的mask */
    private static final long PARTIES_MASK    = 0xffff0000L;
    /* 未到达参与者数量与总参与者数量的mask，用于更新state */
    private static final long COUNTS_MASK     = 0xffffffffL;
    /* 相位器终止位的mask */
    private static final long TERMINATION_BIT = 1L << 63;

	/* 一次参与者到达事件对state的影响，用于更新state */
	private static final int  ONE_ARRIVAL     = 1;
	/* 一个参与者对state的影响，用于更新state */
	private static final int  ONE_PARTY       = 1 << PARTIES_SHIFT;
	/* 一个参与者注销对state的影响，用于更新state */
	private static final int  ONE_DEREGISTER  = ONE_ARRIVAL|ONE_PARTY;

	/* state的预定义常量，表示非法状态 */
	private static final int  EMPTY           = 1;

	/* 构造方法 */
    public Phaser() { this(null, 0); }
    public Phaser(int parties) { this(null, parties); }
    public Phaser(Phaser parent) { this(parent, 0); }
    public Phaser(Phaser parent, int parties) {
        if (parties >>> PARTIES_SHIFT != 0) /* 如果总参与者数量超过最大值，就报错 */
            throw new IllegalArgumentException("Illegal number of parties");
        int phase = 0;
        this.parent = parent;
        if (parent != null) {
            final Phaser root = parent.root;
            this.root = root;
            this.evenQ = root.evenQ;
            this.oddQ = root.oddQ;
            if (parties != 0)
                phase = parent.doRegister(1);
        } else {
            this.root = this;
            this.evenQ = new AtomicReference<QNode>();
            this.oddQ = new AtomicReference<QNode>();
        }
        /* 更新state状态值 */
        this.state = (parties == 0) ? (long)EMPTY :
            ((long)phase << PHASE_SHIFT) |
            ((long)parties << PARTIES_SHIFT) |
            ((long)parties);
    }

	/* 未到达参与者的数量 */
    private static int unarrivedOf(long s) { return ((int)s == EMPTY) ? 0 : ((int)s & UNARRIVED_MASK); }
	/* 总参与者的数量 */
    private static int partiesOf(long s) { return (int)s >>> PARTIES_SHIFT; }
	/* 当前阶段数的bit偏移量 */
    private static int phaseOf(long s) { return (int)(s >>> PHASE_SHIFT); }
    /* 已到达参与者的数量 */
    private static int arrivedOf(long s) { return ((int)s == EMPTY) ? 0 : ((int)s >>> PARTIES_SHIFT) - ((int)s & UNARRIVED_MASK); }
}
```

有了以上的比特位，我们就可以创建相应的修改逻辑：

```java
public class Phaser {

	/* >>> 注册参与者 <<< */
	/* 注册registrations个参与者 */
    private int doRegister(int registrations) {
        long adjust = ((long)registrations << PARTIES_SHIFT) | registrations;
        final Phaser parent = this.parent;
        int phase;
        while (true) {
            long s = (parent == null) ? state : reconcileState();
            
            /* 获取总参与者/未到达参与者的数量 */
            int counts = (int)s;
            int parties = counts >>> PARTIES_SHIFT;
            int unarrived = counts & UNARRIVED_MASK;
            
            /* 防止注册的参与者溢出 */
            if (registrations > MAX_PARTIES - parties)
                throw new IllegalStateException(badRegister(s));
            
            /* 获取当前阶段数 */
            phase = (int)(s >>> PHASE_SHIFT);
            if (phase < 0)
                break;
            
            
            if (counts != EMPTY) { /* 如果相位器不为空 */
                if (parent == null || reconcileState() == s) {
                    if (unarrived == 0) /* 若未达到参与者数量为0，就等待下一个阶段 */
                        root.internalAwaitAdvance(phase, null);
                    else if (STATE.compareAndSet(this, s, s + adjust)) /* 若存在未到达参与者 */
		                /* 修改state，将参与者和未到达参与者都+=1 */
                        break;
                }
            } else if (parent == null) { /* 如果相位器为空，且parent不存在 */
                long next = ((long)phase << PHASE_SHIFT) | adjust;
                if (STATE.compareAndSet(this, s, next)) /* 设置参与者数量为1 */
                    break;
            } else { /* 如果相位器为空，且parent存在 */
                synchronized (this) {               // 1st sub registration
                    if (state == s) {               // recheck under lock
                        phase = parent.doRegister(1);
                        if (phase < 0)
                            break;
                        while (!STATE.weakCompareAndSet(
		                    this, 
		                    s, 
		                    ((long)phase << PHASE_SHIFT) | adjust
		                )) {
                            s = state;
                            phase = (int)(root.state >>> PHASE_SHIFT);
                            // assert (int)s == EMPTY;
                        }
                        break;
                    }
                }
            }
        }
        return phase;
    }
    /* API: 注册一个参与者，重定向到doRegister() */
	public int register() { return doRegister(1); }

	/* >>> 参与者到达 <<< */
	/* API: 参与者到达并阻塞等待 */
    public int arriveAndAwaitAdvance() {
        final Phaser root = this.root;
        while (true) {
	        /* 获取状态变量state */
            long s = (root == this) ? state : reconcileState();
            
            /* 获取当前阶段数phase */
            int phase = (int)(s >>> PHASE_SHIFT);
            if (phase < 0)
                return phase;
            
            /* 获取总参与者+未到达参与者数量 */
            int counts = (int)s;
            int unarrived = (counts == EMPTY) ? 0 : (counts & UNARRIVED_MASK);
            if (unarrived <= 0)
                throw new IllegalStateException(badArrive(s));
            
            if (STATE.compareAndSet(this, s, s -= ONE_ARRIVAL)) {
	            /* 如果未达到参与者数量>1，则一起阻塞等待 */
                if (unarrived > 1) 
                    return root.internalAwaitAdvance(phase, null);
                
                if (root != this)
                    return parent.arriveAndAwaitAdvance();
                
                /* 获取总参与者数量 */
                long n = s & PARTIES_MASK;
                
                /* 如果本阶段恰好结束，则下一回合未到达参与者数量应该为总参与者数量 */
                int nextUnarrived = (int)n >>> PARTIES_SHIFT;
                
                /* 执行onAdvance()，判断是否要终止相位器 */
                if (onAdvance(phase, nextUnarrived))
                    n |= TERMINATION_BIT; /* 设置终止位 */
                else if (nextUnarrived == 0)
                    n |= EMPTY;
                else
                    n |= nextUnarrived; /* 设置未到达状态 */
                
                /* 更新当前阶段数+=1 */
                int nextPhase = (phase + 1) & MAX_PHASE;
                n |= (long)nextPhase << PHASE_SHIFT;
                
                /* 更新状态变量state */
                if (!STATE.compareAndSet(this, s, n))
                    return (int)(state >>> PHASE_SHIFT);
                
                releaseWaiters(phase);
                return nextPhase;
            }
        }
    }
	/* 参与者到达并注销自己 */
    private int doArrive(int adjust) {
        final Phaser root = this.root;
        while (true) {
            /* 获取状态信息并验证是否合法 */
            long s = (root == this) ? state : reconcileState();
            int phase = (int)(s >>> PHASE_SHIFT);
            if (phase < 0)
                return phase;
            int counts = (int)s;
            int unarrived = (counts == EMPTY) ? 0 : (counts & UNARRIVED_MASK);
            if (unarrived <= 0)
                throw new IllegalStateException(badArrive(s));
            
            /* 与doRegister()相似，只不过是s-=adjust */
            if (STATE.compareAndSet(this, s, s-=adjust)) {
                if (unarrived == 1) {
                    long n = s & PARTIES_MASK;  // base of next state
                    int nextUnarrived = (int)n >>> PARTIES_SHIFT;
                    if (root == this) {
                        if (onAdvance(phase, nextUnarrived))
                            n |= TERMINATION_BIT;
                        else if (nextUnarrived == 0)
                            n |= EMPTY;
                        else
                            n |= nextUnarrived;
                        int nextPhase = (phase + 1) & MAX_PHASE;
                        n |= (long)nextPhase << PHASE_SHIFT;
                        STATE.compareAndSet(this, s, n);
                        releaseWaiters(phase);
                    }
                    else if (nextUnarrived == 0) { // propagate deregistration
                        phase = parent.doArrive(ONE_DEREGISTER);
                        STATE.compareAndSet(this, s, s | EMPTY);
                    }
                    else
                        phase = parent.doArrive(ONE_ARRIVAL);
                }
                return phase;
            }
        }
    }
    public int arriveAndDeregister() {
        return doArrive(ONE_DEREGISTER);
    }
}
```


以下是使用相位器的一个示例。只有两个线程同时到达某个阶段，才可以同时放行，直到下一个阶段。

```java
import java.util.concurrent.Phaser;

public class JucMain {
    static Phaser phaser = new Phaser();
    public static void main(String[] args) throws InterruptedException {
        for (int i = 1; i <= 2; i++) {
            Thread thread = new Thread(() -> {
                phaser.register();
                System.out.printf("[%s] Executing in state 1...\n", Thread.currentThread().getName());
                phaser.arriveAndAwaitAdvance();
                System.out.printf("[%s] Executing in state 2...\n", Thread.currentThread().getName());
                phaser.arriveAndAwaitAdvance();
                System.out.printf("[%s] Executing in state 3...\n", Thread.currentThread().getName());
                phaser.arriveAndAwaitAdvance();
                System.out.printf("[%s] finished.\n", Thread.currentThread().getName());
                phaser.arriveAndDeregister();
            });
            thread.start();
        }
        while (!phaser.isTerminated()) {
            Thread.yield();
        }
        System.out.printf("[%s] pharser is terminated.\n", Thread.currentThread().getName());
    }
}
/*
	[Thread-0] Executing in state 1...
	[Thread-1] Executing in state 1...
	[Thread-1] Executing in state 2...
	[Thread-0] Executing in state 2...
	[Thread-0] Executing in state 3...
	[Thread-1] Executing in state 3...
	[Thread-1] finished.
	[Thread-0] finished.
	[main] pharser is terminated.
*/
```

## §4.5 交换器

交换器（`java.util.concurrent.Exchanger`）以两个线程为一组，同时放行并交换信息。

交换器提供了单槽模式和多槽模式，以下是创建的变量：

```java
public class Exchanger<V> {

    /* CPU数量/2，近似作为多槽模式的数量，详见构造函数的逻辑 */
    private final int ncpu;
    /* 多槽模式的最大数组索引，低8位表示索引，高24位表示版本号 */
    private volatile int bound;
    /* 多槽模式的支持的最大数组索引 */
    private static final int MMASK = 0xff;
    /* 版本号，负责叠加到bound上 */
    private static final int SEQ = MMASK + 1;
    /* 自旋等待最大次数 */
    private static final int SPINS = 1 << 10;

    /* 内部类，封装交换保存的信息 */
    static final class Node {
        long seed; /* 随机种子 */
        int index;
        Object item; /* 当前线程携带的信息 */
        volatile Object match; /* 另一个线程携带的信息 */
        volatile Thread parked; /* 阻塞线程 */
        Node() {
            index = -1;
            seed = Thread.currentThread().threadId();
        }
    }
    /* 单槽模式，定义了Node */
    static final class Slot { Exchanger.Node entry; }
    /* 多槽模式，定义了Node[] */
    private final Exchanger.Slot[] arena;

    /* 创建VarHandle供CAS使用 */
    private static final VarHandle BOUND; /* 控制Node.match（多槽模式的支持的最大数组索引） */
    private static final VarHandle MATCH; /* 控制Node.match（另一个线程携带的信息） */
    private static final VarHandle ENTRY; /* 控制Slot.entry */
    private static final VarHandle AA; /* 控制Exchanger.Slot[]（多槽模式的数组） */
    static {
        MethodHandles.Lookup l = MethodHandles.lookup();
        BOUND = MhUtil.findVarHandle(l, "bound", int.class);
        MATCH = MhUtil.findVarHandle(l, Exchanger.Node.class, "match", Object.class);
        ENTRY = MhUtil.findVarHandle(l, Exchanger.Slot.class, "entry", Exchanger.Node.class);
        AA = MethodHandles.arrayElementVarHandle(Exchanger.Slot[].class);
    }

    /* 用于保存本地线程变量 */
    static final class Participant extends ThreadLocal<Exchanger.Node> {
        public Exchanger.Node initialValue() { return new Exchanger.Node(); }
    }
    private static final Exchanger.Participant participant = new Exchanger.Participant();

    /* 构造函数 */
    public Exchanger() {
        int h = (ncpu = Runtime.getRuntime().availableProcessors()) >>> 1;
        int size = (h == 0) ? 1 : (h > MMASK) ? MMASK + 1 : h;
        (arena = new Exchanger.Slot[size])[0] = new Exchanger.Slot();
    }
}
```

现在来看`exchange()`方法的实现：

```java
public class Exchanger<V> {
	/* exchange()的底层方法 */
    private final V xchg(V x, long deadline) throws InterruptedException, TimeoutException {
        /* 获取Exchanger实例的信息 */
        Exchanger.Slot[] cur_arena = arena;
        int cur_arena_len = cur_arena.length;
        Exchanger.Participant cur_participant = participant;
        /* 为了区分对方尚未调用exchange()和exchange(null)两种情况，我们使用一个非null的哨兵对象做区分 */
        Object item = (x == null) ? cur_participant : x;

        /* 获取当前线程ThreadLocal共用的Node */
        Exchanger.Node cur_node = cur_participant.get();

        int cur_index = cur_node.index;
        int misses = 0; /* CAS失败次数，用于控制arena的扩容 */
        Object offered = null; /* 当前线程是否将自己的Node放入了槽位 */
        Object cur_slot_entry_item = null; /* 从另一个线程接受的交换数据 */
        outer: while (true) {
            int cur_bound; /* 当前读取bound值 */
            int cur_bound_max; /* 当前arena的最大可用索引 */
            Exchanger.Slot cur_slot; Exchanger.Node cur_slot_entry;

            /* 如果最大索引cur_bound_max位0，则说明是单槽模式，所有线程都使用arena[0] */
            if ((cur_bound_max = (cur_bound = bound) & MMASK) == 0) { cur_index = 0; }

            if ( /* 如果槽位失效，就随机混淆生成新索引 */
                cur_index < 0 || /* 上一轮发生冲突，索引重置为-1 */
                cur_index > cur_bound_max || /* arena收缩，数组越界 */
                cur_index >= cur_arena_len || /* cur_index超出了理论大小，防御性代码 */
                (cur_slot = cur_arena[cur_index]) == null /* 槽位仍未null，未初始化 */
            ) {
                long r = cur_node.seed;
                r ^= r << 13; r ^= r >>> 7; r ^= r << 17;
                cur_index = cur_node.index = (int)((cur_node.seed = r) % (cur_bound_max + 1));
            } else if ((cur_slot_entry = cur_slot.entry) != null) { /* 如果槽位合法且已有线程，说明当前线程可以与其交换 */
                if (ENTRY.compareAndSet(cur_slot, cur_slot_entry, null)) { /* 把s.entry从q置为null */
                    /* 完成线程见的信息交换 */
                    cur_slot_entry_item = cur_slot_entry.item;
                    cur_slot_entry.match = item;
                    /* 如果槽位内的线程自己阻塞了自己，则需要唤醒 */
                    Thread cur_parked_thread;
                    if (cur_index == 0 && (cur_parked_thread = cur_slot_entry.parked) != null) {
                        LockSupport.unpark(cur_parked_thread);
                    }
                    break;
                } else { /* 把s.entry从q置为null失败，CAS冲突 */
                    int cur_new_bound;
                    cur_index = -1; /* 这一轮发生冲突，索引重置为-1 */
                    if (cur_bound != bound) { /* 如果bound被其他线程更新，则重置misses计数器 */
                        misses = 0;
                    } else if (misses <= 2) { /* 如果bound不变，且CAS冲突次数较少，则可以继续尝试 */
                        ++misses;
                    } else if ((cur_new_bound = (cur_bound + 1) & MMASK) < cur_arena_len) { /*如果bound不变，且CAS冲突次数较少,则需要扩种arena*/
                        misses = 0;
                        if (
                            /* 增加最大可用索引+=1，并更新版本号，防止ABA问题 */    
                            BOUND.compareAndSet(this, cur_bound, cur_bound + 1 + SEQ) &&
                            /* 新的槽位从未被初始化过，因此有责任要初始化赋值 */
                            cur_arena[cur_index = cur_node.index = cur_new_bound] == null
                        ) { 
                            AA.compareAndSet(cur_arena, cur_new_bound, null, new Exchanger.Slot()); 
                        }
                    }
                }
            } else { /* 如果此时槽位的entry是null，说明自己是先到的，需要把自己放进槽位并等待 */
                /* 首次尝试提供交换值给交换器 */
                if (offered == null) { offered = cur_node.item = item; }
                
                /* 把当前线程的Node赋给空槽位 */
                if (ENTRY.compareAndSet(cur_slot, null, cur_node)) {
                    boolean tryCancel; /* 当前线程是否被中断 */
                    Thread t = Thread.currentThread();
                    if (
                        !(tryCancel = t.isInterrupted()) && /* 当前线程未被中断 */
                        ncpu > 1 && /* 单核CPU咨询没有意义 */
                        (cur_index != 0 || (!ForkJoinWorkerThread.hasKnownQueuedWork())) /* 多槽模式或非繁忙虚拟线程的单槽模式 */
                    ) {
                        for (int j = SPINS; j > 0; --j) { /* 尝试自旋，至多SPINS=1024次 */
                            if ((cur_slot_entry_item = cur_node.match) != null) {
                                MATCH.set(cur_node, null);
                                break outer;     // spin wait
                            }
                            Thread.onSpinWait();
                        }
                    }
                    for (long ns = 1L;;) { /* 超过自选次数上限，只能阻塞或取消 */
                        /* 再给一次自旋机会 */
                        if ((cur_slot_entry_item = cur_node.match) != null) {
                            MATCH.set(cur_node, null);
                            break outer;
                        }
                        
                        if ( /* 阻塞 */
                            cur_index == 0 && /* 单槽模式才能阻塞 */ 
                            !tryCancel && /* 当前线程未被中断 */
                            (deadline == 0L || ((ns = deadline - System.nanoTime()) > 0L)) /* 未设置超时或仍未超时 */
                        ) {
                            cur_node.parked = t;
                            if (cur_node.match == null) {
                                if (deadline == 0L)
                                    LockSupport.park(this);
                                else
                                    LockSupport.parkNanos(this, ns);
                                tryCancel = t.isInterrupted();
                            }
                            cur_node.parked = null;
                        }
                        else if (ENTRY.compareAndSet(cur_slot, cur_node, null)) { /* 取消 */
                            offered = cur_node.item = null;
                            if (Thread.interrupted())
                                throw new InterruptedException();
                            if (deadline != 0L && ns <= 0L)
                                throw new TimeoutException();
                            cur_index = -1;
                            if (bound != cur_bound)
                                misses = 0;
                            else if (misses >= 0)
                                --misses;
                            else if ((cur_bound & MMASK) != 0) { /* 如果misses<0，说明竞争压力变小，可以收缩arena*/
                                misses = 0;
                                BOUND.compareAndSet(this, cur_bound, cur_bound - 1 + SEQ);
                            }
                            continue outer;
                        }
                    }
                }
            }
        }
        if (offered != null) { /* 无论交换是否成功，交换已经结束，需要清理交换值 */
            cur_node.item = null;
        }
        /* 使用哨兵对象，判断交换值是否本身就是null */
        @SuppressWarnings("unchecked") V ret = (cur_slot_entry_item == participant) ? null : (V)cur_slot_entry_item;
        return ret;
    }
	/* API: 交换信息，重定向到xchg() */
    public V exchange(V x) throws InterruptedException {
        try { return xchg(x, 0L); } catch (TimeoutException cannotHappen) { return null; }
    }
    /* API: 交换信息，并启用超时机制，重定向到xchg() */
    public V exchange(V x, long timeout, TimeUnit unit) throws InterruptedException, TimeoutException {
        long d = unit.toNanos(timeout) + System.nanoTime();
        return xchg(x, (d == 0L) ? 1L : d);
    }
}
```

以下是使用交换器的一个示例。每两个线程同时由交换器放行，并交换信息。

```java
import java.util.concurrent.Exchanger;

public class JucMain {
    static Exchanger<String> exchanger = new Exchanger<>();
    public static void main(String[] args) throws InterruptedException {
        for (int i = 1; i <= 4; i++) {
            Thread thread = new Thread(() -> {
                String bio = String.format("Hello, I'm %s!", Thread.currentThread().getName());
                String bio_exchanged = null;
                try { bio_exchanged = exchanger.exchange(bio); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.printf("[%s] Received an exchanged message: %s\n", Thread.currentThread().getName(), bio_exchanged);
            });
            thread.start();
        }
    }
}
/*
	[Thread-3] Received an exchanged message: Hello, I'm Thread-0!
	[Thread-2] Received an exchanged message: Hello, I'm Thread-1!
	[Thread-0] Received an exchanged message: Hello, I'm Thread-3!
	[Thread-1] Received an exchanged message: Hello, I'm Thread-2!
*/
```

# §5 原子类

我们已经知道，`volatile`只能保证可见性，不能保证原子性；`synchronized`通过阻塞的方式实现了原子性，是一种**悲观锁**；CAS与`volatile`组合使用可以通过自旋实现无锁的高吞吐量原子性，是一种**乐观锁**。`java.util.concurrent.atomic`包提供了一种CAS与`volatile`组合使用的实现。

基准测试证明，原子类的执行效率的确高于`synchronized`锁：

```java
import java.util.concurrent.atomic.AtomicInteger;

public class JucMain {
    static Integer count_synchronized = 0;
    public static void main(String[] args) throws InterruptedException {
        long startTimeMillis = System.currentTimeMillis();
        for (int i = 1; i <= 10; i++) {
            Thread thread = new Thread(() -> {
                for (int j = 1; j <= 1000000; j++) {
                    synchronized (JucMain.class) {
                        ++count_synchronized;
                    }
                }
            });
            thread.start();
        }
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            long endTimeMillis = System.currentTimeMillis();
            System.out.printf("count = %d with time cost = %dms\n", count_synchronized, endTimeMillis - startTimeMillis);
        }));
    }
}

public class JucMain {  
    static AtomicInteger count_atomic = new AtomicInteger(0);  
    public static void main(String[] args) throws InterruptedException {  
        long startTimeMillis = System.currentTimeMillis();  
        for (int i = 1; i <= 10; i++) {  
            Thread thread = new Thread(() -> {  
                for (int j = 1; j <= 1000000; j++) {  
                    count_atomic.getAndAdd(1);  
                }  
            });  
            thread.start();  
        }  
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {  
            long endTimeMillis = System.currentTimeMillis();  
            System.out.printf("count = %d with time cost = %dms\n", count_atomic.get(), endTimeMillis - startTimeMillis);  
        }));  
    }  
}

/*
	Synchronized: count = 10000000 with time cost = 277ms
	AtomicInteger: count = 10000000 with time cost = 182ms
*/
```

## §5.1 原子数

`java.util.concurrent.atomic`提供了一系列继承自`java.lang.Number`的子类，它们将对应的数据类型包装成对应的原子类。例如`AtomicBoolean`、`AtomicInteger`、`AtomicLong`、`AtomicDouble`。

以下是`AtomicInteger`的JDK实现代码：

```java
public class AtomicInteger extends Number implements java.io.Serializable {

	/* Unsafe实例 */
    private static final Unsafe U = Unsafe.getUnsafe();

	/* value的Getter/Setter/OFFSET */
    private volatile int value;
    private static final long VALUE = U.objectFieldOffset(AtomicInteger.class, "value");
    public final int get() { return value; }
    public final void set(int newValue) { value = newValue; }

    public AtomicInteger() { }
    public AtomicInteger(int initialValue) { value = initialValue; }
    
    public final void lazySet(int newValue) {
        U.putIntRelease(this, VALUE, newValue);
    }

    public final int getAndSet(int newValue) { return U.getAndSetInt(this, VALUE, newValue); }
    public final boolean compareAndSet(int expectedValue, int newValue) { return U.compareAndSetInt(this, VALUE, expectedValue, newValue); }
    public final int getAndIncrement() { return U.getAndAddInt(this, VALUE, 1); }
    public final int getAndDecrement() { return U.getAndAddInt(this, VALUE, -1); }
    public final int incrementAndGet() { return U.getAndAddInt(this, VALUE, 1) + 1; }
    public final int decrementAndGet() { return U.getAndAddInt(this, VALUE, -1) - 1; }
    public final int getAndAdd(int delta) { return U.getAndAddInt(this, VALUE, delta); }
    public final int addAndGet(int delta) { return U.getAndAddInt(this, VALUE, delta) + delta; }

    /* Java 8新增的函数式原子更新方法，可以传入一个java.util.function.IntUnaryOperato型函数 */
    public final int getAndUpdate(IntUnaryOperator updateFunction) {
        int prev = get(), next = 0;
        for (boolean haveNext = false;;) {
            if (!haveNext)
                next = updateFunction.applyAsInt(prev);
            if (weakCompareAndSetVolatile(prev, next))
                return prev;
            haveNext = (prev == (prev = get()));
        }
    }
    public final int updateAndGet(IntUnaryOperator updateFunction) {
        int prev = get(), next = 0;
        for (boolean haveNext = false;;) {
            if (!haveNext)
                next = updateFunction.applyAsInt(prev);
            if (weakCompareAndSetVolatile(prev, next))
                return next;
            haveNext = (prev == (prev = get()));
        }
    }
    public final int getAndAccumulate(int x, IntBinaryOperator accumulatorFunction) {
        int prev = get(), next = 0;
        for (boolean haveNext = false;;) {
            if (!haveNext)
                next = accumulatorFunction.applyAsInt(prev, x);
            if (weakCompareAndSetVolatile(prev, next))
                return prev;
            haveNext = (prev == (prev = get()));
        }
    }
    public final int accumulateAndGet(int x, IntBinaryOperator accumulatorFunction) {
        int prev = get(), next = 0;
        for (boolean haveNext = false;;) {
            if (!haveNext)
                next = accumulatorFunction.applyAsInt(prev, x);
            if (weakCompareAndSetVolatile(prev, next))
                return next;
            haveNext = (prev == (prev = get()));
        }
    }

    public String toString() { return Integer.toString(get()); }

    public int intValue() { return get(); }
    public long longValue() { return (long)get(); }
    public float floatValue() { return (float)get(); }
    public double doubleValue() { return (double)get(); }
}
```

## §5.2 原子引用

除了`java.lang.Number`以外，我们也可以使用`AtomicReference<T>`包装所有数据类型成原子类。这使得我们不能再像往常那样调用`T object`的实例方法，而是只能不断地创建新的`T object_new`来覆盖写入，这个过程需要我们手动调用原子引用提供的CAS方法，并手写自旋。

```java
import java.math.BigDecimal;
import java.util.concurrent.atomic.AtomicReference;

public class JucMain {
    static AtomicReference<BigDecimal> atomic_count = new AtomicReference<>(new BigDecimal(0));
    public static void main(String[] args) throws InterruptedException {
        for (int i = 1; i <= 10; ++i) {
            Thread thread = new Thread(() -> {
                for (int j = 1; j <= 1000000; ++j) {
                    BigDecimal current_count = new BigDecimal(j);
                    BigDecimal next_count = new BigDecimal(j);
                    do {
                        current_count = atomic_count.get();
                        next_count = current_count.add(new BigDecimal(1));
                    } while (!atomic_count.compareAndSet(current_count, next_count));
                }
            });
            thread.start();
        }
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.out.printf("count = %d", atomic_count.get().intValue());
        }));
    }
}
/* count = 10000000 */
```

## §5.3 原子数组

Java提供了针对整型、长整型和原子引用的院子数组类`AtomicIntegerArray`、`AtomicLongArray`、`AtomicReferenceArray`。

```java
import java.util.concurrent.atomic.AtomicIntegerArray;

public class JucMain {
    static AtomicIntegerArray atomicIntegerArray = new AtomicIntegerArray(2);
    public static void main(String[] args) throws InterruptedException {
        for (int i = 1; i <= 10; ++i) {
            Thread thread = new Thread(() -> {
                for (int j = 1; j <= 1000000; ++j) {
                    atomicIntegerArray.getAndAdd(0, 1);
                    atomicIntegerArray.getAndAdd(1, 1);
                }
            });
            thread.start();
        }
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.out.printf("atomicIntegerArray = {%d, %d}", atomicIntegerArray.get(0), atomicIntegerArray.get(1));
        }));
    }
}
/*
	atomicIntegerArray = {10000000, 10000000}
*/
```

## §5.4 原子变量更新器