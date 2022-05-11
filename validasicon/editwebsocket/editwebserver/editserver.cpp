#include "editserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

ChatServer::ChatServer(quint16 port, QObject *parent) :
    QObject(parent),m_pWebSocketServer(Q_NULLPTR),m_clients()
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),QWebSocketServer::NonSecureMode,this);
    m_pWebSocketServer->listen(QHostAddress::Any, port);
    qDebug() << "server standby pada: " << port;
    connect(m_pWebSocketServer, &QWebSocketServer::newConnection,this, &ChatServer::onNewConnection);
    init_time();
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
    qDebug() << "dari client: " << message;
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    Q_FOREACH (QWebSocket *pClient, m_clients)
    {
            message= "masuk bro";
            if(pClient->sendTextMessage(message))
            {
            qDebug() << "balasan: " << message;
            init_time();
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

void ChatServer::init_time()
{
        timer = new QTimer(this);
        QObject::connect(timer,SIGNAL(timeout()),this, SLOT(kirim()));
        timer->start(500);
}

void ChatServer::kirim()
{
    int i;
    i++;
    QString printable = QStringLiteral("data %1").arg(i);
    Q_FOREACH (QWebSocket *pClient, m_clients)
    {
        pClient->sendTextMessage(printable);
        if(!pClient->sendTextMessage(printable))
        {
            qDebug() << "periksa jaringan, data tidak terkirim ";
        }
        else
        {
            qDebug() << "data terkirim: " << printable;
        }
    }
}

