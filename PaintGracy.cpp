//
// Created by kurum on 12/5/2022.
//

#include "PaintGracy.h"

PaintGracy::PaintGracy(QWidget *parents) : QGraphicsView(parents) {

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(parents->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
}

void PaintGracy::mouseMoveEvent(QMouseEvent *event) {
    emit mouse_move(event->pos());
}

void PaintGracy::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
            emit mouse_click(LEFT_B, event->pos());
    else
            emit mouse_click(RIGHT_B, event->pos());
}
