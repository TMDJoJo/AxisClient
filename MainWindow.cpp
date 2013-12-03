#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QVBoxLayout>
#include <QStringList>
#include <QIcon>
#include <QToolButton>

#include "./WorkScene/WelcomeScene.h"
#include "./WorkScene/TestWorkScene.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    tray(NULL),
    trayMenu(NULL),
    animation_(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("AXIS自动化运营平台V0-02-0010"));

    ui->navigation->Init(this);
    ui->logo->Init(this);

    this->setAutoFillBackground(true);

    InitTray();
    InitView();
    InitTitle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*){

    QPainter p(this);
//    QStyleOption opt;
//    opt.init(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
qDebug()<<"a";
    if(this->width() > 45 && this->height() > 45)
        drawWindowShadow(p);

    p.setPen(Qt::NoPen);
    p.setBrush(Qt::white);
    p.drawRoundedRect(QRect(18,18,this->width() - 36,this->height() - 36),2.0f,2.0f);

}

void MainWindow::drawWindowShadow(QPainter &p)
{
    qDebug()<<"l";
    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_left.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_right.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_top.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_bottom.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_corner1.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_corner2.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_corner3.png"));
    pixmaps.append(QPixmap(":/MainScene/Resource/Img/MainScene/shadow_corner4.png"));

    p.drawPixmap(0,0,20,20,pixmaps[4]);
    p.drawPixmap(this->width() - 20,0,20,20,pixmaps[5]);
    p.drawPixmap(0,this->height() - 20,20,20,pixmaps[6]);
    p.drawPixmap(this->width() - 20,this->height() - 20,20,20,pixmaps[7]);

    p.drawPixmap(0,20,20,this->height() - 40,pixmaps[0].scaled(20,this->height() - 40));
    p.drawPixmap(this->width() - 20,20,20,this->height() - 40,pixmaps[1].scaled(20,this->height() - 40));
    p.drawPixmap(20,0,this->width() - 40,20,pixmaps[2].scaled(this->width() - 40,20));
    p.drawPixmap(20,this->height() - 20,this->width() - 40,20,pixmaps[3].scaled(this->width() - 40,20));
}

void MainWindow::InitView(){

    ////设置窗体标题栏隐藏并设置位于顶层
    setWindowFlags(Qt::FramelessWindowHint);

    ////设置导航栏
    QIcon icon(":/Navigation/Resource/Img/Navigation/button.png");
    QStringList list;
    list<<"emma"<<"karl"<<"jame"<<tr("你们");
    ui->navigation->addNavigationBar(tr("资产"),icon,list);
    ui->navigation->addNavigationBar(tr("装机"),icon,list);
    ui->navigation->addNavigationBar(tr("监控"),icon,list);

    WelcomeScene* welcome = new WelcomeScene("welcome");
    AddWorkScene("welcome",welcome);

    TestWorkScene* test1 = new TestWorkScene(tr("资产"));
    test1->SetText(tr("资产")+"emma");
    AddWorkScene(tr("资产"),test1);

    TestWorkScene* test2 = new TestWorkScene(tr("资产")+"karl");
    test2->SetText(tr("资产")+"karl");
    AddWorkScene(tr("资产")+"karl",test2);

    TestWorkScene* test3 = new TestWorkScene(tr("资产")+"jame");
    test3->SetText(tr("资产")+"jame");
    AddWorkScene(tr("资产")+"jame",test3);

    ui->stackedWidget->setCurrentIndex(0);
    ui->navigation->addVerticalSpacer();
}

void MainWindow::InitTitle(){

    QWidget* parent = ui->main_window_title;
    parent->setObjectName("main_window_title");
    parent->setMaximumHeight(20);
    parent->setMinimumHeight(20);
    QHBoxLayout *layout = new QHBoxLayout(parent);
    Q_ASSERT(layout);

    layout->addSpacerItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum));

    ////创建标题栏-设置
    QToolButton* tool_button_set = new QToolButton(parent);
    Q_ASSERT(tool_button_set);
    tool_button_set->setObjectName("main_tool_button_set");
    tool_button_set->setAutoRaise(true);
    //connect(tool_button_set,SIGNAL(clicked()),this,SLOT(doToolButtonSet()));
    layout->addWidget(tool_button_set);

    ////创建标题栏-最小化
    QToolButton* tool_button_min = new QToolButton(parent);
    Q_ASSERT(tool_button_min);
    tool_button_min->setObjectName("main_tool_button_min");
    tool_button_min->setAutoRaise(true);
    connect(tool_button_min,SIGNAL(clicked()),this,SLOT(showMinimized()));
    layout->addWidget(tool_button_min);

    ////创建标题栏-推出
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
    tray = new Tray(this);
    trayMenu = new TrayIconMenu(this);
    Q_ASSERT(tray);
    Q_ASSERT(trayMenu);

    tray->SetMainWindow(this);
    tray->setContextMenu(trayMenu);
    tray->show();
    tray->showMessage(tr("AXIS自动化运营平台"),tr("不可思议之 AXIS 已启动！"),
                          QSystemTrayIcon::NoIcon,2000);
}

void MainWindow::ChangeWorkScene(const QString& workName){

    if( NULL == wrokScenes[workName]){
        qDebug()<<"no this work scene";
        return;
    }

    for(int index = 0;index < ui->stackedWidget->count();++index){
        IWorkScene* scene = static_cast<IWorkScene*>(ui->stackedWidget->widget(index));
        Q_ASSERT(scene);
        if(workName == scene->GetSceneName()){
            ui->stackedWidget->setCurrentIndex(index);

        }
    }

}

bool MainWindow::AddWorkScene(const QString& name,IWorkScene* scene){
    Q_ASSERT(scene);

    if(wrokScenes[name] != NULL){
        return false;
    }
    wrokScenes[name] = scene;

    return ui->stackedWidget->addWidget(scene) == 0;
}

void MainWindow::closeEvent(QCloseEvent *event){
    if (tray->isVisible()) {
        hide();
        event->ignore();
    }
}

void MainWindow::showEvent(QShowEvent* event){
    animation_ = new QPropertyAnimation(this,"windowOpacity");
    Q_ASSERT(animation_);
    animation_->setDuration(400);
    animation_->setStartValue(0);
    animation_->setEndValue(1);
    animation_->start();
//    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
//    animation->setDuration(300);
//    animation->setStartValue(QRect(this->pos().x()+1050*0.2,this->pos().y()+600*0.2,1050*0.4,600*0.4));
//    animation->setEndValue(QRect(this->pos().x(),this->pos().y(), 1050, 600));
//    animation->start();

    event->ignore();
}

void MainWindow::Close(){
    this->close();
}

bool MainWindow::winEvent(MSG *message, long *result)
{
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
        if(xPos > 18 && xPos < 22)
            *result = HTLEFT;
        if(xPos > (this->width() - 22) && xPos < (this->width() - 18))
            *result = HTRIGHT;
        if(yPos > 18 && yPos < 22)
            *result = HTTOP;
        if(yPos > (this->height() - 22) && yPos < (this->height() - 18))
            *result = HTBOTTOM;
        if(xPos > 18 && xPos < 22 && yPos > 18 && yPos < 22)
            *result = HTTOPLEFT;
        if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > 18 && yPos < 22)
            *result = HTTOPRIGHT;
        if(xPos > 18 && xPos < 22 && yPos > (this->height() - 22) && yPos < (this->height() - 18))
            *result = HTBOTTOMLEFT;
        if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > (this->height() - 22) && yPos < (this->height() - 18))
            *result = HTBOTTOMRIGHT;

        return true;
    }
    return false;
}
