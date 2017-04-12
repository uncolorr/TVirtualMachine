#include "tchar.h"

TChar::TChar()
{

}

TChar::TChar(int value)
{
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
        data.setTrit(Trit(remainders.top()), i + r + 1);
        remainders.pop();
        i++;
    }
}

TChar::TChar(char symbol)
{

}

TChar::~TChar()
{

}
