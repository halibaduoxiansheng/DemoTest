enum Week1 {  // ��Ҫ��֮ǰ�����ļ��е������ظ���
    Monday("����һ"),Tuesday("���ڶ�");
    private final String week;
    private Week1(String week) {
        this.week = week;
    }
    public String getWeek() {
        return week;
    }
}
enum Week2 {
    // �½���ö����
    Tuesday {
        public String toString() {
            return "����";
        }
    };
}
public class Test36 {
    public static void main(String[] args) {
        Week1 week = Week1.Monday;
        System.out.println("��:"+week.getWeek());
        System.out.println("�ı���������?"+Week2.Tuesday.toString());
    }
}

