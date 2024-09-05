import java.util.TreeMap;
import java.util.Map;
public class Test29 {
    public static void main(String[] args){
//        Map<Key, Value> map = new TreeMap<>();  // key是键 Value是指
        Map<String, Integer> map = new TreeMap<>();
        map.put("long", 1);
        map.put("niao", 2);
        map.putIfAbsent("hua", 3);  // 代表如果不存在才会插入其中,位置无所谓
        System.out.println("对应为:"+map);

        Map<String, Integer> map1 = new TreeMap<>();
        map1.put("she", 4);  // 可以为空（null）
        map1.putAll(map);
        System.out.println("将map中的加到map1中后，map1为："+map1);

        // 返回所有key值
        System.out.println(map.keySet());

        // 返回所有value值
        System.out.println(map.values());

        // get去锁定键值
        System.out.println(map1.get("she"));

        // remove 删除 删除的值可以不接着
//        int num0 = map1.remove("she");
        boolean ok = map1.remove("she", 4);  // 写两个就是返回true或则false
//        System.out.println("num0:"+num0);
        System.out.println("ok:"+ok);

//        replace() 键值锁定，改变值
//        entrySet() 返回所有键值映射 firstKey() lastKey() firstEntry() lastEntry()

    }
}
