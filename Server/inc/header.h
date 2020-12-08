#ifndef HEADER_H
#define HEADER_H
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <sqlite3.h> 

#define BUF_SIZE 256;

/* database */
void open_db(char* path, sqlite3** db); // ready
void exec_db(char* statement, sqlite3* db); // ready
void close_db(sqlite3* db); // ready
void init_db(sqlite3* users_db, sqlite3* chats_db); //
void add_user_db(int* id, char* login, char* password, sqlite3* db); // ready
int access_db(char* login, char* password, sqlite3* db); // ready
void delete_user(int id, sqlite3* db);
char* get_users_login(int id, sqlite3* db);
char* get_users_password(int id, sqlite3* db);
void set_users_login(int id, char* login, sqlite3* db);
void set_users_password(int id, char* password, sqlite3* db);
int get_users_ID(char* login, sqlite3* db);

/* string */
char* i_to_s(int n);
char* concat(char* s1, char* s2);



#endif
