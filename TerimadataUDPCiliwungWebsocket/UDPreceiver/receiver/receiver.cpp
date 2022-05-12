#include "receiver.h"
#include "setup.h"

receiver::receiver(QObject *parent) : QObject(parent)
{
    qDebug("mulai Bind UDP");
    qDebug() << "Host Address localhost : "<< QHostAddress::LocalHost;
    qDebug()<< "Host Address : "<< QHostAddress::AnyIPv4 << ":" <<PORT_CILIWUNG_DATA;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, PORT_CILIWUNG_DATA);
    connect(socket, SIGNAL(readyRead()), this, SLOT(masuk()));
}

void receiver::init_time()
{
    qDebug("%s()",__FUNCTION__);
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(refresh_plot()));
    timer->start(3000);
}

void receiver::masuk()
{
    qDebug("%s()",__FUNCTION__);
    qDebug()<<"init_data:";
    quint16 senderPort;
    QHostAddress sender;
    struct tt_req2 *p_req2;
    float *p_data;
    int i_kanal;

    while (socket->hasPendingDatagrams())
    {
        qDebug()<<"counter data harusnya";
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        p_req2 = (struct tt_req2 *) datagram.data();
        p_data = (float *) p_req2->buf;
        i_kanal = p_req2->cur_kanal;
        //qDebug()<<i_kanal;
      }
}

void receiver::req_UDP()
{
    qDebug("%s()",__FUNCTION__);
    QByteArray Data;
    Data.append("getdata");
    socket->writeDatagram(Data,QHostAddress("192.168.0.101"), PORT_CILIWUNG_SEND);
    socket->writeDatagram(Data,QHostAddress("192.168.0.102"), PORT_CILIWUNG_SEND);
    qDebug()<<"mintadata";
}

void receiver::refresh_plot()
{
    qDebug("%s()",__FUNCTION__);
    req_UDP();
    tim_count++;
}
