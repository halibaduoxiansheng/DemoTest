/*想要运行别忘了第一件事 先将文件的名字改过来哦~*/
import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        // 模仿一下最短路径
        Scanner reader = new Scanner(System.in);
        System.out.print("请输入结点的数量:");

        // 结点数量
        int num = reader.nextInt();

        // 创建一个二维数组放点与点之间的距离
        int[][] value = new int[num][num];

        // 接下来我们将会将你提供给我们的结点从A-Z向后默认命名
        for (int i = 0; i < num-1; i++) {
            for (int j = i+1; j < num; j++) {
                System.out.println("(不通请输入0)请输入第"+(i+1)+"个地点与第"+(j+1)+"个地点的距离为:");
                value[i][j] = reader.nextInt();
                if (value[i][j] == 0) {
                    value[i][j] = Integer.MAX_VALUE;
                    value[j][i] = value[i][j];
                } else {
                    value[j][i] = value[i][j];
                }
            }
        }

//        // 然后开始输入看一下是否请求数据成功
        for (int i = 0; i < num-1; i++) {
            for (int j = 0; j < num; j++) {
                System.out.print("value["+i+"]["+j+"]="+value[i][j]+"\t\t");
                if (j == (num - 1)) {
                    System.out.println(); // 没什么事,就是简单的换一个行
                }
            }
        }
        // 分别代表求最短路径时的开始下标和结束下标
        int start = 0, end = 3;
        int shortest1 = shortest(value, start, end);
        System.out.println("下标"+start+"到下标"+end+"的最短距离为"+shortest1);
    }

    // value[i][m] + value[m][j] < value[i][j]
    // 谨记函数的value函数是临时的变量 函数只负责返回最短距离 并不会改变函数value

    // [0][0] [0][1] [0][2] [0][3]
    // [1][0] [1][1] [1][2] [1][3]
    // [2][0] [2][1] [2][2] [2][3]
    // [3][0] [3][1] [3][2] [3][3]
    public static int shortest(int[][] value, int start, int end) {
        for (int i = 0; i < value.length; i++) { // 首先i是老大 他可以遍历每一个下标位置
            for (int j = 0; j < value[i].length; j++) {
                for (int k = 0; k < value[i].length; k++) {
                    if ((i != k) && (k != j) && (value[i][k] != Integer.MAX_VALUE) && (value[k][j] != Integer.MAX_VALUE) && (value[i][k] + value[k][j]) < value[i][j]) {
                        value[i][j] = value[i][k] + value[k][j]; // 更新最短距离
                    }
                }
            }
        }

        return value[start][end];
    }
}
