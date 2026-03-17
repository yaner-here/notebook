参考文献：

| 来源       | 文章标题                 | 进度  |
| -------- | -------------------- | --- |
| 小林Coding | 图解网络-应用层篇-HTTP/3强势来袭 | √   |
| 小林Coding |                      | √   |
|          |                      |     |
- 小林Coding
	1. 图解Redis - 前言 - 图解Redis介绍
	2. 图解Redis - 基础篇 - 什么是Redis
	3. 图解Redis - 数据类型篇 - Redis数据结构
	4. 图解Redis - 数据类型篇 - Redis常见数据类型和应用场景
	5. 图解Redis - 持久化篇 - AOF持久化是怎么实现的
	6. 图解Redis - 持久化篇 - RDB快照是怎么实现的
	7. 图解Redis - 持久划篇 - Redis大Key对持久化有什么影响
	8. 图解Redis - 功能篇 - Redis过期删除策略和内存淘汰策略有什么区别
	9. 图解Redis - 功能篇 - 多节点争抢资源，Redis分布式锁是怎么实现的
	10. 图解Redis - 高可用篇 - 如何保证Redis分布式所的高可用和高性能
	11. 图解Redis - 缓存篇 - 数据库和缓存如何保证一致性
- Agent
	- [BIlibili - OpenSpec新版本SDD落地实践分享（20261.X版）](https://www.bilibili.com/video/BV1KafcB4Ecn/)

# §1 Java基础

# §2 Java集合

### 哈希冲突的解决方式有哪些?

`[TODO]`：

- 拉链法：
- 开放地址法：线性探测、二次探测、伪随机探测。
- 再哈希法：

### ThreadLocal为什么会导致内存泄漏？

每个`Thread`内部维护一个`ThreadLocalMap`实例。`ThreadLocalMap`本质上是`Map<K=ThreadLocal, V=Object>`，内部维护一个`Entry[]`数组，`Entry`继承了`WeakReference<ThreadLocal>`并添加了`Object value`字段，弱引用`ThreadLocal`，强引用`Object value`。每次调用`ThreadLocal.get()/set()`时，程序会查找当前`Thread`对应的`ThreadLocalMap`实例，查找当前`ThreadLocal`对应的键值对`Entry`，然后返回值。

只要线程未销毁，`Thread -> ThreadLocalMap --> Entry[] --> Entry --> V value`这条强引用链就一直存活，导致内存泄漏。所以必须在线程执行完每个任务后，手动调用`threadLocal.remove()`。

`Entry`必须弱引用`ThreadLocal`。因为`ThreadLocalMap`在`get()/set()`时会顺便探测`Entry`的`K = ThreadLocal`是否仍然存在，如果不存在则顺便撤销对`V = Object`的强引用，供GC回收。

## §2.A 编程题

### 手写HashMap

手写HashMap，只要求实现最基本的插入和查找操作。这里我们使用哈希映射到`Entries[]`数组+链表尾插法（即**拉链法**）。

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

### 手写LRU

`HashMap` + 模拟双向链表。

```java
class LRUCache {
    static class LinkedNode {
        int key, value;
        LinkedNode prev, next;
        public LinkedNode() { }
        public LinkedNode(int key, int value) { this.key = key; this.value = value; }
    }

    private Map<Integer, LinkedNode> cache = new HashMap<Integer, LinkedNode>();
    private int size = 0, capacity;
    private LinkedNode head = new LinkedNode(), tail = new LinkedNode();

    public LRUCache(int capacity) {
        this.capacity = capacity;
        head.next = tail; tail.prev = head;
    }

    private void pushHeadNode(LinkedNode node) {
        node.prev = head; node.next = head.next;
        head.next.prev = node; head.next = node;
    }
    private void removeNode(LinkedNode node) {
        node.prev.next = node.next; node.next.prev = node.prev;
    }

    public int get(int key) {
        LinkedNode node = cache.get(key);
        if(node == null) { return -1; }
        removeNode(node); pushHeadNode(node);
        return node.value;
    }

    public void put(int key, int value) {
        LinkedNode node = cache.get(key);
        if(node == null) {
            node = new LinkedNode(key, value);
            cache.put(key, node); pushHeadNode(node); ++size;
            while(size > capacity) { cache.remove(tail.prev.key); removeNode(tail.prev); --size; }
        } else {
            node.value = value;
            removeNode(node); pushHeadNode(node);
        }
    }
}
```

Java提供的`LinkedHashMap`直接覆盖了LRU的需求，但是面试大概率不让用。

```java
class LRUCache {
    private LinkedHashMap<Integer, Integer> map;
    
    public LRUCache(int capacity) {
        map = new LinkedHashMap<>(capacity, 0.75F, true) { // accessOrder = true, 否则为行为类似于队列
            @Override protected boolean removeEldestEntry(Map.Entry<Integer, Integer> eldest) {
                return size() > capacity;
            }
        };
    }

    public int get(int key) {
        return map.getOrDefault(key, -1);
    }
    public void put(int key, int value) {
        map.put(key, value);
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

### 手写阻塞队列

```c++
class MyBlockingQueue<T> {
    private final Queue<T> queue = new LinkedList<>();
    private final int capacity;
    private final ReentrantLock lock = new ReentrantLock();
    private final Condition notFull = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();

    public MyBlockingQueue(int capacity) {
        this.capacity = capacity;
    }

    public void put(T element) throws InterruptedException {
        lock.lockInterruptibly(); // 提前加锁,防止多个put()产生竞态条件,同时put()超出容量
        try {
            while(queue.size() == capacity) { notFull.await(); }
            queue.add(element);
            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }

    public T take() throws InterruptedException {
        lock.lockInterruptibly(); // 提前加锁,防止多个take()产生静态条件,同时take()取空
        try {
            while(queue.size() == 0) { notEmpty.await(); }
            T item = queue.poll();
            notFull.signal();
            return item;
        } finally {
            lock.unlock();
        }
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

### 什么是TLAB？（面试鸭）✅

JVM会为每个线程分配一小块堆内存，称为TLAB（Thread Local Allocation Buffer），用于加速内存分配，避免多线程竞争堆内存的开销。每个线程优先从自己的TLAB中分配内存，当TLAB内存耗尽时，向Eden区申请一个新的TLAB，当分配的内存超过阈值时，直接在Eden区分配。

### 什么是PLAB？（面试鸭）✅

在G1中，每个GC线程都有一个PLAB（Promotion Local Allocation Buffer），在内部执行对象晋升操作，无需竞争老年代的内存空间，提高对象晋升到老年代的效率。

### 什么是常量池？（面试鸭）✅

常量池有两种：运行时常量池、字符串常量池。运行时常量池存储每个类或接口的常量信息，放到方法区/元空间；字符串常量池引入自JDK 7，存储字符串字面量，放到堆内存。常量池的优点在于减少创建重复对象，节省内存，提高效率。

### 什么是对外内存/直接内存？它与堆内存的区别是什么？（面试鸭）✅

堆外内存的特点：
1. 不受JVM堆内存大小的限制，通过`java.nio.ByteBuffer.allocateDirect()`直接向操作系统分配内存。
2. 可以绕过GC，通过手动调用`ByteBuffer.cleaner()`释放。
3. IO操作可以减少一次堆内存与本地内存之间的复制次数。

### 什么是JIT与AOT？（面试鸭）✅

JIT（即时编译，Just In Time）在运行时，将字节码编译成机器码。它重点优化多次执行和循环执行的代码，称为热点代码（Hotspot Code）。它使用到的技术有：方法内联、逃逸分析、循环展开等等。它有C1与C2两种类型，C1是用于客户端快速启动的轻量级优化，C2是用于服务器长期运行的重量级优化。

AOT（预编译，Ahead Of Time）在运行前的构建阶段，将字节码编译成机器码。优点：（1）减少运行时的编译开销，提高启动速度；（2）不需要JIT，减少JVM内存占用。缺点：（1）机器码依赖于特定平台；（2）无法利用运行时的动态信息进行深度优化，长期来看性能低于JIT。

### 什么是逃逸分析？（面试鸭）✅

逃逸分析用于分析对象是否会逃逸出当前方法或线程的作用范围。逃逸分析有两种类型——方法逃逸、线程逃逸。方法逃逸指的是一个对象在方法内创建，作为实参或返回值传递给其他方法；线程逃逸指的是一个对象被另一个线程访问，保存为静态变量或共享变量。JVM针对逃逸分析提供了三种优化——栈上分配、同步消除、标量替换。栈上分配指的是没有方法逃逸的对象，可以直接分配到栈上而不是堆上，减少内存分配和垃圾回收的开销；同步消除指的是没有线程逃逸的对象，可以移除不必要的同步锁以提升性能；标量替换指的是没有逃逸的对象，可以拆分为若干个基本类型标量，无需创建一个整体对象。

### 什么是三色标记算法？（面试鸭）

三色标记算法是一种并发的GC算法，用于CMS和G1。它将对象分成三种颜色：白色、灰色、黑色。白色对象指的是尚未被访问的对象，有可能是垃圾；灰色对象指的是已经被访问的，但是它引用的对象尚未被访问的对象；黑色对象指的是已经被访问的，且它引用的对象也已经被访问的对象。初始时所有对象均为白色，然后将GC Roots设置为灰色，遍历所有灰色对象，将它设置为黑色，它引用的对象设置为灰色，重复这个过程，最后清除所有白色对象。

三色标记算法的优点在于它延迟低，可以与主程序并发执行，实现实时GC。缺点是可能会出现漏标和多标的情况。例如给定一个场景：`黑色A->灰色B->白色C`，这时主线程运行，建立`A->C`，删除`A->B`与`B->C`，然后切到GC线程，此时`C`虽然被使用，但是永远为白色对象，因此会被清除，这就是漏标；B应该被清除，但它是灰色对象，所以不会被清除，这就是多标。

为了解决漏标问题，我们有两种方式：增量更新与SATB。增量更新利用写屏障，在黑色对象引用白色对象时将白色对象设置为灰色。SATB（Snapshot At The Beginning）利用写屏障，在灰色对象取消引用白色对象时将白色对象设置为灰色。

### Java对象是如何在JVM中存储的？（面试鸭）✅

对象存储在堆中，有三个部分：

- 对象头：（1）MarkWord：存储运行时数据，例如HashCode、GC标记、锁状态；（2）类型指针：指向对象的类的元数据，确定对象的类型；（3）数组长度，只有数组才有。
- 实例数据：存储对象的字段。
- 对齐填充：在对象末尾添加填充字节，使内存对齐（默认为8字节）。

### JVM中的哪些部分会导致OOM？（面试鸭）

| JVM部分      | OOM原因                                                                                       |
| ---------- | ------------------------------------------------------------------------------------------- |
| 虚拟机栈/本地方法栈 | 调用层次过深、无限递归                                                                                 |
| 堆          | 对象过多、内存泄漏                                                                                   |
| 方法区        | 在JDK 7中，方法区在永久代，内存大小是固定的，不能动态扩展，可能会OOM。在JDK 8中，方法区在元空间，使用本地内存，默认只受物理内存大小限制，也可以手动指定上限来触发OOM。 |

### 为什么JDK 8要移除永久代，引入元空间？（面试鸭）✅

1. 永久代的内存大小是固定的；元空间使用堆外内存，可以动态扩容。
2. 永久代的大部分对象寿命很长，GC回收效率低；元空间不受GC管理，避免了STW。

### JVM的Minor GC如何避免全堆扫描？（面试鸭）✅

JVM将老年代划分成若干个512B的卡片，将其映射为一个BitMap卡表。当老年代对象引用新生代对象时，通过写屏障标记为脏卡。Minor GC只扫描卡表中的脏卡。

### 介绍一下ZGC（面试鸭）

ZGC是Java 11引入的一款垃圾回收器，适用于大内存、低延迟的场景。JDK 17引入了分代ZGC。它有两个核心机制：染色指针和读屏障。
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

### 介绍一下HTTP3/QUIC，它的优点是什么？

- 头部压缩。从HTTP2的HPACK升级为HTTP3的QPACK，扩大了静态表的空间，用确认机制更新动态表。
- 简化了帧格式。HTTP2自带流标识符，HTTP3将其放到QUIC中，并且把数据长度改为变长编码。
- 彻底解决了队头阻塞问题。原本HTTP2但凡丢失一个TCP包，就会阻塞后续Stream的传输。HTTP3使用UDP解决了这一问题。
- 更快地建立连接。原本HTTP2至少需要TCP一二次握手+TLS四次握手，共计3个RTT；现在HTTP3仅需QUIC两次握手，共计1个RTT，后续再连接可以做到0个RTT。
- 支持连接迁移。原本HTTP2依赖于TCP的`(源IP, 源端口, 目标IP, 目标端口)`四元组唯一标记一个连接，切换网络时会断开重连；HTTP3通过QUIC的连接ID唯一标记一个连接，切换网络时无需重连。

# §6 操作系统

# §7 MySQL

### MySQL中的数据排序是如何实现的？（面试鸭）

如果排序字段命中索引，就使用索引排序，因为索引有序所以效率最高。如果没有命中，就使用文件排序，按照能否放入`sort_buffer`（也就是是否小于等于`sort_buffer_size`）分为内存排序和磁盘归并排序，按照内存排序的数据长度是否小于等于`max_length_for_sort_data = 4096B`分为内存单路排序和内存双路排序，其中内存双路排序只把主键和排序字段值放入`sort_buffer`后进行回表。

### 介绍MySQL批量数据入库（面试鸭）

在`INSERT INTO ... VALUES (),(),()`后面拼接多条数据，可以手动设置JDBC的`rewriteBatchedStatements = true`来开启。优点：减少网络传输、解析SQL、写入日志的开销。缺点：一条数据插入失败会导致所有数据插入回滚，而且会降低查询缓存的命中率。

### 什么是深分页问题？如何解决？（面试鸭）

深分页指的是`LIMIT X, Y`中的`X`特别大的场景，MySQL只能做到“扫描后丢弃”。如果排序字段有索引，那么会从B+树的双向链表头部向后遍历`X`次；如果排序字段没有索引，那么会进行文件排序。两种情况的开销都很大。

1. 使用子查询或JOIN，利用`WHERE`二级索引数据量小的特点获取主键范围，再根据这个主键范围进行游标查询
2. 改写业务逻辑为连续查询，下一次的主键范围由上一次的主键最大值给定，进行游标查询。优点：保证数据一致性，不受分页期间数据增删影响
3. 搜索引擎，例如ElasticSearch（也有深分页问题，不了解就别说）

### 什么是视图？（面试鸭）

视图是一个虚拟表，它不存储实际数据，而是通过其它表的数据来生成。视图可以简化复杂查询，减少代码冗余，限制访问某些数据以增加安全性。

### 存储金额应该使用什么数据类型？（面试鸭）

1. MySQL的`bigint`→Java的`long`：存储的精度是固定的
2. MySQL的`decimal`→Java的`BigDecimal`：支持高精度定点数运算，时间空间开销大

### `AUTO_INCREMENT`到达最大值时会发生什么？（面试鸭）

下一次申请自增ID得到的值不变，会触发`DUPLICATE ENTRY ... FOR KEY ...`错误。

### 什么是索引下推？（面试鸭）

将命中二级索引的查询条件下推到存储引擎层进行过滤，从而减少读取到的数据行数量，减少回表次数。

### 三层B+树能存储多少行数据？（面试鸭）

InnoDB的数据页大小由`innodb_page_size`决定，默认为`16KB`。
第一层：假设每个指针`6B`+`bigint`索引`8B`，于是能存放`16KB/14B ≈ 1170`个索引。
第二层：同理能存放`1170`个索引。
第三层：假设每条记录占`1KB`，一个数据页能存储`16`条记录。
于是三层`B+`树能存储`1170 × 1170 × 16 ≈ 两千万+`条数据。

### 二级索引有MVCC快照吗？（面试鸭）

没有。二级索引不包含`transction_id`和`roll_pointer`，但是包含最后修改当前索引页的事务ID`page_max_trx_id`。如果当前事务ID大于`page_max_trx_id`则判定可见，如果当前事务ID小于等于`page_max_trx_id`或标记为已删除，则覆盖索引失效，需要回表通过前面的流程来判定是否可见。

### `VARCHAR(10)`和`VARCHAR(100)`的区别是什么？（面试鸭）

存储的字符串长度最大值不一样。存储相同字符串时占用的存储空间一样，但是在查询时分配的内存块大小不一样。

### 什么是存储过程？为什么不推荐使用？（面试鸭）

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

### Memcached与Redis的区别是什么？

Memcached只支持最基本的数据存储，而Redis支持更多的高级功能，例如高级数据结构、Lua脚本事务、AOF+RDB、主从+哨兵+集群。
### 介绍Redis的`String`数据类型

`String`使用的数据结构是简单动态字符串（SDS），包含三部分——剩余空间长度`free`、字符串长度`len`、字符数组`buf[]`，最大可达`512MB`。

相比于C语言的字符串，SDS的优点是——可以保存二进制数据、获取字符串长度的时间复杂度是$O(1)$，避免了拼接字符串的缓冲区溢出问题。

`String`使用三种编码：
- `int`：如果`String`是一个`long`范围内的整数，则直接存到`(long*) buf`。
- `embstr`：如果`String`长度较短，则通过一次`malloc()`同时分配`RedisObject`与`SDS`。缺点是只能作为只读字符串，如果要更改则会先从`embstr`转换为`raw`。
- `raw`：如果`String`长度较长，则通过两次`malloc()`分别分配`RedisObject`与`SDS`。

### 介绍Redis的`List`数据类型

`List`使用的数据结构是`QuickList`。

压缩列表本质上是一个`char[]`，通过编码字段将不同长度的元素排在一起。每个元素包含一个`prevlen`字段表示前一个元素占用的空间，用于实现逆序遍历。但是元素扩容时会可能导致后续的元素都要重新为`prevlen`字段扩容，导致连锁更新。

`QuickList`是压缩列表+双向链表的折中版本，每个双向链表的节点存储一个压缩列表，从而控制压缩列表连锁更新的影响范围。

### 介绍Redis的`Hash`数据类型

`Hash`使用的数据结构是`ListPack`。

`ListPack`为了避免`QuickList`的连锁更新问题，不再使用`prevlen`字段表示前一个元素占用的空间，而是使用`len`字段表示当前元素占用的空间。下一个元素只需读取自己指针起点的前一个字节，就依然能实现逆序遍历。

`Hash`使用拉链法解决哈希冲突。如果哈希冲突过多则会通过渐进式Rehash进行扩容。Redis事先准备了两个哈希表指针：
1. 扩容时给第2个哈希表分配两倍的空间
2. 每次针对第1个哈希表的条目做增删改查时，都会移动到第2个哈希表中。
3. 随着处理请求的增多，最终会在某一时刻全部清空第1个哈希表，从而完成Rehash操作
优点：可以把大量的数据移动操作，平摊到多次请求进行处理，避免了阻塞的问题。

令$负载因子=\displaystyle\frac{哈希表保存的键值对数量}{哈希表大小}$，则触发渐进式Rehash的条件有两个：
- 负载因子`>=1`，且没在执行AOF或RDB。
- 负载因子`>=5`。

### 介绍Redis的`Set`数据类型

`Set`使用的数据结构是整数集合（元素数量`<512`）或哈希表（元素数量`>=512`）。

整数集合本质上是一个`char[]`，可以根据存储元素的最大值动态升级成`int8_t`/`int16_t`/`int32_t`/`int64_t`。缺点是只能升级，不能降级。

### 介绍Redis的`Zset`数据类型

`Zset`使用的数据结构是`ListPack`（元素数量`<128`且每个值`<64Byte`）或跳表。

跳表是一种多层的有序链表。每个跳表节点都有一个层级数量，表示含有多少个`next`指针，层级越高的`next`指针跳跃距离越长。增删改查都是从高层指针依次向低层指针做二分查找。最好情况下相邻两层节点的数量比例为`2:1`能达到$O(\log n)$的时间复杂度，最坏情况下退化成链表$O(n)$的时间复杂度。为了保证这个数量比例，我们让新创建的跳表节点层级数量符合$p=0.25$的几何分布，且规定它的上限为`64`。

### 什么是AOF重写机制？

为了防止AOF文件过大，Redis会通过AOF重写机制来压缩AOF文件。

1. 主线程会`fork`一份页表给子线程，并且标记为只读。子线程开始AOF重写，每个键值对都只保存一条`SET`命令来压缩AOF文件。
2. 主线程执行客户端的增删改查命令，通过CoW实现并发写入——每次尝试写入的时候，就会触发写保护中断函数，在这里完成内存写入操作，并将其追加写入到AOF缓冲区与AOF重写缓冲区。
3. 子线程完成AOF重写后，主线程会将AOF重写缓冲区的数据追加写入到新AOF文件，保证数据一致性。
4. 主线程用新的AOF文件覆盖原有的AOF文件，而不是直接复用原有的AOF文件，否则如果AOF重写失败就会污染AOF文件。

### RDB是如何做到主线程更新与子线程Dump互不影响的？会存在什么问题？

使用了写时复制（Copy on Write，CoW）。初始时子线程复制了主线程的页表，共享同一片内存，只有修改数据时才会新复制一份。如果写操作比较频繁，那么极端情况下内存占用会飙升至原来的两倍，因此需要监控内存占用情况。

### 什么是Redis混合持久化？如何既能实现AOF的不丢数据，又能实现RDB的快速恢复？

使用Redis混合持久化。子线程将RDB写入AOF文件前半部分，主线程将更新命令写入缓冲区，等待子线程执行完毕后追加到AOF文件的后半部分。于是AOF文件的前半部分是RDB的全量数据，后半部分是AOF的增量数据。

### Redis的过期删除策略有哪些？

过期删除策略有三种：定时删除、惰性删除、定期删除。Redis使用的是后两者。

- 定时删除：设置Key的过期时间时，同步创建一个删除Key的定时事件。优点是可以保证Key尽快删除，释放内存。缺点是Key很多时会占用CPU，降低吞吐量。
- 惰性删除：每次访问Key时，先检查Key是否过期，如果过期才删除。优点是可以将删除成本均摊到每次查询中，减少CPU的占用。缺点是会浪费内存空间，如果一直不访问则会造成内存泄漏。
- 定期删除：每隔一段时间随机取出一批Key判断是否过期，如果过期才删除；如果发现抽检的`>=25%`的Key均过期，那么就循环这一过程，直到比例`<25%`或执行总耗时`>25ms`为止。优点是减少CPU的占用、也不会浪费内存空间，在定时删除与惰性删除中取得了平衡点。缺点是难以确定时间间隔，容易偏向之前两种策略的极端。

### Redis如何实现高可用高性能的分布式锁？

针对单Redis实例：
- 加锁：使用`SET NX`加锁，Key表示细粒度资源，Value表示客户端ID。需要先比较Value再加锁，用Lua脚本保证原子性。
- 加锁失败的策略：
	- 循环轮询——每隔一段时间就重试一次，缺点是时间不容易确定、CPU空转开销大
	- 监听事件——监听锁的释放事件，必须保证检测锁与监听事件是原子化操作，防止错过释放事件陷入永久等待
- 锁过期：使用`SET EX`加锁，防止客户端宕机导致无法释放锁。
- 锁续约：客户端启动子线程作为看门狗（WatchDog）续约锁。
- 锁续约失败的策略：
	- 每执行一步操作就检查是否仍然持有锁，如果锁续约失败则立即中断业务并回滚事务、抛出异常。
	- 假设锁续约失败是小概率事件，继续执行。缺点是风险更大。
- 释放锁：需要先比较Value再释放锁，用Lua脚本保证原子性。

针对多Redis实例：
- RedLock：依次尝试给$N$个实例加锁/解锁，设置较小的加锁超时阈值，直到超过半数实例加锁成功位置，锁的有效时间要扣除加锁时间。

性能优化：
- Singleflight模式：每个客户端只派出一个线程去竞争Redis分布式锁，减少竞争压力。
- 本地锁交接：将线程持有的分布式所直接交给另一个线程，节省网络开销。引入了本地状态，模糊了一致性边界，极端情况下宕机会导致锁泄漏，只能依靠锁过期自动释放。
- 数据库乐观锁：结合版本号竞争更新，需要控制MySQL并发数量，减少竞争压力。
- 一致性哈希做负载均衡：映射到唯一的Redis实例，问题从分布式退化为单机。

### Redis的缓存更新策略有哪些？

旁路缓存策略（Cache Aside）、读穿/写穿策略（Read/Write Through）、写回策略（Write Back）。实际开发中只能使用旁路缓存策略。
- 旁路缓存策略（Cache Aside）：读取时如果缓存未命中则先读取数据库，然后回写缓存；写入时先更新数据库，再删除缓存。
	- 写入时必须先更新数据库，再删除缓存，否则会导致数据不一致——写线程删除缓存，读线程缓存未命中，读线程读取数据库旧值，读线程回写缓存旧值，写线程写入数据库新值，导致缓存与数据库发生数据不一致。有一种玄学的方法是延迟双删，写线程结束后睡眠一段时间再次删除缓存，从而删除读线程写入的缓存旧值，但是睡眠时间无法准确评估。
	- 写入时必须删除缓存，而不是更新缓存，否则会导致数据不一致——写A线程更新数据库，写B线程更新数据库，写B线程更新缓存，写A线程更新缓存，导致缓存与数据库发生数据不一致。
	- 适合读多写少的场景。如果要提高缓存命中率，要么更新缓存前使用分布式锁，要么让缓存尽快过期。
- 读穿/写穿策略（Read/Write Through）：读取时如何缓存未命中则先读取数据库，然后回写缓存；写入时先更新缓存，再更新数据库，如果缓存未命中则直接更新数据库。
	- 应用程序只和缓存交互，缓存只和数据库交互。
	- 无法用于Java开发，因为Redis天生无法直接与数据库交互。
- 写回策略（Write Back）：写入时只更新缓存，打上脏标记，由后台线程异步写入数据库。
	- 不能保证强一致性，可能造成数据丢失。
	- 适合写多的场景，例如CPU缓存。

### Redis与数据库如何保证一致性？

使用旁路缓存策略（Cache Aside）。如果第二步的删除缓存失败，则可以：

- 消息队列重试机制：将删除缓存的操作发送到消息队列，由消息队列保证重试。缺点是会入侵业务代码。
- 订阅MySQL binlog：使用Canal订阅第一步的更新数据库事件，发送到消息队列，由消费者删除缓存。缺点是引入更多组件，对团队的运维能力要求较高。

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
> 1. 以日期划分：`YYYY-mm-DD -> BitMap(用户量)`，过期时间为一个月。用户量高，日期范围短❌。
> 2. 以用户划分：`用户ID -> BitMap(日期范围)`，永不过期。用户量低❌，日期范围长。

> Redis如何实现一亿用户的实时分数Top100排行榜？
> 
> 将用户按照分数阈值拆分成多个ZSet，每个ZSet只存储一定范围内的分数，Top100只需要取分数最高ZSet的前100个值就行。


# §A 场景题

> 给定200MB内存，求1GB文件中各个元素的出现次数。
> 
> 1. 使用Buffer分块读取。这是为了防止OOM。
> 2. 读取的每个元素模`p`得到哈希值`h`，存储到以`h`命名的文件中。这是为了防止`Map`的Key太多导致OOM。
> 3. 遍历每个文件，使用`Map`统计频次，直接`std::cout <<`，然后释放`Map`内存。

### 如何设计一个分布式系统？

分布式意味着通过网络调用远程方法，这带来了大量问题：
- 服务在哪里（服务发现）
- 服务有多少个（负载均衡）
- 网络出现分区、超时或者服务出错了怎么办（熔断、隔离、降级）
- 方法的参数与返回结果如何表示（序列化协议）
- 如何传输（传输协议）
- 服务权限如何管理（认证、授权）
- 如何保证通信安全（网络安全层）
- 如何令调用不同机器的服务能返回相同的结果（分布式数据一致性）

# §B 架构

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

## DDD高并发抽奖模块

### 介绍一下你的项目

我用DDD的领域驱动设计思想，构建了一个高并发的抽奖模块。为了保证规则的可维护性，我将抽奖分为前中后三个环节，分别使用责任链和决策树来搭建流程。为了保证高并发，我会提前把抽奖活动的奖池列表、概率信息、流程节点加载到Redis，使用消息队列异步地更新数据库，使用Redis滑块锁进行二次复核，使用订单表状态做兜底。同时使用Redis实现了令牌桶限流算法，防止模块过载。

请问您对哪些方面感兴趣，我会详细介绍。

### 你为什么要做这个抽奖模块，聊一下它的背景

`[TODO]`：

### 什么是DDD？它与MVC的区别是什么？你是如何使用DDD的？

DDD（Domain-Driven Design）的全称是领域驱动设计，它是一种针对复杂业务逻辑的软件设计方法。

我理解的DDD在三方面与MVC有区别，分别是贫血模型/充血模型、`domain`/`infra`层的隔离、`domain`层的隔离。
- 贫血模型/充血模型：在传统的MVC中，我们的项目一般是` DAO --PO--> Service --VO--> Controller`，其中`Service`负责对`PO`进行处理得到`VO`。我们的业务逻辑会全都放在`Service`中，而不是放在PO中，我们称它为贫血模型，随着业务规模的扩大，`Service`会变得越来越臃肿。而在DDD中，我们将一部分业务逻辑下放到`Entity`，我们称它为充血模型。例如我们用户购买了积分，先通过`query用户by订单ID`得到了`用户`的实体，之后不必调用`Service`的`add积分By用户ID()`，而是直接调用`用户.add积分()`即可。
- `domain`/`infra`层的隔离：Domain层定义接口，Infra层实现接口。Infra层可以有很多的实现，但是都需要通过Adapter映射到统一的接口，这样更换实现时就不会影响Domain层，实现了解耦。
- `domain`层的隔离：我们将业务拆分成若干个Domain，每个Domain向外通过API提供DTO，隐藏了自己内部的业务细节，从而天然地防止领域之间混乱的引用关系，实现高内聚低耦合。

我的项目把DDD分成了五个模块：APP、Domain、Infra、API、Trigger。
- App层：应用启动，有`@SpringBootApplication`的启动入口。
- Domain层：定义接口。
- Infra层：实现接口。例如数据库、消息队列、外界API接口，通过Adapter封装成统一的接口。
- API层：定义Controller接口、DTO（也就是Request/Response）。
- Trigger层：实现Controller接口、创建定时任务（例如输出库存剩余量日志）、监听外界事件（例如消息队列）。

### 为什么要把抽奖分成前中后三个阶段？你是如何使用责任链与决策树的？/你项目的难点是什么，如何解决的？

我项目的一个难点是：面对着不同活动的复杂抽奖逻辑，如何构建一个可配置、可复用的抽奖策略决策模块。

`[TODO]`：决策树的节点与边的含义，使用的模版模式。详见简历的项目经历。

我将抽奖分为前中后三个阶段。
- 前阶段：检验用户是否有抽奖资格。例如是否被风控拉入黑名单、是否超出了每天/每月/每年的最大抽奖次数限制、账户是否有足够的积分参与抽奖。但凡不满足以上任意一个条件，用户都不能参与抽奖，这是一个线性的判定逻辑，所以我使用了责任链模式。
- 中阶段：根据用户的等级加载对应的奖池、生成随机数并映射到奖品、扣减奖品的Redis库存、生成Redis滑块锁、发送消息队列到MySQL做异步更新。
- 后阶段：根据奖品类型调用不同的奖品发放接口。

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

# §D Agent

### 什么是SDD？

规格驱动开发（Spec-Driven Development）。

- `spec-kit`：严格注重流程，7步流程，思维模型线性向前，适合0-1项目，适合组织完善、流程严格的大型团队
- `kiro`：强调速度与自动化，适合初创团队、适合快速迭代的项目，治理能力较弱。
- OpenSpec：强调变更隔离、风险控制，适合1-n项目，轻快敏捷。

### 什么是MCP？它与Function Calling有什么区别？

MCP是由Anthropic提出的Tool Calling标准，工具提供商实现MCP Server，Agent通过统一的MCP Client与外部进行交互。MCP底层走的是JSON-RPC协议，可以通过STDIO或Socket进行通信。

传统的Function Calling与项目的耦合度往往很高，协议也没有固定的标准。

### 什么是Skills？它与Prompt的区别是什么？

一份Skill包含

### 什么是ReAct框架？

ReAct是目前Agent最主流的执行模式，也就是循环做推理和执行（`Planner -> Executor -> Verifier`），直到`Verifier`判定任务结束或超出最大循环次数为止。

ReAct的意思是`Reasoning + Action`，可以与外部环境和MCP工具交互，幻觉风险更低。而CoT只有`Reasoning`，没有执行这一步，只能依赖模型内部知识，幻觉风险更高。

### 什么是OpenSpec？

OpenSpec是一种用于管理Agent开发规范的命令行工具。它能生成市面上常见的Agent适配格式，例如Claude Code、Codex、OpenCode、Trae等等。

OpenSpec规定了以下工件（Artifacts）：
- `specs/.../spec.md`：包含若干需求(Requirement)，每个需求包含若干场景(Scenario)
- `proposal.md`：是什么、为什么。
- `design.md`：怎么做。
- `tasks.md`：做的步骤。

```shell
workspace:
├─.opencode
│  ├─command
│  │      opsx-apply.md
│  │      opsx-archive.md
│  │      opsx-explore.md
│  │      opsx-propose.md
│  └─skills
│      ├─openspec-explore # 阅读代码、按需生成工件用于记录发散性想法
│      │      SKILL.md
│      ├─openspec-propose # 创建变更、强制生成工件用于细化开发规范
│      │      SKILL.md
│      ├─openspec-apply-change # 执行变更，编辑tasks.md来更新进度
│      │      SKILL.md
│      └─openspec-archive-change # 存档变更
│             SKILL.md
└─openspec
    │  config.yaml
    ├─changes # 存储所有变更的目录
    │  └─archive
    └─specs
```

### 如何保证Vide Coding的代码质量？



# §D HR面

### 你当时为什么选择读研？

我的兴趣一直在开发岗上，现在大模型非常火热，与之相关的云原生、分布式、Agent开发都是很热门的开发岗方向，所以我想借此提升我对大模型的理解，在Agent时代更有竞争力。

### 你为什么不选择算法岗？

`[TODO]`：