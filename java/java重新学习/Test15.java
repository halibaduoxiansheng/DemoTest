//java对GUI的支持通过其丰富的软件包来实现
import java.awt.*;
import javax.swing.*;
import javax.swing.JOptionPane;
import javax.swing.ImageIcon;
public class Test15{
	public static void main(String[] args){
		//
		ImageIcon icon = new ImageIcon("C:\\Users\\86199\\Pictures\\桌面背景\\索隆.png");
		Object []selections = {"第一","第二","第三"};
		/*JOptionPane.showConfirmDialog(null
									,"我是一个确认对话框");*/
		/*JOptionPane.showConfirmDialog(null
									,"我是一个确认对话框"
									,"确认标题框"
									,JOptionPane.OK_CANCEL_OPTION);*/
		
		JOptionPane.showConfirmDialog(null
									,"对话框"
									,"B标题"
									,JOptionPane.YES_NO_CANCEL_OPTION
									,JOptionPane.ERROR_MESSAGE);
		/*JOptionPane.showConfirmDialog(null
									,"对话框"
									,"标题"
									,JOptionPane.YES_NO_CANCEL_OPTION
									,JOptionPane.INFORMATION_MESSAGE
									,icon);
		JOptionPane.showMessageDialog(null
									,"对话框"
									,"标题"
									,JOptionPane.INFORMATION_MESSAGE
									,icon);
		JOptionPane.showOptionDialog(null
									,"请选择"
									,"标题"
									,JOptionPane.YES_NO_CANCEL_OPTION
									,JOptionPane.INFORMATION_MESSAGE
									,icon
									,selections
									,selections[0]);
		//以下为下拉
		JOptionPane.showInputDialog(null
									,"请选择"
									,"标题"
									,JOptionPane.INFORMATION_MESSAGE
									,icon
									,selections
									,selections[0]);
									*/
	}
}