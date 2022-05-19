#include "data.h"
#include "setting.h"


data::data(QObject *parent) : QObject(parent)
{
    //INIT_udp
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 5008);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReady()));
    //INIT_websocket
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),QWebSocketServer::NonSecureMode,this);
    m_pWebSocketServer->listen(QHostAddress::Any, 1234);
    connect(m_pWebSocketServer, SIGNAL(newConnection()),this, SLOT(onNewConnection()));
    //INIT_waktu
    jam = new QTimer(this);
    connect(jam, SIGNAL(timeout()),this, SLOT(showTime()));
    jam->start();
    date = QDate::currentDate();
    dateTimeText = date.toString();

}

void data::init_time()
{
    timer = new QTimer(this);
    timera = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(refresh_plot()));
    QObject::connect(timera,SIGNAL(timeout()),this, SLOT(datamanagement()));
    timer->start(4500);
}

void data::req_UDP()
{
    QByteArray Data;
    Data.append("getdata");
    socket->writeDatagram(Data,QHostAddress("192.168.0.101"), 5006);
    socket->writeDatagram(Data,QHostAddress("192.168.0.102"), 5006);
    counterCH1=0;
    counterCH2=0;
    counterCH3=0;
    counterCH4=0;
}

void data::showTime()
{
    QTime time = QTime::currentTime();
    time_text = time.toString("hh:mm:ss:z");
}


void data::readyReady()
{
    struct tt_req2 *p_req2;
    float *p_data;
    int i_kanal;
   // int cnt_ch[JUM_PLOT];
   // float *data_send[JUM_PLOT];
    int no_module;
    //= -1;
    while (socket->hasPendingDatagrams())
    {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sendera, &senderPort);
        //QHostAddress modul1_ip("192.168.0.101");
        QString ip1 =QString::fromUtf8("192.168.0.101");
        QString ip2 =QString::fromUtf8("192.168.0.102");
        QHostAddress ip_modul_1, ip_modul_2;
        ip_modul_1.setAddress(ip1);
        ip_modul_2.setAddress(ip2);
        if(sendera.toIPv4Address() == ip_modul_1.toIPv4Address())
        {
            //Modul1 kanal 0 | kanal 1 | kanal 2 | kanal 3
            //Modul2 kanal 4 | kanal 5 | kanal 6 | kanal 7
            //qDebug()<<" Data dari modul 1 | kanal"<<i_kanal+1;
            no_module = 0;
           // qDebug()<<"module 1 aktif";
           //qDebug()<<"ip setup modul 1 = "<< ip_modul_1.toIPv4Address();
            //qDebug()<<"ip pengirim modul 1 = "<< sendera.toIPv4Address();
        }
        else if(sendera.toIPv4Address() == ip_modul_2.toIPv4Address())
        {
            //Modul1 kanal 0 | kanal 1 | kanal 2 | kanal 3
            //Modul2 kanal 4 | kanal 5 | kanal 6 | kanal 7
            // qDebug()<<" Data dari modul 2 | kanal"<<i_kanal+1;
            i_kanal = i_kanal+4;
            no_module = 1;
            qDebug()<<"module 2 aktif";
            //qDebug()<<"ip setup modul 2 = "<< ip_modul_1.toIPv4Address();
            //qDebug()<<"ip pengirim modul 2 = "<< sendera.toIPv4Address();
        }


         p_req2 = (struct tt_req2 *) datagram.data();
         p_data = (float *) p_req2->buf;
         i_kanal = p_req2->cur_kanal;

        //QByteArray paketkirim;
        //float data10paket_1[2560];

         if(no_module==0) //ip pertama
         {
             //counterCH1++;// ikut 1 paket
             if(i_kanal==0)//kanal 1
             {

                //mengirim 1 paket kanal 1
//                 for(int i=0; i<256; i++)
//                     {
//                         data_y_voltage1[i]=p_data[i%256];
//                         //cnt_ch[i_kanal]++;
//                         //data_send[i_kanal][cnt_ch[i_kanal]] = p_data[i];
//                         //qDebug()<<data_y_voltage1[i];
//                     }
//                 qDebug()<<"oke masuk ----------- CH1 "<< counterCH1 << " -jumlah data 1";
//////////////////////--------------------------------------------------------------/////////////
/////////////////////---------------------------------------------------------------/////////////
                //mengirim 10 paket kanal 1
//                counterCH1++; // ikut 10 paket
//                if (counterCH1<11)
//                {
//                for(int i=0; i<256; i++)
//                     {

//                         data10paket_1[(counterCH1-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
//                         qDebug()<< data10paket_1[(counterCH1-1)*256+i];
//                     }
//                 qDebug()<<"oke masuk ----------- CH1 "<< counterCH1 << " -jumlah data 10";
//                }

                }

//--------------------------------------------------------------------------------------------------//
//             else if(i_kanal==1){ //kanal 2
//             counterCH2++;
//             for(int i=0; i<256; i++)
//                 {
//                     data_y_voltage2[i]=p_data[i%256];
//                     //cnt_ch[i_kanal]++;
//                     //       data_send[i_kanal][cnt_ch[i_kanal]] = p_data[i];
//                     qDebug()<<data_y_voltage2[i];
//                 }
//             qDebug()<<"oke masuk ----------- CH2 " << counterCH2 << " data";
//             }
//             else if(i_kanal==2){ //kanal 3
//             counterCH3++;
//             for(int i=0; i<256; i++)
//                 {
//                     data_y_voltage3[i]=p_data[i%256];
//                     //cnt_ch[i_kanal]++;
//                     //       data_send[i_kanal][cnt_ch[i_kanal]] = p_data[i];
//                     qDebug()<<data_y_voltage3[i];
//                 }
//             qDebug()<<"oke masuk ----------- CH3 " << counterCH3 << " data";
//             }
//             else if(i_kanal==3){ //kanal 4
//             counterCH4++;
//             for(int i=0; i<256; i++)
//                 {
//                     data_y_voltage4[i]=p_data[i%256];
//                     //cnt_ch[i_kanal]++;
//                     //       data_send[i_kanal][cnt_ch[i_kanal]] = p_data[i];
//                     qDebug()<<data_y_voltage4[i];
//                 }
//             qDebug()<<"oke masuk ----------- CH4 " << counterCH4 << " data";
//             }
//------------------------------------------------------------------------------------------------------//

         }
//////////////////////kalau 1 IP 4 kanal sampai sini)




    }
    timer->stop();// biar timernya sekali aja requestnya
}

void data::datamanagement()
{

  //  timera->stop();

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //        //kirim data ke cient//                                       //
    //        QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());   //
    //        Q_FOREACH (QWebSocket *pClient, m_clients)                    //
    //        {                                                             //
    //            //pClient->sendBinaryMessage(datagram);                   //
    //        }                                                             //
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
}

void data::refresh_plot()
{
    req_UDP();
    tim_count++;
    //qDebug("%s() == %d",__FUNCTION__,tim_count);
}

data::~data()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void data::onNewConnection()
{
    //qDebug("%s() == %d",__FUNCTION__,tim_count);
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    connect(pSocket, SIGNAL(textMessageReceived()), this, SLOT(processMessage()));
    connect(pSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    m_clients << pSocket;
}

void data::processMessage()//QByteArray message)
{
    //qDebug() << "server: " << sendera << " " << i_kanal;
//    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
//    Q_FOREACH (QWebSocket *pClient, m_clients)
//    {
//        pClient->sendBinaryMessage(datagram);
//    }
//    //pengecekan koneksi atau balasan dari client
//    //qDebug() << "dari client: " << message;
//    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
//    Q_FOREACH (QWebSocket *cClient, m_clients)
//    {       QString qs = "masuk bro";
//            message += qs;
//            //if(cClient->sendTextMessage(message))
//            if(cClient->sendBinaryMessage(message))
//            {
//            qDebug() << "balasan: " << message;
//            }
//     }
}

void data::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
