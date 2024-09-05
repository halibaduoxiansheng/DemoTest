import java.util.logging.Level;
import java.util.logging.Logger;

public class Test39 {
    public static void main(String[] args) {
        //java注解 是元数据 他们于程序的附加信息 不影响程序的执行
        // @ 开头
        Son1 son = new Son1();
        son.display();

        Logger logger = Logger.getLogger(Test39.class.getName());  // 在当前类之后定义一个Logger

        // SEVERE 严重故障 WARNING 警告信息、潜在问题 INFO 常规运行时信息 这三个是默认的
        // CONFIG 配置信息 FINE 普通的开发人员信息
        logger.setLevel(Level.FINE);

        // 断言 请查看 https://www.nhooo.com/java/java-assertions.html
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
