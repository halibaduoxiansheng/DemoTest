# 拿取主页面的源代码，再进入子页面提取所需的东西
# 谨记:网页会更新，源代码查看太久了要重新查看！！！

import requests
from bs4 import BeautifulSoup
import time

url = "https://www.umei.cc/bizhitupian/"
resp = requests.get(url)
resp.encoding = "utf-8"
# print(resp.text)
# 源代码成功获取到，之后开始将源代码交给BeautifulSoup
main_page = BeautifulSoup(resp.text, "html.parser")
# # find 找出第一个 find(标签, 属性=值)
# # find_all 找出所有 find_all(标签, 属性=值)
# # 以下就是说找出所有这个div里面的所有a便签
alist = main_page.find("div", class_="Clbc_top").find_all('a')
# print(alist)
i = 1
for a in alist:
    if i >= 5:
        href = "https://www.umei.cc" + a.get('href')  # 直接通过get就可以拿到属性的值
        # print(href)
        # 拿到子页面的源代码
        child_page_resp = requests.get(href)
        child_page_resp.encoding = 'utf-8'
        child_page_text = child_page_resp.text
        # # # 从子页面拿到图片的下载途径
        child_page = BeautifulSoup(child_page_text, "html.parser")
        p = child_page.find("div", class_="big-pic")
        img = p.find("img")
        src = img.get("src")
        # 图片地址已经成功拿到了，接下来就是下载
        img_resp = requests.get(src)
        # img_resp.content  # 内容 这里拿到的是字节
        img_name = src.split("/")[-1]  # 拿到url最后一个/以后的所有内容
        with open("img/"+img_name, mode="ab") as f: # 将下载的图片放入img文件夹中
            f.write(img_resp.content) # 图片内容写入文件
        print("over", img_name)
        time.sleep(1)  # 建立休息一秒左右，防止被ip禁止访问
    else:
        i = i + 1
print("all over!")
# 选择需要放入的文件夹，再右键选择Mark directory as 再选择clude 才能支持下载多个图片
