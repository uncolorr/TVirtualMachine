#include "bigint.h"
#include "tryte.h"
BigInt::BigInt()
{

}

BigInt::BigInt(QString value)
{
    for(int i = 0; i < value.size(); i++)
    {
        value_.push_back(value[i].digitValue());
    }
}

BigInt::~BigInt()
{

}

int BigInt::size() const
{
    return value_.size();
}

int BigInt::operator[](int i) const
{
    return value_[i];
}

const BigInt operator+(const BigInt &left, const BigInt &right)
{
    int resSize;
    if(left.size() >= right.size())
    {
        resSize = left.size();
    }
    else
    {
        resSize = right.size();
    }
    QVector<int> result(resSize);

    for(int i = resSize - 1; i >= 0; i--)
    {
        result[i] += left[i] + right[i];
        int temp = result[i];
        result[i] = result[i] % 10; // остаток
        int dec = temp / 10;
        if(i)
        {
            result[i - 1] += dec;
        }
    }
}
