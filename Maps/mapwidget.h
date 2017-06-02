#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include "mapdraw.h"



namespace Ui {
class Mapwidget;
}

class Mapwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Mapwidget(QWidget *parent = 0);
    ~Mapwidget();
   // void setupModel();

public slots:
    void drawmap_show();

private:
    Ui::Mapwidget *ui;
    QPushButton *createmap;
    QPushButton *deletemap;
    QPushButton *checkmap;
 // BaseModel   *baseModel;
  //QTableView  *baseTable;
    QPushButton *nextPage;
    QPushButton *prePage;
    QPushButton *firstPage;
    QPushButton *lastPage;
    MapDraw     *mapdraw;

};

#endif // MAPWIDGET_H




// //////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////
