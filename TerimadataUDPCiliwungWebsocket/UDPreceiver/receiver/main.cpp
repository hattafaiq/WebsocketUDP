#include <QCoreApplication>
#include "receiver.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    receiver waktu;
    waktu.init_time();

    return a.exec();
}
