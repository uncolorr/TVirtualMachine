#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "tint.h"
#include "translator.h"
#include <QVector>
#include <QMap>
#include <iostream>

using namespace std;

class Processor
{
private:
    TInt ax; //регистры
    TInt bx;
    TInt cx;
    TInt dx;
    int pc; // указатель на номер команды
    int sp; // указатель на номер параметра
    QMap<QString, QString> syntax_;
    QMap<QString, TInt*> regs;
    void initRegs();
public:
    Processor(const QMap<QString, QString>& syntax);
    ~Processor();

    void start(QVector<Tryte>& memory, int cmdLength);
};

#endif // PROCESSOR_H
