# 第六章
# 程序的输入和输出
# print(*object, sep=' ', end='\n', file=sys.stdout, flush=False)

# name = input()  # 读入的是字符串 但可以转化为
# num_value = (int)(input("please input your value:"))

# 文件的打开
# open(file, mode='r', encoding=None)
# 当然 打开文件后请及时关闭文件 f = open(……) f.close()
# f = open('静夜思.txt', 'r+', encoding='utf8')  # 要读取必须是r,a,w可不行
# print(f)
# for line in f:
#     print(line.replace('\n', ' '))  # 将故事中的空格换成回车
#     # print(line.strip( ))
# f.close()

# with open ('静夜思.txt', 'r', encoding='utf-8') as f:  # 这个好,能自动关闭文件
#     for line in f:
#         print(line.strip( ))

# 文件的读/写操作
# with open('静夜思.txt', 'r', encoding='utf8') as f:
#     txt = f.read()
#     print(txt)
#     # txt = f.read(3)  # 读取前三个字符
#     txt = f.readline()  # 读取文件的第一行
#     f.seek(0)
#     print(txt)
#     print(f.tell)  # 输出当前文件指针位置
#     txt = f.readlines()
#     print(txt)
#     print(f.tell())
#     txt = f.readlines()
#     print(txt)
#     f.seek(0)  # 调节文件指针的位置 0:文件开始 1:当前位置 2:文件结尾
#     txt = f.readlines()
#     print(txt)


# import turtle
# x = []
# y = []
# with open('XRD.txt', 'r') as f:  # XRD.txt文件需要事先创建好
#     for line in f:
#         set= line.strip( ).split('\t')
#         # strip(' ')去除首尾的' '   split(' ') 全文根据这个来分割
#         turtle.goto(float(set[0]) * 15, float(set[1])/30)
# turtle.done()
