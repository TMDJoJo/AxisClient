#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QVBoxLayout>
#include <QStringList>
#include <QIcon>

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
    InitData();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MainWindow::InitView(){

    ////设置窗体标题栏隐藏并设置位于顶层
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    ////设置导航栏
    QIcon icon(":/Navigation/Resource/Img/Navigation/button.png");
    QStringList list;
    list<<"emma"<<"karl"<<"jame";
    ui->navigation->addNavigationBar(tr("资产"),icon,list);
    ui->navigation->addNavigationBar(tr("装机"),icon,list);
    ui->navigation->addNavigationBar(tr("监控"),icon,list);

    //IWorkScene* ws = new IWorkScene();
    //Q_ASSERT(ws);
    //wrokScenes["Introduce"] = ws;
    WelcomeScene* welcome = new WelcomeScene("welcome");
    AddWorkScene("welcome",welcome);

    TestWorkScene* test1 = new TestWorkScene(tr("资产")+"emma");
    test1->SetText(tr("资产")+"emma");
    AddWorkScene(tr("资产")+"emma",test1);

    TestWorkScene* test2 = new TestWorkScene(tr("资产")+"karl");
    test2->SetText(tr("资产")+"karl");
    AddWorkScene(tr("资产")+"karl",test2);

    TestWorkScene* test3 = new TestWorkScene(tr("资产")+"jame");
    test3->SetText(tr("资产")+"jame");
    AddWorkScene(tr("资产")+"jame",test3);

    ui->stackedWidget->setCurrentIndex(0);
    ui->navigation->addVerticalSpacer();
}

void MainWindow::InitData(){



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
