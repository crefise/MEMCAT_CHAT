
#include "../inc/header.h"

char *ps_comma_dot(char **text){

    char *result = strdup(text[0]);
    for (int i = 1; text[i] ; i++) {
        result = concat(concat(result, ";"), text[i]);
    }
    return result;

}
void send_massage_to_client(char* message, char* sender_login, char* recipient_login,  int sender, int chat_ID) {
    int send_sock = get_socket_db(recipient_login);
    if (send_sock != 1) { // if ONLINE SENDING TO HIM
        add_message(chat_ID, get_users_ID(sender_login), message);
    } 

        char *buffer = concat("message/", sender_login);
        buffer = concat(buffer, "/");
        buffer = concat(buffer, message);

    if (send(send_sock, buffer, strlen(buffer), 0) == -1)
       mx_printerrln("UKNOWN ERROR SENDONG (send_massage_to_client)");
}
char *ps_update_dialog(char *buffer) { // dialogs[login]
    int login_size = 0;
    for (int i = 8; buffer[i] != ']'; i++)
        login_size++;
    char *login = malloc(login_size);
    login = strncpy(login, &buffer[8], login_size);
    return login;
}
void ps_isuser(char **login_1, char **login_2, char *text) { // isuser[login/login]
    int size_login_1 = 0, size_login_2 = 0;
    for (int i = 7; text[i] != '/'; i++)
        size_login_1++;
    for (int i = 8+size_login_1; text[i] != ']'; i++)
        size_login_2++;
    
    *login_1 =  malloc(size_login_1);
    *login_2 =  malloc(size_login_2);
    *login_1 = strncpy(*login_1, &text[7], size_login_1);
    *login_2 = strncpy(*login_2, &text[8+size_login_1], size_login_2);
}


void *user_connect(void* sock) {
    char *buffer = NULL; // Буфер для обмена сообщениями между клиентом и сервером
    int *temp = sock;
    int client_socket = *temp;
    char *login, *pass, *send_login, *send_text;
    bool exit = 0;
    bool logined = 0;
    while (!exit) {


        mx_printerr("--------ONLINE BASE NOW-----------\n");
        exec_db("SELECT * FROM ONLINE_USERS");
        mx_printerr("----------------------------------\n");

        mx_strdel(&buffer);
        buffer = mx_strnew(256);

        int nsize = recv(client_socket, &buffer[0], 256, 0); // Ждем ответа от клиента 

        if (nsize == 0) { // Если клиент вышел/ чистим все что надо
            if (logined) {
               // Удаление пользователя из онлайн базы пользователей
                char* temp_statement = "DELETE FROM ONLINE_USERS WHERE SOCKET=";
                temp_statement = concat(temp_statement, i_to_s(client_socket));
                temp_statement = concat(temp_statement, ";");
                exec_db(temp_statement);
                mx_strdel(&temp_statement);
                mx_printerr("USER \"");
                mx_printerr(login);
                mx_printerr("\" CLOSED CONNECTION.\n");
            }
            else {
                mx_printerr("UKNOWN USER CLOSED CONNECTION.\n");
            }
            mx_strdel(&login);
            mx_strdel(&pass); 
            close(client_socket); // Закрываем сокет клиента
            break;
        }



        mx_printerr("Server took : ");
        mx_printerr(buffer);
        mx_printerr("\n");

        int solution = parse_solution(buffer); // Узнаем чего именно хочет клиент
        char *login_1, *login_2;
        char *temp;
        int chat_ID;
        switch (solution) {
            case 1: // Хотим написать сообщение              
                ps_massage_add(buffer, &send_login, &send_text, &chat_ID); // Парсим сообщение что пришло
                send_massage_to_client(send_text, login, send_login, client_socket, chat_ID); // отправляем сообщение на нужный логин
                exit = 0;
                break;
            case 2: // Хотим обновить диалоги
                write(2, "UPPDATE DIALOGS\n",16);
                login_1 = ps_update_dialog(buffer);
                mx_printerrln("T02");
                char** chats = get_chats(login);
                mx_printerrln("T02");
                for (int i = 0; chats != NULL  && chats[i] != NULL; i++)
                {
                     mx_printerr("CHECK erROR\n");
                    mx_printerr(chats[i]);
                    mx_printerr("\n");

                }
                
                if (chats == NULL) {
                    if (send(client_socket, "-", 1, 0) == -1)
                        mx_printerr("ERROR SENDING (UPDATE DIALOG)\n");
                }
                else {
                                    mx_printerr("CHECK erROR\n");
                temp = ps_comma_dot(chats);
                                mx_printerr("CHECK erROR\n");
                if (send(client_socket, temp, strlen(temp), 0) == -1)
                    mx_printerr("ERROR SENDING (UPDATE DIALOG)\n");
                mx_del_strarr(&chats);
                mx_strdel(&temp);

                }
                /*
                mx_printerr("TEST_1\n");
                for (int i = 0; chats[i]; i++) {
                    mx_printerr("TEST_FOR\n");
                    send(client_socket, chats[i], strlen(chats[i]), 0);
                }
                send(client_socket, "-", 1, 0);
*/
                exit = 0;
                break;
                
            case 3: // Хотим обновить сообщения в диалоге
                write(2, "UPPDATE TEXT IN DIALOG\n",23);
                exit = 1;
                break;
            case 4: // We wanna register
                reg_func(buffer,client_socket);
                exit = 0;
                break;
            case 5: // We wanna login
                log_func(buffer, client_socket, &logined, &login, &pass);
                exit = 0;
                break;
            case 6: // isuser? isuser[login] // ADD NEW CHAT
                
                ps_isuser(&login_1,&login_2, buffer);
                if (get_users_ID(login_1) == 0) { // Если такого логина не существует
                    if (send(client_socket, "0", 1, 0) == -1) { //
                        write(2, "USER CLOSE CONNECTION\n",21);
                    }
                } 
                else { // If login exist
                    int chat_id = create_chat_db(login_1, login_2);
                    if (send(client_socket, i_to_s(chat_id), strlen(i_to_s(chat_id)), 0) == -1) {  // СОЗДАТЬ ЧАТ И ВМЕСТО ЕДЕНИЦИ СКИНУТЬ НОМЕР ЧАТА!
                        write(2, "USER CLOSE CONNECTION\n",21);
                    }
                }
                exec_db("SELECT * FROM CHATS");
                mx_strdel(&login_1);
                mx_strdel(&login_2);
                mx_strdel(&buffer);
                exit = 0;
                break;

            case -1: // ошибка сообщения
                write(2, "-1 ERROR\n",9);
                exit = 1;
                break;
            default: // неизвесная ошибка
                write(2, "UKNOWN ERROR\n",13);
                exit = 1;
                break;
        }
    }


    return NULL;
}




int parse_solution(char *text) {
    if (text[0] == 'm')
        return 1;
    if (text[0] == 'd')
        return 2;
    if (text[0] == 't')
        return 3;
    if (text[0] == 'r')
        return 4;
    if (text[0] == 'l')
        return 5;
    if (text[0] == 'i')
        return 6;
    return -1;
}

bool curr_sybmobol(char *str) {
    int size_banned = 5;
    char banned_symbol[5] = {' ', '\\', '#', '[', ']'};
    for (int i = 0; i < strlen(str); i++) {
        for (int z = 0; z < size_banned; z++) {
            if (str[i] == banned_symbol[z]) {
                return false;
            }
        }
    }
    return true;
}

void reg_func(char *buffer, int client_socket) {
    char** temp = ps_registration(buffer); // нужно удалить память ? НАпомнить сереги
    if (check_user_db(temp[0])) { // if 1 человек уже зарегестрирован
        if (send(client_socket, "0", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        mx_printerr("USER CANT CREATE ACC, BECOUSE HE DID IT ALREADY");
    } 
    else {
        if (send(client_socket, "1", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        add_user_db(temp[0], temp[1]);
    }

    exec_db("SELECT * FROM USERS"); // base show
}

void log_func(char *buffer, int client_socket, bool *logined, char **login, char** pass) {
    char **temp_for_login = ps_login(buffer);
    if (access_db(temp_for_login[0], temp_for_login[1]) == 1) {
        if (send(client_socket, "1", 1, 0) == -1) { // отсылем 1 если логин удачный, отсылаем 0 если логин не удачный
            write(2, "USER CLOSE CONNECTION\n",22);
            return;
        }
        *login = strdup(temp_for_login[0]);
        *pass = strdup(temp_for_login[1]);

        mx_printerr("LOGIN SUCCESS. USER: \"");
        mx_printerr(*login);
        mx_printerr("\"\n");

        *logined = true;
        add_online_user_db(temp_for_login[0], client_socket, data_base);
    }
    else {
        if (send(client_socket, "0", 1, 0) == -1) { // отсылем 1 если логин удачный, отсылаем 0 если логин не удачный
            write(2, "USER CLOSE CONNECTION\n",21);
            return;
        }
        mx_printerr("LOGIN FILED.");
    }
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