#include "../inc/header.h"

void mx_load_dowloaded_messages (char *buffer, CHAT_T *chat) {
    int counter = 0, const_temp = 0;
    for (int i = 0; buffer[const_temp+i] != '/'; i++)
        counter++;
    char *CHAT_ID_CHAR = mx_strnew(counter);
    CHAT_ID_CHAR = strncpy(CHAT_ID_CHAR, &buffer[const_temp], counter);
    const_temp += (counter + 1);
    counter = 0;


    for (int i = 0; buffer[const_temp+i] != '/'; i++)
        counter++;
    char* login = mx_strnew(counter);
    CHAT_ID_CHAR = strncpy(login, &buffer[const_temp], counter);
    const_temp += (counter + 1);
    counter = 0;
    for (int i = 0; buffer[const_temp+i] != '/'; i++)
        counter++;
    char* message_id = mx_strnew(counter);
    message_id = strncpy(message_id, &buffer[const_temp], counter);
    const_temp += (counter + 1);
    counter = 0;


    for (int i = 0; buffer[const_temp+i] != '/'; i++)
        counter++;
    char* data = mx_strnew(counter);
    data = strncpy(data, &buffer[const_temp], counter);
    const_temp += (counter + 1);
    counter = 0;

    char *message = mx_strnew(strlen(buffer) - const_temp);
    message = mx_strncpy(message, &buffer[const_temp], strlen(buffer) - const_temp);


    add_new_message(&(chat->messages), message, login);
    gtk_box_pack_start(GTK_BOX(chat->message_list_box), mx_take_last_message(chat->messages)->text_label, FALSE, FALSE, 5);   

    //mx_strdel(&CHAT_ID_CHAR);
    mx_strdel(&login);
    mx_strdel(&message_id);
    mx_strdel(&data);
    mx_strdel(&message);
    
}


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

void download_message_in_chat(CHAT_T *chat) {
    if (strcmp(chat->name_chat, FAVORITE_CHAT->name_chat) == 0) {
        mx_printerrln("is favorite chat... stoping...");
        return;
    }
    PAUSE = 1;

    char *buffer = "";
    buffer = concat(buffer, "text/");
    buffer = concat(buffer, i_to_s(chat->CHAT_ID));
    if (send(sock, buffer, strlen(buffer), 0) == 0) {
        mx_printerrln("ERROR SENDING(download_message_in_chat)");
    }
    else {
        printf("Testing getting mass\n");
        int32_t ret;
        char *data = (char*)&ret;
        int left = sizeof(ret);
        int rc;
        do {
            rc = read(sock, data, left);
            if (rc <= 0) {
                if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                    // use select() or epoll() to wait for the socket to be readable again
                }
                else if (errno != EINTR) {}
            }
            else {
                data += rc;
                left -= rc;
            }
        }
        while (left > 0);
        int messages_c = ntohl(ret);
        mx_printerr("INT : ");
        mx_printerrln(i_to_s(messages_c));
        
        for (int i = 0; i < messages_c; i++) {
            char* buffer2 = mx_strnew(256);
            if (recv(sock, &buffer2[0], 256, 0) == 0) {
                mx_printerrln("CLOSE CONNECTION");
            }
            mx_printerrln(buffer2);
            mx_load_dowloaded_messages(buffer2, chat);
            mx_strdel(&buffer2);
        }
    }

    mx_printerrln("END...");
   PAUSE = 0;
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
        temp->CHAT_ID = CHAT_ID;
        temp = temp->next;
        temp = malloc(sizeof(CHAT_T));
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
void mx_fill_message_list_box(CHAT_T **chat, char *login, char *sender, char* message) { // WILL DO
if (message == NULL) {
    //download from server
}
else {
    add_new_message(&(*chat)->messages, message, sender);
    gtk_box_pack_start(GTK_BOX((*chat)->message_list_box), mx_take_last_message((*chat)->messages)->text_label, FALSE, FALSE, 5);
}


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

void search_dialog(GtkWidget *button, gpointer data) {
    PAUSE = 1;
  GtkWidget *search_str = data;
  char *text = strdup((char*)gtk_entry_get_text(GTK_ENTRY(search_str)));
  if (strlen(text) == 0 || mx_find_name_chat(MY_CHATS, text) != NULL || strcmp(USER_LOGIN, text) == 0) {
      mx_printerr("CHAT EXIST or CHAT NAME is YOUR LOGIN\n");
      // CAHT IS EXIST ERROR
      mx_strdel(&text);
  } 
  else {
    char *buffer = malloc(256); 
    char *will_send = concat(concat(concat(concat("isuser[", text), "/"), USER_LOGIN), "]");
    gtk_entry_set_text(GTK_ENTRY(search_str), "");
    if (send(sock, will_send, strlen(will_send), 0) == -1) { // send data to server
        write(2, "SERVER DONT CONNETCTED\n",23);
    }
    if (recv(sock, &buffer[0], 256, 0) == 0) {
        write(2, "SERVER DONT CONNETCTED\n",23);
    }

    if (atoi(buffer)) {
        mx_add_new_chat(&MY_CHATS, text, atoi(buffer));
        gtk_box_pack_start(GTK_BOX(chats_list_box), mx_find_name_chat(MY_CHATS, text)->chat_button, FALSE, FALSE, 1);
        gtk_container_add(GTK_CONTAINER(CONTAINER), mx_find_name_chat(MY_CHATS, text)->message_list_box);
        g_signal_connect(G_OBJECT(mx_find_name_chat(MY_CHATS, text)->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)mx_find_name_chat(MY_CHATS, text));
        gtk_widget_show_all(window);
    } 
    else {
        mx_printerr("ERROR CREATING DIALOG");
    }


    mx_strdel(&buffer);
    mx_strdel(&text);

  }
      PAUSE = 0;
}

void select_chat(GtkWidget *button, gpointer data) {
    CHAT_T *used_chat = data;
    if (!used_chat->messages) {
        mx_printerrln("downloading messages....");
        download_message_in_chat(used_chat);
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


