# weeknameprint.py
weekStr = "星期一星期二星期三星期四星期五星期六星期天"
weekId = input("请输入(1-7):")
weekId = eval(weekId[-1])   # 记住 字符串在前面
ps = (weekId-1) * 3
print(weekStr[ps: ps+3])


# 其实下面的代码更加简洁
Str = "一二三四五六日"
weekId = eval(input("请输入(1-7):"))
print("是星期"+Str[weekId-1])
