//
// Created by kurum on 2022/05/29.
//

#ifndef QT_DEMO_PUBLICINCLUDE_H
#define QT_DEMO_PUBLICINCLUDE_H

#include <QDebug>
#include <QMainWindow>
#include <QMetaClassInfo>
#include <QProgressBar>
#include <QtNetwork/QHostInfo>
#include <QFile>
#include <QTcpServer>
#include <QApplication>
#include <QTcpSocket>
#include <QThread>
#include <QUdpSocket>
#include <QPushButton>
#include <QTextBrowser>
#include <QTextDocument>
#include <QDateTime>
#include <QMouseEvent>
#include <QFileDialog>
#include <QPainter>
#define C_STR(A) (A).toStdString().c_str()
#define pr() qInfo()

typedef QString qs;

#endif //QT_DEMO_PUBLICINCLUDE_H
