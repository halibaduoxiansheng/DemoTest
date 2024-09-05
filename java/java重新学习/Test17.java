import java.io.File;
import java.io.IOException;

public class Test17{
	public static boolean createFile(String destFileName){
		File file = new File(destFileName);
		//用到了file.createNewFile()函数
		if(file.exists()){//该文件已经存在的
			System.out.println("创建单个文件"+destFileName+"失败，目标文件已存在");
			return false;
		}
		
		//endWith测试是否以指定的字符串结束
		if(destFileName.endsWith(File.separator)){//separator 文件的路径分隔符
			System.out.println("创建单个文件"+destFileName+"失败，目标文件不能为目录");
			return false;
		}
		
		if(!file.getParentFile().exists()){//防止父目录不存在,所以可以用mkdirs 
			System.out.println("创建"+file.getName()+"所在目录不存在,正在创建!");
			
			if(!file.getParentFile().mkdirs()){//不存在就创建父目录
				System.out.println("创建目标文件所在目录失败!");
				return false;
			}
		}
		
		try{
			if(file.createNewFile()){
				//即使在逻辑上毫无问题时，都应该写上一个可能出现未知问题的处理办法,这便是严谨性
				System.out.println("创建单个文件"+destFileName+"成功！");
				return true;
			}else{
				System.out.println("创建单个文件"+destFileName+"失败！");
				return false;
			}
		}catch (IOException e){
			e.printStackTrace();//在命令行打印异常信息在程序中出错的位置及原因
			System.out.println("创建单个文件"+destFileName+"失败"+e.getMessage());
			return false;
		}
		finally{
			System.out.println("结束!");
		}
	}
	public static void main(String[] args){
		String dirName = "C:\\Users\\86199\\Desktop\\复习\\java\\java重新学习";
		//上面的是母地址
		String fileName = dirName+"\\java重新学习.txt";//也就是字符相加
		//无论原有的基础上是否存在同名的,都会创建一个,只不过除非原有的那个就是这里创建的才会返回失败
		Test17.createFile(fileName);
		}
}	