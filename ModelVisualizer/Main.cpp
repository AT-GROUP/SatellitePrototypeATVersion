#include "ModelVisualizer.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModelVisualizer w;
    w.showMaximized();
    return a.exec();
}
