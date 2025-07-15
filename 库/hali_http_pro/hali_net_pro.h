#ifndef __HALI_NET_PRO_H__
#define __HALI_NET_PRO_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "sl_tls.h"

/**
 * WARNNING
 * 注意， 此程序的初衷并不是为了写一个可以使用的 UDP/TCP/HTTP/Websocket库出来
 * 而只是熟悉这些东西
 *
 * 同时 此库充分的给予了使用者自由度
 */

#define HALI_NET_USE_PSRAM		(1)

enum _NET_TRANSPORT_PROTOCOL {
	HALI_PROTO_NONE = 0,

	HALI_PROTO_TCP,
	HALI_PROTO_UDP,

	HALI_PROTO_MAX,
};


enum _NET_HTTP_METHODS {
	HALI_METHOD_NONE = 0,

	HALI_METHOD_GET,
	HALI_METHOD_POST,

	HALI_METHOD_PUT, // entirely update resources	->	Header + Body
	HALI_METHOD_DELETE, // delete -> Header
	HALI_METHOD_HEAD, // get response header -> Header
	HALI_METHOD_OPTIONS, // search server support whese methods	->	Header
	HALI_METHOD_PATCH, // partially(部分地) update resources	-> Header + Body

	HALI_METHOD_MAX,
};

enum _NET_MODES {
	HALI_MODE_NONE = 0,

	HALI_MODE_RECEIVE_ONLY, /* 只发 */
	HALI_MODE_SEND_ONLY,    /* 只收 */
	HALI_MODE_SEND_RECV,    /* 既发也收 */

	HALI_MODE_MAX,
};

enum _NET_FAMILYS {
	HALI_FAMILY_NONE = 0,

	HALI_FAMILY_IPV4,
	HALI_FAMILY_IPV6,

	HALI_FAMILY_MAX,
}

enum _NET_BLOCK_type {
	HALI_BLOCK_NONE = 0,

	HALI_BLOCK_USE,
	HALI_NO_BLOCK_USE,

	HALI_BLOCK_MAX,
};

enum _NET_APPLI_PRTOL { // Hypertext Transfer Protocol
	HALI_HTTP_APPLI_NONE = 0,

	HALI_HTTP_APPLI_1_0,
	HALI_HTTP_APPLI_1_1,

	HALI_HTTP_APPLI_MAX,
};

enum _NET_ACCEPT_type {
	HALI_ACCEPT_NONE = 0,

	HALI_ACCEPT_OMNIPOTENT,
	HALI_ACCEPT_TEXT_HTML,
	HALI_ACCEPT_JSON,
	HALI_ACCEPT_IMAGE,

	HALI_ACCEPT_MAX,
};

typedef int (*net_connect_callback)(struct hali_net_Info *info);
typedef int (*net_read_callback)(struct hali_net_Info *info);
typedef int (*net_write_callback)(struct hali_net_Info *info);
typedef void (*net_disconnect_callback)(struct hali_net_Info *info);	
typedef struct hali_net_Info {
	int inited;
	enum _TRANSPORT_PROTOCOL proto;
	enum _NET_MODES mode;
	enum _NET_FAMILYS family;
	enum _NET_BLOCK_type type;
	enum _NET_TRANS_PRTOL protol;
	enum _NET_METHODS method;
	enum _NET_ACCEPT_type accept;
	enum _NET_TRANSPORT_PROTOCOL request_method;

	char* src_ip; /* ipv4 or ipv6 malloc use*/
	char* dest_ip; /* ipv4 or ipv6 malloc use*/

	int send_port;
	int recv_port;

	int space_use_info;
	char* udp_tcp_send_buf; /* malloc use */
	char* udp_tcp_recv_buf; /* malloc use */
	int udp_tcp_send_buf_max_size; 
	int udp_tcp_recv_buf_max_size;
	int udp_tcp_real_send_size;  /* 实际发送内容的长度 */


	char *url; /* Users give this */ /* malloc use */
	char *host; /* malloc use */
	char *path; /* malloc use */
	int ssl; /* 1:https 0:http */

	int sockfd;
	int send_timeout; /* http/https unit:millisecond */
	int recv_timeout; /* http/https */

	char *send_header;
	char *send_body;

	char *recv_header;
	char *recv_body;

	int send_header_max_size;
	int send_body_max_size;

	int recv_header_max_size;
	int recv_body_max_size;

	MbedTLSSession *tls_session;

	net_read_callback iot_read;
	net_write_callback iot_write;
	net_connect_callback iot_connect;
	net_disconnect_callback iot_disconnect;
}hali_net_Info_t;



int hali_net_pro_init(hali_net_Info_t *info, enum _NET_TRANSPORT_PROTOCOL proto);
int hali_net_pro_deinit(hali_net_Info_t *info);

/*_______________    Tcp/Udp Public Module _______________*/
int hali_net_pro_set_mode(hali_net_Info_t *info, enum _NET_MODES mode);
int hali_net_pro_set_family(hali_net_Info_t *info, enum _NET_FAMILYS family);
int hali_net_pro_set_block_type(hali_net_Info_t *info, enum _NET_BLOCK_type type);
int hali_net_pro_set_send_port(hali_net_Info_t *info, int port);
int hali_net_pro_set_recv_port(hali_net_Info_t *info, int port);
int hali_net_pro_set_src_ip(hali_net_Info_t *info, char *ip); // args of ip with '\0' end string ( listen ip )
int hali_net_pro_set_dest_ip(hali_net_Info_t *info, char *ip); // args of ip with '\0' end string ( dest send ip )
int hali_net_pro_set_send_buf_size(hali_net_Info_t *info, char* store_address, int size); // not give store_address,then malloc
int hali_net_pro_set_recv_buf_size(hali_net_Info_t *info, char* store_address, int size); // not give store_address,then malloc
int hali_net_pro_set_send_content(hali_net_Info_t *info, char *content, int send_size); // TCP and UDP use this one

/*_______________    Tcp Module _______________*/
int hali_net_pro_tcp_connect(hali_net_Info_t *info);
int hali_net_pro_tcp_send(hali_net_Info_t *info);
int hali_net_pro_tcp_recv(hali_net_Info_t *info);

/*_______________    Udp Module _______________*/
int hali_net_pro_udp_send(hali_net_Info_t *info);
int hali_net_pro_udp_recv(hali_net_Info_t *info);



/*_______________    Http/Https Module _______________*/
int hali_net_pro_set_url(hali_net_Info_t *info, char *url);
int hali_net_pro_set_request_method(hali_net_Info_t *info, enum _NET_HTTP_METHODS method);
int hali_net_pro_set_send_timeout(hali_net_Info_t *info, int timeout); // millisecond
int hali_net_pro_set_recv_timeout(hali_net_Info_t *info, int timeout);
int hali_net_pro_set_application_protocol(hali_net_Info_t *info, enum _NET_APPLI_PRTOL prtol);
int hali_net_pro_set_accept_type(hali_net_Info_t *info, enum _NET_ACCEPT_type accept);


int hali_net_pro_connect(hali_net_Info_t *info);
int hali_net_pro_http_disconnect(hali_net_Info_t *info);

int hali_net_pro_set_send_allBuf_cache(hali_net_Info_t *info, char *header_buf,int header_buf_size, char *body_buf, int body_buf_size);
int hali_net_pro_set_recv_allBuf_cache(hali_net_Info_t *info, char *header_buf,int header_buf_size, char *body_buf, int body_buf_size);

int hali_header_add_Customize_field(hali_net_Info_t *info, char* content, int size);

int hali_net_pro_http_send(hali_net_Info_t *info); // 先设置 send header and body,then send
int hali_net_pro_http_recv(hali_net_Info_t *info); // 先 receive then get header and body TODO


int hali_net_pro_set_send_header(hali_net_Info_t *info, char *header_content, int size);
int hali_net_pro_set_send_body(hali_net_Info_t *info, char *body_content, int size);

int hali_net_pro_get_recv_header(hali_net_Info_t *info, char *header_content, int size);
int hali_net_pro_get_recv_body(hali_net_Info_t *info, char *body_content, int size);


#ifdef __cplusplus
}
#endif
#endif