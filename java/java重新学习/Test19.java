import java.lang.Runnable;
import java.util.Random;

public class Test19{
	public static void main(String[] args){
		
		Alipay alipay = new Alipay(2); //创建两个支付宝类

		new Seller("卖家-聂琴13",alipay,5).start();// 名称，对象，种子
		new Seller("卖家-小不点",alipay,7).start();
		new Buyer("买家-逃之夭夭",alipay,101).start(); 
		new Buyer("买家-相信奇迹",alipay,103).start();
		
	}
}

class Alipay{
	private final String[] deal;
	private int n; //存入的交易数量
	private int m; //支出的交易数量
	private int count; //缓存内的交易数量
	
	public Alipay(int count){ //构造函数
		this.deal = new String[count];
		this.m=0;
		this.n=0;
		this.count=0;
	}
	
	//以下为往支付宝里面存款
	public synchronized void storage(String alipay){
		System.out.println("淘宝用户 ID:"+Thread.currentThread().getName()+" \t支付宝存入："+alipay);
		try{
			while(count >= deal.length){
				//System.out.println("请顾客稍等,此刻还有客户在买东西~");
				wait(); //线程等待函数
			}
			deal[n] = alipay;
			n = (n+1) % deal.length;
			count++;
			notifyAll(); //
		}catch(Exception e){
			System.out.println("支付宝存入功能异常"+e.getMessage());
		}
	}
	//以下为往支付宝里面支出
	public synchronized String outlay(){ //synchronized 是防止一个一个进程被另外一个进程打断
		String alipay = null;
		try{
			while(count <= 0){
				wait(); //进入等待
			}
			alipay = deal[m];
			m = (m+1) % deal.length;
			count--;
			notifyAll(); //唤醒等待的线程
		}catch(Exception e){
			System.out.println("支付宝支付功能异常"+e.getMessage());
		}
		System.out.println("淘宝用户 ID:"+Thread.currentThread().getName()+" \t支付宝支出"+alipay);
		//以上如为实际可加上金钱信息
		return alipay;
	}
}

class Buyer extends Thread{ //买家线程类
	private final Random random;
	private final Alipay alipay;
	private static int id = 0;
	public Buyer(String name,Alipay alipay,long seed){
		super(name);
		this.alipay=alipay;
		this.random=new Random(seed);
	}
	
	public void run(){
		try{
			while(true){
				Thread.sleep(random.nextInt(1000)); //随机休眠
				String flowingID = "交易流水账号"+nextId();
				alipay.storage(flowingID); //流动的id账号
			}
		}catch(Exception e){
	}
	}
		
	private static synchronized int nextId(){
		return id++; //一买一卖结束后就会相应加上1
	}
}

class Seller extends Thread{ //卖家线程类
	private final Random random;
	private final Alipay alipay;
	//public static int num=0;
	
	public Seller(String name,Alipay alipay,long seed){ //种子类型为long型
		super(name); //于本子类中使用原本存在于父类的Thread中的super的构造函数
		this.alipay=alipay;
		this.random = new Random(seed);
	}
	public void run(){
		try{
			while(true){
				//num++;
				String alipay = this.alipay.outlay();
				Thread.sleep(random.nextInt(1000));
			}
		}catch(Exception e){
			System.out.println("买家支付预付款出错:"+e.getMessage());
		}
	}
}
/*join 例如：
 *group1是一个对象,则
 *group1.start();
 *try{
 	group1.join();//此时边属于等待时间
 	}catch(Ecception e){
 		}*/
/*守护线程 ：
 *Yield 另外写出这个函数
 *public Yield(){
 	this.setDaemon(true);
 	}
 	使用:需在使用进程之前调用（text为对象）
 	text.Yield().start();
 	或则分开写 text.serDaemon(true); text.start();*/