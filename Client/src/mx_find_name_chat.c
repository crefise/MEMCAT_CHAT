#include "../inc/header.h"


CHAT_T* mx_find_name_chat(CHAT_T *chat, char* name) {
    CHAT_T *temp = chat;
    while (temp != NULL) {
        if (strcmp(temp->name_chat, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
