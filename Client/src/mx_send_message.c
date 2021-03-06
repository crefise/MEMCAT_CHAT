#include "../inc/header.h"

static void play_music() {
    system("afplay Client/audio/ping_pong_cut.mp3");
}

void mx_send_message(GtkWidget *button, gpointer data) {
    mx_printerrln("HERE...");
    if (ACTIVE_MESSAGE != NULL) {
        gtk_button_set_label(GTK_BUTTON(ACTIVE_MESSAGE->key_label), gtk_entry_get_text(GTK_ENTRY(data)));
        mx_printerrln(ACTIVE_MESSAGE->message_text);
        gtk_widget_set_name(ACTIVE_MESSAGE->key_label, "message_my");
        gtk_entry_set_text(GTK_ENTRY(data), "");
        gtk_widget_hide(edit->edit_key);
        gtk_widget_hide(edit->delete_key);
        ACTIVE_MESSAGE = NULL;
        return;
    }
     mx_printerrln("HERE...");
    char *buffer = NULL;
    //struct message_struct *messages = input;
    GtkWidget *input_str = data;
    CHAT_T *used_chat = NULL;
    if (strcmp(OPENED_DIALOG, FAVORITE_CHAT_DEFINE) == 0) {
        used_chat = FAVORITE_CHAT; 
    }
    else {
        used_chat = mx_find_name_chat(MY_CHATS, OPENED_DIALOG);
    }

    char *text = strdup((char*)gtk_entry_get_text(GTK_ENTRY(input_str)));
    if(text && strlen(text) > 0) {
        play_music();
        char *date = mx_get_client_date();
        mx_printerrln("TEEST?");
        mx_fill_message_list_box(&used_chat,OPENED_DIALOG, USER_LOGIN, text, date);
        gtk_entry_set_text(GTK_ENTRY(input_str), "");
        if (strcmp(FAVORITE_CHAT->name_chat, used_chat->name_chat) != 0) {
            buffer = concat("message/", used_chat->name_chat);
            buffer = concat(buffer, "/");
            buffer = concat(buffer, i_to_s(used_chat->CHAT_ID));
            buffer = concat(buffer, "/");
            buffer = concat(buffer, text);
            mx_printerr("PARSE STR:  |");
            mx_printerr(buffer);
            mx_printerr("\n");
            if (send(sock, buffer, strlen(buffer), 0) == -1) { // send data to server
                mx_printerrln("ERROR SENDING MESSAGE\n");
            } 
            mx_printerrln("SENDING SUCCSESS");
            // send massage to server
        }
    }
    mx_update_used_chat(used_chat);
    free(buffer);
}