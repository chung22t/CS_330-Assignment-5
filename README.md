# CS_330-Assignment-5
/* 
Name: Tony Chung
Student Number: 200363176

Topic:
The goal of this assignment is socket communication between a server and a client.
This program is to resemble a jeopardy game. A player (client) will connect to the server (game master). The player will get to pick
what category and what difficulty (harder questions reward nore points). If the player answers a question correct, they will be rewarded with a certain number of points. If they lose, they will lose a life. After the player answers a question, they will be returned back and the server will ask them for a category and a difficulty level. It should looping in this way until the player (client) run out of lives. The maximum number of points (if the player gets them all correct without running out of lives) is 255.
 
Challenges:
The first challenge had with this project was figuring on what to do for my project. I decided on doing sockets but I did not know what kind of program to do with the sockets. I initially decided to make a chat/messaging app. However, since we already had a lab basedaround this idea, I decided not to do it. I decided to work on a questionaire/jeopardy like game isntead.

A major challenge I had early on in this poject was trying to get my server and client to establish a connection. Another challenge was figuring out how to get the client and server to send messages to each other. I initially wanted the client to be able to send dynamic strings across the socket. However, ultimately I was unable to figure this out so I made the game multiple choice instead. Another challenge I had was figuring out how to loop the game until the client either won or ran out of lives.


Reproduce Project:
This project can be easily reproduced. First, program code for a server and client must be created. The server would create a socket, then it would bind, listen and accept a connection from the client. Meanwhile, the client would create a socket and connect it to the server. A series of char *strings would be created in server for various sentences such as the qustions themselves, correct/incorrect messages to the client. A buffer to store the data would also be created in both the server and the client. Other variables in the program include a integer variable to  keep track the the lives and the points that the client has accumilated. The server will send the category and as well as the difficuly message to client. If-else conditions will be in place for each different scenario. Once category and difficulty is selected, server will send quesiton to client. Client will receive the message, reply to it, and send the reply back to server. A loop will be placed to keep repeating this process until the client has either run out of lives or they successfully answered all the questions correctly.


Below are some notes I have left describing what I managed to accomplish or tried to accomplish on that day. 
Note: Prior to March 23rd, most of my progress on the project was trying to establish a connection between the server and the 
      client. As a result, I did not include them.
      
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

Apr 7
-New category (geography) has been included in the game.
-a loop has been created so client and keep playing game until they run out of lives.
-Current issue is trying to get the game to exit. Once client answers question wrong, the game on client side is in
 infinite loop even if a condition was placed on loop.
 
 Apr 11
 -I am unable to solve the program's looping problem. A loop was been created in client side of socket. It is supposed to loop 
  until the client run out of lives, after which it would exit from the loop. The issue is that after client (user) first answers 
  first question, the server does not send the user the other question.
 - I originally created two repositories for this project (one for server and one for client). I decided to merge them together. As a 
   result, this repository will also include code for both the client side and server side of the socket.

*/

/* The following is the code for the server (game master) */
/*************************************************************SERVER******************************************************************/
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
 char *category ="Please select s (Science), h(history). g(geography)";
 int LIVES = 3;
 char *quitMSG = "Do you want to quit?";
 char *ClientAnswer;
 char *correct = "You are correct!";
 int points = 0;

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

  memset (buffer, 0, 1024);
  recv(new_socket, buffer, 1, 0);
  cout << buffer << endl;

/**********************************Science*****************************************/
  if (strcmp("s",buffer) == 0)
  {
   //Ask user to select a difficulty level
   char *PickSciLev = "You selected science. Pick level (enter a for $10, b for  $25, c for $50)";
   printf("%s\n", buffer);
   send(new_socket, PickSciLev, strlen(PickSciLev), 0);

   //receive the difficulty level input from user
   recv(new_socket, buffer, 1, 0);
   cout << "buffer is " << buffer << endl;
   printf("buffer is %s\n", buffer);

   if (strcmp("a", buffer) == 0)  //if client selects a) difficulty (easy)
   {
     cout << "You picked science for $10" << endl;
     char *SciQ1 = "How many chromosomes do humans have? Enter a)20, b)56, c)23, d)32";
     send(new_socket, SciQ1, strlen(SciQ1), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("c", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
      points = points + 10;
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
    char *SciQ2 = "What is the powerhouse of the cell? Enter a)mitochondria, b)cyptoplasma, c)DNA, d)ribosomes";
    send(new_socket, SciQ2, strlen(SciQ2), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("a", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
      points = points + 25;
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
    char *SciQ3 = "What is the symbol of iron on periodic table? a)Ir, b)Fe, c)In, d)Io";
    send(new_socket, SciQ3, strlen(SciQ3), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("b", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
      points = points + 50;
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

}
else if (strcmp("h", buffer) == 0)
 {
   //Ask user to select a difficulty level
   char *PickHistLev = "You selected history. Pick level (enter a for $10, b for  $25, c for $50)";
   //memset (buffer, 0, 1024);
   printf("%s\n", buffer);
   send(new_socket, PickHistLev, strlen(PickHistLev), 0);

   //receive the difficulty level input from user
   recv(new_socket, buffer, 1, 0);
   cout << "buffer is " << buffer << endl;
   printf("buffer is %s\n", buffer);

   if (strcmp("a", buffer) == 0)  //if client selects a) difficulty
   {
     cout << "You picked history for $10" << endl;
     char *HistQ1 = "Who was Canada's first Prime Minister? a)Mackenzie King, b)John A. Macdonald, c)Wilfrid Laurier, d)Robert Borden";
     send(new_socket, HistQ1, strlen(HistQ1), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("b", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
      points = points + 10;
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
    char *HistQ2 = "Which country allied with Germany during WW1? a)Japan, b)Italy, c)Austria-Hungary, d)Japan and Italy";
    send(new_socket, HistQ2, strlen(HistQ2), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("c", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
      points = points + 25;
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
    char *HistQ3 = "Who led Prussia during the Seven Years' War? a)Frederick the Great, b)Otto I, c)Frederick Barbarossa, d)Frederick   Wilhelm I";
    send(new_socket, HistQ3, strlen(HistQ3), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("a", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
      points = points + 50;
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
 else if (strcmp("g", buffer) == 0)
 {
  cout << "You selected geograpghy" << endl;
  //Ask user to select a difficulty level
   char *PickGeoLev = "You selected geography. Pick level (enter a for $10, b for  $25, c for $50)";
   printf("%s\n", buffer);
   send(new_socket, PickGeoLev, strlen(PickGeoLev), 0);

   //receive the difficulty level input from user
   recv(new_socket, buffer, 1, 0);
   cout << "buffer is " << buffer << endl;

   if (strcmp("a", buffer) == 0)  //if client selects a) difficulty
   {
     cout << "You picked geography for $10" << endl;
     char *GeoQ1 = "What is the highest point in the world? a)Mount Logan, b)Mount Everest, c)Mount Kilimanjaro, d)Mount Olympus";
     send(new_socket, GeoQ1, strlen(GeoQ1), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("b", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
      points = points + 10;
     }
     else
     {
      LIVES--;
      cout << "You are incorrect! You have lives: " << LIVES << endl;
      char *GeoQ1Ans = "You are incorrect. The correct answer is Mount Everest";
      send(new_socket, GeoQ1Ans, strlen(GeoQ1Ans), 0);
     }
   }
   else if (strcmp("b", buffer) == 0) //if client selects b) difficulty
   {
    cout << "You picked geography for $25" << endl;
    char *GeoQ2 = "What is the capital of Brazil? a)Brasilia, b)Rio de Janeiro, c)Sao Paulo, d)Fortaleza";
    send(new_socket, GeoQ2, strlen(GeoQ2), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("a", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
      points = points + 25;
     }
     else
     {
      LIVES--;
      cout << "You are incorrect! You have lives: " << LIVES << endl;
      char *GeoQ2Ans = "You are incorrect. The correct answer is Brasilia";
      send(new_socket, GeoQ2Ans, strlen(GeoQ2Ans), 0);
     }
   }
   else if (strcmp("c", buffer) == 0) //if client selects c) difficulty
   {
    cout << "You picked history for $25" << endl;
    char *GeoQ3 = "What country shares a border with Slovenia? a)Germany, b)Poland, c)Croatia, d)Slovakia";
    send(new_socket, GeoQ3, strlen(GeoQ3), 0);  //send question to client

     recv(new_socket, buffer, 1, 0);  //receive client response
     if (strcmp("c", buffer) == 0)
     {
      cout << "You are correct! " << endl;
      send(new_socket, correct, strlen(correct), 0);
      points = points + 50;
     }
     else
     {
      LIVES--;
      cout << "You are incorrect! You have lives: " << LIVES << endl;
      char *GeoQ3Ans = "You are incorrect. The correct answer is Croatia";
      send(new_socket, GeoQ3Ans, strlen(GeoQ3Ans), 0);
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
/*************************************************************************************************************************************/


/*The following code is for the client (user)
/*******************************************************************CLIENT************************************************************/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;
#define PORT 8080

int main(int argc, char const *argv[])
{
    const int MsgLen = 100; //length of message
    int sock = 0, valread;
    char  client_category; //game category
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    char AnswerBuffer[MsgLen];
    char  difficulty;
    int quit;
    char answer;
    int LIVES = 3;
    int points = 0;

    int QuitBuffer[MsgLen] = {0};
    char NEWBUFF[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");

 while (LIVES >= 0 || points = 255)
 {
    memset(buffer, 0, 1024);
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    cin >> client_category;
    send(sock, &client_category, 1, 0);

  /********************************Science***********************************/
    if (client_category == 's')  //if client picks science category
  {
    //clear buffer and display difficulty message for client
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);
    cout << buffer << endl;

    // send difficulty level to server
    cin >> difficulty;
    send (sock, &difficulty, 1, 0);

    if (difficulty == 'a')  //if client selects difficulty a)
   {
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);  //server sends question to client
    cout << buffer << endl;
    cin >> answer;  //client answers question
    send (sock, &answer, 1, 0); //sends answer to server

    if (answer == 'c')  //if correct
    {
      memset(buffer, 0, 1024);
      recv(sock, buffer, MsgLen, 0);
      cout << buffer << endl;
      points = points + 10;
    }
    else
    {
     LIVES--;
     memset(buffer, 0, 1024);
     recv(sock, buffer, MsgLen, 0);
     cout << buffer << endl;
    }
   }
   else if (difficulty == 'b')   //if client selects difficulty b)
   {
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);  //server sends question to client
    cout << buffer << endl;
    cin >> answer;  //client answers question
    send (sock, &answer, 1, 0); //sends answer to server

    if (answer == 'a')
    {
      memset(buffer, 0, 1024);
      recv(sock, buffer, MsgLen, 0);
      cout << buffer << endl;
      points = points + 25;
    }
    else
    {
     LIVES--;
     memset(buffer, 0, 1024);
     recv(sock, buffer, MsgLen, 0);
     cout << buffer << endl;
    }
   }
   else if (difficulty == 'c')  //if client selects difficulty c)
   {
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);  //server sends question to client
    cout << buffer << endl;
    cin >> answer;  //client answers question
    send (sock, &answer, 1, 0); //sends answer to server

    if (answer == 'b')
    {
      memset(buffer, 0, 1024);
      recv(sock, buffer, MsgLen, 0);
      cout << buffer << endl;
      points = points + 50;
    }
    else
    {
     LIVES--;
     memset(buffer, 0, 1024);
     recv(sock, buffer, MsgLen, 0);
     cout << buffer << endl;
    }
   }
 }
  /*****************************History*******************************/
 else if (client_category == 'h')  //if client picks history category
  {
    //clear buffer and display difficulty message for client
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);
    cout << buffer << endl;

    // send difficulty level to server
    cin >> difficulty;
    send (sock, &difficulty, 1, 0);

    if (difficulty == 'a')  //if client selects difficulty a)
   {
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);  //server sends question to client
    cout << buffer << endl;
    cin >> answer;  //client answers question
    send (sock, &answer, 1, 0); //sends answer to server

    if (answer == 'b')
    {
      memset(buffer, 0, 1024);
      recv(sock, buffer, MsgLen, 0);
      cout << buffer << endl;
      points = points + 10;
    }
    else
    {
     LIVES--;
     memset(buffer, 0, 1024);
     recv(sock, buffer, MsgLen, 0);
     cout << buffer << endl;
    }
   }
   else if (difficulty == 'b')   //if client selects difficulty b)
   {
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);  //server sends question to client
    cout << buffer << endl;
    cin >> answer;  //client answers question
    send (sock, &answer, 1, 0); //sends answer to server

    if (answer == 'c')
    {
      memset(buffer, 0, 1024);
      recv(sock, buffer, MsgLen, 0);
      cout << buffer << endl;
      points = points + 25;
    }
    else
    {
     LIVES--;
     memset(buffer, 0, 1024);
     recv(sock, buffer, MsgLen, 0);
     cout << buffer << endl;
    }
   }
   else if (difficulty == 'c')  //if client selects difficulty c)
   {
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);  //server sends question to client
    cout << buffer << endl;
    cin >> answer;  //client answers question
    send (sock, &answer, 1, 0); //sends answer to server

    if (answer == 'a')
    {
      memset(buffer, 0, 1024);
      recv(sock, buffer, MsgLen, 0);
      cout << buffer << endl;
      points = points + 50;
    }
    else
    {
     LIVES--;
     memset(buffer, 0, 1024);
     recv(sock, buffer, MsgLen, 0);
     cout << buffer << endl;
    }
   }
 }
 /***********************************Geography******************************/
 else if (client_category == 'g')
 {
  //clear buffer and display difficulty message for client
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);
    cout << buffer << endl;

    // send difficulty level to server
    cin >> difficulty;
    send (sock, &difficulty, 1, 0);

    if (difficulty == 'a')  //if client selects difficulty a)
   {
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);  //server sends question to client
    cout << buffer << endl;
    cin >> answer;  //client answers question
    send (sock, &answer, 1, 0); //sends answer to server

    if (answer == 'b')  //answer is correct
    {
      memset(buffer, 0, 1024);
      recv(sock, buffer, MsgLen, 0);
      cout << buffer << endl;
      points = points + 10;
    }
    else
    {
     LIVES--;
     memset(buffer, 0, 1024);
     recv(sock, buffer, MsgLen, 0);
     cout << buffer << endl;
    }
   }
   else if (difficulty == 'b')   //if client selects difficulty b)
   {
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);  //server sends question to client
    cout << buffer << endl;
    cin >> answer;  //client answers question
    send (sock, &answer, 1, 0); //sends answer to server

    if (answer == 'a')
    {
      memset(buffer, 0, 1024);
      recv(sock, buffer, MsgLen, 0);
      cout << buffer << endl;
      points = points + 25;
    }
    else
    {
     LIVES--;
     memset(buffer, 0, 1024);
     recv(sock, buffer, MsgLen, 0);
     cout << buffer << endl;
    }
   }
   else if (difficulty == 'c')  //if client selects difficulty c)
   {
    memset(buffer, 0, 1024);
    recv(sock, buffer, MsgLen, 0);  //server sends question to client
    cout << buffer << endl;
    cin >> answer;  //client answers question
    send (sock, &answer, 1, 0); //sends answer to server

    if (answer == 'c')
    {
      memset(buffer, 0, 1024);
      recv(sock, buffer, MsgLen, 0);
      cout << buffer << endl;
      points = points + 50;
    }
    else
    {
     LIVES--;
     memset(buffer, 0, 1024);
     recv(sock, buffer, MsgLen, 0);
     cout << buffer << endl;
    }
   }
  else
  {
    cout << "Incorrect input!" << endl;
    return 1;
  }
 } //end of if statement

 if (LIVES <= 0)
 {
   cout << "You ran out of lives" << endl;
   return 1;
 }
}

close (sock);
    return 0;
}





