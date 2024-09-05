# 实例一：计算圆的面积
# 可以看到可以约束好输出数据的小数点位数
# r = 2.5
# area = 3.1415 * r * r
# print(area)
# print("温度是{:.2f}".format(area))
# 或则也可以写成 print("温度是：",area)
# print("温度是{},{}".format(area, r))
# {}充当一个槽 format为固定的向其中填入数据
# 也可以写成不做小数约束的形式 print("温度是:{}".format(area))

# 温度装换
# 规律：摄氏度C 华氏度F F = C * 1.8 + 32
# 缩进 ：语法程序表示框架 python特用

# 注释 单行直接用： # 而多行注释就使用： ''' 多行代码or文字 '''
# 变量与其它语言一样通用

# 不同于其它语言，python支持中文做变量
# 你好 = "hello world"
# print(你好)

# 区分大小写 不能以数字开头命名

# python的数组有种不同的反向下标 从-1开始递减
# 切片操作 返回一个字符串的一个子串
# [1:3] 取出下标为1到2的字符，不包括下标为3的那个字符
# str = "1234"
# print(str[0:3])

# 列表类型 ['1', '2'] 数据之间用逗号隔开
# str = "abcd"
# str[-1] in ['d', 'D']
# 如果上面的语句是真值，那么就会返回Ture, 否则返回False


# python用or and not 表示逻辑的

# 字符串从左下标开始是0，但是从右边开始是-1
# 切片 [x: y: z] 左闭右开 z为步长，默认为1(即递增基数) [-3:-1] [1:3] [-2::](同[-2:])等
# 逆序输出 str[::-1]

# Tempstr = input("请输入：")
# if Tempstr[-2:] in ["ok", "OK", "Ok", "oK"]:
#     print("good!")

# if同用 else if 在python用elif else 同用

# 冒号 每个保留字后面都会有一个冒号 为语法的一部分

# 函数 <函数名>() like: print() input() eval()等
# eval() 作用：去除放入其中的字符串的最外侧两边的双引号， 例如 eval("1") 就会产生数字1

# for i in range(0, 12):
#     print(chr(9800+i))

# str = "DWDdwsds"
# print(str.lower())
# str="a,b,c,d"
# print(str.split())

# str = "abcdefg"
# print(str.center(10, "="))

# print("abc def g".strip("a "))
# print("abc def".replace(" ", ""))

# print("p".join("abc"))
# print("{0:,.2f}".format(123455667.43523))
# print(round(3.45, 1))

