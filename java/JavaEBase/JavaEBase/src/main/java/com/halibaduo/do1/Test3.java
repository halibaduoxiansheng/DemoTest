package com.halibaduo.do1;


import org.apache.poi.ss.formula.functions.T;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import javax.swing.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.regex.Pattern;

/**
 * @author halibaduo
 * Description: 打字联系
 */
public class Test3 {
    static List<String> list = new LinkedList<>();
    static int grade = 0;
    public static void main(String[] args) {
        Test3 test3 = new Test3();
        boolean isValidFormat = false;
        String count = "abc";
        int num = 0;
        do {
            // 多少个由用户自己选择
            count = JOptionPane.showInputDialog(null, // 用户输入
                    "请输入题目总数[10,100)，每题只有10秒作答时间",
                    "请输入个数");
            String pattern = "\\d{2}";
            isValidFormat = Pattern.matches(pattern, count);
            if (!isValidFormat) {
                // 显示警告窗口
                JOptionPane.showMessageDialog(null, "格式错误！", "警告", JOptionPane.WARNING_MESSAGE);
            }
        } while (!isValidFormat);

        int gameCount = Integer.parseInt(count); // 获取用户输入的题目个数
        test3.a1();
        ListIterator<String> listiterate = list.listIterator();
        while(listiterate.hasNext()){
            String word = listiterate.next();  // 第一个.next为第一个元素

            // 创建一个倒计时线程
            Thread countdownThread = new Thread(new CountdownRunnable(10));

            // 启动倒计时线程
            countdownThread.start();

            String inputWord = JOptionPane.showInputDialog(null, // 用户输入
                    "请输入第"+(num+1)+"题："+word,
                    "");

            // 停止倒计时线程
            countdownThread.interrupt();

            if (word.equalsIgnoreCase(inputWord)) { // 不区分大小写
                grade++; // 加一分
            }
            num++; // 又多做一道题目
            if (num == gameCount) {
                break;
            }
        }

        double d = (double) grade / gameCount;
        d = d * 100;
        String formatted = String.format("%.2f", d);
        JOptionPane.showMessageDialog(null, "您的正确率是:" + formatted + "%", "Information", JOptionPane.WARNING_MESSAGE);
    }
    protected void a1() {
        // 创建一个File对象来表示当前工作目录
        File currentDir = new File(".");
        try {
            // 创建文件输入流
            FileInputStream file = new FileInputStream(new File(currentDir.getCanonicalPath()+"\\src\\main\\resources\\Excel\\words.xlsx"));

            // 从输入流创建工作簿对象
            XSSFWorkbook workbook = new XSSFWorkbook(file);

            // 获取第一个工作表
            XSSFSheet sheet = workbook.getSheetAt(0);

            // 遍历所有行
            for (Row row : sheet) {
                // 遍历所有列
                for (Cell cell : row) {
                    // 根据单元格类型读取单元格内容
                    switch (cell.getCellType()) {
                        case NUMERIC:
                            System.out.print(cell.getNumericCellValue() + " ");
                            break;
                        case STRING: /*都是这种 excel中全部是字符串类型的*/
//                            System.out.print(cell.getStringCellValue() + " ");
                            list.add(cell.getStringCellValue()); // 加入进去
                            break;
                        default:
                            System.out.print(" - ");
                    }
                }
                System.out.println();
            }

            // 关闭工作簿和文件输入流
            workbook.close();
            file.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
class CountdownRunnable implements Runnable {
    private int seconds;

    public CountdownRunnable(int seconds) {
        this.seconds = seconds;
    }

    @Override
    public void run() {
        while (seconds > 0 && !Thread.currentThread().isInterrupted()) {
            System.out.println("剩余时间：" + seconds + "秒");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                // 线程被中断，提前退出循环
                return;
            }
            seconds--;
        }

        // 倒计时结束，关闭输入对话框
        if (!Thread.currentThread().isInterrupted()) {
            JOptionPane.getRootFrame().dispose();
        }
    }
}
