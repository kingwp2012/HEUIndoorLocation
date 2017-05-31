#ifndef PAINTAREA_H
#define PAINTAREA_H


#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QBrush>
#include <QStack>
#include <QFile>
#include <QPen>
#include <QPushButton>
#include <QPainter>
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsScene>
#include "ellipse.h"
#include "polygon.h"
#include "shape.h"
#include "type.h"
#include "line.h"
#include "rect.h"
#include "pen.h"


class PaintArea : public QWidget
{
    Q_OBJECT
public:
   // enum Shape{Line,Rectangle,RoundRect,Ellipse,Polygon,Polyline,Points,Arc,Path,Text,Pixmap};
    explicit PaintArea(QWidget *parent = 0);
    void setBrush(QBrush);

  //  QPointF mapToMap(QPointF); //用于实现场景坐标系与地图坐标之间的映射，以获得某点的经纬度值

public slots:
    void set_shape(type);
    void set_color(QColor);
    void set_brush(QColor);
    void set_width(int);
    void set_alpha(int);
    void set_straight(bool);
    void open_file();
    void save_file();
    void saveAs_file();
    void Undo();
    void Redo();
    void Reset();
  //  void slotZoom(int); //用于设置放大和缩小

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

   // void drawBackground(QPainter *painter, const QRectF &rect); //用于绘制背景网格

private:


    // //////////////////////
    type shapeType;
    QStack<Shape *>stack;
    QStack<Shape *>redoStack;  //撤销恢复用
    Shape *shape;
    QColor currentColor;
    QColor currentBrush;
    QString currentPath;
    int currentWidth;
    bool stop_polygon;
    bool is_straight;
    QPushButton *pushbutton1;

    QBrush brush;
  //  QPainter *paint;

//    qreal zoom;                   //用于设置缩放因子
//    QLabel *viewCoord;
//    QLabel *sceneCoord;
//    QLabel *mapCoord;
//    double x1,y1;
//    double x2,y2;

};

#endif // PAINTAREA_H



// ///////////////////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////////////////











