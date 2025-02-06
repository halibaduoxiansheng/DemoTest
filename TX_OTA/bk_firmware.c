#include "common.h"

//#define GP_FIRMWARE_MAGIC		 0x11223344
//#define GP_FIRMWARE_MAGIC		 0x22334455
#define GP_FIRMWARE_MAGIC		 0x66778899
#define FIRMWARE_OFFSET			sizeof(struct firmwareHeader)	

struct firmwareHeader{
	int32_t magic;	/*Firmware Magic*/
	uint8_t md5[32];/*firmware md5*/
	int32_t size;	/*firmware size*/
}__attribute__((__packed__));
int main(int argc, char **argv)
{
	uint8_t firmHeader[FIRMWARE_OFFSET] = {0};
	if(argc < 3){
		printf("Usage:%s filename md5\n", argv[0]);
		return 0;
	}
	struct firmwareHeader firm;
	struct stat st;

	memset(&firm, 0, sizeof(firm));
	firm.magic = GP_FIRMWARE_MAGIC; 
	strcpy(firm.md5, argv[2]);

	if(stat(argv[1], &st)){
		printf("stat %s error:%s\n",  argv[1],strerror(errno));
		return -1;
	}
	firm.size = st.st_size;
	printf("firm size is %d\n", firm.size);
	int ofd, nfd;	
	char filename[4096] = {0};

	sprintf(filename, "%s.firm", argv[1]);
	ofd = open(argv[1], O_RDONLY);
	if(ofd < 0){
		printf("open %s failed\n", argv[1]);
		return -1;
	}
	nfd = open(filename, 
		O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
	if(nfd < 0){
		printf("open %s failed\n", filename);
		return -1;
	}
	memcpy(firmHeader, &firm, sizeof(struct firmwareHeader));
	write(nfd, firmHeader, FIRMWARE_OFFSET);
	char buf[4096] = {0};
	int re;
	while(1){
		memset(buf, 0, 4096);
		re = read(ofd, buf, 4096);	
		if(re < 0){
			printf("read failed\n");
			return -1;
		}else if(re == 0){
			printf("read finish..\n");
			fsync(nfd);
			close(nfd);
			return 0;
		}
		printf("read %d bytes\n", re);
		write(nfd, buf, re);
	}

	return 0;	
}

