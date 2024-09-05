import java.util.Map;
import java.util.HashMap;
public class Test28 {
    public static void main(String[] args){
        //使用HashMap类创建map
        Map<String, Integer> map = new HashMap<>();

        //将元素插入map集和
        map.put("niao", 1);  // {niao=1, long=2}
        map.put("long", 2);
        map.put("ji", 3);
        System.out.println("Map:"+map);  // 列表是[]，而集和是{}

        //以组的形式返回所有
        System.out.println("所有："+map.entrySet());

        // 键值为（key）
        System.out.println("键值为:"+map.keySet());  // 也就是put的第一个元素的第一个值
        // 与键相对应的值就是元素的第二个值
        System.out.println("值为:"+map.values());

        int removenum = map.remove("long");
        System.out.println("被删除的那个数："+removenum);  // 通过键值去锁定然后删除

        // 以键值去对应找到值
        System.out.println("键值ji的对应为："+map.get("ji"));

        // 替换值replace
        map.replace("ji", 4);
        System.out.println("没问题的话ji键被替换成4："+map.get("ji"));  // 键值唯一，所以只有通过键值寻找

        // 除了指定也可以通过计算的方式改变值
        map.compute("ji", (String, Integer) -> Integer+2);  // 这里的Integer可以换成其余的变量名
        System.out.println("键ji该变为+2后的值:"+map.get("ji"));

        // 改变值除了replace还能用merge
        map.merge("ji", 3, (newvalue, oldvalue) -> newvalue+oldvalue); // 3为newvalue，oldvlue救赎原本的值
        System.out.println("键值ji的新对应值为:"+map.get("ji"));

        //clear() size() isEmpty()
        System.out.println("map的大小为:"+map.size());
        System.out.println("清空了吗？:"+map.isEmpty());
        map.clear();
        System.out.println("清空了吗？:"+map.isEmpty());



        // map.containsKey(key); 返回值boolean 告诉是否是含有keys

        /*
        * 突然想写一下冒泡排序
        * */
//        for(int i = 1; i < arr.length; i++) {
//            boolean flag = true;
//            for(int j = 0; j < arr.length-i; j++) {
//                if(arr[j] > arr[j+1]) {  // 从小到大排序
//                    int temp = arr[j];
//                    arr[j+1] = arr[j];
//                    arr[j] = temp;
//
//                    flag = false;
//                }
//            }
//            if (flag) {
//                break;
//            }
//        }

    }
}
