#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
int main(int agrc,char *argv[])
{
	int sockfd,rval;
	char rmsg[128];
	struct sockaddr_in s;
	s.sin_family=AF_INET;
	s.sin_port=htons(atoi(argv[2]));
	s.sin_addr.s_addr=inet_addr(argv[1]);
	sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockfd<0)
	{
		perror("unable to create a socket");
		exit(1);
	}
	printf("socket created with id %d \n",sockfd);
	rval=connect(sockfd,(struct sockaddr *)&s,sizeof(s));
	if(rval<0)
	{
		perror("connection failed");
		exit(1);
	}
	printf("\n connection established sucessfully ");
	rval=recv(sockfd,(char *)rmsg,sizeof(rmsg),0);
	if(rval<0)
	{
		perror("unable tp recv ");
		exit(1);
	}
	printf("\n received msg is %s",rmsg);
	printf("\n client terminating ");
	close(sockfd);
}
