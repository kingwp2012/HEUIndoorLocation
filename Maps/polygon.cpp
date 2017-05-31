#include "polygon.h"

Polygon::Polygon()
{

}

void Polygon::paint(QPainter &paint)
{
    paint.setPen(QPen(color, width));
    paint.setBrush(brush);
    QPolygon polygon(polygonStack.size());
    for(int i = 0; i < polygonStack.size(); ++i)
    {
        polygon.setPoint(i, *polygonStack[i]);
    }
    paint.drawPolygon(polygon);
}

int Polygon::get_typeid()
{
    return 5;
}

void Polygon::push(QPoint *p)
{
    polygonStack.push_back(p);
}

QPoint *Polygon::top()
{
    return polygonStack[polygonStack.size() - 1];
}

Polygon::~Polygon()
{
    foreach(QPoint *p, polygonStack)
    {
        delete p;
    }
}

int Polygon::get_size()
{
    return polygonStack.size();
}

QPoint* Polygon::index(int pos)
{
    return polygonStack[pos];
}


