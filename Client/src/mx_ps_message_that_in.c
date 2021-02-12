#include "../inc/header.h"

void mx_ps_message_that_in(char *str) {
    char *temp_1 = mx_strncpy(temp_1,  &str[8], strlen(str) - 8); // Обрезаем massage
///////////////////////// GETTING LOGIN AND TEXT MMESSAGE//////////////////////////////////
    int info_counter = 0;
    for (int i = 0; temp_1[i] != '/'; i++)
        info_counter++;
    char *login = mx_strnew(info_counter);
    login = strncpy(login, temp_1, info_counter);
    char *temp_2 = mx_strnew(strlen(temp_1) - info_counter - 1);
    temp_2 = strncpy(temp_2, &temp_1[info_counter+1], strlen(temp_1) - info_counter - 1);
    mx_strdel(&temp_1);
    info_counter = 0;
    for (int i = 0; temp_2[i] != '/'; i++)
        info_counter++;
    char *chat_ID_char = mx_strnew(info_counter);
    chat_ID_char = strncpy(chat_ID_char, temp_2, info_counter);

    char *text_message = mx_strnew(strlen(temp_2) - info_counter - 1);
    text_message = strncpy(text_message, &temp_2[info_counter+1], strlen(temp_2) - info_counter - 1);

    CHAT_T *used_chat = mx_find_name_chat(MY_CHATS, login);
    if (used_chat == NULL || !used_chat) {
        mx_add_new_chat(&MY_CHATS,login, atoi(chat_ID_char));
        used_chat = mx_find_name_chat(MY_CHATS, login);
        gtk_box_pack_start(GTK_BOX(chats_list_box), used_chat->chat_button, FALSE, FALSE, 1);
        gtk_container_add(GTK_CONTAINER(CONTAINER), used_chat->message_list_box);
        g_signal_connect(G_OBJECT(used_chat->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)used_chat);
        gtk_widget_show_all(window);

    }

    mx_fill_message_list_box(&used_chat, login, login, text_message);
    if (strcmp(OPENED_DIALOG, login) == 0) 
        mx_update_used_chat(used_chat);
    return;
}
