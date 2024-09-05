import java.io.File;//文件需要的包
import java.text.SimpleDateFormat;//此行与下面一行为后面输出时间（调整）的包
import java.util.Date;
public class Test16{
	public static void main(String[] args){
		File file = new File("C:\\java重新学习\\test.txt"); //根据指定的路径创建一个File对象
		//打双\的原因:因为想要编译器读取到\就需要在前面再加一条\
		System.out.println("文件名:"+file.getName());
		
		System.out.println("绝对路径:"+file.getAbsolutePath());
		
		System.out.println("路径为:"+file.getPath());
		
		System.out.println("所属磁盘目录为:"+file.getParent());
		
		if(!file.exists()){//已有的文件自然必有父目录
			file.mkdir();//创建目录,且必须父目录存在,斗则创建失败 boolean型
		}
		System.out.println("此路径名表示的文件是一个目录吗?"+file.isDirectory());
		
		System.out.println("它处于可读状态吗?"+file.canRead());
		
		System.out.println("它处于可写状态吗？"+file.canWrite());
		
		System.out.println("该文件长度为:"+file.length()+"字节");
		
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");//将时间更加具体化
		String date = df.format(new Date(file.lastModified()));
		System.out.println("该文件的最后修改时间为:"+date);
	}
}
		
		
		