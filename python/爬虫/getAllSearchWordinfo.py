import json
import time
import os

import requests
for i in range(1000):
    string = input("\n请输入你想要搜索的名词:")

    url = "http://119.29.15.48:12334/sssv.php?top=10&q=" + string

    #  我相当是差不多将整个头文件都搬进来了!
    headers = {
        "referer": "http://bumimi5.com/",
        "user-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36",
        "Connection": "keep-alive",
        "Host": "119.29.15.48:12334",
        "Origin": "http://bumimi5.com",
        "Pragma": "no-cache"
    }
    # proxies = {
    #     "http": "http://192.168.0.40:100"
    #     # "https":"https://192.168.0.1:80"
    # }
    # resp = requests.post(url, headers=headers, proxies=proxies)
    resp = requests.post(url, headers=headers)
    resp.encoding = 'utf-8'
    # print(resp.text)
    # 使用了json.dump()函数来将JSON数据写入文件
    with open("C:\\Users\\86199\\Desktop\\output.json", "a+", encoding="utf-8") as outfile:
        json.dump(resp.text, outfile, ensure_ascii=False)
        print('\r' + '10%', end='', flush=True)
        time.sleep(1)
        print('\r' + '20%', end='', flush=True)
        time.sleep(1)
        print('\r' + '40%', end='', flush=True)
        time.sleep(1)
        print('\r' + '60%', end='', flush=True)
        time.sleep(1)
        print('\r' + '100%', end='', flush=True)
        time.sleep(0.5)
