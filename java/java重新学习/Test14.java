//�Զ����쳣����
//throws �����쳣�� throw �׳��쳣
import java.util.Scanner;
import javax.swing.JOptionPane;
import javax.swing.ImageIcon;

class ScoreRangeException extends Exception{//�Զ����쳣������:ScoreRangeException �̳���Exception
	ScoreRangeException(String sre){ //д���Լ��Ĺ��췽��
		super(sre);//����Exception���������
	}
}
public class Test14{
	static void convert(int score)throws ScoreRangeException{  //throws�������쳣
	//������:convert(int score);
		if(score<0 || score>100){
			ScoreRangeException e = new ScoreRangeException("����һ�������ķ���,ҪôС��0,Ҫô����100");//��������
			throw e;//��throw�׳����쳣
		}
		else{
			//
			System.out.println("ת��Ϊ�ȼ��ƿ��Գɼ�Ϊ:");
			int s=score/10;
			switch(s){
				case 9: System.out.println("�ɼ�ΪA"); break;
				case 8: System.out.println("�ɼ�ΪB"); break;
				case 7: System.out.println("�ɹ�ΪC"); break;
				case 6: System.out.println("�ɼ�ΪD"); break;
				default : System.out.println("û����,׼����ĸ��һ�ٶ���Ϊ�°벹������׼��");
			}
		}
	}
	public static void main(String[] args){//ͬ�ʾ�̬������main���Ե���convert(int score)����
		Scanner reader = new Scanner(System.in);
		System.out.println("�����������ĩ���Գɼ����ٷ��ƣ�:");
		int score = reader.nextInt();
		try{
			convert(score);
		}
		catch(ScoreRangeException e){
			System.out.println(e.toString());//Ҳ����дe.getMessage()
		}
		finally{//һ����д�ɲ�д�Ĳ��� ����д�˾�һ�����
			ImageIcon icon = new ImageIcon("C:/Users/86199/Pictures/���汳��/��.jpg");
			JOptionPane.showMessageDialog(null,"��ȷ������ѧ���ܿ�����?"
											,"����"
											,JOptionPane.INFORMATION_MESSAGE
											,icon);
			String[] choose = {"��һ","�ڶ�","����"};
			JOptionPane.showMessageDialog(null,"��ϲ���Ѿ���ʹ�ñ�������!","��ʾ",JOptionPane.INFORMATION_MESSAGE);
			int response = JOptionPane.showOptionDialog(null,"����Ϊ����ѧ��Ŭ���Ļ��ܿ��ڼ���,��������ѡ����ѡ��"
										,"ѡ���"
										,JOptionPane.YES_NO_CANCEL_OPTION
										,JOptionPane.INFORMATION_MESSAGE
										,icon
										,choose
										,choose[2] //����Ĭ��ѡ��
										);
			if(response == 0)
				JOptionPane.showMessageDialog(null,"������ǻᴵţ","��ʾ��",JOptionPane.INFORMATION_MESSAGE,icon);
			else if(response == 1)
				JOptionPane.showMessageDialog(null,"û�뵽�㻹����ǫ�����!","��ʾ��",JOptionPane.INFORMATION_MESSAGE,icon);
			else if(response == 2)
				JOptionPane.showMessageDialog(null,"û��־���������","��ʾ��",JOptionPane.INFORMATION_MESSAGE,icon);
			System.out.println("������������!");
		}
	}
}