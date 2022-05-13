#include "editserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

ChatServer::ChatServer(QObject *parent) : QObject(parent)//,m_pWebSocketServer(Q_NULLPTR),m_clients()
{
    //inisialisasi UDP
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 5008);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
//    //inisialisasi websocketserver
//    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),QWebSocketServer::NonSecureMode,this);
//    m_pWebSocketServer->listen(QHostAddress::Any, 1234);
//    //qDebug() << "server standby pada: " << port; //1234
//    connect(m_pWebSocketServer, &QWebSocketServer::newConnection,this, &ChatServer::onNewConnection);
//    //waktu
//    jam = new QTimer(this);
//    connect(jam, SIGNAL(timeout()),this, SLOT(showTime()));
//    jam->start();
//    date = QDate::currentDate();
//    dateTimeText = date.toString();
}

//void ChatServer::showTime()
//{
//    qDebug("%s() == %d",__FUNCTION__,tim_count);
//    QTime time = QTime::currentTime();
//    time_text = time.toString("hh:mm:ss:z");
//}

void ChatServer::init_time()
{
    qDebug("%s() == %d",__FUNCTION__,tim_count);
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(refresh_plot()));
    timer->start(1000);
}

void ChatServer::req_UDP()
{
    qDebug("%s() == %d",__FUNCTION__,tim_count);
    QByteArray Data;
    Data.append("getdata");
    socket->writeDatagram(Data,QHostAddress("192.168.0.101"), 5006);
    socket->writeDatagram(Data,QHostAddress("192.168.0.102"), 5006);
}

void ChatServer::readyRead()
{
    qDebug("%s() == %d",__FUNCTION__,tim_count);
    quint16 senderPort;
    QHostAddress sender;
    struct tt_req2 *p_req2;
    //float *p_data;
    int i_kanal;
    while (socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        p_req2 = (struct tt_req2 *) datagram.data();
       // p_data = (float *) p_req2->buf;
        i_kanal = p_req2->cur_kanal;
        qDebug()<<i_kanal;
//        Q_FOREACH (QWebSocket *pClient, m_clients)
//        {
//            pClient->sendTextMessage(datagram);
//            qDebug() << "data terkirim: " << time_text;

//        }
    }
}

void ChatServer::refresh_plot()
{
    req_UDP();
    tim_count++;
    qDebug("%s() == %d",__FUNCTION__,tim_count);

}

//ChatServer::~ChatServer()
//{
//    m_pWebSocketServer->close();
//    qDeleteAll(m_clients.begin(), m_clients.end());
//}

//void ChatServer::onNewConnection()
//{
//    qDebug("%s() == %d",__FUNCTION__,tim_count);
//    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
//    connect(pSocket, &QWebSocket::textMessageReceived, this, &ChatServer::processMessage);
//    connect(pSocket, &QWebSocket::disconnected, this, &ChatServer::socketDisconnected);
//    m_clients << pSocket;
//}

//void ChatServer::processMessage(QString message)
//{
//    //pengecekan koneksi atau balasan dari client
//   qDebug() << "dari client: " << message;
//    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
//    Q_FOREACH (QWebSocket *cClient, m_clients)
//    {
//            message= "masuk bro";
//            if(cClient->sendTextMessage(message))
//            {
//            qDebug() << "balasan: " << message;
//            }
//     }
//}

//void ChatServer::socketDisconnected()
//{
//    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
//    if (pClient)
//    {
//        m_clients.removeAll(pClient);
//        pClient->deleteLater();
//    }
//}


