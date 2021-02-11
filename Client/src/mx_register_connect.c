#include "../inc/header.h"


void register_connect(GtkWidget *button, gpointer data) {
    char *buffer = NULL;
    struct user_info *temp = data;

    gtk_label_set_text(GTK_LABEL(temp->label_error), "");

    char *login = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_username));
    char *password = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_password));
    char *password_repeat = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_confirm_password));


// Проверки на коректность ввода
    if (strlen(login) > 32 || strlen(login) < 1){ // проверка на коректность ввода
        gtk_label_set_text(GTK_LABEL(temp->label_error), "BAD LOGIN");
        return;
    }

    if (!mx_check_curr_sybmobol(login) || !mx_check_curr_sybmobol(password) || !mx_check_curr_sybmobol(password_repeat)){ // проверка на коректность ввода
        gtk_label_set_text(GTK_LABEL(temp->label_error), "BAD SYMBOL");
        return;
    }

    if (strcmp(login, "") == 0 || strcmp(password, "") == 0 || strcmp(password_repeat, "") == 0) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "Empty field(s)");
        return;
    }

    if (strcmp(password, password_repeat) != 0) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "Passwords do not match");
        return;
    }

    /*
    if (strlen(login) < 4) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "login ne mozet mense 4");
        return;
    }
    */
   /*
    if (strlen(password) < 6) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "Parol ne mojet bit mense 6");
        return;
    }
    */


    else {
        // отправляем на сервер запрос что мы хотим регистрироваться!

        buffer = concat(concat(concat(concat(concat(concat((char*)"registration[", 
                                        (char*)i_to_s(strlen(login))), "]["), 
                                        (char*)i_to_s(strlen(password))), "]"),login),password);

        if (send(sock, buffer, strlen(buffer), 0) == -1) { // отправляем на сервер наши данные для регистрации
            write(2, "SERVER DONT CONNETCTED\n",23);
            return;
        }
        mx_strdel(&buffer);

        buffer = mx_strnew(256);
        if (recv(sock, buffer, 256, 0) == -1) { // А тут мы ждем ответа от сервера/ нормально ли прошла регистрация!
            write(2, "SERVER DONT CONNETCTED\n",23);
            return;
        }
        else if (strcmp(buffer, "1") == 0){ // если от сервера пришло что регистер успешна
            mx_printerr("REGISTER SUCCESS");
            login_clbk((GtkButton*)button, (GtkStack*)stack); // переходим в авторизацию
            return;
        }
        else {
            gtk_label_set_text(GTK_LABEL(temp->label_error), "Login is used"); // если логин используется
        }
        mx_strdel(&buffer);

    }
}