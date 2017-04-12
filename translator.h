#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>
#include <QFile>
#include <QMap>
#include <iostream>
#include <QDebug>
#include <QRegExp>
#include "tint.h"

const int PARAM_MEM_BEGIN = 255;

using namespace std;

class Translator
{
private:
    QMap<QString, QString> syntax_;
    QVector<QString> parameters_;
    QVector<QString> comands_;
    QMap<QString, QString> regs_;
    QRegExp numRegExp_;
private:
    void initRegs();
    bool isReg(QString reg);
    bool isNum(QString num);
    QString to3ss(QString value);
public:
    Translator();
    ~Translator();

    QMap<QString, QString> syntax();
    QMap<QString, QString> regs();
    QVector<QString> parameters();

    QVector<QString> comands();

    void loadSyntax(QString fileName);
    void loadCode(QString fileName);
    void loadMemory(QVector<Tryte>& memory);
};

#endif // TRANSLATOR_H
