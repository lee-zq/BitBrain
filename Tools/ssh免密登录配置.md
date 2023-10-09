1. 创建密钥对（在~/.ssh下）
ssh-keygen -t rsa -C "你的登录邮箱"

2. 设置公钥  
cd ~/.ssh  
cat id_rsa.pub >> authorized_keys用于配置服务器远程登录
或者在github创建新的SSH keys并粘贴公钥id_rsa.pub用于git免密操作

3. 私钥保存在本地~/.ssh下，也可拷贝到其他机器使用，可用于vscode远程连接服务器 或者 免密push
4. vscode配置ssh免密:
```  
Host 192.168.0.123_主机
    HostName 192.168.0.123
    User root
    Port 22
    IdentityFile C:\Users\Lee\.ssh\id_rsa
```
5. option 在任意目录下执行`ssh -vT git@github.com`测试ssh设置是否成功
   `Hi lee-zq! You've successfully authenticated, but GitHub does not provide shell access.`表示成功

PS: 1.如果报错“git@github.com: Permission denied (publickey)”. 可能是创建密匙对的时候重命名了密钥名称，导致测试时没找到对应的私钥，建议使用默认的创建试试
