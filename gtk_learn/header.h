#include <gtk/gtk.h>
#include <string.h>
#include "unistd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>

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
}              CHAT_T;



CHAT_T* mx_get_index_chat(CHAT_T *chat, int index);
void mx_add_new_chat(CHAT_T** chat,char *name);
CHAT_T* mx_create_new_chat(char* name);
void add_new_message(MESSAGE_T **message, char *text, char *sender);
MESSAGE_T* mx_get_index_message(MESSAGE_T *message, int index);
void mx_fill_message_list_box(CHAT_T **chat, char *login, char *sender, char* message);
CHAT_T* mx_find_name_chat(CHAT_T *chat, char* name);
MESSAGE_T* mx_take_last_message(MESSAGE_T *message);
void mx_update_used_chat(CHAT_T *used_chat);
void select_chat_on_off(CHAT_T *chat, char mode);