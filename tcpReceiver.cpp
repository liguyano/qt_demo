//
// Created by kurum on 2022/06/11.
//

#include "tcpReceiver.h"

tcpReceiver::tcpReceiver(QString FileName, QObject *parent) : QObject(parent) {
    fileName = FileName;
    rec = new QTcpSocket;
    connect(rec, SIGNAL(readyRead()), this, SLOT(deal_mess()));
}

void tcpReceiver::deal_mess() {
    auto a = rec->readAll();
    if (a.right(5) == "1Pack") {
        rec->write("OK");
        a = a.left(a.size() - 5);
    }
    if (a.right(3) == "end") {
        bytes.push_back(a.mid(0, a.size() - 3));
        qInfo() << size_recv;
        save();
        auto add = rec->peerAddress();
        //emit file_persent(add,100,0);
        emit persent(100);
        pers->setValue(100);
        rec->disconnectFromHost();
        if (isIcon)
                emit icon_end(fileName, add);

        return;
    }
    bytes.push_back(a);
    size_recv += a.size();
    //  qInfo()<<a.size();
    if (bytes.size() > 500) {
        save();
    }
    //qInfo()<<a;
}

tcpReceiver::~tcpReceiver() {
    //file->close();
}

void tcpReceiver::end() {
    /* QThread::sleep(10);
     save();
     rec->disconnectFromHost();*/
    qInfo() << "received";
}

void tcpReceiver::conn(const QHostAddress &add, QString path) {
    printf_s("path%s\n", C_STR(path));
    file = new QFile(path + fileName);
    size_recv = 0;
    file->open(QIODevice::WriteOnly);
    file->close();
    userInfo uu;
    uu.lood("./setting/option.xml");
    //printf_s("ip:%s,%s\n", C_STR(add.toString()), C_STR(uu.read_info("user.port")));
    rec->connectToHost(add.toString().split(":")[add.toString().split(":").size() - 1],
                       uu.read_info("user.port").toInt());
    if (this->size < 0) {
        auto add = rec->peerAddress();
        //emit file_persent(add,100,0);
        pers->setValue(100);
        emit persent(100);
        rec->disconnectFromHost();
        printf_s("disconnected");
        return;
    }
    printf_s("connected\n");

}

void tcpReceiver::save() {
    file->open(QIODevice::Append);
    for (const auto &b: bytes) {
        file->write(b);
    }
    //   emit file_persent(rec->peerAddress(),(size_recv*100)/size,1);
    if (size != 0) {
        pers->setValue((size_recv * 100) / size);
        emit persent((size_recv * 100) / size);
    }
    file->close();
    bytes.clear();
//    file->close();
}

