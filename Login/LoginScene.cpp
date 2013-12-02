#include "LoginScene.h"
#include "ui_LoginScene.h"
#include <QToolButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

#include "./AxisBaseWidget/AErrorWidget.h"

LoginScene::LoginScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginScene)
{
    ui->setupUi(this);

    setWindowTitle(tr("AXIS登录"));

    CreateScene();

    animation_ = new QPropertyAnimation(this, "windowOpacity");
    Q_ASSERT(animation_);
    animation_->setDuration(300);
    animation_->setStartValue(0);
    animation_->setEndValue(1);
    animation_->start();

}

LoginScene::~LoginScene()
{
    delete ui;
    if(NULL == animation_)
        delete animation_,animation_ = NULL;

}
void LoginScene::createTitleBar(){

    QWidget* parent = ui->widgetTitle;
    parent->setMaximumHeight(20);
    parent->setMinimumHeight(20);
    QHBoxLayout *layout = new QHBoxLayout(parent);


    layout->addSpacerItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum));

    ////创建标题栏-设置
    QToolButton* mToolButtonSet = new QToolButton(parent);
    mToolButtonSet->setObjectName("toolButtonSet");
    mToolButtonSet->setAutoRaise(true);
    connect(mToolButtonSet,SIGNAL(clicked()),this,SLOT(doToolButtonSet()));
    layout->addWidget(mToolButtonSet);

    ////创建标题栏-最小化
    QToolButton* mToolButtonMin = new QToolButton(parent);
    mToolButtonMin->setObjectName("toolButtonMin");
    mToolButtonMin->setAutoRaise(true);
    connect(mToolButtonMin,SIGNAL(clicked()),this,SLOT(showMinimized()));
    layout->addWidget(mToolButtonMin);

    ////创建标题栏-推出
    QToolButton* mToolButtonClose = new QToolButton(parent);
    mToolButtonClose->setObjectName("toolButtonClose");
    mToolButtonClose->setAutoRaise(true);
    connect(mToolButtonClose,SIGNAL(clicked()),this,SLOT(doToolButtonClose()));
    layout->addWidget(mToolButtonClose);

    layout->setSpacing(0);
    layout->setContentsMargins(6,0,0,0);
    parent->setLayout(layout);

}
void LoginScene::CreateScene(){
    ////设置窗体标题栏隐藏并设置位于顶层
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ////可获取鼠标跟踪效果
    setMouseTracking(true);

    ////创建标题栏
    createTitleBar();
    ////将焦点设置到对话框上，
    setFocus();

    ui->ledt_passwd->setEchoMode(QLineEdit::Password);

}

void LoginScene::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    mMovePosition = event->globalPos() - pos();
    return QDialog::mousePressEvent(event);
}
void LoginScene::mouseMoveEvent(QMouseEvent *event)
{
    if (mMoveing
        &&(event->buttons()
        &&Qt::LeftButton)
        &&(event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance()
        ){
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void LoginScene::mouseReleaseEvent(QMouseEvent *event)
{
    //设置鼠标为未被按下
    mMoveing = false;
    event->accept();
}

void LoginScene::doToolButtonSet(){

}

void LoginScene::doToolButtonClose(){
    qApp->quit();
}

void LoginScene::on_pbtn_login_clicked()
{
    if(ui->ledt_userName->text() == "a"){
        AErrorWidget::warning(this,tr("密码错误！"));
        //AErrorWidget::information(this,tr("密码错误！"));
    }
    else{
        accept();
    }

}
