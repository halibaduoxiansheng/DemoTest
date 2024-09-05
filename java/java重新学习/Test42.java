import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class Test42 {
    public static void main(String[] args) {
        //Set 与List不同的是不能包含重复的元素
        Set<Integer> set = new HashSet<>();

        // 写入元素
        set.add(1);
        set.add(2);
//        set.add(2);  // 可以允许写两个一样的元素，但只会储存第一个写的
        set.add(3);
//        set.add(2);
        set.add(4);

        System.out.println("set输出:"+set);

        Set<Integer> set1 = new HashSet<>();
        set1.addAll(set);
        System.out.println("set1输出:"+set1);

        // 循环访问
        Iterator<Integer> iterate = set1.iterator();  // 当然也可以可以使用 TreeSet 而不是 HashSet
        while(iterate.hasNext()) {
            System.out.print(iterate.next());
            System.out.print(", ");
        }

        // 删除 remove
        boolean removeInt = set1.remove(1);
        boolean removeInt1 = set1.remove(5);  // 不存在的数据就会返回false 即删除失败
        System.out.println("数据1被删除成功了吗？:"+removeInt+removeInt1);
        boolean value = set1.removeAll(set1);  // 全部删除 其实括号中放的是其余的直接就是差集

        // set2.retainAll(set1)  ->交集   size() 大小
        // contains() 返回布尔类型 说明是否包含
        System.out.println("set:"+set);
        System.out.println("set1是否为空了(已经进行removeAll操作了):"+set1.isEmpty());
        System.out.println("set的大小为:"+set.size());
        System.out.println("其中是否包含1:"+set.contains(1));
    }
}
