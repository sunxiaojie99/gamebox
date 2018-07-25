#include "double2.h"
#include "ui_double2.h"
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
#include"widget.h"


double2::double2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::double2)
{
    ui->setupUi(this);
    begain_flag=0;//1为开始游戏，0为未开始游戏
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    head=new snake;
    head2=new snake;
    head->xx=290;
    head->yy=290;
    head2->xx=300;
    head2->yy=290;
    head->next=head2;//QT中几何坐标 以左上角为原点-水平为x轴，从左向右为正向-垂直为y轴，从上到下为正向
    head2->next=NULL;
    speed=50;//改500
    food_x=qrand()%10*10+55;
    food_y=qrand()%10*10+55;
    horizontal=-1;

    vertical=0;
    dead=0;
    button=0;
    length=2;
    colo=1;

    //QPalette p;
    //p.setColor(QPalette::Window,Qt::black);//1改
    //this->setPalette(p);
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

    //QPalette palette;
    //palette.setColor(QPalette::WindowText,Qt::white);
   // ui->label->setPalette(palette);

    setWindowTitle(QStringLiteral("Snake"));

    //QSound::play("/QTproject/scoff_snake/snake.wav");
    //player= new QMediaPlayer;
   // connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
   // player->setMedia(QUrl::fromLocalFile("/QTproject/scoff_snake/snake.wav"));
    //player->setVolume(30);
   // player->play();
}

double2::~double2()
{
    delete ui;
}

void double2::paintEvent(QPaintEvent *)
{
//    QDesktopWidget *d=QApplication::desktop();
//    int width=d->width();
//    int height=d->height();
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
    //ui->label_4->setText(QString::number(length));
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
        snake *p;
        p=head;
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
    }
    else
    {
        snake *p1,*p2,*temp;

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
              //paint_snake.setBrush(Qt::white);//改3
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
           //   qDebug()<<"AAAAAAAAAAA";
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
    }
}

void double2::time_sig()
{
 //   static int num=2;
    if(dead==1)
    {
        this->timer->stop();
        button=QMessageBox::information(this,"warning","You Lose!!",0,0);
        button=QMessageBox::information(this,"tip","Try again ?",QMessageBox::No | QMessageBox::Yes);
        this->begain_flag=0;
    }
  //  static int xx=4,yy=4;
 //   QRect body(200,200,250,250);
 //   QPainter painter(this);
 //   painter.drawRect(body);
    this->update();


}

void double2::changeEvent(QEvent *e)
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

void double2::keyPressEvent(QKeyEvent *e)
{
//    QString s = "";
//    switch(e->modifiers()){

//    case Qt::ControlModifier:
//        s = tr("Ctrl+");
//        break;
//    case Qt::AltModifier:
//        s = tr("Alt+");
//        break;
//    }

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
    }

}

void double2::resizeEvent(QResizeEvent *e)
{

}
void double2::initial_snake()
{
    begain_flag=0;

    head=new snake;
    head2=new snake;
    head->xx=290;
    head->yy=290;
    head2->xx=300;
    head2->yy=290;
    head->next=head2;
    head2->next=NULL;

    horizontal=-1;
    vertical=0;
}


void double2::on_pushButton_clicked()
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
void double2::on_pushButton_2_clicked()
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

bool double2::hit_self()
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

void double2::on_pushButton_3_clicked()
{
    game *main_guide = new game();
    main_guide->show();
    this->close();
}

void double2::on_pushButton_4_clicked()
{
    Widget *main_guide= new Widget();
    main_guide->show();
    this->close();
}
