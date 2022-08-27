//
// Created by kurum on 2022/06/11.
//

#include "tcpSock.h"

#include <utility>

#define MB1 10485760

void sendF(tcpSock *sock, QTcpSocket *a, QString fileName) {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    uchar *fpr = file.map(0, MB1);
    int starPOint = 0;
    auto bbb = QByteArray::fromRawData((char *) fpr, MB1);
    auto persize = file.size() / MB1;
    a->write(bbb);

    starPOint = file.size() < MB1 ? 0 : MB1;
    while ((starPOint + MB1) < file.size()) {
        //busy=true;
        starPOint += MB1;
        fpr = file.map(starPOint, MB1);
        bbb = QByteArray::fromRawData((char *) fpr, MB1);
        a->write(bbb);
        sock->pers->setValue(sock->pers->value() + persize);
        a->waitForBytesWritten(-1);
        file.unmap(fpr);
        //a->write("1Pack");
    }
    fpr = file.map(starPOint, file.size() - starPOint);
    bbb = QByteArray::fromRawData((char *) fpr, file.size() - starPOint);
    a->write(bbb);
    //delete fpr;
    //busy= false;
    sock->pers->setValue(100);
    file.unmap(fpr);
    file.close();
    a->write("end");
    a->setProperty("id", 1);
}

tcpSock::tcpSock(QString fileName, QObject *parent) : QObject(parent) {
    fileNa = fileName;
    tcp = new QTcpServer();
    connect(tcp, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

}

void tcpSock::onNewConnection() {
    QTcpSocket *a = tcp->nextPendingConnection();
    if (a == NULL) {
        qInfo() << "wrong";
        return;
    }
    connect(a, SIGNAL(disconnected()), this, SLOT(deal_with()));
    connect(a, SIGNAL(readyRead()), this, SLOT(nptBusy()));
    //auto dd=new std::thread(sendF,this,a,fileNa);
    SendFile(a, fileNa);
}

void tcpSock::SendFile(QTcpSocket *a, QString fileName) {

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    uchar *fpr = file.map(0, MB1);
    int starPOint = 0;
    auto bbb = QByteArray::fromRawData((char *) fpr, MB1);
    auto persize = fileInfo.size() / MB1;
    a->write(bbb);

    starPOint = file.size() < MB1 ? 0 : MB1;
    while ((starPOint + MB1) < file.size()) {
        busy = true;
        starPOint += MB1;
        fpr = file.map(starPOint, MB1);
        bbb = QByteArray::fromRawData((char *) fpr, MB1);
        a->write(bbb);
        pers->setValue(pers->value() + persize);
        a->waitForBytesWritten(100);
        file.unmap(fpr);
        //a->write("1Pack");
    }
    fpr = file.map(starPOint, file.size() - starPOint);
    bbb = QByteArray::fromRawData((char *) fpr, file.size() - starPOint);
    a->write(bbb);
    //delete fpr;
    busy = false;
    pers->setValue(100);
    file.unmap(fpr);
    file.close();
    a->write("end");
    a->setProperty("id", 1);
}

long long tcpSock::star(int port = 7001) {
    QHostAddress add("localhost");
    qInfo() << fileNa << endl;
    fileInfo = QFileInfo(fileNa);
    auto size = fileInfo.size();
    qInfo() << size;
    tcp->listen(add, port);
    qInfo() << "creat host succed" << endl;

    return size;
}

void tcpSock::deal_with() {

    auto a = qobject_cast<QTcpSocket *>(sender());
    disconnect(a);
    a->close();
    tcp->close();
    qInfo() << "over";

}

void tcpSock::nptBusy() {
    auto a = qobject_cast<QTcpSocket *>(sender());
    while (a->canReadLine()) {
        QString bb(a->readLine());
        qInfo() << bb;
        if (bb.left(2) == "OK") {
            busy = false;
        }

    }
}
