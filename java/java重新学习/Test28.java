import java.util.Map;
import java.util.HashMap;
public class Test28 {
    public static void main(String[] args){
        //ʹ��HashMap�ഴ��map
        Map<String, Integer> map = new HashMap<>();

        //��Ԫ�ز���map����
        map.put("niao", 1);  // {niao=1, long=2}
        map.put("long", 2);
        map.put("ji", 3);
        System.out.println("Map:"+map);  // �б���[]����������{}

        //�������ʽ��������
        System.out.println("���У�"+map.entrySet());

        // ��ֵΪ��key��
        System.out.println("��ֵΪ:"+map.keySet());  // Ҳ����put�ĵ�һ��Ԫ�صĵ�һ��ֵ
        // ������Ӧ��ֵ����Ԫ�صĵڶ���ֵ
        System.out.println("ֵΪ:"+map.values());

        int removenum = map.remove("long");
        System.out.println("��ɾ�����Ǹ�����"+removenum);  // ͨ����ֵȥ����Ȼ��ɾ��

        // �Լ�ֵȥ��Ӧ�ҵ�ֵ
        System.out.println("��ֵji�Ķ�ӦΪ��"+map.get("ji"));

        // �滻ֵreplace
        map.replace("ji", 4);
        System.out.println("û����Ļ�ji�����滻��4��"+map.get("ji"));  // ��ֵΨһ������ֻ��ͨ����ֵѰ��

        // ����ָ��Ҳ����ͨ������ķ�ʽ�ı�ֵ
        map.compute("ji", (String, Integer) -> Integer+2);  // �����Integer���Ի�������ı�����
        System.out.println("��ji�ñ�Ϊ+2���ֵ:"+map.get("ji"));

        // �ı�ֵ����replace������merge
        map.merge("ji", 3, (newvalue, oldvalue) -> newvalue+oldvalue); // 3Ϊnewvalue��oldvlue����ԭ����ֵ
        System.out.println("��ֵji���¶�ӦֵΪ:"+map.get("ji"));

        //clear() size() isEmpty()
        System.out.println("map�Ĵ�СΪ:"+map.size());
        System.out.println("�������:"+map.isEmpty());
        map.clear();
        System.out.println("�������:"+map.isEmpty());



        // map.containsKey(key); ����ֵboolean �����Ƿ��Ǻ���keys

        /*
        * ͻȻ��дһ��ð������
        * */
//        for(int i = 1; i < arr.length; i++) {
//            boolean flag = true;
//            for(int j = 0; j < arr.length-i; j++) {
//                if(arr[j] > arr[j+1]) {  // ��С��������
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
