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
    void masuk();
    void init_time();
    void req_UDP();
    void refresh_plot();


private:
    QUdpSocket *socket;
    QTimer *timer;
    int tim_count;
};

#endif // RECEIVER_H
