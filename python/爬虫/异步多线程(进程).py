# 线程（执行单位） 进程（资源单位）
# 每一个进程里面至少有一个线程

# 启动一个程序至少一个主线程

# def func():  # 这还是单线程
#     for i in range(1000):
#         print("func",i)
#
# if __name__ == '__main__':
#     func()
#     for i in range(1000):
#         print("main",i)

# 多线程 方依一
from threading import Thread  # 线程类

# def func():
#     for i in range(1000):
#         print("func", i)
# if __name__ == '__main__':
#     t = Thread(target=func)  # 创建一个线程
#     t.start()  # 开始执行该线程，具体执行时间由CPU决定
#     for i in range(1000):
#         print("main", i)


# 方法二
# class MyThread(Thread):
#     def run(self):
#         for i in range(100):
#             print("子线程", i)
# if __name__ == '__main__':
#     t = MyThread()
#     t.start()
#     for i in range(1000):
#         print("主线程", i)

# from threading import Thread  # 线程类
#
# def func(name):
#     for i in range(1000):
#         print(name, i)
# if __name__ == '__main__':
#     t1 = Thread(target=func, args=("周杰伦",))  # 创建一个线程
#     t1.start()  # 开始执行该线程，具体执行时间由CPU决定
#
#     t2 = Thread(target=func, args=("李佳涵",))  # 创建一个线程
#     t2.start()  # 开始执行该线程，具体执行时间由CPU决定


# 进程  比较考虑自己设备的能力
# from multiprocessing import Process
#
# def func():
#     for i in range(10000):
#         print("子进程", i)
#
# if __name__ == '__main__':
#     p = Process(target=func)
#     p.start()
#     for i in range(10000):
#         print("主进程", i)
