#include "../inc/header.h"

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
  /* Set the border width */
    gtk_container_set_border_width (GTK_CONTAINER (scrollbar), 0);
    //gtk_container_set_border_width (GTK_CONTAINER (f), 11);
  /* Extract our desired image from a file that we have */
    image = gtk_image_new_from_file ("ex.jpg");
    image2 = gtk_image_new_from_file("view.jpg");

  /* And add it to the scrolled window */ 
    gtk_container_add (GTK_CONTAINER (scrollbar), image);
    gtk_container_add (GTK_CONTAINER (f), image2);
  /* Set the policy of the horizontal and vertical scrollbars to automatic.
   * What this means is that the scrollbars are only present if needed.
   */
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollbar),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (f),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);
    
    return console;
}


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

 