//
// Created by kurum on 2022/06/01.
//

#ifndef QT_DEMO_UDPLISTENING_H
#define QT_DEMO_UDPLISTENING_H

#include "publicInclude.h"

class udpListening : public QThread {
Q_OBJECT
private:
    QUdpSocket *udpSock;
public:
    QUdpSocket *getUdpSock() const;

protected:

    [[noreturn]] void run() Q_DECL_OVERRIDE;

public:
    explicit udpListening(QObject *parent = nullptr, int port = 7001);

    udpListening(int port = 7001);

public slots:

    void processData();

signals:

    void recvReginster(QHostAddress add, quint16 a);

    void add_new(QHostAddress add);

    void quit_n(QHostAddress add);

    void message_come(QString message, QHostAddress addr);

    void testAlive();

    void file_come(QString fileName, QHostAddress add, qint64 size, QString fm);

    void file_end();

    void test(int i);

    void name_come(QString name, QHostAddress add);

    void creat_dir(QString path);
};

#endif //QT_DEMO_UDPLISTENING_H
