#include "../inc/header.h"


void download_all_chat(CHAT_T* chats) {
    PAUSE = 1;
    char *buffer = concat(concat("dialogs[", USER_LOGIN), "]");
    printf("Download all chat: buffer = %s\n", buffer);
    if (send(sock, buffer, strlen(buffer), 0) == -1) { // send data to server
        write(2, "SERVER DONT CONNETCTED\n",23);
    } 

    mx_strdel(&buffer);
    buffer = mx_strnew(256);

    if (recv(sock, &buffer[0], 256, 0) == 0) {
        mx_printerr("ERROR SERVER CONNECTIONS (download all chat)\n");
    }




    printf("Client got: buffer = %s\n", buffer);
    if (strcmp(buffer, "-") == 0) {
        mx_printerr("NULL CHATS");
        PAUSE = 0;
        return;
    }
    else {
        mx_ps_off_chat_message(buffer);
    }
    PAUSE = 0;
}




void select_chat(GtkWidget *button, gpointer data);

GtkWidget *chats_list_box = NULL;
GtkWidget *CONTAINER = NULL;
GtkWidget *window; // my window
char *OPENED_DIALOG;

#define SIZE 4
#define SIZE_C 2
#define FAVORIDE_CHAT_DEFINE "Favorite"

    CHAT_T *MY_CHATS = NULL;
    CHAT_T *FAVORITE_CHAT = NULL;
    GtkWidget *collocutor_name = NULL;


void scrolling()
{
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrool_massages));
    gtk_adjustment_set_page_size (adj, 0);
    double value = gtk_adjustment_get_upper(adj);
    gtk_adjustment_set_value(adj, value);
}


void main_menu() {
   
    GtkWidget *main_box, *message_box, *input_box, *search_box, *chats_box; // Боксы 
    GtkWidget *input_key, *input_str;// for imput_box
    GtkWidget *search_str, *search_key;
    GtkWidget *messages_label[SIZE], *chat_list_label[SIZE_C];
    GtkWidget *scrool_chats;
    GtkWidget* setting_str, *home_key, *setting_key; // верхняя полоска настроек
    GtkWidget* search_chat_box;
    GtkWidget* main_menu_box;


    GtkWidget *send_message_button_image;
    
 
 
    gtk_init(NULL, NULL);
    load_css();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MEMCAT CHAT");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);




  // Прогружаем все чаты
  // Делаем запрос на сервер что нужны чаты конкретного пользователя
  // Сервер присылает все чаты и мы их пакуем
    FAVORITE_CHAT = mx_create_new_chat((char*)FAVORIDE_CHAT_DEFINE, -1);
    download_all_chat(MY_CHATS);
    OPENED_DIALOG = strdup("Favorite");
    select_chat_on_off(FAVORITE_CHAT,'+'); // подсветка

    setting_str  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    setting_key = gtk_button_new_with_label("SETTINGS");

// CREATE NEW THING
    input_key = gtk_button_new();
    //input_key = gtk_button_new_with_label("SEND");
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

// DOWNLOAD IMG
send_message_button_image = gtk_image_new_from_file ("Client/img/send_img.jpg");

// END DOWNLOAD IMG




//SETNAME
    gtk_widget_set_name(GTK_WIDGET(chats_box), "chats_box"); // SETNAME FOR CHATLIST BOX
    gtk_widget_set_name(GTK_WIDGET(setting_str), "setting_str");
    gtk_widget_set_name(GTK_WIDGET(setting_key), "main_menu_key");
    gtk_widget_set_name(GTK_WIDGET(collocutor_name), "collocutor_name");
    gtk_widget_set_name(GTK_WIDGET(input_key), "input_key");


// PACK ALL
    gtk_box_pack_start(GTK_BOX(main_box), chats_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), message_box, TRUE, TRUE, 0);


    gtk_box_pack_start(GTK_BOX(message_box), setting_str, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(message_box), scrool_massages, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(message_box), input_box, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(input_box), input_str, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(input_box), input_key, FALSE, FALSE, 0);

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
    CONTAINER = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Содержив в себе все чаты
    gtk_container_add(GTK_CONTAINER(CONTAINER), FAVORITE_CHAT->message_list_box);
    for(int i = 0; mx_get_index_chat(MY_CHATS, i) != NULL; i++) {
        gtk_container_add(GTK_CONTAINER(CONTAINER), mx_get_index_chat(MY_CHATS, i)->message_list_box); 
    }
    gtk_container_add(GTK_CONTAINER(scrool_massages), CONTAINER); 
    gtk_container_add(GTK_CONTAINER(scrool_chats), chats_list_box); // Загружаем чат(все сообщения)
    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_container_add(GTK_CONTAINER(input_key), send_message_button_image);

// CONTAIN ALL END


 
   gtk_widget_show_all(window);


// SIGNAL
    g_signal_connect(input_key, "clicked", G_CALLBACK (mx_send_message), input_str);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // Сигнал для завершения преложения
    for(int i =0; mx_get_index_chat(MY_CHATS,i); i++)
      g_signal_connect(G_OBJECT(mx_get_index_chat(MY_CHATS,i)->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)mx_get_index_chat(MY_CHATS,i));
    
    g_signal_connect(G_OBJECT(FAVORITE_CHAT->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)FAVORITE_CHAT);    
    g_signal_connect(G_OBJECT(search_key), "clicked", G_CALLBACK(mx_search_dialog), (gpointer)search_str);
//END SIGNAL




    gtk_main();

    return ;
}