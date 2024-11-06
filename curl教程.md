# 版本

```
X.Y.Z
主版本、次版本，修订版本
即重大变化->主版本 功能变化->此版本 bug修订->修订版本
```

curl -> **库** libcurl

curl是向前兼容的
    初始化函数 -> 

```
curl_easy_init() //非线程安全，应该确保只调用一次
```

    curl_version_info() 确认自己正在使用哪一版本的Curl
    使用 curl www.baidu.com --libcurl example.c 会生成一个example.c文件

# example.c

> curl == client URL

```
#include <curl/curl.h>

int main(int argc, char *argv[])
{
  CURLcode ret; // 处理存储curl的处理结果
  CURL *hnd;

  hnd = curl_easy_init(); // 创建curl会话，返回句柄hnd,失败返回NULL

  curl_easy_setopt(hnd, CURLOPT_URL, "http://example.com"); // 指定URL
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L); // 禁用进度条
  curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.45.0"); // 模拟User-Agent
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L); // 最大重定向次数
  curl_easy_setopt(hnd, CURLOPT_SSH_KNOWNHOSTS,
                   "/home/daniel/.ssh/known_hosts"); // 指向SSH连接的known hosts文件路径
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L); // 开启TCP活跃机制

  /* Here is a list of options the curl code used that cannot get
     generated as source easily. You may select to either not use them or
     implement them yourself.

  CURLOPT_WRITEDATA set to a objectpointer
  CURLOPT_WRITEFUNCTION set to a functionpointer
  CURLOPT_READDATA set to a objectpointer
  CURLOPT_READFUNCTION set to a functionpointer
  CURLOPT_SEEKDATA set to a objectpointer
  CURLOPT_SEEKFUNCTION set to a functionpointer
  CURLOPT_ERRORBUFFER set to a objectpointer
  CURLOPT_STDERR set to a objectpointer
  CURLOPT_HEADERFUNCTION set to a functionpointer
  CURLOPT_HEADERDATA set to a objectpointer

  */

  ret = curl_easy_perform(hnd); // 执行已配置的请求，结果存储到ret中

  curl_easy_cleanup(hnd); // 清理curl会话，释放资源
  hnd = NULL;

  return (int)ret;
}
/**** End of sample code ****/
```

# 默认

curl默认使用的GET请求方式，更改

**Post**

> 指定发送的内容

```
curl_easy_setopt(hnd, CURLOPT_POST, 1L); // 启动POST请求
/*使用键值对的方式*/
curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "field1=value1&field2=value2");
```

**Get**

> 指定发送内容

```
curl_easy_setopt(hnd, CURLOPT_URL, "http://example.com?value0=1&value1=2"); 
res = curl_easy_perform(curl);
 if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
 }
```

**自定义请求头**

```
struct curl_slist *headers = NULL;
headers = curl_slist_append(headers, "Content-Type: application/json");
curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
```

设置接收函数

```
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    strcat((char*)userdata, (char*)ptr);
    return size * nmemb;
}

char response[1024] = {0};  // 接收缓冲区

/*指定 回调函数 处理响应数据*/
curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
/*指定 接收缓冲区*/
curl_easy_setopt(hnd, CURLOPT_WRITEDATA, response);
```

---

```
// stdout 是用于正常输出的
// stderr 是用于错误输出的

```
