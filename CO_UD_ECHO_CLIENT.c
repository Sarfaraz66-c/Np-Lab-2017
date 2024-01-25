#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int sockfd,rval,clen,nsfd,fd;
	char rmsg[20];
	struct sockaddr_in s,c;
	s.sin_family=AF_INET;
	s.sin_port=htons(atoi(argv[2]));
	s.sin_addr.s_addr=inet_addr(argv[1]);// already in string format need not convert
	clen=sizeof(c);
	sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockfd<0)
	{
		perror("SER: unable to create socket");
		exit(1);
	}
	printf("socket created with id %d\n",sockfd);
	rval=bind(sockfd,(struct sockaddr *)&s,sizeof(s));
	if(rval<0)
	{
		perror("SER: unable to bind");
		exit(1);
	}
	printf("SER: bind succesfully");
	rval=listen(sockfd,5);
	if(rval<0)
	{	
		perror("SER: unable to listen");
		exit(1);
	}
	printf("server is listening \n");
	while(1)
	{
	nsfd=accept(sockfd,(struct sockaddr *)&c,&clen);
	if(nsfd<0)
	{
		perror("SER: unable to accept");
		exit(1);
	}
	system("date > f2.c");
	fd=open("f2.c",O_RDONLY);
	read(fd,(char *)rmsg,sizeof(rmsg),0);
	
/*rval=recv(nsfd,(char *)rmsg,sizeof(rmsg),0);

	if(rval<0)
	{
	
		perror("\n SER: unable to recv ");
		exit(1);
	}*/
	
	printf("SER:Message Recvd Succesfully\n");
	rval=send(nsfd,(char *)rmsg,sizeof(rmsg),0);	
	if(rval<0)
	{
		perror(" SER:unable to send");
		exit(1);
	}
	
	printf("SER:Message Echoed to client\n");
	close(nsfd);
}//end of while loop
}
