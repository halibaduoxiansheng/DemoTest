//基本上都是要求数据为double型数据的
public class Test6{
	public static void main(String[] args){
		//
		double a1 = Math.PI; //π
		double a9 = Math.E;
		System.out.println("e="+a9);
		System.out.println("（无理数π）a1="+a1);
		
		int a2 = -1; double a3 = -1.3;
		a2 = Math.abs(a2); a3 = Math.abs(a3); //括弧里面可以是int、long、float、double
		System.out.println("绝对值a2="+a2+"，绝对值a3="+a3);
		
		double a4=1.3, a5=1.4, a6=0.0;
		a6=Math.sin(a4/a5);//括弧里面是double型 sin、cos、tan
		System.out.println("sin--a6="+a6);
		a6=Math.cos(a4/a5);
		System.out.println("cos--a6="+a6);
		a6=Math.tan(a4/a5);
		System.out.println("tan--a6="+a6);
		a6=Math.pow(a4,a5);//括弧里面也是double型
		System.out.println("a4的a5次方="+a6);
		a6=Math.sqrt(a4);//括弧里面也是double型 只是平方，不是算数平发根
		System.out.println("a4的开方="+a6);
		a6=Math.log(a4);//括弧里面也是double型
		System.out.println("以e为底的a4对数="+a6);
	}
}