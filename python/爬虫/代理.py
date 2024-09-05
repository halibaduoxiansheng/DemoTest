#  代理
#  一般很少用 原理 通过第三方的机器去发送请求
import requests


# 36.137.208.16:7777

proxies = {
    "http": "36.137.208.16:7777"  # 看你需要访问的网站是需要http还是https 比如下面那个百度的
    # "https":
}

resp = requests.get("https://www.baidu.com", proxies=proxies)
resp.encoding = "utf-8"
print(resp.text)

