#ifndef TCHAR_H
#define TCHAR_H

#include "tryte.h"
#include <stack>
using namespace std;
class TChar
{
private:
    Tryte data;
public:
    TChar();
    TChar(int value);
    TChar(char symbol);
    ~TChar();


};

#endif // TCHAR_H
