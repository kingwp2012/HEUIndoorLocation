#include "ellipse.h"

Ellipse::Ellipse()
{

}

void Ellipse::paint(QPainter &paint)
{
    paint.setPen(QPen(color, width));
    paint.setBrush(brush);
    paint.drawEllipse(start, end.rx() - start.rx(), end.ry() - start.ry());
}

int Ellipse::get_typeid()
{
    return 4;
}
