#include "../inc/header.h"

void mx_load_dowloaded_messages (char *buffer, CHAT_T *chat) {
    char *temp_1; char type;
    if (buffer[0] == 'm') {
        temp_1 = mx_strncpy(temp_1,  &buffer[8], strlen(buffer) - 8); // Обрезаем file
        type = 'm';
    }
    else {
        temp_1 = mx_strncpy(temp_1,  &buffer[5], strlen(buffer) - 5); // Обрезаем files
        type = 'f';
    }

    int counter = 0, const_temp = 0;
    for (int i = 0; temp_1[const_temp+i] != '/'; i++)
        counter++;
    char *CHAT_ID_CHAR = mx_strnew(counter);
    CHAT_ID_CHAR = strncpy(CHAT_ID_CHAR, &temp_1[const_temp], counter);
    const_temp += (counter + 1);
    counter = 0;


    for (int i = 0; temp_1[const_temp+i] != '/'; i++)
        counter++;
    char* login = mx_strnew(counter);
    CHAT_ID_CHAR = strncpy(login, &temp_1[const_temp], counter);
    const_temp += (counter + 1);
    counter = 0;
    for (int i = 0; temp_1[const_temp+i] != '/'; i++)
        counter++;
    char* message_id = mx_strnew(counter);
    message_id = strncpy(message_id, &temp_1[const_temp], counter);
    const_temp += (counter + 1);
    counter = 0;


    for (int i = 0; temp_1[const_temp+i] != '/'; i++)
        counter++;
    char* date = mx_strnew(counter);
    date = strncpy(date, &temp_1[const_temp], counter);
    const_temp += (counter + 1);
    counter = 0;

    char *message = mx_strnew(strlen(temp_1) - const_temp);
    message = mx_strncpy(message, &temp_1[const_temp], strlen(temp_1) - const_temp);

    if (login == NULL || strlen(login) == 0)
        return;

if (type == 'm')
    add_new_message(&(chat->messages), message, login, &chat);
else
    add_new_message_file(&(chat->messages), message, login, &chat);

    gtk_box_pack_start(GTK_BOX(chat->messages->message_text_box), mx_take_last_message(chat->messages)->key_label, FALSE, FALSE, 5);   
    

    GtkWidget *date_label = gtk_label_new(date);
    gtk_widget_set_name(date_label, "date_label");
    if (strcmp(login, USER_LOGIN) == 0)
        gtk_widget_set_halign(date_label,GTK_ALIGN_END);
    else 
        gtk_widget_set_halign(date_label,GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chat->messages->message_text_box), date_label, FALSE, FALSE, 1);

    scrolling();


    //mx_strdel(&CHAT_ID_CHAR);
    mx_strdel(&login);
    mx_strdel(&message_id);
    mx_strdel(&date);
    mx_strdel(&message);
    
}

/*
    add_new_message(&(*chat)->messages, message, sender);
    gtk_box_pack_start(GTK_BOX((*chat)->message_list_box), mx_take_last_message((*chat)->messages)->key_label, FALSE, FALSE, 5);

    GtkWidget *date_label = gtk_label_new(date);
    gtk_widget_set_name(date_label, "date_label");
    gtk_box_pack_start(GTK_BOX((*chat)->message_list_box), date_label, FALSE, FALSE, 5);
    scrolling();
*/