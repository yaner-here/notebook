参考文献：

- [《深入浅出Spring Boot 3.x》](https://www.epubit.com/bookDetails?id=UBda9eaf729796)

# §1 Spring

我们先写一个简单的`Hello, world`程序。使用Spring官方提供的模版生成器[Spring initializer](https://yaclt.cn/sysm.jpg)，我们可以得到以下模版工程：

- `/.gitattributes`：Git的仓库级别配置。
- `/.gitignore`：Git忽略文件列表。
- `/mvnw`：针对Linux平台的Maven Wrapper脚本，用于下载Maven可执行文件。
- `/mvnw.cmd`：针对Windows Powershell平台的Maven Wrapper脚本，用于下载Maven可执行文件。
- `/pom.xml`：Maven项目对象模型（Project Object Model）文件。记录该工程的元数据、使用的依赖项、构建插件、构建配置。
- `/.mvn/wrapper/maven-wrapper.properties`：Maven Wrapper配置文件。记录该工程使用的Maven版本与下载源。
- `/src/main/java/<PACKAGE_PATH>`：存放Java源文件。
- `/src/test/java/<PACKAGE>PATH>`：存放Java测试文件。

创建文件`/src/main/java/top/yaner_here/javasite/JavasiteApplication.java`：

```java
package top.yaner_here.javasite;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class JavasiteApplication {
	public static void main(String[] args) {
		SpringApplication.run(JavasiteApplication.class);
	}

	@GetMapping("/hello")
	public String hello(@RequestParam(value = "name", defaultValue = "user") String name) {
		return String.format("Hello, %s", name);
	}
}
```

运行该程序，访问`8080`端口：

```shell
$ curl.exe http://127.0.0.1:8080/hello?name=yaner
	Hello, yaner
```

## §1.1 IoC

控制反转（Inversion of Control，IoC）是Spring中的两个基本概念之一。

控制反转指的是一种容器装配组件的模式。它将本该在组件内部管理的变量，交给容器统一管理，由容器将组件依赖的变量注入到组件中。下面展示了控制反转的优势——我们无需手动新建`Speaker`实例，交给`org.springframework.beans.factory.BeanFactory`即可。

```java
import org.springframework.beans.factory.BeanFactory;  
import org.springframework.beans.factory.support.DefaultListableBeanFactory;

class Speaker {  
    public void hello(String name) {  
        System.out.printf("[%s]: Hello!%n", name);  
    }  
}  
  
class AppWithoutIoC {  
    public void hello() {  
        Speaker speaker = new Speaker();  
        speaker.hello("yaner");  
    }  
}  
  
class AppWithIoC {  
    private BeanFactory beanFactory;  
    public AppWithIoC() {  
	    beanFactory = new DefaultListableBeanFactory();  
	    XmlBeanDefinitionReader reader = new XmlBeanDefinitionReader(beanFactory);  
	    reader.loadBeanDefinitions("beans.xml");  
    }  
    public void hello() {  
	    Speaker speaker = beanFactory.getBean("speaker", Speaker.class);  
        speaker.hello("yaner");  
    }  
}
```

```xml
// beans.xml
<?xml version="1.0" encoding="UTF-8"?>
<beans
	xmlns="http://www.springframework.org/schema/beans"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:schemaLocation="http://www.springframework.org/schema/beans https://www.springframework.org/schema/beans/spring-beans.xsd">
	<bean id="speaker" class="top.yaner_here.javasite.Speaker" />
</beans>
```

这里我们使用的`org.springframework.beans.factory.BeanFactory`只是一个基类而已。Spring在此基础上提供了功能更丰富的继承类，自带事件传播、资源加载、i18n等企业场景所需的高级功能。

```mermaid
graph LR
	BeanFactory["BeanFactory"] --"继承链..."--> 
		ApplicationContext["ApplicationContext<br>"] --"继承链..."--> 
		ClassPathXmlApplicationContext["ClassPathXmlApplicationContext<br>从CLASSPATH加载XML获得配置"] & FileSystemXmlApplicationContext["FileSystemXmlApplicationContext<br>从文件系统加载XML获得配置"] & AnnotationConfigApplicationContext["AnnotationConfigApplicationContext<br>从注解/Java类获得配置"]
```

容器之间也是可以继承的，在初始化容器时传入父容器实例即可。它们的继承规则类似于Java类机制——子容器可以看见父容器，父容器看不见子容器，子容器的值同名值可以覆盖父容器。

```xml
<!-- /src/main/resources/parent-beans.xml -->
<?xml version="1.0" encoding="UTF-8"?>
<beans
    xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://www.springframework.org/schema/beans https://www.springframework.org/schema/beans/spring-beans.xsd">
    <bean id="parentInfo" class="top.yaner_here.javasite.Speaker">
        <property name="name" value="parent" />
    </bean>
    <bean id="info" class="top.yaner_here.javasite.Speaker">
        <property name="name" value="parent" />
    </bean>
</beans>
```

```xml
<!-- /src/main/resources/child-beans.xml -->
<?xml version="1.0" encoding="UTF-8"?>  
<beans  
    xmlns="http://www.springframework.org/schema/beans"  
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"  
    xsi:schemaLocation="http://www.springframework.org/schema/beans https://www.springframework.org/schema/beans/spring-beans.xsd">  
    <bean id="childInfo" class="top.yaner_here.javasite.Speaker">  
        <property name="name" value="child" />  
    </bean>    <bean id="info" class="top.yaner_here.javasite.Speaker">  
        <property name="name" value="child" />  
    </bean></beans>
```

```java
// /src/main/java/top/yaner_here/javasite/Application.java
package top.yaner_here.javasite;

import org.springframework.context.support.ClassPathXmlApplicationContext;

class Speaker {
    private String name;
    public void setName(String name) { this.name = name; }
    public String hello() {
        return String.format("[%s]: Hello!", this.name);
    }
}

public class Application {
    private ClassPathXmlApplicationContext parentContext;
    private ClassPathXmlApplicationContext childContext;
    public Application() {
        parentContext = new ClassPathXmlApplicationContext("./parent-beans.xml");
        parentContext.setId("ParentContext");
        childContext = new ClassPathXmlApplicationContext(new String[]{"./child-beans.xml"}, true, parentContext);
        childContext.setId("ChildContext");
    }
    public static void main(String[] args) {
        Application app = new Application();
        System.out.println(app.parentContext.getId() + " see " + "parentInfo" + ": " + app.parentContext.containsBean("parentInfo"));
        System.out.println(app.parentContext.getId() + " see " + "childInfo" + ": " + app.parentContext.containsBean("childInfo"));
        System.out.println(app.childContext.getId() + " see " + "parentInfo" + ": " + app.childContext.containsBean("parentInfo"));
        System.out.println(app.childContext.getId() + " see " + "childInfo" + ": " + app.childContext.containsBean("childInfo"));
        System.out.println(app.parentContext.getId() + " value [info.speak()]: " + app.parentContext.getBean("info", Speaker.class).hello());
        System.out.println(app.childContext.getId() + " value [info.speak()]: " + app.childContext.getBean("info", Speaker.class).hello());
    }
    // ParentContext see parentInfo: true
	// ParentContext see childInfo: false
	// ChildContext see parentInfo: true
	// ChildContext see childInfo: true
	// ParentContext value [info.speak()]: [parent]: Hello!
	// ChildContext value [info.speak()]: [child]: Hello!
}
```

## §1.2 配置容器与Bean

Bean特指Java中一种特殊的类，它同时满足这些条件——可序列化和持久化、提供无参构造器、提供Getter和Setter方法以访问实例字段的**可重用组件**。按照这一定义，Spring也将可重用的容器称为Bean，使用Beans的配置元数据来管理容器之间的依赖关系。

### §1.2.1 XML配置

前文提到，Spring可以读取XML文件中的`<beans>`标签来配置Bean。具体来说，一个`<bean>`标签用于配制一个Bean

在XML中，`<beans>`内的`<constructor-arg>`标签用于控制Bean构造方法传入的内容。在下面的例子中，我们在`Application`类内使用容器获得一个`Speaker`实例，并且XML文件已经配置了创建`Speaker`实例时传入的构造函数实参。

```xml
<!-- /src/main/java/resources/beans.xml -->
<?xml version="1.0" encoding="UTF-8"?>
<beans
    xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://www.springframework.org/schema/beans https://www.springframework.org/schema/beans/spring-beans.xsd">
    <bean id="speaker" class="top.yaner_here.javasite.Speaker">
        <constructor-arg value="yaner"/>
    </bean>
</beans>
```

```java
// /src/main/java/top/yaner_here/javasite/Application.java
package top.yaner_here.javasite;

import org.springframework.context.support.ClassPathXmlApplicationContext;

class Speaker {
    private final String name;
    public Speaker(String name) { this.name = name; }
    public String hello() { return String.format("[%s]: Hello!", this.name); }
}

public class Application {
    private ClassPathXmlApplicationContext context;
    public Application() { context = new ClassPathXmlApplicationContext("beans.xml"); }
    public void run() { System.out.println(context.getBean("speaker", Speaker.class).hello()); }
    public static void main(String[] args){
        Application app = new Application();
        app.run(); // [yaner]: Hello!
    }
}
```

`<bean>`支持以下属性字段：

- `id`：Bean的标识符
- `class`：Bean的类名
- `factory-method`：指定使用Bean类的某个静态方法来获取Bean实例，而非默认的构造方法
- `scope`：Bean实例的作用域，可以选`singleton`（在整个容器中只存在一个此Bean实例，缺省值）、`prototype`（每次请求或引用时都创建一个Bean实例）、`request`（每次请求时都创建一个Bean实例）、`session`（每个HTTP Session都创建一个Bean实例）、`application`（每个服务器进程均创建一个Bean实例）。
- `lazy-init`：控制Bean实例初始化的时机。若为`true`则在第一次被`getBean()`请求或被其它Bean依赖时创建，若为`false`则在Spring启动时立即创建。
- `depends-on`：强制在当前Bean初始化之前，先创建该列表中举出的所有Bean。


`<constructor-arg>`支持以下属性字段。下面的代码展示了各项的含义。

| 属性字段    | 含义                |
| ------- | ----------------- |
| `value` | 传给Bean构造方法的实参值    |
| `ref`   | 传给Bean构造方法的BeanID |
| `type`  | 传给Bean构造方法的实参数据类型 |
| `index` | 传给Bean构造方法的形参位置w  |
| `name`  | 传给Bean构造方法的形参名称   |

```xml
<!-- beans.xml -->
<?xml version="1.0" encoding="UTF-8"?>  
<beans  
    xmlns="http://www.springframework.org/schema/beans"  
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"  
    xsi:schemaLocation="http://www.springframework.org/schema/beans https://www.springframework.org/schema/beans/spring-beans.xsd">  
    <bean id="container1" class="top.yaner_here.javasite.Container"> <!-- 使用value对默认形参位置作为实参 -->  
        <constructor-arg value="container1"/>  
        <constructor-arg value="123"/>  
    </bean>    <bean id="container2" class="top.yaner_here.javasite.Container"> <!-- 使用ref引用其它Bean作为实参 -->  
        <constructor-arg value="item2"/>  
        <constructor-arg ref="container1"/>  
        <constructor-arg value="123"/>  
    </bean>    <bean id="container3" class="top.yaner_here.javasite.Container"> <!-- 使用index指定形参位置作为实参 -->  
        <constructor-arg index="1" value="123"/>  
        <constructor-arg index="0" value="container3"/>  
    </bean>    <bean id="container4" class="top.yaner_here.javasite.Container"> <!-- 使用type指定传入实参的数据类型 -->  
        <constructor-arg index="0" type="java.lang.String" value="container4"/>  
        <constructor-arg index="1" type="java.lang.Object" value="123"/>  
    </bean></beans>
```

```java
package top.yaner_here.javasite;
import org.springframework.context.support.ClassPathXmlApplicationContext;
class Container {
    private String name;
    private Object item;
    private int size;
    public Container(String name, int size) {
        this.name = name;
        this.item = null;
        this.size = size;
    }
    public Container(String name, Object item) {
        this.name = name;
        this.item = item;
        this.size = 1;
    }
    public Container(String name, Object item, int size) {
        this.name = name;
        this.item = item;
        this.size = size;
    }
    @Override
    public String toString() {
        return String.format("Container info: [name]=%s, [item]=%s, [size]=%d", this.name, this.item, this.size);
    }
    public static void main(String[] args) {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
        Container container1 = context.getBean("container1", Container.class); System.out.println(container1);
        Container container2 = context.getBean("container2", Container.class); System.out.println(container2);
        Container container3 = context.getBean("container3", Container.class); System.out.println(container3);
        Container container4 = context.getBean("container4", Container.class); System.out.println(container4);
	// Container info: [name]=container1, [item]=123, [size]=1
	// Container info: [name]=item2, [item]=Container info: [name]=container1, [item]=123, [size]=1, [size]=123
	// Container info: [name]=container3, [item]=123, [size]=1
	// Container info: [name]=container4, [item]=123, [size]=1
    }
}
```

### §1.2.2 注解配置

Spring支持通过注解来简化Bean配置。

| 注解（基类）        | Java路径                                                   | 作用                         |
| ------------- | -------------------------------------------------------- | -------------------------- |
| `@Component`  | `org.springframework.stereotype.Component`               | 将类注册为Bean                  |
| `@Service`    | `org.springframework.stereotype.Service`                 | 将类注册为服务                    |
| `@Repository` | `org.springframework.stereotype.Repository`              | 将类注册为DAO                   |
| `@Controller` | `org.springframework.stereotype.Controller`              | 将类注册为控制器                   |
| `@Autowired`  | `org.springframework.beans.factory.annotation.Autowired` | 为构造方法、Setter、成员变量，根据类型注入依赖 |

下面的例子展示了如何使用注解配置Bean。

1. 分别定义两个独立无关的Bean——`BeanA`与`BeanB`，使用`@Component`注解将这两个类注册为Bean，它们的BeanID分别为`beanA`与`beanB`。
2. 定义`BeanC`类，同样使用`@Component`注册为Bean，其BeanID为`beanC`，并且定义两个实例变量时，使用了`@Autowired`声明要通过Spring注入变量，使用`@Qualifier`声明注入变量的类型。
3. 定义`AppConfig`类，使用`@Configuration`声明其为Spring配置类，从而取代XML。使用`@ComponentScan`指定要从哪些类中扫描注解信息。除此以外，我们还使用`@Bean`定义了一个新的`Bean`——它的Java类型仍然是`BeanA`，但是BeanID为`manualBeanA`，并且使用Setter方法做了一些自定义。这使得我们不能直接使用`context.getBean(BeanA.class)`来实例化类，因为这个`BeanA.class`同时绑定了两个BeanID，使得Spring无法确定选择哪一个。

```java
package top.yaner_here.javasite;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.*;
import org.springframework.stereotype.Component;

@Component
class BeanA {
    private String name = "BeanA";
    public String getName() { return this.name; }
    public void setName(String name) { this.name = name; }
    public BeanA() { System.out.println("[BeanA] BeanA consturctor is called."); }
    public String info() { return String.format("[BeanA] info: name=%s", this.name); }
}

@Component
class BeanB {
    private String name = "BeanB";
    public String getName() { return this.name; }
    public void setName(String name) { this.name = name; }
    public BeanB() { System.out.println("[BeanB] consturctor is called."); }
    public String info() { return String.format("[BeanB] info: name=%s", this.name); }
}

@Component
class BeanC {
    @Autowired(required = false)
    @Qualifier("beanA")
    private BeanA beanA;

    @Autowired
    @Qualifier("beanB")
    private BeanB beanB;

    public BeanC() { System.out.println("[BeanC] consturctor is called."); }
    public void checkInjectedBeans() {
        if (beanA != null) {
            System.out.println("[BeanC] Injected BeanA: " + beanA.info());
        } else {
            System.out.println("[BeanC] BeanA was not injected.");
        }
        if (beanB != null) {
            System.out.println("[BeanC] Injected BeanB: " + beanB.info());
        } else {
            System.out.println("[BeanC] BeanB was not injected.");
        }
    }
}

@Configuration
@ComponentScan("top.yaner_here.javasite")
class AppConfig {
    public AppConfig() { System.out.println("[AppConfig] constructor is called."); }

    @Bean
    @Lazy
    @Scope("prototype")
    public BeanA manualBeanA() {
        System.out.println("[ManualBeanA] Creating BeanA instance...");
        BeanA beanA = new BeanA();
        beanA.setName("ManualBeanA");
        return beanA;
    }
}

class App {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(AppConfig.class);
        BeanC beanC = context.getBean(BeanC.class);
        beanC.checkInjectedBeans();

        BeanA beanA;
        // beanA = context.getBean(BeanA.class); System.out.println(beanA.info()); // No qualifying bean of type 'top.yaner_here.javasite.BeanA' available: expected single matching bean but found 2: beanA,manualBeanA
        beanA = context.getBean("beanA", BeanA.class); System.out.println(beanA.info());
        beanA = context.getBean("manualBeanA", BeanA.class); System.out.println(beanA.info());

        BeanB beanB;
        beanB = context.getBean("beanB", BeanB.class); System.out.println(beanB.info());
        beanB = context.getBean(BeanB.class); System.out.println(beanB.info());
        
        context.close();
    }
}
/* [AppConfig] constructor is called.
   [BeanA] BeanA consturctor is called.
   [BeanB] consturctor is called.
   [BeanC] consturctor is called.
   [BeanC] Injected BeanA: [BeanA] info: name=BeanA
   [BeanC] Injected BeanB: [BeanB] info: name=BeanB
   [BeanA] info: name=BeanA
   [ManualBeanA] Creating BeanA instance...
   [BeanA] BeanA consturctor is called.
   [BeanA] info: name=ManualBeanA
   [BeanB] info: name=BeanB
   [BeanB] info: name=BeanB */
```

### §1.2.3 Java类配置

前文说过，`@Bean`用于修饰某个方法，该方法的返回值是一个Bean实例。也就是说，`@Bean`的低位有点类似于Python中的修饰器——它不产生新的Class，只产生新的BeanID，它只是对原先的Class做了一点侵入式更改。

`@Bean`提供了以下属性：

| `@Bean`属性名          | 默认值                                   | 作用                                               |
| ------------------- | ------------------------------------- | ------------------------------------------------ |
| `name`              | 被注解的方法名                               | BeanID                                           |
| `value`             | 同上                                    | 同上                                               |
| `autowire`          | `Autowire.NO`                         | 自动注入方式                                           |
| `autowireCandidate` | `true`                                | 是否是自动注入的候选Bean                                   |
| `initMethod`        | `""`                                  | 初始化方法名                                           |
| `destoryMethod`     | `AbstractBeanDefinition.INFER_METHOD` | 销毁方法名，缺省为`public`的、无形参的、名为`close`或`shutdown`的方法。 |

Spring框架对`@Configuration`修饰的配置类中的`@Bean`一律认为是单例模式，即每个`@Bean`只能存在一个实例，即使多次调用`@Bean`修饰的方法，也只会返回同一个实例。

配置类也支持通过`@Import`注解继承自父配置，通过`@ImportResource`注解导入XML配置：

```java
@Configuration
@Import({ConfigA.class, ConfigB.class})
@ImportResource("classpath:/assets/*.xml")
public class Config { }
```

## §1.3 Bean生命周期

Spring容器负责管理Bean的整个生命周期。

```mermaid
graph LR
	subgraph Initialize["初始化阶段"]
		Create["创建对象<br>new Class()"] --> Inject["注入依赖"] --> InitializeCallback["创建后回调"]
	end
	Use["正常使用"]
	subgraph Destroy["销毁阶段"]
		DestroyCallback["销毁前回调"] --> Free["销毁对象"]
	end
	Initialize --> Use --> Destroy
```

Spring提供了以下四种方式指定创建后回调函数和销毁前回调函数：

- 实现`org.springframework.beans.factory.InitializingBean`和`org.springframework.beans.factory.DisposableBean`接口。
- 使用`jakarta.annotation.PostConstruct`和`jakarta.annotation.PreDestroy`提供的`@PostConstruct`和`@PreDestroy`注解指定方法。
- 在XML中使用`<bean class="..." init-method="<CLASS方法名>" destory-method="<CLASS方法名>"`，**需要在`<beans>`中添加`<context:annotation-config/>`开启支持**。
- 在Java类配置中使用`@Bean(initMethod="<CLASS>方法名", destoryMethod="<CLASS方法名>")`

这四种方式可以同时存在，Spring会按照以下顺序进行调用：

1. 由`@PostConstruct`或`@PreDestroy`修饰的方法
2. 重载了接口`Initializing`的`.afterPropertiesSet()`方法，或接口`DisposableBean`的`.destroy()`方法
3. 在XML或Java类配置的方法

Spring将生命周期抽象成了`org.springframework.context.LifeCycle`接口：

- `void .start()`：启动
- `void .stop()`：终止
- `boolean isRunning()`：是否正在运行

其中`.start()`/`.stop()`会在`ApplicationContext`实例调用`.start()`/`.stop()`方法时被调用：

```java
package top.yaner_here.javasite;

import org.springframework.context.Lifecycle;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

class Person implements Lifecycle {
    private boolean isAlive = false;
    public void printInfo() { System.out.println("[Person]: isAlive=" + isAlive); }
    @Override public void start() { this.isAlive = true; System.out.println("[Person]: Started."); }
    @Override public void stop() { this.isAlive = false; System.out.println("[Person]: Stopped."); }
    @Override public boolean isRunning() { return this.isAlive; }
}

@Configuration
class ApplicationConfig {
    @Bean
    public Person person() { return new Person(); }
}

public class Application {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(ApplicationConfig.class);

        Person person = context.getBean("person", Person.class);
        person.printInfo();

        context.start();
        person.printInfo();

        context.close();
        person.printInfo();
    }
}
/* [Person]: isAlive=false
   [Person]: Started.
   [Person]: isAlive=true
   [Person]: Stopped.
   [Person]: isAlive=false */
```

## §1.4 Bean感知容器

在工程中，我们设计的Bean业务逻辑应该是与Spring无耦合的。如果遇到特殊情况需要耦合，Spring提供了两种方式，让Bean能感知到容器的信息：

- 实现`org.springframework.beans.factory.BeanFactoryAware`接口或`org.springframework.context.ApplicationContextAware`接口。**该接口属于Bean生命周期中的注入依赖阶段，因此会在初始化回调函数前执行**。
- 用`@Autowired`注入外界的`BeanFactory`或`ApplicationContextAware`实例

这两种方式在本质上是一样的——都是在函数体内拿到了`BeanFactory`或`ApplicationContextAware`实例，在该实例上进行操作。

```java
package top.yaner_here.javasite;

import org.springframework.beans.BeansException;
import org.springframework.beans.factory.BeanFactory;
import org.springframework.beans.factory.BeanFactoryAware;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

class BeanA implements BeanFactoryAware {
    private BeanFactory beanFactory;
    @Override
    public void setBeanFactory(BeanFactory beanFactory) throws BeansException { this.beanFactory = beanFactory; }
    public void checkBeanB() { System.out.println("Does BeanB exist? " + beanFactory.containsBean("beanB")); }
}

class BeanB { }

@Configuration
class ApplicationConfig {
    @Bean
    public BeanA beanA() { return new BeanA(); }
    @Bean
    public BeanB beanB() { return new BeanB(); }
}

public class Application {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(ApplicationConfig.class);
        BeanA beanA = context.getBean("beanA", BeanA.class);
        beanA.checkBeanB(); // Does BeanB exist? true
    }
}
```

## §1.5 事件机制

`ApplicationContext`提供了一套事件机制，允许开发者通过`ApplicationEvent`通知所有实现了`ApplicationListener`接口的类。

下面的代码同时监听自定义事件和关闭事件。

- 对于自定义事件：
	1. 继承`ApplicationEvent`父类，创建了`MyEvent`类。在构造方法中接收了一个未知的`Object source`形参，这个`source`是由消息发布者指定的。我们直接把`source`传给父类的构造方法。
	2. 新建`MyEventPublisher`类。它实现了`ApplicationEventPublishAware`接口的`.setApplicationEventPublisher(ApplicationEventPublisher publisher)`方法，将Spring传入的`publisher`实例保存在类内变量中。同时公开一个发送自定义事件的API`.setMyEvent()`，它调用这个`publisher`的`.publishEvent()`方法，传入一个`Object source`表示事件内容来实例化`MyEvent`，将该实例传入`.publishEvent()`。
	3. 新建`MyEventListener`类。它自定义了一个由`@EventListener`修饰的回调函数，该函数接受一个`MyEvent`实例，并调用其父类的`.getSource()`拿到`Object source`事件内容。
	4. 在主函数中，我们通过Spring拿到了一个`MyEventPublisher`实例，调用它的`.sendMyEvent()`方法。这样会触发`MyEventListener`实例的回调函数，即使我们没有显式地创建`MyEventListener`实例。
- 对于其它的预定义事件（以关闭事件为例）：Spring提供了一系列预定义事件。例如`ApplicationContext`在启动、停止、关闭、刷新时分别发出`ContextStartedEvent`、`ContextStoppedEvent`、`ContextClosedEvent`、`ContextRefreshedEvent`事件，它们都导入自`org.framework.context.event.*`。**为了监听预定义事件，Spring提供了两种方法：为监听类实现`org.springframework.context.ApplicationListener<Event>`泛型事件接口，或为形参是`Event`的方法使用`org.springframework.context.event.EventListener`给出的`@EventListener`注解修饰**。
	1. 为监听类实现`ApplicationListener<Event>`泛型事件接口。创建自定义类`ContextClosedEventListener`，并且实现`ApplicationListener<ContextClosedEvent>`接口的`public void onApplicationEvent(ContextClosedEvent)`方法作为回调函数。
	2. 为形参是`Event`的方法使用`@EventListener`注解修饰。创建自定义类`ContextClosedEventAnnotationListener`，自定义其`.onEvent(ContextClosedEvent)`作为回调函数，并使用`@EventListener`注解修饰。
	3. `org.springframework.core.annotation.Order`提供的`@Order`注解可以规定同一事件的不同监听器的触发顺序。

```java
package top.yaner_here.javasite;

import org.springframework.context.ApplicationEvent;
import org.springframework.context.ApplicationEventPublisher;
import org.springframework.context.ApplicationEventPublisherAware;
import org.springframework.context.ApplicationListener;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.event.ContextClosedEvent;
import org.springframework.context.event.EventListener;
import org.springframework.core.annotation.Order;
import org.springframework.stereotype.Component;

@Component
@Order(1)
class ContextClosedEventListener implements ApplicationListener<ContextClosedEvent> {
    @Override
    public void onApplicationEvent(ContextClosedEvent event) { System.out.println("[@ApplicationListener(1)] Closed Event received."); }
}

@Component
class ContextClosedEventAnnotationListener {
    @EventListener
    @Order(2)
    public void onEvent(ContextClosedEvent event) { System.out.println("[@EventListener(2)] Closed Event received."); }
}

class MyEvent extends ApplicationEvent {
    public MyEvent(Object source) { super(source); }
}

@Component
class MyEventPublisher implements ApplicationEventPublisherAware {
    private ApplicationEventPublisher publisher;
    @Override
    public void setApplicationEventPublisher(ApplicationEventPublisher publisher) { this.publisher = publisher; System.out.println("[MyEventPublisher]: Got publisher."); }
    public void sendMyEvent() { publisher.publishEvent(new MyEvent("This is my event!")); }
}

@Component
class MyEventListener {
    @EventListener
    public void onEvent(MyEvent event) { System.out.println("[CustomEventListener]: Get MyEvent -> " + event.getSource()); }
}

@Configuration
@ComponentScan
public class Application {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(Application.class);

        MyEventPublisher publisher = context.getBean("myEventPublisher", MyEventPublisher.class);
        publisher.sendMyEvent();

        context.close();
    }
}
/* [MyEventPublisher]: Got publisher.
   [CustomEventListener]: Get MyEvent -> This is my event!
   [@ApplicationListener(1)] Closed Event received.
   [@EventListener(2)] Closed Event received. */
```

## §1.6 后处理

Spring允许开发者定制Bean，封装自己的框架或功能。具体来说，Spring提供了`org.springframework.beans.factory.config.BeanPostProcessor`接口，它包含两个方法：

- `postProcessBeforeInitialization(Object bean, String beanName)`：在Bean初始化前运行。
- `postProcessAfterInitialization(Object bean, String beanName)`：在Bean初始化后运行。

在下面的例子中：

1. 我们不使用`@Component`与`@ComponentScan`导入所有Bean，而是通过`@Bean`只定义了一个Bean——`Speaker`，使用`@PostConstruct`注解注册了一个后处理方法。
2. 定义`SpeakerPostProcessor`类，它实现了`BeanPostProcessor`接口的两个方法。

```java
package top.yaner_here.javasite;

import jakarta.annotation.PostConstruct;
import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanPostProcessor;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

class Speaker {
    @PostConstruct
    public void init() { System.out.println("[Speaker] @PostConstruct is called."); }
    public void hello() { System.out.println("[Speaker] hello() is called."); }
}

class SpeakerPostProcessor implements BeanPostProcessor {
    @Override
    public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException {
        System.out.println("[SpeakerPostProcessor] postProcessBeforeInitialization() is called with beanName=" + beanName);
        return bean;
    }
    @Override
    public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException {
        System.out.println("[SpeakerPostProcessor] postProcessAfterInitialization() is called with beanName=" + beanName);
        return bean;
    }
}

@Configuration
public class Application {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(Application.class);
        context.close();
    }
    @Bean
    public Speaker speaker() { return new Speaker(); }
    @Bean
    public SpeakerPostProcessor speakerPostProcessor() { return new SpeakerPostProcessor(); }
}

/* [SpeakerPostProcessor] postProcessBeforeInitialization() is called with beanName=speaker
   [Speaker] @PostConstruct is called.
   [SpeakerPostProcessor] postProcessAfterInitialization() is called with beanName=speaker */
```

同理，Spring也允许开发者定制Bean配置本身。具体来说，Spring提供了`org.springframework.beans.factory.config.BeanFactoryPostProcessor`接口，它包含了`postProcessBeanFactory(ConfigurableListableBeanFactory)`方法。在该方法内，开发者可以编辑`ConfigurableListableBeanFactory`中的配置信息。

```java
package top.yaner_here.javasite;

import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanDefinition;
import org.springframework.beans.factory.config.BeanFactoryPostProcessor;
import org.springframework.beans.factory.config.ConfigurableListableBeanFactory;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

class BeanA {
    private String name;
    public void setName(String name) { this.name = name; }
    public String getName() { return this.name; }
}

class MyBeanFactoryPostProcessor implements BeanFactoryPostProcessor {
    @Override
    public void postProcessBeanFactory(ConfigurableListableBeanFactory beanFactory) throws BeansException {
        System.out.println("[MyBeanFactoryPostProcessor] postProcessBeanFactory() is called.");
        if(beanFactory.containsBeanDefinition("beanA")) {
            BeanDefinition definition = beanFactory.getBeanDefinition("beanA");
            // 改变Scope
            definition.setScope(BeanDefinition.SCOPE_SINGLETON);
            // 改变Metadata
            definition.getPropertyValues().addPropertyValue("name", "Modified name by MyBeanFactoryPostProcessor");
        }
    }
}

@Configuration
class ApplicationConfig {
    @Bean
    public static MyBeanFactoryPostProcessor myBeanFactoryPostProcessor() { return new MyBeanFactoryPostProcessor(); }
    @Bean
    public BeanA beanA() { return new BeanA(); }
}

public class Application {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(ApplicationConfig.class);
        BeanA beanA = context.getBean("beanA", BeanA.class);
        System.out.println("[beanA] name=" + beanA.getName());
        context.close();
    }
}
```

## §1.7 Spring抽象层

### §1.7.1 Profile

虽然Java宣称自己是“Write Once, Run Anywhere”，但是受制于JVM和宿主机环境的各种差异，我们常常需要在多个配置之间切换。Spring提供了`org.springframework.core.env.Environment`接口表示对环境的抽象。这种对环境的抽象由`org.springframework.context.annotation.Profile`和`org.springframework.context.annotation.PropertySource`两部分描述。

我们先看`Profile`。在前文中，我们初始化`AnnotationConfigApplicationContext`实例的时候，总是给构造函数传入一个配置类的类对象。在本节中，我们先不传入实参，而是先初始化之后，为它的`environment`设置Profile名称，**然后再**注册若干个配置类，最后刷新上下文实例即可。这里的每个配置类都需要使用`@Profile()`注解指定Profile名称。

```java
package top.yaner_here.javasite;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Profile;
import org.springframework.core.env.ConfigurableEnvironment;

class Person {
    private String name;
    public String getName() { return this.name; }
    public void setName(String name) { this.name = name; }
    public void greet() { System.out.printf("[Person]: %s says hello!\n", this.name); }
}

@Configuration
@Profile("dev")
class ApplicationDevConfig {
    @Bean public Person person() { Person person = new Person(); person.setName("DevEnv"); return person; }
}

@Configuration
@Profile("test")
class ApplicationTestConfig {
    @Bean public Person person() { Person person = new Person(); person.setName("TestEnv"); return person; }
}

public class Application {
    public static void main(String[] args) {
        Person person;

        AnnotationConfigApplicationContext context1 = new AnnotationConfigApplicationContext();
        ConfigurableEnvironment environment1 = context1.getEnvironment();
        environment1.setActiveProfiles("dev");
        context1.register(ApplicationDevConfig.class, ApplicationTestConfig.class);
        context1.refresh();
        Person person1 = context1.getBean("person", Person.class);
        person1.greet();
        context1.close();

        AnnotationConfigApplicationContext context2 = new AnnotationConfigApplicationContext();
        ConfigurableEnvironment environment2 = context2.getEnvironment();
        environment2.setActiveProfiles("test");
        context2.register(ApplicationDevConfig.class, ApplicationTestConfig.class);
        context2.refresh();
        Person person2 = context2.getBean("person", Person.class);
        person2.greet();
        context2.close();
    }
}
```

除了在Java代码中切换Profile，Spring也支持在启动命令行时使用`-Dspring.profiles.active="..."`指定Profile。

Spring默认使用的Profile名称为`default`，可以使用`ConfigurableEnvironment.setDefaultProfiles()`或`-Dspring.profiles.default`修改。

### §1.7.2 PropertySource

在Spring的惯例中，属性通常由小数点分隔的小写单词构成，例如`foo.bar`。如果属性是从环境变量中获取，则Spring会依次检索`foo.bar`、`foo_bar`、`FOO.BAR`、`FOO_BAR`环境变量。

Spring的属性名可以使用`${属性名:默认值}`的占位符语法，表示属性名不存在时的默认值。为了获取属性值，Spring提供了两种方法：

- `org.springframework.core.env.Environment`类提供的`.getProperty(String)`方法，**不支持占位符语法**。
- 给实例变量添加`@Value(String)`注解修饰。**支持占位符**，默认值表示属性名不存在时的属性默认值。

Spring会频繁读取属性值，而属性值的来源多种多样，例如JNDI、`-D`命令行参数、操作系统环境变量等。PropertySource将属性来源抽象成一个统一的类。具体来说，对`@Configuration`增加`@PropertySource("classpath:...")`可以指定属性来源。

```inf
// /src/main/resources/application.properties
spring.application.name=javasite
```

```java
package top.yaner_here.javasite;  
  
import org.springframework.beans.factory.annotation.Value;  
import org.springframework.context.annotation.AnnotationConfigApplicationContext;  
import org.springframework.context.annotation.ComponentScan;  
import org.springframework.context.annotation.Configuration;  
import org.springframework.context.annotation.PropertySource;  
import org.springframework.core.env.Environment;  
import org.springframework.stereotype.Component;  
  
@Component  
class ApplicationInfo {  
    @Value("spring.application.name") public String appName;  
    @Value("${app.version:UnknownVersion}") public String version;  
}  
  
@Configuration  
@PropertySource("classpath:/application.properties")  
@ComponentScan  
class ApplicationConfig { }  
  
public class Application {  
    public static void main(String[] args) {  
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(ApplicationConfig.class);  
        ApplicationInfo info = context.getBean("applicationInfo", ApplicationInfo.class);  
  
        // 使用Environment.getProperty()方法获取属性值  
        Environment environment = context.getEnvironment();  
        System.out.println("spring.application.name: " + environment.getProperty("spring.application.name"));  
        System.out.println("version: " + environment.getProperty("${spring.application.name:UnknownVersion}"));  
  
        // 使用@Value注解获取属性值  
        System.out.println("spring.application.name: " + info.appName);  
        System.out.println("version: " + info.version);  
    }  
}
/* spring.application.name: javasite
   version: null
   spring.application.name: spring.application.name
   version: UnknownVersion */
```

Spring允许开发者自定义属性来源，只需要定义一个自己的`org.springframework.core.env.PropertySource`子类即可。在下面的例子中，我们将`Map<String, String>`自定义为一种新的属性来源：

1. 新建`MyMapPropertySource`类，继承自`org.springframework.core.envProperty<Map<String, String>>`子类。重载负载的`.getProperty()`和`.containsProperty()`方法，改成从`Map<String, String>`中查找键值对。
2. 新建自定义配置类`ApplicationConfig`，使用`@PostConstruct`注解修饰自定义`.addCustomPropertySource()`方法，对于`Environment.getPropertySources()`返回的`org.springframework.core.env.MutablePropertySources`实例调用它的`.addFirst()`方法，传入自定义的`MyMapPropertySource`实例。
3. 正常调用`Context.getEnvironment()`返回的实例，即可获取键值对。

```java
package top.yaner_here.javasite;  
  
import jakarta.annotation.PostConstruct;  
import org.springframework.beans.factory.annotation.Autowired;  
import org.springframework.context.annotation.AnnotationConfigApplicationContext;  
import org.springframework.context.annotation.ComponentScan;  
import org.springframework.context.annotation.Configuration;  
import org.springframework.core.env.ConfigurableEnvironment;  
import org.springframework.core.env.Environment;  
import org.springframework.core.env.MutablePropertySources;  
import org.springframework.core.env.PropertySource;  
import org.springframework.stereotype.Component;  
  
import java.util.HashMap;  
import java.util.Map;  
  
class MyMapPropertySource extends PropertySource<Map<String, String>> {  
    public MyMapPropertySource(String name, Map<String, String> source) { super(name, source); }  
    @Override public String getProperty(String name) { return this.source.get(name); }  
    @Override public boolean containsProperty(String name) { return this.source.containsKey(name); }  
}  
  
@Configuration  
@ComponentScan  
@org.springframework.context.annotation.PropertySource("classpath:application.properties")  
class ApplicationConfig {  
    @Autowired private ConfigurableEnvironment environment;  
    @PostConstruct public void addCustomPropertySource() {  
        MutablePropertySources sources = environment.getPropertySources();  
  
        HashMap<String, String> map = new HashMap<String, String>();  
        map.put("email", "admin@yaner-here.top");  
        MyMapPropertySource source = new MyMapPropertySource("yaner_propertysource", map);  
  
        sources.addFirst(source);  
    }  
}  
  
public class Application {  
    public static void main(String[] args) {  
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(ApplicationConfig.class);  
        Environment environment = context.getEnvironment();  
        System.out.println("email: " + environment.getProperty("email")); /* email: admin@yaner-here.top */
    }  
}
```

### §1.7.3 TaskExecutor

我们知道，Java以`java.util.concurrent.Executor`接口的形式提供了对线程池的抽象。Spring在此基础上又进行了一层封装，提供了`org.springframework.core.task.TaskExecutor`接口。

针对该接口，Spring提供了各种类的实现：

| `TaskExecutor`实现类         | 路径                                           | 作用        |
| ------------------------- | -------------------------------------------- | --------- |
| `SimpleAsyncTaskExecutor` | `org.springframework.core.task.`             | 每次创建一个新线程 |
| `SyncTaskExecutor`        | `org.springframework.core.task.`             | 同步线程      |
| `ConcurrentTaskExecutor`  | `org.springframework.scheduling.concurrent.` | 并发线程      |
| `ThreadPoolTaskExecutor`  | `org.springframework.scheduling.concurrent.` | 线程池       |

下面的代码以`ThreadPoolTaskExecutor`为例，创建了一个线程池：

```java
package top.yaner_here.javasite;  
  
import org.springframework.beans.factory.annotation.Autowired;  
import org.springframework.context.annotation.AnnotationConfigApplicationContext;  
import org.springframework.context.annotation.Bean;  
import org.springframework.context.annotation.ComponentScan;  
import org.springframework.context.annotation.Configuration;  
import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;  
import org.springframework.stereotype.Component;  
  
import java.util.concurrent.RejectedExecutionException;  
import java.util.concurrent.ThreadPoolExecutor;  
import java.util.concurrent.TimeUnit;  
  
class MyTask implements Runnable {  
    private final int id;  
    public MyTask(int id) { this.id = id; }  
    @Override public void run() {  
        System.out.printf("Executing task %d by %s\n", this.id, Thread.currentThread().getName());  
        try {  
            TimeUnit.MICROSECONDS.sleep(200);  
        } catch (InterruptedException e) {  
            Thread.currentThread().interrupt();  
        }  
    }  
}  
  
@Configuration  
@ComponentScan  
class MyThreadPoolConfig {  
    @Bean public ThreadPoolTaskExecutor threadPoolTaskExecutor() {  
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();  
        executor.setCorePoolSize(1);  
        executor.setMaxPoolSize(1);  
        executor.setQueueCapacity(1);  
        executor.setRejectedExecutionHandler(new ThreadPoolExecutor.AbortPolicy());  
        executor.setThreadNamePrefix("MyTask-");  
        executor.initialize();  
        return executor;  
    }  
}  
  
@Component  
class MyTaskSubmitter {  
    @Autowired private ThreadPoolTaskExecutor executor;  
    public void submitTasks(int taskNum) {  
        for(int i = 1; i <= taskNum; ++i) {  
            try {  
                System.out.printf("Submitting Task %d\n", i);  
                executor.execute(new MyTask(i));  
                System.out.printf("Submitted Task %d\n", i);  
            } catch (RejectedExecutionException e) {  
                System.err.printf("Task %d is rejected\n", i);  
            }  
        }  
    }  
}  
  
public class Application {  
    public static void main(String[] args) {  
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(MyThreadPoolConfig.class);  
        MyTaskSubmitter submitter = context.getBean(MyTaskSubmitter.class);  
        submitter.submitTasks(5);  
        context.close();  
    }  
}
/* Submitting Task 1
   Submitted Task 1
   Submitting Task 2
   Submitted Task 2
   Submitting Task 3
   Executing task 1 by MyTask-1
   Submitting Task 4
   Submitting Task 5
   Executing task 2 by MyTask-1
   Task 3 is rejected
   Task 4 is rejected
   Task 5 is rejected */
```

### §1.7.4 TaskScheduler

Spring提供了`org.springframework.scheduling.TaskScheduler`接口用于实现定时任务，既包含预期时间点执行的任务，也包含重复执行的任务。Spring提供了以下常用的实现：

| `TaskScheduler`实现             | 路径                                           | 作用                           |
| ----------------------------- | -------------------------------------------- | ---------------------------- |
| `ThreadPoolTaskScheduler`     | `org.springframework.scheduling.concurrent.` | 线程池                          |
| `SimpleAsyncTaskScheduler`    | `org.springframework.scheduling.concurrent.` | 同步线程                         |
| `DefaultManagedTaskScheduler` | `org.springframework.scheduling.concurrent.` | 委托Java EE的应用服务器提供的`schedule` |

下面的代码展示了如何使用`ThreadPoolTaskScheduler`。

- 新建`MyTaskScheduleTask`类，实现`Runnable`接口的`.run()`方法，定义自己的任务。
- 新建`MyTaskScheduler`类作为Bean，自动装载Spring提供的`ThreadPoolTaskScheduler`实例，调用该实例的`.schedule()`、`.scheduleAtFixedRate()`、`.scheduleWithFixedDelay()`方法定义定时任务。
- 新建`MyTaskScheduleConfig`配置类，使用`@Configuration`注解修饰，在内部基于`MaskTaskScheduler`定义一个新的`Bean`，设置`ThreadPoolTaskScheduler`实例的线程池参数。

```java
package top.yaner_here.javasite;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.scheduling.TaskScheduler;
import org.springframework.scheduling.concurrent.ThreadPoolTaskScheduler;
import org.springframework.stereotype.Component;

import java.util.Date;
import java.util.concurrent.ScheduledFuture;

class MyTaskScheduleTask implements Runnable {
    private final String taskName;
    public MyTaskScheduleTask(String taskName) { this.taskName = taskName; }
    @Override public void run() {
        System.out.printf("Task %s starts executing at %s\n", this.taskName, new Date());
        try {
            Thread.sleep(200);
        } catch (InterruptedException e) {
            System.err.printf("Task %s is interrupted at %s", this.taskName, new Date());
            Thread.currentThread().interrupt();
        }
    }
}

@Configuration @ComponentScan class MyTaskScheduleConfig {
    @Bean public ThreadPoolTaskScheduler myThreadPoolTaskScheduler() {
        ThreadPoolTaskScheduler scheduler = new ThreadPoolTaskScheduler();
        scheduler.setPoolSize(1);
        scheduler.setThreadNamePrefix("MyThreadPoolTaskScheduler-");
        scheduler.setDaemon(true);
        scheduler.initialize();
        return scheduler;
    }
}

@Component
class MyTaskScheduler {
    private final TaskScheduler scheduler;
    @Autowired public MyTaskScheduler(TaskScheduler scheduler) { this.scheduler = scheduler; }
    public void startTask() {
        Date futrueTime = new Date(System.currentTimeMillis() + 2000);
        ScheduledFuture<?> futureTask1 = this.scheduler.schedule(new MyTaskScheduleTask("Task 1"), futrueTime);
        ScheduledFuture<?> futureTask2 = this.scheduler.scheduleAtFixedRate(new MyTaskScheduleTask("Task 2"), 2000);
        ScheduledFuture<?> futureTask3 = this.scheduler.scheduleWithFixedDelay(new MyTaskScheduleTask("Task 3"), 1000);
    }
    public void cancelTask(ScheduledFuture<?> future) {
        if(future == null) { return; }
        future.cancel(false);
    }
}

public class Application {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(MyTaskScheduleConfig.class);
        MyTaskScheduler scheduler = context.getBean(MyTaskScheduler.class);
        scheduler.startTask();
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        context.close();
    }
}
/* Task Task 2 starts executing at Thu Apr 24 20:09:00 SGT 2025
   Task Task 3 starts executing at Thu Apr 24 20:09:00 SGT 2025
   Task Task 3 starts executing at Thu Apr 24 20:09:01 SGT 2025
   Task Task 1 starts executing at Thu Apr 24 20:09:02 SGT 2025
   Task Task 2 starts executing at Thu Apr 24 20:09:02 SGT 2025
   Task Task 3 starts executing at Thu Apr 24 20:09:03 SGT 2025
   Task Task 3 starts executing at Thu Apr 24 20:09:04 SGT 2025
   Task Task 2 starts executing at Thu Apr 24 20:09:04 SGT 2025 */
```
## §1.8 AOP及其代理

面向切面编程（Aspect Oriented Programming，AOP）是Spring中的两个基本概念之一。模块中的各种功能称为**关注点**。在工程中常见一种情况：若干模块都需要调用逻辑相同的功能，我们将这段共用的功能称为**横切关注点**（也叫**切面**）。

AOP对应着设计模式中的代理模式。AOP代理指的是实现切面的对象，有JDK动态代理和CGLIB代理两种实现。

|                   | JDK动态代理 | CGLIB代理 | AspectJ代理 |
| ----------------- | ------- | ------- | --------- |
| 必须实现接口            | ✔       | ❌       | ❌         |
| 支持拦截`public`方法    | ✔       | ✔       | ✔         |
| 支持拦截`protected`方法 | ❌       | ✔       | ✔         |
| 支持拦截默认作用域方法       | ❌       | ✔       | ✔         |
| 支持拦截`private`方法   | ❌       | ❌       | ✔         |

### §1.8.1 JDK动态代理

下面的代码使用了JDK动态代理：

- 创建一个接口`PersonInterface`，以及一个实现了该接口的类`Person`。
- 创建一个实现了`java.lang.reflect.InvocationHandler`接口的`.invoke(Object proxy,Method method, Object[] args)`方法的自定义类`LogHandler`。其中`proxy`为实现了接口的实例，`method`为接口中的方法，`args`为调用代理对象传入的其它实参列表。
- 在主函数中，我们用`Person`类初始化一个接口`PersonInterface`接口实例`origin`，可以正常地调用`origin.greet()`方法。随后，我们使用`java.lang.reflect.Proxy()`方法分别传入接口类的ClassLoader、接口实例的类对象的接口列表，以及自己初始化的一个`LogHandler`实例，得到了一个代理对象`target`，它也能调用`target.greet()`方法。

```java
package top.yaner_here.javasite;  
  
import java.lang.reflect.InvocationHandler;  
import java.lang.reflect.Method;  
import java.lang.reflect.Proxy;  
  
interface PersonInterface {  
    public void greet();  
}  
  
class Person implements PersonInterface {  
    @Override public void greet() { System.out.println("Hello!"); }  
}  
  
class LogHandler implements InvocationHandler {  
    private PersonInterface source;  
    public LogHandler(PersonInterface source) { this.source = source; }  
    @Override public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {  
        System.out.printf("[LogHandler] Start: proxy called by method.\n");  
        try {  
            return method.invoke(source, args);  
        } finally {  
            System.out.printf("[LogHandler] Finished: proxy is called successfully.\n");  
        }  
    }  
}  
  
public class Application {  
    public static void main(String[] args) {  
        PersonInterface origin = new Person();  
        origin.greet();  
  
        PersonInterface target = (PersonInterface) Proxy.newProxyInstance(  
            PersonInterface.class.getClassLoader(),  
            origin.getClass().getInterfaces(),  
            new LogHandler(origin)  
        );  
        target.greet();  
    }  
}
/* Hello!
   [LogHandler] Start: proxy called by method.
   Hello!
   [LogHandler] Finished: proxy is called successfully. */
```

### §1.8.2 `@Aspect`配置代理

AspectJ是Eclipse开发的一款代理库。不同于其它代理库创建代理对象，AspectJ直接修改Java字节码，因此理论上能做到其它代理库的一切操作。

为了安装AspectJ，我们需要引入`aspectjrt`和`aspectjweaver`依赖：

```xml
<dependency>  
    <groupId>org.aspectj</groupId>  
    <artifactId>aspectjrt</artifactId>  
    <version>1.9.19</version>  
</dependency>  
  
<dependency>  
    <groupId>org.aspectj</groupId>  
    <artifactId>aspectjweaver</artifactId>  
    <version>1.9.19</version>  
</dependency>
```

AspectJ要求使用`@Aspect`注解将某个类声明为AspectJ配置类。AspectJ使用的语法中，有着一系列**切入点标识符**（PCD，Pointcut Designator），这已经超出了Spring的范围。

下面是一段示例代码：

- 自定义`SayHelloInterface`接口及其实现类`SayHello`。
- 自定义`SayHelloAspect`类，使用`@Aspect`注解声明为AspectJ的代理类，使用`@Order()`注解声明代理顺序。其中定义一个回调方法，使用`@Before()`或`@After()`注解，传入AspectJ表达式来声明该回调方法的触发条件。

```java
package top.yaner_here.javasite;

import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
import org.springframework.core.annotation.Order;
import org.springframework.stereotype.Component;

interface SayHelloInterface {
    String sayHello(StringBuffer words);
}

@Component class SayHello implements SayHelloInterface {
    @Override public String sayHello(StringBuffer words) { return "Hello! " + words; }
}

@Aspect @Component @Order(1) class SayHelloAspect {
    @Before("target(top.yaner_here.javasite.SayHelloInterface) && args(words)")
    public void addWords(StringBuffer words) {
        words.append(" SayHelloAspect add a word.");
    }
}

@Configuration
@EnableAspectJAutoProxy
@ComponentScan("top.yaner_here.javasite")
class ApplicationConfig { }

public class Application {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(ApplicationConfig.class);
        SayHelloInterface sayHello = context.getBean("sayHello", SayHelloInterface.class);
        System.out.println(sayHello.sayHello(new StringBuffer("test1."))); // Hello! test1. SayHelloAspect add a word.
    }
}
```

### §1.8.3 Spring AOP配置代理

Spring AOP对AspectJ框架提供了大部分支持。

以下面的代码为例：

- 创建自定义类`OrderService`模拟业务，提供`placeOrder()`和`cancelOrder()`方法。
- 创建`@Aspect`类，并且用Spring的`@Component`注册为Bean。在其中先使用`@Pointcut(AspectJ表达式)`将被修饰的空方法定义为切入点，再使用`@Before(空方法名)`或`@After(空方法名)`注册切入点的监听函数。

```java
package top.yaner_here.javasite;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;

@Service class OrderService {
    public void placeOrder() { System.out.println("[OrderService] 提交订单"); }
    public void cancelOrder() { System.out.println("[OrderService] 取消订单"); }
}

@Aspect @Component class LoggerAspect {
    @Pointcut("execution(public * top.yaner_here.javasite.OrderService.*(..))")
    public void loggerTrigger() { }

    @Before("loggerTrigger()")
    public void createLog(JoinPoint joinPoint) {
        System.out.printf("[LoggerAspect] 监听到OrderService.%s()被调用了\n", joinPoint.getSignature().getName());
    }
}

@Configuration @ComponentScan class ApplicationConfig { }

public class Application {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(ApplicationConfig.class);
        OrderService service = context.getBean("orderService", OrderService.class);
        service.placeOrder();
        service.cancelOrder();
    }
}
/* [LoggerAspect] 监听到OrderService.placeOrder()被调用了
   [OrderService] 提交订单
   [LoggerAspect] 监听到OrderService.cancelOrder()被调用了
   [OrderService] 取消订单 */
```

> 注意：虽然Spring AOP和AspectJ都使用了AspectJ语法，但是它们之间并不完全互通。由于Spring AOP的实现依赖于动态代理，因此它无法拦截静态初始化方法、构造方法、属性赋值等操作。而且Spring AOP并不完全支持AspectJ的所有PCD。

Spring的通知类型十分灵活，支持在方法的各个执行阶段进行拦截，例如执行前、执行后、抛出异常后，甚至可以完全替代方法的实现，或给某个类添加原先没有的接口实现。Spring的通知类型及其注解如下所示：

- 前置通知`@Before()`：引用事先定义的切入点或切入点表达式，在切入点执行前抢先一步执行。
- 后置通知`@AfterReturning()`：若切入点正常返回，则在返回前调用该回调方法。
- 环绕通知`@Around()`：被该注解修饰的方法的第一个形参必须是`ProceedingJoinPoint`，返回类型就是被拦截方法的返回类型或其父类。TODO：？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
- 引入通知`@DeclareParents()`




### §1.8.3 XML配置代理