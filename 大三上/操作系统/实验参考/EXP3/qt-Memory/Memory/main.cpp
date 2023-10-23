#include "showwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowWidget w;
    w.show();

    return a.exec();
}
