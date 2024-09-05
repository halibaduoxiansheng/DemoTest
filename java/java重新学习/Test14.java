//自定义异常处理
//throws 声明异常类 throw 抛出异常
import java.util.Scanner;
import javax.swing.JOptionPane;
import javax.swing.ImageIcon;

class ScoreRangeException extends Exception{//自定义异常类名称:ScoreRangeException 继承与Exception
	ScoreRangeException(String sre){ //写好自己的构造方法
		super(sre);//调用Exception的输出方法
	}
}
public class Test14{
	static void convert(int score)throws ScoreRangeException{  //throws声明该异常
	//函数名:convert(int score);
		if(score<0 || score>100){
			ScoreRangeException e = new ScoreRangeException("不是一个正常的分数,要么小于0,要么大于100");//创建对象
			throw e;//用throw抛出该异常
		}
		else{
			//
			System.out.println("转化为等级制考试成绩为:");
			int s=score/10;
			switch(s){
				case 9: System.out.println("成绩为A"); break;
				case 8: System.out.println("成绩为B"); break;
				case 7: System.out.println("成功为C"); break;
				case 6: System.out.println("成绩为D"); break;
				default : System.out.println("没及格,准备父母的一顿毒打并为下半补考做好准备");
			}
		}
	}
	public static void main(String[] args){//同问静态函数的main可以调用convert(int score)函数
		Scanner reader = new Scanner(System.in);
		System.out.println("请输入你的期末考试成绩（百分制）:");
		int score = reader.nextInt();
		try{
			convert(score);
		}
		catch(ScoreRangeException e){
			System.out.println(e.toString());//也可以写e.getMessage()
		}
		finally{//一个可写可不写的部分 但是写了就一定输出
			ImageIcon icon = new ImageIcon("C:/Users/86199/Pictures/桌面背景/花.jpg");
			JOptionPane.showMessageDialog(null,"您确定你下学期能考好吗?"
											,"提问"
											,JOptionPane.INFORMATION_MESSAGE
											,icon);
			String[] choose = {"第一","第二","第三"};
			JOptionPane.showMessageDialog(null,"恭喜您已经会使用本程序了!","提示",JOptionPane.INFORMATION_MESSAGE);
			int response = JOptionPane.showOptionDialog(null,"你认为你下学期努力的话能考第几名,请于下列选项中选择"
										,"选择框"
										,JOptionPane.YES_NO_CANCEL_OPTION
										,JOptionPane.INFORMATION_MESSAGE
										,icon
										,choose
										,choose[2] //设置默认选项
										);
			if(response == 0)
				JOptionPane.showMessageDialog(null,"你可真是会吹牛","显示框",JOptionPane.INFORMATION_MESSAGE,icon);
			else if(response == 1)
				JOptionPane.showMessageDialog(null,"没想到你还是能谦虚的吗!","显示框",JOptionPane.INFORMATION_MESSAGE,icon);
			else if(response == 2)
				JOptionPane.showMessageDialog(null,"没有志向的吗？垃圾","显示框",JOptionPane.INFORMATION_MESSAGE,icon);
			System.out.println("程序完美结束!");
		}
	}
}