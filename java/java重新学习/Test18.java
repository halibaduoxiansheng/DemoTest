//main是线程,且为主线程,所以可以在其中启动多个子线程
//实现多线程的两种方法 1.继承Thread类   2.实现Runable接口  用interface定义,implements实现

//其中start()方法进入准备阶段,后将自动调用run()方法真正进入可运行阶段
//interrupt() ：停止线程		stop() ：死锁

//由于java只允许单继承,但多接口的原理 建议采用Runable
import java.util.Date;
import java.lang.Runnable;
public class Test18{
	public void startY(){
		ThreadY ty = new ThreadY(); //启动ThreadY线程 默认的话同一个包内的Thread是可以在本类中使用的
		ty.startThreadY(); 
		try{
			Thread.sleep(1000); //系统休眠一秒 这一秒内系统进程一直在执行
		}catch(InterruptedException e){
			e.printStackTrace();
		}
		ty.stopThreadY(); //停止ThreadY线程
	}
	public void startX(){
		Runnable runnX = new ThreadX(); //ThreadX是实现Runable接口的类
		Thread threadX = new Thread(runnX); //将实例放入线程中
		threadX.start(); //启动
	}
	public static void main(String[] args){
		Test18 test = new Test18();
		test.startY();
		test.startX(); //自己默认拥有线程结束的输出语句
	}
}
class ThreadY extends Thread{
	private boolean isRunState = false;//开始默认进程关闭
	public void start(){
		this.isRunState = true; //当调用start函数后,才为true
		super.start(); //开始本class的run()函数
	}
	public void run(){
		int i = 0;
		try{
			while(isRunState){
				this.setName("Thread-"+ i++); //这一行设置值,下面一行输出这一行设置的值
				//setName、getName等已经存在
				System.out.println("线程Y："+this.getName()+"正在运行");
				Thread.sleep(200);
				//一共给了1秒时间，运行后每次停顿0.2秒
			}
		}catch(Exception e){
			System.out.println(e.getMessage());
		}
		finally{
			System.out.println(this.getName()+"运行结束...");
		}
	}
		public void setRunning(boolean isRunState){
			this.isRunState = isRunState; //也即是定义的时候初始化的值 false
		}
		public void startThreadY(){
			System.out.println("启动线程Y。。。");
			this.start();
		}
		
		public void stopThreadY(){
			System.out.println("结束线程Y。。。");
			this.setRunning(false);//调用自己定义的setRunning函数,里面将isRunState = false
		}
	}
	class ThreadX implements Runnable{ //体验到并发进行
		private Date runDate;
		public void run(){
			System.out.println("线程X已经启动..");
			this.runDate = new Date();
			System.out.println("启动时间:"+runDate.toLocaleString());
		}
	}
				