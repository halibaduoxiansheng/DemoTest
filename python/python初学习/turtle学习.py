# turtle也叫海龟 所以也叫海龟库
# turtle是python标准库之一 也就是说随解释器安装在系统中的库

# 绘制窗口中最小单位是像素 默认在屏幕正中心
# 电脑窗口的左上角坐标为[0, 0]
# startx ： 横坐标 starty： 纵坐标 分别表示绘制窗口的最上角距离电脑窗口的左上角的距离
# width 和 height 分别表示绘制窗口的大小
# 上面的四个数据全部用于一个函数 turtle.setup(width, height, startx, starty) 设置窗口大小和位置

# 可以想象就是有一个海龟在爬动画画 初始位置在绘制窗口的中心 坐标(0, 0)
# 然后有一个坐标系 右为x正方向 上为y正方向
# 最为简单的利用函数 goto 例： turtle.goto(x, y) 作用：去往(x, y)这个位置

# 上面为绝对坐标 另外一个叫做海龟坐标
#     turtle.fd(d) 向正前方运行 d 个像素 其实就是 turtle.forward(d)
#     turtle.bk(d) 向反方向运行 d 个像素
#       turtle.left(angle) 向左方向旋转angle度
#       turtle.right(angle) 向右方向旋转angle度
#     turtle.circle(r, angle) 以当前位置的上方r为半径,进行旋转angle度

# turtle.seth(angle) 作用：改变当前的海龟行进角度 即 turtle.setheading(angle)

# turtle.colormode(mode)
# 如果里面的mode为整数或着下数分别代表 采用255， 或则 1来定义RGB颜色

# from <库名> import *  那么后面使用的函数就不再需要加上  库名.
# 或则也可以使用别名的方法 from <库名> as <库别名>

# turtle.penup() 相当于海龟飞起 此时移动不会形成图案
# 当然 必须与turtle.pendown() 合用 ， 表示此时飞行完毕
# 区分于 turtle.done() 这个是画笔停止

# pensize() 画笔粗细 pencolor() 画笔颜色
# 例 peoplecolor(0.2, 0.4, 0.5) 或则 peoplecolor(169, 123, 223) 或则 peoplecolor("black")

