import java.util.ArrayList;
import java.util.ListIterator;

public class Test44 {
    public static void main(String[] args) {
        //iterator 译 迭代器
        ArrayList<Integer> list = new ArrayList<>();
        list.add(1); list.add(2);
        list.add(4); list.add(3);
        System.out.println("此时的List为:"+list);

//        ListIterator<Integer> iterate = new ListIterator<>();  // 是抽象的 无法实例化
        ListIterator<Integer> iterate = list.listIterator();
        // 使用next()方法
        iterate.next();
        int numValue = iterate.next();
        System.out.println("此时访问的数据是numValue为"+numValue);

        // 上一个元素  毕竟此时已经访问过第一个了 已经向后移动了一个数据
        int numValue1 = iterate.previous();
        System.out.println("上一个元素是(即当前next()输出)(位置又上移动了一个):"+numValue1);
        System.out.println("不信你看这个输出:"+iterate.next());

        // 下一个元素的位置 nextIndex()
        int index1 = iterate.nextIndex();  // 如果没有问题的话就是1 上面那个是下标0
        System.out.println("下一个元素的位置:"+index1);

        // 上一个元素的位置
        int index2 = iterate.previousIndex();
        System.out.println("上一个元素的位置是:"+index2);

        // hasNext()  是否还有下一个
        boolean ok = iterate.hasNext();
        System.out.println("是否还有下一个:"+ok);  // 没错 iterate就像一个指针一样 尤其像文件指针
        System.out.println("此时访问的数据是:"+iterate.next());

        iterate.set(12);  // 此时的这个4已经变为了12
        iterate.previous();
        while(iterate.hasNext()) {
            System.out.print(iterate.next());
            System.out.print(",");
        }
    }
}
