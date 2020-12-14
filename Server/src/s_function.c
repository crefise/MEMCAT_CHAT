
#include "../inc/header.h"

void *user_connect(void* sock) {
    char *buffer = NULL; // Буфер для обмена сообщениями между клиентом и сервером
    int *temp = sock;
    int client_socket = *temp;
    bool exit = 0;

    while (!exit) {

        mx_strdel(&buffer);
        buffer = mx_strnew(256);

        int nsize = recv(client_socket, &buffer[0], 256, 0); // Ждем ответа от клиента 

        if (nsize == 0) {
            write(2, "CLIENT CLOSE CONNECTION\n", 24);
            break;
        }


        pthread_t pthread; 

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
                write(2, "HOTIM  REGISTRAtSIYA\n",21);
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

                exit = 0;
                break;
            case 5: // We wanna login
                write(2, "HOTIM  LOGIN\n",14);
                char **temp_for_login = ps_login(buffer);
                if (access_db(temp_for_login[0], temp_for_login[1], users_db) == 1) {
                    if (send(client_socket, "1", 1, 0) == -1) { // отсылем 1 если логин удачный, отсылаем 0 если логин не удачный
                     write(2, "USER CLOSE CONNECTION\n",21);
                    }
                    mx_printerr("LOGIN SUCCESS");
                }
                else {
                    if (send(client_socket, "0", 1, 0) == -1) { // отсылем 1 если логин удачный, отсылаем 0 если логин не удачный
                     write(2, "USER CLOSE CONNECTION\n",21);
                    }
                    mx_printerr("LOGIN FILED");
                }

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