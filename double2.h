#ifndef DOUBLE2_H
#define DOUBLE2_H

#include <QWidget>
#include <QTimer>
#include<QSoundEffect>
#include<QMediaPlayer>

namespace Ui {
    class double2;
}
class QSoundEffect;
class QMediaPlayer;
class double2 : public QWidget
{
    Q_OBJECT

public:
    explicit double2(QWidget *parent = 0);
   // void draw_map();
    ~double2();
    struct snake{
        int xx;
        int yy;
        snake *next;
    };
    int begain_flag;
    int horizontal;
    int vertical;
    snake *head,*head2;
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
    void initial_snake();
private:
    Ui::double2 *ui;
    QMediaPlayer *player;
    int colo;
public slots:
    void time_sig();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
signals:
    void display(int number);
};

#endif // WIDGET_H
