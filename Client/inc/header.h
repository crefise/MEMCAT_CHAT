#ifndef HEADER_H
#define HEADER_H
#define FAVORIDE_CHAT_DEFINE "Favorite"
//#define SERVERADDR "51.15.120.179"
//#define SERVERADDR "10.11.6.1" // Айпи для моего ПК(VOVA)
#define SERVERADDR "localhost"
#define SERVERPORT 8000 // Порт сервера

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include<stdbool.h>
#include <netdb.h>
#include <pthread.h>
#include <ctype.h>


/*gtk_function.c*/
#include "gtk/gtk.h"
struct user_info {
    GtkWidget *entry_username;
    GtkWidget *entry_password;
    GtkWidget *entry_confirm_password;
    GtkWidget *label_error;
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
extern GtkWidget *login_window;
void main_menu();
GtkWidget* createConsoleBox();
void scrolling();


/* END gtk_function.c */
#include <sys/socket.h>
#include <sys/types.h>


/* string.c */
char* concat(char* s1, char* s2);
char* i_to_s(int n);
char *clear_buffer(char *s1);
char *mx_strnew(const int size);
void mx_strdel(char **str);
void mx_printerr(const char *s);
char *mx_strncpy(char *dst, const char *src, int len);
bool mx_isdigit(char c);
/* END string.c */

/* help_function.c */
bool curr_sybmobol(char *str);
/* END help_function.c */


/* socket_function */
extern int sock;
void initializate_socket();
/* END socket_function */

/* PTHREAD_FUNCTION.c */
void *massage_check_in(void * sock);
void *console_style();

extern GtkWidget *stack;







typedef struct MESSAGE_S 
{
    char* message_text;
    char* sender;
    GtkWidget *text_label;
    struct MESSAGE_S *next;
}              MESSAGE_T;


typedef struct CHAT_S
{
    GtkWidget *message_list_box;
    char* name_chat;
    GtkWidget* chat_button;
    struct CHAT_S* next; 
    MESSAGE_T *messages;
    int CHAT_ID;
}              CHAT_T;



CHAT_T* mx_get_index_chat(CHAT_T *chat, int index);
void mx_add_new_chat(CHAT_T** chat,char *name, int CHAT_ID);
CHAT_T* mx_create_new_chat(char* name, int CHAT_ID);
void add_new_message(MESSAGE_T **message, char *text, char *sender);
MESSAGE_T* mx_get_index_message(MESSAGE_T *message, int index);
void mx_fill_message_list_box(CHAT_T **chat, char *login, char *sender, char* message);
CHAT_T* mx_find_name_chat(CHAT_T *chat, char* name);
MESSAGE_T* mx_take_last_message(MESSAGE_T *message);
void mx_update_used_chat(CHAT_T *used_chat);
void select_chat_on_off(CHAT_T *chat, char mode);
void search_dialog(GtkWidget *button, gpointer data);
void select_chat(GtkWidget *button, gpointer data);
extern char* USER_LOGIN;
extern char *OPENED_DIALOG;
extern CHAT_T *MY_CHATS;
extern CHAT_T *FAVORITE_CHAT;
extern GtkWidget *collocutor_name;
extern GtkWidget *chats_list_box;
extern GtkWidget *CONTAINER;
extern GtkWidget *window; // my window
#endif
