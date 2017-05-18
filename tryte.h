#ifndef TRYTE_H
#define TRYTE_H

#include "trit.h"
#include <iostream>
#include <QString>
#include <cmath>
const int TRYTE_SIZE = 27;
const int SYS_BASE = 3;


class Tryte
{
private:
    Trit data[TRYTE_SIZE];
public:
    Tryte();
    ~Tryte();
    QString getData();
    void setData(QString data);
    void setTrit(Trit trit_, int index);
    size_t trit(int index) const;
    unsigned int numberRank() const;
    int toNum();

    friend bool operator==(const Tryte& left, const QString& right);

    Tryte &operator= (QString value);
};

#endif // TRYTE_H
