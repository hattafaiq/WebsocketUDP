#include "udp.h"

udp::udp(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress("192.168.100.184"), 1111);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void udp::readyRead()
{
    int i;
    i++;
    QString printable = QStringLiteral("data %1").arg(i);
    QByteArray Data;
    Data.append(printable);
    socket->writeDatagram(Data, QHostAddress("192.168.100.184"), 1111);
    qDebug()<<"terkirim: "<<Data << " ke :" <<i;
}

void udp::init_time()
{
        timer = new QTimer(this);
        QObject::connect(timer,SIGNAL(timeout()),this, SLOT(readyRead()));
        timer->start(1000);
}
