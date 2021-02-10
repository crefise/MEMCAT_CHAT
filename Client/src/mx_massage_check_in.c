#include "../inc/header.h"

void* mx_massage_check_in(void* socket) {
    mx_printerr("PTHREAD MASSAGE WAITER IS WORKING...\n");
    int sock = *(int *)socket;
    char *buffer = mx_strnew(256);
    while(1==1) {
        while (!PAUSE) {
            if (recv(sock, &buffer[0], 256, MSG_DONTWAIT) == 0) {
                mx_printerr("MASSAGE_CHECK_IN ERROR\n Starting reconnect....\n");
                mx_reconect();
                continue;
            }
            if (buffer[0] == 'm') {
                mx_printerr("CHECK IN : ");
                mx_printerrln(buffer);
                mx_ps_message_that_in(buffer);
                mx_strdel(&buffer);
                buffer = mx_strnew(256);
            }
            continue;
        }
        //mx_printerr("PAUSE ");
    }
    return NULL;
}