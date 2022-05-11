#ifndef UDP_H
#define UDP_H
#include <QUdpSocket>
#include <QTimer>

//#define BESAR_PAKET     33
////#define BESAR_PAKET_F	(BESAR_PAKET / 4)

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

private:
    QUdpSocket *socket;
    QTimer *timer;
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
