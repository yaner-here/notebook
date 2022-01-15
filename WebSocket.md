# §1 WebSocket API

首先检查浏览器是否支持WebSocket：

```javascript
if(window.WebSocket){
    console.log("支持WebSocket");
}else{
    console.log("不支持WebSocket");
}
```

## §1.1 WebSocket构造函数

```javascript
//建立WebSocket连接
var conn=new WebSocket("ws://echo.websocket.org/");
//建立WebSocket Secure连接
var conn_secure=new WebSocket("wss://echo.websocket.org/");
```

## §1.2 WebSocket事件

### §1.2.1 `open`事件

当客户端收到`open`事件时，就会触发对应的函数。

```javascript
conn_secure.onopen=(e)=>{console.log("Connect Succeed!")};
```

### §1.2.2 `message`事件

```javascript
conn_secure.onmessage=(e)=>{
    if(typeof(e)=='string'){
        console.log("This string is: "+e);
    }else if(typeof(e)=='number'){
        console.log("This number is: "+String(e));
    }
} 
```

该方法也可用于处理二进制数据：

- `Blob`类

  ```javascript
  conn_secure.binaryType='blob'; //指定二进制数据类型
  conn_secure.onmessage=(e)=>{
      if(e.data instanceof Blob){
          var conn_secure.receivedMessage=new Blob(e.data);
      }
  }
  ```

- `ArrayBuffer`类

  ```javascript
  conn_secure.binaryType='arraybuffer';
  conn_secure.onmessage=(e)=>{
      if(e.data instanceof ArrayBuffer){
          var conn_secure.receivedMessage=new Uint8Array(e.data);
      }
  }
  ```


### §1.2.3 `error`事件

```javascript
conn_secure.onerror=(e)=>{
    console.log("WebSocket Error: ",e);
}
```

### §1.2.4 `close`事件

```javascript
conn_secure.onclose=(e)=>{
    console.log("WebSocket closed",e);
}
```

## §1.3 WebSocket方法

### §1.3.1 `send()`方法

```javascript
var conn=new WebSocket('ws://echo.websocket.org');
conn.onopen=function(e){
    conn.send("Hello World!");
    conn.send(new Blob("Blob binary data"));
    conn.send((new Uint8Array([1,2,3])).buffer);
}
```

> 注意：必须确保`conn`处于连接状态时才能发包，下例为错误示范。
>
> ```javascript
> var conn=new WebSocket('ws://echo.websocket.org');
> conn.send("Hello World!"); //可能发送失败
> ```
>
> 在不使用`onopen()`方法的前提下，我们也可以用`readyState`属性判断连接是否成功。
>
> ```javascript
> var conn=new WebSocket('ws://echo.websocket.org');
> if(ws.readyState===WebSocket.OPEN){
> 	conn.send("Hello World!");
> }
> ```

### §1.3.2 `close()`方法

`conn.close([statusCode],[Reason])`用于终止WebSocket连接，有两个可选参数，`statusCode`是整型变量，作为关闭代码发送至服务器；`Reason`是字符串，作为关闭原因发送至服务器。

```javascript
conn.close();
conn.close(403,"Connection Forbidden!");
```

|   代码    |        含义        |                           使用场景                           |
| :-------: | :----------------: | :----------------------------------------------------------: |
|   1000    |      正常关闭      |                     当前session完成任务                      |
|   1001    |        离开        |             当前session主动离开并不期望后续重连              |
|   1002    |      协议错误      |              当前session被要求使用不支持的协议               |
|   1003    |  不支持的数据类型  |              当前session收到一条无法处理的消息               |
|   1004    |        保留        |                                                              |
|   1005    |        保留        |                                                              |
|   1006    |        保留        |                                                              |
|   1007    |      无效数据      | 当前session收到一条数据本体与消息类型不匹配的消息（例UTF8传`/uffff`） |
|   1008    |    消息违反政策    |     当前session不希望消息泄漏或其他关闭代码都表示不了时      |
|   1009    |      消息过大      |          当前session接受的消息太多宜纸宜无法处理时           |
|   1010    |      需要扩展      |             当前session需要的扩展不被服务器支持              |
|   1011    |      意外情况      |             当前session遇到了不可预见的原因情况              |
|   1015    |      TLS失败       |                TLS在WebSocket握手成功之前失败                |
|   0~999   |    （禁止使用）    |            0~999之间的代码无效，不能用于任何目的             |
| 1000~2999 |      （保留）      |            1000~2999用于扩展和WebSocket的修订版本            |
| 3000~3999 |    （需要注册）    | 3000~3999用于程序库、框架和应用程序，需要由IANA（互联网编号分配机构）公开注册分配 |
| 4000~4999 | （私有，可自定义） | 4000~4999可以用自定义用途，但是可能不被其他标准WebSocket协议理解 |



## §1.4 WebSocket对象特性

### §1.4.1 `readyState`

```javascript
function PrintReadyState(conn){
    if(!conn instanceof WebSocket){
        console.log("This isn't a Websocket object!");
    	return;
    }
    switch(conn.readyState){
    	case WebSocket.CONNECTING:
        	console.log("Waiting for connecting.");
        	break;
        case WebSocket.OPEN:
        	console.log("Connection established.");
        	break;
        case WebSocket.CLOSING:
        	console.log("Waiting for closing.");
        	break;
        case WebSocket.CLOSED:
        	console.log("Connection closed.");     
    }
}
```

|        特性常量        | 取值 |       含义       |
| :--------------------: | :--: | :--------------: |
| `WebSocket.CONNECTING` |  0   | 正在尝试建立连接 |
|    `WebSocket.OPEN`    |  1   |   连接建立成功   |
|  `WebSocket.CLOSING`   |  2   | 正在尝试关闭连接 |
|   `WebSocket.CLOSED`   |  3   |   连接关闭成功   |

### §1.4.2 `bufferedAmount`

`conn.bufferedAmount`返回`conn`在`conn.send()`中已经作为浏览器缓存进入到发送队列，但还没来得及发送的数据的字节数。

```javascript
//限制上行速率小于1kb/s
var maxUploadSpeed=1024;
conn.onopen=function(){
    setInterval(
    	function(){
            if(conn.bufferedAmount<maxUploadSpeed){
                conn.send("Some Data Here");
            }else{
                console.log("不允许短时间内发送大量消息!");
            }
        },
        1000
    );
}
conn.onclose=function(){
    if(conn.bufferedAmount>0){
        console.log("关闭连接时还有数据未发送,这部分数据已丢失")
    }
}
```

## §1.5 综合demo

```html
<!DOCTYPE html>
<html>
    <script>
        function Initialize(){
            output=document.getElementById("output");
            conn=new WebSocket("ws://echo.websocket.org/echo");
            conn.onopen=()=>{
                console.log("Connection established!");
                conn.send("Hello World!");
            };
            conn.onclose=()=>{
                console.log("Connection closed!");
            };
            conn.onerror=(e)=>{
                console.log(e);
            };
            conn.onmessage=(e)=>{
                console.log("Received message:"+e.data);
                var p=document.createElement("p");
                p.style.wordWrap="break-word";
                p.textContent=s;
                output.appendChild(p);
            }
        }
        if(window.WebSocket){
            Initialize();
        }else{
            console.log("当前浏览器不支持WebSocket");
        }
    </script>
    <body>
        <div id="output"></div>
    </body>
</html>
```

