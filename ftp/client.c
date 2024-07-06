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
char name[20],fname[20];
FILE *fp;
struct sockaddr_in servaddr,cliaddr;
int sockfd;int b;int s;
char rcvg[100];

sockfd=socket(AF_INET,SOCK_STREAM,0);
int c;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(8081);
int a=sizeof(servaddr);
c=connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(c<0)
{printf("connection not successful\n");
}
else{
printf("connection successful\n");
}

printf("enter the name of the old file");
scanf("%s",name);
printf("enter the name of the new file");
scanf("%s",fname);

send(sockfd,name,sizeof(name),0);
fp=fopen(fname,"w");

while(1)
{
   s=recv(sockfd,rcvg,sizeof(rcvg)-1,0);
   if(s<0)
   {
   printf("can't receive the file contents\n");
   exit(0);
   }
   rcvg[s]='\0';
   
   if(strcmp(rcvg,"error")==0)
   {
   printf("there's error in receiving\n");
   
   }
   else if(strcmp(rcvg,"completed")==0)
   {
   printf("file is transferred\n");
   }
   else{
   fputs(rcvg,stdout);
   fputs(rcvg,fp);
   
   }
return(0);
}



}
