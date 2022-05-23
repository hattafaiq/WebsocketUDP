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
    timer->start(1000);
    timera->start(2000);

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
    unsigned short spsX;
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
         spsX = p_req2->sps;

        //QByteArray paketkirim;
        //float data10paket_1[2560];
        //qDebug()<<"sps :"<<spsX;
             if(no_module==0) //ip pertama
             {
                 //counterCH1++;// ikut 1 paket
                 if(i_kanal==0)//kanal 1
                 {
                     counterCH1++;
                     if (counterCH1<11)
                     {

        ///////////////////////////////////////////////////////////////////////////////////////////////////
                    //mengirim 1o paket kanal 1
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_1[(counterCH1-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }
                                // qDebug()<<"oke masuk ke " << counterCH1 << "CH1" << "-jumlah data " << (counterCH1-1)*256+i;

                                 //double value = 3.14159275;
                                 // Encode the value into the byte array


        //////////////////////--------------------------------------------------------------/////////////
        /////////////////////---------------------------------------------------------------/////////////
                     }
                 }
    //             struct data1 bisa;
    //             *masuk = bisa.data_kirim1;
    //             memcpy(&masuk, &data10paket_1, sizeof (data10paket_1));
    //             struct data11 *bisaa;
    //             float *ap_data;
    //             bisaa = (struct data11 *) masuk;
    //             ap_data = (float *) bisaa;

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

    }

}

void data::datamanagement()
{
        QByteArray byteArray(reinterpret_cast<const char*>(&data10paket_1), 2560 * sizeof(float));
        qDebug()<<"oke terima ke ";
        float outValue[2560];
        // Copy the data from the byte array into the double
        memcpy(&outValue, byteArray.data(), 2560 * sizeof(float));
        for(int i=0; i<2560; i++)
        {
        qDebug("%f", outValue[i]);
        }
}
    //timera->stop();
   // qDebug()<<byteArray;
//    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//    //        //kirim data ke cient//                                       //
//            QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());   //
//            Q_FOREACH (QWebSocket *pClient, m_clients)                    //
//            {                                                             //
//                pClient->sendBinaryMessage(byteArray);
//                qDebug()<<"kirim ke client " <<byteArray;
//            }                                                             //
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//            for(int i=0; i<2560; i++){
//                masuk1 = (struct data1 *) dataterima.data();
//                *baru= masuk1->data_kirim1;
//                qDebug()<<baru[i];
//            }
//            for(int i=0; i<2560; i++)
//                 {
//                    //data_kirim[i]=data10paket_1[i];
//                      qDebug()<< data10paket_1[i];
//                    //qDebug()<<"kirim ke client";
//                 }
//                    //qDebug()<<"data terbaca oleh client";

//                    qDebug()<<"kirim tanpa koneksi";//


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

///emit untuk mentriger counter berdasarkan variabel didalam fungsi bisa atau fungsi;
