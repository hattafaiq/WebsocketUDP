#include "data.h"
#include "setting.h"


data::data(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 5008);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),QWebSocketServer::NonSecureMode,this);
    m_pWebSocketServer->listen(QHostAddress::Any, 1234);
    //qDebug() << "server standby pada: " << port; //1234
    connect(m_pWebSocketServer, SIGNAL(newConnection()),this, SLOT(onNewConnection()));
}

void data::init_time()
{
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(refresh_plot()));
    timer->start(1500);
}

void data::req_UDP()
{
    QByteArray Data;
    Data.append("getdata");
    socket->writeDatagram(Data,QHostAddress("192.168.0.101"), 5006);
    socket->writeDatagram(Data,QHostAddress("192.168.0.102"), 5006);
}

void data::readyRead()
{
    quint16 senderPort;
    QHostAddress sendera;
    struct tt_req2 *p_req2;
    float *p_data;
    int i_kanal;
    while (socket->hasPendingDatagrams())
    {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sendera, &senderPort);
        p_req2 = (struct tt_req2 *) datagram.data();
        p_data = (float *) p_req2->buf;
        i_kanal = p_req2->cur_kanal;
        qDebug() << "service : " << i_kanal;

//        //qDebug() << "dari client: " << message;
        QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
        Q_FOREACH (QWebSocket *pClient, m_clients)
        {
            pClient->sendTextMessage(datagram);
        }
    }
}

void data::refresh_plot()
{
    req_UDP();
    tim_count++;
    qDebug("%s() == %d",__FUNCTION__,tim_count);
}

data::~data()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void data::onNewConnection()
{
    qDebug("%s() == %d",__FUNCTION__,tim_count);
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    connect(pSocket, SIGNAL(textMessageReceived()), this, SLOT(processMessage()));
    connect(pSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    m_clients << pSocket;
}

void data::processMessage(QString message)
{
    //pengecekan koneksi atau balasan dari client
   qDebug() << "dari client: " << message;
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    Q_FOREACH (QWebSocket *cClient, m_clients)
    {
            message= "masuk bro";
            if(cClient->sendTextMessage(message))
            {
            qDebug() << "balasan: " << message;
            }
     }
}

void data::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

