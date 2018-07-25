/*创建砖块类，并定义操作、属性*/
//长度
#ifndef _BRICK_H_
#define _BRICK_H_

#include <QRect>
#include <QColor>

class Brick
{
public:
    Brick( qreal, qreal, qreal, qreal, QColor = Qt::red );
    ~Brick();

    void setShape( const QRectF & );
    void setColor( const QColor & );

    QRectF getShape() const;
    QColor getColor() const;


   QRectF *shape;
    QColor color;
};

#endif
