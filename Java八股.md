
| 参考文献                                                      |     |
| --------------------------------------------------------- | --- |
| [小林Coding(Java面试题)](https://xiaolincoding.com/interview/) |     |

# §1 Java基础

# §2 Java集合

## §2.A 编程题

### 手写HashMap

手写HashMap，只要求实现最基本的插入和查找操作。这里我们使用哈希映射到`Entries[]`数组+链表尾插法。

```java
class CustomizedHashMap<K, V> {

    static class Entry<K, V> {
        K key; V value; Entry<K, V> next;
        public Entry(K key, V value) {
            this.key = key; this.value = value; this.next = null;
        }
    }
    private Entry<K, V>[] entries;


    private static final int INITIAL_CAPACITY = 16;
    @SuppressWarnings("unchecked") public CustomizedHashMap(int capacity) {
        entries = (Entry<K, V>[]) new Entry[capacity];
    }
    public CustomizedHashMap() {
        this(INITIAL_CAPACITY);
    }


    private int getIndex(K key) { return key.hashCode() & 0x7FFFFFFF % entries.length; }
    public void put(K key, V value) {
        Entry<K, V> entry = new Entry<>(key, value);
        int index = getIndex(key);
        Entry<K, V> existEntry = entries[index];
        if (existEntry == null) {
            entries[index] = entry;
        } else {
            while(existEntry.next != null) {
                if(!existEntry.key.equals(key)) {
                    existEntry = existEntry.next; continue;
                }
                existEntry.value = value; return;
            }
            if(existEntry.key.equals(key)) {
                existEntry.value = value; return;
            }
            existEntry.next = entry;
        }
    }
    public V get(K key) {
        int index = getIndex(key);
        Entry<K, V> existEntry = entries[index];
        while(existEntry != null) {
            if(existEntry.key.equals(key)) {
                return existEntry.value;
            }
            existEntry = existEntry.next;
        }
        return null;
    }
    public void remove(K key) {
        int index = getIndex(key);
        Entry<K, V> existEntry = entries[index];
        if(existEntry == null) { return; } // 特判空链表
        if(existEntry.key.equals(key)) { entries[index] = existEntry.next; return; } // 特判头结点
        Entry<K, V> prevEntry = existEntry, curEntry = existEntry.next;
        while(curEntry != null) {
            if(curEntry.key.equals(key)) {
                prevEntry.next = curEntry.next;
                return;
            }
            prevEntry = curEntry; curEntry = curEntry.next;
        }
    }
}
```

# §3 Java并发

## §3.A 编程题

### 两个线程交替打印奇偶数

1. 使用`wait()/notify()`。

```java
public class SingletonDemo {  
    private static int count = 0;  
    public static void main(String[] args) {  
        Object lock = new Object();  
        Thread thread_1 = new Thread(() -> {  
            while(true) {  
                synchronized (lock) {  
                    while(count % 2 == 1) {  
                        try { lock.wait(); } catch (InterruptedException e) { throw new RuntimeException(e); }  
                    }  
                    System.out.println(count++);  
                    lock.notifyAll();  
                }  
            }  
        });  
        Thread thread_2 = new Thread(()->{  
            while(true) {  
                synchronized (lock) {  
                    while(count % 2 == 0) {  
                        try { lock.wait(); } catch (InterruptedException e) { throw new RuntimeException(e); }  
                    }  
                    System.out.println(count++);  
                    lock.notifyAll();  
                }  
            }  
        });  
        thread_1.start();  
        thread_2.start();  
    }  
}
```

2. 使用`Semaphore`。

```java
public class SingletonDemo {
    private static Semaphore semaphore_1 = new Semaphore(1);
    private static Semaphore semaphore_2 = new Semaphore(0);
    private static int count = 0;
    public static void main(String[] args) {
        Thread thread_1 = new Thread(() -> {
            while(true) {
                try { semaphore_1.acquire(); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.println(count++);
                semaphore_2.release();
            }
        });
        Thread thread_2 = new Thread(()->{
            while(true) {
                try { semaphore_2.acquire(); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.println(count++);
                semaphore_1.release();
            }
        });
        thread_1.start();
        thread_2.start();
    }
}
```

### 三个线程交替打印ABC

1. 使用`Semaphore`。

```java
public class Main {
    private static Semaphore semaphore_1 = new Semaphore(1);
    private static Semaphore semaphore_2 = new Semaphore(0);
    private static Semaphore semaphore_3 = new Semaphore(0);
    private static int count = 0;
    public static void main(String[] args) {
        Thread thread_1 = new Thread(()->{
            while(true) {
                try { semaphore_1.acquire(); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.println("A");
                semaphore_2.release();
            }
        });
        Thread thread_2 = new Thread(()->{
            while(true) {
                try { semaphore_2.acquire(); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.println("B");
                semaphore_3.release();
            }
        });
        Thread thread_3 = new Thread(()->{
            while(true) {
                try { semaphore_3.acquire(); } catch (InterruptedException e) { throw new RuntimeException(e); }
                System.out.println("C");
                semaphore_1.release();
            }
        });
        thread_1.start();
        thread_2.start();
        thread_3.start();
    }
}
```

2. 使用`ReentrantLock`与`Condition`。

```java
public class Main {
    private static ReentrantLock reentrantLock = new ReentrantLock();
    private static Condition condition_1 = reentrantLock.newCondition();
    private static Condition condition_2 = reentrantLock.newCondition();
    private static Condition condition_3 = reentrantLock.newCondition();
    private static int state = 0;
    public static void main(String[] args) {
        Thread thread_1 = new Thread(() -> {
            while(true) {
                reentrantLock.lock();
                while(state % 3 != 0) { try { condition_1.await(); } catch (InterruptedException e) { throw new RuntimeException(e); } }
                System.out.println("A"); ++state;
                condition_2.signalAll();
                reentrantLock.unlock();
            }
        });
        Thread thread_2 = new Thread(()->{
            while(true) {
                reentrantLock.lock();
                while(state % 3 != 1) { try { condition_2.await(); } catch (InterruptedException e) { throw new RuntimeException(e); } }
                System.out.println("B"); ++state;
                condition_3.signalAll();
                reentrantLock.unlock();
            }
        });
        Thread thread_3 = new Thread(()->{
            while(true) {
                reentrantLock.lock();
                while(state % 3 != 2) { try { condition_3.await(); } catch (InterruptedException e) { throw new RuntimeException(e); } }
                System.out.println("C"); ++state;
                condition_1.signalAll();
                reentrantLock.unlock();
            }
        });
        thread_1.start();
        thread_2.start();
        thread_3.start();
    }
}
```

### 高性能并发安全自增计数器

1. 原子类`AtomicInteger`：通过乐观锁CAS实现，但是高竞争时CPU空转，缓存失效率高。

```java
public class Main {
    public static AtomicInteger counter = new AtomicInteger();
    public static void main(String[] args) throws InterruptedException {
        ExecutorService executorService = Executors.newFixedThreadPool(100);
        // long start_time = System.currentTimeMillis();
        for(int i = 1; i <= 100; ++i) {
            executorService.submit(()->{
                for(int j = 1; j <= 100; ++j) { counter.getAndIncrement(); }
            });
        }
        executorService.shutdown();
        executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        // long end_time = System.currentTimeMillis();
        System.out.println("Counter: " + counter.get());
        // System.out.println("Time cost: " + (end_time - start_time)); // 224ms
    }
}
```

2. 原子类`LongAdder`：拆分成若干`Cell[] { volatile long; }`

```java
public class Main {
    public static LongAdder counter = new LongAdder();
    public static void main(String[] args) throws InterruptedException {
        ExecutorService executorService = Executors.newFixedThreadPool(100);
        // long start_time = System.currentTimeMillis();
        for(int i = 1; i <= 100; ++i) {
            executorService.submit(()->{
                for(int j = 1; j <= 100000; ++j) { counter.add(1); }
            });
        }
        executorService.shutdown();
        executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        // long end_time = System.currentTimeMillis();
        System.out.println("Counter: " + counter.sum());
        // System.out.println("Time cost: " + (end_time - start_time)); // 54ms
    }
}
```

### 三个线程指定执行顺序

1. `join()`

```java
public class Main {
    public static void main(String[] args) throws InterruptedException {
        Thread thread_1 = new Thread(()->{
            System.out.printf("%s: Done.\n", Thread.currentThread().getName());
        });
        Thread thread_2 = new Thread(()->{
            try { thread_1.join(); } catch (InterruptedException e) { throw new RuntimeException(e); }
            System.out.printf("%s: Done.\n", Thread.currentThread().getName());
        });
        Thread thread_3 = new Thread(()->{
            try { thread_2.join(); } catch (InterruptedException e) { throw new RuntimeException(e); }
            System.out.printf("%s: Done.\n", Thread.currentThread().getName());
        });
        thread_1.start();
        thread_2.start();
        thread_3.start();
    }
}
```

2. `CountDownLatch`

```java
public class Main {
    public static CountDownLatch countDownLatch_1 = new CountDownLatch(1);
    public static CountDownLatch countDownLatch_2 = new CountDownLatch(1);
    public static void main(String[] args) throws InterruptedException {
        Thread thread_1 = new Thread(()->{
            System.out.printf("%s: Done.\n", Thread.currentThread().getName());
            countDownLatch_1.countDown();
        });
        Thread thread_2 = new Thread(()->{
            try { countDownLatch_1.await(); } catch (InterruptedException e) { throw new RuntimeException(e); }
            System.out.printf("%s: Done.\n", Thread.currentThread().getName());
            countDownLatch_2.countDown();
        });
        Thread thread_3 = new Thread(()->{
            try { countDownLatch_2.await(); } catch (InterruptedException e) { throw new RuntimeException(e); }
            System.out.printf("%s: Done.\n", Thread.currentThread().getName());
        });
        thread_1.start();
        thread_2.start();
        thread_3.start();
    }
}
```

3. `CompletableFuture`

```java
public class Main {
    public static void main(String[] args) {
        CompletableFuture<Void> future_1 = CompletableFuture.runAsync(()->{
            System.out.println("A");
        });
        CompletableFuture<Void> future_2 = future_1.thenRunAsync(()->{
            System.out.println("B");
        });
        CompletableFuture<Void> future_3 = future_2.thenRunAsync(()->{
            System.out.println("C");
        });
    }
}
```

### 生产者与消费者的等待队列模型

使用`BlockingQueue`。

```java
public class SingletonDemo {
    private static final Integer SIZE_MAX = 5;
    private static final BlockingQueue<Integer> queue = new ArrayBlockingQueue<Integer>(SIZE_MAX);
    static class Producer {
        private static void produce(Integer item) throws InterruptedException {
            synchronized (queue) {
                while(queue.size() == SIZE_MAX) { queue.wait(); }
                queue.put(item);
                queue.notifyAll();
            }
        }
    }
    static class Consumer {
        private static void consume() throws InterruptedException {
            synchronized (queue) {
                while(queue.size() == 0) { queue.wait(); }
                Integer item = queue.take(); System.out.println(item);
                queue.notifyAll();
            }
        }
    }
    public static void main(String[] args) {
        Thread producer_thread = new Thread(()->{
            for(int i = 1; i <= 100; ++i) {
                try { Producer.produce(i); } catch (InterruptedException e) { throw new RuntimeException(e); }
            }
        });
        Thread consumer_thread = new Thread(()->{
            for(int i = 1; i <= 100; ++i) {
                try { Consumer.consume(); } catch (InterruptedException e) { throw new RuntimeException(e); }
            }
        });
        producer_thread.start();
        consumer_thread.start();
    }
}
```

### 手写线程池

```java
class YanerThreadPool {

    static class YanerWorkerThread extends Thread {
        private final BlockingQueue<Runnable> taskQueue;
        private final long keepAliveTime;
        private final List<YanerWorkerThread> threads;
        public YanerWorkerThread(BlockingQueue<Runnable> taskQueue, long keepAliveTime, List<YanerWorkerThread> threads) {
            this.taskQueue = taskQueue;
            this.keepAliveTime = keepAliveTime;
            this.threads = threads;
        }
        @Override public void run() {
            long lastActiveTime = System.currentTimeMillis();
            while(!Thread.currentThread().isInterrupted() && !taskQueue.isEmpty()) {
                try {
                    Runnable task = taskQueue.poll(keepAliveTime, TimeUnit.MILLISECONDS);
                    if(task == null && System.currentTimeMillis() - lastActiveTime >= keepAliveTime) {
                        threads.remove(this); break; // 超时终止进程
                    } else if(task != null) {
                        task.run(); continue;
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    threads.remove(this);
                }
            }
        }
    }

    interface YanerRejectedExecutionHandler {
        void rejectedExecution(Runnable runnable, YanerThreadPool threadPool);
    }
    static class DiscardPolicy implements YanerRejectedExecutionHandler {
        @Override public void rejectedExecution(Runnable runnable, YanerThreadPool threadPool) { ; /* 直接忽略 */ }
    }
    static class AbortPolicy implements YanerRejectedExecutionHandler {
        @Override public void rejectedExecution(Runnable runnable, YanerThreadPool threadPool) { throw new RuntimeException("TaskQueue is full"); }
    }

    private final int initSize;
    private final int maxSize;
    private final int coreSize;
    private final int queueSize;
    private final BlockingQueue<Runnable> taskQueue;
    private final List<YanerWorkerThread> threads;
    private final YanerRejectedExecutionHandler rejectedExecutionHandler;
    private final long keepAliveTime;
    private volatile boolean isShutdown = false;
    public YanerThreadPool(int initSize, int maxSize, int coreSize, int queueSize, YanerRejectedExecutionHandler rejectedExecutionHandler, long keepAliveTime) {
        this.initSize = initSize;
        this.maxSize = maxSize;
        this.coreSize = coreSize;
        this.queueSize = queueSize;
        this.taskQueue = new LinkedBlockingQueue<>(queueSize);
        this.threads = new ArrayList<>(initSize);
        this.rejectedExecutionHandler = rejectedExecutionHandler;
        this.keepAliveTime = keepAliveTime;
        for(int i = 0; i < this.initSize; ++i) {
            YanerWorkerThread workerThread = new YanerWorkerThread(taskQueue, keepAliveTime, threads);
            workerThread.start();
            threads.add(workerThread);
        }
    }
    public YanerThreadPool() {
        this(4, 16, 8, 256, new AbortPolicy(), 3000);
    }

    private void addWorkerThread(Runnable task) throws InterruptedException {
        YanerWorkerThread workerThread = new YanerWorkerThread(taskQueue, keepAliveTime, threads);
        workerThread.start();
        threads.add(workerThread);
        taskQueue.put(task);
    }
    public void execute(Runnable task) throws InterruptedException {
        if(isShutdown) { throw new IllegalStateException("CustomizedThreadPool has been shutdown"); }
        if(threads.size() < coreSize) { addWorkerThread(task); return; } // 如果线程数量<核心线程数, 则创建核心线程
        boolean isSuccess = taskQueue.offer(task);
        if(!isSuccess) {
            if(threads.size() < maxSize) { addWorkerThread(task); return; } // 如果队列添加失败, 且未达线程数上限, 则创建新线程
            rejectedExecutionHandler.rejectedExecution(task, this); // 如果队列添加失败, 且已达线程数上限, 则执行拒绝策略
        }
    }
    public void shutdown() {
        this.isShutdown = true;
        for(int i = 0; i < this.initSize; ++i) {
            this.threads.get(i).interrupt();
        }
    }
    public List<Runnable> shutdownNow() {
        this.isShutdown = true;

        List<Runnable> remainedTasks = new ArrayList<>();
        this.taskQueue.drainTo(remainedTasks);

        for(int i = 0; i < this.initSize; ++i) {
            this.threads.get(i).interrupt();
        }
        return remainedTasks;
    }
}
```

# §4 JVM

> OOM怎么办？
> 
> 1. JVM启动时使用参数`-XX:+HeapDumpOnOutOfMemoryError -XX:HeapDumpPath=<DUMP路径>`。
> 2. JVM运行中`jmap -dump:format=b,file=<DUMP路径> <PID>`。

> 死锁怎么办？
> 
> `jstack <PID>`会自动检测死锁。

> 频繁Full GC怎么办？
> 
> 1. JVM启动时使用参数`-XX:+PrintGCDetails -XX:+PrintGCDateStamps -Xloggc:<GC日志路径>`
> 2. 使用GCViewer分析各代占用时间图，观察GC频率
> 3. 生成堆转储文件，查看异常代中的变量空间占用情况，定位变量的具体代码位置。

### 什么是TLAB？（面试鸭）

JVM会为每个线程分配一小块堆内存，称为TLAB（Thread Local Allocation Buffer），用于加速内存分配，避免多线程竞争堆内存的开销。每个线程优先从自己的TLAB中分配内存，当TLAB内存耗尽时，向Eden区申请一个新的TLAB，当分配的内存超过阈值时，直接在Eden区分配。

### 什么是常量池？（面试鸭）

常量池有两种：运行时常量池、字符串常量池。运行时常量池存储每个类或接口的编译时常量信息，放到方法区/元空间；字符串常量池从JDK 7开始引入，存储字符串字面量，放在堆内存。常量池的优点在于减少创建重复对象，节省内存，提高效率。

### 什么是PLAB？（面试鸭）

PLAB（Promotion Local Allocation Buffer）用于G1。每个GC线程都有一个局部缓冲区PLAB，在内部执行对象晋升操作，无需竞争老年代的内存空间，提高对象晋升到老年代的效率。

### 什么是对外内存/直接内存？它与堆内存的区别是什么？（面试鸭）

堆外内存的特点：
1. 不受JVM堆内存大小的限制，通过`java.nio.ByteBuffer.allocateDirect()`直接向操作系统分配内存。
2. 可以绕过GC，通过手动调用`ByteBuffer.cleaner()`释放。
3. IO操作可以减少一次堆内存与本地内存之间的复制次数。

### 什么是JIT与AOT？（面试鸭）

JIT（即时编译，Just In Time）在运行时，将字节码编译成机器码。它重点优化多次调用和循环执行的代码，称为热点代码（Hotspot Code）。它使用到的技术有方法内联、陶艺分析、循环展开等等。它有C1（Client Compiler）与C2（Server Compiler）两种类型，C1是用于客户端快速启动的轻量级优化，C2是用于服务器长期运行的重量级优化。

机器码存放在代码缓存区（Code Cache）内，不占用堆空间。Java 8引入了分层编译，将代码缓存区分成了三个区域：非方法代码存储JVM调试与模版代码、方法代码存储JIT编译代码、轮廓代码存储优化级别更高的代码。

AOT（预编译，Ahead Of Time）在运行前的构建阶段，将字节码编译成机器码。优点：（1）减少运行时编译开销，提高启动速度；（2）不需要JIT，减少JVM内存占用。缺点：（1）机器码依赖于特定平台；（2）无法利用运行时动态信息进行深度优化，长期来看性能低于JIT。

### 什么是逃逸分析？（面试鸭）

逃逸分析用于分析对象是否会逃逸出当前方法或线程的作用范围。逃逸分析有两种类型——方法逃逸、线程逃逸。方法逃逸指的是一个对象在方法内创建，作为实参或返回值传递给其他方法；线程逃逸指的是一个对象被另一个线程访问，保存为静态变量或共享变量。JVM针对逃逸分析提供了三种优化——栈上分配、同步消除、标量替换。栈上分配指的是没有逃逸出当前方法的对象，可以直接分配到栈上而不是堆上，减少内存分配和垃圾回收的开销；同步同步消除指的是没有逃逸出当前线程的对象，可以移除不必要的同步锁以提升性能；标量替换指的是没有逃逸且允许拆解的对象，可以拆分为若干个基本类型标量，无需创建一个整体对象。

### 什么是三色标记算法？（面试鸭）

三色标记算法是一种并发的GC算法，用于CMS和G1。它将对象分成三种颜色：白色、灰色、黑色。白色对象指的是尚未被访问的对象，有可能是垃圾；灰色对象指的是已经被访问的，但是它引用的对象尚未被访问的对象；黑色对象指的是已经被访问的，且它引用的对象也已经被访问的对象。初始时所有对象均为白色，然后将GC Roots设置为灰色，遍历所有灰色对象，将它设置为黑色，它引用的对象设置为灰色，重复这个过程，最后清除所有白色对象。

三色标记算法的优点在于它延迟低，可以与主程序并发执行，实现实时GC。缺点是可能会出现漏标和多标的情况。例如给定一个场景：`黑色A->灰色B->白色C`，这时主线程运行，建立`A->C`，删除`A->B`与`B->C`，然后切到GC线程，此时`C`虽然被使用，但是永远为白色对象，因此会被清除，这就是漏标；B应该被清除，但它是灰色对象，所以不会被清除，这就是多标。

为了解决漏标问题，我们有两种方式：增量更新与SATB。增量更新利用写屏障，在黑色对象引用白色对象时将白色对象设置为灰色。SATB（Snapshot At The Beginning）利用写屏障，在灰色对象取消引用白色对象时将白色对象设置为灰色。

### Java对象是如何在JVM中存储的？（面试鸭）

对象存储在堆中，有三个部分：

- 对象头：（1）Mark Word存储运行时数据，例如HashCode、GC标记、锁状态；（2）类型指针指向对象的类的元数据，确定对象的类型；（3）数组长度，只有数组才有。
- 实例数据：存储对象的字段。
- 对齐填充：在对象末尾添加填充字节，使内存对齐（默认为8字节）。

### JVM中的哪些部分会导致OOM？（面试鸭）

| JVM部分      | OOM原因                                                                                                |
| ---------- | ---------------------------------------------------------------------------------------------------- |
| 虚拟机栈/本地方法栈 | 调用层次过深、无限递归                                                                                          |
| 堆          | 对象过多、内存泄漏                                                                                            |
| 方法区        | 在JDK 7中，方法区在永久代中，永久代的内存大小是固定的，不能动态扩展，可能会OOM。在JDK 8中，方法区在元空间中，元空间使用本地内存，默认只受物理内存大小限制，也可以手动指定上限来触发OOM。 |

### 为什么JDK 8要移除永久代，引入元空间？（面试鸭）

1. 永久代的内存大小是固定的；元空间使用堆外内存，可以动态扩容。
2. 永久代的大部分对象寿命很长，GC回收效率低；元空间不受GC管理，避免了STW。

### JVM的Minor GC如何避免全堆扫描？（面试鸭）

JVM将老年代划分成若干个512B的卡片，将其映射为一个BitMap卡表。当老年代对象引用新生代对象时，通过写屏障标记为脏卡。Minor GC只扫描卡表中的脏卡。

### 介绍一下ZGC（面试鸭）

ZGC是Java 11引入的一款垃圾回收器，适用于大内存、低延迟的场景。它有两个核心机制：染色指针和读屏障。
- 染色指针把对象的状态信息直接存放在64位地址的高4bit中，而不是对象头。因此在扫描引用的时候不需要访问对象本身，只需要看指针就行。
- ZGC用的是读屏障。当线程尝试读取一个对象引用时，会触发这个读屏障，检查染色指针的状态。如果发现对象已经被移动了，但是指针还没更新，就会自动修正这个指针指向新的地址，因此无需暂停就可以并发地移动对象。
ZGC流程的绝大部分阶段都是并发的，只有三个极短的阶段需要STW。
1. 初始标记(STW)：使用可达性分析算法标记引用关系。
2. 并发标记：遍历引用关系，使用染色指针进行标记状态信息。
3. 再标记(STW)：处理并发标记遗留的少量对象。
4. 并发转移准备：选择要清理的Region。
5. 初始转移(STW)：转移GC Roots直接关联的对象。
6. 并发转移：使用读屏障解决非GC Roots对象移动时的访问问题，通过并发缩短这个最耗时的阶段。
ZGC的缺点：
- 在并发转移阶段需要预留内存空间，分配给新对象，所以内存利用率较低。
- 每次读操作都会触发读屏障，会产生额外的开销（吞吐量损耗5%），只有在大内存场景才能体现出明显的优势。
# §5 计算机网络

# §6 操作系统

# §7 MySQL

### MySQL中的数据排序是如何实现的？（面试鸭）✅

如果排序字段命中索引，就使用索引排序，因为索引有序所以效率最高。如果没有命中，就使用文件排序，按照能否放入`sort_buffer`（也就是是否小于等于`sort_buffer_size`）分为内存排序和磁盘归并排序，按照内存排序的数据长度是否小于等于`max_length_for_sort_data = 4096B`分为内存单路排序和内存双路排序，其中内存双路排序只把主键和排序字段值放入`sort_buffer`后进行回表。

### 介绍MySQL批量数据入库（面试鸭）✅

在`INSERT INTO ... VALUES (),(),()`后面拼接多条数据，可以手动设置JDBC的`rewriteBatchedStatements = true`来开启。优点：减少网络传输、解析SQL、写入日志的开销。缺点：一条数据插入失败会导致所有数据插入回滚，而且会降低查询缓存的命中率。

### 什么是深分页问题？如何解决？（面试鸭）

深分页指的是`LIMIT X, Y`中的`X`特别大的场景，MySQL只能做到“扫描后丢弃”。如果排序字段有索引，那么会从B+树的双向链表头部向后遍历`X`次；如果排序字段没有索引，那么会进行文件排序。两种情况的开销都很大。

1. 使用子查询或JOIN，利用`WHERE`二级索引数据量小的特点获取主键范围，再根据这个主键范围进行游标查询
2. 改写业务逻辑为连续查询，下一次的主键范围由上一次的主键最大值给定，进行游标查询。优点：保证数据一致性，不受分页期间数据增删影响
3. 搜索引擎，例如ElasticSearch（也有深分页问题，不了解就别说）

### 什么是视图？（面试鸭）✅

视图是一个虚拟表，它不存储实际数据，而是通过其它表的数据来生成。视图可以简化复杂查询，减少代码冗余，限制访问某些数据以增加安全性。

### 存储金额应该使用什么数据类型？（面试鸭）✅

1. MySQL的`bigint`→Java的`long`：存储的精度是固定的
2. MySQL的`decimal`→Java的`BigDecimal`：支持高精度定点数运算，时间空间开销大

### `AUTO_INCREMENT`到达最大值时会发生什么？（面试鸭）✅

下一次申请自增ID得到的值不变，会触发`DUPLICATE ENTRY ... FOR KEY ...`错误。

### 什么是索引下推？（面试鸭）✅

将命中二级索引的查询条件下推到存储引擎层进行过滤，从而减少读取到的数据行数量，减少回表次数。

### 三层B+树能存储多少行数据？（面试鸭）

InnoDB的数据页大小由`innodb_page_size`决定，默认为`16KB`。
第一层：假设每个指针`6B`+`bigint`索引`8B`，于是能存放`16KB/14B ≈ 1170`个索引。
第二层：同理能存放`1170`个索引。
第三层：假设每条记录占`1KB`，一个数据页能存储`16`条记录。
于是三层`B+`树能存储`1170 × 1170 × 16 ≈ 两千万+`条数据。

### 二级索引有MVCC快照吗？（面试鸭）✅

没有。二级索引不包含`transction_id`和`roll_pointer`，但是包含最后修改当前索引页的事务ID`page_max_trx_id`。如果当前事务ID大于`page_max_trx_id`则判定可见，如果当前事务ID小于等于`page_max_trx_id`或标记为已删除，则覆盖索引失效，需要回表通过前面的流程来判定是否可见。

### `VARCHAR(10)`和`VARCHAR(100)`的区别是什么？（面试鸭）✅

存储的字符串长度最大值不一样。存储相同字符串时占用的存储空间一样，但是在查询时分配的内存块大小不一样。

### 什么是存储过程？为什么不推荐使用？（面试鸭）✅

存储过程是一段预编译的SQL代码，用于封装一组特定的业务操作。
1. 可移植性差，依赖于SQL方言。
2. 调试困难，没有设置端点、逐步调试之类的调试方法。
3. 维护复杂，需要同时维护业务代码和存储过程代码。

### 如何避免MySQL单点故障？（面试鸭）

1. 主备架构：主节点负责读写；备节点负责同步，若主节点宕机则自己成为主节点。
2. 主从架构（**常用**）：主节点负责写，从节点负责读。
3. 主主架构：所有节点均负责读写，会产生条件竞争，所以不常用。

### 如何实现MySQL读写分离？（面试鸭）

使用一个中间的代理层来分离读写请求。可以自行实现，也可以使用现成的中间件（例如MySQL-Proxy、ShardingSphere）。

### 为什么不能用MySQL存储文件？（面试鸭）

MySQL是关系型数据库，设计的初衷是存储结构化数据，而不是存储二进制文件。因为会（1）增加表的大小；（2）降低查询效率。应该使用文件系统（HDFS、S3等）或对象存储服务OSS。

### 如何实现数据库的不停服迁移？（面试鸭）

1. 改造业务代码，设置一个双写开关，用于控制是否同步写入新库。
2. 将新数据库设置为旧数据库的从库，或者使用Flick CDC，先全量同步，再增量同步。
3. 在业务低峰期，保证主从数据一致的时候，同时关闭主从同步、打开双写开关，写一个定时任务抽样核对是否一致。
4. 进行灰度切流，逐步增加抛弃旧数据库的比例。
5. 关闭双写，从此只写入新数据库，完成迁移。

### 为什么要用小表JOIN大表？

1. 按照JOIN的前后顺序，时间复杂度可能为$O(n\log m)$与$O(m\log n)$，肯定希望大表的查询开销被索引降到$O(\log)$。
2. 小表可以一次性加载到内存中。

### 相比于Oracle，MySQL的优势有哪些？（面试鸭）

1. MySQL开源免费，文档资源丰富，社区支持完善。
2. MySQL适用于互联网行业的中小型业务，轻量且占用资源少。Oracle面向传统行业的大型业务，例如运输、制造、金融行业。

# §8 Redis

# §9 消息队列

# §10 Spring

> 什么是Spring框架？
> 
> Spring是一款开源的轻量级框架，集合了很多模块，支持IoC和AOP的特性。

> 介绍Spring包含的模块。
> 
> 

> SpringBoot默认最多可以同时处理多少请求？
> 
> `application.yml`的`server.tomcat`配置项下有以下选项：
> - 最小工作线程数`threads.min-spare`：SpringBoot Tomcat最小并发数。
> - 最大工作线程数`threads.max`：SpringBoot Tomcat最大并发数。
> - 最大连接数`max-connections`：SpringBoot Tomcat接受的请求，有`threads.max`个请求会被处理，其它会等待。
> - 最大队列数`accept-count`：未被SpringBoot Tomcat接受的请求，会放在操作系统级别的TCP等待队列。
> 答案是：`max-connections + accept-count = 8192 + 100 = 8292`。

# §11 分布式

### 实现分布式事务。例如创建订单与扣减库存，如果创建订单后MQ宕机，无法发送消息来扣减库存，应该怎么办？

> 使用本地消息表。
> 1. 创建订单的事务提交时，订单状态为`NEW`，发送MQ`库存-topic`和本地消息表的`NEW`。这时的MQ可能宕机。
> 2. 扣减库存监听`库存-topic`，事务提交时，发送MQ`库存结果-tpoic`的`SUCCESS`或`FAILED`。
> 3. 消息恢复系统一方面监听MQ`库存结果-topic`，发送更改本地消息表的订单状态为`CONFIRMED`/`FAILED`，另一方面用定时任务取出本地消息表中的`FAILED`订单，然后再发一遍MQ`库存-topic`的`NEW`进行重试，发送成功后更新本地消息表的订单状态为`SENT`。

# §12 设计模式

## §11.1 单例模式

### 实现单例模式的方法有哪些？

1. 枚举：初始化时线程安全；避免通过反射破坏枚举单例。

```java
enum Singleton {
    INSTANCE;
    public void hello() { System.out.println("Hello world!"); }
}

public class SingletonDemo {
    public static void main(String[] args) {
        Singleton instance = Singleton.INSTANCE;
        instance.hello();
    }
}
```

2. 静态内部类：初始化时线程安全；懒加载。

```java
class Singleton {
	private Singleton() {}
	private static class SingletonInner {
		private final static Singleton INSTANCE = new Singleton();
	}
	public static Singleton getInstance() {
		return SingletonInner.INSTANCE;
	}
	public void hello() { System.out.println("Hello world!"); }
}

public class SingletonDemo {  
    public static void main(String[] args) {  
        Singleton instance = Singleton.getInstance();  
        instance.hello();  
    }  
}
```

3. 双重校验锁：初始化时线程安全；懒加载。

```java
class Singleton {
	private volatile static Singleton INSTANCE;
	private Singleton() {}
	public static Singleton getInstance() {
		if(INSTANCE == null) {
			synchronized(Singleton.class) {
				if(INSTANCE == null) {
					INSTANCE = new Singleton();
				}
			}
		}
		return INSTANCE;
	}
}
```

# §13 Git

> Redis如何统计连续签到天数？
> 
> 两种方式：
> 1. 以日期划分：`YYYY-mm-DD -> BitMap(用户量)`，过期时间为一个月。用户量高✅，日期范围短❌。
> 2. 以用户划分：`用户ID -> BitMap(日期范围)`，永不过期。用户量低❌，日期范围长✅。

> Redis如何实现一亿用户的实时分数Top100排行榜？
> 
> 将用户按照分数阈值拆分成多个ZSet，每个ZSet只存储一定范围内的分数，Top100只需要取分数最高ZSet的前100个值就行。


# §A 场景题

> 给定200MB内存，求1GB文件中各个元素的出现次数。
> 
> 1. 使用Buffer分块读取。这是为了防止OOM。
> 2. 读取的每个元素模`p`得到哈希值`h`，存储到以`h`命名的文件中。这是为了防止`Map`的Key太多导致OOM。
> 3. 遍历每个文件，使用`Map`统计频次，直接`std::cout <<`，然后释放`Map`内存。


# §5 架构

> 如何设计秒杀系统？
> 
> 1. 将前端资源缓存到CDN上
> 2. 前端：活动开始前禁用按钮，下单时验证码，下单后锁定按钮，展示排队页面
> 3. Nginx集群：上层部署硬件级别的负载均衡器（F5、LVS）
> 4. 网关：Sentinel限流
> 5. 消息队列：削峰填谷

> 如何实现订单超时？
> TODO：？？？（https://www.bilibili.com/video/BV11f3jzTEss?p=6）（https://www.bilibili.com/video/BV11f3jzTEss?p=44）

> 如何防止重复下单？
> 
> Redis：`SET NX <用户Token>_<商品ID>_RECOMMIT EX 3~5秒`。

> 如何防止黑产刷单？
> 
> 手机验证码注册、图片验证码、账号异常风控限制、最低消费门槛。

> 如何保证分布式锁的安全性？
> 
> 基于Redission的实现，保证强一致性：
> 1. 线程A以`SETNX UUID_线程ID EX 一段时间`作为Key添加Red Lock，保证只有自己才能释放锁，也防止Master宕机后不释放锁。
> 2. Red Lock等待超过半数的Redis实例从Master同步成功后，才判定从Redis集群获取了锁。
> 3. 设置Watch Dog，若线程A仍运行则每隔10秒刷新一次过期时间，保证锁不会被提前释放。

> 实现扫码登录。
> 
> 1. 电脑请求服务器，服务器生成二维码ID，返回给电脑，存储到Redis（`二维码ID -> 未使用`）。
> 2. 手机扫描二维码，服务器生成临时Token，返回给手机，绑定到Redis（`二维码ID -> 待登录, 临时Token -> 二维码ID`）。防止二维码被扫两次，电脑轮询或长连接更新二维码状态。
> 3. 手机点击同意，发送临时Token到服务器，服务器查询Redis得到`二维码ID`，生成电脑Token，绑定到Redis（`删除临时Token -> 二维码ID, 新增电脑Token -> 用户信息`）。电脑轮询或长连接更新二维码状态。

> 线上问题的排查思路。
> 
> 明确问题的现象与影响范围，评估严重程度，采取应急措施（服务降级、流量限制、回滚版本）。查看日志与监控表（网络/中间件）、代码分析、性能分析工具与监控工具，复现问题，考虑解决方案，复盘和总结。

# §C 项目八股

## AI-Agent

```java
OpenAiApi openAiApi = OpenAiApi.builder() // AI端点
	.baseUrl()
	.apiKey()
	.completionsPath()
	.embeddingsPath()
	.build();
	
ChatModel = OpenAiChatModel.builder() // AI模型
	.openAiApi(openAiApi)
	.defaultOptions(
		OpenAiChatOptions.builder()
			.model()
			.toolCallbacks( // AI MCP
				new SyncMcpToolCallbackProvider()
			)
			.build()
	);
	
ChatClient = ChatClient.builder(chatModel) // AI客户端
	.defaultSystem() // AI系统提示词
	.defaultToolCallbacks(
		new SyncMcpToolCallbackProvider()
	)
	.defaultAdvisors( // AI顾问
		PromptChatMemoryAdvisor.builder().build(), 
		new RagAnswerAdvisor(),
		SimpleLoggerAdvisor.builder().build()
	)
	.build();
```
一个

| 表名                        | 作用       | 联系                                           | 字段                                         |
| ------------------------- | -------- | -------------------------------------------- | ------------------------------------------ |
| `ai_client_api`           | AI端点     | -                                            | API端点、API Key                              |
| `ai_client_model`         | AI模型     | 由一个`ai_client_api`定义                         | 模型名称、模型接入商                                 |
| `ai_client`               | AI客户端    | 由一个`ai_client_model`定义                       | 客户端名称                                      |
| `ai_client_advisor`       | AI顾问     | -                                            | 顾问名称、顾问类型、顺序、参数                            |
| `ai_client_system_prompt` | AI提示词    | -                                            | 提示词名称、提示词内容、描述                             |
| `ai_client_tool_mcp`      | MCP      | -                                            | MCP名称、传输类型、参数<br>(STDIO/SSE)               |
| `ai_agent`                | Agent    | -                                            | Agent名称、描述、渠道类型<br>(`agent`/`chat_stream`) |
| `ai_agent_flow_config`    | Agent工作流 | 由一个`ai_agent`定义<br>由一个`client`定义             | 智能体、客户端、顺序                                 |
| `ai_agent_task_schedule`  | 定时任务     | 由一个`ai_agent`定义                              | 智能体、任务名称、cron表达式、配置                        |
| `ai_client_config`        | 配置图边     | 由源头与目标定义<br>`ai_chat_model`/`ai_chat_client` | 源头/目标的类型与ID、配置                             |
| `ai_client_rag_order`     | RAG配置    |                                              |                                            |
