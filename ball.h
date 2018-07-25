#ifndef _BALL_H_
#define _BALL_H_

#include <QRect>
#include <QColor>

class Ball
{
public:
    Ball( qreal, qreal, qreal, QColor = Qt::green );
    ~Ball();
    
    void move();
    QRectF rect() const;

    void setShape( const QRectF & );
    void setDirX( qreal );
    void setDirY( qreal );

    QRectF getShape() const;

    QRectF *shape;
    QColor color;
    qreal dirX; //砖块水平移动参数
    qreal dirY; //砖块垂直移动参数
    qreal speed;
};

#endif 
