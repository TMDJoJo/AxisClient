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
    //��ȡ������Ŀ��
    parent_height_ = parent->height();
    parent_width_ = parent->width();
    this->resize(parent_width_, parent_height_/8);
    setGeometry(QRect(0,parent_height_-this->height(),parent_width_,parent_height_/8));

    //���ñ���������
    this->setWindowFlags(Qt::FramelessWindowHint);

    //������QWidgetֱ��show�����б���ɫ�ģ���������ŵ�һ����Widget��ʱ������û����Ч����������´����Ϳ����ˣ�
    this->setAutoFillBackground(true);

    //�����رհ�ť
    close_button_= new QToolButton(this);
    Q_ASSERT(close_button_);
    close_button_->setObjectName("error_widget_close_btn");
    QPixmap close_pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    close_button_->setIcon(close_pix);
    close_button_->setGeometry(parent_width_-20, 0, 20, 20);
    close_button_->setCursor(Qt::PointingHandCursor);
    QObject::connect(close_button_, SIGNAL(clicked()), this, SLOT(CloseWidget()));

    //������ʾͼƬ
    icon_label_ = new QLabel(this);
    Q_ASSERT(icon_label_);
    icon_label_->setObjectName("error_widget_icon");
    icon_label_->setGeometry(QRect(5, 5, 21, 21));
    icon_label_->setScaledContents(true);

    //������ʾ��Ϣ
    ask_label_ = new QLabel(this);
    Q_ASSERT(ask_label_);
    ask_label_->setObjectName("error_widget_msg");
    ask_label_->setGeometry(QRect(20, 0, parent_width_ - 40, this->height()));
    ask_label_->setAlignment(Qt::AlignCenter);

    ////��������
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
    //������ʾ��Ϣ
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

////�رհ�ť
void AErrorWidget::CloseWidget(){

    if(life_ == DYING){
        ////�������̵���ر�
    }
    else if(life_ == BORNING){
        ////������
        ////ֹͣ����
        animation_->setEndValue( QPoint(0,this->pos().y()) );
        animation_->stop();
        animation_->setStartValue(QPoint( 0,this->pos().y() ));
        animation_->setEndValue(QPoint(0,parent_height_));
        animation_->start();
        life_ = DYING;
    }
    else{
        ////����״̬
        animation_->setStartValue(QPoint( 0,parent_height_-this->height() ));
        animation_->setEndValue(QPoint(0,parent_height_));
        animation_->start();
        life_ = DYING;
        disconnect(destroy_time_, SIGNAL(timeout()), this, SLOT(CloseWidget()));
    }

}

////�������������Ӧ����
void AErrorWidget::OnAnimationFinish(){

    if(life_ == DYING){
        ////���������������Լ�
        delete this;
    }
    else if(life_ == BORNING){
        ////����������Ϊ�Լ�ע�ᶨʱ����
        life_ = LIVING;
        destroy_time_ = new QTimer(this);
        Q_ASSERT(destroy_time_);
        destroy_time_->start(life_time_);
        connect(destroy_time_, SIGNAL(timeout()), this, SLOT(CloseWidget()));
    }
    else{
        ////����״̬�����ϲ�Ӧ�ô���finished�ź�
    }

}
