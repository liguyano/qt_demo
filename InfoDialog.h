
#ifdef _DEBUG
#include "cmake-build-debug//ui_selfInfo.h"
#else

#include "cmake-build-release/ui_selfInfo.h"

# endif


#ifndef QT_DEMO_INFODIALOG_H
#define QT_DEMO_INFODIALOG_H

#include "publicInclude.h"
#include <QDialog>
#include "userInfo.h"
#include <QStringListModel>

QT_BEGIN_NAMESPACE

namespace Ui { class Infod; }
QT_END_NAMESPACE
class InfoDialog : public QDialog {
Q_OBJECT
public:
    explicit InfoDialog(QStringList info, QWidget *parent = nullptr);

private:
    Ui::Infod *ui;
};


#endif //QT_DEMO_INFODIALOG_H
