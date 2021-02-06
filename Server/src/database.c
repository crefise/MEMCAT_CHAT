#include "../inc/header.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   for(int i = 0; i < argc; i++) printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   return 0;
}

int get_max_id_in_USERS() {
   int max_id = 0;
   sqlite3_stmt* result;
   char* statement = sqlite3_mprintf("SELECT MAX(ID) FROM USERS");

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      char* IDs = concat(IDs, (char*)sqlite3_column_text(result, 0));
      max_id = atoi(IDs);
      free(IDs);
   }
   
   sqlite3_finalize(result);
   sqlite3_free(statement);
   return max_id;
}

void open_db(char* path, sqlite3** db) {
   int rc = sqlite3_open(path, db);
   if (rc) {
      set_console_color(RED);
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
      set_console_color(NORMAL);
   }
   else fprintf(stdout, "Database [%s] opened successfully\n", path);
}

void exec_db(char* statement) {
   char* zErrMsg = 0;
   int rc = sqlite3_exec(data_base, statement, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ) {
      set_console_color(RED);
      fprintf(stderr, "😕 SQL error: %s\n", zErrMsg);
      set_console_color(NORMAL);
      sqlite3_free(zErrMsg);
   } 
} 

void close_db() {
   char* statement = "TRUNCATE TABLE ONLINE_USERS";
   exec_db(statement);
   sqlite3_close(data_base);
}

void add_user_to_USERS(char* login, char* password) {
   char* statement = sqlite3_mprintf("INSERT INTO USERS (LOGIN,PASSWORD) VALUES ('%s', '%s');", login, password);
   exec_db(statement);
   sqlite3_free(statement);
}

void add_user_to_ONLINE_USERS(char* login, int socket) {
   char* statement = sqlite3_mprintf("INSERT INTO ONLINE_USERS (LOGIN,SOCKET) VALUES ('%s', %i);", login, socket);
   exec_db(statement);
   sqlite3_free(statement);
}

void delete_user_from_ONLINE_USERS(int socket) {
   char* statement = sqlite3_mprintf("DELETE FROM ONLINE_USERS WHERE SOCKET=%i;", socket);
   exec_db(statement);
   sqlite3_free(statement);
}

bool check_login_password_in_USERS(char* login, char* password) {
   bool access = false;
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT ID from USERS where LOGIN='%s' AND PASSWORD='%s'", login, password);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
      access = false;
   } 
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      access = true;
   }
   sqlite3_finalize(result);
   sqlite3_free(statement);
   return access;
}

bool check_user_in_USERS(char* login) {
   bool exist = false;
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT ID from USERS where LOGIN='%s';", login);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
      exist = false;
   } 
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      sqlite3_finalize(result);
      exist = true;
   }
   sqlite3_finalize(result);
   sqlite3_free(statement);
   return exist;
}

int get_socket_from_ONLINE_USERS(char* login) {
   int socket = -1;
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT SOCKET FROM ONLINE_USERS WHERE LOGIN='%s';", login);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      socket = atoi((char*)sqlite3_column_text(result, 0));
   
   sqlite3_finalize(result);
   sqlite3_free(statement);
   return socket;
}

void get_chats_from_CHATS_CONSOLE(int id) {
   char* statement = sqlite3_mprintf("SELECT CHAT_ID, USER1_ID, USER2_ID FROM CHATS WHERE USER1_ID=%i, OR USER2_ID=%i;", id, id);
   exec_db(statement);
   sqlite3_free(statement);
}

int get_id_from_USERS(char* login) {
   int id = 0;
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT ID FROM USERS WHERE LOGIN='%s';", login);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      id = atoi((char*)sqlite3_column_text(result, 0));
   
   sqlite3_finalize(result);
   sqlite3_free(statement);
   return id;
}

int add_chat_to_CHATS(char* u1, char* u2) {
   int chat_id = get_chat_id_from_CHATS(u1, u2);
   if (chat_id != 0) return chat_id;
   if (strcmp(u1, u2) == 0) return 0;

   int u1_id = get_id_from_USERS(u1);
   int u2_id = get_id_from_USERS(u2);
   char* statement = sqlite3_mprintf("INSERT INTO CHATS(USER1_ID, USER2_ID) VALUES(%i, %i);", u1_id, u2_id);

   exec_db(statement);

   chat_id = get_chat_id_from_CHATS(u1, u2);
   sqlite3_free(statement);
   return chat_id;
}

int get_chat_id_from_CHATS(char* u1, char* u2) {
   int chat_id = 0;
   int id1 = get_id_from_USERS(u1);
   int id2 = get_id_from_USERS(u2);
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf(
   "SELECT CHAT_ID FROM CHATS WHERE (USER1_ID=%i AND USER2_ID=%i) OR (USER1_ID=%i AND USER2_ID=%i)", 
   id1, id2, id2, id1);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      chat_id = atoi((char*)sqlite3_column_text(result, 0));
   
   sqlite3_finalize(result);
   sqlite3_free(statement);
   return chat_id;
}

int get_max_chat_id_from_CHATS() {
   int id = 0;   
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT MAX(CHAT_ID) FROM CHATS");

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      if ((char*)sqlite3_column_text(result, 0) == NULL) mx_printerr("null\n");
      else id = atoi((char*)sqlite3_column_text(result, 0));
   }

   sqlite3_finalize(result);
   sqlite3_free(statement);
   return id;
}

char* get_login_from_USERS(int id) {
   char* login = NULL;
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT LOGIN FROM USERS WHERE ID=%i;", id);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      login = sqlite3_mprintf("%s",(char*)sqlite3_column_text(result, 0));

   sqlite3_finalize(result);
   sqlite3_free(statement);
   return login;
}

int count_users_chats(int id) {
   int chats = 0;
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT CHAT_ID, USER1_ID, USER2_ID FROM CHATS WHERE USER1_ID=%i OR USER2_ID=%i;", id, id);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);
   if (rc != SQLITE_OK) {
         set_console_color(RED);
         fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
         set_console_color(NORMAL);
         sqlite3_close(data_base);
         return chats;
   }
   rc = sqlite3_step(result);
   for (; rc == SQLITE_ROW; chats++) {
      rc = sqlite3_step(result);
   }

   sqlite3_finalize(result);
   sqlite3_free(statement);
   return chats;
}

char** get_chats_from_CHATS(char* login) {
   sqlite3_stmt *result;
   int user_id = get_id_from_USERS(login);
   int friend_id;
   int chats_c = count_users_chats(user_id);
   if (chats_c == 0) return NULL;

   char** chats = malloc(sizeof(char*) * (chats_c + 1));
   chats[chats_c] = NULL;

   char* statement = sqlite3_mprintf("SELECT CHAT_ID, USER1_ID, USER2_ID FROM CHATS WHERE USER1_ID=%i OR USER2_ID=%i;", user_id, user_id);
   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
      return NULL;
   }
   int i = 0;
   while(true) {
      rc = sqlite3_step(result);
      if (rc == SQLITE_ROW) {
         int chat_id = atoi((char*)sqlite3_column_text(result, 0));
         int user1_id = atoi((char*)sqlite3_column_text(result, 1));
         int user2_id = atoi((char*)sqlite3_column_text(result, 2));

         if (user_id == user2_id) friend_id = user1_id;
         else if (user_id == user1_id) friend_id = user2_id;

         char* friend_login = sqlite3_mprintf("%s", get_login_from_USERS(friend_id));
         char* temp = sqlite3_mprintf("%i/%s", chat_id, friend_login);

         chats[i] = malloc(sizeof(char) * strlen(temp));
         chats[i] = concat(chats[i], temp);
         i++;
      }
      else {
         break;
      }
   }
   sqlite3_free(statement);
   return chats;
}


void add_message_to_CHAT(int chat_id, int sender_id, char* message) {
   char* date_time = get_server_date();
   char* statement = sqlite3_mprintf("INSERT INTO CHAT(CHAT_ID, AUTHOR_ID, MESSAGE, DATE_TIME) VALUES(%i, %i, '%s', '%s');", chat_id, sender_id, message, date_time);
   exec_db(statement);
   free(date_time);
   sqlite3_free(statement);
}

char** get_last_30_messages_from_CHAT(int chat_id) {
   char** last_messages = malloc(sizeof(char*) * 31);
   last_messages[30] = NULL;
   sqlite3_stmt *result;




   return last_messages;
}

int get_max_message_id_from_CHAT(int chat_id) {
   int max_id = 0;   
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT MAX(MESSAGE_ID) FROM CHAT WHERE CHAT_ID=%i;", chat_id);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      max_id = atoi((char*)sqlite3_column_text(result, 0));

   sqlite3_finalize(result);
   sqlite3_free(statement);
   return max_id;
}

char** get_messages_from_CHAT(int chat_id) {
   sqlite3_stmt *result;
   int messages_c = count_messages_from_CHAT(chat_id);
   char** messages = malloc(sizeof(char*) * (messages_c + 1));
   messages[messages_c] = NULL;

   char* statement = sqlite3_mprintf(
   "SELECT MESSAGE_ID, AUTHOR_ID, DATE_TIME, MESSAGE FROM CHAT WHERE CHAT_ID=%i ORDER BY MESSAGE_ID", 
   chat_id);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   for(int i = 0; rc == SQLITE_ROW; i++, rc = sqlite3_step(result)) {
      int message_id = atoi((char*)sqlite3_column_text(result, 0));
      int author_id = atoi((char*)sqlite3_column_text(result, 1));
      char* date_time = (char*)sqlite3_column_text(result, 2);
      char* message = (char*)sqlite3_column_text(result, 3);

      char* temp = sqlite3_mprintf("%i/%i/%i/%s/%s", chat_id, message_id, author_id, message, date_time);

      messages[i] = "";
      messages[i] = concat(messages[i], temp);
   }
   
   sqlite3_finalize(result);
   sqlite3_free(statement);
   return messages;
}

int count_messages_from_CHAT(int chat_id) {
   sqlite3_stmt *result;
   int messages = 0;
   char* statement = sqlite3_mprintf("SELECT MESSAGE_ID FROM CHAT WHERE CHAT_ID=%i;", chat_id);
   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      set_console_color(RED);
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      set_console_color(NORMAL);
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   while(rc == SQLITE_ROW) {
      messages++;
      rc = sqlite3_step(result);
   }

   sqlite3_finalize(result);
   sqlite3_free(statement);
   return messages;
}

void delete_user_from_USERS(int id) {
   if (id == 0) {
      set_console_color(RED);
      char* err = "😕 Failed to delete data: user is not exist\n";
      write(1, err, strlen(err));
      set_console_color(NORMAL);
   }
   char* statement = sqlite3_mprintf("DELETE FROM USERS WHERE ID=%i", id);
   exec_db(statement);
   sqlite3_free(statement);
}