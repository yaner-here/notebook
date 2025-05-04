参考文献：

- [《Spring Redis实战开发》](https://wqbook.wqxuetang.com/book/3251192)

# §1 基础语法与概念

## §1.1 CRUD

增删改查：

| 命令                 | 类型  | 语法                                                                                         | 作用                                                                                                                                                                    |
| ------------------ | --- | ------------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `KEYS`             | 查   | `KEYS <KEY_PATTERN>`                                                                       | 按名查询键，允许使用`*`通配符                                                                                                                                                      |
| `EXISTS`           | 查   | `EXISTS <KEY>`                                                                             | 键值对是否存在，返回`0`/`1`布尔值                                                                                                                                                  |
| `RENAME`           | 改   | `RENAME <OLD_KEY> <NEW_KEY>`                                                               | 重命名键值对                                                                                                                                                                |
| `DEL`              | 删   | `DEL <KEY>+`                                                                               | 删除键值对，若不存在则忽略，返回删除的键值对数量                                                                                                                                              |
| `TYPE`             | 查   | `TYPE <KEY>`                                                                               | 返回键值对的值类型，例如`none`/`string`/`set`/`zset`/`hash`                                                                                                                       |
| `SET`              | 增   | `SET <KEY> <VALUE>`                                                                        | 添加键值对                                                                                                                                                                 |
|                    |     | `SET <KEY> <VALUE> [EX <SECONDS>] [PX <MILLISECONDS>] [NX\|XX]`                            | `EX`指定过期的秒数，`PX`指定过期的毫秒数，`NX`只在键不存在时才操作，`XX`只在键存在时才操作。`EX`和`PX`同时存在时，后面的设置会覆盖前面的设置。                                                                                   |
| `SETEX`            | 增   | `SETEX <KEY> <TIMEOUT> <VALUE>`                                                            | 添加键值对，并指定过期时间                                                                                                                                                         |
| `SETNX`            | 增   | `SETNX <KEY> <VALUE>`                                                                      | 若键值对不存在，才设置键值对                                                                                                                                                        |
| `MSET`             | 增   | `MSET [<KEY> <VALUE>]+`                                                                    | 整体作为一个原子操作，同时设置多个键值对                                                                                                                                                  |
| `GET`              | 查   | `GET <KEY>`                                                                                | 输出键值对的值。若键不存在则输出`nil`                                                                                                                                                 |
| `MGET`             | 查   | `MGET [<KEY>]+`                                                                            | 以列表形式，输出多个键值对的值                                                                                                                                                       |
| `GETSET`           | 改/查 | `GETSET <KEY> <VALUE>`                                                                     | 更新键值对的值，并返回旧值                                                                                                                                                         |
| `SETRANGE`         | 改   | `SETRANGE <KEY> <OFFSET> <VALUE>`                                                          | 将字符串从`<OFFSET>`位置开始用`<VALUE>`覆写                                                                                                                                       |
| `GETRANGE`         | 查   | `GETRANGE <KEY> <START> <END>`                                                             | 截取子字符串，支持从最后一位开始计数的负数索引                                                                                                                                               |
| `APPEND`           | 改   | `APPEND <KEY> <VALUE>`                                                                     | 在字符串/列表末尾追加元素，返回追加后的总长度。若键不存在则创建                                                                                                                                      |
| `STRLEN`           | 查   | `STRLEN <KEY>`                                                                             | 返回字符串的长度。若键不存在则返回`0`                                                                                                                                                  |
| `INCRBY`           | 改   | `INCRBY <KEY> <DELTA>`                                                                     | 给键值对的值加上增量`<DELTA>`                                                                                                                                                   |
| `DECRBY`           | 改   | `DECRBY <KEY> <DELTA>`                                                                     | 给键值对的值减去增量`<DELTA>`                                                                                                                                                   |
| `SETBIT`           | 改   | `SETBIT <KEY> <OFFSET> <VALUE>`                                                            | 将字符串视为`std::bitset`，进行Bit级别的修改，其中`<VALUE>`只能为`0`/`1`，若`OFFSET`超出了原有长度则自动扩充                                                                                            |
| `GETBIT`           | 查   | `GETBIT <KEY> <OFFSET>`                                                                    | 将字符串视为`std::bitset`，进行Bit级别的查询                                                                                                                                        |
| `LPUSH`/`RPUSH`    | 增   | `LPUSH/RPUSH <KEY> <VALUE>+`                                                               | 整体作为一个原子操作，在列表表头/表尾同时插入多个值                                                                                                                                            |
| `LLEN`             | 查   | `LLEN <KEY>`                                                                               | 返回列表的长度。若键不存在则返回`0`，若值不是列表则饭后错误                                                                                                                                       |
| `LLOP`/`RPOP`      | 删   | `LPOP/RPOP <KEY>`                                                                          | 删除并返回列表表头/表尾的一个元素。若键不存在则返回`nil`                                                                                                                                       |
| `LRANGE`           | 查   | `LRANGE <KEY> <START> <STOP>`                                                              | 返回列表中位于闭区间`[<START>, <STOP>]`的元素，支持负数索引                                                                                                                               |
| `LSET`             | 改   | `LSET <KEY> <INDEX> <VALUE>`                                                               | 将列表中索引为`<INDEX>`的值设置为`<VALUE>`，若键不存在或列表为空时返回错误                                                                                                                        |
| `LTRIM`            | 改   | `LTRIM <KEY> <START> <STOP>`                                                               | 列表只保留位于闭区间`[<START>, <STOP>]`的元素，支持负数索引，若值不是列表则返回错误                                                                                                                   |
| `LMOVE`            | 改   | `LMOVE <SOURCE_KEY> <DESTINATION_KEY> <LEFT\|RIGHT> <LEFT\|RIGHT>`                         | 整体作为一个原子操作，将列表`<SOURCE_KEY>`的表头/表尾第一个元素移动到列表`<DESTINATION_KEY>`的表头/表尾处                                                                                                |
| `LINDEX`           | 查   | `LINDEX <KEY> <INDEX>`                                                                     | 返回列表的第`<INDEX>`个元素，从`0`开始数，支持负数索引。若值不是列表则返回错误                                                                                                                         |
| `LREM`             | 删   | `LREM <KEY> <COUNT> <VALUE>`                                                               | 删除列表中值为`<VALUE>`的元素。`COUNT>0`/`COUNT<0`时表示从前往后/从后往前搜索前`<COUNT>`个匹配项，`COUNT=0`表示删除全部匹配项                                                                                |
| `HSET`             | 增   | `HSET <KEY> <FIELD> <VALUE>`                                                               | 给哈希表`<KEY>`设置键值对`<FIELD>:<VALUE>`。若`<FIELD>`已存在/未存在则返回`0`/`1`，若`<KEY>`不存在则新建哈希表后设置                                                                                    |
| `HGET`             | 查   | `HGET <KEY> <FIELD>`                                                                       | 返回哈希表中的键`<FIELD>`对应的值，若`<FIELD>`不存在则返回`nil`                                                                                                                           |
| `HMSET`            | 增   | `HMSET <KEY> [<FIELD> <VALUE>]+`                                                           | 整体作为一个原子操作，同时在哈希表中设置多个键值对，执行成功返回`OK`，若`<KEY>`不是哈希表则返回错误                                                                                                               |
| `HMGET`            | 查   | `HGET <KEY> <FIELD>+`                                                                      | 返回哈希表中的多个键对应的值列表                                                                                                                                                      |
| `HGETALL`          | 查   | `HGETALL <KEY>`                                                                            | 返回哈希表中的所有键和值，以列表格式给出，具体顺序为`[<FIELD_i> <VALUE_i>]+`                                                                                                                    |
| `HDEL`             | 删   | `HDEL <KEY> <FIELD>+`                                                                      | 删除哈希表中的一个或多个键值对                                                                                                                                                       |
| `HLEN`             | 查   | `HLEN <KEY>`                                                                               | 返回哈希表中的键值对数量                                                                                                                                                          |
| `HEXISTS`          | 查   | `HEXISTS <KEY> <FIELD>`                                                                    | 查询哈希表中是否存在某个键值对，返回`0`/`1`                                                                                                                                             |
| `HKEYS`            | 查   | `HKEYS <KEY>`                                                                              | 返回哈希表中的所有`<FIELD>`，以列表形式给出                                                                                                                                            |
| `HVALS`            | 查   | `HVALS <KEY>`                                                                              | 返回哈希表中的所有`<VALUE>`，以列表形式给出                                                                                                                                            |
| `HSCAN`            | 查   |                                                                                            | TODO：？？？                                                                                                                                                              |
| `HINCRBY`          | 改   | `HINCRBY <KEY> <FIELD> <INCREMENT>`                                                        | 将哈希表中的某个`int64`值添加`<INCREMENT>`的增量。若`<KEY>`不存在则新建哈希表，若`<FIELD>`不存在则设置初始值为`0`                                                                                          |
| `SADD`             | 增   | `SADD <KEY> <MEMBER>+`                                                                     | 将若干个元素`<MEMBER>+`添加到集合中，返回集合原先不存在的元素的数量                                                                                                                               |
| `SMEMBERS`         | 查   | `SMEMBERS`                                                                                 | 返回集合中的所有成员                                                                                                                                                            |
| `SMOVE`            | 改   | `SMOVE <SOURCE> <DESTINATION> <MEMBER>`                                                    | 将集合`<SOURCE>`中的元素`<MEMBER>`移动到集合`<DESTINATION>`中。若`<MEMBER>`在`<SOURCE>`中不存在或`<SOURCE>`不存在则返回`0`；若`<SOURCE>`或`<DESTINATION>`非集合类型则返回错误；若`<MEMBER>`存在于`<SOURCE>`则返回`1`。 |
| `SREM`             | 删   | `SREM <KEY> <MEMBER>+`                                                                     | 删除集合中的若干个元素，返回删除的元素数量                                                                                                                                                 |
| `SPOP`             | 删   | `SPOP <KEY>`                                                                               | 随机删除集合中的一个元素，并返回该元素的值                                                                                                                                                 |
| `SCARD`            | 查   | `SCARD <KEY>`                                                                              | 返回集合中的元素个数。若`<KEY>`不存在则返回`0`                                                                                                                                          |
| `SISMEMBER`        | 查   | `SISMEMBER <KEY> <MEMBER>`                                                                 | 检测集合是否包含某个元素，返回布尔值`0`/`1`                                                                                                                                             |
| `SINTER`           | 集   | `SINTER <KEY>+`                                                                            | 返回若干个集合的交集，若`<KEY>`不存在则视为空集                                                                                                                                           |
| `SUNION`           | 集   | `SUNION <KEY>+`                                                                            | 返回若干个集合的并集，若`<KEY>`不存在则视为空集                                                                                                                                           |
| `SDIFF`            | 集   | `SDIFF <KEY>+`                                                                             | 返回第一个集合减后面若干个集合的差集，若`<KEY>`不存在则视为空集                                                                                                                                   |
| `ZADD`             | 增   | `ZADD <KEY> [<SCORE> <MEMBER>]+`                                                           | 将若干个元素`<MEMBER>+`添加到有序集合中，返回有序集合原先不存在的元素的数量                                                                                                                           |
| `ZRANGE`           | 查   | `ZRANGE <KEY> <START> <STOP> [WITHSCORES]`                                                 | 返回有序集合中位于闭区间`[<START>, <STOP>]`中的所有元素，支持负数索引，索引越界时不报错。使用`WITHSCORE`选项时会同时间隔返回所有`MEMBER`的`<SCORE>`，放在其前面                                                               |
| `ZREM`             | 删   | `ZREM <KEY> <MEMBER>+`                                                                     | 删除有序集合中的若干个元素，返回删除的元素数量                                                                                                                                               |
| `ZCARD`            | 查   | `ZCARD <KEY>`                                                                              | 返回有序集合中的元素个数                                                                                                                                                          |
| `ZCOUNT`           | 查   | `ZCOUNT <KEY> <MIN> <MAX>`                                                                 | 返回有序集合中`<SCORE>`位于闭区间`[<MIN>, <MAX>]`内的所有`<MEMBER>`的个数                                                                                                                |
| `ZSCORE`           | 查   | `ZSCORE <KEY> <MEMBER>`                                                                    | 返回有序集合中`<MEMBER>`对应的`<SCORE>`值，若`<KEY>`不存在或`<MEMBER>`不存在则返回`nil`                                                                                                      |
| `ZRANK`            | 查   | `ZRANK <KEY> <MEMBER>`                                                                     | 返回有序集合中`<MEMBER>`对于`<SCOER>`的升序排名，从`0`开始计数。若`<MEMBER>`不存在则返回`nil`                                                                                                     |
| `ZINCRBY`          | 改   | `ZINCRBY <KEY> <INCREMENT> <MEMBER>`                                                       | 为有序集合中`<MEMBER>`对应的`<SCORE>`添加增量`<INCREMENT>`                                                                                                                         |
| `ZREVRANK`         | 查   | `ZREVRANK <KEY> <MEMBER>`                                                                  | 返回有序集合中`<MEMBER>`对于`<SCOER>`的降序排名，从`0`开始计数。若`<MEMBER>`不存在则返回`nil`                                                                                                     |
| `ZUNIONSTORE`      | 集   | `ZUNIONSTORE <DESTINATION> <NUMKEYS> <KEY>+ [WEIGHTS <WEIGHT>+] [AGGREGATE SUM\|MIN\|MAX]` | 给定若干个有序集合`<KEY>+`，统计其中所有同名`<MEMBER>`的`<SCORE>`经过指定聚合函数（缺省为`SUM`）得到的结果作为新`<SCORE>`，存储到新的有序集合`<DESTINATION>`中。`<NUMKEYS>`表示输入有序集合的个数。使用`<WEIGHTS>`指定各个有序集合的权重系数         |
| `ZREMRANGEBYRANK`  | 删   | `ZREMRANGEBYRANK <KEY> <START> <STOP>`                                                     | 删除有序集合中排名位于闭区间`[<START>, <STOP>]`中的元素，排名从`0`计数，支持负数排名                                                                                                                 |
| `ZREVRANGEBYSCORE` | 查   | `ZREVRANGEBYSCORE <KEY> <MIN> <MAX> [WITHSCORES] [LIMIT <OFFSET> <COUNT>]`                 | 返回有序集合中`<SCORE>`位于闭区间`[<MIN>, <MAX>]`的所有`<MEMBER>`，按`<SCORE>`降序排列，若`<SCORE>`相同则按`<MEMBER>`字典序逆序排列                                                                     |
| `ZRANDMEMBER`      | 查   | `ZRANDMEMBER <KEY> [<COUNT> [<WITHSCORES>]]`                                               | 从有序集合中随机返回`min(abs(<COUNT>), ZCOUNT <KEY>`个元素，缺省值为`1`。若`<COUNT>`为负，则允许重复地挑选随机元素                                                                                       |
| `PFADD`            | 增   | `PFADD <KEY> <VALUE>+`                                                                     | 向超级日志添加元素                                                                                                                                                             |
| `PFCOUNT`          | 查   | `PFCOUNT <KEY>+`                                                                           | 查询超级日志中的元素数量近似值                                                                                                                                                       |
| `PFMERGE`          | 并   | `PFMERGE <DESTKEY> <SRCKEY>+`                                                              | 取若干个超级日志的并集并保存                                                                                                                                                        |

键值对的元数据：

| 命令          | 语法                                                                                                                               | 作用                                            |
| ----------- | -------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------- |
| `SCAN`      | `SCAN <CURSOR>`                                                                                                                  | 基于游标的查询，返回一个数组，其中`[0]`表示下一个游标，`[1]`表示得到的值     |
| `TTL`       | `TTL <KEY>`                                                                                                                      | 键值对的剩余生存时间，返回秒数，其中`-2`表示键不存在，`-1`表示没有设置剩余生存时间 |
| `EXPIRE`    | `EXPIRE <KEY> <SECONDS>`                                                                                                         | 设置键值对的剩余生存时间，返回`0`/`1`布尔值表示是否设置成功             |
| `SELECT`    | `SELECT <DATABASE>`                                                                                                              | 切换到数据库                                        |
| `MOVE`      | `MOVE <KEY> <DATABASE>`                                                                                                          | 将键值对从当前数据库移动到指定数据库                            |
| `FLUSHDB`   | `FLUSHDB`                                                                                                                        | 清除当前数据库的所有键值对                                 |
| `RANDOMKEY` | `RAMDOMKEY`                                                                                                                      | 从当前数据库随机返回一个键值对的键名。若数据库为空则返回`nil`             |
| `SORT`      | `SORT <KEY> [BY <PATTERN>] [LIMIT <OFFSET> <COUNT>] [GET <PATTERN>[GET <PATTERN>...]] [ASC\|DESC] [ALPHA] [STORE <DESTINATION>]` | 排序                                            |

## §1.2 消息机制

Redis提供了基于发布-订阅的消息机制。准确来说，Redis只有消息，没有队列。很多其他专业的消息队列系统（例如Kafka、RabbitMQ）提供了完善的消息堆积与回溯的解决方案。

| REDIS CLI命令    | 语法                                | 作用                             |
| -------------- | --------------------------------- | ------------------------------ |
| `SUBSCRIBE`    | `SUBSCRIBE <CHANNEL>+`            | 为客户端订阅若干个通道                    |
| `UNSUBSCRIBE`  | `UNSUBSCRIBE <CHANNEL>*`          | 删除客户端订阅的若干个通道，若未指定`<PUB>`则全部删除 |
| `PUBSUB`       | `PUBSUB <CHANNEL_PATTERN>`        | 查看订阅状态（支持通配符）                  |
| `PUBLISH`      | `PUBLISH <CHANNEL> <MESSAGE>`     | 向频道发布消息                        |
| `PSUBSCRIBE`   | `PSUBSCRIBE <CHANNEL_PATTERN>+`   | 为客户端订阅若干个通道（支持通配符）             |
| `PUNSUBSCRIBE` | `PUNSUBSCRIBE <CHANNEL_PATTERN>+` | 为客户端订阅若干个分片通道（支持通配符）           |

```shell
shell_1:6379> SUBSCRIBE news chat
1) "subscribe"
2) "news"
3) (integer) 1

shell_1:6379> SUBSCRIBE news chat
1) "subscribe"
2) "chat"
3) (integer) 2

shell_2:6379> PUBLISH news "This is news channel."
(integer) 1

shell_1:6379>
1) "message"
2) "news"
3) "This is news channel."
```

下面是使用Jedis的Java代码例子：

```java
package top.yaner_here.javasite;

import lombok.extern.log4j.Log4j2;
import redis.clients.jedis.Jedis;
import redis.clients.jedis.JedisPubSub;

@Log4j2
public class MyRedisPublisher {
    public static void main(String[] args) {
        Jedis jedis = new Jedis("localhost", 6379);
        log.info("[Publisher] Alice send a message: {}", "Hello");
        jedis.publish("chat", "[Alice] Hello!");
    }
}

@Log4j2
public class MyRedisSubscriber extends JedisPubSub {
    @Override public void onMessage(String channel, String message) {
        log.info("[Subscriber] Channel {} got message: {}", channel, message);
    }
    @Override public void onSubscribe(String channel, int subscribedChannels) {
        log.info("[Subscriber] Subscribed to channel {}", channel);
    }
    @Override public void onUnsubscribe(String channel, int subscribedChannels) {
        log.info("[Subscriber] Unsubscribed to channel {}", channel);
    }
    public static void main(String[] args) {
        MyRedisSubscriber subscriber = new MyRedisSubscriber();
        Jedis jedis = new Jedis("localhost", 6379);
        jedis.subscribe(subscriber, "chat");
    }
}
/*
[Subscriber] Subscribed to channel chat
[Publisher] Alice send a message: Hello
[Subscriber] Channel chat got message: [Alice] Hello!
*/
```

## §1.3 Redis流

自Redis 5.0起，Redis提供了一个新的数据结构——Redis流（Redis Stream）。它是一个专为日志设计的、可持久化的、只能在链表末尾添加元素的数据结构。Redis流维护了一个链表，其中的每个节点都代表一条信息（Entry）。每条信息可以包含若干个键值对。

| Redis CLI命令 | 语法                                           | 作用                                                                                      |
| ----------- | -------------------------------------------- | --------------------------------------------------------------------------------------- |
| `XADD`      | `XADD <KEY> <ID> [<FIELD> <VALUE>]+`         | 向Redis流末尾追加一条信息。`<ID>`为`*`时表示自动生成ID                                                     |
| `XLEN`      | `XLEN <KEY>`                                 | 返回Redis流的长度                                                                             |
| `XRANGE`    | `XRANGE <KEY> <START> <END> [COUNT <COUNT>]` | 获取消息列表。`<START>`可为`-`表示最小值，`<END>`可为`+`表示最大值。若`[START, END]`的长度大于`<COUNT>`则以`<COUNT>`为准 |
| `XACK`      | `XACK <KEY> <GROUP> <ID>`                    | 消费者向Redis告知已经消费了`GROUP`中的标识符为`<ID>`的消息                                                  |

```shel
localhost:db0> XADD loginfo * username Bob loginTime 2025.05.04
1746281356792-0

localhost:db0> XLEN loginfo
2

localhost:db0> XRANGE loginfo - +
1)1)"1746281348896-0"
2)1)"username"
2)"Alice"
3)"loginTime"
4)"2025.05.03"
2)1)"1746281356792-0"
2)1)"username"
2)"Bob"
3)"loginTime"
4)"2025.05.04"
```

在负载均衡等场景中，我们不需要向所有客户端提供完整的Redis流，而是Redis流的一个划分形成的子集。为此Redis流提供了消费组概念，消息与消费者是多对一关系，每个消费者都要通过名称来表示，每个消费者组都维护一个指针，表示从未使用过的第一个ID。

| Redis CLI命令        | 语法                                                                                                       | 作用                                                                                                                                                      |
| ------------------ | -------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `XGROUP CREATE`    | `XGROUP CREATE <KEY> <GROUP> <ID> [MKSTREAM]`                                                            | 为Redis流`<KEY>`创建名为`<GROUP>`的消费组，从`<ID>`处开始，表示消费者从第几条消息开始消费，设为`$`时表示只消费新追加消息。`MKSTREAM`表示如果`<KEY>`不存在则创建Redis流                                           |
| `XREADGROUP GROUP` | `XREADGROUP GROUP <GROUP> <CONSUMER> [COUNT <COUNT>] [BLOCK <MILLSECONDS>] [NOACK] STREAMS <KEY>+ <ID>+` | 消费者`<CONSUMER>`从消费组`<GROUP>`中消费`<COUNT>`条消息，阻塞时间至多为`<MILLSECONDS>`毫秒。`<KEY>`表示要读取的消息字段，`<ID>`表示要读取的消息编号，设为`>`表示读取未被消费的信息。`NOACK`表示读取消息但不放入队列，也无须`XACK`。 |

```shell
localhost:db0> XGROUP CREATE my_stream my_group $ MKSTREAM
OK

localhost:db0> XADD my_stream * username Alice age 18
1746342954851-0

localhost:db0> XADD my_stream * username Bob age 19
1746342968732-0

localhost:db0> XREADGROUP GROUP my_group consumer_1 COUNT 2 STREAMS my_stream >
1 ) "my_stream"
2 )     1 )      1 ) "1746342954851-0"
        2 )      1 ) "username"
        2 ) "Alice"
        3 ) "age"
        4 ) "18"
        2 )      1 ) "1746342968732-0"
        2 )      1 ) "username"
        2 ) "Bob"
        3 ) "age"
        4 ) "19"

localhost:db0> XACK my_stream my_group 1746342954851-0 1746342968732-0
2

localhost:db0> XREADGROUP GROUP my_group consumer_1 COUNT 2 STREAMS my_stream >
# 没有返回值
```

## §1.4 Redis事务

Redis事务是一组命令的集合，保证其中的所有命令都顺序执行，不存在两个事务同时执行的情况。

| Redis CLI命令 | 语法             | 作用                                              |
| ----------- | -------------- | ----------------------------------------------- |
| `DISCARD`   | `DISCARD`      | 事务的结束符，取消执行事务                                   |
| `EXEC`      | `EXEC`         | 事务的结束符，开始执行事务                                   |
| `MULTI`     | `MULTI`        | 事务的开始符                                          |
| `UNWATCH`   | `UNWATCH`      | 取消监视所有键                                         |
| `WATCH`     | `WATCH <KEY>+` | 监视多个键，若事务由`EXEC`执行前被修改，则调用`DISCARD`终止事务。用于实现乐观锁 |

```shell
localhost:db0> MULTI
OK

localhost:db0> SADD user:1:follow user:2
QUEUED

localhost:db0> SADD user:2:fan user:1
QUEUED

localhost:db0> EXEC
1) 1
2) 1

localhost:db0> MULTI
OK

localhost:db0> SADD user:1:follow user:3
QUEUED

localhost:db0> DISCARD # 取消执行事务
OK
```


Redis事务不保证事务隔离和原子性。为了解决这个问题，Redis引入了Lua脚本，将其作为一个整体执行，所以自带原子性。

| Redis CLI命令 | 语法                                      | 作用                                           |
| ----------- | --------------------------------------- | -------------------------------------------- |
| `EVAL`      | `EVAL <STRING> <NUM_KEY> <KEY>+ <ARG>+` | 把Lua脚本作为一个原子性事务来执行。`<NUM_KEY>`指定了`<KEY>`的数量。 |

```shell
localhost:db0> EVAL "return redis.call('SET', KEYS[1], ARGV[1])" 1 username yaner
OK

localhost:db0> GET username
yaner
```

## §1.x Redis风险

### §1.x.1 缓存雪崩

缓存雪崩指的是：由于缓存未加载、缓存在短时间内大面积失效等原因，大量并发请求访问数据库，导致资源占用率极高甚至宕机。

生产场景中有以下解决方案：

1. 提高缓存的高可用性。使用Redis哨兵模式或Redis集群。
2. 优化缓存过期时间。要么牺牲更多内存保证缓存永不过期，要么使得各个缓存的过期时间巧妙地错开。
3. 使用互斥锁。若某线程发现缓存未命中，则直接给键加锁后再查询数据库。若其他线程发现互斥锁，则直接阻塞。这样能保证多个针对同一数据的查询只会查询数据库一次。
4. 定时更新。若不要求时效性，则可以使用定时任务定期刷新缓存。

### §1.x.2 缓存穿透

缓存穿透指的是：如果多个查询均指向数据库中不存在的数据，那么每次查询的结果虽然均为空值，但是不会写入到Redis中，导致缓存命中率为零，增大数据库查询压力。

生产场景中有以下解决方案：

1. 缓存空对象。如果查询结果依然为空对象，则依然存入Redis中。为了防止该方案占用过多内存，可以设置一个较短的过期时间；为了防止该方案导致缓存与数据库的数据不一致，可以使用消息系统实现同步。**适用于缓存命中率低、数据频繁更新、实时性要求高、代码维护简单**的场景。缺点是**内存占用大、数据不一致**。
2. 使用布隆过滤器拦截。在查询数据库之前，先过一遍布隆过滤器判断是否查询条目是否存在。如果判定为不存在，那么数据库中肯定不存在，直接返回空值即可；如果判定为存在，则不一定存在，照常执行后续的逻辑。适用于**缓存命中率低、数据相对固定、实时性要求低、内存占用少**的场景。缺点是**代码维护复杂**。

## §2 Redis集群

Redis集群有三种模式：实现数据热备份的主从复制模式、保证可用性的哨兵模式、提升吞吐量和可用性的集群模式。

## §2.1 主从复制模式

主从复制模式将Redis服务器划分为主结点和从节点。主节点与从节点是一对多的关系，主节点负责向从节点同步数据。在客户端看来，主节点负责读写，而从节点是只读的。

- 一主一从结构：最简单的主从复制模式，只有两个集群，分别是主节点和从节点。
- 一主多从结构：一个主节点配多个从节点。优点是有多个从节点，可以分担主节点读操作的工作负载，确实是写入主节点操作较为频繁时，会导致频繁的同步，增加了主节点的工作负载。
- 树状主从结构：一个主节点配少量从节点，一个从节点配少量从节点，以此类推，使得Redis数据库沿着树状的根节点向下同步。优点是解决了一主多从结构中的根节点对于数据同步的工作负载。

使用以下步骤启用主从复制模式：

1. 使用默认配置启动一个主节点（端口默认为`6379`）。
2. 创建一个从节点，有以下两种方法：
	- 修改配置文件。复制一份默认配置，设置其它的端口号（例如`8000`）启用`replicaof <masterip> <masterport>`这一行，其中`<masterip>`和`<masterport>`分别是主节点的主机名和端口号。使用该配置启动一个从节点。
	- 指定命令行参数。使用`./redis-server.exe --port <port> --replicaof <masterip> <masterport>`命令行参数指定端口、主节点主机名、主节点端口号。

在Redis CLI中使用`INFO REPLICATION`查看主从节点信息。其中`save_read_only:1`表示从节点是只读的。

```shell
localhost_6379_master:db0> INFO REPLICATION
# Replication
role:master
connected_slaves:1
slave0:ip=127.0.0.1,port=8000,state=online,offset=56,lag=0
master_failover_state:no-failover
master_replid:2645c133ae198e19831079d8867b258025569a6a
master_replid2:0000000000000000000000000000000000000000
master_repl_offset:56
second_repl_offset:-1
repl_backlog_active:1
repl_backlog_size:1048576
repl_backlog_first_byte_offset:1
repl_backlog_histlen:56

localhost_8000_slave:db0> INFO REPLICATION
# Replication
role:slave
master_host:127.0.0.1
master_port:6379
master_link_status:up
master_last_io_seconds_ago:3
master_sync_in_progress:0
slave_read_repl_offset:42
slave_repl_offset:42
slave_priority:100
slave_read_only:1
replica_announced:1
connected_slaves:0
master_failover_state:no-failover
master_replid:2645c133ae198e19831079d8867b258025569a6a
master_replid2:0000000000000000000000000000000000000000
master_repl_offset:42
second_repl_offset:-1
repl_backlog_active:1
repl_backlog_size:1048576
repl_backlog_first_byte_offset:1
repl_backlog_histlen:42

localhost_8000_slave:db0> SET username yaner
READONLY You can't write against a read only replica.
```

## §2.2 哨兵模式

## §2.3 集群模式


# §2x 场景实战

以下例子均用Java演示，需要导入这些包作为前置：

```java
package top.yaner_here.javasite;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.redis.connection.RedisConnectionFactory;
import org.springframework.data.redis.connection.RedisStandaloneConfiguration;
import org.springframework.data.redis.connection.jedis.JedisConnectionFactory;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.data.redis.core.StringRedisTemplate;

import static org.junit.jupiter.api.Assertions.*;

@Configuration @ComponentScan
class MyRedisApplicationConfiguration {
    @Bean public JedisConnectionFactory redisConnectionFactory() {
        return new JedisConnectionFactory(new RedisStandaloneConfiguration("localhost", 6379));
    }
    @Bean public RedisTemplate<String, String> stringRedisTemplate(@Autowired RedisConnectionFactory redisConnectionFactory) {
        StringRedisTemplate template = new StringRedisTemplate();
        template.setConnectionFactory(redisConnectionFactory);
        return template;
    }
}
```

## §2.1 过期

> 设计手机验证码登录的逻辑。手机验证码生成后的有效期只有一分钟，且每天每个手机号发送验证码的次数最多为三次。

使用Redis设置两个变量——当前验证码与今日验证码发送次数。

```java
@SpringBootTest(classes = MyRedisApplicationConfiguration.class) @Log4j2 
public class MyRedisApplicationTest {
    @Autowired RedisTemplate<String, String> stringRedisTemplate;
    @Test public void testTextVerifyCode() {
        final String phoneNumber = "123456789";
        final String verifyCode = "123456";

        String verifyCodeKey = "VERIFY_CODE_" + phoneNumber;
        String verifyCodeCountKey = "VERIFY_CODE_COUNT_" + phoneNumber;
        Integer verifyCodeCount = 0;
        try {
            String verifyCodeCountRedis = stringRedisTemplate.opsForValue().get(verifyCodeCountKey);
            verifyCodeCount = Integer.parseInt(verifyCodeCountRedis);
        } catch (NumberFormatException e) {
            log.info("Phone {} verification code count isn't cached in Redis.", phoneNumber);
        }
        if(++verifyCodeCount > 3) {
            log.info("Phone {} has exceeded verification code limit.", phoneNumber);
            return;
        }
        stringRedisTemplate.opsForValue().set(verifyCodeKey, verifyCode, 60, TimeUnit.SECONDS);
        stringRedisTemplate.opsForValue().set(
            verifyCodeCountKey,
            String.valueOf(verifyCodeCount),
            verifyCodeCount == 1 ? 24 * 60 * 60 : stringRedisTemplate.getExpire(verifyCodeCountKey),
            TimeUnit.SECONDS
        );
        log.info("Phone {} has refreshed the verify code.", phoneNumber);
    }
}
```

## §2x.x1 有序集合

> 给定若干个字符串作为搜索关键词，和一个用户输入到一半的前缀`p`。请返回任意10个前缀完全匹配的搜索关键词。

可以使用有序集合。我们根据字典序将搜索关键词存储在有序集合中。查询时我们只须设置上下界`p`和`p{`，进行区间查找即可。

```java
@SpringBootTest(classes = MyRedisApplicationConfiguration.class) @Log4j2
public class MyRedisApplicationTest {
    public Set<String> getSimilarKeywords(RedisTemplate<String, String> redisTemplate, String[] keywordsList, String keywordPrefix) {
        BoundZSetOperations<String, String> operations = redisTemplate.boundZSetOps("keywords");
        Arrays.stream(keywordsList).forEach(word -> {
            operations.add(word, 0);
        });
        String keywordPrefixStart = keywordPrefix + "`", keywordPrefixEnd = keywordPrefix + "{";
        operations.add(keywordPrefixStart, 0);
        operations.add(keywordPrefixEnd, 0);
        Long indexStart = operations.rank(keywordPrefixStart), indexEnd = operations.rank(keywordPrefixEnd);
        assert indexStart != null && indexEnd != null;
        if(indexEnd - indexStart > 10) {
            indexEnd = indexStart + 11;
        }
        return operations.range(indexStart + 1, indexEnd - 1);
    }
    @Test public void testIpCounter(@Autowired RedisTemplate<String, String> redisTemplate) {
        final String[] keywordsList = {"alice", "apple", "absent", "abuse", "academic", "advance", "as", "AI", "artificial", "aside", "above", "always", "anywhere", "affiliation"};
        assertTrue(getSimilarKeywords(redisTemplate, keywordsList, "b").isEmpty());
        assertTrue(getSimilarKeywords(redisTemplate, keywordsList, "a").size() == 10);
    }
}
```

## §2x.x2 超级日志

> 设计一个IPv4地址去重器。给定若干个IPv4地址构成的访问日志，求其去重后有多少个互异的IPv4地址。

```java
@SpringBootTest(classes = MyRedisApplicationConfiguration.class) @Log4j2
public class MyRedisApplicationTest {
    @Autowired RedisTemplate<String, String> stringRedisTemplate;
    private String generateRandomIPv4() {
        Random random = new Random();
        return random.nextInt(256) + "." + random.nextInt(256) + "." + random.nextInt(256) + "." + random.nextInt(256);
    }
    @Test public void testIpCounter() {
        HyperLogLogOperations hllOps = stringRedisTemplate.opsForHyperLogLog();
        hllOps.delete("IP_COUNTER");
        for(int i = 0; i < 10000; ++i) {
            hllOps.add("IP_COUNTER", generateRandomIPv4());
        }
        log.info("{} of 10000 IP was recorded", hllOps.size("IP_COUNTER"));
    }
}
```