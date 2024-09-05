import re

# findall 匹配字符串中所有符合正则的内容
# lst = re.findall(r"\d+", "我的电话号是：10086,我女朋友的电话号是：10000")

# print(lst)
# finditer 匹配字符串中所有满足的内容，但是返回的是迭代器
# it = re.finditer(r"\d+", "我的电话号是：10086,我女朋友的电话号是：10000")
# for i in it:
#     print(i)
# 下面的输出结果完全不一样
# 从迭代器中拿到内容需要.group()
# for i in it:
#     print(i.group())


# 返回的是match对象,需要返回数据也是需要.group()
# search全文搜索，只要找到就直接返回了
# s = re.search(r"\d+", "我的电话号是：10086,我女朋友的电话号是：10000")
# print(s.group())


# match是从头开始匹配 头不是
# s = re.match(r"\d+", "我的电话号是：10086,我女朋友的电话号是：10000")
# print(s.group())

# 预加载正则表达式
# obj = re.compile(r"\d+")
#
# ret = obj.finditer("我的电话号是：10086,我女朋友的电话号是：10000")
# for it in ret:
#     print(it.group())

s = """
<div class="jay"><span id="1">郭麒麟</span></div>
<div class="jo"><span id="2">马云</span></div>
<div class="jer"><span id="3">马化腾</span></div>
<div class="ok"><span id="4">王健林</span></div>
"""

# re.S让.能匹配换行符
# ()先括起来,再?P<正则名字>
obj = re.compile(r"<div class=\".*?\"><span id=\"(?P<wa>.*?)\">(?P<wahaha>.*?)</span></div>",re.S)
ret = obj.finditer(s)
for it in ret:
    print(it.group("wahaha"))
    print(it.group("wa"))