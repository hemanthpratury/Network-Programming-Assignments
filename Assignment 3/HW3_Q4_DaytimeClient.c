#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_LENGTH    250
#define FALSE              0
#define SERVER_NAME     "0:0:0:0:0:0:0:1"
#define HOST_LENGTH 256


int main(int argc, char**argv)
{

   int    sd=-1, rc, bytesReceived=0;
   char   buffer[BUFFER_LENGTH];
   char   server[HOST_LENGTH];
   char   servport[] = "4181";
   struct in6_addr serveraddr;
   struct addrinfo hints, *res=NULL;

       strcpy(server, SERVER_NAME);

      memset(&hints, 0x00, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
    
      rc = getaddrinfo(server, servport, &hints, &res);
      if (rc != 0)
      {
         printf("ERROR --> %s\n", gai_strerror(rc));
         return 0;
      }
	 

      sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
      rc = connect(sd, res->ai_addr, res->ai_addrlen);
      if (rc < 0)
      {
         printf("ERROR --> %s\n", gai_strerror(rc));
         return 0;
      }
      printf("Connected...\n");
     
     int n=read(sd,buffer,1024);
	if(n>0){
	buffer[n]=0;
	//printf("%s\n",buffer);
	if(fputs(buffer,stdout)==EOF)
	perror("fputs error\n");	 
	}
	else
	{	
	perror("read error\n");

	}
   
   
      close(sd);
      freeaddrinfo(res);
}
