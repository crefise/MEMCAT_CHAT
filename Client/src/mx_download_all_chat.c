#include "../inc/header.h"


void mx_download_all_chat(CHAT_T* chats) {
    PAUSE = 1;
    char *buffer = concat(concat("dialogs[", USER_LOGIN), "]");
    printf("Download all chat: buffer = %s\n", buffer);
    if (send(sock, buffer, strlen(buffer), 0) == -1) { // send data to server
        write(2, "SERVER DONT CONNETCTED\n",23);
    } 

    mx_strdel(&buffer);
    buffer = mx_strnew(256);

    if (recv(sock, &buffer[0], 256, 0) == 0) {
        mx_printerr("ERROR SERVER CONNECTIONS (download all chat)\n");
    }




    printf("Client got: buffer = %s\n", buffer);
    if (strcmp(buffer, "-") == 0) {
        mx_printerr("NULL CHATS");
        PAUSE = 0;
        return;
    }
    else {
        mx_ps_off_chat_message(buffer);
    }
    PAUSE = 0;
}
