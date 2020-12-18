
#include "../inc/header.h"



void *user_connect(void* sock) {
    char *buffer = NULL; // Буфер для обмена сообщениями между клиентом и сервером
    int *temp = sock;
    int client_socket = *temp;
    char *login, *pass;
    bool exit = 0;
    bool logined = 0;
    while (!exit) {

        mx_strdel(&buffer);
        buffer = mx_strnew(256);

        int nsize = recv(client_socket, &buffer[0], 256, 0); // Ждем ответа от клиента 

        if (nsize == 0) {
            write(2, "CLIENT CLOSE CONNECTION\n", 24);
            if (logined) {
               mx_printerr(login);
               mx_strdel(&login);
               mx_strdel(&pass); 
               // Удаление пользователя из онлайн базы пользователей
               char* temp_statement = "DELETE FROM ONLINE_USERS WHERE SOCKET=";
               temp_statement = concat(temp_statement, i_to_s(client_socket));
               temp_statement = concat(temp_statement, ";");
               exec_db(temp_statement, online_users_db);
               mx_strdel(&temp_statement);
            }
            break;
        }



        printf("Server took : %s\n", buffer);
        int solution = parse_solution(buffer); // Узнаем чего именно хочет клиент

        switch (solution) {
            case 1: // Хотим написать сообщение
                write(2, "ADD MASSAGE\n",13);
                exit = 1;
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
        mx_printerr("--------ONLINE BASE NOW-----------");
        exec_db("SELECT * FROM ONLINE_USERS", online_users_db);
        mx_printerr("----------------------------------");
    }

    printf("CONNECTION  CLOSED\n");
    close(client_socket);
    ph_count--;

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
    if (check_user_db(temp[0], users_db)) { // if 1 человек уже зарегестрирован
        if (send(client_socket, "0", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        mx_printerr("USER CANT CREATE ACC, BECOUSE HE DID IT ALREADY");
    } 
    else {
        if (send(client_socket, "1", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        add_user_db(temp[0], temp[1], users_db);
    }

    exec_db("SELECT * FROM USERS", users_db); // base show
}

void log_func(char *buffer, int client_socket, bool *logined, char **login, char** pass) {
    char **temp_for_login = ps_login(buffer);
    if (access_db(temp_for_login[0], temp_for_login[1], users_db) == 1) {
        if (send(client_socket, "1", 1, 0) == -1) { // отсылем 1 если логин удачный, отсылаем 0 если логин не удачный
            write(2, "USER CLOSE CONNECTION\n",22);
            return;
        }
        *login = strdup(temp_for_login[0]);
        *pass = strdup(temp_for_login[1]);
        mx_printerr("LOGIN SUCCESS");
        *logined = true;
        add_online_user_db(temp_for_login[0], client_socket, online_users_db);
    }
    else {
        if (send(client_socket, "0", 1, 0) == -1) { // отсылем 1 если логин удачный, отсылаем 0 если логин не удачный
            write(2, "USER CLOSE CONNECTION\n",21);
            return;
        }
        mx_printerr("LOGIN FILED");
    }
}
