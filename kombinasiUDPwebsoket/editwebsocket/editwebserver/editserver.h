#ifndef EDITSERVER_H
#define EDITSERVER_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QWebSocket>
#include <QTimer>
#include <QUdpSocket>
#include <QDate>
#include <QString>
#include "QWebSocketServer"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

#define BESAR_PAKET 1024
class ChatServer : public QObject
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);
    void req_UDP();
//    virtual ~ChatServer();
signals:

public slots:
    void init_time();
    void refresh_plot();
    void readyRead();

private slots:
//    void onNewConnection();
//    void processMessage(QString message);
//    void socketDisconnected();
//    void showTime();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QUdpSocket *socket;
    QString *data;
    QTimer *jam;
    QTimer *timer;
    QDate date;
    QString dateTimeText;
    QString time_text;
    int tim_count;

};

struct tt_req2 {
    char head[10];
    unsigned short sps;
    char cur_kanal;
    int kanal_enable;
    int request_sample;
    unsigned char buf[ BESAR_PAKET ];
};


#endif // EDITSERVER_H
