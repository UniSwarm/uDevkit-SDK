#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>

class Robot : public QGraphicsItem
{
public:
    explicit Robot(QGraphicsItem *parent = 0);

    void setPosition(int x, int y, int t);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    QPainterPath clipPath() const;

    QPainterPath _path;
};

#endif // ROBOT_H
