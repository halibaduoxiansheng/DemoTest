//JOptionPane.showOptionDialog��JOptionPane.showMessageDialog��JOptionPane.showInputDialog��JOptionPane.showConfirmDialog���ܺ�
//����ֵΪ int
import javax.swing.JOptionPane; //ͬ��,�������������
import javax.swing.ImageIcon; //����ͼƬ��
public class Test8{
	public static void main(String[] args){
		int aa = 1234;
		String aa1 = aa+"";
		System.out.println(aa1);
		String[] options = {"ȷ��","ȡ��","����"};
		int response = JOptionPane.showOptionDialog(null, //���null����ʹ��Ĭ�ϵĸ����ڣ�����Ļ������ʾ
				"���ǶԻ��򲿷�,��������û��Լ�ѡ��ť����",
				"����ѡ��Ի�����ⲿ��",
				JOptionPane.DEFAULT_OPTION, 
				JOptionPane.QUESTION_MESSAGE, //�Ի�����ʾ�ʺ�ͼ��
				null, //����������ͼ�� 
				options, //��ʾʹ�ø�������Ϊ��ť,�����Լ���ʾ
				options[1]); //Ĭ�ϰ�ť,�����и�����һ�����ʾ
		if(response == 0)//��һ����ť����ֵ
			System.out.println("���ѡȷ��?");
		else if(response == 1)
			System.out.println("��֪��ѡ��Ĭ�ϵ�,ȡ����ȡ��!");
		else if(response == 2)
			System.out.println("�ް���!");
		System.out.println("����������ʵ�������б�!");
		ImageIcon icon = new ImageIcon("C:\\Users\\86199\\Pictures\\���汳��\\��¡.png");
		//�ڷ����Ƿ��ŵ�ʱ��Ҳ�ǿ���дJOptionPane.QUESTION_MESSAGE
		//Ĭ���������б����ʽ�� JOptionPane.InputDialog �ķ���ֵ��Object�͵�
		String str3 = (String)JOptionPane.showInputDialog(null,"��ѡ�����µļ���ѡ��","�����б���ⲿ��"
									,JOptionPane.QUESTION_MESSAGE
									,icon
									,options
									,options[0]);
		if(str3.equals("ȷ��") == true)
			System.out.println("�㾹Ȼ�Ѿ�ѡ����ȷ��,��ôû��˵");
		else if(str3.equals("ȡ��") == true)
			System.out.println("������ʲôԭ��ѡ��ȡ�����أ�");
		else if(str3.equals("����") == true)
			JOptionPane.showMessageDialog(null,"��ʵ��Ҳ��֪�������,�Լ�����ร","�������ⲿ��",
									JOptionPane.INFORMATION_MESSAGE);
	}
}
