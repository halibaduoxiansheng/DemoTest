//ͬһ���������ɲ�ͬ�Ķ���ָ���󣬾Ϳ���ͬʱ����ܶ���ֵ��
import java.util.Scanner; //���������Scanner
class people{
	protected int a=1;//Ĭ����Щ������һ���ļ�����(��ͬһ����) ����protected �µ�����a�����ں����඼���Է���
	//Ĭ�ϵ���ͬһ�����ж����Է��ʣ���public���Ӵ󵨣��κζ����Է���
	private int b = 0;
	void seta(){ //����һ
		Scanner reader = new Scanner(System.in);
		System.out.print("a=");
		a=reader.nextInt();
	}
	void showa(){ //������
		System.out.println(a);
	}
}
class student{
	//���ೢ��ʹ��class people�е�private����
	void tell(){
			System.out.println("�ҽ������������һ�������ܱ�����a��ֵ");
	}
	//peopleΪĬ�ϵ�class�ļ���������ͬһ������Ҳ����ʹ��
	people dd = new people();
	void show(){
		System.out.println("a="+dd.a);//���Ϊstatic����,ֱ��������.������ ����Ϊ������ʽ
	}
//	void tell1(){
	//	System.out.println("�޶���ż,��ô˽�ܵ�ֵ���ܷ�����");
//	}
//	void show1(){
	//	System.out.println("a="+dd.b);	
	//} //�����ԣ�����������ض������ˣ�����
}
public class Test2{//������������ʱ��û�пռ�,ֻ���ڴ��������
	public static void main(String[] args){
		String grade[]={"һ�꼶","���꼶","���꼶","���꼶"};//��c���Բ�ͬ�ľ��ǲ���Ҫ�鷳��ʹ�ö�ά����ȥ����������ַ���
		//int num=Integer.parseInt(args[0]);//�����в���ת��Ϊ����
		//System.out.print("num="+num);
		System.out.println("�ۿ�Դ����ᷢ���Ѿ�����һ���ַ������飡��ô");
		for(int i=0; i<grade.length; i++){
			//grade[i]= new String();  //����Ҫ�ٴ��������ڿ�ʼ��ʱ���ڳ������д������Ѿ��൱�ڴ�����
			System.out.println("��"+(i+1)+"���ַ���Ϊ:"+grade[i]);
		}
		people p[] = new people[3];//�������ʱ��� __ �������� ��ʱ��ֻ����������
		System.out.println("��ô����,�Ҹ�����һ���µ�����!");
		for(int i=0; i<p.length; i++){ //length���� length()�Ƕ����ַ����ĳ���
			p[i] = new people();//��������
			System.out.print("���������"+(i+1)+"����ֵ");
			p[i].seta();
		}
		System.out.println("----------------------------------(�ָ���)");
		for(int j=0; j<3; j++){
			//System.out.println("��"+(i+1)+"��a��ֵΪ"+p[i].showa());//���ܽ�p[i].showa()��������
			System.out.print("��"+(j+1)+"��a��ֵΪ");
			p[j].showa();
		}
		student abc = new student();
		abc.tell(); //���и�����Ҫ������
		abc.show();
	}
}