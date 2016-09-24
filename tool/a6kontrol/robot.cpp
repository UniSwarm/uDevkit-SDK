#include "robot.h"

#include <QPainter>

Robot::Robot(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    _path.moveTo(0, -140);
    _path.lineTo(80, -30);
    _path.lineTo(80, 50);
    _path.lineTo(-80, 50);
    _path.lineTo(-80, -30);
    _path.closeSubpath();
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(QColor(0,0,0)));
    painter->drawPath(_path);

    painter->setPen(QPen(QColor(255,127,39),5));
    painter->setBrush(QColor(255,127,39));
    painter->drawRect(QRect(80,-30,10,80));
    painter->drawRect(QRect(-80,-30,-10,80));

    QPainterPath tri;
    tri.moveTo(0, -140);
    tri.lineTo(40, -70);
    tri.lineTo(-40, -70);
    tri.closeSubpath();
    painter->drawPath(tri);
}

QRectF Robot::boundingRect() const
{
    return QRectF(-300,-300,600,600);
}

QPainterPath Robot::clipPath() const
{
    return _path;
}

void Robot::setPosition(int x, int y, int t)
{
    setPos(x,y);
    setRotation(t);
    prepareGeometryChange();
}
