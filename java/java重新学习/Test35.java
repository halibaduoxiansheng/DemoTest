import java.time.MonthDay;

// һ�־��й̶�����ֵ�ļ�������  ö�ٳ���һ���ô�д��ʽ
public class Test35 {
    public static void main(String[] args) {
        // ʹ��ö�����Ʒ��ʳ���ֵ
        System.out.println("Week�ĵ�һ��:"+Week.Monday);

        // ��������ȥ����
        Order order = new Order(Week.Monday);
        order.show();

        // �ٿ���ö������ĺ���Ч��
        System.out.println("Ϊ:"+Week.Monday.getsome()+Week.Tuesday.getsome()+Week.Wednesday.getsome());

        // ö�����һЩ�ȶ�����
        System.out.println("Mondayλ��:"+Week.Monday.ordinal());
        System.out.println("Mondayλ����Wednesdayλ�����:"+Week.Monday.compareTo(Week.Wednesday)); // 0-2
        System.out.println("����Monday�ַ��������ʽ:"+Week.Monday.toString());
        System.out.println("����Monday�ַ��������ʽ:"+Week.Monday.name()); // ͬ��

        Week ok = Week.valueOf("Wednesday");  // ���ؾ�����ͬ�ַ������Ƶ�ö�ٱ���
        System.out.println("okΪ:"+ok.toString());
        // Week.valueOf("Monday")

        Week[] ch = Week.values();  // ת��Ϊ���� �����������ö������
        for(Week ok1 : ch)
            System.out.print(ok1.toString()+",");


    }
}
class Order {
    Week week;
    public Order(Week week) {
        this.week = week;
    }
    public void show() {
        switch(week) {
            case Monday:
                System.out.println("Ϊ����һ");
                break;
            case Tuesday:
                System.out.println("Ϊ����һ");
                break;
            case Wednesday :
                System.out.println("Ϊ����һ");
                break;
            case Thursday :
                System.out.println("Ϊ����һ");
                break;
            case Friday :
                System.out.println("Ϊ����һ");
                break;
            case Saturday :
                System.out.println("Ϊ����һ");
                break;
            case Sunday :
                System.out.println("Ϊ����һ");
                break;
            default:
                System.out.println("something wrong");
                break;
        }
    }
}
enum Week {  // ö���� ʹ�ùؼ���enum
    Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday;  // �ֺű����Բ��ӣ������к���ĺ����͵ü�
    // ö��������ĺ���
    public String getsome() {
        switch(this) {
            case Monday: return "��";
            case Tuesday: return "��";
            case Wednesday: return "��";
            case Thursday: return "��";
            case Friday: return "ѽ";
            case Saturday: return "Ϊ";
            case Sunday: return "ë?";
            default: return "error!!!";
        }
    }
}
