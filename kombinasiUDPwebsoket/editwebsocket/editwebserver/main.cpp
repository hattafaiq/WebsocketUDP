#include <QtCore/QCoreApplication>
#include "editserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ChatServer server;
    server.init_time();
    return a.exec();
}
