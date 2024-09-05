public class Employee implements java.io.Serializable{  // 服务于Test50
    public String name;
    public String address;
    public transient int SSN;  // transient表示文件不是序列里面的
    public int number;
    public void mailCheck() {
        System.out.println("Mail a check to:" + name + " "+ address);
    }
}
