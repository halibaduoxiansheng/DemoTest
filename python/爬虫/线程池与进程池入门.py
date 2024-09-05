# 线程池: 一次性开辟一些线程池，我们用户直接向线程池提交任任务

# import requests
#
# resp = requests.post("http://www.xinfadi.com.cn/getCat.html")
#
# print(resp.text)

from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

def fun(name):
    for i in range(1000):
        print(name, i)

if __name__ == '__main__':
    # 创建线程池(50个的)
    with ThreadPoolExecutor(50) as t:
        for i in range(100):
            t.submit(fun, name=f"线程{i}")
    # 会等待线程池中的全部任务完成才会继续
    print("123")
