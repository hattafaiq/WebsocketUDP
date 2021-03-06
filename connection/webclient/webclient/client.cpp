#include "client.h"

QT_USE_NAMESPACE

//! [constructor]
EchoClient::EchoClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),m_url(url),m_debug(debug)
{
    qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
    m_webSocket.open(QUrl(url));
}

void EchoClient::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, SIGNAL(binaryMessageReceived()),this, SLOT(kirim()));
}

void EchoClient::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
    //m_webSocket.close();
}

void EchoClient::kirim()
{
    QByteArray data;
       QString qs = "String";
       data += qs;
    //QString printable = QStringLiteral("data %1").arg(i);
    m_webSocket.sendBinaryMessage(data);
    qDebug()<<"data " << data;
}

//void EchoClient::init_time()
//{
//        timer = new QTimer(this);
//        QObject::connect(timer,SIGNAL(timeout()),this, SLOT(kirim()));
//        timer->start(50);
//}


