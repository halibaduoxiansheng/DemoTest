//�������ͨ��super���ø���Ĺ��췽��,ֱ����super()��ʹ��,����Ҫд����������Ȳ���
//��������super.���� super.�������ʸ���� ��Ϊ�����ڸ����ͬ��������������
public class Test10{
	public static void main(String[] args){
		xiao2 m = new xiao2(99,'m',"����",100);
		xiao2 q = new xiao2();
		System.out.println("���Ĭ��ֵ");
		q.show1();//��������Ķ�����ʸ���ķ���
		xiao1 n = new xiao2();//�����n�Ǹ���xiao1�Ķ���
		//n.show2(); ���д����ǷǷ���,���ǲ����ܷ���n����xiao2�Ķ���,���Կ��Բ������µķ���
		xiao2 ba = (xiao2)n;
		ba.show2();//��˱���ͬ������ֻ����������������ͨ��
		//n.show2(); �������д��벻�Ϸ�,����ͨ������Ķ����������ķ���
		
		//�����������˵������һ�������Ը�д
		//xiao1 w = new xiao1();
		//xiao2 l = (xiao2)w;
		//l.show2();
		
		xiao2 p = (xiao2)n;//ǿ��ת���� xiao1�Ķ���n Ϊ���� xiao2 �Ķ���ǿ�ƽ��������ת��Ϊ�������
		//��ʵ�������,�����ֽб���,���� xiao2 q = m;���ʱ������������ʱ��,���Խ����ʹ��q����m
		//ע���ʱ���Խ�������жԱ� q==m��ΪBoolean��true��
		m.show1();//��һ�������Ǽ̳ж���
		m.show2();
		m.show3();
		m.show4();
		p.show1(); //���Բ���p������xiao1�еķ���
	}
}
class xiao1{
	//
	int num=0;
	char sex='n'; //�õ�����
	void show1(){
		System.out.println("����:"+num+",�Ա�:"+sex);
	}
	void show3(){ //��������ͬ�ķ���ʱ,���า�Ǹ���,���ǷǾ�̬,��̬���޷�����
		System.out.println("����Ԥ��,�����޷������");
	}
	static void show4(){
		System.out.println("���Ǿ�̬����,����Ԥ�������޷����ǵ�");
	}
}
//ֻ�����̳У��������̳У�ֻ����class
//public interface Test1 extends Test2,Test3������ģ��ӿڿ��Զ�̳�
class xiao2 extends xiao1{ //�̳еĹؼ���extends ��Ϊ���࣬��Ϊ����
	String name; //��˫����
	int grand;
	
	xiao2(){}		//��ʶ��������,�޲ι��캯��������Ҫд��
	xiao2(int num, char sex, String name, int grand){
		this.num=num;//ע��,this�����ھ�̬������ʹ�� this�ǵ��ñ���Ķ����������˵��Щ������
		this.sex=sex;
		this.name=name;
		this.grand=grand;
	}
	void show2(){
		System.out.println("����:"+name+",�꼶:"+grand+"��");
		super.show3();
		System.out.println("haha~��������,����������ͨ��superȥ���õ�");
	}
	void show3(){
		System.out.println("����Ԥ��,�����show3()�����ǿ��Խ������ͬ���������ǵģ���Ȼ�����Բ���super.������ȥ����!");
	}
	//void show4(){ //�⼸�д�������Ͳ���ͨ��!!!
	//	System.out.println("���Ը��Ǹ���ľ�̬����,��Ҫ������˾�˵��������");
	//}
}