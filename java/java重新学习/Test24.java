import java.util.ArrayList; //这些类就需要再添加进来
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List; // 这是列表必须要的类
// Vector是线程同步的,安全但效率低 ArrayList是线程异步的，效率高
//列表是
public class Test24 {
    // List介绍就是一种类似java数组的存在
    public static void main(String[] args){
        //开始去创建对象List1,这些对象可以使用List接口的功能
        List<String> list1 = new ArrayList<>();//最常用的数组列表 String代表我们的数据类型是字符串 整数用Integer
//        List<String> list2 = new LinkedList<>(); //当然，这个链表列表也是不错的
        //下面是一些常用的接口方法的使用 列表长度 list1.size()
        list1.add("你");  //add函数，就是从前往后的将数据填入
        list1.add("好");
        list1.add("呀");
        list1.add(3,"哦"); //使用索引号直接填入列表中
        System.out.println("List1:"+list1); //可以发现数据用中括号括起来，数据之间是逗号隔开，而对象list1就像一个数组

        String str0 = list1.get(0); //get函数中放下标
        System.out.println("列表中下标为0的那个数据是:"+str0); //可以看出get函数就是获取数据
//        System.out.println("List:"+list1); //而且发现get只是read，而非将数据提取出来

        String removestr0 = list1.remove(0); //可以发现说曹操曹操到，这个才是删除 而且这个删除的返回值必须读取
        System.out.println("被删除的那个数据是:"+removestr0+"，List1:"+list1);

        List<String> list3 = new ArrayList<>();
        list3.add("真假"); //一个新的对象创建的列表
        System.out.println("List3:"+list3);
        list3.addAll(list1); //作用:将list1的东西都加到list3的后面去
        System.out.println("List1:"+list1+"List3:"+list3); //可见改变了list3，但list1没有影响

        List<String> list4 = new ArrayList<>(Arrays.asList("你", "好", "呀")); // 直接初始化
        System.out.println("直接初始化为:"+list4);

        //更改ArrayList元素 set()   本质上为替换
        ArrayList animals = new ArrayList<>(Arrays.asList("dog", "cot", "robot"));
        animals.set(1, "people"); // 更改 前为下标、后为键（即数据）
        System.out.println(animals);

        ArrayList list5 = new ArrayList<>(Arrays.asList("ni", "hao", "shi", "jie"));
        System.out.println("list5的长度:"+list5.size());  // 长度函数不再是length
        list5.removeAll(list5);
        list5.clear();  // 效果与上面一致
        System.out.println(list5);  // 输出为空

        ArrayList list6 = new ArrayList<>(Arrays.asList("ab", "cd", "ef", "gh"));
        String[] str1 = new String[list6.size()];
        list6.toArray(str1);
        for(String item : str1)
            System.out.print(item+","); // 将数列转化为字符串数组输出
        //相反的就为下面
//        ArrayList list7 = new ArrayList<>(Ararys.asList(str1));
    }
}
