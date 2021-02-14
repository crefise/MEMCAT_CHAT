#include "../inc/header.h"

void mx_send_file(int sock, char* filename) {
    char* path = sqlite3_mprintf("Server/databases/files/%s", filename);
    mx_printerr("PATH USED IN MX_SEND_FILE "); mx_printerrln(path);
    FILE *picture;
    picture = fopen(path, "r");

    int size;
    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
    write(sock, &size, sizeof(size));
    char send_buffer[size];
    while(!feof(picture)) {
        fread(send_buffer, 1, sizeof(send_buffer), picture);
        write(sock, send_buffer, sizeof(send_buffer));
        bzero(send_buffer, sizeof(send_buffer));
    }
mx_printerrln("GERE SADLKaSs ");
    sqlite3_free(path);
}