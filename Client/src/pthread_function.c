#include "../inc/header.h"

void* massage_check_in(void* socket) {
    mx_printerr("PTHREAD MASSAGE WAITER IS WORKING...\n");
    int sock = *(int *)socket;
    char *buffer = mx_strnew(256);
    if (recv(sock, &buffer[0], 256, 0) == 0) {
        mx_printerr("MASSAGE_CHECK_IN ERROR\n");
        return NULL;
    } 
    mx_printerr("Massage that in: ");
    mx_printerr(buffer);
    mx_printerr("\n");
    return NULL;
}

static int check_console_style(char *str) {
    char send_command[6] = "/send ";
    for (int i = 0; i < 6; i++) { // /send check 
        if (str[i] && str[i] == send_command[i]) {
            continue;
        }
        else {
            return -1;
        }
    }
    return 1;
}

char* parce_for_send_to_client(char *str) {
    int login_size = 0;
    int i;
    for (i = 6; str[i] != ' '; i++)
        login_size++;
    char *temp_1 = i_to_s(login_size);
    char *temp_2 = mx_strncpy(temp_2, &str[6], login_size);
    char *temp_3 = mx_strncpy(temp_3, &str[6+login_size+1], strlen(str)-(6+login_size+1));
    char *result = concat(concat(concat("message",temp_1), temp_2), temp_3);
    mx_strdel(&temp_1);
    mx_strdel(&temp_2);
    mx_strdel(&temp_3);
    return result;
}


void *console_style() {


    bool exit = false;
    while (!exit) {

        char *buff = NULL;
        mx_strdel(&buff);
        buff = mx_strnew(256);


        fgets(buff, 256, stdin); // Считываем команду с строки


        int solution = check_console_style(buff); // Обработка команды
        char *will_send = NULL;

        

        switch (solution) {
        case 1: // send 
            will_send = parce_for_send_to_client(buff);
        if (send(sock, &will_send[0], strlen(will_send), 0) == 0) { // А тут мы ждем ответа от сервера/ нормально ли прошла регистрация!
            mx_printerr("CONSOLE ERR\n");
            return NULL;
        } 
            break;
        case -1:
            mx_printerr("UKNOWN COMMAND\n");
            break;
        default:
            mx_printerr("UKNOWN ERROR\n");
            break;
        }
    }
    return NULL;
}