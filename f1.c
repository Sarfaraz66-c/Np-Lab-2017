#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
int main()
{
char rmsg[20],smsg[20];
int sockfd,rval;
struct sockaddr_in s;
s.sin_family=AF_INET;
s.sin_port=htons(7);
s.sin_addr.s_addr=inet_addr("10.2.0.7");
sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(sockfd<0)
{
perror("unable to create socket");
exit(1);
}
printf("socket created with id %d \n",sockfd);
rval=connect(sockfd,(struct sockaddr *)&s,sizeof(s));
if(rval<0)
{
perror("unable to connect");
exit(1);
}
printf("connection established \n");
printf("enter the message \n");
scanf("%s",smsg);
rval=send(sockfd,(char *)smsg,sizeof(smsg),0);
rval=recv(sockfd,(char *)rmsg,sizeof(rmsg),0);
if(rval<0)
{
perror("cannot received");
exit(1);
}
printf("msg recv is %s \n",rmsg);
close(sockfd);
}




