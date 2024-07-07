#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void main() {
    int sockfd, connfd, ret_val, i = -1;
    char msg[50] = "Received Frame", read_buff[50], write_buff[50];
    fd_set set;
    struct sockaddr_in serv_addr, other_addr;
    struct timeval timeout;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7004);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("Binding failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("--------Sender of Go back N where N=7\n");
    listen(sockfd, 5);

    len = sizeof(other_addr);
    connfd = accept(sockfd, (struct sockaddr *)&serv_addr, &len);
    if (connfd== -1) {
        perror("Accept failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    zero:
    i = i + 1;
    memset(write_buff, 0, sizeof(write_buff));
    strcpy(write_buff, msg);
    write_buff[strlen(msg)] = i + '0';
    printf("To Receiver -> Frame %d\n", i);
    write(connfd, write_buff, sizeof(write_buff));

    i = i + 1;
    sleep(1);

    one:
    memset(write_buff, 0, sizeof(write_buff));
    strcpy(write_buff, msg);
    write_buff[strlen(msg)] = i + '0';
    printf("To Receiver -> Frame %d\n", i);
    write(connfd, write_buff, sizeof(write_buff));

    FD_ZERO(&set);
    FD_SET(connfd, &set);
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    ret_val = select(connfd + 1, &set, NULL, NULL, &timeout);
    if (ret_val == -1) {
        perror("Error in select");
    } else if (ret_val == 0) {
        printf("---- TIMER TIMEOUT - PACKET %d SENT LOST ----\n", i - 1);
        printf("-- RESTART TIMER GO BACK N RESENDING PACKETS\n");
        i = i - 2;
        goto zero;
    } else {
        read(connfd, read_buff, sizeof(read_buff));
        if ((i == 6) || (i == 4) || (i == 1)) {
            printf("From Receiver <- %s CUMULATIVE ACKNOWLEDGEMENT\n", read_buff);
        } else {
            printf("From Receiver <- %s INDIVIDUAL ACKNOWLEDGEMENT\n", read_buff);
        }
        printf("--Wn\n");
        i++;
        if (i > 7) exit(EXIT_SUCCESS);
        if ((i == 5) || (i == 3)) {
            i--;
            goto zero;
        }
        if ((i < 8) || (i != 5)) goto one;
    }

    close(sockfd);
    close(connfd);
}
