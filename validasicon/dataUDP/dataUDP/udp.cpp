#include "udp.h"

udp::udp(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 1111);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void udp::readyRead()
{   int i;
    QByteArray Data;
    Data.append("data masuk");
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1111);
    i++;
    if(!socket->writeDatagram(Data, QHostAddress::LocalHost, 1111))
    {
        qDebug()<<"gagal terkirim";
    }
    else{
        qDebug()<<"terkirim: "<<Data << " ke :" <<i;
    }
}

void udp::init_time()
{
        timer = new QTimer(this);
        QObject::connect(timer,SIGNAL(timeout()),this, SLOT(readyRead()));
        timer->start(1000);
}
