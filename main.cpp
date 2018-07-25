#include <QtGui>
#include"game.h"
#include"mywidget.h"
#include "widget.h"
#include<QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game *x=new game();
    x->show();
    return a.exec();
}
