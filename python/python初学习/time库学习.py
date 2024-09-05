# time库的使用 计算机时间的表达
# 提供获取系统时间并格式化输出功能
# import time
# 再运用time.<b>()的形式
import datetime
# 三类函数
# 获取时间 time() ctime() gmtime()
# 时间格式化 strftime() strptime()
# 程序计时 sleep() perf_counter()  很重要

# 获取当前时间戳,即计算机内部时间值 浮点数
# time.time() # 是指从1970年1月1日0时开始到当前为止 单位：秒
# time.ctime() # 就比较好读取 返回的是一个字符串
# time.gmtime() # 生成的是计算机可以处理的时间格式(struct_time格式)

# import time  # 尽量用大写的字母,小写的不太好 import datatime
# t = time.gmtime()
# datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
# print(time.strftime("%Y-%m-%d %H:%M:%S", t))

# 以下就死互补关系了
# import time
# str = "2022-12-19 07:53:53"
# print(time.strptime(str, "%Y-%m-%d %H:%M:%S"))

# 程序计时 perf_counter()
# 当个使用毫无意义,必须连续使用取差值才有效
# import time
# start = time.perf_counter()
# end = time.perf_counter()
# zhi = start - end
# print(zhi, end="")


# import turtle
# turtle.pencolor("red")
# turtle.write('年', font=('Arial', 18, "normal"))
# turtle.done()
