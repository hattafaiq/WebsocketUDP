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
    void onTextMessageReceived(QString message);
    void init_time();
    void kirim();

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    QTimer *timer;
};

#endif // CLIENT_H
