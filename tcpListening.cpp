//
// Created by kurum on 2022/06/01.
//

#include "tcpListening.h"

[[noreturn]] void tcpListening::run() {
    /* int itime=0;
     while (true)
     {
         sleep(1);
         itime++;
         itime%=50;
         if (itime==40)
         {
            // emit testAlive();
         }
     }*/

    //读取的数据报大小

}


tcpListening::tcpListening() {
    this->udpSock = new QUdpSocket;
    udpSock->bind(7001);
    this->setProperty("times", 0);
    printf_s("bind 7001 succeed\n");
    connect(udpSock, SIGNAL(readyRead()), this, SLOT(processData()));
}

void tcpListening::processData() {
    QString strData;

    while (udpSock->hasPendingDatagrams()) {
        QByteArray dataGram;
        dataGram.resize(udpSock->pendingDatagramSize());
        QHostAddress add;
        quint16 a;
        udpSock->readDatagram(dataGram.data(), dataGram.size(), &add, &a);
        qInfo() << add.toString() << ":" << dataGram << a;
        if (dataGram == "hello") {
            emit recvReginster(add, a);
            // udpSock->writeDatagram("ok",add,7001);
        }
        QString message(dataGram);
        if (message[0] == 'I' && message[1] == 'M') {
            emit add_new(add);
        }
        if (message[0] == 'M') {
            emit message_come(message.mid(1, -1), add);
        }
        if (message == "quit") {
            emit quit_n(add);
        }
        if (message[0] == 'F')//F_filename_100;
        {
            auto me = message.split('_');
            QString file_name = me[1];
            if (me.size() > 3) {
                for (int i = 2; i < me.size() - 1; ++i) {
                    file_name += "_" + me[i];
                }
            }
            emit file_come(file_name, add, me[me.size() - 1].toInt());
        }
        if (message == "test") {
            auto a = this->property("times").value<int>();
            this->setProperty("times", ++a);
            emit test(a);
        }
/*        if (message=="end")
        {
            emit file_end();
        }*/
    }
}

tcpListening::tcpListening(QObject *parent) : QThread(parent) {
    this->udpSock = new QUdpSocket;
    udpSock->bind(7001);
    printf_s("bind 7001 succeed\n");
    connect(udpSock, SIGNAL(readyRead()), this, SLOT(processData()));
}

QUdpSocket *tcpListening::getUdpSock() const {
    return udpSock;
}
