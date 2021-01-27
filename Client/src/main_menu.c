#include "../inc/header.h"

/*
GtkWidget* createConsoleBox()
{
    GtkWidget* f = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *image, *image2;
    GtkWidget* mArea = gtk_search_entry_new();
    GtkWidget* scrollbar = gtk_scrolled_window_new (NULL, NULL);
    GtkWidget* textEntry = gtk_search_entry_new();

    //GtkWidget* console = gtk_table_new(4, 2, FALSE);
    GtkWidget *console = gtk_grid_new();
    //gtk_table_attach_defaults(GTK_TABLE(console), textEntry, 0, 1, 0, 1);
    //gtk_table_attach_defaults(GTK_TABLE(console), textArea, 1, 2, 1, 2);
    //gtk_table_attach_defaults(GTK_TABLE(console), scrollbar, 0, 1, 1, 2);
    gtk_grid_attach(GTK_GRID(console), f, 30, 0, 70, 93);
    gtk_grid_attach(GTK_GRID(console), textEntry, 0, 0, 30, 10);
    gtk_grid_attach(GTK_GRID(console), mArea, 30, 93, 70, 7); 
    gtk_grid_attach(GTK_GRID(console), scrollbar, 0, 10, 30, 90);
    //This code sets the preferred size for the widget, so it does not ask for extra space
    gtk_widget_set_size_request(textEntry, 1, 1);
    gtk_widget_set_size_request(scrollbar, 1, 670);
    gtk_widget_set_size_request(mArea, 500, 1);
    gtk_widget_set_size_request(f, 500, 670);
  //Set the border width 
    gtk_container_set_border_width (GTK_CONTAINER (scrollbar), 0);
    //gtk_container_set_border_width (GTK_CONTAINER (f), 11);
  //Extract our desired image from a file that we have 
    image = gtk_image_new_from_file ("Client/src/ex.jpg");
    image2 = gtk_image_new_from_file("Client/src/view.jpg");

  // And add it to the scrolled window 
    gtk_container_add (GTK_CONTAINER (scrollbar), image);
    gtk_container_add (GTK_CONTAINER (f), image2);
  // Set the policy of the horizontal and vertical scrollbars to automatic.
   * What this means is that the scrollbars are only present if needed.
   //
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollbar),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (f),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);
    
    return console;
}
*/


/*
void main_menu()
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *hbox1;

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MEMCHAT");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 700);
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox1), createConsoleBox(), TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, TRUE, 0);
    //gtk_container_add(GTK_CONTAINER(vbox), createConsoleBox());// does not  matter this size
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    gtk_widget_show_all(window);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
}

 */


void my_close_app(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}


 void main_menu() {
  GtkWidget *window; // my window
  GtkWidget *main_box,*chats_list_box,  *message_list_box, *message_box, *input_box; // Боксы 
  GtkWidget *input_str, *input_key; // for imput_box
  GtkWidget *message_1, *message_2,*message_3,*message_4,*message_5,*message_6,*message_7,*message_8,*message_9,*message_10,*message_11; // for messages


  GtkWidget *scrool_massages, *scrool_chats;


  gtk_init(NULL, NULL);
  load_css();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(window), "MEMCAT CHAT");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(my_close_app), NULL); // Сигнал для завершения преложения

  message_1 = gtk_label_new("Pidoddsa;;;");
  message_2 = gtk_label_new("Pidordsadasina");
  message_3 = gtk_label_new("Pidorsdaadasina");
  message_4 = gtk_label_new("Pidoradasadsina");
  message_5 = gtk_label_new("Pidoradsadsina");
  message_6 = gtk_label_new("Pidoradsasdasina");
  message_7 = gtk_label_new("Pidoradsasdsina");
  message_8 = gtk_label_new("Pidorasdasdasina");
  message_9 = gtk_label_new("Pidoradsasdasina");
  message_10 = gtk_label_new("Pidoradsasdsina");
  message_11 = gtk_label_new("Pidorasdasdasina");

  input_key = gtk_button_new ();
  input_str = gtk_entry_new();

  main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  chats_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  message_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  message_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  scrool_massages = gtk_scrolled_window_new(NULL, NULL); 
  scrool_chats = gtk_scrolled_window_new(NULL, NULL); 

  gtk_box_pack_start(GTK_BOX(main_box), scrool_chats, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), message_box, TRUE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(message_box), scrool_massages, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(message_box), input_box, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(input_box), input_str, TRUE, FALSE, 2);
  gtk_box_pack_start(GTK_BOX(input_box), input_key, TRUE, FALSE, 2);

gtk_widget_set_name(GTK_WIDGET(chats_list_box), "test");

  //PACK CHATSS
      gtk_box_pack_start(GTK_BOX(chats_list_box), message_6, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(chats_list_box), message_7, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(chats_list_box), message_8, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(chats_list_box), message_9, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(chats_list_box), message_10, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(chats_list_box), message_11, FALSE, FALSE, 5);


  // END PACK

  //PACK MASSAGES
      gtk_box_pack_start(GTK_BOX(message_list_box), message_1, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(message_list_box), message_2, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(message_list_box), message_3, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(message_list_box), message_4, FALSE, FALSE, 5);
      gtk_box_pack_start(GTK_BOX(message_list_box), message_5, FALSE, FALSE, 5);

  // END PACK

  gtk_container_add(GTK_CONTAINER(scrool_massages), message_list_box);
  gtk_container_add(GTK_CONTAINER(scrool_chats), chats_list_box);
  gtk_container_add(GTK_CONTAINER(window), main_box);

  gtk_widget_show_all(window);

  gtk_main();
 }