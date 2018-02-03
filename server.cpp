#include "server.h"
Server::Server(QObject *parent) : QObject(parent)
{

}



QTcpSocket* Server::CreateServer(int _port)
{
    server = new QTcpServer(this);                                  //initialize Server socket

    std::cout<<"Wait for connection (if you wait so long, try to run with root access)"<<std::endl;
    while(!server->listen(QHostAddress::Any,_port) )            //wait for at least connection
    {
    }
        std::cout<<"Server start success"<<std::endl;           //message, listen success
        if(server->waitForNewConnection(30000))
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
