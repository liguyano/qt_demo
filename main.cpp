#include <QSharedMemory>
#include <QMessageBox>
#include "mainwindow.h"

//#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
int main(int argc, char *argv[]) {
    static QSharedMemory *shareMem = new QSharedMemory("SingleApp"); //创建“SingleApp”的共享内存块
    if (!shareMem->create(1))//创建大小1b的内存
    {
        qInfo() << "already running";
        qApp->quit(); //创建失败，说明已经有一个程序运行，退出当前程序
        return -1;
    }
    QApplication::addLibraryPath("./plugins");
    QApplication a(argc, argv);
    auto *w = new MainWindow();
    w->show();
    return a.exec();
}
