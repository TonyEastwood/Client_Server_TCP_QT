#include <QCoreApplication>
#include "client.h"
#include "server.h"
#include <QTcpSocket>
#include <QtConcurrent/QtConcurrent>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client client;
    Server server;
    QTcpSocket *sock;
    int _port;
    char choose='m';
    while(choose!='c' && choose!='s')
    {
    std::cout<<"Input: \n 'c' - if you want to connect to server \n 's' - if you want to create server"<<std::endl;
    choose=getchar();
    }
    switch(choose)
    {
        case 'c':
            char _host[30];
            std::cout<<"Input host and port that you want to connect:"<<std::endl<<"host:";
            std::cin>>_host;                                                     //input host
            std::cout<<"port:";
            std::cin>>_port;                                                      //input port
            if(client.ConnectToServer(_host,_port))                         //create socket and connect to server
            std::cout<<"Connections with host established success! "<<std::endl;
            else
            {
                std::cout<<"\nConnection failed... Try another host or port"<<std::endl;
                client.~Client();                                               //call destructor
                 return a.exec();                                               //the same return 0
            }
             QtConcurrent::run(&client, &Client::ReceiveData);                      //create new thread for ReceiveData (multithreading)
             std::cout<<"Chat is start! \n Type some thing to your interlocutor"<<std::endl;
            client.SendData();                                                  //run loop for SendData on socket (server)
            client.~Client();                                                   //call destructor to delete pointer on socket
            server.~Server();
        return a.exec();
                  break;

        case 's':
                  std::cout<<"Input numb of port that you want to open on server (Example: 777) \n port:";
                  std::cin>>_port;
                  sock=server.CreateServer(_port);                      //Wait for connection wich _port
                  client.ConnectToServer(sock);                        //create socket and connect to server
                  QtConcurrent::run(&client, &Client::ReceiveData);                      //create new thread for ReceiveData (multithreading)
                  std::cout<<"Chat is start!"<<std::endl;
                  client.SendData();                                                  //run loop for SendData on socket (server)
                  client.~Client();                                                   //call destructor to delete pointer on socket
                       server.~Server();
        break;
    }
    return a.exec();
}
