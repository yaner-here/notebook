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

TCP（Transmission Control Protocol，传输控制协议）与UDP（User Datagram Protocol，用户数据报协议）就是上述提到的新协议。两者的单个数据包最大长度均为`65536`字节。其中TCP满足了两个特性，而UDP只满足了前一个特性，需要开发者自行设计可靠传输的细节。

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

端口号必须与IP地址相绑定。例如`0.0.0.0:80`会拦截所有尝试访问本机的`80`端口的数据包，而`127.0.0.1:80`只允许处理经过本机回环网卡IP地址的数据包，不允许其它网卡接收到的数据包：

```shell
$ netstat -ano
    激活Internet连接 (服务器和已建立连接的)
    Proto Recv-Q Send-Q Local Address           Foreign Address         State       Timer
    tcp        0      0 127.0.0.1:38847         0.0.0.0:*               LISTEN      关闭 (0.00/0/0)
    tcp        0      0 127.0.0.1:38847         127.0.0.1:48614         ESTABLISHED 关闭 (0.00/0/0)
    tcp        0      0 172.29.83.151:33448     172.29.80.1:10811       ESTABLISHED 关闭 (0.00/0/0)
    tcp        0      0 127.0.0.1:48618         127.0.0.1:38847         ESTABLISHED 关闭 (0.00/0/0)
    tcp6       0      0 :::42853                :::*                    LISTEN      关闭 (0.00/0/0)
    udp        0      0 127.0.0.1:60000         0.0.0.0:*                           关闭 (0.00/0/0)
```

事实上，端口号”冲突“的本质是端口号与监听地址均重合。例如我们完全可以给回环网卡的`127.0.0.1`与以太网的`192.168.1.2`分别绑定两个不同的`80`端口服务器。我们把IP地址和TCP/UDP端口号结合起来，称为**套接字名**。

# §1 套接字

所有操作系统的网络操作都是围绕套接字开展的，用一个整数来标识不同的套接字。Python的`socket`库对其进行了抽象，只需通过`socket.socket()`就能得到一个`socket`实例，通过该实例的`fileno()`就能获取到其整数：

```python
import socket
sockList = []
for i in range(0,3):
    sockList.append(socket.socket())
sockList[2].close()
for sock in sockList:
    print(sock.fileno())
    # 4
    # 5
    # -1
```

## §1.1 UDP套接字

### §1.1.1 混杂客户端

下面是一个最简单的UDP服务器和客户端：

```python
# TestServer.py
import socket
import random
MAX_BYTES = 65535

def server(ip: str, port: int):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((ip,port))
    print('Listening at {}'.format(sock.getsockname()))
    while True:
        (data,address) = sock.recvfrom(MAX_BYTES)
        print('The client at {} says {!r}'.format(address,data.decode('ascii')))
        response = 'Here\'s your lucky number:{}'.format(random.random()).encode('ascii')
        sock.sendto(response,address)

server('localhost',60000)
```

```python
# TestClient.py
import socket
MAX_BYTES = 65535

def client(serverIp: str, port: int):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    data = bytes("Hello, I'm a client.", 'ascii')
    sock.sendto(data, (serverIp, port))
    print('Requesting from {}'.format(sock.getsockname()))
    (data, address) = sock.recvfrom(MAX_BYTES)
    print('The server replied {!r}'.format(data.decode('ascii')))

client('localhost',60000)
```

```shell
$ python TestServer.py
    Listening at ('127.0.0.1', 60000)
    The client at ('127.0.0.1', 37979) says "Hello, I'm a client."
```

```shell
$ python TestClient.py
    Requesting from ('0.0.0.0', 37979)
	The server replied "Here's your lucky number:0.3872235270764811"
```

这段程序虽然满足了功能要求，但是有着非常大的风险：因为任何人得知客户端的端口号后，都可以自行向客户端发送数据包。而客户端只管开放端口，接受端口的所有数据包，而不会检验数据包的发送方，从而产生伪造的风险：

```shell
$ python TestClient.py
    Requesting from ('0.0.0.0', 43542)
    The server replied 'You are hacked!'
```

```shell
$ python
    Python 3.10.4 (main, Apr  2 2022, 09:04:19) [GCC 11.2.0] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import socket
    >>> socket.socket(socket.AF_INET,socket.SOCK_DGRAM).sendto('You are hacked!'.encode('ascii'),('127.0.0.1',43542))
        15
```

这种”什么都接受“的客户端称为**混杂客户端（Promiscuous Client）**。

### §1.1.2 不可靠性

我们知道，UDP没有重传机制。这意味着我们必须自己编写相应的逻辑，以应对阻塞、超时、丢包等情形。为模拟网络阻塞，我们在服务器端模拟随机丢包：

```python
# UnstableUDPServer.py
import socket
import random
MAX_BYTES = 65535

def server(ip:str, port:int):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((ip, port))
    print('Listening at', sock.getsockname())
    while True:
        (data, address) = sock.recvfrom(MAX_BYTES)
        if random.random() < 0.7:
            print('Pretending to drop packet from {}'.format(address))
            continue
        text = data.decode('ascii')
        print('The client at {} says {!r}'.format(address, text))
        message = 'Here\'s your lucky number:{}'.format(random.random())
        sock.sendto(message.encode('ascii'), address)
        print('Packet sent successfully!')

server('localhost',60000)
```

```python
# RetransmissionUDPClient.py
import socket
MAX_BYTES = 65535

def client(serverIp: str, serverPort: int):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.connect((serverIp,serverPort))
    delay = 0.1
    data = bytes("Hello, I'm a client.", 'ascii')
    while True:
        sock.send(data)
        sock.settimeout(delay)
        print('Waiting up to {} seconds for a reply'.format(delay))
        try:
            data = sock.recv(MAX_BYTES)
            print('The server replied {!r}'.format(data.decode('ascii')))
            break
        except socket.timeout as e:
            delay *= 2
            if(delay > 5):
                raise e
            else:
                continue

client('localhost',60000)
```

```shell
$ python UnstableUDPServer.py
    Listening at ('127.0.0.1', 60000)
    
    The client at ('127.0.0.1', 55549) says "Hello, I'm a client."
    Packet sent successfully!
    
    Pretending to drop packet from ('127.0.0.1', 51947)
    The client at ('127.0.0.1', 51947) says "Hello, I'm a client."
    Packet sent successfully!
    
    Pretending to drop packet from ('127.0.0.1', 41668)
    Pretending to drop packet from ('127.0.0.1', 41668)
    Pretending to drop packet from ('127.0.0.1', 41668)
    Pretending to drop packet from ('127.0.0.1', 41668)
    Pretending to drop packet from ('127.0.0.1', 41668)
    Pretending to drop packet from ('127.0.0.1', 41668)
```

```shell
$ python RetransmissionUDPClient.py
    Waiting up to 0.1 seconds for a reply
    The server replied "Here's your lucky number:0.06272517207969697"
$ python RetransmissionUDPClient.py
    Waiting up to 0.1 seconds for a reply
    Waiting up to 0.2 seconds for a reply
    The server replied "Here's your lucky number:0.8496767580730985"
$ python RetransmissionUDPClient.py
    Waiting up to 0.1 seconds for a reply
    Waiting up to 0.2 seconds for a reply
    Waiting up to 0.4 seconds for a reply
    Waiting up to 0.8 seconds for a reply
    Waiting up to 1.6 seconds for a reply
    Waiting up to 3.2 seconds for a reply
    Traceback (most recent call last):
      File "RetransmissionUDPClient.py", line 25, in <module>
        client('localhost',60000)
      File "RetransmissionUDPClient.py", line 21, in client
        raise e
      File "RetransmissionUDPClient.py", line 15, in client
        data = sock.recv(MAX_BYTES)
    TimeoutError: timed out
```









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

### §1.1.3 MTU与分组

MTU（Maximum Transmission Unit）指的是TCP/UDP协议中，能承载最多数据的数据包，长度通常为`65536`。这一最长长度可以通过`getsockopt()`与`setsocketopt()`调用和更改：

```python
import socket
MAX_BYTES = 65535

class IN:
    IP_MTU = 14
    IP_MTU_DISCOVER = 10
    IP_PMTUDISC_DO = 2

def server(ip: str, port: int):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.IPPROTO_IP, IN.IP_MTU_DISCOVER, IN.IP_PMTUDISC_DO)
    sock.connect((ip,port))
    sockMTU = sock.getsockopt(socket.IPPROTO_IP, IN.IP_MTU)
    print(sockMTU)
    	# 65535
   
server('localhost', 60000)
```