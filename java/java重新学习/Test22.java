//������ǿ��ת��ʱ��ʹ�������õķ������ǻ�����Եĵ�����ǰ�����еķ���������û�б�����
public class Test22{
	protected String name;
	public Test22(){}
	//������Ҫע�����ﱾ��main����,��Ҫ�ں��������ٶ��庯��
	//Ȼ��������е����ж��Ǵ�main������ʼ
	public static void main(String[] args){
		//
		
		Test22 m = new Test22();
		if(m instanceof Test22){
			System.out.println("���������������������㹻˵������m����Test22��~");
		}
		Ant n = new Ant();
		n.hanshu();
		Ant q = new Ant("����");
		Ant p = new Ant("����");
		Ant pp = (Ant)p;//��ʱ������������ȵĶ���,�ҽ��������
		if(p.equals(q)){
			System.out.println("��������������ȵ�"); // ������������ȵ�
		}
		if(pp.equals(p)){
			System.out.println("�������");
		}
		System.out.println("ok����ʼ��֤��һ�л�����˼");
		Ant qq = new Ant();
		Test22 qqq = (Test22)qq;
		System.out.println("����ɹ��Ļ�,�������ɾ��м����Ե���� ��չʾ1�� ");//ok
		qqq.show(); // Ҳ����˵�����������޷���������ķ����� ����ȴ�ɹ��� ˵���Ǿ��м����Եģ�
	}
	//��toString����Ϊpublic�������޷����Ǳ��е�toString()
	public String toString(){
		return "��������һ�����~";
	}
	void show(){
		System.out.println("չʾ2");
	}
}
class Ant extends Test22{
	//
	public Ant(){}
	public Ant(String name){
		super.name=name;
	}
	void hanshu(){
		System.out.println(toString());
	}
	void show(){
		System.out.println("չʾ1");
	}
}
abstract class dudu{
	//���÷��������ڲ��ǹ��õ�class���涨��
	public void haha(){//���巽��
	}
	public abstract void happy();//���󷽷�(���ܼ�{})
}//���������ʲô��������