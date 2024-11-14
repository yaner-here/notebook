```sh
apt update && apt upgrade -y

# GoAccess: An Apache server log analyzer
# https://goaccess.io/
wget -O - https://deb.goaccess.io/gnugpg.key | gpg --dearmor | sudo tee /usr/share/keyrings/goaccess.gpg >/dev/null
echo "deb [signed-by=/usr/share/keyrings/goaccess.gpg arch=$(dpkg --print-architecture)] https://deb.goaccess.io/ $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/goaccess.list
apt-get update
apt-get install goaccess -y

# npkill: node_modules folder cleaner
npm install -g npkill

```

```bashrc
alias cp = cp -i # 覆盖文件时弹出确认提示
alias mv = mv -i # 覆盖文件时弹出确认提示
alias mkdir = mkdir -p # 当文件夹不存在时自动创建
```