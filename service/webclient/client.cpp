#include "client.h"
#include "datasetup.h"
#include "QWebSocket"

QT_USE_NAMESPACE

EchoClient::EchoClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),m_url(url),m_debug(debug)
{
    qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&m_webSocket, SIGNAL(disconnected()), this, SLOT(closed()));
    m_webSocket.open(QUrl(url));
    //waktu
    jam = new QTimer(this);
    connect(jam, SIGNAL(timeout()),this, SLOT(showTime()));
    jam->start();
    date = QDate::currentDate();
    dateTimeText = date.toString();
    //count=0;
}

void EchoClient::showTime()
{
    QTime time = QTime::currentTime();
    time_text = time.toString("hh:mm:ss:z");
}

void EchoClient::onConnected()
{
    //connect(&m_webSocket, &QWebSocket::textMessageReceived,this, &EchoClient::onTextMessageReceived);
    //connect(&m_webSocket, SIGNAL(binaryMessageReceived()),this, SLOT(onTextMessageReceived())); //tidak mau signal slot
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,this, &EchoClient::onTextMessageReceived);
    qDebug() << "____--WebSocket terhubung--____";

    QString qs = "aktif bro";
    QByteArray ba;
    ba += qs;
   // m_webSocket.sendTextMessage(QStringLiteral("aktif bro"));
    m_webSocket.sendBinaryMessage(ba);
}

void EchoClient::onTextMessageReceived(QByteArray message)
{
    float outValue[2560];
    // Copy the data from the byte array into the double
    memcpy(&outValue, message.data(), 2560 * sizeof(float));
    for(int i=0; i<2560; i++)
    {
    qDebug("%f", outValue[i]);
    //qDebug()<<"terima data";
    }
    qDebug()<<"terima data----------------------------------------**//";
}


