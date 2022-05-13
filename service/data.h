#ifndef DATA_H
#define DATA_H

#include <QUdpSocket>
#include <QTimer>
#include <QObject>
#include <QList>
#include <QByteArray>
#include <QWebSocket>
#include <QTimer>
#include <QUdpSocket>
#include <QDate>
#include <QString>
#include "QWebSocketServer"

class data : public QObject
{
    Q_OBJECT
public:
    explicit data(QObject *parent = nullptr);
    void req_UDP();
    virtual ~data();
signals:

public slots:
    void readyRead();
    void init_time();
    void refresh_plot();

private slots:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();
    //void showTime();

private:
    QUdpSocket *socket;
    QTimer *timer;
    int tim_count;
    QByteArray datagram;
    //
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QString *datas;
    //
    QTimer *jam;
    QTimer *timers;
    QDate date;
    QString dateTimeText;
    QString time_text;
};
#endif // DATA_H
