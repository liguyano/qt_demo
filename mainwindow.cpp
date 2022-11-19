#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->dirExit("./setting/");
    QString imghtml = "<img filename= \"a.png\" src=\"a.png\" width=\"001\" height=\"28\" alt=\"404\"  />";
    changImgWidth(imghtml, 1);

    qInfo() << imghtml;
    ui->setupUi(this);

    this->upGradeuserIfo();
    connect(ui->actionhow, SIGNAL(triggered(bool)), this, SLOT(openSetting(bool)));
    connect(ui->actionself_info, SIGNAL(triggered(bool)), this, SLOT(open_self_info(bool)));
    userInfo us;
    ui->groupBox->hide();
    us.lood("./setting/option.xml");
    port = us.read_info("user.port").toInt();
    qInfo() << "port" << port;
    //  ui->textBrowser->setAlignment(Qt::AlignLeft);
    auto btn = ui->centralwidget->findChild<QPushButton *>("unknow");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(btn_clicked()));
    person = new Q_person(this);
    auto clsi = person->metaObject()->classInfo(0);
    printf_s("%s \t %s", clsi.name(), clsi.value());
    connect(person, SIGNAL(age_changed(int)), this, SLOT(deal_change()));
    auto ll = new QLabel(this);
    ll->setText("it's new");
    person->setProperty("age", 10);
    ui->unknow->setDisabled(true);
    ui->unknow->setShortcut(tr("alt+s"));
    // person->setProperty("ano",56);
    printf_s("ano:%d\n", person->property("ano").value<int>());
    ui->textBrowser->insertPlainText(QString::number(person->property("age").value<qint32>()) + "\n");
    ll->setGeometry({100, 100, 100, 20});
    QDir qDir("./file_recv");
    if (!qDir.exists()) {
        qInfo() << "mkdir";
        qDebug() << qDir.mkdir("../file_recv");
    }
    setAttribute(Qt::WA_DeleteOnClose);
    getAllip();
    qInfo() << all_ip.size();
    // qInfo()<<all_ip->at(1).toString();
    tcp = new tcpListening(this, port);
    tcp->setProperty("port", port);
    tcp->start();
    sock = new tcpSock("s.txt", this);
    receiver = new tcpReceiver("", this);
    /*   document=new QTextDocument;

       ui->textBrowser->setDocument(document);
       document->setHtml("<div align=\"right\">addds<div/><br/><div align=\"left\">addds<div/>");*/
    // ui->textBrowser->setAlignment(Qt::AlignRight);
    sent2All();
    connect(tcp, SIGNAL(recvReginster(QHostAddress, quint16)), this, SLOT(sendSelfInfo(QHostAddress, quint16)));
    connect(tcp, SIGNAL(add_new(QHostAddress)), this, SLOT(regist_one(QHostAddress)));
    connect(tcp, SIGNAL(message_come(QString, QHostAddress)), this, SLOT(add_message(QString, QHostAddress)));
    connect(tcp, SIGNAL(testAlive()), this, SLOT(test_alive()));
    connect(tcp, SIGNAL(quit_n(QHostAddress)), this, SLOT(remove_one(QHostAddress)));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(send_file()));
    connect(tcp, SIGNAL(file_come(QString, QHostAddress, qint64, QString)), this,
            SLOT(recv_file(QString, QHostAddress, qint64, QString)));
    connect(tcp, SIGNAL(name_come(QString, QHostAddress)), this, SLOT(add_nameAndip(QString, QHostAddress)));
    connect(tcp, SIGNAL(creat_dir(QString)), this, SLOT(creatDir(QString)));
    connect(ui->dir_send, SIGNAL(clicked(bool)), this, SLOT(send_dir()));
    connect(sock, SIGNAL(next()), this, SLOT(nextFIle()));
}

MainWindow::~MainWindow() {
    for (const auto &ip: all_user) {
        tcp->getUdpSock()->writeDatagram("quit", ip, port);
    }
    qInfo() << "bye";
    for (int i = 0; i < all_user.size(); ++i) {
        auto ip = all_user[i].toString().split(":")[3];
        QFile tmp("./" + ip + ".txt");
        tmp.open(QIODevice::WriteOnly);
        for (auto mess: messages[i]) {
            auto a = mess.toUtf8();
            tmp.write(a, a.length());
        }
    }
    delete ui;
}

void MainWindow::btn_clicked() {
    person->setAge(person->getAge() + 1);
    ui->label->setText(ui->lineEdit->text());
    QByteArray me = "M";
    me += ui->lineEdit->text();
    if (ui->lineEdit->text().size() > 0) {
        tcp->getUdpSock()->writeDatagram(me, all_user[who], this->port);
        QDateTime curDateTime = QDateTime::currentDateTime();
        QString str = "<div style=\" text-align:right\">";
        //    ui->textBrowser->setAlignment(Qt::AlignRight);
        str += "<font color ='black' size=3 >" + curDateTime.toString("hh:mm:ss") + "</font><br/>";
        str += "<font color ='black' style=\" background-color:rgba(230, 200, 200, 0.96);\" size=6>";
//        ui->textBrowser->insertHtml("<span style= font-size:xx-large; color:#ff0000;align:left; >ME: fds</span\n"
//                                    ">");
        str += ui->lineEdit->text() + "</font><div/>";
        messages[who].push_back(str);
        buttons[who]->click();
        //  qInfo()<<ui->textBrowser->toHtml();
        ui->lineEdit->clear();
    }
}

void MainWindow::deal_change() {
    //ui->textBrowser->setText();
    ui->textBrowser->insertPlainText(QString::number(person->property("age").value<int>()) + "\n");
}

QList<QHostAddress> MainWindow::getAllip() {
    auto hostname = QHostInfo::localHostName();
    ui->textBrowser->insertPlainText(hostname + "\n");
    auto hostInfo = QHostInfo::fromName(hostname);

    auto addList = hostInfo.addresses();

    for (const auto &hi: addList) {

        if (QAbstractSocket::IPv4Protocol == hi.protocol())//test if it is ipv4
        {
            all_ip.push_back(hi);
            auto b = hi.toString().split('.');
            ui->textBrowser->insertPlainText(hi.toString() + "\n");
        }

    }
    QStringList ssl = {};
    for (const auto &s: all_ip) {
        qInfo() << s.toString() << endl;
        ssl.append(s.toString());
    }
    userInfo userfo;
    userfo.lood("./setting/option.xml");
    userfo.save_list(ssl, "user.ipAddres", "v4", 1);
    /*
     * read attribute ok
     * auto aa = userfo.get_element("user");
     qInfo() << aa->Attribute("name");*/
    return addList;
}

void MainWindow::setAllIp(QList<QHostAddress> allIp) {
    all_ip = allIp;
}

void MainWindow::sendSelfInfo(QHostAddress add, quint16 a) {
    bool quit = false;
    auto ips = add.toString().split(':');
    auto iip = ips[ips.size() - 1];

    for (auto s: all_ip) {
        if (s.toString() == iip) {
            return;
        }
    }
    auto udps = tcp->getUdpSock();
    udps->writeDatagram("IM", add, this->port);
    QString mess = "N" + options.value("name");
    tcp->getUdpSock()->writeDatagram(mess.toStdString().c_str(), add, this->port);
}

void MainWindow::regist_one(QHostAddress add) {
    bool quit = false;
    auto ips = add.toString().split(':');
    auto iip = ips[ips.size() - 1];
    for (auto s: all_ip) {//if self
        if (s.toString() == iip) {
            return;
        }
    }

    ui->label->hide();
    int i = 0;
    for (const auto &user: all_user) {//if register already

        if (user.isEqual(add)) {
            buttons[i]->setDisabled(false);
            //tcp->getUdpSock()->writeDatagram("IM",add,this->port);
            return;
        }
        i++;
    }
    QFile record(iip + ".txt");
    QStringList mes;
    record.open(QIODevice::ReadOnly);
    if (record.exists()) {
        mes.push_back(record.readAll());
    }
    record.close();
    tcp->getUdpSock()->writeDatagram("IM", add, this->port);
    auto btn = new QPushButton(this);
    btn->setProperty("id", all_user.size());
    ip_name_map[add.toString()] = add.toString();
    btn->setProperty("ip", add.toString());
    ui->users->addWidget(btn);
    btn->setText(add.toString());
    all_user.push_back(add);

    messages.push_back(mes);
    buttons.push_back(btn);
    QString mess = "N" + options.value("name");
    tcp->getUdpSock()->writeDatagram(mess.toStdString().c_str(), add, this->port);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(usr_ben_clicked()));
}

void MainWindow::usr_ben_clicked() {
    auto btn = qobject_cast<QPushButton *>(QObject::sender());
    auto id = btn->property("id").value<int>();
    ui->textBrowser->clear();
    QString str1 = "";
    for (const auto &str: messages[id]) {
        str1 += str;
    }
    ui->textBrowser->append(str1);
    who = id;
    ui->unknow->setDisabled(false);
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void MainWindow::add_message(const QString &message, const QHostAddress &add) {
    int i = 0;
    for (const auto &s: all_user) {
        if (s.isEqual(add)) {
            //    ui->textBrowser->setAlignment(Qt::AlignLeft);
            QDateTime curDateTime = QDateTime::currentDateTime();
            messages[i].push_back("<div style=\" text-align:left; \"><font color ='black' size=3>" +
                                          curDateTime.toString("hh:mm:ss") + "</font><br/>");
            messages[i].push_back(
                    "<font color ='black' size=6 style=\"  background-color: #c2bdbd;\">" + message + "</font><div/>");
            if (i == who) {
                //ui->textBrowser->append("<div align=left><font color ='black' size=3>"+curDateTime.toString("hh:mm:ss")+"</font><br/>"+"<font color ='green' size=10>"+message+"</font><div/></br>");
                buttons[who]->click();
            }
            break;
        }
        i++;
    }
}

void MainWindow::test_alive() {
    for (auto btn: buttons) {
        btn->setDisabled(true);
    }
}

void MainWindow::sent2All() {
    for (auto ip: all_ip) {
        auto ips = ip.toString();
        auto all = ips.split('.');
        for (int i = 1; i < 255; ++i) {
            QString needIp = "";
            for (int j = 0; j < 3; ++j) {
                needIp += all[j];
                needIp += ".";
            }
            needIp += QString::number(i);
            //   qInfo()<<needIp;
            QHostAddress tmp(needIp);
            //tcp->getUdpSock()->writeDatagram("IM",tmp,this->port);
            tcp->getUdpSock()->writeDatagram("hello", tmp, this->port);
        }
    }
}

void MainWindow::remove_one(QHostAddress add) {
    int i = 0;
    for (const auto &s: all_user) {
        if (s.isEqual(add)) {
            buttons[i]->setDisabled(true);
            ui->unknow->setDisabled(true);
            ui->textBrowser->append("<font color=pink size=5>" + add.toString() + "断开连接<font/><br/>");
            break;
        }
        i++;
    }
}

void MainWindow::send_file() {
    userInfo us;
    us.lood("./setting/option.xml");
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("文件对话框！"),
                                                    us.read_info("user.fileOpenDir"));
    file_list.append(fileName + "?" + "");
    if (!sock->isBusy()) {
        emit sock->next();
    }
}


void MainWindow::recv_file(QString fileName, QHostAddress add, qint64 size, QString dir) {
//auto reciver=new tcpReceiver(add,fileName,this);

    auto pers = new QProgressBar(this);
    pers->setValue(0);
    receiver->fileName = fileName;
    receiver->size = size;

    receiver->pers = pers;
    receiver->conn(add, "./file_recv/" + dir);
    ui->perbars->addWidget(pers);
    auto la = new QLabel(fileName + "\nfrom " + add.toString());
    ui->perbars->addWidget(la);
    //  connect(tcp, SIGNAL(file_end()),receiver, SLOT(end()));
}

void MainWindow::paintEvent(QPaintEvent *event) {
    /*   QWidget::paintEvent(event);
       QPainter painter(this);
       painter.setRenderHint(QPainter::Antialiasing);
       painter.setRenderHint(QPainter::TextAntialiasing);
       int w=this->width();
       int h=this->height();
       QRect rect1(w/4,h/4,w/2,h/2);
       QPen pen;
       pen.setWidth(3);
       pen.setColor(Qt::red);
       pen.setStyle(Qt::SolidLine);
       pen.setCapStyle(Qt::FlatCap);
       pen.setJoinStyle(Qt::BevelJoin);
       painter.setPen(pen);
       QBrush brush;
       brush.setColor(Qt::yellow);
       brush.setStyle(Qt::SolidPattern);
       painter.setBrush(brush);
       painter.drawRect(rect1);*/
}


void MainWindow::changImgWidth(QString &origin, qint32 width) {
    auto i = origin.lastIndexOf("width=");
    origin.replace(i + 7, 3, QString("%1").arg(width, 3, 10, QLatin1Char('0')));
    //  qInfo()<<origin;
}

void MainWindow::dirExit(QString path) {
    QDir dir(path);
    if (dir.exists()) {
    } else {
        qDebug() << dir.mkdir("." + path);
    }

}

void MainWindow::openSetting(bool a) {
    auto dia = new setting(this);
    connect(dia, SIGNAL(port_change(qint32)), this, SLOT(port_change(qint32)));
    dia->exec();
    delete dia;
    upGradeuserIfo();

}


void MainWindow::upGradeuserIfo() {
    userInfo user;
    user.lood("./setting/option.xml");
    ui->myName->setText(user.read_info("user.name"));
    options["name"] = user.read_info("user.name");
    QString mess = "N" + options.value("name");
    for (auto ip: all_user) {
        //auto ip=btn->property("ip").toString();
        tcp->getUdpSock()->writeDatagram(mess.toStdString().c_str(), ip, this->port);
    }


}

void MainWindow::add_nameAndip(QString name, QHostAddress add) {
    ip_name_map[add.toString()] = (name);
    for (auto a: buttons) {
        a->setText(ip_name_map.value(a->property("ip").toString()));
    }
}

void MainWindow::open_self_info(bool a) {
    userInfo uu;
    uu.lood("./setting/option.xml");
    // uu.read_multi_data("user.ipAddres.v4");
    auto dia = new InfoDialog(uu.read_multi_data("user.ipAddres.v4"), this);
    dia->exec();
    delete dia;

}

void MainWindow::port_change(qint32 port) {
    this->port = port;
}

void MainWindow::sendF(QString fileName, QString p) {
    sock->busy = true;

    if (fileName.size() <= 0)
        return;
    printf_s("line 395: filename: %s path%s \n", fileName.toStdString().c_str(), p.toStdString().c_str());
    auto paths = fileName.split('/');
    QString pathName = "";
    for (int i = 0; i < paths.size() - 1; ++i) {
        pathName += paths[i];
        pathName += "/";
    }
    userInfo us;
    us.lood("./setting/option.xml");
    us.change_self_info("user.fileOpenDir", pathName);
    sock->fileNa = fileName;
    auto pers = new QProgressBar(this);
    pers->setValue(0);
    sock->pers = pers;
    port = us.read_info("user.port").toInt();
    sock->star(port);
    auto size = QFileInfo(fileName).size();
    QString mess = "FD?" + paths[paths.size() - 1] + "?" + QString::number(size) + "?" + p;
    tcp->getUdpSock()->writeDatagram(mess.toUtf8(), all_user[who], port);
    //  messages[who].append(QString("<div style=\" text-align:right\"><img filename= \"%1\" src=\"a.png\" width=\"034\" height=\"028\" alt=\"404\"  /><div/>").arg(fileName));
    // buttons[who]->click();
    ui->perbars->addWidget(pers);
    auto la = new QLabel(fileName + "\nto " + all_user[who].toString());
    ui->perbars->addWidget(la);
}

QString createMultipleFolders(const QString path) {
    QDir dir(path);
    if (dir.exists(path)) {
        return path;
    }

    QString parentDir = createMultipleFolders(path.mid(0, path.lastIndexOf('/')));
    QString dirName = path.mid(path.lastIndexOf('/') + 1);
    QDir parentPath(parentDir);
    if (!dirName.isEmpty()) {
        parentPath.mkpath(dirName);
    }
    return parentDir + "/" + dirName;
}

void MainWindow::creatDir(QString path) {
    qInfo() << path << endl;
    createMultipleFolders("./file_recv/" + path);
}

void MainWindow::send_dir() {
    userInfo us;
    us.lood("./setting/option.xml");
    if (file_list.size() > 0) {
        QMessageBox::critical(this, tr("warning"), tr("请等待文件夹传输完成"));
        return;
    }
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), us.read_info("user.fileOpenDir"),
                                                    QFileDialog::DontResolveSymlinks);
    QList<int> floor;
    auto dirs = new QStringList();
    dirs->append(dir);
    floor.append(1);
    while (dirs->size()) {
        dir = dirs->at(0);
        QString tPath = "";
        auto paths = dir.split("/");

        QString path;
        //   printf_s("dir:: %s\n",C_STR(dir));
        for (int i = paths.size() - floor[0]; i < paths.size(); ++i) {
            path = path + paths[i] + "/";
        }
        //path : qt_Demo/cmake-build-release/.cmake/api/v1/
        this->tcp->getUdpSock()->writeDatagram(C_STR(("CD" + path)), all_user[who], port);
        QDir dir1(dir);
        dir1.setFilter(QDir::AllDirs);
        auto fl = dir1.entryList(QDir::AllDirs);
        for (auto s: fl) {
            if (s == "." || s == "..")
                continue;
            //printf_s("%s/%s\n",C_STR(dir),C_STR(s));
            dirs->append(dir + "/" + s);
            floor.append(floor[0] + 1);
        }
        dir1.setFilter(QDir::Files);
        auto tfl = dir1.entryList(QDir::Files);
        for (auto s: tfl) {
            file_list.append(dir + "/" + s + "?" + path);
        }
        // QThread::sleep(100);
        dirs->removeAt(0);
        floor.removeAt(0);
    }
    if (!sock->busy)
            emit sock->next();
    delete dirs;
/*    QThread::sleep(100);
    if (dir != "") {

        qInfo() << "line 451: " << dir;
        auto paths = dir.split("/");
        auto path = "CD" + paths[paths.size() - 1];
        this->tcp->getUdpSock()->writeDatagram(path.toStdString().c_str(), all_user[who], port);
        path = paths[paths.size() - 1];
        file_path_tmp = path + "/";
        QDir dir1(dir);
        dir1.setFilter(QDir::Files);
        file_list = dir1.entryList(QDir::Files);

        for (auto &ff: file_list)ff = dir + "/" + ff + "?" + path + "/";
        if (!sock->busy)emit sock->next();
        delete dirs;
    }*/
}

void MainWindow::nextFIle() {
    if (file_list.size() >= 1) {
        // QThread::sleep(1);
        sendF(file_list[0].split("?")[0], file_list[0].split("?")[1]);
        file_list.removeAt(0);
    } else {

    }
}


