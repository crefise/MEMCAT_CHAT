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

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"

/* SERVER FUNCTION*/
char* get_server_date();
void *user_connect(void* sock); // функция оброботки каждого клиента
int parse_solution(char *text); // Функция которая определяем что именно хочет клиент
bool curr_sybmobol(char *str);
void reg_func(char *buffer, int client_socket); // register function;
void log_func(char *buffer, int client_socket, bool *logined,  char **login, char** pass); // login function;
void send_massage_to_client(char* message, char* sender_login, char* recipient_login,  int sender, int chat_ID);

/* database */
void open_db(char* path, sqlite3** db);
void exec_db(char* statement);
void close_db(); 

void add_user_to_USERS(char* login, char* password);
void delete_user_from_USERS(char* login);
void get_all_users_from_USERS_CONSOLE();
int get_max_id_in_USERS();
int get_id_from_USERS(char* login);
char* get_login_from_USERS(int id);
char* get_pass_from_USERS(int id);
void set_login_in_USERS(int id, char* login);
void set_password_in_USERS(int id, char* password);
bool check_user_in_USERS(char* login);
bool check_login_password_in_USERS(char* login, char* password);
int count_users_in_USERS(); // not ready

void add_user_to_ONLINE_USERS(char* login, int socket);
void delete_user_from_ONLINE_USERS(int socket);
int get_socket_from_ONLINE_USERS(char* login);

int add_chat_to_CHATS(char* u1, char* u2);
void get_chats_from_CHATS_CONSOLE(int id);
void get_all_chats_from_CHATS_CONSOLE();
int get_chat_id_from_CHATS(char* u1, char* u2);
char** get_chats_from_CHATS(char* login);
char** get_all_chats_from_CHATS();
int get_max_chat_id_from_CHATS();
void double_free_for_CHATS(char** array);

void add_message_to_CHAT(int chat_id, int sender_id, char* message);
void delete_message_from_CHAT(int message_id);
char** get_last_30_messages_from_CHAT(int chat_id);
char** get_messages_from_CHAT(int chat_id);
int get_max_message_id_from_CHAT(int chat_id);
char* get_message_from_CHAT(int chat_id, int message_id);
int count_messages_from_CHAT(int chat_id);

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

/* other */
void double_free(char** array);
void set_console_color(char* color);
void print_emoji(char* emoji);

#endif
