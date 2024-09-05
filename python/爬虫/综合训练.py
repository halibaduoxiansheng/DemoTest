# 源代码与框架源代码
import requests

url = "https://music.163.com/weapi/comment/resource/comments/get?csrf_token=e5c4959db762f6e8bede80755b6d17bc"
headers = {
    "referer": "https://music.163.com/song?id=1325905146",
    "user-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Safari/537.36"
}
resp = requests.post(url, headers=headers)
print(resp.text)

# 听不懂 跳过了
