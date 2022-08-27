#include "mainwindow.h"


//#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
int main(int argc, char *argv[]) {
    QApplication::addLibraryPath("./plugins");
    QApplication a(argc, argv);
    auto *w = new MainWindow();
    w->show();
    return a.exec();

}
