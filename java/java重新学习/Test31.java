import java.util.Scanner;

public class Test31 {
    public static void main(String[] args){
        // �Ƚ�һ�����ݽ�ȥ����
        Scanner reader = new Scanner(System.in);
        ListNode head = new ListNode(1);
        ListNode list0 = head;
        System.out.println("�����е�����Ϊ:"+head.val);
//        System.out.println("��ʼ����ڶ�������!");  // error �ƺ�ĳ����ʾ����c���Ե���ʽ
//        head = head.next;
//        System.out.println("������ڶ�������:");
//        int b = reader.nextInt();
//        head.val = b;
//        System.out.println("Ϊ��"+head.val);
        for(int i = 0; i < 3; i++) {
            System.out.print("\n��"+(i+2)+"����������Ϊ:");
            int temp = reader.nextInt();
//            list0.val = temp;  // ����ͨ����ֵ�ķ�ʽ����ֵ
            ListNode node = new ListNode(temp);  // �е������
            list0.next = node;
            list0 = list0.next;
        }
        System.out.println("���:");
        ListNode node1 = head;
        for(int i = 0; node1 != null; i++) {
            System.out.print(node1.val+",");
            node1 = node1.next;
        }

        // ������ֵΪ5������ (�˴�ѡ����ֵΪ3�ĺ������)
        ListNode node2 = head;
        while(true) {
            if (node2.val == 3) {
                ListNode newnode = new ListNode(5);
                newnode.next = node2.next;
                node2.next = newnode;
                break;
            }
            else
                node2 = node2.next;
        }
        // �ɹ��������� ��������β��������

        System.out.println("β����������6��:");
        ListNode node3 = head;
        while(node3.next != null) {
            node3 = node3.next;
        }
        // ֻҪ�������whileѭ����˵����ָ�롱�Ѿ�ָ�������һ����
        ListNode newnode1 = new ListNode(6);
        node3.next = newnode1;

        ListNode head1 = head;
        while(head1 != null) {
            System.out.print(head1.val+",");
            head1 = head1.next;
        }
    }
}
// �������������������д
class ListNode {
    int val;
    ListNode next;
    ListNode() {} // ���캯��
    ListNode(int val) {this.val = val;}
    ListNode(int val , ListNode next) {this.val = val; this.next = next; }
}