#ifndef JZWIDGET_H
#define JZWIDGET_H

#include <QWidget>
#include <QPushButton>
#include"basemodel.h"
#include<QTableView>
#include "jizhan.h"

namespace Ui {
class JzWidget;
}

class JzWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JzWidget(QWidget *parent = 0);
    ~JzWidget();
    void setupModel();
private:
    Ui::JzWidget *ui;
public slots:
    void deleteBaseItem();
    void addBaseWin();
    void freshBaseItem();
    void addBaseItem(BaseInfo &info);
private:
    QPushButton *addBase;
    QPushButton *deleteBase;
    QPushButton *freshBase;
    BaseModel   *baseModel;
  //QTableView  *baseTable;
    QPushButton *nextPage;
    QPushButton *prePage;
    QPushButton *firstPage;
    QPushButton *lastPage;
    jizhan      *addWin;
};

#endif // JZWIDGET_H

