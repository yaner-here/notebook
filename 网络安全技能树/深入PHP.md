# §1 函数参考
## §1.20 Session扩展

Session的本质是一个二进制文件。其文件名为`sess_`+`PHPSESSID`。其中`PHPSESSID`可从浏览器的Cookie中获取：

```php
<?php
session_save_path('./');
session_start();
$_SESSION['username'] = 'admin';
$_SESSION['password'] = "123456";
```

Session的存储引擎由`php.ini`中的`session.serialize_handler`参数决定：

```ini
; Handler used to serialize data. php is the standard serializer of PHP.
; https://php.net/session.serialize-handler
session.serialize_handler = php
```

根据[官方文档](https://www.php.net/manual/en/session.configuration.php)，PHP提供了三种不同的存储引擎：

- `php_serialize`：PHP Serialize Format，对应的Session等于`serialize($_SESSION)`。

  ```shell
  $ hexdump -C sess_......
  00000000  61 3a 32 3a 7b 73 3a 38  3a 22 75 73 65 72 6e 61  a:2:{s:8:"userna
  00000010  6d 65 22 3b 73 3a 35 3a  22 61 64 6d 69 6e 22 3b  me";s:5:"admin";
  00000020  73 3a 38 3a 22 70 61 73  73 77 6f 72 64 22 3b 73  s:8:"password";s
  00000030  3a 36 3a 22 31 32 33 34  35 36 22 3b 7d           :6:"123456";}
  ```

- `php_binary`/`php`：PHP Internal Format

  `php`对应的Session为键名+竖线+经过`serialize()`序列化的值。

  ```shell
  $ hexdump -C sess_......
  00000000  75 73 65 72 6e 61 6d 65  7c 73 3a 35 3a 22 61 64  username|s:5:"ad
  00000010  6d 69 6e 22 3b 70 61 73  73 77 6f 72 64 7c 73 3a  min";password|s:
  00000020  36 3a 22 31 32 33 34 35  36 22 3b                 6:"123456";
  ```

  `php_binary`在`php`的基础上，在每个键名之前都添加一个`chr(键名长度)`的ASCII字符。

  ```shell
  $ hexdump -C sess_......
  00000000  08 75 73 65 72 6e 61 6d  65 73 3a 35 3a 22 61 64  .usernames:5:"ad
  00000010  6d 69 6e 22 3b 08 70 61  73 73 77 6f 72 64 73 3a  min";.passwords:
  00000020  36 3a 22 31 32 33 34 35  36 22 3b                 6:"123456";
  ```

- `wddx`：Web Distributed Data eXchange机制。此选项要求编译PHP时加入WDDX支持。

> - `session.serialize_handler` string
>
>   `session.serialize_handler` defines the name of the handler which is used to serialize/deserialize data. PHP serialize format (name `php_serialize`), PHP internal formats (name `php` and `php_binary`) and WDDX are supported (name `wddx`). WDDX is only available, if PHP is compiled with [WDDX support](https://www.php.net/manual/en/ref.wddx.php). `php_serialize` uses plain serialize/unserialize function internally and does not have limitations that `php` and `php_binary` have. Older serialize handlers cannot store numeric index nor string index contains special characters (`|` and `!`) in $_SESSION. Use `php_serialize` to avoid numeric index or special character errors at script shutdown. Defaults to `php`.

require_once()重复包含：https://syunaht.com/p/2339718074.html