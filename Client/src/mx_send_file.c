#include "../inc/header.h"

void mx_send_file(int sockfd, char* filename) {
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("[-]Error in reading file.");
        return;
    }

    int n;
    char data[1024] = {0};

    while(fgets(data, 1024, fp) != NULL) {
        if (send(sockfd, data, sizeof(data), 0) == -1) {
        perror("[-]Error in sending file.");
        exit(1);
    }
    bzero(data, 1024);
  }
}