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
   statement = concat(statement, "'");

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