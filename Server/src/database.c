#include "../inc/header.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i = 0; i < argc; i++)
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   return 0;
}

int get_maxID_db(sqlite3* db) {
   int max_id = 0;
   sqlite3_stmt *result;
   char* statement = "SELECT MAX(ID) FROM USERS";

   int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return false;
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

void exec_db(char* statement, sqlite3* db) {
   char* zErrMsg = 0; // вывод ошибки если такая есть
   int rc = sqlite3_exec(db, statement, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
} 

void close_db(sqlite3* db) {
   char* statement = "TRUNCATE TABLE ONLINE_USERS";
   exec_db(statement, db);
   free(statement);
   sqlite3_close(db);
}

void add_user_db(char* login, char* password, sqlite3* db) {
   char* statement = "INSERT INTO USERS (LOGIN,PASSWORD) VALUES ('";
   statement = concat(statement, login);
   statement = concat(statement, "', '");
   statement = concat(statement, password);
   statement = concat(statement, "'); ");

   exec_db(statement, db);
   free(statement);
}

void add_online_user_db(char* login, int socket, sqlite3* db) {
   char* statement = "INSERT INTO ONLINE_USERS (LOGIN,SOCKET) VALUES ('";
   statement = concat(statement, login);
   statement = concat(statement, "', '");
   statement = concat(statement, i_to_s(socket));
   statement = concat(statement, "'); ");

   exec_db(statement, db);
   free(statement);
}

void delete_online_user_db(int socket, sqlite3* db) {
   char* statement = "DELETE FROM ONLINE_USERS WHERE SOCKET=";
   statement = concat(statement, i_to_s(socket));
   statement = concat(statement, "; ");

   exec_db(statement, db);
   free(statement);
}

int access_db(char* login, char* password, sqlite3* db) {
   sqlite3_stmt *result;
   char* statement = "SELECT ID from USERS where LOGIN='";
   statement = concat(statement, login);
   statement = concat(statement, "' AND PASSWORD='");
   statement = concat(statement, password);
   statement = concat(statement, "'");

   int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return false;
   } 
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      free(statement);
      return true;
   }
   else {
      sqlite3_finalize(result);
      free(statement);
      return false;
   }
}

int check_user_db(char* login, sqlite3* db) {
   sqlite3_stmt *result;
   char* statement = "SELECT ID from USERS where LOGIN='";
   statement = concat(statement, login);
   statement = concat(statement, "'");

   int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return false;
   } 
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      free(statement);
      return true;
   }
   else {
      sqlite3_finalize(result);
      free(statement);
      return false;
   }
}

int get_socket_db(char* login, sqlite3* db) {
   int socket = -1;
   sqlite3_stmt *result;
   char* statement = "SELECT SOCKET FROM ONLINE_USERS WHERE LOGIN='";
   statement = concat(statement, login);
   statement = concat(statement, "';");

   int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      socket = atoi((char*)sqlite3_column_text(result, 0));
   
   sqlite3_finalize(result);
   free(statement);
   return socket;
}
/*
void get_chats_by_login_db(char* login) {
   //char* result = NULL;
   int id = get_users_ID(login, data_base);
   char* statement = "SELECT CHAT_ID, USER1_ID, USER2_ID FROM CHATS WHERE USER1_ID=";
   statement = concat(statement, i_to_s(id));
   statement = concat(statement, "OR USER2_ID=");
   statement = concat(statement, i_to_s(id));
   statement = concat(statement, ";");

   exec_db(statement, data_base);

   //return result;
}
*/
void get_chats_by_id_db(int id) {
   char* statement = "SELECT CHAT_ID, USER1_ID, USER2_ID FROM CHATS WHERE USER1_ID=";
   statement = concat(statement, i_to_s(id));
   statement = concat(statement, " OR USER2_ID=");
   statement = concat(statement, i_to_s(id));
   statement = concat(statement, ";");

   exec_db(statement, data_base);

   //return result;
}

int get_users_ID(char* login, sqlite3* db) {
   int id = 0;
   sqlite3_stmt *result;
   char* statement = "SELECT ID FROM USERS WHERE LOGIN='";
   statement = concat(statement, login);
   statement = concat(statement, "';");

   int rc = sqlite3_prepare_v2(db, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      id = atoi((char*)sqlite3_column_text(result, 0));
   
   sqlite3_finalize(result);
   free(statement);
   return id;
}

int create_chat_db(char* u1, char* u2) {
   int chat_id = get_chat_id_by_logins(u1, u2);
   if (chat_id != 0) {
      return chat_id;
   }
   char* statement = "INSERT INTO CHATS(USER1_ID, USER2_ID) VALUES(";
   statement = concat(statement, i_to_s(get_users_ID(u1, data_base)));
   statement = concat(statement, ",");
   statement = concat(statement, i_to_s(get_users_ID(u2, data_base)));
   statement = concat(statement, ");");

   exec_db(statement, data_base);

   free(statement);
   chat_id = get_chat_id_by_logins(u1, u2);
   return chat_id;
}

int get_chat_id_by_logins(char* u1, char* u2) {
   int chat_id = 0;
   int id1 = get_users_ID(u1, data_base);
   int id2 = get_users_ID(u2, data_base);
   sqlite3_stmt *result;
   char* statement = "SELECT CHAT_ID FROM CHATS WHERE USER1_ID=";
   statement = concat(statement, i_to_s(id1));
   statement = concat(statement, " AND USER2_ID=");
   statement = concat(statement, i_to_s(id2));
   statement = concat(statement, ";");

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      chat_id = atoi((char*)sqlite3_column_text(result, 0));
   
   sqlite3_finalize(result);
   free(statement);
   return chat_id;
}

int get_max_chat_id() {
   int id;   
   sqlite3_stmt *result;
   char* statement = strdup("SELECT MAX(CHAT_ID) FROM CHATS");
   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) {
      if ((char*)sqlite3_column_text(result, 0) == NULL) {
         mx_printerr("null\n");
      }
      else {
         id = atoi((char*)sqlite3_column_text(result, 0));
      }
   }
   sqlite3_finalize(result);
   free(statement);
   return id;
}

char* get_users_login(int id) {
   char* login = "";
   sqlite3_stmt *result;
   char* statement = "SELECT LOGIN FROM USERS WHERE ID=";
   statement = concat(statement, i_to_s(id));
   statement = concat(statement, ";");

   int rc = sqlite3_prepare_v2(data_base, statement, -1, &result, 0);    
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(data_base));
      sqlite3_close(data_base);
   }
   rc = sqlite3_step(result);
   if (rc == SQLITE_ROW) 
      login = concat(login, (char*)sqlite3_column_text(result, 0));

   free(statement);
   return login;
}

char** get_chats(char* login) {
   int max_chat_id = get_max_chat_id();
   char** result = malloc(sizeof(char*) * max_chat_id + 1);

   result[max_chat_id] = NULL;
   sqlite3_stmt *res;
   char* statement = "SELECT CHAT_ID, USER1_ID, USER2_ID FROM CHATS WHERE USER1_ID=";
      statement = concat(statement, i_to_s(get_users_ID(login, data_base)));
      statement = concat(statement, " OR USER2_ID=");
      statement = concat(statement, i_to_s(get_users_ID(login, data_base)));
      statement = concat(statement, ";");
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
      int u1 = get_users_ID(login, data_base);
      int u2;
      char* u2_login = "";

      if (rc == SQLITE_ROW) {
         chat_id = atoi((char*)sqlite3_column_text(res, 0));
         chat_u1 = atoi((char*)sqlite3_column_text(res, 1));
         chat_u2 = atoi((char*)sqlite3_column_text(res, 2));

         if (u1 == chat_u1) {
            u2 = chat_u2;
         }
         else if (u1 == chat_u2) {
            u2 = chat_u1;
         }
      }
      else {
                  result[i] = NULL;
         break;

      }
      u2_login = concat(u2_login, get_users_login(u2));
      char* temp = "";
      temp = concat(temp, i_to_s(chat_id));
      temp = concat(temp, "/");
      temp = concat(temp, u2_login);

      result[i] = malloc(sizeof(char) * strlen(temp));
      result[i] = concat(result[i], temp);

      free(statement);
      free(u2_login);
      free(temp);
      i++;
   }
   sqlite3_finalize(res);
   return result;
}


/*
void init_db(sqlite3* data_base, sqlite3* data_base) {
   open_db("Server/databases/users.db", &data_base);
   open_db("Server/databases/chats.db", &data_base);

   exec_db("CREATE TABLE USERS("\
           "ID             INT PRIMARY KEY     NOT NULL,"\
           "LOGIN          TEXT                NOT NULL,"\
           "PASSWORD       TEXT                NOT NULL,"\
           "UNIQUE (ID, LOGIN));", data_base);
   
   exec_db("CREATE TABLE CHATS("\
           "CHAT_ID        INT PRIMARY KEY     NOT NULL,"\
           "USER1_ID       INT                 NOT NULL,"\
           "USER2_ID       INT                 NOT NULL,"\
           "PATH           TEXT                NOT NULL);", data_base);
}
*/
