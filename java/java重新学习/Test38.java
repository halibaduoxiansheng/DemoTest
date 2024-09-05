// �쳣������:��Ч���û�������,�豸����,�������Ӷ�ʧ���������ƣ�������󣬴�һ�������õ��ļ�
// Throwable��Ϊerror��Exception Exception�ٷ�RuntimeException��IOException

// Error�ǳ���Ա�޷����Ƶģ����Բ��÷�ʱ�䴦����� ���Ƿ����쳣������
// �������ڳ����쳣ʱ�����л����һ������ ���а�����

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

// RuntimeException ����ʱ���� IOException�Ǳ���ʱ����
// try{}catch(){}finally{}ȥ��Test13
public class Test38 {
    public static void main(String[] args) {
        // �쳣����
        try{
            Work();
            System.out.println("");
            findFile();
        }
        catch(IOException e){
            System.out.println(e.getMessage());
        }
    }

    private static void Work() throws IOException{  // throws�������п��ܷ������쳣
        File newfile = new File("test1.txt");  // ����test.txt����
        FileInputStream stream = new FileInputStream(newfile);
    }

    private static void findFile() throws IOException {
        throw new IOException("�ļ�û�ҵ�");
    }
}

