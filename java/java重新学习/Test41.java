import java.awt.*;
import java.sql.Array;
import java.util.ArrayDeque;
import java.util.Deque;

// ˫�˶���(Deque) �̳���Queue�Ľӿ�
// ����һ��Ķ��ж����Ƚ��ȳ�����˫�˶������ǿ��Դ���ͷѡ���ԵĲ�����ɾ��
public class Test41 {
    public static void main(String[] args) {
        //ʵ�ֽӿڵ��� ArrayDeque �� LinkedList
        Deque<Integer> deque = new ArrayDeque<>();
        // Ĭ�ϵĲ�����ͷ�� ���� offer(Ĭ����ͷ�����룬����ͷ��β��) offerLast(β������)  offerFirst(ͷ������)

        deque.offer(1);  // ͬ��add() addFirst() addLast()
        deque.offer(2);
        deque.offer(3);
        deque.offer(4);
        deque.offerFirst(5);
        deque.offerLast(6);  // ���������Ĳ���

        System.out.println("���:"+deque);

        // ����
        System.out.println("ͷ��:"+deque.peek());  // Ĭ��Ϊ����ͷ��
        System.out.println("ͷ��:"+deque.peekFirst());
        System.out.println("β��:"+deque.peekLast());

        System.out.println("����ͷ��:"+deque.getFirst());  // ͬ��
        System.out.println("����β��:"+deque.getLast());

        // �Ƴ�
        System.out.println("�Ƴ�ͷ��:"+deque.poll());  // Ĭ���Ƴ�
        System.out.println("���Ƴ���һ��β��:"+deque.pollLast());
        System.out.println("���Ƴ�ͷ��:"+deque.pollFirst());

        // �������ͬ�� remove() removeFirst() removeLast()
        System.out.println("now it is :"+deque);
        System.out.println("�Ƴ�ͷ��:"+deque.remove());
        System.out.println("�Ƴ�ͷ��:"+deque.removeFirst());
        System.out.println("��β��:"+deque.removeLast());

        //deuqe.clear() ���
    }
}
