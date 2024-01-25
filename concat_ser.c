#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
int main(int agrc,char *argv[])
{
	int sockfd,rval;
	char rmsg[20],smsg1[20],smsg2[20];
	struct sockaddr_in s;
	s.sin_family=AF_INET;
	s.sin_port=htons(atoi(argv[2]));//network byte ordering routine//
	s.sin_addr.s_addr=inet_addr(argv[1]);
	sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockfd<0)
{
	
		perror("unable to create a socket");

		exit(1);
}	
printf("socket created with id %d \n	",sockfd);
	rval=connect(sockfd,(struct sockaddr *)&s,sizeof(s));
	if(rval<0)
{	
		perror("connection failed");
		exit(1);
}	
	printf("\n connection established sucessfully");
	printf("\n Enter a first message to be entered");
	scanf("%s",smsg1);
	printf("\n enter a second msg to be entered \n");
	scanf("%s",smsg2);
	rval=send(sockfd,(char *)smsg1,sizeof(smsg1),0);
	rval=send(sockfd,(char *)smsg2,sizeof(smsg2),0);
	rval=recv(sockfd,(char *)rmsg,sizeof(rmsg),0);
	if(rval<0)
{
perror("unable to rcv");
exit(1);
}


printf("\n rcvd msg is %s",rmsg);
printf("\n client terminating");
close(sockfd);
}
