# 文件的使用 打开、关闭 读、写
# 文件就是数据的抽象与集和
# 展示方式分 1.文本文件 2.二进制文件   但本质都是二进制方式存储

# 由单一特定编码组成的文件 如UTF-8  txt文件 py文件
# 二进制:没有统一编码，只有0和1   .png  .avi
# 但无论什么，都可以用二进制去打开

# tf = open("OK.txt", "rt", encoding="utf-8")  # rt是文件文件 rb则是二进制文件
# print(tf.readline().strip('\n'))  # 加一个strip使得最后的换行符失效不读取
# print(tf.readline())
# print(tf.readlines())  # 这个是全部读出来
# print(tf.read())  # 默认为全部读取 也可以加约束条件 前几个 回车也属于一个
# tf.close()  # 和c一样，打开了文件记得 关闭文件

# 文件的打开与关闭  使文案从 存储状态 -> 占用状态  open  close
# 文件地址可以使用相对地址或则绝对地址 C:/eo/1.txt  不要/是怕转义符  或则 C://eo//1.txt
# 写文件的函数  write(s) writelines(lines) seek(offset)
# tf = open("C:\\Users\\86199\\Desktop\\python初学习\\写.txt", "at+", encoding="utf-8")  #  tf叫文件句柄
# tf.write("hello world！")
# lines = ["你", "好", "呀"]
# Str = "好的"
# tf.writelines(lines)
# tf.writelines(Str)
# tf.seek(0)
# for line in tf:
#     print(line)  # 注意这里需要读了就加上+
# tf.close()  # 如果你不写这个，那么整个程序过程文件都是打开的，程序结束后也会自动关闭(正常运行的话)




