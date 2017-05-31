#include "rect.h"

Rect::Rect()
{

}

void Rect::paint(QPainter &paint)
{
    paint.setPen(QPen(color, width));
    paint.setBrush(brush);
    paint.drawRect(start.x(), start.y(),end.x() - start.x(), end.y() - start.y());
}

int Rect::get_typeid()
{
    return 1;
}
