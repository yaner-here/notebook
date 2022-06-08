# JSP

# §1 JSP基本语法

## §1.1 脚本元素

JSP的脚本元素包括声明、脚本段和表达式。

### §1.1.1 注释（Comment）

JSP包含两种注释：

- HTML注释

  面向前端，用户可以看到，格式为`<!-- -->`

- JSP注释

  面向后端，只有后端才能看到，格式为`<%-- --%>`。内部可以嵌套Java注释，例如`<%-- // --%>`或`<%-- /* */ --%>`

### §1.1.2 声明（Declearation）

声明语句用于在JSP中声明变量和定义方法，格式为`<%! %>`，不能向当前输出流进行操作。

```jsp
<html>
    <body>
        <%! 
            int a = 1;
            int GetSquare(int data){
                return data*data;
            }
        %>
        <% out.println(a + GetSquare(2)); %>
    </body>
</html>
```

### §1.1.3 脚本段（Scriptlets）

脚本段是在处理请求时执行的Java代码段，格式为`<% %>`，可以对当前输出流进行操作。

```jsp
<html>
    <body>
        <% if(Math.random() > 0.5){ %>
            You are lucky! :)
        <% }else{ %>
            You are unlucky! :(
        <% } %>
    </body>
</html>
```



### §1.1.4 表达式（Expression）

表达式指的是Java中完整的表达式，格式为`<%= %>`计算后会被转换为字符串，输出到当前的输出流中。

```jsp
<%@ page import="java.util.Date" %>
<html>
    <body>
        <%= new Date() %>
    </body>
</html>
```

## §1.2 指令元素

JSP的指令元素包括`page`指令、`include`指令、`taglib`指令，格式为`<%@ 指令名属性="属性值" %>`，**只在编译时运行一次**。

### §1.2.1 page指令

`page`指令用于定义JSP页面内的属性和属性值，格式为`<%@ page key1=value1 key2=value2 ... %>`。该指令可以修改的属性和属性值有：

- `language`：使用的脚本语言，缺省为`java`

- `import`：导入的Java软件包

- `extends`：编译时需要使用的Java类

- `session`：设置此网页是否加入到`session`中，缺省为`true`

- `buffer`：输出网页时使用的缓冲区的长度，可取`none`或数字，缺省为`8KB`

- `autoFlush`：缓冲区已满时是否自动输出缓冲区。若设为`false`，则缓冲区满时抛出异常，缺省为`true`

- `info`：指定网页的说明信息，可由`Servlet.getServletInfo()`获取

  ```jsp
  <%@ page info="This is info!" %>
  <html>
      <body>
          <% out.print(getServletInfo()); %>
      </body>
  </html>
  ```

- `isThreadSafe`：设置能否多线程访问，缺省为`true`

- `isErrorPage`：指定此网页是否为另一个JSP页面的错误提示页面，决定能否调用`Exception`类

- `errorPage`：指定此网页的错误提示页面

- `contentType`：指定该网页使用的字符集、JSP响应的MINE类型，缺省为`text/html;charset=ISO-8859-1 `

### §1.2.2 include指令

`include`指令在当前文件中包含一个静态文件，格式为`<%@ include file="<path>" %>`。

> 注意：包含的文件不能有`<html>`/`<body>`等标签，否则将破坏当前文件的DOM结构。

```jsp
<!-- nowTime.jsp -->
<%@ page import="java.util.Date" %>
<% out.print(new Date()); %>
```

```jsp
<!-- index.jsp -->
<html>
    <body>
        <%@ include file="nowTime.jsp" %>
    </body>
</html>
```

### §1.2.3 taglib指令

？？？？？？？？？？？？？？TODO：

`taglib`指令用于指定JSP自定义的标签，格式为`<%@ taglib uri="<TagLibrary>" prefix="<Prefix>">`，其中各参数的含义为：

- `uri`：根据标签前缀，对自定义标签进行的唯一命名
- `prefix`：在自定义标签之前的前缀

> 注意：`jsp`/`jspx`/`java`/`javax`/`servlet`/`sun`/`sunw`等保留字不允许作为自定义标签的前缀。

## §1.3 动作元素

动作元素用于控制JSP容器的动作，**每次请求时都被执行一次**。

### §1.3.1 `<jsp:include>`

`<jsp:include>`用于在该文件中包含其它文件，并将结果输出到页面中，格式为`<jsp:include page="URL<%=expression>" flush="true" />`。

```jsp
<html>
    <body>
        <jsp:include page="nowtime.jsp" />
    </body>
</html>
```

### §1.3.2 `<jsp:forward>`

`<jsp:forward>`用于在不改变地址栏地址的情况下，实现重定向页面，格式为`<jsp:forward page="URL">`。

### §1.3.3 `<jsp: param>`

`<jsp:param>`用于传参，通常与`<jsp:include>`、`<jsp:forward>`、`<jsp:plugin>`搭配使用，格式为`<jsp:param name="name" value="value">`。

```jsp
<!-- sendMessage.jsp -->
<jsp:forward page="showMessage.jsp">
    <jsp:param name="message" value="This is a message"/>
</jsp:forward>
```

```jsp
<!-- showMessage.jsp -->
<%= request.getParameter("message") %>
```

### §1.3.4 `<jsp:useBean>`

`<jsp:useBean>`允许JSP使用JavaBean，格式为`<jsp:useBean id="<InstanceName>" scope="<ScopeName>" <typeSpec> />`，其中各参数的含义如下所示：

- `id`：在当前`scope`内调用或新建名为`<InstanceName>`的实例

- `scope`：指定Bean类的作用域，取值范围为`page`、`request`、`session`、`application`

- `<typeSpec>`：指定Bean类的种类属性。

  | 组合情况 | `class` | `beanName` | `type` |
  | :------: | :-----: | :--------: | :----: |
  |          |    √    |            |        |
  |          |    √    |     √      |        |
  |          |         |     √      |   √    |
  |          |         |            |   √    |

  - `class`：指定Bean类的完整路径
  - `beanName`：指定Bean实例的名称
  - `type`：指定Bean类的名称/超类的名称/实现的任意接口之一。

```java
public class Person {
	private String name;
	public void setName(String name){
        this.name = name;
    }
    public String getName(String name){
        return this.name;
    }
}
```

```jsp
<html>
    <head>
        <jsp:useBean id="LiHua" scope="page" class="Person" />
        <%
        	LiHua.setName("LiHua");
        	out.println(LiHua.getName());
        %>
    </head>
</html>
```

将编译得到的`.class`文件放到`/src/WebApp/WEB-INF/classes/com/example`目录下即可。

```shell
C:\workspace> javac Person.java
C:\workspace> mv Person.class ...
```

## §1.4 内置对象

JavaBean要求必须先手动初始化实例，才能调用改实例。然而JSP页面初始化时会自动声明某些对象，因此在JSP中可以直接使用。这些对象被称为内置对象（Implicit Object）。

|   实例名称    |           内容            |      生存周期      | 对应类                                   |
| :-----------: | :-----------------------: | :----------------: | ---------------------------------------- |
| `application` |      整个WebApp对象       | 整个WebApp运行期间 | `javax.servlet.ServletContext`           |
|   `config`    | JSP页面初始化时使用的容器 |    页面执行期间    | `javax.servlet.ServletConfig`            |
|  `exception`  | 发生错误时产生的异常对象  |    页面执行期间    | `java.lang.Throwable`                    |
|     `out`     |  服务器的`OutputStream`   |    页面执行期间    | `javax.servlet.jsp.JspWriter`            |
|    `page`     |      当前网页的对象       |    页面执行期间    | `javax.lang.Object`，也就是`this`        |
| `pageContext` | 提供其他对象和方法的对象  |    页面执行期间    | `javax.servlet.jsp.PageContext`          |
|   `request`   |   客户端发送请求的信息    |    用户请求时间    | `javax.servlet.http.HttpServletRequest`  |
|  `response`   |   服务器发送响应的信息    |    页面响应期间    | `javax.servlet.http.HttpServletResponse` |
|   `session`   |      当前会话的信息       |      会话期间      | `javax.servlet.http.HttpSession`         |

### §1.4.1 `request`

`request`实例代表客户端的请求，包含客户端所有基于HTTP协议传递的信息，例如`GET`/`POST`传递的表单信息、COOKIE等。

| 方法名                            |                        作用                        |                          返回示例                          |
| --------------------------------- | :------------------------------------------------: | :--------------------------------------------------------: |
| `getAttribute(String)`            |          获取Server内`name`属性对应的对象          |                                                            |
| `setAttribute(String,Object)`     |          设置Server内`name`属性对应的对象          |                                                            |
| `removeAttribute(String)`         |          删除Server内`name`属性对应的对象          |                                                            |
| `getAttributeNames()`             |               获取Server内所有属性名               |                                                            |
| `getParameter(String name)`       |    获取Client内**第一个**`name`属性对应的字符串    |                                                            |
| `getParameterValues(String name)` | 获取Client内**所有**`name`属性对应的字符串**数组** |                                                            |
| `getServerName()`                 |             获取Client访问的Domain或IP             |                  `127.0.0.1`或`localhost`                  |
| `getServerPort()`                 |                获取Client访问的Port                |                   `80`或`10809`（代理）                    |
| `getServletPath()`                |              获取Client请求的资源路径              |                        `/index.jsp`                        |
| `getRemoteAddr()`                 |                 获取Client看到的IP                 | `127.0.0.1`或`0.0.0.0.0.0.0.1`（hosts定义`::1 localhost`） |
| `getRemotePort()`                 |             获取`Client`监听本机的Port             |                          `64651`                           |
| `getLocalPort()`                  |              获取Server当前监听的端口              |                            `80`                            |
| `getContextPath()`                |          获取Client请求的资源所在的文件夹          |                        `/myWebApp`                         |
| `getCharacterEncoding()`          |        获取Server解析Request时使用的字符集         |                     缺省为`iso-8859-1`                     |
| `setCharacterEncoding(String)`    |        设置Server解析Request时使用的字符集         |                                                            |
| `getCookies()`                    |          获取Client发送的`Cookie`实例数组          |                                                            |
| `getSession()`                    |         获取当前Session的`HttpSession`实例         |                                                            |
| `getContentType()`                |            获取Client请求数据的MINE类型            |                        `text/html`                         |
| `getProtocol()`                   |                获取Client使用的协议                |                         `HTTP/1.1`                         |
| `getContentLength()`              |    获取Client发送Request时指明的`ContentLength`    |                        `-1`（缺省）                        |

> 这里的Server和Client是相对而言的。`Attribute`是自己可以控制和修改的，而`Parameter`只能受对方控制，自己无权更改。
>
> 例如Client经过Proxy向Server发包，那么Client的`Attribute`就是Proxy的`Parameter`，Proxy再设置自己的`Parameter`，那么Server受到的`Attribute`包含了Server的`Parameter`和`Parameter`。

```jsp
<!-- index.jsp -->
<%@ page contentType="text/html;UTF-8" %>
<html>
    <body>
        <form name="MessageBoard" method="post" action="showOrder.jsp">
            <label><input type="text" name="username" placeholder="Your Name Here"></label>
            <label>
                <input type="checkbox" name="order" id="Apple" value="Apple"><label for="Apple">Apple</label>
                <input type="checkbox" name="order" id="Banana" value="Banana"><label for="Banana">Banana</label>
                <input type="checkbox" name="order" id="Cheery" value="Cheery"><label for="Cheery">Cheery</label>
            </label>
            <label><input type="submit" value="Buy"></label>
            <label><input type="reset" value="Reset"></label>
        </form>
    </body>
</html>
```

```jsp
<!-- showOrder.jsp -->
<%@ page import="java.util.Arrays" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<% request.setCharacterEncoding("UTF-8"); %>
<html>
    <body>
        Your name is: <%= request.getParameter("username") %><br>
        Your order is: <%= Arrays.toString(request.getParameterValues("order")) %>
    </body>
</html>
```

### §1.4.2 `response`

`res`
