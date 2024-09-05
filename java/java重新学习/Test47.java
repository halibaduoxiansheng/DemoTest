import java.util.Scanner;
import java.lang.FunctionalInterface;
@FunctionalInterface
interface MyInterface {
    public double getPiValue();
}
interface MyInterface1 {
    String getValue(String str);
}
interface Myinterface2<T> {
    T func(T t);
}
public class Test47 {
    public static void main(String[] args) {
        //如果Java接口仅包含一个抽象方法，则将其称为功能接口
        MyInterface resp;

        // lambda表达式
        resp = () -> 3.1415;
        System.out.println("PI is:"+resp.getPiValue());


        MyInterface1 resp1 = (str) -> {
            String result="";

            for(int i = str.length()-1; i >= 0; i--) {
                result += str.charAt(i);
            }
            return result;
        };
        System.out.println("The opposite of HELLO is : "+resp1.getValue("HELLO"));


        // 范类
        Myinterface2<String> resp2= (str) -> {
          String result="";
          for(int i = str.length()-1; i >=0; i--) {
              result += str.charAt(i);
          }
          return result;
        };
        System.out.println("The opposite of WORLD is :"+resp2.func("WORLD"));

        Myinterface2<Integer> resp3 = (n) -> {
            for(int i = n; i >= 0; i--) {
                System.out.print(i+",");  // 没调用就直接输出了
                continue;
            }
            return null;
        };
        System.out.println("Smaller than 10 are:"+resp3.func(10));
    }
}
