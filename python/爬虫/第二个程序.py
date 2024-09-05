import requests  # 在pip install requests

query = input("please input someone:")

url = f'https://www.baidu.com/s?ie=UTF-8&wd={query}'

dic = {  # 请求头信息 作用就是欺骗服务器让其认为本程序是一个人而非一个程序
    "User-Agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36"
}
resp = requests.get(url, headers=dic)


print(resp.url)
resp.close()

