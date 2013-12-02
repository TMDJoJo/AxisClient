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

    setWindowTitle(tr("AXIS��¼"));

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

    ////����������-����
    QToolButton* mToolButtonSet = new QToolButton(parent);
    mToolButtonSet->setObjectName("toolButtonSet");
    mToolButtonSet->setAutoRaise(true);
    connect(mToolButtonSet,SIGNAL(clicked()),this,SLOT(doToolButtonSet()));
    layout->addWidget(mToolButtonSet);

    ////����������-��С��
    QToolButton* mToolButtonMin = new QToolButton(parent);
    mToolButtonMin->setObjectName("toolButtonMin");
    mToolButtonMin->setAutoRaise(true);
    connect(mToolButtonMin,SIGNAL(clicked()),this,SLOT(showMinimized()));
    layout->addWidget(mToolButtonMin);

    ////����������-�Ƴ�
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
    ////���ô�����������ز�����λ�ڶ���
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ////�ɻ�ȡ������Ч��
    setMouseTracking(true);

    ////����������
    createTitleBar();
    ////���������õ��Ի����ϣ�
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
    //�������Ϊδ������
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
        AErrorWidget::warning(this,tr("�������"));
        //AErrorWidget::information(this,tr("�������"));
    }
    else{
        accept();
    }

}
