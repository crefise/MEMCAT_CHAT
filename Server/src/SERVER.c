#include "../inc/header.h"

void *user_connect(void* sock);
int parse_solution(char *text);
int ph_count = 0; 
sqlite3* users_db;
sqlite3* chats_db;

int main() {
    /**** START DATABASE BLOCK ****/
    write(1, "####### DATABASE BLOCK ######\n", 30);

    open_db("Server/databases/users.db", &users_db);
    open_db("Server/databases/chats.db", &chats_db);

    exec_db("CREATE TABLE USERS("\
           "ID             INTEGER PRIMARY KEY AUTOINCREMENT,"\
           "LOGIN          TEXT                NOT NULL,"\
           "PASSWORD       TEXT                NOT NULL,"\
           "UNIQUE (ID, LOGIN));", users_db);
   
    exec_db("CREATE TABLE CHATS("\
           "CHAT_ID        INT PRIMARY KEY     NOT NULL,"\
           "USER1_ID       INT                 NOT NULL,"\
           "USER2_ID       INT                 NOT NULL,"\
           "PATH           TEXT                NOT NULL);", chats_db);

    exec_db("SELECT * FROM USERS", users_db);
    
    write(1, "####### DATABASE BLOCK ######\n", 30);
    /**** END DATABASE BLOCK ****/

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
        return -1;
    }
    write(1, "BIND SUCCESS\n",13);

    //Устанавливаем очередь для сокета & Ожидаем подключения
    if (listen(sock, 0x100) < 0) {
        write(2, "LISTEN() ERROR\n", 15);
        return -1;
    }
    write(1, "LISTEN SUCCESS\n Waiting connection...\n",38);

    // Получаем сообщения из сокета
    pthread_t pthreads[5];
    int client_socket; // сокет для клиента
    struct sockaddr_in client_addr; // адрес клиента (заполняется системой)
    unsigned int client_addr_size = (unsigned int)sizeof(client_addr);
    while ((client_socket = accept(sock, (struct sockaddr *)&client_addr, &client_addr_size))) {
        write(1,"CONNETCTED: \n",13);
        pthread_create(&pthreads[ph_count], NULL, user_connect, &client_socket);
        ph_count++;
        printf("Подключенные клиенты - %d\n",  ph_count);
        write(1,"PTHREAD CREATED: \n",18);
    }
    close(sock);

    /**** START DATABASE BLOCK ****/
    exec_db("SELECT * FROM USERS", users_db);
    close_db(users_db);
    close_db(chats_db);

    /**** END DATABASE BLOCK ****/
    return 0;
}



