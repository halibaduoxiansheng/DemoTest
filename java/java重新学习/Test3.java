import java.util.Scanner;//����java.util�µ�Scanner��,����ʹ����
public class Test3{
	static int a3=10; //���þ�̬���� ��Ҫ������,������,�Ҳ�û��Ҫ��ӵ�г�ʼ��ֵ
	public static void main(String[] args){
		//
		int a1=0, a2=0;
		Scanner reader = new Scanner(System.in);
		lei1 m = new lei1();//lei1�Ķ��󴴽�
		do{
			System.out.println("�������������������ÿո����(�벻Ҫ����0):");
			a1=reader.nextInt();
			a2=reader.nextInt();
		}while(a1 == 0 || a2 == 0);
		m.setshu(a1,a2);
		m.getshu();
		lei1 m1 = new lei1(3);
		m1.show();
		lei1 m2 = new lei1(2,3);
		m2.show();
		lei2 m3 = new lei2();
		m3.haha();
	}
}
class lei1{
	//
	int m1=0, m2=0, de=0, de1=0; // ������Ĭ��ֵȨȫ����ʼ��Ϊ0
	void setshu(int a,int b) {//������ı�ʵ��a��b��ֵ
		m1=a;
		m2=b;
	}
	void getshu() {
		de=m1*m2;
		de1=m1+m2;
		System.out.println("�����������ĳ˻�Ϊ"+de);
		System.out.println("���������������Ϊ"+de1);
		System.out.println();
	}
	//���캯��û�з���ֵ���ͣ�����������voidҲû�У��β���������
	lei1(){
		//�޲ι�����Ҳ��Ҫд������вι�����д�˵Ļ�(ǰ��)
	}
	lei1(int m1){//һ�������Ĺ����� thisֻ���ڹ��췽����ʹ��,�ұ����ǵ�һ����� thisֻ�ܵ��õ�ǰ������Ķ���
	//��ʱ������ڸö��������,��������е�һ�ַ���,��ɲ������ɶ���,ֱ��this.����������,��������һ������ȥ������һ������
		this.m1=m1;
	}
	lei1(int a,int b){//���������Ĺ�����
		m1=a;
		m2=b;
	}
	void show(){
		System.out.println("��һ����Ϊ:"+m1+"�ڶ�����Ϊ:"+m2);
		if(m1 == 0)
			System.out.println("��һ������û�гɹ���ʼ��!");
		if(m2 == 0)
			System.out.println("�ڶ�������û�гɹ���ʼ��!");
	}
}
class lei2{
	////ͨ����������������ȫ�ֱ���(��̬����)
	lei2(){
			//
	}
	void haha(){
		System.out.println("ͨ����������,ȫ�ֱ���Ϊa3="+Test3.a3);
		Test3 m4 = new Test3();
		System.out.println("ͨ��������÷���,��̬����a3="+m4.a3);
		//����ͨ������ķ�ʽ�ı�ȫ�ֱ�����ֵ
		Test3.a3=99;  //m4.a3=99
		System.out.println();
		System.out.println("ͨ�� m4.a3=99 ����ֵ�� ���� Test3.a3=99 ������ֵ�� �ı�a3��ֵ��");
		System.out.println("��̬����a3��ֵ�Ѿ����ı�Ϊ:"+Test3.a3);
	}
}
//super()Ϊ���ø���Ĺ��캯��,��Ȼ��������治�Ų������ǵ����޲ι��캯��
//super.���෽�� �Ϳ��Ե��ø���ķ�����