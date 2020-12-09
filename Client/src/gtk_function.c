#include "../inc/header.h"
//#define test_cout
char *login;
char *password;

void visible_pasword(GtkWidget *button, gpointer password_entry) {
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), !gtk_entry_get_visibility(password_entry));
}

void login_connect(GtkWidget *button, gpointer data) {
    struct user_info *temp = data;
    login = (char*) gtk_entry_get_text(GTK_ENTRY(temp->username_entry));
    password = (char*) gtk_entry_get_text(GTK_ENTRY(temp->password_entry));
    #ifdef test_cout
    write(2,"LOGIN CHECK:\n", 16);
    write(2,login, strlen(login));
    write(2,"\n",1);
    write(2,password, strlen(password));
    write(2,"\n",1);
    write(2,"\n",1);
    write(2,"\n",1);

    
    #endif
    
    char *str = concat((char*)"login[", (char*)i_to_s(strlen(login)));
    str = concat(str, "][");
    str = concat(str, (char*)i_to_s(strlen(password)));
    str = concat(str, "]");
    str = concat(str,login);
    str = concat(str,password);

    send(sock, str, strlen(str), 0); // send data to server
    close(sock);
}

void register_connect(GtkWidget *button, gpointer data) {
    struct user_info *temp = data;
    login = (char*) gtk_entry_get_text(GTK_ENTRY(temp->username_entry));
    password = (char*) gtk_entry_get_text(GTK_ENTRY(temp->password_entry));
    char *password_repeat = (char*) gtk_entry_get_text(GTK_ENTRY(temp->password_entry_repeat));
    #ifdef test_cout
    write(2,"REGISTER CHECK:\n", 16);
    write(2,login, strlen(login));
    write(2,"\n",1);
    write(2,password, strlen(password));
    write(2,"\n",1);
    write(2,password_repeat, strlen(password_repeat));
    write(2,"\n",1);
    write(2,"\n",1);
    write(2,"\n",1);
    #endif
    if (strcmp(password, password_repeat) != 0) {
        #ifdef test_cout
        write(2, "\nPASS REPEAT ERROR\n",19);
        #endif
    }
    else {
        #ifdef test_cout
        write(2, "\nPASS REPEAT OKAY\n",18);
        #endif
        // SEND INFO TO SERVER
    }
}

void go_to_log(GtkWidget *button, gpointer window1) {
    gtk_widget_hide(window1);
    main_loop();
}

void reg_window(GtkWidget *button, gpointer window) {
    struct user_info *user_login_info = malloc(sizeof(struct user_info));
    GtkWidget *window1;
    GtkWidget *username_label;// *username_entry;
    GtkWidget *password_label, *password_label1; //*password_entry, *password_entry1;
    GtkWidget *hbox1, *hbox2, *hbox3, *hbox4;
    GtkWidget *vbox;
    GtkWidget *exit, *reg_button;

    window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (GTK_WINDOW (window1), "MEMCAT(ˆ_ˆ)");
    gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window1), 500, 200);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
 
    // Создаем ярлык и поле ввода логина
    username_label = gtk_label_new("Введите логин:");
    user_login_info->username_entry = gtk_entry_new();
 
    // Создаем ярлык и поле ввода пароля
    password_label = gtk_label_new("Введите пароль:");
    user_login_info->password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(user_login_info->password_entry), FALSE);//видимость пароля

    password_label1 = gtk_label_new("Повторите пароль:");
    user_login_info->password_entry_repeat = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(user_login_info->password_entry_repeat), FALSE);

    reg_button = gtk_button_new_with_label("Зарегистрироваться");
    exit = gtk_button_new_with_label("Ввойти");
 
    //добавили в первую коробку username_label и username_entry и в основную коробку добавили первую
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox1), username_label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), user_login_info->username_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, FALSE, 5);
 
    //сделали также для пароля
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), password_label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), user_login_info->password_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, FALSE, 5);

    hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox3), password_label1, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox3), user_login_info->password_entry_repeat, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox3, TRUE, FALSE, 5);

    hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox4), reg_button, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox4), exit, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox4, TRUE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window1), vbox);

    gtk_widget_hide(window);

    g_signal_connect(G_OBJECT(reg_button), "clicked", G_CALLBACK(register_connect), user_login_info);
    g_signal_connect(G_OBJECT(exit), "clicked", G_CALLBACK(go_to_log), window1);
    g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window1);

}

void main_loop() {

    struct user_info *user_login_info = malloc(sizeof(struct user_info));
    GtkWidget *window;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *hbox1, *hbox2, *hbox3;
    GtkWidget *vbox;
    GtkWidget *login_button, *reg_button;
    GtkWidget *checkbutton;

    //for_test = malloc(sizeof(struct test*));

    bool visible = false;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 
    gtk_window_set_title (GTK_WINDOW (window), "MEMCAT(ˆ_ˆ)");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
 
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
 
    // Создаем ярлык и поле ввода логина
    username_label = gtk_label_new("Введите логин:");
    user_login_info->username_entry  = gtk_entry_new();
 
    // Создаем ярлык и поле ввода пароля
    password_label = gtk_label_new("Введите пароль:");
     user_login_info->password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY( user_login_info->password_entry), visible);//видимость пароля
    
    //кнопки
    login_button = gtk_button_new_with_label("Авторизоваться");
    reg_button = gtk_button_new_with_label("Зарегистрироваться");
    checkbutton = gtk_check_button_new_with_label ("Показать пароль");

     //добавили в первую коробку username_label и username_entry и в основную коробку добавили первую
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox1), username_label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), user_login_info->username_entry , TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, FALSE, 5);
 
    //сделали также для пароля
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), password_label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox2),  user_login_info->password_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, FALSE, 5);

    hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(vbox), checkbutton);
    gtk_box_pack_start(GTK_BOX(hbox3), login_button, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox3), reg_button, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox3, TRUE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    g_signal_connect(G_OBJECT(reg_button), "clicked", G_CALLBACK(reg_window), window);
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(login_connect), user_login_info );
    g_signal_connect(G_OBJECT(checkbutton), "clicked", G_CALLBACK(visible_pasword),  user_login_info->password_entry);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}
