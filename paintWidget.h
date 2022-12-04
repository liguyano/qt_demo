//
// Created by kurum on 12/4/2022.
//

#ifndef QT_DEMO_PAINTWIDGET_H
#define QT_DEMO_PAINTWIDGET_H

#include "publicInclude.h"

#ifdef _DEBUG
#include "cmake-build-debug/ui_paintWidget.h"
#else

#include "cmake-build-release/ui_paintWidget.h"

# endif
QT_BEGIN_NAMESPACE
namespace Ui { class paintWIdget; }
QT_END_NAMESPACE

class paintWidget : public QWidget {
Q_OBJECT
public:
    explicit paintWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

private:
    Ui::paintWIdget *ui;
};


#endif //QT_DEMO_PAINTWIDGET_H
