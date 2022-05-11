#ifndef RECEIVER_H
#define RECEIVER_H
#include <QUdpSocket>
#include <QTimer>

class receiver: public QObject
{
    Q_OBJECT
public:
    explicit receiver(QObject *parent = nullptr);
    //udp();
signals:

public slots:
    void readyRead();
//    void readysend();
//    void init_time();

private:
    QUdpSocket *socket;
    QTimer *timer;
};

#endif // RECEIVER_H
