//
// Created by kurum on 2022/05/29.
//

#include "Q_person.h"


void Q_person::deal_age(int age) {
    qInfo() << "age changed\n" << age;
}

Q_person::Q_person(QObject *parent) : QObject(parent) {
    setProperty("name", "hello");

    emit age_changed(10);
}

int Q_person::getAge() const {
    return age;
}

void Q_person::setAge(int age) {
    Q_person::age = age;
}

