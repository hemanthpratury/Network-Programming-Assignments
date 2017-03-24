#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
 
int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        cout << "Expected execution : ./#programName# #portNumber#" <<endl;
        return 0;
    }

    int sckt,client,data_len;
    int portNumber = atoi(argv[1]);
    int bufferSize = 1024;
    char buffer[bufferSize];

    struct sockaddr_in server_addr,client_addr;
    socklen_t size;

    sckt = socket(AF_INET, SOCK_STREAM, 0);

    if (sckt < 0)
    {
        cerr << "Error establishing a socket !!" << endl;
        return 0;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNumber);

    if ((bind(sckt, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0)
    {
        cerr << "Error binding the connection !!" << endl ;
        return 0;
    }

    size = sizeof(server_addr);
    cout << "Waiting for clients to connect..." << endl;

    listen(sckt , 5);
    
	while(1)
	{
		client = accept(sckt,(struct sockaddr *)&client_addr, &size);
		cerr << "Connected to client: IP " << inet_ntoa(client_addr.sin_addr) << "  Port :" << client_addr.sin_port << endl;
		if(client < 0)
    	{
        	cerr << "Error accepting the connection..!!" << endl;
        	return 1;
    	}
	
	int pid = fork();	
	if(pid == 0)
	{
    	while(data_len)
    	{
            data_len = recv(client, buffer, bufferSize, 0);
			    if(data_len == 0)
			    { 
				    close(client);
			 	    break;
			    }
                if(data_len)
                {
                    cout <<"\n message received from client is : " << buffer << endl;
					write(client,buffer,bufferSize);
                }
            memset(buffer,0,bufferSize);
    	}
	}
	else 
	{
		close(client);
	}
    }
}
