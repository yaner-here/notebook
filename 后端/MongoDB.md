# §1 MongoDB基础知识

## §1.1 概念

| Excel通称     | 行(`line`)             | 工作表(`sheet`)     | 工作簿(`xls文件`)    |
|:-----------:|:---------------------:|:----------------:|:---------------:|
| MySQL概念     | 记录(`record`)          | 表(`table`)       | 数据库(`database`) |
| MySQL表示方法   | `1,"hello"`           |                  |                 |
| MongoDB概念   | 文档(`document`)        | 集合(`collection`) | 数据库(`database`) |
| MongoDB表示方法 | `{"a":1,"b":"hello"}` |                  |                 |

## §1.2 启动

- Linux
  
  ```shell
  root@localhost:~# wget https://repo.mongodb.org/apt/ubuntu/dists/focal/mongodb-org/5.0/multiverse/binary-amd64/mongodb-org-server_5.0.3_amd64.deb
  root@localhost:~# sudo dpkg -i mongodb-org-server_5.0.3_amd64.deb
  root@localhost:~# mkdir /data/db (否则缺失存储目录,无法启动)
  root@localhost:~# mongod (全局变量,直接执行即可)
  root@localhost:~# mongo (进入mongo shell)
  
  root@localhost:~# mongo --nodb (进入mongo shell,且不预先连接任何数据库,需要自定义db对象)
  > conn = new Mongo("<HostName:Port>") //一般是localhost:27017
  > db = conn.getDB("<DatabaseName>")
  ```

- Windows
  
  ```cmd
  C:\> mkdir C:\data\db (否则缺失存储目录,无法启动)
  C:\> cd "C:\Program Files\MongoDB\Server\5.0\bin"
  C:\Program Files\MongoDB\Server\5.0\bin> mongod.exe (除非添加到全局变量)
  ```

## §1.3 操作入门

选择数据库：`use <DatabaseName>`或

查看当前数据库：`db`

添加文档：`db.<CollectionName>.insert(<DocumentName>)`

查看文档：`db.<CollectionName>.find()`(无格式文本),`<DatabaseName>.<CollectionName>.findOne()`(格式友好)

更新文档：`db.<CollectionName>.update(<TargetObjectClue>,<NewObject>)`

删除文档：`db.<CollectionName>.remove([TargetObjectClue])`根据`TargetObjectClue`匹配删除项，缺省时删除所有文档

查看帮助：`help`

```javascript
> post={
... "title":"Blog",
... "content":"This is a blog",
... "date":new Date()
... }
> db.blog.insert(post)
> db.blog.find()
> db.blog.findOne()
> post.comment=[]
> TargetObjectClue={"title":"Blog"}
> db.blog.update(TargetObjectClue,post)
```

## §1.4 数据类型

| 类型              | 取值                         | 描述                                                                       |
|:---------------:|:--------------------------:|:------------------------------------------------------------------------:|
| `null`          | `null`                     | 表示空值或不存在的值                                                               |
| `boolean`       | `true`或`false`             | 布尔值                                                                      |
| `number`        | 所有实数                       | 64位浮点型                                                                   |
| `NumberInt()`类  | 所有整数                       | 4字节有符号整型                                                                 |
| `NumberLong()`类 | 所有整数                       | 8字节有符号整形                                                                 |
| `string`        | 字符串                        | UTF-8编码                                                                  |
| `Date()`类       | 日期                         | ISODate()表示的标准时                                                          |
| `RegExp()`类     | `\<Regex>\`                | 正则表达式，`var i = new RegExp(\<Regex>\)`或`var o={"regex":\<Regex>\}`        |
| `ObjectId()`类   | '61769e13f5e3ce5398480af8' | 12字节的对象ID，是文档的唯一标识符<br />1-4位是时间戳，5-7位是主机名的哈希值，8-9位是进程标识符(PID)，10-12是计数器 |

## §1.5 脚本

### §1.5.1 执行外部脚本

```shell
root@localhost:~# mongo javascript.js
root@localhost:~# mongo
> load("javascript.js")
```

### §1.5.2 shell辅助函数

在脚本中不能使用shell辅助函数，替代品如下表所示：

| 作用        | 选择数据库                              | 显示全部数据库                  | 显示全部集合                    |
|:---------:|:----------------------------------:|:------------------------:|:-------------------------:|
| shell辅助函数 | `use <DatabaseName>`               | `show dbs`               | `show collections`        |
| 等价函数      | `db.getSisterDB("<DatabaseName>")` | `db.getMongo().getDBs()` | `db.getCollectionNames()` |

### §1.5.3 与外界terminal交互

```javascript
> // mongo shell特供run(),mongosh没有
> run('ls','/','-l','-a') //Linux,用,逗号分隔参数
> run('test.bat')         //Windows,不支持环境变量,只能调用该目录下的内容
```

### §1.5.4 自定义初始化脚本

在用户个人根目录下（Linux:`~/`，Windows:`C:\Users\<Username>`）下存在一个`.mongorc.js`文件。每次mongo shell启动时都会执行一次该脚本。

- 启动时指定`--norc`可以禁用默认执行。
- 可以在其中重写变量`prompt`为字符串或函数，使shell执行每条命令前都输出该字符串或函数返回值。
- 可以在其中或shell中指定字符串变量`EDITOR`为Linux编辑器可执行文件路径，从而使用`edit <VariableName>`来修改变量`VariableName`的定义，也就是编辑复合变量。

```javascript
function notAllow(){print("This function is banned for security.")}
//禁止删除数据库
db.dropDatabase = notAllow;
DB.prototype.dropDatabase = notAllow;
//禁止删除集合
DBCollection.prototype.drop = notAllow;
//禁止删除索引
DBCollection.prototype.dropIndex = notAllow;
//仿Conda输出当前数据库
prompt=function(){
    if(typeof db=='undefined'){return '(nodb)> ';}
    try{db.runCommand({getLastError:1});}
        catch(e){print(e);}
    return db+'> ';
}
//制定编辑复合变量的编译器
EDITOR="/usr/bin/vim";
```

### §1.5.5 保留字段冲突的解决方案

已知`version`是MongoDB中对象`db`的一个方法。设想如下情景：`db`此时指向`test`数据库，其中有一个名为`version`的集合，现在尝试拿到这个集合对应的对象。

```javascript
> db.version.insert({"a":1});
> db.version_2.insert({"b":2});
> db.version
    function () {
        return this.serverBuildInfo().version;
    }
> db.version_2
    test.version
```

为了获取集合`version`，有以下几种方法：

```javascript
> db.version.find();
    {...}
> db.getCollection("version")
     test.version
> db.version["a"]
     1
```

# §2 增删查改

## §2.1 插入

- 单个插入：`db.<CollectionName>.insert(<ObjectName>)`
  
  ```javascript
  var obj={"a":1};
  db.testDatabase.insert(obj);
  ```

- 批量插入：`db.<CollectionName>.insert(<ArrayOfObject>)`
  
  ```javascript
  var obj1={"b":2};
  var obj2={"c":3};
  var obj3={"d":4};
  var array=[obj1,obj2,obj3];
  db.test.insert(array);
  ```

## §2.2 删除

- 删除所有文档：`db.<CollectionName>.drop()`
  
  ```javascript
  db.test.drop();
  ```

- 删除指定文档：`db.<CollectionName>.remove(<TargetObjectClue>)`
  
  ```javascript
  db.test.remove({d:4});
  ```

## §2.3 更新

> `db.<CollectionName>.update()`只匹配符合条件的第一个文档

### §2.3.1 替换文档

```javascript
var obj={"id":1,score:100};
db.test.insert(obj);
obj.score=99;
db.test.update({"id":1},obj);
```

### §2.3.2 修改器

`"$set"`用于指定一个字段的值，如果字段不存在则新建。

```javascript
> db.test.find()
    {
        "_id":ObjectId("...")
        "name":"LiHua"
    }
> db.test.update(
...     {name:"LiHua"},
...     {"$set":{"age":18}}
... )
```

`"$unset"`用于删除一个字段的值。

```javascript
> db.test.find()
    {
        "_id":ObjectId("...")
        "name":"LiHua"
    }
> db.test.update(
...        {"name":"LiHua"},
...        {"$unset":{"name":"anything"}} //只需指定要删除的键名即可,键值随意
... )
> db.test.update(
...     {"name":"LiHua"},
...        {"name":"anything"} //错误,这样会覆盖掉原有的键值对
... )
```

`"$inc"`用于增加一个整型字段的值。

```javascript
> db.test.insert({"id":1,"score":59,"grade":"★"});
> db.test.update({"id":1},{"$inc":{"score":1}}); //score++
> db.test.update({"id":1},{"$inc":{"score":1,"grade":"★"}}); //报错,score不变,因为Cannot increment with non-numeric argument
```

`"$push"`用于为数组添加元素，若数组不存在则先创建。

```javascript
> db.test.update(
...     {"id":1},
...     {"$push":
...         {"comments":
...                "Good" //创建comments数组并array.push("Good")
...         }
...     }
... )
> db.test.update(
...     {"id":1},
...     {"$push":
...         {"comments":
...                "Well" //array.push("Well")
...         }
...     }
... )
//一次性push多个元素
> var remark=["Excellent","Great","Fine"];
> db.test.update(
...         {"id":1},
...         {"$push":
...         {"comments":
...             {"$each":remark}
...         }
...      }
... )
//限制一次性push的数量/按顺序输入
> db.test.update(
...         {"id":1},
...         {"$push":
...         {"comments":
...             {"$each":remark,"$slice":-2,"$sort":{"rating":-1}}
                //"$slice"必须为负数,在"$sort"规定的排序规则进行排序后保留最后2项
...         }
...      }
... )
```

`"$addToSet"`确保数组内的元素不会重复。

```javascript
> db.test.update({"id":1},{"$addToSet":{"country":"China"}});
> db.test.update({"id":1},{"$addToSet":{"country":"China"}});
> db.test.update({"id":1},{"$addToSet":{"country":{"$each":["China","America","England"]}}});
> db.test.find();
```

`"$pop"`删除属组内的元素。

```javascript
> db.test.update({"id":1},{"$pull":{"country":"America"}});
```

`$`返回当前选中元素在数组中的下标。

```javascript
> db.test.find();
[
  {
    _id: ObjectId("617803cd0fd927116ff3fd0a"),
    id: 1,
    country: [ { name: 'China', rank: 2 }, { name: 'America', rank: 1 } ]
  }
]
> db.test.update({"country.name":"China"},{"$set":{"country.$.rank":1}});
> db.test.update({"country.name":"America"},{"$set":{"country.$.rank":2}});
> db.test.find();
[
  {
    _id: ObjectId("617803cd0fd927116ff3fd0a"),
    id: 1,
    country: [ { name: 'China', rank: 1 }, { name: 'America', rank: 2 } ]
  }
]
```

### §2.3.3 upsert

观察`db.<CollectionName>.update(<TargetObjectClue>,<NewObject>,[upsert])`的完整定义，`upsert`是一个布尔值，决定着当`<TargetObjectClue>`没有匹配到任何一个文档时，是否将`<NewObject>`作为一个新文档插入到`<CollectionName>`中。

```javascript
> db.test.update({"country.name":"England"},{"$set":{"c":3}}) //无效果
> db.test.update({"country.name":"England"},{"$set":{"country.$.rank":3}},true)
```
