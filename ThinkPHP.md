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

1. 框架配置：框架自带的默认配置
2. 全局配置：`application/config.php`
3. 扩展配置：`application/extra/*`
4. 场景配置：`app_status`常量
5. 模块配置：`application/模块名/config.php`
6. 动态配置：自定义`Config`类





