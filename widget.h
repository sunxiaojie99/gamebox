#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include<QSoundEffect>
#include<QMediaPlayer>
namespace Ui {
    class Widget;
}
class QSoundEffect;
class QMediaPlayer;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void draw_map();
    ~Widget();
    struct snake{
        int xx;
        int yy;
        snake *next;
    };
    int begain_flag;
    int horizontal;
    int horizontal0;
    int vertical;
    int vertical0;
    snake *head,*head2;
    snake *head0,*head02;
    int food_x,food_y;
    int speed;
    int dead;
    int button;
    int length;
    QTimer *timer;
protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent *);
    bool hit_self();
    bool hit_self0();
    void initial_snake();
private:
    Ui::Widget *ui;
    QMediaPlayer *player;
    int colo;
public slots:
    void time_sig();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

signals:
    void display(int number);
};

#endif // WIDGET_H
