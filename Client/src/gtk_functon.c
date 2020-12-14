#include "../inc/header.h"
//#define test_cout
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
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
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
    user_login_info->label_error = gtk_label_new ( "" );

    /// ***
    user_login_info->entry_username = gtk_entry_new();
    user_login_info->entry_password = gtk_entry_new();

    /// ***
    login_button = gtk_button_new_with_label ( "Login" );
    back_button  = gtk_button_new_with_label ( "Back to Main" );

    /// ***
    gtk_grid_attach ( GTK_GRID ( grid ), label_username, 0, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), user_login_info->entry_username, 1, 0, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), label_password, 0, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), user_login_info->entry_password, 1, 1, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), user_login_info->label_error, 0, 2, 2, 2 );

    gtk_grid_attach ( GTK_GRID ( grid ), back_button,    0, 5, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), login_button,   1, 5, 1, 1 );

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

    struct user_info *user_login_info = malloc(sizeof(struct user_info));

    /// *** Create the Grid
    grid = gtk_grid_new();

    /// ***
    label_login = gtk_label_new ( "Login:" );
    label_password  = gtk_label_new ( "Password:" );
    label_confirm_password  = gtk_label_new ( "Confirm password:" );
    user_login_info->label_error = gtk_label_new ( "" );

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

    gtk_grid_attach ( GTK_GRID ( grid ), user_login_info->label_error, 0, 3, 2, 2 );

    gtk_grid_attach ( GTK_GRID ( grid ), back_button,     0, 5, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), register_button, 1, 5, 1, 1 );

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
    char *buffer = NULL;
    struct user_info *temp = data;

    gtk_label_set_text(GTK_LABEL(temp->label_error), "");

    char  *login = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_username));
    char *password = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_password));

    if (strcmp(login, "") == 0 || strcmp(password, "") == 0) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "Empty field(s)");
        return;
    }

    // А тут мы ждем ответа от сервера/ можно ли нам менять окно!
    buffer = concat((char*)"login[", (char*)i_to_s(strlen(login)));
    buffer = concat(buffer, "][");
    buffer = concat(buffer, (char*)i_to_s(strlen(password)));
    buffer = concat(buffer, "]");
    buffer = concat(buffer,login);
    buffer = concat(buffer,password);

    if (!curr_sybmobol(login) || !curr_sybmobol(password)){ // проверка на коректность ввода
        gtk_label_set_text(GTK_LABEL(temp->label_error), "BAD SYMBOL");
        return;
    }

    if (send(sock, buffer, strlen(buffer), 0) == -1) {
        write(2, "SERVER DONT CONNETCTED\n",23);
    } // send data to server
    free(buffer);


    buffer = malloc(2);
    if (recv(sock, &buffer[0], sizeof(buffer) - 1, 0) == -1) { // А тут мы ждем ответа от сервера/ нормально ли прошла регистрация!
        write(2, "SERVER DONT CONNETCTED\n",23);
    } 
    else {
        if (strcmp(buffer, "1") != 0) {
            gtk_label_set_text(GTK_LABEL(temp->label_error), "UNCOREECT PASS OR LOGIN");
        }
        else {
            write(2, "LOGIN OKAY ",12);
        }
        mx_strdel(&buffer);
    }
}

void register_connect(GtkWidget *button, gpointer data) {
    char *buffer = NULL;
    struct user_info *temp = data;

    gtk_label_set_text(GTK_LABEL(temp->label_error), "");

    char *login = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_username));
    char *password = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_password));
    char *password_repeat = (char*) gtk_entry_get_text(GTK_ENTRY(temp->entry_confirm_password));


// Проверки на коректность ввода
    if (!curr_sybmobol(login) || !curr_sybmobol(password) || !curr_sybmobol(password_repeat)){ // проверка на коректность ввода
        gtk_label_set_text(GTK_LABEL(temp->label_error), "BAD SYMBOL");
        return;
    }

    if (strcmp(login, "") == 0 || strcmp(password, "") == 0 || strcmp(password_repeat, "") == 0) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "Empty field(s)");
        return;
    }

    if (strcmp(password, password_repeat) != 0) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "Passwords do not match");
        return;
    }

    /*
    if (strlen(login) < 4) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "login ne mozet mense 4");
        return;
    }
    */
   
    if (strlen(password) < 6) {
        gtk_label_set_text(GTK_LABEL(temp->label_error), "Parol ne mojet bit mense 6");
        return;
    }



    else {
        // отправляем на сервер запрос что мы хотим регистрироваться!

        buffer = concat(concat(concat(concat(concat(concat((char*)"registration[", 
                                        (char*)i_to_s(strlen(login))), "]["), 
                                        (char*)i_to_s(strlen(password))), "]"),login),password);

        if (send(sock, buffer, strlen(buffer), 0) == -1) { // отправляем на сервер наши данные для регистрации
            write(2, "SERVER DONT CONNETCTED\n",23);
            return;
        }
        free(buffer);

        buffer = mx_strnew(256);
        if (recv(sock, buffer, 256, 0) == -1) { // А тут мы ждем ответа от сервера/ нормально ли прошла регистрация!
            write(2, "SERVER DONT CONNETCTED\n",23);
            return;
        }
        else if (strcmp(buffer, "1") == 0){
            write(2, "REGISTER OKAY\n",14);
            login_clbk((GtkButton*)button, (GtkStack*)stack);
            return;
        }
        else {
            gtk_label_set_text(GTK_LABEL(temp->label_error), "Login zanyat hahuy");
        }
        mx_strdel(&buffer);

    }
}
