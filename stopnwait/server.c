#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int sockfd;
    char servmsg[2000], climsg[2000];
    struct sockaddr_in servaddr, cli;int data;
    socklen_t client_struct_length = sizeof(cli);int ack;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Error while creating socket...\n");
        exit(1);
    }
    printf("Socket created successfully..\n");

    // Set server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8081);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        printf("Couldn't bind to port...\n");
        exit(1);
    }
    printf("Binding done...\n");
    printf("Listening...\n");
while(1){
    // Receive message from client
    if (recvfrom(sockfd, (char*)&data, sizeof(data), 0, (struct sockaddr*)&cli, &client_struct_length) < 0) {
        printf("Couldn't receive\n");
        exit(1);
    }
    printf("Message from client: %d\n", data);

    // Copy client's message to server's response
    printf("enter the acknowledgement \n");
    scanf("%d",&ack);

    // Send message back to client
    if (sendto(sockfd, (char*)&ack, sizeof(ack), 0, (struct sockaddr *)&cli, client_struct_length) < 0) {
        printf("Can't send\n");
        exit(1);
    }}

    // Close the socket
    close(sockfd);

    return 0;
}
