#include "../inc/header.h"

void mx_recv_file(int sockfd) {
  int n;
  FILE *fp;
  char *filename = "recv.txt";
  char buffer[1024];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, 1024, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, 1024);
  }
  return;
}