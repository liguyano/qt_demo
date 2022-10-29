//
// Created by kurum on 10/29/2022.
//


#include "InfoDialog.h"

InfoDialog::InfoDialog(QStringList info, QWidget *parent) : QDialog(parent), ui(new Ui::Infod) {
    ui->setupUi(this);
    QStringListModel *model = new QStringListModel;
    model->setStringList(info);
    ui->listView->setModel(model);
}
