// 说到匿名类了哦
class Father {  // 这的class换成interface 就可以换成实现接口的匿名类 当然，里面得有没有完成的方法来去实现
    public void toString1() {
        System.out.println("输出在外的!");
    }
}
class Son {
    void create() {
        // 创建匿名类，继承Father类
        Father son = new Father() {
            public void toString1() {
                System.out.println("输出在内的!");  // 这个覆盖了父类的toString1
          }
        };   // 请十分注意此处的分号，这是匿名类的表示一般
        son.toString1();
    }
}
public class Test33 {
    public static void main(String[] args) {
        Son son1 = new Son();
        son1.create();
    }
}
