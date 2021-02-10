#include "../inc/header.h"

void mx_fill_message_list_box(CHAT_T **chat, char *login, char *sender, char* message) { // WILL DO
    add_new_message(&(*chat)->messages, message, sender);
    gtk_box_pack_start(GTK_BOX((*chat)->message_list_box), mx_take_last_message((*chat)->messages)->text_label, FALSE, FALSE, 5);
    scrolling();
}