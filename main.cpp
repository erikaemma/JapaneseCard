#include "ui/include/japanesecard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JapaneseCard w;
    w.show();
    return a.exec();
}
