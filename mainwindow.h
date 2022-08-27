#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "publicInclude.h"
#include "Q_person.h"
#include "tcpListening.h"
#include "tcpSock.h"
#include <QDir>
#include <thread>
#include "tcpReceiver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
    Q_CLASSINFO("version", "12");
    Q_PROPERTY(QList<QHostAddress> allIp MEMBER all_ip);
public:

    MainWindow(QWidget *parent = nullptr);

    QList<QHostAddress> all_ip;
    QList<QHostAddress> all_user;
    QList<QStringList> messages;
    QList<QPushButton *> buttons;

    void changImgWidth(QString &origin, qint32 width);

    int who = 0;

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void setAllIp(QList<QHostAddress> allIp);

    void sent2All();

    tcpListening *tcp;
    tcpSock *sock;
    tcpReceiver *receiver;

    QList<QHostAddress> getAllip();

    ~MainWindow();

public slots:

    void btn_clicked();

    void deal_change();

    void sendSelfInfo(QHostAddress add, quint16 a);

    void regist_one(QHostAddress add);

    void usr_ben_clicked();

    void add_message(const QString &message, const QHostAddress &add);

    void test_alive();

    void remove_one(QHostAddress add);

    void send_file();

    void recv_file(QString fileName, QHostAddress add, qint64 size);

private:
    Ui::MainWindow *ui;
    Q_person *person;
};

#endif // MAINWINDOW_H
