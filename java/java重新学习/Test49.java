
public class Test49 {
    public static void main(String[] args) {
        //javac xxx.java  后 java xxx
        for(String str : args) {
            System.out.println(str + " ");
        }

        // split
        String str = "ab-cd-ef-gh";
        for(String str1 : str.split("-"))  // 这里必须是"
            System.out.print(str1+",");

        // compareTo
        String str2="f",str3="a";  // 只比较第一个字母  A:65  a:97
        int resp = str2.compareTo(str3);
        System.out.println("\nresp="+resp);

        // compare
        String str4="a",str5="B";  // 也是比较第一个字母，只不过这个忽略大小写
        int resp1 = str4.compareToIgnoreCase(str5);
        System.out.println("resp1="+resp1);

        // replace
        String str6="abc",str7="";
        str7=str6;
        str6.replace('a','k');  // 只是形式上改变,不会影响实质str6的变化
        System.out.println("str6="+str6);
        System.out.println("替换的str6="+str6.replace('a','k'));
        str7=str6.replace('a','p');  // 这才是改变的法子
        System.out.println("改变的str7="+str7);

        // substring
        String str8="abcdefg";
        System.out.println("str8[0-2]:"+str8.substring(0,3));
        System.out.println("但实质上的str8不会改变,还是:"+str8);

        // equals 与 equalsIgnoreCase
        String str9="abc",str10="abc",str11="ABc";
        if(str9.equals(str10))
            System.out.println("str9 and str10 is equal");
        if(str9.equalsIgnoreCase(str11))
            System.out.println("忽略大小写还是一样的case9和case11");

        // contains
        String str12="abcdef",str13="ab";
        if(str12.contains(str13))
            System.out.println("str13 is in str12 !");

        // indexOf
        String str14="abcdefg";
        System.out.println("字母c首次出现的位置:"+str14.indexOf('c'));
        System.out.println("字符串cde首次出现的位置"+str14.indexOf("cde"));  // 不存在就会返回-1

        // trim
        String str15=" abcdef ";
        System.out.println("str15删除空格后:"+str15.trim());  // 可以删除前后的空格

        // charAt
        String str16="abcd";
        System.out.println("the index(1) of str16 is :"+str16.charAt(1));  // 只能返回下标字母，而不能赋值改变

        // toLowerCase toUpperCase
        String str17="DSsdD";
        System.out.println("the lower of str17 is :"+str17.toLowerCase());  // 原本的str17是不会改变的
        System.out.println("the Upper of str17 is :"+str17.toUpperCase());

        // concat 就是 +
        String str18="abc", str19="def";
        String str20 = str18.concat(str19);
        System.out.println("is :"+str20);

        // ValueOf
        int num = 123;
        String str21 = String.valueOf(num);
        System.out.println("为:"+str21);

        // starsWith endsWith
        String str22 = "abcdefg";
        if(str22.startsWith("a",0))  // 必须使用" 后面的那个是开始查找的位置
            System.out.println("the first character of str22 is a");
        if(str22.endsWith("g"))
            System.out.println("the end character of str22 is g");

        // isEmpty
        String str23 = "";  // 只能用于字符串 而不能使用字符
        if(str23.isEmpty())  // 检查是否为空
            System.out.println("str23 is empty");

        // getBytes()  得到字符串的字节序列
        byte[] data = new byte[100];
        String str24 = "abcdefg";
        data = str24.getBytes();
        System.out.println("data="+data);

        // join()
        String str25 = String.join("-","ni","hao","ya");  // ni-hao-ya
        System.out.println("str25="+str25);

        // replaceFirst()
        String str26 = "abcd";
        str26=str26.replaceFirst("ab","gg");  // 从左到右将第一个匹配的子字符串替换成gg
        System.out.println("str26="+String.format(str26));  // 返回格式化的字符串
    }
}
