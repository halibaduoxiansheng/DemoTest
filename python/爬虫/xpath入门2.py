from lxml import etree



tree = etree.parse('b.html')
# result = tree.xpath('//body/ul/li[1]/a/text()')  # 在后面加上[x]表示第x个，从1开始
# result = tree.xpath("/html/body/ol/li/a[@href='dapao']/text()")  # 不要这个html

# print(result)

ol_li_list = tree.xpath("/html/body/ol/li")

# for li in ol_li_list:
    # 从每个li中提取到文字信息
    # result1 = li.xpath("./a/text()")  # 在li中继续查找 ./表示单前结点
    # print(result1)

    # 再找a标签里面的href的值
    # result2 = li.xpath("./a/@href")  # 直接用@href拿
    # result2 = li.xpath("./a/@class")  # 当然这就是class的值的提取方式
    # print(result2)
# print(tree.xpath("/html/body/ul/li/a/@href"))  # 也可以这样直接拿

# 小技巧  当页面机器复杂  用浏览器查看源码再右键可以copy xpath地址
# print(tree.xpath("/html/body/div[2]/text()"))
# 然后再微调可以活用了







