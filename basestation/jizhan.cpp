#include "jizhan.h"


jizhan::jizhan(QWidget *parent) :
    QWidget(parent)

{

    formlayout=new QFormLayout();
    //formlayout->setContentsMargins(60,20,100,20);
    formlayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    idEdit=new QLineEdit();
    macEdit = new QLineEdit();
    cateEdit=new QLineEdit();
    xEdit=new QLineEdit();
    yEdit=new QLineEdit();
    zEdit=new QLineEdit();
    remarkEdit=new QLineEdit();

    idEdit->setPlaceholderText(QStringLiteral("请输入基站ID"));
    macEdit->setPlaceholderText(QStringLiteral("请输入Mac地址"));
    cateEdit->setPlaceholderText(QStringLiteral("请输入建站类型"));
    xEdit->setPlaceholderText(QStringLiteral("基站x轴坐标"));
    yEdit->setPlaceholderText(QStringLiteral("基站y轴坐标"));
    zEdit->setPlaceholderText(QStringLiteral("基站z轴坐标"));
    remarkEdit->setPlaceholderText(QStringLiteral("备注"));

    formlayout->addRow(QStringLiteral("&基站ID："),idEdit);
    formlayout->addRow(QStringLiteral("&基站Mac地址："),macEdit);
    formlayout->addRow(QStringLiteral("&基站类型："),cateEdit);
    formlayout->addRow(QStringLiteral("&基站X坐标："),xEdit);
    formlayout->addRow(QStringLiteral("&基站Y坐标："),yEdit);
    formlayout->addRow(QStringLiteral("&基站Z坐标："),zEdit);
    formlayout->addRow(QStringLiteral("&备注："),remarkEdit);

    chk_btn=new QPushButton();
    chk_btn->setText(QStringLiteral("确 定"));

    hor_layout=new QHBoxLayout();
    hor_layout->addWidget(chk_btn);
    //hor_layout->setContentsMargins(100,100,0,30);
    gridlayout=new QGridLayout(this);
    gridlayout->addLayout(formlayout,0,0,1,1);
    gridlayout->addLayout(hor_layout,1,0,1,1);
    gridlayout->setSizeConstraint(QLayout::SetMaximumSize);

    setLayout(gridlayout);
    connect(this->chk_btn,SIGNAL(clicked()),this,SLOT(combine()));
}


  void jizhan::combine(){
      BaseInfo newbaseInfo;
      newbaseInfo.SetbaseID(this->idEdit->text());
      newbaseInfo.SetbaseMac(this->macEdit->text());
      newbaseInfo.SetbaseRemark(this->remarkEdit->text());
      newbaseInfo.SetbaseType(this->cateEdit->text());
      newbaseInfo.SetbaseX(this->xEdit->text());
      newbaseInfo.SetbaseY(this->yEdit->text());
      newbaseInfo.SetbaseZ(this->zEdit->text());
      emit newBaseItem(newbaseInfo);
      this->close();

  }


jizhan::~jizhan()
{

}
