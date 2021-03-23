#include <QApplication>
#include <QtAVWidgets/QtAVWidgets>
#include <QtAVWidgets/WidgetRenderer.h>

#include <playerwidget.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    playerWidget player;
    player.show();
    return a.exec();
}
