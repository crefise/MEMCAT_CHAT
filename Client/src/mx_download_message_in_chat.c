#include "../inc/header.h"


void mx_download_message_in_chat(CHAT_T *chat) {
    if (strcmp(chat->name_chat, FAVORITE_CHAT->name_chat) == 0) {
        mx_printerrln("is favorite chat... stoping...");
        return;
    }
    PAUSE = 1;
    mx_printerr("CHECK CHAT ID NOW IS "); mx_printerr(i_to_s(chat->CHAT_ID)); mx_printerr(" AND CHAT NOW IS "); mx_printerrln(chat->name_chat);
    char *buffer = "";
    buffer = concat(buffer, "text/");
    buffer = concat(buffer, i_to_s(chat->CHAT_ID));
    mx_printerr("WILL SEND IF WANT UPDATE : "); mx_printerrln(buffer);
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
            if (strlen(buffer2) <= 1) {
                i--;
                continue;
            }
            mx_printerrln(buffer2);
            mx_load_dowloaded_messages(buffer2, chat);
            mx_strdel(&buffer2);
        }
    }

    mx_printerrln("END...");
   PAUSE = 0;
}