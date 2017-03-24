#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<signal.h>


int main(int argc, char**argv){

int tcpSocket,udpSocket;
struct sockaddr_in servaddr,clientaddr;
int n,val;
socklen_t addrlen;
char buffer[65507];
addrlen=sizeof(val);

   tcpSocket=socket(AF_INET,SOCK_STREAM,0);   //For TCP type= SOCK_STREAM
   udpSocket=socket(AF_INET,SOCK_DGRAM,0); //For UDP
	n=getsockopt(tcpSocket,SOL_SOCKET,SO_SNDBUF,&val,&addrlen);
	if(n==-1)
	 printf("error in getSockopt\n");
	else
	{
		printf("TCP socket descriptor:%d\n",tcpSocket);
		printf("System layer:%d\n",SOL_SOCKET);
		printf("Option name: SO_SNDBUF\n");
		printf("Option value:%d\n",val);
		printf("Option len:%d\n",addrlen);
	    printf("\n");
	}	
	
	val=9000;
	addrlen=sizeof(val);
	printf("setting SND_BUF to %d\n",val);
	setsockopt(tcpSocket,SOL_SOCKET,SO_SNDBUF,&val,addrlen);
	printf("getting SND_BUF val again\n");
	n=getsockopt(tcpSocket,SOL_SOCKET,SO_SNDBUF,&val,&addrlen);
		if(n==-1)
		 printf("error in getSockopt\n");
		else
	{
		printf("Option name: SO_SNDBUF\n");
		printf("Option value:%d\n",val);
		  printf("\n");
	}

	n=getsockopt(tcpSocket,SOL_SOCKET,SO_RCVBUF,&val,&addrlen);
	if(n==-1)
	 printf("error in getSockopt\n");
	else
	{
		printf("TCP socket descriptor:%d\n",tcpSocket);
		printf("System layer:%d\n",SOL_SOCKET);
		printf("Option name: SO_RCVBUF\n");
		printf("Option value:%d\n",val);
		printf("Option len:%d\n",addrlen);
		printf("\n");
	}
	val=9000;
	addrlen=sizeof(val);
	printf("setting RCV_BUF to %d\n",val);
	setsockopt(tcpSocket,SOL_SOCKET,SO_RCVBUF,&val,addrlen);
	printf("getting RCV_BUF val again\n");
	n=getsockopt(tcpSocket,SOL_SOCKET,SO_RCVBUF,&val,&addrlen);
		if(n==-1)
		 printf("error in getSockopt\n");
		else
	{
		printf("Option name: SO_RCVBUF\n");
		printf("Option value:%d\n",val);
		  printf("\n");
	}

	n=getsockopt(udpSocket,SOL_SOCKET,SO_SNDBUF,&val,&addrlen);
		if(n==-1)
		 printf("error in getSockopt\n");
		else
	{
		printf("UDP socket descriptor:%d\n",udpSocket);
		printf("System layer:%d\n",SOL_SOCKET);
		printf("Option name: SO_SNDBUF\n");
		printf("Option value:%d\n",val);
		printf("Option len:%d\n",addrlen);
		 printf("\n");
	}
	val=9000;
	addrlen=sizeof(val);
	printf("setting SND_BUF to %d\n",val);
	setsockopt(udpSocket,SOL_SOCKET,SO_SNDBUF,&val,addrlen);
	printf("getting SND_BUF val again\n");
	n=getsockopt(udpSocket,SOL_SOCKET,SO_SNDBUF,&val,&addrlen);
		if(n==-1)
		 printf("error in getSockopt\n");
		else
	{
		printf("Option name: SO_SNDBUF\n");
		printf("Option value:%d\n",val);
		  printf("\n");
	}
	
	n=getsockopt(udpSocket,SOL_SOCKET,SO_RCVBUF,&val,&addrlen);
		if(n==-1)
		 printf("error in getSockopt\n");
		else
	{
		printf("UDP socket descriptor:%d\n",udpSocket);
		printf("System layer:%d\n",SOL_SOCKET);
		printf("Option name: SO_RCVBUF\n");
		printf("Option value:%d\n",val);
		printf("Option len:%d\n",addrlen);
		 printf("\n");
	}
	val=9000;
	addrlen=sizeof(val);
	printf("setting RCV_BUF to %d using setsockopt\n",val);
	setsockopt(udpSocket,SOL_SOCKET,SO_RCVBUF,&val,addrlen);
	printf("getting RCV_BUF val again\n");
	n=getsockopt(udpSocket,SOL_SOCKET,SO_RCVBUF,&val,&addrlen);
		if(n==-1)
		 printf("error in getSockopt\n");
		else
	{
		printf("Option name: SO_RCVBUF\n");
		printf("Option value:%d\n",val);
		  printf("\n");
	}
return 0;
}


