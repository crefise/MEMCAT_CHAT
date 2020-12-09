#include "header.h"

static char* add_char_to_str(char* str, char ch) {
    int len1 = strlen(str);
    int len2 = 1;                      
    char *result = malloc(len1 + len2 + 1);
    if (!result) {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);    
    return result;
}

char** ps_registration(char* src) {
    
}

char** ps_login(char* src) {
    int index = 6;
    int login_length, pass_length;
    char* login_length_s;
    char* pass_length_s;
    char** result = (char*)malloc(sizeof(char*) * 2);
    //result[0] = (char)malloc(sizeof(char))

    return result;
}
