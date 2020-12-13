#include "../inc/header.h"

//#define SERVERADDR "51.15.120.179"
//#define SERVERADDR "10.11.6.1" // Айпи для моего ПК(VOVA)
#define SERVERADDR "localhost"
#define SERVERPORT 8000 // Порт сервера

void initializate_socket(){
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sock = socket(AF_INET, SOCK_STREAM, 0); // Сокет который ведет к серверу
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERVERPORT);
    server = gethostbyname(SERVERADDR);
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr,    server->h_addr_list[0],  server->h_length);
    serv_addr.sin_port = htons(SERVERPORT);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
}



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
