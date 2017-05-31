#include "line.h"

Line::Line()
{

}

void Line::paint(QPainter &paint)
{
    paint.setPen(QPen(color, width));
    paint.setBrush(brush);
    paint.drawLine(start, end);
}

int Line::get_typeid()
{
    return 2;
}
