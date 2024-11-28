# ThinkPHP

ThinkPHP是一个支持MVC模式的、免费开源的轻量级PHP开发框架，使用Apache2开源许可证。

# §1 初见ThinkPHP

ThinkPHP支持Composer安装：

```shell
$ composer create-project topthink/think=5.0.* thinkphp
$ ls
    application   composer.json  LICENSE.txt  runtime   vendor
    build.php     composer.lock  public       think
    CHANGELOG.md  extend         README.md    thinkphp
```

```shell
$ php -S localhost:8080 -t public
```

# §2 配置

配置加载顺序如下，优先级越来越低：

1. 框架配置/惯例配置：框架自带的默认配置

   ThinkPHP通过`\think\Config::get()`和`\think\Config::set()`来获取和更改属性值。下面我们尝试在ThinkPHP框架中调用该函数：

   ```php
   /* 更改application/index/controller/index.php */
   <?php
   namespace app\index\controller;
   use think\Config;
   class Index{
       public function index(){
           echo json_encode(Config::get(),JSON_PRETTY_PRINT);
       }
   }
   ```

   ```php
   $ curl localhost:8080
   { 
       "app_debug": true, 
       "app_trace": false, 
       "app_status": "", 
       "app_multi_module": true, 
       "auto_bind_module": false, 
       "root_namespace": [], 
       "extra_file_list": [ "C:\\WWW\\thinkphp\\helper.php" ],
       "default_return_type": "html", 
       "default_ajax_return": "json", 
       "default_jsonp_handler": "jsonpReturn", 
       "var_jsonp_handler": "callback", 
       "default_timezone": "PRC", 
       "lang_switch_on": false, 
       "default_filter": "", 
       "default_lang": "zh-cn", 
       "class_suffix": false, 
       "controller_suffix": false, 
       "default_module": "index", 
       "deny_module_list": [ "common" ], 
       "default_controller": "Index", 
       "default_action": "index", 
       "default_validate": "", 
       "empty_controller": "Error", 
       "use_action_prefix": false, 
       "action_suffix": "", 
       "controller_auto_search": false, 
       "var_pathinfo": "s", 
       "pathinfo_fetch": [
           "ORIG_PATH_INFO", "REDIRECT_PATH_INFO", "REDIRECT_URL" 
       ],
       "pathinfo_depr": "\/",
       "url_html_suffix": "html", 
       "url_common_param": false, 
       "url_param_type": 0, 
       "url_route_on": true, 
       "route_config_file": [ "route" ], 
       "route_complete_match": false, 
       "url_route_must": false, 
       "url_domain_deploy": false, 
       "url_domain_root": "", 
       "url_convert": true, 
       "url_controller_layer": "controller", 
       "var_method": "_method", 
       "var_ajax": "_ajax", 
       "var_pjax": "_pjax", 
       "request_cache": false, 
       "request_cache_expire": null, 
       "request_cache_except": [], 
       "template": {
           "type": "Think",
           "view_path": "", 
           "view_suffix": "html", 
           "view_depr": "\\", 
           "tpl_begin": "{", 
           "tpl_end": "}", 
           "taglib_begin": "{", 
           "taglib_end": "}" 
       }, 
       "view_replace_str": [],
       "dispatch_success_tmpl": "C:\\WWW\\thinkphp\\tpl\\dispatch_jump.tpl", 
       "dispatch_error_tmpl": "C:\\WWW\\thinkphp\\tpl\\dispatch_jump.tpl", 
       "exception_tmpl": "C:\\WWW\\thinkphp\\tpl\\think_exception.tpl", 
       "error_message": "页面错误！请稍后再试～", 
       "show_error_msg": false,
       "exception_handle": "",
       "log": { 
           "type": "File", 
           "path": "C:\\WWW\\runtime\\log\\",
           "level": [] 
       }, 
       "trace": {
           "type": "Html" 
       }, 
       "cache": {
           "type": "File", 
           "path": "C:\\WWW\\runtime\\cache\\", 
           "prefix": "", 
           "expire": 0 
       }, 
       "session": {
           "id": "", 
           "var_session_id": "", 
           "prefix": "think", 
           "type": "", 
           "auto_start": true 
       }, 
       "cookie": { 
           "prefix": "", 
           "expire": 0, 
           "path": "\/", 
           "domain": "", 
           "secure": false, 
           "httponly": "", 
           "setcookie": true 
       }, 
       "database": { 
           "type": "mysql", 
           "dsn": "", 
           "hostname": "127.0.0.1", 
           "database": "", 
           "username": "root", 
           "password": "", 
           "hostport": "", 
           "params": [], 
           "charset": "utf8", 
           "prefix": "", 
           "debug": true, 
           "deploy": 0, 
           "rw_separate": false, 
           "master_num": 1, 
           "slave_no": "", 
           "fields_strict": true, 
           "resultset_type": "array", 
           "auto_timestamp": false, 
           "datetime_format": "Y-m-d H:i:s", 
           "sql_explain": false 
       }, 
       "paginate": {
           "type": "bootstrap", 
           "var_page": "page", 
           "list_rows": 15 
       },
       "queue": {
           "connector": "Sync" 
       } 
   }
   ```

2. 全局配置：`application/config.php`

   编辑`application/config.php`：

   ```php
   /* 编辑application/config.php */
   <?php
   return [
       ......
       "YanerMessage" => "Hello, World",
       ......
   ]
   ```

   刷新页面即可看到全局配置：

   ```json
   $ curl localhost:8080
   { 
       ......
       "yanermessage": "Hello, World", 
       ......
   }
   ```

3. 扩展配置：`application/extra/*`

   在`application/extra`目录下新建一个`amqp.php`，用于模拟AMQP协议：

   ```php
   /* 新建application/extra/amqp.php */
   <?php
   return [
       'conn' => 'amqp://localhost:5672'
   ];
   ```

   在`application/index/controller/index.php`中输出框架配置：

   ```php
   /* 查看application/index/controller/index.php */
   ......
       public function index(){
       	echo json_encode(Config::get(),JSON_PRETTY_PRINT);
   	}
   ......
   ```

   即可在框架配置中查看`amqp.php`扩展的配置：

   ```json
   $ curl localhost:8080
   {
       ......
   	"amqp": {
           "conn": "amqp:\/\/localhost:5672" 
       },
       ......
   }
   ```

4. 场景配置：`app_status`常量

   先根据第3条设置“扩展配置”，然后在`application/`目录下新建`home.php`：

   ```php
   /* 新建application/home.php */
   <?php
   return [
       'amqp' => [
           'conn' => 'I am in home now!'
       ]
   ];
   ```

   将`application/config.php`的`app_status`属性更改为`home`，刷新页面即可看到`amqp`扩展的输出发生变化：

   ```json
   $ curl localhost:8080
   {
       ......
       "amqp": {
           "conn": "I am in home now!" 
       },
       ......
   }
   ```

   也可以接着在`application/index`目录下新建`home.php`：

   ```php
   /* 新建application/index/home.php */
   <?php
   return [
       'amqp' => [
           'conn' => 'I am index module home config'
       ]
   ];
   ```

   刷新页面即可看到变化：

   ```json
   $ curl localhost:8080
   { 
       ......
       "amqp": { 
           "conn": "I am index module home config" 
       }, 
   	......
   }
   ```

5. 模块配置：`application/模块名/config.php`

   在`application/index`目录下新建`config.php`：

   ```php
   /* 新建application/index/config.php */
   <?php
   return [
       'amqp' => [
           'conn' => 'I am in index module now!'
       ]
   ];
   ```

   刷新页面即可看到变化：

   ```json
   $ curl localhost:8080
   {
       ......
       "amqp": {
           "conn": "I am in index module now!" 
       }, 
   	......
   }
   ```

6. 动态配置：自定义`Config`类

   编辑`application/index/controller`目录下的`index.php`：

   ```php
   /* 编辑application/index/controller/index.php */
   class Index {
       public function index(){
           ......
       }
       public function configTest(){
           var_dump(Config::get("test"));
           Config::set("test","Hello World");
           var_dump(Config::get("test"));
       }
   }
   ```
   
   访问`localhost:8080/index/index/coonfigTest`：
   
   ```shell
   $ curl localhost:8080/index/index/configTest
       C:\WWW\application\index\controller\Index.php:13:null
       C:\WWW\application\index\controller\Index.php:15:string 'Hello World' (length=11)
   ```
   
   
   
   
   
   

# §3 路由

ThinkPHP 5支持PATHINFO规则进行路由：

   ```
   http://server/module/controller/action/param/value/
   ```

## §3.1 路由模式

ThinkPHP 5通过`application/config.php`中的`url_route_on`和`url_route_must`这两个布尔参数控制陆路由的行为，由此可以延伸出三种路由模式——**普通模式、混合模式、强制模式**：

   | 路由模式                 | `url_route_on`参数值 | `url_route_must`参数值 | 含义                                  |
   | ------------------------ | -------------------- | ---------------------- | ------------------------------------- |
   | 普通模式（PATHINFO模式） | `false`              |                        | 只执行PATHINFO规则                    |
   | 混合模式（默认）         | `true`               | `false`                | 优先执行自定义路由，然后PATHINIFO规则 |
   | 强制模式                 | `true`               | `true`                 | 强制要求所有请求必须设置路由          |

## §3.2 路由定义

### §3.2.1 编码定义

编码定义指的是在`application/route.php`中以硬编码的方式定义路由：

```php
/* 编辑applicationi/route.php */
// \think\Route::rule(路由表达式,路由地址,请求方法,路由条件,变量规则);

\think\Route::rule('news/:id','index/News/read','GET|POST');
	// 将GET或POST方法访问news/123视作访问index模块的News控制器的read方法
```

ThinkPHP 5还支持单独指定HTTP请求方法：

```php
\think\Route::get	('news/:id','index/News/read'); // 匹配GET方法
\think\Route::post	('news/:id','index/News/read'); // 匹配POST方法
\think\Route::put	('news/:id','index/News/read'); // 匹配PUT方法
\think\Route::delete('news/:id','index/News/read'); // 匹配DELETE方法
\think\Route::any	('news/:id','index/News/read'); // 匹配任意方法
```

### §3.2.2 配置定义

编码定义指的是在`application/route.php`中以返回数组的方式定义路由：

```php
<?php
return [
    'news/:id' => 'index/News/read',			// 定义必选变量
    'news/[:id]' => 'index/News/read',			// 定义可选变量
    'news/:id$' => 'index/News/read',			// 定义完全匹配
    'news/:id' => 'index/News/read?status=1',	// 定义隐式传参
    'news/:id' => [								// 限制变量类型
        'index/News/read',
        ['ext'=>'html'],
        ['id'=>'\d{4}']
    ]
]
```

在满足路由定义的前提下，路由条件负责是否接受/拒绝该请求：

| 路由参数名称       | 数据类型   | 作用                                         |
| ------------------ | ---------- | -------------------------------------------- |
| `method`           | `string`   | 允许的HTTP请求方法（支持`|`匹配多个值）      |
| `ext`              | `string`   | 允许的URL后缀（支持`|`匹配多个值）           |
| `deny_ext`         | `string`   | 禁止的URL后缀（支持`|`匹配多个值）           |
| `https`            | `bool`     | 是否接受https请求                            |
| `domain`           | `string`   | 允许的域名                                   |
| `before_behaviour` | `function` | 前置行为检测，通过返回的布尔值决定是否接受   |
| `callback`         | `function` | 自定义条件函数，通过返回的布尔值决定是否接受 |
| `merge_extra_vars` | `bool`     | 合并额外参数                                 |
| `bind_model`       | `array`    | 绑定模型                                     |
| `cache`            | `integer`  | 当前路由缓存的保存时长（秒）                 |
| `param_depr`       | `string`   | 路由参数分隔符                               |
| `ajax`             | `bool`     | 是否接受ajax请求                             |
| `pjax`             | `bool`     | 是否接受pjax请求                             |

```php
/* application/route.php */
return [
    'news/:id' => [
        'news/show/:name$',
        [
            'method' => 'get|post', // 只允许GET和POST方法
            'ext' => 'shtml', // 只允许shtml后缀
            'deny_ext' => 'shtml', // 不允许shtml后缀
            'https' => true, // 只允许https
            'domain' => 'www.example.com', // 只允许www.wxample.com域名
            'before_behaviour' => 'app\index\behaviour\before', // 调用index模块的before()方法，根据布尔返回值决定是否匹配
            'callback' => function(){return true;}, // 根据布尔返回值决定是否匹配
            'merge_extra_vars' => true, // 合并额外参数，例如访问/news/show/a/b/c，得到的name仅为a/b/c
            'bind_model' => ['User','name'], // 将绑定到User模型的name属性
            'cache' => 3600, // 缓存当前路由一小时
            'param_depr' => '///', // 使用///作为分隔符，而不是默认的/
            'ajax' => true, // 允许ajax请求
            'pjax' => true // 允许pjax请求
        ]
    ]
]
```

## §3.3 路由地址

路由地址指的是路由匹配成功后执行的操作，分为以下五种：

### §3.3.1 路由到模块指定的控制器

控制器定义如下：

```shell
$ tree ./application
│  ......
├─index
│  └ ......  
└─news
    └─controller
            News.php
```

```php
/* 新建application/news/controller/News.php */
<?php
namespace app\news\controller; // 注意命名空间！
class News{
    public function read($id){
        echo '您访问的是第'.$id.'号新闻';
    }
}
```

测试可以正常访问：

```
$ curl localhost:8080/news/news/show/id/000001
	您访问的是第000001号新闻
```

现在设置路由：

```php
/* 修改application/route.php */
'news/:id' => 'index/news/read'
```

测试路由：

```shell
$ curl localhost:8080/news/000001
	您访问的是第000001号新闻
```

### §3.3.2 重定向

这种方式会向浏览器发送301或302的HTTP状态码，路由配置如下：

```php
/* 修改application/route.php */
'news/:id' => 'news/show/:id.html' // 站内跳转
'news/:id' => 'http://www.example.com/news/show/:id.html' // 站外跳转
```

### §3.3.3 路由到直接指定的控制器方法

这种方式不需要按照PATHINFO模式走一遍，也不用实例化控制器类，而是直接执行调用方法。因此不能获取到当前模块名、控制器名、方法名，因为ThinkPHP框架没有初始化这些变量，获取时会报错：

```php
/* 修改application/route.php */
'news/:id' => '@news/news/show/'
```

测试路由：

```shell
$ curl localhost:8080/news/000001
	您访问的是第000001号新闻
```

### §3.3.4 路由到类静态方法

这种方式允许访问包括控制器类在内的**任何类的静态方法**：

```php
/* 修改application/route.php */
'news/:id' => 'app\index\controller\News::show'
```

### §3.3.5 路由到闭包

这种方式允许直接在`application/router.php`直接定义路由的内容：

```php
/* 修改application/route.php */
Route::get(
    'news/:id',
	function($id){
        return '您访问的是第'.$id.'号新闻';
    }
)
```

## §3.4 路由分组

我们可以将多个路由合并到一个分组中：

```php
/* 修改application/route.php */
// 两条独立的路由
'news/:id' => ['index/news/show',['method'=>'get']],
'news/post/:id' => ['index/news/post',['method'=>'post']]
    
// 一个路由分组
'[news]' => [
    ':id' => ['index/news/show',['method'=>'get']],
    'post/:id' => ['index/news/post',['method'=>'post']]
]
```

## §3.5 404路由

404路由`__miss__`用于处理所有路由规则不匹配的情况：

```php
/* 修改application/route.php */
'[news]' => [
    ':id' => ['index/news/show',['method'=>'get']],
    '__miss__' => 'index/index/notfound' // 局部404路由
],
'__miss__' => 'index/index/notfound' // 全局404路由
```

## §3.6 路由绑定

如果当前的入口文件只使用一个模块，则可以使用路由绑定以简化路由定义，不用每次都声明模块名：

```php
/* 修改application/route.php */
Route::bind('index'); // 绑定index模块
'news/:id' => 'news/show'
```

## §3.7 URL生成

可以通过`Url::build()`或`url()`生成路由：

```php
/* 修改application/route.php */
Url::build(路由地址,参数,伪静态后缀,是否加上域名);
url(路由地址,参数,伪静态后缀,是否加上域名);

'news/:id' => 'news/show'
url('news/show',['id'=>1],'html'); // 生成的URL为"/news/1.html"
```

# §4 控制器

控制器（Controller）是MVC模式中负责协调视图和模型的一层。ThinkPHP 3要求所有控制器类必须继承`Controller`类，而ThinkPHP 5开始不再强制要求。

我们之前已经接触过控制器了，最简单的例子在`application/index/controller/index.php`：

```php
/* 查看application/index/controller/index.php */
<?php
namespace app\index\controller;
class Index{
    public function index(){
        return "......ThinkPHP 5 由亿速云提供......";
    }
}
```

> 注意：ThinkPHP 3的所有控制器类的方法全部使用`echo`进行输出，而ThinkPHP 5既可以使用`echo`，也可以使用`return`，其中官方更推荐`return`。

## §4.1 初始化操作

ThinkPHP框架使用类的反射来实例化控制类，这使得我们不能轻易更改`__construct()`方法的形参列表进行初始化。为弥补这一缺陷，ThinkPHP提供了`_initialize()`方法作为替代品。

## §4.2 前置操作

ThinkPHP框架在控制器中提供了`$beforeActionList`数组，用于为某个方法指定前置操作：

```php
public $beforeActionList = [
	'方法名', // 所有方法都会预先执行该方法
	'方法名'=>['except'=>'action1,action2,...'], // 数组内的action不预先执行该方法
    '方法名'=>['only'=>['action1,action2,...']] // 只有数组内的action预先执行该方法
]；
```

## §4.3 控制器嵌套

我们到目前为止所用的控制器全都定义于`application/模块名/controller/控制器类名.php`。事实上，为了便于模块化开发，我们也可以在`application/模块名/controller`目录下新建文件夹，在文件夹内编写其它控制器类：

```php
/* 创建application/index/controller/user/Wallet.php */
namespace app\index\controller\user;
class Wallet{
    public function index(){
        return "用户钱包首页";
    }
}
```

```shell
$ curl localhost:8080/index/user/wallet/index
	用户钱包首页
```

## §4.4 Request

### §4.4.1 获取输入数据

ThinkPHP 5对PHP的原始输入进行了包装：

| `Request`实例方法                            | 作用                                      |
| -------------------------------------------- | ----------------------------------------- |
| `param($name='',$default=null,$filter='')`   | 返回当前请求类型的参数、PATHINFO、`$_GET` |
| `get($name='',$default=null,$filter='')`     | 返回`$_GET`                               |
| `post($name='',$default=null,$filter='')`    | 返回`$_POST`                              |
| `put($name='',$default=null,$filter='')`     | 返回PUT请求方法的数据                     |
| `delete($name='',$default=null,$filter='')`  | 返回DELETE请求方法的数据                  |
| `session($name='',$default=null,$filter='')` | 返回`$_SESSION`                           |
| `cookie($name='',$default=null,$filter='')`  | 返回`$_COOKIE`                            |
| `request($name='',$default=null,$filter='')` | 返回`$_REQUEST`                           |
| `server($name='',$default=null,$filter='')`  | 返回`$_SERVER`                            |
| `env($name='',$default=null,$filter='')`     | 返回`$_ENV`                               |
| `route($name='',$default=null,$filter='')`   | 返回路由数据                              |
| `file($name='')`                             | 返回`$_FILES[$name]`                      |
| `header($name='',$default=null)`             | 返回Header数据                            |

```php
$request = Request::instance();
$username = $request->param('username');	// 筛选名为username的参数
$allParam = $request->param();				// 获取经过过滤的所有参数
$allParam = $request->param(false);			// 获取未经过滤的所有参数
// $request->param()有以上三种用法，其它方法同理
```

### §4.4.2 过滤数据

```php
Request::instance()->get(
	'username',
    '',
    'htmlspecialchars,strip_tags'
);
Request::instance()->only(
	['username','password']
); // 一次筛选多个数据
Request::instance()->except(
	['username','password']
); // 一次排除多个数据
```

###  §4.4.3 数据类型转换

我们知道，原生PHP使用强制类型转换（`(int)`/`(string)`/`(array)`/......）或类型转换函数（`intval()`/`floatval()`/`strval()`）进行数据类型之间的转换。为了简化这一过程，ThinkPHP框架提供了数据类型修饰符：

```php
Request::instance()->param('username/s');	// 字符串 
Request::instance()->param('age/d');		// 整型
Request::instance()->param('gender/b');		// 布尔型
Request::instance()->param('price/f');		// 浮点型
Request::instance()->param('list/a');		// 数组
```

## §4.5 页面缓存

在实际场景中，高并发的网站为降低服务器压力，通常使用页面缓存：

```php
/* 编辑application/route.php */
'tryYourLuck/:id' => ['index/index/index',['cache'=>5]]
```

```php
/* 编辑application/index/controller/index.php */
......
class Index {
    public function index(){
        return "您的随机数是".rand(0,10);
    }
}
```

```shell
$ curl localhost:8080/index/index/ (重复三次)
	您的随机数是3
	您的随机数是9
	您的随机数是7
$ curl localhost:8008/tryYourLuck (5秒内重复三次)
	您的随机数是1
	您的随机数是1
	您的随机数是1
$ curl localhost:8080/tryYourLuck (5秒后再试一次)
	您的随机数是10
```

# §5 数据库操作层

MVC的模型层可以再细分，其中DAO（Data Access Object）层用于进行底层数据库的操作，并不涉及业务逻辑。ThinkPHP框架实现了这一层，并且提供数据库的配置文件：

```php
/* 查看application/database.php */
return [
    // 数据库类型
    'type'           => 'mysql',
    // 服务器地址
    'hostname'       => '127.0.0.1',
    // 数据库名
    'database'       => '',
    // 用户名
    'username'       => 'root',
    // 密码
    'password'       => '',
    // 端口
    'hostport'       => '',
    // 连接dsn
    'dsn'            => '',
    // 数据库连接参数
    'params'         => [],
    // 数据库编码默认采用utf8
    'charset'        => 'utf8',
    // 数据库表前缀
    'prefix'         => '',
    // 数据库调试模式
    'debug'          => true,
    // 数据库部署方式:0 集中式(单一服务器),1 分布式(主从服务器)
    'deploy'         => 0,
    // 数据库读写是否分离 主从式有效
    'rw_separate'    => false,
    // 读写分离后 主服务器数量
    'master_num'     => 1,
    // 指定从服务器序号
    'slave_no'       => '',
    // 是否严格检查字段是否存在
    'fields_strict'  => true,
    // 数据集返回类型 array 数组 collection Collection对象
    'resultset_type' => 'array',
    // 是否自动写入时间戳字段
    'auto_timestamp' => false,
    // 是否需要进行SQL性能分析
    'sql_explain'    => false,
];
```

ThinkPHP允许模型类使用`$connection`来连接`database.php`定义之外的数据库：

```php
class User extends Model {
    protected $connection = 'user'; // 自动读取user连接定义来连接数据库
}
```

## §5.1 SQL语句的CURD

数据库的基本操作离不开CURD（Create/Update/Read/Delete），ThinkPHP 5定义了`Db`类用于实现增删查改：

```php
$受影响行 = Db::execute( // 增
    'INSERT INTO user (username,password) VALUES (?,?)',
	['admin',md5('123456')]    
);
$受影响行 = Db::execute( // 改
	'UPDATE user SET password=? WHERE username=?',
    [md5('123456'),'admin']
);
$受影响行 = Db::execute( // 删
	'DELETE FROM user WHERE username=?',
    ['admin']
);
$查询结果 = Db::query(
	'SELECT * FROM user WHERE username=?',
    ['admin']
);
```

如果要使用`database.php`定义的默认数据库之外的数据库，可以使用`Db::config()`方法：

```php
Db::config($connection)->query(
	'SELECT * FROM user WHERE username=?',
    ['admin']
);
```

## §5.2 查询构造器的CURD

实际项目中很少使用`Db::execute()`直接执行手写的SQL语句。ThinkPHP将CURD的SQL语句封装成了查询构造器，并且使用了设计模式中的建造者模式，因此支持链式调用：

- 添

  ```php
  // 插入单行
  Db::table('user')->insert(
          ['username'=>'admin', 'password'=>md5('123456')]
      );
  
  // 插入多行
  Db::table('user')->insertAll(
      [
          ['username'=>'admin', 'password'=>md5('123456')],
          ['username'=>'user1', 'password'=>md5('abcdef')],
      ]
  );
  ```

- 改：

  ```php
  // 更新数据
  Db::table('user')->where('username','admin')->update(
      ['password'=>md5('123456')]
  );
  
  // 更新数据（特用于更新的数据中包含主键的情形）
  Db::table('user')->update(
      ['id'=>1,'password'=>md5('123456')]
  );
  
  // 更新数据（特用于只更新某一行的某一个字段的情形）
  Db::table('user')->where('username','admin')->setField(
      'password',
      md5('123456')
  );
  
  // 让整型字段自增
  Db::table('user')->where('username','admin')->setInc(
      'visit',1
  );
  
  // 让整型字段自减
  Db::table('user')->where('username','admin')->setInc(
      'money',1
  );
  ```

- 查

  ```php
  // 查询单行数据
  Db::table('user')->where('username','admin')->find();
  
  // 查询多行数据
  Db::table('user')->where('gender',1)->select();
  
  // 查询单行数据的某个字段值
  Db::table('user')->where('username','admin')->value('age');
  
  // 查询多行数据的某个字段值集合
  Db::table('user')->where('gender',1)->column('username');
  
  // 批量查询（适用于服务器内存有限的情景，通过循环来降低资源占用）
  Db::table('user')->where('gender',1)->chunk(
      100,
      function ($users){print_r($users);},
      'username'
  );
  ```

  MySQL自5.7版本开始支持JSON类型，可以像MongoDB一样存储非结构化数据。ThinkPHP 5也提供了对应的支持：

  ```php
  // admin为JSON类型的字段，在其名称后使用$符号
  Db::table('user')->where('info$.email','admin@example.com')->find();
  ```

- 删

  ```php
  // 依据主键删除
  Db::table('user')->delete([1,2,3]);
  
  // 删除
  Db::table('user')->where('username','admin')->delete();
  ```

对于`WHERE`子句，ThinkPHP适配SQL语句中的所有逻辑运算符：

|      SQL逻辑运算符      |     ThinkPHP逻辑运算符      |            作用            |             代码实例（省略`Db::table('...')->`）             |
| :---------------------: | :-------------------------: | :------------------------: | :----------------------------------------------------------: |
|           `=`           |             `=`             |            等于            | `where('username','=','admin')`/<br />`where('username','admin')` |
|          `<>`           |            `<>`             |           不等于           |                     `where('id','<>',9)`                     |
|           `>`           |             `>`             |            大于            |                     `where('id','>',9)`                      |
|          `>=`           |            `>=`             |          大于等于          |                     `where('id','>=',9)`                     |
|           `<`           |             `<`             |            小于            |                     `where('id','<',9)`                      |
|          `<=`           |            `<=`             |          小于等于          |                     `where('id','<=',9)`                     |
| `between`/`not between` |   `between`/`not between`   |          区间查询          |              `where('age','between',][18,24])`               |
|      `in`/`not in`      |        `in`/`not in`        |        **列表查询**        |                 `where('age','in',[6,7,8])`                  |
|    `null`/`not null`    |   `is null`/`is not null`   |      **是否为`null**`      |                     `where('列名',null)`                     |
|  `exists`/`not exists`  | `is exists`/`is not exists` |        **是否存在**        |                                                              |
|         `like`          |           `like`            |          模糊查询          |               `where('name','like','%Smith%')`               |
|          `exp`          |                             | 表达式查询（ThinkPHP独有） |          `where('name','exp','between 18 and 24')`           |
|                         |            `and`            |           逻辑与           |             `where(...)->where(...)->where(...)`             |

## §5.3 连贯操作



| 方法名                 | 作用                       | 方法名            | 作用                             |
| ---------------------- | -------------------------- | ----------------- | -------------------------------- |
| `table()`              | 指定表名                   | `relation()`      | 关联查询（可多次调用）           |
| `alias()`              | 为当前表定义别名           | `page()`          | 分页查询（ThinkPHP独有）         |
| `filed()`              | 查询指定字段（可多次调用） | `lock()`          | 数据库锁                         |
| `order()`/`orderRaw()` | 查询结果排序（可多次调用） | `cache()`         | 缓存查询（ThinkPHP语法）         |
| `limit()`              | 限制查询结果行数           | `with()`          | 关联查询预处理（可多次调用）     |
| `group()`              | 分组查询                   | `bind()`          | 数据绑定（配合占位符使用）       |
| `having()`             | 筛选结果集                 | `strict()`        | 是否严格检测字段名是否存在       |
| `join()`               | 关联查询（可多次调用）     | `master()`        | 读写分离环境下从主服务器读取数据 |
| `union()`              | 联合查询（可多次调用）     | `failException()` | 未查询到数据时是否抛出异常       |
| `view()`               | 视图查询                   | `partition()`     | 数据库分表查询（ThinkPHP独有）   |
| `distinct()`           | 过滤重复数据               |                   |                                  |

### §5.3.1 `table()`

```php
// SELECT * FROM `user` LIMIT 1;
Db::table('user')->find();

// SELECT * FROM `think_user` LIMIT 1; (使用表前缀，假设为think_)
Db::table('__USER__')->find();

// SELECT * FROM `think`.`user` LIMIT 1; (指定数据库名)
Db::table('think.user')->find();
```

### §5.3.2 `alias()`

```php
// SELECT * FROM `think_user` `user` INNER JOIN `think_post` `post` ON `post`.`user_id`=`user`.`user.id`;
Db::table('__USER__')->alias(['think_user'=>'user','think_post'=>'post'])
    ->join(['think_user'=>'user'],'post.user_id=user.user_id')
    ->select();
```

### §5.3.3 `field()`

```php
// SELECT `username`,`password` FROM `user` LIMIT 1;
Db::table('user')->field(['username','password'])->find();

// SELECT `username` as `ShownName` FROM `user` LIMIT 1;
Db::table('user')->field(['username'=>'ShownName'])->find();

// SELECT SUM(`amount`) AS `amount` FROM `user` LIMIT 1;
Db::table('user')->field(['SUM(amount)'=>'amount'])->find();

// SELECT `article_id`,`title`,`desc` FROM `article` LIMIT 1; (常用于排除TEXT大字段)
Db::table('user')->field('content',true)->find();

// 安全写入
Db::table('user')->field(['email','phone'])->insert(
    ['email'=>'test@example.com','phone'=>'123-456789']
);
```

### §5.3.4 `order()`

```php
// SELECT * FROM `user` ORDER BY `age` DESC, `user_id` DESC;
Db::table('user')->order(
    ['age'=>'desc','user_id'=>'desc']
)->select();

// SELECT * FROM `user` ORDER BY RAND();
Db::table('user')->order('RAND()')->select();
```

### §5.3.5 `limit()`

```php
// SELECT * FROM `user` LIMIT 10;
Db::table('user')->limit(10)->select();

// SELECT * FROM `user` LIMIT 100,10; (指定起始行)
Db::table('user')->limit(10)->select();

// DELETE FROM `user` WHERE `gender`=1 LIMIT 1;
Db::table('user')->where('gender',1)->limit(1)->delete();
```

### §5.3.6 `group()`

```php
// SELECT `user_id`,SUM(`score`) AS `score` FROM `exam` GROUP BY `user_id`;
Db::table('exam')->field(
    ['user_id','SUM(score)'=>'score']
)->group('user_id')->select();
```

### §5.3.7 `having()`

```php
// SELECT `user_id`,SUM(`score`) AS `score`
Db::table('exam')->field(
    ['user_id','SUM(score)'=>'score']
)->group('user_id')->having('score>=60')->select();
```

### §5.3.8 `join()`

```php
// SELECT * FROM `think_user`INNER JOIN `think post` ON `think_post`.`user_id`=`think_user`.`user_id`;
Db::table('think_user')->join(
    ['think post','think post.user id=think user.user id']
)->select();

// SELECT * FROM `think user` `user` INNER JOIN `think article` `article` ON `article`.`user_id`=`user`.`user_id` INNER JOIN `think_comment` `comment` ON `comment`.`user_id`=`user`.`user_id`;
Db::table('think user')->alias('user')->join(
    [
        ['think article article','article.user id=user.user id'],
        ['think_comment comment','comment.user id=user.user id']
    ]
)->select();
```

### §5.3.9 `union()`

```php
// SELECT `name` FROM `user` UNION SELECT `name` FROM `user1` UNION SELECT `name` FROM `user2`;
Db::table('user')->field(['name'])->union([
	'SELECT name FROM user1','SELECT name FROM user2'
])->select();

// SELECT `name` FROM `user` UNION SELECT `name` FROM `user1` UNION SELECT `name` FROM `user2`;
Db::table('user')->field(['name'])
    ->union(function($query){$query->table('user1')->filed(['name']);})
    ->union(function($query){$query->table('user2')->filed(['nane']);})
    ->select();

// SELECT `name` FROM `user` UNION ALL SELECT `name` FROM `user1`;
Db::table('user')->field(['name'])->union(
    ['SELECT name FROM user1',true]
)->select();
```

### §5.3.10 `distinct()`

```php
// SELECT DISTINCT `username` FROM `user`;
Db::table('user')->distinct(true)->field(['username'])->select();
```

### §5.3.11 `page()`

`page()`是ThinkPHP框架独有的一个方法，用于简化`limit()`方法的计算：

```php
// SELECT * FROM `user` LIMIT 0,10
Db::table('user')->page(1,10)->select();
```

### §5.3.12 `lock()`

```php
// SELECT * FROM `user` WHERE `user_id`=1 FOR UPDATE;
Db::table('user')->where('user_id',1)->lock(true)->find();

// SELECT * FROM `user` WHERE `user_id`=1 LOCK IN SHARE MODE;
Db::table('user')->where('user_id',1)->lock('lock in share mode')->find();
```

### §5.3.13 `cache()`

```php
Db::table('user')->cache(60)->find();

// 指定缓存Key
Db::table('user')->cache('tmp_user',60)->find();
Cache::get('tmp_user');

// 清除缓存
Db::table('user')->update(['user_id'=>1,'name'=>'demo']);

// 根据Key清除缓存
Db::table('user')->cache('tmp_user')->where('user_id',1)->update(['name'=>'demo']);
```

## §5.4 查询事件

ThinkPHP 5新增对SQL查询事件的支持，可以在执行数据库操作前后添加监听器。其声明为`Query::event(string $event,callable $callable)`，其中监听器`$event`的种类包含`before_select`、`before_find`、`after_insert`、`after_update`、`after_delete`。

```php
Query::event('after_delete',function($options){
    return "删除成功！";
});
```

## §5.5 SQL调试

```php
Db::listen(function($sql,$time,$explain,$isMaster){
    // ......
})
```

## §5.6 事务

```php
Db::transaction(function(){
    Db::table('user')->insert($data1);
    Db::table('user')->insert($data2);
});
```

# §6 模型层

模型层是对DAO层的进一步包装，基于对象之间的关系映射来操作数据库。

一个模型的定义如下所示：

```php
/* 创建application/index/model/User.php */
<?php
namespace app\index\model;
use think\Model;

class User extends Model {
    protected $pk = 'id'; // Primary Key名称
    protected $table = 'users'; // 表名称
    // protected $connection = 'db1'; //
}
```

## §6.1 CURD

- 增

  ```php
  $user = new User();
  
  // 对象方式
  $user->username = 'admin';
  $user->password = md5('123456');
  $user->save();
  
  // 数组方式
  $user->data([
      'username'=>'admin'
      'password'=>md5('123456')
  ]);
  $user->save();
  ```

- 改

  ```php
  // 查询条件方式
  $user = new User();
  $user->save(
  	['password'=>md5('123456')],
      ['username'=>'admin']
  );
  
  // 对象方式
  $user = User::get(['username'=>'admin']);
  $user->password = md5('123456');
  $user->save();
  
  // 根据主键批量更新
  $user = new User();
  $user->saveAll([
      ['id'=>1,'password'=>md5('123456')],
      ['id'=>1,'password'=>md5('654321')]
  ]);
  ```

- 删

  ```php
  // 对象方式
  $user = User::get(['username'=>'admin']);
  $user->delete();
  
  // 主键方式
  User::destory(1);
  User::destory([2,3,4]);
  
  // 根据条件删除
  User::where('id',1)->delete();
  ```

- 查

  ```php
  // 根据主键查询
  $user = User::get(1);
  
  // 根据主键批量查询
  $users = User::get([1,2.3]);
  
  // 指定字段查询
  $user = User::get(['username'=>'demo']);
  
  // 指定字段批量查询
  $users = User::get(['gender'=>1]);
  
  // where子句查询
  $user = User::where('id',1)->find();
  
  // where子句批量查询
  $users = User::where('gender',1);
      ->page(1,10)
      ->select();
  
  // 闭包查询
  $user = User::get(
  	function($query){$query->where('id',1);}
  );
  
  // 指定字段查询(通过PHP魔术方法自动识别字段)
  $user = User::getByUsername('admin');
  ```

## §6.2 `get()`/`set()`

在[§6.1 CURD](#§6.1 CURD)的`User`类中，我们只在数据库中定义了`username`和`password`字段，但是没有在`User`类中定义。为什么我们可以直接调用`$user->username`，并且可以得到正确的值且不报错呢？这是因为ThinkPHP框架重写了`Model`类的魔术方法`__get()`/`__set()`

```php
abstract class Model implements \JsonSerializable, \ArrayAccess{
	......
    public function __get($name){
        return $this->getAttr($name);
    }
    public function getAttr($name){
        try {
            $notFound = false;
            $value    = $this->getData($name);
        } catch (InvalidArgumentException $e) {
            $notFound = true;
            $value    = null;
        }

        // 检测属性获取器
        $method = 'get' . Loader::parseName($name, 1) . 'Attr';
        if (method_exists($this, $method)) {
            $value = $this->$method($value, $this->data);
        } elseif (isset($this->type[$name])) {
            // 类型转换
            $value = $this->readTransform($value, $this->type[$name]);
        } elseif (in_array($name, [$this->createTime, $this->updateTime])) {
            if (is_string($this->autoWriteTimestamp) && in_array(strtolower($this->autoWriteTimestamp), [
                'datetime',
                'date',
                'timestamp',
            ])
            ) {
                $value = $this->formatDateTime(strtotime($value), $this->dateFormat);
            } else {
                $value = $this->formatDateTime($value, $this->dateFormat);
            }
        } elseif ($notFound) {
            $relation = Loader::parseName($name, 1, false);
            if (method_exists($this, $relation)) {
                $modelRelation = $this->$relation();
                // 不存在该字段 获取关联数据
                $value = $this->getRelationData($modelRelation);
                // 保存关联对象值
                $this->relation[$name] = $value;
            } else {
                throw new InvalidArgumentException('property not exists:' . $this->class . '->' . $name);
            }
        }
        return $value;
    }
    ......
}
```

## §6.3 时间戳

ThinkPHP支持自动向数据库写入时间戳（默认字段名为`create_time`/`update_time`），可以通过以下两种方式

- 更改配置文件`application/database.php`

  ```php
  'auto_timestamp'=>true; // 取值范围true|'datetime'|'timestamp'
  ```

- 通过模型类定义

  ```php
  class ... extends Model {
      protected $autoWriteTimeStamp = true;
      // protected $createTime = '自定义字段名';
      // protected $updateTime = '自定义字段名';
  }
  ```

## §6.4 软删除

我们知道，有时我们在数据库中删除数据，并不是真的使用`DELETE`语句，而是标志一个删除位。

```php
class User extends Model {
    use SoftDelete;
    protected $deleteTime = '自定义字段名';
    
    // 配置后默认为软删除
    User::destory([1,2,3]);
    
    // 硬删除
    $user = User::get(1);
    $user->delete();
}
```

ThinkPHP在查询时默认不包含软删除的数据，如要需要，则应使用`Model::withTrashed()`方法：

```php
User::withTrashed()->select();
User::withTrashed()->find();
```

只查询软删除数据应使用`Model::onlyTrashed()`方法：

```php
User::onlyTrashed()->select();
User::onlyTrashed()->select();
```

## §6.5 自动完成

ThinkPHP框架支持调用`Model::save()`自动更新某些字段的值：

```php
class User extends Model {
    protected $auto = [];
    protected $insert = ['created_ip','created_ua'];
    protected $update = ['login_ip','login_at'];
    protected function setCreatedIpAttr(){ // 插入时自动填充create_ip字段
        return request()->ip();
    }
    protected function setCreatedUaAttr(){ // 插入时自动填充create_ua字段
        return request()->header('user-agent');
    }
    protected function setLoginIpAttr(){ // 更新时自动填充login_ip字段
        return request()->ip();
    }
    protected function setLoginAtAttr(){ // 更新时自动填充login_at字段
        return time();
    }
}
```

## §6.6 数据类型字段转换

我们知道PHP是一门弱类型语言，而Server通过Database收到的数据全都是字符串，需要开发者手动完成类型转换。ThinkPHP框架支持的数据库数据类型如下所示：

| ThinkPHP数据类型 | 作用                                                         |
| ---------------- | ------------------------------------------------------------ |
| `integer`        | 读写时转换为整型                                             |
| `float`          | 读写时转换为浮点型                                           |
| `boolean`        | 读写时转换为布尔型                                           |
| `array`          | 写入时转换为JSON，读取时转换为array                          |
| `object`         | 写入时转换为JSON，读取时转换为stdClass                       |
| `serialize`      | 写入时序列化转换为字符串，读取时反序列化转换为前类型         |
| `json`           | 写入时调用`json_encode()`转为字符串，读取时调用`json_decode()`转换为前类型 |
| `timestamp`      | 写入时调用`strtotime()`，读取时调用`date()`，默认格式为`Y-m-d H:i:s`，受`$dateFormat`控制 |

```php
class User extends Model {
    protected $type = [
        'status'=>'integer',
        'balance'=>'float',
        'data'=>'json'
    ];
}

$user = new User;
$user->status = '1';
$user->balance = '123.456';
$user->data = ['username'=>'Alice'];
$user->save();
var_dump($user->status,$user->balance,$user->data);
	// int(1) float(123.456) array(size=1) 'username'=>'Alice'
```

## §6.7 快捷查询

ThinkPHP框架提供了`scopeXXX`的魔术方法：

```php
class User extends Model {
    protected function scopeMale($query){
        $query->where('gender',1);
    }
}

$user = User::scope('male')->select();
```

## §6.8 全局查询条件

在实际项目中，我们有时频繁地只希望查询符合某个条件的记录，例如只查询删除位为`false`的所有记录。如果每次使用`where()`都必须带上排除删除位的语句就太麻烦了。ThinkPHP提供了`base()`方法，我们可以重载该方法实现全局内的查询条件：

```php
class User extends Model {
    protected function base($query){
        $query->where('deleted',false);
    }
}

User::useGolbalScope(true)->where('username','admin')->select(); // 开启全局查询条件
User::useGolbalScope(false)->where('username','admin')->select(); // 关闭全局查询条件
```

## §6.9 模型事件

我们已经在[§5.4 查询事件](#§5.4 查询事件)一节中得知如何为数据库操作绑定监听事件，那么如何为`Model`操作绑定鉴定事件呢？ThinkPHP在`Model`类中提供了静态方法`init()`用于注册以下监听事件，通过返回的布尔值控制后续代码是否执行：

| 监听事件方法名   | 作用   | 监听事件方法名   | 作用   | 监听事件方法名  | 作用   | 监听事件方法名   | 作用   |
| ---------------- | ------ | ---------------- | ------ | --------------- | ------ | ---------------- | ------ |
| `beforeInsert()` | 插入前 | `beforeUpdate()` | 更新前 | `beforeWrite()` | 写入前 | `beforeDelete()` | 删除前 |
| `afterInsert()`  | 插入后 | `afterUpdate()`  | 更新后 | `afterWrite()`  | 写入后 | `afterDelete()`  | 删除后 |

```php
class User extends Model {
    protected function init(){
        User::beforeInsert(
            function($user){
                return $user->age > 0;
            }
        );
    }
}
```

## §6.10 关联模型

### §6.10.1 一对一关联

```php
class Wallet extends Model {
    
}
class User extends Model {
    protected function wallet(){
        return $this->hasOne('Wallet','wallet_id','wallet_id');
    }
}

$user = User::get(1);
echo $user->wallet->balance;
$user->wallet->save()
```

？？？？？？？？？？？TODO：



# §7 视图与模版

ThinkPHP框架规定，如果一个类继承了`Controller`类，则可以直接通过`echo`/`return`输出视图；如果没有继承，则可以通过`view('模版文件','模版数据'，'模板替换数据')`输出内容。



## §7.1 绑定视图

`Controller->fetch()`方法负责为控制器类的某个方法绑定模版：

```php
<?php
namespace app\index\controller;
use think\Controller;
class Index extends Controller {
    public function index(){
        return $this->fetch();
    }
}
```

其中模版路径默认为`当前模块/view/当前控制器类名小写/当前方法名小写.html`：

```html
/* 新建application/indes/view/index/index.html */
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
    </head>
    <body>
        <p>Hello World</p>
    </body>
</html>
```

访问路径即可看到模版：

```shell
$ curl localhost:8080/index/index
	Hello World
```

如果需要绑定指定的模版，可以给`Controller->fetch()`传递相应的参数：

| 作用                             | `Controller->fetch()`的`$template`参数 | 举例                                                         |
| -------------------------------- | -------------------------------------- | ------------------------------------------------------------ |
| 绑定当前模块默认路径下的其他模版 | `fetch('文件主名')`                    | `fetch('home')`绑定`application/模块名/view/控制器类名/文件主名开头的html文件` |
| 绑定当前模块其他路径下的其他模版 | `fetch('目录/文件主名')`（支持`../`）  | `fetch('public/home')`绑定`application/模块名/view/public/home.html` |
| 绑定其它模块其他路径下的其他模版 | `fetch('其它模块名@目录/主名')`        | `fetch('forum/public/home')`绑定`application/forum/view/public/home.html` |
| 绑定`view_path`目录下的模版      | `fetch('/目录/主名')`                  | `view_path`缺省时为`application/模块名/view`                 |

> 注意：如果当前控制器类没有继承`Controller`类，也可以使用助手函数`view()`实现上述效果，参数及其含义完全相同。
>
> ```php
> return $this->fetch() // 继承Controller时
> return view(...); // 助手函数
> ```

## §7.2 视图赋值

当控制器类继承`Controller`类时，我们可以使用`Controller->assign()`方法向视图进行赋值。

向模版传参的赋值的方法有：

1. 传入一个键值对

   ```php
   $this->assign('键名','值');
   ```

2. 传入多个键值对（一个数组）

   ```php
   $this->assign(
       [
           '键名1'=>'值1',
           '键名2'=>'值2',
       ]
   );
   ```

3. 直接传入`fetch()`方法的`$vars`形参

   ```php
   $this->fetch('index',
       [
           '键名1'=>'值1',
           '键名2'=>'值2',
       ]  
   );
   ```

4. 直接使用`display()`方法，绕过模版直接输出

   ```php
   $content = '{$name}'
   return $this->display($content,['name'=>'Alice']);
   ```

5. 使用助手函数`view()`的`$vars`形参

   ```php
   return view('index',
       [
           '键名1'=>'值1',
           '键名2'=>'值2',
       ]
   );
   
   return view('index')->assign(
       [
           '键名1'=>'值1',
           '键名2'=>'值2',
       ]
   );
   ```

6. 使用`View::share()`进行全局赋值

   ```php
   \think\facade\View::share('键名','值');
   \think\facade\View::share(
       [
           '键名1'=>'值1',
           '键名2'=>'值2',
       ]
   );
   ```

下面是一个简单的例子：

```php
class Index extends Controller {
    public function index(){
        $this->assign('name','Alice');
        $this->assign([
            'chinese'=>150,
            'math'=>150,
            'english'=>150
        ]);
        return $this->fetch('index',[
            'classRank'=>2,'schoolRank'=>30,'provinceRank'=>3480
        ]);
    }
}
```

```html
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Score List</title>
    </head>
    <body>
        <h1>{$name|default='Null'}'s Score List</h1>
        <ul>
            <li>Chinese: {$chinese}</li>
            <li>Math: {$math}</li>
            <li>English: {$english}</li>
        </ul>
        <ul>
            <li>Class Rank: {$classRank}</li>
            <li>School Rank: {$schoolRank}</li>
            <li>Province Rank: {$provinceRank}</li>
        </ul>
    </body>
</html>
```

这里使用的`{$...}`是由`application/config.php`中的`template`数组中的`tpl_begin`与`tpl_end`决定的。

ThinkPHP会在访问时，将HTML中的变量占位符`{$...}`替换成PHP语句，并把新生成的PHP文件放在`runtime/temp`目录中：

```php+HTML
/* 查看 */
<?php 
	if (!defined('THINK_PATH')) 
        exit(); 
	/*
		a:1:{
			s:101:"C:\WWW\public/../application/index\view\index\index.html";
			i:1658219700;
		}
	*/ 
?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Score List</title>
    </head>
    <body>
        <h1><?php echo $name; ?>'s Score List</h1>
        <ul>
            <li>Chinese: <?php echo $chinese; ?></li>
            <li>Math: <?php echo $math; ?></li>
            <li>English: <?php echo $english; ?></li>
        </ul>
        <ul>
            <li>Class Rank: <?php echo $classRank; ?></li>
            <li>School Rank: <?php echo $schoolRank; ?></li>
            <li>Province Rank: <?php echo $provinceRank; ?></li>
        </ul>
    </body>
</html>
```

### §7.2.1 模版内置变量

ThinkPHP模版不仅支持获取原生PHP中的超全局变量、常量等变量，也支持获取ThinkPHP框架本身配置文件的数据：

| PHP原生变量               | ThinkPHP框架模版的调用方法 |
| ------------------------- | -------------------------- |
| `$_SERVER`                | `{$Think.server.键名}`     |
| `$_ENV`                   | `{$Think.env.键名}`        |
| `$_POST`                  | `{$Think.post.键名}`       |
| `$_GET`                   | `{$Think.get.键名}`        |
| `$_COOKIE`                | `{$Think.cookie.键名}`     |
| `$_SESSION`               | `{$Think.session.键名}`    |
| `$_REQUEST`               | `{$Think.request.键名}`    |
| 常量                      | `{$Think.const.常量名}`    |
| ThinkPHP框架模版配置      | `{$Think.config.template}` |
| ThinkPHP框架多语言配置    | `{$Think.lange.error}`     |
| ThinkPHP框架`Reuqest`对象 | `{$Request.get.键名}`      |

### §7.2.2 默认值

在之前的例子中，如果我们没有给模版中的某个参数传值，那么ThinkPHP就会抛出`think\exception\ErrorException`。为避免这一情况，我们可以为其指定一个默认值：

```html
{$signature|default='该用户未填写个性签名'}
```

### §7.2.3 调用函数

在视图中使用`|`表示将左边的结果作为右边函数的第一个参数。如果要强制指定参数的其它位置，可以使用`###`占位符：

```html
{$user.password|md5}
	// 编译为<?php echo md5($user['password']) ?>
{$user.name|substr=0,4}
	// 编译为<?php echo substr($user['name'],0,20) ?>
{$user.registerTime|date='y-m-d h:m:s',###}
	// 编译为<?php echo date('y-m-d h:m:s',$user['registerTime'])
```

以此类推，我们可以嵌套多个函数：

```html
{$user.password|md5|substr=0,16|default="密码不能为空！"}
```

### §7.2.4 运算符

```
// 算术运算符
{$user->score+10}
{$user->score++}
{$user->score*2}
{pow($user->score,0.5)}

// 三目运算符
{$isVIP?'续费VIP':'成为VIP'}
{$nam??'Null'}
```

### §7.2.5 不解析输出

受制于其它模版引擎的特性，任何`{$...}`都可能会被明文输出。之前我们已经知道了如何让其不输出，如果我们就想让它明文输出的话，每次都指定默认值`{$...|default=...}`太麻烦了，我们可以使用`{literal}`标签：

```html
{literal}
	Hello, {$name}! // 每次都输出'{$name}'字符串
{/literal}
```

## §7.3 视图过滤

视图过滤可以在页面显示之前对页面内容进行更改：

```php
class User extends Controller {
    public function initialize(){
        $this->filter(function($content){
    		return str_replace('Alice','You\'re hacked!');
		});
    }
    public function index(){
        //  ......
        return $this->fetch(...);
    }
}

// 助手函数
return view()->filter(function($content){
    // ......
});
```

## §7.4 布局文件

实际项目中，许多页面的头部都是导航栏，底部都是版权说明。为了提高代码复用率，ThinkPHP 5提供了布局功能。

- 全局配置

  ```php
  /* 查看application/config.php */
  return [
  	// ......
      'template' => [
          'layout_on' => true,
          'layout_name' => 'layout_file'
      ],
      // ......
  ];
  ```

  ????????TODO：？？？？？？？？？







模版引擎配置在`application/config.php`的`template`键中：

```php
/* 查看application/confg.php */
return [
    ......
    'template'               => [
        // 模板引擎类型 支持 php think 支持扩展
        'type'         => 'Think',
        // 模板路径
        'view_path'    => '',
        // 模板后缀
        'view_suffix'  => 'html',
        // 模板文件名分隔符
        'view_depr'    => DS,
        // 模板引擎普通标签开始标记
        'tpl_begin'    => '{',
        // 模板引擎普通标签结束标记
        'tpl_end'      => '}',
        // 标签库标签开始标记
        'taglib_begin' => '{',
        // 标签库标签结束标记
        'taglib_end'   => '}',
    ],
    ......
]
```

????????TODO：？？？？？？？？？



# §8 验证器

ThinkPHP 5使用`\think\Validate`类对数据进行验证。在这之前，验证逻辑大多集成在控制器类中，而验证器的出现有利于项目的解耦。

1. 验证器的代码模版可以通过在终端中执行`php think make:validate 模型类名`，自动在`applicaiton/validate`目录下创建`模型类名.php`：

   ```php
   <?php
   namespace app\index\validate;
   use think\Validate;
   
   class User extends Validate {
       protected $rule = [];
       protected $message = [];
   }
   ```

2. 或者现场`new`一个验证器实例：

   ```php
   $validator = new Validate(
   	$rule, // 数组
       $message, // 信息
   );
   ```

3. 或者使用`Controller`的`validate()`方法：

   ```php
   $result = $this->validate(
   	$rule, // 数组
       $message, // 信息
   );
   $result = $this->validate(XXXValidator::class)->save($data);
   ```

4. 或者使用`Model`的`validate()`方法：

   ```php
   $model = new User();
   $result = $model->validate(XXXValidator::class)->save($data);
   if($result !== true){
       throw new Exception($result);
   }
   ```

5. 甚至直接使用验证器类的静态方法进行便捷验证：

   ```php
   if(!Validate::length('username',1,127)){
       thrown ew Exception('......');
   }
   ```

`Validate->$rule`数组表示规则，`Validate->$message`数组表示报错提示信息：

```php
// ......
class User extends Validate {
    protected $rule = [
    	'name' => 'require|max:128',
        'age' => 'number|between:0,127'
        'email' =? 'email'
    ];
    protected $message = [
    	'name.require' => '姓名不能为空！',
        'name.max' => '姓名长度不得大于128位！',
        'age.number' => '年龄必须为数字！',
        'age.between' => '年龄必须在0-127之间！',
        'email' => '邮箱格式错误！'
    ];
}
```

创建测试类：

```php
class Index extends Controller {
    
    public $data = [
        'name'=>'Alice',
        'age'=>20,
        'email'=>'test@example.com'
    ];
    
    // 手动实例化验证器类
    public function verifyUser(){
        $validate = new \app\index\validate\User();
        if(!$validate->check($this->data)){
            dump($validate->getError());
        }
    }
    
    // 使用自Controller类继承的validate()方法
    public function verityUser(){
    	$result = $this->validate($this->data,\app\index\validate\User::class);
        if($result !== true{
        	dump($result);
        }
    }
}
```

默认情况下，`Validate`类会顺序逐次验证数据是否符合要求，一旦发现不符之处就马上终止验证过程，不会验证后续数据。为了让`Validate`类把所有数据都验证一遍，找出所有错误，我们可以手动给`Controller`的`$batchValidate`字段设为`true`：

```php
class User extends Controller {
	protected $batchValidate = true;
    // ......
}
```

默认情况下，`Validate`类发现不符之处就马上终止验证过程，返回错误信息。如果我们想让其直接抛出异常`ValidateException`，而不是返回错误信息的字符串或数组，可以手动给`Controller`的`$failException`字段设为`true`：

```php
class User extends Controller {
	protected $faliException = true;
    // ......
}
```

除了使用预置规则外，我们也可以自定义新规则：

```php
class User extends Controller {
	protected function checkName($value,$rule,$data,$field,$title){
    	return $value != $rule ? true : '请填写真实姓名！'
    }
}
```

```html
'name'=>'require|checkName:无名氏'
```

ThinkPHP框架内置了众多常用的规则：

| ThinkPHP内置验证器  | 含义                                   | 举例                                                        |
| ------------------- | -------------------------------------- | ----------------------------------------------------------- |
| `require`           | 必填项                                 | `'username'=>'require'`                                     |
| `integer`           | 整数                                   | `'age'=>'integer'`                                          |
| `float`             | 浮点数                                 | `'percent'=>'float'`                                        |
| `boolean`           | 布尔值                                 | `'isAdmin'=>'boolean'`                                      |
| `email`             | 邮箱                                   | `'email'=>'email'`                                          |
| `array`             | 数组                                   | `'list'=>'array'`                                           |
| `date`              | 日期                                   | `'registerDate'=>'date'`                                    |
| `alpha`             | 纯字母                                 | `'username'=>'alpha'`                                       |
| `alphaNum`          | 字母+数字                              | `'username'=>'alphaNum'`                                    |
| `alphaDash`         | 字母+数字+下划线+中划线                | `'username'=>'alphaDash'`                                   |
| `chs`               | 纯中文                                 | `'username'=>'chs'`                                         |
| `chsAlpha`          | 中文+字母                              | `'username'=>'chsAlpha'`                                    |
| `chsAlphaNum`       | 中文+字母+数字                         | `'username'=>'chsAlphaNum'`                                 |
| `chsDash`           | 中文+字母+数字+下划线+中划线           | `'username'=>'chsDash'`                                     |
| `activeUrl`         | 主机名（包含域名和IP）                 | `'hostname'=>'activeUrl'`                                   |
| `url`               | 链接                                   | `'homepage'=>'url'`                                         |
| `ip`                | IPv4/IPv6地址                          | `'loginIP'=>'ip'`                                           |
| `dateFormat:format` | 指定格式日期                           | `'loginTime'=>'dateFormat:y-m-d'`                           |
| `in`                | 在列表中                               | `'gender'=>'in:0,1'`                                        |
| `notIn`             | 不在列表中                             | `'gender'=>'notIn:0,1'`                                     |
| `between`           | 在范围内                               | `'age'=>'between:20,60'`                                    |
| `notbetween`        | 不在范围内                             | `'age'=>'nowBetween:20,60'`                                 |
| `length:min,max`    | 字符串长度、数组元素数、文件大小的范围 | `'telephone'=>'length:11'`<br />`'username'=>'length:3,12'` |

# §9 缓存

ThinkPHP框架使用`\think\Cache`类实现缓存，缓存的配置文件在`application/config.php`的`cache`数组：

```php
/* 查看application/config.php */
return [
    // ......
	'cache'                  => [
        // 驱动方式
        'type'   => 'File',
        // 缓存保存目录
        'path'   => CACHE_PATH,
        // 缓存前缀
        'prefix' => '',
        // 缓存有效期 0表示永久缓存
        'expire' => 0,
    ],
    // ......
];
```

目前ThinkPHP框架缓存支持的驱动方式`type`包括`File`、`Memecache`、`wincache`、`sqlite`、`redis`、`xcache`。

```php
Cache::set('key','value',3600); // 存入缓存一个小时
$value = Cache::get('key'); // 获取缓存
Cache::rm('key'); // 删除缓存

Cache::inc('number',1); // 自增1
Cache::dec('number',2); // 自减2

$value = Cache::pull('number'); // 获取缓存后删除缓存
Cache::clear(); // 清空缓存
Cache::remember('key',function(){ // 如果存在就返回，富国不存在就写入缓存之后缓存
	return 'data';
},3600);
```

# §10 Session和Cookie

ThinkPHP 5将原生的Session和Cookie分别包装成`\think\Session`和`\think\Cookie`类，便于切换底层驱动。

Session指的是会话信息，位于服务器中，负责与客户端的交互，当客户端中断连接时Session失效。Cookie位于客户端中，用于维护客户端的信息，在用户主动删除前Cookie一直有效。

Session和Cookie的配置在`application/config.php`中：

```php
return [
    // ......
    'session'                => [
        'id'             => '',
        // SESSION_ID的提交变量,解决flash上传跨域
        'var_session_id' => '',
        // SESSION 前缀
        'prefix'         => 'think',
        // 驱动方式 支持redis memcache memcached
        'type'           => '',
        // 是否自动开启 SESSION
        'auto_start'     => true,
    ],
    'cookie'                 => [
        // cookie 名称前缀
        'prefix'    => '',
        // cookie 保存时间
        'expire'    => 0,
        // cookie 保存路径
        'path'      => '/',
        // cookie 有效域名
        'domain'    => '',
        //  cookie 启用安全传输
        'secure'    => false,
        // httponly设置
        'httponly'  => '',
        // 是否使用 setcookie
        'setcookie' => true,
    ],
    // ......
];
```

## §10.1 数据存取

```php
Session::set('key','value'); // 写入默认scope
Session::has('key'); // 判断是否写入默认scope
Session::get('name'); // 从默认scope中读取
Session::delete('key'); // 删除默认scope中的值
Session::pull('key'); // 返回默认scope的值并删除
Session::clear(); // 清空默认scope中的所有值

Session::set('key','value','user'); // 写入user scope
Session::has('key','user'); // 判断是否写入user scope
Session::get('name','user'); // 从user scope中读取
Session::delete('key','user'); // 删除user scope中的值
Session::pull('key','value'); // 范湖user scope的值并删除
Session::clear('user'); // 删除user scope中的所有值

Cookie::set('key','value',3600); // 设置Cookie有效期为一小时
Cookie::set('key','value', // 设置Cookie前缀和有效期
	[
        'prefix'=>'forum_',
        'expire'=>'3600'
    ]
);
Cookie::get('name'); // 获取名为name的Cookie值
Cookie::get('name','demo_'); //获取名为demo_name的Cookie值
Cookie::has('name'); // 判断名为name的Cookie是否存在
Cookie::has('name','demo_'); // 判断名为demo_name的Cookie是否存在
Cookie::delete('name','demo_'); // 删除名为demo_name的Cookie
Cookie::clear('demo_'); // 删除所有以demo_为前缀的Cookie
```

# §11 命令行应用

对于一些对算力要求比较高的业务逻辑，指望PHP在用户提交请求后的几秒内就能返回预期界面是不现实的。这部分业务逻辑必须常驻内存持续运行。

先在`application/command.php`配置文件中注册命令行应用：

```php
/* 编辑application/command.php */
return [
    'app\index\command\HelloWorld' // 新加的一行
];
```

然后新建命令行应用类：

```php
/* 新建application/index/command/HelloWorld.php */
<?php
namespace app\index\command;

use think\console\Input;
use think\console\Output;

class HelloWorld extends \think\console\Command{
    protected function configure(){
        $this->setName('hello_world')
            ->setDescription('This is a Hello World Command');
    }
    protected function execute(Input $input, Output $output){
        $output->writeln('Hello World');
    }
}
```

在终端中执行该命令行应用：

```html
$ php ./think hello_world
    Hello World
```

PHP脚本可以直接调用命令行应用：

```php
class Index extends Controller {
	public function index(){
    	$output = Console::call('hello_world');
	
        return $this->fetch(......);
    }
}
```

