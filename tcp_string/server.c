#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(){

int sockfd;
struct sockaddr_in servaddr,cliaddr;char buffer[50];int b;int connfd;

sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(8081);

int a=sizeof(servaddr);
socklen_t len=sizeof(cliaddr);

b=bind(sockfd,(struct sockaddr*)&servaddr,a);
if(b<0)
{
printf("Can't bind\n");
exit(1);
}
else{
printf("binded successfully\n");
}
listen(sockfd,5);
printf("server is listening\n");

connfd=accept(sockfd,(struct sockaddr*)&servaddr,&a);
if(connfd<0)
{
printf("connection not set up");
}
else{
printf("connection is set\n");}

recv(connfd,buffer,sizeof(buffer),0);
int length=strlen(buffer);

send(connfd,&length,sizeof(length),0);
printf("sending length\n");

exit(1);
close(sockfd);






}
