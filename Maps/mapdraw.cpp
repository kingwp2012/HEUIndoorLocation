#include "mapdraw.h"
#include "ui_mapdraw.h"

MapDraw::MapDraw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapDraw)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);


    //paint->setMinimumSize(1000,600);
    int width=this->width();
    int height= this->height();

//    scene=new QGraphicsScene;
//    view =new QGraphicsView;
//  //  view->setMinimumSize(1100,700);
//    view->setScene(scene);
//    scene->setSceneRect(-width/2, -height/2, width, height);
//    view->show();

   // QToolBar *shapeBar = this->addToolBar("Shape");

    QToolBar *shapeBar= new QToolBar("Shape");
    shapeBar->setAllowedAreas(Qt::LeftToolBarArea);
    QActionGroup *shapeGroup = new QActionGroup(shapeBar);

    QAction *act_rect = new QAction(QIcon(":res/Rect.ico"),"Draw a Rect", shapeBar);
    act_rect->setCheckable(true);
    act_rect->setChecked(true);
    shapeGroup->addAction(act_rect);
    shapeBar->addAction(act_rect);

    QAction *act_line = new QAction(QIcon(":res/Line.ico"),"Draw A Line", shapeBar);
    act_line->setCheckable(true);
    shapeGroup->addAction(act_line);
    shapeBar->addAction(act_line);

    QAction *act_pen = new QAction(QIcon(":res/pen.ico"), "Draw With Pen", shapeBar);
    act_pen->setCheckable(true);
    shapeGroup->addAction(act_pen);
    shapeBar->addAction(act_pen);

    QAction *act_ellipse = new QAction(QIcon(":res/Ellipse.ico"), "Draw A Ellipse", shapeBar);
    act_ellipse->setCheckable(true);
    shapeGroup->addAction(act_ellipse);
    shapeBar->addAction(act_ellipse);

    QAction *act_polygon = new QAction(QIcon(":res/Polygon.ico"), "Draw A Polygon", shapeBar);
    act_polygon->setCheckable(true);
    shapeGroup->addAction(act_polygon);
    shapeBar->addAction(act_polygon);

   // shapeBar->setAllowedAreas(Qt::LeftToolBarArea);
    this->addToolBar(shapeBar);

  //  ////////操作选择框架///////////

    QToolBar *operatorBar= new QToolBar("Operator");
    operatorBar->setAllowedAreas(Qt::LeftToolBarArea);


    QActionGroup *operatorGroup = new QActionGroup(operatorBar);
    QAction *Undo = new QAction(QIcon(":/new/images/undo.png"), "Undo", operatorBar);
    Undo->setShortcut(tr("Ctrl+Z"));
    operatorGroup->addAction(Undo);
    operatorBar->addAction(Undo);

    QAction *Redo = new QAction(QIcon(":/new/images/redo.png"), "Redo", operatorBar);
    Redo->setShortcut(tr("Ctrl+Y"));
    operatorGroup->addAction(Redo);
    operatorBar->addAction(Redo);

    QAction *Reset = new QAction(QIcon(":/new/images/reset.png"), "Reset", operatorBar);
    Reset->setShortcut(tr("Ctrl+N"));
    operatorGroup->addAction(Reset);
    operatorBar->addAction(Reset);

    widthDial = new QDial(operatorBar);
    widthDial->setRange(1, 20);
    operatorBar->addWidget(widthDial);
    widthLabel = new QLabel("Size: 1", operatorBar);
    operatorBar->addWidget(widthLabel);

    alphaDial = new QDial(operatorBar);
    alphaDial->setRange(0, 100);
    alphaDial->setValue(100);
    operatorBar->addWidget(alphaDial);
    alphaLabel = new QLabel("Alpha: 100%", operatorBar);
    operatorBar->addWidget(alphaLabel);

//    QWidget *setbackground= new QWidget();
//    QHBoxLayout *h1= new QHBoxLayout();
//    setbackground->setLayout(h1);


    l1=new QLabel(operatorBar);
    l1->setText(QStringLiteral("背景选择"));
    operatorBar->addWidget(l1);


    box1=new QComboBox(operatorBar);
    box1->addItem(tr("SolidPattern"),static_cast<int>(Qt::SolidPattern));
    box1->addItem(tr("Dense1Pattern"),static_cast<int>(Qt::Dense1Pattern));
    box1->addItem(tr("Dense2Pattern"),static_cast<int>(Qt::Dense2Pattern));
    box1->addItem(tr("Dense3Pattern"),static_cast<int>(Qt::Dense3Pattern));
    box1->addItem(tr("Dense4Pattern"),static_cast<int>(Qt::Dense4Pattern));
    box1->addItem(tr("Dense5Pattern"),static_cast<int>(Qt::Dense5Pattern));
    box1->addItem(tr("Dense6Pattern"),static_cast<int>(Qt::Dense6Pattern));
    box1->addItem(tr("Dense7Pattern"),static_cast<int>(Qt::Dense7Pattern));
    box1->addItem(tr("HorPattern"),static_cast<int>(Qt::HorPattern));
    box1->addItem(tr("VerPattern"),static_cast<int>(Qt::VerPattern));
    box1->addItem(tr("CrossPattern"),static_cast<int>(Qt::CrossPattern));
    box1->addItem(tr("BDiagPattern"),static_cast<int>(Qt::BDiagPattern));
    box1->addItem(tr("FDiagPattern"),static_cast<int>(Qt::FDiagPattern));
    box1->addItem(tr("DiagCrossPattern"),static_cast<int>(Qt:: DiagCrossPattern));
    connect(box1,SIGNAL(activated(int)),this,SLOT(background_SLOT(int)));

    operatorBar->addWidget(box1);
    brushColorFrame= new QFrame(operatorBar);
    brushColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    brushColorFrame->setAutoFillBackground(true);
    brushColorFrame->setPalette(QPalette(Qt::green));
    brushColorBtn = new QPushButton(operatorBar);
    brushColorBtn->setText(QStringLiteral("颜色选择"));
    connect(brushColorBtn,SIGNAL(clicked()),this,SLOT (ShowBrushColor()));
    operatorBar->addWidget(brushColorFrame);
    operatorBar->addWidget(brushColorBtn);
//    h1->addWidget(l1);
//    h1->addWidget(box1);

    this->addToolBar(operatorBar);

   // operatorBar->setAllowedAreas(Qt::LeftToolBarArea);
    paint=new PaintArea;
    setCentralWidget(paint);
//    view->setMaximumSize(1100,600);
//    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   // scene->addWidget(paint);
//    paint->setMaximumSize(1100,900);
//    paint->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   // setCentralWidget(paint);



// 缩放滑动条区域以及窗口布局
    zoom = 50;

    QSlider *slider = new QSlider;
    slider->setOrientation(Qt::Vertical);
    slider->setRange(1,100);
    slider->setTickInterval(10);
    slider->setValue(50);
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(slotZoom(int)));

    QLabel *zoominLabel = new QLabel;
    zoominLabel->setScaledContents(true);
    zoominLabel->setPixmap(QPixmap("zoomin.png"));

    QLabel *zoomoutLabel = new QLabel;
    zoomoutLabel->setScaledContents(true);
    zoomoutLabel->setPixmap(QPixmap("zoomout.png"));





    ////////////菜单区域////////////////
    QMenu *file = menuBar()->addMenu(tr("&File"));
    QAction *newFile = new QAction(QIcon(":/new/images/reset.png"),tr("New"), file);
    newFile->setShortcut(tr("Ctrl+N"));
    file->addAction(newFile);
    QAction *openFile = new QAction(QIcon(":/new/images/reset.png"),tr("Open"), file);
    openFile->setShortcut(tr("Ctrl+O"));
    file->addAction(openFile);
    QAction *saveFile = new QAction(QIcon(":/new/images/reset.png"),tr("Save"), file);
    saveFile->setShortcut(tr("Ctrl+S"));
    file->addAction(saveFile);
    QAction *saveAsFile = new QAction(QIcon(":/new/images/reset.png"),tr("Save As"), file);
    saveAsFile->setShortcut(tr("Ctrl+Alt+S"));
    file->addAction(saveAsFile);
    QAction *quit = new QAction(QIcon(":/new/images/reset.png"),tr("Quit"), file);
    quit->setShortcut(tr("Ctrl+Q"));
    file->addAction(quit);

    QMenu *change = menuBar()->addMenu(tr("&Change"));
    QAction *changeColor = new QAction(QIcon(":/new/images/reset.png"),tr("Color"), change);
    changeColor->setShortcut(tr("Ctrl+C"));
    change->addAction(changeColor);
    QAction *changeBrush = new QAction(QIcon(":/new/images/reset.png"),tr("Brush"), change);
    changeBrush->setShortcut(tr("Ctrl+B"));
    change->addAction(changeBrush);
    QAction *changeWidth = new QAction(QIcon(":/new/images/reset.png"),tr("Width"), change);
    changeWidth->setShortcut(tr("Ctrl+W"));
    change->addAction(changeWidth);

//    QMenu *background =menuBar()->addMenu(tr("&Background"));
//    QAction *changebackground=new QAction(QIcon(":/new/images/reset.png"),tr("background"),background);


    //缩放控制子布局
    QVBoxLayout *zoomLayout = new QVBoxLayout;
    zoomLayout->addWidget(zoominLabel);
    zoomLayout->addWidget(slider);
    zoomLayout->addWidget(zoomoutLabel);

//    //主布局
//    QHBoxLayout *toollayout =new QHBoxLayout;
//    QHBoxLayout *menulayout =new QHBoxLayout;
//    menulayout->addWidget(file);
//    menulayout->addWidget(change);
//    toollayout -> addWidget(shapeBar);
//    toollayout->addWidget(operatorBar);
//    QHBoxLayout *paintlayout =new QHBoxLayout;
//    paintlayout->addLayout(zoomLayout);
//    paintlayout->addWidget(view);
//    view->setMaximumSize(1100,700);
//    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      QHBoxLayout *mainLayout = new QHBoxLayout;

   //    mainLayout->addLayout(menulayout);
//    mainLayout->addLayout(toollayout);
    mainLayout->addLayout(zoomLayout);
//    mainLayout->addLayout(paintlayout);
// //   mainLayout->addLayout(coordLayout);
    mainLayout->addStretch();
    mainLayout->setMargin(30);
    mainLayout->setSpacing(10);
//   // mainLayout->addWidget(view);
//  //  mainLayout->addWidget(paint);
    this->setLayout(mainLayout);
   // mainlayout
    mainLayout->addWidget(view);

    //pushbutton1=new QPushButton();
   // pushbutton1->setText(QStringLiteral("哈哈哈哈哈"));
    //pushbutton1->setFixedSize(200,200);
    //mainLayout->addWidget(pushbutton1);



  //  connect(slider,SIGNAL(valueChanged(int)),this,SLOT(slotZoom(int)));




    ////////////paintarea定义////////////


    ////////工具栏信号槽//////////////////
    QObject::connect(act_rect, SIGNAL(triggered()), this, SLOT(draw_rect()));
    QObject::connect(act_line, SIGNAL(triggered()), this, SLOT(draw_line()));
    QObject::connect(act_pen, SIGNAL(triggered()), this, SLOT(draw_pen()));
    QObject::connect(act_polygon, SIGNAL(triggered()), this, SLOT(draw_polygon()));
    QObject::connect(act_ellipse, SIGNAL(triggered()), this, SLOT(draw_ellipse()));
    QObject::connect(Undo, SIGNAL(triggered()), paint, SLOT(Undo()));
    QObject::connect(Redo, SIGNAL(triggered()), paint, SLOT(Redo()));
    QObject::connect(Reset, SIGNAL(triggered()), paint, SLOT(Reset()));
    QObject::connect(Reset, SIGNAL(triggered()), this, SLOT(reset_dial()));
    QObject::connect(widthDial, SIGNAL(valueChanged(int)), paint, SLOT(set_width(int)));
    QObject::connect(widthDial, SIGNAL(valueChanged(int)), this, SLOT(change_widthLabel(int)));
    QObject::connect(alphaDial, SIGNAL(valueChanged(int)), paint, SLOT(set_alpha(int)));
    QObject::connect(alphaDial, SIGNAL(valueChanged(int)), this, SLOT(change_alphaLabel(int)));

    ////////菜单栏信号槽//////////////////
    QObject::connect(newFile, SIGNAL(triggered()), paint, SLOT(Reset()));
    QObject::connect(openFile, SIGNAL(triggered()), paint, SLOT(open_file()));
    QObject::connect(saveFile, SIGNAL(triggered()), paint, SLOT(save_file()));
    QObject::connect(saveAsFile, SIGNAL(triggered()), paint, SLOT(saveAs_file()));
    QObject::connect(quit, SIGNAL(triggered()),this, SLOT(close()));
    QObject::connect(changeColor, SIGNAL(triggered()), this, SLOT(color_SLOT()));
    QObject::connect(changeBrush, SIGNAL(triggered()), this, SLOT(brush_SLOT()));
    QObject::connect(changeWidth, SIGNAL(triggered()), this, SLOT(width_SLOT()));

  //  QObject::connect(changebackground, SIGNAL(triggered()), this, SLOT(background_SLOT()));
    /////////Paint交互信号槽///////////////////
    QObject::connect(this, SIGNAL(select_shape(type)), paint, SLOT(set_shape(type)));
    QObject::connect(this, SIGNAL(color_change(QColor)), paint, SLOT(set_color(QColor)));
    QObject::connect(this, SIGNAL(brush_change(QColor)), paint, SLOT(set_brush(QColor)));
    QObject::connect(this, SIGNAL(width_change(int)), paint, SLOT(set_width(int)));
    QObject::connect(this, SIGNAL(change_straight(bool)), paint, SLOT(set_straight(bool)));
}

MapDraw::~MapDraw()
{
    delete ui;
}


void MapDraw::slotZoom(int value)   	//地图缩放
{
    qreal s;
    if(value>zoom)                 		//放大
    {
        s=pow(1.01,(value-zoom));
    }
    else                             	//缩小
    {
        s=pow(1/1.01,(zoom-value));
    }
    view->scale(s,s);
    //scale(s,s);
    zoom = value;
}

void MapDraw::keyPressEvent(QKeyEvent *k)
{
    if (k->modifiers() == Qt::ShiftModifier)
    {
        emit change_straight(true);
    }
}

void MapDraw::keyReleaseEvent(QKeyEvent *k)
{
    if (k->key() == Qt::Key_Shift)
    {
       emit change_straight(false);
    }
}

void MapDraw::color_SLOT()
{
    QColor c = QColorDialog::getColor(Qt::black);
    emit color_change(c);
}

void MapDraw::brush_SLOT()
{
    QColor c = QColorDialog::getColor(Qt::transparent);
    emit brush_change(c);
}

void MapDraw::width_SLOT()
{
    int c = QInputDialog::getInt(this, tr("Width Set"), tr("Enter the Width"), true, 1, 20, 1);
    emit width_change(c);
}

void MapDraw::ShowBrushColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::blue));
    brushColorFrame->setPalette(QPalette(color));
    background_SLOT(box1->currentIndex());
}

void MapDraw::background_SLOT(int value)
{
    QColor color = brushColorFrame->palette().color(QPalette::Window);
    Qt::BrushStyle style = Qt::BrushStyle(box1->itemData(value,Qt::UserRole).toInt());
    paint->setBrush(QBrush(color,style));
}

void MapDraw::draw_rect()
{
    emit select_shape(type_Rect);
}
void MapDraw::draw_line()
{
    emit select_shape(type_Line);
}
void MapDraw::draw_pen()
{
    emit select_shape(type_Pen);
}
void MapDraw::draw_polygon()
{
    emit select_shape(type_Polygon);
}
void MapDraw::draw_ellipse()
{
    emit select_shape(type_Ellipse);
}
///////////////////槽函数////////////////
void MapDraw::change_widthLabel(int w)
{
    widthLabel->setText("Size: " + QString::number(w));
}

void MapDraw::change_alphaLabel(int w)
{
    alphaLabel->setText("Alpha: " + QString::number(w) + "%");
}

void MapDraw::reset_dial()
{
    widthDial->setValue(1);
    alphaDial->setValue(100);
    widthLabel->setText("Size: 1");
    alphaLabel->setText("Alpha: 100%");
}

QSize MapDraw::sizeHint() const
{
    return QSize(1024, 768);
}

