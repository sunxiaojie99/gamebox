#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include<QSoundEffect>

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    ~game();

private slots:
    void Check();
    void enter();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::game *ui;
    QSoundEffect *effect;
signals:
    void display(int number);
};

#endif // GAME_H
