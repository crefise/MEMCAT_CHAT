#include "../inc/header.h"

bool curr_sybmobol(char *str) {
    int size_banned = 6;
    char banned_symbol[6] = {' ', '\\', '#', '[', ']', '/'};
    for (int i = 0; i < strlen(str); i++) {
        for (int z = 0; z < size_banned; z++) {
            if (str[i] == banned_symbol[z]) {
                return false;
            }
        }
    }
    return true;
}

void mx_del_strarr(char ***arr) {
    int i = 0;
    
    while ((*arr)[i] != NULL) {
        mx_strdel(&(*arr)[i]);
        i++;
    }
    free(*arr);
    *arr = NULL;
}

char *mx_strnew(const int size) {
    if (size < 1) {
        return NULL;
    }
    char *result = (char *)malloc(size + 1);
    for (int i = 0; i < size+1; i++)
    {
        result[i] = '\0';
    }
    return result;
}