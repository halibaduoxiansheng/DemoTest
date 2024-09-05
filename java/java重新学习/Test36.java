enum Week1 {  // 不要与之前其余文件中的名字重复了
    Monday("星期一"),Tuesday("星期二");
    private final String week;
    private Week1(String week) {
        this.week = week;
    }
    public String getWeek() {
        return week;
    }
}
enum Week2 {
    // 新建的枚举类
    Tuesday {
        public String toString() {
            return "哈哈";
        }
    };
}
public class Test36 {
    public static void main(String[] args) {
        Week1 week = Week1.Monday;
        System.out.println("是:"+week.getWeek());
        System.out.println("改变了内容吗?"+Week2.Tuesday.toString());
    }
}

