#ifndef BIGINT_H
#define BIGINT_H

#include <QVector>
#include <QString>
#include <iostream>


using namespace std;

class BigInt
{
private:
    QVector<unsigned int> value_;
public:
    BigInt();
    BigInt(QString value);
    ~BigInt();
    int size() const;
    int operator[] (int i) const;

    friend const BigInt operator+ (const BigInt& left, const BigInt& right);


};

#endif // BIGINT_H
