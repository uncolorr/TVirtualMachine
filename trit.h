
#ifndef TRIT_H
#define TRIT_H

#include <iostream>

class Trit
{
private:
   size_t value_;
private:
   size_t index(size_t t);
   size_t indexedTrit(size_t n);
public:
    Trit();
    Trit(size_t value);
    ~Trit();
    size_t trit() const;
    void setTrit(size_t value);    
    size_t increment(size_t n = 1);
    size_t decrement(size_t n = 1);
};



#endif // TRIT_H
