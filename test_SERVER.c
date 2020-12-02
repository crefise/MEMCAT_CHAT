#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <pthread.h>
#define BUF_SIZE 256;

void *func(void* sock) {
        char buff[256];
        char buff2[256];
           printf("CONNECTED\n");
           int *temp = sock;
           int client_socket = *temp;
            while (1) {
            int nsize = recv(client_socket, &buff2[0], sizeof(buff2) - 1, 0);
            if (nsize == 0)
                break;
            printf("%d\n", nsize);
            if (nsize < 0)
                continue;

            else {
                //printf ("Server took : %s\n", buff2);
                send(client_socket, &buff2[0], sizeof(&buff2[0]) - 1, 0);
            }
        }
       // printf("CONNECTION CLOSED\n");
        close(client_socket);
        return NULL;
}

int main() {
    // Инициализируем сокет!
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        write(2, "SOCK() ERROR\n", 13);
        return -1;
    }
    write(1, "SOCK SUCCESS\n",13);


    //Вводим информацию для связывания
    struct sockaddr_in sock_info;
    sock_info.sin_family = AF_INET;
    sock_info.sin_port = htons(8000); // переводим порт в сетевой порядок
    sock_info.sin_addr.s_addr = 0;    // сервер принимает подключения на все свои IP-адреса


    //Связываем сокет
    if (bind(sock, (struct sockaddr *)&sock_info, sizeof(sock_info))) {
        write(2, "BIND() ERROR\n", 13);
        close(sock); // закрываем сокетб перед выходом
        exit(-1);
    }
    write(1, "BIND SUCCESS\n",13);

    //Устанавливаем очередь для сокета & Ожидаем подключения
    if (listen(sock, 0x100) < 0) {
        write(2, "LISTEN() ERROR\n", 15);
        exit(-1);
    }
    write(1, "LISTEN SUCCESS\n Waiting connection...\n",38);

    // Получаем сообщения из сокета
    int ph_count;
    pthread_t pthreads[5];
    int client_socket; // сокет для клиента
    struct sockaddr_in client_addr; // адрес клиента (заполняется системой)
    int client_addr_size = sizeof(client_addr);
    while ((client_socket = accept(sock, (struct sockaddr *)&client_addr, &client_addr_size))) {
        write(1,"CONNETCTED: \n",13);
        //struct DWORD thID;

        pthread_create(&pthreads[ph_count], NULL, func, &client_socket);
      //  pthread_join(pthreads[ph_count], NULL);
        ph_count++;
       // pthread_create(&pthreads[0], NULL, test_func, NULL);

        write(1,"PTHREAD CREATED: \n",18);

        //send(client_socket, "Hello", sizeof("Hello"), 0);
        /*
        while (1) {
            int nsize = recv(client_socket, &buff2[0], sizeof(buff2) - 1, 0);
            if (nsize == 0)
                break;
            printf("%d\n", nsize);
            if (nsize < 0)
                continue;

            else {
                printf ("Server took : %s\n", buff2);
                send(client_socket, &buff2[0], sizeof(buff2), 0);
            }
        }
    
        printf("CONNECTION CLOSED\n");
        close(client_socket);
            */
    }
    close(sock);
    return 0;
}