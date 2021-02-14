#include "../inc/header.h"

void edit_func(GtkWidget *button, gpointer data)
{   
    if (choosen_one->key_label == NULL) {
        ACTIVE_MESSAGE = data;
        gtk_widget_show(edit->edit_key);
        gtk_widget_show(edit->delete_key);
        gtk_widget_show(edit->open_key);
        gtk_widget_set_name(button, "choosen_label");
        choosen_one->key_label = button;
    }
    else if (choosen_one->key_label == button){
        ACTIVE_MESSAGE = NULL;
        gtk_widget_hide(edit->edit_key);
        gtk_widget_hide(edit->delete_key);
        gtk_widget_hide(edit->open_key);
        gtk_widget_set_name(button, "message_my");
        choosen_one->key_label = NULL;
    }
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
    (*message)->key_label = gtk_button_new_with_label(text);

}

/* 
        temp->message_text_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        temp->message_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

       // gtk_widget_set_halign(temp->message_text_box,GTK_ALIGN_START);
       // gtk_widget_set_halign(temp->message_box,GTK_ALIGN_START);

        gtk_box_pack_start(GTK_BOX(temp->message_box), temp->message_text_box, FALSE, FALSE, 5);
        */
void add_new_message(MESSAGE_T **message, char *text, char *sender, CHAT_T **chat) {

    if (!text || !sender)
        return;
    if (*message == NULL) {
        (*message) = malloc(sizeof(MESSAGE_T));
        (*message)->message_text = strdup(text);
        (*message)->sender = strdup(sender);
        (*message)->next = NULL;
         (*message)->message_text_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        //(*message)->key_label = gtk_label_new(text);
        set_label(message, text, sender);
        if (strcmp(sender, USER_LOGIN) == 0) {
            gtk_widget_set_halign((*message)->key_label,GTK_ALIGN_END);
            gtk_widget_set_halign((*message)->message_text_box,GTK_ALIGN_FILL);
        }
        else {
            gtk_widget_set_halign((*message)->key_label,GTK_ALIGN_START);
            gtk_widget_set_halign((*message)->message_text_box,GTK_ALIGN_FILL);
        }
        if (strcmp(sender, USER_LOGIN) == 0) {
            gtk_widget_set_name(GTK_WIDGET((*message)->key_label), "message_my");
            gtk_widget_set_name(GTK_WIDGET((*message)->message_text_box), "text_box_my");
        }
        else {
            gtk_widget_set_name(GTK_WIDGET((*message)->key_label), "message_interlocutor");
            gtk_widget_set_name(GTK_WIDGET((*message)->message_text_box), "text_box_interlocutor");
        }
        gtk_box_pack_start(GTK_BOX((*chat)->message_box), (*message)->message_text_box, TRUE, TRUE, 20);
        g_signal_connect(G_OBJECT((*message)->key_label), "clicked", G_CALLBACK(edit_func), (gpointer)(*message));
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
        set_label(&temp, text, sender);
        temp->message_text_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        if (strcmp(sender, USER_LOGIN) == 0) {
            gtk_widget_set_halign(temp->key_label,GTK_ALIGN_END);
            gtk_widget_set_halign(temp->message_text_box,GTK_ALIGN_END);
        }
        else {
            gtk_widget_set_halign(temp->key_label,GTK_ALIGN_START);
            gtk_widget_set_halign(temp->message_text_box,GTK_ALIGN_START);
        }
        temp_1->next = temp;
        temp->next = NULL;
        if (strcmp(sender, USER_LOGIN) == 0) {
            gtk_widget_set_name(GTK_WIDGET(temp->key_label), "message_my");
            gtk_widget_set_name(GTK_WIDGET(temp->message_text_box), "text_box_interlocutor");
        }
        else {
            gtk_widget_set_name(GTK_WIDGET(temp->key_label), "message_interlocutor");
            gtk_widget_set_name(GTK_WIDGET(temp->message_text_box), "text_box_interlocutor");
        }
        gtk_box_pack_start(GTK_BOX((*chat)->message_box), temp->message_text_box, FALSE, FALSE, 0);
        g_signal_connect(G_OBJECT((temp)->key_label), "clicked", G_CALLBACK(edit_func), (gpointer)(temp));
    }
    scrolling();

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
    if (strcmp(chat->name_chat, FAVORITE_CHAT_DEFINE) == 0) {
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
    mx_printerrln("check(select_chat)...");
    if (strcmp(used_chat->name_chat, OPENED_DIALOG) == 0) { // Если мы кликнулы на тот диалог что у нас уже открыт
        return;
    }
        mx_printerrln("check(select_chat)...");
    GtkWidget *will_hide; 
        mx_printerrln("check(select_chat)...");
    if (strcmp(FAVORITE_CHAT_DEFINE, OPENED_DIALOG) == 0) { // Если открытый чат это сохраненки
        will_hide = FAVORITE_CHAT->message_box;
        select_chat_on_off(FAVORITE_CHAT,'-'); // подсветка
    }
    else {
        will_hide = mx_find_name_chat(MY_CHATS, OPENED_DIALOG)->message_box;
        select_chat_on_off(mx_find_name_chat(MY_CHATS,OPENED_DIALOG),'-'); // подсветка
    }
        mx_printerrln("check(select_chat)...");
     GtkWidget *will_show = used_chat->message_box;
    mx_printerrln("check(select_chat)...");
    OPENED_DIALOG = strdup(used_chat->name_chat);
    select_chat_on_off(used_chat,'+'); // подсветка
        mx_printerrln("check(select_chat)...");
    gtk_widget_hide(will_hide);
    gtk_widget_show_all(will_show);
    scrolling();
}


