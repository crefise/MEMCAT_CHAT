
#include "header.h"



char *OPENED_DIALOG; // Нужна для отслеживания открытого диалоги
#define SIZE 4
#define SIZE_C 2

    CHAT_T *MY_CHATS = NULL;

    GtkWidget *window; // my window
    GtkWidget *main_box,*chats_list_box,  *message_list_box, *message_box, *input_box, *search_box, *chats_box; // Боксы 
    GtkWidget *input_str, *input_key; // for imput_box
    GtkWidget *search_str, *search_key;
    GtkWidget *dialog;


void select_chat(GtkWidget *button, gpointer data) {
    CHAT_T *used_chat = data;
    char *chat_name  = strdup((char*)gtk_button_get_label (GTK_BUTTON(button)));
    mx_fill_message_list_box(&used_chat, used_chat->name_chat);


    GtkWidget *will_hide = mx_find_name_chat(MY_CHATS, OPENED_DIALOG)->message_list_box;
    GtkWidget *will_show = used_chat->message_list_box;

    OPENED_DIALOG = strdup(used_chat->name_chat);

    gtk_widget_hide(will_hide);
    gtk_widget_show_all(will_show);
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

//////////////////////////////////////////////////////////////////////////////////////////////// VIKTOR
struct message_struct {
    GtkWidget *input_str;
    GtkWidget *message_list_box;
};



void send(GtkWidget *button, gpointer input)
{   
    struct message_struct *messages = input;

    char *text = (char*)gtk_entry_get_text(GTK_ENTRY(messages->input_str));
    if(text && strlen(text)) {
        GtkWidget *message = gtk_label_new(text);
        gtk_widget_set_name(message, "message");
        gtk_box_pack_start(GTK_BOX(messages->message_list_box), message, FALSE, FALSE, 5);
        gtk_widget_show_all(messages->message_list_box);
        gtk_entry_set_text(GTK_ENTRY(messages->input_str), "");
    }
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////



int main(int argc, char *argv[]) {
    GtkWidget *window; // my window
    GtkWidget *main_box,*chats_list_box, *message_box, *input_box, *search_box, *chats_box; // Боксы 
    GtkWidget *input_key; // for imput_box
    GtkWidget *search_str, *search_key;
    char *messages[] = {"Hello", "mello", "tello", "pello"};
    char *chat_list[] = {"Kostya", "Vova", "Sergii", "Viktor", "Vlad"};
    GtkWidget *messages_label[SIZE], *chat_list_label[SIZE_C];
    GtkWidget *scrool_massages, *scrool_chats;


    
 
 
    gtk_init(&argc, &argv);
    load_css();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MEMCAT CHAT");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // Сигнал для завершения преложения

    struct message_struct *MessageInfo =  malloc(sizeof(struct message_struct));

    MY_CHATS = mx_create_new_chat((char*)"Vladimir");
    mx_add_new_chat(&MY_CHATS,"Viktor");

    OPENED_DIALOG = strdup("NONE"); 


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
// END CREATE NEW THING


//SETNAME
    gtk_widget_set_name(GTK_WIDGET(chats_box), "chats_box"); // SETNAME FOR CHATLIST BOX



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

    for (int i = 0; mx_get_index_chat(MY_CHATS,i) != NULL; i++) {
        gtk_box_pack_start(GTK_BOX(chats_list_box), mx_get_index_chat(MY_CHATS,i)->chat_button, FALSE, FALSE, 1); // Пакуем все чаты
    }
// END PACK

// CONTAIN ALL
    GtkWidget *CONTAINER = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Содержив в себе все чаты
    for(int i = 0; mx_get_index_chat(MY_CHATS, i) != NULL; i++) {
    gtk_container_add(GTK_CONTAINER(CONTAINER), mx_get_index_chat(MY_CHATS, i)->message_list_box); 
    }
    gtk_container_add(GTK_CONTAINER(scrool_massages), CONTAINER); 
    gtk_container_add(GTK_CONTAINER(scrool_chats), chats_list_box); // Загружаем чат(все сообщения)
    gtk_container_add(GTK_CONTAINER(window), main_box);
// CONTAIN ALL END



 
   gtk_widget_show_all(window);

// SIGNAL
    g_signal_connect(input_key, "clicked", G_CALLBACK (send), MessageInfo);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // Сигнал для завершения преложения
    for(int i =0; i < SIZE_C; i++)
       g_signal_connect(G_OBJECT(mx_get_index_chat(MY_CHATS,i)->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)mx_get_index_chat(MY_CHATS,i));
//END SIGNAL




    gtk_main();

    return 0;
}