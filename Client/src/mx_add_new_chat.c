#include "../inc/header.h"



void mx_add_new_chat(CHAT_T** chat,char *name, int CHAT_ID) {
    CHAT_T *new_chat;
    if (*chat == NULL) {
        *chat = mx_create_new_chat(name, CHAT_ID);
        new_chat = *chat;
    }
    else {

        CHAT_T *temp = *chat;
        CHAT_T *temp_1 = NULL;
        while(temp->next!= NULL) {
            temp = temp->next;
        }
        temp_1 = temp;
        
        temp = temp->next;
        temp = malloc(sizeof(CHAT_T));
        temp->CHAT_ID = CHAT_ID;
        temp->name_chat = strdup(name);
        temp->message_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        temp->chat_button = gtk_button_new_with_label(temp->name_chat);
        if (strcmp(name, FAVORITE_CHAT_DEFINE) == 0) {
            gtk_widget_set_name(GTK_WIDGET(temp->chat_button), "main_menu_key");
        }
        else {
            gtk_widget_set_name(GTK_WIDGET(temp->chat_button), "chat");
        }
        temp->messages = NULL;
        temp->next = NULL;
        temp_1->next = temp;
        new_chat = temp;
    }
}