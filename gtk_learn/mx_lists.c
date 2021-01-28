#include "header.h"

CHAT_T* mx_get_index_chat(CHAT_T *chat, int index) {
    CHAT_T *temp = chat;
    int i = 0;
    while (temp != NULL) {
        if (i == index) {
            return temp;
        }
        temp = temp->next;
        i++;
    }
   // write(2, "Index error(mx_get_index_chat())\n", 33);
    return NULL;
}
void mx_add_new_chat(CHAT_T** chat,char *name) {

    CHAT_T *temp = *chat;
    CHAT_T *temp_1 = NULL;
    while(temp->next!= NULL) {
        temp = temp->next;
    }
    temp_1 = temp;
    temp = temp->next;
    temp = malloc(sizeof(CHAT_T));
    temp->name_chat = strdup(name);
    temp->message_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    temp->chat_button = gtk_button_new_with_label(temp->name_chat);
    gtk_widget_set_name(GTK_WIDGET(temp->chat_button), "chat");
    temp->messages = NULL;
    temp->next = NULL;
    temp_1->next = temp;
}
CHAT_T* mx_create_new_chat(char* name) {
    CHAT_T *temp = malloc(sizeof(CHAT_T));
    temp->name_chat = strdup(name);
    temp->message_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    temp->chat_button = gtk_button_new_with_label(temp->name_chat);
    temp->messages = NULL;
    gtk_widget_set_name(GTK_WIDGET(temp->chat_button), "chat");
    temp->next = NULL;
    return temp;
}




void add_new_message(MESSAGE_T **message, char *text, char *sender) {
    if (*message == NULL) {
        (*message) = malloc(sizeof(MESSAGE_T));
        (*message)->message_text = strdup(text);
        (*message)->sender = strdup(sender);
        (*message)->next = NULL;
        (*message)->text_label = gtk_label_new(text);
        gtk_widget_set_name(GTK_WIDGET((*message)->text_label), "message");
    } 
    else {
        MESSAGE_T *temp = *message, *temp_1 = NULL;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp_1 = temp;
        temp = temp->next;
        temp = malloc(sizeof(MESSAGE_T));
        temp->message_text = strdup(text);
        temp->sender = strdup(sender);
        temp->text_label = gtk_label_new(text);
        temp_1->next = temp;
        temp->next = NULL;
        gtk_widget_set_name(GTK_WIDGET(temp->text_label), "message");
    }

}

MESSAGE_T* mx_get_index_message(MESSAGE_T *message, int index){
    MESSAGE_T *temp = message;
    int i = 0;
    while (temp != NULL) {
        if (i == index) {
            return temp;
        }
        temp = temp->next;
        i++;
    }
   // write(2, "Index error(mx_get_index_message())\n", 36);
    return NULL;
}

void mx_fill_message_list_box(CHAT_T **chat, char *login) { // WILL DO

if (strcmp(login, "Viktor") == 0 ) {
    add_new_message(&(*chat)->messages, "1", "Vladimir");
    add_new_message(&(*chat)->messages, "1", "Vladimir");
    add_new_message(&(*chat)->messages, "1", "Vladimir");
}
else {
    add_new_message(&(*chat)->messages, "2", "Vladimir");
    add_new_message(&(*chat)->messages, "2", "Vladimir");
    add_new_message(&(*chat)->messages, "2", "Vladimir");
}
    for (int i = 0; mx_get_index_message((*chat)->messages,i) != NULL; i++) { // PACK MESSAGES
        gtk_box_pack_start(GTK_BOX((*chat)->message_list_box), mx_get_index_message((*chat)->messages,i)->text_label, FALSE, FALSE, 5);
    }
}


CHAT_T* mx_find_name_chat(CHAT_T *chat, char* name) {
    CHAT_T *temp = chat;
    while (temp != NULL) {
        if (strcmp(temp->name_chat, name) == 0) {
            write(2, temp->name_chat, strlen(temp->name_chat));

            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}