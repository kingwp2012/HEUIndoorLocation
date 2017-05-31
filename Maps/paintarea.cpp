#include "paintarea.h"
#include <QPainter>
#include <QSlider>
#include <QGridLayout>
#include <QGraphicsScene>
#include <typeinfo>
#include <math.h>

PaintArea::PaintArea(QWidget *parent) :
     QWidget(parent), shape(nullptr), shapeType(type_Rect)
  {
      currentBrush = Qt::transparent;
      currentColor = Qt::black;
      currentWidth = 1;
      stop_polygon = true;
      is_straight = false;
      setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


//void PaintArea::slotZoom(int value)   	//地图缩放
//{
//    QPainter paint(this);
//    qreal s;
//    if(value>zoom)                 		//放大
//    {
//        s=pow(1.01,(value-zoom));
//    }
//    else                             	//缩小
//    {
//        s=pow(1/1.01,(zoom-value));
//    }
//    paint.scale(s,s);
//    zoom = value;
//}

  void PaintArea::paintEvent(QPaintEvent *)
  {
      QPainter paint(this);
      paint.setBrush(brush);
     // paint.setBrush(Qt::white);
      paint.setPen(Qt::white);   //绘制画板区域
      paint.drawRect(0, 0, size().width(), size().height());
      foreach(Shape *shape, stack)
      {
          shape->paint(paint);
      }     
  }

  void PaintArea::mousePressEvent(QMouseEvent *e)
  {
      while(!redoStack.empty())
      {
          Shape *tmp = redoStack.top();
          redoStack.pop();
          delete tmp;
      }
      ////////////Polygon特殊处理/////////////////
      if(e->button() == Qt::RightButton)
      {
          stop_polygon = true;
          return;
      }
      if (shapeType == type_Polygon)
      {
          if(stop_polygon == true || stack.isEmpty())
          {
              shape = new Polygon;
              Polygon *tmp = dynamic_cast<Polygon *>(shape);
              QPoint *p = new QPoint(e->pos());
              tmp->push(p);
              QPoint *p2 = new QPoint(e->pos() + QPoint(0, 1));
              tmp->push(p2);
              stack.push(shape);
              shape->set(currentColor, currentBrush, currentWidth);
              stop_polygon = false;
          }
          else
          {
              if (typeid(*stack.top()) != typeid(Polygon))
              {
                  stop_polygon = true;
                  return;
              }
              QPoint *p = new QPoint(e->pos());
              dynamic_cast<Polygon *>(shape)->push(p);
          }
          update();
          return;
      }
      stop_polygon = true;
      switch(shapeType)
      {
      case type_Line:
          shape = new Line;
          break;
      case type_Rect:
          shape = new Rect;
          break;
      case type_Pen:
          shape = new Pen;
          break;
      case type_Ellipse:
          shape = new Ellipse;
          break;
      }
      if(shape != NULL)
      {
          if (shapeType == type_Pen)
          {
              Shape *zero = new Pen;
              zero->set_start(QPoint(0, 0));
              zero->set_end(QPoint(0, 0));
              stack.push(zero);

          }//Pen 制造间隔点
          shape->set(currentColor, currentBrush, currentWidth);
          shape->set_pos(e->pos(), e->pos() + QPoint(0, 1), is_straight);
          stack.push(shape);
      }
      update();
  }

  void PaintArea::mouseMoveEvent(QMouseEvent *e)
  {
      ////////////Polygon特殊处理/////////////////
  // 用于显示视图 场景 地图的坐标
  //  /////////////////QGraphicsView 坐标////////////////////
//      QPoint viewPoint = event->pos();
//      viewCoord->setText(QString::number(viewPoint.x())+","+QString::number(viewPoint.y()));

//      //QGraphicsScene 坐标
//      QPointF scenePoint = mapToScene(viewPoint);
//      sceneCoord->setText(QString::number(scenePoint.x())+","+QString::number(scenePoint.y()));

//      //地图坐标(经、纬度值)
//      QPointF latLon = mapToMap(scenePoint);
//      mapCoord->setText(QString::number(latLon.x())+","+QString::number(latLon.y()));
  // ///////////////////END //////////////////////

      if (shapeType == type_Polygon)
      {
          Polygon *tmp = dynamic_cast<Polygon *>(stack.top());
          QPoint *p = tmp->top();
          p->setX(e->x());
          p->setY(e->y());
          update();
          return;
      }
      shape->set_pos(shape->get_start(), e->pos(), is_straight);

      ////////////Pen特殊处理/////////////////
      if (shapeType == type_Pen)
      {
          shape = new Line;
          shape->set(currentColor, currentBrush, currentWidth);
          stack.push(shape);
          shape->set_start(e->pos());
          shape->set_end(e->pos());
      }
      update();
  }


//  QPointF PaintArea::mapToMap(QPointF p)
//  {
//      QPointF latLon;
//      qreal w =sceneRect().width();
//      qreal h =sceneRect().height();

//      qreal lon = y1-((h/2+p.y())*abs(y1-y2)/h);
//      qreal lat = x1+((w/2+p.x())*abs(x1-x2)/w);

//      latLon.setX(lat);
//      latLon.setY(lon);

//      return latLon;
//  }





  void PaintArea::mouseReleaseEvent(QMouseEvent *)
  {
       ////////////Pen特殊处理/////////////////
      if (shapeType== type_Pen)
      {
          Shape *zero = new Pen;
          zero->set_start(QPoint(0, 0));
          zero->set_end(QPoint(0, 0));
          stack.push(zero);
      }//制造间隔点
  }

  void PaintArea :: setBrush(QBrush b)
  {
      brush = b;
      update();
  }
  void PaintArea::set_straight(bool c)
  {
      is_straight = c;
  }

  ///////////////////SLOT/////////////
  void PaintArea::set_color(QColor c)
  {
      currentColor = c;
  }
  void PaintArea::set_brush(QColor c)
  {
      int tmp;
      int a;
      currentBrush.getRgb(&tmp, &tmp, &tmp, &a);
      currentBrush = c;
      currentBrush.setAlpha(a);

  }

  void PaintArea::set_shape(type new_shape)
  {
      shapeType = new_shape;
  }

  void PaintArea::set_width(int w)
  {
      currentWidth = w;
  }

  void PaintArea::set_alpha(int a)
  {
      currentBrush.setAlpha((100 - a) * 255 / 100);
  }

  ////撤销
  void PaintArea::Undo()
  {
      if (!stack.empty())
      {
          if(typeid(*stack.top()) == typeid(Pen))//运行期类型识别
          {

              redoStack.push(stack.top());
              stack.pop();

              while(1) //寻找临界点
              {
                  if (stack.top()->get_start() == QPoint(0, 0) && stack.top()->get_end() == QPoint(0, 0))
                      break;
                  redoStack.push(stack.top());
                  stack.pop();
              }
              redoStack.push(stack.top());    //加入临界点
              stack.pop();

          }
          else
          {
              Shape *tmp = stack.top();
              stack.pop();
              redoStack.push(tmp);
          }
      }
      update();
  }

  ///恢复
  void PaintArea::Redo()
  {
      if (!redoStack.empty())
      {
          if(typeid(*redoStack.top()) == typeid(Pen))//运行期类型识别
          {

              stack.push(redoStack.top());
              redoStack.pop();

              while(1) //寻找临界点
              {
                  if (redoStack.top()->get_start() == QPoint(0, 0) && redoStack.top()->get_end() == QPoint(0, 0))
                      break;
                  stack.push(redoStack.top());
                  redoStack.pop();
              }
              stack.push(redoStack.top());    //加入临界点
              redoStack.pop();

          }
          else
          {
              Shape *tmp = redoStack.top();
              redoStack.pop();
              stack.push(tmp);
          }
      }
      update();
  }

  void PaintArea::Reset()
  {
      currentBrush = Qt::transparent;
      currentColor = Qt::black;
      currentWidth = 1;
      stack.clear();
      redoStack.clear();
      stop_polygon = true;
      update();
  }

  void PaintArea::open_file()
  {
      QString s = QFileDialog::getOpenFileName(this, "Select A File", "/", "Paint File(*.paint)");
      if (s.isEmpty())
      {
          QMessageBox::information(this, tr("INformation"), tr("Open failed!"));
          return;
      }
      int st = 0;
      int x1, y1, x2, y2;
      int r1, r2, g1, g2, b1, b2, a1, a2;
      int width;
      Reset();
      currentPath = s;
      QFile file(currentPath);
      if (file.open(QFile::ReadOnly))
      {
          QTextStream cin(&file);
          while(!cin.atEnd())
          {
              st = 0;
              cin >>st;
              Shape *tmp;
              if (st == 0)
                  break;  //每次都会莫名其妙多读一行，，What A Fhuack
              if (st == 5)
              {
                  tmp = new Polygon;

                  int size;
                  cin >> size;

                  for(int i = 0; i < size; ++i)
                  {
                      cin >> x1 >> y1;
                      QPoint *p = new QPoint(x1, y1);
                      dynamic_cast<Polygon*>(tmp)->push(p);
                  }
                  cin >> r1>>g1>>b1>>a1>>r2>>g2>>b2>>a2>>width;
                  tmp->set(QColor(r1, g1, b1, a1), QColor(r2, g2, b2, a2), width);
                  stack.push(tmp);

                  continue;
              }
              else
                  cin >>x1>>y1>>x2>>y2>>r1>>g1>>b1>>a1>>r2>>g2>>b2>>a2>>width;

              switch(st)
              {
              case 1:
               tmp = new Rect;
                  break;
              case 2:
                  tmp = new Line;
                  break;
              case 3:
                  tmp = new Pen;
                  break;
              case 4:
                  tmp = new Ellipse;
              }
              tmp->set_start(QPoint(x1, y1));
              tmp->set_end(QPoint(x2, y2));
              tmp->set(QColor(r1, g1, b1, a1), QColor(r2, g2, b2, a2), width);

              stack.push(tmp);
          }
      }
      file.close();
      update();
  }

  void PaintArea::save_file()
  {
      if (stack.empty())
      {
          QMessageBox::information(this, tr("Information"), tr("Nothing To Be Save!"));
          return;
      }
      if (currentPath.isEmpty())
      {
          // *.paint *.gif *jpg *.ico
          QString s = QFileDialog::getSaveFileName(this, "Select A File", "/", "Paint File(*.paint)");
          currentPath = s;
      }
      else
      {
          QMessageBox::information(this, tr("Information"), tr("Save Successful!"));
      }

      int r1, r2, g1, g2, b1, b2, a1, a2;
      QFile file(currentPath);
      if (file.open(QFile::WriteOnly))
      {
          QTextStream cout(&file);
          foreach(Shape *shape, stack)
          {
              if (shape->get_typeid() == 5)
              {
                  cout << "5 ";
                  Polygon *p = dynamic_cast<Polygon*>(shape);
                  cout << p->get_size() << " ";
                  for(int i = 0; i < p->get_size(); ++i)
                      cout << p->index(i)->rx() << " " << p->index(i)->ry() << " ";
              }
              else
              {
                  cout << shape->get_typeid() << " "
                   << shape->get_start().rx() << " " << shape->get_start().ry() << " "
                   << shape->get_end().rx() << " " << shape->get_end().ry() << " ";
              }

              shape->get_color().getRgb(&r1, &g1, &b1, &a1);
              shape->get_brush().getRgb(&r2, &g2, &b2, &a2);

              cout <<r1<<" "<<g1<<" "<<b1<<" "<<a1<<" "
                   <<r2<<" "<<g2<<" "<<b2<<" "<<a2<<" "
                   << shape->get_width() << endl;
          }
      }
      file.close();
  }

  void PaintArea::saveAs_file()
  {
      if (stack.empty())
      {
          QMessageBox::information(this, tr("Information"), tr("Nothing To Be Save!"));
          return;
      }
      else
      {
          QString s = QFileDialog::getSaveFileName(this, "Select A File", "/", "Paint File(*.paint)");
          currentPath = s;
      }
      save_file();
  }
