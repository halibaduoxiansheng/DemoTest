import java.util.Scanner;//导入java.util下的Scanner类,才能使用它
public class Test3{
	static int a3=10; //设置静态变量 需要再类内,函数外,且并没有要求拥有初始化值
	public static void main(String[] args){
		//
		int a1=0, a2=0;
		Scanner reader = new Scanner(System.in);
		lei1 m = new lei1();//lei1的对象创建
		do{
			System.out.println("请依次输入两个数，用空格隔开(请不要输入0):");
			a1=reader.nextInt();
			a2=reader.nextInt();
		}while(a1 == 0 || a2 == 0);
		m.setshu(a1,a2);
		m.getshu();
		lei1 m1 = new lei1(3);
		m1.show();
		lei1 m2 = new lei1(2,3);
		m2.show();
		lei2 m3 = new lei2();
		m3.haha();
	}
}
class lei1{
	//
	int m1=0, m2=0, de=0, de1=0; // 将所有默认值权全部初始化为0
	void setshu(int a,int b) {//并不会改变实参a、b的值
		m1=a;
		m2=b;
	}
	void getshu() {
		de=m1*m2;
		de1=m1+m2;
		System.out.println("它的两个数的乘积为"+de);
		System.out.println("它的两个数的相加为"+de1);
		System.out.println();
	}
	//构造函数没有返回值类型，甚至就是连void也没有，形参数量不定
	lei1(){
		//无参构造器也需要写，如果有参构造器写了的话(前提)
	}
	lei1(int m1){//一个参数的构造器 this只能在构造方法中使用,且必须是第一条语句 this只能调用当前所处类的对象
	//有时候就是在该对象的类中,想调用其中的一种方法,大可不必生成对象,直接this.方法名即可,不用生成一个对象去调用另一个对象
		this.m1=m1;
	}
	lei1(int a,int b){//两个参数的构造器
		m1=a;
		m2=b;
	}
	void show(){
		System.out.println("第一个数为:"+m1+"第二个数为:"+m2);
		if(m1 == 0)
			System.out.println("第一个数并没有成功初始化!");
		if(m2 == 0)
			System.out.println("第二个数并没有成功初始化!");
	}
}
class lei2{
	////通过类名或则对象访问全局变量(静态变量)
	lei2(){
			//
	}
	void haha(){
		System.out.println("通过类名访问,全局变量为a3="+Test3.a3);
		Test3 m4 = new Test3();
		System.out.println("通过对象调用访问,静态变量a3="+m4.a3);
		//可以通过对象的方式改变全局变量的值
		Test3.a3=99;  //m4.a3=99
		System.out.println();
		System.out.println("通过 m4.a3=99 对象赋值法 或则 Test3.a3=99 类名赋值法 改变a3的值后");
		System.out.println("静态变量a3的值已经被改变为:"+Test3.a3);
	}
}
//super()为调用父类的构造函数,当然，如果里面不放参数就是调用无参构造函数
//super.父类方法 就可以调用父类的方法了