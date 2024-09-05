#  代理是灰色地带 所以懂得都懂
#  如何使用反爬虫
#  模拟浏览器登录 处理cookies
#  cookie就类似身份验证

#  登录 —> 得到cookie -> 带着cookie去访问
#  我们可以使用session进行请求 --> session可以认为是一连串的请求，而且在这过程中cookie不会消失

import requests

#  会话
session = requests.session()
data = {
    "loginName": "19914576362",
    "password": "HAHAHA123"
}

url = "https://passport.17k.com/ck/user/login"

resp = session.post(url, data=data)  # post还是get看源代码
# print(resp.text)
# print(resp.cookies)  # 看cookie
# 1.登录 2.拿数据

# 这里不要用request了，毕竟需要cookie，而使用session则是新的请求了
# resp1 = session.get("https://user.17k.com/ck/author/shelf?page=1&appKey=2406394919")
# print(resp1.text)  # 用resp1.json()

# 当然可以直接用requests
# resp2 = requests.get("https://user.17k.com/ck/author/shelf?page=1&appKey=2406394919", headers={"Cookie": "GUID=ebd3cbf1-595f-4efc-86bb-ac5b652ad98c; sajssdk_2015_cross_new_user=1; Hm_lvt_9793f42b498361373512340937deb2a0=1673249006; __bid_n=1859569a44b7346c5c4207; FPTOKEN=NRYqIRyvB+QD0JlavsOjkGGoTqrTbDZJA1tcKQ1MjxcK3eKjIFilaLPvC/fJ6JumGlFLupNP+vfxYV6kJJ77EMJyht9Z6wjpB5kBhMEBv7FW1iLxGAt+U8E7Nin8mG7vCiMoz9Agp1huEFbF7Yam/XOpP8mH3hEFnwziRfOBkWvu1KMoIohwri8oKyxrWO3nx2lBI8/vLHCu+srlVNoB45ImYJAOPNoMl4g1l7RiKKioZKSGY7gEZIqHS3IIhTlxBOoEYs/9AO/d4ChYOWJmXKrw3wwLqylZBjOgBR30yC0bmdrTRRZX/SKf/16PYekQBH2Ev0nXJ2IDJQo/J1LHLDVMsMCX/sIfxEfxS00sBdHFDT3x7XGV98S7mfWEwT5fkJLnNEbR1rQOFcdvxE6Q3A==|0RTd+2N3zsueJv0Se0HhHGGj7cJNY0QROi+zeaXld7k=|10|eda32364cd36ca34c2430fdc0ed56f31; c_channel=0; c_csc=web; accessToken=avatarUrl%3Dhttps%253A%252F%252Fcdn.static.17k.com%252Fuser%252Favatar%252F17%252F97%252F01%252F99880197.jpg-88x88%253Fv%253D1673249320000%26id%3D99880197%26nickname%3D%25E6%259D%25B0%25E5%2593%25A512305%26e%3D1688802141%26s%3D9a9b5272a4316c76; sensorsdata2015jssdkcross=%7B%22distinct_id%22%3A%2299880197%22%2C%22%24device_id%22%3A%2218595699cd65be-0f2a659e8af2f7-26021151-921600-18595699cd7421%22%2C%22props%22%3A%7B%22%24latest_traffic_source_type%22%3A%22%E7%9B%B4%E6%8E%A5%E6%B5%81%E9%87%8F%22%2C%22%24latest_referrer%22%3A%22%22%2C%22%24latest_referrer_host%22%3A%22%22%2C%22%24latest_search_keyword%22%3A%22%E6%9C%AA%E5%8F%96%E5%88%B0%E5%80%BC_%E7%9B%B4%E6%8E%A5%E6%89%93%E5%BC%80%22%7D%2C%22first_id%22%3A%22ebd3cbf1-595f-4efc-86bb-ac5b652ad98c%22%7D; Hm_lpvt_9793f42b498361373512340937deb2a0=1673250845"
# })
# print(resp2.text)