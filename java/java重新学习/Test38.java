// 异常的类型:无效的用户的输入,设备故障,网络连接丢失，物理限制，代码错误，打开一个不可用的文件
// Throwable分为error和Exception Exception再分RuntimeException和IOException

// Error是程序员无法控制的，所以不该放时间处理错误 而是放在异常的上面
// 当方法内出现异常时，其中会产生一个对象 其中包含了

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

// RuntimeException 运行时发现 IOException是编译时发现
// try{}catch(){}finally{}去看Test13
public class Test38 {
    public static void main(String[] args) {
        // 异常处理
        try{
            Work();
            System.out.println("");
            findFile();
        }
        catch(IOException e){
            System.out.println(e.getMessage());
        }
    }

    private static void Work() throws IOException{  // throws声明其中可能发生的异常
        File newfile = new File("test1.txt");  // 换称test.txt可用
        FileInputStream stream = new FileInputStream(newfile);
    }

    private static void findFile() throws IOException {
        throw new IOException("文件没找到");
    }
}

