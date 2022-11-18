//
// Created by kurum on 2022/06/10.
//
#include "publicInclude.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QString b = "play game?";
    auto c = b.split("?");
    qInfo() << c[1];
    // tcpReceiver te;
    return a.exec();
}
