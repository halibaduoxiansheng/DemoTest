import javax.swing.JOptionPane;//����һ��javax.swing�µ�JOptionPane��
import javax.swing.ImageIcon;
//Ӧ�ñ�̽ӿ� api ����java��javax javax����չ��
import java.util.Random; //�����������
import java.util.Scanner;
public class Test5{
	public static void main(String[] args){
		//
		ImageIcon icon = new ImageIcon("C:\\Users\\86199\\Pictures\\�½��ļ���\\Camera Roll\\happy.jpg");
		String str2 = JOptionPane.showInputDialog(null,"û��Ļ�������Ի���Ӧ�������������","����");
		String str = JOptionPane.showInputDialog(null,"������һ���ַ���,���ǽ���ת��Ϊdouble��:","TMD����־Ϳ�Щ");
		//���������������JOptionPane.showInputDialog��һ�ֱȽϳ��õĶԻ�����ʽ
		if(str != "000"){
			JOptionPane.showConfirmDialog(null,"���ƻظ�","��TM�ľ���Ƿ��",JOptionPane.YES_NO_CANCEL_OPTION
			,JOptionPane.INFORMATION_MESSAGE,icon);	
		}
	//	double r1 = Double.parseDouble(str);//��������ֻ�����ַ���,�����ǿ���̨��������
	//	System.out.println("����double��Ϊ"+r1);
		
		//���������1 
		//�����Ϊ�����ӵ�,���������һֱ�ڱ�,�����Random(4)���۸�����4����,��Ϊ�����ӵ�,�Ǹ�������,��������Ҳ���ű�
		Scanner reader = new Scanner(System.in);
		System.out.println("(���������)������һ������:");
		long bb = reader.nextLong();
		Random random = new Random(bb); //���������double��,�˴��Ͳ���Ҫǿ��ת��
		int r2 = random.nextInt(12); //�����������ֵ  Ĭ�Ϸ�Χ[0,1) ��������д��������(5)----��Χ[0,5)
		//nextDouble�Ͳ����ױ任���ݴ�С
		//int r3 = random.nextInt();  //�ο���һ�д����֪����
		System.out.println("���������Int������r2="+r2);
		
		//���������2
		int a = (int)(Math.random()*7+9); //��Χ,��9��ʼ,��16��9+7��,������16 Ĭ��Ҳ��[0,1)
		System.out.println("�����a="+a);
		
		String a1 = "abcdef";
		String a2 = "bcdefg";
		boolean b = a1.equals(a2);
		System.out.println("�ַ���a1��abcdef�����ַ���a2��bcdefg�������"+b+"\n");//�����һ�� ��ȷ���true,����ȷ���false
		
		int a3[] = new int[]{1,2,3,4};
		int []a4 = new int[3];//δ��ʼ���ľͰ���ԭ���������Զ���ʼ����
		System.out.println("a3[0]="+a3[0]);
		System.out.println("û��ʼ����a4[0]="+a4[0]);
	}
}