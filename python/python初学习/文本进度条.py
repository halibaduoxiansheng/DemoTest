# import time
# scale = 10
# print("------执行开始------")
# for i in range(scale+1):
#     a = '*' * i
#     b = '.' * (scale-i)
#     c = (i / scale)*100
#     print("\r{:^3.0f}%[{}->{}]".format(c, a, b), end="")
#     time.sleep(0.3)
# print("\n------执行结束------")

# 数递增
# import time
# for i in range(100):
#     print("\r{}".format(i), end="")
#     time.sleep(0.4)

# 百分号递增
# import time
# for i in range(101):
#     print("\r{:^3.0f}%".format(i), end="")
#     time.sleep(0.1)