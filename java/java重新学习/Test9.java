import javax.swing.JOptionPane;
public class Test9{ //�ȶԻ���ͼ��,�ٱ���ͼ��
	public static void main(String[] args){
		//
		Object[] possibleValues = {"first","Second","Third"}; //Object��һ����,������û�и���ĸ���
		Object selectedVaule = JOptionPane.showInputDialog(null,"��ѡ��","������ⲿ��"
								,JOptionPane.INFORMATION_MESSAGE //�Ի�����ʾ̾��ͼ��
								,null //���ⲻ��ͼ��
								,possibleValues //�ø������������б���û�ѡ��
								,possibleValues[0]); //����Ĭ��ѡ���ѡ��
		System.out.println("��������"+(String)selectedVaule+"��Ŀ");
		//��JOptionPane.showOptionDialog(...);ʮ������ �ټ���JOptionPane.showInputDialog();�����б���
		String str = (String)JOptionPane.showInputDialog(null,"��ѡ��","������ⲿ��",//�������ͱ�ΪObject,ǿ��ת��ΪString
								JOptionPane.INFORMATION_MESSAGE
								,null
								,possibleValues
								,possibleValues[0]);
		System.out.println("�ո�����ĵ�:"+str+"��Ŀ");
		//������ʾЧ��һģmuһ��
	}
}