import java.util.Arrays;  // 升序函数要的
import java.lang.Integer; // 表示最大数、最小数要的
import java.lang.Double;  // 浮点数需要的
public class Test25 {
    public static void main(String[] args){
        int[] arrays = {1, 3, 2, 7, 5, 4, 6, 9, 8};
        Arrays.sort(arrays);
//        System.out.println(arrays);  // 可以发现这个是有点乱码的输出
        for(int i : arrays)
            System.out.print(i);  // 但是下标还是完美对应的
        System.out.println("能表示的最大数:"+Integer.MAX_VALUE);  // 与下面一行一样只是代表整数的max、min
        System.out.println("能表示的最大数:"+Integer.MIN_VALUE);
//        System.out.println(Double.MAX_VALUE);  // 当然也可以这样去表示

        // StringBuffer与String差不多,只不过前者在修改时不会生成新的对象，对于内存而言比较友善
        StringBuffer str0 = new StringBuffer("abcdefg");  // 初始化方式
        String str1 = "hijklmn";
        System.out.println(str0);
        System.out.println(str1);
        StringBuffer str2 = new StringBuffer(str1);  // 转化方式
        String str3 = str0.toString();  // 转化方式
        System.out.println(str2);
        System.out.println(str3);
    }
}
