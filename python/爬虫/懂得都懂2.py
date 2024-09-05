# 拿到页面圆的代码

# 乱码的问题就是python的内部编码方式都是utf-8，随意无论处理什么都会先转化为UTF-8，然后再转化为你要的编码方式输出

import requests
import re
import csv
# csv文件的模块
import requests
import io
import sys
# for j in range(0,250)
# url = "https://movie.douban.com/top250"

# str2 = input("你需要查找什么内容")
for it in range(2, 10, 1):
    # if it == 8 or it == 11 or it == 16 or it == 22 or it == 23 or it == 25:
    #     continue
    it = str(it)
    # url = "https://www.b3f9k.com/shipin/list-中文字幕-"+it+".html"
    # url = "https://www.d298d65472ae.com/shipin/list-%E4%B8%AD%E6%96%87%E5%AD%97%E5%B9%95-"+it+".html"
    url = "https://www.toutoupa.com/videolist/3-"+it+".html"
    headers = {
        "user-agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36"
        # "user-agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36"
    }
    # proxies = {
    #     "http": "http://1.192.218.106:9999"
    #     # "https":"https://192.168.0.1:80"
    # }
    res = requests.get(url, headers=headers)
    # res.content.decode("utf8", "ignore").encode("gbk", "ignore")
    # res.encoding = 'utf-8'
    page_content = res.text
    # obj = re.compile(r'<li>.*?<div class="item">.*?<span class="title">(?P<name>.*?)</span>.*?<p class="">.*?<br>(?P<year>.*?)&nbsp;.*?<span class="rating_num" property="v:average">(?P<score>.*?)</span>'
    #                  r'.*?<span>(?P<people>.*?)人评价</span>', re.S)
    obj = re.compile(r'<(?P<name1>.*?)h.*?>', re.S)
    result = obj.finditer(page_content)
    # a为追加,w会清空原来的再写入
    f = open("dat.txt", mode="a", encoding="utf-8")
    csvwriter = csv.writer(f)
    for it in result:
        # print(it.group("name"))
        # 恰逢数据前面是一堆空格，就使用strip()
        # print(it.group("year").strip())
        # print(it.group("score"))
        # print(it.group("people"))
        dic = it.groupdict()
        # dic['year'] = dic['year'].strip()
        csvwriter.writerow(dic.values())
    f.close()
print("over!")