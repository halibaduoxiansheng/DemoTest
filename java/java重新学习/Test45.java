import com.sun.xml.internal.bind.v2.runtime.output.Encoded;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

public class Test45 {
    public static void main(String[] args) {
        // 流是从源读取并写入目标的数据序列
        // 输入流:用于从源读取数据    输出流:用于将数据写入目标

        // 根据流包含的数据 可以分为 字节流 和 字符流
        // 所有字节流都派生于 InputStream 和 OutputStream
        // 所有字符流都派生于 Reader 和 Writer

        // 先讲讲      字节流

//        FileInputStream  和 ByteArrayInputStream 和 ObjectInputStream 三个子类
        byte[] array = new byte[100];
        try{  // 必须 采用捕捉的方式去打开文件
            InputStream input = new FileInputStream("test.txt");
            System.out.println("文件中的可用字节:"+input.available());

            input.read(array);  // read李阿敏也是只能放byte[]
            System.out.println("从文件中读取的数据:");

//            System.out.println("the data is:"+array);
            String data = new String(array);
            System.out.println("数据为:"+data);

            // 关闭不能忘记
            input.close();
        }catch(Exception e) {
//            System.out.println(e.toString());
            e.getStackTrace();
        }finally {
            System.out.println("over!");
        }

        // 接下来将OutputStream
        String str = "那就好";
        try{
            // Charset.forName("unicode")
            OutputStream output = new FileOutputStream("test.txt",true);  // 默认是false不追加
            byte[] data1 = str.getBytes();  // 直接将数据读入了进去
//            int num = 1;
            // 开始写入数据
//            System.out.println("code way is:"+Character.getName("1"));
            output.write(data1);
//            output.write(num);  // 可以直接理解为write(byte[])
            System.out.println("数据被写入文件成功!");

            // 关闭文件
            output.close();
        }catch(Exception e) {
            e.getStackTrace();
        }finally {
            System.out.println("over!");
        }
    }
}
