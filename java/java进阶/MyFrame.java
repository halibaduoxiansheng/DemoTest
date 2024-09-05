/*基于Swing的图形界面编程 - 第一章*/
import javax.swing.*;//一个100%纯java实现的轻量级组件
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
		super(s);//设置标题,后面的GUIDome函数会给出
		setSize(300,300);//设置窗口的大小
		setLocationRelativeTo(null);//null为置于屏幕的中央
		
		Color c = new Color(50,100,200);//设置颜色
		Font f = new Font("仿宋",Font.BOLD+Font.ITALIC,18);
		JPanel contentPane = new JPanel();
		
		Icon icon1 = new ImageIcon("R-C.jpg");
		JLabel lab1 = new JLabel("标签1",icon1,SwingConstants.LEFT);
		//SwingConstants.LEFT,SwingConstants.CENTER,SwingConstants.RIGHT,SwingConstants.LEADING,SwingConstants.TRAILING
		
		setContentPane(contentPane);//将面板放置于框架中,setContentPane是一种方法
		contentPane.setLayout(new GridLayout());//五种布局之一FlowLayout(按键在上面)、BorderLayout(按键在下面)、
		//GridLayout(按键在右边)、CardLayout(无按键显示)、BoxLayout(参数，参数)
		
		txa=new JTextArea();
		panBtn=new JPanel();
		ImageIcon buttonIcon = new ImageIcon("R-C.jpg");
		btnOK=new JButton("确定",buttonIcon);//加一个图标
		btnCancel=new JButton("取消");
		btnHapi=new JButton("哈皮");
		panBtn.add(btnOK);
		panBtn.add(btnCancel);
		//panBtn.remove(btnCancel);
		panBtn.add(btnHapi);
		
		contentPane.add(txa,BorderLayout.CENTER);
		contentPane.add(panBtn,BorderLayout.SOUTH);
		contentPane.add(lab1);
		
		menuBar= new JMenuBar();
		this.setJMenuBar(menuBar);
		
		fileMenu = new JMenu("文件");
		openItem=new JMenuItem("打开a",'a');//a会以下划线的形式展示
		exitItem=new JMenuItem("退出");
		
		menuBar.add(fileMenu);
		fileMenu.add(openItem);
		fileMenu.add(exitItem);
		
		btnOK.setBackground(c);//成功将确认按钮设置别样的颜色
		btnOK.setForeground(Color.YELLOW);//设置前景色，也就是字体颜色
		btnOK.setFont(f);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//不知道为什么可以有NO_NOTHING_ON_CLOSE这样的流氓选择！
		setVisible(true);//设置可见性,默认为不可见（false）
		setEnabled(true);//设置可用性,默认为可用
	}
}