#  1.通过python基础拿到contid
import requests

url = "https://www.pearvideo.com/video_1742141"
conDid = url.split("_")[1]  # split是将这个作为分割 下标从0开始的列表
# contid = url.strip("h")  # 该方法只能删除头部活或者尾部的
# print(contid)

#  在前面加上个f就能替换了
videoStatusUrl = f"https://www.pearvideo.com/videoStatus.jsp?contId={conDid}&mrd=0.2375479071459503"
# print(videoStatusUrl)

headers = {
    "User-Agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36",
    #  防盗链：就是需要知道当你访问这个页面时，你的上一个页面需要是原网页
    "Referer": url
}

resp = requests.get(videoStatusUrl, headers= headers)
# print(resp.text)  #  这里如果能正常输出说明没有反爬 但是不能 说明被反爬了
dic = resp.json()
# print(dic)
srcUrl = dic['videoInfo']['videos']['srcUrl']
systemTime = dic['systemTime']
srcUrl = srcUrl.replace(systemTime, f"cont-{conDid}")

# print(srcUrl)  #  这一步已经搞到videos的路径并且还是能打开的地址
#  接下来就是去下载视频了
with open("视频.mp4",mode="wb") as f:
    f.write(requests.get(srcUrl).content)