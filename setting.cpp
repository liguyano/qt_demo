//
// Created by kurum on 10/27/2022.
//


#include "ui_setting.h"
#include "setting.h"

setting::setting(QWidget *parents) : QDialog(parents),
                                     ui(new Ui::Setting), UserInfo(new userInfo) {
    ui->setupUi(this);
    UserInfo->lood("./setting/option.xml");
    ui->portInput->setText(UserInfo->read_info("user.port"));
    ui->lineEdit->setText(UserInfo->read_info("user.name"));
    connect(this, SIGNAL(Save()), this, SLOT(saveTheName()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveTheName()));
    // UserInfo->change_self_info("friends.friend[name=dd].ipAddres", "002");
    qInfo() << ui->buttonBox->buttons()[0]->text();
    // qInfo()<<UserInfo->read_info("user.ipAddres.v6");

}

setting::~setting() {
    delete UserInfo;
    delete ui;

}

void setting::saveTheName() {
    //ui->lineEdit->text();
    UserInfo->change_self_info("user.name", ui->lineEdit->text());
    UserInfo->change_self_info(("user.port"), ui->portInput->text());
    emit port_change(ui->portInput->text().toInt());
}
