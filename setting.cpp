//
// Created by kurum on 10/27/2022.
//



#include "setting.h"

setting::setting(QWidget *parents) : QDialog(parents),
                                     ui(new Ui::Setting), UserInfo(new userInfo) {
    ui->setupUi(this);
    UserInfo->lood("./setting/option.xml");
    ui->portInput->setText(UserInfo->read_info("user.port"));
    ui->lineEdit->setText(UserInfo->read_info("user.name"));
    ui->file_save_line->setText(UserInfo->read_info("user.fileSavePath"));
    connect(this, SIGNAL(Save()), this, SLOT(saveTheName()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveTheName()));
    connect(ui->find_dir, SIGNAL(clicked(bool)), this, SLOT(save_path_btn()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(selectIcon()));
    qInfo() << ui->buttonBox->buttons()[0]->text();
}

setting::~setting() {
    delete UserInfo;
    delete ui;

}

void setting::saveTheName() {
    //ui->lineEdit->text();
    UserInfo->change_self_info("user.name", ui->lineEdit->text());
    UserInfo->change_self_info(("user.port"), ui->portInput->text());
    UserInfo->change_self_info(("user.fileSavePath"), ui->file_save_line->text());
    emit port_change(ui->portInput->text().toInt());
}

void setting::save_path_btn() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    UserInfo->read_info("user.fileSavePath"),
                                                    QFileDialog::DontResolveSymlinks);
    ui->file_save_line->setText(dir + "/");
}

void setting::selectIcon() {

    QString initialPath = QDir::currentPath();
    QString filter = "Image files (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)";

    // 显示对话框并获取所选文件名
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("打开图片"),
            initialPath,
            filter);

    if (!fileName.isEmpty()) {
        UserInfo->changeIconPath(fileName);
    }

}
