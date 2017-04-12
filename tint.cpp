#include "tint.h"

QVector<int> TInt::pow(int rank)
{
    if (!rank)
    {
        QVector<int> v = {1};
        for(int i = 0; i < 12; i++)
        {
            v.push_front(0);
        }
        return v;
    }

    if (rank == 1)
    {
        QVector<int> v = {3};
        for(int i = 0; i < 12; i++)
        {
            v.push_front(0);
        }
        return v;
    }
}

long long TInt::abs(long long v)
{
    if (v < 0)
    {
        return -v;
    }
    return v;
}

TInt::TInt()
{

}

TInt::TInt(const TInt &other)
{
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        data.setTrit(Trit(other.data.trit(i)), i);
    }
}

TInt::TInt(long long value)
{
    bool isPositive;
    if (value < 0)
    {
        isPositive = false;
    }
    else
    {
        isPositive = true;
    }
    value = abs(value);
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
    if(isPositive)
    {
        data.setTrit(Trit(0),0);
    }
    else
    {
        data.setTrit(Trit(1),0);
    }
}

TInt::TInt(const QString& value)
{
    QString number = value;
    bool isPositive;
    if (number[0] == '-')
    {
        isPositive = false;
    }
    else
    {
        isPositive = true;
    }
    number.remove('-');
    stack <unsigned int> result; // вид числа в троичной системе
    QVector<unsigned int> vecValue;
    for(int i = 0; i < number.size(); i++)
    {
        vecValue.push_back(number.at(i).digitValue());
    }

    while(vecValue.size() != 1 || vecValue.at(0) >= SYS_BASE)
    {
        QVector <unsigned int> nextVector;
        int rem = 0; // остаток
        for(int i = 0; i < vecValue.size(); i++)
        {
            if(vecValue.at(i) >= SYS_BASE)
            {
                rem = vecValue[i] % SYS_BASE; // остаток
                int n = vecValue[i] / SYS_BASE;
                nextVector.push_back(n);
                if(i != vecValue.size() - 1)
                {
                    vecValue[i+1] += rem * 10;
                }
            }
            else if (vecValue.at(i) < SYS_BASE)
            {
                rem = vecValue.at(i);
                nextVector.push_back(0);
                if(i != vecValue.size() - 1)
                {
                    vecValue[i+1] += vecValue[i] * 10;
                }
            }
        }

        result.push(rem);
        while(nextVector.at(0) == 0)
        {
            nextVector.removeFirst();
        }
        vecValue.clear();
        for(int i = 0; i < nextVector.size(); i++)
        {
            vecValue.push_back(nextVector.at(i));
        }
    }

    result.push(vecValue.at(0));
    int i = 0;
    int shift = TRYTE_SIZE - result.size() - 1;
    while(result.size())
    {
        data.setTrit(Trit(result.top()), i + shift + 1);
        qDebug() << "result.top()" << result.top();
        result.pop();
        i++;
    }

    if(isPositive)
    {
        data.setTrit(Trit(0),0);
    }
    else
    {
        data.setTrit(Trit(1),0);
    }
}

TInt::TInt(const Tryte &tryte)
{
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        this->data.setTrit(tryte.trit(i), i);
    }
}

TInt::~TInt()
{

}

int TInt::size() const
{
    return INT_SIZE;
}

unsigned int TInt::numberRank() const
{
    return data.numberRank();
}

void TInt::setIn3ss(QString value)
{
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        data.setTrit(Trit(value[i].digitValue()), i);
    }

}

void TInt::print() const
{
    //cout << endl;
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        qDebug() << "int" << data.trit(i);
    }
}

QString TInt::toString() const
{
    QString result;
    for(int i = 0; i < TRYTE_SIZE; i++)
    {
        result.append(QString::number(this->data.trit(i)));
    }
    return result;
}

bool TInt::isNegative() const
{
    return data.trit(0) == 1;
}

TInt &TInt::operator= (const TInt &other)
{
    data = other.data;
    return *this;
}

bool operator!=(const TInt &left, const TInt &right)
{
    for( int i = 0; i < TRYTE_SIZE; i++)
    {
        if(left.data.trit(i) != right.data.trit(i))
        {
            return true;
        }
    }
    return false;
}

istream& operator >>(istream & is,TInt &value)
{
    long long v;
    is >> v;
    value = v;
    return is;
}

ostream& operator<<(ostream & os, const TInt &value)
{
    for(size_t i = 0; i < TRYTE_SIZE; i++)
    {
        os << value.data.trit(i);
    }
    return os;
}

TInt &TInt::operator=(long long value)
{
    bool isPositive;
    if (value < 0)
    {
        isPositive = false;
    }
    else
    {
        isPositive = true;
    }
    value = abs(value);
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

    int r = TRYTE_SIZE - remainders.size();
    int i = 0;

    while(remainders.size())
    {
        data.setTrit(Trit(remainders.top()), i + r);
        remainders.pop();
        i++;
    }

    if(isPositive)
    {
        data.setTrit(Trit(0),0);
    }
    else
    {
        data.setTrit(Trit(1),0);
    }

}

TInt &TInt::operator=(QString value)
{
    bool isPositive;
    if (value[0] == '-')
    {
        isPositive = false;
    }
    else
    {
        isPositive = true;
    }
    value.remove('-');
    stack <unsigned int> result; // вид числа в троичной системе
    QVector<unsigned int> vecValue;
    for(int i = 0; i < value.size(); i++)
    {
        vecValue.push_back(value.at(i).digitValue());
    }

    while(vecValue.size() != 1 || vecValue.at(0) >= SYS_BASE)
    {
        QVector <unsigned int> nextVector;
        int rem = 0; // остаток
        for(int i = 0; i < vecValue.size(); i++)
        {
            if(vecValue.at(i) >= SYS_BASE)
            {
                rem = vecValue[i] % SYS_BASE; // остаток
                int n = vecValue[i] / SYS_BASE;
                nextVector.push_back(n);
                if(i != vecValue.size() - 1)
                {
                    vecValue[i+1] += rem * 10;
                }
            }
            else if (vecValue.at(i) < SYS_BASE)
            {
                rem = vecValue.at(i);
                nextVector.push_back(0);
                if(i != vecValue.size() - 1)
                {
                    vecValue[i+1] += vecValue[i] * 10;
                }
            }
        }

        result.push(rem);
        while(nextVector.at(0) == 0)
        {
            nextVector.removeFirst();
        }
        vecValue.clear();
        for(int i = 0; i < nextVector.size(); i++)
        {
            vecValue.push_back(nextVector.at(i));
        }
    }

    result.push(vecValue.at(0));
    int i = 0;
    int shift = TRYTE_SIZE - result.size();
    while(result.size())
    {
        data.setTrit(Trit(result.top()), i + shift);
        qDebug() << "result.top()" << result.top();
        result.pop();
        i++;
    }
    if(isPositive)
    {
        data.setTrit(Trit(0),0);
    }
    else
    {
        data.setTrit(Trit(1),0);
    }
}

const TInt& larger(const TInt &left,const TInt &right, TInt &first, TInt &second)
{
    for(int i = 1; i < TRYTE_SIZE; i++)
    {
        if(left.data.trit(i) > right.data.trit(i))
        {
            first = left;
            second = right;
            return TInt(0);
        }
        else if(left.data.trit(i) < right.data.trit(i))
        {
            first = right;
            second = left;
            return TInt(1);
        }
    }
    first = left;
    second = right;
}

bool operator==(const TInt &left, const TInt &right)
{
    for( int i = 0; i < TRYTE_SIZE; i++)
    {
        if(left.data.trit(i) != right.data.trit(i))
        {
            return false;
        }
    }
    return true;
}


bool operator>(const TInt &left, const TInt &right)
{
    if(left.data.trit(0) > right.data.trit(0))
    {
        return false;
    }

    else if(left.data.trit(0) < right.data.trit(0))
    {
        return true;
    }

    if(left.data.trit(0) == 0 && right.data.trit(0) == 0)
    {
        for(int i = 1; i < TRYTE_SIZE; i++)
        {
            if(left.data.trit(i) > right.data.trit(i))
            {
                return true;
            }
            else if(left.data.trit(i) < right.data.trit(i))
            {
                return false;
            }
        }
    }

    if(left.data.trit(0) == 1 && right.data.trit(0) == 1)
    {
        for(int i = 1; i < TRYTE_SIZE; i++)
        {
            if(left.data.trit(i) > right.data.trit(i))
            {
                return false;
            }
            else if(left.data.trit(i) < right.data.trit(i))
            {
                return true;
            }
        }
    }
    return false;
}

bool operator<(const TInt &left, const TInt &right)
{
    if(left.data.trit(0) > right.data.trit(0))
    {
        return true;
    }

    else if(left.data.trit(0) < right.data.trit(0))
    {
        return false;
    }

    if(left.data.trit(0) == 0 && right.data.trit(0) == 0)
    {
        for(int i = 1; i < TRYTE_SIZE; i++)
        {
            if(left.data.trit(i) > right.data.trit(i))
            {
                return false;
            }
            else if(left.data.trit(i) < right.data.trit(i))
            {
                return true;
            }
        }
    }

    if(left.data.trit(0) == 1 && right.data.trit(0) == 1)
    {
        for(int i = 1; i < TRYTE_SIZE; i++)
        {
            if(left.data.trit(i) > right.data.trit(i))
            {
                return true;
            }
            else if(left.data.trit(i) < right.data.trit(i))
            {
                return false;
            }
        }
    }
    return false;
}


bool operator>=(const TInt &left, const TInt &right)
{
    return ((left > right) || (left == right));
}

bool operator<=(const TInt &left, const TInt &right)
{
    return ((left < right) || (left == right));
}



TInt& operator+= (TInt &left, const TInt &right)
{
    left = left + right;
    return left;
}

TInt& operator-= (TInt &left, const TInt &right)
{
    left = left - right;
    return left;
}

TInt& operator/= (TInt &left, const TInt &right)
{
    left = left / right;
    return left;
}

TInt& operator*= (TInt &left, const TInt &right)
{
    left = left * right;
    return left;
}

const TInt operator+ (const TInt &left, const TInt &right)
{
    qDebug() << "was in +";
    TInt result;
    if(left.isNegative() && right.isNegative())
    {
        int arr[TRYTE_SIZE] = {};
        for(int i = TRYTE_SIZE - 1; i >= 1; i--)
        {
            arr[i] += (left.data.trit(i) + right.data.trit(i));
            int temp = arr[i];
            arr[i] = arr[i] % SYS_BASE; // остаток
            int dec = temp / SYS_BASE;
            if(i > 1)
            {
                arr[i - 1] += dec;
            }
        }

        for(int i = 0; i < TRYTE_SIZE; i++)
        {
            result.data.setTrit(Trit(arr[i]),i);
        }
        result = -result;
        return result;

    }

    if(!left.isNegative() && !right.isNegative())
    {
        int arr[TRYTE_SIZE] = {};
        for(int i = TRYTE_SIZE - 1; i >= 1; i--)
        {
            arr[i] += (left.data.trit(i) + right.data.trit(i));
            int temp = arr[i];
            arr[i] = arr[i] % SYS_BASE; // остаток
            int dec = temp / SYS_BASE;
            if(i > 1)
            {
                arr[i - 1] += dec;
            }
        }

        for(int i = 0; i < TRYTE_SIZE; i++)
        {
            result.data.setTrit(Trit(arr[i]),i);
        }
        return result;
    }

    if(left.isNegative() || right.isNegative())
    {
        TInt first;
        TInt second;
        larger(left, right, first, second);
        if(first.isNegative())
        {
            first = -first;
            result = first - second;
            result = -result;
        }
        else if(second.isNegative())
        {
            second = -second;
            result = first - second;
        }
        return result;
    }

}

const TInt operator- (const TInt &left, const TInt &right)
{
    qDebug() << "was in -";
    TInt result;
    TInt first = left;
    TInt second = right;

    if(left.isNegative() && !right.isNegative())
    {
        second = -second;
        result = first + second;
        return result;
    }

    if(!left.isNegative() && right.isNegative())
    {
        second = -second;
        result = first + second;
        return result;
    }

    if(!left.isNegative() && !right.isNegative())
    {
        larger(left, right, first, second);
        qDebug() << "first";
        first.print();
        qDebug() << "second";
        second.print();
        for(int i = TRYTE_SIZE - 1; i >= 1; i--) //1
        {
            if(first.data.trit(i) >= second.data.trit(i))
            {
                result.data.setTrit(first.data.trit(i) - second.data.trit(i), i);
            }
            else
            {
                int index = i - 1;
                bool isFindDec = false;
                while(!isFindDec)
                {

                    if (first.data.trit(index) == 0)
                    {
                        first.data.setTrit(Trit(first.data.trit(index) - 1), index);
                        index--;
                    }
                    else
                    {
                        first.data.setTrit(Trit(first.data.trit(index) - 1), index);
                        int k = first.data.trit(i) - second.data.trit(i) + 3;
                        result.data.setTrit(k, i);
                        isFindDec = true;
                    }
                }
            }

        }
        if(left < right)
        {
            result = -result;
            return result;
        }

        return result;
    }

    if(left.isNegative() && right.isNegative()) // -11 - (-11) = -11 + 11 = 0
    {
        if(first == second)
        {
            return TInt(0);
        }
        else
        {
            second = -second;
            result = first + second;
            return result;
        }
    }


    /*for(int i = 0; i < 27; i++)
        {
            leftArray[i].setTrit(left.data.trit(i));
        }
        for(int i = TRYTE_SIZE - 1; i >=0; i--)
        {
            if(leftArray[i].trit() >= right.data.trit(i))
            {
                result.data.setTrit(leftArray[i].trit() - right.data.trit(i), i);
            }
            else
            {
                int index = i - 1;
                bool isFindDec = false;
                while(!isFindDec)
                {

                    if (leftArray[index].trit() == 0)
                    {
                        leftArray[index].decrement();
                        index--;
                    }
                    else
                    {
                        leftArray[index].decrement();
                        int k = leftArray[i].trit() - right.data.trit(i) + 3;
                        result.data.setTrit(k, i);
                        isFindDec = true;
                    }
                }
            }

        }

      return result;*/

}

const TInt operator/ (const TInt &left, const TInt &right)
{
    qDebug() << "l" << left.numberRank();
    qDebug() << "r" << right.numberRank();

    if (left < right)
    {
        //return TInt(0);
    }

    if(right == TInt(0))
    {
        cout << "делить на ноль нельзя!";
        return TInt(0);
    }

    QVector<Trit> vecResult;
    TInt result(0);
    TInt temp(0);
    for(int i = 0; i < left.numberRank() - right.numberRank() + 1; i++)
    {
        cout << endl << "i " << i << endl;
        TInt div = temp;
        if(!i)
        {
            size_t shift = TRYTE_SIZE - left.numberRank();
            size_t r = left.numberRank() - right.numberRank();
            for(int j = 0; j < right.numberRank(); j++)
            {
                div.data.setTrit(left.data.trit(shift + j), shift + r + j);
            }
        }
        else
        {
            size_t shift = TRYTE_SIZE - div.numberRank();
            QVector <Trit> newDiv;
            for(int j = 0; j < div.numberRank(); j++)
            {
                newDiv.push_back(Trit(div.data.trit(shift + j)));
            }
            shift = TRYTE_SIZE - left.numberRank();
            newDiv.push_back(Trit(left.data.trit(shift + right.numberRank() + i - 1)));
            shift = TRYTE_SIZE - newDiv.size();
            for(int j = 0; j < shift; j++)
            {
                newDiv.push_front(Trit());
            }
            for(int j = 0; j < TRYTE_SIZE; j++)
            {
                div.data.setTrit(newDiv[j], j);
            }
        }
        size_t counter = 0;

        while(div >= right) // >= =
        {
            qDebug() << "div";
            div.print();
            div = div - right;
            qDebug() << "div";
            div.print();
            counter++;
        }
        temp = div;
        vecResult.push_back(Trit(counter));
    }
    qDebug() << "was here";

    size_t shift = TRYTE_SIZE - vecResult.size() - 1;
    for(int i = 0; i < vecResult.size(); i++)
    {
        result.data.setTrit(vecResult[i], shift + i + 1);
    }
    if((left.isNegative() && !right.isNegative()) || (!left.isNegative() && right.isNegative()))
    {
        result = -result;
    }
    qDebug() << "res" << result.numberRank();
    return result;
    //return TInt(0);
}

const TInt operator* (const TInt &left, const TInt &right)
{
    if(left == TInt(0) || right == TInt(0))
    {
        return TInt(0);
    }
    TInt first = left;
    if(first.isNegative())
    {
        first = -first;
    }
    TInt second = right;
    if(second.isNegative())
    {
        second = -second;
    }
    // qDebug() << "left";
    //left.print();
    //qDebug() << "right";
    // right.print();
    QVector <TInt> terms;
    stack <int> multipliers;
    TInt result;
    int shift = TRYTE_SIZE - second.numberRank();
    qDebug() << "shift" << shift;
    for(size_t i = 0; i < second.numberRank(); i++)
    {
        multipliers.push((int)second.data.trit(shift + i));
        cout << endl;
        cout <<"s "<< multipliers.top();
    }

    while(!multipliers.empty())
    {
        cout << "stack size " << multipliers.size();
        TInt term(0);
        for(int j = 0; j < multipliers.top(); j++)
        {
            term += first;
        }
        terms.push_back(term);
        multipliers.pop();
    }
    cout << endl << "terms size " << terms.size() << endl;

    for(int i = 0; i < terms.size(); i++)
    {
        terms[i].print();
    }

    for(int i = 0; i < terms.size(); i++)
    {
        TInt t(0);
        if(!i)
        {
            result += terms.at(i);
        }
        else
        {
            int sub = 1;
            for(int j = 0; j < i; j++)
            {
                sub *= 3;
            }
            // cout << endl;
            // cout << "sub " << sub << endl;
            for(int j = 0; j < sub; j++)
            {
                t += terms.at(i);
            }
            // cout << endl << i;
            // t.print();
        }
        result += t;

    }
    //result.print();
    if(((right.isNegative() && !left.isNegative()) || (!right.isNegative() && left.isNegative())) )
    {
        result = -result;
    }

    return result;
}

const TInt& operator++(TInt &i)
{
    i += TInt(1);
    return i;
}

const TInt operator++(TInt &i, int)
{
    TInt oldValue = i;
    i += TInt(1);
    return oldValue;
}

const TInt& operator--(TInt &i)
{
    i -= TInt(1);
    return i;
}

const TInt operator--(TInt &i, int)
{
    TInt oldValue = i;
    i -= TInt(1);
    return oldValue;
}

const TInt& operator+(const TInt &i) //унарный плюс ничего не делает
{
    return i;
}

const TInt operator-(const TInt &i)
{
    TInt result = i;
    if(result.isNegative())
    {
        result.data.setTrit(Trit(0) , 0);
    }
    else
    {
        result.data.setTrit(Trit(1) , 0);
    }
    return result;
}
