#include "../inc/header.h"




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
        if (strcmp(name, "Favorite") == 0) {
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
CHAT_T* mx_find_name_chat(CHAT_T *chat, char* name) {
    CHAT_T *temp = chat;
    while (temp != NULL) {
        if (strcmp(temp->name_chat, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void mx_update_used_chat(CHAT_T *used_chat) {

    GtkWidget *will_hide = used_chat->message_list_box;
    GtkWidget *will_show = used_chat->message_list_box;
    gtk_widget_hide(will_hide);
    gtk_widget_show_all(will_show);
}

int space_index(char *text, int beg, int end)
{
    int len = strlen(text);
    for (int i = beg; i < end; i--) 
        if (isspace(text[i]))
            return i;
    return -1;
}

void set_label(MESSAGE_T **message, char *text, char *sender) {
    int num = 36, i = 0, len = strlen(text);
    if(strlen(text) > num) {
        for (; len - i > num;) {
            char *tmp = (char*)malloc(len + 1);
            int index = space_index(text, i + num, i);
            
            if (index != -1) {
                strncpy(tmp, text, index);
                tmp[index] = '\0';
                while (isspace(text[index])) index++;
                text = concat(tmp, concat("\n", &text[index]));
                i = index;
            }
            
            else {
                strncpy(tmp, text, i + num);
                tmp[i + num] = '\0';
                text = concat(tmp, concat("\n", &text[i + num]));
                i = i + num + 1;
            }
            len++;
        }
    }
    (*message)->text_label = gtk_label_new(text);

}

void add_new_message(MESSAGE_T **message, char *text, char *sender) {
    mx_printerrln("????");
    if (*message == NULL) {
            mx_printerrln("????");
        (*message) = malloc(sizeof(MESSAGE_T));
             mx_printerrln("????");
        (*message)->message_text = strdup(text);
             mx_printerrln("????");
        (*message)->sender = strdup(sender);
             mx_printerrln("????");
        (*message)->next = NULL;
             mx_printerrln("????");
        //(*message)->text_label = gtk_label_new(text);
        set_label(message, text, sender);
        if (strcmp(sender, USER_LOGIN) == 0)
            gtk_widget_set_name(GTK_WIDGET((*message)->text_label), "message_my");
        else
            gtk_widget_set_name(GTK_WIDGET((*message)->text_label), "message_interlocutor");
    } 
    else {
        mx_printerrln("OOO");
        MESSAGE_T *temp = *message, *temp_1 = NULL;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp_1 = temp;
        temp = temp->next;
        temp = malloc(sizeof(MESSAGE_T));
        temp->message_text = strdup(text);
        temp->sender = strdup(sender);
        //temp->text_label = gtk_label_new(text);
        set_label(&temp, text, sender);
        temp_1->next = temp;
        temp->next = NULL;
        if (strcmp(sender, USER_LOGIN) == 0)
            gtk_widget_set_name(GTK_WIDGET(temp->text_label), "message_my");
        else
            gtk_widget_set_name(GTK_WIDGET(temp->text_label), "message_interlocutor");
    }

}
MESSAGE_T* mx_take_last_message(MESSAGE_T *message) {
    while (message->next != NULL)
    {
        message = message->next;
    }
    if (message == NULL) {
        write(2, "NULL ERROR MESSAGE(mx_take_last_message)\n",41);
        return NULL;
    }
    return message;
    
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



void select_chat_on_off(CHAT_T *chat, char mode) {  // Включение и выключения подсветки для чата
    if (strcmp(chat->name_chat, "Favorite") == 0) {
        if (mode == '+') { 
            gtk_widget_set_name(GTK_WIDGET(chat->chat_button), "main_menu_key_active");
        }
        else {
            gtk_widget_set_name(GTK_WIDGET(chat->chat_button), "main_menu_key");
        }
    }
    else {
        if (mode == '+') { 
            gtk_widget_set_name(GTK_WIDGET(chat->chat_button), "chat_active");
        }
        else {
            gtk_widget_set_name(GTK_WIDGET(chat->chat_button), "chat");
        }
    }
}


void select_chat(GtkWidget *button, gpointer data) {
    
    CHAT_T *used_chat = data;
    mx_printerr(" SELECT CHAT CHAT_ID HERE : "); mx_printerr(i_to_s(used_chat->CHAT_ID)); mx_printerr(" CHAT NAME NOW IS : "); mx_printerrln(used_chat->name_chat);
    if (!used_chat->messages) {
        mx_printerrln("downloading messages....");
        mx_download_message_in_chat(used_chat);
    }
    if (strcmp(used_chat->name_chat, OPENED_DIALOG) == 0) { // Если мы кликнулы на тот диалог что у нас уже открыт
        return;
    }
    GtkWidget *will_hide; 
    if (strcmp(FAVORIDE_CHAT_DEFINE, OPENED_DIALOG) == 0) { // Если открытый чат это сохраненки
        will_hide = FAVORITE_CHAT->message_list_box;
        select_chat_on_off(FAVORITE_CHAT,'-'); // подсветка
    }
    else {
        will_hide = mx_find_name_chat(MY_CHATS, OPENED_DIALOG)->message_list_box;
        select_chat_on_off(mx_find_name_chat(MY_CHATS,OPENED_DIALOG),'-'); // подсветка
    }
     GtkWidget *will_show = used_chat->message_list_box;

    OPENED_DIALOG = strdup(used_chat->name_chat);
    gtk_label_set_text(GTK_LABEL(collocutor_name), OPENED_DIALOG); // Имя для собеседника
    select_chat_on_off(used_chat,'+'); // подсветка
    
    gtk_widget_hide(will_hide);
    gtk_widget_show_all(will_show);
    scrolling();
}


