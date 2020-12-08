#include "../inc/header.h"

char* i_to_s(int n) {
   int length = snprintf(NULL, 0, "%d", n);
   char* result = malloc( length + 1 );
   snprintf(result, length + 1, "%d", n);
   return result;
}

char* concat(char* s1, char* s2) {
   int len1 = strlen(s1);
   int len2 = strlen(s2);                      
   char *result = malloc(len1 + len2 + 1);
   if (!result) {
      fprintf(stderr, "malloc() failed: insufficient memory!\n");
      return NULL;
   }
   memcpy(result, s1, len1);
   memcpy(result + len1, s2, len2 + 1);    
   return result;
}
