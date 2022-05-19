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
    //count++;
    //quint16 senderPort;
//    QString ciliwung = m_webSocket.peerAddress().toString();
//    struct tt_req2 *p_req2;
//    float *p_data;
//    int i_kanal;
//    p_req2 = (struct tt_req2 *) message.data();
//    p_data = (float *) p_req2->buf;
//    i_kanal = p_req2->cur_kanal;
    for(int i=0; i<256; i++){
    char* terima = message.data();
    ////qDebug() << "Pesan Diterima: " << message << time_text;
    //qDebug() << "client: " << i_kanal << time_text; //<< " " //<< count;
    //HostAddress ipv4(sender.toIPv4Address());
            qDebug()<< terima[i];
    }
    //qDebug() << "client: " << ciliwung << " " << i_kanal;
//lemot kalau print data secara detile bisajadi karena antrian yang menumpuk
//    int i;
//    for (i=0; i<255; i++)
//    {
//        qDebug() << "client: " << i_kanal << p_data[i] << time_text;
//    }
    //m_webSocket.close();

}


