#include "mywidget.h"
#include <qpainter.h>
#include <qfont.h>
#include "mywidget.h"
#include <qpainter.h>
#include <qfont.h>
#include <qdebug.h>
#include<QWidget>
#include"game.h"


MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QString::fromUtf8("炫彩小砖块"));
  resize(600,600);
   level = 1;
    initGame();
    QPixmap pixmap(":/image/12.jpg");
        QPalette palette;
        palette.setBrush(backgroundRole(), QBrush(pixmap));
        setPalette(palette);
        beginflag=0;
        col=1;
}


//定义右键菜单事件
void MyWidget::contextMenuEvent(QContextMenuEvent  *event)
{
    QMenu  *menu=new QMenu;
    menu->addAction(QString::fromUtf8("新游戏"),this,SLOT(reGame()));
    menu->addSeparator();
    menu->addAction(QString::fromUtf8("返回菜单"),this,SLOT(fanhui()));
    menu->exec(event->globalPos());
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    point = e->pos();
}

void MyWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->pos().x() < point.x())
          mydynamicBrick->setShape(mydynamicBrick->getShape().x()-100,mydynamicBrick->getShape().y(),mydynamicBrick->getShape().width(),mydynamicBrick->getShape().height(),this->width());
   else if(e->pos().x() > point.x() )
         mydynamicBrick->setShape(mydynamicBrick->getShape().x()+100,mydynamicBrick->getShape().y(),mydynamicBrick->getShape().width(),mydynamicBrick->getShape().height(),this->width());
}

//响应左右移动按键，每次移动60个像素
void MyWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Left) {

        mydynamicBrick->setShape(mydynamicBrick->getShape().x()-60,mydynamicBrick->getShape().y(),mydynamicBrick->getShape().width(),mydynamicBrick->getShape().height(),this->width());
    }

    else if(e->key() == Qt::Key_Right )
    {
        mydynamicBrick->setShape(mydynamicBrick->getShape().x()+60,mydynamicBrick->getShape().y(),mydynamicBrick->getShape().width(),mydynamicBrick->getShape().height(),this->width());

    }
    else if(e->key()==Qt::Key_Space)
    {
        if(beginflag==0)
        {
            beginflag=1;
      //      ui->pushButton->setEnabled(0);
       //     ui->pushButton_2->setEnabled(0);
            //qDebug()<<"begain_flag:"<<begain_flag;
        }

        else
        {
            beginflag=0;
        }
        //qDebug()<<"begain_flag:"<<begain_flag;
    }

    update();
}


//重定义绘制事件
void MyWidget::paintEvent(QPaintEvent *e)
{


    QPainter paint(this);

    //绘制挡板滑块

    paint.setBrush(QColor(100,200,80));
    paint.drawRect(*(mydynamicBrick->shape));

    //绘制滚球

    paint.setBrush(myBall->color);
    paint.drawRoundRect(*(myBall->shape),90,90);

    //绘制砖块
    paint.setPen(Qt::black);//绘制边缘线，使砖块好看一点
    if(col==1){
    paint.setBrush( QColor(255 ,250 ,205));
    col=2;
    }
    else if(col==2)
    {
        paint.setBrush( QColor(240,255,240));
        col=1;
    }

    foreach( Brick *brick, bricks )
    paint.drawRoundRect( *(brick->shape) );

    paint.setFont(QFont("华文行楷",20));
    paint.drawText(this->width()/2-100,this->height()/2-300,200,80,Qt::AlignCenter,QString::fromUtf8("第%1关").arg(level));
    paint.drawText(this->width()/2-220,this->height()/2-250,500,200,Qt::AlignLeft,QString::fromUtf8("Press Spacebar to start or pause..."));
    advanceCheck();
}

//碰撞检测，实现小球滚动
void MyWidget::advanceCheck()
{
    static int che = 0;

    if(myBall->getShape().x() < 0)
        myBall->setDirX(-1.5);
    if(myBall->getShape().x() > width()-50)
        myBall->setDirX(1.5);
    if(myBall->getShape().y() < 0)
        myBall->setDirY(1.5);

    //判断是否与挡板相碰
    if(myBall->getShape().y() > height()-75){
    if(mydynamicBrick->getShape().left() < myBall->getShape().right() && mydynamicBrick->getShape().right() > myBall->getShape().left() )
     {
        //这里使小球改变运动方向，为了不费事，就做的简单点了，也可以使用随机数

        if(che == 0)
        { myBall->setDirY(-1.5);
            che = 1;
        }
        else
        {
                myBall->setDirY(-3.0);
                che = 0;
        }

     }
    else
        gameEnd();
    }



    //判断与砖块相撞
     foreach( Brick *brick, bricks )
        if(brick->getShape().left() < myBall->getShape().right() && brick->getShape().right() > myBall->getShape().left())
        if(myBall->getShape().top() < brick->getShape().bottom() )
        {
                      bricks.removeOne(brick);
                      myBall->setDirY(-myBall->dirY);
        }
     //过关检测
     if(bricks.isEmpty())
     {
         level++;
         reGame();
     }

}

//初始化游戏
void MyWidget::initGame()
{
    myBall = new Ball(this->width()/2-10,this->height()-32,50,Qt::blue);
    mydynamicBrick = new dynamicBrick(this->width()/2-60,this->height()-22,240,20,Qt::blue);

    //创建砖块并入队列
    for(int j=0; j< 354 ; j += 43)
    for(int i=0; i < width();i +=150)
    {
        Brick *brick = new Brick(i,j,147,40);
        bricks.append(brick);
    }

    //创建定时器，确定滚球移动速度

   timer.start(7-2*level);
    connect(&timer,SIGNAL(timeout()),this,SLOT(ballMove()));

}

//重新游戏
void MyWidget::reGame()
{
    delete mydynamicBrick;
    delete myBall;
    bricks.clear();
    timer.stop();
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(ballMove()));
    initGame();


}



void MyWidget::gameEnd()
{

     // QMessageBox::warning(this,"losed","Sorry,You are losed!","New Game");
      reGame();

}

//定义球移动槽
void MyWidget::ballMove()
{
if(beginflag==1)
{
    myBall->move();
    update();
}
}

MyWidget::~MyWidget()
{
    delete mydynamicBrick;
    delete myBall;
}
void MyWidget::fanhui()
{
    game *main_guide = new game();
    main_guide->show();
    this->close();
}
