# 安装
# pip install bs4 -i 汽车之家

import re
import requests
import csv
from bs4 import BeautifulSoup

url = "http://www.xinfadi.com.cn/getCat.html"
headers = {
        "user-agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36"
}
resp = requests.get(url, headers=headers)
print(resp.text)
page_content = resp.text
obj = re.compile(r'{"id":1379195,"prodName":"(?P<name1>.*?)"'
                 r'.*?prodName":"(?P<name2>.*?)"'
                 r'.*?prodName":"(?P<name3>.*?)"'
                 r'.*?prodName":"(?P<name4>.*?)"'
                 r'.*?prodName":"(?P<name5>.*?)"'
                 r'.*?prodName":"(?P<name6>.*?)"'
                 r'.*?prodName":"(?P<name7>.*?)"', re.S)
result = obj.finditer(page_content)
f = open("data1.csv", mode="a", encoding='gbk')
csvwriter = csv.writer(f)
for it in result:
        dic = it.groupdict()
        csvwriter.writerow(dic.values())
f.close()
# 开始解析
# 生成bs对象
page = BeautifulSoup(resp.text, "html.parser")  # 指定为html
# 从其中获取数据
# find 找出第一个 find(标签, 属性=值)
# find_all 找出所有 find_all(标签, 属性=值)
# 当发现class是pyton自带的关键字时可以采用class_代替使用

