
#include "../inc/header.h"

void *user_connect(void* sock) {
    char buff[256]; // client - massage
    int *temp = sock;
    int client_socket = *temp;
    bool exit = 0;

    while (!exit) {
        int nsize = recv(client_socket, &buff[0], sizeof(buff) - 1, 0);

        if (nsize == 0) {
            write(2, "CLIENT CLOSE CONNECTION\n", 24);
            break;
        }

        printf("%d\n", nsize);

        if (nsize < 0)
            continue;
        else {
            pthread_t pthread;
            printf ("Server tooked : %s\n", buff);
            int solution = parse_solution(buff);

            switch (solution)
            {
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
                    char** temp = ps_registration(buff);
                    add_user_db(temp[0], temp[1], users_db);
                    exec_db("SELECT * FROM USERS", users_db);
                    exit = 0;
                    break;
                case 5: // We wanna login
                    write(2, "HOTIM  LOGIN\n",21);
                    exit = 1;
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