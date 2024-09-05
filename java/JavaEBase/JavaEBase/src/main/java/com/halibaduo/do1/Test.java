package com.halibaduo.do1;

import javax.swing.*;

/**
 * @author halibaduo
 * Description:
 */
public class Test {
    public static void main(String[] args) throws InterruptedException {
        JOptionPane.showMessageDialog(null, "我是一个软件！", "说明", JOptionPane.WARNING_MESSAGE);
        Thread.sleep(5000);
        System.out.println("ok");
    }
}

/* *
 * 四步骤：
 * 1. IntelliJ IDEA的Project Structure
 * 2. 选择Artifacts选额卡
 * 3. 点击 + ，JAR的From modules with dependencies，后选择你要的Java程序的Main入口文件
 * 4. apply后，选择Build的Build Artifact，在弹出的框中选择你再选择刚刚第三步设置的
 *
 * 暂且遇到的问题是 版本的不合适 可以考虑将版本替换
 */