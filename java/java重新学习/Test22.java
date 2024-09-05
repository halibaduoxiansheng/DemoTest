//将对象强制转化时，使用他调用的方法还是会记忆性的调用以前的类中的方法，除非没有被覆盖
public class Test22{
	protected String name;
	public Test22(){}
	//尤其需要注意这里本有main函数,不要在函数里面再定义函数
	//然后就是所有的运行都是从main函数开始
	public static void main(String[] args){
		//
		
		Test22 m = new Test22();
		if(m instanceof Test22){
			System.out.println("如果本语句输出，这条语句足够说明对象m是类Test22的~");
		}
		Ant n = new Ant();
		n.hanshu();
		Ant q = new Ant("王杰");
		Ant p = new Ant("王杰");
		Ant pp = (Ant)p;//这时才能是两个相等的对象,我叫其对象复制
		if(p.equals(q)){
			System.out.println("这两个对象是相等的"); // 这两个不是相等的
		}
		if(pp.equals(p)){
			System.out.println("便是相等");
		}
		System.out.println("ok，开始验证第一行话的意思");
		Ant qq = new Ant();
		Test22 qqq = (Test22)qq;
		System.out.println("如果成功的话,就是依旧具有记忆性的输出 “展示1” ");//ok
		qqq.show(); // 也就是说本来父类是无法调用子类的方法的 这里却成功了 说明是具有记忆性的！
	}
	//此toString必须为public，否则无法覆盖本有的toString()
	public String toString(){
		return "仅仅代表一个输出~";
	}
	void show(){
		System.out.println("展示2");
	}
}
class Ant extends Test22{
	//
	public Ant(){}
	public Ant(String name){
		super.name=name;
	}
	void hanshu(){
		System.out.println(toString());
	}
	void show(){
		System.out.println("展示1");
	}
}
abstract class dudu{
	//公用方法可以在不是公用的class里面定义
	public void haha(){//具体方法
	}
	public abstract void happy();//抽象方法(不能加{})
}//抽象类可以什么都不包括