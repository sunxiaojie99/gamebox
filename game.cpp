#include "game.h"
#include "ui_game.h"
#include "widget.h"
#include<QDialog>
#include"mywidget.h"
#include<QSoundEffect>
#include"double2.h"

game::game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(Check()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(enter()));
    setWindowTitle(QStringLiteral("GameBox"));
    effect= new QSoundEffect(this);
    effect->setSource(QUrl::fromLocalFile(":/music/snake.wav"));
}

game::~game()
{
    delete ui;
}


void game::Check(){
    MyWidget *main_guide = new MyWidget();
    main_guide->show();
    this->close();
    //this->setVisible(false);
}
 void game::enter(){
    double2 *main_guide = new double2();
    main_guide->show();
    this->close();
 }

void game::on_pushButton_4_clicked()
{
    effect->play();
    effect->setLoopCount(QSoundEffect::Infinite);
}

void game::on_pushButton_5_clicked()
{
    effect->stop();
}

void game::on_spinBox_valueChanged(int arg1)
{
    effect->setLoopCount(arg1);
}
