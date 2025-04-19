参考文献：

- [深入浅出Spring Boot 3.x](https://www.epubit.com/bookDetails?id=UBda9eaf729796)

# 

```java
package com.learn.demo.main;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller // Spring MVC控制器
@SpringBootApplication // Spring Boot自动装配
public class DemoServer {
	@RequestMapping("/test")
	@ResponseBody
	public String test() {
		return "Hello, world!";
	}
	
	public static void main(String[] args) throws Exception {
		SpringApplication.run(DemoServer.class, args);
	}
}
```

```shell
$ /home/yaner/.jdks/corretto-18.0.2/bin/java
	-javaagent:/home/yaner/下载/ideaIC-2024.3.5/idea-IC-243.26053.27/lib/idea_rt.jar=36601
	-Dfile.encoding=UTF-8
	-Dsun.stdout.encoding=UTF-8
    -Dsun.stderr.encoding=UTF-8
    -classpath <TARGET_CLASS_PATH>  
        :<M2_PATH>/<PACKAGE_PATH>/spring-boot-starter-web.jar  
        :<M2_PATH>/<PACKAGE_PATH>/spring-boot-starter.jar  
        :<M2_PATH>/<PACKAGE_PATH>/spring-boot.jar  
        :<M2_PATH>/<PACKAGE_PATH>/spring-boot-autoconfigure.jar  
        :<M2_PATH>/<PACKAGE_PATH>/spring-boot-starter-logging.jar
        :<M2_PATH>/<PACKAGE_PATH>/logback-classic.jar
        :<M2_PATH>/<PACKAGE_PATH>/logback-core.jar
        :<M2_PATH>/<PACKAGE_PATH>/log4j-to-slf4j.jar
        :<M2_PATH>/<PACKAGE_PATH>/log4j-api.jar
        :<M2_PATH>/<PACKAGE_PATH>/jul-to-slf4j.jar
        :<M2_PATH>/<PACKAGE_PATH>/jakarta.annotation-api.jar
        :<M2_PATH>/<PACKAGE_PATH>/snakeyaml.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-boot-starter-json.jar
        :<M2_PATH>/<PACKAGE_PATH>/jackson-databind.jar
        :<M2_PATH>/<PACKAGE_PATH>/jackson-annotations.jar
        :<M2_PATH>/<PACKAGE_PATH>/jackson-core.jar
        :<M2_PATH>/<PACKAGE_PATH>/jackson-datatype-jdk.jar
        :<M2_PATH>/<PACKAGE_PATH>/jackson-datatype-jsr.jar
        :<M2_PATH>/<PACKAGE_PATH>/jackson-module-parameter-names.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-boot-starter-tomcat.jar
        :<M2_PATH>/<PACKAGE_PATH>/tomcat-embed-core.jar
        :<M2_PATH>/<PACKAGE_PATH>/tomcat-embed-el.jar
        :<M2_PATH>/<PACKAGE_PATH>/tomcat-embed-websocket.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-web.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-beans.jar
        :<M2_PATH>/<PACKAGE_PATH>/micrometer-observation.jar
        :<M2_PATH>/<PACKAGE_PATH>/micrometer-commons.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-webmvc.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-aop.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-context.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-expression.jar
        :<M2_PATH>/<PACKAGE_PATH>/slf4j-api.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-core.jar
        :<M2_PATH>/<PACKAGE_PATH>/spring-jcl.jar
  .   ____          _            __ _ _  
 /\\ / ___'_ __ _ _(_)_ __  __ _ \ \ \ \  
( ( )\___ | '_ | '_| | '_ \/ _` | \ \ \ \  
 \\/  ___)| |_)| | | | | || (_| |  ) ) ) )  
  '  |____| .__|_| |_|_| |_\__, | / / / /  
 =========|_|==============|___/=/_/_/_/  
 :: Spring Boot ::       (v3.0.0-SNAPSHOT)  
  
<TIME> <PID> [           main] com.learn.demo.main                      : Starting DemoServer using Java 18.0.2 with PID <PID> (<TARGET_CLASS_PATH> started by yaner in <PATH>)  
<TIME> <PID> [           main] com.learn.demo.main                      : No active profile set, falling back to 1 default profile: "default"  
<TIME> <PID> [           main] o.s.b.w.embedded.tomcat.TomcatWebServer  : Tomcat initialized with port(s): 8080 (http)  
<TIME> <PID> [           main] o.apache.catalina.core.StandardService   : Starting service [Tomcat]  
<TIME> <PID> [           main] o.apache.catalina.core.StandardEngine    : Starting Servlet engine: [Apache Tomcat/10.1.1]  
<TIME> <PID> [           main] o.a.c.c.C.[Tomcat].[localhost].[/]       : Initializing Spring embedded WebApplicationContext  
<TIME> <PID> [           main] w.s.c.ServletWebServerApplicationContext : Root WebApplicationContext: initialization completed in 485 ms  
<TIME> <PID> [           main] o.s.b.w.embedded.tomcat.TomcatWebServer  : Tomcat started on port(s): 8080 (http) with context path ''  
<TIME> <PID> [           main] com.learn.demo.main                      : Started Chapter1Main in 0.919 seconds (process running for 1.037)  
<TIME> <PID> [nio-8080-exec-1] o.a.c.c.C.[Tomcat].[localhost].[/]       : Initializing Spring DispatcherServlet 'dispatcherServlet'  
<TIME> <PID> [nio-8080-exec-1] o.s.web.servlet.DispatcherServlet        : Initializing Servlet 'dispatcherServlet'  
<TIME> <PID> [nio-8080-exec-1] o.s.web.servlet.DispatcherServlet        : Completed initialization in 0 ms
```