//java��GUI��֧��ͨ����ḻ���������ʵ��
import java.awt.*;
import javax.swing.*;
import javax.swing.JOptionPane;
import javax.swing.ImageIcon;
public class Test15{
	public static void main(String[] args){
		//
		ImageIcon icon = new ImageIcon("C:\\Users\\86199\\Pictures\\���汳��\\��¡.png");
		Object []selections = {"��һ","�ڶ�","����"};
		/*JOptionPane.showConfirmDialog(null
									,"����һ��ȷ�϶Ի���");*/
		/*JOptionPane.showConfirmDialog(null
									,"����һ��ȷ�϶Ի���"
									,"ȷ�ϱ����"
									,JOptionPane.OK_CANCEL_OPTION);*/
		
		JOptionPane.showConfirmDialog(null
									,"�Ի���"
									,"B����"
									,JOptionPane.YES_NO_CANCEL_OPTION
									,JOptionPane.ERROR_MESSAGE);
		/*JOptionPane.showConfirmDialog(null
									,"�Ի���"
									,"����"
									,JOptionPane.YES_NO_CANCEL_OPTION
									,JOptionPane.INFORMATION_MESSAGE
									,icon);
		JOptionPane.showMessageDialog(null
									,"�Ի���"
									,"����"
									,JOptionPane.INFORMATION_MESSAGE
									,icon);
		JOptionPane.showOptionDialog(null
									,"��ѡ��"
									,"����"
									,JOptionPane.YES_NO_CANCEL_OPTION
									,JOptionPane.INFORMATION_MESSAGE
									,icon
									,selections
									,selections[0]);
		//����Ϊ����
		JOptionPane.showInputDialog(null
									,"��ѡ��"
									,"����"
									,JOptionPane.INFORMATION_MESSAGE
									,icon
									,selections
									,selections[0]);
									*/
	}
}