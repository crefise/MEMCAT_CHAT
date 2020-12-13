#include "../inc/header.h"

int sock;

int main ( void ) {
    initializate_socket();
    GtkWidget *window;
    GtkWidget *login_box;
    GtkWidget *login_grid;
    GtkWidget *register_grid;

    GtkWidget *stack_box;
    GtkWidget *stack;

    /// ***
    gtk_init ( NULL, NULL );
    load_css();

    /// *** Create a Window
    window = createWindow ( 300, 300, "MEMCAT(ˆ_ˆ)" );

    /// *** Create the Stack Box
    stack_box = create_stack_box ( &stack );
    gtk_container_add ( GTK_CONTAINER ( window ), stack_box );

    /// ***
    login_box     = create_login_box     ( stack );
    login_grid    = create_login_grid    ( stack );
    register_grid = create_register_grid ( stack );

    /// ***
    gtk_stack_add_named  ( GTK_STACK ( stack ), login_box,     "Main" );
    gtk_stack_add_named  ( GTK_STACK ( stack ), login_grid,    "Login" );
    gtk_stack_add_named  ( GTK_STACK ( stack ), register_grid, "Register" );

    /// ***
    gtk_stack_set_transition_type ( GTK_STACK ( stack ), GTK_STACK_TRANSITION_TYPE_SLIDE_DOWN );
    gtk_stack_set_transition_duration ( GTK_STACK ( stack ), 1000 );
    gtk_stack_set_interpolate_size ( GTK_STACK ( stack ), TRUE );

    /// ***
    gtk_widget_show_all ( window );
    gtk_main ();
}
