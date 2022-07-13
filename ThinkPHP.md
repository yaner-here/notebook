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

5. 模块配置：`application/模块名/config.php`

6. 动态配置：自定义`Config`类



