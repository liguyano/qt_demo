//
// Created by kurum on 2022/06/01.
//

#ifndef QT_DEMO_TCPLISTENING_H
#define QT_DEMO_TCPLISTENING_H

#include "publicInclude.h"

class tcpListening : public QThread {
Q_OBJECT
private:
    QUdpSocket *udpSock;
public:
    QUdpSocket *getUdpSock() const;

protected:

    [[noreturn]] void run() Q_DECL_OVERRIDE;

public:
    explicit tcpListening(QObject *parent = nullptr);

    tcpListening();

public slots:

    void processData();

signals:

    void recvReginster(QHostAddress add, quint16 a);

    void add_new(QHostAddress add);

    void quit_n(QHostAddress add);

    void message_come(QString message, QHostAddress addr);

    void testAlive();

    void file_come(QString fileName, QHostAddress add, qint64 size);

    void file_end();

    void test(int i);

    void name_come(QString name, QHostAddress add);

};

#endif //QT_DEMO_TCPLISTENING_H
