# //选择不同的发光可以显示 1-9 A-F
import turtle, time
def drawGap():
    turtle.penup()
    turtle.fd(5)
def drawLine(draw): # 绘制单段数码管
    turtle.pendown() if draw else turtle.penup()
    turtle.pencolor("black")
    turtle.fd(40)
    drawGap()
    turtle.right(90)
def drawDigit(digit):
    drawLine(True) if digit in [2, 3, 4, 5, 6, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 1, 3, 4, 5, 6, 7, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 2, 3, 5, 6, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 2, 6, 8] else drawLine(False)
    turtle.left(90)
    drawLine(True) if digit in [0, 4, 5, 6, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 2, 3, 5, 6, 7, 8, 9] else drawLine(False)
    drawLine(True) if digit in [0, 1, 2, 3, 4, 7, 8, 9] else drawLine(False)
    turtle.left(180)
    turtle.penup()
    turtle.fd(20)
def drawData(data):  # 通过约束输入的数据格式,来修改 "%Y-%m=%d+"
    for i in data:
        if i == '-':
            turtle.pencolor("red")
            turtle.write('年', font=('Arial', 18, "normal"))
            turtle.fd(40)
        elif i == '=':
            turtle.pencolor("red")
            turtle.write('月', font=('Arial', 18, "normal"))
            turtle.fd(40)
        elif i == '+':
            turtle.pencolor("red")
            turtle.write('日', font=('Arial', 18, "normal"))
        else:
            drawDigit(eval(i))
def main():
    please = input("please input the data what is you want to konw:")
    turtle.tracer(False)  # 使画的瞬间显示,不用显示画的过程
    turtle.setup(800, 350, 200, 200)
    turtle.penup()
    turtle.fd(-300)
    turtle.pensize(5)
    drawData(please)
    turtle.hideturtle()
    turtle.done()
main()
