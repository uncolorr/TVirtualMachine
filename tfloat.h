#ifndef TFLOAT_H
#define TFLOAT_H

#include "tint.h"
//1 трит 20 трит и 6 трит

const int SPACE_FOR_FRAC = 6;
class TFloat
{
private:
    TInt mantissa;
    TInt degree;
    void setMantissa(TInt other);
public:
    TFloat();
    TFloat(float value);
    TFloat(TInt m, TInt d );

    QString toString();

    ~TFloat();

    TFloat& operator= (const TFloat& other);
    friend const TFloat operator+ (const TFloat& left, const TFloat& right);
    friend const TFloat operator- (const TFloat& left, const TFloat& right);
    friend const TFloat operator/ (const TFloat& left, const TFloat& right);
    friend const TFloat operator* (const TFloat& left, const TFloat& right);

    friend TFloat& operator+=(TFloat& left, const TFloat& right);
    friend TFloat& operator-=(TFloat& left, const TFloat& right);
    friend TFloat& operator/=(TFloat& left, const TFloat& right);
    friend TFloat& operator*=(TFloat& left, const TFloat& right);

    friend bool operator==(const TFloat& left, const TFloat& right);
    friend bool operator!=(const TFloat& left, const TFloat& right);
    friend bool operator>(const TFloat& left, const TFloat& right);
    friend bool operator<(const TFloat& left, const TFloat& right);
    friend bool operator>=(const TFloat& left, const TFloat& right);
    friend bool operator<=(const TFloat& left, const TFloat& right);

    //унарный +
    friend const TFloat& operator+(const TFloat& i);
    //унарный -
    friend const TFloat operator-(const TFloat& i);
    //префиксный инкремент
    friend const TFloat& operator++(TFloat& i);
    //постфиксный инкремент
    friend const TFloat operator++(TFloat& i, int);
    //префиксный декремент
    friend const TFloat& operator--(TFloat& i);
    //постфиксный декремент
    friend const TFloat operator--(TFloat& i, int);
};

#endif // TFLOAT_H
