# 攻防世界WriteUp
# Web
## 高手进阶区
### 3.PHP2
F12查看源码，发现什么也没有。
![[Pasted image 20220529000114.png]]
![[Pasted image 20220529000049.png]]
扫描站点，发现存在`index.php`与[[网络安全/CTF/PHP#phps 文件|`index.phps`]] 两个文件，得到源码：
```php
<?php
if("admin"===$_GET[id]) {
  echo("<p>not allowed!</p>");
  exit();
}

$_GET[id] = urldecode($_GET[id]);
if($_GET[id] == "admin")
{
  echo "<p>Access granted!</p>";
  echo "<p>Key: xxxxxxx </p>";
}
?>
Can you anthenticate to this website?
```
利用[[网络安全/CTF/PHP#URL二次编码绕过|URL二次编码绕过]]，得到payload为`?id=%2561%2564%256d%2569%256e`
![[Pasted image 20220529002801.png]]
Flag为`cyberpeace{67a2667d7292cf7219078caad8f4a0e9}`。

