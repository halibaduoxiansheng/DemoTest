# 脚本语言 不需要编译器，而脚本语言直接边解释边执行
# 学习每一种语言都差不多是从下面这条语句开始的
# 基本上很多种的软件都是ctrl+/是注释和反注释
print("hello world!")

# 可以看得出range不设定的话默认是+1递增
# 默认数据之间用,隔开 然后用空格隔开会更加好看
for it in range(0, 4):
    print("2")

# IPO I：input P:process O：output

for i in range(5):
    print(i)
# 可以发现打印的是0到4 5个数字

for i in range(1, 5):
    print(i)
# 可以发现输出的为1 ，2， 3， 4 但是不包括5

# range(start, end, 步长)
for i in range(1, 10, 2): # 同理于for(int i = 1; i < 10; i = i+2)
    print(i)

print("^", "你还", "骂我", "好")  # 就是会在,的地方输出时会自动加上一个空格
print("{}那可以{}".format("好的", "好多"))

for i in range(12):
    print(i, end=" ")


