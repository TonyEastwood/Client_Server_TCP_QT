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
    ///////////////////Test
    sock=server.CreateServer(777);
    client.ConnectToServer(sock);                        //create socket and connect to server

    QtConcurrent::run(&client, &Client::ReceiveData);                      //create new thread for ReceiveData (multithreading)
       client.SendData();                                                  //run loop for SendData on socket (server)
       client.~Client();                                                   //call destructor to delete pointer on socket


    /////////////////////////

    return a.exec();
}
