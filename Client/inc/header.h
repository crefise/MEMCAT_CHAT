#ifndef HEADER_H
#define HEADER_H


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include<stdbool.h>
#include <netdb.h>

/*gtk_function.c*/
#include "gtk/gtk.h"
struct user_info {
    GtkWidget *entry_username;
    GtkWidget *entry_password;
    GtkWidget *entry_confirm_password;
};
void load_css ( void );
GtkWidget *createWindow ( const gint width, const gint height, const gchar *const title );
GtkWidget *create_login_box (GtkWidget *stack);
GtkWidget *create_login_grid (GtkWidget *stack);
GtkWidget *create_register_grid (GtkWidget *stack);
GtkWidget *create_stack_box (GtkWidget **stack);
void main_clbk (GtkButton *button, GtkStack *stack);
void login_clbk (GtkButton *button, GtkStack *stack );
void register_clbk (GtkButton *button, GtkStack *stack);
void quit_clbk    ( void );
void login_connect(GtkWidget *button, gpointer data);
void register_connect(GtkWidget *button, gpointer data);


/* END gtk_function.c */
#include <sys/socket.h>
#include <sys/types.h>

/* string.c */
char* concat(char* s1, char* s2);
char* i_to_s(int n);
/* END string.c */

/* socket_function */
extern int sock;
/* END socket_function */

#endif
