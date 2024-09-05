// 请再看一次  把用到的函数 没用到的函数都详细说明一下
import java.io.*;
import java.net.Socket;

public class GreetingClient { // 客户端
    public static void main(String[] args) {
        String serverName = "wangJie";
        int port = 8070;  // 我随意定下的
        try {
            System.out.println("lianjiedaozhuji:"+serverName+",duankouhao:"+port);
            Socket client = new Socket(serverName, port);
            System.out.println("yuanchengzhujidizhi:"+client.getRemoteSocketAddress());
            OutputStream outToServer = client.getOutputStream();
            DataOutputStream out = new DataOutputStream(outToServer);

            out.writeUTF("Hello From:"+client.getLocalSocketAddress());
            InputStream inFromServer = client.getInputStream();
            DataInputStream in = new DataInputStream(inFromServer);
            System.out.println("fuwuqixiangying:"+in.readUTF());
            client.close();

        }catch(Exception e) {
            e.getStackTrace();
        }finally {
            System.out.println("over !");
        }
    }
}
