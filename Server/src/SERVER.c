#include "header.h"

int main(int argc, char* argv[]) {
   int count_users = 1;
   sqlite3* users_db;
   sqlite3* chats_db;
   init_bd(&users_db, &chats_db);
   
   close_db(users_db);
   close_db(chats_db);
   return 0;
}
