#ifndef TCHAR_H
#define TCHAR_H

#include "tint.h"
#include <stack>
using namespace std;
class TChar
{
private:
    TInt data;
public:
    TChar();
    TChar(unsigned value);
    TChar(char symbol);
    TChar(const TChar& other);
    TChar(const Tryte& tryte);
    ~TChar();
public:
    TInt getData();
    void setData(const TInt& other);
public:
    TInt &operator= (char symbol);
    friend ostream& operator << (ostream & os, const TChar& value);
    friend istream& operator >> (istream & is, TChar& value);


};

#endif // TCHAR_H
