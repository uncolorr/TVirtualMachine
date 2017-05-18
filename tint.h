#ifndef TINT_H
#define TINT_H

#include "tryte.h"
#include <iostream>
#include <stack>
#include <QVector>
#include <QDebug>


using namespace std;
const int INT_SIZE = 1;


class TInt
{
private:
    Tryte data;
private:
    long long abs(long long);
public:
    TInt();
    TInt(const TInt& other);
    TInt(long long value);
    TInt(const QString& value);
    TInt(const Tryte& tryte);
    ~TInt();

    int size() const;
    unsigned int numberRank() const;
    void setIn3ss(QString value);
    void print() const;
    QString toString() const;
    bool isNegative() const ;



    TInt& operator= (const TInt& other);
    friend const TInt operator+ (const TInt& left, const TInt& right);
    friend const TInt operator- (const TInt& left, const TInt& right);
    friend const TInt operator/ (const TInt& left, const TInt& right);
    friend const TInt operator* (const TInt& left, const TInt& right);

    friend TInt& operator+=(TInt& left, const TInt& right);
    friend TInt& operator-=(TInt& left, const TInt& right);
    friend TInt& operator/=(TInt& left, const TInt& right);
    friend TInt& operator*=(TInt& left, const TInt& right);

    friend bool operator==(const TInt& left, const TInt& right);
    friend bool operator!=(const TInt& left, const TInt& right);
    friend bool operator>(const TInt& left, const TInt& right);
    friend bool operator<(const TInt& left, const TInt& right);
    friend bool operator>=(const TInt& left, const TInt& right);
    friend bool operator<=(const TInt& left, const TInt& right);

    friend ostream& operator << (ostream & os, const TInt& value);
    friend istream& operator >> (istream & is, TInt& value);

    TInt &operator= (long long value);
    TInt &operator= (QString value);
    //унарный +
    friend const TInt& operator+(const TInt& i);
    //унарный -
    friend const TInt operator-(const TInt& i);
    //префиксный инкремент
    friend const TInt& operator++(TInt& i);
    //постфиксный инкремент
    friend const TInt operator++(TInt& i, int);
    //префиксный декремент
    friend const TInt& operator--(TInt& i);
    //постфиксный декремент
    friend const TInt operator--(TInt& i, int);

   friend const TInt& larger(const TInt& left,const TInt& right, TInt &first, TInt &second);




};

#endif // TINT_H
