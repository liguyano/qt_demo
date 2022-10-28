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
// frindes.frined[name=haha].a
bool userInfo::change_self_info(QString what, QString value) {
    auto command = what.split(".");
    auto a = data.RootElement();
    auto d = a;
    QStringList attr = {};
    for (int i = 0; i < command.length(); ++i) {
        d = a;
        if (command[i].count("[") > 0) {
            auto aComm = command[i].mid(command[i].indexOf("[") + 1,
                                        command[i].indexOf("]") - command[i].indexOf("[") - 1);
            qInfo() << aComm;
            command[i] = command[i].remove(command[i].indexOf("["), command[i].indexOf("]"));
            //qInfo()<<"comi:   "<<command[i];
            auto va = aComm.split("=")[1];
            auto Comm = aComm.split("=")[0];
            qInfo() << va << "  " << Comm;
            a = a->FirstChildElement(C_STR(command[i]));

            while (a != NULL && QString(a->Attribute(C_STR(Comm))) != va) {

                a = a->NextSiblingElement();
            }
            if (a == NULL) {
                auto c = new TiXmlElement(C_STR(command[i]));
                c->SetAttribute(C_STR(Comm), C_STR(va));
                d->LinkEndChild(c);
                a = c;
            }
        } else {
            a = a->FirstChildElement(C_STR(command[i]));
        }// deal when contains attribte

        if (a == NULL) {
            auto c = new TiXmlElement(C_STR(command[i]));
            d->LinkEndChild(c);
            a = d->FirstChildElement(C_STR(command[i]));
        }
    }
    auto b = a->FirstChild();

    if (b == NULL || !b->NoChildren()) {
        a->LinkEndChild(new TiXmlText(C_STR(value)));
    } else {
        qInfo() << b->Value();
        b->SetValue(C_STR(value));
    }
    return 1;
}

userInfo::~userInfo() {
    data.SaveFile();
    data.Clear();
}

QString userInfo::read_info(QString what) {
    auto command = what.split(".");
    auto a = data.RootElement();
    auto d = a;
    for (int i = 0; i < command.length(); ++i) {
        d = a;
        if (command[i].count("[") > 0) {
            auto aComm = command[i].mid(command[i].indexOf("[") + 1,
                                        command[i].indexOf("]") - command[i].indexOf("[") - 1);
            qInfo() << aComm;
            command[i] = command[i].remove(command[i].indexOf("["), command[i].indexOf("]"));
            //qInfo()<<"comi:   "<<command[i];
            auto va = aComm.split("=")[1];
            auto Comm = aComm.split("=")[0];
            qInfo() << va << "  " << Comm;
            a = a->FirstChildElement(C_STR(command[i]));

            while (a != NULL && QString(a->Attribute(C_STR(Comm))) != va) {

                a = a->NextSiblingElement();
            }
            if (a == NULL) {
                auto c = new TiXmlElement(C_STR(command[i]));
                c->SetAttribute(C_STR(Comm), C_STR(va));
                d->LinkEndChild(c);
                a = c;
            }
        } else {
            a = a->FirstChildElement(C_STR(command[i]));
        }
        if (a == NULL) {
            auto c = new TiXmlElement(C_STR(command[i]));
            d->LinkEndChild(c);
            a = d->FirstChildElement(C_STR(command[i]));
        }
    }
    auto b = a->FirstChild();
    return b->Value();
}
