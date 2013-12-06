#include "AErrorWidget.h"
#include <QPixmap>
#include <QStyle>
#include <QDebug>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QPainter>
#include <QMessageBox>

AErrorWidget::AErrorWidget(QWidget *parent,int life_time_ms) :
    QWidget(parent),
    destroy_time_(NULL),
    close_button_(NULL),
    icon_label_(NULL),
    ask_label_(NULL),
    animation_(NULL),
    life_(BORNING),
    life_time_(life_time_ms)
{
    //获取主界面的宽度
    parent_height_ = parent->height();
    parent_width_ = parent->width();
    this->resize(parent_width_, parent_height_/8);
    setGeometry(QRect(0,parent_height_-this->height(),parent_width_,parent_height_/8));

    //设置标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);

    //如果这个QWidget直接show，是有背景色的，但是如果放到一个父Widget中时，它就没有了效果。添加如下代码后就可以了：
    this->setAutoFillBackground(true);

    //构建关闭按钮
    close_button_= new QToolButton(this);
    Q_ASSERT(close_button_);
    close_button_->setObjectName("error_widget_close_btn");
    QPixmap close_pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    close_button_->setIcon(close_pix);
    close_button_->setGeometry(parent_width_-20, 0, 20, 20);
    close_button_->setCursor(Qt::PointingHandCursor);
    QObject::connect(close_button_, SIGNAL(clicked()), this, SLOT(CloseWidget()));

    //设置提示图片
    icon_label_ = new QLabel(this);
    Q_ASSERT(icon_label_);
    icon_label_->setObjectName("error_widget_icon");
    icon_label_->setGeometry(QRect(5, 5, 21, 21));
    icon_label_->setScaledContents(true);

    //设置提示信息
    ask_label_ = new QLabel(this);
    Q_ASSERT(ask_label_);
    ask_label_->setObjectName("error_widget_msg");
    ask_label_->setGeometry(QRect(20, 0, parent_width_ - 40, this->height()));
    ask_label_->setAlignment(Qt::AlignCenter);

    ////弹出动画
    animation_ = new QPropertyAnimation(this,"pos");
    Q_ASSERT(animation_);
    animation_->setDuration(400);
    animation_->setStartValue(QPoint(0,parent_height_));
    animation_->setEndValue(QPoint(0,parent_height_-this->height()));
    animation_->start();

    connect(animation_, SIGNAL(finished()), this, SLOT(OnAnimationFinish()));
}
AErrorWidget::~AErrorWidget(){
    if(icon_label_ == NULL)
        delete icon_label_,icon_label_ = NULL;
    if(close_button_ == NULL)
        delete close_button_,close_button_ = NULL;
    if(ask_label_ == NULL)
        delete ask_label_,ask_label_ = NULL;
    if(animation_ == NULL)
        delete animation_,animation_ = NULL;
}

void AErrorWidget::warning(QWidget* parent,
                           const QString& msg,
                           const QPixmap& icon /*= QPixmap(":/Resource/Img/AxisBaseWidget/warning.png"*/,
                           int live_time_ms/* = 2000*/){
    AErrorWidget* warning_widget = new AErrorWidget(parent,live_time_ms);
    Q_ASSERT(warning_widget);
    warning_widget->setObjectName("warning");
    warning_widget->setTipInfo(msg);
    warning_widget->setTipIcon(icon);
    warning_widget->show();
}

void AErrorWidget::information(QWidget* parent,
                           const QString& msg,
                           const QPixmap& icon /*= QPixmap(":/Resource/Img/AxisBaseWidget/information.png"*/,
                           int live_time_ms/* = 2000*/){
    AErrorWidget* warning_widget = new AErrorWidget(parent,live_time_ms);
    Q_ASSERT(warning_widget);
    warning_widget->setObjectName("infromation");
    warning_widget->setTipInfo(msg);
    warning_widget->setTipIcon(icon);
    warning_widget->show();
}

void AErrorWidget::setTipInfo(const QString& info){
    //设置提示信息
    ask_label_->setText(info);
}

void AErrorWidget::setTipIcon(const QPixmap& pixmap){
    icon_label_->setPixmap(pixmap);
}

void AErrorWidget::paintEvent(QPaintEvent*){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

////关闭按钮
void AErrorWidget::CloseWidget(){

    if(life_ == DYING){
        ////死亡过程点击关闭
    }
    else if(life_ == BORNING){
        ////出生中
        ////停止动画
        animation_->setEndValue( QPoint(0,this->pos().y()) );
        animation_->stop();
        animation_->setStartValue(QPoint( 0,this->pos().y() ));
        animation_->setEndValue(QPoint(0,parent_height_));
        animation_->start();
        life_ = DYING;
    }
    else{
        ////活着状态
        animation_->setStartValue(QPoint( 0,parent_height_-this->height() ));
        animation_->setEndValue(QPoint(0,parent_height_));
        animation_->start();
        life_ = DYING;
        disconnect(destroy_time_, SIGNAL(timeout()), this, SLOT(CloseWidget()));
    }

}

////动画播放完成响应函数
void AErrorWidget::OnAnimationFinish(){

    if(life_ == DYING){
        ////死亡结束后销毁自己
        delete this;
    }
    else if(life_ == BORNING){
        ////出生结束后为自己注册定时函数
        life_ = LIVING;
        destroy_time_ = new QTimer(this);
        Q_ASSERT(destroy_time_);
        destroy_time_->start(life_time_);
        connect(destroy_time_, SIGNAL(timeout()), this, SLOT(CloseWidget()));
    }
    else{
        ////活着状态理论上不应该处罚finished信号
    }

}
