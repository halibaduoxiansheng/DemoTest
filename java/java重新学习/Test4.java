// package 就可以控制class文件的生成位置
package balabala.gulugulu; // 存入balabala包中,若其他文件需要访问其中的类,可以  import balabala.类名 访问
import java.text.DecimalFormat; //导入控制小数点的类
public class Test4{
	//四种修饰符作用如下:
	public int a1=0;//所有类都可以访问
	protected int a2=0;//子类和同一个包内的其他类可以访问 比如现在所在界面上的所有类都可以访问
	int a3=0;//默认，同一个包中的类可以访问
	private int a4=0;//只有定义在该变量或该方法的类中可以访问,其他类都无法访问
	
	public static void main(String[] args){
		//
		double a5=12.3456789;
		int a=0;
		DecimalFormat df = new DecimalFormat("0.00");//此为保留两位小数 0.0就是一位，类推
		String s=df.format(a5); //format返回值是一种格式化后的字符串
//		double num10 = Integer.parseInt(s); // 并不能轻易的转化为数
//		System.out.println("num10="+num10);
		//double s1=df.format(a5);
		System.out.println("12.3456789保留两位小数后为"+s);
		//System.out.println("12.3456789保留两位小数后为"+s1);
		lei1 m1 = new lei1();
		m1.shuchu();
		m1.shuchu1();
	}
}
class lei1{
	int a=0;
	static String str="\\n"; //多写一个\即可将那些转义字符输出
	void shuchu(){
		//
		int a=1;//很明显作用域下此时的a=1必将屏蔽前面的a=0，不过作用域也就是与该函数中,函数外还是a=0
		System.out.println("由屏蔽现象可以知道此时输出的a为函数里面的,为:"+a);//该是1
	}
	static void shuchu1(){
		System.out.println("此时的a不再被屏蔽,将为a=0,只不过无法直接调用非静态的变量a\n");
		System.out.println("可见换行"+str+"与java中依旧可用");
		System.out.println("静态方法中不允许调用有非静态的方法或变量出现");
	}
}