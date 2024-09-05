import java.util.Scanner;

public class Test31 {
    public static void main(String[] args){
        // 先进一个数据进去玩玩
        Scanner reader = new Scanner(System.in);
        ListNode head = new ListNode(1);
        ListNode list0 = head;
        System.out.println("链表中的数据为:"+head.val);
//        System.out.println("开始读入第二个数据!");  // error 似乎某处表示按照c语言的形式
//        head = head.next;
//        System.out.println("请输入第二个数据:");
//        int b = reader.nextInt();
//        head.val = b;
//        System.out.println("为："+head.val);
        for(int i = 0; i < 3; i++) {
            System.out.print("\n第"+(i+2)+"个数据输入为:");
            int temp = reader.nextInt();
//            list0.val = temp;  // 不是通过赋值的方式传入值
            ListNode node = new ListNode(temp);  // 有点像代孕
            list0.next = node;
            list0 = list0.next;
        }
        System.out.println("输出:");
        ListNode node1 = head;
        for(int i = 0; node1 != null; i++) {
            System.out.print(node1.val+",");
            node1 = node1.next;
        }

        // 插入结点值为5的数据 (此处选择结点值为3的后面插入)
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
        // 成功插入数据 再试试在尾部插入结点

        System.out.println("尾部插入数据6后:");
        ListNode node3 = head;
        while(node3.next != null) {
            node3 = node3.next;
        }
        // 只要出了这个while循环就说明“指针”已经指到了最后一个了
        ListNode newnode1 = new ListNode(6);
        node3.next = newnode1;

        ListNode head1 = head;
        while(head1 != null) {
            System.out.print(head1.val+",");
            head1 = head1.next;
        }
    }
}
// 下面的类就是链表类的抒写
class ListNode {
    int val;
    ListNode next;
    ListNode() {} // 构造函数
    ListNode(int val) {this.val = val;}
    ListNode(int val , ListNode next) {this.val = val; this.next = next; }
}