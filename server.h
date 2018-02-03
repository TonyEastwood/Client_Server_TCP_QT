#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
class Server : public QObject
{
    Q_OBJECT
    QTcpServer *server;                                     //Server socket for listening connection
    QTcpSocket *socket;                                     //socket get new connections and return it in CreateServer
public:
    explicit Server(QObject *parent = nullptr);
  ~Server();
    QTcpSocket* CreateServer(QString _ip, int _port);                                //open socket for _ip and _port for listen return socket on TcpConnection
signals:

public slots:

};


#endif // SERVER_H
