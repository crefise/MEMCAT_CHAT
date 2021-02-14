#include "../inc/header.h"
       #include <sys/types.h>
       #include <sys/socket.h>
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

void send_chats_to_client(char** chats, int client_socket) {
    for (int i = 0; chats != NULL && chats[i] != NULL; i++) {}
        if (chats == NULL) {
            if (send(client_socket, "-", 1, 0) == -1)
                mx_printerr("ERROR SENDING (UPDATE DIALOG): chats == NULL\n");
        }
        else {
            mx_printerr("CHECK erROR\n");
            char* temp = ps_comma_dot(chats);
            mx_printerr("CHECK erROR\n");

            if (send(client_socket, temp, strlen(temp), 0) == -1)
                mx_printerr("ERROR SENDING (UPDATE DIALOG)\n");

            mx_strdel(&temp);
        }
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
    */

    //send(client_socket, "-", 1, 0);
}

void send_messages_to_client(char** messages, int client_socket) {
        if (messages == NULL) {
            mx_printerrln("messages = null");
            return;
        }
        int size_chats_int = 0;
        for (; messages[size_chats_int] != NULL; size_chats_int++);
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
        mx_printerrln("QWEREWFSDA");
        for (int i = 0; messages[i]; i++) {
            char* temp2 = sqlite3_mprintf("%s\0", messages[i]);
            if (send(client_socket, temp2, strlen(temp2), 0) == 0 ) {
                mx_printerrln("Error");
            }
            if (temp2[0] == 'f') {
                
                char *check_temp = strdup(temp2);
                mx_printerrln(check_temp);
                mx_printerrln("QWEREWFSDA");
                int counter_1 =0 ; int counter_temp = 0;
                for (int i = 0; 1 == 1; i++) {
                    if (check_temp[i] == '/')
                        counter_1++;
                    if (counter_1 == 3) {
                        counter_temp = i;
                        counter_temp++;
                        break;
                    }
                }
                mx_printerrln("QWEREWFSDA");
                counter_1 = 0;
                mx_printerrln("QWEREWFSDA");
                for (int i = counter_temp; check_temp[i] != '/'; i++)
                   counter_1++;
                   mx_printerrln("QWEREWFSDA");
                char *message_id = mx_strnew(counter_1);
                mx_printerr("COUNTER"); mx_printerrln(i_to_s(counter_1));
                mx_printerrln("QWEREWFSDA");
                message_id = strncpy(message_id, &check_temp[counter_temp], counter_1);
                mx_printerr("WEE TAKE FILE NAME:::");
                mx_printerrln(message_id);

                

                mx_printerrln("try sending to client!"); 
                char *extension = get_extension_from_filename(check_temp);
                char* temp3 = sqlite3_mprintf("%s%s", message_id, extension);
                mx_send_file(client_socket, temp3);
                mx_printerrln("sending okay!");
            }
            sqlite3_free(temp2);
            usleep(10000);
        }
}

void double_free(char** array) {
   for (int i = 0; array[i]; i++) free(array[i]);
   free(array);
   array = NULL;
}

char *ps_comma_dot(char **text) {

    char *result = strdup(text[0]);
    for (int i = 1; text[i] ; i++) {
        result = concat(concat(result, ";"), text[i]);
    }
    return result;

}
void send_massage_to_client(char* message, char* sender_login, char* recipient_login,  int sender, int chat_ID) {
    if (!message)
        mx_printerrln(message);
    if (!sender_login)
        mx_printerrln(sender_login);
    if (!recipient_login)
        mx_printerrln(recipient_login);
    int send_sock = get_socket_from_ONLINE_USERS(recipient_login);
    if (send_sock != 1) { // if ONLINE SENDING TO HIM
        //printf("sender id = %d\n", get_id_from_USERS(sender_login));
        mx_printerr("IF OKAY!");
        add_message_to_CHAT(chat_ID, get_id_from_USERS(sender_login), message);
    } 
    mx_printerr("OKAY!");
    char *buffer = "message/";
    buffer = concat(buffer, sender_login);
    buffer = concat(buffer, "/");
    buffer = concat(buffer, i_to_s(chat_ID));
    buffer = concat(buffer, "/");
    buffer = concat(buffer, message);
        mx_printerr("OKAY!");

    if (send(send_sock, buffer, strlen(buffer), 0) == -1)
       mx_printerrln("UKNOWN ERROR SENDONG (send_massage_to_client)");
       mx_printerr("OKAY!");
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
  


char* ps_delete_text(char *buffer) {
    char *result = mx_strnew(strlen(buffer) - 5);
    result = strncpy(result, &buffer[5], strlen(buffer) - 5);
    return result;
}


void ps_parse_file(char *buffer, int client_socket, char* login_my) {
    char *temp = mx_strnew(strlen(buffer) - 4 );
    temp = strncpy(temp, &buffer[4], strlen(buffer) - 4);
    mx_printerr("BUFFER TEMP:"); mx_printerrln(temp);

    int counter = 0;
   for (int i = 0; temp[i] != '/'; i++)
        counter++;
    char* loogin_second = mx_strnew(counter);
    loogin_second = strncpy(loogin_second, temp, counter);

    char *filename_temp = mx_strnew(strlen(temp) - strlen(loogin_second) - 1);
    filename_temp = strncpy(filename_temp, &temp[strlen(loogin_second)+1] ,strlen(temp) - strlen(loogin_second) - 1);
    mx_printerr("Login_second :"); mx_printerrln(loogin_second);
    mx_printerr("filename :"); mx_printerrln(filename_temp);

    counter = 0;
    for (int i = 0; filename_temp[i] != '/'; i++)
        counter++;
    char *filename = mx_strnew(counter);
    filename = strncpy(filename, filename_temp, counter);
    mx_printerr("filename normal :"); mx_printerrln(filename);
    int ID = add_file_to_CHAT(get_chat_id_from_CHATS(login_my, loogin_second), get_id_from_USERS(login_my), filename);


   int temo = get_socket_from_ONLINE_USERS(loogin_second);
    char *extension = get_extension_from_filename(filename);
    char *new_filename = i_to_s(ID);
    new_filename = concat(new_filename, extension);
    mx_write_file(client_socket, new_filename, get_chat_id_from_CHATS(login_my, loogin_second));
    mx_printerrln("mx_write_file_okay");
/*
       int send_sock = get_socket_from_ONLINE_USERS(loogin_second);
        if (send_sock != 1) { // if ONLINE SENDING TO HIM

        mx_printerr("IF OKAY!");
        return;
    } 
    */

    char *buff = strdup("file/");
    buff = concat(buff, login_my);
    buff = concat(buff, "/");
    buff = concat(buff, filename);

    if (send(temo, buff, strlen(buff), 0) == -1) { // send data to server
                mx_printerrln("ERROR SENDING MESSAGE\n");
    } 
    usleep(1000);
    mx_printerr("will use ");
    mx_printerrln(new_filename);
    mx_printerr("File name that will be used.:");
    mx_printerrln(new_filename);
    mx_printerrln("trying send file online");
    usleep(1000);
    mx_send_file(temo, new_filename);
    mx_printerrln("Sinding file to client succsess!");
}


void *user_connect(void* sock) {
    char *buffer = NULL; // Буфер для обмена сообщениями между клиентом и сервером
    int *temp = sock;
    int client_socket = *temp;
    char *login, *pass, *send_login, *send_text;
    bool exit = 0;
    bool logined = 0;

    while (!exit) {
        mx_printerr("\n--------ONLINE BASE NOW-----------\n");
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
                char** chats = get_chats_from_CHATS(login);
                send_chats_to_client(chats, client_socket);
                exit = 0;
                if (chats) {
                    mx_del_strarr(&chats);
                }
                break;
                
            case 3: // Хотим обновить сообщения в диалоге
                write(2, "UPPDATE TEXT IN DIALOG\n",23);
                mx_printerrln(ps_delete_text(buffer));
                char** messages = get_messages_from_CHAT(atoi(ps_delete_text(buffer)));
                if (messages != NULL) {
                    send_messages_to_client(messages, client_socket);
                }
                else {
                    mx_printerrln("messages = null");
                }
                
                if (messages) {
                    double_free(messages);
                }
                exit = 0;
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
            case 7:
                #ifdef TEST
                    mx_printerrln("Trying reconnect...");
                #endif

                login = mx_ps_reconnect(buffer, client_socket);
                logined = 1;
                mx_printerrln(login);

                #ifdef TEST
                    mx_printerr("Reconnect succsess login = \"");
                    mx_printerr(login);
                    mx_printerrln("\"");
                #endif
                exit = 0;
                break;
            case 8:
                #ifdef TEST
                    mx_printerrln("Trying take file...");
                #endif
                ps_parse_file(buffer,client_socket, login);

                       
                       
                mx_strdel(&buffer);
                exit = 0;
                break;
            case -1: // ошибка сообщения
                mx_strdel(&buffer);
                write(2, "-1 ERROR\n",9);
                exit = 0;
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
    if (text[0] == 'c')
        return 7;
    if (text[0] == 'f') 
        return 8;
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
        mx_printerr("USER CANT CREATE ACC, BECOUSE HE DID IT ALREADY\n");
        if (send(client_socket, "0", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        
    } 
    else {
        mx_printerr("USER  CREATE ACC\n");
        if (send(client_socket, "1", 1, 0) == -1) { // 1 - success registration, 0 - bad registration
            write(2, "USER CLOSE CONNECTION\n",21);
        }
        add_user_to_USERS(temp[0], temp[1]);
    }

    get_all_users_from_USERS_CONSOLE();
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

