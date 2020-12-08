
mkdir Libs
mkdir Libs/gtk/
mkdir Libs/gtk/include
mkdir Libs/gtk/lib
brew install gtk+3
cp -aRv /Users/"$USER"/.brew/Cellar/libffi/3.3/include/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/gtk+3/3.24.23/include/gtk-3.0/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/include/gio-unix-2.0/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/cairo/1.16.0_3/include/cairo/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/libepoxy/1.5.4_1/include/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/pango/1.48.0/include/pango-1.0/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/fribidi/1.0.10/include/fribidi/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/harfbuzz/2.7.2/include/harfbuzz/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/graphite2/1.3.14/include/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/atk/2.36.0/include/atk-1.0/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/cairo/1.16.0_3/include/cairo/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/pixman/0.40.0/include/pixman-1/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/fontconfig/2.13.1/include/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/opt/freetype/include/freetype2/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/libpng/1.6.37/include/libpng16/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/gdk-pixbuf/2.42.0/include/gdk-pixbuf-2.0/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/include/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/include/glib-2.0/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/lib/glib-2.0/include/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/opt/gettext/include/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/pcre/8.44/include/* Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/gtk+3/3.24.23/lib/* Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/pango/1.48.0/lib/* Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/harfbuzz/2.7.2/lib/* Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/atk/2.36.0/lib/* Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/cairo/1.16.0_3/lib/* Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/gdk-pixbuf/2.42.0/lib/* Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/lib/* Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/opt/gettext/lib Libs/gtk/lib/*