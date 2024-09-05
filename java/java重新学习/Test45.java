import com.sun.xml.internal.bind.v2.runtime.output.Encoded;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

public class Test45 {
    public static void main(String[] args) {
        // ���Ǵ�Դ��ȡ��д��Ŀ�����������
        // ������:���ڴ�Դ��ȡ����    �����:���ڽ�����д��Ŀ��

        // ���������������� ���Է�Ϊ �ֽ��� �� �ַ���
        // �����ֽ����������� InputStream �� OutputStream
        // �����ַ����������� Reader �� Writer

        // �Ƚ���      �ֽ���

//        FileInputStream  �� ByteArrayInputStream �� ObjectInputStream ��������
        byte[] array = new byte[100];
        try{  // ���� ���ò�׽�ķ�ʽȥ���ļ�
            InputStream input = new FileInputStream("test.txt");
            System.out.println("�ļ��еĿ����ֽ�:"+input.available());

            input.read(array);  // read���Ҳ��ֻ�ܷ�byte[]
            System.out.println("���ļ��ж�ȡ������:");

//            System.out.println("the data is:"+array);
            String data = new String(array);
            System.out.println("����Ϊ:"+data);

            // �رղ�������
            input.close();
        }catch(Exception e) {
//            System.out.println(e.toString());
            e.getStackTrace();
        }finally {
            System.out.println("over!");
        }

        // ��������OutputStream
        String str = "�Ǿͺ�";
        try{
            // Charset.forName("unicode")
            OutputStream output = new FileOutputStream("test.txt",true);  // Ĭ����false��׷��
            byte[] data1 = str.getBytes();  // ֱ�ӽ����ݶ����˽�ȥ
//            int num = 1;
            // ��ʼд������
//            System.out.println("code way is:"+Character.getName("1"));
            output.write(data1);
//            output.write(num);  // ����ֱ�����Ϊwrite(byte[])
            System.out.println("���ݱ�д���ļ��ɹ�!");

            // �ر��ļ�
            output.close();
        }catch(Exception e) {
            e.getStackTrace();
        }finally {
            System.out.println("over!");
        }
    }
}
