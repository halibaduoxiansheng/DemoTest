public class Test34 {
    public static void main(String[] args) {
        Test test1;
        test1 = Test.getInstance();
        test1.getConnection();
    }
}
class Test {  // ������
    private static Test test;  // Ϊ�������ֶ�
    private Test (){}  // private���޲ι��캯�� private�ɷ�ֹ�����ⲿ��������

    public static Test getInstance() {  // static����ֱ��������ȥ����
        // �����û�д�����������ڿ�ʼ��������
        if(test == null) {
            test = new Test();
        }
        // ���ص������� ���ʵ�����Żظ��ⲿ
        return test;  // �еĻ���ֱ�ӷ���
    }

    public void getConnection() {  // һ�����ֵ�һ����ĸ���Ǵ�д
        System.out.println("�Ѿ����ӵ����ݿ��ˣ�");
    }
}
