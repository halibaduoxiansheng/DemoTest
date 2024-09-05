import java.util.*;

public class Test30 {
    public static void main(String[] args){
        //区分好ArrayList与LinkdedList  基本差不多一样
        // ArrayList是动态数组 而LinkedList是链表的数据结构
        // 访问速度上 一般访问时用ArrayList   载入、删除是用LinkedList
        // prev data next
        List<String> animals = new LinkedList<>();
        animals.add("niao");
        animals.add("ji");
        animals.add("gou");

        animals.add(3,"zhu");  // 与ArrayList一致
        System.out.println("animals:"+animals);

        List<String> list0 = new LinkedList<>();
        list0.add("ya");
        list0.addAll(animals);
        System.out.println("没问题的话list0为一共:"+list0);

        LinkedList<String> list1 = new LinkedList<>();  // 可以换成ArrayList
        ListIterator<String> list2 = list1.listIterator();  // ListIterator的使用
        list2.add("feng");
        list2.add("shou");
        System.out.println("list1:"+list1);

        // get使用方法一致
        String str0 = list1.get(1);
        System.out.println("索引为1的list1元素为:"+str0);

        Iterator iterate = list0.iterator(); // 创建的时候是指向开头那个（迭代器）
        while(iterate.hasNext()){  // 只要链接后面还有就继续
            System.out.print(iterate.next());
            System.out.print(",");
        }

        // 更适合的迭代器
        System.out.println("");
        ListIterator<String> listiterate = list0.listIterator();
        while(listiterate.hasNext()){
            System.out.print(listiterate.next());  // 第一个.next为第一个元素
            System.out.print(",");
        }
        // 反向
        System.out.println("");
        while(listiterate.hasPrevious()){
            System.out.print(listiterate.previous());  // 反向输出了
            System.out.print(",");
        }

        if(list0.contains("ya"))  // 查找其中是否包含
            System.out.println("\nlist0其中有ya");

        int num0 = list0.indexOf("ya");  // 返回第一次出现的索引
        int num1 = list0.lastIndexOf("gou"); // 返回最后一次出现的索引
        System.out.println("num0="+num0+",num1="+num1);

        //改变 set
        System.out.println("list0:"+list0);
        list0.set(1, "hu");
        System.out.println("现在list0:"+list0);

        // 通过ListIterator
        ListIterator<String> listiterate0 = list0.listIterator();
        listiterate0.next();
        listiterate0.set("xia");
        System.out.println("list0:"+list0);

        // 删除remove
        list0.remove(0);  // 删除索引0处的元素
        System.out.println("list0"+list0);  // xia被删除了

        // 也可以使用不需要参数的removeLast() 默认是删除最新进去的那一个
        // 但是需要使用 LinkedList<> path = new LinkedList<>();

        // 当然和set一样，可以用listiterate0去删除

        // clear() 清空 不写例子了 list3.clear()

        Deque<Integer> list3 = new LinkedList<>();
        list3.add(1);
        list3.add(2);
        list3.add(3);
        System.out.println("队列list3:"+list3);
        // getFirst() getLast() removeFirst() removeLast() size()
        //上面的函数功能一眼就可以看出来，我就不写了，像list3.getFirst() list3.removeLast()……
        //peek() 访问第一个元素 poll() 删除第一个元素

//        offer()
        System.out.println("将元素4添加到lst3的末尾");
        list3.offer(4);
        System.out.println("list3:"+list3);

        //foreach循环 :
        for(String str1 : list0)
            System.out.print(str1+",");
    }
}


