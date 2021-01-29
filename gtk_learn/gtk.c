
#include "header.h"
char *OPENED_DIALOG;
#define SIZE 4
#define SIZE_C 2
#define FAVORIDE_CHAT_DEFINE "Favorite"
    CHAT_T *MY_CHATS = NULL;
    CHAT_T *FAVORITE_CHAT = NULL;
    GtkWidget *collocutor_name = NULL;





void select_chat(GtkWidget *button, gpointer data) {
    CHAT_T *used_chat = data;
    if (strcmp(used_chat->name_chat, OPENED_DIALOG) == 0) { // Если мы кликнулы на тот диалог что у нас уже открыт
        return;
    }
    GtkWidget *will_hide; 
    if (strcmp(FAVORIDE_CHAT_DEFINE, OPENED_DIALOG) == 0) { // Если открытый чат это сохраненки
        will_hide = FAVORITE_CHAT->message_list_box;
        select_chat_on_off(FAVORITE_CHAT,'-'); // подсветка
    }
    else {
        will_hide = mx_find_name_chat(MY_CHATS, OPENED_DIALOG)->message_list_box;
        select_chat_on_off(mx_find_name_chat(MY_CHATS,OPENED_DIALOG),'-'); // подсветка
    }
     GtkWidget *will_show = used_chat->message_list_box;

    OPENED_DIALOG = strdup(used_chat->name_chat);
    gtk_label_set_text(GTK_LABEL(collocutor_name), OPENED_DIALOG); // Имя для собеседника
    select_chat_on_off(used_chat,'+'); // подсветка

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



void send_message(GtkWidget *button, gpointer data) {   
    //struct message_struct *messages = input;
    GtkWidget *input_str = data;
    CHAT_T *used_chat = NULL;
    if (strcmp(OPENED_DIALOG, FAVORIDE_CHAT_DEFINE) == 0) {
        used_chat = FAVORITE_CHAT; 
    }
    else {
        used_chat = mx_find_name_chat(MY_CHATS, OPENED_DIALOG);
    }

    char *text = (char*)gtk_entry_get_text(GTK_ENTRY(input_str));
    if(text && strlen(text) > 0) {
        mx_fill_message_list_box(&used_chat,OPENED_DIALOG, "TESTING", text);
        gtk_entry_set_text(GTK_ENTRY(input_str), "");
    }
    mx_update_used_chat(used_chat);
    
}

int main(int argc, char *argv[]) {
    GtkWidget *window; // my window
    GtkWidget *main_box,*chats_list_box, *message_box, *input_box, *search_box, *chats_box; // Боксы 
    GtkWidget *input_key, *input_str;// for imput_box
    GtkWidget *search_str, *search_key;
    GtkWidget *messages_label[SIZE], *chat_list_label[SIZE_C];
    GtkWidget *scrool_massages, *scrool_chats;
    GtkWidget* setting_str, *home_key, *setting_key; // верхняя полоска настроек
    GtkWidget* search_chat_box;
    GtkWidget* main_menu_box;

    
 
 
    gtk_init(&argc, &argv);
    load_css();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MEMCAT CHAT");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);






    FAVORITE_CHAT = mx_create_new_chat((char*)FAVORIDE_CHAT_DEFINE);


    mx_add_new_chat(&MY_CHATS,"Vladimir");
    mx_add_new_chat(&MY_CHATS,"Viktor");
    mx_add_new_chat(&MY_CHATS,"Vlad");
    mx_add_new_chat(&MY_CHATS,"Kostya");
    mx_add_new_chat(&MY_CHATS,"Sergei");

    OPENED_DIALOG = strdup("Favorite");
    select_chat_on_off(FAVORITE_CHAT,'+'); // подсветка

    setting_str  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    setting_key = gtk_button_new_with_label("SETTINGS");


// CREATE NEW THING
    input_key = gtk_button_new_with_label("SEND");
    input_str = gtk_entry_new();

    search_key = gtk_button_new_with_label("SEARCH");
    search_str = gtk_entry_new();

    main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    chats_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    message_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    search_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    chats_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    search_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Сделать поиск боксов
    main_menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // сделать главное меню
    
    scrool_massages = gtk_scrolled_window_new(NULL, NULL); 
    scrool_chats = gtk_scrolled_window_new(NULL, NULL); 

    collocutor_name = gtk_label_new("Favorite");

// END CREATE NEW THING


//SETNAME
    gtk_widget_set_name(GTK_WIDGET(chats_box), "chats_box"); // SETNAME FOR CHATLIST BOX
    gtk_widget_set_name(GTK_WIDGET(setting_str), "setting_str");
    gtk_widget_set_name(GTK_WIDGET(setting_key), "main_menu_key");
    gtk_widget_set_name(GTK_WIDGET(collocutor_name), "collocutor_name");


// PACK ALL
    gtk_box_pack_start(GTK_BOX(main_box), chats_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), message_box, TRUE, TRUE, 0);


    gtk_box_pack_start(GTK_BOX(message_box), setting_str, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(message_box), scrool_massages, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(message_box), input_box, FALSE, FALSE, 10);

    gtk_box_pack_start(GTK_BOX(input_box), input_str, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(input_box), input_key, FALSE, FALSE, 2);

    gtk_box_pack_start(GTK_BOX(chats_box), search_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chats_box), scrool_chats, TRUE, TRUE, 5);

    gtk_box_pack_start(GTK_BOX(search_box), search_str, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(search_box), search_key, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(setting_str), FAVORITE_CHAT->chat_button, FALSE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(setting_str), setting_key, FALSE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(setting_str), collocutor_name, TRUE, TRUE, 5);

    for (int i = 0; mx_get_index_chat(MY_CHATS,i) != NULL; i++) {
        gtk_box_pack_start(GTK_BOX(chats_list_box), mx_get_index_chat(MY_CHATS,i)->chat_button, FALSE, FALSE, 1); // Пакуем все чаты
    }
// END PACK

// CONTAIN ALL
    GtkWidget *CONTAINER = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Содержив в себе все чаты
    gtk_container_add(GTK_CONTAINER(CONTAINER), FAVORITE_CHAT->message_list_box);
    for(int i = 0; mx_get_index_chat(MY_CHATS, i) != NULL; i++) {
        gtk_container_add(GTK_CONTAINER(CONTAINER), mx_get_index_chat(MY_CHATS, i)->message_list_box); 
    }
    gtk_container_add(GTK_CONTAINER(scrool_massages), CONTAINER); 
    gtk_container_add(GTK_CONTAINER(scrool_chats), chats_list_box); // Загружаем чат(все сообщения)
    gtk_container_add(GTK_CONTAINER(window), main_box);
// CONTAIN ALL END



 
   gtk_widget_show_all(window);


// SIGNAL
    g_signal_connect(input_key, "clicked", G_CALLBACK (send_message), input_str);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // Сигнал для завершения преложения
    for(int i =0; mx_get_index_chat(MY_CHATS,i); i++)
    g_signal_connect(G_OBJECT(mx_get_index_chat(MY_CHATS,i)->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)mx_get_index_chat(MY_CHATS,i));
    g_signal_connect(G_OBJECT(FAVORITE_CHAT->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)FAVORITE_CHAT);
//END SIGNAL




    gtk_main();

    return 0;
}