import requests

url = " https://movie.douban.com/j/chart/top_list?type=24&interval_id=100%3A90&action=&start=0&limit=20"

# 重新封装参数
# print(resp.request.url)
# 爬虫如果没有效果，那么就是被反爬了
# 第一个就该尝试user-Agent

headers ={
    "User-Agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36"
}

resp = requests.get(url=url, headers=headers)

# print(resp.request.headers)
# 会知道不设置的话那么这个将会是什么配置
# print(resp.text)
# 上面那个格式看着不太舒服
print(resp.text)

resp.close()  # 需要关闭
