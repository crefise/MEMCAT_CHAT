#include "../inc/header.h"

void mx_send_file(int sock, char* filename) {
    char* path = sqlite3_mprintf("databases/files/%s", filename);
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

    sqlite3_free(path);
}