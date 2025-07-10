# 首先

（插入：MarkText插入图片：![Alt text](F:\MarkTextProject\photo\2024-08-23-17-47-10-image.png)

下载安装配置环境

官方教程：[Git 教程 | 菜鸟教程](https://www.runoob.com/git/git-tutorial.html)
如果在命令提示符下 输入  git --version 显示版本号

[.\photo\2024-08-19-17-49-47-image.png]()

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
# 注意此处也有另外一种 SSH的方式 成功率更高 配合github浏览器端设置SSH，
git remote add origin git@github.com:halibaduoxiansheng/Repository/DemoTest.git
git push -u origin master # 增加到主分支，第一次需要密码验证
```

### tips
```
编写 .gitignore 文件
**/build/
*.o
*.a
*.elf
*.map
*.bin
*.hex
*.log
**/gen/
*.d
然后git add . 防止 git add 失败
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
git remote add <新别名> <新的远程仓库地址> # git remote add origin ...
```

#### 增加SSH

[git创建远程仓库并上传代码到远程仓库中-CSDN博客](https://blog.csdn.net/liuweixiao520/article/details/78971221)
参考这篇文件，这可以保证每一次的上传到远程仓库能够成功。
```
ssh-keygen -t rsa -C "halibaduoxiansheng@gmail.com"
```
不想跳转，就是这个，然后一路回车，将终端提示位置下的id_rsa.pub内的内容复制到github网页下的Setting->SSH下新增的里面，确认即可

#### 删除配置的远程仓库

```
git remote rm <仓库名>
```

#### 创建新的分支并切换到该分支

```
git checkout -b <branchname>
```

#### 切换分支

```
git checkout <branchname>
```

#### 查看分支

```
git branch # 查看本地分支
git branch # 查看远程分支
git branch -a # 查看所有分支
```

#### 查看提交版本

```
git log -n num # 只显示num条
```

![](F:\MarktextPhoto\2024-08-14-11-56-10-image.png)

### 如果是在新电脑上的编辑，而且本地版本还要高于github的版本可以：
```
git push -f origin master #有冲突会提示
```
### 然后
```
git push origin master # 提交
```
### 获取可以一开始就直接强制提交
```
git push -f origin master
```
## 传输大的文件
#### 首先：
```
https://git-lfs.com/
```
下载安装，然后
```
git init / git lfs install / git lfs track "*.cab" # replace your file / git add * / git commit -m "ok" / git push -f origin master、
```
固定下载某一分支
git clone -b master <repository_url>

#### 如果是移动后SSH失效
先重新走一遍ssh流程，然后类似像下面的设置一遍，就行了
```
git remote set-url origin git@github.com:halibaduoxiansheng/new_smartbrush.git
```
### 回退版本
##### 先:
```
git log # 找到你想要回退到的版本的 commit ID
```
#### 后
```
git reset --hard <commit_id> # ：将 HEAD 指向指定的提交，并同时修改暂存区和工作目录，使其与指定的提交完全一致。这会丢失回退点之后的所有提交，请谨慎使用。
git reset --mixed <commit_id> # ：将 HEAD 指向指定的提交，并修改暂存区，但保持工作目录不变。这会保留工作目录中的修改，但会将回退点之后的提交从暂存区中移除。
git reset --soft <commit_id> # ：将 HEAD 指向指定的提交，但保持暂存区和工作目录不变。这会保留工作目录和暂存区中的所有修改，并将回退点之后的提交标记为未提交的更改。
git revert <commit_id> # ：创建一个新的提交，撤销指定的提交所做的更改。Git 会自动打开一个编辑器，让你输入提交信息。
git checkout <commit_id> # ：将 HEAD 指向指定的提交，并将工作目录修改为该提交的状态。这会将你的工作目录置于“分离 HEAD”状态，这意味着你不在任何分支上。
```


## github 增加子模块
```
# 用于提交大内容文件 从而拆分
cd ..
cd bk_avdk
git init
git submodule add git@github.com:halibaduoxiansheng/Bo_Tong_idk.git bk_idk
git add .gitmodules bk_idk
git commit -m "add bk_idk submodule"
git remote add origin git@github.com:halibaduoxiansheng/Bo_Tong_avdk.git
git push -u origin master
```

## 提示User 不对
```
# 类似这种做法
git config --global --add safe.directory "D:/i4season_BoTong/armino/bk_aidk/bk_aidk" 
```

