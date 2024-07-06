#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<netdb.h>


int main(){
FILE *fp;
char fileread[100];
struct sockaddr_in servaddr,cliaddr;
int sockfd;int b;
char rcv[100];int n;

sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(8081);
int a=sizeof(servaddr);

b=bind(sockfd,(struct sockaddr*)&servaddr,a);
if(b<0)
{
printf("Can't bind\n");
}
else{
printf("binded successfully\n");
}
listen(sockfd,5);
printf("server is listening\n");

int connfd=accept(sockfd,(struct sockaddr*)&servaddr,&a);
if(connfd<0)
{printf("connection not set up\n");
}
else{
printf("connection set up\n");
}

n=recv(connfd,rcv,100,0);
rcv[n]='\0';
fp=fopen(rcv,"r");
if(fp==NULL)
{
printf("the file can't be opened\n");
send(connfd,"error",5,0);
exit(0);

}
else{
while(fgets(fileread,sizeof(fileread),fp))
{
     if(send(connfd,fileread,100,0),0)
     {printf("cant send file contents\n");
     sleep(1);
     }
     
     if(!fgets(fileread,sizeof(fileread),fp))
     {
     send(connfd,"completed",9,0);
     }
     return 0;
     
     
     


}

}







}
