# §1 函数参考

## §1.13 数学扩展（Mathematical Extensions）

### §1.13.36 梅森旋转算法——`mt_getrandmax()`、`mt_rand()`、`mt_srand()`

[梅森旋转算法](https://en.wikipedia.org/wiki/Mersenne_Twister)是一种伪随机数生成算法，现在被广泛应用于多种编程语言的默认随机数生成器。PHP为其提供了`mt_getrandmax()`、`mt_rand()`、`mt_srand()`这三个API实现。

- `mt_getrandmax(): int`

  该函数返回`mt_rand()`可能返回的最大值。PHP默认使用的是32位版本的梅森旋转算法，因此返回的最大值为$2^{32}-1$。

- `mt_srand(int $seed = 0, int $mode = MT_RAND_MT19937): void`

  这是梅森旋转算法的种子`$seed:int`，若`$seed`等于0，则缺省值为**`mt_srand()`或`mt_rand()`第一次被调用时的时间戳**。

  > 在PHP 7.1.0之前，PHP使用的梅森旋转算法一直是错误的。为保证兼容性，对应的`$mode`为`MT_RAND_PHP`。
  >
  > 自PHP 7.1.0起，PHP使用的是正确的梅森旋转算法，并将`srand()`和`mt_srand()`合并成功能完全相同的函数。为保证兼容性，这两个函数都保留了下来，对应的`$mode`为`MT_RAND_MT19937`。

- `mt_rand([$min = 0, $max = mt_getrandmax()]): int`

  随机返回`[$min,$max]`范围之内的一个整数。

梅森旋转算法虽然运算速度快，且能产生高质量的随机数，但是它本身不是一个密码学意义上的安全算法。理论上只要能获取其一段连续的时间内产生的足够多的随机数输出，那么就可以反向逆推出使用的种子。

`php_md_seed`是开源项目[Openwall](https://www.openwall.com/php_mt_seed)发布的一款PHP梅森旋转算法的种子爆破工具。

- `PHP < 3.0.6`：使用`php_mt_seed 3.4`
- `PHP >= 3.0.7`：使用`php_mt_seed 4.0`

```shell
$ curl -O https://www.openwall.com/php_mt_seed/php_mt_seed-4.0.tar.gz
      % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                     Dload  Upload   Total   Spent    Left  Speed
    100 15608  100 15608    0     0   7290      0  0:00:02  0:00:02 --:--:--  7293

$ tar -x -f php_mt_seed-4.0.tar.gz
$ cd php_mt_seed-4.0/
$ ls
	Makefile  php_mt_seed.c  README

$ make
    gcc -Wall -march=native -mtune=generic -O2 -fomit-frame-pointer -funroll-loops -fopenmp php_mt_seed.c -o php_mt_seed
    php_mt_seed.c:47:2: warning: #warning AVX-512 not enabled. Try gcc -mavx512f (on Intel Knights Landing, Skylake-X, or some newer). [-Wcpp]
       47 | #warning AVX-512 not enabled. Try gcc -mavx512f (on Intel Knights Landing, Skylake-X, or some newer).
          |  ^~~~~~~
```

使用方法：

1. 根据`mt_rand()`的第一个随机数爆破种子

   只输入一个形参，`./php_mt_seed <mt_rand()的第一个随机数>`：

   ```shell
   $ php -r 'mt_srand(1234567890); echo mt_rand(), "\n";'
       1328851649
   
   $ time ./php_mt_seed 1328851649
       Pattern: EXACT
       Version: 3.0.7 to 5.2.0
       Found 0, trying 0xfc000000 - 0xffffffff, speed 18382.0 Mseeds/s 
   	......
       seed = 0x499602d2 = 1234567890 (PHP 5.2.1 to 7.0.x; HHVM)
       seed = 0x499602d2 = 1234567890 (PHP 7.1.0+)
       Found 4, trying 0xfe000000 - 0xffffffff, speed 195.7 Mseeds/s 
       Found 4
   
       ________________________________________________________
       Executed in   22.19 secs    fish           external
          usr time  262.45 secs  436.00 micros  262.44 secs
          sys time    0.12 secs    0.00 micros    0.12 secs
   ```

2. 根据`mt_rand()`输出的第一个数的上下界爆破种子

   输入两个形参，`./php_mt_seed <mt_rand()的第一个随机数的下界> <mt_rand()的第一个随机数的上界>`：

   ```shell
   $ php -r 'mt_srand(114514); echo mt_rand(), "\n";'
   1476944489
   
   $ time ./php_mt_seed 1476944488 1476944490
       Pattern: RANGE
       Version: 3.0.7 to 5.2.0
       Found 0, trying 0x2c000000 - 0x2fffffff, speed 2050.5 Mseeds/s 
       seed = 0x2e3ee3ae = 775873454 (PHP 3.0.7 to 5.2.0)
       seed = 0x2e3ee3af = 775873455 (PHP 3.0.7 to 5.2.0)
       ......
       Found 8, trying 0x00000000 - 0x01ffffff, speed 0.0 Mseeds/s 
       seed = 0x0001bf52 = 114514 (PHP 7.1.0+)
       ......
       Found 23, trying 0xfe000000 - 0xffffffff, speed 140.5 Mseeds/s 
       Found 23
   
       ________________________________________________________
       Executed in   32.82 secs    fish           external
          usr time  379.62 secs  426.00 micros  379.62 secs
          sys time    0.18 secs    0.00 micros    0.18 secs
   ```

3. 根据`mt_rand($min,$max)`输出的第一个数的上下界爆破种子

   输入四个形参，`./php_mt_seed <mt_rand()的第一个随机数的下界> <mt_rand()的第一个随机数的上界>,<$min>,<$max>`：

4. 根据`mt_rand($min,$max)`输出的一系列数字的上下界爆破种子

   输入大于等于五个形参，从头开始，每$4$个实参一组等价于第3种情况，剩余的0~3个实参等价于第1/2种情况。

   ```php
   # test.php
   <?php
   mt_srand(114514);
   for($i = 10000000 ; $i < 10000010 ; $i++){
       $random = mt_rand($i,2*$i);
       printf("%d %d %d %d ",$random,$random,$i,2*$i);
   }
   ```

   ```shell
   $ php ./test.php
       13888684 13888684 10000000 20000000 19083320 19083320 10000001 ......
   
   $ time ./php_mt_seed `php ../test.php`
       Pattern: EXACT-FROM-10000001 EXACT-FROM-10000002 EXACT-FROM-10000003 EXACT-FROM-10000004 EXACT-FROM-10000005 EXACT-FROM-10000006 EXACT-FROM-10000007 EXACT-FROM-10000008 EXACT-FROM-10000009 EXACT-FROM-10000010
       Version: 3.0.7 to 5.2.0
       Found 0, trying 0xfc000000 - 0xffffffff, speed 1368.2 Mseeds/s 
       Version: 5.2.1+
       Found 0, trying 0x00000000 - 0x01ffffff, speed 0.0 Mseeds/s 
       seed = 0x0001bf52 = 114514 (PHP 7.1.0+)
       Found 1, trying 0xfe000000 - 0xffffffff, speed 117.2 Mseeds/s 
   
       real    0m39.857
       user    7m44.354s
       sys     0m0.253s
   ```

   

## §1.20 Session扩展（Session Extensions）

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