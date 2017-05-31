#include "shape.h"

Shape::Shape()
    :start(QPoint(0, 0)), end(QPoint(0, 0))
{
    ;
}

void Shape::set_end(QPoint p)
{
    end = p;
}

void Shape::set_start(QPoint p)
{
    start = p;
}

void Shape::set_pos(QPoint p1, QPoint p2, bool is_straight)
{
    start = p1;
    int dis;
    if (is_straight)
    {
        if (abs(p1.rx() - p2.rx()) < abs(p1.ry() - p2.ry()))
            dis = abs(p1.rx() - p2.rx());
        else
            dis = abs(p1.ry() - p2.ry());
        if (p1.rx() - p2.rx() > 0)
            p2.setX(p1.rx() - dis);
        else
            p2.setX(p1.rx() + dis);

        if(p1.ry() - p2.ry() > 0)
            p2.setY(p1.ry() - dis);
        else
            p2.setY(p1.ry() + dis);
    }
    end = p2;
}

QPoint Shape::get_end()
{
    return end;
}

QPoint Shape::get_start()
{
    return start;
}

QColor Shape::get_color()
{
    return color;
}

QColor Shape::get_brush()
{
    return  brush;
}

int Shape::get_width()
{
    return width;
}

void Shape::set(QColor c1, QColor c2, int w)
{
    color = c1;
    brush = c2;
    width = w;
}
