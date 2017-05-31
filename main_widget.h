#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H
//#include "../about_us/about_us.h"
//#include "../main_menu/main_menu.h"
//#include "../skin_widget/skin_widget.h"
//#include "../system_tray/system_tray.h"
#include"titlewidget.h"
#include"basestation/jzwidget.h"
#include"camera/bqwidget.h"
#include"attence/kqwidget.h"
#include"label/truebqwidget.h"
#include "Maps/mapwidget.h"
#include"warningwidget.h"
//#include "../setting_dialog/setting_dialog.h"
#include "contentwidget.h"
//#include "../character_widget/character_widget.h"
#include <QSystemTrayIcon>
#include <QWidget>


namespace Ui {
class main_widget;
}
class main_widget : public QWidget
{
    Q_OBJECT

public:
    explicit main_widget(QWidget *parent = 0);
    ~main_widget();


protected:
    void paintEvent(QPaintEvent *);

public slots:
    void showWidget();

private slots:
    void showMax();
    void showJzwidget();
    void showBqwidget();// carema manage
    void showKqwidget();
    void showTrueBqwidget();//label manage
    void showWarnings(); //显示警告窗口
    void showMapwidget();
  //  void closejizhan();
   // void showSkinWidget();
    //void showMainMenu();
  //  void showSettingDialog();
 //   void showAboutUs();
  //  void showNewCharacter();
    void changeSkin(QString skin_name);
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);


private:
    Ui::main_widget *ui;
    QRect location;
    titlewidget *title_widget; //标题栏
    contentwidget *content_widget; //主界面内容
    JzWidget *jzwidget;
    BqWidget *bqwidget;
    KqWidget *kqwidget;
    TrueBqWidget *truebqwidget;
    warningWidget *warningwidget; //警告窗口
    Mapwidget *mapwidget;

   // SystemTray *system_tray; //托盘项
   // SettingDialog *setting_dialog; //设置界面
   // CharacterWidget *character_widget; //新版特性界面
 //   AboutUsDialog *about_us_dialog; //关于我们界面
     QString skin_name;//主窗口背景图片的名称
//    MainMenu *main_menu; //主菜单
  //  SkinWidget *skin_widget; //显示皮肤界面
};

#endif // MAIN_WIDGET_H





