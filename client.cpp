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
