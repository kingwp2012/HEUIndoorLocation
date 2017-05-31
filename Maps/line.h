#ifndef LINE_H
#define LINE_H

#include <QPainter>
#include "shape.h"
class Line : public Shape
{
public:
    Line();
private:
    virtual void paint(QPainter& paint) override;
    virtual int get_typeid() override;
};

#endif // LINE_H

