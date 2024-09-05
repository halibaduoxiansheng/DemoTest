# python是脚本语言，跨平台语言 避免重复造轮子
# 语法具有强制可读性 -- 缩进

# 下面为绘制蟒蛇的代码
# 引入绘图库 turtle
import turtle
turtle.setup(650, 350, 200, 200)
turtle.penup()
turtle.fd(-250)
turtle.pendown()
turtle.pensize(3)
turtle.pencolor("red")
turtle.seth(-40)
turtle.fd(200)
turtle.goto(-250, 0)
turtle.left(90)
turtle.fd(200)
turtle.goto(-250, 0)
turtle.right(90)
for i in range(4):
    turtle.circle(40, 80)
    turtle.circle(-40, 80)
turtle.circle(40, 80/2)
turtle.fd(40)
turtle.circle(16, 180)
turtle.fd(40 * 2 / 3)
turtle.done()