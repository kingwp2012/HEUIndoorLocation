#include "pen.h"

Pen::Pen()
{
   ;
}

void Pen::paint(QPainter &paint)
{
    paint.setPen(QPen(color, width));
    paint.setBrush(brush);
    paint.drawLine(start, end);
}

int Pen::get_typeid()
{
    return 3;
}
