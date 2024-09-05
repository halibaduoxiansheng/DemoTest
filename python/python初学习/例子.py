# import turtle
# turtle.setup(600, 400, 300, 300)
# turtle.pensize(5)
# # turtle.rgb(1, 1, 1)
# turtle.color("red")
# turtle.seth(45)
# turtle.fd(40)
# turtle.circle(20, 360)
# turtle.circle(-50,-360)
# turtle.fd(40)
# turtle.done()

# for i in range(1, 5, 1):
#     print(i)
# a = "abc"
# b = "def"
# c = a + b
# print(c)

# a = "abc"
# n = 2
# a = n * a
# print(a)
# str = "abc"
# print(str[-1])
# print(ord('1'))
# print(chr(49))

# a = 2.3
# b = 1
# c = a - b
# print(round(c, 1))

# import time
# for i in range(100):
#     print("\r{}".format(i), end="")
#     time.sleep(0.4)

# def jisuan(x):
#     sum = 1
#     for i in range(1, x+1, 1):
#         sum *= i
#     return sum
# y = eval(input("please input a value:"))
# k = jisuan(y)
# print("{}的阶乘为:{}".format(y, k))

# def f1(a, b = 2):
#     c = a * b
#     return c
# print(f1(2,3))

# for i in [1, 2]:
#     print(i)

# def change(x, y):
#     return y, x
# a = 1
# b = 2
# a, b = change(a, b)
# print("a={},b={}".format(a, b))

# ls = ['1', '2']
# def func():
#     # ls = ['3', '4']  # 在这被真实创建了,那么就为局部变量
#     for i in range(0, 2): # 如果没有上面这行代码,那么ls还是第一行的列表 如果修改数据,会修改
#        ls[i] = 3
# func()
# print(ls)
# print(1) if False else print(2)

# c = 'a'
# c = c * 3
# print(c)
# str = "abcdefg"
# print(str.split("c")[-1])

# str = "dabcd"
# print(str[0].strip("d"))  # 只删除头尾的字符c

# str = "a1b1c1d"
# str1 = str.split("1")
# print(str1)

# def print_hi(name):
#     print(f'hello,{name}')
#
# if __name__ == '__main__':
#     print_hi('lingxingjian')
# print("hello")