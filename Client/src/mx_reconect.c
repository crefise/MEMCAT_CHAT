#include "../inc/header.h"

void mx_reconect() {

    gtk_widget_show_all(window);
    gtk_widget_hide(main_box);

    close(sock);
    sock = socket(AF_INET, SOCK_STREAM, 0); // Сокет который ведет к серверу
    while (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        close(sock);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        mx_printerrln("reconecting..");
        usleep(100000);
    }
    char *will_send = "connect";
    will_send = concat(will_send, USER_LOGIN);
    if (send(sock, will_send, strlen(will_send), 0) == -1) { // send data to server
        write(2, "SERVER DONT CONNETCTED\n",23);
        return;
    }

    gtk_widget_show_all(window);
    gtk_widget_hide(reconnect_widget);


    for (int i = 0; mx_get_index_chat(MY_CHATS, i)  && mx_get_index_chat(MY_CHATS, i) != NULL; i++) {
        gtk_widget_hide(mx_get_index_chat(MY_CHATS, i)->message_box);
    }  
    if (strcmp(FAVORITE_CHAT_DEFINE, OPENED_DIALOG) == 0) {
        gtk_widget_show_all(FAVORITE_CHAT->message_box);
    } 
    else {
        gtk_widget_show_all(mx_find_name_chat(MY_CHATS, OPENED_DIALOG)->message_box);
    }
    return;
}