/*定义挡板滑块，,有左右移动操作*/


#ifndef _dynamicBrick_H_
#define _dynamicBrick_H_

#include <QRect>
#include <QColor>

class dynamicBrick
{
public:
    dynamicBrick( qreal, qreal, qreal, qreal, QColor = Qt::red );
    ~dynamicBrick();

    void setShape(qreal x , qreal y, qreal width, qreal height,int w);
    QRectF getShape() const;


    QRectF *shape;
    QColor color;
};

#endif 
