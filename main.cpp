#include <QCoreApplication>
#include "client.h"
#include "server.h"
#include <QTcpSocket>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client client;
    Server server;
    QTcpSocket *sock;
    ///////////////////Test
    sock=server.CreateServer("localhost", 777);



    /////////////////////////

    return a.exec();
}
