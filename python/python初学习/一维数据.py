# 数据组织的维度
# 例如 一维数据 与 二维数据 的不同

# 一维有序数据  -> 列表
List = ["你", "好", "world"]
print(List[0])  # 就是c里面的数组


# 一维无序数据  -> 集和  数据不能重复
st = {"你", "好", "world"}
print(st)
if "你" in st:
    print("ok")


# 一维数据的存储  用空格、逗号分割(有缺点) 或则其它的符号

ls = ["中国", "美国", "俄罗斯"]
f = open("2.txt", "a+")
f.write(' ');
f.write(' '.join(ls))
f.close()
