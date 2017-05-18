#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "tint.h"
#include "tfloat.h"
#include "tchar.h"
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
    TFloat eax;
    TFloat ebx;
    TFloat ecx;
    TFloat edx;
    int pc; // указатель на номер команды
    int sp; // указатель на номер параметра
    QMap<QString, QString> syntax_;
    QMap<QString, TInt*> regs;
    QMap<QString, TFloat*> floatRegs;
    void initRegs();
    void initFloatRegs();
public:
    Processor(const QMap<QString, QString>& syntax);
    ~Processor();

    void start(QVector<Tryte>& memory, QVector<Tryte>& ROM, int cmdLength);
};

#endif // PROCESSOR_H
