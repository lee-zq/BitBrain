1. 创建密钥对（在~/.ssh下）
ssh-keygen -t rsa -C "你的登录邮箱"

2. 设置公钥
cd ~/.ssh
cat id_rsa.pub >> authorized_keys
或者在gitlab创建新的SSH keys

3. 私钥保存在本地，可用于vscode远程连接 或者 免密push

4. option 在git仓库目录下执行`ssh -T git@github.com`刷新ssh设置