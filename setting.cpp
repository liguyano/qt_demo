//
// Created by kurum on 10/27/2022.
//


#include "ui_setting.h"
#include "setting.h"

setting::setting(QWidget *parents) : QDialog(parents), ui(new Ui::Setting) {
    ui->setupUi(this);
}

setting::~setting() {

}
