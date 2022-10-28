//
// Created by kurum on 10/27/2022.
//

#include "userInfo.h"

userInfo::userInfo() {
    auto a = 0;


}

bool userInfo::lood(QString path) {
    TiXmlDocument data;
    data.LoadFile(path.toStdString().c_str());


    return false;
}

bool userInfo::creatInitFile() {

    return false;
}
