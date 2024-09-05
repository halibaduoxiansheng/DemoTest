# 安装
# pip install bs4 -i 汽车之家

import re
import requests
import csv
from bs4 import BeautifulSoup

url = "http://www.xinfadi.com.cn/index.html"
headers = {
        "user-agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36"
}
resp = requests.get(url, headers=headers)
# print(resp.text)

# 开始解析
# 生成bs对象
page = BeautifulSoup(resp.text, "html.parser")  # 指定为html
# 从其中获取数据
# find 找出第一个 find(标签, 属性=值)
# find_all 找出所有 find_all(标签, 属性=值)
# 当发现class是pyton自带的关键字时可以采用class_代替使用
# table = page.find("div", class_="tbl-body")
# 下面这行代码与上面那行代码一模一样的意思
table = page.find("div", attrs={"class": "tbl-body"})
print(table)
# 从这去学 https://www.bilibili.com/video/BV1bL4y1V7q1?p=30&spm_id_from=pageDriver&vd_source=430b320228f8543528f8913267b412ec
