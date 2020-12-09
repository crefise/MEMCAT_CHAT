#include <gtk/gtk.h>

GtkWidget* createConsoleBox()
{
    GtkWidget* f;
    GtkWidget *image;
    GtkWidget* textArea = gtk_text_view_new();
    GtkWidget* scrollbar = gtk_scrolled_window_new (NULL, NULL);
    GtkWidget* textEntry = gtk_search_entry_new();

    GtkWidget* console = gtk_table_new(4, 2, FALSE);
    gtk_table_attach_defaults(GTK_TABLE(console), textEntry, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(console), textArea, 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(console), scrollbar, 0, 1, 1, 2);
    
    //This code sets the preferred size for the widget, so it does not ask for extra space
    gtk_widget_set_size_request(textEntry, 1, 1);
    gtk_widget_set_size_request(scrollbar, 2, 550);
    gtk_widget_set_size_request(textArea, 400, 20);
    
  /* Set the border width */
    gtk_container_set_border_width (GTK_CONTAINER (scrollbar), 11);
  /* Extract our desired image from a file that we have */
    image = gtk_image_new_from_file ("ex.jpg");
  /* And add it to the scrolled window */
    gtk_container_add (GTK_CONTAINER (scrollbar), image);
  /* Set the policy of the horizontal and vertical scrollbars to automatic.
   * What this means is that the scrollbars are only present if needed.
   */
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollbar),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);
    return console;
}


int main(int argc,char* argv[])
{
    GtkWidget *window;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MEMCHAT");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 600);// does not  matter this size
    gtk_container_add(GTK_CONTAINER(window), createConsoleBox());
    gtk_widget_show_all(window);
    gtk_window_set_resizable(GTK_WINDOW(window),TRUE);//because of this
    gtk_main();
    return 0;
}

 