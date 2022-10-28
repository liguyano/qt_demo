//
// Created by kurum on 10/27/2022.
//


#include "ui_setting.h"
#include "setting.h"

setting::setting(QWidget *parents) : QDialog(parents),
                                     ui(new Ui::Setting), UserInfo(new userInfo) {
    ui->setupUi(this);
    UserInfo->lood("./setting/option.xml");
    UserInfo->change_self_info("friends.friend[name=dd].ipAddres", "002");
    // qInfo()<<UserInfo->read_info("user.ipAddres.v6");

}

setting::~setting() {
    delete UserInfo;
    delete ui;

}
