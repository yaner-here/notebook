# §1 JVM

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

# §2 Redis

> Redis如何统计连续签到天数？
> 
> 两种方式：
> 1. 以日期划分：`YYYY-mm-DD -> BitMap(用户量)`，过期时间为一个月。用户量高✅，日期范围短❌。
> 2. 以用户划分：`用户ID -> BitMap(日期范围)`，永不过期。用户量低❌，日期范围长✅。

> Redis如何实现一亿用户的实时分数Top100排行榜？
> 
> 将用户按照分数阈值拆分成多个ZSet，每个ZSet只存储一定范围内的分数，Top100只需要取分数最高ZSet的前100个值就行。


# §3 内存限制

> 给定200MB内存，求1GB文件中各个元素的出现次数。
> 
> 1. 使用Buffer分块读取。这是为了防止OOM。
> 2. 读取的每个元素模`p`得到哈希值`h`，存储到以`h`命名的文件中。这是为了防止`Map`的Key太多导致OOM。
> 3. 遍历每个文件，使用`Map`统计频次，直接`std::cout <<`，然后释放`Map`内存。

# §4 Spring

> SpringBoot默认最多可以同时处理多少请求？
> 
> `application.yml`的`server.tomcat`配置项下有以下选项：
> - 最小工作线程数`threads.min-spare`：SpringBoot Tomcat最小并发数。
> - 最大工作线程数`threads.max`：SpringBoot Tomcat最大并发数。
> - 最大连接数`max-connections`：SpringBoot Tomcat接受的请求，有`threads.max`个请求会被处理，其它会等待。
> - 最大队列数`accept-count`：未被SpringBoot Tomcat接受的请求，会放在操作系统级别的TCP等待队列。
> 答案是：`max-connections + accept-count = 8192 + 100 = 8292`。

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

