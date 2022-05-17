#include "client.h"
#include "setting.h"

QT_USE_NAMESPACE

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
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,this, &EchoClient::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("aktif bro"));
}

void EchoClient::onTextMessageReceived(QByteArray message)
{
    qDebug() << message;
//    message.resize(m_webSocket.readBufferSize());
//    p_req2 = (struct tt_req2 *) message.data();
//    p_data = (float *) p_req2->buf;
//    i_kanal = p_req2->cur_kanal;
//    qDebug() << "service : " << i_kanal;
    //m_webSocket.close();
}


