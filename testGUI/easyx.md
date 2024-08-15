# **EasyX**

##### Easyx是什么？

![](F:\MarktextPhoto\2024-08-15-19-35-06-image.png)

**先下载对应的.h库文件**

### 函数使用

```
initgraph(

    int width,

    int height,

    int flag = NULL

);
// 作用：创建一个width×height的绘图窗口
```

flag的**取值**

![](F:\MarktextPhoto\2024-08-15-19-39-29-image.png)

```
void closegraph(void);
// 作用：关闭绘图窗口
```

```c
HRGN CreateRectRgn(
    int nLeftRect, // 左上x坐标
    int nTopRect, // 左上y坐标
    int nRightRect, // 右下x坐标
    int nBottomRect // 右下y坐标
);
// 船舰一个矩形区域(不是画图)
// 返回值 区域的句柄
// 使用这个区域后 就可以调用Deleteobject函数了
```

```
Deleteobject(HRGN rgn);
// 删除矩形区域
```

---

缩放因子 概念： 1即原本    >1即放大    <1即缩小    -1即翻转(x、y轴对调)

---

```
void setaspectratio(
    float xasp, // x方向的缩放因子
    float yasp  // y方向的缩放因子
);
```

```
void setcliprgn(HRGN hrgn);
// 设置为裁剪区  传入NULL则取消之前的裁剪区
```

```
void circle(
    int x, // 圆心x坐标
    int y, // 圆心y坐标
    int radius // 圆的半径
);
// 画一个圆
```


