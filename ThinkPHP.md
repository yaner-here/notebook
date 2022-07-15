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

TODO：？？？？？？？？？？？？？

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
| `file($name='')`                             | 返回`$_GET`                               |
| `header($name='',$default=null)`             | 返回`$_GET`                               |

