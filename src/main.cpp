#include <QApplication>

#include "main_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow main_window(nullptr);

    return app.exec();
}