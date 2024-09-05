import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;

// 其中的方法大多数(all)都是适用于 List
public class Test43 {
    public static void main(String[] args) {
        // 算法
        // java中的算法时静态算法
        List<Integer> list4 = new ArrayList<>();  //
        list4.add(1);
        list4.add(2);
        list4.add(3);
        // 排序
        aa ak = new aa();
        ak.kk();
        ak.display();

        // 打乱
        System.out.print("\nlist4:"+list4);
        luan(list4);
        System.out.println("\n打乱后list4:"+list4);  // 可能没变 几率很小

        // 寻找  下标从0开始
        int pos = Collections.binarySearch(list4, 3);  // 只适用于List
        System.out.println("position；"+pos);

        // 最大值和最小值 也是List的
        int maxValue = Collections.max(list4);
        int minValue = Collections.min(list4);
        System.out.println("list4中的最大值是:"+maxValue+"最小值是:"+minValue);
    }
    public static void luan(List list) {  // 只能用于List
        Collections.shuffle(list);
    }
}
class aa{
    int[] a = new int[]{1,4,2,4,2,5,2,9,8};

    public void kk() {
        Arrays.sort(a);  // 升序
    }
    public void display() {
        for(int i : a)
            System.out.print(i+",");
    }
}
