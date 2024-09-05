# ：爬虫：通过书写程序去获取网络数据
# import urllib.request

# from urllib.request import urlopen  # 引入库
#
# url = "http://www.baidu.com"  # 百度首页地址
# resp = urlopen(url)  # 另外一种引入库的话就得是urllib.request.urlopen
# content = resp.read()  # 读取网页内容
# print(content)  # 输出网页源代码
# resp.close()  # 关闭连接
#
#
# with open("mybaidu.html", mode="w", encoding="utf-8") as f:
#     f.write(resp.read().decode("utf-8"))  # 读取到页面源代码
# print("over!")



import requests

# url = 'https://www.baidu.com/'
# response = requests.get(url)
#
# # 获取到百度首页的源代码
# content = response.text.encode('utf-8')
# print(content.decode('gbk', errors='replace'))

url = 'https://www.csdn.net/'
resp = requests.get(url)
# resp.encoding = 'UTF-8'
print(resp)  # <Response [200]> 代表成功响应
print(resp.request)  # 返回请求方式
# resp.encoding = 'utf-8'
print(resp.text)  # 文本形式输出 拿到页面源代码
# print(resp.content)

