//
// Created by kurum on 2022/05/29.
//

#ifndef QT_DEMO_Q_PERSON_H
#define QT_DEMO_Q_PERSON_H

#include "publicInclude.h"

class Q_person : public QObject {
Q_OBJECT
    Q_CLASSINFO("version", "1.2");
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY age_changed)
    Q_PROPERTY(int ano MEMBER m_age)
private:
    int m_age = 9;
    int age = 0;
public:
    void setAge(int age);

public:
    int getAge() const;

public:
    explicit Q_person(QObject *parent = nullptr);

signals:

    void age_changed(int age);

public slots:

    void deal_age(int age);
};


#endif //QT_DEMO_Q_PERSON_H
