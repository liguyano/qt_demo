#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frinds.h"



MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->dirExit("./setting/");


    //qInfo() << imghtml;
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
    tcp = new udpListening(this, port);
    tcp->setProperty("port", port);
    tcp->start();
    sock = new tcpSock("s.txt", this);
    receiver = new tcpReceiver("", this);
    QWidget *contentWidget = new QWidget();
    ui->frindsArea->setWidget(contentWidget);
    ui->frindsArea->setWidgetResizable(true); // 使内容区域自动适应滚动区域大小
    frindBoxLayout = new QVBoxLayout(contentWidget);
    frindBoxLayout->setAlignment(Qt::AlignTop);
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
    connect(receiver, SIGNAL(persent(qint32)), this, SLOT(persent_change(qint32)));
    connect(ui->handWrite, SIGNAL(clicked(bool)), this, SLOT(handWrite_click()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(friend_click()));
    connect(tcp, SIGNAL(icon_come(QString, QHostAddress, qint64, QString)), this,
            SLOT(recv_icon(QString, QHostAddress, qint64, QString)));
    connect(receiver, SIGNAL(icon_end(QString, QHostAddress)), this, SLOT(setFrindIcon(QString, QHostAddress)));
    loadIcon();
    auto fris = us.getFrineds();
    for (auto f: fris) {
        if (f.isObject()) {
            // qInfo()<<f.toObject()["name"].toString();
            //qInfo()<<f.toObject()["v4"].toString();
            QHostAddress address(f.toObject()["name"].toString());
            //regist_one(QHostAddress(f.toObject()["v4"].toString()));
            //add_nameAndip(f.toObject()["name"].toString(), QHostAddress(f.toObject()["v4"].toString()));
            //remove_one(QHostAddress(f.toObject()["v4"].toString()));

            tcp->getUdpSock()->writeDatagram("hello", QHostAddress(f.toObject()["v4"].toString()), 7001);
            tcp->getUdpSock()->writeDatagram("IM", QHostAddress(f.toObject()["v4"].toString()), 7001);
        }
    }


}

MainWindow::~MainWindow() {
    for (const auto &ip: all_user) {
        tcp->getUdpSock()->writeDatagram("quit", ip, port);
    }
    qInfo() << "bye";
    for (int i = 0; i < all_user.size(); ++i) {
        auto ip = all_user[i].toString().split(":")[3];
        QFile tmp("./" + ip + ".html");
        tmp.open(QIODevice::WriteOnly);
/*        tmp.write(R"(<link rel="stylesheet" type="text/css" href="./setting/style.css" />)",68);
        tmp.write("\n",1);*/
        for (auto mess: messages[i]) {
            auto a = mess.toUtf8();
            tmp.write(a, a.length());
            tmp.write("\n", 1);
        }
    }
    delete ui;
}

void MainWindow::btn_clicked() {
    person->setAge(person->getAge() + 1);

    QByteArray me = "M";
    me += ui->lineEdit->text();
    if (ui->lineEdit->text().size() > 0) {
        tcp->getUdpSock()->writeDatagram(me, all_user[who], this->port);
        QDateTime curDateTime = QDateTime::currentDateTime();
/*        QString str = "<div style=\" text-align:right\">";
        //    ui->textBrowser->setAlignment(Qt::AlignRight);
        str += "<font color ='black' size=3 >" + curDateTime.toString("hh:mm:ss") + "</font><br/>";
        str += "<font color ='black' style=\" background-color:rgba(230, 200, 200, 0.96);\" size=6>";

        str += ui->lineEdit->text() + "</font><div/>";
        messages[who].push_back(str);*/
        messages[who].push_back("SM:" + ui->lineEdit->text() + ":" + curDateTime.toString("hh:mm:ss"));
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
    iip = iip.split('%')[0];
    for (auto s: all_ip) {//if self
        if (s.toString() == iip) {
            return;
        }
    }
    qInfo() << iip;
    int i = 0;
    for (const auto &user: all_user) {//if register already

        if (user.isEqual(add)) {
            buttons[i]->setDisabled(false);
            //tcp->getUdpSock()->writeDatagram("IM",add,this->port);
            return;
        }
        i++;
    }
    QFile record(iip + ".html");
    QStringList mes;

    if (record.exists()) {
        record.open(QIODevice::ReadOnly);
        while (!record.atEnd()) {
            mes.append(record.readLine());
            mes[mes.size() - 1] = mes[mes.size() - 1].replace('\n', "");
            //  printf_s("%s\n", C_STR(mes[mes.size()-1]));
        }
    } else {
        record.open(QIODevice::WriteOnly);
        mes.append(R"(<link rel="stylesheet" type="text/css" href="./setting/style.css" />)");
        record.write(R"(<link rel="stylesheet" type="text/css" href="./setting/style.css" />)", 68);
        record.write("\n", 1);
    }
    record.close();
    tcp->getUdpSock()->writeDatagram("IM", add, this->port);
    auto btn = new QPushButton(this);
    btn->setProperty("id", all_user.size());
    ip_name_map[add.toString()] = add.toString();
    btn->setProperty("ip", add.toString());

    btn->setText(add.toString());
    all_user.push_back(add);
    frindBoxLayout->addWidget(btn);
    QString iconFilePath = "D:/OneDrive - jxstnu.edu.cn/c++/demo/qt_Demo/cmake-build-release/file_recv/a.png";

    QPixmap pixmap(iconFilePath);
    btn->setIcon(pixmap);
    btn->setIconSize({32, 32});
    messages.push_back(mes);
    buttons.push_back(btn);
    QString mess = "N" + options.value("name");
    tcp->getUdpSock()->writeDatagram(mess.toStdString().c_str(), add, this->port);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(usr_ben_clicked()));
    userInfo us;
    us.lood("setting/option.xml");
    sendF(us.read_info("user.iconPath"), "", "FI");
}

void MainWindow::usr_ben_clicked() {
    auto btn = qobject_cast<QPushButton *>(QObject::sender());
    auto id = btn->property("id").value<int>();
    //  auto cc=ui->textBrowser->cursor();
    ui->textBrowser->clear();
    QString str1 = R"(<link rel="stylesheet" type="text/css" href="./setting/style.css" />)";
    for (auto &str: messages[id]) {
        auto mess = str.split(":");

        auto command = mess[0];
        QString str2;
        if (command == "SM") {
            str = str.replace('<', "&lt;");
            str = str.replace('>', "&gt;");
            str = str.replace(' ', "&nbsp;");//printf_s("%s \n", C_STR(str));
            str = str.replace('\n', "</br>");

            mess = str.split(":");
            str2 = "<div class=\"sender\">";
            //    ui->textBrowser->setAlignment(Qt::AlignRight);
            str2 += "<font class=\"time\">" + mess[mess.size() - 3] + ":" + mess[mess.size() - 2] + ":" +
                    mess[mess.size() - 1] + "</font><br/>";
            str2 += "<font class=\"send_text\">";
            QString tmpmess;//SM:mee::s::ss::1:2:2;
            for (int i = 1; i < mess.size() - 4; ++i) {
                str2 += mess[i] + ":";
            }
            str2 += mess[mess.size() - 4];
            str2 += +"</font><div/>";
            str = "D:" + str2;
        } else if (command == "M") {

            str = str.replace(' ', "&nbsp;");
            //printf_s("%s \n", C_STR(str));
            str = str.replace('<', "&lt;");
            str = str.replace('>', "&gt;");
            str = str.replace('\n', "</br>");
            mess = str.split(":");
            str2 = "<div class=\" recvd\">";
            //    ui->textBrowser->setAlignment(Qt::AlignRight);
            str2 += "<font class=\"time\">" + mess[mess.size() - 3] + ":" + mess[mess.size() - 2] + ":" +
                    mess[mess.size() - 1] + "</font><br/>";
            str2 += "<font class=\"recv_text\">";
            QString tmpmess;//SM:mee::s::ss::1:2:2;
            for (int i = 1; i < mess.size() - 4; ++i) {
                str2 += mess[i] + ":";
            }
            str2 += mess[mess.size() - 4];
            str2 += +"</font><div/>";
            str = str2;
        } else if (command == "PERSENT") {//<img filename= "a.png" src="a.png" width="001" height="28" alt="404"  />
            str2 += "<div style=\" text-align:" + mess[2] + "\">";
            str2 += "<img filename= \"a.png\" src=\"a.png\" width=\"" + mess[1] +
                    "\" height=\"28\" alt=\"404\"  />";
            str2 += "<font color='black' size=5>" + mess[1] + "%</font>";
            str2 + "</div>";
            if (mess[1].toInt() >= 100)
                str = str2;
        } else if (command == "D") {
            str2 = str.right(str.size() - 2);
            str = str2;
        } else {
            str2 = str;
        }
        str1 += str2;
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
            QDateTime curDateTime = QDateTime::currentDateTime();
            messages[i].push_back("M:" + message + ":" + curDateTime.toString("hh:mm:ss"));
            // messages[i].push_back("<div style=\" text-align:left; \"><font color ='black' size=3>" +
            //                             curDateTime.toString("hh:mm:ss") + "</font><br/>");
            /*  messages[i].push_back(
                      "<font color ='black' size=6 style=\"  background-color: #c2bdbd;\">" + message + "</font><div/>");*/
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
//auto reciver=new tcpReceiver(add,fileName,this)
    auto pers = new QProgressBar(this);
    pers->setValue(0);
    messages[who].append("PERSENT:0:left");
    receiver->fileName = fileName;
    receiver->setProperty("who", who);
    receiver->setProperty("id", messages[who].size() - 1);
    receiver->setProperty("align", "left");
    receiver->size = size;
    userInfo us;
    us.lood("./setting/option.xml");
    receiver->pers = pers;
    receiver->conn(add, us.read_info("user.fileSavePath") + dir);
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
    loadIcon();

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

/**
 * @arg p mean the path that you want to save in.
 * */
void MainWindow::sendF(QString fileName, QString p, QString type) {
    sock->busy = true;
    if (fileName.size() <= 0)
        return;

    printf_s("line"": filename: %s path%s \n", fileName.toStdString().c_str(), p.toStdString().c_str());
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
    QString mess = type + "?" + paths[paths.size() - 1] + "?" + QString::number(size) + "?" + p;
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
    userInfo us;
    us.lood("./setting/option.xml");
    createMultipleFolders(us.read_info("user.fileSavePath") + path);
}

void MainWindow::send_dir() {
    userInfo us;
    us.lood("./setting/option.xml");
/*    if (file_list.size() > 0) {
        QMessageBox::critical(this, tr("warning"), tr("请等待文件夹传输完成"));
        return;
    }*/
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), us.read_info("user.fileOpenDir"),
                                                    QFileDialog::DontResolveSymlinks);
    //printf_s("dir: %s\n",dir.toStdString().c_str());
    if (dir == "")return;
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
}

void MainWindow::nextFIle() {
    if (file_list.size() >= 1) {
        // QThread::sleep(1);
        sendF(file_list[0].split("?")[0], file_list[0].split("?")[1]);
        file_list.removeAt(0);
    } else {

    }
}

void MainWindow::persent_change(int pers) {
    messages[receiver->property("who").toInt()][receiver->property("id").toInt()] = "PERSENT:" + QString::number(pers)
                                                                                    + ":left";
    if (receiver->property("who").toInt() == who) {
        buttons[who]->click();
    }
}

void MainWindow::handWrite_click() {
    auto h = new paintWidget(this);
    h->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    ui->groupBox->hide();
}

void MainWindow::friend_click() {
    auto fr = new frindWidget();
    fr->show();
    userInfo us;
    us.lood("./setting/option.xml");
    auto fris = us.getFrineds();
    for (auto f: fris) {
        if (f.isObject()) {
            // qInfo()<<f.toObject()["name"].toString();
            //qInfo()<<f.toObject()["v4"].toString();
            QHostAddress address(f.toObject()["name"].toString());
            regist_one(QHostAddress(f.toObject()["v4"].toString()));
            add_nameAndip(f.toObject()["name"].toString(), QHostAddress(f.toObject()["v4"].toString()));
            remove_one(QHostAddress(f.toObject()["v4"].toString()));
        }
    }
}

void MainWindow::loadIcon() {
    qInfo() << "loadIcon start";
    userInfo uinfo;
    uinfo.lood("./setting/option.xml");

    QPixmap pixmap(uinfo.getIconPath());
    QPixmap scaledPixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if (!pixmap.isNull()) {
        // 创建一个QBrush并设置其为QPixmap
        QBrush background(scaledPixmap);

        // 创建一个QPalette并设置其窗口背景为上述brush
        QPalette palette;
        palette.setBrush(QPalette::Window, background);

        // 将palette应用到frame
        ui->frame_3->setAutoFillBackground(true);
        ui->frame_3->setPalette(palette);
    }

}

bool isFileExists(const QString &filePath) {
    return QFile::exists(filePath);
}

void MainWindow::recv_icon(QString fileName, QHostAddress add, qint64 size, QString dir) {
    static int iconNum = 0;

    auto pers = new QProgressBar(this);
    pers->setValue(0);
    messages[who].append("PERSENT:0:left");
    receiver->fileName = fileName;
    receiver->isIcon = true;
    receiver->setProperty("who", who);
    receiver->setProperty("id", messages[who].size() - 1);
    receiver->setProperty("align", "left");
    receiver->size = size;
    userInfo us;
    us.lood("./setting/option.xml");
    receiver->pers = pers;
    receiver->conn(add, "./");
    ui->perbars->addWidget(pers);
    auto la = new QLabel(fileName + "\nfrom " + add.toString());
    ui->perbars->addWidget(la);
    qInfo() << add;


}

void MainWindow::setFrindIcon(QString fileName, QHostAddress add) {
    int i;
    for (const auto &s: all_user) {
        if (s.isEqual(add)) {
            //  buttons[i]->setIcon();
            qInfo() << __LINE__ << "./" + fileName;
            qInfo() << isFileExists(fileName);

            // fileName="./a.png";

            QPixmap pixmap("./" + fileName);
            if (pixmap.isNull()) {
                qInfo() << "null";
            } else {
                buttons[i]->setIcon(pixmap);
                buttons[i]->setIconSize({32, 32});
            }
            break;
        }
        i++;
    }
    receiver->isIcon = false;
}




