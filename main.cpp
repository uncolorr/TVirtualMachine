#include <QCoreApplication>
#include "tint.h"
#include "tfloat.h"
#include "tchar.h"
#include "translator.h"
#include "processor.h"
#include <iostream>
#include <wchar.h>
#include <codecvt>

using namespace std;

int main()
{
    QVector<Tryte> memory(512);
    QVector<Tryte> ROM(512);

    Translator translator;
    translator.loadSyntax(":/resources/files/syntax.txt");
    translator.loadCode(":/resources/files/code.txt");
    translator.loadMemory(memory);
    Processor processor(translator.syntax());
    processor.start(memory,ROM, translator.countCommands() - 2);


    return 0;
}
