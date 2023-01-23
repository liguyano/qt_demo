//
// Created by kurum on 12/4/2022.
//

#ifndef QT_DEMO_PAINTWIDGET_H
#define QT_DEMO_PAINTWIDGET_H
#define STATUE_DRAW 1
#define STATUE_SELECT 2
#define STATUE_MOVE 3

#include "publicInclude.h"

#ifdef _DEBUG
#include "cmake-build-debug/ui_paintWidget.h"
#else

#include "cmake-build-release/ui_paintWidget.h"

# endif

#include "PaintGracy.h"
#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
namespace Ui { class paintWIdget; }
QT_END_NAMESPACE

class paintWidget : public QWidget {
Q_OBJECT
public:
    explicit paintWidget(QWidget *parent = nullptr);

    ~paintWidget();

    PaintGracy *paintArea;

    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

public slots:

    void mouse_move(QPoint point);

    void mouse_down(bool isleft, QPoint where);

    void select_button_clicked(bool clicked);

    void draw_button_clicked(bool clicked);

    void color_button_clicked(bool clicked);

    void del_button_clicked(bool clicked);

    void mouse_button_clicked(bool clicked);


private:
    qint32 statue = STATUE_DRAW;
    qint32 pen_font_size;
    QColor pen_brush_color;
    QPoint lastPoint = {0, 0};
    //QPoint l_lastPoint = {0, 0};
    QGraphicsScene *scene;
    Ui::paintWIdget *ui;

    void _sceneMove(QPoint point);

};


#endif //QT_DEMO_PAINTWIDGET_H
