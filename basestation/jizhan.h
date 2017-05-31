#ifndef JIZHAN_H
#define JIZHAN_H

#include <QWidget>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <basestation/basemodel.h>


class jizhan : public QWidget
{
    Q_OBJECT

public:
    explicit jizhan(QWidget *parent = 0);
    ~jizhan();
public:
    QFormLayout *formlayout;
    QLineEdit *idEdit;
    QLineEdit *cateEdit;
    QLineEdit *xEdit;
    QLineEdit *yEdit;
    QLineEdit *zEdit;
    QLineEdit *remarkEdit;
    QPushButton *chk_btn;
    QGridLayout *gridlayout;
    QHBoxLayout *hor_layout;
signals:
    void newBaseItem(BaseInfo &info);
public slots:
    void combine();
};

#endif // JIZHAN_H
