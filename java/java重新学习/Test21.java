import java.util.*;
public class Test21{
	public static void main(String[] args){
		//System.out.println("���"+
		//"ʹ��"); //���ַ��лᷢ�����ԵĴ���
		Calendar calendar = new GregorianCalendar();
		System.out.println("Current time is:"+new Date());
		System.out.println("YEAR:"+calendar.get(Calendar.YEAR));
		System.out.println("MONTH:"+(calendar.get(Calendar.MONTH)+1)); //0��ʾһ��
		System.out.println("DATE:"+calendar.get(Calendar.DATE));
		System.out.println("HOUR:"+calendar.get(Calendar.HOUR)+" ʮ��Сʱ��"); //ʮ��Сʱ��
		System.out.println("HOUR_OF_DAY:"+calendar.get(Calendar.HOUR_OF_DAY)+" ��ʮ��Сʱ��"); //��ʮ��Сʱ��
		System.out.println("MINUNT:"+calendar.get(Calendar.MINUTE));
		System.out.println("SECOND:"+calendar.get(Calendar.SECOND));
		System.out.println("DAY_OF_WEEK:"+calendar.get(Calendar.DAY_OF_WEEK)); //1��������
		System.out.println("DAY_OF_MONTH:"+calendar.get(Calendar.DAY_OF_MONTH));
		System.out.println("DAY_OF_YEAR:"+calendar.get(Calendar.DAY_OF_YEAR));
		System.out.println("WEEK_OF_MONTH:"+calendar.get(Calendar.WEEK_OF_MONTH));
		System.out.println("WEEK_OF_YEAR:"+calendar.get(Calendar.WEEK_OF_YEAR));
		String[] am_pmName = {"����","����"}; 
		System.out.println("AM_PM:"+am_pmName[calendar.get(Calendar.AM_PM)]); //��������һ�д���,���������Ϊֱ�۵�������
		//�����Զ���һ��ʱ��,Ȼ���жϸ�ʱ���һЩ��ϵ
		Calendar calendar1 = new GregorianCalendar(2022,2,4);
		String[] dayNameOfWeek = {"Sunday","Monday","Tuesday","Wednesday","Thurday","Firday","Saturday"};
		System.out.println("2022��2��4����"+dayNameOfWeek[calendar.get(Calendar.DAY_OF_WEEK)-1]);
	}
}