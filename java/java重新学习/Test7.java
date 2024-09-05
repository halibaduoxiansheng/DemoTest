//JOptionPane.showConfirmDialog的返回值是 int
//JOptionPane.showInputDialog的返回值是 string
//JOptionPane.showMessageDialog的返回值是 void
import javax.swing.JOptionPane;
import javax.swing.ImageIcon;
public class Test7{ 
	public static void main(String[] args){
		//确认对话框ConfirmDialog
		//第一个null为默认选择父类
		ImageIcon icon = new ImageIcon("C:\\Users\\86199\\Pictures\\新建文件夹\\Camera Roll\\happy.jpg");
		//Object是每一个类的祖先,如果说某个类不属于其中某个类的派生,那就是Object类派生的
		Object[] possibleVaules = {"可以","不可以"};
		int response = JOptionPane.showConfirmDialog(null,"这是你第一次看见这么高级的对话框吗？","（标题）确认对话框"
		,JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.INFORMATION_MESSAGE,icon);//三种选项,YES,NO,CANCEL
		if(response == JOptionPane.YES_OPTION)
			System.out.println("哈哈哈,我就是这么牛皮!");
		if(response == JOptionPane.NO_OPTION)
			System.out.println("呦,小老弟,挺牛呀!");
		if(response == JOptionPane.CANCEL_OPTION)
			System.out.println("好好的干嘛需要取消!唉");
		//提示输入文本对话框
		String inputVaule = (String)JOptionPane.showInputDialog(null,"你觉得你自己可以写出刚才上面的对话框吗?请详细说明"
														,"我是输入标题,可省略不写"
														,JOptionPane.INFORMATION_MESSAGE
														,null,
														possibleVaules,
														possibleVaules[0]);
		System.out.println("你的回答:"+inputVaule);
		
		//显示信息对话框
		if(inputVaule.equals("可以") == true)//上一个回答 是"可以"就显示
			JOptionPane.showMessageDialog(null,"我是显示内容"
										,"我这里是标题"
										,JOptionPane.ERROR_MESSAGE
										,icon);
		else
			JOptionPane.showMessageDialog(null,"你没有输入我的默认字符串--可以"
										,"我这里也是标题"
										,JOptionPane.INFORMATION_MESSAGE
										,icon);
		//System.out.println("是到我这里就结束了,对吗？"); //这句话是会正常输出
	}
}