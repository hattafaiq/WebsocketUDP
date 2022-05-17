#include "editserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

ChatServer::ChatServer(quint16 port, QObject *parent) :
    QObject(parent),m_pWebSocketServer(Q_NULLPTR),m_clients()
{
    //inisialisasi websocketserver
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),QWebSocketServer::NonSecureMode,this);
    m_pWebSocketServer->listen(QHostAddress::Any, port);
    qDebug() << "server standby pada: " << port; //1234
    connect(m_pWebSocketServer, &QWebSocketServer::newConnection,this, &ChatServer::onNewConnection);
    //inisialisasi UDP
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 1111);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    //waktu
    jam = new QTimer(this);
    connect(jam, SIGNAL(timeout()),this, SLOT(showTime()));
    jam->start();
    date = QDate::currentDate();
    dateTimeText = date.toString();
}

void ChatServer::showTime()
{
    QTime time = QTime::currentTime();
    time_text = time.toString("hh:mm:ss:z");
}

ChatServer::~ChatServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void ChatServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    connect(pSocket, &QWebSocket::textMessageReceived, this, &ChatServer::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &ChatServer::socketDisconnected);

    m_clients << pSocket;
}

void ChatServer::processMessage(QString message)
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

void ChatServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void ChatServer::readyRead()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);

    Q_FOREACH (QWebSocket *pClient, m_clients)
    {
        pClient->sendTextMessage(buffer);
        qDebug() << "data terkirim: " << buffer << time_text;

    }
}
