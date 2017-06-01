

#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <QPolygon>
#include <QPoint>
#include <QVector>

class Polygon : public Shape
{
public:
    Polygon();
    ~Polygon();
    virtual void paint(QPainter&);
    virtual int get_typeid();
    void push(QPoint *);
    QPoint *top();
    int get_size();
    QPoint *index(int pos);
private:
    QVector<QPoint *>polygonStack;

};

#endif // POLYGON_H



