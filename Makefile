all: compile_all

ORACLE_FLAG = -std=c11 -Wall -Wextra -Wpedantic

CLIENT_COMPILE_FLAG = -I"Client/Libs/gtk/include" -L"Client/Libs/gtk/lib" -lgtk-3 -lgdk-3 -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,CoreGraphics -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 #-lintl

CLIENT_COMPILE_GLOBAL = 'pkg-config --cflags gtk+-3.0' 'pkg-config --libs gtk+-3.0'

CLIENT_FILES = Client/src/*.c

SERVER_FILES = Server/src/*.c



comp_s:
	@clang $(SERVER_FILES) -l sqlite3 -o server_run

comp_c:
	@clang $(CLIENT_FILES) -o client_run $(CLIENT_COMPILE_GLOBAL)

compile_all: comp_s comp_c

install_lib:
	sh Client/Libs/install_lib_gtk+3.sh

clear:
	@rm -rf server_run
	@rm -rf client_run
