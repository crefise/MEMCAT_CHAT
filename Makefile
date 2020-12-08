all: run

ORACLE_FLAG = -std=c11 -Wall -Wextra -Wpedantic

GTK_COMPILE_FLAG = -I"Libs/gtk/include" -L"Libs/gtk/lib" -lgtk-3 -lgdk-3 -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,CoreGraphics -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 #-lintl

FILES = main.c

run:
	clang $(FILES) -o test $(GTK_COMPILE_FLAG)

install_lib:
	sh Libs/install_lib_gtk+3.sh