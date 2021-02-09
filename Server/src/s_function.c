#include "../inc/header.h"

void set_console_color(char* color) {
    write(1, color, strlen(color));
}

void print_emoji(char* emoji) {
    write(1, emoji, strlen(emoji));
}

char* get_server_date() {
   char* time_date = malloc(sizeof(char) * 18);
   long int s_time;
   struct tm *m_time;
   s_time = time (NULL);
   m_time = localtime (&s_time);
   strftime (time_date, 128, "%X %d.%m.%Y", m_time);
   return time_date;
}

void double_free(char** array) {
   for (int i = 0; array[i]; i++) free(array[i]);
   free(array);
   array = NULL;
}

char *ps_comma_dot(char **text){

    char *result = strdup(text[0]);
    for (int i = 1; text[i] ; i++) {
        result = concat(concat(result, ";"), text[i]);
    }
    return result;

}
void send_massage_to_client(char* message, char* sender_login, char* recipient_login,  int sender, int chat_ID) {
    int send_sock = get_socket_from_ONLINE_USERS(recipient_login);
    if (send_sock != 1) { // if ONLINE SENDING TO HIM
        //printf("sender id = %d\n", get_id_from_USERS(sender_login));
        add_message_to_CHAT(chat_ID, get_id_from_USERS(sender_login), message);
    } 

        char *buffer = "message/";
        buffer = concat(buffer, sender_login);
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
    
    *login_1 =  mx_strnew(size_login_1);
    *login_2 =  mx_strnew(size_login_2);
    *login_1 = strncpy(*login_1, &text[7], size_login_1);
    *login_2 = strncpy(*login_2, &text[8+size_login_1], size_login_2);
    /*
    char *temp = NULL;
    if ((*login_1)[strlen(*login_1) - 1] == '\n') {
        mx_printerr("DELETE NEW STR");
        temp = &((*login_1)[strlen(*login_1) - 1]);
        free(temp);
    }
    if ((*login_2)[strlen(*login_2) - 1] == '\n') {
        mx_printerr("DELETE NEW STR");
        temp = &(*(login_2)[strlen(*login_2) - 1]);
        free(temp);
    }
    */
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
                delete_user_from_ONLINE_USERS(client_socket);
                printf("User [%s] closed connection\n", login);
            }
            else {
                printf("User [???] closed connection\n");
            }
            mx_strdel(&login);
            mx_strdel(&pass); 
            close(client_socket); // Закрываем сокет клиента
            break;
        }
        printf("Server took: %s\n", buffer);

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
                //mx_printerrln("T02");
                char** chats = get_chats_from_CHATS(login);
                //mx_printerrln("T02");
                for (int i = 0; chats != NULL && chats[i] != NULL; i++) {
                    //mx_printerr("CHECK erROR\n");
                    //mx_printerr(chats[i]);
                    //mx_printerr("\n");
                }
                
                if (chats == NULL) {
                    if (send(client_socket, "-", 1, 0) == -1)
                        mx_printerr("ERROR SENDING (UPDATE DIALOG): chats == NULL\n");
                }
                else {
                    mx_printerr("CHECK erROR\n");
                    temp = ps_comma_dot(chats);
                    mx_printerr("CHECK erROR\n");

                    if (send(client_socket, temp, strlen(temp), 0) == -1)
                        mx_printerr("ERROR SENDING (UPDATE DIALOG)\n");

                    mx_strdel(&temp);
                }

                ///////////////////////////////////////
                /*
                mx_printerr("Testing sending massive\n");
                int size_chats_int = 0;
                for (; chats[size_chats_int] != NULL; size_chats_int++);
                int32_t conv = htonl(size_chats_int);
                char *data = (char*)&conv;
                int left = sizeof(conv);
                int rc;
                do {
                    rc = write(client_socket, data, left);
                    if (rc < 0) {
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                            // use select() or epoll() to wait for the socket to be writable again
                        }
                        else if (errno != EINTR) {}
                    }
                    else {
                        data += rc;
                        left -= rc;
                    }
                }
                while (left > 0);

                for (int i = 0; chats[i]; i++) {
                    char* temp2 = sqlite3_mprintf("%s", chats[i]);
                    printf("Sending data: %s\n", temp2);
                    send(client_socket, temp2, strlen(temp2), 0);
                    sqlite3_free(temp2);
                }
                ///////////////////////////////////////////
                */

                //send(client_socket, "-", 1, 0);
                


                exit = 0;
                if (chats) {
                    mx_del_strarr(&chats);
                }
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
                mx_printerr("LOGIN|");
                mx_printerr(login_1);
                mx_printerr("|\n");
                mx_printerr("LOGIN|");
                mx_printerr(login_2);
                mx_printerr("|\n");
                if (get_id_from_USERS(login_1) == 0) { // Если такого логина не существует

                    mx_printerr("USER OR DIALOG DOES NOT EXIST\n");
                    if (send(client_socket, "0", 1, 0) == -1) { //
                        write(2, "USER CLOSE CONNECTION\n",21);
                    }
                } 
                else { // If login exist
                    int chat_id = add_chat_to_CHATS(login_1, login_2);
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
    if (check_user_in_USERS(temp[0])) { // if 1 человек уже зарегестрирован
        if (send(client_socket, "0", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        mx_printerr("USER CANT CREATE ACC, BECOUSE HE DID IT ALREADY");
    } 
    else {
        if (send(client_socket, "1", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        add_user_to_USERS(temp[0], temp[1]);
    }

    exec_db("SELECT * FROM USERS"); // base show
}

void log_func(char *buffer, int client_socket, bool *logined, char **login, char** pass) {
    char **temp_for_login = ps_login(buffer);
    if (check_login_password_in_USERS(temp_for_login[0], temp_for_login[1]) == 1) {
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
        add_user_to_ONLINE_USERS(temp_for_login[0], client_socket);
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
