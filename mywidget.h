#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <qmenu.h>
#include <QAction>
#include <QContextMenuEvent>
#include <QPaintEvent>
#include <QMessageBox>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <ball.h>
#include <dynamicBrick.h>
#include <qlist.h>
#include <brick.h>
#include <qtimer.h>
#include <QMouseEvent>
#include <qpoint.h>
#include<QWidget>
#include<QPushButton>
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = 0);
    ~MyWidget();
    void contextMenuEvent(QContextMenuEvent  *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);
    void advanceCheck();
    dynamicBrick *mydynamicBrick;
    Ball *myBall;
    QList< Brick * > bricks;
    QTimer timer;
    int level;
    QPoint point;
    int col;
    int beginflag;
public slots:
    void initGame();
    void reGame();
    void gameEnd();
    void ballMove();
    void fanhui();
 //   void showMainwindow2();



};

#endif // WIDGET_H
