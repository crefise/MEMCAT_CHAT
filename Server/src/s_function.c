
#include "../inc/header.h"


void send_massage_to_client(char* message, char* login, int sender) {
    /*
    sqlite3_stmt *result;
    char* statement = "SELECT SOCKET from ONLINE_USERS where LOGIN='";
    statement = concat(statement, login);
    statement = concat(statement, "'");
    int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);
    result.
    */

    /*
    if (send(7, message, strlen(message), 0) == -1) { // 1 - success registration, 0 - bad registration
            mx_printerr("SEND ERROR\n");
    }
    */
   int send_sock = get_socket_db(login, data_base);
   mx_printerr("TOOK SOCK: ");
   write(2, i_to_s(send_sock), strlen(i_to_s(send_sock)));
   mx_printerr("\n");
    if (send(send_sock, message, strlen(message), 0) == -1) { // 1 - success registration, 0 - bad registration
        if (send(sender, "MESSAGE ERROR SEND!!!", 21, 0) == -1) { // 1 - success registration, 0 - bad registration
                mx_printerr("SEND ERROR\n");
        }
        mx_printerr("SEND ERROR\n");
    }
    else {
        if (send(sender, "Message send okay!", 18, 0) == -1) { // 1 - success registration, 0 - bad registration
                mx_printerr("SEND ERROR\n");
        }
    }
}

void *user_connect(void* sock) {
    char *buffer = NULL; // Буфер для обмена сообщениями между клиентом и сервером
    int *temp = sock;
    int client_socket = *temp;
    char *login, *pass, *send_login, *send_text;
    bool exit = 0;
    bool logined = 0;
    while (!exit) {


        mx_printerr("--------ONLINE BASE NOW-----------\n");
        exec_db("SELECT * FROM ONLINE_USERS", data_base);
        mx_printerr("----------------------------------\n");

        mx_strdel(&buffer);
        buffer = mx_strnew(256);

        int nsize = recv(client_socket, &buffer[0], 256, 0); // Ждем ответа от клиента 

        if (nsize == 0) { // Если клиент вышел/ чистим все что надо
            if (logined) {
               // Удаление пользователя из онлайн базы пользователей
                char* temp_statement = "DELETE FROM ONLINE_USERS WHERE SOCKET=";
                temp_statement = concat(temp_statement, i_to_s(client_socket));
                temp_statement = concat(temp_statement, ";");
                exec_db(temp_statement, data_base);
                mx_strdel(&temp_statement);
                mx_printerr("USER \"");
                mx_printerr(login);
                mx_printerr("\" CLOSED CONNECTION.\n");
            }
            else {
                mx_printerr("UKNOWN USER CLOSED CONNECTION.\n");
            }
            mx_strdel(&login);
            mx_strdel(&pass); 
            close(client_socket); // Закрываем сокет клиента
            break;
        }



        mx_printerr("Server took : ");
        mx_printerr(buffer);
        mx_printerr("\n");

        int solution = parse_solution(buffer); // Узнаем чего именно хочет клиент

        switch (solution) {
            case 1: // Хотим написать сообщение              
                ps_massage_add(buffer, &send_login, &send_text); // Парсим сообщение что пришло
                send_massage_to_client(send_text, send_login, client_socket); // отправляем сообщение на нужный логин
                exit = 0;
                break;
            case 2: // Хотим обновить диалоги
                write(2, "UPPDATE DIALOGS\n",16);
                exit = 1;
                break;
            case 3: // Хотим обновить сообщения в диалоге
                write(2, "UPPDATE TEXT IN DIALOG\n",23);
                exit = 1;
                break;
            case 4: // We wanna register
                reg_func(buffer,client_socket);
                exit = 0;
                break;
            case 5: // We wanna login
                log_func(buffer, client_socket, &logined, &login, &pass);
                exit = 0;
                break;
            case -1: // ошибка сообщения
                write(2, "-1 ERROR\n",9);
                exit = 1;
                break;
            default: // неизвесная ошибка
                write(2, "UKNOWN ERROR\n",13);
                exit = 1;
                break;
        }
    }


    return NULL;
}

int parse_solution(char *text) {
    if (text[0] == 'm')
        return 1;
    if (text[0] == 'd')
        return 2;
    if (text[0] == 't')
        return 3;
    if (text[0] == 'r')
        return 4;
    if (text[0] == 'l')
        return 5;
    return -1;
}

bool curr_sybmobol(char *str) {
    int size_banned = 5;
    char banned_symbol[5] = {' ', '\\', '#', '[', ']'};
    for (int i = 0; i < strlen(str); i++) {
        for (int z = 0; z < size_banned; z++) {
            if (str[i] == banned_symbol[z]) {
                return false;
            }
        }
    }
    return true;
}

void reg_func(char *buffer, int client_socket) {
    char** temp = ps_registration(buffer); // нужно удалить память ? НАпомнить сереги
    if (check_user_db(temp[0], data_base)) { // if 1 человек уже зарегестрирован
        if (send(client_socket, "0", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        mx_printerr("USER CANT CREATE ACC, BECOUSE HE DID IT ALREADY");
    } 
    else {
        if (send(client_socket, "1", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        add_user_db(temp[0], temp[1], data_base);
    }

    exec_db("SELECT * FROM USERS", data_base); // base show
}

void log_func(char *buffer, int client_socket, bool *logined, char **login, char** pass) {
    char **temp_for_login = ps_login(buffer);
    if (access_db(temp_for_login[0], temp_for_login[1], data_base) == 1) {
        if (send(client_socket, "1", 1, 0) == -1) { // отсылем 1 если логин удачный, отсылаем 0 если логин не удачный
            write(2, "USER CLOSE CONNECTION\n",22);
            return;
        }
        *login = strdup(temp_for_login[0]);
        *pass = strdup(temp_for_login[1]);

        mx_printerr("LOGIN SUCCESS. USER: \"");
        mx_printerr(*login);
        mx_printerr("\"\n");

        *logined = true;
        add_online_user_db(temp_for_login[0], client_socket, data_base);
    }
    else {
        if (send(client_socket, "0", 1, 0) == -1) { // отсылем 1 если логин удачный, отсылаем 0 если логин не удачный
            write(2, "USER CLOSE CONNECTION\n",21);
            return;
        }
        mx_printerr("LOGIN FILED.");
    }
}
