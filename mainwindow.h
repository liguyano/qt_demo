#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "publicInclude.h"
#include "Q_person.h"
#include "udpListening.h"
#include "tcpSock.h"
#include <QDir>
#include <thread>
#include "tcpReceiver.h"
#include "InfoDialog.h"
#include "setting.h"
#include "paintWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
    Q_CLASSINFO("version", "12");
    Q_PROPERTY(QList<QHostAddress> allIp MEMBER all_ip);
public:


    MainWindow(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    QList<QHostAddress> all_ip;
    QList<QHostAddress> all_user;
    QList<QStringList> messages;
    QList<QPushButton *> buttons;
    QMap<QString, QString> ip_name_map;
    QMap<QString, QString> options;

    void changImgWidth(QString &origin, qint32 width);

    int who = 0;

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void setAllIp(QList<QHostAddress> allIp);

    void sent2All();

    udpListening *tcp;
    tcpSock *sock;
    tcpReceiver *receiver;

    QList<QHostAddress> getAllip();

    ~MainWindow();

public slots:

    void persent_change(qint32 pers);

    void port_change(qint32 port);

    void open_self_info(bool a);

    void openSetting(bool a);

    void btn_clicked();

    void deal_change();

    void sendSelfInfo(QHostAddress add, quint16 a);

    void regist_one(QHostAddress add);

    void usr_ben_clicked();

    void add_message(const QString &message, const QHostAddress &add);

    void test_alive();

    void remove_one(QHostAddress add);

    void send_file();

    void send_dir();

    void recv_file(QString fileName, QHostAddress add, qint64 size, QString dir);

    void add_nameAndip(QString name, QHostAddress add);

    void creatDir(QString path);

    void nextFIle();

    void handWrite_click();


private:
    QStringList file_list;
    Ui::MainWindow *ui;
    Q_person *person;
    qint32 port;
    QString file_path_tmp;

    void sendF(QString filename, QString path = "");

    void dirExit(QString path);

    void upGradeuserIfo();


};

#endif // MAINWINDOW_H
