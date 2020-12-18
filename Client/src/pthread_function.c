#include "../inc/header.h"

void* massage_check_in(void* socket) {
    mx_printerr("PTHREAD MASSAGE WAITER IS WORKING...\n");
    int sock = *(int *)socket;
    char *buffer = mx_strnew(256);
    if (recv(sock, &buffer[0], 256, 0) == 0) { // А тут мы ждем ответа от сервера/ нормально ли прошла регистрация!
        write(2, "SERVER DONT CONNETCTED\n",23);
        return NULL;
    } 
    mx_printerr("Massage that in:");
    mx_printerr(buffer);
    mx_printerr("\n");
    return NULL;
}