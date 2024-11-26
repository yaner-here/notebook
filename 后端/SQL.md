# SQL

# §1 数据库/表

## §1.1 数据库

创建数据库：

```sql
create database MyWebsite;
```

```sql
create database 
	if not exists MyWebsite -- [if not exists],若已存在重名数据库则不报error:database exists
	default character set utf8 -- [default character set <CHARSET>],设定字符集
	default collate utf8 chinese_ci -- [default collate SORT_RULE],设定排序规则
```

删除数据库：

```sql
drop database demo;
drop database if exists demo;
```

## §1.2 表

创建表：

```sql
create table passage{
	primary key (id), -- 指定主键
	id integer not null, -- 非空
	title varchar(50),
	content text default null -- 指定默认值
};
```

删除表：

```sql
drop table users;
```

# §2 插入

单行插入：

```sql
insert into users(id,username,score) value (1,'张三',750);
```

多行插入：

```sql
insert into users(id,username,score) value
	(2,'李四',710)
	(3,'王五',500);
```

省略列清单插入：

```sql
insert into users value (4,'赵六',780);
```

隐式设定默认值：

```sql
insert into users value (5,default,150);
```

# §3 更改

单值更改：

```sql
update users set score=100 where id=2;
```

多值更改：

```sql
update users set score=100,username='幸运儿' where id=3;
```

# §4 查询

## §4.1 基础

最简单的查询：

```sql
select id,username from users;
```

指定列别名：

```sql
select id as '序号',username as '用户名' from users;
```

书写常数：

```sql
select 'VIP' as type,username from users;
```

表达式计算：

```sql
select username,score*2 as '分数的两倍' from users;
```

列举非重复记录：

```sql
select distinct username from users;
```

## §4.2 WHERE筛选

### §4.2.1 表达式判别

```sql
select username from users where score>=60;
-- 比较字符串时,将所有字符串按名称从小到大排序
-- 例如:'10'>'1','啊'<'这'
select username from users where username>'闫';
-- 比较NULL时,任何包含NULL的表达式均不为True,需要用IS NULL
select username from users where username = null;-- ×
select username from users where username is null;-- √
select username from users where username is not null ;-- √
-- 否定前缀NOT
select username from users where not username is null;
-- AND和OR,注意AND优先级大于OR
select username from users where id<5 and score>60;
select username from users where id<5 and (score>60 or score<100);
-- 可以将NULL理解为位于0和1之间的值,1>null>0
1 and null = null
0 and null = 0
1 or null =1
0 or null =null
```

### §4.2.2 LIKE筛选

`_`表示单个任意字符匹配，`%`表示不限长度的任意字符匹配。

```sql
select * from users where username like '小%'; -- 前方一致查询
select * from users where username like '%明'; -- 后方一致查询
select * from users where username like '%小%'; -- 中间一致查询
select * from users where username like '小_';
```

### §4.2.3 BETWEEN筛选

```sql
select username,score from users where score between 60 and 100;
select username,score from users where score>=60 and score<=100;
-- 两者等价
```

### §4.2.4 IN筛选

```sql
select username from users where username in ('张三','李四');
select username from users where username='张三' or username='李四';
-- 两者等价
```

### §4.2.5 EXIST筛选

`exist`和`no exist`用于多表筛选。

```sql
select id,username from users as p1 where exists
	(
        select 1 as WHATEVER_SOMETHING from users as p2
        	where p1.username='张三' and p2.score>60
    );
```

### §4.2.6 GROUP BY筛选

```sql
select username,count(username) from users group by username;
select username,count(username) from users group by username,id;
```

### §4.2.7 HAVING筛选

```sql
select username,count(*) from users where count(*)=2 group by username; -- ×
select username,count(*) from users group by username having count(*)=2; -- √
```

### §4.2.8 ORDER BY筛选

```sql
-- NULL会聚集在表首或表尾
select id,username from users order by username,id desc; -- descd
select id,username from users order by 2,1 desc;-- 数字代表select列
```

### §4.2.9 IN筛选

```sql
select id from users where username='张三' or username='李四';
select id from users where username in ('张三','李四');
```

### §4.2.10 LIKE筛选

```sql
-- 前方一致查询
    select * from users where username like 'a%';
-- 中间一致查询
    select * from users where username like '%g%';
-- 后方一致查询
    select * from users where username like '%z';
-- 通配符
```

### §4.2.11 BETWEEN筛选

```sql
select * from users where score between 50 and 80;
```

### §4.2.12 EXIST/NO EXIST筛选

```sql
select id,username from users as p1 where exists(
    select 1 as whatever_something from users as p2
        where p1.username='闫刚' and p2.score>60);
```

## §4.3 函数

### §4.3.1 统计类聚合函数

```sql
select count(*) from users; -- 统计表中一共有多少行,当且仅当实参为*时统计NULL
select count(score) from users; -- 统计表中score一列的数量,不包括NULL
select count(distinct username) from users; -- 统计不重名username的数量,不包括NULL
```

### §4.3.2 计算类聚合函数

```sql
select sum(score),avg(score),max(score),min(score) from users;
```

### §4.3.3 字符串函数

```sql
-- CONCAT(str,str,...),拼接字符串
    select concat(username,password) from users;
-- LENGTH(str),统计字符串占用字节数(ASCII1字节,UTF2字节)
    select length(concat(username,password)) from users;
-- UPPER(str)/LOWER(str),转换为大/小写
    select lower('ABC');
    select upper('abc');
-- REPLACE(string,pre_character,after_character),替换字符串
    select replace(username,'刘','闫') from users;
-- SUBSTRING(str FROM start FOR length),截取字符串(序号从1开始数)
    select substring(username from 1 for 1) from users;
    select substring(username,1,1) from users;-- 简化版
    select substr(username from 1 for 1) from users;
-- 另一种写法
    select substr(username,1,1) from users;
```

### §4.3.4 日期函数

```sql
-- CURRENT_DATE,返回当前日期(年-月-日)
    select current_date;
    select current_date();
-- CURRENT_TIMESTAMP,返回当前时间戳(年-月-日 时:分:秒)
    select current_timestamp();
    select current_timestamp;
-- CURRENT_TIME,返回当前时间(时:分:秒)
    select current_time;
    select current_time();
-- EXTRACT(type FROM date_variable),截取日期中的各种元素
    select extract(year from current_timestamp),
           extract(month from current_timestamp),
           extract(day from current_timestamp),
           extract(hour from current_timestamp),
           extract(minute from current_timestamp),
           extract(second from current_timestamp);
```

### §4.3.5 转换函数

```sql
-- CAST(variable,format),转换数据类型
    select cast(current_timestamp as date);-- 时间戳转换为日期
    select cast('0001' as signed integer);-- 字符串转换为整数
    select cast('2020-1-1' as date);-- 字符串转换为日期
-- COALESCE(null,variable,...),返回从左往右第一个不为NULL的值
    select coalesce(null,null,1,2);
    select coalesce(score,'NULL') from users;
-- 若为NULL则返回字符串'NULL'
```



# §5 高级

## §5.1 CASE表达式&CHECK约束

用于按照指定的条件对数据进行映射。

> 注意：
>
> - CASE表达式返回各值的数据类型应该保持一致。
> - 未指定`else`子句时，若存在某个值使得没有任何`when`的条件能匹配，则CASE表达式默认返回`NULL`。

### §5.1.1 CASE表达式种类

#### §5.1.1.1 简单CASE表达式

```sql
select username,case username
    when '嘉然Diana' then 'Asoul'
    when '七海Nana7mi' then 'Virtual Real'
    when '白神遥Haruka' then 'PSP Live'
    else '其它'
    end as '所属社团'
from users;
```

#### §5.1.1.2 搜索CASE表达式

```sql
select id,username,case
	when score>90 then '优秀'
	when score<60 then '不及格'
	else '良好'
	end as 'level'
from users;
```

### §5.1.2  具体应用

|   省份 `province`    |  广东  |  江苏  | 山东  | 浙江  | 河南  | 四川  | 福建  | 湖北  | 上海  |
| :------------------: | :----: | :----: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|       所属地区       |  华南  |  华东  | 华东  | 华东  | 华中  | 华西  | 华东  | 华中  | 华东  |
| 2020年GDP `GDP_2020` | 110760 | 102700 | 73129 | 64613 | 54997 | 48598 | 43903 | 43443 | 41781 |

#### §5.1.2.1 统计地区GDP总和——指定Group

```sql
select case province
    when '广东' then '华南'
    when '江苏' then '华东'
    when '山东' then '华东'
    when '浙江' then '华东'
    when '河南' then '华中'
    when '四川' then '华西'
    when '福建' then '华东'
    when '湖北' then '华中'
    when '上海' then '华东'
    end as district,
sum(GDP_2020) as '2020年GDP总和' from GDP group by district;
```

#### §5.1.2.2 统计GDP各档次的省数量——指定Group

```sql
select case
    when GDP_2020>=100000 then 'x>100000'
    when GDP_2020<100000 and GDP_2020>=50000 then '100000>x>=50000'
    else 'x<50000'
    end as GDP档次,
count('GDP情况') as '省份数量' from GDP group by GDP档次;
```

#### §5.1.2.3 对上题指定排列顺序——重构ORDER BY排序依据

```sql
-- select case
--  when GDP_2020>=100000 then 'x>100000'
--  when GDP_2020<100000 and GDP_2020>=50000 then '100000>x>=50000'
--  else 'x<50000'
--  end as GDP档次,
-- count('GDP情况') as '省份数量' from GDP group by GDP档次
order by case GDP档次
	when 'x<50000' then 1
	when '100000>x>=50000' then 2
	when 'x>100000' then 3
	end;
```

#### §5.1.2.4 统计每个人的总收入和总支出——CASE的内嵌调用

| 交易人 `username` | 张三 | 张三 | 王五 | 李四 | 王五 | 张三 |
| ----------------- | ---- | ---- | ---- | ---- | ---- | ---- |
| 交易类型 `type`   | 收入 | 支出 | 支出 | 收入 | 收入 | 支出 |
| 交易金额 `amount` | 100  | 200  | 100  | 400  | 300  | 100  |

- 方法一：在列清单添加各年数据TODO

  ```sql
  select p1.username,sum(p1.amount) from expense as p1 where p1.type='收入' group by p1.username
      inner join
  sum(p2.amount) from expense as p2 on where p2.type='支出' group by p2.username
  ```

- 方法二：CASE的内嵌调用

  ```sql
  select username,
  	sum(case when type='支出' then amount else 0 end) as '总支出',
  	sum(case when type='收入' then amount else 0 end) as '总收入'
  from expense group by username;
  ```

#### §5.1.2.5 对上题进行行列互换——CASE的内嵌调用

```sql
select 
	case type
		when '支出' then '总支出'
		when '收入' then '总收入'
	end as '交易类型',
	sum(amount) as '总数',
	sum(case when username='张三' then amount else 0 end) as '张三',
   	sum(case when username='李四' then amount else 0 end) as '李四',
   	sum(case when username='王五' then amount else 0 end) as '王五'
from expense group by type;
```

#### §5.1.2.6 限制单次支出交易金额——CHECK约束TODO

> 注意：
>
> - `constraint check`子句从MySQL 8.0.16开始才被引入，这使得它与`MariaDB`各版本不兼容。
>
>   | MariaDB | 5.1  | 5.3  | 5.5  | 10.0 | 10.1 | 10.2 | 10.3 |  10.4  |  10.5  |  10.6  |  10.7  |
>   | :-----: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :----: | :----: | :----: | :----: |
>   |  MySQL  | 5.0  | 5.5  | 5.5  | 5.6  | 5.6  | 5.7  | 5.7  | 8.0.22 | 8.0.22 | 8.0.25 | 8.0.25 |
>

```sql
constraint CheckAmount check
	(
        (
            case when type='支出' then 
                case when amount>300 then 1 
                else 0
                end
            else 1
            end
        )=1
    )
```

#### §5.1.2.7 $3n+1$猜想——构造单射函数

```sql
update SampleTable set number=case
	when number%2=0 then number/2
	when number%2=1 then 3*number+1
	else 'error'
	end;
```

每执行一次该语句，number的值就会由单射函数$f(x)=\begin{cases}\displaystyle\frac{x}{2}&x \in\bold{E}\\3x+1&x\in\bold{O}\end{cases}$进行映射。

#### §5.1.2.8 交换键值——CASE表达式内嵌标量子查询

```sql
update exchange set score=case
    when id=1 then (select score from exchange where id=2)
    when id=2 then (select score from exchange where id=1)
    else score
    end;
```

#### §5.1.2.9 生成授课课程表——CASE表达式

|   课程id `course_id`   |  1   |  2   |  3   |  4   |
| :--------------------: | :--: | :--: | :--: | :--: |
| 课程名称 `course_name` | 语文 | 数学 | 英语 | 物理 |

|  授课月份 `month`  |  6   |  6   |  6   |  7   |  8   |  8   |
| :----------------: | :--: | :--: | :--: | :--: | :--: | :--: |
| 课程id `course_id` |  1   |  3   |  4   |  4   |  2   |  4   |

```sql
select course_name,case
	when course_id in (select course_id from OpenCourseRecord where month=6) then '√'
	else '×' end as '6月',
case
	when course_id in (select course_id from OpenCourseRecord where month=7) then '√'
	else '×' end as '7月'
case
	when course_id in (select course_id from OpenCourseRecord where month=8) when '√'
	else '×' end as '8月'
from CourseList;
```

## §5.2 自连接

| 组合情况     | $\mathrm{C}_m^m=1$,有序非重复排列                            | $\mathrm{A}_m^m=m!$,无序非重复排列                           | $m^n$,无序重复排列(笛卡尔积)                           |
| ------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------ |
| 对应筛选代码 | $\forall i<j\in\N$,`pi.name<pj.name`                         | $\forall i\ne j\in\N$,`pi.name<>pj.name`                     | 无限制条件                                             |
| 代码示例     | `select p1.name,p2.name from sheet as p1,sheet as p2 where p1.name>p2.name;` | `select p1.name from sheet as p1,sheet as p2 where p1.name<>p2.name;` | `select p1.name,p2.name from sheet as p1,sheet as p2;` |

### §5.2.1 删除重复行

| 记录`ID`     | 1    | 2    | 3    | 4    |
| ------------ | ---- | ---- | ---- | ---- |
| 水果名`name` | 苹果 | 苹果 | 苹果 | 苹果 |
| 种类`type`   | A    | A    | B    | B    |
| 价格`price`  | 100  | 100  | 100  | 150  |

显然第一条和第二条数据重复，我们的目标是只留下其中一个。

```mysql
# 标量子查询
delete from product as p1
	where id < (
    	select Max(p2.id) from product as p2
        	where p1.name=p2.name and p1.type=p2.type and p1.price=p2.price
    );
# EXISTS
delete from product as p1
	where exists ( select * from product as p2
    	where p1.name=p2.name and p1.type=p2.type and p1.price=p2.price
    )
```

> 在MariaDB中，语法细节与MySQL有些地方不同，直接执行上述语句会报错。
>
> - 使用`delete`语句时，`delete from TableName`必须改为`delete Alias from TableName Alias`或`delete Alias from TableName as Alias`。（详见[StackOverflow](https://stackoverflow.com/questions/58728419/cant-use-alias-in-delete-statement-in-maria-db)）
>
> - MariaDB会认为用户在外层中尝试删除里层内准备`select`的表，这样会导致报错`[HY000][1093] (conn=17) Table 'p1' is specified twice, both as a target for 'DELETE' and as a separate source for data`。（详见[StackOverflow](https://stackoverflow.com/questions/44970574/table-is-specified-twice-both-as-a-target-for-update-and-as-a-separate-source/44971214)）
>
> ```mysql
> # MariaDB版 标量子查询
> delete p1 from product as p1
>     where id < (
>         select Max(p2.id) from (select * from product) as p2
>         where p1.name=p2.name and p1.type=p2.type and p1.price=p2.price
>     );
> # MariaDB版 EXISTS
> delete p1 from product as p1
> 	where exists ( select * from (select * from product) as p2
>     	where p1.name=p2.name and p1.type=p2.type and p1.price=p2.price
>     )
> ```

### §5.2.2 删除矛盾行

相同的水果，相同的种类，对应的价格应该是一样的。容易找出所有互相矛盾的记录：

```mysql
select p1.id from product as p1, product as p2
	where p1.name=p2.name..........................T
```
