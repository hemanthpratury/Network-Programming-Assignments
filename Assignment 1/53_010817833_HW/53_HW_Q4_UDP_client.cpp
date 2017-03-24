#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
 
int main(int argc, char *argv[])
{
	if(argc < 3)
	{
        cout << "Expected execution syntax : ./#programName# #serverIP/hostName# #portNumber#" << endl;
		return 0;
	}

    int sckt,server,bufferSize = 1024;
    char buffer[bufferSize];
    struct hostent *remoteHost;
    struct sockaddr_in server_addr,client_addr;
 
    sckt = socket(AF_INET, SOCK_DGRAM, 0);

    if (sckt < 0)
    {
        perror("Error establishing a socket !!");
        return 0;
    }

    remoteHost = gethostbyname(argv[1]);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    bcopy((char *)remoteHost->h_addr,(char *)&server_addr.sin_addr,remoteHost->h_length);

   
        socklen_t serverlen = sizeof(server_addr);
	socklen_t clientlen = sizeof(client_addr);
    	while(true)
	{
            	memset(buffer,0,strlen(buffer));
		cout << "\n Please enter the text " << endl;
		fgets(buffer,bufferSize,stdin);	  		
	        sendto(sckt, buffer, bufferSize, 0, (struct sockaddr *)&server_addr,serverlen);
		
		memset(buffer,0,strlen(buffer));
	   	int n = read(sckt,buffer,bufferSize);
		cout << "\n message echo from the server is:  " << buffer << endl;
       	}

    
    close(sckt);

}
