import java.awt.*;
import java.sql.Array;
import java.util.ArrayDeque;
import java.util.Deque;

// 双端队列(Deque) 继承了Queue的接口
// 对于一般的队列都是先进先出、而双端队列则是可以从两头选择性的插入与删除
public class Test41 {
    public static void main(String[] args) {
        //实现接口的类 ArrayDeque 和 LinkedList
        Deque<Integer> deque = new ArrayDeque<>();
        // 默认的插入是头部 插入 offer(默认是头部插入，该是头进尾出) offerLast(尾部插入)  offerFirst(头部插入)

        deque.offer(1);  // 同理add() addFirst() addLast()
        deque.offer(2);
        deque.offer(3);
        deque.offer(4);
        deque.offerFirst(5);
        deque.offerLast(6);  // 就是正常的插入

        System.out.println("输出:"+deque);

        // 访问
        System.out.println("头部:"+deque.peek());  // 默认为访问头部
        System.out.println("头部:"+deque.peekFirst());
        System.out.println("尾部:"+deque.peekLast());

        System.out.println("访问头部:"+deque.getFirst());  // 同理
        System.out.println("访问尾部:"+deque.getLast());

        // 移出
        System.out.println("移出头部:"+deque.poll());  // 默认移出
        System.out.println("再移出下一个尾部:"+deque.pollLast());
        System.out.println("再移出头部:"+deque.pollFirst());

        // 与上面的同理 remove() removeFirst() removeLast()
        System.out.println("now it is :"+deque);
        System.out.println("移出头部:"+deque.remove());
        System.out.println("移出头部:"+deque.removeFirst());
        System.out.println("移尾部:"+deque.removeLast());

        //deuqe.clear() 清空
    }
}
