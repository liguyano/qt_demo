//
// Created by kurum on 2022/06/01.
//

#include "udpListening.h"

[[noreturn]] void udpListening::run() {
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


udpListening::udpListening(int port) {
    this->udpSock = new QUdpSocket;
    udpSock->bind(port);
    this->setProperty("times", 0);
    printf_s("bind 7001 succeed\n");
    connect(udpSock, SIGNAL(readyRead()), this, SLOT(processData()));
}

void udpListening::processData() {
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
        /*if (message[0] == 'F')//F_filename_100/;
        {
            auto me = message.split('_');
            QString file_name = me[1];
            if (me.size() > 3) {
                for (int i = 2; i < me.size() - 1; ++i) {
                    file_name += "_" + me[i];
                }
            }
            emit file_come(file_name, add, me[me.size() - 1].toInt(),"");
        }*/
        if (message.left(2) == "FD")//FD?filename?100?new1
        {
            auto ff = message.split('?');
            emit file_come(ff[1], add, ff[2].toInt(), ff[3]);
        } else if (message.left(2) == "FI") {
            auto ff = message.split('?');
            emit icon_come(ff[1], add, ff[2].toInt(), ff[3]);
        }
        if (message == "test") {
            auto a = this->property("times").value<int>();
            this->setProperty("times", ++a);
            emit test(a);
        }
        if (message[0] == 'N') {
            emit name_come(message.mid(1, -1), add);
        }
        if (message.left(2) == "CD")
                emit creat_dir(message.mid(2));
/*        if (message=="end")
        {
            emit file_end();
        }*/
    }
}

udpListening::udpListening(QObject *parent, int port) : QThread(parent) {
    this->udpSock = new QUdpSocket;
    udpSock->bind(port);
    printf_s("bind %d succeed\n", port);
    connect(udpSock, SIGNAL(readyRead()), this, SLOT(processData()));
}

QUdpSocket *udpListening::getUdpSock() const {
    return udpSock;
}
