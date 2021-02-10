#include "../inc/header.h"

CHAT_T* mx_create_new_chat(char* name, int CHAT_ID) {
    CHAT_T *temp = malloc(sizeof(CHAT_T));
    temp->name_chat = strdup(name);
    temp->CHAT_ID = CHAT_ID;  
    temp->message_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    temp->chat_button = gtk_button_new_with_label(temp->name_chat);
    temp->messages = NULL;
    if (strcmp(name, "Favorite") == 0) {
        gtk_widget_set_name(GTK_WIDGET(temp->chat_button), "main_menu_key");
    }
    else {
        gtk_widget_set_name(GTK_WIDGET(temp->chat_button), "chat");
    }
    temp->next = NULL;
    return temp;
}