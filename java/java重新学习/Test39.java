import java.util.logging.Level;
import java.util.logging.Logger;

public class Test39 {
    public static void main(String[] args) {
        //javaע�� ��Ԫ���� �����ڳ���ĸ�����Ϣ ��Ӱ������ִ��
        // @ ��ͷ
        Son1 son = new Son1();
        son.display();

        Logger logger = Logger.getLogger(Test39.class.getName());  // �ڵ�ǰ��֮����һ��Logger

        // SEVERE ���ع��� WARNING ������Ϣ��Ǳ������ INFO ��������ʱ��Ϣ ��������Ĭ�ϵ�
        // CONFIG ������Ϣ FINE ��ͨ�Ŀ�����Ա��Ϣ
        logger.setLevel(Level.FINE);

        // ���� ��鿴 https://www.nhooo.com/java/java-assertions.html
    }
}
class Father1 {
    void display() {
        System.out.println("I am father !");
    }
}
class Son1 extends Father1{
    @Override
    void display() {
        System.out.println("I am son !");
    }
}
