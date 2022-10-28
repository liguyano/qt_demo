//
// Created by kurum on 10/27/2022.
//

#include "userInfo.h"
#define C_STR(A) A.toStdString().c_str()

userInfo::userInfo() {
    auto a = 0;
    creatInitFile();
}

bool userInfo::lood(QString path) {
    data.LoadFile(path.toStdString().c_str());

    return false;
}

bool userInfo::creatInitFile() {
    QFile setData("./setting/option.xml");
    if (setData.exists()) {

    } else {
        setData.open(QIODevice::WriteOnly);
        setData.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                      "<data>\n"
                      "    <user>\n"
                      "        <name>\n"
                      "            deault\n"
                      "        </name>\n"
                      "        <id>001</id>\n"
                      "        <ipAddres>\n"
                      "            <v4>\n"
                      "                0.0.0.0\n"
                      "            </v4>\n"
                      "            <v6>\n"
                      "                ff::0.0.0.0\n"
                      "            </v6>\n"
                      "        </ipAddres>\n"
                      "    </user>\n"
                      "    <friends>\n"
                      "        <friend name=\"\">\n"
                      "            <ipAddres>\n"
                      "                <v4>\n"
                      "                    0.0.0.0\n"
                      "                </v4>\n"
                      "                <v6>\n"
                      "                    ff::0.0.0.0\n"
                      "                </v6>\n"
                      "            </ipAddres>\n"
                      "        </friend>\n"
                      "    </friends>\n"
                      "</data>"
        );
        setData.close();
    }

    return false;
}

bool userInfo::change_self_info(QString what, QString value) {
    auto command = what.split(".");
    auto first = data.FirstChild(command[0].toStdString().c_str());
    if (command[0] == "user") {
        auto scend = first->FirstChild(C_STR(command[1]));
        if (command.length() > 2) {
            auto addr = scend->FirstChild(C_STR(command[2]));
            addr->SetValue(C_STR(value));
            addr->Clear();
        } else {
            scend->SetValue(C_STR(value));
        }

    }
    return false;
}

userInfo::~userInfo() {
    data.SaveFile();
    data.Clear();
}
