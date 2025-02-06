#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>
#include <dirent.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
//#include <sys/inotify.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/un.h>
#include <net/if.h>
#include <sys/param.h>
#include <pthread.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <math.h>
#define MAXLINE		4096
#define SUCCESS		1
#define FAILURE		0
#ifndef INFTIM
#define INFTIM		-1
#endif


int readn(int fd, void *buf, size_t size);
int writen(int fd, void *buf, size_t size);
int readline(int fd, void *buf, size_t size);
void make_rand_number(int *num, int range);
int fd_noblck(int fd);
int tcp_conetct(const char *hostname, const char *prot);
int connect_unblock(int sockfd, struct sockaddr *saptr, int len, int nsec);
struct addrinfo * host_serv(const char *host, const char *serv, int family, int socktype);
ssize_t write_fd(int fd, void *ptr, size_t nbyte, int sendfd);

int fd_noblck(int fd)
{
	int flag;
	flag = fcntl(fd, F_GETFL, 0);
	if(flag == -1){
		perror("fcntl");
		return FAILURE;
	}
	if(fcntl(fd, F_SETFL, flag|O_NONBLOCK) != 0){
		perror("fcntl");
		return FAILURE;
	}
	
	return SUCCESS;
}

void make_rand_number(int *num, int range)
{
	srand((unsigned int)time(NULL));/*rand seed*/
	if(range > 0){
		*num = rand() % range;
	}else{
		*num = rand();
	}
	
	return;
}

int readn(int fd, void *buf, size_t size)
{
	size_t left, count;
	left = size;
	char *vbuf = buf;
	while(left > 0){
		count = read(fd, vbuf, left);
		if(count < 0){
			if(errno == EINTR){	
				continue;
			}else{
				return -1;
			}
		}else if(count == 0){
			break;
		}
		
		left -= count;
		vbuf += count;
	}

	return size - left;
}

int writen(int fd, void *buf, size_t size)
{
	size_t left, count;
	left = size;
	char *vbuf = buf;
	while(left > 0){
		count = write(fd, vbuf, left);
		if(count < 0){
			if(errno == EINTR){	
				continue;
			}else{
				printf("write failed\n");
				return -1;
			}
		}else if(count == 0){
			break;
		}
		
		left -= count;
		vbuf += count;
	}

	return size;
}
static int my_read(int fd, char *ptr)
{
	static int read_cnt = 0;
	static char *read_ptr;
	static char read_buf[MAXLINE];
	if(read_cnt <= 0){
		again:
		if((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0){
			if(errno == EINTR){
				goto again;
			}
			return -1;
		}else if(read_cnt == 0){
		//	printf("EOF\n");
			return 0;
		}
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;

	return 1;
}

int readline(int fd, void *buf, size_t size)
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = buf;
	
	for(n = 1; n < size; n++){
	again:
//		if((rc = read(fd, &c, 1)) == 1){
		if((rc = my_read(fd, &c)) == 1){
			*ptr++ = c;
			if(c == '\n'){
				break;
			}
		}else if(rc == 0){
			if(n == 1){
				printf("[%s]Read EOF\n", __func__);
				return 0;
			}else
				break;
		}else{
			if(errno == EINTR)
				goto again;
			return -1;
		}
	}

	*ptr = 0;
	return n;

}

int tcp_connect(const char *hostname, const char *port)
{
	struct addrinfo *res,*ressave, buf;
	int sockfd, n;

	memset(&buf, 0, sizeof(struct addrinfo));	
	buf.ai_family = AF_UNSPEC;
	buf.ai_socktype = SOCK_STREAM;

	if(getaddrinfo(hostname, port, &buf, &res) != 0){
	//if(getaddrinfo(NULL, port, &buf, &res) != 0){
		perror("getaddrinfo");
		return -1;
	}

	ressave = res;

	do{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd < 0){
			printf("socket failed\n");
			continue;
		}
		n = connect(sockfd, res->ai_addr, res->ai_addrlen);	
		if(n == 0){
			printf("connect successful\n");
			break;
		}

		close(sockfd);

	}while((res = res->ai_next) != NULL);
	
	if(res == NULL){
		freeaddrinfo(ressave);
		printf("Can't connect %s:%s\n", hostname, port);
		return -1;
	}
	freeaddrinfo(ressave);
	
	return sockfd;
		
}

int readable_timeout(int fd, int second)
{
	fd_set rset;
	struct timeval val;

	FD_ZERO(&rset);
	FD_SET(fd, &rset);

	val.tv_sec = second;
	val.tv_usec = 0;

	return (select(fd+1, &rset, NULL, NULL, &val));
}
int connect_unblock(int sockfd, struct sockaddr *saptr, int len, int nsec)
{
	int flag, res, tmp, error;
	fd_set rset, wset;
	struct timeval tm;
	
	/*set sockfd unblock*/	
	flag = fcntl(sockfd, F_GETFL, 0);
	if(flag < 0){
		perror("fcntl");
		return -1;
	}
	res = fcntl(sockfd, F_SETFL, flag|O_NONBLOCK);
	if(res < 0){
		perror("fcntl");
		return -1;
	}
	res = connect(sockfd, saptr, len);
	if(res < 0){
		if(errno == EINPROGRESS){
			printf("inprogress\n");
		}else{
			perror("connect");
			return -1;
		}
	}
	if(res == 0){
		printf("connect successful..\n");
		goto done;
	}
	FD_ZERO(&rset);
//	FD_ZERO(&wset);
	FD_SET(sockfd, &rset);
//	FD_SET(sockfd, &wset);
	tm.tv_sec = nsec;
	tm.tv_usec = 0;
	wset = rset;
	
	res = select(sockfd+1, &rset, &wset, NULL, nsec ? &tm:NULL);
	if(res == 0){
		printf("Time out\n");
		return -1;
	}
//	printf("select return %d\n", res);
	if(FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)){
		tmp = sizeof(error);
		res = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
		if(res < 0){
			perror("getsockopt");
			return -1;
		}
		if(error){
			printf("select connect falied..\n");
			return -1;
		}else{
			printf("select connect successful..\n");
			goto done;
		}
	}else{
		printf("select failed\n");
		return -1;
	}
	
done:
	res = fcntl(sockfd, F_SETFL, flag);
	if(res < 0){
		perror("fcntl");
		return -1;
	}
	
	return 0;
}
struct addrinfo * host_serv(const char *host, const char *serv, int family, int socktype)
{
	struct addrinfo tmp, *res;
	int n;
	
	tmp.ai_flags = AI_CANONNAME;
	tmp.ai_family = family;
	tmp.ai_socktype = socktype;
	
	n = getaddrinfo(host, serv, &tmp, &res);
	if(n < 0){
		printf("getaddrinfo failed\n");
		return NULL;
	}
	
	return res;
}

ssize_t write_fd(int fd, void *ptr, size_t nbyte, int sendfd)
{
	struct msghdr msg;
	struct iovec iov[1];
	struct cmsghdr *cmptr;

	union {
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	}control_un;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);
	cmptr = CMSG_FIRSTHDR(&msg);		
	cmptr->cmsg_len = CMSG_LEN(sizeof(int));
	cmptr->cmsg_level = SOL_SOCKET;
	cmptr->cmsg_type = SCM_RIGHTS;
	*((int *)CMSG_DATA(cmptr)) = sendfd;
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	
	iov[0].iov_base = ptr;
	iov[0].iov_len = nbyte;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	
	return(sendmsg(fd, &msg, 0));
}

ssize_t read_fd(int fd, void *ptr, size_t nbyte, int *recvfd)
{
	struct msghdr msg;
	struct iovec iov[1];
	
	union{
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	}control_un;
	struct cmsghdr *cmptr;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);

	msg.msg_name = NULL;
	msg.msg_namelen = 0;

	iov[0].iov_base = ptr;
	iov[0].iov_len = nbyte;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	
	if(recvmsg(fd, &msg, 0) <= 0){
		perror("recvmsg");
		return -1;
	}
	printf("Receive buf:%s\n", ptr);	
	if((cmptr = CMSG_FIRSTHDR(&msg)) != NULL &&
		cmptr->cmsg_len == CMSG_LEN(sizeof(int))){
		if(cmptr->cmsg_level != SOL_SOCKET){
			printf("cmsg_level is wrong\n");
			return -1;
		}
		if(cmptr->cmsg_type != SCM_RIGHTS){
			printf("cmsg_type is wrong\n");
			return -1;
		}
		*recvfd = *((int *)CMSG_DATA(cmptr));
	}else{
		*recvfd = -1;
	}

	return 0;

}
#if 0
void read_cwnd(int tcp_socket)
{
   struct tcp_info info;
   int length = sizeof(struct tcp_info);
   
   if ( getsockopt( tcp_socket, SOL_TCP, TCP_INFO, (void *)&info, (socklen_t *)&length ) == 0 ) {
      printf("%u %u %u %u %u %u %u %u %u %u %u %u\n",
            info.tcpi_snd_cwnd,
            info.tcpi_snd_ssthresh,
            info.tcpi_rcv_ssthresh,
            info.tcpi_rtt,
            info.tcpi_rttvar,
            info.tcpi_unacked,
            info.tcpi_sacked,
            info.tcpi_lost,
            info.tcpi_retrans,
            info.tcpi_fackets,
            info.tcpi_ca_state,
            info.tcpi_reordering
           );
   }
}
#endif
