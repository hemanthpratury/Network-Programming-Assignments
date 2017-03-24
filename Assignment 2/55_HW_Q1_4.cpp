#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

//the thread function
void *newThread_handler(void *);

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

    struct sockaddr_in server_addr,client_addr;
    socklen_t size;

    sckt = socket(AF_INET, SOCK_STREAM, 0);

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
        return -1;
    }

    size = sizeof(server_addr);
    cout << "Waiting for clients to connect..." << endl;

    listen(sckt , 5);
    pthread_t thread_id;
	
	while(client = accept(sckt,(struct sockaddr *)&client_addr, &size))
	{
		cerr << "Connected to client: IP " << inet_ntoa(client_addr.sin_addr) << "  Port :" << client_addr.sin_port << endl;
		if(client < 0)
    	{
        	cerr << "Error accepting the connection..!!" << endl;
        	return 1;
    	}
		
		if( pthread_create( &thread_id , NULL ,  newThread_handler , (void*) &client) < 0)
        {
            perror("could not create thread");
            return -1;
        }
	}
		
		if (client < 0)
    	{
        	perror("accept failed");
        	return 1;
    	}
     
    return 0;
}

void *newThread_handler(void *sckt)
{
    //Get the socket descriptor
    int sock = *(int*)sckt;
    int data_len;
    char *message , client_message[2000];	
  
    //Receive a message from client
    while( (data_len = recv(sock , client_message , 2000 , 0)) > 0 )
    {
   		if(data_len == 0)
    		{
        		cout << "Client disconnected"    << endl;
   				close(sock);
    		}
		
		if(data_len)
            {
                 cout << "\n message received from client is : " << client_message << endl;
				 write(sock,client_message,2000);
            }
						
		//Send the message back to client => echo
        write(sock , client_message , strlen(client_message));
		
		//clear the message buffer
		memset(client_message, 0, 2000);
    }
 
    if(data_len == -1)
    {
        cerr << "recv failed" << endl;
		close(sock);
		
    }
         
    return 0;
} 
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
