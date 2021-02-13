#include "../inc/header.h"


void login_connect(GtkWidget *button, gpointer data) {
    char *buffer = NULL;
    struct user_info *temp = data;

    gtk_label_set_text(GTK_LABEL(temp->label_error), "");

    char  *login = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_username));
    char *password = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_password));
    

    if (strcmp(login, "") == 0 || strcmp(password, "") == 0) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "Empty field(s)");
        return;
    }

    // А тут мы ждем ответа от сервера/ можно ли нам менять окно!
    buffer = concat((char*)"login[", (char*)i_to_s(strlen(login)));
    buffer = concat(buffer, "][");
    buffer = concat(buffer, (char*)i_to_s(strlen(password)));
    buffer = concat(buffer, "]");
    buffer = concat(buffer,login);
    buffer = concat(buffer,password);

    if (!mx_check_curr_sybmobol(login) || !mx_check_curr_sybmobol(password)){ // проверка на коректность ввода
        gtk_label_set_text(GTK_LABEL(temp->label_error), "BAD SYMBOL");
        return;
    }

    if (send(sock, buffer, strlen(buffer), 0) == -1) { // send data to server
        write(2, "SERVER DONT CONNETCTED\n",23);
    } 
    mx_strdel(&buffer);


    buffer = mx_strnew(1);
    if (recv(sock, &buffer[0], 1, 0) == -1) { // А тут мы ждем ответа от сервера/ нормально ли прошла регистрация!
        write(2, "SERVER DONT CONNETCTED\n",23);
    } 
    else {
        if (strcmp(buffer, "1") != 0) {
            gtk_label_set_text(GTK_LABEL(temp->label_error), "UNCOREECT PASS OR LOGIN");
        }
        else {
            write(2, "LOGIN OKAY\n",11);
            USER_LOGIN = strdup(login);
            pthread_t pthreads[1];
            pthread_create(&pthreads[0], NULL, mx_massage_check_in, &sock);
            pthread_create(&pthreads[0], NULL, console_style, NULL);
            gtk_widget_hide(login_window);
            main_menu(login_window);
        }
        mx_strdel(&buffer);

    }

}

