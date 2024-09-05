import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

// 队列我们应该是很清楚原理的 先进先出 Queue
public class Test40 {
    public static void main(String[] args) {
        Queue<String> queue = new LinkedList<>();
        // add 同理 offer   element 同理 peek

        // 加元素
        queue.offer("你");
        queue.add("好");

        System.out.println("头为："+queue.element());
        System.out.println("头为："+queue.peek());  // 访问
        System.out.println("大小:"+queue.size());  // 大小

        // 删除头部
        queue.remove();
        System.out.println("头部:"+queue.element());

        // poll 返回头部并删除
        queue.offer("呀");
        System.out.println("被删除的头部为:"+queue.poll());
        System.out.println("现在的头部为:"+queue.element());


        // Queue<String> animal3 = new PriorityQueue<>();
        Queue<Integer> animal = new PriorityQueue<>();
        // 操作一模一样变化
        animal.offer(1);
        animal.add(2);
        animal.add(new Integer(3));
        System.out.println("头部:"+animal.peek());

        // 转化为数组
        Object[] str1 = animal.toArray();  // 这里不能使用int[] str1
        for(int i = 0; i < animal.size(); i++) {  // 这里不能使用(:)那个循环
            System.out.print(str1[i]+",");
        }


    }
}
