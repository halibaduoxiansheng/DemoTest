// ˵����������Ŷ
class Father {  // ���class����interface �Ϳ��Ի���ʵ�ֽӿڵ������� ��Ȼ���������û����ɵķ�����ȥʵ��
    public void toString1() {
        System.out.println("��������!");
    }
}
class Son {
    void create() {
        // ���������࣬�̳�Father��
        Father son = new Father() {
            public void toString1() {
                System.out.println("������ڵ�!");  // ��������˸����toString1
          }
        };   // ��ʮ��ע��˴��ķֺţ�����������ı�ʾһ��
        son.toString1();
    }
}
public class Test33 {
    public static void main(String[] args) {
        Son son1 = new Son();
        son1.create();
    }
}
