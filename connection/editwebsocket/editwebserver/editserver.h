#ifndef EDITSERVER_H
#define EDITSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QWebSocket>
#include <QTimer>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class ChatServer : public QObject
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = Q_NULLPTR);
    virtual ~ChatServer();

private Q_SLOTS:
    void onNewConnection();
    void processMessage(QByteArray message);
    void socketDisconnected();

private:
    int i;


private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;

};


#endif // EDITSERVER_H
