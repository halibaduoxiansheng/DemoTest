import java.util.TreeMap;
import java.util.Map;
public class Test29 {
    public static void main(String[] args){
//        Map<Key, Value> map = new TreeMap<>();  // key�Ǽ� Value��ָ
        Map<String, Integer> map = new TreeMap<>();
        map.put("long", 1);
        map.put("niao", 2);
        map.putIfAbsent("hua", 3);  // ������������ڲŻ��������,λ������ν
        System.out.println("��ӦΪ:"+map);

        Map<String, Integer> map1 = new TreeMap<>();
        map1.put("she", 4);  // ����Ϊ�գ�null��
        map1.putAll(map);
        System.out.println("��map�еļӵ�map1�к�map1Ϊ��"+map1);

        // ��������keyֵ
        System.out.println(map.keySet());

        // ��������valueֵ
        System.out.println(map.values());

        // getȥ������ֵ
        System.out.println(map1.get("she"));

        // remove ɾ�� ɾ����ֵ���Բ�����
//        int num0 = map1.remove("she");
        boolean ok = map1.remove("she", 4);  // д�������Ƿ���true����false
//        System.out.println("num0:"+num0);
        System.out.println("ok:"+ok);

//        replace() ��ֵ�������ı�ֵ
//        entrySet() �������м�ֵӳ�� firstKey() lastKey() firstEntry() lastEntry()

    }
}
