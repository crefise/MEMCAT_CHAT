#include "../inc/header.h"

void mx_write_file(int sock, char* filename, int chat_id) {
    //add_file_to_CHAT(get_chat_id_from_CHATS(login_my, loogin_second), get_id_from_USERS(login_my), filename);
    char* file_name = sqlite3_mprintf("Server/databases/files/%i.png", get_max_message_id_from_CHAT(chat_id));

    int size;
    read(sock, &size, sizeof(int));
    char p_array[size];
    read(sock, p_array, size);
    FILE *file;
    file = fopen(file_name, "w");
    fwrite(p_array, 1, sizeof(p_array), file);
    fclose(file);
    sqlite3_free(file_name);

}
/*
void mx_write_file(int new_sock, char* filename, int chat_id) {
    int size;
    read(new_sock, &size, sizeof(int));
    //Read Picture Byte Array
    printf("Reading Picture Byte Array\n");
    char p_array[size];
    read(new_sock, p_array, size);
    //Convert it Back into Picture
    printf("Converting Byte Array to Picture\n");
    FILE *image;
    image = fopen("c1.png", "w");
    fwrite(p_array, 1, sizeof(p_array), image);
    fclose(image);
}
*/