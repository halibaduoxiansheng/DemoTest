public class Test11{
	public static void main(String[] args){
		//
		final int a=10;//��ʱ�൱��a�Ǹ�����
		//final������,��Ϊ������,�������ٱ��̳�
		//final���η���,��Ϊ���շ���,�����ܱ�����
		haha1 m = new haha1();//ʹ�õ����޲ι��캯��,��������Ҳ�������вεĹ��캯��
		m.show1();
		System.out.println(m.toString1());
		
		haha1 o = new haha1();
		showya(o);//�˴���������õ��˳�����ļ����Դ�������
	}
	static void showya(haha n){//����Ϊ����ʱ,��ֱ��ʹ�ú���ʱ��ֱ�Ӵ���������
		n.printinfo();
	}

}
abstract class haha{
	//������,�ǲ��ܴ��������һ����,������--ר�ż̳е� 
	//������󷽷���û��ʵ���,ֻ�к���ͷ����,{}��û�� ��:abstract void show(); �Ҹ÷��������ڳ�������
	String name;
	char sex;
	public haha(){
		
	}
	public haha(String name,char sex){
		this.name=name;
		this.sex=sex;
	}
	abstract public void show1();
	abstract String toString1();
	//abstract public void show2();//���Զ�дһ�������� ���������޷�ͨ�������,���û������������ɺ����ı�д
	//���Ǽ�ס,�����һ��������ȥ�̳�����һ��������,��ô���ⲻҪ�����󻯵������ɶ�����,�ǲ��е�
	void printinfo(){
		System.out.println("��ϸ��������������"); // û���ǵ��õĶ����β�
	}
}
class haha1 extends haha{ //�������û����ɸ�������г��󷽷�����ô����ҲΪ���������
	public haha1(){
	}
	public haha1(String name,char sex){
		super(name,sex);
	}
	public void show1(){
		System.out.println("�������û��ɵĳ����������������");
	}
	public String toString1(){
		return "���������super.toString()"+"�����Ҵ˿����ڵ��ø����toString����";
	}
}