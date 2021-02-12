#include "../inc/header.h"

char* mx_get_client_date() {
   char* time_date = malloc(sizeof(char) * 18);
   long int s_time;
   struct tm *m_time;
   s_time = time (NULL);
   m_time = localtime (&s_time);
   strftime (time_date, 128, "%X %d.%m.%Y", m_time);
   return time_date;
}