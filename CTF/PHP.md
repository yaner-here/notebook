# PHP
## 信息收集
### 源码泄露
#### `.phps`文件
如果直接访问`.php`文件，用户得到的是该文件执行后的结果。为了便于用户查看其源码，民间自行规定了`.phps`这一文本后缀名。
### 过滤绕过
#### URL二次编码绕过
要让传参同时满足`$_GET[] != KEYWORD`与`urldecode($_GET[]) === KEYWORD` ，就需要对参数进行URL二次编码：
```php
$text = "admin";
$text_urlencoded = "%61%64%6d%69%6e";
$text_urlencoded_twice = "%25%36%31%25%36%34%25%36%64%25%36%39%25%36%65";
$text_urlencoded_twice_short = "%2561%64%6d%69%6e";  // 只对第一个%再编码

echo $text === "admin"; // 1
echo $text_urlencoded === "admin"; // 0
echo urldecode($text_urlencoded) === "admin"; // 1
echo urldecode($text_urlencoded_twice) == "admin"; // 0
echo urldecode(urldecode($text_urlencoded_twice)) === "admin" // 1
echo urldecode(urldecode($text_urlencoded_twice_short)) === "admin"; // 1
```
需要注意的是，`$_GET[]`本身会将URL编码进行一次解码，所以payload需要经过两次URL编码。