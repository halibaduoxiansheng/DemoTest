// package �Ϳ��Կ���class�ļ�������λ��
package balabala.gulugulu; // ����balabala����,�������ļ���Ҫ�������е���,����  import balabala.���� ����
import java.text.DecimalFormat; //�������С�������
public class Test4{
	//�������η���������:
	public int a1=0;//�����඼���Է���
	protected int a2=0;//�����ͬһ�����ڵ���������Է��� �����������ڽ����ϵ������඼���Է���
	int a3=0;//Ĭ�ϣ�ͬһ�����е�����Է���
	private int a4=0;//ֻ�ж����ڸñ�����÷��������п��Է���,�����඼�޷�����
	
	public static void main(String[] args){
		//
		double a5=12.3456789;
		int a=0;
		DecimalFormat df = new DecimalFormat("0.00");//��Ϊ������λС�� 0.0����һλ������
		String s=df.format(a5); //format����ֵ��һ�ָ�ʽ������ַ���
//		double num10 = Integer.parseInt(s); // ���������׵�ת��Ϊ��
//		System.out.println("num10="+num10);
		//double s1=df.format(a5);
		System.out.println("12.3456789������λС����Ϊ"+s);
		//System.out.println("12.3456789������λС����Ϊ"+s1);
		lei1 m1 = new lei1();
		m1.shuchu();
		m1.shuchu1();
	}
}
class lei1{
	int a=0;
	static String str="\\n"; //��дһ��\���ɽ���Щת���ַ����
	void shuchu(){
		//
		int a=1;//�������������´�ʱ��a=1�ؽ�����ǰ���a=0������������Ҳ������ú�����,�����⻹��a=0
		System.out.println("�������������֪����ʱ�����aΪ���������,Ϊ:"+a);//����1
	}
	static void shuchu1(){
		System.out.println("��ʱ��a���ٱ�����,��Ϊa=0,ֻ�����޷�ֱ�ӵ��÷Ǿ�̬�ı���a\n");
		System.out.println("�ɼ�����"+str+"��java�����ɿ���");
		System.out.println("��̬�����в���������зǾ�̬�ķ������������");
	}
}