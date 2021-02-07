mkdir Client/Libs
mkdir Client/Libs/gtk/
mkdir Client/Libs/gtk/include
mkdir Client/Libs/gtk/lib
brew install gtk+3
cp -aRv /Users/"$USER"/.brew/Cellar/libffi/3.3/include/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/gtk+3/3.24.23/include/gtk-3.0/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/include/gio-unix-2.0/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/cairo/1.16.0_3/include/cairo/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/libepoxy/1.5.4_1/include/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/pango/1.48.0/include/pango-1.0/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/fribidi/1.0.10/include/fribidi/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/harfbuzz/2.7.2/include/harfbuzz/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/graphite2/1.3.14/include/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/atk/2.36.0/include/atk-1.0/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/cairo/1.16.0_3/include/cairo/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/pixman/0.40.0/include/pixman-1/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/fontconfig/2.13.1/include/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/opt/freetype/include/freetype2/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/libpng/1.6.37/include/libpng16/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/gdk-pixbuf/2.42.0/include/gdk-pixbuf-2.0/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/include/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/include/glib-2.0/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/lib/glib-2.0/include/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/opt/gettext/include/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/pcre/8.44/include/* Client/Libs/gtk/include
cp -aRv /Users/"$USER"/.brew/Cellar/gtk+3/3.24.23/lib/* Client/Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/pango/1.48.0/lib/* Client/Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/harfbuzz/2.7.2/lib/* Client/Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/atk/2.36.0/lib/* Client/Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/cairo/1.16.0_3/lib/* Client/Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/gdk-pixbuf/2.42.0/lib/* Client/Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/Cellar/glib/2.66.2_1/lib/* Client/Libs/gtk/lib
cp -aRv /Users/"$USER"/.brew/opt/gettext/lib Client/Libs/gtk/lib/*
