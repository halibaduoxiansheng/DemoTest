public class Test26 {
    public static void main(String[] args){
        String str0 = "abcdefg";
        char[] ch0 = new char[str0.length()];
        System.out.println("�ַ������±�Ϊ1����ĸ��:"+str0.charAt(1));
        ch0 = str0.toCharArray();
        for(char i : ch0)
            System.out.print(i);

        //������˵������ת��Ϊ�ַ���
        char[] ch1 = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
        String str3 = String.copyValueOf(ch1);
        System.out.println("\n����ch1ת��Ϊ�ַ���:"+str3);

        int num0 = 1;
        String str1 = String.valueOf(num0);  // ��Ȼ��򵥵ľ��� num0 + "" ֱ�Ӿͺ�
        System.out.println("����nums0ת��Ϊ�ַ���:"+str1.charAt(0));
        String str2 = "12";
        int num1 = Integer.parseInt(str2); //���ǽ��ַ���ת��Ϊ����
        System.out.println("�ַ���str2ת��Ϊ����:"+num1);
        char ch4 = '1';  // �Ƚ���������ַ���Ϊ����
        System.out.println("(int)ch4�����ASCII��ֵ��"+(int)ch4);
        int num2 = ch4 - '0';
        System.out.println("ch4-'0'����"+num2);  // ����ǵ����ַ�ת��Ϊ����
        int num3 = 1;
        String str4 = String.valueOf(num3);
        char ch7 = str4.charAt(0);
        System.out.println("��������num3ת��Ϊ�ַ�:"+ch7);  // �ɼ���Ҫ��ת��Ϊ�ַ�������ȡ

        char ch2 = 'a', ch3 = ' ';
        if(Character.isSpace(ch2))
            System.out.println("ch2�ǿո�");
        if(Character.isSpaceChar(ch3))
            System.out.println("ch3�ǿո�");

        //����ĸa��Ϊb
        char ch5 = 'a';
        char ch6 = (char)(ch5+1);
        System.out.println("Ϊ:"+ch6);

        //substring��startsWith��endsWith
        String str5 = "abcdefg";
        boolean answer1 = str5.startsWith("a"); // ע����"" �����Ų���
        boolean answer2 = str5.endsWith("f");
        str5 = str5.substring(0,2);   // ���±�0��ʼ�����������±�2
        System.out.println("str5Ϊ:"+str5);
        System.out.println("answer1="+answer1+",answer2"+answer2);


        // Arrays.sort(ch);  �ǵ�������   Array.sort(ch,begin,end) ������end
        // Arrays.fill(ch,2);  ��2����ch��ÿһ��λ�� Arrays.fill(ch,begin,end,value)  ������end
    }
}
