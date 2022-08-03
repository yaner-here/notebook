# Django

# §0 基础知识

我们以一个简单的HTTP GET请求入手，学习Python中各种库所处的层级。

`requests`是Python自带的一个系统库，封装了互联网的大部分底层代码，默认使用系统代理，所以用起来非常地简便：

```python
import requests

def getGoogleSearchResult(query:str)->str:
    parameters:dict = {'q':query}
    response:requests.Response = requests.get(url='https://www.google.com',params=parameters)
    return response.text

if __name__ == '__main__':
    print("Input search keyword: ")
    result:str = getGoogleSearchResult(input())
    print(result)
```

`http`库是一个较为底层的库，暴露了HTTP协议实现的大部分细节，但是默认直连，代码较为繁琐：

```python
import http.client

def getBaiduSearchResult(query:str):
    path = '{}?q={}'.format('/',query)
    connection = http.client.HTTPConnection('www.baidu.com')
    connection.request('GET',path)
    rawReply:bytes = connection.getresponse().read()
    reply:str = str(rawReply)
    return reply

if __name__ == '__main__':
    print("Input search keyword: ")
    result:str = getBaiduSearchResult(input())
    print(result)
```

继续向底层深挖，我们知道HTTP协议建立在TCP/IP协议的Socket之上的。Python也提供了`socket`库：

```python
import socket
import ssl
from urllib.parse import quote_plus

request_text = """\
GET /search?q={} HTTP/1.1\r\n\
Host: baidu.com\r\n\
User-Agent: Foundations of Python Network Programming example search4.py\r\n\
Connection: close\r\n\
\r\n\
"""

def getBaiduSearchResult(query:str):
    unencrypted_sock = socket.socket()
    unencrypted_sock.connect(('baidu.com', 443))
    sock = ssl.wrap_socket(unencrypted_sock)
    request = request_text.format(quote_plus(query))
    sock.sendall(request.encode('ascii'))
    raw_reply = b''
    while True:
        more = sock.recv(4096)
        if not more:
            break
        raw_reply += more
    print(raw_reply.decode('utf-8'))

if __name__ == '__main__':
    print("Input search keyword: ")
    result:str = getBaiduSearchResult(input())
    print(result)
```

Python对各层次的网络都实现了完整的支持。

## §0.1 编码与解码

Python使用`encode()`与`decode()`方法，实现字符串`str`数据类型与字节数组`bytes`数据类型之间的转化：

```python
inputBytes_1 = b'Hello '
inputBytes_2 = bytes('World','ascii')
inputBytes_3 = b'\x21'
inputBytes:bytes = inputBytes_1 + inputBytes_2 + inputBytes_3
inputString = inputBytes.decode('ascii')
print(inputString)
	# Hello World!

outputString = '你好，世界！'.encode('utf-8')
outputBytes = outputString.decode('gbk')
print(outputBytes)
	# 浣犲ソ锛屼笘鐣岋紒
```

## §0.2 IP地址

操作系统倾向于自己处理IP的各种细节，这部分细节通常对Python不可见，我们只能在Python中获取相关的结果。例如`socket`库支持DNS解析的相关操作：

```python
hostname:str = 'www.baidu.com'
ip:str = socket.gethostbyname(hostname)
print(ip)
	# 39.156.66.18
```

IPv4规定了一些特殊地址段：

- `127.0.0.0/8`：被本地运行的应用程序使用。通常情况下，大多数操作系统（Windows/Linux）只使用`127.0.0.1`这一个地址，并且在`hosts`文件中为该地址指定`localhost`域名。
- `10.0.0.0/8`、`172.16~31.0.0/16`、`192.168.0.0/16`：互联网运营商机构划分的私有子网。

## §0.3 TCP与UDP

IP协议只负责将数据包转发到正确的设备。如果要维护一个会话，那么还需要在IP协议的基础之上发明新协议，满足以下两个特性：

- 多路复用（Multiplexing）：将不同的会话区分开来
- 可靠传输（Reliable Transport）：修复发生错误的数据包，重传丢失的数据包，丢弃重复的数据包，重组到达时序错乱的数据包

TCP（Transmission Control Protocol，传输控制协议）与UDP（User Datagram Protocol，用户数据报协议）就是上述提到的新协议。其中TCP满足了两个特性，而UDP只满足了前一个特性，需要开发者自行设计可靠传输的细节。

TCP/UDP使用端口（Port）这一概念实现多路复用。每个数据包都有一个无符号16位二进制数表示端口号，范围从0到65536。IANA（Internet Assigned Numbers Authority，互联网号码分配机构）规定了端口号的分配规则：

- 知名端口（0-1023）：分配给最重要、最常用的服务，通常普通权限用户无法监听这类端口，例如DNS端口为`53`
- 注册端口（1024-49151）：一般由软件开发商指定，例如MySQL端口为`3306`，但是MariaDB端口也是`3306`
- 普通端口（49152-65535）：可以随意使用，操作系统会在此区间内随机选取端口号进行动态分配

`socket`储存了知名端口和注册端口与相关软件的对应关系：

```python
import socket

print("{} protocol port: {}".format('ssh',socket.getservbyname('ssh')))
print("{} protocol port: {}".format('domain',socket.getservbyname('domain')))
print("{} protocol port: {}".format('telnet',socket.getservbyname('telnet')))
print("{} protocol port: {}".format('mysql',socket.getservbyname('mysql')))
```

```shell
$ python test.py
    ssh protocol port: 22
    domain protocol port: 53
    telnet protocol port: 23
    ftp protocol port: 3306
```

在Linux中，这些对应关系也储存在`/etc/services`文件中：

```shell
$ cat /etc/services
    tcpmux          1/tcp                           # TCP port service multiplexer
    echo            7/tcp
    echo            7/udp
    discard         9/tcp           sink null
    discard         9/udp           sink null
    systat          11/tcp          users
    daytime         13/tcp
    daytime         13/udp
    netstat         15/tcp
    qotd            17/tcp          quote
    chargen         19/tcp          ttytst source
    chargen         19/udp          ttytst source
    ftp-data        20/tcp
    ftp             21/tcp
    fsp             21/udp          fspd
    ssh             22/tcp                          # SSH Remote Login Protocol
    telnet          23/tcp
    smtp            25/tcp          mail
    time            37/tcp          timserver
    time            37/udp          timserver
    whois           43/tcp          nicname
    tacacs          49/tcp                          # Login Host Protocol (TACACS)
    # ......
```



## §0.2 `socket`库

```python
import socket

EOL1 = b'\n\n'
EOL2 = b'\n\r\n'
body = '''Hello World'''
response_params = [
    'HTTP/1.0 200 OK',
    'Date: Sun, 27 may 2018 01:01:01 GMT',
    'Content-Type: text/plain; charset=utf-8',
    'Content-Length: {}\r\n'.format(len(body.encode())),
    body
]
response = '\r\n'.join(response_params)

def handle_connection(conn,addr):
    request = b""
    while EOL1 not in request and EOL2 not in request:
        request += conn.recv(1024)
    print(request)
    conn.send(response.encode())
    conn.close()

def main():
    serversocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    serversocket.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
    serversocket.bind(('127.0.0.1',8001))
    serversocket.listen(5)
    print('http://127.0.0.1:8001')
    try:
        while True:
            conn,address = serversocket.accept()
            handle_connection(conn,address)
    finally:
        serversocket.close()

if __name__ == '__main__':
    main()
```



```powershell
C:\PythonServer\> python server.py
	http://127.0.0.1:8001
	b'GET / HTTP/1.1\r\nHost: localhost:8001\r\nUser-Agent: curl/7.79.1\r\nAccept: */*\r\n\r\n'
C:\PythonServer\> curl localhost:8001
	Hello World
```

