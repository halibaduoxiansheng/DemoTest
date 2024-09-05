import javax.annotation.processing.Filer;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.security.spec.EncodedKeySpec;
import java.util.Scanner;

public class Test48 {
    public static void main(String[] args) {
        File file = new File("wahaha.txt");
        try {
            boolean ok = file.createNewFile();

            if(ok) {
                System.out.println("create file is ok!");
            }else {
                System.out.println("create file is fail!");
            }
        }catch(Exception e) {
            e.getStackTrace();
        }finally {
            System.out.println("over!");
        }

        // 写入数据
        String data = "China is a beautiful Country !";
        try {
            FileWriter output = new FileWriter("wahaha.txt", true);


            output.write(data);
            System.out.println("write completed !");

            output.close();
        }catch (Exception e) {
            e.getStackTrace();
        }finally {
            System.out.println("over!");
        }


        // 既然文件已经创建，那么便开始读取
        char[] array = new char[100];
        try {
            FileReader read = new FileReader("wahaha.txt");

            read.read(array);
            System.out.print("data is:"+array+"\n");

            read.close();
        }catch (Exception e) {
            e.getStackTrace();
        }finally {
            System.out.println("over!");
        }

        System.out.println("Do you want to delete the file? yes or no?");
        System.out.print("please input your choose:");
        Scanner reader = new Scanner(System.in);
        String answer = reader.nextLine();
        if(answer.equals("yes")) {
            File file1 = new File("wahaha.txt");
            boolean ok1 = file1.delete();
            if(ok1) {
                System.out.println("delete success!");
            } else {
                System.out.println("some wrong!");
            }
        }

        // 包装类
        int a = 1;
        double b = 1.2f;
        Integer aOBJ = Integer.valueOf(a);
        Double bOBJ = Double.valueOf(b);

        if(aOBJ instanceof Integer) {
            System.out.println("数据a(1)为整数类的！");
        }
        if(bOBJ instanceof Double) {  // 如此这般后 int a = null; 将不是错误了
            System.out.println("数据b(1.2f)属于浮点数类型double的!");
        }
        Integer c=null;
        if(c == null) {
            System.out.println("ok");
        }
    }
}
