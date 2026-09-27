#include <QApplication>

#include "main_window.h"
#include "net.h"
#include "utils.h"

#define IP      "172.20.10.2"
#define PORT    12345

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Net net(IP, PORT);

    MainWindow main_window(nullptr, net);

    return app.exec();
}