import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

// ��������Ӧ���Ǻ����ԭ��� �Ƚ��ȳ� Queue
public class Test40 {
    public static void main(String[] args) {
        Queue<String> queue = new LinkedList<>();
        // add ͬ�� offer   element ͬ�� peek

        // ��Ԫ��
        queue.offer("��");
        queue.add("��");

        System.out.println("ͷΪ��"+queue.element());
        System.out.println("ͷΪ��"+queue.peek());  // ����
        System.out.println("��С:"+queue.size());  // ��С

        // ɾ��ͷ��
        queue.remove();
        System.out.println("ͷ��:"+queue.element());

        // poll ����ͷ����ɾ��
        queue.offer("ѽ");
        System.out.println("��ɾ����ͷ��Ϊ:"+queue.poll());
        System.out.println("���ڵ�ͷ��Ϊ:"+queue.element());


        // Queue<String> animal3 = new PriorityQueue<>();
        Queue<Integer> animal = new PriorityQueue<>();
        // ����һģһ���仯
        animal.offer(1);
        animal.add(2);
        animal.add(new Integer(3));
        System.out.println("ͷ��:"+animal.peek());

        // ת��Ϊ����
        Object[] str1 = animal.toArray();  // ���ﲻ��ʹ��int[] str1
        for(int i = 0; i < animal.size(); i++) {  // ���ﲻ��ʹ��(:)�Ǹ�ѭ��
            System.out.print(str1[i]+",");
        }


    }
}
