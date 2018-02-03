#include "server.h"
Server::Server(QObject *parent) : QObject(parent)
{

}



QTcpSocket* Server::CreateServer(QString _ip, int _port)
{
    server = new QTcpServer(this);                                  //initialize Server socket

    if(server->listen(QHostAddress(_ip),_port))             //if listen succes (have a root access)
    {
        std::cout<<"Server start success"<<std::endl;           //message, listen success
        if(server->waitForNewConnection())
        {
            socket = server->nextPendingConnection();       //cause by signal newConecction in server
            std::cout<<"New connection established"<<std::endl;
            return socket;                                         //return socket on new connection

        }


    }
    else std::cout<<"Error listen"<<std::endl;              //else error
    return 0;
}

Server::~Server()
{
       delete server;                                       //delete socket server
}
