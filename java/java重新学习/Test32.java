public class Test32 {
    public static void main(String[] args) {
        //嵌套类的使用 即在一个类里面写上类外一个类
        //分为 非静态嵌套类 和 静态嵌套类
        // 里面的类 叫 inner class（内部类）
        CPU cpu = new CPU();  // 先用最外部的类定义出一个一个 大对象

        CPU.Processer processor = cpu.new Processer();  // 外类.内类 方式使用内部类
        CPU.RAM ram = cpu.new RAM();  // 创建对象仍旧需要使用外部类的能力

        System.out.println("Processer cache is:"+processor.getCache());
        System.out.println("RAM clock speed is:"+ram.getClockSpeed());

        // 静态类的使用
        motherborad.USA usa = new motherborad.USA(); // 区分:不在需要最外类创建对象
        System.out.println("总和:"+usa.getsbsum());
    }
}
class CPU {
    CPU (){}
    double price;
    class Processer {
        // 嵌套内部成员
        double cores;
        String manufacturer;

        double getCache() {
            return 4.3;
        }
    }

    // 嵌套受保护的类
    protected class RAM {
        double memory;
        String manufacturer;

        double getClockSpeed() {
            return 5.5;
        }
    }
}
class motherborad {
    static class USA {
        int sb1 = 1;
        int sb2 = 2;
        int getsbsum() {
            return sb1+sb2;
        }
    }
}