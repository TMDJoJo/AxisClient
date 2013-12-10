#include "MainWindow.h"
#include <QVBoxLayout>
#include <QStringList>
#include <QIcon>
#include <QToolButton>
#include <QGridLayout>

#include "./AxisBaseWidget/Common.h"
#include "./WorkScene/WelcomeScene.h"
#include "./WorkScene/TestWorkScene.h"


#define SHADOW_WIDTH        5
#define RESIZE_WIDTH_MIN    0
#define RESIZE_WIDTH_MAX    SHADOW_WIDTH

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    tray_(NULL),
    tray_menu_(NULL),
    animation_(NULL),
    grid_layout_(NULL),
    logo_(NULL),
    main_window_title_(NULL),
    navigation_(NULL),
    stacked_widget_(NULL)
{
    setWindowTitle(tr("AXIS自动化运营平台V0-02-0010"));

    InitUi();
    InitTitle();
    InitTray();
    InitWorkScene();
}

MainWindow::~MainWindow()
{
    SAFE_DELETE(animation_);
    SAFE_DELETE(tray_);
    SAFE_DELETE(tray_menu_);
    SAFE_DELETE(stacked_widget_);
    SAFE_DELETE(main_window_title_);
    SAFE_DELETE(logo_);
    SAFE_DELETE(grid_layout_);
}

void MainWindow::InitUi(){

    ////设置窗体标题栏隐藏并设置位于顶层
    setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(false);

    ////TODO: XP下启用一下属性后会失去焦点，客户端出现卡死现象
    ////https://bugreports.qt-project.org/browse/QTBUG-17548
    ////暂时采用void MainWindow::showEvent(QShowEvent* event)中调用一次repaint()解决
    this->setAttribute(Qt::WA_TranslucentBackground,true);

    grid_layout_ = new QGridLayout();
    Q_ASSERT(grid_layout_);
    grid_layout_->setSpacing(0);
    grid_layout_->setContentsMargins(SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH);

    main_window_title_ = new QWidget();
    Q_ASSERT(main_window_title_);
    main_window_title_->setObjectName("main_window_title");
    main_window_title_->setMinimumSize(QSize(0, 20));
    main_window_title_->setMaximumSize(QSize(16777215, 20));

    logo_ = new LogoScene();
    Q_ASSERT(logo_);
    logo_->setObjectName("main_scene_logo");
    logo_->setMinimumSize(QSize(0, 100));
    logo_->setMaximumSize(QSize(16777215, 100));
    logo_->Init(this);

    navigation_ = new Navigation();
    Q_ASSERT(navigation_);
    navigation_->setObjectName("navigation");
    navigation_->setMinimumSize(QSize(250, 0));
    navigation_->setMaximumSize(QSize(250, 16777215));
    navigation_->Init(this);

    stacked_widget_ = new QStackedWidget();
    Q_ASSERT(stacked_widget_);
    stacked_widget_->setObjectName("main_stacked_widget");

    grid_layout_->addWidget(main_window_title_,0,0,1,2);
    grid_layout_->addWidget(logo_,1,0,1,1);
    grid_layout_->addWidget(navigation_,2,0,1,1);
    grid_layout_->addWidget(stacked_widget_,1,1,2,1);
    this->setLayout(grid_layout_);

    animation_ = new QPropertyAnimation(this,"windowOpacity");
    Q_ASSERT(animation_);
    animation_->setDuration(400);
    animation_->setStartValue(0);
    animation_->setEndValue(1);

}

void MainWindow::paintEvent(QPaintEvent*){

    QPainter p(this);

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    if(this->width() > 2*SHADOW_WIDTH && this->height() >  2*SHADOW_WIDTH)
        drawWindowShadow(p);
////设置对话框圆角
//    p.setPen(Qt::NoPen);
//    p.setBrush(Qt::white);
//    p.drawRoundedRect(QRect(RESIZE_WIDTH_MIN,RESIZE_WIDTH_MIN,
//                            this->width() - 2*RESIZE_WIDTH_MIN,this->height() - 2*RESIZE_WIDTH_MIN),
//                      2.0f,2.0f);
}

void MainWindow::drawWindowShadow(QPainter &p)
{
    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_left.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_right.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_top.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_bottom.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_corner1.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_corner2.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_corner3.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_corner4.png"));

    p.drawPixmap(0,0,SHADOW_WIDTH,SHADOW_WIDTH,pixmaps[4]);
    p.drawPixmap(this->width() - SHADOW_WIDTH,0,SHADOW_WIDTH,SHADOW_WIDTH,pixmaps[5]);
    p.drawPixmap(0,this->height() - SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH,pixmaps[6]);
    p.drawPixmap(this->width() - SHADOW_WIDTH,this->height() - SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH,pixmaps[7]);

    p.drawPixmap(0,SHADOW_WIDTH,SHADOW_WIDTH,this->height() - 2*SHADOW_WIDTH,pixmaps[0].scaled(SHADOW_WIDTH,this->height() - 2*SHADOW_WIDTH));
    p.drawPixmap(this->width() - SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH,this->height() - 2*SHADOW_WIDTH,pixmaps[1].scaled(SHADOW_WIDTH,this->height() - 2*SHADOW_WIDTH));
    p.drawPixmap(SHADOW_WIDTH,0,this->width() - 2*SHADOW_WIDTH,SHADOW_WIDTH,pixmaps[2].scaled(this->width() - 2*SHADOW_WIDTH,SHADOW_WIDTH));
    p.drawPixmap(SHADOW_WIDTH,this->height() - SHADOW_WIDTH,this->width() - 2*SHADOW_WIDTH,SHADOW_WIDTH,pixmaps[3].scaled(this->width() - 2*SHADOW_WIDTH,SHADOW_WIDTH));
}

void MainWindow::InitWorkScene(){

    ////设置导航栏
    QIcon icon(":/Navigation/Resource/Img/Navigation/button.png");
    QStringList list;
    list<<"emma"<<"karl"<<"jame"<<tr("你们");
    navigation_->addNavigationBar(tr("zc"),icon,list);
    navigation_->addNavigationBar(tr("zj"),icon,list);
    navigation_->addNavigationBar(tr("jk"),icon,list);

    WelcomeScene* welcome = new WelcomeScene("welcome");
    AddWorkScene("welcome",welcome);

    TestWorkScene* test1 = new TestWorkScene(tr("zc"));
    test1->SetText(tr("zc")+"emma");
    AddWorkScene(tr("zc"),test1);

    TestWorkScene* test2 = new TestWorkScene(tr("zc")+"karl");
    test2->SetText(tr("zc")+"karl");
    AddWorkScene(tr("zc")+"karl",test2);

    TestWorkScene* test3 = new TestWorkScene(tr("zc")+"jame");
    test3->SetText(tr("zc")+"jame");
    AddWorkScene(tr("zc")+"jame",test3);

    stacked_widget_->setCurrentIndex(0);
    navigation_->addVerticalSpacer();
}

void MainWindow::InitTitle(){

    QWidget* parent = main_window_title_;
    parent->setObjectName("main_window_title");
//    parent->setMaximumHeight(22);
//    parent->setMinimumHeight(22);
    QHBoxLayout *layout = new QHBoxLayout(parent);
    Q_ASSERT(layout);

    layout->addSpacerItem(new QSpacerItem(40,30,QSizePolicy::Expanding,QSizePolicy::Minimum));

    ////创建标题栏-点赞
    QToolButton* tool_button_praise = new QToolButton(parent);
    Q_ASSERT(tool_button_praise);
    tool_button_praise->setObjectName("main_tool_button_praise");
    tool_button_praise->setAutoRaise(true);
    connect(tool_button_praise,SIGNAL(clicked()),this,SLOT(Mail()));
    tool_button_praise->setToolTip(tr("赞一下我们吧"));
    layout->addWidget(tool_button_praise);

    ////创建标题栏-最小化
    QToolButton* tool_button_min = new QToolButton(parent);
    Q_ASSERT(tool_button_min);
    tool_button_min->setObjectName("main_tool_button_min");
    tool_button_min->setAutoRaise(true);
    connect(tool_button_min,SIGNAL(clicked()),this,SLOT(showMinimized()));
    layout->addWidget(tool_button_min);

    ////创建标题栏-最大化
    tool_button_max_ = new QToolButton(parent);
    Q_ASSERT(tool_button_max_);
    tool_button_max_->setObjectName("main_tool_button_max");
    tool_button_max_->setAutoRaise(true);
    connect(tool_button_max_,SIGNAL(clicked()),this,SLOT(MaxOrNormal()));
    layout->addWidget(tool_button_max_);

    ////创建标题栏-还原
    tool_button_normal_ = new QToolButton(parent);
    Q_ASSERT(tool_button_normal_);
    tool_button_normal_->setObjectName("main_tool_button_normal");
    tool_button_normal_->setAutoRaise(false);
    connect(tool_button_normal_,SIGNAL(clicked()),this,SLOT(MaxOrNormal()));
    layout->addWidget(tool_button_normal_);
    tool_button_normal_->hide();

    ////创建标题栏-退出
    QToolButton* tool_button_close = new QToolButton(parent);
    Q_ASSERT(tool_button_close);
    tool_button_close->setObjectName("main_tool_button_close");
    tool_button_close->setAutoRaise(true);
    connect(tool_button_close,SIGNAL(clicked()),this,SLOT(Close()));
    layout->addWidget(tool_button_close);

    layout->setSpacing(0);
    layout->setContentsMargins(6,0,0,0);
    parent->setLayout(layout);

}

void MainWindow::InitTray(){
    tray_ = new Tray(this);
    tray_menu_ = new TrayIconMenu(this);
    Q_ASSERT(tray_);
    Q_ASSERT(tray_menu_);

    tray_->SetMainWindow(this);
    tray_->setContextMenu(tray_menu_);
    tray_->setToolTip(tr("提示\n我是谁"));
    tray_->show();
    tray_->showMessage(tr("提示"),tr("不可思议之 我已启动！"),
                          QSystemTrayIcon::NoIcon,2000);
}

void MainWindow::ChangeWorkScene(const QString& workName){

    if( NULL == wrokScenes[workName]){
        qDebug()<<"no this work scene";
        return;
    }

    for(int index = 0;index < stacked_widget_->count();++index){
        IWorkScene* scene = static_cast<IWorkScene*>(stacked_widget_->widget(index));
        Q_ASSERT(scene);
        if(workName == scene->GetSceneName()){
            stacked_widget_->setCurrentIndex(index);

        }
    }

}

bool MainWindow::AddWorkScene(const QString& name,IWorkScene* scene){
    Q_ASSERT(scene);

    if(wrokScenes[name] != NULL){
        return false;
    }
    wrokScenes[name] = scene;

    return stacked_widget_->addWidget(scene) == 0;
}

void MainWindow::closeEvent(QCloseEvent *event){
    if (tray_->isVisible()) {
        hide();
        event->ignore();
        tray_->showMessage(tr("AXIS自动化运营平台"),tr("单击打开！"),
                              QSystemTrayIcon::NoIcon,1000);
    }
}

void MainWindow::showEvent(QShowEvent* event){

    animation_->start();

    QWidget::showEvent(event);
    repaint();
    return;
}

void MainWindow::Close(){
    this->close();
}

void MainWindow::Mail(){

    system("start outlook.exe /f ./Resource/mail/default.msg");
}

void MainWindow::MaxOrNormal(){
    if(this->isMaximized()){
        tool_button_normal_->hide();
        tool_button_max_->show();
        this->showNormal();
    }
    else{
        tool_button_max_->hide();
        tool_button_normal_->show();
        this->showMaximized();
    }
}

bool MainWindow::winEvent(MSG *message, long *result)
{
    if(this->isMaximized()){
        return false;
    }
    switch(message->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(message->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(message->lParam) - this->frameGeometry().y();
        if(this->childAt(xPos,yPos) == 0)
        {
            *result = HTCAPTION;
        }else{
            return false;
        }
        if(xPos >  RESIZE_WIDTH_MIN && xPos <  RESIZE_WIDTH_MAX)
            *result = HTLEFT;
        if(xPos > (this->width() - RESIZE_WIDTH_MAX) && xPos < (this->width() - RESIZE_WIDTH_MIN))
            *result = HTRIGHT;
        if(yPos > RESIZE_WIDTH_MIN && yPos < RESIZE_WIDTH_MAX)
            *result = HTTOP;
        if(yPos > (this->height() - RESIZE_WIDTH_MAX) && yPos < (this->height() - RESIZE_WIDTH_MIN))
            *result = HTBOTTOM;
        if(xPos > RESIZE_WIDTH_MIN && xPos < RESIZE_WIDTH_MAX && yPos > RESIZE_WIDTH_MIN && yPos < RESIZE_WIDTH_MAX)
            *result = HTTOPLEFT;
        if(xPos > (this->width() - RESIZE_WIDTH_MAX) && xPos < (this->width() - RESIZE_WIDTH_MIN) && yPos > RESIZE_WIDTH_MIN && yPos < RESIZE_WIDTH_MAX)
            *result = HTTOPRIGHT;
        if(xPos > RESIZE_WIDTH_MIN && xPos < RESIZE_WIDTH_MAX && yPos > (this->height() - RESIZE_WIDTH_MAX) && yPos < (this->height() - RESIZE_WIDTH_MIN))
            *result = HTBOTTOMLEFT;
        if(xPos > (this->width() - RESIZE_WIDTH_MAX) && xPos < (this->width() - RESIZE_WIDTH_MIN) && yPos > (this->height() - RESIZE_WIDTH_MAX) && yPos < (this->height() - RESIZE_WIDTH_MIN))
            *result = HTBOTTOMRIGHT;

        return true;
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    moveing_ = true;
    move_position_ = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(this->isMaximized())
        return QWidget::mouseMoveEvent(event);
    if (moveing_
        &&(event->buttons()
        &&Qt::LeftButton)
        &&(event->globalPos()-move_position_).manhattanLength() > QApplication::startDragDistance()
        ){
        move(event->globalPos()-move_position_);
        move_position_ = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //设置鼠标为未被按下
    moveing_ = false;
    event->accept();
}
