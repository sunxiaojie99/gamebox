#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QRect>
#include <QDesktopWidget>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <qDebug>
#include <QMessageBox>
#include <QWidget>
#include <QPushButton>
#include <QString>
#include"game.h"
#include<QMediaPlayer>
#include<QSound>
#include<QSoundEffect>
#include"double2.h"


Widget::Widget(QWidget *parent) :QWidget(parent),ui(new Ui::Widget){
    ui->setupUi(this);
    begain_flag=0;//1为开始游戏，0为未开始游戏
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    head=new snake;
    head2=new snake;
    head->xx=350;//290
    head->yy=290;//290
    head2->xx=360;//300
    head2->yy=290;//290
    head->next=head2;//QT中几何坐标 以左上角为原点-水平为x轴，从左向右为正向-垂直为y轴，从上到下为正向
    head2->next=NULL;

    head0=new snake;
    head02=new snake;
    head0->xx=250;//290
    head0->yy=290;//290
    head02->xx=260;//300
    head02->yy=290;//290
    head0->next=head02;//QT中几何坐标 以左上角为原点-水平为x轴，从左向右为正向-垂直为y轴，从上到下为正向
    head02->next=NULL;

    speed=50;
    food_x=qrand()%10*10+55;
    food_y=qrand()%10*10+55;
    horizontal=-1;
    vertical=0;

    horizontal0=-1;
    vertical0=0;

    dead=0; button=0;
    length=2;colo=1;
    QPixmap pixmap(":/image/snakebackground.jpg");
        QPalette palette;
        palette.setBrush(backgroundRole(), QBrush(pixmap));
        setPalette(palette);
    timer=new QTimer(this);
    timer->start(speed);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_sig()));
    QFont font;
    font.setFamily("华文行楷");
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    setWindowTitle(QStringLiteral("Snake"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    if((head->xx+horizontal*10==food_x-5)&&(head->yy+vertical*10==food_y-5))
    {
        length++;
        food_x=qrand()%50*10+55;
        food_y=qrand()%50*10+55;
        snake *new_head;
        new_head=new snake;
        new_head->xx=head->xx+horizontal*10;
        new_head->yy=head->yy+vertical*10;
        new_head->next=head;
        head=new_head;
        qDebug()<<"food_x and food_y"<<food_x<<food_y;
    }
    else if((head0->xx+horizontal0*10==food_x-5)&&(head0->yy+vertical0*10==food_y-5))
    {
        length++;
        food_x=qrand()%50*10+55;
        food_y=qrand()%50*10+55;
        snake *new_head;
        new_head=new snake;
        new_head->xx=head0->xx+horizontal0*10;
        new_head->yy=head0->yy+vertical0*10;
        new_head->next=head0;
        head0=new_head;
        qDebug()<<"food_x and food_y"<<food_x<<food_y;
    }

    QPoint point(food_x,food_y);
    QRect rectangle(50,50,500,500);
    QPainter painter(this);
    painter.drawRect(rectangle);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);
    painter.drawEllipse(point,4,4);
    switch(button){
    case QMessageBox::No:
        this->close();
        break;
    case QMessageBox::Yes:
        ui->pushButton->setEnabled(1);//按钮可点击
        ui->pushButton_2->setEnabled(1);
        dead=0;
        button=0;
        length=2;
        this->initial_snake();
        timer=new QTimer(this);
        timer->start(speed);
        connect(timer,SIGNAL(timeout()),this,SLOT(time_sig()));
        break;
    }
    if(begain_flag==0)
    {
        snake *p,*p0;
        p=head;
        p0=head0;
        while(p!=NULL)
        {
            QRect snake_body(p->xx,p->yy,10,10);
            QPainter paint_snake(this);
            if(colo==1){
            paint_snake.setBrush( QColor(255 ,255 ,0));
            colo=2;
            }
            else if(colo==2)
            {
                paint_snake.setBrush( QColor(0,191,255));
                colo=3;
            }
            else if(colo==3)
            {
                paint_snake.setBrush( QColor(255,105,180));
                colo=4;
            }
            else if(colo==4)
            {
                paint_snake.setBrush( QColor(255,0,255));
                colo=5;
            }
            else if(colo==5)
            {
                paint_snake.setBrush( QColor(250,128,114));
                colo=6;
            }
            else if(colo==6)
            {
                paint_snake.setBrush( QColor(173,255,47));
                colo=7;
            }
            else if(colo==7)
            {
                paint_snake.setBrush( QColor(255,160,114));
                colo=1;
            }
            //paint_snake.setBrush(Qt::white);//改2 原来green
            paint_snake.drawRect(snake_body);
            p=p->next;
        }


        while(p0!=NULL)
        {
            QRect snake_body0(p0->xx,p0->yy,10,10);
            QPainter paint_snake0(this);
            if(colo==1){
            paint_snake0.setBrush( QColor(255 ,255 ,0));
            colo=2;
            }
            else if(colo==2)
            {
                paint_snake0.setBrush( QColor(0,191,255));
                colo=3;
            }
            else if(colo==3)
            {
                paint_snake0.setBrush( QColor(255,105,180));
                colo=4;
            }
            else if(colo==4)
            {
                paint_snake0.setBrush( QColor(255,0,255));
                colo=5;
            }
            else if(colo==5)
            {
                paint_snake0.setBrush( QColor(250,128,114));
                colo=6;
            }
            else if(colo==6)
            {
                paint_snake0.setBrush( QColor(173,255,47));
                colo=7;
            }
            else if(colo==7)
            {
                paint_snake0.setBrush( QColor(255,160,114));
                colo=1;
            }
            //paint_snake.setBrush(Qt::white);//改2 原来green
            paint_snake0.drawRect(snake_body0);
            p0=p0->next;
        }
    }
    else
    {
        snake *p1,*p2,*temp;
        snake *p01,*p02,*temp0;

      if((head->xx>=50)&&(head->xx<550)&&
         (head->yy<550)&&(head->yy>=50)&&(head!=NULL)&&(!hit_self()))
      {
            temp=new snake;
            temp->xx=head->xx+horizontal*10;
            temp->yy=head->yy+vertical*10;
            temp->next=head;
            head=temp;
            p1=head;
            p2=head;
            while(p1->next!=NULL)
            {
              qDebug()<<"vertical and hor:"<<vertical<<"  "<<horizontal;

              QRect snake_body(p1->xx,p1->yy,10,10);
              QPainter paint_snake(this);
              if(colo==1){
              paint_snake.setBrush( QColor(255 ,255 ,0));
              colo=2;
              }
              else if(colo==2)
              {
                  paint_snake.setBrush( QColor(0,191,255));
                  colo=3;
              }
              else if(colo==3)
              {
                  paint_snake.setBrush( QColor(255,105,180));
                  colo=4;
              }
              else if(colo==4)
              {
                  paint_snake.setBrush( QColor(255,0,255));
                  colo=5;
              }
              else if(colo==5)
              {
                  paint_snake.setBrush( QColor(250,128,114));
                  colo=6;
              }
              else if(colo==6)
              {
                  paint_snake.setBrush( QColor(173,255,47));
                  colo=7;
              }
              else if(colo==7)
              {
                  paint_snake.setBrush( QColor(255,160,114));
                  colo=1;
              }
              paint_snake.drawRect(snake_body);
              p2=p1;
              p1=p1->next;
            }
            p2->next=NULL;
            delete(p1);
       }
       else
       {
            dead=1;
       }


      //new
      if((head0->xx>=50)&&(head0->xx<550)&&
         (head0->yy<550)&&(head0->yy>=50)&&(head0!=NULL)&&(!hit_self0()))
      {
            temp0=new snake;
            temp0->xx=head0->xx+horizontal0*10;
            temp0->yy=head0->yy+vertical0*10;
            temp0->next=head0;
            head0=temp0;
            p01=head0;
            p02=head0;
            while(p01->next!=NULL)
            {
              qDebug()<<"vertical and hor:"<<vertical0<<"  "<<horizontal0;

              QRect snake_body0(p01->xx,p01->yy,10,10);
              QPainter paint_snake0(this);
              if(colo==1){
              paint_snake0.setBrush( QColor(255 ,255 ,0));
              colo=2;
              }
              else if(colo==2)
              {
                  paint_snake0.setBrush( QColor(0,191,255));
                  colo=3;
              }
              else if(colo==3)
              {
                  paint_snake0.setBrush( QColor(255,105,180));
                  colo=4;
              }
              else if(colo==4)
              {
                  paint_snake0.setBrush( QColor(255,0,255));
                  colo=5;
              }
              else if(colo==5)
              {
                  paint_snake0.setBrush( QColor(250,128,114));
                  colo=6;
              }
              else if(colo==6)
              {
                  paint_snake0.setBrush( QColor(173,255,47));
                  colo=7;
              }
              else if(colo==7)
              {
                  paint_snake0.setBrush( QColor(255,160,114));
                  colo=1;
              }
              paint_snake0.drawRect(snake_body0);
              p02=p01;
              p01=p01->next;
            }
            p02->next=NULL;
            delete(p01);
       }
       else
       {
            dead=1;
       }
    }

    }


void Widget::time_sig()
{
    if(dead==1)
    {
        this->timer->stop();
        button=QMessageBox::information(this,"warning","You Lose!!",0,0);
        button=QMessageBox::information(this,"tip","Try again ?",QMessageBox::No | QMessageBox::Yes);
        this->begain_flag=0;
    }
    this->update();
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {//Returns the event type.
    case QEvent::LanguageChange://The application translation changed.
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Space:
        if(begain_flag==0)
        {
            begain_flag=1;
      //      ui->pushButton->setEnabled(0);
       //     ui->pushButton_2->setEnabled(0);
            qDebug()<<"begain_flag:"<<begain_flag;
       }
        else
        {
            begain_flag=0;
        }
        qDebug()<<"begain_flag:"<<begain_flag;
        break;
    case Qt::Key_Left:
        if(horizontal!=1)//改4 1
        {
         //   update();
            horizontal=-1;
            vertical=0;
        }
        break;
    case Qt::Key_Right:
        if(horizontal!=-1)//改5 -1
        {
          //  update();
            horizontal=1;
            vertical=0;
        }
        break;
    case Qt::Key_Up:
        if(vertical!=1)//改6  1
        {
          //  update();
            horizontal=0;
            vertical=-1;
        }
        break;
    case Qt::Key_Down:
        if(vertical!=-1)//改7 -1
        {
          //  update();
            horizontal=0;
            vertical=1;
        }
        break;
//    case Qt::Key_Z:
 //       s += tr("Z_Key Press");
 //       break;
    case Qt::Key_A:
        if(horizontal0!=1)//改4 1
        {
         //   update();
            horizontal0=-1;
            vertical0=0;
        }
        break;
    case Qt::Key_D:
        if(horizontal0!=-1)//改5 -1
        {
          //  update();
            horizontal0=1;
            vertical0=0;
        }
        break;
    case Qt::Key_W:
        if(vertical0!=1)//改6  1
        {
          //  update();
            horizontal0=0;
            vertical0=-1;
        }
        break;
    case Qt::Key_S:
        if(vertical0!=-1)//改7 -1
        {
          //  update();
            horizontal0=0;
            vertical0=1;
        }
        break;
//    case Qt::Key_Z:
 //       s += tr("Z_Key Press");
 //       break;
    }
}

void Widget::resizeEvent(QResizeEvent *e)
{

}
void Widget::initial_snake()
{
    begain_flag=0;
    head=new snake;
    head2=new snake;
    head->xx=350;
    head->yy=290;
    head2->xx=360;
    head2->yy=290;
    head->next=head2;
    head2->next=NULL;
    horizontal=-1;
    vertical=0;

    head0=new snake;
    head02=new snake;
    head0->xx=250;
    head0->yy=290;
    head02->xx=260;
    head02->yy=290;
    head0->next=head02;
    head02->next=NULL;
    horizontal0=-1;
    vertical0=0;
}


void Widget::on_pushButton_clicked()
{

    if(speed>10)//100
    {
        speed=speed-10;//100
        delete(timer);
        timer=new QTimer(this);
        timer->start(speed);
        connect(timer,SIGNAL(timeout()),this,SLOT(time_sig()));
    }
    ui->progressBar->setValue((100-speed)/1);//1000 10
}
void Widget::on_pushButton_2_clicked()
{
    if(speed<100)//1000
    {
        speed=speed+10;//100
        delete(timer);
        timer=new QTimer(this);
        timer->start(speed);
        connect(timer,SIGNAL(timeout()),this,SLOT(time_sig()));
    }
    ui->progressBar->setValue((100-speed)/1);//1000 10
}

bool Widget::hit_self()
{
    snake *p;
    p=head;
    bool flag=0;
    while(p!=NULL)
    {
        if(((head->xx+horizontal*10)==p->xx)&&((head->yy+vertical*10)==p->yy))
        {
            flag=1;
            break;
        }
        p=p->next;
    }
    return flag;
}

bool Widget::hit_self0()
{
    snake *p;
    p=head0;
    bool flag=0;
    while(p!=NULL)
    {
        if(((head0->xx+horizontal0*10)==p->xx)&&((head0->yy+vertical0*10)==p->yy))
        {
            flag=1;
            break;
        }
        p=p->next;
    }
    return flag;
}


void Widget::on_pushButton_3_clicked()
{
     game *main_guide = new game();
    main_guide->show();
    this->close();
    //delete this;
}

void Widget::on_pushButton_4_clicked()
{
    double2 *main_guide=new double2();
    main_guide->show();
    this->close();
}
