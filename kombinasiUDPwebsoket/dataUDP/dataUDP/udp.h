#ifndef UDP_H
#define UDP_H
#include <QUdpSocket>
#include <QTimer>
#include <QDate>
#include <QString>

class udp : public QObject
{
    Q_OBJECT
public:
    explicit udp(QObject *parent = nullptr);
    //udp();
signals:

public slots:
    void readyRead();
//    void readysend();
     void init_time();
     void showTime();

private:
    QUdpSocket *socket;
    QTimer *timer;
    QTimer *jam;
    QDate date;
    QString dateTimeText;
    QString time_text;
    int i;

};
//struct tt_req2 {
//    char head[10];
//    unsigned short sps;//KUKU
//    char cur_kanal;
//    int kanal_enable;       /* jumlah kanal aktif */
//    int request_sample;		/* sample diminta */
//    unsigned char buf[ BESAR_PAKET ];
//};

#endif // UDP_H
