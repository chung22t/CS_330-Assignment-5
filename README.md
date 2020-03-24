# CS_330-Assignment-5
/* The goal of this assignment is socket communication between a server and a client.
   This program is to resemble a jeopardy game. A client will connect to the server (game master). The client will get to pick
   what category and what difficulty (harder questions reward nore points). The player will only have 3 lives. that is if they make 
   more than 3 mistakes, it is game over.
*/

/* 
Mar. 23 
-included information about the game
-server will ask client (player) for category and what difficulty
-client messages for category & difficulty received  by server
- next step is to continue this process for the other categories and begin writing the questions of the game.
*/

/* The following is the code for the server (game master) */

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;
#define PORT 8080

void *display() { printf("|Math|----|Science|----|History|\n"); printf("|$10|-----|$10|--------|$10|\n"); printf("|$20|---|$20|--------|$20|\n");

return NULL; }

int main(int argc, char const *argv[])
{
const int MsgLen = 100;
int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = {0};
char *hello = "Hello from server";
char *category ="Please select s or h";
int LIVES = 3;
 //char *PickSciLev = "You selected science. Pick level ($10, $25, $50)";

// Creating socket file descriptor
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
{
    perror("socket failed");
    exit(EXIT_FAILURE);
}

// Forcefully attaching socket to the port 8080
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                              &opt, sizeof(opt)))
{
    perror("setsockopt");
    exit(EXIT_FAILURE);
}
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons( PORT );

// Forcefully attaching socket to the port 8080
if (bind(server_fd, (struct sockaddr *)&address,
                             sizeof(address))<0)
{
    perror("bind failed");
    exit(EXIT_FAILURE);
}
if (listen(server_fd, 3) < 0)
{
    perror("listen");
    exit(EXIT_FAILURE);
}
if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                   (socklen_t*)&addrlen))<0)
{
    perror("accept");
    exit(EXIT_FAILURE);
}
/*valread = read( new_socket , buffer, 1024);
printf("%s\n",buffer );
send(new_socket , hello , strlen(hello) , 0 );
printf("Hello message sent\n");*/

valread = read(new_socket, buffer, 1024);
printf("%s\n", buffer);
send(new_socket, category, strlen(category), 0);

/*valread = read(new_socket, buffer, 1024);
printf(%s\n, buffer);
send(new_socket, display, buffer, 1024);*/

memset (buffer, 0, 1024);
recv(new_socket, buffer, 1, 0);
//cout << buffer;
printf("%s\n", buffer);
cout << buffer << endl;


if (strcmp("s",buffer) == 0)
{
 //Ask user to select a difficulty level
 char *PickSciLev = "You selected science. Pick level (enter 1 for $10, 2 for  $25, 3 for $50)";
 memset (buffer, 0, 1024);
 printf("%s\n", buffer);
 send(new_socket, PickSciLev, strlen(PickSciLev), 0);

//receive the difficulty level input from user
 //memset(buffer, 0, 1024);
 int count = recv(new_socket, buffer, 1, 0);
 cout << count;
 cout << buffer;

 if (count == 1)
 {
   cout << "You selected Science for $10";
 }
 else
 {
  cout <<"Errir";
 }
}
else
{
 cout << "Incorrect";
}


 return 0;
}
