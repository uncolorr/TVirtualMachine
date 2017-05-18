#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>
#include <QFile>
#include <QMap>
#include <iostream>
#include <QDebug>
#include <QRegExp>
#include "tint.h"
#include "tfloat.h"

const int PARAM_MEM_BEGIN = 255;

using namespace std;

class Translator
{
private:
    QMap<QString, QString> syntax_;
    QVector<QString> parameters_;
    QVector<QString> comands_;
    QMap<QString, QString> regs_;
    QMap<QString, QString> floatRegs_;
    unsigned countCommands_;

    QRegExp numRegExp_;
private:
    void initRegs();
    bool isFloatReg(QString floatReg);
    bool isReg(QString reg);
    bool isNum(QString num);
    bool isFloatNum(QString floatNum);
    bool isSym(QString sym);
    bool isAddr(QString addr);
    QString to3ss(QString value);
public:
    Translator();
    ~Translator();

    QMap<QString, QString> syntax();
    QMap<QString, QString> regs();
    QMap<QString, QString> floatRegs();
    QVector<QString> parameters();    
    QVector<QString> comands();
    unsigned countCommands();

    void loadSyntax(QString fileName);
    void loadCode(QString fileName);
    void loadMemory(QVector<Tryte>& memory);
};

#endif // TRANSLATOR_H
