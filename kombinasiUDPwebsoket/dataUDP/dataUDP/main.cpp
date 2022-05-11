#include <QCoreApplication>
#include "udp.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    udp kirim;
    kirim.init_time();

    return a.exec();
}
