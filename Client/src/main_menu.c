#include "../inc/header.h"











void main_menu() {
   
    GtkWidget *input_box;                           // Бокс для строки сообщений
    GtkWidget *input_str;                           // Вводимая строка
    GtkWidget *input_key;                           // Кнопка ввода
    GtkWidget *send_message_button_image;           // Картинка для кнопки ввода

    GtkWidget *search_box;                          // Бокс для строки поиска
    GtkWidget *search_str;                          // Вводимая строка
    GtkWidget *search_key;                          // Кнопка ввода
    GtkWidget *search_key_image;                    // Картинка для кнопки поиска

    GtkWidget *scrool_chats;                        // Для скролла чатов
    GtkWidget *chats_box;                           // Бокс в котором храняться чаты



    GtkWidget* setting_str;                         // Бокс для верхней полоски настроек
    GtkWidget* home_key;                            // Кнопка домой (фаворит чат);
    GtkWidget* setting_key;                         // Кнопка настроек
    GtkWidget* home_key_IMG;                        // Картинка для кнопки
    GtkWidget* settings_key_IMG;                    // Картинка для кнопки настроек
    
    GtkWidget* main_menu_box;                       // Бокс в котором хранятся реконект и основное меню


    GdkPixbufAnimation* reconnect_animation_GIF;    // Для гиффки реконекта 
    GtkWidget* reconnect_animation_IMG;             // Картинка в которую будет загружена гиффка
    GtkWidget *reconect_label;                      // текст для реконекта


 
    gtk_init(NULL, NULL);
    load_css();                                     // Подгружаем CSS
    
                /* Инициализация окна */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MEMCAT CHAT");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);



    FAVORITE_CHAT = mx_create_new_chat((char*)FAVORITE_CHAT_DEFINE, -1);        // Создания главного чата (фаворит)
    OPENED_DIALOG = strdup(FAVORITE_CHAT_DEFINE);
    select_chat_on_off(FAVORITE_CHAT,'+');                                      // Делаем подсветку чата

    mx_download_all_chat(MY_CHATS);                                             // Загружаем все чаты пользователя



            /* Инициализация обьектов для чата */

    main_menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); 

    main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    reconnect_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    reconect_label = gtk_label_new("Reconnecting....");

    chats_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    message_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    scrool_massages = gtk_scrolled_window_new(NULL, NULL); 
    scrool_chats = gtk_scrolled_window_new(NULL, NULL); 

    chats_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    search_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    search_key = gtk_button_new();
    search_str = gtk_entry_new();

    input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    input_key = gtk_button_new();
    input_str = gtk_entry_new();

    setting_str  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    setting_key = gtk_button_new();


        /*  (КОНЕЦ)Инициализация обьектов для чата */


        /*  Загрузка медиа */
    settings_key_IMG = gtk_image_new_from_file ("Client/img/home_img.png");
    home_key_IMG = gtk_image_new_from_file ("Client/img/home_img.png");
    
    send_message_button_image = gtk_image_new_from_file ("Client/img/send_img.png");
    search_key_image = gtk_image_new_from_file ("Client/img/search_key_img.png");

    reconnect_animation_GIF = gdk_pixbuf_animation_new_from_file ("Client/GIFS/reconnect.gif", NULL);

    reconnect_animation_IMG = gtk_image_new();
    gtk_image_set_from_animation (GTK_IMAGE(reconnect_animation_IMG), reconnect_animation_GIF);

        /*  (Конец)Загрузка медиа */




        /* Присваивания имен */

    gtk_widget_set_name(GTK_WIDGET(chats_box), "chats_box"); 
    gtk_widget_set_name(GTK_WIDGET(message_box), "message_box");

    gtk_widget_set_name(GTK_WIDGET(setting_str), "setting_str");
    gtk_widget_set_name(GTK_WIDGET(setting_key), "main_menu_key");



    gtk_widget_set_name(GTK_WIDGET(input_box), "input_box");
    gtk_widget_set_name(GTK_WIDGET(input_str), "input_str");
    gtk_widget_set_name(GTK_WIDGET(input_key), "input_key");
    gtk_widget_set_name(GTK_WIDGET(send_message_button_image), "send_message_button_image");

    gtk_widget_set_name(GTK_WIDGET(search_box), "search_box");
    gtk_widget_set_name(GTK_WIDGET(search_key), "search_key");
    gtk_widget_set_name(GTK_WIDGET(search_str), "search_str");

    gtk_widget_set_name(GTK_WIDGET(reconect_label), "reconect_label");

    gtk_widget_set_name(GTK_WIDGET(main_menu_box), "main_menu_box");
    

        /* (Конец)Присваивания имен */



        /* Пакуем обьекты */
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

    for (int i = 0; mx_get_index_chat(MY_CHATS,i) != NULL; i++) {
        gtk_box_pack_start(GTK_BOX(chats_list_box), mx_get_index_chat(MY_CHATS,i)->chat_button, FALSE, FALSE, 1); // Пакуем все чаты
    }

    gtk_box_pack_start(GTK_BOX(reconnect_widget), reconnect_animation_IMG, TRUE, TRUE, 0);

         /* (Конец)Пакуем обьекты */



        /* Containing */
    CONTAINER = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);                               // Содержит в себе все чаты

    
    for(int i = 0; mx_get_index_chat(MY_CHATS, i) != NULL; i++) 
        gtk_container_add(GTK_CONTAINER(CONTAINER), mx_get_index_chat(MY_CHATS, i)->message_list_box); 
    
    gtk_container_add(GTK_CONTAINER(scrool_massages), CONTAINER); 
    gtk_container_add(GTK_CONTAINER(scrool_chats), chats_list_box); // Загружаем чат(все сообщения)
    gtk_container_add(GTK_CONTAINER(window), main_menu_box);
    gtk_container_add(GTK_CONTAINER(input_key), send_message_button_image);
    gtk_container_add(GTK_CONTAINER(search_key), search_key_image);
    gtk_container_add(GTK_CONTAINER(FAVORITE_CHAT->chat_button), home_key_IMG);
    gtk_container_add(GTK_CONTAINER(setting_key), settings_key_IMG);
    
   
        /* (END)Containing */



    gtk_widget_show_all(window);
    gtk_widget_hide(reconnect_widget);

        /* Проверка сигналов */
    g_signal_connect(input_key, "clicked", G_CALLBACK (mx_send_message), input_str);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // Сигнал для завершения преложения

    for(int i =0; mx_get_index_chat(MY_CHATS,i); i++)
        g_signal_connect(G_OBJECT(mx_get_index_chat(MY_CHATS,i)->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)mx_get_index_chat(MY_CHATS,i));
    
    g_signal_connect(G_OBJECT(FAVORITE_CHAT->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)FAVORITE_CHAT);    
    g_signal_connect(G_OBJECT(search_key), "clicked", G_CALLBACK(mx_search_dialog), (gpointer)search_str);
          /* (Конец)Проверка сигналов */

    gtk_main();
  exit(0);
}
