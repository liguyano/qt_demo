//
// Created by kurum on 10/27/2022.
//

#include "userInfo.h"

userInfo::userInfo() {
    auto a = 0;
    creatInitFile();
}

bool userInfo::lood(QString path) {
    TiXmlDocument data;
    data.LoadFile(path.toStdString().c_str());


    return false;
}

bool userInfo::creatInitFile() {
    QFile setData("setting/option.xml");
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
