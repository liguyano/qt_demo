#include <QApplication>
#include <QPushButton>
#include <QDebug>

int ma2in(int argc, char *argv[]) {
    QApplication::addLibraryPath("./plugins");
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    QPixmap pixmap("../a.png");
    qInfo() << "hello world\n";
    button.setIcon(pixmap);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
