
//Ä¬ÈÏÖµ ¶ÔÏó:null »ù±¾Êý¾ÝÀàÐÍ:0 boolean:false 
//±»final¶¨ÒåµÄ±äÁ¿¼´Îª³£Á¿£¬±»¶¨ÒåµÄº¯ÊýÎª×îºóº¯Êý£¬²»ÄÜ±»¸²¸Ç(extends)£¬±»¶¨ÒåµÄÀàÎª×îÖÕÀà£¬²»ÄÜ±»ÅÉÉú
import sun.security.timestamp.TSResponse;

import java.util.*;

//ÊýµÄ×î¸ßÎ»Îª·ûºÅÎ»£¬Îª1ÊÇ´ú±í¸ºÊý£¬Îª0ÊÇ´ú±íÕýÊý
public class Test1 {
	public static void main(String[] args) {
		int a = 0; // ÕûÐÍ 4¸ö×Ö½Ú
		byte b = 0; // ×Ö½ÚÐÍ 1¸ö×Ö½Ú
		short c = 0; // ¶ÌÕûÐÍ 2¸ö×Ö½Ú
		long d = 0L; // ³¤ÕûÐÍ 8¸ö×Ö½Ú
		float e = 0.0f; // µ¥¾«¶È¸¡µãÊýÀàÐÍ 4¸ö×Ö½Ú floatÐÍÒªÐ´ÉÏf,¶ødoubleÐÍ²»ÓÃ¼Ó
		double f = 0.0; // Ë«¾«¶È¸¡µãÊýÀàÐÍ 8¸ö×Ö½Ú
		boolean g = true; // ²¼¶ûÀàÐÍÊý¾Ý 1¸ö×Ö½Ú Î´³õÊ¼»¯µÄÎªfalse
		char h = 'a'; // ×Ö·ûÀàÐÍ 2¸ö×Ö½Ú(ÕâÒ»µãÓëc²»ÓÃ£¬cÖÐÖ»Õ¼ÓÃÒ»¸ö×Ö½Ú£¬µ«ÏàÍ¬µÄÊÇ¶¼ÓÃ'')

		String i = "ÄãºÃÑ½!"; // ×Ö·û´®ÀàÐÍ
		// StringÐÍ±äÁ¿iÊµ¼ÊÉÏ¾ÍÊÇÒ»¸öÒýÓÃÀàÐÍµÄ±äÁ¿,±äÁ¿iÖÐ´æ´¢µÄÊÇ"ÄãºÃÑ½"µÄÒýÓÃ,¶ø²»ÊÇ"ÄãºÃÑ½"×Ö·û´®±¾Éí
		Scanner reader = new Scanner(System.in);
		System.out.println("ÏÈ¼òµ¥Êã·¢Ò»ÏÂÎÒµ±Ê±µÄÈÈÇé£¬ºÃ£¬ÏÖÔÚ¿ªÊ¼£¡£¡£¡");
		System.out.println("EDGÅ£±Æ!");

		System.out.print("ÇëÊäÈëÒ»¸öaµÄÖµ£¨ÕûÐÍ£©:"); // reader.nextInt();ÊÇÊäÈëÕûÐÍÊý¾Ý
		a = reader.nextInt();
		System.out.println("ËùÒÔÄú¸Õ²ÅÊäÈëµÄaÊÇ£º" + a);

		System.out.println("ÓÐ±ØÒªËµÒ»ÏÂbyteÊý¾ÝÀàÐÍ×î´óÎª127,×î¸ßÎ»ÊÇ·ûºÅÎ»£¬2^6+2^5+2^4+2^3+2^2+2^1+2^0=127");
		System.out.print("Í¬Ñù£¬ÏÖÔÚÇëÔÙÊäÈëÒ»¸öbµÄÖµ£¨×Ö½ÚÐÍ£©:");
		b = reader.nextByte();
		System.out.println("ËùÒÔ£¬Äú¸Õ²ÅÊäÈëµÄbÊÇ£º" + b);

		System.out.print("ÔÙÍ¬Ñù£¬ÇëÔÙÊäÈëÒ»¸öcµÄÖµ£¨¶ÌÕûÐÍ£©:");
		c = reader.nextShort();
		System.out.println("ËùÒÔ£¬Äú¸Õ²ÅÊäÈëµÄcÊÇ£º" + c);

		System.out.print("ºÙºÙ£¬ÇëÔÙÊäÈëÒ»¸ödµÄÖµ£¨³¤ÕûÐÍ£©:");
		d = reader.nextLong();
		System.out.println("ËùÒÔ£¬Äú¸Õ²ÅÊäÈëµÄdÊÇ£º" + d);

		System.out.print("àÅ£¬ÇëÔÙÔÙÊäÈëÒ»¸öeµÄÖµ£¨µ¥¾«¶È¸¡µãÊý£©:");
		e = reader.nextFloat();
		System.out.println("ËüµÄÖµeÊÇ(to be the best,i think you should add the character as L)£º" + e);

		System.out.print("ÇëÔÙÔÙÔÙÊäÈëÒ»¸öfµÄÖµ£¨Ë«¾«¶È¸¡µãÊý£©:");
		f = reader.nextDouble();
		System.out.println("Ë«¾«¶È¸¡µãÊýfµÄÖµÊÇ£º" + f);

		System.out.print("ÇëÊäÈëÒ»¸ögµÄÖµ£¨²¼¶ûÀàÐÍ,¼´true or false£©:");
		g = reader.nextBoolean();
		System.out.println("²¼¶ûÖµg=" + g);

		System.out.println("Ô­ÀíÊÇ»ñÈ¡×î³õµÄÒ»¸ö×Ö½Ú!ËùÒÔ¼´Ê¹ÊÇÊäÈë×Ö·û´®Ò²Ö»ÊÇ»ñÈ¡µÚÒ»¸ö×ÖÄ¸!");
		System.out.print("ÇëÊäÈëÒ»¸öhµÄÖµ£¨×Ö·û£©:");
		h = reader.next().charAt(0);// ¶ÁÈ¡ÏÂ±êÎª0µÄ×Ö·û ÏÂ±ê´Ó0¿ªÊ¼ÊÇÖªµÀµÄ,µ±È»£¬Èç¹ûÄãÆäÖÐÐ´ÉÏ1£¬ÄÇÃ´¾ÍÊÇµÚ¶þ¸ö×Ö½Ú
		System.out.println("h=" + h);

		System.out.print("ÇëÊäÈëÒ»¸öiµÄÖµ£¨×Ö·û´®£©:");
		i = reader.next(); // nextLine() ÊÇ¿ÉÒÔ¶ÁÈ¡¿Õ¸ñµÄ
		System.out.println("¸Ã×Ö·û´®ÎªiÎª£º" + i);

		Test1 ab = new Test1();
		boolean ok = ab instanceof Test1;
		if(ok)
			System.out.println("ËµÃ÷¶ÔÏóaÊÇÀàTest1µÄ");

		// javaµÄëS™C”µÓÐƒÉ·N
		// 1.Math.random()
//		double random_Value =  Math.random();  // ·µ»ØÖµÊÇdoubleÐÍµÄ
		int random_Value =  (int)(Math.random()*10+3);  // ÊÇ°üº¬ÔÚjava.langÏÂµÄ°ü [3,13)
		System.out.println("random_Value="+random_Value);

		// ÁíÍâÒ»‚€ÊÇjava.util.Random;
		Random random = new Random();
		int value_R = random.nextInt(5); // ¹ ‡ú [0,5)
		System.out.println("value_R="+value_R);
	}
}