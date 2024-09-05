package com.halibaduo.do1;

import jdk.nashorn.internal.ir.IfNode;

import javax.swing.*;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URI;
import java.net.URISyntaxException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Objects;
import java.util.regex.Pattern;

/**
 * @author halibaduo
 * Description: 用户设置定时给qq的某位好友发送消息 （未能完全实现）
 */
public class Test2 {
    private static int goto1 = 1; // 1就退出 ， 0就再执行一便
    public static void main(String[] args) throws IOException, URISyntaxException, InterruptedException {
        try {
            // 设置外观为系统默认外观
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }

        String time1 = "abc";
        boolean isValidFormat = true;
        do {
            do {
                A a1 = new A(); // 获取用户使用本程序时的时间
                String currentTime = a1.a1();
                time1 = JOptionPane.showInputDialog(null, // 用户输入
                        "请输入发送时间(格式请保存一致)",
                        currentTime);
                if (Objects.isNull(time1)) {
                    JOptionPane.showMessageDialog(null, "程序不确认无法继续工作！", "警告", JOptionPane.WARNING_MESSAGE);
                }
            } while (Objects.isNull(time1));


            // 定义日期时间格式的正则表达式
            String pattern = "\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}";
            // 匹配输入的字符串与正则表达式
            isValidFormat = Pattern.matches(pattern, time1);
            if (!isValidFormat) {
                // 显示警告窗口
                JOptionPane.showMessageDialog(null, "格式错误！", "警告", JOptionPane.WARNING_MESSAGE);
            }
        } while (!isValidFormat); // 格式错误会重新提示输入

        do {
            A a2 = new A(); // 获取系统的时间，好确定是否执行程序
            if (a2.a1().equals(time1)) {
                System.out.println("时间一致 返回true");

                try {
                    ProcessBuilder builder = new ProcessBuilder("tasklist");
                    Process process = builder.start();
                    InputStream inputStream = process.getInputStream();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
                    String line;
                    boolean isQQRunning = false;
                    while ((line = reader.readLine()) != null) {
                        if (line.contains("QQ.exe")) {
                            isQQRunning = true;
                            break;
                        }
                    }
                    if (isQQRunning) {
                        System.out.println("QQ登录success");

                        builder = new ProcessBuilder("cmd", "/c", "start qq.exe");
                        builder.start();
                        // !!!!!!!!!!!!! 似乎没有法子可以获得qq的掌握权
                        /* *
                         * 涉及到QQ互联平台，需要注册成为开发人员，获取id和key
                         * 所以项目到此终结
                         */

                    } else {
                        System.out.println("QQ未登录 请先登录qq"); // 还没启动就帮助你启动
                        Process process1 = Runtime.getRuntime().exec("C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQ.exe");
                        if (process1 != null) {
                            Thread.sleep(4000); // 等待启动
                            process1.destroy();
                        } else { // 没有安装qq就自动跳转下载页面
                            if (Desktop.isDesktopSupported()) {
                                Desktop desktop = Desktop.getDesktop();
                                if (desktop.isSupported(Desktop.Action.BROWSE)) {
                                    try {
                                        desktop.browse(new URI("https://im.qq.com/pcqq/"));
                                    } catch (Exception e) {
                                        e.printStackTrace();
                                    }
                                }
                            }
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
                goto1 = 1;
            }
            else {  // 发现时间对不上就再执行一下
                System.out.println("时间不匹配");
                Thread.sleep(5000); // 每隔5秒触发一次检查
                goto1 = 0;
            }
        } while (goto1 == 0);
    }
}
class A{
    protected String a1() {
        // 获取系统当前时间
        LocalDateTime currentTime = LocalDateTime.now();

        // 定义日期时间格式
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
        String formattedTime = currentTime.format(formatter);

        // 打印当前时间
        return formattedTime;
    }
}
