#include "../inc/header.h"

//#define SERVERADDR "127.0.0.1"
#define SERVERADDR "10.11.6.1" // Айпи для моего ПК
//./Desktop/MEMCHAT_VOVA/MEMCAT_CHAT/client_run
int main() { 
    char buff[256]; // Для передаваемого текста
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(8000);

    server = gethostbyname(SERVERADDR);
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr,    server->h_addr_list[0],  server->h_length);

  
    serv_addr.sin_port = htons(8000);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    char str[256];// = "test";
    scanf("%s", str);
    send(sock, str, sizeof(str), 0); // send data to server
    printf("YOU INPUTED %s\n", str);
    while (1) {
        //sleep(1);

        int nsize = recv(sock, &buff[0], sizeof(buff) - 1, 0);
        if (nsize == 0){
            write(2,"server CLOSE CONNECTION\n",24);
            return 1;
        }
        if (nsize < 0)
            continue;
        else
            printf("Server has returt %s\n", &buff[0]);
    }

    
    close(sock);
}
