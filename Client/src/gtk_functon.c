#include "../inc/header.h"
#define test_cout
void load_css ( void ) {
    GtkCssProvider *provider;
    GdkDisplay     *display;
    GdkScreen      *screen;
    /// ***
    const gchar *css_style_file = "Client/src/style.css";
    GFile *css_fp               = g_file_new_for_path ( css_style_file );
    GError *error               = 0;
    /// ***
    provider = gtk_css_provider_new ();
    display  = gdk_display_get_default ();
    screen   = gdk_display_get_default_screen ( display );
    /// ***
    gtk_style_context_add_provider_for_screen   ( screen, GTK_STYLE_PROVIDER ( provider ), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );
    gtk_css_provider_load_from_file             ( provider, css_fp, &error );
    /// ***
}

GtkWidget *createWindow ( const gint width, const gint height, const gchar *const title ) {
    GtkWidget *window;
    window = gtk_window_new ( GTK_WINDOW_TOPLEVEL );
    gtk_window_set_title ( GTK_WINDOW ( window ), title );
    g_signal_connect ( window, "destroy", gtk_main_quit, window );
    gtk_window_set_default_size ( GTK_WINDOW ( window ), width, height );
    gtk_container_set_border_width ( GTK_CONTAINER ( window ), 50 );
    return window;
}

GtkWidget *create_login_box (GtkWidget *stack) {
    GtkWidget *box;
    GtkWidget *login_button;
    GtkWidget *register_button;
    GtkWidget *close_button;
    GtkWidget *label_memcat;

    /// *** Create the Box
    box = gtk_box_new ( GTK_ORIENTATION_VERTICAL, 10 );

    label_memcat = gtk_label_new("MEMCAT(ˆ_ˆ)");

    /// *** Create the Buttons
    login_button    = gtk_button_new_with_label ( "Login" );
    register_button = gtk_button_new_with_label ( "Register" );
    close_button    = gtk_button_new_with_label ( "Close" );

    /// *** Add them to the Box
    gtk_box_pack_start ( GTK_BOX ( box ), label_memcat,    0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX ( box ), login_button,    0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX ( box ), register_button, 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX ( box ), close_button,    0, 0, 0 );

    /// ***
    g_signal_connect ( login_button,    "clicked", G_CALLBACK ( login_clbk ),    stack );
    g_signal_connect ( register_button, "clicked", G_CALLBACK ( register_clbk ), stack );
    g_signal_connect ( close_button,    "clicked", G_CALLBACK ( quit_clbk ),      NULL );

    /// *** Return the Box
    return box;
}

GtkWidget *create_login_grid (GtkWidget *stack) {
    struct user_info *user_login_info = malloc(sizeof(struct user_info));

    GtkWidget *grid;
    GtkWidget *login_button;
    GtkWidget *back_button;

    GtkWidget *label_username;
    GtkWidget *label_password;

    /// *** Create the Grid
    grid = gtk_grid_new();

    /// ***
    label_username = gtk_label_new ( "Username:" );
    label_password = gtk_label_new ( "Password:" );

    /// ***
    user_login_info->entry_username = gtk_entry_new();
    user_login_info->entry_password = gtk_entry_new();

    /// ***
    login_button = gtk_button_new_with_label ( "Login" );
    back_button  = gtk_button_new_with_label ( "Go to Main" );

    /// ***
    gtk_grid_attach ( GTK_GRID ( grid ), label_username, 0, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), user_login_info->entry_username, 1, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), label_password, 0, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), user_login_info->entry_password, 1, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), back_button,    0, 2, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), login_button,   1, 2, 1, 1 );

    /// ***
    g_signal_connect ( login_button, "clicked", G_CALLBACK ( login_connect ), user_login_info );
    g_signal_connect ( back_button, "clicked", G_CALLBACK ( main_clbk ), stack );

    /// ***
    return grid;
}

GtkWidget *create_register_grid (GtkWidget *stack) {
    GtkWidget *grid;
    GtkWidget *register_button;
    GtkWidget *back_button;

    GtkWidget *label_login;
    GtkWidget *label_password;
    GtkWidget *label_confirm_password;
    GtkWidget *label_error;

    struct user_info *user_login_info = malloc(sizeof(struct user_info));

    /// *** Create the Grid
    grid = gtk_grid_new();

    /// ***
    label_login = gtk_label_new ( "Login:" );
    label_password  = gtk_label_new ( "Password:" );
    label_confirm_password  = gtk_label_new ( "Confirm password:" );
    label_error = gtk_label_new ( "Confirm password:" );

    /// ***
    user_login_info->entry_username = gtk_entry_new();
    user_login_info->entry_password  = gtk_entry_new();
    user_login_info->entry_confirm_password = gtk_entry_new();

    /// ***
    register_button = gtk_button_new_with_label ( "Register" );
    back_button    = gtk_button_new_with_label ( "Back to Main" );

    /// ***
    gtk_grid_attach ( GTK_GRID ( grid ), label_login, 0, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), user_login_info->entry_username, 1, 0, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), label_password,  0, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), user_login_info->entry_password,  1, 1, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), label_confirm_password,  0, 2, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), user_login_info->entry_confirm_password,  1, 2, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), back_button,     0, 3, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), register_button, 1, 3, 1, 1 );

    /// ***
    g_signal_connect ( register_button, "clicked", G_CALLBACK ( register_connect ), user_login_info );
    g_signal_connect ( back_button, "clicked", G_CALLBACK ( main_clbk ), stack );

    /// ***
    return grid;
}

GtkWidget *create_stack_box (GtkWidget **stack) {
    GtkWidget *box;

    /// *** Create the Box
    box = gtk_box_new ( GTK_ORIENTATION_VERTICAL, 10 );

    /// *** Create a Stack
    *stack = gtk_stack_new ();
    gtk_widget_set_halign ( *stack, GTK_ALIGN_CENTER );
    gtk_box_set_center_widget ( GTK_BOX ( box ), *stack );

    /// ***
    return box;
}

void main_clbk (GtkButton *button, GtkStack *stack) {
    g_return_if_fail ( GTK_IS_BUTTON ( button ) );
    g_return_if_fail ( GTK_IS_STACK ( stack ) );

    gtk_stack_set_visible_child_full ( stack, "Main", GTK_STACK_TRANSITION_TYPE_SLIDE_DOWN );
}

void login_clbk (GtkButton *button, GtkStack *stack ) {
    g_return_if_fail ( GTK_IS_BUTTON ( button ) );
    g_return_if_fail ( GTK_IS_STACK ( stack ) );


    gtk_stack_set_visible_child_full ( stack, "Login", GTK_STACK_TRANSITION_TYPE_SLIDE_UP );
}

void register_clbk (GtkButton *button, GtkStack *stack) {
    g_return_if_fail ( GTK_IS_BUTTON ( button ) );
    g_return_if_fail ( GTK_IS_STACK ( stack ) );

    gtk_stack_set_visible_child_full ( stack, "Register", GTK_STACK_TRANSITION_TYPE_SLIDE_UP );
}

void quit_clbk    ( void ) {
    gtk_main_quit();
}

void login_connect(GtkWidget *button, gpointer data) {
    struct user_info *temp = data;
    char  *login = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_username));
    char *password = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_password));
    // А тут мы ждем ответа от сервера/ можно ли нам менять окно!
}

void register_connect(GtkWidget *button, gpointer data) {
    struct user_info *temp = data;
    char *login = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_username));
    char *password = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_password));
    char *password_repeat = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_confirm_password));
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

// отправляем на сервер запрос что мы хотим регистрироваться!
    char *str = concat((char*)"registration[", (char*)i_to_s(strlen(login)));
    str = concat(str, "][");
    str = concat(str, (char*)i_to_s(strlen(password)));
    str = concat(str, "]");
    str = concat(str,login);
    str = concat(str,password);
    if (send(sock, str, strlen(str), 0) == -1) {
        write(2, "SERVER DONT CONNETCTED\n",23);
    } // send data to server
    free(str);
    // А тут мы ждем ответа от сервера/ нормально ли прошла регистрация!
    write(2, "END\n",4);
    }
}
