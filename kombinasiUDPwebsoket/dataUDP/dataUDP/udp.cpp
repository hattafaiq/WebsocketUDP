#include "udp.h"

udp::udp(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 1111);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    jam = new QTimer(this);
    connect(jam, SIGNAL(timeout()),this, SLOT(showTime()));
    jam->start();
    date = QDate::currentDate();
    dateTimeText = date.toString();
}
void udp::showTime()
{
    QTime time = QTime::currentTime();
    time_text = time.toString("hh:mm:ss:z");
}

void udp::readyRead()
{
    i++;
    QString printable = QStringLiteral("data %1").arg(i);
    QByteArray Data;
    Data.append(printable);
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1111);

    if(!socket->writeDatagram(Data, QHostAddress::LocalHost, 1111))
    {
        qDebug()<<"gagal terkirim";
    }
    else{
        qDebug()<<"terkirim: "<<Data << time_text;
    }
}

void udp::init_time()
{
        timer = new QTimer(this);
        QObject::connect(timer,SIGNAL(timeout()),this, SLOT(readyRead()));
        timer->start(500);
}
