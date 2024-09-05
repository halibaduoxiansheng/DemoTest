//接口里面的成员变量一律是公开的、静态的、最终的 public static final,这些关键字可省略不写
//三个修饰可以挑着写，反正无论如何都是都存在的
//里面的成员方法一律是公开的，抽象的 public abstract ,这些关键字可省略不写
//如果接口被继承，那么这个儿辈接口将具有父辈接口的所有方法
public class Test12{
	public static void main(String[] args){
		lizi m = new lizi();
		m.getSalary();
		m.show1();
	}
}
interface ISalary{
	double rate = 0.15;
	int num = 19;
	double getSalary();
	void show1();
}
//类必须为接口中声明的每一个方法实现定义
//一个类可以实现不止一个接口 如下：
// class lei implements ISalary1,ISalary2{。。。}
class lizi implements ISalary{ //这里采用的是implements
	double money=0.0;
	public double getSalary(){  //  public必须不变的抄写过来
		System.out.println("相当于继承而来rate="+rate+",num="+num);
		money=rate*num;
		return money;
	}
	public void show1(){//如果为接口来的,那么不能少加了public
		System.out.println("钱money="+money);
	}
	void show2(){//所以不用硬加上public
		System.out.println("我为自行定义的函数");
	}	
}