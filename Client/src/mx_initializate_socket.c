#include "../inc/header.h"

void mx_initializate_socket(){
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sock = socket(AF_INET, SOCK_STREAM, 0); // Сокет который ведет к серверу
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERVERPORT);
    server = gethostbyname(SERVERADDR);
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr,    server->h_addr_list[0],  server->h_length);
    serv_addr.sin_port = htons(SERVERPORT);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        sock = -1;
}
