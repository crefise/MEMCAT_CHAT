#include "../inc/header.h"

void mx_write_file(int sock, char* filename) {
    //char* file_name = sqlite3_mprintf("Server/databases/files/%s" get_reference_file_in_CHAT(message_id));

    int size;
    read(new_sock, &size, sizeof(int));
    char p_array[size];
    read(new_sock, p_array, size);
    FILE *file;
    file = fopen(file_name, "w");
    fwrite(p_array, 1, sizeof(p_array), file);
    fclose(file);
    //sqlite3_free(file_name);
}