# 定位到某某框架里面，再在这里定位到子链接的地址
import csv
import requests
import re

domain = "https://www.dytt8.net/index2.htm"
resp = requests.get(domain, verify=False)  # verify = False 去掉安全验证
resp.encoding = 'gb2312'  # 指定字符集
# print(resp.text)

# 开始提取阶段
obj1 = re.compile(r'2022新片精品.*?<ul>(?P<ul>.*?)</ul>', re.S)
obj2 = re.compile(r']<a href=\'(?P<href>.*?)\'', re.S)
obj3 = re.compile(r'◎译　　名(?P<movie>.*?)<br />.*?<a target="_blank" href="'
                  r'(?P<download>.*?)">', re.S)
result1 = obj1.finditer(resp.text)
child_href_list = []
for it in result1:
    ul = it.group('ul')
    # print(ul)
    result2 = obj2.finditer(ul)
    for itt in result2:
        # 拼接地址
        # 下面本来可以是有domain，可是我用不来，需要删减东西现在会了
        domain1 = domain[0:21:1]
        child_href = domain1 + itt.group('href')
        # child_href = "https://www.dytt8.net" + itt.group('href')  # 如果需要删除某个字节 .strip('c') c为字节
        # print(itt.group('href'))
# 定位成功 拿到了想要的url了 然后就是拿到子链接了
        child_href_list.append(child_href)  # 放入到列表里面

# 提取子页面
for href in child_href_list:
    child_resp = requests.get(href, verify=False)
    child_resp.encoding = 'gb2312'
    # print(child_resp.text)
    # result3 = obj3.search(child_resp.text)
    page_content = child_resp.text
    result3 = obj3.finditer(page_content)
    f = open("data.csv", mode="a")
    csvwriter = csv.writer(f)
    for it in result3:
        dic = it.groupdict()
        csvwriter.writerow(dic.values())
    f.close()
    # print(result3.group("movie"))
    # print(result3.group("download"))
    # break
    # 子页面的源代码已经到手，还有什么难的呢？
print("over!")

