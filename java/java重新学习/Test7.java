//JOptionPane.showConfirmDialog�ķ���ֵ�� int
//JOptionPane.showInputDialog�ķ���ֵ�� string
//JOptionPane.showMessageDialog�ķ���ֵ�� void
import javax.swing.JOptionPane;
import javax.swing.ImageIcon;
public class Test7{ 
	public static void main(String[] args){
		//ȷ�϶Ի���ConfirmDialog
		//��һ��nullΪĬ��ѡ����
		ImageIcon icon = new ImageIcon("C:\\Users\\86199\\Pictures\\�½��ļ���\\Camera Roll\\happy.jpg");
		//Object��ÿһ���������,���˵ĳ���಻��������ĳ���������,�Ǿ���Object��������
		Object[] possibleVaules = {"����","������"};
		int response = JOptionPane.showConfirmDialog(null,"�������һ�ο�����ô�߼��ĶԻ�����","�����⣩ȷ�϶Ի���"
		,JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.INFORMATION_MESSAGE,icon);//����ѡ��,YES,NO,CANCEL
		if(response == JOptionPane.YES_OPTION)
			System.out.println("������,�Ҿ�����ôţƤ!");
		if(response == JOptionPane.NO_OPTION)
			System.out.println("��,С�ϵ�,ͦţѽ!");
		if(response == JOptionPane.CANCEL_OPTION)
			System.out.println("�úõĸ�����Ҫȡ��!��");
		//��ʾ�����ı��Ի���
		String inputVaule = (String)JOptionPane.showInputDialog(null,"��������Լ�����д���ղ�����ĶԻ�����?����ϸ˵��"
														,"�����������,��ʡ�Բ�д"
														,JOptionPane.INFORMATION_MESSAGE
														,null,
														possibleVaules,
														possibleVaules[0]);
		System.out.println("��Ļش�:"+inputVaule);
		
		//��ʾ��Ϣ�Ի���
		if(inputVaule.equals("����") == true)//��һ���ش� ��"����"����ʾ
			JOptionPane.showMessageDialog(null,"������ʾ����"
										,"�������Ǳ���"
										,JOptionPane.ERROR_MESSAGE
										,icon);
		else
			JOptionPane.showMessageDialog(null,"��û�������ҵ�Ĭ���ַ���--����"
										,"������Ҳ�Ǳ���"
										,JOptionPane.INFORMATION_MESSAGE
										,icon);
		//System.out.println("�ǵ�������ͽ�����,����"); //��仰�ǻ��������
	}
}