import java.util.Stack;  // ջ��Ҫ��

//ջ�ļ�ʹ��
public class Test27 {
    public static void main(String[] args){
        Stack<Character> stack = new Stack<Character>();  // ��ջ����
        stack.push('a');  // ��ջ
        stack.push('b');
        stack.push('c');
        stack.push('d');
        char ch = stack.pop();  // ��ջ
        System.out.println("����ջ���Ƚ������ԭ��Ӧ�������:"+ch);

        int position = stack.search('a');  // ��0��ʼ  ȥ�ҵ����ַ�
        System.out.println("Ԫ��a��λ��:"+position);

        boolean ok = stack.empty();  // �ж����ջ�Ƿ�Ϊ��
        System.out.println("û��Ļ����ջ���ǿյģ�����false:"+ok);


    }
}
