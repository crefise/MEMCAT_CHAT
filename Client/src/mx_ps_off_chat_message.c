#include "../inc/header.h"


void mx_ps_off_chat_message(char *str) {
    printf("str from un_ps_chat:\n%s\n", str);
    if (!str) {
        mx_printerr("NULL CHAT STR (un_ps_chat)\n");
        return;
    }
    str = concat(str, ";");
    int count_chat = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == ';')
            count_chat++;

    char **chats = malloc(sizeof(char*) * count_chat);
    int begin_size = 0;

    for (int i = 0; i < count_chat; i++) {
        int size = 0;
        while(str[begin_size + size] != ';' ) {
            size++;
        }
        chats[i] = mx_strnew(size);
        chats[i] = strncpy(chats[i], &str[begin_size], size);
        begin_size += size;
        begin_size++;
    }

    for (int i = 0; i < count_chat; i++) {
        char *chat_ID_char;
        char *chat_name;
        int char_ID_int;
        int temp_size = 0;

        for (int z = 0; chats[i][z] != '/' && &chats[i][z] != NULL; z++)
            temp_size++;

        chat_ID_char = malloc(temp_size);
        chat_ID_char = strncpy(chat_ID_char, chats[i], temp_size);
        chat_name = strndup(&chats[i][temp_size+1], strlen(&chats[i][temp_size+1]));
        mx_printerrln("CHECK?");
        mx_add_new_chat(&MY_CHATS, chat_name, atoi(chat_ID_char));  
        mx_printerrln("CHECK END");      
    }
}