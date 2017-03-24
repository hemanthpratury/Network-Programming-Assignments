#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

using namespace std;
 
int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        cout << "Expected execution : ./#programName# #portNumber#" <<endl;
        return 0;
    }
    
fd_set readset, tempset;
int maxfd, flags;
int sckt, newsckt, j, result, result1, sent;
timeval tv;
int portNumber = atoi(argv[1]);
int MAX_BUFFER_SIZE = 1024;
char buffer[MAX_BUFFER_SIZE+1];

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
        return 0;
    }

    cout << "Waiting for clients to connect..." << endl;

    listen(sckt , 0);

//select protocol begins
FD_ZERO(&readset);
FD_SET(sckt, &readset);
maxfd = sckt;

do {
   memcpy(&tempset, &readset, sizeof(tempset));
   tv.tv_sec = 30;
   tv.tv_usec = 0;
   result = select(maxfd + 1, &tempset, NULL, NULL, &tv);

   if (result == 0) {
      cout << "select() timed out!" << endl;
   }
   else if (result < 0 && errno != EINTR) {
      cerr << "Error in select():" << strerror(errno) << endl;
   }
   else if (result > 0) {

      if (FD_ISSET(sckt, &tempset)) {
         size = sizeof(server_addr);
		 newsckt = accept(sckt,(struct sockaddr *)&client_addr, &size);
         if (newsckt < 0) {
            cerr << "Error in accept(): " << strerror(errno) << endl;
			
         }
         else {
            FD_SET(newsckt, &readset);
            maxfd = (maxfd < newsckt)?newsckt:maxfd;
         }
         FD_CLR(sckt, &tempset);
      }

      for (j=0; j<maxfd+1; j++) {
         if (FD_ISSET(j, &tempset)) {

            do {
               result = recv(j, buffer, MAX_BUFFER_SIZE, 0);
            } while (result == -1 && errno == EINTR);

            if (result > 0) {
               buffer[result] = 0;
               cout << "Echoing client :" << buffer << endl;
               sent = 0;

               do {
                  result1 = send(j, buffer+sent, result-sent, MSG_NOSIGNAL);
                  if (result1 > 0)
                     sent += result1;
                  else if (result1 < 0 && errno != EINTR);
                     break;
                } while (result > sent);

            }
            else if (result == 0) {
               close(j);
               FD_CLR(j, &readset);
            }
            else {
               cerr << "Error in recv(): " << strerror(errno) << endl;
            }
         }      
      }     
   }      
} while (1);
}