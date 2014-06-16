#include "startdialog.h"
#include "drawpos.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartDialog w;
    w.show();

    return a.exec();
}
