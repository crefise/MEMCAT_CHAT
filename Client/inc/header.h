#ifndef HEADER_H
#define HEADER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include<stdbool.h>
#include <netdb.h>
#include "gtk/gtk.h"

void visible_pasword(GtkWidget *button, gpointer password_entry);
void visible_pasword(GtkWidget *button, gpointer password_entry);
void get_login(GtkWidget *button, gpointer data);
void get_password(GtkWidget *button, gpointer data);
void go_to_log(GtkWidget *button, gpointer window1);
void reg_window(GtkWidget *button, gpointer window);
void main_loop();
#endif
