import java.util.Scanner;
//�����з������κ��쳣���Ƕ�Ӧ����Ӧ����,��Щ�쳣�඼�̳���Throwable ��ʾ�����ܹ�"������"
//Exception���µ����з�RuntimeException�����������쳣,��Ҫ���� ���÷��� ����:
//public static toString();  public static getMessage();  try-catch-finally
//         ��ʽ����:
//try{                          
//		//���ܲ����쳣�Ĵ���
//}
//catch(someException e){
//		//�����쳣�Ĵ���
//}
//finally{
//		//����ִ�еĴ���
//}
public class Test13{
	public static void main(String[] args){
		//
		int m=0, n=0;
		Scanner reader = new Scanner(System.in);
		try{
			System.out.println("���������������ÿո������:");
			m=reader.nextInt();
			n=reader.nextInt();
		}
		catch(ArrayIndexOutOfBoundsException e){
			System.out.println(e.toString());
			System.out.println("�����±�Խ��");
		}
		catch(NumberFormatException e){
			System.out.println(e.toString());
			System.out.println("�޷�ת��Ϊ����");
		}
		catch(ArithmeticException e){
			System.out.println(e.toString());
			System.out.println("��������Ϊ0");
		}
		catch(Exception e){
			System.out.println(e.toString());//���쳣��������,�ұ�����������
			e.getStackTrace();
		}
		finally{
			int k = m * n;
			System.out.println("��:"+m+"����:"+n+"�ĳ˻�Ϊ:"+k);
			System.out.println("�������!");
		}
	}
}
//�쳣����ĺô����� �������쳣��ʱ����򲻻�ֱ���˳�