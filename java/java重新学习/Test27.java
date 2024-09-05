import java.util.Stack;  // 栈需要的

//栈的简单使用
public class Test27 {
    public static void main(String[] args){
        Stack<Character> stack = new Stack<Character>();  // 建栈函数
        stack.push('a');  // 入栈
        stack.push('b');
        stack.push('c');
        stack.push('d');
        char ch = stack.pop();  // 出栈
        System.out.println("按照栈的先进后出的原则应该是输出:"+ch);

        int position = stack.search('a');  // 从0开始  去找到该字符
        System.out.println("元素a的位置:"+position);

        boolean ok = stack.empty();  // 判断这个栈是否为空
        System.out.println("没错的话这个栈不是空的，返回false:"+ok);


    }
}
