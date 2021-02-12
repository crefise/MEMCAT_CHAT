#include "../inc/header.h"


void mx_update_used_chat(CHAT_T *used_chat) {

    GtkWidget *will_hide = used_chat->message_box;
    GtkWidget *will_show = used_chat->message_box;
    gtk_widget_hide(will_hide);
    gtk_widget_show_all(will_show);
}