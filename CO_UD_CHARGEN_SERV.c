#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
int main()
{
	int sockfd,rval;
	char rmsg[20],smsg[20];
	struct sockaddr_in s;
	s.sin_family=AF_INET;
	s.sin_port=htons(7);//network byte ordering routine//
	s.sin_addr.s_addr=inet_addr("10.2.0.7");
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
	printf("\n Enter a message to be Echoed");
	scanf("%s",smsg);
	rval=send(sockfd,(char *)smsg,sizeof(smsg),0);
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
