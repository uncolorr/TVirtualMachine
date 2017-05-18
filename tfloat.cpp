#include "tfloat.h"

void TFloat::setMantissa(TInt other)
{
    mantissa = other;
}

TFloat::TFloat()
{

}

TFloat::TFloat(float value)
{
    QVector<int> vec;
    TInt intPart = (int)(value);
    float fracPart = value - (int)(value);
    if(fracPart < 0)
    {
        fracPart = -fracPart;
    }
    for(int i = 0; i < SPACE_FOR_FRAC; i++)
    {
        fracPart *= SYS_BASE;
        vec.push_back((int)(fracPart));
        fracPart -= (int)(fracPart);
    }
    for(int i = 0; i < vec.size(); i++)
    {
 //       cout << vec.at(i);
    }
  //  cout << endl;
    Tryte tempTryte;
    tempTryte.setData(intPart.toString());
    Tryte tryte;
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        if(i - SPACE_FOR_FRAC >= 0)
        {
            tryte.setTrit(Trit(tempTryte.trit(i)),i - SPACE_FOR_FRAC);
        }
    }
    for(int i = 1; i <= vec.size(); i++)
    {
        tryte.setTrit(Trit(vec.at(i - 1)), TRYTE_SIZE - SPACE_FOR_FRAC - 1 + i);
    }

    TInt m(tryte);
    if(intPart.isNegative())
    {
        m = -m;
    }
    mantissa = m;
    degree = -SPACE_FOR_FRAC;
  //  cout << "number " << mantissa << " | " << degree << endl;
}

TFloat::TFloat(TInt m, TInt d)
{
    mantissa = m;
    degree = d;
}

QString TFloat::toString()
{
    QString result;
    return mantissa.toString();
}

TFloat::~TFloat()
{

}

TFloat &TFloat::operator=(const TFloat &other)
{
    this->mantissa = other.mantissa;
    this->degree = other.degree;
}

const TFloat& operator+(const TFloat &i)
{
    return i;
}

const TFloat operator-(const TFloat &i)
{
    TFloat result(-i.mantissa, i.degree);
    return result;
}

bool operator==(const TFloat &left, const TFloat &right)
{
    bool isMantissaEqual = true;
    Tryte leftMantissa;
    Tryte rightMantissa;
    leftMantissa.setData(left.mantissa.toString());
    rightMantissa.setData(right.mantissa.toString());
    for(int i = 0; i < TRYTE_SIZE - 1; i++)
    {
        if(leftMantissa.trit(i) != rightMantissa.trit(i))
        {
            isMantissaEqual = false;
            break;
        }
    }

    return (isMantissaEqual && (left.degree == left.degree));
}

bool operator!=(const TFloat &left, const TFloat &right)
{
    bool isMantissaEqual = true;
    Tryte leftMantissa;
    Tryte rightMantissa;
    leftMantissa.setData(left.mantissa.toString());
    rightMantissa.setData(right.mantissa.toString());
    for(int i = 0; i < TRYTE_SIZE - 1; i++)
    {
        if(leftMantissa.trit(i) != rightMantissa.trit(i))
        {
            isMantissaEqual = false;
            break;
        }
    }

    return !(isMantissaEqual && (left.degree == left.degree));
}

bool operator>=(const TFloat &left, const TFloat &right)
{
    return ((left > right) || (left == right));
}

bool operator<=(const TFloat &left, const TFloat &right)
{
    return ((left < right) || (left == right));
}

bool operator <(const TFloat &left, const TFloat &right)
{
    if(left.mantissa.isNegative() && !right.mantissa.isNegative())
    {
        return true;
    }

    if(!left.mantissa.isNegative() && right.mantissa.isNegative())
    {
        return false;
    }

    if(!left.mantissa.isNegative() && !right.mantissa.isNegative())
    {
        Tryte leftMantissa;
        Tryte rightMantissa;
        leftMantissa.setData(left.mantissa.toString());
        rightMantissa.setData(right.mantissa.toString());
        for(int i = 1; i < TRYTE_SIZE - 1; i++)
        {
            if(leftMantissa.trit(i) > rightMantissa.trit(i))
            {
                return false;
            }
            else if(leftMantissa.trit(i) < rightMantissa.trit(i))
            {
                return true;
            }
        }
    }

    if(left.mantissa.isNegative() && right.mantissa.isNegative())
    {
        Tryte leftMantissa;
        Tryte rightMantissa;
        leftMantissa.setData(left.mantissa.toString());
        rightMantissa.setData(right.mantissa.toString());
        for(int i = 1; i < TRYTE_SIZE - 1; i++)
        {
            if(leftMantissa.trit(i) > rightMantissa.trit(i))
            {
                return true;
            }
            else if(leftMantissa.trit(i) < rightMantissa.trit(i))
            {
                return false;
            }
        }
    }
    return false;
}

bool operator >(const TFloat &left, const TFloat &right)
{
    if(left.mantissa.isNegative() && !right.mantissa.isNegative())
    {
        return false;
    }

    if(!left.mantissa.isNegative() && right.mantissa.isNegative())
    {
        return true;
    }

    if(!left.mantissa.isNegative() && !right.mantissa.isNegative())
    {
        Tryte leftMantissa;
        Tryte rightMantissa;
        leftMantissa.setData(left.mantissa.toString());
        rightMantissa.setData(right.mantissa.toString());
        for(int i = 1; i < TRYTE_SIZE - 1; i++)
        {
            if(leftMantissa.trit(i) > rightMantissa.trit(i))
            {
                return true;
            }
            else if(leftMantissa.trit(i) < rightMantissa.trit(i))
            {
                return false;
            }
        }
    }

    if(left.mantissa.isNegative() && right.mantissa.isNegative())
    {
        Tryte leftMantissa;
        Tryte rightMantissa;
        leftMantissa.setData(left.mantissa.toString());
        rightMantissa.setData(right.mantissa.toString());
        for(int i = 1; i < TRYTE_SIZE - 1; i++)
        {
            if(leftMantissa.trit(i) > rightMantissa.trit(i))
            {
                return false;
            }
            else if(leftMantissa.trit(i) < rightMantissa.trit(i))
            {
                return true;
            }
        }
    }
    return false;

}

TFloat& operator+=(TFloat &left, const TFloat &right)
{
    left = left + right;
    return left;
}

TFloat& operator-=(TFloat &left, const TFloat &right)
{
    left = left - right;
    return left;
}

TFloat& operator*=(TFloat &left, const TFloat &right)
{
    left = left * right;
    return left;
}

TFloat& operator/=(TFloat &left, const TFloat &right)
{

}

const TFloat operator+(const TFloat &left, const TFloat &right)
{
    TFloat result;
    TFloat first = left;
    TFloat second = right;

    //cout << first.mantissa << " | " << first.degree << endl;

    //cout << second.mantissa << " | " << second.degree << endl;
    if(left.degree > right.degree)
    {
        while(first.degree != second.degree)
        {
            first.degree--;
            first.mantissa *= SYS_BASE;
        }
    }
    else if(left.degree < right.degree)
    {
        while(first.degree != second.degree)
        {
            second.degree--;
            second.mantissa *= SYS_BASE;
        }
    }

   // cout << first.mantissa << " | " << first.degree << endl;
   // cout << second.mantissa << " | " << second.degree << endl;

    result.degree = first.degree;
    result.mantissa = first.mantissa + second.mantissa;
  //  cout << endl <<"result: " << result.mantissa << " | " << result.degree;



    return result;

}

const TFloat operator-(const TFloat &left, const TFloat &right)
{
    TFloat result;
    TFloat first = left;
    TFloat second = right;

    cout << first.mantissa << " | " << first.degree << endl;

    cout << second.mantissa << " | " << second.degree << endl;
    if(left.degree > right.degree)
    {
        while(first.degree != second.degree)
        {
            first.degree--;
            first.mantissa *= SYS_BASE;
        }
    }
    else if(left.degree < right.degree)
    {
        while(first.degree != second.degree)
        {
            second.degree--;
            second.mantissa *= SYS_BASE;
        }
    }

  //  cout << first.mantissa << " | " << first.degree;
  //  cout << second.mantissa << " | " << second.degree;

    result.degree = first.degree;
    result.mantissa = first.mantissa - second.mantissa;
   // cout << endl <<"result: " << result.mantissa << " | " << result.degree;

    return result;
}

const TFloat operator/(const TFloat &left, const TFloat &right)
{

}

const TFloat operator*(const TFloat &left, const TFloat &right)
{
    TFloat result;
    TFloat first = left;
    TFloat second = right;
    result.mantissa = first.mantissa * second.mantissa;
    Tryte tempTryte;
    tempTryte.setData(result.mantissa.toString());
    Tryte tryte;
    for(int i = 1; i < TRYTE_SIZE - SPACE_FOR_FRAC; i++)
    {
        tryte.setTrit(Trit(tempTryte.trit(i)), i + SPACE_FOR_FRAC);
    }
    if (result.mantissa.isNegative())
    {
        tryte.setTrit(Trit(1), 0);
    }

    TInt m(tryte);
    result.mantissa = m;
    result.degree = -SPACE_FOR_FRAC;
   // cout << endl <<"result: " << result.mantissa << " | " << result.degree;

    return result;
}
