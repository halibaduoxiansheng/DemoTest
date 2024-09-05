//子类可以通过super调用父类的构造方法,直接用super()来使用,不需要写父类的类名等操作
//于子类中super.变量 super.方法访问父类的 因为子类于父类的同名变量并不覆盖
public class Test10{
	public static void main(String[] args){
		xiao2 m = new xiao2(99,'m',"王杰",100);
		xiao2 q = new xiao2();
		System.out.println("输出默认值");
		q.show1();//子类产生的对象访问父类的方法
		xiao1 n = new xiao2();//这里的n是父类xiao1的对象
		//n.show2(); 此行代码是非法的,但是并不能否认n不是xiao2的对象,所以可以采用以下的方法
		xiao2 ba = (xiao2)n;
		ba.show2();//如此便是同样的理，只是这样编译器才能通过
		//n.show2(); 所以这行代码不合法,不能通过父类的对象访问子类的方法
		
		//下面三行语句说明以上一行语句可以改写
		//xiao1 w = new xiao1();
		//xiao2 l = (xiao2)w;
		//l.show2();
		
		xiao2 p = (xiao2)n;//强制转化类 xiao1的对象n 为子类 xiao2 的对象（强制将父类对象转化为子类对象）
		//其实除了这个,还有种叫别名,例如 xiao2 q = m;则此时引用这个对象的时候,可以交替的使用q或则m
		//注意此时可以将对象进行对比 q==m是为Boolean的true的
		m.show1();//这一方法就是继承而来
		m.show2();
		m.show3();
		m.show4();
		p.show1(); //可以采用p来访问xiao1中的方法
	}
}
class xiao1{
	//
	int num=0;
	char sex='n'; //用单引号
	void show1(){
		System.out.println("数字:"+num+",性别:"+sex);
	}
	void show3(){ //子类有相同的方法时,子类覆盖父类,这是非静态,静态的无法覆盖
		System.out.println("不出预料,我是无法输出的");
	}
	static void show4(){
		System.out.println("我是静态方法,不出预料我是无法覆盖的");
	}
}
//只允许单继承，不允许多继承，只限于class
//public interface Test1 extends Test2,Test3是允许的，接口可以多继承
class xiao2 extends xiao1{ //继承的关键字extends 左为子类，右为父类
	String name; //用双引号
	int grand;
	
	xiao2(){}		//常识告诉我们,无参构造函数还是需要写的
	xiao2(int num, char sex, String name, int grand){
		this.num=num;//注意,this不能在静态方法中使用 this是调用本类的对象（在这就是说这些变量）
		this.sex=sex;
		this.name=name;
		this.grand=grand;
	}
	void show2(){
		System.out.println("姓名:"+name+",年级:"+grand+"级");
		super.show3();
		System.out.println("haha~不出意外,上面的语句是通过super去调用的");
	}
	void show3(){
		System.out.println("不出预料,子类的show3()方法是可以将父类的同名方法覆盖的，当然，可以采用super.方法名去调用!");
	}
	//void show4(){ //这几行代码根本就不能通过!!!
	//	System.out.println("尝试覆盖父类的静态方法,我要是输出了就说明覆盖了");
	//}
}