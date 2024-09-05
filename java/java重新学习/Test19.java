import java.lang.Runnable;
import java.util.Random;

public class Test19{
	public static void main(String[] args){
		
		Alipay alipay = new Alipay(2); //��������֧������

		new Seller("����-����13",alipay,5).start();// ���ƣ���������
		new Seller("����-С����",alipay,7).start();
		new Buyer("���-��֮زز",alipay,101).start(); 
		new Buyer("���-�����漣",alipay,103).start();
		
	}
}

class Alipay{
	private final String[] deal;
	private int n; //����Ľ�������
	private int m; //֧���Ľ�������
	private int count; //�����ڵĽ�������
	
	public Alipay(int count){ //���캯��
		this.deal = new String[count];
		this.m=0;
		this.n=0;
		this.count=0;
	}
	
	//����Ϊ��֧����������
	public synchronized void storage(String alipay){
		System.out.println("�Ա��û� ID:"+Thread.currentThread().getName()+" \t֧�������룺"+alipay);
		try{
			while(count >= deal.length){
				//System.out.println("��˿��Ե�,�˿̻��пͻ�������~");
				wait(); //�̵߳ȴ�����
			}
			deal[n] = alipay;
			n = (n+1) % deal.length;
			count++;
			notifyAll(); //
		}catch(Exception e){
			System.out.println("֧�������빦���쳣"+e.getMessage());
		}
	}
	//����Ϊ��֧��������֧��
	public synchronized String outlay(){ //synchronized �Ƿ�ֹһ��һ�����̱�����һ�����̴��
		String alipay = null;
		try{
			while(count <= 0){
				wait(); //����ȴ�
			}
			alipay = deal[m];
			m = (m+1) % deal.length;
			count--;
			notifyAll(); //���ѵȴ����߳�
		}catch(Exception e){
			System.out.println("֧����֧�������쳣"+e.getMessage());
		}
		System.out.println("�Ա��û� ID:"+Thread.currentThread().getName()+" \t֧����֧��"+alipay);
		//������Ϊʵ�ʿɼ��Ͻ�Ǯ��Ϣ
		return alipay;
	}
}

class Buyer extends Thread{ //����߳���
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
				Thread.sleep(random.nextInt(1000)); //�������
				String flowingID = "������ˮ�˺�"+nextId();
				alipay.storage(flowingID); //������id�˺�
			}
		}catch(Exception e){
	}
	}
		
	private static synchronized int nextId(){
		return id++; //һ��һ��������ͻ���Ӧ����1
	}
}

class Seller extends Thread{ //�����߳���
	private final Random random;
	private final Alipay alipay;
	//public static int num=0;
	
	public Seller(String name,Alipay alipay,long seed){ //��������Ϊlong��
		super(name); //�ڱ�������ʹ��ԭ�������ڸ����Thread�е�super�Ĺ��캯��
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
			System.out.println("���֧��Ԥ�������:"+e.getMessage());
		}
	}
}
/*join ���磺
 *group1��һ������,��
 *group1.start();
 *try{
 	group1.join();//��ʱ�����ڵȴ�ʱ��
 	}catch(Ecception e){
 		}*/
/*�ػ��߳� ��
 *Yield ����д���������
 *public Yield(){
 	this.setDaemon(true);
 	}
 	ʹ��:����ʹ�ý���֮ǰ���ã�textΪ����
 	text.Yield().start();
 	����ֿ�д text.serDaemon(true); text.start();*/