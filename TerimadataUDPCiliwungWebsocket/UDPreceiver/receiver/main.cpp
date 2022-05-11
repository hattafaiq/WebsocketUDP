#include <QCoreApplication>
#include "receiver.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    receiver terima;
    terima.readyRead();

    return a.exec();
}
