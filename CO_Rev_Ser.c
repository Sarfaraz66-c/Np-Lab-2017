#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(int argc,char *argv[])
{
	int sockfd,rval,clen;
	char smsg[20],rmsg[20];
	struct sockaddr_in s,c;
	s.sin_family=AF_INET;
	s.sin_port=htons(atoi(argv[2]));
	s.sin_addr.s_addr=inet_addr(argv[1]);
	sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sockfd<0)
	{
		perror("unable to create a socket");
		exit(1);
	}
	printf("socket created with id %d\n",sockfd);
	rval=bind(sockfd,(struct sockaddr *) &s,sizeof(s));
	if(rval<0)
{	
	perror("unable to bind");
		exit(1);
}
	clen=sizeof(c);
	while(1)
{
	rval=recvfrom(sockfd,(char *)rmsg,sizeof(rmsg),0,(struct sockaddr *)&c,&clen);
		if(rval<0)
	{
		perror("unable to recv from client");
		exit(1);
	}
	rval=sendto(sockfd,(char *)rmsg,sizeof(rmsg),0,(struct sockaddr *)&c,sizeof(c));
	if(rval<0)
	{
		perror("unable to sent to client ");
		exit(1);
	}
	printf("\n recv msg is %s",rmsg);
	printf("\n server termination ");
}
	close(sockfd);
}
