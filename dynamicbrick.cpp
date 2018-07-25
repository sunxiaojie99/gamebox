#include "dynamicBrick.h"
#include <qdebug.h>

dynamicBrick::dynamicBrick( qreal x, qreal y, qreal width, qreal height, QColor dynamicBrickColor )
{
    shape = new QRectF( x, y, width, height );
    color = dynamicBrickColor;
}

dynamicBrick::~dynamicBrick()
{
    delete shape;
}

//使滑块移动
void dynamicBrick::setShape( qreal x, qreal y, qreal width, qreal height,int w )
{

    if( x > -60 && x < w-200) //避免滑出界外
    shape->setRect(x, y,width,height);
}

//获取滑块位置及大小
QRectF dynamicBrick::getShape() const
{
    return QRectF( shape->left(), shape->top(),
		  shape->width(), shape->height() );
}


