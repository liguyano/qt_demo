//
// Created by kurum on 2022/06/11.
//

#ifndef QT_DEMO_TCPSOCK_H
#define QT_DEMO_TCPSOCK_H

#include "publicInclude.h"


class tcpSock : public QObject {
Q_OBJECT
public:
    QTcpServer *tcp;
    QString fileNa;
    QFileInfo fileInfo;
    QProgressBar *pers;

    explicit tcpSock(QString fileName, QObject *parent = nullptr);

    qint64 star(int port);

    void SendFile(QTcpSocket *a, QString fileName);

    bool busy = false;

public slots:

    void deal_with();

    void onNewConnection();

    void nptBusy();

signals:

    void end();

};


#endif //QT_DEMO_TCPSOCK_H
