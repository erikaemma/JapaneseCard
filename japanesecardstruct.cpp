#include "japanesecardstruct.h"

JapaneseCardStruct::JapaneseCardStruct(QString filename)
{
    qfile = new QFile(filename);
}

bool JapaneseCardStruct::readAll()
{
    if(!(qfile->open(QIODevice::ReadWrite | QIODevice::Truncate)))
        return false;
}
