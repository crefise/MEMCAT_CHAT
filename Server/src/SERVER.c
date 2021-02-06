#include "../inc/header.h"

void *user_connect(void* sock);
int parse_solution(char *text);
int ph_count = 0;

sqlite3* data_base;

int main() {
    /**** START DATABASE BLOCK ****/
    write(1, "####### DATABASE BLOCK ######\n", 30);

    set_console_color(GREEN);
    printf("Server start date: %s\n", get_server_date());
    set_console_color(NORMAL);

    open_db("Server/databases/data_base.db", &data_base);
    exec_db("CREATE TABLE USERS ("\
            "    ID INTEGER PRIMARY KEY AUTOINCREMENT,"\
            "    LOGIN TEXT(32) NOT NULL UNIQUE,"\
            "    PASSWORD TEXT NOT NULL);");
    exec_db("CREATE TABLE CHATS ("\
            "    CHAT_ID INTEGER PRIMARY KEY AUTOINCREMENT,"\
            "    USER1_ID INT NOT NULL,"\
            "    USER2_ID INT NOT NULL);");
    exec_db("CREATE TABLE ONLINE_USERS ("\
            "    USER_ID INTEGER PRIMARY KEY,"\
            "    LOGIN TEXT NOT NULL UNIQUE,"\
            "    SOCKET INT NOT NULL UNIQUE)");
    exec_db("CREATE TABLE CHAT ("\
            "    CHAT_ID INT NOT NULL,"\
            "    MESSAGE_ID INTEGER PRIMARY KEY AUTOINCREMENT,"\
            "    DATE_TIME DATETIME NOT NULL,"\
            "    MESSAGE TEXT NOT NULL,"\
            "    AUTHOR_ID INT NOT NULL);");

    //add_message_to_CHAT(1, 1, "hello, man");
    add_user_to_USERS("test_user1", "a");
    add_user_to_USERS("test_user2", "a");
    add_user_to_USERS("test_user3", "a");
    add_user_to_USERS("test_user4", "a");
    add_chat_to_CHATS("test_user1", "test_user2");
    add_chat_to_CHATS("test_user2", "test_user1");
    add_chat_to_CHATS("test_user1", "test_user3");
    add_chat_to_CHATS("test_user2", "test_user2");
    //delete_user_from_USERS(get_id_from_USERS("test_user4"));
    //delete_user_from_USERS(get_id_from_USERS("test_user4"));

    mx_printerr("======== ALL DB =========\n");
    mx_printerr("-----chats----\n");
    exec_db("SELECT * FROM CHATS");
    mx_printerr("-----users----\n");
    exec_db("SELECT * FROM USERS");
    mx_printerr("-----chat----\n");
    exec_db("SELECT * FROM CHAT");
    mx_printerr("======== ALL DB =========\n");

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
    pthread_t pthreads[1];
    int client_socket; // сокет для клиента
    struct sockaddr_in client_addr; // адрес клиента (заполняется системой)
    unsigned int client_addr_size = (unsigned int)sizeof(client_addr);
    while ((client_socket = accept(sock, (struct sockaddr *)&client_addr, &client_addr_size))) {
        pthread_create(&pthreads[0], NULL, user_connect, &client_socket);
        printf("Подключенные клиенты - %d\n",  ph_count);
    }
    close(sock);

    /**** START DATABASE BLOCK ****/
    close_db();

    /**** END DATABASE BLOCK ****/
    
    return 0;
}
