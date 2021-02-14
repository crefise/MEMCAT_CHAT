#include "../inc/header.h"

void mx_send_file(int sock, char* filename) {
    FILE *picture;
    picture = fopen(filename, "r");
    int size;
    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
    //Send Picture Size
    printf("Sending Picture Size\n");
    write(sock, &size, sizeof(size));
    //Send Picture as Byte Array
    printf("Sending Picture as Byte Array\n");
    char send_buffer[size];
    while(!feof(picture)) {
        fread(send_buffer, 1, sizeof(send_buffer), picture);
        write(sock, send_buffer, sizeof(send_buffer));
        bzero(send_buffer, sizeof(send_buffer));
    }


    CHAT_T *used_chat = NULL;
    if (strcmp(OPENED_DIALOG, FAVORITE_CHAT_DEFINE) == 0) {
        used_chat = FAVORITE_CHAT; 
    }
    else {
        used_chat = mx_find_name_chat(MY_CHATS, OPENED_DIALOG);
    }

        char *date = mx_get_client_date();
        mx_fill_message_file_list_box(&used_chat,OPENED_DIALOG, USER_LOGIN, filename, date);
        
    mx_update_used_chat(used_chat);
}
