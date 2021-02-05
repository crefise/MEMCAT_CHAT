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

void mx_strdel(char **str) {
    free(*str);
    *str = NULL;
}

void mx_printerr(const char *s) {
   write(2, s, strlen(s));
}
void mx_printerrln(const char *s) {
   write(2, s, strlen(s));
   write(2, "\n", 1);
}

char *mx_strncpy(char *dst, const char *src, int len) {
    dst = mx_strnew(len);
   for (int i = 0; i < len; i++) {
        if (dst) {
            if(src) {
                dst[i] = src[i];
            }
           else {
                dst[i] = '\n';
           }
        }
        else {
           return dst;
        }
   }
   return dst;
}

bool mx_isdigit(char c) {
    char alphabet[] = "0123456789";
    char *letter = alphabet;
    while (*letter != '\0' && *letter != c) {
        ++letter;
    }
    if (*letter) {
        return true;
    }
    return false;
}
