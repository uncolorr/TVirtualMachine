#include "translator.h"

void Translator::initRegs()
{
    regs_["ax"] = "000000000000000000000000001";
    regs_["bx"] = "000000000000000000000000002";
    regs_["cx"] = "000000000000000000000000010";
    regs_["dx"] = "000000000000000000000000011";
}

bool Translator::isReg(QString reg)
{
    if (regs_.contains(reg))
    {
        return true;
    }
    return false;

}

bool Translator::isNum(QString num)
{
    if(num.contains(numRegExp_))
    {
        return true;
    }
    return false;
}

QString Translator::to3ss(QString value)
{
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
    QString r;
    for(int i = 0; i < shift; i++)
    {
        r.append(QString::number(0));

    }

    while(result.size())
    {
        r.append(QString::number(result.top()));
        qDebug() << "result.top()" << result.top();
        result.pop();
        i++;
    }
    qDebug() << "r" << r;
    return r;
}

Translator::Translator()
{
    initRegs();
    numRegExp_.setPattern("([0-9]+)");
}

Translator::~Translator()
{

}

QMap<QString, QString> Translator::syntax()
{
    return syntax_;
}

QMap<QString, QString> Translator::regs()
{
    return regs_;
}

QVector<QString> Translator::parameters()
{
    return parameters_;
}

QVector<QString> Translator::comands()
{
    return comands_;
}

void Translator::loadSyntax(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString text = file.readAll();
        QStringList lines = text.split("\n");
        for(int i = 0; i < lines.size(); i++)
        {
            QStringList pair = lines[i].split(" ");
            if(pair.size() == 2)
            {
                syntax_[pair[0]] = pair[1];
                qDebug() << pair[0] << "|" << pair[1] << endl;
            }
        }
    }
}

void Translator::loadCode(QString fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString text = file.readAll();
        qDebug() << text;
        QStringList lines = text.split("\n");
        for(int i = 0; i < lines.size(); i++)
        {
            if(lines.at(i).isEmpty() || lines.at(i) == ":")
            {
                lines.removeAt(i);
            }
        }
        for(int i = 0; i < lines.size(); i++)
        {
            QStringList expParts = lines[i].split(" ");
            QString byteCode;
            for(int j = 0; j < expParts.size(); j++)
            {
                if(!j)
                {
                    byteCode.append(expParts[j] + ":");
                }
                else if(j != expParts.size() - 1)
                {
                    if(isNum(expParts[j]))
                    {
                        byteCode.append("num:");
                        parameters_.push_back(to3ss(expParts[j]));
                    }

                    if(isReg(expParts[j]))
                    {
                        byteCode.append("reg:");
                        parameters_.push_back(regs_[ expParts[j] ]);
                    }
                }
                else
                {
                    if(isNum(expParts[j]))
                    {
                        byteCode.append("num");
                        parameters_.push_back(to3ss(expParts[j]));

                    }

                    if(isReg(expParts[j]))
                    {
                        byteCode.append("reg");
                        parameters_.push_back(regs_[ expParts[j] ]);
                    }
                }
            }

            qDebug() << byteCode;
            if(syntax_.contains(byteCode))
            {
                comands_.push_back(syntax_[byteCode]);
                qDebug() << syntax_[byteCode];
            }

        }
        for(int i = 0; i < parameters_.size(); i++)
        {
            qDebug() <<"p "<< parameters_.at(i);
        }
    }
}

void Translator::loadMemory(QVector<Tryte>& memory)
{
    for(int i = 0; i < comands_.size(); i++)
    {
        memory[i].setData(comands_.at(i));
    }

    for(int i = 0; i < parameters_.size(); i++)
    {
        memory[i + PARAM_MEM_BEGIN].setData(parameters_.at(i));
    }
}
