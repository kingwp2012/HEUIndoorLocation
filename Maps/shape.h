#ifndef SHAPE_H
#define SHAPE_H
#include <QPoint>
#include <QPainter>
#include <QColor>

class Shape
{
public:
    Shape();
    void set_start(QPoint p);
    void set_end(QPoint p);
    void set_pos(QPoint, QPoint, bool);
    void set(QColor, QColor, int);

    QPoint get_start();
    QPoint get_end();
    QColor get_color();
    QColor get_brush();
    int get_width();
    virtual void paint(QPainter& painter) = 0;
    virtual int get_typeid() = 0;
protected:
    QPoint start;
    QPoint end;
    QColor color;
    QColor brush;
    int width;
};

#endif // SHAPE_H
