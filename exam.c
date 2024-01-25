#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
struct emp
{
	float bp,hra,da,epf,pt,net;
};
int main(int agrc,char *argv[])
{
	struct emp sa;
	int sockfd,rval;
	char rmsg[20],smsg[20];
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
	printf("\n Enter a basic pay");
	scanf("%s",&sa.bp);
	
	printf("\n Enter house rental allowance");
	scanf("%s",&sa.hra);

	printf("\n Enter DA");
	scanf("%s",&sa.da);

	printf("\n Enter emplym,ent provision funds");
	scanf("%s",&sa.epf);

	printf("\n Enter provision tax");
	scanf("%s",&sa.pt);
	
	rval=send(sockfd,(struct emp *)&sa,sizeof(sa),0);
	rval=recv(sockfd,(struct emp *)&sa,sizeof(sa),0);
	if(rval<0)
{
perror("unable to rcv");
exit(1);
}


printf("\n rcvd msg is %f",sa.net);
printf("\n client terminating");
close(sockfd);
}
