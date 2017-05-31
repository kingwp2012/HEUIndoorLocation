#include "mapwidget.h"
#include "ui_mapwidget.h"


Mapwidget::Mapwidget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Mapwidget)
 {
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);


   //setupModel();

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
    checkmap=new QPushButton();
    checkmap->setText(QStringLiteral("查看地图"));
    createmap=new QPushButton();
    createmap->setText(QStringLiteral("创建地图"));
    deletemap=new QPushButton();
    deletemap->setText(QStringLiteral("删除地图"));
    hl1->setAlignment(Qt::AlignLeft);
    hl1->addWidget(createmap);
    hl1->addWidget(deletemap);
    hl1->addWidget(checkmap);
    ui->widget_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

   // //////////////////tableview
    ui->tableView->setMaximumSize(1100,500);
    ui->tableView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
   // ui->tableView->setModel(baseModel);
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


    connect(createmap,SIGNAL(clicked()),this,SLOT(drawmap_show()));


}


Mapwidget::~Mapwidget()
{
    delete ui;
}


void Mapwidget :: drawmap_show()
{
    mapdraw = new MapDraw();
    mapdraw->show();

}
