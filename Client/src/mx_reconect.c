#include "../inc/header.h"

void mx_reconect() {

    gtk_widget_show_all(window);
    gtk_widget_hide(chats_box);
    gtk_widget_hide(message_box);

    close(sock);
    sock = socket(AF_INET, SOCK_STREAM, 0); // Сокет который ведет к серверу
    while (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        close(sock);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        mx_printerrln("reconecting..");
        usleep(100000);
    }
    mx_printerrln("RECONECT IS OKAY!!!");
    gtk_widget_show_all(window);
    gtk_widget_hide(reconnect_widget);


    return;
}