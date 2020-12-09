#include "../inc/header.h"

static char* add_char_to_str(char* str, char ch) {
    char* result;
    return result;
}

char** ps_registration(char* src) {
    char** result;
    return result;
}

char** ps_login(char* src) {
    for (int i = 0; i < 6; i++, src++);
    int login_length, pass_length;
    char* login_length_s = "";
    char* pass_length_s= "";

    for(; src[0] != ']'; src++) {
        char* ch = (char*)malloc(2);
        ch[0] = src[0];
        ch[1] = '\0';
        login_length_s = concat(login_length_s, ch);
        free(ch);
    }
    src++;
    src++;
    for(; src[0] != ']'; src++) {
        char* ch = (char*)malloc(2);
        ch[0] = src[0];
        ch[1] = '\0';
        pass_length_s = concat(pass_length_s, ch);
        free(ch);
    }
    src++;

    login_length = atoi(login_length_s);
    pass_length = atoi(pass_length_s);

    char** result = (char**)malloc(sizeof(char*) * 2);
    result[0] = (char*)malloc(sizeof(char) * login_length);
    result[1] = (char*)malloc(sizeof(char) * pass_length);

    for(int i = 0; i < login_length; i++, src++) {  result[0][i] = src[0]; }
    for(int i = 0; i < pass_length; i++, src++) {   result[1][i] = src[0]; }

    free(login_length_s);
    free(pass_length_s);
    return result;
}
