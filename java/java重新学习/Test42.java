import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class Test42 {
    public static void main(String[] args) {
        //Set ��List��ͬ���ǲ��ܰ����ظ���Ԫ��
        Set<Integer> set = new HashSet<>();

        // д��Ԫ��
        set.add(1);
        set.add(2);
//        set.add(2);  // ��������д����һ����Ԫ�أ���ֻ�ᴢ���һ��д��
        set.add(3);
//        set.add(2);
        set.add(4);

        System.out.println("set���:"+set);

        Set<Integer> set1 = new HashSet<>();
        set1.addAll(set);
        System.out.println("set1���:"+set1);

        // ѭ������
        Iterator<Integer> iterate = set1.iterator();  // ��ȻҲ���Կ���ʹ�� TreeSet ������ HashSet
        while(iterate.hasNext()) {
            System.out.print(iterate.next());
            System.out.print(", ");
        }

        // ɾ�� remove
        boolean removeInt = set1.remove(1);
        boolean removeInt1 = set1.remove(5);  // �����ڵ����ݾͻ᷵��false ��ɾ��ʧ��
        System.out.println("����1��ɾ���ɹ�����:"+removeInt+removeInt1);
        boolean value = set1.removeAll(set1);  // ȫ��ɾ�� ��ʵ�����зŵ��������ֱ�Ӿ��ǲ

        // set2.retainAll(set1)  ->����   size() ��С
        // contains() ���ز������� ˵���Ƿ����
        System.out.println("set:"+set);
        System.out.println("set1�Ƿ�Ϊ����(�Ѿ�����removeAll������):"+set1.isEmpty());
        System.out.println("set�Ĵ�СΪ:"+set.size());
        System.out.println("�����Ƿ����1:"+set.contains(1));
    }
}
