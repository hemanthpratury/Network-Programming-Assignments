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
        cout << "Expected execution : ./#programName# #serverIP/hostName# #portNumber#" << endl;
		return 0;
	}

	int sckt,server,bufferSize = 1024;
    char buffer[bufferSize];
    struct hostent *remoteHost;
    struct sockaddr_in server_addr;
 
    sckt = socket(AF_INET, SOCK_STREAM, 0);

    if (sckt < 0)
    {
        perror("Error establishing a socket !!");
        return 0;
    }

    remoteHost = gethostbyname(argv[1]);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    bcopy((char *)remoteHost->h_addr,(char *)&server_addr.sin_addr,remoteHost->h_length);

    server = connect(sckt,(struct sockaddr *)&server_addr, sizeof(server_addr)) ; 

    if ( server < 0){
        perror("Unable to connect to server !!");
        return 0;
    }

    cout << "Successfully connected to the server..." << endl;
    cout << "please enter the text to communicate to the server " << endl; 
    while(true)
    	{
            memset(buffer,0,strlen(buffer));
	  		cin.getline(buffer,bufferSize);
	       	send(sckt, buffer, strlen(buffer), 0);
	    
	    memset(buffer,0,strlen(buffer));
	   int n = read(sckt,buffer,bufferSize);
		cout << "\n message echo from the server is:  " << buffer << endl;
       	}

    cout << "Server disconnected !! Closing the socket..." << endl ;
    
    close(sckt);

}
