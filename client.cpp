#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

void EndTheMessage(char * message)
{
    for(int i=0;;i++)
    {
        if (message[i]=='\0')
        {
            message[i]='\r';
            message[i+1]='\n';
            message[i+2]='\0';
            break;
        }

    }
}
bool Client::ConnectToServer(QString host, int port)
{
    socket=new QTcpSocket();                        //initialize socket as tcp socket
    socket->connectToHost(host,port);                 //try connect to server host:port
    if(socket->waitForConnected(30000))              //wait 30000ms for connection
        return true;                                //if connection establish success, return true
    else return false;                              //else return false
}
void Client::ConnectToServer(QTcpSocket* _socket)
{
    socket = new QTcpSocket();
    socket=_socket;                        //initialize socket as tcp socket


}

void Client::SendData()                              //send data on server
{
    char data[120]="wefwe";                                 //buff for send data
    char Name[50];                                          //NickName user
    char result[170];                                       //result message that will be send
    std::cout<<"Input your name:"<<std::endl;
    std::cin>>Name;                                         //input NickName

       while(IfConnectedToServ())                   //till connection establish, send data from istream
       {
        strncpy ( result, Name, sizeof(Name) );             //union result with NickName
        std::cin.getline (data,1024);                      //get data from input data to send it as message
        strcat(result,":");
        strcat(result,data);                                //union NickName with Data
        EndTheMessage(result);                              //end message by \r\n
        socket->write(result);                        //write data to socket
        socket->flush();                            //write all data from buffer
        socket->waitForBytesWritten(3000);          //wait till at least one byte has been written on the socket
        }
}
void Client::ReceiveData()                          //function read data from socket
{
     while(IfConnectedToServ())                     //till connection establish, send data from istream
    {
        std::cout<<socket->readAll().data();        //read all data from socket
       socket->waitForReadyRead(3000);             //wait till all data will be read
        socket->waitForBytesWritten(3000);          //wait till at least one byte has been written on the socket
    }
}

bool Client::IfConnectedToServ()                //check if connection establish now
{
    return socket->state()==QTcpSocket::ConnectedState;         //return connection state
}

void Client::DisconnectFromServer()
{
   socket->close();                                 //close socket, disconect
}


Client::~Client()
{
    if(IfConnectedToServ())
    DisconnectFromServer();                          //close socket before delete that
    delete socket;                              //delete pointer on socket
}


