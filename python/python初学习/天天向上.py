# 一年365天，每天进步1%,那么一年后进步多少呢？
dayup = pow((1 + 0.01), 365)
print("还剩", dayup)
# 同理，每天退步1%,那么一年后是多少
daydown = pow((1 - 0.01), 365)
print("还剩{}".format(daydown))

