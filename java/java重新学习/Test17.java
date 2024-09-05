import java.io.File;
import java.io.IOException;

public class Test17{
	public static boolean createFile(String destFileName){
		File file = new File(destFileName);
		//�õ���file.createNewFile()����
		if(file.exists()){//���ļ��Ѿ����ڵ�
			System.out.println("���������ļ�"+destFileName+"ʧ�ܣ�Ŀ���ļ��Ѵ���");
			return false;
		}
		
		//endWith�����Ƿ���ָ�����ַ�������
		if(destFileName.endsWith(File.separator)){//separator �ļ���·���ָ���
			System.out.println("���������ļ�"+destFileName+"ʧ�ܣ�Ŀ���ļ�����ΪĿ¼");
			return false;
		}
		
		if(!file.getParentFile().exists()){//��ֹ��Ŀ¼������,���Կ�����mkdirs 
			System.out.println("����"+file.getName()+"����Ŀ¼������,���ڴ���!");
			
			if(!file.getParentFile().mkdirs()){//�����ھʹ�����Ŀ¼
				System.out.println("����Ŀ���ļ�����Ŀ¼ʧ��!");
				return false;
			}
		}
		
		try{
			if(file.createNewFile()){
				//��ʹ���߼��Ϻ�������ʱ����Ӧ��д��һ�����ܳ���δ֪����Ĵ���취,������Ͻ���
				System.out.println("���������ļ�"+destFileName+"�ɹ���");
				return true;
			}else{
				System.out.println("���������ļ�"+destFileName+"ʧ�ܣ�");
				return false;
			}
		}catch (IOException e){
			e.printStackTrace();//�������д�ӡ�쳣��Ϣ�ڳ����г����λ�ü�ԭ��
			System.out.println("���������ļ�"+destFileName+"ʧ��"+e.getMessage());
			return false;
		}
		finally{
			System.out.println("����!");
		}
	}
	public static void main(String[] args){
		String dirName = "C:\\Users\\86199\\Desktop\\��ϰ\\java\\java����ѧϰ";
		//�������ĸ��ַ
		String fileName = dirName+"\\java����ѧϰ.txt";//Ҳ�����ַ����
		//����ԭ�еĻ������Ƿ����ͬ����,���ᴴ��һ��,ֻ��������ԭ�е��Ǹ��������ﴴ���ĲŻ᷵��ʧ��
		Test17.createFile(fileName);
		}
}	