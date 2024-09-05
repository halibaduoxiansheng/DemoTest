/*����Swing��ͼ�ν����� - ��һ��*/
import javax.swing.*;//һ��100%��javaʵ�ֵ����������
import java.awt.Color;
import java.awt.Font;
import java.awt.BorderLayout;
import java.awt.*;

public class MyFrame extends JFrame{
	JTextArea txa;
	JPanel panBtn;
	JButton btnOK,btnCancel,btnHapi;
	JMenuBar menuBar;
	JMenu fileMenu;
	JMenuItem openItem,exitItem;
	
	MyFrame(String s){
		super(s);//���ñ���,�����GUIDome���������
		setSize(300,300);//���ô��ڵĴ�С
		setLocationRelativeTo(null);//nullΪ������Ļ������
		
		Color c = new Color(50,100,200);//������ɫ
		Font f = new Font("����",Font.BOLD+Font.ITALIC,18);
		JPanel contentPane = new JPanel();
		
		Icon icon1 = new ImageIcon("R-C.jpg");
		JLabel lab1 = new JLabel("��ǩ1",icon1,SwingConstants.LEFT);
		//SwingConstants.LEFT,SwingConstants.CENTER,SwingConstants.RIGHT,SwingConstants.LEADING,SwingConstants.TRAILING
		
		setContentPane(contentPane);//���������ڿ����,setContentPane��һ�ַ���
		contentPane.setLayout(new GridLayout());//���ֲ���֮һFlowLayout(����������)��BorderLayout(����������)��
		//GridLayout(�������ұ�)��CardLayout(�ް�����ʾ)��BoxLayout(����������)
		
		txa=new JTextArea();
		panBtn=new JPanel();
		ImageIcon buttonIcon = new ImageIcon("R-C.jpg");
		btnOK=new JButton("ȷ��",buttonIcon);//��һ��ͼ��
		btnCancel=new JButton("ȡ��");
		btnHapi=new JButton("��Ƥ");
		panBtn.add(btnOK);
		panBtn.add(btnCancel);
		//panBtn.remove(btnCancel);
		panBtn.add(btnHapi);
		
		contentPane.add(txa,BorderLayout.CENTER);
		contentPane.add(panBtn,BorderLayout.SOUTH);
		contentPane.add(lab1);
		
		menuBar= new JMenuBar();
		this.setJMenuBar(menuBar);
		
		fileMenu = new JMenu("�ļ�");
		openItem=new JMenuItem("��a",'a');//a�����»��ߵ���ʽչʾ
		exitItem=new JMenuItem("�˳�");
		
		menuBar.add(fileMenu);
		fileMenu.add(openItem);
		fileMenu.add(exitItem);
		
		btnOK.setBackground(c);//�ɹ���ȷ�ϰ�ť���ñ�������ɫ
		btnOK.setForeground(Color.YELLOW);//����ǰ��ɫ��Ҳ����������ɫ
		btnOK.setFont(f);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//��֪��Ϊʲô������NO_NOTHING_ON_CLOSE��������åѡ��
		setVisible(true);//���ÿɼ���,Ĭ��Ϊ���ɼ���false��
		setEnabled(true);//���ÿ�����,Ĭ��Ϊ����
	}
}