all: compile

CLIENT_COMPILE_GLOBAL = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`


compile: 
	clang *.c $(CLIENT_COMPILE_GLOBAL) -o test
	./test