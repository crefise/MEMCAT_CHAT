#include "../inc/header.h"
void mx_write_file(int new_sock) {
    int size;
    read(new_sock, &size, sizeof(int));
    //Read Picture Byte Array
    printf("Reading Picture Byte Array\n");
    char p_array[size];
        mx_printerrln("TEST1");
    read(new_sock, p_array, size);
        mx_printerrln("TEST1-2");
    //Convert it Back into Picture
    FILE *image;
    image = fopen("c1.zip", "w");
        mx_printerrln("TEST2");
    fwrite(p_array, 1, sizeof(p_array), image);
    fclose(image);
    mx_printerrln("TEST3");
}