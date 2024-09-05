//JOptionPane.showOptionDialog是JOptionPane.showMessageDialog、JOptionPane.showInputDialog、JOptionPane.showConfirmDialog的总和
//返回值为 int
import javax.swing.JOptionPane; //同样,这个包不能少了
import javax.swing.ImageIcon; //放入图片的
public class Test8{
	public static void main(String[] args){
		int aa = 1234;
		String aa1 = aa+"";
		System.out.println(aa1);
		String[] options = {"确认","取消","帮助"};
		int response = JOptionPane.showOptionDialog(null, //这个null代表使用默认的父窗口，于屏幕中央显示
				"我是对话框部分,后面可以用户自己选择按钮个数",
				"我是选择对话框标题部分",
				JOptionPane.DEFAULT_OPTION, 
				JOptionPane.QUESTION_MESSAGE, //对话框显示问号图标
				null, //标题栏不带图标 
				options, //表示使用该数组作为按钮,个数以及显示
				options[1]); //默认按钮,就是有个特殊一点的显示
		if(response == 0)//第一个按钮返回值
			System.out.println("你敢选确认?");
		else if(response == 1)
			System.out.println("就知道选择默认的,取消就取消!");
		else if(response == 2)
			System.out.println("无帮助!");
		System.out.println("接下来尝试实现下拉列表!");
		ImageIcon icon = new ImageIcon("C:\\Users\\86199\\Pictures\\桌面背景\\索隆.png");
		//在放入标记符号的时候也是可以写JOptionPane.QUESTION_MESSAGE
		//默认在下拉列表的形式下 JOptionPane.InputDialog 的返回值是Object型的
		String str3 = (String)JOptionPane.showInputDialog(null,"请选择以下的几种选项","下拉列表标题部分"
									,JOptionPane.QUESTION_MESSAGE
									,icon
									,options
									,options[0]);
		if(str3.equals("确认") == true)
			System.out.println("你竟然已经选择了确认,那么没的说");
		else if(str3.equals("取消") == true)
			System.out.println("您是有什么原因选择取消的呢？");
		else if(str3.equals("帮助") == true)
			JOptionPane.showMessageDialog(null,"其实我也不知道如何你,自己自求多福","帮助标题部分",
									JOptionPane.INFORMATION_MESSAGE);
	}
}
