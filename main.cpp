#include "Wrench.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wrench w;
    w.show();

    return a.exec();
}
