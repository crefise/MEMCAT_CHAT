#include "../inc/header.h"
char * get_extension_from_filename(char *buff) {
    int counter = 0;
    for (int i = strlen(buff); buff[i] != '.'; i--)
        counter++;
    // hello.exe
    char *result = mx_strnew(counter);
    result = strcpy(result, &buff[strlen(buff) - counter]);
    return result;
}