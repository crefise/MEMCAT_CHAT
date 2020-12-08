#include "header.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i = 0; i < argc; i++)
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   return 0;
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
   sqlite3_close(db);
}

void add_user(int* id, char* login, char* password, sqlite3* db) {
   (*id)++;
   char* id_s = i_to_s(*id);

   char* statement = "INSERT INTO USERS (ID,LOGIN,PASSWORD) VALUES (";
   statement = concat(statement, id_s);
   statement = concat(statement, ", '");
   statement = concat(statement, login);
   statement = concat(statement, "', '");
   statement = concat(statement, password);
   statement = concat(statement, "'); ");

   exec_db(statement, db);
   free(statement);
   free(id_s);
}

int access(char* login, char* password, sqlite3* db) {
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
      char* ID_c = sqlite3_column_text(result, 0);
      int ID = 0;
      //printf("USER ID = %s\n", sqlite3_column_text(result, 0));
      sqlite3_finalize(result);
      free(statement);
      
      free(ID_c);
      return true;
   }
   else {
      sqlite3_finalize(result);
      free(statement);
      return false;
   }
}

void init_db(sqlite3* users_db, sqlite3* chats_db) {
   open_db("databases/users.db", &users_db);
   open_db("databases/chats.db", &chats_db);

   exec_db("CREATE TABLE USERS("\
           "ID             INT PRIMARY KEY     NOT NULL,"\
           "LOGIN          TEXT                NOT NULL,"\
           "PASSWORD       TEXT                NOT NULL,"\
           "UNIQUE (ID, LOGIN));", users_db);
   
   exec_db("CREATE TABLE CHATS("\
           "CHAT_ID        INT PRIMARY KEY     NOT NULL,"\
           "USER1_ID       INT                 NOT NULL,"\
           "USER2_ID       INT                 NOT NULL,"\
           "PATH           TEXT                NOT NULL);", chats_db);
}