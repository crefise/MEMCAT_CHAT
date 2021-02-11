#include "../inc/header.h"



void select_chat(GtkWidget *button, gpointer data);




void scrolling()
{
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrool_massages));
    gtk_adjustment_set_page_size (adj, 0);
    double value = gtk_adjustment_get_upper(adj);
    gtk_adjustment_set_value(adj, value);
}

void main_menu() {
   
    GtkWidget *input_box;                           // Бокс для строки сообщений
    GtkWidget *input_str;                           // Вводимая строка
    GtkWidget *input_key;                           // Кнопка ввода

    GtkWidget *search_box;                          // Бокс для строки поиска
    GtkWidget *search_str;                          // Вводимая строка
    GtkWidget *search_key;                          // Кнопка ввода

    GtkWidget *scrool_chats;                        // Для скролла чатов
    GtkWidget *chats_box;                           // Бокс в котором храняться чаты



    GtkWidget* setting_str;                         // Бокс для верхней полоски настроек
    GtkWidget* home_key;                            // Кнопка домой (фаворит чат);
    GtkWidget* setting_key;                         // Кнопка настроек
    
    
    GtkWidget* main_menu_box;


    GdkPixbufAnimation* reconnect_animation_GIF;    // Для гиффки реконекта 
    GtkWidget* reconnect_animation_IMG;             // Картинка в которую будет загружена гиффка
    GtkWidget *reconect_label;                      // текст для реконекта

    GtkWidget *send_message_button_image;
    GtkWidget *search_key_image;

    
    gtk_init(NULL, NULL);
    load_css();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MEMCAT CHAT");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);




  // Прогружаем все чаты
  // Делаем запрос на сервер что нужны чаты конкретного пользователя
  // Сервер присылает все чаты и мы их пакуем
    FAVORITE_CHAT = mx_create_new_chat((char*)FAVORIDE_CHAT_DEFINE, -1);
    mx_download_all_chat(MY_CHATS);
    OPENED_DIALOG = strdup("Favorite");
    select_chat_on_off(FAVORITE_CHAT,'+'); // подсветка

    setting_str  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    setting_key = gtk_button_new_with_label("SETTINGS");

// CREATE NEW THING
    input_key = gtk_button_new();
    //input_key = gtk_button_new_with_label("SEND");
    input_str = gtk_entry_new();

    search_key = gtk_button_new();
    search_str = gtk_entry_new();

    main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    chats_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    message_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    search_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    chats_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);


    main_menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // сделать главное меню
    
    scrool_massages = gtk_scrolled_window_new(NULL, NULL); 
    scrool_chats = gtk_scrolled_window_new(NULL, NULL); 

    collocutor_name = gtk_label_new("Favorite");


    reconnect_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    reconect_label = gtk_label_new("Reconnecting....");

// END CREATE NEW THING

// DOWNLOAD IMG
send_message_button_image = gtk_image_new_from_file ("Client/img/send_img.png");
search_key_image = gtk_image_new_from_file ("Client/img/search_key_img.png");

// END DOWNLOAD IMG

reconnect_animation_GIF = gdk_pixbuf_animation_new_from_file ("Client/GIFS/reconnect.gif", NULL);
reconnect_animation_IMG = gtk_image_new();
gtk_image_set_from_animation (GTK_IMAGE(reconnect_animation_IMG), reconnect_animation_GIF);

//SETNAME
    gtk_widget_set_name(GTK_WIDGET(chats_box), "chats_box"); // SETNAME FOR CHATLIST BOX
    gtk_widget_set_name(GTK_WIDGET(message_box), "message_box");
    gtk_widget_set_name(GTK_WIDGET(setting_str), "setting_str");
    gtk_widget_set_name(GTK_WIDGET(setting_key), "main_menu_key");
    gtk_widget_set_name(GTK_WIDGET(collocutor_name), "collocutor_name");
    gtk_widget_set_name(GTK_WIDGET(input_key), "input_key");

    gtk_widget_set_name(GTK_WIDGET(send_message_button_image), "send_message_button_image");
    gtk_widget_set_name(GTK_WIDGET(input_str), "input_str");

    gtk_widget_set_name(GTK_WIDGET(search_key), "search_key");
    gtk_widget_set_name(GTK_WIDGET(search_str), "search_str");

    gtk_widget_set_name(GTK_WIDGET(reconect_label), "reconect_label");


//main_menu_box
// PACK ALL


    gtk_box_pack_start(GTK_BOX(main_menu_box), main_box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_menu_box), reconnect_widget, TRUE, TRUE, 0);

    gtk_box_pack_end(GTK_BOX(reconnect_widget), reconect_label, TRUE, TRUE, 0);

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

    gtk_box_pack_start(GTK_BOX(reconnect_widget), reconnect_animation_IMG, TRUE, TRUE, 0);


    //gtk_container_add(GTK_CONTAINER(window), reconnect_widget); 
    
// END PACK

// CONTAIN ALL
    CONTAINER = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Содержив в себе все чаты
    gtk_container_add(GTK_CONTAINER(CONTAINER), FAVORITE_CHAT->message_list_box);
    for(int i = 0; mx_get_index_chat(MY_CHATS, i) != NULL; i++) {
        gtk_container_add(GTK_CONTAINER(CONTAINER), mx_get_index_chat(MY_CHATS, i)->message_list_box); 
    }
    gtk_container_add(GTK_CONTAINER(scrool_massages), CONTAINER); 
    gtk_container_add(GTK_CONTAINER(scrool_chats), chats_list_box); // Загружаем чат(все сообщения)
    gtk_container_add(GTK_CONTAINER(window), main_menu_box);
    gtk_container_add(GTK_CONTAINER(input_key), send_message_button_image);
    gtk_container_add(GTK_CONTAINER(search_key), search_key_image);
    

// CONTAIN ALL END



    gtk_widget_show_all(window);
    gtk_widget_hide(reconnect_widget);

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