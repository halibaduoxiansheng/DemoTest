import java.util.ArrayList; //��Щ�����Ҫ����ӽ���
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List; // �����б����Ҫ����
// Vector���߳�ͬ����,��ȫ��Ч�ʵ� ArrayList���߳��첽�ģ�Ч�ʸ�
//�б���
public class Test24 {
    // List���ܾ���һ������java����Ĵ���
    public static void main(String[] args){
        //��ʼȥ��������List1,��Щ�������ʹ��List�ӿڵĹ���
        List<String> list1 = new ArrayList<>();//��õ������б� String�������ǵ������������ַ��� ������Integer
//        List<String> list2 = new LinkedList<>(); //��Ȼ����������б�Ҳ�ǲ����
        //������һЩ���õĽӿڷ�����ʹ�� �б��� list1.size()
        list1.add("��");  //add���������Ǵ�ǰ����Ľ���������
        list1.add("��");
        list1.add("ѽ");
        list1.add(3,"Ŷ"); //ʹ��������ֱ�������б���
        System.out.println("List1:"+list1); //���Է���������������������������֮���Ƕ��Ÿ�����������list1����һ������

        String str0 = list1.get(0); //get�����з��±�
        System.out.println("�б����±�Ϊ0���Ǹ�������:"+str0); //���Կ���get�������ǻ�ȡ����
//        System.out.println("List:"+list1); //���ҷ���getֻ��read�����ǽ�������ȡ����

        String removestr0 = list1.remove(0); //���Է���˵�ܲٲܲٵ����������ɾ�� �������ɾ���ķ���ֵ�����ȡ
        System.out.println("��ɾ�����Ǹ�������:"+removestr0+"��List1:"+list1);

        List<String> list3 = new ArrayList<>();
        list3.add("���"); //һ���µĶ��󴴽����б�
        System.out.println("List3:"+list3);
        list3.addAll(list1); //����:��list1�Ķ������ӵ�list3�ĺ���ȥ
        System.out.println("List1:"+list1+"List3:"+list3); //�ɼ��ı���list3����list1û��Ӱ��

        List<String> list4 = new ArrayList<>(Arrays.asList("��", "��", "ѽ")); // ֱ�ӳ�ʼ��
        System.out.println("ֱ�ӳ�ʼ��Ϊ:"+list4);

        //����ArrayListԪ�� set()   ������Ϊ�滻
        ArrayList animals = new ArrayList<>(Arrays.asList("dog", "cot", "robot"));
        animals.set(1, "people"); // ���� ǰΪ�±ꡢ��Ϊ���������ݣ�
        System.out.println(animals);

        ArrayList list5 = new ArrayList<>(Arrays.asList("ni", "hao", "shi", "jie"));
        System.out.println("list5�ĳ���:"+list5.size());  // ���Ⱥ���������length
        list5.removeAll(list5);
        list5.clear();  // Ч��������һ��
        System.out.println(list5);  // ���Ϊ��

        ArrayList list6 = new ArrayList<>(Arrays.asList("ab", "cd", "ef", "gh"));
        String[] str1 = new String[list6.size()];
        list6.toArray(str1);
        for(String item : str1)
            System.out.print(item+","); // ������ת��Ϊ�ַ����������
        //�෴�ľ�Ϊ����
//        ArrayList list7 = new ArrayList<>(Ararys.asList(str1));
    }
}
