#include "../inc/header.h"

bool mx_check_curr_sybmobol(char *str) {
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
