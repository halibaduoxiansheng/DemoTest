from lxml import etree
import requests

url = "https://shangrao.zbj.com/search/f/?type=new&ke=saas&r=2"
resp = requests.get(url)
# print(resp.text)

# 解析
html = etree.HTML(resp.text)
divs = html.xpath("html/@lang")  # 不再源码中，这里的源码指的是查看源码，而不是检查
print(divs)
# for div in divs:
#     price = div.xpath("./div[1]/div[2]/div[1]/span/text()")
#     print(price)
# print(html.xpath("/html/body/div[2]/div/div/div[3]/div/div[4]/div[4]/div[1]/div[1]/div/div[2]/div[1]/span/text()"))
price = div.xpath("./div[1]/div[2]/div[1]/span/text()")[0].strip()  # 默认的为去除空格
#  比如[0].strip("￥")  #  就是去除￥
