#ifndef RECEIVER_H
#define RECEIVER_H
#include <QUdpSocket>
#include <QTimer>

class receiver: public QObject
{
    Q_OBJECT
public:
    explicit receiver(QObject *parent = nullptr);

signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
    QTimer *timer;
};

#endif // RECEIVER_H
