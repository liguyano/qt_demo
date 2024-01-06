//
// Created by kurum on 2/5/2023.
//

#include "loadingWidget.h"

loadingWidget::loadingWidget(QWidget *parent) : QWidget(parent), ui(new Ui::loading) {
    ui->setupUi(this);
}
