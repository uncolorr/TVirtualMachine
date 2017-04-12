#include "processor.h"
/*mov:num:reg 000000000000000000000000001
mov:reg:reg 000000000000000000000000002
sub:reg:reg 000000000000000000000000010
sub:num:reg 000000000000000000000000011
mul:num:reg 000000000000000000000000012
mul:reg:reg 000000000000000000000000020
div:reg:num 000000000000000000000000021
div:reg:reg 000000000000000000000000022
inc:reg 000000000000000000000000100
dec:reg 000000000000000000000000101
not:reg 000000000000000000000000102*/
Processor::Processor(const QMap<QString, QString>& syntax)
{
    ax = 0;
    bx = 0;
    cx = 0;
    dx = 0;
    pc = 0; // указатель на номер команды
    sp = 0; // указатель на номер параметра
    syntax_ = syntax;
    initRegs();
}

Processor::~Processor()
{

}

void Processor::initRegs()
{
    regs["000000000000000000000000001"] = &ax;
    regs["000000000000000000000000002"] = &bx;
    regs["000000000000000000000000010"] = &cx;
    regs["000000000000000000000000011"] = &dx;
}

void Processor::start(QVector<Tryte>& memory, int cmdLength)
{
    bool isF = false;
    while(true)
    {
        qDebug() << "iter";
        if(memory[pc] == syntax_["mov:num:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]) = TInt(memory[PARAM_MEM_BEGIN + sp]);
            pc++;
            sp += 2;
            qDebug() << "dddddd";
            ax.print();

        }
        else if(memory[pc] == syntax_["mov:reg:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]) = *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["sub:reg:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) -= *(regs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]);
            pc++;
            sp += 2;
        }
        else if(memory[pc] == syntax_["sub:reg:num"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) -= TInt(memory[PARAM_MEM_BEGIN + sp + 1]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["mul:reg:num"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) *= TInt(memory[PARAM_MEM_BEGIN + sp + 1]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["mul:reg:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) *= *(regs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["div:reg:num"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) /= TInt(memory[PARAM_MEM_BEGIN + sp + 1]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["div:reg:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) /= *(regs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["inc:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()])++;
            pc++;
            sp++;
        }

        else if(memory[pc] == syntax_["dec:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()])--;
            pc++;
            sp++;
        }

        else if(memory[pc] == syntax_["not:reg"])
        {

        }

        else if(memory[pc] == syntax_["add:reg:num"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) += TInt(memory[PARAM_MEM_BEGIN + sp + 1]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["add:reg:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) += *(regs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]);
            pc++;
            sp += 2;
        }



        if(pc > cmdLength && !isF)
        {
            char answer;
            while (answer != 'y' || answer != 'n')
            {
                cout << "Виртуальная машина завершила свою работу. Хотите ее выключить? y/n" << endl;
                cin >> answer;
                switch (answer)
                {
                case 'y':
                    cout << "Виртуальная машина завершила работу." << endl;
                    ax.print();
                    return;                 
                    break;
                case 'n':
                    isF = true;
                    break;
                default:
                    cout << "Некорректный ответ!" << endl;
                    break;
                }
            }
        }
    }
}
