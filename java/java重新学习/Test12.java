//�ӿ�����ĳ�Ա����һ���ǹ����ġ���̬�ġ����յ� public static final,��Щ�ؼ��ֿ�ʡ�Բ�д
//�������ο�������д������������ζ��Ƕ����ڵ�
//����ĳ�Ա����һ���ǹ����ģ������ public abstract ,��Щ�ؼ��ֿ�ʡ�Բ�д
//����ӿڱ��̳У���ô��������ӿڽ����и����ӿڵ����з���
public class Test12{
	public static void main(String[] args){
		lizi m = new lizi();
		m.getSalary();
		m.show1();
	}
}
interface ISalary{
	double rate = 0.15;
	int num = 19;
	double getSalary();
	void show1();
}
//�����Ϊ�ӿ���������ÿһ������ʵ�ֶ���
//һ�������ʵ�ֲ�ֹһ���ӿ� ���£�
// class lei implements ISalary1,ISalary2{������}
class lizi implements ISalary{ //������õ���implements
	double money=0.0;
	public double getSalary(){  //  public���벻��ĳ�д����
		System.out.println("�൱�ڼ̳ж���rate="+rate+",num="+num);
		money=rate*num;
		return money;
	}
	public void show1(){//���Ϊ�ӿ�����,��ô�����ټ���public
		System.out.println("Ǯmoney="+money);
	}
	void show2(){//���Բ���Ӳ����public
		System.out.println("��Ϊ���ж���ĺ���");
	}	
}