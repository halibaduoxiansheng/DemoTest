//同一个变量，由不同的对象指定后，就可以同时代表很多中值了
import java.util.Scanner; //输入所需的Scanner
class people{
	protected int a=1;//默认这些都是在一个文件夹下(即同一个包) 所以protected 下的数据a本类内和子类都可以访问
	//默认的是同一个包中都可以访问，而public更加大胆，任何都可以访问
	private int b = 0;
	void seta(){ //方法一
		Scanner reader = new Scanner(System.in);
		System.out.print("a=");
		a=reader.nextInt();
	}
	void showa(){ //方法二
		System.out.println(a);
	}
}
class student{
	//本类尝试使用class people中的private变量
	void tell(){
			System.out.println("我将尝试输出另外一个类中受保护的a的值");
	}
	//people为默认的class文件，所以在同一个包下也可以使用
	people dd = new people();
	void show(){
		System.out.println("a="+dd.a);//如果为static变量,直接用类名.变量名 否则为本程序方式
	}
//	void tell1(){
	//	System.out.println("无独有偶,那么私密的值我能访问吗？");
//	}
//	void show1(){
	//	System.out.println("a="+dd.b);	
	//} //很明显，这连编译这关都过不了！！！
}
public class Test2{//对象在声明的时候没有空间,只有在创建后才有
	public static void main(String[] args){
		String grade[]={"一年级","二年级","三年级","四年级"};//与c语言不同的就是不需要麻烦的使用二维数组去储存大量的字符串
		//int num=Integer.parseInt(args[0]);//命令行参数转化为整数
		//System.out.print("num="+num);
		System.out.println("观看源代码会发现已经存在一个字符串数组！那么");
		for(int i=0; i<grade.length; i++){
			//grade[i]= new String();  //不需要再创建对象，在开始的时候（于常量池中创建）已经相当于创建了
			System.out.println("第"+(i+1)+"个字符串为:"+grade[i]);
		}
		people p[] = new people[3];//这个数组时类的 __ 对象数组 此时还只是声明对象
		System.out.println("那么现在,我给与您一个新的数组!");
		for(int i=0; i<p.length; i++){ //length属性 length()是对象字符串的长度
			p[i] = new people();//创建对象
			System.out.print("请您输入第"+(i+1)+"个数值");
			p[i].seta();
		}
		System.out.println("----------------------------------(分割线)");
		for(int j=0; j<3; j++){
			//System.out.println("第"+(i+1)+"个a的值为"+p[i].showa());//不能将p[i].showa()放在里面
			System.out.print("第"+(j+1)+"个a的值为");
			p[j].showa();
		}
		student abc = new student();
		abc.tell(); //先行告诉需要干嘛了
		abc.show();
	}
}