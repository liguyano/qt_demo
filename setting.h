//
// Created by kurum on 10/27/2022.
//
#include "publicInclude.h"

#ifndef QT_DEMO_SETTING_H
#define QT_DEMO_SETTING_H

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui { class Dialog; }
QT_END_NAMESPACE
class setting : public QDialog {
Q_OBJECT
public:
    explicit setting(QWidget *parents = nullptr);

private:
    Ui::Dialog *ui;
};


#endif //QT_DEMO_SETTING_H
