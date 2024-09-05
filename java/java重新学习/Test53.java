//import java.sql.Connection;
//import java.sql.DriverManager;
//import java.sql.Statement;
//import java.util.*;
//
///*  复习资料
////        List<List<Integer>> res = new ArrayList<>(); // 就是一个List里面嵌套另外一个List
//// 配套的函数有 add  get  remove asList() set() size() toArray(str1)
////        map<Integer, Integer> map1 = new TreeMap<>();
//// 配套的函数有 put() KeySet() values() remove(键值对两个参数都得要) putIfAbsent()
//
////        Stack<Character> stack = new Stack<>();  // 里面的item的元素
//// 配套的函数有 push() pop()
//
////        Queue<Character> queue = new LinkedList<>();  // 注意后面是LinkedList 先进先后
//// 配套的函数有 offer() 访问头部peek()和element() 删除头部：remove()和poll()    size()
//*/
//
//// 在没有确认之前这个test是杂例子
//
//// =========================================================================================================
////   !!!!!!!!!!!!            请转到JDBC文件夹               !!!!!!!!!!!!!!
//// =========================================================================================================
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//public class Test53 {
//    // 说白了，JDBC就是用java语言区操作关系型数据库的API
//    public static void main(String[] args){
//        // 1.注册驱动
////        Class.forName("com.mysql.jdbc.Driver");
//        // 2.获取连接对象
//        String url = "jdbc:mysql://127.0.0.1:3306/db1?useSSL=false";
//        String username = "root";
//        String password = "123456";
//        Connection conn = DriverManager.getConnection(url, username, password);
//
//        // 3.定义sql
//        String sql = "update account set money = 2000 where id = 1";
//        // 4.获取执行sql对象
//        Statement stmt = conn.createStatement();
//        // 5.执行sql
//        int count = stmt.executeUpdate(sql);
//        // 6.处理结果
//        // System.out.println(count);
//        // 7.释放资源
//        stmt.close();
//        conn.close();
//    }
//}
