//import java.sql.Connection;
//import java.sql.DriverManager;
//import java.sql.Statement;
//import java.util.*;
//
///*  ��ϰ����
////        List<List<Integer>> res = new ArrayList<>(); // ����һ��List����Ƕ������һ��List
//// ���׵ĺ����� add  get  remove asList() set() size() toArray(str1)
////        map<Integer, Integer> map1 = new TreeMap<>();
//// ���׵ĺ����� put() KeySet() values() remove(��ֵ��������������Ҫ) putIfAbsent()
//
////        Stack<Character> stack = new Stack<>();  // �����item��Ԫ��
//// ���׵ĺ����� push() pop()
//
////        Queue<Character> queue = new LinkedList<>();  // ע�������LinkedList �Ƚ��Ⱥ�
//// ���׵ĺ����� offer() ����ͷ��peek()��element() ɾ��ͷ����remove()��poll()    size()
//*/
//
//// ��û��ȷ��֮ǰ���test��������
//
//// =========================================================================================================
////   !!!!!!!!!!!!            ��ת��JDBC�ļ���               !!!!!!!!!!!!!!
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
//    // ˵���ˣ�JDBC������java������������ϵ�����ݿ��API
//    public static void main(String[] args){
//        // 1.ע������
////        Class.forName("com.mysql.jdbc.Driver");
//        // 2.��ȡ���Ӷ���
//        String url = "jdbc:mysql://127.0.0.1:3306/db1?useSSL=false";
//        String username = "root";
//        String password = "123456";
//        Connection conn = DriverManager.getConnection(url, username, password);
//
//        // 3.����sql
//        String sql = "update account set money = 2000 where id = 1";
//        // 4.��ȡִ��sql����
//        Statement stmt = conn.createStatement();
//        // 5.ִ��sql
//        int count = stmt.executeUpdate(sql);
//        // 6.������
//        // System.out.println(count);
//        // 7.�ͷ���Դ
//        stmt.close();
//        conn.close();
//    }
//}
