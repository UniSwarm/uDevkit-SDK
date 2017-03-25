#include "map.h"

#include <math.h>
#define PI 3.1415;

#include <QRectF>
#include <QPen>
#include <QBrush>
#include <QColor>

Map::Map(QObject *parent) :
    QGraphicsScene(parent)
{
    for(int x=0; x<10; x++)
        for(int y=0; y<5; y++)
            addRect(x*300, (y*2+x%2)*300, 300, 300, QPen(Qt::black), QBrush(Qt::gray));

    robot = new Robot();
    addItem(robot);
    robot->setPos(1000,1000);
}

void Map::setPosition(int x, int y, int t)
{
    robot->setPosition(x, y, -t+90);
    if(lastP.x()!=0) addLine(QLine(lastP, QPoint(x, y)));
    lastP.setX(x);
    lastP.setY(y);
}
