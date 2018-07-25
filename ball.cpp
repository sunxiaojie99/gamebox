
#include "ball.h"

Ball::Ball( qreal x, qreal y, qreal radius, QColor ballColor )
{
    dirX = 1.5;
    dirY = -1.5;
    speed = 2.0;

    shape = new QRectF( x, y, radius, radius );
    color = ballColor;
}

Ball::~Ball()
{
    delete shape;
}

void Ball::setShape( const QRectF &newShape )
{
    shape->setRect( newShape.left(), newShape.top(),
            newShape.width(), newShape.height() );
}



void Ball::setDirX( qreal newDirX )
{
    dirX = newDirX;
}

void Ball::setDirY( qreal newDirY )
{
    dirY = newDirY;
}

QRectF Ball::getShape() const
{
    return QRectF( shape->left(), shape->top(),
          shape->width(), shape->height() );
}



void Ball::move()
{
    shape->setLeft( shape->left() - dirX );
    shape->setRight( shape->right() - dirX );
    shape->setTop( shape->top() + dirY );
    shape->setBottom( shape->bottom() + dirY );
}

