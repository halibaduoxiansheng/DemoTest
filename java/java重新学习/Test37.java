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
        System.out.println("bark bark ��");
    }
}
public class Test37 {
    public static void main(String[] args) {
        //��ѧϰ֮ǰ����Ҫ֪��һ���� ����Class ��������ʱ�������й���Ͷ����������Ϣ
        try {
            Dog dog = new Dog();
            Class obj = dog.getClass(); // getClass ʹ���ض���Ķ����������µĶ���Class
            // ��Ӧ��forName()Ϊ�Ż�Class���� Class c1 = Class.forName("obj");

            // ������Dogʵ�ֵĽӿ�
            Class[] objInterface = obj.getInterfaces();
            for(Class c : objInterface){
                // ��ӡ�ӿ�����
                System.out.println("Ϊ:"+c.getName());
            }

            int modifier = obj.getModifiers();
            System.out.println("���η�:"+Modifier.toString(modifier)); // Ĭ�ϵľͲ������ʲô
            Test37 test = new Test37();
            Class obj1 = test.getClass();
            int modifier1 = obj1.getModifiers();
            System.out.println("���η�:"+Modifier.toString(modifier1));  // ����ͻ����public
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
}
