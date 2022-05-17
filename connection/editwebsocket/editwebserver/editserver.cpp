#include "editserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

ChatServer::ChatServer(QObject *parent) : QObject(parent)
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),QWebSocketServer::NonSecureMode,this);
    m_pWebSocketServer->listen(QHostAddress::Any, 1111);
    connect(m_pWebSocketServer, &QWebSocketServer::newConnection,this, &ChatServer::onNewConnection);
}

ChatServer::~ChatServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void ChatServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &ChatServer::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &ChatServer::socketDisconnected);
    m_clients << pSocket;
}

void ChatServer::processMessage(QByteArray message)
{
    i++;
    QString DataAsString = QString(message);
    qDebug() << "Message received:" << DataAsString << "ke- " <<i;
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

