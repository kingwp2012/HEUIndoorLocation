#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
class Ellipse : public Shape
{
public:
    Ellipse();
private:
virtual void paint(QPainter& paint) override;
virtual int get_typeid() override;
};


#endif // CIRCLE_H
