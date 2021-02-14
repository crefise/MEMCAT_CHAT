#include "../inc/header.h"

void logout(GtkWidget *button, gpointer data)
{
    gtk_widget_hide(window);
    gtk_widget_show_all(login_window);
}
 void edit_message(GtkWidget *btn, gpointer data)
 {
     if (ACTIVE_MESSAGE != NULL) {
        gtk_entry_set_text(GTK_ENTRY(data), gtk_button_get_label(GTK_BUTTON(ACTIVE_MESSAGE->key_label)));
     }

 }

 void delete_message(GtkWidget *btn, gpointer data)
 {

    gtk_widget_destroy(ACTIVE_MESSAGE->key_label);
    gtk_widget_destroy(ACTIVE_MESSAGE->data_label);

    gtk_widget_hide(edit->edit_key);
    gtk_widget_hide(edit->delete_key);
    gtk_widget_hide(edit->open_key);

    ACTIVE_MESSAGE = NULL;
    mx_printerrln("Deleting okay...");
 }

char *mx_take_name_from_path_file(char *temp) {
    int counter = 0;
    for (int i = strlen(temp) - 1; temp[i] != '/'; i--) {
        counter++;
    }
    char *result = mx_strnew(counter);
    result = strcpy(result, &temp[strlen(temp) - counter]);
    mx_printerrln("NAME : "); mx_printerrln(result);
    return result;
} 

void mx_select_file_to_send(GtkWidget *button, gpointer window) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Open File", window, action, ("_Cancel"), GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filepath = "";
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filepath = gtk_file_chooser_get_filename (chooser);

        char* filename = mx_take_name_from_path_file(filepath);

        char *will_send = ""; 
        will_send = concat(will_send, "find"); // findlogin/filename
        will_send = concat(will_send, mx_find_name_chat(MY_CHATS, OPENED_DIALOG)->name_chat);
        will_send = concat(will_send, "/");
        will_send = concat(will_send, filename);
        if (send(sock, will_send, strlen(will_send), 0) == -1)
            return;

        mx_send_file(sock, filepath);
        mx_strdel(&will_send);
        g_free (filepath);
    }

    gtk_widget_destroy (dialog);
}

MESSAGE_T* ACTIVE_MESSAGE = NULL;
void main_menu(GtkWidget *login_window) {
   
    GtkWidget *input_box;                           // Бокс для строки сообщений
    GtkWidget *input_str;                           // Вводимая строка
    GtkWidget *input_key;                           // Кнопка ввода
    GtkWidget *send_file_key;                       // Кнопка send file
    GtkWidget *send_file_button_image;
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

    edit = malloc(sizeof(struct edit_struct));
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
    mx_printerrln("test okay...");


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
    send_file_key = gtk_button_new();

    setting_str  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    setting_key = gtk_button_new();

    edit->edit_key = gtk_button_new_with_label("Edit");
    edit->delete_key = gtk_button_new_with_label("Delete");
    edit->open_key = gtk_button_new_with_label("Open");




   mx_printerrln("test okay1...");
        /*  (КОНЕЦ)Инициализация обьектов для чата */


        /*  Загрузка медиа */
    settings_key_IMG = gtk_image_new_from_file ("Client/img/setting_img.png");
    home_key_IMG = gtk_image_new_from_file ("Client/img/home_img.png");
    
    send_message_button_image = gtk_image_new_from_file ("Client/img/send_img.png");
    search_key_image = gtk_image_new_from_file ("Client/img/search_img.png");

    reconnect_animation_GIF = gdk_pixbuf_animation_new_from_file ("Client/GIFS/reconnect.gif", NULL);

    send_file_button_image = gtk_image_new_from_file ("Client/img/13456.png");

    reconnect_animation_IMG = gtk_image_new();
    gtk_image_set_from_animation (GTK_IMAGE(reconnect_animation_IMG), reconnect_animation_GIF);

        /*  (Конец)Загрузка медиа */

   mx_printerrln("test okay2...");


        /* Присваивания имен */

    gtk_widget_set_name(GTK_WIDGET(chats_box), "chats_box"); 
    gtk_widget_set_name(GTK_WIDGET(message_box), "message_box");

    gtk_widget_set_name(GTK_WIDGET(setting_str), "setting_str");
    gtk_widget_set_name(GTK_WIDGET(setting_key), "main_menu_key");



    gtk_widget_set_name(GTK_WIDGET(input_box), "input_box");
    gtk_widget_set_name(GTK_WIDGET(input_str), "input_str");
    gtk_widget_set_name(GTK_WIDGET(input_key), "input_key");
    gtk_widget_set_name(GTK_WIDGET(send_message_button_image), "send_message_button_image");
    gtk_widget_set_name(GTK_WIDGET(send_file_key), "send_file_key");

    gtk_widget_set_name(GTK_WIDGET(search_box), "search_box");
    gtk_widget_set_name(GTK_WIDGET(search_key), "search_key");
    gtk_widget_set_name(GTK_WIDGET(search_str), "search_str");

    gtk_widget_set_name(GTK_WIDGET(reconect_label), "reconect_label");

    gtk_widget_set_name(GTK_WIDGET(main_menu_box), "main_menu_box");

 
    
    
        /* (Конец)Присваивания имен */

   mx_printerrln("test okay3...");

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
    gtk_box_pack_start(GTK_BOX(input_box), send_file_key, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(input_box), input_key, FALSE, FALSE, 0);


    gtk_box_pack_start(GTK_BOX(chats_box), search_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chats_box), scrool_chats, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(search_box), search_str, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(search_box), search_key, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(setting_str), FAVORITE_CHAT->chat_button, FALSE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(setting_str), setting_key, FALSE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(setting_str), edit->edit_key, FALSE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(setting_str), edit->delete_key, FALSE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(setting_str), edit->open_key, FALSE, TRUE, 5);

    for (int i = 0; mx_get_index_chat(MY_CHATS,i) != NULL; i++) {
        gtk_box_pack_start(GTK_BOX(chats_list_box), mx_get_index_chat(MY_CHATS,i)->chat_button, FALSE, FALSE, 1); // Пакуем все чаты
    }

    gtk_box_pack_start(GTK_BOX(reconnect_widget), reconnect_animation_IMG, TRUE, TRUE, 0);

         /* (Конец)Пакуем обьекты */

   mx_printerrln("test okay4...");

        /* Containing */
        gtk_widget_set_halign(scrool_massages,GTK_ALIGN_FILL);

    CONTAINER = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);                               // Содержит в себе все чаты
   for(int i = 0; mx_get_index_chat(MY_CHATS, i) != NULL; i++) 
        gtk_container_add(GTK_CONTAINER(CONTAINER), mx_get_index_chat(MY_CHATS, i)->message_box); 
          // gtk_widget_set_name(GTK_WIDGET(CONTAINER), "scrool_massages");
    
    gtk_container_add(GTK_CONTAINER(scrool_massages), CONTAINER); 
    gtk_container_add(GTK_CONTAINER(scrool_chats), chats_list_box); // Загружаем чат(все сообщения)
    gtk_container_add(GTK_CONTAINER(window), main_menu_box);
    gtk_container_add(GTK_CONTAINER(input_key), send_message_button_image);
    gtk_container_add(GTK_CONTAINER(search_key), search_key_image);
    gtk_container_add(GTK_CONTAINER(FAVORITE_CHAT->chat_button), home_key_IMG);
    gtk_container_add(GTK_CONTAINER(setting_key), settings_key_IMG);
    gtk_container_add(GTK_CONTAINER(send_file_key),send_file_button_image);
   
        /* (END)Containing */
   mx_printerrln("test okay5...");

    gtk_widget_show_all(window);
    
    gtk_widget_hide(edit->edit_key);
    gtk_widget_hide(edit->delete_key);
    gtk_widget_hide(reconnect_widget);
    gtk_widget_hide(edit->open_key);

        /* Проверка сигналов */
    g_signal_connect(input_key, "clicked", G_CALLBACK (mx_send_message), input_str);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // Сигнал для завершения преложения
    g_signal_connect(setting_key, "clicked", G_CALLBACK (logout), NULL);

    for(int i =0; mx_get_index_chat(MY_CHATS,i); i++)
        g_signal_connect(G_OBJECT(mx_get_index_chat(MY_CHATS,i)->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)mx_get_index_chat(MY_CHATS,i));
    
    g_signal_connect(G_OBJECT(send_file_key), "clicked", G_CALLBACK(mx_select_file_to_send), (gpointer)window);
    g_signal_connect(G_OBJECT(FAVORITE_CHAT->chat_button), "clicked", G_CALLBACK(select_chat), (gpointer)FAVORITE_CHAT);    
    g_signal_connect(G_OBJECT(search_key), "clicked", G_CALLBACK(mx_search_dialog), (gpointer)search_str);
    g_signal_connect(G_OBJECT(edit->edit_key), "clicked", G_CALLBACK(edit_message), (gpointer)input_str);
    g_signal_connect(G_OBJECT(edit->delete_key), "clicked", G_CALLBACK(delete_message), NULL);
          /* (Конец)Проверка сигналов */
   mx_printerrln("test okay6...");
    gtk_main();
  exit(0);
}
