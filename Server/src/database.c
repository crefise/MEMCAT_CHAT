#include "../inc/header.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   for(int i = 0; i < argc; i++) printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   return 0;
}

void double_free(char** array) {
   for (int i = 0; array[i]; i++) {
      free(array[i]);
   }
   free(array);
   array = NULL;
}

int get_max_user_id() {
   int max_id = 0;
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT MAX(ID) FROM USERS");

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      char* IDs = concat(IDs, (char*)sqlite3_column_text(result, 0));
      max_id = atoi(IDs);
      free(IDs);
   }
   
   sqlite3_finalize(result);
   free(statement);
   return max_id;
}

void open_db(char* path, sqlite3** db) {
   int rc = sqlite3_open(path, db);
   if (rc) fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
   else fprintf(stdout, "Database [%s] opened successfully\n", path);
}

void exec_db(char* statement) {
   char* zErrMsg = 0; // вывод ошибки если такая есть
   int rc = sqlite3_exec(data_base, statement, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
} 

void close_db() {
   char* statement = "TRUNCATE TABLE ONLINE_USERS";
   exec_db(statement);
   sqlite3_close(data_base);
}

void add_user_db(char* login, char* password) {
   char* statement = sqlite3_mprintf("INSERT INTO USERS (LOGIN,PASSWORD) VALUES ('%s', '%s');", login, password);
   exec_db(statement);
}

void add_online_user_db(char* login, int socket, sqlite3* db) {
   char* statement = sqlite3_mprintf("INSERT INTO ONLINE_USERS (LOGIN,SOCKET) VALUES ('%s', %i);", login, socket);
   exec_db(statement);
}

void delete_online_user_db(int socket) {
   char* statement = sqlite3_mprintf("DELETE FROM ONLINE_USERS WHERE SOCKET=%i;", socket);
   exec_db(statement);
}

int access_db(char* login, char* password) {
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT ID from USERS where LOGIN='%s' AND PASSWORD='%s'", login, password);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
      return false;
   } 
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      sqlite3_finalize(result);
      return true;
   }

   sqlite3_finalize(result);
   return false;
}

int check_user_db(char* login) {
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT ID from USERS where LOGIN='%s';", login);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
      return false;
   } 
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      sqlite3_finalize(result);
      return true;
   }
   sqlite3_finalize(result);
   return false;
}

int get_socket_db(char* login) {
   int socket = -1;
   sqlite3_stmt *result;

   char* statement = sqlite3_mprintf("SELECT SOCKET FROM ONLINE_USERS WHERE LOGIN='%s';", login);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      socket = atoi((char*)sqlite3_column_text(result, 0));
   
   sqlite3_finalize(result);
   return socket;
}
/*
void get_chats_by_login_db(char* login) {
   int id = get_users_ID(login);
   char* statement = sqlite3_mprintf("SELECT CHAT_ID, USER1_ID, USER2_ID FROM CHATS WHERE USER1_ID=%i, OR USER2_ID=%i;", id, id);
   exec_db(statement);
}
*/
void get_chats_by_id_db(int id) {
   char* statement = sqlite3_mprintf("SELECT CHAT_ID, USER1_ID, USER2_ID FROM CHATS WHERE USER1_ID=%i, OR USER2_ID=%i;", id, id);
   exec_db(statement);
}

int get_users_ID(char* login) {
   int id = 0;
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT ID FROM USERS WHERE LOGIN='%s';", login);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      id = atoi((char*)sqlite3_column_text(result, 0));
   
   sqlite3_finalize(result);
   return id;
}

int create_chat_db(char* u1, char* u2) {
   int chat_id = get_chat_id_by_logins(u1, u2);
   if (chat_id != 0) return chat_id;

   int u1_id = get_users_ID(u1);
   int u2_id = get_users_ID(u2);
   char* statement = sqlite3_mprintf("INSERT INTO CHATS(USER1_ID, USER2_ID) VALUES(%i, %i);", u1_id, u2_id);

   exec_db(statement);

   chat_id = get_chat_id_by_logins(u1, u2);
   return chat_id;
}

int get_chat_id_by_logins(char* u1, char* u2) {
   int chat_id = 0;
   int id1 = get_users_ID(u1);
   int id2 = get_users_ID(u2);
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT CHAT_ID FROM CHATS WHERE USER1_ID=%i AND USER2_ID=%i", id1, id2);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      chat_id = atoi((char*)sqlite3_column_text(result, 0));
   
   sqlite3_finalize(result);
   return chat_id;
}

int get_max_chat_id() {
   int id = 0;   
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT MAX(CHAT_ID) FROM CHATS");

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      if ((char*)sqlite3_column_text(result, 0) == NULL) mx_printerr("null\n");
      else id = atoi((char*)sqlite3_column_text(result, 0));
   }

   sqlite3_finalize(result);
   return id;
}

char* get_users_login(int id) {
   char* login = NULL;
   sqlite3_stmt *result;
   char* statement = sqlite3_mprintf("SELECT LOGIN FROM USERS WHERE ID=%i;", id);

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      login = sqlite3_mprintf("%s",(char*)sqlite3_column_text(result, 0));

   return login;
}

char** get_chats(char* login) {
   int max_chat_id = get_max_chat_id();
   if (max_chat_id == 0) return NULL;
   char** result = malloc(sizeof(char*) * max_chat_id + 1);

   //for (int i = 0; i < max_chat_id + 1; i++) 
   result[max_chat_id] = NULL;
   sqlite3_stmt *res;

   int id = get_users_ID(login);
   char* statement = sqlite3_mprintf("SELECT CHAT_ID, USER1_ID, USER2_ID FROM CHATS WHERE USER1_ID=%i OR USER2_ID=%i;", id, id);
   mx_printerr("shos\n");
   int rc = sqlite3_prepare_v2(data_base, statement, -1, &res, 0);
   if (rc != SQLITE_OK) {
         fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
         sqlite3_close(data_base);
         return NULL;
   }
   int i = 0;
   while(true) {
      rc = sqlite3_step(res);
      int chat_id;
      int chat_u1;
      int chat_u2;
      int u1 = get_users_ID(login);
      int u2;
      
      if (rc == SQLITE_ROW) {
         chat_id = atoi((char*)sqlite3_column_text(res, 0));
         chat_u1 = atoi((char*)sqlite3_column_text(res, 1));
         chat_u2 = atoi((char*)sqlite3_column_text(res, 2));

         if (u1 == chat_u1) u2 = chat_u2;
         else if (u1 == chat_u2) u2 = chat_u1;

         char* u2_login = sqlite3_mprintf("%s", get_users_login(u2));
         char* temp = sqlite3_mprintf("%i/%s", chat_id, u2_login);
      
         result[i] = malloc(sizeof(char) * strlen(temp));
         result[i] = concat(result[i], temp);
         i++;
      }
      else {
         result[i] = NULL;
         break;
      }
   }

   mx_printerrln("in get_chats start");
   for (int i = 0; result[i] != NULL; i++) {
      mx_printerrln(result[i]);
   }
   mx_printerrln("in get_chats end");

   sqlite3_finalize(res);
   return result;
}

char* get_server_date() {
   char* time_date = malloc(sizeof(char) * 18);
   long int s_time;
   struct tm *m_time;
   s_time = time (NULL);
   m_time = localtime (&s_time);
   strftime (time_date, 128, "%X %d.%m.%Y", m_time);
   return time_date;
}

void add_message(int chat_id, int sender_id, char* message) {
   char* date_time = get_server_date();
   char* statement = sqlite3_mprintf("INSERT INTO CHAT(CHAT_ID, AUTHOR_ID, MESSAGE, DATE_TIME) VALUES(%i, %i, '%s', '%s');", chat_id, sender_id, message, date_time);
   exec_db(statement);
   free(date_time);
}

char** get_last_30_messages(int chat_id) {
   char** last_messages = malloc(sizeof(char*) * 31);
   last_messages[30] = NULL;
   sqlite3_stmt *result;




   return last_messages;
}
