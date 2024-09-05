import java.time.MonthDay;

// 一种具有固定可能值的集的类型  枚举常量一般用大写形式
public class Test35 {
    public static void main(String[] args) {
        // 使用枚举名称访问常量值
        System.out.println("Week的第一个:"+Week.Monday);

        // 产生对象去访问
        Order order = new Order(Week.Monday);
        order.show();

        // 再看看枚举里面的函数效果
        System.out.println("为:"+Week.Monday.getsome()+Week.Tuesday.getsome()+Week.Wednesday.getsome());

        // 枚举类的一些既定方法
        System.out.println("Monday位置:"+Week.Monday.ordinal());
        System.out.println("Monday位置与Wednesday位置相差:"+Week.Monday.compareTo(Week.Wednesday)); // 0-2
        System.out.println("返回Monday字符串表达形式:"+Week.Monday.toString());
        System.out.println("返回Monday字符串表达形式:"+Week.Monday.name()); // 同上

        Week ok = Week.valueOf("Wednesday");  // 返回具有相同字符串名称的枚举变量
        System.out.println("ok为:"+ok.toString());
        // Week.valueOf("Monday")

        Week[] ch = Week.values();  // 转化为数组 不过是特殊的枚举数组
        for(Week ok1 : ch)
            System.out.print(ok1.toString()+",");


    }
}
class Order {
    Week week;
    public Order(Week week) {
        this.week = week;
    }
    public void show() {
        switch(week) {
            case Monday:
                System.out.println("为星期一");
                break;
            case Tuesday:
                System.out.println("为星期一");
                break;
            case Wednesday :
                System.out.println("为星期一");
                break;
            case Thursday :
                System.out.println("为星期一");
                break;
            case Friday :
                System.out.println("为星期一");
                break;
            case Saturday :
                System.out.println("为星期一");
                break;
            case Sunday :
                System.out.println("为星期一");
                break;
            default:
                System.out.println("something wrong");
                break;
        }
    }
}
enum Week {  // 枚举类 使用关键字enum
    Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday;  // 分号本可以不加，但是有后面的函数就得加
    // 枚举类里面的函数
    public String getsome() {
        switch(this) {
            case Monday: return "你";
            case Tuesday: return "好";
            case Wednesday: return "聪";
            case Thursday: return "明";
            case Friday: return "呀";
            case Saturday: return "为";
            case Sunday: return "毛?";
            default: return "error!!!";
        }
    }
}
