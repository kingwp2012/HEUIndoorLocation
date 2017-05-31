#ifndef PEN_H
#define PEN_H
#include "shape.h"
#include <QPainter>
class Pen : public Shape
{
public:
    Pen();
    virtual void paint(QPainter& paint) override;
    virtual int get_typeid() override;
};

#endif // PEN_H

