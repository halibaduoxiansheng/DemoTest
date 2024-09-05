import java.lang.Class;
import java.lang.reflect.*;
interface Animal {
    public void display();
}
interface Mammal {
    public void makeSound();
}
class Dog implements Animal,Mammal {
    public void display() {
        System.out.println("I AM A DOG !");
    }
    public void makeSound() {
        System.out.println("bark bark ！");
    }
}
public class Test37 {
    public static void main(String[] args) {
        //在学习之前你需要知道一个类 叫做Class 该类运行时保留了有关类和对象的所有信息
        try {
            Dog dog = new Dog();
            Class obj = dog.getClass(); // getClass 使用特定类的对象来创建新的对象Class
            // 对应的forName()为放回Class对象 Class c1 = Class.forName("obj");

            // 查找由Dog实现的接口
            Class[] objInterface = obj.getInterfaces();
            for(Class c : objInterface){
                // 打印接口名称
                System.out.println("为:"+c.getName());
            }

            int modifier = obj.getModifiers();
            System.out.println("修饰符:"+Modifier.toString(modifier)); // 默认的就不会输出什么
            Test37 test = new Test37();
            Class obj1 = test.getClass();
            int modifier1 = obj1.getModifiers();
            System.out.println("修饰符:"+Modifier.toString(modifier1));  // 这个就会输出public
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
}
