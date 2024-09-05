// java迷宫  java-maze

// 思路: 使用二维数组    1: 墙   0: 路   -1: 走过的路
// 在构建的地图上记得将上下左右的位置定为-- "墙"
import java.util.List;
import java.util.ArrayList;


// 可行时------依次按照右、下、左、上 去判断能否走路
// 不可行时-----回退到上一个位置
// 坐标是一个与一般的数学二维坐标一样的,  横线x轴(向右)  纵向y轴(向下)

// 留意maze的坐标x，y 与 point的x，位置相反
public class Test52 {
    private static int[][] maze = {
            {1,0,1,1,0,1,0,1,0,1},
            {0,1,0,0,1,0,0,1,1,0},
            {1,0,0,1,1,1,0,0,1,1},
            {1,0,1,0,0,0,1,0,1,1},
            {1,1,1,1,1,1,1,0,0,0},
            {1,0,0,1,1,1,0,1,1,1},
            {1,1,1,1,0,0,1,1,0,0}
    };
    private static List<Point> route = new ArrayList<>();   // 理解一下Point
    public static void main(String[] args) {
//        System.out.println("java maze");
//         先打印一下迷宫地图
//        for(int i = 0; i < maze.length; i++) {
//            for(int j = 0; j < maze.length; j++) {
//                System.out.print(maze[i][j]+" ");
//            }
//            System.out.println(); // 换行
//        }
        System.out.println("ok?");
        boolean flag = maze(Test52.maze, new Point(1,1));  // 起点这里定为了(1,1)
        if(flag) {
            System.out.println("成功到达迷宫的终点！\n路线如下：");
            for(int i = 0; i < route.size(); i++) {
                System.out.print("("+route.get(i).getX()+","+route.get(i).getY()+")");
                if(i != route.size()-1) {
                    System.out.print("->");
                }
            }
        }
        else
            System.out.println("根本没有办法到达终点哦!");
    }
    // 判断接下来可以往哪方向前进   依次顺序为  右 下 左 上
    private static boolean isWalk(int[][] maze, Point currentPoint) {
        int x = currentPoint.getX(); // 先获取坐标位置
        int y = currentPoint.getY();

        // 开始依次判断 记住 0是路 1才是墙 -1为走过的路
        if(maze[y][x+1] != 1 && maze[y][x+1] != -1) {  // 向右
            route.add(new Point(x+1,y));
            return true;  // 返回系统是否能行走该方向
        }

        if(maze[y+1][x] != 1 && maze[y+1][x] != -1) { // 向下
            route.add(new Point(x,y+1));
            return true;
        }

        if(maze[y][x-1] != 1 && maze[y][x-1] != -1) { // 向左
            route.add(new Point(x-1,y));
            return true;
        }

        if(maze[y-1][x] != 1 && maze[y-1][x] != -1) { // 向上
            route.add(new Point(x,y-1));
            return true;
        }
        else
            return false;  // 遇到死路了就只能倒退了
    }

    private static boolean maze(int[][] maze, Point enter) {
        maze[enter.getX()][enter.getY()] = -1;  // 先标记起点走过
        route.add(enter);  // 入列表

        while(!route.isEmpty()) {  // 只要列表里面仍有数据就可以一直执行
            while(isWalk(maze, enter)) {
                enter = route.get(route.size() - 1);  // 先进后出的原理 先出最后一个进入的元素
                if (enter.getX() == 8 && enter.getY() == 8) {  // 这里假定终点的坐标为 (8,8)
                    return true;  // 到达终点退出
                } else {
                    maze[enter.getX()][enter.getY()] = -1;
                }
            }
            route.remove(route.size()-1);
            enter = route.get(route.size()-1);
        }
        return false;
    }
}
class Point{
    private int x;
    private int y;

    public Point(){x=0;y=0;}
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }
    public int getY() {
        return y;
    }
}
