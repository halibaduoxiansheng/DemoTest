//�����϶���Ҫ������Ϊdouble�����ݵ�
public class Test6{
	public static void main(String[] args){
		//
		double a1 = Math.PI; //��
		double a9 = Math.E;
		System.out.println("e="+a9);
		System.out.println("���������У�a1="+a1);
		
		int a2 = -1; double a3 = -1.3;
		a2 = Math.abs(a2); a3 = Math.abs(a3); //�������������int��long��float��double
		System.out.println("����ֵa2="+a2+"������ֵa3="+a3);
		
		double a4=1.3, a5=1.4, a6=0.0;
		a6=Math.sin(a4/a5);//����������double�� sin��cos��tan
		System.out.println("sin--a6="+a6);
		a6=Math.cos(a4/a5);
		System.out.println("cos--a6="+a6);
		a6=Math.tan(a4/a5);
		System.out.println("tan--a6="+a6);
		a6=Math.pow(a4,a5);//��������Ҳ��double��
		System.out.println("a4��a5�η�="+a6);
		a6=Math.sqrt(a4);//��������Ҳ��double�� ֻ��ƽ������������ƽ����
		System.out.println("a4�Ŀ���="+a6);
		a6=Math.log(a4);//��������Ҳ��double��
		System.out.println("��eΪ�׵�a4����="+a6);
	}
}