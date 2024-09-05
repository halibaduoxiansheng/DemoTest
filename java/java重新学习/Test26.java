public class Test26 {
    public static void main(String[] args){
        String str0 = "abcdefg";
        char[] ch0 = new char[str0.length()];
        System.out.println("字符串的下标为1的字母是:"+str0.charAt(1));
        ch0 = str0.toCharArray();
        for(char i : ch0)
            System.out.print(i);

        //接来下说下数组转化为字符串
        char[] ch1 = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
        String str3 = String.copyValueOf(ch1);
        System.out.println("\n数组ch1转化为字符串:"+str3);

        int num0 = 1;
        String str1 = String.valueOf(num0);  // 淡然最简单的就是 num0 + "" 直接就好
        System.out.println("数字nums0转化为字符串:"+str1.charAt(0));
        String str2 = "12";
        int num1 = Integer.parseInt(str2); //这是将字符串转化为数字
        System.out.println("字符串str2转化为数字:"+num1);
        char ch4 = '1';  // 先将这个单个字符变为数字
        System.out.println("(int)ch4是输出ASCII码值！"+(int)ch4);
        int num2 = ch4 - '0';
        System.out.println("ch4-'0'才是"+num2);  // 这才是单个字符转化为数字
        int num3 = 1;
        String str4 = String.valueOf(num3);
        char ch7 = str4.charAt(0);
        System.out.println("单个数字num3转化为字符:"+ch7);  // 可见需要先转化为字符串再提取

        char ch2 = 'a', ch3 = ' ';
        if(Character.isSpace(ch2))
            System.out.println("ch2是空格");
        if(Character.isSpaceChar(ch3))
            System.out.println("ch3是空格");

        //将字母a变为b
        char ch5 = 'a';
        char ch6 = (char)(ch5+1);
        System.out.println("为:"+ch6);

        //substring、startsWith、endsWith
        String str5 = "abcdefg";
        boolean answer1 = str5.startsWith("a"); // 注意是"" 单引号不行
        boolean answer2 = str5.endsWith("f");
        str5 = str5.substring(0,2);   // 从下标0开始，但不包括下标2
        System.out.println("str5为:"+str5);
        System.out.println("answer1="+answer1+",answer2"+answer2);


        // Arrays.sort(ch);  是递增排序   Array.sort(ch,begin,end) 不包括end
        // Arrays.fill(ch,2);  将2放入ch的每一个位置 Arrays.fill(ch,begin,end,value)  不包括end
    }
}
