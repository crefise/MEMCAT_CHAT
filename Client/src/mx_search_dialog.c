#include "../inc/header.h"


void mx_search_dialog(GtkWidget *button, gpointer data) {
    PAUSE = 1;
  GtkWidget *search_str = data;
  char *text = strdup((char*)gtk_entry_get_text(GTK_ENTRY(search_str)));
  if (strlen(text) == 0 || mx_find_name_chat(MY_CHATS, text) != NULL || strcmp(USER_LOGIN, text) == 0) {
      mx_printerr("CHAT EXIST or CHAT NAME is YOUR LOGIN\n");
      // CAHT IS EXIST ERROR
      mx_strdel(&text);
  } 
  else {
    char *buffer = malloc(256); 
    char *will_send = concat(concat(concat(concat("isuser[", text), "/"), USER_LOGIN), "]");
    gtk_entry_set_text(GTK_ENTRY(search_str), "");
    if (send(sock, will_send, strlen(will_send), 0) == -1) { // send data to server
        write(2, "SERVER DONT CONNETCTED\n",23);
    }
    if (recv(sock, &buffer[0], 256, 0) == 0) {
        write(2, "SERVER DONT CONNETCTED\n",23);
    }

    if (atoi(buffer)) {
        mx_add_new_chat(&MY_CHATS, text, atoi(buffer));
        gtk_box_pack_start(GTK_BOX(chats_list_box), mx_find_name_chat(MY_CHATS, text)->chat_button, FALSE, FALSE, 1);
        gtk_container_add(GTK_CONTAINER(CONTAINER), mx_find_name_chat(MY_CHATS, text)->message_box);
        g_signal_connect(G_OBJECT(mx_find_name_chat(MY_CHATS, text)->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)mx_find_name_chat(MY_CHATS, text));
        gtk_widget_show_all(window);
        gtk_widget_hide(reconnect_widget);

        for (int i = 0; mx_get_index_chat(MY_CHATS, i)  && mx_get_index_chat(MY_CHATS, i) != NULL; i++) {
            gtk_widget_hide(mx_get_index_chat(MY_CHATS, i)->message_box);
        }  
        if (strcmp(FAVORITE_CHAT_DEFINE, OPENED_DIALOG) == 0) {
            gtk_widget_show_all(FAVORITE_CHAT->message_box);
        } 
        else {
            gtk_widget_show_all(mx_find_name_chat(MY_CHATS, OPENED_DIALOG)->message_box);
        }
    } 
    else {
        mx_printerr("ERROR CREATING DIALOG");
    }


    mx_strdel(&buffer);
    mx_strdel(&text);

  }
      PAUSE = 0;
}
