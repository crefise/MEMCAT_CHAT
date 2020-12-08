#include "gtk/gtk.h"

int main( int argc, char *argv[])
{
        /* тут мы объявим переменные */

        /* запускаем GTK+ */
        gtk_init(&argc, &argv);

        /* тут будет код нашего приложения */

        /* передаём управление GTK+ */
        gtk_main();

        return 0;
}