#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include <netdb.h>


#define SERVERADDR "127.0.0.1"

int main() { 
    char buff[256];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(8000);

    //struct HOSTENT *hst;
    server = gethostbyname(SERVERADDR);
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr,    server->h_addr,  server->h_length);

  
    serv_addr.sin_port = htons(8000);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        char str[10];// = "test";
        scanf("%s", str);
    while (1) {
        sleep(3);
        printf("YOU INPUTED %s\n", str);
        send(sock, str, sizeof(str), 0);

        int nsize = recv(sock, &buff[0], sizeof(buff) - 1, 0);
        if (nsize < 0) {
            continue;
        }
        else
        {
            printf("Server has returt %s\n", &buff[0]);
            //write(1,buff, strlen(buff));
        }
              


    }

    
    close(sock);
}