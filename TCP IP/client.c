#include <stdio.h>
#include <winsock.h>//Ì×½Ó×ÖÐèÒª´øÉÏµÄÍ·ÎÄ¼þ
#include <string.h>
#pragma comment(lib,"ws2_32.lib") // ¼ÓÔØÌ×½Ó×Ö¿â
/**
 * #pragma comment(lib,"ws2_32.lib")
 * ×÷ÓÃ£º¸ÃÖ¸ÁîÓÃÓÚÖ¸¶¨ÒªÁ´½ÓµÄ¿âÎÄ¼þ¡£
 * ²ÎÊý£ºlibname.lib
 * ËµÃ÷£ºlibname.libÊÇ¿âÎÄ¼þµÄÃû×Ö£¬ËüÍ¨³£ÊÇÒ»¸ö.libÎÄ¼þ¡£
 * ×÷ÓÃ£ºÔÚ±àÒë¹ý³ÌÖÐ£¬±àÒëÆ÷»á×Ô¶¯ËÑË÷²¢Á´½ÓÖ¸¶¨µÄ¿âÎÄ¼þ¡£
 */

int main(void)
{
	/*    ¶¨Òå±äÁ¿            */
	char Sendbuf[100] = {0};   // ·¢ËÍÊý¾ÝµÄ»º³åÇø
	char Receivebuf[100] = {0}; // ½ÓÊÜÊý¾ÝµÄ»º³åÇø
	int SendLen;                // ·¢ËÍÊý¾ÝµÄ³¤¶È
	int ReceiveLen;             // ½ÓÊÜÊý¾ÝµÄ³¤¶È

	SOCKET socket_send;         // ¶¨ÒåÌ×½Ó×Ö
	SOCKADDR_IN Server_add;     // ·þÎñÆ÷µØÖ·½á¹¹

	WORD wVersionRequested;     // ×Ö
	WSADATA wsaData;            // ¿â°æ±¾ÐÅÏ¢½á¹¹
	int error;

	/*		³õÊ¼»¯Ì×½Ó×Ö			*/
	wVersionRequested = MAKEWORD(2, 2);
	error = WSAStartup(wVersionRequested, &wsaData);
	if (error != 0)
	{
		printf("¼ÓÔØÌ×½Ó×ÖÊ§°Ü\n");
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) // LOBYTE µÍ×Ö½Ú HIBYTE ¸ß×Ö½Ú
	{
		WSACleanup();
		return 0;
	}
	
	/*		ÉèÖÃ·þÎñÆ÷µØÖ·			*/
	Server_add.sin_family = AF_INET; // ±ØÐëÊÇAF_INET ±íÊ¾Ê¹ÓÃIPv4µØÖ·
	Server_add.sin_addr.S_un.S_addr = inet_addr("192.168.73.1"); // ipµØÖ·,Ëæ»ú¸Ä±ä ipµØÖ·ÒÑ×Ô¼ºÓµÓÐµÄÎªÀý
	Server_add.sin_port = htons(5000); // ¶Ë¿ÚºÅ

	/*			½øÐÐÁ¬½Ó·þÎñÆ÷		*/
	socket_send = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_send == INVALID_SOCKET)
	{
		printf("´´½¨Ì×½Ó×ÖÊ§°Ü\n");
		WSACleanup();
		return 0;
	}
	/**
	 * ¿Í»§¶Ë ·¢Æð µÚÒ»´ÎÎÕÊÖ Á¬½Ó·þÎñÆ÷
	 * ·þÎñÆ÷ ÏìÓ¦ µÚÒ»´ÎÎÕÊÖ Á¬½Ó³É¹¦
	 * ¿Í»§¶Ë ÏìÓ¦ µÚ¶þ´ÎÎÕÊÖ Á¬½Ó³É¹¦
	 * ¿Í»§¶Ë ·¢ËÍ Êý¾Ý
	 * ·þÎñÆ÷ ½ÓÊÕ Êý¾Ý
	 */
	if (connect(socket_send, (SOCKADDR*)&Server_add, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("Á¬½ÓÊ§°Ü\n");
		closesocket(socket_send);
		WSACleanup();
		return 0;
	}
	
	/*	½øÐÐÁÄÌì			*/
	printf("You are already onlice~\n");
	while (1)
	{
		printf("please enter message(Êä³öexitÍË³ö): ");
		scanf("%99s", Sendbuf);  // ÕâÀïÏÞ¶¨ÁË»º³åÇø´óÐ¡£¬·ÀÖ¹Òç³ö
		
		/*			ÍË³öÁÄÌì			*/
		if (strcmp(Sendbuf, "exit") == 0)
		{
		    break;
		}
		SendLen = send(socket_send, Sendbuf, strlen(Sendbuf), 0);
		if (SendLen == SOCKET_ERROR)
		{
			printf("·¢ËÍÊ§°Ü\n");
			break;
		}

		/*	½ÓÊÜÊý¾Ý¹ý³Ì			*/
		memset(Receivebuf, 0, sizeof(Receivebuf)); // Çå¿Õ»º³åÇø
		ReceiveLen = recv(socket_send, Receivebuf, sizeof(Receivebuf) - 1, 0);
		/**
		 * recvº¯Êý·µ»ØÖµ£º
		 * -1£º±íÊ¾½ÓÊÕÊ§°Ü
		 * 0£º±íÊ¾Á¬½Ó¶Ï¿ª
		 * >0£º±íÊ¾½ÓÊÕµ½µÄÊý¾Ý³¤¶È
		 */
		if (ReceiveLen <= 0)
		{
			printf("½ÓÊÜÊ§°Ü\n³ÌÐòÍË³ö\n");
			break;
		}
		else
		{
			printf("Server(he or she) say: %s\n", Receivebuf);
		}
	}

	/*	ÊÍ·ÅÌ×½Ó×Ö£¬¹Ø±Õ¶¯Ì¬¿â			*/
	closesocket(socket_send);
	WSACleanup();
	return 0;
}
