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
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
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

void Processor::initFloatRegs()
{
    floatRegs["000000000000000000000000012"] = &eax;
    floatRegs["000000000000000000000000020"] = &ebx;
    floatRegs["000000000000000000000000021"] = &ecx;
    floatRegs["000000000000000000000000022"] = &edx;
}

void Processor::start(QVector<Tryte>& memory,QVector<Tryte>& ROM, int cmdLength)
{
    bool isF = false;
    while(true)
    {
        //qDebug() << "iter";
        if(memory[pc] == syntax_["mov:num:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]) = TInt(memory[PARAM_MEM_BEGIN + sp]);
            pc++;
            sp += 2;
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
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) += TInt(1);
            pc++;
            sp++;
        }

        else if(memory[pc] == syntax_["dec:reg"])
        {
            *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) -= TInt(1);
            pc++;
            sp++;
        }

        else if(memory[pc] == syntax_["not:reg"])//
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

        else if(memory[pc] == syntax_["mov:sym:adr"])
        {
            ROM[memory[PARAM_MEM_BEGIN + sp + 1].toNum()] = memory[PARAM_MEM_BEGIN + sp];
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["mov:num:adr"])
        {
            ROM[memory[PARAM_MEM_BEGIN + sp + 1].toNum()] = memory[PARAM_MEM_BEGIN + sp];
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["mov:adr:reg"])//
        {

        }

        else if(memory[pc] == syntax_["mov:reg:adr"])
        {
            ROM[memory[PARAM_MEM_BEGIN + sp + 1].toNum()] = (regs[memory[PARAM_MEM_BEGIN + sp].getData()])->toString();
            pc++;
            sp += 2;

        }//------------------------------------------

        else if(memory[pc] == syntax_["sub:frg:frg"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) -= *(floatRegs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]);
            pc++;
            sp += 2;

        }

        else if(memory[pc] == syntax_["sub:frg:fnm"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) -= TFloat(TInt(memory[PARAM_MEM_BEGIN + sp + 1]),TInt(memory[PARAM_MEM_BEGIN + sp + 2]));
            pc++;
            sp += 3;
        }

        else if(memory[pc] == syntax_["mul:frg:fnm"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) *= TFloat(TInt(memory[PARAM_MEM_BEGIN + sp + 1]),TInt(memory[PARAM_MEM_BEGIN + sp + 2]));
            pc++;
            sp += 3;
        }

        else if(memory[pc] == syntax_["mul:frg:frg"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) *= *(floatRegs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["div:frg:fnm"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) /= TFloat(TInt(memory[PARAM_MEM_BEGIN + sp + 1]),TInt(memory[PARAM_MEM_BEGIN + sp + 2]));
            pc++;
            sp += 3;
        }

        else if(memory[pc] == syntax_["div:frg:frg"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) /= *(floatRegs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["add:frg:fnm"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) += TFloat(TInt(memory[PARAM_MEM_BEGIN + sp + 1]),TInt(memory[PARAM_MEM_BEGIN + sp + 2]));
            pc++;
            sp += 3;
        }

        else if(memory[pc] == syntax_["add:frg:frg"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) += *(floatRegs[memory[PARAM_MEM_BEGIN + sp + 1].getData()]);
            pc++;
            sp += 2;
        }

        else if(memory[pc] == syntax_["inc:frg"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) += TFloat(1.0);
            pc++;
            sp++;
        }

        else if(memory[pc] == syntax_["dec:frg"])
        {
            *(floatRegs[memory[PARAM_MEM_BEGIN + sp].getData()]) -= TFloat(1.0);
            pc++;
            sp++;
        }

        else if(memory[pc] == syntax_["out:reg"])
        {
            cout << *(regs[memory[PARAM_MEM_BEGIN + sp].getData()]) << endl;
            pc++;
            sp++;
        }

        else if(memory[pc] == syntax_["out:frg"])
        {

        }

        else if(memory[pc] == syntax_["out:num"])
        {

        }

        else if(memory[pc] == syntax_["out:fnm"])
        {

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
