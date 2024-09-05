package com.halibaduo.do1;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;

/**
 * @author halibaduo
 * Description: B站热搜数据快知晓
 */
public class Test4 {
    static int Num = 0;
    static String num = "1"; /* num是从1到26的  */
    public static void main(String[] args) {
        do {

            String url = "https://api.bilibili.com/x/web-interface/popular?ps=20&pn="+num; // 替换为你要访问的JSON数据的URL

            try {
                // 设置代理服务器的IP地址和端口
/*                String proxyHost = "fe80::2442:919c:5801:80a7%21";
                int proxyPort = 8081;

                // 创建代理对象
                Proxy proxy = new Proxy(Proxy.Type.HTTP, new InetSocketAddress(proxyHost, proxyPort));*/

                URL jsonUrl = new URL(url);

                HttpURLConnection connection = (HttpURLConnection) jsonUrl.openConnection();
                connection.setRequestProperty("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36");/*模拟是浏览器访问*/
                BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));

                String line;
                StringBuilder jsonBuilder = new StringBuilder();

                while ((line = reader.readLine()) != null) {
                    jsonBuilder.append(line);
                }

                reader.close();

                String jsonString = jsonBuilder.toString();
                System.out.println(jsonString); // 获取了json

                try {
                    JSONObject jsonObject = new JSONObject(jsonString);
                    JSONArray listArray = jsonObject.getJSONObject("data").getJSONArray("list");

                    for (int i = 0; i < listArray.length(); i++) {
                        JSONObject item = listArray.getJSONObject(i);
                        String title = item.getString("title");
                        String pic = item.getString("pic");
                        String ownerName = item.getJSONObject("owner").getString("name");
                        String videoUrl = item.getString("bvid");

                        System.out.println("视频标题: " + title);
                        System.out.println("视频封面: " + pic);
                        System.out.println("作者名称: " + ownerName);
                        String videoUrl1 = "https://www.bilibili.com/video/"+ videoUrl +"/?spm_id_from=333.934.0.0&vd_source=430b320228f8543528f8913267b412ec";
                        System.out.println("视频地址: " + videoUrl1);
                        Num++;
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }

            } catch (IOException e) {
                e.printStackTrace();
            }
            int num1 = Integer.parseInt(num) + 1;
            num = String.valueOf(num1);
        } while (Integer.parseInt(num) < 25);
        System.out.println("Num:"+Num);
    }
}
