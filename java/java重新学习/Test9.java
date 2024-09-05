import javax.swing.JOptionPane;
public class Test9{ //先对话框图标,再标题图标
	public static void main(String[] args){
		//
		Object[] possibleValues = {"first","Second","Third"}; //Object是一种类,是所有没有父类的父类
		Object selectedVaule = JOptionPane.showInputDialog(null,"请选择","输入标题部分"
								,JOptionPane.INFORMATION_MESSAGE //对话框显示叹号图标
								,null //标题不带图标
								,possibleValues //用该数组做下拉列表给用户选择
								,possibleValues[0]); //设置默认选择的选项
		System.out.println("您按下了"+(String)selectedVaule+"项目");
		//与JOptionPane.showOptionDialog(...);十分相似 再加上JOptionPane.showInputDialog();下拉列表结合
		String str = (String)JOptionPane.showInputDialog(null,"请选择","输入标题部分",//返回类型本为Object,强制转化为String
								JOptionPane.INFORMATION_MESSAGE
								,null
								,possibleValues
								,possibleValues[0]);
		System.out.println("刚刚输入的的:"+str+"项目");
		//两个显示效果一模mu一样
	}
}