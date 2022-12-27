//
// Created by kurum on 12/4/2022.
//

#include <QHBoxLayout>
#include <QLabel>
#include <QColorDialog>
#include "paintWidget.h"

paintWidget::paintWidget(QWidget *parent) : QWidget(parent), ui(new Ui::paintWIdget) {
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlag(Qt::Window, true);

    /*
     *         paintArea = new QGraphicsView(paintWIdget);
        paintArea->setObjectName(QString::fromUtf8("paintArea"));
        paintArea->setGeometry(QRect(0, 40, 551, 381));
        */
    paintArea = new PaintGracy(this);
    paintArea->setObjectName(QString::fromUtf8("paintArea"));
    paintArea->setGeometry(QRect(0, 40, 551, 381));
    paintArea->setCursor(Qt::CrossCursor);
    paintArea->setDragMode(QGraphicsView::RubberBandDrag);
    connect(paintArea, SIGNAL(mouse_move(QPoint)), this, SLOT(mouse_move(QPoint)));
    connect(paintArea, SIGNAL(mouse_click(bool, QPoint)), this, SLOT(mouse_down(bool, QPoint)));
    connect(this->ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(select_button_clicked(bool)));
    connect(this->ui->draw_btn, SIGNAL(clicked(bool)), this, SLOT(draw_button_clicked(bool)));
    connect(this->ui->color_selecter, SIGNAL(clicked(bool)), this, SLOT(color_button_clicked(bool)));
    connect(this->ui->del_btn, SIGNAL(clicked(bool)), this, SLOT(del_button_clicked(bool)));
    scene = new QGraphicsScene(QRect(-200, -100, 400, 200));
    paintArea->setScene(scene);
    draw_button_clicked(true);
}


void paintWidget::paintEvent(QPaintEvent *event) {

    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    int w = this->width();
    int h = this->height();
    QRect rect1(w / 4, h / 4, w / 2, h / 2);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(rect1);

}

void paintWidget::mouse_move(QPoint point) {
    if (statue == STATUE_DRAW) {

/*        if (abs(point.y()-lastPoint.y())>=35)
        {  printf_s("%d ,%d  \n", point.x(), point.y());
            qInfo()<<"err"<<abs(point.y()-lastPoint.y());
           // lastPoint = l_lastPoint;
        }*/
        QGraphicsLineItem *item = new QGraphicsLineItem(); //矩形框正好等于scene的大小
        item->setFlags(QGraphicsItem::ItemIsSelectable     //可选，可以有焦点，但是不能移动
                       | QGraphicsItem::ItemIsFocusable);
        item->setLine(lastPoint.x(), lastPoint.y(), point.x(), point.y());
        QPen pen;
        lastPoint = point;
        pen.setColor(pen_brush_color);
        pen.setWidth(2);
        item->setPen(pen);
        item->setPos(-paintArea->size().rwidth() / 2, -paintArea->size().rheight() / 2);//缺省位置在scene的（0,0）
        // item->setSelected(true);
        scene->addItem(item);


    }
//qInfo()<<point.x()<<" "<<point.y();

    //  scene->clearSelection();
}

void paintWidget::mouseMoveEvent(QMouseEvent *event) {

}

void paintWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // qInfo()<<"sss";
        //lastPoint = event->pos();
    }
}

paintWidget::~paintWidget() {
    QPixmap pix = paintArea->grab();
    pix.save("./a.png");
}

void paintWidget::mouseReleaseEvent(QMouseEvent *event) {

}

void paintWidget::mouse_down(bool isleft, QPoint where) {
    if (isleft) {
        lastPoint = where;

        mouse_move(where);
    }
}

void paintWidget::select_button_clicked(bool clicked) {
    this->statue = STATUE_SELECT;
    paintArea->setMouseTracking(true);
    paintArea->setDragMode(QGraphicsView::RubberBandDrag);
    qInfo() << scene->selectedItems().count();
}

void paintWidget::draw_button_clicked(bool clicked) {
    this->statue = STATUE_DRAW;
    paintArea->setDragMode(QGraphicsView::NoDrag);
    paintArea->setMouseTracking(false);


}

void paintWidget::color_button_clicked(bool clicked) {
    pen_brush_color = QColorDialog::getColor(pen_brush_color, NULL, "选择填充颜色");

}

void paintWidget::del_button_clicked(bool clicked) {
    for (auto *s: scene->selectedItems()) {
        scene->removeItem(s);
    }
}

void paintWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    // qInfo()<<"size"<<event->size();
    paintArea->resize(event->size());
}
