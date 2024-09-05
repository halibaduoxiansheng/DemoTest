import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class GreetingServer extends Thread { // 服务端
    private ServerSocket serverSocket;

    public GreetingServer(int port) throws IOException {
        serverSocket = new ServerSocket(port);
        serverSocket.setSoTimeout(10000);
    }

    public void run() {
        while(true) {
            try {
                System.out.println("dengdaiyuanchenglianjie, daunkouhaowei:"+serverSocket.getLocalPort()+"so on .");
                Socket server = serverSocket.accept();
                System.out.println("yuanchengzhujidizhi:"+server.getRemoteSocketAddress());
                DataInputStream in = new DataInputStream(server.getInputStream());
                System.out.println(in.readUTF());
                DataOutputStream out = new DataOutputStream(server.getOutputStream());
                out.writeUTF("thank you to conect me:"+server.getLocalSocketAddress()+"\ngoodbye");
                server.close();

            }catch(Exception e) {
                e.getStackTrace();
            }
        }
    }
    public static void main(String[] args) {
        int port = 8070; // 与前面(GreetingClient)的一样
        try {
            Thread t = new GreetingServer(port);
            t.run();

        }catch(Exception e) {
            e.getStackTrace();
        }
    }
}
