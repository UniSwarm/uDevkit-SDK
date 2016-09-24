#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QVector>
#include "robot.h"

class Map : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Map(QObject *parent = 0);
    Robot *getRobot() {return robot;}

private:
    Robot *robot;
    QVector<QPoint> lPoints;
    QPoint lastP;
signals:
    
public slots:
    void setPosition(int x, int y, int t);
    
};

#endif // MAP_H
