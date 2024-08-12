# 首先

下载安装配置环境

官方教程：[Git 教程 | 菜鸟教程](https://www.runoob.com/git/git-tutorial.html)
如果在命令提示符下 输入  git --version 显示版本号

![](C:\Users\dell\AppData\Roaming\marktext\images\2024-08-12-19-10-52-image.png)

# 图理解

![](C:\Users\dell\AppData\Roaming\marktext\images\2024-08-12-19-11-52-image.png)

# 使用范例

### 创建本地仓库

![](F:\MarktextPhoto\2024-08-12-19-39-31-image.png)

### 先添加到暂存区，再添加到本地仓库中，上传远程仓库并合并

```
git add . # 所有文件、增加到缓冲区
git commit -m "first time" # 添加到本地仓库
git remote add origin https://github.com/halibaduoxiansheng/DemoTest.git #指明远程仓库
git push -u origin master # 增加到主分支，第一次需要密码验证
```

### 之后更新提交

```
git add . # 因为你无法拿准自己修改了哪些，所以一般都是 再次提交所有 
git commit -m "second time"
git push # 即可
```

分支的概念

如果你下次提交的远程分支继续是上次的，那么直接

```
git push
```

如果需要添加到另一个分支

```
git push -u origin develop
```

### 配置

```
git remote -v
```

显示图

![](F:\MarktextPhoto\2024-08-12-20-22-59-image.png)

**(fetch)** 和 **(push)**： 表示这个远程仓库分别用于从远程获取代码（fetch）和向远程推送代码（push）。

#### 修改配置

```
git remote set-url origin https://新的远程仓库地址
```

#### 增加配置

```
git remote add <新别名> <新的远程仓库地址>
```


