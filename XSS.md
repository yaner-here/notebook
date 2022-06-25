# XSS

攻击者通过可控参数，将恶意JavaScript代码块注入HTML中，污染用户看到的页面





反射型XSS/非持久型XSS

反射型XSS通过破坏原HTML结构中的`""`与`<>`的闭合关系，从而插入恶意代码块。

> 以下面的PHP页面为例：
>
> ```php+HTML
> <!DOCTYPE html>
> <html>
> 	<body>
>         <input type="text" value="<?php echo $_GET['a']; ?>">
>     </body>
> </html>
> ```
>
> 其中`$_GET['a']`参数完全可控，考虑插入一段弹窗JavaScript代码：
>
> ```php+HTML
> <!-- ?a="><script>alert("XSS Hacked");</script><input type="hidden 
> 	经过URL转码得到?a=%22%3E%3Cscript%3Ealert(%22XSS%20Hacked%22);%3C/script%3E%3Cinput%20type=%22hidden
> -->
> 
> <!DOCTYPE html>
> <html>
> 	<body>
>         <input type="text" value="
>             "><script>alert("XSS Hacked");</script><input type="hidden
>         ">
>     </body>
> </html>
> ```





存储型XSS/持久型XSS

存储型XSS在反射型XSS的基础上，将恶意payload保存到数据库中。

> 以下面的站点为例：
>
> 首先创建数据库：
>
> ```sql
> CREATE DATABASE xss;
> use xss;
> CREATE TABLE users(
>     id int(5) NOT NULL,
>     name varchar(128) DEFAULT '',
>     PRIMARY KEY (id)
> );
> ```
>
> 创建登录、注册与欢迎页面：
>
> ```php+HTML
> <!DOCTYPE html>
> <meta charset="utf-8">
> <html>
> 	<body>
>     <?php
>         $connection = mysqli_connect("localhost","root","root","xss",3306);
>         mysqli_select_db($connection,'xss');
>         if(mysqli_connect_errno($connection)) {
>             echo "连接失败" . mysqli_connect_error();
>             exit();
>         }
>         if(isset($_GET['id'])&&isset($_GET['name'])){
>             $sql = "INSERT INTO users(id,name) values(".$_GET['id'].",'".$_GET['name']."')";
>             mysqli_query($connection,$sql);
>             mysqli_errno($connection) ? print($connection->error) : print("SQL语句执行成功！") ;
>             echo "注册成功";
>         }elseif(isset($_GET['id'])) {
>             $sql = "select * from users where id=".$_GET['id'];
>             $result = mysqli_query($connection,$sql);
>             mysqli_errno($connection) ? print($connection->error) : print("SQL语句执行成功！") ;
>             if($row = mysqli_fetch_array($result)){
>                 echo "欢迎您,".$row['name'];
>             }else{
>                 echo "用户不存在，请重新检查id是否存在";
>             }
>         }else{
>             echo "你还没有登录，可以通过GET传参id登录，或者通过GET传参id和name注册";
>         }
>     ?>
>     </body>
> </html>
> ```
>
> 测试网站是否运行正常：
>
> ```
> localhost/index.php 
> 	// 你还没有登录，可以通过GET传参id登录，或者通过GET传参idi和name注册
> localhost/index.php?id=0 
> 	// SQL语句执行成功！用户不存在，请重新检查id是否存在
> localhost/index.php?id=0&name=hello 
> 	// SQL语句执行成功！注册成功
> localhost/index.php?id=0 
> 	// SQL语句执行成功！欢迎您,hello
> ```
>
> 尝试注入存储型XSS：
>
> ```
> localhost/index.php?id=1 
> 	// SQL语句执行成功！用户不存在，请重新检查id是否存在
> localhost/index.php?id=1&name=<script>alert("XSS hacked");</script> 
> 	// SQL语句执行成功！注册成功
> localhost/index.php?id=1
> 	// 弹窗，XSS hacked
> ```







DOM型XSS

DOM型XSS将恶意代码放在DOM的属性参数中，当其作为DOM元素被前端所`Document.createElement()`时被执行。

> u
>
> ```php+HTML
> <!DOCTYPE html>
> <meta charset="utf-8">
> <html>
> 	<body>
>     <?php
>         $a = @$_GET['a'];
>     ?>
>     <input id="a" type="text" value="<?php echo $a; ?>">
>     <script>
>         let test = document.getElementById("a");
>         let display = document.createElement("display");
>         display.innerHTML = test.value;
>     </script>
>     </body>
> </html>
> ```



DVWA的DOM题解



蝉知门户系统（chanzhiEPS）三次URL编码XXS漏洞

蝉知门户系统是



