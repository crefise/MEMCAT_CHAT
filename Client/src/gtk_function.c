#include "../inc/header.h"

char *login;
char *password;

void visible_pasword(GtkWidget *button, gpointer password_entry) {
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), !gtk_entry_get_visibility(password_entry));
}

void get_login(GtkWidget *button, gpointer data) {
    login = (char*) gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
}

void get_password(GtkWidget *button, gpointer data) {
    password = (char*) gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
}

void go_to_log(GtkWidget *button, gpointer window1) {
    gtk_widget_hide(window1);
    main_loop();
}

void reg_window(GtkWidget *button, gpointer window) {
    GtkWidget *window1;
    GtkWidget *username_label, *username_entry;
    GtkWidget *password_label, *password_label1, *password_entry, *password_entry1;
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
    username_entry = gtk_entry_new();
 
    // Создаем ярлык и поле ввода пароля
    password_label = gtk_label_new("Введите пароль:");
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);//видимость пароля

    password_label1 = gtk_label_new("Повторите пароль:");
    password_entry1 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry1), FALSE);

    reg_button = gtk_button_new_with_label("Зарегистрироваться");
    exit = gtk_button_new_with_label("Ввойти");
 
    //добавили в первую коробку username_label и username_entry и в основную коробку добавили первую
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox1), username_label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), username_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, FALSE, 5);
 
    //сделали также для пароля
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), password_label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), password_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, FALSE, 5);

    hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox3), password_label1, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox3), password_entry1, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox3, TRUE, FALSE, 5);

    hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox4), reg_button, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox4), exit, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox4, TRUE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window1), vbox);

    gtk_widget_hide(window);

    g_signal_connect(G_OBJECT(exit), "clicked", G_CALLBACK(go_to_log), window1);
    g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window1);

}

void main_loop() {
    GtkWidget *window;
    GtkWidget *username_label, *username_entry;
    GtkWidget *password_label, *password_entry;
    GtkWidget *hbox1, *hbox2, *hbox3;
    GtkWidget *vbox;
    GtkWidget *login_button, *reg_button;
    GtkWidget *checkbutton;
    bool visible = false;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 
    gtk_window_set_title (GTK_WINDOW (window), "MEMCAT(ˆ_ˆ)");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
 
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
 
    // Создаем ярлык и поле ввода логина
    username_label = gtk_label_new("Введите логин:");
    username_entry = gtk_entry_new();
 
    // Создаем ярлык и поле ввода пароля
    password_label = gtk_label_new("Введите пароль:");
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), visible);//видимость пароля
    
    //кнопки
    login_button = gtk_button_new_with_label("Авторизоваться");
    reg_button = gtk_button_new_with_label("Зарегистрироваться");
    checkbutton = gtk_check_button_new_with_label ("Показать пароль");

     //добавили в первую коробку username_label и username_entry и в основную коробку добавили первую
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox1), username_label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), username_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, FALSE, 5);
 
    //сделали также для пароля
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), password_label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), password_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, FALSE, 5);

    hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(vbox), checkbutton);
    gtk_box_pack_start(GTK_BOX(hbox3), login_button, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox3), reg_button, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox3, TRUE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox);
 
    g_signal_connect(G_OBJECT(reg_button), "clicked", G_CALLBACK(reg_window), window);
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(get_login), username_entry);
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(get_password), password_entry);
    g_signal_connect(G_OBJECT(checkbutton), "clicked", G_CALLBACK(visible_pasword), password_entry);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

}
