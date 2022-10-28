//
// Created by kurum on 10/27/2022.
//

#ifndef QT_DEMO_USERINFO_H
#define QT_DEMO_USERINFO_H

#include "publicInclude.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"

class userInfo : public QObject {
Q_OBJECT
public:
    bool creatInitFile();

    bool lood(QString path);

    userInfo();

private:
    QString settingPath;

};


#endif //QT_DEMO_USERINFO_H
