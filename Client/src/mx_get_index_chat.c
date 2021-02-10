#include "../inc/header.h"




CHAT_T* mx_get_index_chat(CHAT_T *chat, int index) {
    CHAT_T *temp = chat;
    int i = 0;
    while (temp != NULL) {
        if (i == index) {
            return temp;
        }
        temp = temp->next;
        i++;
    }
   // write(2, "Index error(mx_get_index_chat())\n", 33);
    return NULL;
}