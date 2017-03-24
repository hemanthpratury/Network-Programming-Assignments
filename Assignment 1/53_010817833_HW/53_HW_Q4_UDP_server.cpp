#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
 
int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        cout << "Expected execution syntax : ./#programName# #portNumber#" <<endl;
        return 0;
    }

    int sckt,client,data_len;
    int portNumber = atoi(argv[1]);
    int bufferSize = 1024;
    char buffer[bufferSize];

    struct sockaddr_in server_addr,client_addr;
    socklen_t size;

    sckt = socket(AF_INET, SOCK_DGRAM, 0);

    if (sckt < 0)
    {
        perror("Error establishing a socket !!");
        return 0;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNumber);

    if ((bind(sckt, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0)
    {
        perror("Error binding the connection !!");
        return 0;
    }

    size = sizeof(server_addr);
    cout << "Waiting for UDP connections..." << endl << endl;
    
	data_len = 1;
	socklen_t clientlen=sizeof(client_addr);

    while(data_len)
    {
            //Receiving message 
	data_len = recvfrom(sckt,buffer,bufferSize,0, (struct sockaddr *)&client_addr, &clientlen);              
		  if(data_len < 0)
                {
		cout << "error in reception" << endl;
		}                     
		cout <<"\n message received is :  " << buffer << endl;

		sendto(sckt, buffer, bufferSize, 0, (struct sockaddr *)&client_addr,clientlen);
                
            	memset(buffer,0,bufferSize);
    }

    cout << "\n Client disconnected !! Closing the server socket" << endl;

    close(client);
    close(sckt);

}
