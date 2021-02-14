#include "../inc/header.h"


void mx_fill_message_list_box(CHAT_T **chat, char *login, char *sender, char* message, char *date) { // WILL DO

    
    add_new_message(&(*chat)->messages, message, sender, chat, date);
    

   

    

    scrolling();
}

void mx_fill_message_file_list_box(CHAT_T **chat, char *login, char *sender, char* message, char *date) { // WILL DO

    
    add_new_message_file(&(*chat)->messages, message, sender, chat, date);
    gtk_box_pack_start(GTK_BOX((*chat)->messages->message_text_box), mx_take_last_message((*chat)->messages)->key_label, FALSE, FALSE, 5);


   

    scrolling();
}

void add_new_message_file(MESSAGE_T **message, char *text, char *sender, CHAT_T **chat, char *date) {

    if (!text || !sender)
        return;
    if (*message == NULL) {
        (*message) = malloc(sizeof(MESSAGE_T));
        (*message)->message_text = strdup(text);
        (*message)->sender = strdup(sender);
        (*message)->next = NULL;
        (*message)->message_text_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        (*message)->type = 'f';
        (*message)->data_label = gtk_label_new(date);
        (*message)->key_label = gtk_button_new();
        GtkWidget *file_img = gtk_image_new_from_file ("Client/img/file_img.png");
        gtk_container_add(GTK_CONTAINER((*message)->key_label),file_img);


        if (strcmp(sender, USER_LOGIN) == 0) {
            gtk_widget_set_halign((*message)->key_label,GTK_ALIGN_END);
            gtk_widget_set_halign((*message)->message_text_box,GTK_ALIGN_FILL);
        }
        else {
            gtk_widget_set_halign((*message)->key_label,GTK_ALIGN_START);
            gtk_widget_set_halign((*message)->message_text_box,GTK_ALIGN_FILL);
        }
        if (strcmp(sender, USER_LOGIN) == 0) {
            gtk_widget_set_name(GTK_WIDGET((*message)->key_label), "message_file_my");
            gtk_widget_set_name(GTK_WIDGET((*message)->message_text_box), "message_file_my");
        }
        else {
            gtk_widget_set_name(GTK_WIDGET((*message)->key_label), "message_file_interlocutor");
            gtk_widget_set_name(GTK_WIDGET((*message)->message_text_box), "message_file_interlocutor");
        }

        gtk_widget_set_name((*message)->data_label, "date_label");
        if (strcmp(sender, USER_LOGIN) == 0) {
            #ifdef TEST 
                mx_printerrln("we in my_message");
            #endif
            gtk_widget_set_halign((*message)->data_label,GTK_ALIGN_END);
        }
        else {
            #ifdef TEST 
                mx_printerrln("we in not my_message");
            #endif
            gtk_widget_set_halign((*message)->data_label,GTK_ALIGN_START);
        }


        gtk_box_pack_start(GTK_BOX((*chat)->message_box), (*message)->message_text_box, TRUE, TRUE, 20);
        gtk_box_pack_start(GTK_BOX((*chat)->messages->message_text_box), mx_take_last_message((*chat)->messages)->key_label, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX((*chat)->messages->message_text_box), (*message)->data_label, FALSE, FALSE, 1);
        g_signal_connect(G_OBJECT((*message)->key_label), "clicked", G_CALLBACK(edit_func), (gpointer)(*message));
    } 
    else {
        MESSAGE_T *temp = *message, *temp_1 = NULL;
        while (temp->next != NULL){
            temp = temp->next;
        }

        temp_1 = temp;
        temp = temp->next;
        temp = malloc(sizeof(MESSAGE_T));
        temp->message_text = strdup(text);
        temp->sender = strdup(sender);
        //set_label(&temp, text, sender);

        temp->key_label = gtk_button_new();
        GtkWidget *file_img = gtk_image_new_from_file ("Client/img/file_img.png");
        gtk_container_add(GTK_CONTAINER(temp->key_label),file_img);
        temp->type = 'f';
        temp->message_text_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        temp->data_label = gtk_label_new(date);
        if (strcmp(sender, USER_LOGIN) == 0) {
            gtk_widget_set_halign(temp->key_label,GTK_ALIGN_END);
            gtk_widget_set_halign(temp->message_text_box,GTK_ALIGN_END);
        }
        else {
            gtk_widget_set_halign(temp->key_label,GTK_ALIGN_START);
            gtk_widget_set_halign(temp->message_text_box,GTK_ALIGN_START);
        }
        temp_1->next = temp;
        temp->next = NULL;
        if (strcmp(sender, USER_LOGIN) == 0) {
            gtk_widget_set_name(GTK_WIDGET(temp->key_label), "message_file_my");
            gtk_widget_set_name(GTK_WIDGET(temp->message_text_box), "message_file_my");
        }
        else {
            gtk_widget_set_name(GTK_WIDGET(temp->key_label), "message_file_interlocutor");
            gtk_widget_set_name(GTK_WIDGET(temp->message_text_box), "message_file_interlocutor");
        }

        gtk_widget_set_name(temp->data_label, "date_label");
        if (strcmp(sender, USER_LOGIN) == 0) {
            #ifdef TEST 
                mx_printerrln("we in my_message");
            #endif
            gtk_widget_set_halign(temp->data_label,GTK_ALIGN_END);
        }
        else {
            #ifdef TEST 
                mx_printerrln("we in not my_message");
            #endif
            gtk_widget_set_halign(temp->data_label,GTK_ALIGN_START);
        }

        gtk_box_pack_start(GTK_BOX((*chat)->message_box), temp->message_text_box, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX((*chat)->messages->message_text_box), mx_take_last_message((*chat)->messages)->key_label, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX((*chat)->messages->message_text_box), temp->data_label, FALSE, FALSE, 1);
        g_signal_connect(G_OBJECT((temp)->key_label), "clicked", G_CALLBACK(edit_func), (gpointer)(temp));
    }
    scrolling();

}