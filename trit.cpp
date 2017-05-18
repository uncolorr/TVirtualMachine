#include <trit.h>

Trit::Trit()
{
    value_ = 0;
}

Trit::Trit(size_t value)
{
    value_ = value % 3;
}

Trit::~Trit()
{

}

size_t Trit::trit() const
{
    return value_;
}

void Trit::setTrit(size_t value)
{
    value_ = value % 3;
}

size_t Trit::index(size_t t)
{
    switch(t)
    {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    }
}

size_t Trit::increment(size_t n)
{
    this->setTrit(indexedTrit( index(this->trit()) + n ));
    return this->trit();
}

size_t Trit::decrement(size_t n)
{
    this->setTrit(indexedTrit( index(this->trit())+3 - (n%3) ));
    return this->trit();
}

size_t Trit::indexedTrit(size_t n)
{
    switch(n % 3)
    {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    }
}
