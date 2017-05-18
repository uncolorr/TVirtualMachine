#include "tchar.h"

TChar::TChar()
{

}

TChar::TChar(unsigned value)
{
    Tryte d;
    value %= 256;
    stack <int> remainders;
    if(value < SYS_BASE)
    {
        remainders.push(value);
    }
    else
    {
        while (value >= SYS_BASE)
        {
            int rem = value % SYS_BASE;

            value /= SYS_BASE;
            remainders.push(rem);

        }
        remainders.push(value);
    }

    int r = TRYTE_SIZE - remainders.size() - 1;
    int i = 0;

    while(remainders.size())
    {
        d.setTrit(Trit(remainders.top()), i + r + 1);
        remainders.pop();
        i++;
    }
    TInt temp(d);
    data = temp;
}

TChar::TChar(char symbol)
{
    int chr = (int)symbol;
    data = chr;
}

TChar::TChar(const TChar &other)
{
    data = other.data;
}

TChar::TChar(const Tryte &tryte)
{
    TInt temp(tryte);
    data = temp;
}

TChar::~TChar()
{

}

TInt TChar::getData()
{
    return data;
}

void TChar::setData(const TInt &other)
{
    data = other;
}

TInt &TChar::operator=(char symbol)
{
    TChar chr(symbol);
    data = chr.data;
}

ostream& operator <<(ostream &os, const TChar &value)
{
    string data = value.data.toString().toStdString();
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        os << data[i];
    }
    return os;
}

istream& operator >>(istream &is, TChar &value)
{
    char symbol;
    is >> symbol;
    TChar temp(symbol);
    value.setData(temp.data);
    return is;
}
