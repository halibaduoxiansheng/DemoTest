#include "hali_net_pro.h"


#define TAG "hali_net_pro"
#define HALI_NET_LIB_VER	"1.0"

enum HALI_LP_RETURN {
	HALI_RETURN_INVALID_ARGS = -10,
	HALI_RETURN_LOGICAL,
	HALI_RETURN_ERROR,
	HALI_RETURN_MALLOC_FAIL,

	HALI_RETURN_OK = 0,
	HALI_RETURN_MAX,
};

enum HALI_FLAG {
	HALI_FLAG_ZERO = 0,
	HALI_FLAG_ONE,

	HALI_FLAG_MAX,
};

enum Space_Use {
	HALI_SEND_BUF_USE_MALLOC = 0,
	HALI_RECV_BUF_USE_MALLOC,
	HALI_BLOCK_IS_NOBLOCK,
	HALI_SEND_HEAD_USE_MALLOC,
	HALI_SEND_BODY_USE_MALLOC,
	HALI_RECV_HEAD_USE_MALLOC,
	HALI_RECV_BODY_USE_MALLOC,

	HALI_USE_MALLOC_MAX,
};

enum HALI_SELECT_type {
	HALI_SELECT_READABLE = 0,
	HALI_SELECT_WRITABLE,

	HALI_SELECT_MAX, 
};

/*_______________    Debug Module _______________*/
// NOTE 分等级是一种，后续可能考虑设置为 LOGE, LOGW, LOGI, LOGD, LOGV
#define HALI_NET_DEBUG_FLAG		1
#if HALI_NET_DEBUG_FLAG /* NOTE 不建议关闭 HALI_NET_DEBUG_L0 */
 #define HALI_NET_DEBUG_L0 printf /* Level0 > Level1 */ 
 #define HALI_NET_DEBUG_L1 printf 
#else
 #define HALI_NET_DEBUG_L0 
 #define HALI_NET_DEBUG_L1 
#endif

// Tcp/Udp TIMES  ( 如果数据量太大，是分多次接收的，需要适当调大这个值 )
#define HALI_TCP_SEND_RETRY_MAX_TIMES 10
#define HALI_TCP_RECV_RETRY_MAX_TIMES 10
#define HALI_UDP_SEND_RETRY_MAX_TIMES 10
#define HALI_UDP_RECV_RETRY_MAX_TIMES 10
#define HALI_HTTP_RECV_RETRY_MAX_TIMES 10

// UDP Port Scope
#define _PORT_MIN 1024
#define _PORT_MAX 49151

// timeout
#define HALI_SELECT_SOCKET_TIMEOUT 3000
#define _UDP_SEND_TIMEOUT 10000 // millisecond
#define _UDP_RECV_TIMEOUT 10000
#define _TCP_SEND_TIMEOUT 10000
#define _TCP_RECV_TIMEOUT 10000 

// time
#define HALF_SECONDS 500
#define ONE_SECONDS	1000
#define FIVE_SECONDS 5000
#define TEN_SECONDS 10000
#define ONE_MINUTES 60000

// send and recv buf size
#define HTTP_S_SEND_HEADER_SIZE	1024
#define HTTP_S_RECV_HEADER_SIZE 4096
#define HTTP_S_SEND_BODY_SIZE 1024
#define HTTP_S_RECV_BODY_SIZE 4096

// url default header str
#define HALI_URL_DEFAULT_HTTP_HEAD "http://"
#define HALI_URL_DEFAULT_HTTPS_HEAD "https://"
#define HALI_URL_DEFAULT_WS_HEAD	"ws://"
#define HALI_URL_DEFAULT_WSS_HEAD	"wss://"
#define HALI_URL_DEFAULT_MQTT_HEAD "tcp://"
#define HALI_URL_DEFAULT_MQTTS_HEAD "ssl://"

// url default port
#define HALI_URL_DEFAULT_HTTP_PORT 80
#define HALI_URL_DEFAULT_HTTPS_PORT 443
#define HALI_URL_DEFAULT_WS_PORT 1883
#define HALI_URL_DEFAULT_WSS_PORT 8883
#define HALI_URL_DEFAULT_MQTT_PORT 1883
#define HALI_URL_DEFAULT_MQTTS_PORT 8883

static void hali_ver_print(void)
{
	HALI_NET_DEBUG_L0("\r\n*	*	*	*\r\n");
	HALI_NET-DEBUG_L0("welcome use hali_net_libs: %s\r\n", HALI_NET_LIB_VER);
	HALI_NET_DEBUG_L0("\r\n*	*	*	*\r\n");
}

/*_______________    Tools Module _______________*/
static inline int proto_check_validity(int value)
{
	if (value > HALI_PROTO_NONE && value < HALI_PROTO_MAX) {
		return HALI_FLAG_ONE; // legitimate
	} else {
		return HALI_FLAG_ZERO;
	}
}

static inline int port_check_validity(int port)
{
	if (port >= _PORT_MIN && port <= _PORT_MAX) {
		return HALI_FLAG_ONE; // legitimate
	} else {
		return HALI_FLAG_ZERO;
	}
}

static inline int mode_check_validity(int mode)
{
	if (mode > HALI_MODE_NONE && mode < HALI_MODE_MAX) {
		return HALI_FLAG_ONE; // legitimate
	} else {
		return HALI_FLAG_ZERO;
	}
}

static inline int family_check_validity(int family)
{
	if (family > HALI_FAMILY_NONE && family < HALI_FAMILY_MAX) {
		return HALI_FLAG_ONE; // legitimate
	} else {
		return HALI_FLAG_ZERO;
	}
}

static inline int blcok_check_validity(int type)
{
	if (type > HALI_BLOCK_NONE && type < HALI_BLOCK_MAX) {
		return HALI_FLAG_ONE;
	} else {
		return HALI_FLAG_ZERO;
	}
}

static inline int method_check_validity(int method)
{
	if (method > HALI_METHOD_NONE && method < HALI_METHOD_MAX) {
		return HALI_FLAG_ONE;
	} else {
		return HALI_FLAG_ZERO;
	}
}

static inline int prtol_check_validity(int prtol)
{
	if (prtol > HALI_HTTP_APPLI_NONE && prtol < HALI_HTTP_APPLI_MAX) {
		return HALI_FLAG_ONE;
	} else {
		return HALI_FLAG_ZERO;
	}
}

static inline int accept_check_validity(int accept_type) {
	if (accept_type > HALI_ACCEPT_NONE && accept_type < HALI_ACCEPT_MAX) {
		return HALI_FLAG_ONE;
	} else {
		return HALI_FLAG_ZERO;
	}
}

static inline int type_check_validity(int type) {
	if (type > HALI_URL_NONE && type < HALI_URL_MAX) {
		return HALI_FLAG_ONE;
	} else {
		return HALI_FLAG_ZERO;
	}
}

static inline void* hali_strdup(const char* data) 
{
	int len = strlen(data);
	char *temp =  hali_malloc(len + 1);
	memcpy(temp, data, len);
	temp[len] = '\0';
	return temp;
}

static inline void* hali_malloc(int size)
{
#if HALI_NET_USE_PSRAM
	return psram_malloc(size);
#else
	return malloc(size);
#endif
}

static inline void hali_free(void **data) 
{
	if (*data)
#if HALI_NET_USE_PSRAM
		psram_free(*data);
#else
		free(*data);
#endif
	*data = NULL;
}

static inline void hali_sleep(int milliseconds)
{
	rtos_delay_milliseconds(milliseconds);
}

static inline void hali_url_parse_safe_strdup(hali_net_Info_t *info)
{
	hali_free(&info->url);
	hali_free(&info->host);
	hali_free(&info->path);
}

static int hali_strtol(char *str_in, int base, int *value)
{
	char *endptr = NULL;
	long i_value = 0;

	i_value = strtol(str_in, &endptr, base);

	if (str_in == endptr) {
		HALI_NET_DEBUG_L0("%s -> no any num convert\r\n", TAG);
		return HALI_RETURN_ERROR;
	} else if (errno == ERANGE) {
		HALI_NET_DEBUG_L0("%s -> range is over\r\n", TAG);
		return HALI_RETURN_ERROR;
	} else {
		*value = (int)i_value;
		return HALI_RETURN_OK;
	}
}

/*_______________    Static Inside Code Module _______________*/
static int hali_net_just_body_method(hali_net_Info_t *info)
{
	if (info->method == HALI_METHOD_GET || info->method == HALI_METHOD_DELETE || info->method == HALI_METHOD_HEAD || info->method == HALI_METHOD_OPTIONS) {
		return HALI_RETURN_OK;
	}
	return HALI_RETURN_ERROR;
}

static int hali_net_header_add_body_method(hali_net_Info_t *info)
{
	if (info->method == HALI_METHOD_POST || info->method == HALI_METHOD_PUT || info->method == HALI_METHOD_PATCH) {
		return HALI_RETURN_OK;
	}
	return HALI_RETURN_ERROR;
}

static void hali_http_recv_info_memset(hali_net_Info_t *info)
{
	memset(info->recv_header, 0x0, info->recv_header_max_size);
	memset(info->recv_body, 0x0, info->recv_body_max_size);
}

static void hali_http_send_info_memset(hali_net_Info_t *info)
{
	memset(info->send_header, 0x0, info->send_header_max_size);
	memset(info->send_body, 0x0, info->send_body_max_size);
}

static int header_check_validity(char *str) 
{
	if (strcasestr(str, "Content-Length")) {
		HALI_NET_DEBUG_L0("%s -> custom request body length is not allow\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	if (strcasestr(info->send_header, str)) { // NOTE 防止不可预测行为的出现 不允许出现两个一样的字段
		HALI_NET_DEBUG_L0("%s -> not support same request header field(%s)\r\n", TAG, str);
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}

static int hali_http_send_header_add_tail_for_get(hali_net_Info_t *info)
{
	if (strcasestr(info->send_header, "\r\n\r\n")) {
		HALI_NET_DEBUG_L0("%s user already add \\r\\n\\r\\n ,please check it is correct\r\n", TAG);
	} else {
		hali_header_add_content_length_field(info);
	}

	return HALI_RETURN_OK;
}

static int hali_close(hali_net_Info_t *info)
{
	if (info->sockfd >= 0) {
		shutdown(info->sockfd, SHUT_RDWR);
		if (close(info->sockfd) == 0) {
			HALI_NET_DEBUG_L0("%s -> close socket success\r\n", TAG);
		}
	}
	info->sockfd = -1;
}

static int hali_http_send(hali_net_Info_t *info)
{
	hali_http_send_info_memset(info);
	if (hali_select(info, HALI_SELECT_WRITABLE) == HALI_RETURN_OK) {
		if (hali_net_just_body_method(info) == HALI_RETURN_OK) {
			hali_http_send_head(info);
		} else if (hali_net_header_add_body_method(info) == HALI_RETURN_OK) { 
			hali_http_send_head(info);
			hali_http_send_body(info);
		}
	} else {
		HALI_NET_DEBUG_L0("%s -> select func return can not write\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

}

static char *strcasestr(const char *haystack, const char *needle) {
	int i = 0;
    if (!haystack || !needle) return NULL;

    int needle_len = strlen(needle);
    if (needle_len == 0) return (char *)haystack;

    for (; *haystack; ++haystack) {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            for (i = 1; i < needle_len; ++i) { // 匹配开始，逐字符比较
                if (tolower((unsigned char)haystack[i]) != tolower((unsigned char)needle[i])) {
                    break;
                }
            }
            if (i == needle_len) {
                return (char *)haystack;
            }
        }
    }

    return NULL;
}

static void fill_random(void *buf, size_t len)
{
	unsigned char *buf_bytes = (uint8_t *)buf;
	while (len > 0) {
		uint32_t word = (uint32_t)rand();
		uint32_t to_copy = MIN(sizeof(word), len);
		memcpy(buf_bytes, &word, to_copy);
		buf_bytes += to_copy;
		len -= to_copy;
	}
}

static int hali_http_send_timeout_do(hali_net_Info_t *info)
{
	if (info->send_timeout && info->sockfd >= 0) {
		sock_set_send_timeout(info->sockfd, info->send_timeout);
	} else if (info->sockfd < 0) {
		HALI_NET_DEBUG_L0("%s -> sockfd is not craete\r\n", TAG);
		return HALI_RETURN_ERROR;
	} else {
		sock_set_send_timeout(info->sockfd, _TCP_SEND_TIMEOUT);
	}

	return HALI_RETURN_OK;
}

static int hali_http_recv_timeout_do(hali_net_Info_t *info)
{
	if (info->send_timeout && info->sockfd >= 0) {
		sock_set_send_timeout(info->sockfd, info->recv_timeout);
	} else if (info->sockfd < 0) {
		HALI_NET_DEBUG_L0("%s -> sockfd is not craete\r\n", TAG);
		return HALI_RETURN_ERROR;
	} else {
		sock_set_send_timeout(info->sockfd, _TCP_RECV_TIMEOUT);
	}

	return HALI_RETURN_OK;
}

static int hali_http_recv_http(hali_net_Info_t *info)
{
	char *p_0 = NULL, *p_1 = NULL;
	int header_buf_recv_len = 0, body_buf_recv_len = 0;
	int ret = 0, max_retry = HALI_HTTP_RECV_RETRY_MAX_TIMES;
	int content_length = 0;
	int use_buf_switch = 0;

	hali_http_recv_info_memset(info);

	do {
		if (use_buf_switch == 0) {
			if (info->ssl) {
				ret = mbedtls_ssl_read(&info->tls_session->ssl, info->recv_header + header_buf_recv_len, info->recv_header_max_size - header_buf_recv_len);
			} else {
				ret = recv(info->sockfd, (void*)info->recv_header + header_buf_recv_len, info->recv_header_max_size - header_buf_recv_len, 0); // 先拿body装一装全部试一试
			}
			if (ret > 0) {
				header_buf_recv_len += ret;
			} else if (ret == 0) {
				if (content_length == strlen(info->recv_body)) {
					return HALI_RETURN_OK;
				} else {
					HALI_NET_DEBUG_L0("%s -> Connection is Close\r\n", TAG);
					return HALI_RETURN_ERROR;
				}
			} else {
				if (info->ssl) {
					if (ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE) {
					    if (hali_select(info, HALI_SELECT_READABLE) == HALI_RETURN_OK) {
					        continue;
					    } else {
					        return HALI_RETURN_ERROR;
					    }
					} else {
					    HALI_NET_DEBUG_L0("%s -> mbedtls_ssl_read error: %d\r\n", TAG, ret);
					    return HALI_RETURN_ERROR;
					}
				} else {
					if (errno == EAGAIN || errno == EWOULDBLOCK) {
						if (hali_select(info, HALI_SELECT_READABLE) == HALI_RETURN_OK) {
							continue; // no-block state,no data now,but can wait or again
						} else if (errno == EINTR) {
							continue; // interrupt
						} else {
							return HALI_RETURN_ERROR;
						}
					}
				}
			}

			p_0 = strcasestr(info->recv_header, "Content-Length:");
			if (p_0 == NULL && content_length == 0) {
				continue;
			} else if (content_length == 0) {
				p_0 += strlen("Content-Length:");
				if (hali_strtol(p_0, 10, &content_length) == HALI_RETURN_OK) {
					// content_length = atoi(p_0); // atoi 函数 会自动跳过 前面的空格、制表符、回车、换行、垂直制表符、换页符等
				} else {
					return HALI_RETURN_ERROR;
				}
			}

			p_0 = strstr(info->recv_header, "\r\n\r\n"); // \r\n\r\n 放在 header_buf 中
			if (p_0 == NULL) {
				continue;
			} else {
				p_0 += strlen("\r\n\r\n");
				int header_bytes = p_0 - info->recv_header;
				if (header_buf_recv_len >= header_bytes) {
					memcpy(info->recv_body, info->recv_header + header_bytes, header_buf_recv_len - header_bytes);
					body_buf_recv_len += (header_buf_recv_len - header_bytes);
					memset(info->recv_header + header_bytes, 0, info->recv_header_max_size - header_bytes);
				}

				use_buf_switch = 1;
			}

		} else {
			if (info->ssl)
				ret = mbedtls_ssl_read(&info->tls_session->ssl, info->recv_body + body_buf_recv_len, info->recv_body_max_size - body_buf_recv_len);
			else
				ret = recv(info->sockfd, (void*)info->recv_body + body_buf_recv_len, info->recv_body_max_size - body_buf_recv_len, 0);
			if (ret > 0) {
				body_buf_recv_len += ret;
				if (body_buf_recv_len == content_length) {
					return HALI_RETURN_OK;
				}
			} else if (ret == 0) {
				HALI_NET_DEBUG_L0("%s -> Connect is Close\r\n", TAG);
				return HALI_RETURN_OK;
			} else {
				if (hali_select(info, HALI_SELECT_READABLE) == HALI_RETURN_OK) {
					continue;
				} else {
					if (ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE) {
					    if (hali_select(info, HALI_SELECT_READABLE) == HALI_RETURN_OK) {
					        continue;
					    } else {
					        return HALI_RETURN_ERROR;
					    }
					} else {
					    HALI_NET_DEBUG_L0("%s -> mbedtls_ssl_read error: %d\r\n", TAG, ret);
					    return HALI_RETURN_ERROR;
					}
				}
			}
		}
	} while(max_retry--);

	return HALI_RETURN_ERROR;
}

static int hali_http_recv(hali_net_Info_t *info)
{
	return hali_http_recv_http(info);
}

static int hali_header_add_first_field(hali_net_Info_t *info) // complete http[s]  first request line
{
	char method[5] = {0}, protol[9] = {0};

	if (info->method == HALI_HTTP_TRANS_1_0) { // method
		strncpy(method, "GET", strlen("GET"));
	} else if (info->protol == HALI_HTTP_TRANS_1_1) {
		strncpy(method, "POST", strlen("POST"));
	} else {
		return HALI_RETURN_ERROR;
	}

	if (info->protol == HALI_HTTP_TRANS_1_0) {
		strncpy(protol, "HTTP/1.0", strlen("HTTP/1.0"));
	} else if (info->protol == HALI_HTTP_TRANS_1_1) {
		strncpy(protol, "HTTP/1.1", strlen("HTTP/1.1"));
	} else {
		return HALI_RETURN_ERROR;
	}

	if (!info->send_header) {
		HALI_NET_DEBUG_L0("%s -> send header buf not set\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	memcpy(info->send_header, 0, info->send_header_max_size);
	snprintf(info->send_header, info->send_header_max_size, "%s %s %s\r\n",
				method, info->path, protol);
	if (info->protol == HALI_HTTP_TRANS_1_1) {
		int already_have_bytes = strlen(info->send_header);

		snprintf(info->send_header + already_have_bytes, info->send_header_max_size - already_have_bytes,
				 "%s\r\n",
				 "Connection: Keep-alive");
	}


	return HALI_RETURN_OK;
}

static int hali_header_add_host_field(hali_net_Info_t *info)
{
	if (info->send_header == NULL) {
		HALI_NET_DEBUG_L0("%s -> send header buf not set\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
	if (info->send_header && (!strcmp(info->send_header, "GET") || !strcmp(info->send_header, "POST"))) {
		return HALI_RETURN_ERROR;
	}
	int already_have_bytes = strlen(info->send_header);

	snprintf(info->send_header + already_have_bytes, info->send_header_max_size - already_have_bytes, 
				"Host: %s\r\n",
				info->host);

	return HALI_RETURN_OK;
}

static int hali_header_add_user_agent_field(hali_net_Info_t *info) // not must
{
	if (info->send_header == NULL) {
		HALI_NET_DEBUG_L0("%s -> send header buf not set\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
	if (info->send_header && (!strcmp(info->send_header, "GET") || !strcmp(info->send_header, "POST"))) {
		return HALI_RETURN_ERROR;
	}
	int already_have_bytes = strlen(info->send_header);

	snprintf(info->send_header + already_have_bytes, info->send_header_max_size - already_have_bytes, 
				"User-Agent: %s\r\n",
				"Mydevice/1.0");

	return HALI_RETURN_OK;
}

static int hali_header_add_Accept(hali_net_Info_t *info)
{
	if (info->send_header == NULL) {
		HALI_NET_DEBUG_L0("%s -> send header buf not set\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
	if (info->send_header && (!strcmp(info->send_header, "GET") || !strcmp(info->send_header, "POST"))) {
		return HALI_RETURN_ERROR;
	}
	int already_have_bytes = strlen(info->send_header);

	if (info->accept == HALI_ACCEPT_OMNIPOTENT) {
		snprintf(info->send_header + already_have_bytes, info->send_header_max_size - already_have_bytes, 
					"Accept: %s\r\n",
					"*/*"); // 万能统配
	} else if (info->accept == HALI_ACCEPT_TEXT_HTML) {
		snprintf(info->send_header + already_have_bytes, info->send_header_max_size - already_have_bytes, 
					"Accept: %s\r\n",
					"text/html"); 
	} else if (info->accept == HALI_ACCEPT_JSON) {
		snprintf(info->send_header + already_have_bytes, info->send_header_max_size - already_have_bytes, 
					"Accept: %s\r\n",
					"application/json"); 
	} else if (info->accept == HALI_ACCEPT_IMAGE) {
		snprintf(info->send_header + already_have_bytes, info->send_header_max_size - already_have_bytes, 
					"Accept: %s\r\n",
					"image/png, image/jpeg"); // image/png;1=0.9, image/jpeg;1=0.8 // q 值范围是 0.0 ~ 1.0 默认
	} else {
		HALI_NET_DEBUG_L0("%s -> no right accept type\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}

static int hali_header_add_content_length_field(hali_net_Info_t *info) // add "\r\n",post will more add Content-Length
{
	int already_write_bytes = strlen(info->send_header);
	if (info->method == HALI_METHOD_GET) {
		if (!strcasestr(info->send_header, "\r\n\r\n")) {
			snprintf(info->send_header + already_write_bytes, info->send_header_max_size - already_write_bytes,
						"%s", "\r\n");
		}
	} else if (info->method == HALI_METHOD_POST) {
		int content_length = strlen(info->send_body);
		
		snprintf(info->send_header + already_write_bytes, info->send_header_max_size - already_write_bytes,
					"Content-Length: %d\r\n\r\n", content_length);
	} else {
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}

static int hali_header_set_no_keepalive(hali_net_Info_t *info)
{
	if (info->send_header == NULL) {
		HALI_NET_DEBUG_L0("%s -> send header buf not set\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
	if (info->send_header && (!strcmp(info->send_header, "GET") || !strcmp(info->send_header, "POST"))) {
		return HALI_RETURN_ERROR;
	}
	int already_have_bytes = strlen(info->send_header);

	snprintf(info->send_header + already_have_bytes, info->send_header_max_size - already_have_bytes, 
					"Connection: %s\r\n",
					"close"); 

	return HALI_RETURN_OK;
}

static void hali_set_no_block(int fd)
{
	int flags = 1;// 非0值表示启动非堵塞模式 ( set no-block )
    if (lwip_ioctl(fd, FIONBIO, &flags) < 0) {
    	HALI_NET_DEBUG_L0("%s -> set no_block failed\r\n", TAG);
    	return HALI_RETURN_ERROR;
    }
}

/**
 * 默认阻塞 配合select 使用
 * 防止 send,recv,sendto,recvfrom 卡死
 *
 * 设置为非阻塞 配合 select 使用 ->  最优雅
 * 防止大量使用send，recv，sendto，recvfrom，浪费CPU资源
 */

static void hali_set_block(int fd)
{
	int flags = 0;// 非0值表示启动堵塞模式 ( set no-block )
    if (lwip_ioctl(fd, FIONBIO, &flags) < 0) {
    	HALI_NET_DEBUG_L0("%s -> set no_block failed\r\n", TAG);
    	return HALI_RETURN_ERROR;
    }
}

static void hali_destory(hali_net_Info_t *info) // TODO
{
	hali_free(&info->src_ip);
	hali_free(&info->dest_ip);
	hali_free(&info->udp_tcp_send_buf);
	hali_free(&info->udp_tcp_recv_buf);
	hali_free(&info->url);
	hali_free(&info->host);
	hali_free(&info->path);

	if (info->space_use_info & (1 << HALI_SEND_BUF_USE_MALLOC)) {
		hali_free(&info->udp_tcp_send_buf);
	}
	if (info->space_use_info & (1 << HALI_RECV_BUF_USE_MALLOC)) {
		hali_free(&info->udp_tcp_recv_buf);
	}
	if (info->space_use_info & (1 << HALI_SEND_HEAD_USE_MALLOC)) {
		hali_free(&info->send_header);
	}
	if (info->space_use_info & (1 << HALI_SEND_BODY_USE_MALLOC)) {
		hali_free(&info->send_body);
	}
	if (info->space_use_info & (1 << HALI_RECV_HEAD_USE_MALLOC)) {
		hali_free(&info->recv_header);
	}
	if (info->space_use_info & (1 << HALI_RECV_BODY_USE_MALLOC)) {
		hali_free(&info->recv_body);
	}

	hali_close(info);
}

static void hali_func_deinit(hali_net_Info_t *info)
{
	info->iot_read = NULL;
	info->iot_write = NULL;
	info-iot_connect = NULL;
	info->iot_disconnect = NULL;
}

static void hali_func_init(hali_net_Info_t *info)
{
	info->iot_connect = hali_net_pro_connect;
	info->iot_read = hali_net_pro_http_recv;
	info->iot_write = hali_net_pro_http_send;
}

static int hali_net_pro_ipv4_bind(hali_net_Info_t *info)
{
	// 需要 收 就需要有本地监听端口
	if (info->mode == HALI_MODE_RECEIVE_ONLY || info->mode == HALI_MODE_SEND_RECV) {
		struct sockaddr_in local;
		memset(&local, 0, sizeof(local));
		local.sin_family = AF_INET;
		local.sin_port = htons(info->recv_port); // Little Endian -> Big Endian
		if (info->src_ip) {
			if (inet_pton(AF_INET, info->src_ip, &local.sin_addr) != 1) {
				HALI_NET_DEBUG_L0("%s -> invalid Ipv4 address\r\n", TAG);
				return HALI_RETURN_ERROR;
			}
		} else {
			local.sin_addr.s_addr = htonl(INADDR_ANY); // listen any ip
		}

		if (bind(info->sockfd, (struct sockaddr*)&local, sizeof(local)) < 0) {
			HALI_NET_DEBUG_L0("%s -> udp bind failed\r\n", TAG);
			return HALI_RETURN_ERROR;
		}
	}

	return HALI_RETURN_OK;
}

static int hali_net_pro_ipv6_bind(hali_net_Info_t *info)
{
	// 需要 收 就需要有本地监听端口
	if (info->mode == HALI_MODE_RECEIVE_ONLY || info->mode == HALI_MODE_SEND_RECV) {
		struct sockaddr_in6 local;
		memset(&local, 0, sizeof(local));
		local.sin6_family = AF_INET6;
		local.sin6_port = htons(info->recv_port); // Little Endian -> Big Endian
		if (info->src_ip) {
			if (inet_pton(AF_INET6, info->src_ip, &local.sin6_addr) != 1) {
				HALI_NET_DEBUG_L0("%s -> invalid Ipv6 address\r\n", TAG);
				return HALI_RETURN_ERROR;
			}
		} else {
			local.sin6_addr = in6addr_any; // listen any ip
		}

		if (bind(info->sockfd, (struct sockaddr*)&local, sizeof(local)) < 0) {
			HALI_NET_DEBUG_L0("%s -> udp bind failed\r\n", TAG);
			return HALI_RETURN_ERROR;
		}
	}
	
	return HALI_RETURN_OK;
}

static void sock_set_recv_timeout(int sock_hdl, uint32_t millsec)
{	
	struct timeval tv;
	tv.tv_sec = millsec / 1000;  // second
    tv.tv_usec = (millsec % 1000) * 1000;  // millisecond
	
	if (setsockopt(sock_hdl, SOL_SOCKET, SO_RCVTIMEO, (const void*)&tv, sizeof(tv)) < 0) {
		HALI_NET_DEBUG_L0("setsockopt failed\n");
	}
}

static void sock_set_send_timeout(int sock_hdl, uint32_t millsec)
{
	struct timeval tv;
	tv.tv_sec = millsec / 1000;  // second
    tv.tv_usec = (millsec % 1000) * 1000;  // millisecond
	
	if (setsockopt(sock_hdl, SOL_SOCKET, SO_SNDTIMEO, (const void*)&tv, sizeof(tv)) < 0) {
		HALI_NET_DEBUG_L0("setsockopt failed\n");
	}
}

static int hali_socket(int domain, int type, int protocol)
{
	int fd = socket(domain, type, protocol);
	if (fd < 0) {
		return HALI_RETURN_ERROR;
	}

	if (type == SOCK_DGRAM) {
		sock_set_recv_timeout(fd, _UDP_RECV_TIMEOUT);
		sock_set_send_timeout(fd, _UDP_SEND_TIMEOUT);
	} else if (type == SOCK_STREAM) {
		sock_set_recv_timeout(fd, _TCP_RECV_TIMEOUT);
		sock_set_send_timeout(fd, _TCP_SEND_TIMEOUT);
	} else {
		return HALI_RETURN_ERROR;
	}

	return fd;
}

static int hali_net_pro_tcp_init(hali_net_Info_t *info) // TODO
{
	if (info->family == HALI_FAMILY_IPV4) {
		info->sockfd = hali_socket(AF_INET, SOCK_STREAM, 0);
		if (info->sockfd < 0) {
			return HALI_RETURN_ERROR;
		}
	} else if (info->family == HALI_FAMILY_IPV6) {
		info->sockfd = hali_socket(AF_INET6, SOCK_STREAM, 0);
		if (info->sockfd < 0) {
			return HALI_RETURN_ERROR;
		}
	} else {
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}

static int hali_net_pro_udp_init(hali_net_Info_t *info) // TODO
{
	if (!mode_check_validity(info->mode) || !port_check_validity(info->recv_port)) {
		HALI_NET_DEBUG_L0("%s -> not set mode or recv_port first\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}
	int ret = 0;

	if (info->family == HALI_FAMILY_IPV4) {
		info->sockfd = hali_socket(AF_INET, SOCK_DGRAM, 0);
		if (info->sockfd < 0) {
			return HALI_RETURN_ERROR;
		}
		ret = hali_net_pro_ipv4_bind(info);
		if (ret < 0) {
			return HALI_RETURN_ERROR;
		}

	} else if (info->family == HALI_FAMILY_IPV6) {
		info->sockfd = hali_socket(AF_INET6, SOCK_DGRAM, 0);
		if (info->sockfd < 0) {
			return HALI_RETURN_ERROR;
		}
		ret = hali_net_pro_ipv6_bind(info);
		if (ret < 0) {
			return HALI_RETURN_OK;
		}

	} else {
		return HALI_RETURN_ERROR;
	}

	if (info->space_use_info & (1 << HALI_BLOCK_IS_NOBLOCK)) {
		hali_set_no_block(info->sockfd);
	}

	return HALI_RETURN_OK;
}

static int hali_net_socket_init(hali_net_Info_t *info, int proto)
{
	if (proto == HALI_PROTO_TCP) {
		ret = hali_net_pro_tcp_init(info);
	} else if (proto == HALI_PROTO_UDP) {
		ret = hali_net_pro_udp_init(info);
	} else {
		HALI_NET_DEBUG_L0("%s -> not support transport protocol\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
}

static int hali_select(hali_net_Info_t *info, enum HALI_SELECT_type type) 
{
	int ret = 0;
	fd_set writefds, readfds;
    struct timeval timeout;

    timeout.tv_sec = HALI_SELECT_SOCKET_TIMEOUT / 1000;  // 超时时间
    timeout.tv_usec = (HALI_SELECT_SOCKET_TIMEOUT % 1000) * 1000;

	if (type == HALI_SELECT_READABLE) {
		FD_ZERO(&readfds);
    	FD_SET(info->sockfd, &readfds);
		ret = select(info->sockfd + 1, &readfds, NULL, NULL, &timeout);
	} else if (type == HALI_SELECT_WRITABLE) {
		FD_ZERO(&writefds);
    	FD_SET(info->sockfd, &writefds);
    	ret = select(info->sockfd + 1, NULL, &writefds, NULL, &timeout);
	} else {
		return HALI_RETURN_ERROR;
	}

    if (ret == -1) {
    	HALI_NET_DEBUG_L1("%s -> select failed\r\n", TAG);
    	return HALI_RETURN_ERROR;
    } else if (ret == 0) {
    	HALI_NET_DEBUG_L1("%s -> select timeout", TAG);
    	return HALI_RETURN_ERROR;
    } else {
    	return HALI_RETURN_OK;
    }
}

static int hali_send(hali_net_Info_t *info, int alread_send_bytes)
{
	return send(info->sockfd, (void*)info->udp_tcp_send_buf + alread_send_bytes, info->udp_tcp_real_send_size - alread_send_bytes, 0);
}

static int hali_recv(hali_net_Info_t *info, int already_recv_bytes)
{
	return recv(info->sockfd, (void*)info->udp_tcp_recv_buf + already_recv_bytes, info->udp_tcp_recv_buf_max_size - already_recv_bytes, 0);
}

static int hali_sendto(hali_net_Info_t *info, int already_send_bytes)
{
	struct sockaddr_in server_addr;
	struct sockaddr_in6 server_addr6;
	memset(&server_addr, 0, sizeof(server_addr));
	memset(&server_addr6, 0, sizeof(server_addr6));

	if (info->family == HALI_FAMILY_IPV4) {
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(info->send_port);
		if (info->dest_ip) {
			if (inet_pton(AF_INET, info->dest_ip, &server_addr.sin_addr) != 1) {
				HALI_NET_DEBUG_L0("%s -> invalid Ipv4 address\r\n", TAG);
				return HALI_RETURN_ERROR;
			}
		} else {
			HALI_NET_DEBUG_L0("%s -> should set dest ip first\r\n", TAG);
			return HALI_RETURN_LOGICAL;
		}

		return sendto(info->sockfd, (void*)info->udp_tcp_send_buf + already_send_bytes, info->udp_tcp_real_send_size - already_send_bytes, MSG_DONTWAIT,
						(struct sockaddr *)&server_addr, sizeof(server_addr));
	} else if (info->family == HALI_FAMILY_IPV6) {
		server_addr6.sin6_family = AF_INET6;
		server_addr6.sin6_port = htons(info->send_port);
		if (info->dest_ip) {
			if (inet_pton(AF_INET6, info->dest_ip, &server_addr6.sin6_addr) != 1) {
				HALI_NET_DEBUG_L0("%s -> invalid Ipv6 address\r\n", TAG);
				return HALI_RETURN_ERROR;
			}
		} else {
			HALI_NET_DEBUG_L0("%s -> should set dest ip first\r\n", TAG);
			return HALI_RETURN_LOGICAL;
		}

		return sendto(info->sockfd, (void*)info->udp_tcp_send_buf + already_send_bytes, info->udp_tcp_real_send_size - already_send_bytes, MSG_DONTWAIT,
						(struct sockaddr *)&server_addr6, sizeof(server_addr6));
	} else {
		HALI_NET_DEBUG_L0("%s -> not support family\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
}

static int hali_http_send_head(hali_net_Info_t *info)
{
	// TODO 目前设置是在设置请求体时,post的会在增加 Content-Length 时增加上 \r\n\r\n
	hali_http_send_header_add_tail_for_get(info);
	int header_size = strlen(info->send_header);
	if (info->ssl) {
		return ssl_txdat_sender(info->tls_session, header_size, info->send_header);
	} else {
		return send(info->sockfd, (void*)info->send_header, header_size, 0);
	}
}

static int hali_http_send_body(hali_net_Info_t *info)
{
	int body_size = strlen(info->send_body);
	if (info->ssl) {
		return ssl_txdat_sender(info->tls_session, body_size, info->send_body);
	} else {
		return send(info->sockfd, (void*)info->send_body, body_size, 0);
	}
}

static int hali_recvfrom(hali_net_Info_t *info)
{
	struct sockaddr_in cli_addr;
	struct sockaddr_in6 cli_addr6;
	socklen_t addr_len = sizeof(cli_addr);
	socklen_t addr6_len = sizeof(cli_addr6);
	char ipbuf[INET6_ADDRSTRLEN] = {0};
	int port = 0, ret = 0;

	if (info->family == HALI_FAMILY_IPV4) {
		ret = recvfrom(info->sockfd, info->udp_tcp_recv_buf, info->udp_tcp_recv_buf_max_size,
					 0, //  or MSG_DONTWAIT
					  (struct sockaddr *)&cli_addr, &addr_len);
		inet_ntop(AF_INET, &cli_addr.sin_addr, ipbuf, sizeof(ipbuf));
    	port = ntohs(cli_addr.sin_port);
	} else if (info->family == HALI_FAMILY_IPV6) {
		ret = recvfrom(info->sockfd, info->udp_tcp_recv_buf, info->udp_tcp_recv_buf_max_size, 
					 0, //  or MSG_DONTWAIT
					 (struct sockaddr *)&cli_addr6, &addr6_len);
		inet_ntop(AF_INET6, &cli_addr6.sin6_addr, ipbuf, sizeof(ipbuf));
    	port = ntohs(cli_addr6.sin6_port);
	} else {
		return HALI_RETURN_ERROR;
	}

	// NOTE 将收到的讯息的来源 打印 如果需要进一步操作，请自己完善
	HALI_NET_DEBUG_L0("%s -> [RECEFROM] is %s:%d\r\n", ipbuf, port);

	return ret;
}


// the '\r\n' between request header and request body take to send module add 
static int hali_net_pro_header_auto_for_get(hali_net_Info_t *info) // 
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	hali_header_add_first_field(info);
	hali_header_add_host_field(info);
	hali_header_add_user_agent_field(info);
	hali_header_add_Accept(info);

	return HALI_RETURN_OK;
}

static int hali_net_pro_header_auto_for_post(hali_net_Info_t *info) // TODO
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	
	hali_header_add_field_first(info);
	hali_header_add_host_field(info);
	hali_header_add_user_agent_field(info);
	hali_header_add_Accept(info);

	return HALI_RETURN_OK;
}

static void url_default_args_ensure(int type, char *url_head_str, char *url_head_s_str, int *url_default_port, int *url_default_s_port)
{
	if (type == HALI_HTTP_S_TYPE) {
		memcpy(url_head_str, HALI_URL_DEFAULT_HTTP_HEAD, strlen(HALI_URL_DEFAULT_HTTP_HEAD));
		memcpy(url_head_s_str, HALI_URL_DEFAULT_HTTPS_HEAD, strlen(HALI_URL_DEFAULT_HTTPS_HEAD));
		*url_default_port = HALI_URL_DEFAULT_HTTP_PORT;
		*url_default_s_port = HALI_URL_DEFAULT_HTTPS_PORT;
	} else if (type == HALI_WS_S_TYPE) {
		memcpy(url_head_str, HALI_URL_DEFAULT_WS_HEAD, strlen(HALI_URL_DEFAULT_WS_HEAD));
		memcpy(url_head_s_str, HALI_URL_DEFAULT_WSS_HEAD, strlen(HALI_URL_DEFAULT_WSS_HEAD));
		*url_default_port = HALI_URL_DEFAULT_WS_PORT;
		*url_default_s_port = HALI_URL_DEFAULT_WSS_PORT;
	} else if (type == HALI_MQTT_S_TYPE) {
		memcpy(url_head_str, HALI_URL_DEFAULT_MQTT_HEAD, strlen(HALI_URL_DEFAULT_MQTT_HEAD));
		memcpy(url_head_s_str, HALI_URL_DEFAULT_MQTTS_HEAD, strlen(HALI_URL_DEFAULT_MQTTS_HEAD));
		*url_default_port = HALI_URL_DEFAULT_MQTT_PORT;
		*url_default_s_port = HALI_URL_DEFAULT_MQTTS_PORT;
	}
}

int hali_connect(hali_net_Info_t *info)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	int ret = -1;
	
	if (info->family == HALI_FAMILY_IPV4) {
		struct sockaddr_in server_addr;
		memset(&server_addr, 0, sizeof(server_addr));

		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(info->send_port);
		if (info->dest_ip) {
			if (inet_pton(AF_INET, info->dest_ip, &server_addr.sin_addr) != 1) {
				HALI_NET_DEBUG_L0("%s -> invalid Ipv4 address\r\n", TAG);
				return HALI_RETURN_ERROR;
			}
		} else {
			HALI_NET_DEBUG_L0("%s -> should set dest ip first\r\n", TAG);
			return HALI_RETURN_LOGICAL;
		}

		ret = connect(info->sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
	} else if (info->family == HALI_FAMILY_IPV6) {
		struct sockaddr_in6 server_addr6;
		memset(&server_addr6, 0, sizeof(server_addr6));

		server_addr6.sin6_family = AF_INET6;
		server_addr6.sin6_port = htons(info->send_port);
		if (info->dest_ip) {
			if (inet_pton(AF_INET6, info->dest_ip, &server_addr6.sin6_addr) != 1) {
				HALI_NET_DEBUG_L0("%s -> invalid Ipv6 address\r\n", TAG);
				return HALI_RETURN_ERROR;
			}
		} else {
			HALI_NET_DEBUG_L0("%s -> should set dest ip first\r\n", TAG);
			return HALI_RETURN_LOGICAL;
		}

		ret = connect(info->sockfd, (const struct sockaddr *)&server_addr6, sizeof(server_addr6));
	} else {
		HALI_NET_DEBUG_L0("%s -> not support family\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	if (ret == 0) {
        HALI_NET_DEBUG_L0("%s -> Connecting to %s:%d\n", TAG, info->dest_ip, info->port);
		if (info->ssl) {
			info->tls_session = ssl_create(info->host, info->send_port);
			if (info->tls_session == NULL) {
				HALI_NET_DEBUG_L0("%s -> take ssl with https failed\r\n", TAG);
				return HALI_RETURN_ERROR;
			}
		}
	}

	if (ret == 0) {
		return HALI_RETURN_OK;
	} else {
		return HALI_RETURN_ERROR;
	}
}

/*_______________    ( TCP / UDP ) Interface Module _______________*/
int hali_net_pro_set_family(hali_net_Info_t *info, enum _NET_FAMILYS family) // must have set before init
{
	if (info == NULL || !family_check_validity(family)) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	info->family = family;

	return HALI_RETURN_OK;
}

int hali_net_pro_set_mode(hali_net_Info_t *info, enum _NET_MODES mode) // must hava set before init
{
	if (info == NULL || !mode_check_validity(mode)) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	info->mode = mode;

	return HALI_RETURN_OK;
}

int hali_net_pro_set_send_port(hali_net_Info_t *info, int port) 
{
	if (info == NULL || !port_check_validity(port)) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	info->send_port = port; 

	return HALI_RETURN_OK;
}

int hali_net_pro_set_block_type(hali_net_Info_t *info, enum _NET_BLOCK_type type)
{
	if (info == NULL || !blcok_check_validity(type)) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (info->sockfd >= 0) {
		HALI_NET_DEBUG_L1("%s -> sockfd is not create\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	info->type = type; 
	if (info->type == HALI_NO_BLOCK_USE) {
		info->space_use_info |= (1 << HALI_BLOCK_IS_NOBLOCK);
		hali_set_no_block(info->sockfd);
	} else if (info->type == HALI_BLOCK_USE) {
		info->space_use_info &= ~(1 << HALI_BLOCK_IS_NOBLOCK);
		hali_set_block(info->sockfd);
	} else {
		HALI_NET_DEBUG_L1("%s -> not support block type\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}

int hali_net_pro_set_recv_port(hali_net_Info_t *info, int port) // must have set before init
{
	if (info == NULL || !port_check_validity(port)) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	info->recv_port = port; 

	return HALI_RETURN_OK;
}

int hali_net_pro_set_src_ip(hali_net_Info_t *info, const char *ip) // if set should before init
{
	if (info == NULL || ip == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	info->src_ip = hali_strdup(ip);
	if (info->src_ip == NULL) {
		return HALI_RETURN_MALLOC_FAIL;
	}

	return HALI_RETURN_OK;
}

int hali_net_pro_set_dest_ip(hali_net_Info_t *info, const char *ip)
{
	if (info == NULL || ip == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	info->dest_ip = hali_strdup(ip);
	if (info->dest_ip == NULL) {
		return HALI_RETURN_MALLOC_FAIL;
	}

	return HALI_RETURN_OK;
}

int hali_net_pro_set_send_buf_size(hali_net_Info_t *info, char* store_address, int size)
{
	if (info == NULL || size < 0) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	info->udp_tcp_send_buf_max_size = size;
	if (store_address == NULL) {
		info->udp_tcp_send_buf = hali_strdup(size);
		if (info->udp_tcp_send_buf == NULL) {
			HALI_NET_DEBUG_L0("%s -> malloc failed\r\n", TAG);
			return HALI_RETURN_MALLOC_FAIL;
		}
		info->space_use_info |= (1 << HALI_SEND_BUF_USE_MALLOC);
	} else {
		info->udp_tcp_send_buf = store_address;
	}

	setsockopt(info->sockfd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));
	return HALI_RETURN_OK;
}

int hali_net_pro_set_recv_buf_size(hali_net_Info_t *info, char* store_address, int size)
{
	if (info == NULL || size < 0) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	info->udp_tcp_recv_buf_max_size = size;
	if (store_address == NULL) {
		info->udp_tcp_recv_buf = hali_strdup(size);
		if (info->udp_tcp_recv_buf == NULL) {
			HALI_NET_DEBUG_L0("%s -> malloc failed\r\n", TAG);
			return HALI_RETURN_MALLOC_FAIL;
		}
		info->space_use_info |= (1 << HALI_RECV_BUF_USE_MALLOC);
	} else {
		info->udp_tcp_recv_buf = store_address;
	}

	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
	return HALI_RETURN_OK;
}

int hali_net_pro_set_send_content(hali_net_Info_t *info, char *content, int send_size)
{
	if (info == NULL || content == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (!info->udp_tcp_send_buf) {
		HALI_NET_DEBUG_L0("%s -> please set send buf size first\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}
	if (send_size > info->udp_tcp_send_buf_max_size) {
		HALI_NET_DEBUG_L0("%s -> send buf size is not enough\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	memcpy(info->udp_tcp_send_buf, (const char *)content, send_size);
	info->udp_tcp_real_send_size = send_size; // NOTE 唯一设置位置

	return HALI_RETURN_OK;
}

int hali_net_pro_tcp_connect(hali_net_Info_t *info) // TODO
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (info->inited == 0) {
		HALI_NET_DEBUG_L1("%s -> have not init, can not send\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}

	if (info->sockfd < 0) {
		if (hali_net_socket_init(info, info->request_method) != HALI_RETURN_OK) {
			return HALI_RETURN_ERROR;
		}
	}

	int ret = hali_select(info, HALI_SELECT_WRITEBALE);
	if (ret > 0) {
		ret = hali_connect(info);
	}
	if (ret != 0) {
		return HALI_RETURN_ERROR;
	}

    return HALI_RETURN_OK;
}

int hali_net_pro_tcp_send(hali_net_Info_t *info) 
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (info->inited == 0) {
		HALI_NET_DEBUG_L1("%s -> have not init, can not send\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}
	if (info->sockfd < 0) {
		HALI_NET_DEBUG_L1("%s -> sockfd is not ok\r\n", TAG);
		return HALI_RETURN_ERROR;
	}
	int already_send_bytes = 0, ret = 0, retry_times = HALI_TCP_SEND_RETRY_MAX_TIMES;

	if (info->udp_tcp_real_send_size <= 0) {
		HALI_NET_DEBUG_L0("%s -> northing need to send ", TAG);
		return HALI_RETURN_ERROR;
	}

	do {
		ret = hali_select(info, HALI_SELECT_WRITEBALE);
		if (ret == HALI_RETURN_OK) {
			ret = hali_send(info, already_send_bytes);
			if (ret > 0) {
				already_send_bytes += ret;
			} else {
				if (errno == EAGAIN || errno == EWOULDBLOCK) {
					HALI_NET_DEBUG_L0("%s -> sendbuffer is full\r\n", TAG);
					hali_sleep(200); continue;
				} else if (errno == ENOBUFS) {
					HALI_NET_DEBUG_L0("%s -> no buffer space available\r\n", TAG);
				} else if (errno == ECONNREFUSED) {
					HALI_NET_DEBUG_L0("%s -> connection refused\r\n", TAG);
					return HALI_RETURN_ERROR;
				} else if (errno == EHOSTUNREACH) {
					HALI_NET_DEBUG_L0("%s -> host unreachable\r\n", TAG);
					return HALI_RETURN_ERROR;
				} else {
					HALI_NET_DEBUG_L0("%s -> \r\n", TAG);
					return HALI_RETURN_ERROR;
				}
			}
			if (already_send_bytes != info->udp_tcp_real_send_size) {
				continue;
			} else {
				return HALI_RETURN_OK;
			}
		} else {
			hali_sleep(HALF_SECONDS);
			continue;
		}
	} while(retry_times--);

	return HALI_RETURN_ERROR;
}

int hali_net_pro_tcp_recv(hali_net_Info_t *info) // TODO
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (info->inited == 0) {
		HALI_NET_DEBUG_L1("%s -> have not init, can not send\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}
	if (info->sockfd < 0) {
		HALI_NET_DEBUG_L1("%s -> sockfd is not ok\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	int ret = 0, retry_times = HALI_TCP_RECV_RETRY_MAX_TIMES, already_recv_bytes = 0;

	// NOTE 清空一下 后续靠 strlen 确认接收的长度
	memset(info->udp_tcp_recv_buf, 0, info->udp_tcp_recv_buf_max_size);

	do {
		ret = hali_select(info, HALI_SELECT_READABLE);
		if (ret == HALI_RETURN_OK) {
			ret == hali_recv(info, already_recv_bytes);
			if (ret < 0) {
				if (errno == EAGAIN || errno == EWOULDBLOCK) {
					HALI_NET_DEBUG_L1("%s -> no data read\r\n", TAG);
					return HALI_RETURN_OK;
				}
				continue;
			} else if (ret == 0) {
				HALI_NET_DEBUG_L0("%s -> the peer is close\r\n", TAG);
				return HALI_RETURN_ERROR;
			} else { 
				already_recv_bytes += ret;
			}
		} else {
			hali_sleep(HALF_SECONDS);
			continue;
		}
	} while(retry_times--);

	return HALI_RETURN_ERROR;
}

// NOTE 如果断开了 -> tcp: 在connect时会重新socket udp: 在send时会重新socket
int hali_net_pro_udp_send(hali_net_Info_t *info) // TODO
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (info->inited == 0) {
		HALI_NET_DEBUG_L1("%s -> have not init, can not send\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}
	if (info->sockfd < 0) {
		if (hali_net_socket_init(info, info->request_method) != HALI_RETURN_OK) {
			return HALI_RETURN_ERROR;
		}
	}

	int already_send_bytes = 0, ret = 0, retry_times = HALI_UDP_SEND_RETRY_MAX_TIMES;

	if (info->udp_tcp_real_send_size <= 0) {
		HALI_NET_DEBUG_L0("%s -> northing need to send ", TAG);
		return HALI_RETURN_ERROR;
	}

	do {
		ret = hali_select(info, HALI_SELECT_WRITEBALE);
		if (ret == HALI_RETURN_OK) {
			ret = hali_sendto(info, already_send_bytes);
			if (ret > 0) {
				already_send_bytes += ret;
			}
			if (already_send_bytes != info->udp_tcp_real_send_size) {
				continue;
			} else {
				return HALI_RETURN_OK;
			}
		} else {
			hali_sleep(HALF_SECONDS);
			continue;
		}
	} while(retry_times--);

	return HALI_RETURN_ERROR;
}

int hali_net_pro_udp_recv(hali_net_Info_t *info) // 接收一个UDP包
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (info->inited == 0) {
		HALI_NET_DEBUG_L1("%s -> have not init, can not send\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}
	if (info->sockfd < 0) {
		HALI_NET_DEBUG_L1("%s -> sockfd is not ok\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	int ret = 0, retry_times = HALI_UDP_RECV_RETRY_MAX_TIMES;

	do {
		ret = hali_select(info, HALI_SELECT_READABLE);
		if (ret == HALI_RETURN_OK) {
			ret == hali_recvfrom(info);
			if (ret < 0) {
				continue;
			} else { 
				return HALI_RETURN_OK; 
			}
		} else {
			hali_sleep(HALF_SECONDS);
			continue;
		}
	} while(retry_times--);
	
	return HALI_RETURN_OK;
}

/*_______________    Http/Https Module _______________*/
int hali_net_pro_set_url(hali_net_Info_t *info, char *url, enum _HALI_URL_TYPE type)
{
	if (info == NULL || url == NULL || type_check_validity(type) != HALI_FLAG_ONE) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS; 
	}

	int len = 0;
	char *p_left = NULL, *p_right = NULL;
	char url_head_str[8] = {0}, url_head_s_str = {0};
	int url_default_port , url_default_s_port;
	url_default_args_ensure(type, url_head_str, url_head_s_str, &url_default_port, &url_default_s_port);

	hali_url_parse_safe_strdup(info);

	info->url = hali_strdup(url);
	if (info->url == NULL) {
		return HALI_RETURN_MALLOC_FAIL;
	}
	p_left = p_right = info->url;

	if (strncmp(info->url, url_head_str, strlen(url_head_str)) == 0) {
		info->ssl = 0; p_left += strlen(url_head_str);
		p_right = p_left;
		p_right = strchr(p_left, ':');
		if (p_right == NULL) {
			info->send_port = url_default_port;
			p_right = strchr(p_left, '/');
			if (p_right == NULL) {
				return HALI_RETURN_INVALID_ARGS;
			}
			info->path = hali_strdup(p_right);
			*p_right = '\0';
			info->host = hali_strdup(p_left);
		} else {
			*p_right = '\0';
			info->host = hali_strdup(p_left);
			p_left = p_right + 1;
			p_right = strchr(p_left, '/');
			if (p_right == NULL) {
				return HALI_RETURN_INVALID_ARGS;
			}
			info->path = hali_strdup(p_right);
			*p_right = '\0';
			if (hali_strtol(p_left, 10, &info->send_port) == HALI_RETURN_OK) {
				// info->send_port = atoi(p_left);
			} else {
				return HALI_RETURN_ERROR;
			}
		}
	} else if (strncmp(info->url, url_head_s_str, strlen(url_head_s_str)) == 0) {
		info->ssl = 1; p_left += strlen(url_head_s_str);
		p_right = p_left;
		p_right = strchr(p_left, ':');
		if (p_right == NULL) {
			info->send_port = url_default_s_port;
			p_right = strchr(p_left, '/');
			if (p_right == NULL) {
				return HALI_RETURN_INVALID_ARGS;
			}
			info->path = hali_strdup(p_right);
			*p_right = '\0';
			info->host = hali_strdup(p_left);
		} else {
			*p_right = '\0';
			info->host = hali_strdup(p_left);
			p_left = p_right + 1;
			p_right = strchr(p_left, '/');
			if (p_right == NULL) {
				return HALI_RETURN_INVALID_ARGS;
			}
			info->path = hali_strdup(p_right);
			*p_right = '\0';
			if (hali_strtol(p_left, 10, &info->send_port) == HALI_RETURN_OK) {
				// info->send_port = atoi(p_left);
			} else {
				return HALI_RETURN_ERROR;
			}
		}
	} else {
		return HALI_RETURN_ERROR;
	}

	if (info->host == NULL || info->path == NULL) {
		return HALI_RETURN_MALLOC_FAIL;
	}

	return HALI_RETURN_OK;
}

int hali_net_pro_connect(hali_net_Info_t *info)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	int ret = 0;
    struct addrinfo hints, *res, *p;
    char ipstr[IP4ADDR_STRLEN_MAX] = {0};

    memset(&hints, 0, sizeof(hints));

    hints.ai_flags = AI_ADDRCONFIG; // 如果本地网络有IPV4地址，则优先解析
    hints.ai_family = AF_UNSPEC;;  //
    hints.ai_socktype = SOCK_STREAM;

    // 解析域名
    if ((ret = getaddrinfo(info->host, NULL, &hints, &res)) != 0) {
        HALI_NET_DEBUG_L1("%s -> [ERROR] Get host IP failed\r\n", TAG);
        return HALI_RETURN_ERROR;
    }

    // 遍历获取可用的 IP 地址
    for (p = res; p != NULL; p = p->ai_next) {
        struct sockaddr_in *server_addr = (struct sockaddr_in *)p->ai_addr;
        server_addr->sin_port = htons(info->port);  // 设置端口号

        // 转换 IP 地址
        inet_ntop(p->ai_family, &(server_addr->sin_addr), ipstr, sizeof(ipstr));
        HALI_NET_DEBUG_L1("%s -> Resolved IP: %s\n", TAG, ipstr);

        // 检查 socket 是否有效
        if (info->sockfd < 0) {
            HALI_NET_DEBUG_L1("%s -> Socket is invalid\n", TAG);
            freeaddrinfo(res);
            return HALI_RETURN_ERROR;
        }

        strncpy(info->dest_ip, ipstr, sizeof(info->dest_ip));

        ret = hali_connect(info);

        if (ret == 0) {
            HALI_NET_DEBUG_L1("%s -> Connected to %s:%d successfully\n", TAG, ipstr, info->port);

            // connect success，设置 (启动 linger，延迟 0 秒)
            struct linger ling = {1, 0}; // 立即关闭并丢弃未发送数据
            setsockopt(info->sockfd, SOL_SOCKET, SO_LINGER, (void*)&ling, sizeof(ling));

            break;  // 连接成功，跳出循环
        } else {
            HALI_NET_DEBUG_L1("%s -> Connection failed: %d, trying next...\n", TAG, ret);
            hali_sleep(100);
        }
    }

    freeaddrinfo(res);  // 释放资源

    if (ret != 0) {
        HALI_NET_DEBUG_L1("%s -> [ERROR] Failed to connect to any resolved IP\n", TAG);
        return ret;
    }

    return HALI_RETURN_OK;
}

int hali_net_pro_http_disconnect(hali_net_Info_t *info)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	if (info->ssl && info->tls_session) {
		mbedtls_client_close(info->tls_session);
		info->tls_session = NULL;
	} 

	hali_close(info);  // NOTE mbedtls_client_close TCP上层断开，但TCP并没有断开

	return HALI_RETURN_OK;
}

int hali_net_pro_set_send_allBuf_cache(hali_net_Info_t *info, char *header_buf,int header_buf_size, char *body_buf, int body_buf_size)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	if (header_buf == NULL) {
		if (info->space_use_info & (1 << HALI_SEND_HEAD_USE_MALLOC)) {
			hali_free(&info->send_header);
		}
		info->send_header = hali_strdup(HTTP_S_SEND_HEADER_SIZE);
		send_header_max_size = HTTP_S_SEND_HEADER_SIZE;
		if (info->send_header == NULL) {
			HALI_NET_DEBUG_L1("%s -> malloc failed\r\n", TAG);
			return HALI_RETURN_MALLOC_FAIL;
		}
		info->space_use_info |= (1 << HALI_SEND_HEAD_USE_MALLOC);
	} else if (header_buf_size > 0) {
		if (info->space_use_info & (1 << HALI_SEND_HEAD_USE_MALLOC)) {
			hali_free(&info->send_header);
			info->space_use_info &= ~(1 << HALI_SEND_HEAD_USE_MALLOC);
		}
		info->send_header = header_buf;
		info->send_header_max_size = header_buf_size;
		memset(info->send_header, 0, info->send_header_max_size);
	} else {
		HALI_NET_DEBUG_L1("%s -> args is valid\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	if (body_buf == NULL) {
		if (info->space_use_info & (1 << HALI_SEND_BODY_USE_MALLOC)) {
			hali_free(&info->send_body);
		}
		info->send_body = hali_strdup(HTTP_S_SEND_BODY_SIZE);
		info->send_body_max_size = HTTP_S_SEND_BODY_SIZE;
		if (info->send_body == NULL) {
			HALI_NET_DEBUG_L1("%s -> malloc failed\r\n", TAG);
			return HALI_RETURN_MALLOC_FAIL;
		}
		info->space_use_info |= (1 << HALI_SEND_BODY_USE_MALLOC);
	} else if (body_buf_size > 0) {
		if (info->space_use_info & (1 << HALI_SEND_BODY_USE_MALLOC)) {
			hali_free(&info->send_body);
			info->space_use_info &= ~(1 << HALI_SEND_BODY_USE_MALLOC);
		}
		info->send_body = body_buf;
		info->send_body_max_size = body_buf_size;
	} else {
		HALI_NET_DEBUG_L1("%s -> args is valid\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}

// NOTE 自定义 使用空间 需要是永久生效的
int hali_net_pro_set_recv_allBuf_cache(hali_net_Info_t *info, char *header_buf,int header_buf_size, char *body_buf, int body_buf_size)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	if (header_buf == NULL) {
		if (info->space_use_info & (1 << HALI_RECV_HEAD_USE_MALLOC) {
			hali_free(&info->recv_header);
		}
		info->recv_header = hali_strdup(HTTP_S_RECV_HEADER_SIZE);
		info->recv_header_max_size = HTTP_S_RECV_HEADER_SIZE;
		if (info->recv_header == NULL) {
			HALI_NET_DEBUG_L1("%s -> malloc failed\r\n", TAG);
			return HALI_RETURN_MALLOC_FAIL;
		}
		info->space_use_info |= (1 << HALI_RECV_HEAD_USE_MALLOC);
	} else if (header_buf_size > 0) {
		if (info->space_use_info & (1 << HALI_RECV_HEAD_USE_MALLOC)) {
			hali_free(&info->recv_header);
			info->space_use_info &= ~(1 << HALI_RECV_HEAD_USE_MALLOC);
		}
		info->recv_header = header_buf;
		info->recv_header_max_size = header_buf_size;
	} else {
		HALI_NET_DEBUG_L1("%s -> args is valid(meet header_buf_size <= 0)\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	if (body_buf == NULL) {
		if (info->space_use_info & (1 << HALI_RECV_BODY_USE_MALLOC) {
			hali_free(&info->recv_body);
		}
		info->recv_body = hali_strdup(HTTP_S_RECV_BODY_SIZE);
		info->recv_body_max_size = HTTP_S_RECV_BODY_SIZE;
		if (info->recv_body == NULL) {
			HALI_NET_DEBUG_L1("%s -> malloc failed\r\n", TAG);
			return HALI_RETURN_MALLOC_FAIL;
		}
		info->space_use_info |= (1 << HALI_RECV_BODY_USE_MALLOC);
	} else if (body_buf_size > 0) {
		if (info->space_use_info & (1 << HALI_RECV_BODY_USE_MALLOC)) {
			hali_free(&info->recv_body);
			info->space_use_info &= ~(1 << HALI_RECV_BODY_USE_MALLOC);
		}
		info->recv_body = body_buf;
		info->recv_body_max_size = body_buf_size;
	} else {
		HALI_NET_DEBUG_L1("%s -> args is valid(meet body_buf_size <= 0)\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}

// NOTE "\r\n\r\n" 的封装是在send函数中做的 所以这里添加不需要考虑这个问题
int hali_header_add_Customize_field(hali_net_Info_t *info, char* content_key, char* content_value)
{
	if (info == NULL || content_key == NULL || content_value == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	int already_have_bytes = 0;
	char *p_get = strcasestr(info->send_header, "GET");
	char *p_post = strcasestr(info->send_header, "POST");
	if (p_get == NULL && p_post == NULL) {
		HALI_NET_DEBUG_L1("%s -> please add request line first\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}

	if (header_check_validity(content_key) != HALI_RETURN_OK) {
		return HALI_RETURN_ERROR;
	}

	already_have_bytes = strlen(info->send_header);
	snprintf(info->send_header + already_have_bytes, info->send_header_max_size - already_have_bytes, 
				"%s: %s\r\n",
				content_key, content_value);

	return HALI_RETURN_OK;
}

int hali_net_pro_http_send(hali_net_Info_t *info)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	if (hali_http_send_timeout_do(info) != HALI_RETURN_OK) {
		return HALI_RETURN_ERROR;
	}

	if (hali_net_just_body_method(info) == HALI_RETURN_OK) {
		if (!info->send_header) {
			return HALI_RETURN_ERROR;
		} else {
			hali_http_send(info);
		}
	} else if (hali_net_header_add_body_method(info) == HALI_RETURN_OK) {
		if (!info->send_header || !info->send_body) {
			return HALI_RETURN_ERROR;
		} else {
			hali_http_send(info);
		}
	} else {
		HALI_NET_DEBUG_L0("%s -> not support method(%d)\r\n", TAG, info->method);
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}


int hali_net_pro_http_recv(hali_net_Info_t *info)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	if (hali_http_recv_timeout_do(info) != HALI_RETURN_OK) {
		return HALI_RETURN_ERROR;
	}
	
	if (hali_http_recv(info) != HALI_RETURN_OK) {
		return HALI_RETURN_ERROR;
	}
	
	return HALI_RETURN_OK;
}

int hali_net_pro_get_recv_header(hali_net_Info_t *info, char *header_content, int size)
{
	if (info == NULL || header_content == NULL || info->recv_header_max_size < size) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	strncpy(header_content, info->recv_header, info->recv_header_max_size);

	return HALI_RETURN_OK;
}

int hali_net_pro_get_recv_body(hali_net_Info_t *info, char *body_content, int size)
{
	if (info == NULL || body_content == NULL || info->recv_body_max_size < size) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	strncpy(body_content, info->recv_body, info->recv_body_max_size);

	return HALI_RETURN_OK;
}

int hali_net_pro_set_send_header(hali_net_Info_t *info, char *header_content, int size)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	} 

	if (header_content && size > 0) {
		if (info->send_header && size <= info->send_header_max_size) {
			memcpy(info->send_header, (const void*)header_content, size);
		} else {
			HALI_NET_DEBUG_L1("%s -> please check set args\r\n", TAG);
			return HALI_RETURN_INVALID_ARGS;
		}
	} else { // NOTE use define by oneself
		if (info->method == HALI_METHOD_GET) {
			hali_net_pro_header_auto_for_get(info);
		} else if (info->method == HALI_METHOD_POST) {
			hali_net_pro_header_auto_for_post(info);
		} else {
			HALI_NET_DEBUG_L0("%s -> not support method now\r\n", TAG);
			return HALI_RETURN_ERROR;
		}
	}

	return HALI_RETURN_OK;
}

int hali_net_pro_set_send_body(hali_net_Info_t *info, char *body_content, int size)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	if (info->method == HALI_METHOD_GET) {
		HALI_NET_DEBUG_L0("%s -> get method not need to set body\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	if (body_content == NULL) { // 目前只考虑 GET and POST
		if (info->method != HALI_METHOD_GET) {
			HALI_NET_DEBUG_L0("%s -> do you forget add body\r\n", TAG);
			return HALI_RETURN_ERROR;
		} else {
			hali_header_add_content_length_field(info);
		}
	} else if (size > info->send_body_max_size) {
		HALI_NET_DEBUG_L0("%s -> args of size is too big\r\n", TAG);
		return HALI_RETURN_ERROR;
	} else {
		memset(info->send_body, 0, info->send_body_max_size);
		strncpy(info->send_body, body_content, size);
		hali_header_add_content_length_field(info);
	}

	return HALI_RETURN_OK;
}



int hali_net_pro_set_request_method(hali_net_Info_t *info, enum _NET_HTTP_METHODS method)
{
	if (info == NULL || !method_check_validity(method)) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	info->method = method;

	return HALI_RETURN_OK;
}

int hali_net_pro_set_send_timeout(hali_net_Info_t *info, int timeout)
{
	if (info == NULL || timeout < 0) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	info->send_timeout = timeout;

	return HALI_RETURN_OK;
}

int hali_net_pro_set_recv_timeout(hali_net_Info_t *info, int timeout)
{
	if (info == NULL || timeout < 0) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	info->recv_timeout = timeout;

	return HALI_RETURN_OK;
}

int hali_net_pro_set_application_protocol(hali_net_Info_t *info, enum _NET_APPLI_PRTOL prtol)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	if (!prtol_check_validity(prtol)) {
		HALI_NET_DEBUG_L1("%s -> prtol is not right\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	info->protol = prtol;

	return HALI_RETURN_OK;
}

int hali_net_pro_set_accept_type(hali_net_Info_t *info, enum _NET_ACCEPT_type accept)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}

	if (!accept_check_validity(accept)) {
		HALI_NET_DEBUG_L1("%s -> accept type is not right\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	info->accept = accept;

	return HALI_RETURN_ERROR;
}

static int hali_net_pro_parse_websocket_establish_package(hali_net_Info_t *info, unsigned char *client_key)
{
	char *p_left = NULL, p_right = NULL;

	p_left = strcasestr(info->recv_header, "Sec-WebSocket-Accept");
	if (p_left == NULL) {
		HALI_NET_DEBUG_L1("%s -> package is not complete\r\n", TAG);
		goto _err;
	} else {
		p_right = strcasestr(p_left, "\r\n");
		if (p_right == NULL) {
			HALI_NET_DEBUG_L1("%s -> package is not complete\r\n", TAG);
			goto _err;
		} else {
			p_right = '\0';
			char *server_key = hali_strdup(p_left + (p_right - p_left));

			size_t outlen;
			unsigned char expected_server_sha1[20] = {0};
			unsigned char expected_server_key[33] = {0};

			// NOTE 1.先对本地的key SHA-1 哈希计算 2.然后进行Base64编码
			mbedtls_sha1_ret(client_key, strlen(client_key), expected_server_sha1);
			mbedtls_base64_encode(expected_server_key, sizeof(expected_server_key),  &outlen, expected_server_sha1, sizeof(expected_server_sha1));

			if (strmcp(expected_server_key, server_key) != 0) {
				HALI_NET_DEBUG_L0("%s -> server key is error\r\n", TAG);
				goto _err;
			}
		}
	}

	if (server_key) {
		hali_free(server_key);
	}
	return HALI_RETURN_OK;
_err:
	if (server_key) {
		hali_free(server_key);
	}
	return HALI_RETURN_ERROR;
}

/*_______________    Init/Deinit Module _______________*/

/**
 * do 创建套接字、设置默认的发送、接收超时,设置 info-> iot_connect、iot_read、iot_write
 * need info->family
 */
int hali_net_pro_init(hali_net_Info_t *info, const enum _NET_TRANSPORT_PROTOCOL proto)
{
	hali_ver_print();
	if (info == NULL || !proto_check_validity(proto)) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (info->inited == 1) {
		HALI_NET_DEBUG_L1("%s -> already init\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}
	int ret = -1;

	info->sockfd = -1;

	ret = hali_net_socket_init(info, proto);

	hali_func_init(info);

	if (ret != HALI_RETURN_OK) {
		return HALI_RETURN_ERROR;
	}
	info->request_method = proto;

	info->inited = 1;

	return HALI_RETURN_OK;
}

int hali_net_pro_deinit(hali_net_Info_t *info)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	if (info->inited == 0) {
		HALI_NET_DEBUG_L0("%s -> have not inited\r\n", TAG);
		return HALI_RETURN_LOGICAL;
	}

	hali_destory(info);
	hali_func_deinit(info);

	hali_net_pro_http_disconnect(info);

	memset(info, 0, sizeof(hali_net_Info_t));
	return HALI_RETURN_OK;
}

int Websocket_establish(hali_net_Info_t *info)
{
	if (info == NULL) {
		HALI_NET_DEBUG_L0("%s -> args is invalid\r\n", TAG);
		return HALI_RETURN_INVALID_ARGS;
	}
	int ret = 0;
	unsigned char random_key[16]; // len must >= 16
	unsigned char client_key[28] = {0};
	size_t outlen;

	fill_random(random_key, sizeof(random_key));

	hali_net_pro_set_request_method(info, HALI_METHOD_GET);

	if (hali_connect(info) != HALI_RETURN_OK) {
		HALI_NET_DEBUG_L0("connect failed,can not establish websocket\r\n");
		return HALI_RETURN_ERROR;
	}

	// NOTE 此处使用默认随机 客户端握手本地密钥
	mbedtls_base64_encode(client_key, sizeof(client_key), &outlen, random_key, sizeof(random_key));

	memset(info->send_header, 0, info->send_header_max_size);

	os_snprintf(info->send_header, info->send_header_max_size, 
					"GET %s HTTP/1.1\r\n"
					"Upgrade: websocket\r\n"
					"Connection: Upgrade\r\n"
					"Host: %s\r\n"
					"Origin: http://%s\r\n"
					"Sec-Websocket-Key: %s\r\n"
					"Sec-WebSocket-Version: 13\r\n",
					info->path, info->host, info->url, client_key
					);

	if (hali_net_pro_http_send(info) != HALI_RETURN_OK) {
		HALI_NET_DEBUG_L0("%s -> establish websocket send failed\r\n\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	if (hali_net_pro_http_recv(info) != HALI_RETURN_OK) {
		HALI_NET_DEBUG_L0("%s -> establish websocket no receive\r\n\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	if (hali_net_pro_parse_websocket_establish_package(info, client_key) != HALI_RETURN_OK) {
		HALI_NET_DEBUG_L0("%s -> key check error\r\n", TAG);
		return HALI_RETURN_ERROR;
	}

	return HALI_RETURN_OK;
}