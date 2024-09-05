# 讲解字典之前我们需要了解到一个知识点:映射 即键(索引)和值(数据)的对应
# 使用{}活着dict来创建字典 键值对用冒号表示
# {<键1>:<值1>,<键2><值2>,<键3><值3>}

d = {"中国": "北京", "美国": "华盛顿", "法国": "巴黎", "日本": "东京"}
print(d["中国"])
d1 = {}  # 生成一个空的字典 而不是集和

#  向字典中新增元素
d["俄罗斯"] = "莫斯科"  # 修改就直接是d["莫斯科"] = "基辅"

#  字典处理函数
del d["美国"]  # 删除字典中的美国
print(d)

#  in的使用
if "中国" in d:
    print("中国无敌！")

print("输出所有的keys:{}".format(d.keys()))
print("输出所有的values:{}".format(d.values()))
print("字典中所有键值对的信息:{}".format(d.items()))

#  获取建值对应的values
print("键值中国对应的values:{}".format(d.get("中国")))  # 这个只是访问，而下面的pop则是去除
print("键值日本将消失的values:{}".format(d.pop("日本")))

#  d.clear() 清空   len(d)返回字典中键值对的个数
print("现在键值对为:{}".format(d))
print("键值的对数还剩:{}个".format(len(d)))