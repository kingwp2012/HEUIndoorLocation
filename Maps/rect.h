#ifndef RECT_H
#define RECT_H

#include "shape.h"
#include <QPainter>

class Rect : public Shape
{
public:
    Rect();
private:
    virtual void paint(QPainter& paint) override;
    virtual int get_typeid() override;
};

#endif // RECT_H


