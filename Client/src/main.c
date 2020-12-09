#include "../inc/header.h"



int main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);

    main_loop();
 
    gtk_main ();

    return 0;
}