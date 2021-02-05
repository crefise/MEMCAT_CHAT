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
#include <time.h>

extern int count_users;
extern sqlite3* data_base;

#define BUF_SIZE 256;
/* SERVER FUNCTION*/
void *user_connect(void* sock); // функция оброботки каждого клиента
int parse_solution(char *text); // Функция которая определяем что именно хочет клиент
bool curr_sybmobol(char *str);
void reg_func(char *buffer, int client_socket); // register function;
void log_func(char *buffer, int client_socket, bool *logined,  char **login, char** pass); // login function;
void send_massage_to_client(char* message, char* login, int sender);

/* database */
void open_db(char* path, sqlite3** db); // ready
void exec_db(char* statement, sqlite3* db); // ready
void close_db(sqlite3* db); // ready
int get_maxID_db(sqlite3* db); // 
int check_user_db(char* login, sqlite3* db);
void add_online_user_db(char* login, int socket, sqlite3* db);
void delete_online_user_db(int socket, sqlite3* db);
int get_socket_db(char* login, sqlite3* db);
void add_user_db(char* login, char* password, sqlite3* db); // ready
int access_db(char* login, char* password, sqlite3* db); // ready
void delete_user(int id, sqlite3* db);
char* get_users_login(int id);
char* get_users_password(int id, sqlite3* db);
void set_users_login(int id, char* login, sqlite3* db);
void set_users_password(int id, char* password, sqlite3* db);
int get_users_ID(char* login, sqlite3* db);
void get_chats_by_id_db(int id);
int create_chat_db(char* u1, char* u2);
int get_chat_id_by_logins(char* u1, char* u2);
char* get_user2_and_chat_id_by_login(char* u1);
char** get_chats(char* login);
int get_max_chat_id();
char* get_chat_by_login(char* u1, int count);
char* get_server_date();
void add_message(int chat_id, int sender_id, char* message);

/* Parsing */
char** ps_registration(char* src);
char** ps_login(char* src);
char** ps_message(char* src);
void ps_massage_add(char *str,char **login, char **message, int *chat_ID);

/* string */
char* i_to_s(int n);
char* concat(char* s1, char* s2);
char *clear_buffer(char *s1);
char *mx_strnew(const int size);
void mx_strdel(char **str);
void mx_printerr(const char *s);
char *mx_strncpy(char *dst, const char *src, int len);
bool mx_isdigit(char c);
void ps_isuser(char **login_1, char **login_2, char *text);
void mx_del_strarr(char ***arr);
void mx_printerrln(const char *s);
/* GTK */

#endif
