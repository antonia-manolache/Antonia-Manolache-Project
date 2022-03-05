#include"server.h"
#include<QtWidgets/QApplication>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Server s;
    s.doConnect();

    return a.exec();
}
