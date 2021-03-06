#include "tryte.h"


Tryte::Tryte()
{
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        data[i].setTrit(0);
    }
}

Tryte::~Tryte()
{

}

QString Tryte::getData()
{
    QString result;
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        result.append(QString::number(this->trit(i)));
    }
    return result;
}



void Tryte::setData(QString data)
{
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        this->setTrit(Trit(data.at(i).digitValue()), i);
    }
}

void Tryte::setTrit(Trit trit_, int index)
{
    data[index].setTrit(trit_.trit());
}

size_t Tryte::trit(int index) const
{   
    return data[index].trit();
}

unsigned int Tryte::numberRank() const
{
    unsigned int rank = TRYTE_SIZE - 1;
    for(int i = 1; i < TRYTE_SIZE; i++)
    {
        if(this->trit(i) == 0)
        {
            rank--;
        }
        else
        {
            return rank;
        }
    }
}

int Tryte::toNum()
{
    int result = 0;
    int degree = TRYTE_SIZE - 2;
    for(int i = 1; i < TRYTE_SIZE; i++)
    {
        result += data[i].trit() * pow(3,degree);
        degree--;
    }
    if(data[0].trit() == 1)
    {
        result = -result;
    }
    return result;
}

Tryte &Tryte::operator=(QString value)
{
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        data[i].setTrit(value[i].digitValue());
    }
}

bool operator==(const Tryte &left, const QString &right)
{
    QString leftToStr;
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        leftToStr.append(QString::number(left.trit(i)));
    }
    return leftToStr == right;

}


