public class Test11{
	public static void main(String[] args){
		//
		final int a=10;//此时相当于a是个常量
		//final修饰类,就为最终类,即不能再被继承
		//final修饰方法,就为最终方法,即不能被覆盖
		haha1 m = new haha1();//使用的是无参构造函数,本程序中也定义了有参的构造函数
		m.show1();
		System.out.println(m.toString1());
		
		haha1 o = new haha1();
		showya(o);//此处的输出就用到了抽象类的假设性创建对象
	}
	static void showya(haha n){//参数为对象时,就直接使用函数时就直接创建对象了
		n.printinfo();
	}

}
abstract class haha{
	//抽象类,是不能创建对象的一种类,是用来--专门继承的 
	//其外抽象方法是没有实体的,只有函数头部分,{}都没有 例:abstract void show(); 且该方法必须在抽象类中
	String name;
	char sex;
	public haha(){
		
	}
	public haha(String name,char sex){
		this.name=name;
		this.sex=sex;
	}
	abstract public void show1();
	abstract String toString1();
	//abstract public void show2();//尝试多写一个抽象类 很明显是无法通过编译的,如果没有在子类中完成函数的编写
	//但是记住,如果是一个抽象类去继承另外一个抽象类,那么留意不要将抽象化的类生成对象了,是不行的
	void printinfo(){
		System.out.println("仔细看我是如何输出的"); // 没错，是调用的对象形参
	}
}
class haha1 extends haha{ //如果子类没有完成父类的所有抽象方法，那么子类也为抽象类才行
	public haha1(){
	}
	public haha1(String name,char sex){
		super(name,sex);
	}
	public void show1(){
		System.out.println("我来完成没完成的抽象函数的输出函数了");
	}
	public String toString1(){
		return "我是子类的super.toString()"+"但是我此刻正在调用父类的toString方法";
	}
}