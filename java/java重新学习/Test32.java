public class Test32 {
    public static void main(String[] args) {
        //Ƕ�����ʹ�� ����һ��������д������һ����
        //��Ϊ �Ǿ�̬Ƕ���� �� ��̬Ƕ����
        // ������� �� inner class���ڲ��ࣩ
        CPU cpu = new CPU();  // �������ⲿ���ඨ���һ��һ�� �����

        CPU.Processer processor = cpu.new Processer();  // ����.���� ��ʽʹ���ڲ���
        CPU.RAM ram = cpu.new RAM();  // ���������Ծ���Ҫʹ���ⲿ�������

        System.out.println("Processer cache is:"+processor.getCache());
        System.out.println("RAM clock speed is:"+ram.getClockSpeed());

        // ��̬���ʹ��
        motherborad.USA usa = new motherborad.USA(); // ����:������Ҫ�����ഴ������
        System.out.println("�ܺ�:"+usa.getsbsum());
    }
}
class CPU {
    CPU (){}
    double price;
    class Processer {
        // Ƕ���ڲ���Ա
        double cores;
        String manufacturer;

        double getCache() {
            return 4.3;
        }
    }

    // Ƕ���ܱ�������
    protected class RAM {
        double memory;
        String manufacturer;

        double getClockSpeed() {
            return 5.5;
        }
    }
}
class motherborad {
    static class USA {
        int sb1 = 1;
        int sb2 = 2;
        int getsbsum() {
            return sb1+sb2;
        }
    }
}