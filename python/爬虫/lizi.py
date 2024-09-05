# print("Hello World")

# 第五章

# 列表
# x1 = [1, "niah", 3, 4]
# print("列表:")
# for i in range(len(x1)):  # 别漏了range
#     print(x1[i])

# 元组
# x2 = (1, 1, "sa", 4)   # 元组是固定长度 而列表是动态长度
# print("元组")
# for i in range(len(x2)):
#     print(x2[i]);
# x2[5] = "hah1"  # 无效的

# x1 = [1, 2, 3]  #  x1 = (1, 2, 3)
# print(x1[-1])

# 切片 不包含右括号 与random类似
# x1 = [1, 2, 3, 4, 5]
# print(x1[1:3])  #  返回值 小 列表

# x1 = (1, 2, 3, 4)  #  返回值 小 元组
# print(x1[1:3])

# x1 = [1, 2, 3, 4, 5]
# print(x1[-3:3])   #  返回值 [3]
# print("--------")

# 字符串
# str = "bcdedit"
# print(str[1:4])

# x1 = [1, 2, 3, 4, 5]
# print(x1[3:])  # 下标为3到最后
# print(x1[:3])  # 下标0到2
# print(x1[:])   # 原样输出

# [begin_index, end_index+1, step]
# x1 = [1, 2, 3, 4, 5, 6, 7]
# print(x1[1:5:1])  # 等价于x1[1:5] 默认步长为1(记住:步长不能为0)
# print(x1[1::1])

# x1 = (1, 2, 3, 4, 5, 6, 7)
# print(x1[3::-1])  # 输出:(4, 3, 2, 1)

# 相互加减 --> 数列、元组、字符串
# x1 = [1, 2, 3]
# x2 = [4, 5, 6]
# x2 = x1 + x2
# for i in range(len(x2)):
#     print(x2[i])  # 输出1 2 3 4 5 6

# x1 = (1, 2, 3)  # 元组
# x2 = (4, 5, 6)
# x2 = x1 + x2
# for i in range(len(x2)):
#     print(x2[i])  # 这里不会报错 输出 1 2 3 4 5 6

# str = "wo" + "kao"
# print(str)
# print(not str)  # 输出false
# print((str))  # 即默认的括号被省去罢了

# 但请注意这三者不能混合乱来加减 只能同类别


# * 可以 ===== 重复 =====
# x1 = [1, 2]
# x1 = x1 * 2
# print(x1)  # 输出 [1,2,1,2] 没错,会重复

# x1 = (1, 2)
# x1 = x1 * 2
# print(x1)

# str = "wa"
# str = str * 2
# print((str))

# 成员资格 --> 关键字 in
# print("列表")
# print(1 in [1, 2, 3])   # 输出:True
# print(1 in (1, 2, 3))   # 输出:True
# print("a" in "happy")   # 输出:True

# 长度、最小值、最大值、求和
# x1 = [1, 2, 3, 4, 5]  # x1 = (1, 2, 3, 4, 5)
# print("如下", end="\n")
# print("x1的长度:{}".format(len(x1)))
# print("x1的最小值:{}".format(min(x1)))
# print("x1的列表求和:{}".format(sum(x1)))
# print("----------------------")

# str = 'abcdegf'
# print("字符串:")
# print("str的长度:{}".format(len(str)))
# print("str的最小值:{}".format(min(str)))  # 算出每个字符的ascii码求min\max
# print("str的最大值:{}".format(max(str)))

# 列表的更新 增 删 改 查
# x1 = [1, 2, 2, 3, 4]
# # 增
# x1.append(5)    # 无法指定具体加的位置 而且每次只能操作一个
# x1.extend([6, 7])   # 这个可以一下子增加好几个
# # 删
# x1.pop()    # 默认删除最后一个
# print(x1)  # 只是虚假的删除  仍旧保留了该位置
# # 也可以删除所有查询到的 使用关键字 --> del
# del x1[3]  # 真实删除
# print(x1)
# # x1.pop(3)   # 指定下标删除
# x1.remove(2)  # 锁定值删除,当有多个是值是值删除从左打右第一个
# print(x1)
# # 改
# x1[0] = "开始"
# print(x1)
# # 查 就懒得写了，真不会可以西内了
# print("‘开始’二字的位置:{}".format(x1.index("开始")))

# 反转
# x1 = [1, 2, 3, 4]
# print(x1[::-1])  # 输出 [4, 3, 2, 1]
# x1.reverse()    # 该方法没有返回值
# print(x1)    # 输出 [4, 3, 2, 1]


# count函数  作用:统计某个元素的个数
# x1 = (1, 2, 3, 4, 5, 5)
# print(x1.count(5))  # 输出:2
#
# str = "abcdefg"
# print(str.count('a'))   # 输出:1


# type函数 作用: 返回数据的类型
# x1 = (1, 2)
# x2 = [1, 2]
# str = "12"
#
# print(type(x1))  # tuple --> 元组
# print(type(x2))
# print(type(str))

# del
# x1 = (1, 2)
# x2 = x1
# del x1  # 仅仅是删除了x1,但x1的数据已经转变给了x2
# print(x2)

# 字典 --> 使用{}大括号 类似java map key_value
# city = {
#     "china": "beijin",
#     "美国": "纽约",
#     "英国": "伦敦"
# }
# print(city)
# print(city["china"])  # key就是下标
# # 字典的清空归零 与java一样,使用clear()函数
# city.clear()
# print(city)  # 输出{} not None

# english = {
#     "we": "我们",
#     "your": "你们",
#     "them": "他们"
# }
# english2 = english  # 复制
# english3 = english2.copy()
# print(english2, end="\n")
# print(english3, end="\n")

# fromkeys方法用于创建一个新的字典
# x1 = (1, 2, 3)
# student = dict.fromkeys(x1)
# print("不指定去默认值:{}".format(student))  # None
# # 那么使用默认值的是→
# student2 = dict.fromkeys(x1, "好的")  # 无法分别给每一个赋值
# # dict.fromkeys(x1,['1','2','3'])也只是给每一个都赋值:['1','2','3']
# print(student2)

# get函数
# dictla = {
#     'a': 1,
#     'b': 2,
#     'c': 3
# }
# print(dictla.get('a'))  # 使用key去锁定
# print(dictla.keys())  # 返回值:['a', 'b', 'c'] 列表java采用的是keyset() value是values
# print(dictla.values())
# print(dictla)   # {'a': 1, 'b': 2, 'c': 3}
# print(dictla.items())   # [('a', 1), ('b', 2), ('c', 3)] 将元组封装在列表中

# 数据大小
# c语言 sizeof(……)   java : Integer.Size() -> 例
# getsizeof()
# import sys
# print(sys.getsizeof(12))

# 第七小节
# 顺序查找法 not 排序
# def seqentialSearch(alist, item):
#     pos = 0
#     found = False
#     while pos < len(alist) and not found:
#         if alist[pos] == item:
#             found = True
#         else:
#             pos = pos + 1
#     return found
# def main():
#     test = [1, 3, 5, 8, 9, 3, 1, 10, 18, 16]
#     print("是否找到10:{}".format(seqentialSearch(test, 10)))
# if __name__ == '__main__':
#     main()

# 查找法
# 二分查找法
# 前提必须是已经为从小到大的序列排序了
# def binarySearch(key, alist, begin, end):  #  注意此处不能初始化 否则后面的递归受到的影响很大
#     if begin > end:
#         return -1  # 自然是不可能发生begin<end的情况的,只能是输入错误
#     # print("begin={}".format(begin))
#     # print("end={}".format(end))
#     mid = (begin + end)//2  # 就是//才是python的整数除法
#     if alist[mid] > key:
#         return binarySearch(key, alist, begin, mid)
#     elif alist[mid] < key:
#         return binarySearch(key, alist, mid+1, end)  # mid+1代表有可能本身此时为key
#     else:
#         return mid  # 找到了
# def main():
#     a = [1, 2, 3, 4, 5, 6, 7, 8]
#     print("5的位置:{}".format(binarySearch(5, a, 0, 8)))
# if __name__ == '__main__':
#     main()

# 冒泡排序法

# def bubbleSort(alist):
#     for i in range(len(alist) - 1, 0, -1):
#         for j in range(i):
#             if alist[j] > alist[j+1]:  # 如果后面的还能小于前面的就交换value信息
#                   # 原理就是确保最小的值一直在最左边
#                 alist[j], alist[j+1] = alist[j+1], alist[j]
# def main():
#     alist = [2, 3, 5, 23, 22, 0, 76, 98, 23]
#     bubbleSort(alist)
#     print(alist)
# if __name__ == '__main__':
#     main()

# 选择排序法
# def selectionSort(alist):
#     for i in range(0, len(alist) - 1):
#         m = i
#         for j in range(i+1, len(alist)):
#             if alist[j] < alist[m]:
#                 alist[j], alist[m] = alist[m], alist[j]
# def main():
#     alist = [12, 23, 32, 320, 53, 94, 73, 21]
#     selectionSort(alist)
#     print(alist)
# if __name__ == '__main__':
#     main()

# 插入排序法
# def insertSort(alist):
#     for i in range(1, len(alist)):
#         j = i
#         while j > 0 and alist[j] < alist[j-1]:
#             alist[j], alist[j-1] = alist[j-1], alist[j]
#             j = j - 1
# def main():
#     alist = [2, 21, 32, 45, 32, 45, 90, 132, 73, 3, 9]
#     insertSort(alist)
#     print(alist)
# if __name__ == '__main__':
#     main()

# 归并排序法
# def merge(left, right):
#     merged = []
#     i, j = 0, 0
#     left_len, right_len = len(left), len(right)
#     while i < left_len and j < right_len:
#         if left[i] <= right[j]:
#             merged.append(left[i])
#             i = i + 1
#         else:
#             merged.append(right[j])
#             j = j + 1
#     merged.extend(left[i:])
#     merged.extend(right[j:])
#     return merged
# def mergeSort(alist):
#     if len(alist) <= 1:
#         return alist
#     mid = len(alist)//2
#     left = mergeSort(alist[:mid])
#     right = mergeSort(alist[mid:])
#     return merge(left, right)
# def main():
#     alist = [21, 34, 56, 23, 32, 65, 7, 87, 454]
#     alist1 = mergeSort(alist)
#     print(alist1)
# if __name__ == '__main__':
#     main()

# 集和  可以使用set关键字
# empty = set()
# print(empty)
# mix = set([1, "年级哦", "dasadas", 1.3234])  # 集和是没有顺序的
# print(mix)

# 往集和里面添加元素
# number = {1, 2, 3, "eqe", 1.35}
# print(number)
# number.add("WaLa")
# print(number)

# 删除用remove
# number = {1, "ni", "hao1", 1.32, "hello", 3}
# print(number)
# number.remove(3)
# print(number)

# 集和的四个概念
# n1 = {1, 2, 3, 4, 5}
# n2 = {4, 5, 6, 7, 8}
# print("n1为:{}".format(n1))
# print("n2为:{}".format(n2))
# print("n1和n2的交集:{}".format(n1 & n2))
# print("n1和n2的并集:{}".format(n1 | n2))
# print("n1和n2的差集:{}".format(n1 - n2))
# print("n1和n2的对称差集:{}".format(n1 ^ n2))

# 列表推导式 字典推导式 集和推导式
# l1 = [x for x in range(5)]
# print(l1)   # 输出: [0, 1, 2, 3, 4]
#
# # l1 = (x for x in range(5))  # 元组没有
# # print(l1)
#
# d1 = {n: n**2 for n in range(5)}  # 输出: {0: 0, 1: 1, 2: 4, 3: 9, 4: 16}
# print(d1)
#
# si = {i**2 for i in [-1, -4, 1, 4, -8, 9]}
# print(si)
