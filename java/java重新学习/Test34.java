public class Test34 {
    public static void main(String[] args) {
        Test test1;
        test1 = Test.getInstance();
        test1.getConnection();
    }
}
class Test {  // 单例类
    private static Test test;  // 为类类型字段
    private Test (){}  // private的无参构造函数 private可防止在类外部创建对象

    public static Test getInstance() {  // static方法直接有类名去访问
        // 如果还没有创建对象就现在开始创建对象
        if(test == null) {
            test = new Test();
        }
        // 返回单例对象 类的实例犯放回给外部
        return test;  // 有的话就直接返回
    }

    public void getConnection() {  // 一般名字第一个字母都是大写
        System.out.println("已经连接到数据库了！");
    }
}
