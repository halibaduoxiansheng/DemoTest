import java.util.ArrayList;
import java.util.ListIterator;

public class Test44 {
    public static void main(String[] args) {
        //iterator �� ������
        ArrayList<Integer> list = new ArrayList<>();
        list.add(1); list.add(2);
        list.add(4); list.add(3);
        System.out.println("��ʱ��ListΪ:"+list);

//        ListIterator<Integer> iterate = new ListIterator<>();  // �ǳ���� �޷�ʵ����
        ListIterator<Integer> iterate = list.listIterator();
        // ʹ��next()����
        iterate.next();
        int numValue = iterate.next();
        System.out.println("��ʱ���ʵ�������numValueΪ"+numValue);

        // ��һ��Ԫ��  �Ͼ���ʱ�Ѿ����ʹ���һ���� �Ѿ�����ƶ���һ������
        int numValue1 = iterate.previous();
        System.out.println("��һ��Ԫ����(����ǰnext()���)(λ�������ƶ���һ��):"+numValue1);
        System.out.println("�����㿴������:"+iterate.next());

        // ��һ��Ԫ�ص�λ�� nextIndex()
        int index1 = iterate.nextIndex();  // ���û������Ļ�����1 �����Ǹ����±�0
        System.out.println("��һ��Ԫ�ص�λ��:"+index1);

        // ��һ��Ԫ�ص�λ��
        int index2 = iterate.previousIndex();
        System.out.println("��һ��Ԫ�ص�λ����:"+index2);

        // hasNext()  �Ƿ�����һ��
        boolean ok = iterate.hasNext();
        System.out.println("�Ƿ�����һ��:"+ok);  // û�� iterate����һ��ָ��һ�� �������ļ�ָ��
        System.out.println("��ʱ���ʵ�������:"+iterate.next());

        iterate.set(12);  // ��ʱ�����4�Ѿ���Ϊ��12
        iterate.previous();
        while(iterate.hasNext()) {
            System.out.print(iterate.next());
            System.out.print(",");
        }
    }
}
