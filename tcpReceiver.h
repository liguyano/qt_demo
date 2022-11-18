//
// Created by kurum on 2022/06/11.
//

#ifndef QT_DEMO_TCPRECEIVER_H
#define QT_DEMO_TCPRECEIVER_H

#include "publicInclude.h"
#include "userInfo.h"

class tcpReceiver : public QObject {
Q_OBJECT
    QTcpSocket *rec;
    QList<QByteArray> bytes;

    QFile *file;

public:
    QString fileName;
    qint64 size;
    QProgressBar *pers;
    qint64 size_recv;

    explicit tcpReceiver(QString FileName, QObject *parent = nullptr);

    void conn(const QHostAddress &add, QString path = "./file_recv/");

    void save();

    ~tcpReceiver();

signals:

    void file_persent(QHostAddress add, qint32 persent, int speed);

public slots:

    void deal_mess();

    void end();
};


#endif //QT_DEMO_TCPRECEIVER_H
