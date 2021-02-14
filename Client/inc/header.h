#ifndef HEADER_H
#define HEADER_H

#define FAVORITE_CHAT_DEFINE "HOME"

/* IP CONFIG */

//#define SERVERADDR "51.15.120.179"
//#define SERVERADDR "10.11.6.1" // Айпи для моего ПК(VOVA)
//#define SERVERADDR "31.133.82.217" // DERLAS PC
//#define SERVERADDR "localhost"
#define TEST


/* LIB INCLUDING */
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
#include <pthread.h>
#include <ctype.h>
#include "gtk/gtk.h"
#include <sys/stat.h>

/*  (END)LIB INCLUDING */

struct user_info {
    GtkWidget *entry_username;
    GtkWidget *entry_password;
    GtkWidget *entry_confirm_password;
    GtkWidget *label_error;
};

typedef struct MESSAGE_S 
{
    GtkWidget *message_text_box;
    char* message_text;
    char* sender;
    GtkWidget *key_label;
    GtkWidget *data_label;
    char type;
    struct MESSAGE_S *next;
}              MESSAGE_T;


typedef struct CHAT_S
{
    GtkWidget *message_box;
    char* name_chat;
    GtkWidget* chat_button;
    struct CHAT_S* next; 
    MESSAGE_T *messages;
    int CHAT_ID;
}              CHAT_T;



struct edit_struct
{
    GtkWidget* edit_key;
    GtkWidget* delete_key;
};

struct edit_struct *edit;


extern char* USER_LOGIN;
extern char *OPENED_DIALOG;
extern CHAT_T *MY_CHATS;
extern CHAT_T *FAVORITE_CHAT;
extern GtkWidget *chats_list_box;
extern GtkWidget *CONTAINER;
extern GtkWidget *scrool_massages;
extern GtkWidget *window; // my window
extern GtkWidget *chats_box;
extern GtkWidget *message_box;
extern GtkWidget *reconnect_widget;
extern GtkWidget *main_box;
extern int sock;
extern int PAUSE;
extern GtkWidget *stack;
extern MESSAGE_T *ACTIVE_MESSAGE;


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
char* concat(char* s1, char* s2);
char* i_to_s(int n);
char *clear_buffer(char *s1);
void mx_strdel(char **str);
void mx_printerr(const char *s);
char *mx_strncpy(char *dst, const char *src, int len);
bool mx_isdigit(char c);
void mx_del_strarr(char ***arr);
void mx_printerrln(const char *s);
bool mx_check_curr_sybmobol(char *str);
void mx_initializate_socket(char *SERVERADDR, int SERVERPORT);
void *console_style();
char *mx_strnew(const int size);
extern struct sockaddr_in serv_addr;
void mx_reconect();
CHAT_T* mx_get_index_chat(CHAT_T *chat, int index);
void mx_add_new_chat(CHAT_T** chat,char *name, int CHAT_ID);
CHAT_T* mx_create_new_chat(char* name, int CHAT_ID);
void add_new_message(MESSAGE_T **message, char *text, char *sender, CHAT_T **chat);
MESSAGE_T* mx_get_index_message(MESSAGE_T *message, int index);
void mx_fill_message_list_box(CHAT_T **chat, char *login, char *sender, char* message, char *date);
CHAT_T* mx_find_name_chat(CHAT_T *chat, char* name);
MESSAGE_T* mx_take_last_message(MESSAGE_T *message);
void mx_update_used_chat(CHAT_T *used_chat);
void select_chat_on_off(CHAT_T *chat, char mode);
void select_chat(GtkWidget *button, gpointer data);
void exit_in_check_function();
void start_in_check_function();
void mx_ps_off_chat_message(char *str);
void mx_ps_message_that_in(char *str);
void mx_search_dialog(GtkWidget *button, gpointer data);
void mx_download_all_chat(CHAT_T* chats);
void mx_load_dowloaded_messages (char *buffer, CHAT_T *chat);
void mx_download_message_in_chat(CHAT_T *chat);
void mx_send_message(GtkWidget *button, gpointer data);
void* mx_massage_check_in(void* socket);
void select_chat(GtkWidget *button, gpointer data);
char* mx_get_client_date();
void mx_write_file(int sockfd);
void mx_send_file(int sockfd, char* filename);
void edit_func(GtkWidget *button, gpointer data);


void mx_fill_message_file_list_box(CHAT_T **chat, char *login, char *sender, char* message, char *date);
void add_new_message_file(MESSAGE_T **message, char *text, char *sender, CHAT_T **chat);
#endif
