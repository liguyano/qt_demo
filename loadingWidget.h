//
// Created by kurum on 2/5/2023.
//

#ifndef README_MD_LOADINGWIDGET_H
#define README_MD_LOADINGWIDGET_H

#include "publicInclude.h"

#ifdef _DEBUG
#include "cmake-build-debug/ui_loading.h"
#else

#include "cmake-build-release/ui_loading.h"

# endif
QT_BEGIN_NAMESPACE
namespace Ui { class loading; };
QT_END_NAMESPACE


class loadingWidget : public QWidget {
Q_OBJECT
public:
    loadingWidget(QWidget *parent = nullptr);

private:
    Ui::loading *ui;
};


#endif //README_MD_LOADINGWIDGET_H
