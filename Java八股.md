
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


# §5 计算机网络

# §6 操作系统

# §7 MySQL

### MySQL中的数据排序是如何实现的？（面试鸭）

如果排序字段命中索引，就使用索引排序，因为索引有序所以效率最高。如果没有命中，就使用文件排序，按照能否放入`sort_buffer`（也就是是否小于等于`sort_buffer_size`）分为内存排序和磁盘归并排序，按照内存排序的数据长度是否小于等于`max_length_for_sort_data = 4096B`分为内存单路排序和内存双路排序，其中内存双路排序只把主键和排序字段值放入`sort_buffer`后进行回表。

### 介绍MySQL批量数据入库（面试鸭）

在`INSERT INTO ... VALUES (),(),()`后面拼接多条数据，可以手动设置JDBC的`rewriteBatchedStatements = true`来开启。优点：减少网络时间的开销，均摊解析SQL与写入日志的开销。缺点：一条数据插入失败导致所有数据插入回滚，降低查询缓存的命中率。

### 为什么要用小表JOIN大表？

1. 按照JOIN的前后顺序，时间复杂度可能为$O(n\log m)$与$O(m\log n)$，肯定希望大表的查询开销被索引降到$O(\log)$。
2. 小表可以一次性加载到内存中。

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

# §6 分布式

> 实现分布式事务。例如创建订单与扣减库存，如果创建订单后MQ宕机，无法发送消息来扣减库存，应该怎么办？
> 
> 使用本地消息表。
> 1. 创建订单的事务提交时，订单状态为`NEW`，发送MQ`库存-topic`和本地消息表的`NEW`。这时的MQ可能宕机。
> 2. 扣减库存监听`库存-topic`，事务提交时，发送MQ`库存结果-tpoic`的`SUCCESS`或`FAILED`。
> 3. 消息恢复系统一方面监听MQ`库存结果-topic`，发送更改本地消息表的订单状态为`CONFIRMED`/`FAILED`，另一方面用定时任务取出本地消息表中的`FAILED`订单，然后再发一遍MQ`库存-topic`的`NEW`进行重试，发送成功后更新本地消息表的订单状态为`SENT`。

