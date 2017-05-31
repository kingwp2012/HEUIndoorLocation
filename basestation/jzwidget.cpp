#include "jzwidget.h"
#include "ui_jzwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include "jizhan.h"
JzWidget::JzWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JzWidget)
{

    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
    this->baseStationdao = new BaseStationDao();
    setupModel();
    setLayout(ui->verticalLayout);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);//布局内控件居中
    ui->tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tab->setLayout(ui->verticalLayout_2);
    ui->verticalLayout_2->setAlignment(Qt::AlignCenter);
    ui->widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->widget->setMaximumSize(1200,650);
    ui->widget->setLayout(ui->verticalLayout_3);
    ui->verticalLayout_3->setAlignment(Qt::AlignCenter);
    ui->widget_2->setMaximumSize(1100,40);
    QHBoxLayout *hl1=new QHBoxLayout();
    ui->widget_2->setLayout(hl1);
    freshBase=new QPushButton();
    freshBase->setText(QStringLiteral("刷新"));
    addBase=new QPushButton();
    addBase->setText(QStringLiteral("添加"));
    deleteBase=new QPushButton();
    deleteBase->setText(QStringLiteral("删除"));
    hl1->setAlignment(Qt::AlignLeft);
    hl1->addWidget(addBase);
    hl1->addWidget(deleteBase);
    hl1->addWidget(freshBase);
    ui->widget_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

   // //////////////////tableview
    ui->tableView->setMaximumSize(1100,500);
    ui->tableView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->tableView->setModel(baseModel);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:skyblue;"
                                                           "color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  //  /////////////////////////////
    ui->widget_3->setMaximumSize(1100,40);
    QHBoxLayout *hl2=new QHBoxLayout();
    ui->widget_3->setLayout(hl2);
    firstPage =new QPushButton();
    firstPage->setText(QStringLiteral("第一页"));
    nextPage=new QPushButton();
    nextPage->setText(QStringLiteral("下一页"));
    prePage=new QPushButton();
    prePage->setText(QStringLiteral("前一页"));
    lastPage=new QPushButton();
    lastPage->setText(QStringLiteral("最后一页"));
    hl2->setAlignment(Qt::AlignHCenter);
    hl2->addWidget(firstPage);
    hl2->addWidget(nextPage);
    hl2->addWidget(prePage);
    hl2->addWidget(lastPage);
    ui->widget_3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    ui->verticalLayout_3->addWidget(ui->widget_2,0);
    ui->verticalLayout_3->addWidget(ui->tableView,1);
    ui->verticalLayout_3->addWidget(ui->widget_3,2);

    connect(this->addBase,SIGNAL(clicked()),this,SLOT(addBaseWin()));
    connect(this->deleteBase,SIGNAL(clicked()),this,SLOT(deleteBaseItem()));
    connect(this->freshBase,SIGNAL(clicked()),this,SLOT(freshBaseItem()));


}

JzWidget::~JzWidget()
{
    delete ui;
}



void JzWidget::setupModel(){

    BaseInfo query;
    QVector<BaseInfo> infos =  this->baseStationdao->getPageList(query);
    baseModel = new BaseModel(9, 8);
    baseModel->appendBaseInfos(infos);
}

 void JzWidget::addBaseWin(){
     addWin = new jizhan();
     addWin ->show();
     connect(addWin,SIGNAL(newBaseItem(BaseInfo&)),this,SLOT(addBaseItem(BaseInfo&)));
 }


 void JzWidget::addBaseItem(BaseInfo &info){

     this->baseStationdao->insert(info);
     //baseModel->AddBaseInfo(info);
     freshBaseItem();
 }

 void JzWidget::deleteBaseItem(){
     int count = baseModel->rowCount();
     int j = 0;
     for (int i = 0; i < count; ++i)
     {
         if (baseModel->rowCheckStateMap[i]==Qt::Checked)
         {
             BaseInfo info = baseModel->getBaseInfo().at(i-j);
             this->baseStationdao->deleteById(info.GetbaseID().toInt());
             baseModel->removeRow(i-j);
             j++;
         }
     }
     freshBaseItem();
}


 void JzWidget::freshBaseItem(){
     for(int i = 0;i < baseModel->rowCount();i++){
              QModelIndex index = baseModel->index(i,8,QModelIndex());
              baseModel->setData(index,Qt::Unchecked,Qt::CheckStateRole);
     }
     BaseInfo query;
     QVector<BaseInfo> infos =  this->baseStationdao->getPageList(query);
     baseModel->appendBaseInfos(infos);
     baseModel->freshModel();
 }






