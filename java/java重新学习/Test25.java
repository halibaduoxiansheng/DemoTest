import java.util.Arrays;  // ������Ҫ��
import java.lang.Integer; // ��ʾ���������С��Ҫ��
import java.lang.Double;  // ��������Ҫ��
public class Test25 {
    public static void main(String[] args){
        int[] arrays = {1, 3, 2, 7, 5, 4, 6, 9, 8};
        Arrays.sort(arrays);
//        System.out.println(arrays);  // ���Է���������е���������
        for(int i : arrays)
            System.out.print(i);  // �����±껹��������Ӧ��
        System.out.println("�ܱ�ʾ�������:"+Integer.MAX_VALUE);  // ������һ��һ��ֻ�Ǵ���������max��min
        System.out.println("�ܱ�ʾ�������:"+Integer.MIN_VALUE);
//        System.out.println(Double.MAX_VALUE);  // ��ȻҲ��������ȥ��ʾ

        // StringBuffer��String���,ֻ����ǰ�����޸�ʱ���������µĶ��󣬶����ڴ���ԱȽ�����
        StringBuffer str0 = new StringBuffer("abcdefg");  // ��ʼ����ʽ
        String str1 = "hijklmn";
        System.out.println(str0);
        System.out.println(str1);
        StringBuffer str2 = new StringBuffer(str1);  // ת����ʽ
        String str3 = str0.toString();  // ת����ʽ
        System.out.println(str2);
        System.out.println(str3);
    }
}
