#include "../inc/header.h"

static char* add_char_to_str(char* str, char ch) {
    char* result;
    return result;
}

char** ps_message(char* src) {
    for (int i = 0; i < 8; i++, src++);
    char* id1_s = "";
    char* id2_s = "";

    for(; src[0] != ']'; src++) {
        char* ch = (char*)malloc(2);
        ch[0] = src[0];
        ch[1] = '\0';
        id1_s = concat(id1_s, ch);
        free(ch);
    }

    src++;
    src++;
    for(; src[0] != ']'; src++) {
        char* ch = (char*)malloc(2);
        ch[0] = src[0];
        ch[1] = '\0';
        id2_s = concat(id2_s, ch);
        free(ch);
    }
    src++;
    int id1_l = strlen(id1_s);
    int id2_l = strlen(id2_s);

    char** result = (char**)malloc(sizeof(char*) * 3);
    result[0] = strdup(id1_s);//(char*)malloc(sizeof(char) * id1_l + 1);
    result[1] = strdup(id2_s);
    result[2] = strdup(src);

    free(id1_s);
    free(id2_s);
    return result;
}

char** ps_registration(char* src) {
    for (int i = 0; i < 13; i++, src++);
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

void ps_massage_add(char *str,char **login, char **message, int *chat_ID) {
    mx_printerr(str);
    char *temp_1 = mx_strncpy(temp_1,  &str[7], strlen(str) - 8); // Обрезаем massage
    int info_counter = 0;

    for (int i = 0; temp_1[i] != '/'; i++)
        info_counter++;
    char *chat_ID_char = mx_strnew(info_counter);
    chat_ID_char = strncpy(chat_ID_char, temp_1, info_counter);
    temp_1 = strncpy(temp_1, &temp_1[info_counter+1], strlen(temp_1) - info_counter - 1);

    *chat_ID = atoi(chat_ID_char);

//    for (int i = 1; mx_isdigit(temp_1[i]); i++) // Считаем количество цифр в размере логина
   //     num_counter++; 
    
    //temp_1 = mx_strncpy(temp_1, &temp_1[2+num_counter], strlen(temp_1) - 2+num_counter);



 //   char* temp_login_size = mx_strncpy(temp_login_size, &temp_1[1], num_counter);
  //  int temp_login_size_NUM = atoi(temp_login_size);



   // *login = mx_strncpy(*login, &temp_1[2+num_counter], temp_login_size_NUM); // вырезаем логин
    //mx_printerr(*login);
  //  *message = mx_strncpy(*message, &temp_1[2+num_counter+temp_login_size_NUM], strlen(temp_1) - (temp_login_size_NUM)); // вырезаем пароль
    //mx_printerr(*message);

   // mx_strdel(&temp_1);
  //  mx_strdel(&temp_login_size);
    return;
}