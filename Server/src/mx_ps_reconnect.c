#include "../inc/header.h"
char* mx_ps_reconnect(char * buffer, int client_socket) { // connectlogin
    char *result = mx_strnew(strlen(buffer) - 7);
    result = mx_strncpy(result, &buffer[7], strlen(buffer) - 7);
    add_user_to_ONLINE_USERS(result, client_socket);
    return result;
}