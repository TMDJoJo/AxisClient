#include <QPainter>

#include "LogoScene.h"
#include "ui_LogoScene.h"
#include "../MainWindow.h"

LogoScene::LogoScene(QWidget *parent) :
    QWidget(parent),
    main_widget_(NULL),
    ui(new Ui::LogoScene),
    isInit(false)
{
    ui->setupUi(this);
}

LogoScene::~LogoScene()
{
    delete ui;
}

bool LogoScene::Init(MainWindow* main){
    Q_ASSERT(main);
    if(isInit)
        return false;
    isInit = true;
    main_widget_ = main;
    return true;
}

void LogoScene::paintEvent(QPaintEvent*){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LogoScene::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){

        if(isInit){
            main_widget_->ChangeWorkScene("welcome");
        }
    }
}
