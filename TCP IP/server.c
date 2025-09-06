#include <stdio.h>
#include <winsock.h> // ÒýÈëwinsockÍ·ÎÄ¼þ£¬ÕâÀïÒª×¢ÒâÁËÕâ¸öÐÂÍ·ÎÄ¼þ
#include <string.h>
/**
 * ÏÈÔËÐÐ·þÎñÆ÷¶Ë£¬ÔÙÔËÐÐ¿Í»§¶Ë£¬È»ºó¾Í¿ÉÒÔ½øÐÐÍ¨ÐÅÁË
 * .\server.exe
 * .\client.exe
 */

int main(void)
{
    /*--------------------------------*/
    /*---------¶¨Òå±äÁ¿---------------*/ // ¿´µ½ADD¾ÍµÃÏëµ½µØÖ·£¬µØÖ·Ó¢ÎÄÊÇaddress£¬ÓÐÊ±ºò»¹»á¼ÓÉÏÕâ¸ör£¬³ÉÎªaddr
    /*--------------------------------*/
    char Sendbuf[100] = {0};   // ·¢ËÍÊý¾ÝµÄ»º³åÇø
    char Receivebuf[100] = {0}; // ½ÓÊÜÊý¾ÝµÄ»º³åÇø
    int SendLen;                // ·¢ËÍÊý¾ÝµÄ³¤¶È
    int ReceiveLen;             // ½ÓÊÜÊý¾ÝµÄ³¤¶È
    int Length;                 // ±íÊ¾SOCKADDRµÄ´óÐ¡

    SOCKET socket_server;       // ¶¨Òå·þÎñÆ÷Ì×½Ó×Ö
    SOCKET socket_receive;      // ¶¨ÒåÓÃÓÚÁ¬½ÓÌ×½Ó×Ö Ò²¾ÍÊÇacceptºóµÄ·µ»ØÖµ¡ªÐÂµÄÌ×½Ó×Ö

    SOCKADDR_IN Server_add;     // ·þÎñÆ÷µØÖ·ÐÅÏ¢½á¹¹
    SOCKADDR_IN Client_add;     // ¿Í»§¶ËµØÖ·ÐÅÏ¢½á¹¹

    WORD wVersionRequested;     /* ×Ö£¨word£©£ºunsigned short */
    WSADATA wsaData;            // ¿â°æ±¾ÐÅÏ¢½á¹¹
    int error;                  // ±íÊ¾´íÎó

    /*---------------------------------*/
    /*-------³õÊ¼»¯Ì×½Ó×Ö--------------*/
    /*---------------------------------*/
    // ¶¨Òå°æ±¾ÀàÐÍ¡£½«Á½¸ö×Ö½Ú×é³ÉÒ»¸ö×Ö£¬Ç°ÃæÊÇµÍ×Ö½Ú£¬ºóÃæÊÇ¸ß×Ö½Ú
    wVersionRequested = MAKEWORD(2, 2);
    /* ¼ÓÔØÌ×½Ó×Ö¿â£¬³õÊ¼»¯Ws2_32.dll¶¯Ì¬Á´½Ó¿â */
	/**
	 * ws2_32.dllÊÇWindows SocketsÓ¦ÓÃ³ÌÐò½Ó¿Ú£¬ÓÃÓÚÖ§³ÖInternetºÍÍøÂçÓ¦ÓÃ³ÌÐò¡£
	 * ËüÌá¹©ÁËÒ»×éº¯Êý£¬ÓÃÓÚ´´½¨ºÍÅäÖÃÌ×½Ó×Ö£¬·¢ËÍºÍ½ÓÊÕÊý¾Ý£¬ÒÔ¼°¹ÜÀíÍøÂçÁ¬½Ó¡£
	 * Ëü»¹Ìá¹©ÁËÒ»×é³£Á¿£¬ÓÃÓÚ¶¨ÒåÌ×½Ó×ÖµÄ×´Ì¬¡¢´íÎóµÈ¡£
	 * ¼ÓÔØÌ×½Ó×Ö¿â£¬³õÊ¼»¯Ws2_32.dll¶¯Ì¬Á´½Ó¿â¡£
	 */
    error = WSAStartup(wVersionRequested, &wsaData);
    if (error != 0)
    {
        printf("¼ÓÔØÌ×½Ó×ÖÊ§°Ü£¡");
        return 0; // ³ÌÐò½áÊø
    }
    /* ÅÐ¶ÏÇëÇó¼ÓÔØµÄ°æ±¾ÊÇ·ñ·ûºÏÒªÇó */
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        WSACleanup(); // ²»·ûºÏ£¬¹Ø±ÕÌ×½Ó×Ö
        return 0;     // ³ÌÐò½áÊø
    }

    /*----------------------------------*/
    /*------ÉèÖÃÁ¬½ÓµØÖ·----------------*/
    /*----------------------------------*/
    Server_add.sin_family = AF_INET; /* µØÖ·¼Ò×å£¬±ØÐëÊÇAF_INET,×¢ÒâÖ»ÓÐËü²»ÊÇÍøÂç×Ö½ÚË³Ðò */
    Server_add.sin_addr.S_un.S_addr = inet_addr("192.168.73.1"); /* Ö÷»úµØÖ· */ 
    Server_add.sin_port = htons(5000); /* ¶Ë¿ÚºÅ */

    /*---------´´½¨Ì×½Ó×Ö--------*/
    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_server == INVALID_SOCKET)
    {
        printf("´´½¨Ì×½Ó×ÖÊ§°Ü\n");
        WSACleanup();
        return 0;
    }

    /*----------------------------------*/
    /*-----ÉèÖÃÌ×½Ó×ÖÑ¡Ïî£¨¿ÉÑ¡£©-------*/
    /*----------------------------------*/
    int opt = 1;
    setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));

    /*----------------------------------*/
    /*-----ÉèÖÃÌ×½Ó×ÖÎª¼àÌýÄ£Ê½---------*/
    /*----------------------------------*/
    if (bind(socket_server, (SOCKADDR *)&Server_add, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        printf("°ó¶¨Ê§°Ü\n");
        closesocket(socket_server);
        WSACleanup(); // ÖÕÖ¹ËùÓÐÏß³Ì
        return 0;
    }

    /*------------------------------*/
    /*---------ÉèÖÃÎª¼àÌýÄ£Ê½-------*/
    /*------------------------------*/
    if (listen(socket_server, 5) < 0)
    {
        printf("¼àÌýÊ§°Ü\n");
        closesocket(socket_server);
        WSACleanup();
        return 0;
    }

    /*-----------------------------*/
    /*-----------½ÓÊÜÁ¬½Ó----------*/
    /*-----------------------------*/
    Length = sizeof(SOCKADDR);
	// ½ÓÊÜÁ¬½Ó
	/**
	 * µÚ¶þ´ÎÎÕÊÖ
	 * acceptº¯Êý½ÓÊÜÒ»¸öÁ¬½Ó£¬²¢·µ»ØÒ»¸öÐÂµÄÌ×½Ó×ÖÓÃÓÚÓë¿Í»§¶ËÍ¨ÐÅ¡£
	 * ¸Ãº¯Êý»á×èÈû³ÌÐò£¬Ö±µ½ÓÐÐÂµÄÁ¬½ÓÇëÇóµ½´ï¡£
	 * º¯ÊýµÄ²ÎÊý°üÀ¨£º
	 * socket_server£ºÓÃÓÚ¼àÌýÁ¬½ÓµÄÌ×½Ó×Ö¡£
	 * Client_add£ºÓÃÓÚ´æ´¢¿Í»§¶ËµØÖ·ÐÅÏ¢µÄ½á¹¹Ìå¡£
	 * Length£ºÓÃÓÚ´æ´¢¿Í»§¶ËµØÖ·ÐÅÏ¢µÄ³¤¶È¡£
	 */
    socket_receive = accept(socket_server, (SOCKADDR *)&Client_add, &Length);
    if (socket_receive == SOCKET_ERROR)
    {
        printf("Á¬½ÓÊ§°Ü\n");
        closesocket(socket_server);
        WSACleanup();
        return 0;
    }

    /*---------------------------------*/
    /*----------½øÐÐÁÄÌì---------------*/
    /*---------------------------------*/
    while (1) /* ÎÞÏÞÑ­»· */
    {
        /*----------½ÓÊÜÊý¾Ý-------------*/
        memset(Receivebuf, 0, sizeof(Receivebuf)); // Çå¿Õ»º³åÇø
        ReceiveLen = recv(socket_receive, Receivebuf, sizeof(Receivebuf) - 1, 0);
        if (ReceiveLen <= 0)
        {
            printf("½ÓÊÜÊ§°Ü\n");
            break;
        }
        else
        {
            printf("client(he or she) say: %s\n", Receivebuf);
        }

        /*-------·¢ËÍÊý¾Ý--------*/
        printf("please input message£¨Êä³ö exit ÍË³ö£©: ");
        scanf("%99s", Sendbuf);
        getchar(); // ¶ÁÈ¡»»ÐÐ·û
        if (strcmp(Sendbuf, "exit") == 0)
        {
            break;
        }
        SendLen = send(socket_receive, Sendbuf, strlen(Sendbuf), 0);
        if (SendLen == SOCKET_ERROR)
        {
            printf("·¢ËÍÊ§°Ü\n");
            break;
        }
    }

    /*----------------------------------*/
    /*------ÊÍ·ÅÌ×½Ó×Ö£¬¹Ø±Õ¶¯Ì¬¿â------*/
    /*----------------------------------*/
    closesocket(socket_receive); // ÊÍ·Å¿Í»§¶ËµÄÌ×½Ó×Ö×ÊÔ´
    closesocket(socket_server);  // ÊÍ·ÅÌ×½Ó×Ö×ÊÔ´
    WSACleanup();                // ¹Ø±Õ¶¯Ì¬Á´½Ó¿â
    return 0;
}


