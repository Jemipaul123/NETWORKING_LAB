#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<math.h>


int main(){

int sockfd;int data;
struct sockaddr_in servaddr,cliaddr;int b;int connfd;

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

recv(connfd,&data,sizeof(data),0);

printf("the recieved data is %d",data);
int power=data*data;
send(connfd,&power,sizeof(power),0);

exit(1);
close(sockfd);






}
