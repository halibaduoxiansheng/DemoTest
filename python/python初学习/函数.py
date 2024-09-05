# 其实函数就是一端可重用的语句组 表达特定的功能
# def <函数名>(参数):
#     <函数体>
#     return <返回值>

# 函数没有没调用是不会起作用的

# def f1(): # 无参参数
#     print("I am a function too !")
# f1()

# 在传入参数时，如果没有传入可选参数,那么可选参数的值就按函数给出的算,所以可循参数需要初始化
# def f2(<必有参数>, <可选参数>): # 顺序不能错
#     <函数体>

# 可变参数传递
# def f3(<必有参数>,*<可变参数>):
#     <函数体>

# def f3(a, *b):
#     c = 1
#     for i in range(1, a+1):
#         c *= i
#     for item in b: # b就是一个列表
#         a *= item
#     return a
# print(f3(2, 2))
# print(f3(2, 2, 3))

# 交换两个值 返回多个值 元组类型(1, 2) 列表类型[1, 2]
# def change(x, y):
#     return y, x
# a = 1
# b = 2
# a, b = change(a, b)
# print("a={},b={}".format(a, b))

# 全局变量和局部变量与其余语言一样
# 也可以在函数里面定义全局变量
# c = 1
# def f3():
#     global c  # ☞这个c为外部的那个全局变量,同时这个不能赋予初始值
#     return c
# print(f3())

# 列表 就是指针的概念
# 如果没有创建实例,那么就不能太

# ls = ['1', '2']
# def func():
#     ls = ['3', '4']  # 在这被真实创建了,那么就为局部变量
#     for i in range(0, 2): # 如果没有上面这行代码,那么ls还是第一行的列表 如果修改数据,会修改
#         print(ls[i])
# func()
# print(ls)

# lambda()函数
# 一种匿名函数(即没有名字的函数) 函数名是函数返回值
# f = lambda x, y : x + y
# print(f(1, 2))

# f = lambda : "我不用print就可以输出,而且没有参数"


