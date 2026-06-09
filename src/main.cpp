#include <QApplication>

#include "main_window.h"
#include "net.h"
#include "utils.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Net net;

    MainWindow main_window(nullptr, net);

    return app.exec();
}