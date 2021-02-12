#include "../inc/header.h"

void mx_fill_message_list_box(CHAT_T **chat, char *login, char *sender, char* message, char *date) { // WILL DO
    add_new_message(&(*chat)->messages, message, sender, chat);
    gtk_box_pack_start(GTK_BOX((*chat)->messages->message_text_box), mx_take_last_message((*chat)->messages)->text_label, FALSE, FALSE, 5);

 //   GtkWidget *date_label = gtk_label_new(date);
 //   gtk_widget_set_name(date_label, "date_label");
 //   gtk_box_pack_start(GTK_BOX((*chat)->message_text_box), date_label, FALSE, FALSE, 5);
    scrolling();
}