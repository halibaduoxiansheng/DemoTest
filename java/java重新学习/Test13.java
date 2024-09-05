import java.util.Scanner;
//过程中发生的任何异常都是对应了相应的类,这些异常类都继承自Throwable 表示他们能够"被捕获"
//Exception类下的所有非RuntimeException子类叫做检查异常,需要处理 常用方法 如下:
//public static toString();  public static getMessage();  try-catch-finally
//         格式如下:
//try{                          
//		//可能产生异常的代码
//}
//catch(someException e){
//		//处理异常的代码
//}
//finally{
//		//必须执行的代码
//}
public class Test13{
	public static void main(String[] args){
		//
		int m=0, n=0;
		Scanner reader = new Scanner(System.in);
		try{
			System.out.println("请输入两个数（用空格隔开）:");
			m=reader.nextInt();
			n=reader.nextInt();
		}
		catch(ArrayIndexOutOfBoundsException e){
			System.out.println(e.toString());
			System.out.println("数组下标越界");
		}
		catch(NumberFormatException e){
			System.out.println(e.toString());
			System.out.println("无法转化为整数");
		}
		catch(ArithmeticException e){
			System.out.println(e.toString());
			System.out.println("除数不能为0");
		}
		catch(Exception e){
			System.out.println(e.toString());//该异常处理必须加,且必须加在最后面
			e.getStackTrace();
		}
		finally{
			int k = m * n;
			System.out.println("数:"+m+"和数:"+n+"的乘积为:"+k);
			System.out.println("程序结束!");
		}
	}
}
//异常处理的好处就是 当出现异常的时候程序不会直接退出