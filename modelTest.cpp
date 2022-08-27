//
// Created by kurum on 2022/06/10.
//
#include "publicInclude.h"
#include "tcpSock.h"
#include "tcpReceiver.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QString b = "play game";
    tcpSock sock;
    // tcpReceiver te;
    return a.exec();
}
