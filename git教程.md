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

## 实际工作中常用
```
git status # 查看当前修改了什么
git branch # 查看当前所处分支
git branch -d dev # 删除dev分支
git checkout dev # 切换到dev分支
git submodule update --init # 更新子模块
git log # 查看日志
git show <commit-id> # 查看具体修改了什么
git reset --hard # 丢弃所有本地修改
git clone -b dev # clone dev 分支的内容到本地
git remote -v # 查看当前仓库的地址
git pull # 获取最新内容到本地
git branch -r 或 git branch -a # 查看所有分支
```

## 最为常用的
```
git stash # 暂存所有本地修改数据
git pull # 更新为最新的服务器上代码
git stash pop # 恢复
```

## 提交代码
```
git checkout -b bugfix/描述 # 基于本分支创建新分支
git push # 提交
然后请求合并
```




## 以下为公司实际使用中所学
查看当前分支
git branch
切换分支
git checkout dev # 切换到dev分支
查看所有分支
git branch -r # 按q退出
基于当前分支创建分支
一般提交代码，是基于什么分支创建的，就请求合并到什么分支
git checkout -b feature/change_pd336_sdk_version
git checkout -b bugfix/fix_wifi_start_step
删除分支
注意：无法删除当前正处分支
git branch -d bugfix/fix_wifi_start_step
git branch -D bugfix/fix_wifi_start_step # 强制
创建分支
基于当前分支内容，复制一份，成为新的分支
git checkout -b bugfix/fix_wifi_start_step
同步服务器代码
git fetch
git pull
查看commit一致性
git log
查看当前git仓库
git remote -v
提交
将暂存区的内容提交到本地仓库
git commit -m "first commit"
推送
将本地仓库的提交推送到远程仓库
git push 
同步代码
挑选一个 commit 应用到当前分支，如果有歧义，会提示
git cherry-pick <commit-id>
下载代码
git clone -b master <repository> #当然，其中的-b master 可以不用
修改未合并的代码 小修改 GIT(不增加新的commit)
当已经提交合并的代码，有人提出问题且你对应修复后，为了步增加一个commit，可以直接
git reset --soft HEAD~1 # 选用，撤销上个提交

git reset <commit-id> # 回复到某一个代码
然后对新生成的进行修改
git add .
git commit --amend
git push -f
修改未push的commit的备注内容
git commit --amend
回到过去的某个修改，且强制修改
谨慎使用，强制修改会将本地的修改全部丢弃，且无法恢复
git reset --hard <commit-id>
切换其余分支或commit，但又需要保存本地修改的
git stash push -m "commit reason"
git stash list # 打印所有暂存
git stash pop stash@{1} # 弹出第一个修改,并删除这个
git stash apply pop stash@{1} # 弹出第一个修改
git stash drop stash@{1} # 删除第一个修改
git stash clear # 清除所有

强制恢复，将未提交的commit丢弃
git reset --hard origin/release/v2.2.0 
撤销提交
git reset --soft HEAD^ # 改动还在工作区
git reset --hard HEAD^ # 彻底回到上个提交的状态
git reset --soft HEAD~3 # 回退最近3个提交，但是仍然保留修改
删除分支
git push origin --delete feature/test # 删除远端分支
git branch -D feature/test # 删除本地分支
变换到某commit-id
git reset --hard <commit-id>
或则
git checkout <commit-id>
git rev-parse HEAD # 查看当前commit-id
显示默认分支
git remote show origin
遇到无法撤销的暂存
git reset HEAD . # 直接取消所有暂存


