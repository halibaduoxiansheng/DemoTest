import java.io.File;//�ļ���Ҫ�İ�
import java.text.SimpleDateFormat;//����������һ��Ϊ�������ʱ�䣨�������İ�
import java.util.Date;
public class Test16{
	public static void main(String[] args){
		File file = new File("C:\\java����ѧϰ\\test.txt"); //����ָ����·������һ��File����
		//��˫\��ԭ��:��Ϊ��Ҫ��������ȡ��\����Ҫ��ǰ���ټ�һ��\
		System.out.println("�ļ���:"+file.getName());
		
		System.out.println("����·��:"+file.getAbsolutePath());
		
		System.out.println("·��Ϊ:"+file.getPath());
		
		System.out.println("��������Ŀ¼Ϊ:"+file.getParent());
		
		if(!file.exists()){//���е��ļ���Ȼ���и�Ŀ¼
			file.mkdir();//����Ŀ¼,�ұ��븸Ŀ¼����,���򴴽�ʧ�� boolean��
		}
		System.out.println("��·������ʾ���ļ���һ��Ŀ¼��?"+file.isDirectory());
		
		System.out.println("�����ڿɶ�״̬��?"+file.canRead());
		
		System.out.println("�����ڿ�д״̬��"+file.canWrite());
		
		System.out.println("���ļ�����Ϊ:"+file.length()+"�ֽ�");
		
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");//��ʱ����Ӿ��廯
		String date = df.format(new Date(file.lastModified()));
		System.out.println("���ļ�������޸�ʱ��Ϊ:"+date);
	}
}
		
		
		