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

    bool change_self_info(QString what, QString towhat);

    QString read_info(QString command);

    bool save_list(QStringList list, QString where, QString label, bool clear = 0);

    bool add_element(QString where, QString what, QString label, QMap<QString, QString> attribute = {});

    TiXmlElement *get_element(QString where);

    userInfo();

    ~userInfo();

    const TiXmlDocument &getData() const;

    QStringList read_multi_data(QString where);

private:
    TiXmlDocument data;
    QString settingPath;

};


#endif //QT_DEMO_USERINFO_H
