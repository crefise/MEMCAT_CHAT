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
