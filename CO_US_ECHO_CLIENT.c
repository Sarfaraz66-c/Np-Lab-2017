#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int sockfd,rval,clen,nsfd,slen;
	char rmsg[20],smsg[20];
	struct sockaddr_in s,c,sname,cname;
	s.sin_family=AF_INET;
	s.sin_port=htons(atoi(argv[2]));
	s.sin_addr.s_addr=inet_addr(argv[1]);// already in string format need not convert
	clen=sizeof(c);
	slen=sizeof(sname);
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
	getsockname(sockfd,(struct sockaddr *)&sname,&slen);
	printf("\n SER: My name is %s,%d",inet_ntoa(sname.sin_addr.s_addr),ntohs(sname.sin_port));
	rval=listen(sockfd,5);
	if(rval<0)
	{	
		perror("SER: unable to listen");
		exit(1);
	}
	printf("\n server is listening \n");
	while(1)
	{
	nsfd=accept(sockfd,(struct sockaddr *)&c,&clen);
	if(nsfd<0)
	{
		perror("SER: unable to accept");
		exit(1);
	}
	clen=sizeof(cname);
	getpeername(nsfd,(struct sockaddr *)&cname,&clen);
	printf("\n My clients details are %s, %d",inet_ntoa(cname.sin_addr.s_addr),ntohs(cname.sin_port));	
	rval=recv(nsfd,(char *)rmsg,sizeof(rmsg),0);

	if(rval<0)
	{
	
		perror("\n SER: unable to recv ");
		exit(1);
	}
	
	printf("SER:Message Recvd Succesfully\n");
	rval=send(nsfd,(char *)rmsg,sizeof(rmsg),0);	
	if(rval<0)
	{
		perror(" SER:unable to echoed");
		exit(1);
	}
	
	printf("SER:Message Echoed to client\n");
	close(nsfd);
}//end of while loop
}
