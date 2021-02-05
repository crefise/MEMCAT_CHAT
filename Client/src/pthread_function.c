#include "../inc/header.h"


void ps_massage_in(char *str) {
    char *temp_1 = mx_strncpy(temp_1,  &str[8], strlen(str) - 8); // Обрезаем massage

///////////////////////// GETTING LOGIN AND TEXT MMESSAGE//////////////////////////////////
    int info_counter = 0;
    for (int i = 0; temp_1[i] != '/'; i++)
        info_counter++;
    char *login = mx_strnew(info_counter);
    login = strncpy(login, temp_1, info_counter);
    char *text_message = mx_strnew(strlen(temp_1) - info_counter - 1);
    text_message = strncpy(text_message, &temp_1[info_counter+1], strlen(temp_1) - info_counter - 1);
    mx_strdel(&temp_1);
//////////////////////////////////////////////////////////////////////////////////////////

    mx_printerrln("USED_CHECK");
    mx_printerr("\n|");
    mx_printerr(login);
    mx_printerr("|\n");
    CHAT_T *used_chat = mx_find_name_chat(MY_CHATS, login);
    if (used_chat == NULL || !used_chat)
        mx_printerrln("ERRORRRRRR");
        mx_printerrln("USED_CHECK");
    mx_fill_message_list_box(&used_chat, login, login, text_message);
        mx_printerrln("USED_CHECK");
    if (strcmp(OPENED_DIALOG, login) == 0) 
        mx_update_used_chat(used_chat);
    return;
}




void* massage_check_in(void* socket) {
    mx_printerr("PTHREAD MASSAGE WAITER IS WORKING...\n");
    int sock = *(int *)socket;
    char *buffer = mx_strnew(256);
    while(1==1) {
    if (recv(sock, &buffer[0], 256, 0) == 0) {
        mx_printerr("MASSAGE_CHECK_IN ERROR\n");
        return NULL;
    } 
    mx_printerr("Massage that in: ");
    mx_printerrln(buffer);
    if (buffer[0] == 'm') {
        ps_massage_in(buffer);
    }

    }
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
    char *result = concat(concat(concat("message[",temp_1), concat("]",temp_2)), temp_3); // massage[size_login]loginMESSAGE
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
