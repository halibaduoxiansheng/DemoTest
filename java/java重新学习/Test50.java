import java.io.*;

public class Test50 {
    public static void main(String[] args) {
        //序列化  文件中有个Employee是用于此类的
        Employee e = new Employee();
        e.name = "Ran ali";
        e.address = "jiangxi PoYang";
        e.SSN=111333;
        e.number=121;
        try {
            FileOutputStream file = new FileOutputStream("employee.ser");
            ObjectOutputStream out = new ObjectOutputStream(file);
            out.writeObject(e);
            out.close();
            file.close();
            System.out.println("everything is ok !");
        }catch(Exception i) {  // 注意上面已经定义了e,所以不能再重复使用
            i.getStackTrace();
        }finally {
            System.out.println("over!");
        }


        // 反序列化等以后再补充
    }
}
