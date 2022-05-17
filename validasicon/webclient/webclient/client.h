#ifndef CLIENT_H
#define CLIENT_H

#include <QWebSocket>
#include <QTimer>

class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(const QUrl &url, bool debug = false, QObject *parent = nullptr);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QByteArray message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    struct tt_req2 *p_req2;
    float *p_data;
    int i_kanal;

};

#endif // CLIENT_H
