#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int clientfd;
    char servmsg[2000], climsg[2000];
    struct sockaddr_in servaddr, cli;
    socklen_t server_struct_length = sizeof(servaddr);

    // Create socket
    clientfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientfd < 0) {
        printf("Error while creating socket...\n");
        exit(1);
    }
    printf("Socket created successfully..\n");

    // Set server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8081);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Get message from user
    printf("Enter a message: ");
    fgets(climsg, sizeof(climsg), stdin);

    // Send message to server
    if (sendto(clientfd, climsg, strlen(climsg), 0, (struct sockaddr *)&servaddr, server_struct_length) < 0) {
        printf("Can't send\n");
        exit(1);
    }

    // Receive message from server
    if (recvfrom(clientfd, servmsg, sizeof(servmsg), 0, (struct sockaddr*)&servaddr, &server_struct_length) < 0) {
        printf("Couldn't receive\n");
        exit(1);
    }

    // Print server message
    printf("Message from server: %s\n", servmsg);

    // Close socket
    close(clientfd);

    return 0;
}
