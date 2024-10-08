# IPv6

一个IPv4地址仅占32bit，而一个IPv6地址占128bit。

## 报头

IPv6报头的结构如下所示：

```
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version| Traffic Class |           Flow Label                  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|         Payload Length        |  Next Header  |   Hop Limit   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                         Source Address                        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                      Destination Address                      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

1. `<Version>`表示互联网协议版本号，在IPv6中是一个4bit的数字`0110`，表示`6`。
2. `<Traffic Class>`表示流类别，等价于IPv4中的TOS字段。该字段长度为8bit，表示数据包的类或优先级，应用于QoS。
3. `<Flow Label>`表示流标签，字段长度为20bit。这是IPv6的新增字段，用于区分实时流量。一组流标签和源地址可以唯一确定一个数据流。
4. `<Payload Length>`表示有效载荷长度，字段长度为16bit，单位为8byte。这里的有效载荷指的是数据包中除IPv6报头以外的其他部分，当有效载荷长度超过`UINT16_MAX`时，该字段置零，真正的长度用IPv6扩展报头中的超大有效载荷字段表示。
5. `<Next Header>`表示下一个报头，字段长度为8bit。用于定义紧跟在IPv6报头后面的第一个扩展报头的类型。
6. `<Hop Limit>`表示条数限制，字段长度为8bit，作用等价于IPv4报头中的`<TTL>`字段，即每经过一个节点自减一次。如果路由器收到数据包时，`<HOP LIMIT>`为零或者自减为零，则丢弃该数据包。
7. `<Source Address>`：源地址，字段长度为128bit。
8. `<Destination Address>`：目标地址，字段长度为128bit。

一个IPv6数据包可以携带任意数量个IPv6扩展报头，每个扩展报头的类型都由前一个报头的`<Next Header>`字段标识。路由器不会添加、删除和更改IPv6扩展报头。目前已规定的扩展报头如下表所示，每个扩展包括必须按照顺序出现，且最多只出现一次（目的选项报头可以出现两次）：

| 出现顺序 | 报头/扩展报头名称                              | `<Next Header>`值 | 作用                                                         |
| ---- | -------------------------------------- | ---------------- | ---------------------------------------------------------- |
| ①    | IPv6报头                                 |                  |                                                            |
| ②    | 逐跳选项报头（Hop-by-Hop Options）             | `0`              | 用于有效载荷过长的情况、设备提示和资源预留                                      |
| ③/⑧  | 目的选项报头（Destination Options）            | `60`             | 携带数据包途径节点需要处理的信息，用于移动IPv6<br>③表示途径路由器对应的节点<br>⑧表示目标地址对应的节点 |
| ④    | 路由报头（Routing）                          | `43`             | 强制指定数据包必须经过特定的节点                                           |
| ⑤    | 分段报头（Fragment）                         | `44`             | 用于数据包长度过长的情况，受MTU长度限制而分段                                   |
| ⑥    | 认证报头（Authentication）                   | `51`             | 用于IPsec的身份认证、数据完整性校验、重放检测、报头字段防篡改                          |
| ⑦    | 封装安全报头（Encapsulating Security Payload） | `50`             | 用于IPsec的身份认证、数据完整性校验、数据报内容加密                               |

$$
举例:\begin{array}{|c|c|c|c|}
	\hline
	\underset{\mathrm{next\_header}=\mathrm{Routing}}{\mathrm{IPv6报头}} &
	\underset{\mathrm{next\_header}=\mathrm{Fragment}}{\mathrm{IPv6扩展报头(Routing)}} &
	\underset{\mathrm{next\_header}=\mathrm{TCP}}{\mathrm{IPv6扩展报头(Fragment)}} &
	\mathrm{TCP报头}+\mathrm{数据}
	\\ \hline
\end{array}
$$

## 寻址方式

根据[RFC 3513](https://datatracker.ietf.org/doc/html/rfc3513#page-3)的规定，IPv6地址有三种表示方式：

- `x:x:x:x:x:x:x:x`。其中每个`x`都是一个16bit的字，用4个Hex字符表示，例如`1234:0:0:CDEF:1234:0:0:0`。
- 使用`::`压缩一段连续的`0`。如果地址中包含多段连续的`0`，则`::`最好用于表示最长的一段连续`0`。例如上面的示例地址最好表示为`1234:0:0:CDEF::`，也可以表示为`1234::CDEF:1234:0:0:0`。一个地址中最多只能出现一次`::`。
- `x:x:x:x:x:x:d.d.d.d`。其中每个`x`都是一个16bit的字，用4个Hex字符表示（可以省略前导零，使用更少字符表示）；每个`d`都是一个8bit的字，用3个Dec字符表示。

与IPv4地址的CIDR表示法类似（例如`127.0.0.1/24`），IPv6地址使用`<IPv6_ADDRESS>/<PREFIX_LENGTH>`表示地址前缀。

IPv6的地址分为三种：单播（Unicast）、任播（Anycast）和多播（Multicast），各自对应着自己的寻址方式。

- 单播（Unicast）：单个接口的标识符，只发送到这一个接口。
- 任播（Anycast）：一组接口的标识符，只发送到路由协议规定的、距离最短的接口。
- 多播（Multicast）：一组接口的标识符，发送到其中的所有接口。

| 地址类型                           | IPv6地址前缀 |
| ---------------------------------- | ------------ |
| 未指定（Unspecified）              | `::/128`     |
| 环回（Loopback）                   | `::1/128`    |
| 多播（Multicast）                  | `FF00::/8`   |
| 链路本地单播（Link-local Unicast） | `FE80::/10`  |
| 站点本地单播（Sute-local Unicast） | `FEC0::/10`  |
| 全球单播（Global Unicast）         | 其他任何地址 |

未指定地址`::`不能分配给任何节点，也不能作为IPv6数据包的目标地址，也不会被路由器转发。

环回地址`::1`指代节点自身的地址，不能分配给任何物理接口，也不会被路由器转发。

全球单播地址由三部分组成：`<GLOBAL_ROUTING_PREFIX><SUBNET_ID><INTERFACE_ID>`。其中`<GLOBAL_ROUTING_PREFIX>`和`<SUBNET_ID>`两部分相加均为64bit，以`000`为开头的IPv6地址除外。这类特例地址指的是嵌入了IPv4地址的IPv6地址，以实现对IPv4的兼容性。

链路本地单播地址的格式为`<GLOBAL_ROUTING_PREFIX><SUBNET_ID><INTERFACE_ID>`，其中`<GLOBAL_ROUTING_PREFIX>`为`1111111010`的10bit常量，`<SUBNET_ID>`为全零的54bit常量，剩余64bit的`<INTERFACE_ID>`可以自由选择。链路本地单播适用于自动配置地址、邻居搜索、链路无路由器等情况。路由器不会将链路本地单播地址的数据包转发到其他链路。

站点本地单播地址的格式为`<GLOBAL_ROUTING_PREFIX><SUBNET_ID><INTERFACE_ID>`，其中`<GLOBAL_ROUTING_PREFIX>`为`1111111011`的10bit常量，`<SUBNET_ID>`为任意选择的54bit，剩余64bit的`<INTERFACE_ID>`也可以自由选择。站点本地单播用于站点内部的寻址。路由器不会将站点本地单播地址的数据包转发到其它站点。

任播地址的格式为`<SUBNET_PREFIX><INTERFACE_ID>`，其中`<SUBNET_PREFIX>`是长度任意的随机值，`<INTERFACE_ID>`全为零。它可以分配给多个不同的接口，也就是说每个接口可以分配相同的单播地址。根据路由协议提供的距离，路由器会将数据包发送至距离最短的接口。目前为了安全起见，任播地址禁止作为数据包的源地址，只能分配给路由器，不能分配给主机。

多播地址的格式为`11111111<FLGS><SCOP><GROUP_ID>`，其中`<FLGS>`为4bit，前3bit全为0，后1bit分为两种情况：为`0`时表示有IANA永久分配的多播地址，为`1`时表示非永久分配的多播地址。`<SCOP>`长为4bit，其含义如下表所示。`<GROUP_ID>`为任意选择的112bit。目前`FF0?::`系列的16个多播地址均被保留，不能分配和使用。特殊地，下标还展示了一系列被预先占用的多播地址。

| 多播地址`<SCOP>`取值              | 含义                              | 具体说明                  |
| --------------------------- | ------------------------------- | --------------------- |
| `1`                         | 接口本地域（Interface-local Scope）    | 仅跨域节点上的单个接口，仅作用于环回的多播 |
| `2`                         | 链路本地域（Link-local Scope）         | 仅作用于同一链路内             |
| `4`                         | 管理本地域（Admin-local Scope）        | 进行惯例配置的最小范围           |
| `5`                         | 站点本地域（Site-local Scope）         | 仅作用于同一链路内             |
| `8`                         | 组织本地域（Organization-local Scope） | 跨越单个组织的多个站点           |
| `E`                         | 全球域（Global Scope）               |                       |
| `0`/`3`/`F`                 | 保留（Reserved）                    |                       |
| `6`/`7`/`9`/`A`/`B`/`C`/`D` | 尚未分配（Unassigned）                | 可以自定义多播区域             |

| 多播地址            | 含义                                                         |
| ------------------- | ------------------------------------------------------------ |
| `FF01::1`           | 接口本地的所有节点                                           |
| `FF02::1`           | 链路本地的所有节点                                           |
| `FF01::2`           | 接口本地的所有路由器                                         |
| `FF02::2`           | 链路本地的所有路由器                                         |
| `FF05::2`           | 站点本地的所有路由器                                         |
| `FF02::1:FF??:????` | 请求节点多播地址，将`FF02::1:FF00:0/104`与IPv6地址的低24位拼接而成，用于减少节点必须假如的多播地址的数量 |
