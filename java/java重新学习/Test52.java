// java�Թ�  java-maze

// ˼·: ʹ�ö�ά����    1: ǽ   0: ·   -1: �߹���·
// �ڹ����ĵ�ͼ�ϼǵý��������ҵ�λ�ö�Ϊ-- "ǽ"
import java.util.List;
import java.util.ArrayList;


// ����ʱ------���ΰ����ҡ��¡����� ȥ�ж��ܷ���·
// ������ʱ-----���˵���һ��λ��
// ������һ����һ�����ѧ��ά����һ����,  ����x��(����)  ����y��(����)

// ����maze������x��y �� point��x��λ���෴
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
    private static List<Point> route = new ArrayList<>();   // ���һ��Point
    public static void main(String[] args) {
//        System.out.println("java maze");
//         �ȴ�ӡһ���Թ���ͼ
//        for(int i = 0; i < maze.length; i++) {
//            for(int j = 0; j < maze.length; j++) {
//                System.out.print(maze[i][j]+" ");
//            }
//            System.out.println(); // ����
//        }
        System.out.println("ok?");
        boolean flag = maze(Test52.maze, new Point(1,1));  // ������ﶨΪ��(1,1)
        if(flag) {
            System.out.println("�ɹ������Թ����յ㣡\n·�����£�");
            for(int i = 0; i < route.size(); i++) {
                System.out.print("("+route.get(i).getX()+","+route.get(i).getY()+")");
                if(i != route.size()-1) {
                    System.out.print("->");
                }
            }
        }
        else
            System.out.println("����û�а취�����յ�Ŷ!");
    }
    // �жϽ������������ķ���ǰ��   ����˳��Ϊ  �� �� �� ��
    private static boolean isWalk(int[][] maze, Point currentPoint) {
        int x = currentPoint.getX(); // �Ȼ�ȡ����λ��
        int y = currentPoint.getY();

        // ��ʼ�����ж� ��ס 0��· 1����ǽ -1Ϊ�߹���·
        if(maze[y][x+1] != 1 && maze[y][x+1] != -1) {  // ����
            route.add(new Point(x+1,y));
            return true;  // ����ϵͳ�Ƿ������߸÷���
        }

        if(maze[y+1][x] != 1 && maze[y+1][x] != -1) { // ����
            route.add(new Point(x,y+1));
            return true;
        }

        if(maze[y][x-1] != 1 && maze[y][x-1] != -1) { // ����
            route.add(new Point(x-1,y));
            return true;
        }

        if(maze[y-1][x] != 1 && maze[y-1][x] != -1) { // ����
            route.add(new Point(x,y-1));
            return true;
        }
        else
            return false;  // ������·�˾�ֻ�ܵ�����
    }

    private static boolean maze(int[][] maze, Point enter) {
        maze[enter.getX()][enter.getY()] = -1;  // �ȱ������߹�
        route.add(enter);  // ���б�

        while(!route.isEmpty()) {  // ֻҪ�б������������ݾͿ���һֱִ��
            while(isWalk(maze, enter)) {
                enter = route.get(route.size() - 1);  // �Ƚ������ԭ�� �ȳ����һ�������Ԫ��
                if (enter.getX() == 8 && enter.getY() == 8) {  // ����ٶ��յ������Ϊ (8,8)
                    return true;  // �����յ��˳�
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
