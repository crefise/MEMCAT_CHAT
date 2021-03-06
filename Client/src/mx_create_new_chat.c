#include "../inc/header.h"

CHAT_T* mx_create_new_chat(char* name, int CHAT_ID) {
    CHAT_T *temp = malloc(sizeof(CHAT_T));
    temp->name_chat = strdup(name);
    temp->CHAT_ID = CHAT_ID;  
    temp->message_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(temp->message_box), "sss");
    gtk_widget_set_halign(temp->message_box,GTK_ALIGN_FILL);
    temp->messages = NULL;
    if (strcmp(name, FAVORITE_CHAT_DEFINE) == 0) {
        temp->chat_button = gtk_button_new();
        gtk_widget_set_name(GTK_WIDGET(temp->chat_button), "main_menu_key");
        
    }
    else {
        temp->chat_button = gtk_button_new_with_label(temp->name_chat);
        gtk_widget_set_name(GTK_WIDGET(temp->chat_button), "chat");
    }
    temp->next = NULL;
    return temp;
}