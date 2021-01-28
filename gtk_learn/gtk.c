#include <gtk/gtk.h>
#include <string.h>
#include "unistd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    GtkWidget *window; // my window
    GtkWidget *main_box,*chats_list_box,  *message_list_box, *message_box, *input_box, *search_box, *chats_box; // Боксы 
    GtkWidget *input_str, *input_key; // for imput_box
    GtkWidget *search_str, *search_key;
    GtkWidget *dialog;


void key_test(GtkWidget *button, gpointer data) {
    char *chat_name  = strdup((char*)gtk_button_get_label (GTK_BUTTON(button)));
    write(2,chat_name, strlen(chat_name));
}

void load_css ( void ) {
    GtkCssProvider *provider;
    GdkDisplay     *display;
    GdkScreen      *screen;
    /// ***
    const gchar *css_style_file = "style.css";
    GFile *css_fp               = g_file_new_for_path ( css_style_file );
    GError *error               = 0;
    /// ***
    provider = gtk_css_provider_new ();
    display  = gdk_display_get_default ();
    screen   = gdk_display_get_default_screen ( display );
    /// ***
    gtk_style_context_add_provider_for_screen   ( screen, GTK_STYLE_PROVIDER ( provider ), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );
    gtk_css_provider_load_from_file             ( provider, css_fp, &error );
    /// ***
}

struct message_struct {
    GtkWidget *input_str;
    GtkWidget *message_list_box;
};

#define SIZE 4
#define SIZE_C 5
#include <malloc/malloc.h>

void send(GtkWidget *button, gpointer input)
{   
    struct message_struct *temp = input;

    char *text = (char*)gtk_entry_get_text(GTK_ENTRY(temp->input_str));
    if(text) {
        GtkWidget *message = gtk_label_new(text);
        gtk_widget_set_name(message, "message");
        gtk_box_pack_start(GTK_BOX(temp->message_list_box), message, FALSE, FALSE, 5);
        gtk_widget_show_all(temp->message_list_box);
    }
}

int main(int argc, char *argv[]) {
    GtkWidget *window; // my window
    GtkWidget *main_box,*chats_list_box, *message_box, *input_box, *search_box, *chats_box; // Боксы 
    GtkWidget *input_key; // for imput_box
    GtkWidget *search_str, *search_key;
    char *messages[] = {"Hello", "mello", "tello", "pello"};
    char *chat_list[] = {"Kostya", "Vova", "Sergii", "Viktor", "Vlad"};
    GtkWidget *messages_label[SIZE], *chat_list_label[SIZE_C];
    GtkWidget *scrool_massages, *scrool_chats;

    struct message_struct *MessageInfo =  malloc(sizeof(struct message_struct));
    
 
    gtk_init(&argc, &argv);
    load_css();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MEMCAT CHAT");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // Сигнал для завершения преложения



// CREATE NEW THING
    input_key = gtk_button_new_with_label("SEND");
    MessageInfo->input_str = gtk_entry_new();

    search_key = gtk_button_new_with_label("SEARCH");
    search_str = gtk_entry_new();

    main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    chats_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    message_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    MessageInfo->message_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    search_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    chats_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    scrool_massages = gtk_scrolled_window_new(NULL, NULL); 
    scrool_chats = gtk_scrolled_window_new(NULL, NULL); 

    for (int i = 0; i < SIZE; i++)
        messages_label[i] = gtk_label_new(messages[i]);
    for (int i = 0; i < SIZE_C; i++)
        chat_list_label[i] = gtk_button_new_with_label(chat_list[i]);

    // END CREATE NEW THING


    //SETNAME
    gtk_widget_set_name(GTK_WIDGET(chats_box), "chats_box"); // SETNAME FOR CHATLIST BOX
    for (int i = 0; i < SIZE; i++)// SET NAME FOR MESSAGE
        gtk_widget_set_name(GTK_WIDGET(messages_label[i]), "message");
    for (int i = 0; i < SIZE_C; i++) // SET NAME FOR CHAT
        gtk_widget_set_name(GTK_WIDGET(chat_list_label[i]), "chat");
   // END SETNAME



// PACK ALL
    gtk_box_pack_start(GTK_BOX(main_box), chats_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), message_box, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(message_box), scrool_massages, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(message_box), input_box, FALSE, FALSE, 10);

    gtk_box_pack_start(GTK_BOX(input_box), MessageInfo->input_str, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(input_box), input_key, FALSE, FALSE, 2);

    gtk_box_pack_start(GTK_BOX(chats_box), search_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chats_box), scrool_chats, TRUE, TRUE, 5);

    gtk_box_pack_start(GTK_BOX(search_box), search_str, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(search_box), search_key, FALSE, FALSE, 0);

    for (int i = 0; i < SIZE; i++) // PACK MESSAGES
        gtk_box_pack_start(GTK_BOX(MessageInfo->message_list_box), messages_label[i], FALSE, FALSE, 5);
    for (int i = 0; i < SIZE_C; i++) // PACK CHAT_LIST
        gtk_box_pack_start(GTK_BOX(chats_list_box), chat_list_label[i], FALSE, FALSE, 1);
// END PACK

// CONTAIN ALL
    gtk_container_add(GTK_CONTAINER(scrool_massages), MessageInfo->message_list_box); 
    gtk_container_add(GTK_CONTAINER(scrool_chats), chats_list_box);
    gtk_container_add(GTK_CONTAINER(window), main_box);
// CONTAIN ALL END

    g_signal_connect(input_key, "clicked", G_CALLBACK (send), MessageInfo);

    gtk_widget_show_all(window);


    // SIGNAL
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // Сигнал для завершения преложения
    for(int i =0; i < SIZE_C; i++)
        g_signal_connect(G_OBJECT(chat_list_label[i]), "clicked", G_CALLBACK(key_test), NULL);
    //END SIGNAL
   // write(2,(char*)gtk_button_get_label (GTK_BUTTON(chat_list_label[0])), 6);



    gtk_main();

    return 0;
}