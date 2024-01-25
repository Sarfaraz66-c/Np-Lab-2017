#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
int main()
{
	int sockfd,rval,slen;
	char rmsg[20],smsg[20];
	struct sockaddr_in s,c;
	s.sin_family=AF_INET;
	s.sin_port=htons(13);//network byte ordering routine//
	s.sin_addr.s_addr=inet_addr("10.2.0.7");
	sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sockfd<0)
	{
	
		perror("unable to create a socket");

		exit(1);
	}	
	printf("socket created with id %d \n	",sockfd);
	c.sin_family=AF_INET;
	c.sin_port=htons(5313);
	c.sin_addr.s_addr=inet_addr("10.2.0.7");
	rval=bind(sockfd,(struct sockaddr*)&c,sizeof(c));
	if(rval<0)
	{
		perror("unable to bind");
		exit(1);
	}
//	printf("\n Enter a message to be Echoed");
//	scanf("%s",smsg);
	rval=sendto(sockfd,(char *)smsg,sizeof(smsg),0,(struct sockaddr*)&s,sizeof(s));
	slen=sizeof(s);
	rval=recvfrom(sockfd,(char *)rmsg,sizeof(rmsg),0,(struct sockaddr *)&s,&slen);
	if(rval<0)
	{
		perror("unable to rcv");
		exit(1);
	}
	printf("\n rcvd msg is %s",rmsg);
	printf("\n client terminating");
	close(sockfd);
}
