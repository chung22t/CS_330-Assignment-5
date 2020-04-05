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

Mar. 30
-server begins asking questions for client
-client begins responding to questions
-current challenge is trying to get the server and client to keep continuing to play the game or exit if the client requests to.

Apr. 5
-Server has asked client a category of questions.
-Server will ask client to select one of two categories (science or history).
-I am planning to add a couple more categories such as math and/or geography.
-Server will ask client for category and difficulty level. Then server will ask client quesiton.
-Server will send message to client if they are correct or incorrrect.
-Current issue right now is to get game to keep looping until client run out of lives

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
 int LifeBuffer[1] ={0};
 char answer[MsgLen] = {0};
 //int quit = 0;
 char *quitMSG = "Do you want to quit?";
 char QuitBuffer[MsgLen] = {0};
 char CAT[1] = {0};
 char *ClientAnswer;
 char quit;
 char *correct = "You are correct!";

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

for (;;)
{
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

/**********************************Science*****************************************/
  if (strcmp("s",buffer) == 0)
  {
   //Ask user to select a difficulty level
   char *PickSciLev = "You selected science. Pick level (enter a for $10, b for  $25, c for $50)";
   //memset (buffer, 0, 1024);
   printf("%s\n", buffer);
   send(new_socket, PickSciLev, strlen(PickSciLev), 0);

   //receive the difficulty level input from user
   //memset(buffer, 0, 1024);
   recv(new_socket, buffer, 1, 0);
   //cout << "count is " << count;
   cout << "buffer is " << buffer << endl;
   printf("buffer is %s\n", buffer);

   if (strcmp("a", buffer) == 0)  //if client selects a) difficulty
   {
     cout << "You picked science for $10" << endl;
     char *SciQ1 = "How many chromosomes do humans have? Enter a)20, b)56, c)23";
     send(new_socket, SciQ1, strlen(SciQ1), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("c", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
     }
     else
     {
      LIVES--;
      cout << "You are incorrect! You have lives: " << LIVES << endl;
      char *SciQ1Ans = "You are incorrect. The correct answer is 23";
      send(new_socket, SciQ1Ans, strlen(SciQ1Ans), 0);
     }
   }
   else if (strcmp("b", buffer) == 0) //if client selects b) difficulty
   {
    cout << "You picked science for $25" << endl;
    char *SciQ2 = "What is the powerhouse of the cell? Enter a)mitochondria, b)cyptoplasma, c)DNA";
    send(new_socket, SciQ2, strlen(SciQ2), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("a", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
     }
     else
     {
      LIVES--;
      cout << "You are incorrect! You have lives: " << LIVES << endl;
      char *SciQ2Ans = "You are incorrect. The correct answer is mitochondria";
      send(new_socket, SciQ2Ans, strlen(SciQ2Ans), 0);
     }
   }
   else if (strcmp("c", buffer) == 0) //if client selects c) difficulty
   {
    cout << "You picked science for $25" << endl;
    char *SciQ3 = "What is the symbol of iron on periodic table? a)Ir, b)Fe, c)In";
    send(new_socket, SciQ3, strlen(SciQ3), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("b", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
     }
     else
     {
      LIVES--;
      cout << "You are incorrect! You have lives: " << LIVES << endl;
      char *SciQ3Ans = "You are incorrect. The correct answer is Fe";
      send(new_socket, SciQ3Ans, strlen(SciQ3Ans), 0);
     }
   }
  /***********************************************************************/

  /***********************************History*****************************/


  /*****************************************************************************/
}
else if (strcmp("h", buffer) == 0)
 {
   cout << "Hi" << endl;
   //Ask user to select a difficulty level
   char *PickHistLev = "You selected history. Pick level (enter a for $10, b for  $25, c for $50)";
   //memset (buffer, 0, 1024);
   printf("%s\n", buffer);
   send(new_socket, PickHistLev, strlen(PickHistLev), 0);

   //receive the difficulty level input from user
   //memset(buffer, 0, 1024);
   recv(new_socket, buffer, 1, 0);
   //cout << "count is " << count;
   cout << "buffer is " << buffer << endl;
   printf("buffer is %s\n", buffer);

   if (strcmp("a", buffer) == 0)  //if client selects a) difficulty
   {
     cout << "You picked history for $10" << endl;
     char *HistQ1 = "Who was Canada's first Prime Minister? a)Mackenzie King, b)John A. Macdonald, c)Wilfrid Laurier";
     send(new_socket, HistQ1, strlen(HistQ1), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("b", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
     }
     else
     {
      LIVES--;
      cout << "You are incorrect! You have lives: " << LIVES << endl;
      char *HistQ1Ans = "You are incorrect. The correct answer is John A. Macdonald";
      send(new_socket, HistQ1Ans, strlen(HistQ1Ans), 0);
     }
   }
   else if (strcmp("b", buffer) == 0) //if client selects b) difficulty
   {
    cout << "You picked history for $25" << endl;
    char *HistQ2 = "Which country allied with Germany during WW1? a)Japan, b)Italy, c)Austria-Hungary";
    send(new_socket, HistQ2, strlen(HistQ2), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("c", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
     }
     else
     {
      LIVES--;
      cout << "You are incorrect! You have lives: " << LIVES << endl;
      char *HistQ2Ans = "You are incorrect. The correct answer is Austria-Hungary";
      send(new_socket, HistQ2Ans, strlen(HistQ2Ans), 0);
     }
   }
   else if (strcmp("c", buffer) == 0) //if client selects c) difficulty
   {
    cout << "You picked history for $25" << endl;
    char *HistQ3 = "Who led Prussia during the Seven Years' War? a)Frederick the Great, b)Otto I, c)Frederick Barbarossa";
    send(new_socket, HistQ3, strlen(HistQ3), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("a", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
     }
     else
     {
      LIVES--;
      cout << "You are incorrect! You have lives: " << LIVES << endl;
      char *HistQ3Ans = "You are incorrect. The correct answer is Frederick the Great";
      send(new_socket, HistQ3Ans, strlen(HistQ3Ans), 0);
     }
   }
 }
 else
 {
  cout << "Incorrect";
 }
}

 return 0;
}
