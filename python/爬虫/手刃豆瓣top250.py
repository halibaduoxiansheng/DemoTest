# 拿到页面圆的代码
import requests
import re
import csv
# csv文件的模块

# for j in range(0,250)
# url = "https://movie.douban.com/top250"
for str1 in range(0, 226, 25):
    str2 = str(str1)
    url = "https://movie.douban.com/top250?start="+str2+"&filter="
    headers = {
        "user-agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36"
    }
    res = requests.get(url, headers=headers)
    page_content = res.text
    obj = re.compile(r'<li>.*?<div class="item">.*?<span class="title">(?P<name>.*?)</span>.*?<p class="">.*?<br>(?P<year>.*?)&nbsp;.*?<span class="rating_num" property="v:average">(?P<score>.*?)</span>'
                     r'.*?<span>(?P<people>.*?)人评价</span>', re.S)
    result = obj.finditer(page_content)
    # a为追加,w会清空原来的再写入
    f = open("data.csv", mode="a", encoding='utf-8')
    csvwriter = csv.writer(f)
    for it in result:
        # print(it.group("name"))
        # 恰逢数据前面是一堆空格，就使用strip()
        # print(it.group("year").strip())
        # print(it.group("score"))
        # print(it.group("people"))
        dic = it.groupdict()
        dic['year'] = dic['year'].strip()
        csvwriter.writerow(dic.values())

    f.close()
    # print("over!")