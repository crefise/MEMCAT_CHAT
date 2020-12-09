#include "../inc/header.h"

//#define SERVERADDR "51.15.120.179"
#define SERVERADDR "10.11.6.1" // Айпи для моего ПК
#define SERVERPORT 8000 // Порт сервера

void initializate_socket(){
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
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
}



int sock;

int main (int argc, char *argv[])
{
    initializate_socket();


    gtk_init (&argc, &argv);

    main_loop();
 
    gtk_main ();

    return 0;
}