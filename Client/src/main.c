#include "../inc/header.h"

int sock;
GtkWidget *stack;
GtkWidget *login_window;
GtkWidget *scrool_massages;
GtkWidget *chats_list_box = NULL;
GtkWidget *CONTAINER = NULL;
GtkWidget *window; // my window
GtkWidget *chats_box;
GtkWidget *message_box;
GtkWidget *reconnect_widget;
GtkWidget *main_box;
char *OPENED_DIALOG;
CHAT_T *MY_CHATS = NULL;
CHAT_T *FAVORITE_CHAT = NULL;






int main ( int argc, char* argv[] ) {
    if (argc != 3) {
        mx_printerrln("usage: ./uchat [IP] [PORT]");
        return 0;
    }
    mx_initializate_socket(argv[1], atoi(argv[2]));
    if (sock == -1)
        mx_printerr("NO_CONNECT_TO_SERVER\n");

    GtkWidget *login_box;
    GtkWidget *login_grid;
    GtkWidget *register_grid;
    GtkWidget *stack_box;



    /// ***
    gtk_init ( NULL, NULL );
    load_css();

    /// *** Create a Window
    login_window = createWindow ( 300, 300, "MEMCAT(ˆ_ˆ)" );

    /// *** Create the Stack Box
    stack_box = create_stack_box ( &stack );
    gtk_container_add ( GTK_CONTAINER ( login_window ), stack_box );

    /// ***
    login_box     = create_login_box     ( stack );
    login_grid    = create_login_grid    ( stack );
    register_grid = create_register_grid ( stack );

    /// ***
    gtk_stack_add_named  ( GTK_STACK ( stack ), login_box,     "Main" );
    gtk_stack_add_named  ( GTK_STACK ( stack ), login_grid,    "Login" );
    gtk_stack_add_named  ( GTK_STACK ( stack ), register_grid, "Register" );

    /// ***
    gtk_stack_set_transition_type ( GTK_STACK ( stack ), GTK_STACK_TRANSITION_TYPE_SLIDE_DOWN ); // Тип перехода между страницами стака
    gtk_stack_set_transition_duration ( GTK_STACK ( stack ), 1000 ); // Скорость перехода между страницами стака
    gtk_stack_set_interpolate_size ( GTK_STACK ( stack ), TRUE );

    /// ***
    gtk_widget_show_all ( login_window );
    gtk_main ();
}
