//main���߳�,��Ϊ���߳�,���Կ�������������������߳�
//ʵ�ֶ��̵߳����ַ��� 1.�̳�Thread��   2.ʵ��Runable�ӿ�  ��interface����,implementsʵ��

//����start()��������׼���׶�,���Զ�����run()����������������н׶�
//interrupt() ��ֹͣ�߳�		stop() ������

//����javaֻ�����̳�,����ӿڵ�ԭ�� �������Runable
import java.util.Date;
import java.lang.Runnable;
public class Test18{
	public void startY(){
		ThreadY ty = new ThreadY(); //����ThreadY�߳� Ĭ�ϵĻ�ͬһ�����ڵ�Thread�ǿ����ڱ�����ʹ�õ�
		ty.startThreadY(); 
		try{
			Thread.sleep(1000); //ϵͳ����һ�� ��һ����ϵͳ����һֱ��ִ��
		}catch(InterruptedException e){
			e.printStackTrace();
		}
		ty.stopThreadY(); //ֹͣThreadY�߳�
	}
	public void startX(){
		Runnable runnX = new ThreadX(); //ThreadX��ʵ��Runable�ӿڵ���
		Thread threadX = new Thread(runnX); //��ʵ�������߳���
		threadX.start(); //����
	}
	public static void main(String[] args){
		Test18 test = new Test18();
		test.startY();
		test.startX(); //�Լ�Ĭ��ӵ���߳̽�����������
	}
}
class ThreadY extends Thread{
	private boolean isRunState = false;//��ʼĬ�Ͻ��̹ر�
	public void start(){
		this.isRunState = true; //������start������,��Ϊtrue
		super.start(); //��ʼ��class��run()����
	}
	public void run(){
		int i = 0;
		try{
			while(isRunState){
				this.setName("Thread-"+ i++); //��һ������ֵ,����һ�������һ�����õ�ֵ
				//setName��getName���Ѿ�����
				System.out.println("�߳�Y��"+this.getName()+"��������");
				Thread.sleep(200);
				//һ������1��ʱ�䣬���к�ÿ��ͣ��0.2��
			}
		}catch(Exception e){
			System.out.println(e.getMessage());
		}
		finally{
			System.out.println(this.getName()+"���н���...");
		}
	}
		public void setRunning(boolean isRunState){
			this.isRunState = isRunState; //Ҳ���Ƕ����ʱ���ʼ����ֵ false
		}
		public void startThreadY(){
			System.out.println("�����߳�Y������");
			this.start();
		}
		
		public void stopThreadY(){
			System.out.println("�����߳�Y������");
			this.setRunning(false);//�����Լ������setRunning����,���潫isRunState = false
		}
	}
	class ThreadX implements Runnable{ //���鵽��������
		private Date runDate;
		public void run(){
			System.out.println("�߳�X�Ѿ�����..");
			this.runDate = new Date();
			System.out.println("����ʱ��:"+runDate.toLocaleString());
		}
	}
				