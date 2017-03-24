#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include<string.h>


#define BUFFER_LENGTH    250


void main()
{
  
   int sd=-1, sdconn=-1;
   int rc, on=1;
   char buffer[BUFFER_LENGTH];
   struct sockaddr_in6 serveraddr, clientaddr;
   int addrlen=sizeof(clientaddr);

   time_t ticks;

  
      sd = socket(AF_INET6, SOCK_STREAM, 0);
	serveraddr.sin6_family = AF_INET6;
      serveraddr.sin6_port   = htons(4181);
      
      serveraddr.sin6_addr   = in6addr_any;
      
      bind(sd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
      
      listen(sd, 10);
      
      printf("Ready for client connect().\n");

      sdconn = accept(sd, NULL, NULL);
      printf("Connected...\n");
     

       ticks=time(NULL);
	snprintf(buffer,sizeof(buffer),"%.24s\r\n",ctime(&ticks));
	printf("before sending from server\n");
	write(sdconn,buffer, strlen(buffer));

 
      close(sd);
      close(sdconn);

}


