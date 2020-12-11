#include "../inc/header.h"
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

char* i_to_s(int n) {
   int length = snprintf(NULL, 0, "%d", n);
   char* result = malloc( length + 1 );
   snprintf(result, length + 1, "%d", n);
   return result;
}

char *clear_buffer(char *s1) {
   for (int i = 0; i < strlen(s1); i++) {
      s1[i] = '\0';
   }
   return s1;
}
char *mx_strnew(const int size) {
    if (size < 0) {
        return NULL;
    }
    char *result = (char *)malloc(size + 1);
    for (int i = 0; i < size+1; i++)
    {
        result[i] = '\0';
    }
    return result;
}

void mx_strdel(char **str) {
    free(*str);
    *str = NULL;
}