#include <gtk/gtk.h>
#include<stdbool.h>

int main (int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *username_label, *username_entry;
    GtkWidget *password_label, *password_entry;
    GtkWidget *hbox1, *hbox2;
    GtkWidget *vbox;
    GtkWidget *login_button;
    GtkWidget *checkbutton;
    static char **log;
    bool visible = false;
 
    gtk_init (&argc, &argv);
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
 
    //добавили в первую коробку username_label и username_entry и в основную коробку добавили первую
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), username_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), username_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, FALSE, 5);
 
    //сделали также для пароля
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), password_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), password_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    //кнопки
    login_button = gtk_button_new_with_label("Авторизоваться");
    checkbutton = gtk_check_button_new_with_label ("Показать пароль");
    //действия кнопки ...   g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), "Button 1");
    gtk_container_add(GTK_CONTAINER(vbox), checkbutton);
    gtk_container_add(GTK_CONTAINER(vbox), login_button);
 
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(button_clicked), password_entry);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

 
    gtk_main ();
    printf("%s", log[2]);
    return 0;
}
