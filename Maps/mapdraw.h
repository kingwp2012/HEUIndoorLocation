#ifndef MAPDRAW_H
#define MAPDRAW_H

#include <QMainWindow>
#include <QWidget>
#include "paintarea.h"
#include <QColorDialog>
#include <QInputDialog>
#include <QActionGroup>
#include <QComboBox>
#include <QFileDialog>
#include <QKeyEvent>
#include <QToolBar>
#include <QMenuBar>
#include <QSlider>
#include <QAction>
#include <QColor>
#include <QLabel>
#include <QMenu>
#include <QDial>
#include "type.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
//#include "backgroundstyle.h"

namespace Ui {
class MapDraw;
}

class MapDraw : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapDraw(QWidget *parent = 0);
    ~MapDraw();
    void keyPressEvent(QKeyEvent *);    //键盘事件
    void keyReleaseEvent(QKeyEvent *);  //键盘事件
signals:
    void openFile_SIGNAL(QString);
    void saveFile_SIGNAL(QString);      //文件操作信号
    void change_straight(bool);          //改变是否笔直绘画的信号
    void color_change(QColor);          //属性调整信号
    void brush_change(QColor);
    void width_change(int);         //设置线条粗细的信号
    void alpha_change(int);         //设置透明度的信号
    void select_shape(type);      //选择形状信号
public slots:
      void slotZoom(int); //用于设置放大和缩小
private:
    Ui::MapDraw *ui;
    QGraphicsScene *scene;

    qreal zoom;                   //用于设置缩放因子
    QGraphicsView *view;
    PaintArea *paint;
    QLabel *widthLabel;     //显示当前线条大小
    QDial *widthDial;
    QLabel *alphaLabel;     //显示当前透明度
    QDial *alphaDial;
    virtual QSize sizeHint() const override;        //调整窗体的函数
   // BackgroundStyle *backgroundstyle;
    QLabel *l1;
    QComboBox *box1;
 //   QWidget *setbackground;
    QFrame *brushColorFrame;
    QPushButton *brushColorBtn;

private slots:
    void change_widthLabel(int);        ///改变属性的槽
    void change_alphaLabel(int);
    void color_SLOT();
    void brush_SLOT();
    void width_SLOT();
    void ShowBrushColor();
    void background_SLOT(int);
    void draw_rect();           ///绘制槽
    void draw_line();
    void draw_pen();
    void draw_polygon();
    void draw_ellipse();
    void reset_dial();      //重置面板
};

#endif // MAPDRAW_H
