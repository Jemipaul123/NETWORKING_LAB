#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<netdb.h>


void main(){

int sockfd;
struct sockaddr_in servaddr,cliaddr;
char buffer[50];int length;
int c;
sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(8081);

c=connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(c<0)
{printf("connection not successful\n");

}
else{
printf("connection successful\n");
}

printf("enter the string to be send\n");
scanf("%s",buffer);
printf("sending the string to server\n");
send(sockfd,buffer,sizeof(buffer),0);
recv(sockfd,&length,sizeof(length),0);
printf("the size of string received is %d",length);
exit(1);
close(sockfd);






}
