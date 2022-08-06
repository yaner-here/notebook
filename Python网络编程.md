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

`setsockopt()`提供了众多的套接字选项：

- `socket.SO_BROADCAST`：发送并接受UDP广播数据包
- `socket.SO_DONTROUTE`：告知路由器只能发送到本机所在的内网，不得发送到外网
- `socket.SO_TYPE`：传给`getsocketopt()`时，用于返回套接字类型

### §1.1.4 广播

我们知道，每一网段都有自己的广播地址。例如`192.168.1.0`为C类IP地址，其子网掩码为`255.255.255.0`，则这一网段的广播地址为`192.168.1.255`：

```python
# UDPBroadcast.py
import argparse
import socket
BUFFER_SIZE = 65535

def server(serverIp: str = '0.0.0.0', serverPort: int = 60000):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((serverIp, serverPort))
    print('Listening on {}'.format(sock.getsockname()))
    while True:
        (rawReceiveData, senderIP) = sock.recvfrom(BUFFER_SIZE)
        data = rawReceiveData.decode('ascii')
        print('The client from {} says {!r}'.format(senderIP, data))
        sock.sendto('Response 200 OK'.encode('ascii'),senderIP)

def client(serverIp: str, serverPort: int = 60000):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    rawSendData = bytes('Hello World!', 'ascii')
    sock.sendto(rawSendData, (serverIp, serverPort))
    sock.settimeout(5)
    rawReceiveData = sock.recv(BUFFER_SIZE)
    print('Server responded: {}'.format(rawReceiveData.decode('ascii')))

if __name__ == '__main__':
    options = {'client': client, 'server': server}
    parser = argparse.ArgumentParser(description='UDP server broadcast Demo')
    parser.add_argument('option',choices=options)
    parser.add_argument('--serverIp',help='Server\'s IP')
    parser.add_argument('--serverPort',help='Server\'s port')
    args = parser.parse_args()
    function = options[args.option]
    if(args.serverIp is not None or args.serverPort is not None):
        function(args.serverIp,args.serverPort)
    else:
        function()
```

```shell
# 设备1
$ ifconfig
    eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>
            inet 192.168.1.2  netmask 255.255.255.0  broadcast 192.168.1.255
$ python UDPBroadcast.py server
	Listening on 0.0.0.0:60000
	The client from 192.168.1.4 says 'Hello World'
```

```shell
# 设备2
$ ifconfig
    eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>
            inet 192.168.1.3  netmask 255.255.255.0  broadcast 192.168.1.255
$ python UDPBroadcast.py server
	Listening on 0.0.0.0:60000
	The client from 192.168.1.4 says 'Hello World'
```

```shell
# 设备3
$ ifconfig
    eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>
            inet 192.168.1.4  netmask 255.255.255.0  broadcast 192.168.1.255
$ python UDPBroadcast.py client 192.168.1.255 60000
	Response 200 OK
	Response 200 OK
```

`socket.bind((listenIP,listenPort))`中的`listenIP`既可以是普通的字符串`127.0.0.1`，也可以是`<broadcast>`表示广播。

## §1.2 TCP

TCP基于以下机制实现可靠连接：

- 每个TCP数据包都有一个序列号，被客户端用于排序并检测丢包

- 序列号的具体数值取决于该数据包的首尾数据在整体数据中的偏移量。例如要通过TCP发送一个`1000`字节的文件，开始的序列号值可以随机选取。假设前一个数据包的序列号为$\text{offset}$，承载的数据长度为$\text{length}$，那么下一个数据包的序列号就是$\text{offset+length}$

- 为保证安全，如果中间人无法获取TCP数据包的明文序列号，那么第一个TCP数据包的序列号必须随机选取，防止攻击者轻易伪造出合法的恶意数据包

- TCP没有阻塞（锁步）这一概念，取而代之的是窗口，用于控制同时传输的数据量

- 建立连接时需要三次握手：

  ```mermaid
  sequenceDiagram
      autonumber
      actor Client
      participant Server
      
      Client->>Server: SYN(Synchronize)<br/>Client向Server发送初始序列号
      Server->>Client: SYN-ACK(Synchronize-Acknowledge)<br/>Server向Client确认初始序列号
      Client->>Server: ACK(Acknowledge)<br/>Client告知Server可以建立连接
  ```

- 结束时进行3~4次挥手：

  ```mermaid
  sequenceDiagram
      autonumber
      participant A
      participant B
      
      A->>B: FIN(Finish)<br/>A停止发送数据，并向B发送中止请求
      B-->>A: Ack(Acknowledge)<br/>B发送应答报文，表示自己不会再尝试接收数据
      B->>A: FIN-ACK(Finish-Acknowledge)<br/>B停止发送数据，并向A发送中止请求
      A->>B: ACK(Acknowledge)<br/>A发送应答报文，表示自己不会再尝试接收数据
  ```

TCP的连接必须经过三次握手，而且第一个包只能由客户端发起。于是，我们将服务器的套接字分成两种：

- 被动套接字（Passive Socket）/监听套接字（Listening Socket）：用于向众多客户端提供了一个普遍的端口，使得客户端先能“发现”服务器。这种Socket不负责传输任何数据，也不代表实际的网络会话，只是负责网络发现与主动套接字的分配。
- 主动套接字（Active Socket）/连接套接字（Conntected Socket）：负责与客户端进行绑定。一个套接字名可以被多个主动套接字所共享，例如多个Socket的套接字名都可以是本机的外网IP`1.2.3.4`的`80`端口。`(本地IP,本地端口,客户端IP,客户端端口)`是标识不同主动套接字的唯一依据。

这意味着服务器的Socket只需要`socket.bind((interface,port))`与`socket.listen(1)`，而客户端的Socket只需要`socket.connect((ip,port))`。

```python
# TCPServer.py
import socket

def recvall(sock: socket.socket, length: int) -> bytes:
    rawData = b''
    rawDataLength = 0
    while rawDataLength < length:
        buffer = sock.recv(length - rawDataLength)
        if not buffer:
            raise EOFError('Expecting {} bytes but only {} bytes received.'.format(
                length, rawDataLength))
        rawData += buffer
        rawDataLength += len(buffer)
    return rawData

def server(interface: str = 'localhost', port: int = 60000):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((interface, port))
    sock.listen(1)
    print('Listening at {}'.format(sock.getsockname()))
    while True:
        (sc, sockname) = sock.accept()
        print('A new TCP Connection from {} was accepted.'.format(sockname))
        print('\tSocket Name: {}'.format(sc.getsockname()))
        print('\tSocket Peer: {}'.format(sc.getpeername()))
        rawResponse = recvall(sc, 16)
        print('\tReceiving request: {}'.format(rawResponse.decode('ascii')))
        sc.sendall(b'Request received')
        sc.close()
        print('\tResponse was been sent successfully.')

if __name__ == '__main__':
    server()
```

```python
# TCPClient.py
import socket

def recvall(sock: socket.socket, length: int) -> bytes:
    rawData = b''
    rawDataLength = 0
    while rawDataLength < length:
        buffer = sock.recv(length - rawDataLength)
        if not buffer:
            raise EOFError('Expecting {} bytes but only {} bytes received.'.format(
                length, rawDataLength))
        rawData += buffer
        rawDataLength += len(buffer)
    return rawData

def client(host: str = 'localhost', port: int = 60000):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((host, port))
    print('Client is bound to {}'.format(sock.getsockname()))

    rawRequest = b'1010101010101010'
    print('\tSending to Server: {}'.format(rawRequest.decode('ascii')))
    sock.sendall(rawRequest)
    rawResponse = recvall(sock, 16)
    print('\tServer responded {!r}'.format(rawResponse.decode('ascii')))

    sock.close()

if __name__ == '__main__':
    client()
```

```shell
$ python TCPServer.py
    Listening at ('127.0.0.1', 60000)
    A new TCP Connection from ('127.0.0.1', 46998) was accepted.
            Socket Name: ('127.0.0.1', 60000)
            Socket Peer: ('127.0.0.1', 46998)
            Receiving request: 1010101010101010
            Response was been sent successfully.
    A new TCP Connection from ('127.0.0.1', 47000) was accepted.
            Socket Name: ('127.0.0.1', 60000)
            Socket Peer: ('127.0.0.1', 47000)
            Receiving request: 1010101010101010
            Response was been sent successfully.
```

```shell
$ python TCPClient.py
    Client is bound to ('127.0.0.1', 46998)
            Sending to Server: 1010101010101010
            Server responded 'Request received'
$ python TCPClient.py
    Client is bound to ('127.0.0.1', 47000)
            Sending to Server: 1010101010101010
            Server responded 'Request received'
```

1. 这里我们必须先设置套接字的属性：`sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)`，否则当上一个曾经连接过客户端的服务器终止后，下一个服务器立刻重启时，就会抛出`OSError: [Errno 98] Address alreay in use`：

   ```shell
   $ python TCPServer.py
       Listening at ('127.0.0.1', 60000)
       A new TCP Connection from ('127.0.0.1', 47010) was accepted.
               Socket Name: ('127.0.0.1', 60000)
               Socket Peer: ('127.0.0.1', 47010)
               Receiving request: 1010101010101010
               Response was been sent successfully.
       ^C
   $ python TCPServer.py
       Traceback (most recent call last):
         File "TCPServer.py", line 35, in <module>
           server()
         File "TCPServer.py", line 20, in server
           sock.bind((interface, port))
       OSError: [Errno 98] Address already in use
   ```

   ```shell
   yaner@DESKTOP-UVBN0SD ~/f/p/chapter03 (m)> python TCPClient.py
   Client is bound to ('127.0.0.1', 47010)
           Sending to Server: 1010101010101010
           Server responded 'Request received'
   ```

   这个错误抛出地非常诡异。第一：上一个服务器已经停止运行，那么是谁还在占用着这个地址呢？第二：`Address`本来就可以复用，多个套接字就是可以共用同一个套接字名，按理来说不可能发生冲突。怎么会事呢？答案是操作系统的网络栈部分必须非常谨慎地处理连接的关闭（即四次挥手）。这四个数据包一来一回，产生的网络延迟就会特别大，而`socket.SO_REUSEADDR`可以允许Python脚本强行占用仍处于`CLOSE-WAIT`与`TIME-WAIT`的TCP连接。

2. 这里我们自定义了一个`recvall()`函数。这是因为当套接字的缓冲区将满时，TCP会自动将整个数据流分开，这使得只调用一次`socket.send()`与`socket.recv()`并不能保证所有数据都会被发送或接受。为确保所有数据都被发送，我们可以设计一个`sendall()`函数，内部逻辑大致如下所示：

   ```python
   def sendall(sock,message):
       sentLength = 0
       while sentLength < len(message)
           sentLength += sock.send(message[sentLength:]) # sock.send()返回此次发送的长度
   ```

3. 其实`Socket`库已经实现了`sendall()`方法，并且是用C语言实现的，并且在循环中释放了全局解释器锁，因此效率更高。然而`Socket`库并没有实现`recvall()`方法，所以我们只能自己写一个了。

4. 然后我们对`sock`实例使用了`sock.listen(1)`，这一步标志着该套接字正式成为被动套接字，只能通过`sock.accept()`返回的新套接字来接受和发送数据。这一过程不可逆转。`sock.accept()`返回了一个新的套接字`sc`，这就是前面提到的主动套接字。

5. 最后我们使用`sock.close()`关闭套接字，该函数会自动进行TCP的四次挥手。

### §1.2.1 死锁

当两个程序共享有限的资源时，一方只能等待另一方结束资源占用。当其中一方遇到异常情况而阻塞，导致无法释放资源时，另一方也会陷入阻塞状态，这种现象被称为**死锁（Deadlock）**。

请看以下代码，下面的服务器能将收到的字母全转换成大写形式，然后返回给客户端：

```python
import argparse, socket, sys

def server(host: str, port: int):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((host, port))
    sock.listen(1)
    print('Listening at', sock.getsockname())
    while True:
        (sc, sockname) = sock.accept()
        print('Processing up to 1024 bytes at a time from', sockname)
        rawRequestLength = 0
        while True:
            rawRequest = sc.recv(1024)
            if not rawRequest:
                break
            rawReponse = rawRequest.decode('ascii').upper().encode('ascii')
            sc.sendall(rawReponse)
            rawRequestLength += len(rawRequest)
            print('\r\t%d bytes have been processed so far.' % rawRequestLength, end='')
            sys.stdout.flush()  # 确保stdout的缓冲区内容均被输出
        sc.close()
        print('\n\tSocket closed.')

def client(host: str, port: int, requestLength: int):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    requestLength = (requestLength + 15) // 16 * 16  # 舍弃最后一个长度不满16 Bytes的包
    message = b'capitalize this!'  # 16-byte message to repeat over and over

    print('Sending', requestLength, 'bytes of data, in chunks of 16 bytes')
    sock.connect((host, port))

    sentLength = 0
    while sentLength < requestLength:
        sock.sendall(message)
        sentLength += len(message)
        print('\r\t%d bytes sent' % (sentLength), end='')
        sys.stdout.flush()

    sock.shutdown(socket.SHUT_WR)

    print('\n\tReceiving all the data the server sends back:')
    receivedLength = 0
    while True:
        rawResponse = sock.recv(16)
        if not receivedLength: # 只输出前16个Bytes的数据
            print('\tThe first chunk received says', repr(rawResponse))
        if not rawResponse:
            break
        receivedLength += len(rawResponse)
        print('\r\t%d bytes received' % (receivedLength), end='')
    sock.close()

if __name__ == '__main__':
    roles = ('client', 'server')
    parser = argparse.ArgumentParser(description='Get deadlocked over TCP')
    parser.add_argument('role', choices=roles, help='which role to play')
    parser.add_argument('host', help='The interface which server listens at or client sends to')
    parser.add_argument('requestLength', type=int,nargs='?',default=16)
    parser.add_argument('-p', metavar='PORT', type=int, default=60000, help='TCP port (default 1060)')
    args = parser.parse_args()
    if args.role == 'client':
        client(args.host, args.p, args.requestLength)
    elif args.role == 'server':
        server(args.host, args.p)
```

这段代码处理小数据时运行正常：

```shell
$ python tcp_deadlock.py server ''
    Listening at ('0.0.0.0', 60000)
    Processing up to 1024 bytes at a time from ('127.0.0.1', 43268)
            16 bytes have been processed so far.
            Socket closed.
    Processing up to 1024 bytes at a time from ('127.0.0.1', 43270)
            65536 bytes have been processed so far.
            Socket closed.
```

```shell
$ python tcp_deadlock.py client '' 16
    Sending 16 bytes of data, in chunks of 16 bytes
            16 bytes sent
            Receiving all the data the server sends back:
            The first chunk received says b'CAPITALIZE THIS!'
            16 bytes received
$ python tcp_deadlock.py client '' 65536
    Sending 65536 bytes of data, in chunks of 16 bytes
            65536 bytes sent
            Receiving all the data the server sends back:
            The first chunk received says b'CAPITALIZE THIS!'
            65536 bytes received
```

但是处理大数据时会卡死，一段时间后，服务器首先停止运行，然后客户端也停止运行：

```shell
$ python tcp_deadlock.py server ''
    Listening at ('0.0.0.0', 60000)
    Processing up to 1024 bytes at a time from ('127.0.0.1', 43272)
            3254304 bytes have been processed so far.
    Traceback (most recent call last):
      File "tcp_deadlock.py", line 74, in <module>
        server(args.host, args.p)
      File "tcp_deadlock.py", line 25, in server
        sc.sendall(rawReponse)
    ConnectionResetError: [Errno 104] Connection reset by peer
```

```shell
$ python tcp_deadlock.py client '' 99999999
    Sending 100000000 bytes of data, in chunks of 16 bytes
            8364592 bytes sent
    Traceback (most recent call last):
      File "tcp_deadlock.py", line 72, in <module>
        client(args.host, args.p, args.requestLength)
      File "tcp_deadlock.py", line 43, in client
        sock.sendall(message)
    ConnectionResetError: [Errno 104] Connection reset by peer
```

问题出在客户端：客户端源源不断地发送数据（`sock.sendall(message)`），服务器也在源源不断地发送数据（`sc.sendall(rawResponse)`），问题是客户端一方面接受数据，另一方面又没有及时执行`rawResponse = sock.recv(16)`来接受数据。

首先，客户端的逻辑是：必须先把所有数据发送完，才开始接受数据。于是服务器发过来的数据全都被积压在客户端的输入缓冲区。随着时间的推移，客户端的输入缓冲区先会被占满，此时服务器发现自己发送的数据没有得到应答，于是会尝试不断重发，导致服务器阻塞`sendall()`方法，自然也不会进入下一个循环调用`sc.recv(1024)`接收新数据。但是客户端仍然不断地发送数据，于是服务器的输入缓冲区也会被占满。接着客户端发现自己发送的数据得不到应答，于是不断地尝试重发，导致客户端阻塞`sock.sendall(message)`方法，自然也不可能进入到下一个用于读取服务器数据的`rawResponse = sock.recv(16)`。综上所述，两者均陷入阻塞状态，形成死锁。

解决死锁问题的思路有以下两种：

1. 给套接字调用`setblocking()`方法禁用阻塞

   ```python
   sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
   # ......
   (sc, sockname) = sock.accpet()
   sc.setblocking(0)
   sc.recv(1024) # 立即返回，若输入缓冲区不足1024字节则只返回输入缓冲区已有的数据
   ```

2. 使用多线程，将接受与发送分成两个进程

3. 使用IO多路复用，调用`select()`与`poll()`

### §1.2.2 半开连接

