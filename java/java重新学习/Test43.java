import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;

// ���еķ��������(all)���������� List
public class Test43 {
    public static void main(String[] args) {
        // �㷨
        // java�е��㷨ʱ��̬�㷨
        List<Integer> list4 = new ArrayList<>();  //
        list4.add(1);
        list4.add(2);
        list4.add(3);
        // ����
        aa ak = new aa();
        ak.kk();
        ak.display();

        // ����
        System.out.print("\nlist4:"+list4);
        luan(list4);
        System.out.println("\n���Һ�list4:"+list4);  // ����û�� ���ʺ�С

        // Ѱ��  �±��0��ʼ
        int pos = Collections.binarySearch(list4, 3);  // ֻ������List
        System.out.println("position��"+pos);

        // ���ֵ����Сֵ Ҳ��List��
        int maxValue = Collections.max(list4);
        int minValue = Collections.min(list4);
        System.out.println("list4�е����ֵ��:"+maxValue+"��Сֵ��:"+minValue);
    }
    public static void luan(List list) {  // ֻ������List
        Collections.shuffle(list);
    }
}
class aa{
    int[] a = new int[]{1,4,2,4,2,5,2,9,8};

    public void kk() {
        Arrays.sort(a);  // ����
    }
    public void display() {
        for(int i : a)
            System.out.print(i+",");
    }
}
