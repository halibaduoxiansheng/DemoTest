# BMI = 体重(kg) / 身高^2(米^2);
try:
    # tizhon = eval(input("请输入您的体重:"))
    # shengao = eval(input("请输入您的身高:"))
    tizhon, shengao = eval(input("请输入您的体重(kg)和身高(米)(逗号分割):"))
    BMI = tizhon / (pow(shengao, 2))
except:
    print("输入的信息有误")
else:
    print("您的BMI值为:{:^6.2f}".format(BMI))
    if BMI < 14:
        print("???逗我玩呢？")
    elif (BMI < 18.5) and (BMI >= 14):
        print("您偏瘦哦！建议多补充营养！")
    elif (BMI >= 18.5) and (BMI <= 24):
        print("您的身体非常健康,请继续保持!")
    elif (BMI > 24) and (BMI <= 28):
        print("您的身体偏胖,可以稍微注意饮食哦！")
    elif BMI > 28:
        print("您的身体太肥胖了,你个死肥猪,快减肥！！！")
finally:
    print("祝你生活愉快~")