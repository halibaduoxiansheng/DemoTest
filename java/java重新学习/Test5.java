import javax.swing.JOptionPane;//导入一个javax.swing下的JOptionPane类
import javax.swing.ImageIcon;
//应用编程接口 api 分有java和javax javax是扩展包
import java.util.Random; //随机数所需类
import java.util.Scanner;
public class Test5{
	public static void main(String[] args){
		//
		ImageIcon icon = new ImageIcon("C:\\Users\\86199\\Pictures\\新建文件夹\\Camera Roll\\happy.jpg");
		String str2 = JOptionPane.showInputDialog(null,"没错的话我这个对话框应该是正常输出的","嗯嗯");
		String str = JOptionPane.showInputDialog(null,"请输入一个字符串,我们将其转化为double型:","TMD想打字就快些");
		//下面是正常输出的JOptionPane.showInputDialog的一种比较常用的对话框形式
		if(str != "000"){
			JOptionPane.showConfirmDialog(null,"友善回复","您TM的就是欠的",JOptionPane.YES_NO_CANCEL_OPTION
			,JOptionPane.INFORMATION_MESSAGE,icon);	
		}
	//	double r1 = Double.parseDouble(str);//括弧里面只能是字符串,或则是控制台的命令行
	//	System.out.println("它的double型为"+r1);
		
		//随机数方法1 
		//下面的为无种子的,所以随机数一直在变,如果在Random(4)，价格类似4的数,就为有种子的,那个将不变,除非种子也跟着变
		Scanner reader = new Scanner(System.in);
		System.out.println("(随机数产生)请输入一个种子:");
		long bb = reader.nextLong();
		Random random = new Random(bb); //随机数都是double型,此处就不需要强制转化
		int r2 = random.nextInt(12); //生成随机数赋值  默认范围[0,1) 括弧里面写上数就是(5)----范围[0,5)
		//nextDouble就不容易变换数据大小
		//int r3 = random.nextInt();  //参考上一行代码可知规律
		System.out.println("产生随机数Int型数据r2="+r2);
		
		//随机数方法2
		int a = (int)(Math.random()*7+9); //范围,从9开始,到16（9+7）,不包活16 默认也是[0,1)
		System.out.println("随机数a="+a);
		
		String a1 = "abcdef";
		String a2 = "bcdefg";
		boolean b = a1.equals(a2);
		System.out.println("字符串a1（abcdef）与字符串a2（bcdefg）相等是"+b+"\n");//多分行一次 相等返回true,不相等返回false
		
		int a3[] = new int[]{1,2,3,4};
		int []a4 = new int[3];//未初始化的就按照原本的类型自动初始化了
		System.out.println("a3[0]="+a3[0]);
		System.out.println("没初始化的a4[0]="+a4[0]);
	}
}