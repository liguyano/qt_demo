//
// Created by kurum on 10/27/2022.
//
#include "publicInclude.h"
#include "userInfo.h"

#ifdef _DEBUG
#include "cmake-build-debug/ui_setting.h"
#else
#include "cmake-build-release/ui_setting.h"
# endif
#ifndef QT_DEMO_SETTING_H
#define QT_DEMO_SETTING_H

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui { class Setting; }
QT_END_NAMESPACE
class setting : public QDialog {
Q_OBJECT
signals:

    void Save();

    void port_change(qint32 port);

public slots:

    void saveTheName();

    void save_path_btn();

public:

    explicit setting(QWidget *parents = nullptr);

    userInfo *UserInfo;

    ~setting();

private:
    Ui::Setting *ui;
    QString name = "unknuupp";
};


#endif //QT_DEMO_SETTING_H
