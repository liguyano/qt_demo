//
// Created by kurum on 10/29/2022.
//

#ifndef QT_DEMO_INFODIALOG_H
#define QT_DEMO_INFODIALOG_H

#include "publicInclude.h"

QT_BEGIN_NAMESPACE

namespace Ui { class InfoDialog; }
QT_END_NAMESPACE
class InfoDialog : public QDialog {
Q_OBJECT

    explicit InfoDialog(QWidget *parent = nullptr);

private:
    Ui::InfoDialog *ui;
};


#endif //QT_DEMO_INFODIALOG_H
