import java.util.*;
public class Test21{
	public static void main(String[] args){
		//System.out.println("你好"+
		//"使得"); //文字分行会发现明显的错误
		Calendar calendar = new GregorianCalendar();
		System.out.println("Current time is:"+new Date());
		System.out.println("YEAR:"+calendar.get(Calendar.YEAR));
		System.out.println("MONTH:"+(calendar.get(Calendar.MONTH)+1)); //0表示一月
		System.out.println("DATE:"+calendar.get(Calendar.DATE));
		System.out.println("HOUR:"+calendar.get(Calendar.HOUR)+" 十二小时制"); //十二小时制
		System.out.println("HOUR_OF_DAY:"+calendar.get(Calendar.HOUR_OF_DAY)+" 二十四小时制"); //二十四小时制
		System.out.println("MINUNT:"+calendar.get(Calendar.MINUTE));
		System.out.println("SECOND:"+calendar.get(Calendar.SECOND));
		System.out.println("DAY_OF_WEEK:"+calendar.get(Calendar.DAY_OF_WEEK)); //1是星期天
		System.out.println("DAY_OF_MONTH:"+calendar.get(Calendar.DAY_OF_MONTH));
		System.out.println("DAY_OF_YEAR:"+calendar.get(Calendar.DAY_OF_YEAR));
		System.out.println("WEEK_OF_MONTH:"+calendar.get(Calendar.WEEK_OF_MONTH));
		System.out.println("WEEK_OF_YEAR:"+calendar.get(Calendar.WEEK_OF_YEAR));
		String[] am_pmName = {"上午","下午"}; 
		System.out.println("AM_PM:"+am_pmName[calendar.get(Calendar.AM_PM)]); //用于下面一行代码,便于输出较为直观的上下午
		//下面自定义一个时间,然后判断该时间的一些关系
		Calendar calendar1 = new GregorianCalendar(2022,2,4);
		String[] dayNameOfWeek = {"Sunday","Monday","Tuesday","Wednesday","Thurday","Firday","Saturday"};
		System.out.println("2022年2月4日是"+dayNameOfWeek[calendar.get(Calendar.DAY_OF_WEEK)-1]);
	}
}