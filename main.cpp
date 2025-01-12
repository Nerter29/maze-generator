#include "mainwindow.h"
#include <QFontDatabase>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowFullScreen);

    w.setWindowIcon(QIcon(":/assets/icon.png"));

    int fontId = QFontDatabase::addApplicationFont(":/assets/Renogare.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontName);

    w.show();

    return a.exec();
}
