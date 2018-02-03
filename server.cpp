#include "server.h"
Server::Server(QObject *parent) : QObject(parent)
{

}



QTcpSocket* Server::CreateServer(int _port)
{
    server = new QTcpServer(this);                                  //initialize Server socket


    while(!server->listen(QHostAddress::Any,_port) )            //if listen succes (have a root access)
    {
    }
        std::cout<<"Server start success"<<std::endl;           //message, listen success
        if(server->waitForNewConnection(3000000))
        {
            socket = server->nextPendingConnection();       //cause by signal newConecction in server
            std::cout<<"New connection established"<<std::endl;
            return socket;                                         //return socket on new connection

        }
    return 0;
}

Server::~Server()
{
       delete server;                                       //delete socket server
}
