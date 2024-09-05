# 是使用随机数 标准库之一
# 常用 seed(a = None) random()
# 也就是伪随机数 # 需要一个随机数种子
import random
random.seed(10)
a = random.random() # 产生0-1的数
print("{:.2f}".format(a))

# 扩展随机数函数
# randint(a,b) # random.randint(5,10)
# random.randrange(a, b, c) # a-b 步长为c
# random.getrandbits(a) # 生成一个比特长为a的数
# random.uniform(a, b) # 生成一个a到b的随机小数
# random.choice([1, 2, 34, 5, 6]) # 从列表中随机选出一个
# random.shuffle([1, 2, 3, 4, 5, 6]) # 打乱原本序列
