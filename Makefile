all: compile_all

ORACLE_FLAG = -std=c11 -Wall -Wextra -Wpedantic

GTK_COMPILE_FLAG = -I"Client/Libs/gtk/include" -L"Client/Libs/gtk/lib" -lgtk-3 -lgdk-3 -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,CoreGraphics -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 #-lintl

GTK_FILES = Client/src/*.c

SERVER_FILES = Server/src/*.c

CLIENT_FILES = Client/src/test_SOCK_CLIENT/test_CLIENT.c

comp_s:
	@clang $(SERVER_FILES) -l sqlite3 -o server_run

comp_c:
	@clang $(CLIENT_FILES) -l sqlite3 -o client_run

comp_g:
	@clang $(GTK_FILES) -o gtk_run $(GTK_COMPILE_FLAG)

compile_all: comp_s comp_c comp_g

install_lib:
	sh Client/Libs/install_lib_gtk+3.sh

clear:
	@rm -rf server_run
	@rm -rf client_run
	@rm -rf gtk_run