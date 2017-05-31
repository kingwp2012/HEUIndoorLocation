#include "main_widget.h"
#include "util.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
main_widget::main_widget(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(900, 600);
    setWindowIcon(QIcon(":/new/images/account.png"));
    setWindowFlags(Qt::FramelessWindowHint);
    location = this->geometry();

    bool is_read = Util::readInit(QString("./user.ini"), QString("new/skin"), skin_name);
    if(is_read)
    {
        if(skin_name.isEmpty())
        {
            skin_name = QString(":new/skin/17_big");
        }
    }
    else
    {
        skin_name = QString(":new/skin/17_big");
    }



    title_widget = new  titlewidget();
    content_widget = new contentwidget();
    jzwidget = new JzWidget();
    bqwidget = new BqWidget();
    kqwidget = new KqWidget();
    truebqwidget= new TrueBqWidget();
    mapwidget=new Mapwidget();
    warningwidget = new warningWidget();
   // main_menu = new MainMenu();
  //  character_widget = new CharacterWidget();
  //  about_us_dialog = new AboutUsDialog(this);
  //  setting_dialog = new SettingDialog(this);
  //  skin_widget = new SkinWidget(this);
//    system_tray = new SystemTray(this);
//
    QVBoxLayout *center_layout = new QVBoxLayout();
    center_layout->addWidget(content_widget);


    center_layout->addWidget(bqwidget);
    center_layout->addWidget(jzwidget);
    center_layout->addWidget(kqwidget);
    center_layout->addWidget(truebqwidget);
    center_layout->addWidget(mapwidget);

    bqwidget->hide();
    jzwidget->hide();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->hide();

    center_layout->setSpacing(0);
    center_layout->setContentsMargins(1, 0, 1, 1);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_widget);
    main_layout->addLayout(center_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);

  //  connect(title_widget, SIGNAL(showSkin()), this, SLOT(showSkinWidget()));
    connect(title_widget, SIGNAL(showMainMenu()), this, SLOT(showMainMenu()));
    connect(title_widget, SIGNAL(showMax()), this, SLOT(showMax()));
    connect(title_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(title_widget, SIGNAL(showWarnings()), this, SLOT(showWarnings()));

    connect(title_widget, SIGNAL(closeWidget()), this, SLOT(hide()));
    connect(title_widget, SIGNAL(showJzwidget()), this, SLOT(showJzwidget()));
    connect(title_widget, SIGNAL(showBqwidget()), this, SLOT(showBqwidget()));
    connect(title_widget, SIGNAL(showKqwidget()), this, SLOT(showKqwidget()));
    connect(title_widget, SIGNAL(showTrueBqwidget()), this, SLOT(showTrueBqwidget()));
    connect(title_widget, SIGNAL(showMapwidget()),this, SLOT(showMapwidget()));


  //  connect(main_menu, SIGNAL(showSettingDialog()), this, SLOT(showSettingDialog()));
  //  connect(main_menu, SIGNAL(showNewCharacter()), this, SLOT(showNewCharacter()));
  //  connect(main_menu, SIGNAL(showAboutUs()), this, SLOT(showAboutUs()));

  //  connect(skin_widget, SIGNAL(changeSkin(QString)), this, SLOT(changeSkin(QString)));

  //  connect(system_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));

   // system_tray->show();
}

main_widget::~main_widget()
{

}

void main_widget::paintEvent(QPaintEvent *)
{
    /*QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(skin_name);
    painter.drawPixmap(rect(), pixmap);*/

    /*QPainter painter(this);
    QPixmap pixmap(this->size());
    pixmap.fill();
    painter.end();
    painter.begin(&pixmap);
    QBrush brush;
    brush.setTextureImage(QImage(skin_name));
    painter.setBrush(brush);
    painter.setPen(Qt::gray);
    painter.drawRect(0, 0, this->width()-1, this->height()-1);
    painter.end();
    painter.begin(this);
    painter.drawPixmap(this->rect(),pixmap);*/

    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(skin_name));

    QPainter painter2(this);
    painter2.setPen(Qt::gray);
    static const QPointF points[4] = {QPointF(0, 100), QPointF(0, this->height()-1), QPointF(this->width()-1, this->height()-1), QPointF(this->width()-1, 100)};
    painter2.drawPolyline(points, 4);
}


void main_widget::showMax()
{
    static bool is_max=false;
    if(is_max)
    {
        this->setGeometry(location);
    }
    else
    {
        //获取当前界面的位置
        location = this->geometry();
        this->setGeometry(QApplication::desktop()->availableGeometry());
    }
    is_max = !is_max;
}

//void main_widget::showSkinWidget()
//{
//    skin_widget->show();
//}

//void main_widget::showMainMenu()
//{
//    //设置主菜单出现的位置
//    QPoint p = rect().topRight();
//    p.setX(p.x() - 150);
//    p.setY(p.y() + 22);
//    main_menu->exec(this->mapToGlobal(p));
//}

void main_widget::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    //点击托盘图标之后松开
    case QSystemTrayIcon::Trigger:
    {
        showWidget();
        break;
    }
        //双击托盘图标
    case QSystemTrayIcon::DoubleClick:
    {
        showWidget();
        break;
    }
    default:
        break;
    }
}

void main_widget::showWidget()
{
    this->showNormal();
    this->raise();
    this->activateWindow();
    title_widget->turnPage(0);
}

//void main_widget::showAboutUs()
//{
//    about_us_dialog->exec();
//}

//void main_widget::showNewCharacter()
//{
//    character_widget->show();
//}

//void main_widget::showSettingDialog()
//{
//    setting_dialog->exec();
//}

void main_widget::changeSkin(QString skin_name)
{
    Util::writeInit(QString("./user.ini"), QString("/new/skin"), skin_name);
    this->skin_name = skin_name;
    update();
}


void main_widget::showWarnings(){
    warningwidget->show();
}

void main_widget::showJzwidget()
{
    content_widget->hide();
    jzwidget->show();
    bqwidget->hide();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->hide();
}

void main_widget::showBqwidget()
{
    content_widget->hide();
    jzwidget->hide();
    bqwidget->show();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->hide();
}
void main_widget::showKqwidget()
{
    content_widget->hide();
    jzwidget->hide();
    bqwidget->hide();
    kqwidget->show();
    truebqwidget->hide();
    mapwidget->hide();

}
void main_widget::showTrueBqwidget()
{
    content_widget->hide();
    jzwidget->hide();
    bqwidget->hide();
    kqwidget->hide();
    truebqwidget->show();
    mapwidget->hide();
}
void main_widget:: showMapwidget()
{
    content_widget->hide();
    jzwidget->hide();
    bqwidget->hide();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->show();

}




