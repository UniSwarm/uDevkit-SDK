#include "map.h"

#include <math.h>
#define PI 3.1415;

#include <QRectF>

Map::Map(QObject *parent) :
    QGraphicsScene(parent)
{
    QGraphicsItem *haut,*bas,*gauche,*droite;
    QGraphicsItem *gateau;

    QColor marron(140,70,0),gray(240,240,240),green(0,255,0),noir(0,0,0);
    QPixmap pixmap(3000,2000);

    lastP.setX(0);
    lastP.setY(0);

    pixmap.fill(green);
    addPixmap (pixmap);

    // pens
    QPen pen_black_thick(Qt::black,20);
    QPen pen_yellow_thick(Qt::yellow,20);
    QPen pen_red_thick(Qt::red,20);
    QPen pen_black_not_thick(Qt::black,2);

    // frame
    QRect frame(0,0,3000,2000);

    // stating zones
    QPainterPath redstartzone;
    redstartzone.arcMoveTo(QRect(-400,-100,800,800), 0);
    redstartzone.arcTo(QRect(-400,-100,800,800), 0, -90);
    redstartzone.lineTo(0,0);
    redstartzone.lineTo(400,0);
    redstartzone.closeSubpath();
    addPath(redstartzone, QPen(), QBrush(gray));
    QPainterPath redcirclestart;
    redcirclestart.arcMoveTo(QRect(-410,-100,800,800), 0);
    redcirclestart.arcTo(QRect(-410,-100,800,800), 0, -90);
    addPath(redcirclestart, pen_red_thick, Qt::transparent);
    addLine(QLine(390,0,390,300), pen_red_thick);

    QPainterPath yellowstartzone;
    yellowstartzone.arcMoveTo(QRect(2600,-100,800,800), 180);
    yellowstartzone.arcTo(QRect(2600,-100,800,800), 180, 90);
    yellowstartzone.lineTo(3000,0);
    yellowstartzone.lineTo(2600,0);
    yellowstartzone.closeSubpath();
    addPath(yellowstartzone, QPen(), QBrush(gray));
    QPainterPath yellowcirclestart;
    yellowcirclestart.arcMoveTo(QRect(2610,-100,800,800), 180);
    yellowcirclestart.arcTo(QRect(2610,-100,800,800), 180, 90);
    addPath(yellowcirclestart, pen_yellow_thick, Qt::transparent);
    addLine(QLine(2610,0,2610,300), pen_yellow_thick);

    // fruit
    addRect(400, 0, 700, 130, QPen(Qt::black, 2), green);
    addRect(400, 130, 700, 170, QPen(Qt::black, 2), Qt::yellow);

    addRect(1900, 0, 700, 130, QPen(Qt::black, 2), green);
    addRect(1900, 130, 700, 170, QPen(Qt::black, 2), Qt::red);

    // black lines
    addLine(QLine(0,600,1200,600), pen_black_thick);
    addLine(QLine(1350,0,1350,450), pen_black_thick);
    QPainterPath leftCircleLine;
    leftCircleLine.arcMoveTo(QRect(1050,300,300,300),-90);
    leftCircleLine.arcTo(QRect(1050,300,300,300),-90,90);
    addPath(leftCircleLine, pen_black_thick, Qt::transparent);

    addLine(QLine(3000,600,1800,600), pen_black_thick);
    addLine(QLine(1650,0,1650,450), pen_black_thick);
    QPainterPath rightCircleLine;
    rightCircleLine.arcMoveTo(QRect(1650,300,300,300),-90);
    rightCircleLine.arcTo(QRect(1650,300,300,300),-90,-90);
    addPath(rightCircleLine, pen_black_thick, Qt::transparent);

    // black frame
    addRect(frame,pen_black_not_thick, Qt::transparent);
    haut = addRect(0,0,3000,-20, noir, gray);
    bas = addRect(0,2000,3000,20, noir, gray);
    gauche = addRect(0,-20,-20,2040, noir, gray);
    droite = addRect(3000,-20,20,2040, noir, gray);
    addRect(0,0,-20,710,QPen(),Qt::red);
    addRect(-20,0,420,-20,QPen(),Qt::red);
    addRect(3000,0,20,710,QPen(),Qt::yellow);
    addRect(2600,0,420,-20,QPen(),Qt::yellow);

    // tree
    addEllipse(-150,1150,300,300,QPen(),green)->setZValue(2);
    addEllipse(2850,1150,300,300,QPen(),green)->setZValue(2);
    addEllipse(550,1850,300,300,QPen(),green)->setZValue(2);
    addEllipse(2150,1850,300,300,QPen(),green)->setZValue(2);

    // center depose
    addEllipse(1350,850,300,300,QPen(),marron);

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
